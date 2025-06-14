////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///============================================================ Jason Пиратская линейка ================================================================================
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// эпизод 1 - Янтарная лихорадка
void Mtraxx_TerraxReset(int i) // общая функция при провалах
{
	QuestSetCurrentNode("Terrax", "First time");
	CloseQuestHeader("Roger_"+i);
	pchar.questTemp.Mtraxx = "fail";
	if (CheckAttribute(pchar, "GenQuest.HunterLongPause")) DeleteAttribute(pchar, "GenQuest.HunterLongPause");
	// belamour legendary edition забрать флаг обратно
	if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
	{
		DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
		DeleteAttribute(pchar,"perks.list.FlagSpa"); 
		log_info(StringFromKey("Roger_1"));
	}
	if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves")) DeleteAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves");
	if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox")) DeleteAttribute(pchar,"questTemp.Mtraxx.MagicBox");
}

void Mtraxx_JewelryBegin() // старт первого квеста
{
	// девка
	pchar.quest.mtr_sdm_brothel.win_condition.l1 = "location";
	pchar.quest.mtr_sdm_brothel.win_condition.l1.location = "santodomingo_brothel";
	pchar.quest.mtr_sdm_brothel.function = "Mtraxx_SetGabriela";
	// таймер
	SetFunctionTimerCondition("Mtraxx_JewelrySDMOver", 0, 0, 3, false);
}

void Mtraxx_SetGabriela(string qName) // 
{
	chrDisableReloadToLocation = true;
	DoQuestFunctionDelay("Mtraxx_RenameGabriela", 2.0);
}

void Mtraxx_RenameGabriela(string qName) // 
{
	sld = characterFromId("HorseGen_"+reload_location_index+"_2"); // переименуем девку
	sld.name = StringFromKey("Roger_2");
	sld.lastname = StringFromKey("Roger_3");
	AddLandQuestMark(sld, "questmarkmain");
}

void Mtraxx_JewelrySDMOver(string qName) // опоздание по Санто-Доминго
{
	if(bImCasual)
	{
		if(CheckAttribute(pchar,"quest.Mtraxx_JewelrySDMOver.over"))
		DeleteAttribute(pchar,"quest.Mtraxx_JewelrySDMOver.over");
		NewGameTip(StringFromKey("Roger_4"));
		SetFunctionTimerCondition("Mtraxx_JewelrySDMOver", 0, 0, 3, false);
		return;
	}
	DeleteAttribute(pchar, "questTemp.Mtraxx.AffairOfHonor");
	DeleteAttribute(pchar, "questTemp.ZA.Block");
	pchar.quest.mtr_sdm_brothel.over = "yes";
	AddQuestRecord("Roger_1", "2");
	Mtraxx_TerraxReset(1);
	DelMapQuestMarkCity("SantoDomingo");
}

void Mtraxx_JewelryHavanaOver(string qName) // опоздание по Гаване
{
	if(bImCasual)
	{
		if(CheckAttribute(pchar,"quest.Mtraxx_JewelryHavanaOver.over"))
		DeleteAttribute(pchar,"quest.Mtraxx_JewelryHavanaOver.over");
		NewGameTip(StringFromKey("Roger_4"));
		SetFunctionTimerCondition("Mtraxx_JewelryHavanaOver", 0, 0, 7, false);
		return;
	}
	DeleteAttribute(pchar, "GenQuest.PrisonQuestLock");
	pchar.quest.mtr_jewelry_havana.over = "yes";
	AddQuestRecord("Roger_1", "4");
	Mtraxx_TerraxReset(1);
	DelMapQuestMarkCity("Havana");
	DelLandQuestMark(characterFromId("Havana_PortMan"));
	DelLandQuestMark(characterFromId("Havana_tavernkeeper"));
	DelLandQuestMark(characterFromId("Lope"));
	DelLandQuestMarkToPhantom();
}

void Mtraxx_HavanaInfo(string qName) // 
{
	if (pchar.questTemp.Mtraxx != "jewelry_3") return;
	AddQuestRecord("Roger_1", "6");
}

void Mtraxx_CreateOfficer() // ставим Лопе Монторо
{
	if (pchar.questTemp.Mtraxx == "fail") return;
	sld = GetCharacter(NPC_GenerateCharacter("Lope", "sold_spa_16", "man", "man", 25, SPAIN, 15, true, "quest"));
	SetFantomParamFromRank(sld, 25, true);
	sld.name = StringFromKey("Roger_5");
	sld.lastname = StringFromKey("Roger_6");
	sld.dialog.FileName = "Quest\Roger.c";
	sld.dialog.currentnode = "Mtr_officer";
	sld.greeting = "";
	RemoveAllCharacterItems(sld, true);
	LAi_SetStayType(sld);
	ChangeCharacterAddressGroup(sld, "Havana_prison", "goto", "goto9");
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
}

void Mtraxx_TimeclearPrison(string qName) // опоздание по тюрьме
{
	DeleteAttribute(pchar, "GenQuest.PrisonQuestLock");
	AddQuestRecord("Roger_1", "9");
	sld = characterFromId("Lope");
	LAi_CharacterDisableDialog(sld);
	if (GetCharacterIndex("Rosario") != -1)
	{
		sld = characterFromId("Rosario");
		LAi_CharacterDisableDialog(sld);
		sld.lifeday = 0;
	}
	Mtraxx_TerraxReset(1);
	DelMapQuestMarkCity("Havana");
	DelLandQuestMark(characterFromId("Havana_Mayor"));
	DelLandQuestMark(characterFromId("Rosario"));
	DelLandQuestMark(characterFromId("Lope"));
}

void Mtraxx_CreateRosario() // ставим Росарио
{
	if (pchar.questTemp.Mtraxx == "fail") return;
	sld = GetCharacter(NPC_GenerateCharacter("Rosario", "off_spa_3", "man", "man", 25, SPAIN, -1, true, "quest"));
	SetFantomParamFromRank(sld, 25, true);
	sld.name = StringFromKey("Roger_7");
	sld.lastname = StringFromKey("Roger_8");
	sld.dialog.FileName = "Quest\Roger.c";
	sld.dialog.currentnode = "Mtr_rosario";
	sld.greeting = "";
	LAi_SetImmortal(sld, true);
	LAi_SetLoginTime(sld, 16.0, 20.0);
	LAi_SetWarriorType(sld);
	LAi_warrior_DialogEnable(sld, true);
	ChangeCharacterAddressGroup(sld, "Havana_town", "goto", "goto1");
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	AddLandQuestMark(sld, "questmarkmain");
}

void Mtraxx_PrisonerFree(string qName) // пленник свободен
{
	pchar.questTemp.Mtraxx = "jewelry_8";
	sld = characterFromId("Lope");
	LAi_CharacterEnableDialog(sld);
	sld.dialog.currentnode = "Mtr_officer_7";
	AddLandQuestMark(sld, "questmarkmain");
	AddLandQuestMarkToPhantom("havana_prison", "havanaJailOff");
}

void Mtraxx_TimeclearGulf(string qName) // опоздание в залив
{
	if(bImCasual)
	{
		if(CheckAttribute(pchar,"quest.Mtraxx_TimeclearGulf.over"))
			DeleteAttribute(pchar,"quest.Mtraxx_TimeclearGulf.over");
		NewGameTip(StringFromKey("Roger_4"));
		SetFunctionTimerCondition("Mtraxx_TimeclearGulf", 0, 0, 7, false);
		return;
	}
	pchar.quest.mtr_jewelry_gulf.over = "yes";
	AddQuestRecord("Roger_1", "13");
	Mtraxx_TerraxReset(1);
	DelMapQuestMarkShore("Shore53");
}

void Mtraxx_JewelryGulf(string qName) // Кабаньяс в заливе
{	
	pchar.quest.Mtraxx_TimeclearGulf.over = "yes";
	Island_SetReloadEnableGlobal("Santacatalina", false);//на остров нельзя
	bQuestDisableMapEnter = true;//на карту тоже
	pchar.questTemp.Mtraxx.JewQty = 0;
	Group_FindOrCreateGroup("Mtr_Jewhead");
	Group_FindOrCreateGroup("Mtr_Jewwork");
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+5;
	if (iRank > 50) iRank = 50;
	sld = GetCharacter(NPC_GenerateCharacter("Cabanos", "off_spa_2", "man", "man", iRank, SPAIN, -1, true, "quest"));
	FantomMakeCoolSailor(sld, SHIP_SCHOONER_W, StringFromKey("Roger_9"), CANNON_TYPE_CULVERINE_LBS8, 50, 50, 50);
	FantomMakeCoolFighter(sld, iRank, 50, 50, "blade_15", "pistol5", "bullet", 150); // патч 17/1
	sld.name = StringFromKey("Roger_10");
	sld.lastname = StringFromKey("Roger_11");
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true; // патч 17/1
	sld.Ship.Mode = "war";
	sld.AlwaysEnemy = true;
	SetSailsColor(sld, 6);
	sld.ship.Crew.Morale = 40+MOD_SKILL_ENEMY_RATE*4;
	sld.Ship.Crew.Exp.Sailors = 40+MOD_SKILL_ENEMY_RATE*4;
	sld.Ship.Crew.Exp.Cannoners = 40+MOD_SKILL_ENEMY_RATE*4;
	sld.Ship.Crew.Exp.Soldiers = 40+MOD_SKILL_ENEMY_RATE*4;
	SetCharacterPerk(sld, "MusketsShoot");
	Group_AddCharacter("Mtr_Jewhead", "Cabanos");
	Group_SetGroupCommander("Mtr_Jewhead", "Cabanos");
	Group_SetAddress("Mtr_Jewhead", "Santacatalina", "quest_ships", "quest_ship_7");
	Group_SetTaskAttack("Mtr_Jewhead", PLAYER_GROUP);
	Group_LockTask("Mtr_Jewhead");
	
	for (int i=1; i<=5; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Catcher_"+i, "citiz_3"+i, "man", "man", 10, SPAIN, -1, true, "quest"));
		FantomMakeCoolSailor(sld, SHIP_TARTANE, "", CANNON_TYPE_NONECANNON, 30, 30, 30);
		SetFantomParamFromRank(sld, 10, true);
		sld.DontRansackCaptain = true;
		sld.AnalizeShips = true;
		sld.AlwaysEnemy = true;
		sld.JewelryGulf = true;
		sld.PearlTartane = true;
		Character_SetAbordageEnable(sld, false);
		Group_AddCharacter("Mtr_Jewwork", "Catcher_"+i);
	}
	Group_SetGroupCommander("Mtr_Jewwork", "Catcher_1");
	Group_SetAddress("Mtr_Jewwork", "Santacatalina", "quest_ships", "quest_ship_5");
	Group_SetTaskRunaway("Mtr_Jewwork", PLAYER_GROUP);
	Group_LockTask("Mtr_Jewwork");
	
	pchar.quest.mtr_jewgulf_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.mtr_jewgulf_AfterBattle.win_condition.l1.group = "Mtr_Jewhead";
	pchar.quest.mtr_jewgulf_AfterBattle.function = "Mtraxx_JewelryAfterBattle";
	
	pchar.quest.mtr_jewgulf_result.win_condition.l1 = "MapEnter";
	pchar.quest.mtr_jewgulf_result.function = "Mtraxx_JewelryResult";
	
	DelMapQuestMarkShore("Shore53");
}

void Mtraxx_JewelryAfterBattle(string qName) // уничтожили Кабаньяса
{
	bQuestDisableMapEnter = false;
	Group_DeleteGroup("Mtr_Jewhead");
	DoQuestCheckDelay("sea_victory", 1.5);
	ChangeCharacterNationReputation(pchar, SPAIN, -5);
	ChangeCharacterComplexReputation(pchar, "authority", 3);
	ChangeCharacterComplexReputation(pchar, "nobility", -3);
	ChangeCharacterComplexReputation(pchar, "fame", 3);
	OfficersReaction("bad");
	AddComplexSeaExpToScill(150, 50, 50, 50, 70, 70, 0);
	pchar.Cheats.SeaTeleport = true;
}

void Mtraxx_PearlHelpHint(string qName) // подсказка как собирать янтарь с лодочек
{
	NewGameTip(StringFromKey("Roger_12"));
}

void Mtraxx_PearlQuantityHint(string qName) // сколько лодочек собрали
{
	notification(StringFromKey("Roger_13", sti(pchar.questTemp.Mtraxx_SobralVsyo)), "Capacity");
}

void Mtraxx_JewelryResult(string qName) // считаем янтарь
{
	Island_SetReloadEnableGlobal("Santacatalina", true);
	Group_DeleteGroup("Mtr_Jewwork");
	if (sti(pchar.questTemp.Mtraxx_SobralVsyo) != 5)
	{
		DeleteAttribute(pchar, "Cheats.SeaTeleport");
		int i = sti(pchar.questTemp.Mtraxx.JewQty);
		if (i < 1)
		{
			AddQuestRecord("Roger_1", "14");
			Mtraxx_TerraxReset(1);
		}
		else
		{
			if (i < 30)
			{
				AddQuestRecord("Roger_1", "15");
				AddQuestUserData("Roger_1", "sQty", FindRussianQtyString(i));
				Mtraxx_TerraxReset(1);
			}
			else
			{
				AddQuestRecord("Roger_1", "16");
				AddQuestUserData("Roger_1", "sQty", FindRussianQtyString(i));
				QuestSetCurrentNode("Terrax", "mtraxx_7");
				pchar.questTemp.Mtraxx = "jewelry_11";
				AddLandQuestMark(characterFromId("Terrax"), "questmarkmain");
				AddMapQuestMarkCity("LaVega", false);
			}
		}
	}
}

// Эпизод 2 - Шелковый путь

void Mtraxx_SilkBegin() // 
{
	SetFunctionTimerCondition("Mtraxx_SilkCPVOver", 0, 0, 8, false);
	pchar.quest.mtr_silk_jeffry.win_condition.l1 = "location";
	pchar.quest.mtr_silk_jeffry.win_condition.l1.location = "Nevis";
	pchar.quest.mtr_silk_jeffry.function = "Mtraxx_SilkCreateJeffry";
}

void Mtraxx_SilkCPVOver(string qName) // опоздание к Капстервилю
{
	if(bImCasual)
	{
		if(CheckAttribute(pchar,"quest.Mtraxx_SilkCPVOver.over"))
			DeleteAttribute(pchar,"quest.Mtraxx_SilkCPVOver.over");
		NewGameTip(StringFromKey("Roger_4"));
		SetFunctionTimerCondition("Mtraxx_SilkCPVOver", 0, 0, 8, false);
		return;
	}
	pchar.quest.mtr_silk_jeffry.over = "yes";
	AddQuestRecord("Roger_2", "2");
	Mtraxx_TerraxReset(2);
}

void Mtraxx_SilkCreateJeffry(string qName) // создаем Джеффри // 3 прогона
{
	Group_FindOrCreateGroup("Mtr_Jeffry");
	sld = GetCharacter(NPC_GenerateCharacter("Jeffry", "Jeffry", "man", "man", 25, ENGLAND, -1, true, "quest"));
	FantomMakeCoolSailor(sld, SHIP_GALEON_L, StringFromKey("Roger_14"), CANNON_TYPE_CULVERINE_LBS18, 80, 80, 80);
	sld.name = StringFromKey("Roger_15");
	sld.lastname = StringFromKey("Roger_16");
	sld.dialog.FileName = "Quest\Roger.c";
	sld.DeckDialogNode = "Jeffry";
	sld.greeting = "Jeffry_01";
	sld.rank = 28;
	sld.reputation = 15;
	LAi_SetHP(sld, 350, 350);
	SetSelfSkill(sld, 90, 55, 45, 90, 50);
	SetShipSkill(sld, 40, 40, 70, 60, 80, 60, 80, 60, 40);
	SetSPECIAL(sld, 8, 6, 8, 4, 5, 8, 6);
	SetCharacterPerk(sld, "Energaiser");
	SetCharacterPerk(sld, "BasicDefense");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "Gunman");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "BasicBattleState");
	SetCharacterPerk(sld, "AdvancedBattleState");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	SetCharacterPerk(sld, "Carpenter");
	SetCharacterPerk(sld, "ShipSpeedUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "SailsMan");
	SetCharacterPerk(sld, "LongRangeGrappling");
	SetCharacterPerk(sld, "GrapplingProfessional");
	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterPerk(sld, "Doctor1");
	SetCharacterPerk(sld, "Doctor2");
	SetCharacterPerk(sld, "BasicCommerce");
	sld.SuperShooter = true;
	RemoveAllCharacterItems(sld, true);
	GiveItem2Character(sld, "blade_15");
	EquipCharacterbyItem(sld, "blade_15");
	GiveItem2Character(sld, "pistol6");
	EquipCharacterbyItem(sld, "pistol6");
	LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "cartridge");
    TakeNItems(sld, "cartridge", 50);
	TakeNItems(sld, "potion2", 3);
	sld.cirassId = Items_FindItemIdx("cirass2");
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.Ship.Mode = "pirate";
	LAi_SetImmortal(sld, true);
	sld.AlwaysFriend = true;
	sld.ShipEnemyDisable  = true;
	Group_AddCharacter("Mtr_Jeffry", "Jeffry");
	Group_SetGroupCommander("Mtr_Jeffry", "Jeffry");
	Group_SetAddress("Mtr_Jeffry", "Nevis", "quest_ships", "quest_ship_1");
	Group_SetTaskNone("Mtr_Jeffry");
	Group_LockTask("Mtr_Jeffry");
}

void Mtraxx_CreateBilly(string qName) // создаем Билли
{
	if (pchar.questTemp.Mtraxx == "fail") return;
	Group_SetAddress("Mtr_Jeffry", "Nevis", "quest_ships", "quest_ship_6"); // переместить судно Джеффри
	Group_FindOrCreateGroup("Mtr_Billi");
	sld = GetCharacter(NPC_GenerateCharacter("Siplyi", "Billy_Pirt", "man", "man", 25, ENGLAND, -1, true, "quest"));
	FantomMakeCoolSailor(sld, SHIP_TARTANE, StringFromKey("Roger_17"), CANNON_TYPE_NONECANNON, 70, 70, 70);
	FantomMakeCoolFighter(sld, 25, 70, 70, "blade_06", "pistol1", "bullet", 150);
	sld.name = StringFromKey("Roger_18");
	sld.lastname = StringFromKey("Roger_19");
	sld.dialog.FileName = "Quest\Roger.c";
	sld.DeckDialogNode = "Billy";
	sld.greeting = "";
	LAi_SetHP(sld, 250, 250);
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.Ship.Mode = "pirate";
	LAi_SetImmortal(sld, true);
	sld.AlwaysFriend = true;
	sld.ShipEnemyDisable  = true;
	sld.ship.HP = makeint(sti(sld.ship.HP)/2);
	Group_AddCharacter("Mtr_Billi", "Siplyi");
	Group_SetGroupCommander("Mtr_Billi", "Siplyi");
	Group_SetAddress("Mtr_Billi", "Jamaica", "quest_ships", "quest_ship_7");
	Group_SetTaskNone("Mtr_Billi");
	Group_LockTask("Mtr_Billi");
}

void Mtraxx_BillySeaTimeOver(string qName) // прозевали баркас Билли в море
{
	sld = characterFromId("Siplyi");
	sld.DontDeskTalk = true;
	sld.lifeday = 0;
	sld = characterFromId("Jeffry");
	sld.lifeday = 0;
	AddQuestRecord("Roger_2", "10-1"); // правки прогона 3
	Mtraxx_TerraxReset(2);
}

void Mtraxx_BillyTimeOver(string qName) // опоздание к Билли на суше
{
	sld = characterFromId("Siplyi");
	sld.DontDeskTalk = true;
	sld.lifeday = 0;
	pchar.quest.mtr_billy_coast.over = "yes";
	if (GetCharacterIndex("Siplyi1") != -1)
	{
		sld = characterFromId("Siplyi1");
		sld.lifeday = 0;
		LAi_CharacterDisableDialog(sld);
	}
	sld = characterFromId("Jeffry");
	sld.lifeday = 0;
	AddQuestRecord("Roger_2", "10");
	Mtraxx_TerraxReset(2);
}

void Mtraxx_BillyOnCoast(string qName) // Билли на берегу
{
	if (pchar.questTemp.Mtraxx == "fail") return;
	sld = GetCharacter(NPC_GenerateCharacter("Siplyi1", "Billy_Pirt", "man", "man", 25, ENGLAND, -1, true, "quest"));
	FantomMakeCoolFighter(sld, 25, 70, 70, "blade_06", "pistol1", "bullet", 150);
	sld.name = StringFromKey("Roger_18");
	sld.lastname = StringFromKey("Roger_19");
	sld.dialog.FileName = "Quest\Roger.c";
	sld.dialog.currentnode = "Billy_9";
	sld.greeting = "";
	LAi_SetHP(sld, 250, 250);
	LAi_SetWarriorType(sld);
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, "shore35", "goto", "goto1");
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
}

void Mtraxx_BillyTakeShip() // корабельный обмен
{
	ref sld, chr;
	aref arTo, arFrom;
	sld = CharacterFromID("Siplyi");
	chr = CharacterFromID(pchar.GenQuest.CompanionId);			
	DeleteAttribute(sld,"ship");
	sld.ship = "";
	makearef(arTo, sld.ship);
	makearef(arFrom, chr.Ship);
	CopyAttributes(arTo, arFrom);
	SeaAI_SetOfficer2ShipAfterAbordage(sld, chr); 			
	DeleteAttribute(chr,"ship"); // трем корабль
	chr.ship.type = SHIP_NOTUSED;
	RemoveCharacterCompanion(pchar, chr);
	AddPassenger(pchar, chr, false);
	SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_FRIEND);
	SetCrewQuantityFull(sld);
	DeleteAttribute(pchar,"GenQuest.CompanionId");
	RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 1);
	sld.lifeday = 1;
	pchar.quest.mtr_silk_billyremove.win_condition.l1 = "MapEnter";
	pchar.quest.mtr_silk_billyremove.function = "Mtraxx_SilkRemoveBilly";
}

void Mtraxx_SilkRemoveBilly(string qName) // удаляем Билли
{
	sld = CharacterFromID("Siplyi");
	sld.lifeday = 0;
	Group_DeleteGroup("Mtr_Billi");
}

void Mtraxx_SilkCreateSmuggler(string qName) // Утрехт отправляется из Кюрасао
{
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+2;
	if (iRank > 45) iRank = 45;
	Group_FindOrCreateGroup("Mtr_Utreht");
	sld = GetCharacter(NPC_GenerateCharacter("Cap_Utreht", "mercen_19", "man", "man", iRank, ENGLAND, -1, true, "quest"));
	FantomMakeCoolSailor(sld, SHIP_BRIGANTINE, StringFromKey("Roger_20"), CANNON_TYPE_CULVERINE_LBS8, 50, 50, 50);
	FantomMakeCoolFighter(sld, iRank, 50, 50, "blade_13", "pistol5", "bullet", 100);
	sld.name = StringFromKey("Roger_21");
	sld.lastname = StringFromKey("Roger_22");
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.Coastal_Captain = true;
	DeleteAttribute(sld, "SaveItemsForDead");
	sld.Ship.Mode = "pirate";
	SetSailsColor(sld, 2);
	sld.ship.Crew.Morale = 40+MOD_SKILL_ENEMY_RATE*4;
	sld.Ship.Crew.Exp.Sailors = 60+MOD_SKILL_ENEMY_RATE*4;
	sld.Ship.Crew.Exp.Cannoners = 40+MOD_SKILL_ENEMY_RATE*4;
	sld.Ship.Crew.Exp.Soldiers = 40+MOD_SKILL_ENEMY_RATE*4;
	if (MOD_SKILL_ENEMY_RATE > 4) SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterGoods(sld, GOOD_SHIPSILK, 80);

	sld.CompanionEnemyEnable = true;
	sld.mapEnc.type = "war";
	sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.Name = StringFromKey("Roger_23");
	Group_AddCharacter("Mtr_Utreht", "Cap_Utreht");
	Group_SetGroupCommander("Mtr_Utreht", "Cap_Utreht");
	Group_SetTaskAttackInMap("Mtr_Utreht", PLAYER_GROUP);
	Group_LockTask("Mtr_Utreht");
	Map_CreateTrader("Villemstad", "Shore36", "Cap_Utreht", 13);
	
	pchar.quest.mtr_silksmuggler_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.mtr_silksmuggler_AfterBattle.win_condition.l1.group = "Mtr_Utreht";
	pchar.quest.mtr_silksmuggler_AfterBattle.function = "Mtraxx_SilkSmugglerAfterBattle";
	
	SetTimerFunction("Mtraxx_SilkSmugglerFail", 0, 0, 14);
}

void Mtraxx_SilkSmugglerAfterBattle(string qName) // после боя с Утрехт
{
	DeleteQuestCondition("Mtraxx_SilkSmugglerFail");
	Group_DeleteGroup("Mtr_Utreht");
	//Island_SetReloadEnableGlobal("Jamaica", true);
	pchar.quest.mtr_silk_shore.win_condition.l1 = "location";
	pchar.quest.mtr_silk_shore.win_condition.l1.location = "shore36";
	pchar.quest.mtr_silk_shore.function = "Mtraxx_SilkInShore";
	AddQuestRecord("Roger_2", "11");
	pchar.questTemp.Mtraxx = "silk_9";
	AddComplexSeaExpToScill(100, 100, 100, 100, 100, 100, 0);
	ChangeCharacterComplexReputation(pchar, "nobility", -2);
	ChangeCharacterComplexReputation(pchar, "authority", 3);
}

void Mtraxx_SilkInShore(string qName) // высадились в бухте
{
	if (pchar.questTemp.Mtraxx == "fail") return;
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+10;
	if (iRank > 50) iRank = 50;
	pchar.GenQuest.Hunter2Pause = true;
	bQuestDisableMapEnter = false;
	ref rItm = ItemsFromID("fire");
	rItm.shown = true;
	rItm.startLocation = "shore36";
	rItm.startLocator = "goto7";
	CreateFireParticles("goto", "goto7");
	if (CheckAttribute(pchar, "questTemp.Mtraxx.Silkfail"))
	{
		AddQuestRecord("Roger_2", "12");
		DeleteAttribute(pchar, "questTemp.Mtraxx.Silkfail");
		Mtraxx_TerraxReset(2);
	}
	else
	{
		LAi_LocationFightDisable(&Locations[FindLocation("shore36")], true);//запретить драться
		for (int i=1; i<=4; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("Mtr_acceptor_"+i, "citiz_2"+i, "man", "man", 20, ENGLAND, -1, true, "quest"));
			FantomMakeCoolFighter(sld, iRank, 50, 50, "blade_0"+(5+i), "pistol1", "bullet", iRank*5);
			sld.dialog.FileName = "Quest\Roger.c";
			sld.dialog.currentnode = "Mtr_acceptor";
			sld.greeting = "";
			LAi_SetStayType(sld);
			if (i > 1)
			{
				ChangeCharacterAddressGroup(sld, "shore36", "goto", "goto"+(10+i));
				LAi_CharacterDisableDialog(sld);
			}
			else 
			{
				ChangeCharacterAddressGroup(sld, "shore36", "goto", "goto6");
				sld.talker = 9;
			}
		}
	}
}

void Mtraxx_SilkSmugglerOver(string qName) // не нашли Утрехт
{
	if (pchar.questTemp.Mtraxx == "fail") return;
	log_Testinfo("Опоздали!");
	if (sti(pchar.questTemp.Mtraxx.month) < 1)
	{
		log_Testinfo("На второй круг");
		pchar.questTemp.Mtraxx.month = 1;
		int hour = 1+rand(3);
		int day = 13+rand(2);
		pchar.quest.mtr_silk_smuggler.win_condition.l1 = "Timer";
		pchar.quest.mtr_silk_smuggler.win_condition.l1.date.hour  = hour;
		pchar.quest.mtr_silk_smuggler.win_condition.l1.date.day   = day;
		pchar.quest.mtr_silk_smuggler.win_condition.l1.date.month = GetAddingDataMonth(0, 1, 0);
		pchar.quest.mtr_silk_smuggler.win_condition.l1.date.year  = GetAddingDataYear(0, 1, 0);
		pchar.quest.mtr_silk_smuggler.win_condition.l2 = "location";
		pchar.quest.mtr_silk_smuggler.win_condition.l2.location = "Jamaica";
		pchar.quest.mtr_silk_smuggler.function = "Mtraxx_SilkCreateSmuggler";
		// таймер
		pchar.quest.mtr_silk_smuggler_over.win_condition.l1 = "Timer";
		pchar.quest.mtr_silk_smuggler_over.win_condition.l1.date.hour  = hour+2;
		pchar.quest.mtr_silk_smuggler_over.win_condition.l1.date.day   = day;
		pchar.quest.mtr_silk_smuggler_over.win_condition.l1.date.month = GetAddingDataMonth(0, 1, 0);
		pchar.quest.mtr_silk_smuggler_over.win_condition.l1.date.year  = GetAddingDataYear(0, 1, 0);
		pchar.quest.mtr_silk_smuggler_over.function = "Mtraxx_SilkSmugglerOver";
		if(bImCasual) NewGameTip(StringFromKey("Roger_24"));
	}
	else
	{
		pchar.quest.mtr_silk_smuggler_over.win_condition.l1 = "Timer";
		pchar.quest.mtr_silk_smuggler_over.win_condition.l1.date.hour  = 6;
		pchar.quest.mtr_silk_smuggler_over.win_condition.l1.date.day   = 15;
		pchar.quest.mtr_silk_smuggler_over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
		pchar.quest.mtr_silk_smuggler_over.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
		pchar.quest.mtr_silk_smuggler_over.function = "Mtraxx_SilkSmugglerFail";
	}
}

void Mtraxx_SilkSmugglerFail(string qName) // провал по Утрехту
{
	sld = CharacterFromID("Cap_Utreht");
	sld.lifeday = 0;
	DeleteQuestCondition("mtr_silksmuggler_AfterBattle");
	pchar.quest.Mtraxx_BillyTimeOver.over = "yes";
	AddQuestRecord("Roger_2", "13");
	Mtraxx_TerraxReset(2);
}

void Mtraxx_SilkTimeOver(string qName) // вышли 2 месяца
{
	if (pchar.questTemp.Mtraxx == "fail") return;
	if (pchar.questTemp.Mtraxx == "silk_10")
	{
		AddQuestRecord("Roger_2", "16");
		SetFunctionTimerCondition("Mtraxx_SilkTimeLateAll", 0, 0, 10, false);
		pchar.questTemp.Mtraxx.SilkLate = "true";
		pchar.questTemp.Mtraxx = "silk_15"; // к Тираксу
		QuestSetCurrentNode("Terrax", "mtraxx_12");
		// прячем Джеффри
		sld = characterFromId("Jeffry");
		sld.DontDeskTalk = true;
		SetFunctionTimerCondition("Mtraxx_SilkHideJeffry", 0, 0, 1, false);
	}
	else
	{
		sld = characterFromId("Jeffry");
		sld.DontDeskTalk = true;
		sld.lifeday = 0;
		AddQuestRecord("Roger_2", "18");
		Mtraxx_TerraxReset(2);
	}
}

void Mtraxx_SilkTimeLateAll(string qName) // опоздали полностью
{
	DeleteAttribute(pchar, "questTemp.Mtraxx.SilkLate");
	AddQuestRecord("Roger_2", "17");
	Mtraxx_TerraxReset(2);
}

void Mtraxx_CargoSilk() // выгрузка шелка
{
	SetLaunchFrameFormParam(StringFromKey("Roger_25", NewStr()), "", 0, 5);
	LaunchFrameForm();
	WaitDate("", 0, 0, 0, 1, 10); //крутим время
	RecalculateJumpTable();
	DoQuestFunctionDelay("Mtraxx_CargoSilkExit", 5.5);
}

void Mtraxx_CargoSilkExit(string qName) // расчет
{
	int iQty = GetSquadronGoods(pchar, GOOD_SHIPSILK);
	RemoveCharacterGoods(pchar, GOOD_SHIPSILK, iQty);
	AddMoneyToCharacter(pchar, iQty*2500);
	sld = characterFromId("Mtr_acceptor_1");
	sld.dialog.currentnode = "Mtr_acceptor_5";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 1.0, -1);
}

void Mtraxx_CargoSilkWin() // чистим покупателей
{
	for (int i=1; i<=4; i++)
	{
		sld = characterFromId("Mtr_acceptor_"+i);
		sld.lifeday = 0;
		LAi_CharacterDisableDialog(sld);
	}
	pchar.quest.mtr_cargosilk_clear.win_condition.l1 = "ExitFromLocation";
	pchar.quest.mtr_cargosilk_clear.win_condition.l1.location = pchar.location;
	pchar.quest.mtr_cargosilk_clear.function = "Mtraxx_CargoSilkClear";
}

void Mtraxx_CargoSilkClear(string qName) // чистим покупателей
{
	LAi_LocationFightDisable(&Locations[FindLocation("shore36")], false);
	ref rItm = ItemsFromID("fire");
	rItm.shown = false;
	AddQuestRecord("Roger_2", "15");
	pchar.questTemp.Mtraxx = "silk_10"; // покупатель найден
	sld = characterFromId("Jeffry");
	sld.DeckDialogNode = "Jeffry_9";
}

void Mtraxx_SilkSmugglerPatrol(string qName) // сдали губеру
{
	pchar.questTemp.Mtraxx = "silk_12";
}

void Mtraxx_SilkPay(string qName) // 
{
	QuestSetCurrentNode("Terrax", "mtraxx_16");
}

/*void Mtraxx_SilkPayLate(string qName) // 
{
	QuestSetCurrentNode("Terrax", "mtraxx_22");
}*/

void Mtraxx_SilkHideJeffry(string qName) // прячем Джеффри
{
	Group_SetAddress("Mtr_Jeffry", "Jamaica", "quest_ships", "quest_ship_7");
	Group_DelCharacter("Mtr_Jeffry", "Jeffry");
	Group_DeleteGroup("Mtr_Jeffry");
}

void Mtraxx_SilkTradeOver(string qName) // 
{
	DeleteAttribute(pchar, "questTemp.Mtraxx.SilkTrade");
}

// эпизод 3: Жаркое солнце Маракайбо

void Mtraxx_PlantBegin() // старт плантации
{
	SetFunctionTimerCondition("Mtraxx_PlantLate", 0, 0, 30, false);
	pchar.quest.mtr_plant_pelly.win_condition.l1 = "location";
	pchar.quest.mtr_plant_pelly.win_condition.l1.location = "Barbados";
	pchar.quest.mtr_plant_pelly.function = "Mtraxx_PlantCreatePelly";
	pchar.questTemp.Mtraxx = "plant_1";
}

void Mtraxx_PlantLate(string qName) // опоздали
{
	if(bImCasual)
	{
		if(CheckAttribute(pchar,"quest.Mtraxx_PlantLate.over"))
			DeleteAttribute(pchar,"quest.Mtraxx_PlantLate.over");
		NewGameTip(StringFromKey("Roger_4"));
		SetFunctionTimerCondition("Mtraxx_PlantLate", 0, 0, 30, false);
		return;
	}
	pchar.quest.mtr_plant_pelly.over = "yes";
	AddQuestRecord("Roger_3", "2");
	Mtraxx_TerraxReset(3);
}
// belamour legendary edition -->
void MtraxxGiveMeSlavesKapsterInShore(string qName) //покупка рабов у контриков
{
	pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.over = "yes";
	pchar.quest.Mtraxx_GiveMeSlavesKapster.over = "yes";
	chrDisableReloadToLocation = true;//закрыть локацию
	LAi_LocationFightDisable(&Locations[FindLocation("Shore29")], true); // запретить драться
	for(i=1; i<=3; i++)
	{
		if(i == 1) sld = GetCharacter(NPC_GenerateCharacter("Mtraxx_SlavesSeller"+i, "citiz_29", "man", "man", 20, FRANCE, -1, true, "soldier"));
		else sld = GetCharacter(NPC_GenerateCharacter("Mtraxx_SlavesSeller"+i, "citiz_"+(22+i), "man", "man", 20, FRANCE, -1, true, "soldier"));
		SetFantomParamFromRank(sld, 20, true);
		sld.Dialog.Filename = "Quest\Roger.c";
		sld.dialog.currentnode = "SlavesTrader";
		sld.greeting = "smuggler";
		LAi_SetImmortal(sld, true);
		LAi_SetActorType(sld);
		GetCharacterPos(pchar, &locx, &locy, &locz);
		ChangeCharacterAddressGroup(sld, "Shore29", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		if(i != 1) LAi_CharacterDisableDialog(sld);
	}
}

void MtraxxGiveMeSlavesKapsterInShoreLate(string qName) //опоздание к контре
{
	if(bImCasual)
	{
		if(CheckAttribute(pchar,"quest.MtraxxGiveMeSlavesKapsterInShoreLate.over"))
			DeleteAttribute(pchar,"quest.MtraxxGiveMeSlavesKapsterInShoreLate.over");
		NewGameTip(StringFromKey("Roger_4"));
		SetFunctionTimerCondition("MtraxxGiveMeSlavesKapsterInShoreLate", 0, 0, 1, false);
		return;
	}
	pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.over = "yes";
	pchar.quest.Mtraxx_GiveMeSlavesKapster.over = "yes";
	DeleteAttribute(&locations[FindLocation("Shore29")],"DisableEncounters"); //энкаунтеры открыть
	AddQuestRecord("Roger_3", "24");
	pchar.questTemp.Mtraxx.GiveMeSlaves = "WithoutSlaves";
}
// <-- legendary edition

void Mtraxx_PlantCreatePelly(string qName) // ставим Пелли
{
	pchar.quest.Mtraxx_PlantLate.over = "yes";
	Island_SetReloadEnableGlobal("Barbados", false);
	bQuestDisableMapEnter = true;
	pchar.GenQuest.MapClosedNoBattle = true;
	Group_FindOrCreateGroup("PellyGroup");
	Group_SetType("PellyGroup", "pirate");//тип группы
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+10;
	if (iRank > 50) iRank = 50;
	sld = GetCharacter(NPC_GenerateCharacter("Pelly_sea", "Tesak", "man", "man", iRank, ENGLAND, -1, true, "quest"));
	FantomMakeCoolSailor(sld, SHIP_BARKENTINE, StringFromKey("Roger_26"), CANNON_TYPE_CANNON_LBS12, 65, 65, 65);
	FantomMakeCoolFighter(sld, iRank, 65, 65, "blade_06", "pistol3", "grapeshot", 200);
	sld.name = StringFromKey("Roger_27");
	sld.lastname = StringFromKey("Roger_28");
	sld.dialog.FileName = "Quest\Roger.c";
	sld.DeckDialogNode = "Pelly";
	sld.greeting = "Pelly_01";
	sld.rank = 25;
	sld.reputation = 10;
	LAi_SetHP(sld, 450, 450);
	SetSelfSkill(sld, 50, 90, 55, 90, 50);
	SetShipSkill(sld, 30, 40, 70, 70, 66, 50, 90, 50, 50);
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	LAi_SetImmortal(sld, true);
	sld.AlwaysFriend = true;
	sld.ShipEnemyDisable = true;
	sld.Ship.Mode = "pirate";
	SetSailsColor(sld, 8);
	sld.ship.Crew.Morale = 70;
	sld.Ship.Crew.Exp.Sailors = 70;
	sld.Ship.Crew.Exp.Cannoners = 70;
	sld.Ship.Crew.Exp.Soldiers = 100;
	SetCharacterPerk(sld, "MusketsShoot");
	Group_AddCharacter("PellyGroup", "Pelly_sea");
	Group_SetGroupCommander("PellyGroup", "Pelly_sea");
	Group_SetTaskNone("PellyGroup");
	Group_SetAddress("PellyGroup", "Barbados", "quest_ships", "quest_ship_5");
	Group_LockTask("PellyGroup");
}

void Mtraxx_PlantContinue() // в Маракайбо
{
	SetFunctionTimerCondition("Mtraxx_PlantLate_1", 0, 0, 15, false);
	Island_SetReloadEnableGlobal("Barbados", true);
	bQuestDisableMapEnter = false;
	DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
	Group_SetTaskRunAway("PellyGroup", PLAYER_GROUP);
	Group_LockTask("PellyGroup");
	pchar.quest.mtr_plant_maracaibo.win_condition.l1 = "location";
	pchar.quest.mtr_plant_maracaibo.win_condition.l1.location = "Maracaibo";
	pchar.quest.mtr_plant_maracaibo.function = "Mtraxx_PlantMaracaiboArrive";
	pchar.quest.mtr_plant_pelly1.win_condition.l1 = "ExitFromLocation";
	pchar.quest.mtr_plant_pelly1.win_condition.l1.location = pchar.location;
	pchar.quest.mtr_plant_pelly1.function = "Mtraxx_PlantPellyRun";
	pchar.questTemp.Mtraxx = "plant_2";
}

void Mtraxx_PlantLate_1(string qName) // 
{
	if(bImCasual)
	{
		if(CheckAttribute(pchar,"quest.Mtraxx_PlantLate_1.over"))
			DeleteAttribute(pchar,"quest.Mtraxx_PlantLate_1.over");
		NewGameTip(StringFromKey("Roger_4"));
		SetFunctionTimerCondition("Mtraxx_PlantLate_1", 0, 0, 15, false);
		return;
	}
	pchar.quest.mtr_plant_pelly1.over = "yes";
	pchar.quest.Mtraxx_PlantPellyArrive.over = "yes";
	AddQuestRecord("Roger_3", "4");
	Mtraxx_TerraxReset(3);
	Mtraxx_PlantPellyClear();
} 

void Mtraxx_PlantPellyRun(string qName) // 
{
	SetFunctionTimerCondition("Mtraxx_PlantPellyArrive", 0, 0, 6+rand(2), false);
	Group_SetAddress("PellyGroup", "Curacao", "quest_ships", "quest_ship_6"); 
} 

void Mtraxx_PlantPellyArrive(string qName) // 3 прогона
{
	Group_SetAddress("PellyGroup", "Maracaibo", "quest_ships", "quest_ship_4");
	Group_SetTaskNone("PellyGroup");
	Group_LockTask("PellyGroup");
	ref loc = &Locations[FindLocation("shore37")];
	loc.DisableEncounters = true; //энкаутеры закрыть
	ref rItm = ItemsFromID("fire");
	rItm.shown = true;
	rItm.startLocation = "shore37";
	rItm.startLocator = "fire";
	loc.fire = true;
	LAi_LocationFightDisable(&Locations[FindLocation("shore37")], true);//запретить драться
	for (int i=1; i<=4; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Pelly_sailor_"+i, "citiz_2"+i, "man", "man", 25, ENGLAND, -1, true, "quest"));
		FantomMakeCoolFighter(sld, 25, 50, 50, "blade_0"+(5+i), "pistol1", "bullet", 100);
		LAi_SetWarriorType(sld);
		LAi_CharacterDisableDialog(sld);
		ChangeCharacterAddressGroup(sld, "shore37", "goto", "goto"+i);
	}
	// клон Пелли - сухопутный
	sld = GetCharacter(NPC_GenerateCharacter("Pelly", "Tesak", "man", "man", 25, PIRATE, -1, false, "quest"));
	sld.name = StringFromKey("Roger_27");
	sld.lastname = StringFromKey("Roger_28");
	sld.greeting = "Pelly_02";
	sld.Dialog.Filename = "Quest\Roger.c";
	sld.dialog.currentnode = "Pelly_7";
	sld.rank = 25;
	sld.reputation = 10;
	LAi_SetHP(sld, 450, 450);
	SetSelfSkill(sld, 50, 90, 55, 90, 50);
	SetShipSkill(sld, 30, 40, 70, 70, 66, 50, 90, 50, 50);
	SetSPECIAL(sld, 10, 6, 10, 3, 3, 10, 5);
	SetCharacterPerk(sld, "Energaiser");
	SetCharacterPerk(sld, "BasicDefense");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "BladeDancer");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "Gunman");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "BasicBattleState");
	SetCharacterPerk(sld, "AdvancedBattleState");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	SetCharacterPerk(sld, "Carpenter");
	SetCharacterPerk(sld, "ShipSpeedUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "WindCatcher");
	SetCharacterPerk(sld, "LongRangeGrappling");
	SetCharacterPerk(sld, "GrapplingProfessional");
	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterPerk(sld, "Doctor1");
	SetCharacterPerk(sld, "Doctor2");
	SetCharacterPerk(sld, "BasicCommerce");
	sld.SuperShooter = true;
	RemoveAllCharacterItems(sld, true);
	GiveItem2Character(sld, "blade_10");
	EquipCharacterbyItem(sld, "blade_10");
	GiveItem2Character(sld, "pistol4");
	EquipCharacterbyItem(sld, "pistol4");
	LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "cartridge");
    TakeNItems(sld, "cartridge", 50);
	TakeNItems(sld, "potion2", 10);
	sld.cirassId = Items_FindItemIdx("cirass1");
	LAi_SetStayType(sld);
	LAi_CharacterEnableDialog(sld);
	sld.dialog.currentnode = "Pelly_7";
	ChangeCharacterAddressGroup(sld, "shore37", "goto", "goto6");
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER); // 3 прогона
} 

void Mtraxx_PlantPellyClear() // чистим Пелли
{
	LAi_LocationFightDisable(&Locations[FindLocation("shore37")], false);//разрешить драться
	Group_DeleteGroup("PellyGroup");
	sld = characterFromId("Pelly_sea");
	sld.lifeday = 0;
	if (GetCharacterIndex("Pelly") != -1)
	{
		sld = characterFromId("Pelly");
		sld.lifeday = 0;
	}
	for (int i=1; i<=4; i++)
	{
		if (GetCharacterIndex("Pelly_sailor_"+i) != -1)
		{
			sld = characterFromId("Pelly_sailor_"+i);
			sld.lifeday = 0;
		}
	}
	ref loc = &Locations[FindLocation("shore37")];
	loc.DisableEncounters = false;
	ref rItm = ItemsFromID("fire");
	rItm.shown = false;
	DeleteAttribute(loc, "fire");
} 

void Mtraxx_PlantMaracaiboArrive(string qName) // прибыли к Маракайбо
{
	pchar.GenQuest.HunterLongPause = true;
	pchar.quest.Mtraxx_PlantLate_1.over = "yes";
	pchar.questTemp.Mtraxx = "plant_2";
	SetFunctionTimerCondition("Mtraxx_PlantPrepareTimeOver", 0, 0, 10, false);
	// готовим плантацию Маракайбо. Управляющий
	sld = GetCharacter(NPC_GenerateCharacter("Mtr_plantation_boss", "citiz_20", "man", "man", 15, SPAIN, -1, false, "soldier"));
	SetFantomParamFromRank(sld, 15, true);
	sld.Dialog.Filename = "Plantation_dialog.c";
	sld.Dialog.currentnode = "plantator";
	RemoveAllCharacterItems(sld, true);
	LAi_SetLoginTime(sld, 6.0, 22.99);
	ChangeCharacterAddressGroup(sld, "Maracaibo_Plantation_Sp1", "barmen", "stay");
	LAi_SetOwnerType(sld);
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	// типа пленные пираты, 5 штук
	for (int i=4; i<=8; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Mtr_plantation_prisoner_"+i, "citiz_4"+i, "man", "man", 15, PIRATE, 30, false, "soldier"));
		SetFantomParamFromRank(sld, 15, true);
		sld.Dialog.Filename = "Plantation_dialog.c";
		sld.Dialog.currentnode = "pirate_slave";
		sld.greeting = ""; 
		LAi_SetLoginTime(sld, 6.0, 22.99);
		RemoveAllCharacterItems(sld, true);
		ChangeCharacterAddressGroup(sld, "Maracaibo_Plantation", "goto", "goto"+i);
		LAi_SetCitizenType(sld);
		LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	}
}

void Mtraxx_PlantPrepareTimeOver(string qName) // стал заниматься фигней вместо дела
{
	if(bImCasual)
	{
		if(CheckAttribute(pchar,"quest.Mtraxx_PlantPrepareTimeOver.over"))
			DeleteAttribute(pchar,"quest.Mtraxx_PlantPrepareTimeOver.over");
		NewGameTip(StringFromKey("Roger_4"));
		SetFunctionTimerCondition("Mtraxx_PlantPrepareTimeOver", 0, 0, 10, false);
		return;
	}
	sld = characterFromId("Mtr_plantation_boss");
	sld.lifeday = 0;
	if (GetCharacterIndex("Mrt_Rocur") != -1)
	{
		sld = characterFromId("Mrt_Rocur");
		sld.lifeday = 0;
	}
	if (GetCharacterIndex("Mrt_Rocur_clone") != -1)
	{
		sld = characterFromId("Mrt_Rocur_clone");
		sld.lifeday = 0;
	}
	AddQuestRecord("Roger_3", "4-1");
	Mtraxx_PlantPellyClear();
	Mtraxx_TerraxReset(3);
}

void Mtraxx_PlantSetMaxRocur() // ставим Жана Пикара
{
	sld = GetCharacter(NPC_GenerateCharacter("Mrt_Rocur", "Jan_Slave", "man", "man", 20, PIRATE, -1, false, "soldier"));
	sld.name = StringFromKey("Roger_29");
	sld.lastname = StringFromKey("Roger_30");
	sld.Dialog.Filename = "Quest\Roger.c";
	sld.Dialog.currentnode = "rocur";
	sld.greeting = "Rocur_01"; 
	sld.rank = 20;
	sld.reputation = 30;
	LAi_SetHP(sld, 300.0, 300.0);
	SetSPECIAL(sld, 7, 6, 8, 6, 8, 7, 5);
	SetSelfSkill(sld, 45, 85, 55, 50, 55);
    SetShipSkill(sld, 50, 60, 60, 60, 70, 60, 70, 60, 55);
	SetCharacterPerk(sld, "Energaiser");
	SetCharacterPerk(sld, "BasicDefense");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Gunman");
	SetCharacterPerk(sld, "ShipSpeedUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "BasicBattleState");
	SetCharacterPerk(sld, "Doctor1");
	SetCharacterPerk(sld, "BasicCommerce");
	SetCharacterPerk(sld, "AdvancedCommerce");
	sld.SuperShooter = true;
	LAi_SetImmortal(sld, true);
	LAi_SetLoginTime(sld, 6.0, 22.99);
	RemoveAllCharacterItems(sld, true);
	ChangeCharacterAddressGroup(sld, "Maracaibo_Plantation", "goto", "goto10");
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves")) DeleteAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves");
}

void Mtraxx_PlantMakeMaxRocurClone() // ставим клон Жана Пикара
{
	sld = GetCharacter(NPC_GenerateCharacter("Mrt_Rocur_clone", "Jan_Slave", "man", "man", 20, PIRATE, -1, false, "soldier"));
	SetFantomParamFromRank(sld, 15, true);
	sld.name = StringFromKey("Roger_29");
	sld.lastname = StringFromKey("Roger_30");
	sld.Dialog.Filename = "Quest\Roger.c";
	sld.Dialog.currentnode = "rocur_4";
	sld.greeting = "Rocur_01";
	sld.rank = 20;
	LAi_SetHP(sld, 300.0, 300.0);
	LAi_SetImmortal(sld, true);
	LAi_SetLoginTime(sld, 23.0, 5.99);
	RemoveAllCharacterItems(sld, true);
	ChangeCharacterAddressGroup(sld, "Maracaibo_Plantation_S2", "goto", "goto1");
	LAi_SetStayType(sld);
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
}

void Mtraxx_PlantCheckShoreBox() // анализ содержимого сундука
{
	int iBlade, iGun, iMushket, iPotion, iBullet, iGunpowder, iCartridge, iShot;
	iBlade = 0;
	string sBlade;
	if (!CheckAttribute(pchar, "questTemp.Mtraxx.Weapon.Blade") && GetSquadronGoods(pchar, GOOD_WEAPON) >= 30)
	{
		PlaySound("interface\notebook.wav");
		RemoveCharacterGoods(pchar, GOOD_WEAPON, 30);
		pchar.questTemp.Mtraxx.Weapon.Blade = "true";
		int n = Findlocation("Shore37");
		locations[n].private1.items.Bunch = 1;
		log_info(StringFromKey("Roger_31"));
		log_info(StringFromKey("Roger_32"));
	}
	if (CheckAttribute(pchar, "questTemp.Mtraxx.Weapon.Blade"))
	{
		DeleteAttribute(pchar, "questTemp.Mtraxx.Weapon.NoBlade");
		iBlade = CheckItemInBox("Bunch", "Shore37", "private1");
		if (iBlade > 0) log_info(StringFromKey("Roger_32"));
		else 
		{
			pchar.questTemp.Mtraxx.Weapon.NoBlade = "true";
			log_info(StringFromKey("Roger_33"));
		}
	}
	iGun = 0;
	iGun = iGun+CheckItemInBox("pistol1", "Shore37", "private1");
	log_info(StringFromKey("Roger_34", FindRussianQtyString(iGun)));
	pchar.questTemp.Mtraxx.Weapon.Gun = iGun;
	iMushket = 0;
	iMushket = iMushket+CheckItemInBox("mushket1", "Shore37", "private1");
	log_info(StringFromKey("Roger_35", FindRussianQtyString(iMushket)));
	pchar.questTemp.Mtraxx.Weapon.Mushket = iMushket;
	iPotion = 0;
	iPotion = iPotion+CheckItemInBox("potion1", "Shore37", "private1");
	iPotion = iPotion+CheckItemInBox("potion2", "Shore37", "private1");
	log_info(StringFromKey("Roger_36", FindRussianQtyString(iPotion)));
	pchar.questTemp.Mtraxx.Weapon.Potion = iPotion;
	iBullet = 0;
	iBullet = iBullet+CheckItemInBox("bullet", "Shore37", "private1");
	iGunpowder = 0;
	iGunpowder = iGunpowder+CheckItemInBox("Gunpowder", "Shore37", "private1");
	iCartridge = 0;
	iCartridge = iCartridge+CheckItemInBox("Cartridge", "Shore37", "private1");
	if (iBullet > iGunpowder || iBullet == iGunpowder) iShot = iGunpowder;
	else iShot = iBullet;
	iShot = iShot+iCartridge;
	log_info(StringFromKey("Roger_37", iShot));
	pchar.questTemp.Mtraxx.Weapon.Shot = iShot;
}

void Mtraxx_PlantShoreBoxComplete() // сбор оружия окончен
{
	// belamour legendary edition вернуть обратно, что сами насобирали -->
	if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "Full")
	{
		TakeNItems(pchar, "pistol1", CheckItemInBox("pistol1", "Shore37", "private1"));
		TakeNItems(pchar, "mushket1", CheckItemInBox("mushket1", "Shore37", "private1"));
		TakeNItems(pchar, "potion1", CheckItemInBox("potion1", "Shore37", "private1"));
		TakeNItems(pchar, "potion2", CheckItemInBox("potion2", "Shore37", "private1"));
		TakeNItems(pchar, "bullet", CheckItemInBox("bullet", "Shore37", "private1"));
		TakeNItems(pchar, "Gunpowder", CheckItemInBox("Gunpowder", "Shore37", "private1"));
		TakeNItems(pchar, "Cartridge", CheckItemInBox("Cartridge", "Shore37", "private1"));
		pchar.questTemp.Mtraxx.Weapon.Gun = 30;
		pchar.questTemp.Mtraxx.Weapon.Mushket = 2;
		pchar.questTemp.Mtraxx.Weapon.Potion = 90;
		pchar.questTemp.Mtraxx.Weapon.Shot = 70;
		DeleteAttribute(pchar,"questTemp.Mtraxx.MagicBox");
		SendMessage(&ILogAndActions,"l",LI_CLEAR_STRINGS);
		log_info(StringFromKey("Roger_38"));
		log_info(StringFromKey("Roger_39"));
		log_info(StringFromKey("Roger_40"));
		log_info(StringFromKey("Roger_41"));
	}
	// <-- legendary edition
	DeleteAttribute(pchar, "questTemp.Mtraxx.Ammo");
	pchar.questTemp.Mtraxx = "plant_5";
	AddQuestRecord("Roger_3", "8");
	// закрыть сундук
	ref loc = &Locations[FindLocation("Shore37")];
	DeleteAttribute(loc, "private1.opened");
	loc.private1.closed = true;
	if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox")) DeleteAttribute(pchar,"questTemp.Mtraxx.MagicBox");
}
// belamour legendary edition -->
void Mtraxx_MagicBoxready(string qName) // Ящик Фадея готов
{
	pchar.questTemp.Mtraxx.MagicBox = "Today";
}
//<-- legendary edition

void Mtraxx_PlantFindRocurDay(string qName) // ищем Жана Пикара днем
{
	chrDisableReloadToLocation = true;
	sld = characterFromId("Mrt_Rocur");
	LAi_CharacterEnableDialog(sld);
	sld.dialog.currentnode = "rocur_25";
	sld.greeting = "Rocur_02";
	AddLandQuestMark(sld, "questmarkmain");
}	

void Mtraxx_SeekWeaponOver(string qName) // истек месяц на сбор оружия
{
	if(bImCasual)
	{
		if(CheckAttribute(pchar,"quest.Mtraxx_SeekWeaponOver.over"))
			DeleteAttribute(pchar,"quest.Mtraxx_SeekWeaponOver.over");
		NewGameTip(StringFromKey("Roger_4"));
		SetFunctionTimerCondition("Mtraxx_SeekWeaponOver", 0, 0, 30, false);
		return;
	}
	DeleteAttribute(pchar, "questTemp.Mtraxx.Weapon");
	pchar.quest.mtraxx_plant_goods.over = "yes";
	DeleteAttribute(pchar, "GenQuest.CannotWait");
	sld = characterFromId("Mtr_plantation_boss");
	sld.lifeday = 0;
	sld = characterFromId("Mrt_Rocur");
	sld.lifeday = 0;
	sld = characterFromId("Mrt_Rocur_clone");
	sld.lifeday = 0;
	AddQuestRecord("Roger_3", "16");
	Mtraxx_PlantPellyClear();
	Mtraxx_TerraxReset(3);
}

void Mtraxx_PlantPlantVykup_1(string qName)
{
	
	sld = characterFromId("Pelly");
	sld.dialog.currentnode = "Pelly_54";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 0, 0);
}

void Mtraxx_PlantPlantVykup_2(string qName)
{
	Achievment_Set("ach_CL_144");
	pchar.quest.Mtraxx_SeekWeaponOver.over = "yes";
	sld = characterFromId("Mrt_Rocur");
	LAi_RemoveLoginTime(sld);
	LAi_CharacterEnableDialog(sld);
	ChangeCharacterAddressGroup(sld, "Maracaibo_ExitTown", "rld", "loc18");
	sld.dialog.filename = "Quest\Roger.c";
	sld.dialog.currentnode = "rocur_104";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 0, 0);
}

void Mtraxx_PlantPlantVykup_3(string qName)
{
	
	sld = characterFromId("Pelly");
	sld.dialog.currentnode = "Pelly_59";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 0, 0);
	
	sld = characterFromId("Mrt_Rocur");
	ChangeCharacterAddressGroup(sld, "Shore37", "goto", "goto6");
}
	
void Mtraxx_PlantWaitDay(string qName) // крутим время до 21 ч следующего дня
{
	pchar.quest.Mtraxx_SeekWeaponOver.over = "yes"; // снимаем таймер на поиск оружия релиз-правка
	bDisableCharacterMenu = true;//лочим F2
	pchar.GenQuest.FrameLockEsc = true; // закрыть ESC
	int iTime, iAddTime;
	iTime = sti(environment.time);
	if (iTime >= 21) iAddTime = 24 - iTime;
	if (iTime < 7) iAddTime = 21 - iTime;
	if (iTime >= 7 && iTime < 21) iAddTime = 21 - iTime;
	SetLaunchFrameFormParam(StringFromKey("Roger_42"), "Mtraxx_PlantWaitDay", 0, 5);
	LaunchFrameForm();
	StoreDayUpdate();
	WaitDate("",0,0,1,iAddtime,5);
	RecalculateJumpTable();
	RefreshWeather();
	RefreshLandTime();
}	
	
void Mtraxx_PlantAfterTrading() // поторговали, на выход
{
	bDisableCharacterMenu = false; // разлочим F2
	DeleteAttribute(pchar, "GenQuest.FrameLockEsc");
	chrDisableReloadToLocation = false;
	sld = characterFromId("Mtr_plantation_boss");
	sld.lifeday = 0;
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "houseSp1", "none", "", "", "", 20.0);
	AddQuestRecord("Roger_3", "12");
	pchar.quest.Mtraxx_SeekWeaponOver.over = "yes"; // снимаем таймер на поиск оружия
	pchar.quest.Mtraxx_TimerPlantMutiny.win_condition.l1 = "Timer";
	pchar.quest.Mtraxx_TimerPlantMutiny.win_condition.l1.date.hour  = 0.0;
	pchar.quest.Mtraxx_TimerPlantMutiny.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
	pchar.quest.Mtraxx_TimerPlantMutiny.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
	pchar.quest.Mtraxx_TimerPlantMutiny.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
	pchar.quest.Mtraxx_TimerPlantMutiny.function = "Mtraxx_PlantShoreTimeOver";
	sld = CharacterFromID("Pelly");
	LAi_SetStayType(sld);
	sld.dialog.currentnode = "Pelly_7";
	pchar.questTemp.Mtraxx = "plant_8";
	if(bImCasual) NewGameTip(StringFromKey("Roger_24"));
}		
	
void Mtraxx_PlantShoreTimeOver(string qName) // не явился в бухту до полуночи либо без корабля
{
	DeleteAttribute(pchar, "questTemp.Mtraxx.Weapon");
	DeleteAttribute(pchar, "GenQuest.CannotWait");
	sld = characterFromId("Mrt_Rocur");
	sld.lifeday = 0;
	sld = characterFromId("Mrt_Rocur_clone");
	sld.lifeday = 0;
	AddQuestRecord("Roger_3", "13");
	Mtraxx_PlantPellyClear();
	Mtraxx_TerraxReset(3);
}	
	
void Mtraxx_PlantPrepareMarch() // к походу
{
	DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
	pchar.questTemp.Mtraxx = "plant_9";
	LocatorReloadEnterDisable("shore37", "boat", true); // закрыть выход в море
	LocatorReloadEnterDisable("Maracaibo_ExitTown", "reload4", true); // закрыть вход в город
	LocatorReloadEnterDisable("Maracaibo_ExitTown", "reload3_back", true); // закрыть вход в форт
	pchar.quest.Mtraxx_TimerPlantMutiny.over = "yes"; // снимаем таймер на полночь
	int i = 0;
	if (stf(environment.time) < 24.00) i = 1;
	pchar.quest.Mtraxx_enterPlantMutiny.win_condition.l1 = "location";
	pchar.quest.Mtraxx_enterPlantMutiny.win_condition.l1.location = "Maracaibo_Plantation";
	pchar.quest.Mtraxx_enterPlantMutiny.function = "Mtraxx_PlantWaitMutiny";
	
	pchar.quest.Mtraxx_TimerPlantMutiny1.win_condition.l1 = "Timer";
	pchar.quest.Mtraxx_TimerPlantMutiny1.win_condition.l1.date.hour  = 4.0;
	pchar.quest.Mtraxx_TimerPlantMutiny1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, i);
	pchar.quest.Mtraxx_TimerPlantMutiny1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, i);
	pchar.quest.Mtraxx_TimerPlantMutiny1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, i);
	pchar.quest.Mtraxx_TimerPlantMutiny1.function = "Mtraxx_PlantMutinyOver";
	
	pchar.quest.Mtraxx_TimerPlantMutiny2.win_condition.l1 = "locator";
	pchar.quest.Mtraxx_TimerPlantMutiny2.win_condition.l1.location = "Maracaibo_Plantation";
	pchar.quest.Mtraxx_TimerPlantMutiny2.win_condition.l1.locator_group = "quest";
	pchar.quest.Mtraxx_TimerPlantMutiny2.win_condition.l1.locator = "detector3";
	pchar.quest.Mtraxx_TimerPlantMutiny2.function = "Mtraxx_PlantMutinyAlarm";
	
	int n = 26 - sti(environment.time);
	SetLaunchFrameFormParam(StringFromKey("Roger_43"), "Mtraxx_PlantPrepareMarch", 0, 3);
	LaunchFrameForm();
	StoreDayUpdate();
	WaitDate("",0,0,0,n,5);
	RecalculateJumpTable();
	RefreshWeather();
	RefreshLandTime();
}	

void Mtraxx_PlantWaitMutiny(string qName) // 
{
	chrDisableReloadToLocation = true;//закрыть локацию
	pchar.questTemp.Mtraxx.Mutiny = "true";
	sld = characterFromId("Pelly");
	sld.Dialog.currentnode = "Pelly_20";
	ChangeCharacterAddressGroup(sld, "Maracaibo_Plantation", "quest", "detector2");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	for (int i=1; i<=7; i++)
	{
		sld = CharacterFromID("Mtr_PellyPirate_"+i);
		ChangeCharacterAddressGroup(sld, "Maracaibo_Plantation", "reload", "reload2_back");
		LAi_CharacterDisableDialog(sld); // патч 17/1
		LAi_SetActorType(sld);
		LAi_ActorFollowEverywhere(sld, "", -1);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
}	
	
void Mtraxx_PlantMutinyAlarm(string qName) // подошел слишком близко
{
	chrDisableReloadToLocation = false;
	DeleteAttribute(pchar, "questTemp.Mtraxx.Mutiny");
	pchar.quest.Mtraxx_Plant_Mutiny.over = "yes";
	pchar.quest.Mtraxx_TimerPlantMutiny1.over = "yes";
	LocatorReloadEnterDisable("shore37", "boat", false); 
	LocatorReloadEnterDisable("Maracaibo_ExitTown", "reload4", false); 
	LocatorReloadEnterDisable("Maracaibo_ExitTown", "reload3_back", false); 
	LAi_group_AttackGroup("SPAIN_CITIZENS", LAI_GROUP_PLAYER);
	log_info(StringFromKey("Roger_44"));
	SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
	sld = characterFromId("Pelly");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	for (int i=1; i<=7; i++)
	{
		sld = CharacterFromID("Mtr_PellyPirate_"+i);
		sld.lifeday = 0;
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	sld = characterFromId("Mrt_Rocur");
	sld.lifeday = 0;
	sld = characterFromId("Mrt_Rocur_clone");
	sld.lifeday = 0;
	AddQuestRecord("Roger_3", "14");
	Mtraxx_PlantPellyClear();
	Mtraxx_TerraxReset(3);
}		
	
void Mtraxx_PlantMutinyOver(string qName) // не пришёл до 4 часов
{
	DeleteAttribute(pchar, "questTemp.Mtraxx.Mutiny");
	pchar.quest.Mtraxx_Plant_Mutiny.over = "yes";
	pchar.quest.Mtraxx_TimerPlantMutiny2.over = "yes";
	pchar.quest.Mtraxx_enterPlantMutiny.over = "yes";
	LocatorReloadEnterDisable("shore37", "boat", false); 
	LocatorReloadEnterDisable("Maracaibo_ExitTown", "reload4", false); 
	LocatorReloadEnterDisable("Maracaibo_ExitTown", "reload3_back", false); 
	Mtraxx_PlantPellyClear();
	for (int i=1; i<=7; i++)
	{
		sld = CharacterFromID("Mtr_PellyPirate_"+i);
		sld.lifeday = 0;
	}
	sld = characterFromId("Mrt_Rocur");
	sld.lifeday = 0;
	sld = characterFromId("Mrt_Rocur_clone");
	sld.lifeday = 0;
	AddQuestRecord("Roger_3", "15");
	Mtraxx_TerraxReset(3);
}		
	
void Mtraxx_PlantMutiny() // восстание на плантации
{
	DeleteAttribute(pchar, "questTemp.Mtraxx.Mutiny");
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE;
	int iScl = 30 + 2*sti(pchar.rank);
	chrDisableReloadToLocation = true;//закрыть локацию
	pchar.GenQuest.FrameLockEsc = true; // закрыть ESC
	bDisableCharacterMenu = true;//лочим F2
	InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться
	pchar.GenQuest.CannotWait = true;
	SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
	pchar.quest.Mtraxx_TimerPlantMutiny1.over = "yes";
	pchar.quest.Mtraxx_TimerPlantMutiny2.over = "yes";
	PlaySound("VOICE\Russian\EvilPirates01.wav");
	PlaySound("interface\abordage_wining.wav");
	for(int n=0; n<MAX_LOCATIONS; n++)
	{	
		sld = &characters[n];
		if (CheckAttribute(sld, "plantation") && sld.plantation == "patrol" && sld.city == "Maracaibo")
		{
			ChangeCharacterAddressGroup(sld, "none", "", "");
		}
	}
	// Пелли и его бригада
	sld = characterFromId("Pelly");
	LAi_SetCheckMinHP(sld, 10, true, ""); // скрытое бессмертие
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	for (int i=1; i<=7; i++)
	{
		sld = CharacterFromID("Mtr_PellyPirate_"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	// Жан Пикар и его команда, все расчеты тут
	int iGun = sti(pchar.questTemp.Mtraxx.Weapon.Gun);
	int iMush = sti(pchar.questTemp.Mtraxx.Weapon.Mushket);
	int iPtn = sti(pchar.questTemp.Mtraxx.Weapon.Potion);
	int iShot = sti(pchar.questTemp.Mtraxx.Weapon.Shot);
	int iMptn = 0;
	// Жан Пикар
	sld = characterFromId("Mrt_Rocur");
	LAi_RemoveLoginTime(sld);
	DoQuestCheckDelay("Mtraxx_PlantJanReady", 15.0);
	GiveItem2Character(sld, "blade_08");
	EquipCharacterbyItem(sld, "blade_08");
	if (iGun > 0 && iShot > 0)
	{
		GiveItem2Character(sld, "pistol1");
		EquipCharacterbyItem(sld, "pistol1");
		TakeNItems(sld, "cartridge", 5);
		LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "cartridge");
		iGun--;
	}
	if (iPtn > 0)
	{
		if (iPtn > 90) 
		{
			TakeNItems(sld, "potion2", 3);
			iPtn = iPtn-6;
		}
		else
		{
			if (iPtn > 60) 
			{
				TakeNItems(sld, "potion2", 2);
				iPtn = iPtn-3;
			}
			else
			{
				TakeNItems(sld, "potion2", 1);
				iPtn--;
			}
		}
	}
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	ChangeCharacterAddressGroup(sld, "Maracaibo_Plantation", "goto", "goto14");
	iTotalTemp = 7;
	if (iMush > 0 && iShot >= (iMush*20)) // расчет мушкетов и зарядов к ним
	{
		iTotalTemp = 7 + iMush;
		iShot = iShot - iMush*20;
	}
	if (iGun > 0) // расчет числа пистолей. iGun - то, что в сундуке, Gun - на выдачу, /4
	{
		int Gun = makeint(iGun/4);
		if (Gun < 1) Gun = 1;
		if (Gun > 7) Gun = 7;
	}
	if (iShot > 0) // расчет числа зарядов. Аналогично 
	{
		int Shot = makeint(iShot/4);
		if (Shot < 1) Shot = 1;
	}
	if (iPtn >= 6 && iMush > 0)
	{
		iMptn = 1;
		iPtn = iPtn - 6;
	}
	if (iPtn > 0) // расчет числа зелий. Аналогично 
	{
		int Ptn = makeint(iPtn/4);
		if (Ptn < 1) Ptn = 1;
		if (Ptn > 21) Ptn = 21;
	}
	for (i=1; i<=iTotalTemp; i++)
	{
		if (i > 7) // мушкетеры до 2 шт
		{
			sld = GetCharacter(NPC_GenerateCharacter("Mtr_RocursPirat_"+i, "mush_ctz_"+i, "man", "mushketer", iRank, PIRATE, 0, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "cartridge", iScl);
			RemoveItems(sld, "cartridge", GetCharacterItem(sld, "cartridge"));
			RemoveItems(sld, "bullet", GetCharacterItem(sld, "bullet"));
			RemoveItems(sld, "gunpowder", GetCharacterItem(sld, "gunpowder"));
			RemoveItems(sld, "potion1", GetCharacterItem(sld, "potion1"));
			RemoveItems(sld, "potion2", GetCharacterItem(sld, "potion2"));
			RemoveItems(sld, "potion3", GetCharacterItem(sld, "potion3"));
			TakeNItems(sld, "cartridge", 20);
			LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "cartridge");
			if (iMptn > 0)
			{
				TakeNItems(sld, "potion1", 1);
				TakeNItems(sld, "potion2", 1);
				LAi_SetHP(sld, LAi_GetCharacterHP(sld)+30, LAi_GetCharacterHP(sld)+30);
			}
		}
		else
		{
			sld = GetCharacter(NPC_GenerateCharacter("Mtr_RocursPirat_"+i, "citiz_4"+(i+2), "man", "man", iRank, PIRATE, 0, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, LinkRandPhrase("blade_03","blade_05","blade_07"), "", "", iScl);
			RemoveItems(sld, "bullet", GetCharacterItem(sld, "bullet"));
			RemoveItems(sld, "gunpowder", GetCharacterItem(sld, "gunpowder"));
			RemoveItems(sld, "potion1", GetCharacterItem(sld, "potion1"));
			RemoveItems(sld, "potion2", GetCharacterItem(sld, "potion2"));
			RemoveItems(sld, "potion3", GetCharacterItem(sld, "potion3"));
			if (Gun > 0)
			{
				GiveItem2Character(sld, "pistol1");
				EquipCharacterbyItem(sld, "pistol1");
				Gun--;
				LAi_SetHP(sld, LAi_GetCharacterHP(sld)+80, LAi_GetCharacterHP(sld)+80);
			}
			if (Shot > 0)
			{
				if (Shot >= 7)
				{
					TakeNItems(sld, "cartridge", makeint(Shot/7));
					LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "cartridge");
					Shot = 0;
				}
				else
				{
					TakeNItems(sld, "cartridge", 1);
					LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "cartridge");
					Shot--;
				}
			}
			if (Ptn > 0)
			{
				int m = makeint(Ptn/7);
				LAi_SetHP(sld, LAi_GetCharacterHP(sld)+20*m, LAi_GetCharacterHP(sld)+20*m);
				if (Ptn >= 7)
				{
					TakeNItems(sld, "potion2", m);
					Ptn = 0;
				}
				else
				{
					TakeNItems(sld, "potion2", 1);
					Ptn--;
				}
			}
		}
		if (iMush > 0)
		{
			LAi_SetHP(sld, LAi_GetCharacterHP(sld)+20*iMush, LAi_GetCharacterHP(sld)+20*iMush);
		}
		if (i < 4) ChangeCharacterAddressGroup(sld, "Maracaibo_Plantation", "goto", "goto11");
		else
		{
			if (i < 7) ChangeCharacterAddressGroup(sld, "Maracaibo_Plantation", "goto", "goto13");
			else ChangeCharacterAddressGroup(sld, "Maracaibo_Plantation", "goto", "goto12");
		}
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	// ставим испанцев
	LAi_group_Delete("EnemyFight");
	for (i=1; i<=16; i++)
	{
		if (i < 3) // мушкетеры, 2 шт
		{
			sld = GetCharacter(NPC_GenerateCharacter("Mtr_PlantGuard_"+i, "mush_spa_"+i, "man", "mushketer", iRank, SPAIN, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "cartridge", iScl*2+30);
			LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "cartridge");
			if (MOD_SKILL_ENEMY_RATE > 4) sld.cirassId = Items_FindItemIdx("cirass1");
			ChangeCharacterAddressGroup(sld, "Maracaibo_Plantation", "goto", "goto"+i);
		}
		else
		{
			if (i == 4) // начальник охраны
			{
				sld = GetCharacter(NPC_GenerateCharacter("Mtr_PlantGuard_"+i, "sold_spa_15", "man", "man", iRank+5, SPAIN, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, iRank+5, iScl+10, iScl+10, "topor_04", "pistol4", "bullet", iScl*2+60);
				SetCharacterPerk(sld, "SwordplayProfessional");
				SetCharacterPerk(sld, "Gunman");
				SetCharacterPerk(sld, "GunProfessional");
				sld.cirassId = Items_FindItemIdx("cirass1");
			}
			else
			{
				sld = GetCharacter(NPC_GenerateCharacter("Mtr_PlantGuard_"+i, "sold_spa_"+(rand(7)+1), "man", "man", iRank, SPAIN, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, LinkRandPhrase("blade_08","blade_12","blade_14"), "pistol1", "bullet", iScl*2);
				if (MOD_SKILL_ENEMY_RATE > 4) sld.cirassId = Items_FindItemIdx("cirass2");
			}
			if (i < 10) ChangeCharacterAddressGroup(sld, "Maracaibo_Plantation", "goto", "goto"+i);
			else ChangeCharacterAddressGroup(sld, "Maracaibo_Plantation", "goto", "goto"+(i-9));
		}
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "Mtraxx_PlantMutinyAfterFight");
	LAi_SetFightMode(pchar, true);
	// таймер, для большего эффекта - визуальный
	pchar.questTemp.Mtraxx.PlantMutiny = "true";
	SetShowTimer(300.0);
	log_info(StringFromKey("Roger_45"));
	DoQuestFunctionDelay("Terrapin_SetMusic", 0.5);
	pchar.quest.Escort_fail.win_condition.l1 = "NPC_Death";
	pchar.quest.Escort_fail.win_condition.l1.character = "Mrt_Rocur";
	pchar.quest.Escort_fail.function = "Mtraxx_PlantRocurDie";
	
}		

void Mtraxx_PlantRocurDie(string qName) // Пикар дал дуба
{
	pchar.questTemp.Mtraxx.RocurDie = "true";
}

void Mtraxx_PlantExitopen(string qName) // убежали
{
	if (CheckAttribute(pchar, "questTemp.Mtraxx.PlantFort")) return;
	pchar.questTemp.Mtraxx.PlantEscape = "true"; // флаг - убежали
	DeleteAttribute(pchar, "questTemp.Mtraxx.PlantMutiny");
	DoQuestReloadToLocation("Maracaibo_ExitTown", "reload", "reload2", "Mtraxx_PlantEscape");
}

void Mtraxx_PlantMutinyFortAttack() // пришло подкрепление из форта
{
	if (CheckAttribute(pchar, "questTemp.Mtraxx.PlantEscape")) return;
	pchar.questTemp.Mtraxx.PlantFort = "true"; // флаг - пришли из форта
	pchar.quest.mtraxx_plant_exitopen.over = "yes";
	PlaySound("interface\abordage_wining.wav");
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+5;
	int iScl = 40 + 2*sti(pchar.rank);
	for (i=1; i<=15; i++)
	{
		if (i < 3) // мушкетеры, 2 шт
		{
			sld = GetCharacter(NPC_GenerateCharacter("Mtr_FortGuard_"+i, "mush_spa_"+i, "man", "mushketer", iRank, SPAIN, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "cartridge", iScl*2+30);
			LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "cartridge");
			if (MOD_SKILL_ENEMY_RATE > 4) sld.cirassId = Items_FindItemIdx("cirass1");
			ChangeCharacterAddressGroup(sld, "Maracaibo_Plantation", "reload", "reload1");
		}
		else
		{
			if (i == 3) // офицер
			{
				sld = GetCharacter(NPC_GenerateCharacter("Mtr_FortGuard_"+i, "off_spa_4", "man", "man", iRank+5, SPAIN, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, iRank+5, iScl+10, iScl+10, "topor_04", "pistol4", "bullet", iScl*2+90);
				SetCharacterPerk(sld, "SwordplayProfessional");
				SetCharacterPerk(sld, "Gunman");
				SetCharacterPerk(sld, "GunProfessional");
				sld.cirassId = Items_FindItemIdx("cirass1");
			}
			else
			{
				sld = GetCharacter(NPC_GenerateCharacter("Mtr_FortGuard_"+i, "sold_spa_"+(rand(7)+1), "man", "man", iRank, SPAIN, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, LinkRandPhrase("blade_08","blade_12","blade_14"), "pistol1", "bullet", iScl*2);
				if (MOD_SKILL_ENEMY_RATE > 4) sld.cirassId = Items_FindItemIdx("cirass2");
			}
			ChangeCharacterAddressGroup(sld, "Maracaibo_Plantation", "reload", "reload1");
		}
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetCheck("EnemyFight", "Mtraxx_PlantMutinyAfterFortFight");
}

void Mtraxx_PlantEscapeInShore(string qName) // в бухте
{
	// нулим бойцов
	for (int i=1; i<=7; i++)
	{
		if (GetCharacterIndex("Mtr_PellyPirate_"+i) != -1)
		{
			sld = CharacterFromID("Mtr_PellyPirate_"+i);
			LAi_SetWarriorType(sld);
			sld.lifeday = 0;
		}
	}
	// нулим пленников на плантации
	for (i=4; i<=8; i++)
	{
		if (GetCharacterIndex("Mtr_plantation_prisoner_"+i) != -1)
		{
			sld = CharacterFromID("Mtr_plantation_prisoner_"+i);
			sld.lifeday = 0;
		}
	}
	// подводим итоги
	if (CheckAttribute(pchar, "questTemp.Mtraxx.RocurDie")) // провалили дело
	{
		sld = characterFromId("Pelly");
		sld.Dialog.currentnode = "Pelly_14";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	else
	{
		sld = characterFromId("Mrt_Rocur");
		LAi_CharacterEnableDialog(sld);
		sld.Dialog.currentnode = "rocur_27";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
}

void Mtraxx_PlantFailFinal() // провалили дело
{
	LAi_LocationFightDisable(&Locations[FindLocation("shore37")], false);
	locations[FindLocation("shore37")].DisableEncounters = false;
	LocatorReloadEnterDisable("Maracaibo_ExitTown", "reload2_back", false);
	LocatorReloadEnterDisable("Maracaibo_ExitTown", "reload3_back", false);
	LocatorReloadEnterDisable("Maracaibo_ExitTown", "reload4", false);
	LocatorReloadEnterDisable("shore37", "boat", false);
	sld = characterFromId("Pelly");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "sea", "none", "", "", "", 10.0);
	Mtraxx_PlantPellyClear();
	AddQuestRecord("Roger_3", "17");
	Mtraxx_TerraxReset(3);
}

void Mtraxx_PlantSeaEscape() // уходим в море
{
	sld = characterFromId("Mrt_Rocur");// лесник . Пикар убегает на корабль Тисака лесник
	DeleteAttribute(sld,"ReducedDamage"); // belamour legendary edition
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "sea", "none", "", "", "", 3.0); // лесник 
	sld = characterFromId("Pelly");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "sea", "none", "", "", "OpenTheDoors", 10.0);
	LocatorReloadEnterDisable("shore37", "boat", false);
	AddQuestRecord("Roger_3", "18");
	LocatorReloadEnterDisable("shore37", "reload1_back", true);
	pchar.quest.mtraxx_plant_seabattle.win_condition.l1 = "location";
	pchar.quest.mtraxx_plant_seabattle.win_condition.l1.location = "Maracaibo";
	pchar.quest.mtraxx_plant_seabattle.function = "Mtraxx_PlantSeaBattle";
}

void Mtraxx_PlantSeaBattle(string qName) // бой с испанской эскадрой
{
	DeleteAttribute(pchar, "GenQuest.HunterLongPause");
	AddQuestRecord("Roger_3", "19");
	LAi_LocationFightDisable(&Locations[FindLocation("shore37")], false);
	locations[FindLocation("shore37")].DisableEncounters = false;
	LocatorReloadEnterDisable("shore37", "reload1_back", false);
	LocatorReloadEnterDisable("Maracaibo_ExitTown", "reload2_back", false);
	LocatorReloadEnterDisable("Maracaibo_ExitTown", "reload3_back", false);
	LocatorReloadEnterDisable("Maracaibo_ExitTown", "reload4", false);
	DeleteAttribute(pchar, "GenQuest.CannotWait");
	Island_SetReloadEnableGlobal("Maracaibo", false);
	bQuestDisableMapEnter = true;
	pchar.nation = FRANCE;
	// ставим три испанских корабля
	Group_FindOrCreateGroup("Mtr_PlantSeaGroup");
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE;
	int iScl = 20 + 2*sti(pchar.rank);
	int Type, iShip, Ship1, Ship2, Ship3, iCannon, Cannon1, Cannon2;
	int iClass = sti(RealShips[sti(pchar.ship.type)].Class);
	if (MOD_SKILL_ENEMY_RATE < 4) // халява
	{
		Type = 1;
		if (iClass == 3) Type = 2;
		if (iClass < 3) Type = 4;
	}
	if (MOD_SKILL_ENEMY_RATE >= 4 && MOD_SKILL_ENEMY_RATE < 8) // 2-3 уровни
	{
		Type = 4;
		if (iClass == 3) Type = 3;
		if (iClass < 3) Type = 5;
	}
	if (MOD_SKILL_ENEMY_RATE >= 8) // высшие уровни
	{
		Type = 3;
		if (iClass == 3) Type = 5;
		if (iClass < 3) Type = 6;
	}
	switch (Type)
	{
		case 1:
			Ship1 = SHIP_SLOOP;
			Ship2 = SHIP_LUGGER;
			Ship3 = SHIP_CAREERLUGGER;
			Cannon1 = CANNON_TYPE_CANNON_LBS6;
			Cannon2 = CANNON_TYPE_CULVERINE_LBS8;
		break;
		
		case 2:
			Ship1 = SHIP_SHNYAVA;
			Ship2 = SHIP_SLOOP;
			Ship3 = SHIP_CAREERLUGGER;
			Cannon1 = CANNON_TYPE_CANNON_LBS16;
			Cannon2 = CANNON_TYPE_CULVERINE_LBS8;
		break;
		
		case 3:
			Ship1 = SHIP_CARAVEL;
			Ship2 = SHIP_BARKENTINE;
			Ship3 = SHIP_SCHOONER_W;
			Cannon1 = CANNON_TYPE_CULVERINE_LBS18;
			Cannon2 = CANNON_TYPE_CANNON_LBS8;
		break;
		
		case 4:
			Ship1 = SHIP_CORVETTE;
			Ship2 = SHIP_BRIG;
			Ship3 = SHIP_SHNYAVA;
			Cannon1 = CANNON_TYPE_CULVERINE_LBS18;
			Cannon2 = CANNON_TYPE_CANNON_LBS16;
		break;
		
		case 5:
			Ship1 = SHIP_CORVETTE;
			Ship2 = SHIP_POLACRE;
			Ship3 = SHIP_CARAVEL;
			Cannon1 = CANNON_TYPE_CANNON_LBS20;
			Cannon2 = CANNON_TYPE_CULVERINE_LBS18;
		break;
		
		case 6:
			Ship1 = SHIP_GALEON_L;
			Ship2 = SHIP_CORVETTE;
			Ship3 = SHIP_XebekVML;
			Cannon1 = CANNON_TYPE_CANNON_LBS24;
			Cannon2 = CANNON_TYPE_CULVERINE_LBS18;
		break;
	}
	for (int i=1; i<=3; i++)
	{
		switch (i)
		{
			case 1:
				iShip = Ship1;
				iCannon = Cannon1;
			break;
			
			case 2:
				iShip = Ship2;
				iCannon = Cannon2;
				if (Type == 6) iCannon = Cannon1;
			break;
			
			case 3:
				iShip = Ship3;
				iCannon = Cannon2;
			break;
		}
		sld = GetCharacter(NPC_GenerateCharacter("Mtr_PlantSeaCap_"+i, "off_spa_"+(5-i), "man", "man", iRank, SPAIN, -1, true, "quest"));
		FantomMakeCoolSailor(sld, iShip, "", iCannon, iScl, iScl, iScl);
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, LinkRandPhrase("blade_15","blade_16","topor_04"), "pistol1", "bullet", iScl*3);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		sld.DontRansackCaptain = true;
		sld.AnalizeShips = true;
		sld.AlwaysEnemy = true;
		sld.Ship.Mode = "war";
		sld.ship.Crew.Morale = 40+MOD_SKILL_ENEMY_RATE*6;
		sld.Ship.Crew.Exp.Sailors = 40+MOD_SKILL_ENEMY_RATE*6;
		sld.Ship.Crew.Exp.Cannoners = 40+MOD_SKILL_ENEMY_RATE*6;
		sld.Ship.Crew.Exp.Soldiers = 40+MOD_SKILL_ENEMY_RATE*6;
		if (MOD_SKILL_ENEMY_RATE > 4) SetCharacterPerk(sld, "MusketsShoot");
		if (Type > 1 && i == 1) SetRandGeraldSail(sld, SPAIN);
		Group_AddCharacter("Mtr_PlantSeaGroup", "Mtr_PlantSeaCap_"+i);
	}
	Group_SetGroupCommander("Mtr_PlantSeaGroup", "Mtr_PlantSeaCap_1");
	Group_SetAddress("Mtr_PlantSeaGroup", "Maracaibo", "quest_ships", "quest_ship_7");
	Group_SetTaskAttack("Mtr_PlantSeaGroup", PLAYER_GROUP);
	Group_LockTask("Mtr_PlantSeaGroup");
	// Пелли уплывает
	ref chr = characterFromId("Mtr_PlantSeaCap_1");
	sld = characterFromId("Pelly_sea");
	sld.nation = SPAIN;
	Ship_SetTaskRunAway(SECONDARY_TASK, sti(sld.index), sti(chr.index));
	
	pchar.quest.mtraxx_plant_seabattlewin.win_condition.l1 = "NPC_Death";
	pchar.quest.mtraxx_plant_seabattlewin.win_condition.l1.character = "Mtr_PlantSeaCap_1";
	pchar.quest.mtraxx_plant_seabattlewin.function = "Mtraxx_PlantSeaBattleCanEscape";
}

void Mtraxx_PlantSeaBattleCanEscape(string qName) // уничтожили флагман испанцев
{
	Log_Info(StringFromKey("Roger_46"));
	PlaySound("interface\notebook.wav");
	bQuestDisableMapEnter = false;//открыть карту
	pchar.quest.mtraxx_plant_seabattlemap.win_condition.l1 = "MapEnter";
	pchar.quest.mtraxx_plant_seabattlemap.function = "Mtraxx_PlantGoHome";
}

void Mtraxx_PlantGoHome(string qName) // пора домой
{
	AddQuestRecord("Roger_3", "20");
	Group_SetAddress("PellyGroup", "Hispaniola1", "quest_ships", "quest_ship_6"); // Пелли в Ла Вегу
	pchar.questTemp.Mtraxx = "plant_success";
	QuestSetCurrentNode("Terrax", "mtraxx_27");
	//SetFunctionTimerCondition("Mtraxx_PlantGoHomeOver", 0, 0, 40, false);
	SetFunctionTimerCondition("Mtraxx_PlantOpenMaracaibo", 0, 0, 5, false);
	AddComplexSeaExpToScill(100, 100, 100, 50, 50, 50, 0);
	ChangeCharacterComplexReputation(pchar, "authority", 7);
	ChangeCharacterComplexReputation(pchar, "fame", 5);
	ChangeCharacterHunterScore(PChar, "spahunter", 15); 
}

void Mtraxx_PlantOpenMaracaibo(string qName) // открываем остров
{
	Island_SetReloadEnableGlobal("Maracaibo", true);
}

void Mtraxx_PlantGoHomeOver(string qName) // истекло время на возвращение
{
	if(bImCasual)
	{
		if(CheckAttribute(pchar,"quest.Mtraxx_PlantGoHomeOver.over"))
			DeleteAttribute(pchar,"quest.Mtraxx_PlantGoHomeOver.over");
		NewGameTip(StringFromKey("Roger_4"));
		SetFunctionTimerCondition("Mtraxx_PlantGoHomeOver", 0, 0, 40, false);
		return;
	}
	QuestSetCurrentNode("Terrax", "mtraxx_31");
	Group_DeleteGroup("PellyGroup");
	CloseQuestHeader("Roger_3");
	// belamour legendary edition забрать флаг обратно
	if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
	{
		DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
		DeleteAttribute(pchar,"perks.list.FlagSpa"); 
		log_info(StringFromKey("Roger_1"));
	}
}

void Mtraxx_PlantFithTaskTimer(string qName) // таймер на опоздание к 5 заданию
{
	if(bImCasual)
	{
		if(CheckAttribute(pchar,"quest.Mtraxx_PlantFithTaskTimer.over"))
			DeleteAttribute(pchar,"quest.Mtraxx_PlantFithTaskTimer.over");
		NewGameTip(StringFromKey("Roger_4"));
		SetFunctionTimerCondition("Mtraxx_PlantFithTaskTimer", 0, 0, 35, false);
		return;
	}
	pchar.questTemp.Mtraxx.Late = "true";
}

// эпизод 4 - Особенности пиратской торговли
void Mtraxx_PasqualeBegin() // установка параметров
{
	Group_DeleteGroup("PellyGroup");
	SetFunctionTimerCondition("Mtraxx_PasqualeLate", 0, 0, 7, false);
	// здесь определим координаты эскадры
	int degN, degW, minN1, minN2, minW1, minW2;
	int i = rand(2); // широта
	int n = rand(4); // долгота // правки прогона 3
	int k = rand(2)+1; // минуты широты
	int m = rand(2)+1; // минуты долготы
	pchar.questTemp.Mtraxx.Crdn.degN = 22 + i; // градус широты
	pchar.questTemp.Mtraxx.Crdn.degW = 62 + n; // градус долготы // правки прогона 3
	pchar.questTemp.Mtraxx.Crdn.minN1 = 0; // нижний предел интервала широты
	pchar.questTemp.Mtraxx.Crdn.minN2 =60; // верхний предел интервала широты
	pchar.questTemp.Mtraxx.Crdn.minW1 = 0; // нижний предел интервала долготы
	pchar.questTemp.Mtraxx.Crdn.minW2 = 60; // верхний предел интервала долготы
	// тип целевого корабля тоже определим здесь
	int iClass = sti(RealShips[sti(pchar.ship.type)].Class);
	pchar.questTemp.Mtraxx.Crdn.Ship = SHIP_PINNACE;
	
	if (MOD_SKILL_ENEMY_RATE > 8) iClass -= 1;
	if(iClass < 3) iClass = 3;
	if(iClass > 6) iClass = 6;
	
	pchar.questTemp.Mtraxx.Crdn.Ship = GetRandomShipType(GetClassFlag(iClass), FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
}

void Mtraxx_PasqualeLate(string qName) // опоздали к Паскалю
{
	if(bImCasual)
	{
		if(CheckAttribute(pchar,"quest.Mtraxx_PasqualeLate.over"))
			DeleteAttribute(pchar,"quest.Mtraxx_PasqualeLate.over");
		NewGameTip(StringFromKey("Roger_4"));
		SetFunctionTimerCondition("Mtraxx_PasqualeLate", 0, 0, 7, false);
		return;
	}
	DeleteAttribute(pchar, "questTemp.Mtraxx.Crdn");
	pchar.questTemp.Mtraxx = "pasq_late";
	QuestSetCurrentNode("Terrax", "mtraxx_34"); // правки прогона 3
	AddQuestRecord("Roger_4", "2");
	CloseQuestHeader("Roger_4");
}

void Mtraxx_PasqualeTimeConvoy(string qName) // дата прихода конвоя
{
	if (CheckAttribute(pchar, "questTemp.Mtraxx.PasqFail")) return;
	pchar.quest.mtraxx_pasq_convoy.win_condition.l1 = "EnterToSea";
	pchar.quest.mtraxx_pasq_convoy.function = "Mtraxx_PasqualeCheckCoordinates";
}

void Mtraxx_PasqualeCheckCoordinates(string qName) // проверяем координаты
{
	if (CheckAttribute(pchar, "questTemp.Mtraxx.PasqFail")) return;
	int degN, degW, minN1, minN2, minW1, minW2;
	degN = sti(pchar.questTemp.Mtraxx.Crdn.degN); // градус широты
	degW = sti(pchar.questTemp.Mtraxx.Crdn.degW); // градус долготы
	minN1 = sti(pchar.questTemp.Mtraxx.Crdn.minN1); // нижний предел интервала широты
	minN2 = sti(pchar.questTemp.Mtraxx.Crdn.minN2); // верхний предел интервала широты
	minW1 = sti(pchar.questTemp.Mtraxx.Crdn.minW1); // нижний предел интервала долготы
	minW2 = sti(pchar.questTemp.Mtraxx.Crdn.minW2); // верхний предел интервала долготы
	if (CheckAttribute(pchar, "Ship.pos.x") && !bDisableMapEnter)
	{
		if(GetSeaCoordDegreeZ(makefloat(pchar.Ship.pos.z)) == degN && GetMapCoordMinutesZ(makefloat(worldMap.playerShipZ)) >= minN1 && GetMapCoordMinutesZ(makefloat(worldMap.playerShipZ)) < minN2 && GetSeaCoordDegreeX(makefloat(pchar.Ship.pos.x)) == degW && GetMapCoordMinutesX(makefloat(worldMap.playerShipX)) >= minW1 && GetMapCoordMinutesX(makefloat(worldMap.playerShipX)) < minW2) 
		{	
			log_Testinfo("Координаты найдены!");
			bQuestDisableMapEnter = true;
			pchar.quest.Mtraxx_PasqualeConvoyOver.over = "yes";
			DoQuestFunctionDelay("Mtraxx_PasqualeCreateConvoy", 3.0);
		}
		else 
		{
			log_Testinfo("Координаты не соответствуют");
			pchar.quest.mtraxx_pasq_convoy1.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_pasq_convoy1.function = "Mtraxx_PasqualeTimeConvoy";
		}
	}
	
	// Captain Beltrop, 12.09.21, отключаем морских ОЗГов на время
    pchar.GenQuest.SeaHunter2Pause = true;
    SeaHunter_Delete();
}

void Mtraxx_PasqualeConvoyOver(string qName) // не нашли конвой
{
	pchar.questTemp.Mtraxx.PasqFail = "true";
	DeleteAttribute(pchar, "questTemp.Mtraxx.Crdn");
	pchar.questTemp.Mtraxx = "pasq_late";
	AddQuestRecord("Roger_4", "4");
	CloseQuestHeader("Roger_4");
	QuestSetCurrentNode("Terrax", "mtraxx_34");
	
	DeleteAttribute(pchar, "GenQuest.SeaHunter2Pause"); // вертаем морских ОЗГов
}

void Mtraxx_PasqualeCreateConvoy(string qName) // создаем конвой
{
	log_info(StringFromKey("Roger_47"));
	PlaySound("interface\notebook.wav");
	PlaySound("interface\" + LanguageGetLanguage() + "\_EvEnemy0.wav");
	Group_FindOrCreateGroup("Mtr_PasqSeaGroup");
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE;
	int iScl = 20 + 2*sti(pchar.rank);
	int iShip[4], iSpace;
	int iClass = sti(RealShips[sti(pchar.ship.type)].Class) + 1;
	
	if (MOD_SKILL_ENEMY_RATE > 8) iClass -= 1;
	if(iClass < 3) iClass = 3;
	if(iClass > 6) iClass = 6;
	
	iShip[1] = GetRandomShipType(GetClassFlag(iClass), FLAG_SHIP_TYPE_WAR, FLAG_SHIP_NATION_ANY);
	iShip[2] = sti(pchar.questTemp.Mtraxx.Crdn.Ship);
	iShip[3] = GetRandomShipType(GetClassFlag(iClass), FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
	for (int i=1; i<=3; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Mtr_PasqCap_"+i, "off_hol_"+i, "man", "man", iRank, HOLLAND, -1, true, "quest"));
		FantomMakeCoolSailor(sld, iShip[i], "", -1, iScl, iScl, iScl);
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, LinkRandPhrase("blade_15","blade_16","topor_04"), "pistol1", "bullet", iScl*3);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		sld.DontRansackCaptain = true;
		sld.AnalizeShips = true;
		sld.AlwaysEnemy = true;
		sld.Ship.Mode = "war";
		sld.ship.Crew.Morale = 40+MOD_SKILL_ENEMY_RATE*6;
		sld.Ship.Crew.Exp.Sailors = 40+MOD_SKILL_ENEMY_RATE*6;
		sld.Ship.Crew.Exp.Cannoners = 40+MOD_SKILL_ENEMY_RATE*6;
		sld.Ship.Crew.Exp.Soldiers = 40+MOD_SKILL_ENEMY_RATE*6;
		if (MOD_SKILL_ENEMY_RATE > 4) SetCharacterPerk(sld, "MusketsShoot");
		if (i == 1) 
		{
			SetRandGeraldSail(sld, HOLLAND);
			iSpace = GetCharacterFreeSpace(sld, GOOD_WHEAT);
			iSpace = makeint(iSpace/2 + rand(iSpace/2));
			Fantom_SetCharacterGoods(sld, GOOD_WHEAT, iSpace, 1);
		}
		if (i == 2) 
		{
			sld.ship.name = StringFromKey("Roger_48");
			NullCharacterGoods(sld);
			AddCharacterGoods(sld, GOOD_BALLS, 500);
			AddCharacterGoods(sld, GOOD_GRAPES, 400);
			AddCharacterGoods(sld, GOOD_KNIPPELS, 300);
			AddCharacterGoods(sld, GOOD_BOMBS, 500);
			AddCharacterGoods(sld, GOOD_POWDER, 1000);
			AddCharacterGoods(sld, GOOD_WEAPON, 450);
			AddCharacterGoods(sld, GOOD_FOOD, 500);
			AddCharacterGoods(sld, GOOD_MEDICAMENT, 150);
			AddCharacterGoods(sld, GOOD_RUM, 50);
			iSpace = GetCharacterFreeSpace(sld, GOOD_EBONY);
			Fantom_SetCharacterGoods(sld, GOOD_EBONY, iSpace, 1);
			pchar.questTemp.Mtraxx.Crdn.Ebony = iSpace;
		}
		if (i == 3) 
		{
			iSpace = GetCharacterFreeSpace(sld, GOOD_FRUITS);
			iSpace = makeint(iSpace/2 + rand(iSpace/2));
			Fantom_SetCharacterGoods(sld, GOOD_FRUITS, iSpace, 1);
		}
		Group_AddCharacter("Mtr_PasqSeaGroup", "Mtr_PasqCap_"+i);
	}
	Group_SetGroupCommander("Mtr_PasqSeaGroup", "Mtr_PasqCap_1");
	Group_SetTaskAttack("Mtr_PasqSeaGroup", PLAYER_GROUP);
	Group_LockTask("Mtr_PasqSeaGroup");
	Sea_LoginGroupCurrentSea("Mtr_PasqSeaGroup");
	pchar.quest.mtr_pasq_seabattleCheck.win_condition.l1 = "MapEnter";
	pchar.quest.mtr_pasq_seabattleCheck.function = "Mtraxx_PasqualeCheck";
	pchar.quest.mtr_pasq_seabattleAbordage.win_condition.l1 = "Character_Capture";
	pchar.quest.mtr_pasq_seabattleAbordage.win_condition.l1.character = "Mtr_PasqCap_2";
	pchar.quest.mtr_pasq_seabattleAbordage.function = "Mtraxx_PasqualeBoarding";
	pchar.quest.mtr_pasq_seabattleSink.win_condition.l1 = "Character_sink";
	pchar.quest.mtr_pasq_seabattleSink.win_condition.l1.character = "Mtr_PasqCap_2";
	pchar.quest.mtr_pasq_seabattleSink.function = "Mtraxx_PasqualeSink";
	bQuestDisableMapEnter = false;
	Island_SetReloadEnableGlobal("Bermudes", false);
	
	DeleteAttribute(pchar, "GenQuest.SeaHunter2Pause"); // вертаем морских ОЗГов
}

void Mtraxx_PasqualeSink(string qName) // утопили Розбоом
{
	pchar.quest.mtr_pasq_seabattleAbordage.over = "yes";
	pchar.questTemp.Mtraxx.Crdn.Fail = "true";
}

void Mtraxx_PasqualeBoarding(string qName) // взяли Розбоом
{
	pchar.quest.mtr_pasq_seabattleSink.over = "yes";
	pchar.questTemp.Mtraxx.Crdn.Win = "true";
}

void Mtraxx_PasqualeCheck(string qName) // подводим итоги боя // правки прогона 3
{
	Group_DeleteGroup("Mtr_PasqSeaGroup");
	Island_SetReloadEnableGlobal("Bermudes", true);
	OfficersReaction("bad");
	ChangeCharacterComplexReputation(pchar, "nobility", -2);
	if (CheckAttribute(pchar, "questTemp.Mtraxx.Crdn.Fail"))
	{
		pchar.questTemp.Mtraxx = "pasq_sink";
		AddQuestRecord("Roger_4", "5");
		CloseQuestHeader("Roger_4");
		DeleteAttribute(pchar, "questTemp.Mtraxx.Crdn");
		QuestSetCurrentNode("Terrax", "mtraxx_34");
		ChangeCharacterHunterScore(PChar, "holhunter", 15);
		ChangeCharacterComplexReputation(pchar, "nobility", -3);
		return;
	}
	if (CheckAttribute(pchar, "questTemp.Mtraxx.Crdn.Win"))
	{
		pchar.questTemp.Mtraxx = "pasq_win";
		AddQuestRecord("Roger_4", "7");
		DoQuestCheckDelay("sea_victory", 1.3);
		ChangeCharacterComplexReputation(pchar, "authority", 3);
		ChangeCharacterComplexReputation(pchar, "fame", 3);
		AddComplexSeaExpToScill(100, 50, 50, 100, 100, 100, 0);
		ChangeCharacterHunterScore(PChar, "holhunter", 15); 
		ChangeCharacterComplexReputation(pchar, "nobility", -4);
		return;
	}
	DeleteAttribute(pchar, "questTemp.Mtraxx.Crdn");
	pchar.questTemp.Mtraxx = "pasq_esc";
	AddQuestRecord("Roger_4", "6");
	CloseQuestHeader("Roger_4");
	QuestSetCurrentNode("Terrax", "mtraxx_34");
}

void Mtraxx_PasqualeJeffry(string qName) // подходит Джеффри
{
	chrDisableReloadToLocation = true;
	sld = characterFromId("Jeffry");
	sld.dialog.currentnode = "Jeffry_15";
	sld.greeting = "Jeffry_02";
	ChangeCharacterAddressGroup(sld, "Pirates_town", "reload", "reload3_back");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void Mtraxx_PasqualeJan(string qName) // продолжение квеста
{
	if (!CheckAttribute(pchar, "questTemp.Mtraxx.Pasquale.Continue")) return; // правки прогона 3
	chrDisableReloadToLocation = true;
	sld = characterFromId("Mrt_Rocur");
	LAi_CharacterEnableDialog(sld); // релиз-правка
	sld.dialog.currentnode = "rocur_48";
	ChangeCharacterAddressGroup(sld, "LaVega_exittown", "reload", "reload2_back");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	// корвет Пикара в бухту для антуража
	Group_FindOrCreateGroup("RocurSeaGroup");
	FantomMakeCoolSailor(sld, SHIP_CORVETTE, StringFromKey("Roger_49"), CANNON_TYPE_CULVERINE_LBS18, 90, 90, 90);
	sld.nation = PIRATE;
	sld.Abordage.Enable = false;
	sld.AlwaysFriend = true;
	sld.ShipEnemyDisable = true; 
	LAi_SetImmortal(sld, true); // сплошная защита от дурака
	sld.DontDeskTalk = true;
	Group_AddCharacter("RocurSeaGroup", "Mrt_Rocur");
	Group_SetGroupCommander("RocurSeaGroup", "Mrt_Rocur");
	Group_SetTaskNone("RocurSeaGroup");
	Group_SetAddress("RocurSeaGroup", "Hispaniola1", "quest_ships", "quest_ship_4");
	Group_LockTask("RocurSeaGroup");
}

void Mtraxx_PasqualeJanTimer(string qName) // корвет Жана к бухте Гонаив
{
	Group_SetAddress("RocurSeaGroup", "Hispaniola2", "quest_ships", "quest_ship_4");
}

void Mtraxx_PasqualeJanTimeOver(string qName) // не явился на стрелку
{
	AddQuestRecord("Roger_4", "13");
	CloseQuestHeader("Roger_4");
	pchar.quest.mtraxx_pasq_gonaiv.over = "yes";
	if (pchar.location == "Hispaniola2" && bSeaActive)
	{
		pchar.quest.mtraxx_pasq_janover.win_condition.l1 = "ExitFromLocation";
		pchar.quest.mtraxx_pasq_janover.win_condition.l1.location = pchar.location;
		pchar.quest.mtraxx_pasq_janover.function = "Mtraxx_PasqualeJanTimeOver1";
	}
	else 
	{
		Group_DelCharacter("RocurSeaGroup", "Mrt_Rocur");
		Group_DeleteGroup("RocurSeaGroup");
	}
	DeleteAttribute(pchar, "questTemp.Mtraxx.Pasquale.Grabbing");
}

void Mtraxx_PasqualeJanTimeOver1(string qName) // 
{
	Group_DelCharacter("RocurSeaGroup", "Mrt_Rocur");
	Group_DeleteGroup("RocurSeaGroup");
}

void Mtraxx_PasqualeJanGonaiv(string qName) // встретились в бухте
{
	pchar.GenQuest.HunterLongPause = true;
	pchar.quest.mtraxx_pasq_check.over = "yes";
	pchar.quest.Mtraxx_PasqualeJanTimeOver.over = "yes";
	chrDisableReloadToLocation = true;
	sld = characterFromId("Mrt_Rocur");
	sld.dialog.currentnode = "rocur_57";
	ChangeCharacterAddressGroup(sld, "Shore34", "goto", "goto1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void Mtraxx_PasqualeNight() // ночной порой два жулика...
{
	int iTime, iAddTime;
	iTime = sti(environment.time);
	iAddTime = 24 - iTime;
	if (iAddTime < 1) iAddTime = 24;
	SetLaunchFrameFormParam(StringFromKey("Roger_50"), "", 0, 3);
	LaunchFrameForm();
	StoreDayUpdate();
	WaitDate("",0,0,0,iAddtime,5);
	RecalculateJumpTable();
	RefreshWeather();
	RefreshLandTime();
	DoQuestFunctionDelay("Mtraxx_PasqualeNightTalk", 3.0);
}

void Mtraxx_PasqualeNightTalk(string qName) // ... сговорились пойти на дело
{
	pchar.GenQuest.Hunter2Pause = true; // 3 прогона
	DoQuestReloadToLocation("Shore34", "reload", "reload1", "Mtraxx_PasqualeNightTalk");
}

void Mtraxx_PasqualeNightMarch() // параметры локаций для похода
{
	AddQuestRecord("Roger_4", "12");
	sld = characterFromId("Mrt_Rocur");
	LAi_SetActorType(sld);
	LAi_ActorFollowEverywhere(sld, "", -1);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	chrDisableReloadToLocation = false;
	LocatorReloadEnterDisable("Shore34", "boat", true);
	pchar.quest.mtraxx_pasq_night.win_condition.l1 = "Timer";
	pchar.quest.mtraxx_pasq_night.win_condition.l1.date.hour  = 4.0;
	pchar.quest.mtraxx_pasq_night.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
	pchar.quest.mtraxx_pasq_night.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
	pchar.quest.mtraxx_pasq_night.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
	pchar.quest.mtraxx_pasq_night.function = "Mtraxx_PasqualeNightTimeover";
	pchar.quest.mtraxx_pasq_lavega.win_condition.l1 = "location";
	pchar.quest.mtraxx_pasq_lavega.win_condition.l1.location = "Lavega_town";
	pchar.quest.mtraxx_pasq_lavega.function = "Mtraxx_PasqualeNightLavega";
	pchar.GenQuest.CannotWait = true;
	for (int i=0; i<MAX_LOCATIONS; i++)
	{				
		if (CheckAttribute(&locations[i], "islandId") && locations[i].islandId == "Hispaniola")
		{
			LAi_LocationDisableOfficersGen(locations[i].id, true);
		}
	}
}

void Mtraxx_PasqualeNightClear() // чистка запретов
{
	for (int i=0; i<MAX_LOCATIONS; i++)
	{				
		if (CheckAttribute(&locations[i], "islandId") && locations[i].islandId == "Hispaniola")
		{
			LAi_LocationDisableOfficersGen(locations[i].id, false);
		}
	}
	LocatorReloadEnterDisable("shore34", "boat", false);
	DeleteAttribute(pchar, "GenQuest.CannotWait");
	DeleteAttribute(pchar, "questTemp.Mtraxx.Pasquale.Grabbing");
	DeleteAttribute(pchar, "GenQuest.HunterLongPause");
}

void Mtraxx_PasqualeNightTimeover(string qName) // замешкались
{
	pchar.questTemp.Mtraxx.Pasquale.Timeover = "true";
	DeleteAttribute(pchar, "GenQuest.HunterLongPause");
}

void Mtraxx_PasqualeNightLavega(string qName) // вошли в Ла Вегу
{
	if (CheckAttribute(pchar, "questTemp.Mtraxx.Pasquale.Timeover"))
	{
		DeleteAttribute(pchar, "questTemp.Mtraxx.Pasquale.Timeover");
		Mtraxx_PasqualeNightClear();
		sld = characterFromId("Mrt_Rocur");
		sld.dialog.currentnode = "rocur_98";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		return;
	}
	pchar.quest.mtraxx_pasq_night.over = "yes";
	chrDisableReloadToLocation = true;
	sld = characterFromId("Mrt_Rocur");
	sld.dialog.currentnode = "rocur_72";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	// заполняем сундуки
	int n = Findlocation("LaVega_TwoFloorHouse");
	locations[n].private1.items.chest = 1;
	locations[n].private1.items.jewelry3 = 50;
	locations[n].private1.items.map_hisp = 1;
	locations[n].private1.items.potionrum = 10;
	locations[n].private2.items.totem_03 = 1;
	locations[n].private2.items.Mineral13 = 1;
	locations[n].private2.items.Mineral30 = 1;
	locations[n].private2.items.Mineral6 = 1;
	locations[n].private2.items.Mineral2 = 1;
	locations[n].private2.items.Mineral3 = 1;
	locations[n].private2.items.potionwine = 5;
	// ставим деваху
	sld = GetCharacter(NPC_GenerateCharacter("Mirabella", "Mirabelle", "woman", "towngirl", 1, PIRATE, -1, false, "quest"));
	LAi_LoginInCaptureTown(sld, true);
	SetFantomParamFromRank(sld, 1, true);
	sld.name = StringFromKey("Roger_51");
	sld.lastname = StringFromKey("Roger_52");
	sld.Dialog.Filename = "Quest\Roger.c";
	sld.dialog.currentnode = "mirabelle";
	RemoveAllCharacterItems(sld, true);
	sld.DontClearDead = true;
	ChangeCharacterAddressGroup(sld, "LaVega_TwoFloorHouse", "goto", "goto7");
	LAi_SetActorType(sld);
}

void Mtraxx_PasqualeNightToHouse() // бежим в дом
{
	sld = characterFromId("Mrt_Rocur");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload10", "LaVega_TwoFloorHouse", "goto", "goto1", "Mtraxx_PasqualeNightToHouse", -1);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
}

void Mtraxx_PasqualeNightInHouse() // в доме
{
	sld = characterFromId("Mrt_Rocur");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "goto", "goto3", "Mtraxx_PasqualeJanAni", -1);
	pchar.quest.mtraxx_pasq_girl.win_condition.l1 = "locator";
	pchar.quest.mtraxx_pasq_girl.win_condition.l1.location = "LaVega_TwoFloorHouse";
	pchar.quest.mtraxx_pasq_girl.win_condition.l1.locator_group = "quest";
	pchar.quest.mtraxx_pasq_girl.win_condition.l1.locator = "quest1";
	pchar.quest.mtraxx_pasq_girl.function = "Mtraxx_PasqualeFindGirl";
}

void Mtraxx_PasqualeCheckChest() // проверяем залез ли в сундук
{
	pchar.questTemp.Mtraxx.Pasquale.Grabbing.Chest = "true";
}

void Mtraxx_PasqualeFindGirl(string qName) // нашел Мирабель
{
	pchar.questTemp.Mtraxx.Pasquale.Girl = "true";
	sld = characterFromId("Mirabella");
	LAi_SetActorType(sld);
	LAi_ActorDialogDelay(sld, pchar, "", 1.5);
}

void Mtraxx_PasqualeJanSeeGirl() // Жан видит Мирабель
{
	sld = characterFromId("Mrt_Rocur");
	sld.dialog.currentnode = "rocur_75";
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "goto", "goto6", "Mtraxx_PasqualeJanSeeGirl", 5);
}

void Mtraxx_PasqualeJanTreasure(string qName) // делим добычу
{
	if (CheckAttribute(pchar, "questTemp.Mtraxx.Pasquale.Girl")) return;
	pchar.quest.mtraxx_pasq_girl.over = "yes"; 
	sld = characterFromId("Mirabella");
	sld.lifeday = 0;
	ChangeCharacterAddressGroup(sld, "none", "", "");
	sld = characterFromId("Mrt_Rocur");
	sld.dialog.currentnode = "rocur_86";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void Mtraxx_PasqualeNightOutHouse() // вышли из дома
{
	sld = characterFromId("Mrt_Rocur");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload1", "LaVega_town", "reload", "reload10", "Mtraxx_PasqualeNightOutHouse", -1);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
}

/*void Mtraxx_PasqualeNightGulf() // за воротами
{
	chrDisableReloadToLocation = false;
	sld = characterFromId("Mrt_Rocur");
	LAi_SetActorType(sld);
	LAi_ActorFollowEverywhere(sld, "", -1);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	pchar.quest.mtraxx_pasq_final.win_condition.l1 = "location";
	pchar.quest.mtraxx_pasq_final.win_condition.l1.location = "shore34";
	pchar.quest.mtraxx_pasq_final.function = "Mtraxx_PasqualeFinal";
}*/

void Mtraxx_PasqualeFinal(string qName) // завершающий разговор в заливе
{
	chrDisableReloadToLocation = true;
	sld = characterFromId("Mrt_Rocur");
	ChangeCharacterAddressGroup(sld, "shore34", "goto", "goto10");
	sld.dialog.currentnode = "rocur_90";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 0, 0);
	if (CheckAttribute(pchar, "questTemp.Mtraxx.Mirabella"))
	{
		sld = characterFromId("Mirabella");
		ChangeCharacterAddressGroup(sld, "shore34", "goto", "goto10");
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, pchar, "", -1);
	}
}

void Mtraxx_PasqualeAddComplete() // итоги
{
	chrDisableReloadToLocation = false;
	sld = characterFromId("Mrt_Rocur");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "sea", "none", "", "", "", 10.0);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	sld.lifeday = 0;
	Group_DeleteGroup("RocurSeaGroup");
	//AddQuestRecord("Roger_4", "17");
	CloseQuestHeader("Roger_4");
	LocatorReloadEnterDisable("LaVega_Exittown", "reload3", false);
	Mtraxx_PasqualeNightClear();
	if (CheckAttribute(pchar, "questTemp.Mtraxx.Mirabella"))
	{
		chrDisableReloadToLocation = true;
		sld = characterFromId("Mirabella");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		AddQuestRecord("Roger_4", "16");
	}
	else AddQuestRecord("Roger_4", "15");
	AddCharacterExpToSkill(pchar, "Sneak", 400);
	AddCharacterExpToSkill(pchar, "Fortune", 300);
}

void Mtraxx_PasqualeGrabbingCheck(string qName) // проверка на заход к Тираксу до ограбления Паскуале
{
	if (CheckAttribute(pchar, "questTemp.Mtraxx.Pasquale.Grabbing"))
	{
		DeleteAttribute(pchar, "questTemp.Mtraxx.Pasquale.Grabbing");
		pchar.quest.mtraxx_pasq_gonaiv.over = "yes";
		pchar.quest.Mtraxx_PasqualeJanTimer.over = "yes";
		pchar.quest.Mtraxx_PasqualeJanTimeOver.over = "yes";
		AddQuestRecord("Roger_4", "19");
		CloseQuestHeader("Roger_4");
	}
	else return;
}

void Mtraxx_PasqualeMirabella(string qName) // Мирабель вышла на Исла Моне
{
	float locx, locy, locz;
	bQuestDisableMapEnter = true;//закрыть карту
	pchar.GenQuest.MapClosedNoBattle = true;
	pchar.quest.Mtraxx_MirabellaSailOver.over = "yes";
	pchar.quest.mtraxx_pasq_mirabella.over = "yes";
	pchar.quest.mtraxx_pasq_mirabella1.over = "yes";
	sld = characterFromId("Mirabella");
	sld.dialog.currentnode = "mirabelle_14";
	RemovePassenger(pchar, sld);
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_SetActorType(sld);
	LAi_ActorFollowEverywhere(sld, "", -1);
	pchar.quest.mtraxx_islamona_mirabella.win_condition.l1 = "location";
	pchar.quest.mtraxx_islamona_mirabella.win_condition.l1.location = "IslaMona_TwoFloorHouse";
	pchar.quest.mtraxx_islamona_mirabella.function = "Mtraxx_PasqualeMirabellaHouse";
}

void Mtraxx_PasqualeMirabellaHouse(string qName) // привели Мирабель в дом
{
	LocatorReloadEnterDisable("IslaMona_TwoFloorHouse", "reload1", true);
	LocatorReloadEnterDisable("IslaMona_TwoFloorHouse", "reload3", true);
	sld = characterFromId("Mirabella");
	LAi_SetActorType(sld);
	LAi_ActorDialogDelay(sld, pchar, "", 2.0);
}

void Mtraxx_PasqualeMirabellaRoom(string qName) // привели Мирабель в комнату
{
	chrDisableReloadToLocation = true;
	LocatorReloadEnterDisable("IslaMona_TwoFloorHouse", "reload1", false);
	LocatorReloadEnterDisable("IslaMona_TwoFloorHouse", "reload3", false);
	sld = characterFromId("Mirabella");
	sld.dialog.currentnode = "mirabelle_18";
	LAi_SetStayType(sld);
	ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto3");
}

void Mtraxx_PasqualeMirabellaSex(string qName) // занялись любовью с ней
{
	EndQuestMovie();
	bDisableCharacterMenu = false;
	locCameraTarget(PChar);
	locCameraFollow();
	DeleteAttribute(pchar, "GenQuest.FrameLockEsc");
	LAi_SetPlayerType(pchar);
	sld = characterFromId("Mirabella");
	sld.model.animation = "towngirl";
	Characters_RefreshModel(sld);
	sld.dialog.currentnode = "mirabelle_22";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void Mtraxx_MirabellaSetLife(string qName) // устанавливаем поведение Мирабель в доме // прогона 3
{
	pchar.quest.mtraxx_mirabella_life.win_condition.l1 = "locator";
	pchar.quest.mtraxx_mirabella_life.win_condition.l1.location = "IslaMona_TwoFloorHouse";
	pchar.quest.mtraxx_mirabella_life.win_condition.l1.locator_group = "reload";
	pchar.quest.mtraxx_mirabella_life.win_condition.l1.locator = "reload1";
	pchar.quest.mtraxx_mirabella_life.again = true;
	pchar.quest.mtraxx_mirabella_life.function = "Mtraxx_MirabellaLife";
}

void Mtraxx_MirabellaLife(string qName) // поведение Мирабель в доме
{
	if (CheckAttribute(pchar, "questTemp.IslaMona.Tavern")) 
	{
		sld = characterFromId("Mirabella");
		ChangeCharacterAddressGroup(sld, "IslaMona_Town", "waitress", "barmen");
		LAi_SetWaitressType(sld);
		sld.greeting = "mirabella";
		return;
	}																	   
	sld = characterFromId("Mirabella");
	sld.greeting = "mirabella";
	LAi_SetStayType(sld);
	if (stf(environment.time) > 7.99 && stf(environment.time) < 21.0) // днем внизу
	{
		ChangeCharacterAddressGroup(sld, "IslaMona_TwoFloorHouse", "goto", "goto"+(rand(2)+1));
	}
	else
	{
		ChangeCharacterAddressGroup(sld, "IslaMona_TwoFloorRoom", "goto", "goto"+(rand(4)+1));
	}
}

void Mtraxx_MirabellaSex(string qName) // секс с Мирабель
{
	string sTemp;
	float fTime;
	ResetSound();
	pchar.GenQuest.FrameLockEsc = true;
	bDisableCharacterMenu = true;
	switch (rand(5))
	{
		case 0: 
			sTemp = "8";
			fTime = 5.0;
		break;
		
		case 1: 
			sTemp = "10";
			fTime = 5.0;
		break;
		
		case 2: 
			sTemp = "12";
			fTime = 5.0;
		break;
		
		case 3: 
			sTemp = "13";
			fTime = 5.0;
		break;
		
		case 4: 
			sTemp = "14";
			fTime = 5.0;
		break;
	}
	PlayStereoSound("sex\sex" + sTemp + ".wav");
	WaitDate("", 0, 0, 0, 2, 30);
	SetLaunchFrameFormParam("", "", 0, fTime);
	SetLaunchFrameFormPic("loading\inside\censored1.tga");
	LaunchFrameForm();
	if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	
	{
		AddCharacterHealth(pchar, 8);
		AddCharacterMaxHealth(pchar, 1.0);
	}
	else AddCharacterHealth(pchar, 4);
	LAi_SetCurHPMax(pchar);
	DoQuestFunctionDelay("Mtraxx_MirabellaAfterSex", fTime);
}

void Mtraxx_MirabellaAfterSex(string qName) // после секса с Мирабель
{
	EndQuestMovie();
	bDisableCharacterMenu = false;
	DeleteAttribute(pchar, "GenQuest.FrameLockEsc");
	LAi_SetPlayerType(pchar);
	ChangeCharacterAddressGroup(pchar, "IslaMona_TwoFloorRoom", "goto", "goto2");
	sld = characterFromId("Mirabella");
	sld.model.animation = "towngirl";
	Characters_RefreshModel(sld);
	ChangeCharacterAddressGroup(sld, "IslaMona_TwoFloorRoom", "goto", "goto4");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void Mtraxx_MirabellaSailOver(string qName) // не довез Мирабель
{
	if(bImCasual)
	{
		if(CheckAttribute(pchar,"quest.Mtraxx_MirabellaSailOver.over"))
			DeleteAttribute(pchar,"quest.Mtraxx_MirabellaSailOver.over");
		NewGameTip(StringFromKey("Roger_4"));
		SetFunctionTimerCondition("Mtraxx_MirabellaSailOver", 0, 0, 30, false);
		return;
	}
	pchar.quest.mtraxx_pasq_mirabella.over = "yes";
	pchar.quest.mtraxx_pasq_mirabella1.over = "yes";
	sld = characterFromId("Mirabella");
	sld.lifeday = 0;
	RemovePassenger(pchar, sld);
	Log_Info(StringFromKey("Roger_53"));
	PlaySound("interface\notebook.wav");
}

// эпизод 5 - Камни цвета леса и крови
void Mtraxx_MeridaBegin() // к Леприкону
{
	pchar.quest.mtraxx_merida_begin.win_condition.l1 = "location";
	pchar.quest.mtraxx_merida_begin.win_condition.l1.location = "LaVega_port";
	pchar.quest.mtraxx_merida_begin.win_condition.l2 = "Ship_location";
	pchar.quest.mtraxx_merida_begin.win_condition.l2.location = "LaVega_port";
	pchar.quest.mtraxx_merida_begin.function = "Mtraxx_MeridaCreateLepricon";
	SetFunctionTimerCondition("Mtraxx_MeridaSailTimer", 0, 0, 30, false);
}

void Mtraxx_MeridaSailTimer(string qName) // не доплыли до Маракайбо
{
	if(bImCasual)
	{
		if(CheckAttribute(pchar,"quest.Mtraxx_MeridaSailTimer.over"))
			DeleteAttribute(pchar,"quest.Mtraxx_MeridaSailTimer.over");
		NewGameTip(StringFromKey("Roger_4"));
		SetFunctionTimerCondition("Mtraxx_MeridaSailTimer", 0, 0, 30, false);
		return;
	}
	pchar.quest.mtraxx_merida_begin.over = "yes";
	pchar.quest.mtraxx_merida_sailover.win_condition.l1 = "Location_Type";
	pchar.quest.mtraxx_merida_sailover.win_condition.l1.location_type = "town";
	pchar.quest.mtraxx_merida_sailover.function = "Mtraxx_MeridaTimeOver";
	pchar.questTemp.Mtraxx = "merida_timeover";
}

void Mtraxx_MeridaTimeOver(string qName) // не доплыли до Маракайбо
{
	chrDisableReloadToLocation = true;
	float locx, locy, locz;
	sld = characterFromId("Mrt_Rocur");
	LAi_SetActorType(sld);
	sld.dialog.currentnode = "rocur_35";
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void Mtraxx_MeridaTimeOverFail() // не доплыли до Маракайбо
{
	chrDisableReloadToLocation = false;
	AddMoneyToCharacter(pchar, 50000);
	sld = characterFromId("Mrt_Rocur");
	RemovePassenger(pchar, sld);
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload4", "none", "", "", "", 10.0);
	sld.lifeday = 0;
	if (GetCharacterIndex("Lepricon") != -1)
	{
		sld = characterFromId("Lepricon");
		RemovePassenger(pchar, sld);
		sld.lifeday = 0;
	}
	AddQuestRecord("Roger_5", "2");
	Mtraxx_TerraxReset(5);
}

void Mtraxx_MeridaCreateLepricon(string qName) // ставим Леприкона с бригадой
{
	chrDisableReloadToLocation = true;
	sld = GetCharacter(NPC_GenerateCharacter("Lepricon", "Leprechaun", "man", "man", 25, PIRATE, -1, true, "quest"));
	sld.name = StringFromKey("Roger_54");
	sld.lastname = StringFromKey("Roger_55");
	sld.dialog.FileName = "Quest\Roger.c";
	sld.dialog.currentnode = "lepricon";
	sld.greeting = "Lepricon_01";
	sld.rank = 30;
	sld.reputation = 20;
	LAi_SetHP(sld, 420, 420);
	SetSPECIAL(sld, 7, 10, 8, 3, 5, 9, 5);
	SetSelfSkill(sld, 30, 40, 90, 75, 65);
	SetShipSkill(sld, 45, 50, 5, 5, 5, 5, 5, 5, 90);
	SetCharacterPerk(sld, "Energaiser");
	SetCharacterPerk(sld, "BasicDefense");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "BladeDancer");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "Gunman");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "BasicCommerce");
	sld.SuperShooter = true;
	RemoveAllCharacterItems(sld, true);
	GiveItem2Character(sld, "topor_01");
	EquipCharacterbyItem(sld, "topor_01");
	GiveItem2Character(sld, "pistol2");
	EquipCharacterbyItem(sld, "pistol2");
	LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "grapeshot");
    TakeNItems(sld, "grapeshot", 50);
	TakeNItems(sld, "gunpowder", 50);
	sld.cirassId = Items_FindItemIdx("cirass4");
	LAi_SetCheckMinHP(sld, 10, true, "");
	TakeNItems(sld, "potion2", 7);
	TakeNItems(sld, "potion3", 7);
	TakeNItems(sld, "potion4", 7);
	ChangeCharacterAddressGroup(sld, "Lavega_port", "goto", "goto1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	for (int i=5; i<=9; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Lepricons_pirate_"+i, "mercen_"+i, "man", "man", 20, PIRATE, -1, true, "quest"));
		FantomMakeCoolFighter(sld, 20, 55, 55, LinkRandPhrase("blade_04","blade_06","topor_02"), "pistol3", "grapeshot", 150);
		LAi_CharacterDisableDialog(sld);
		TakeNItems(sld, "potion2", 5);
		TakeNItems(sld, "potion3", 6);
		TakeNItems(sld, "potion4", 6);
		ChangeCharacterAddressGroup(sld, "Lavega_port", "goto", "goto2");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
}

void Mtraxx_MeridaSail() // отправляемся к Маракайбо
{
	sld = characterFromId("Lepricon");
	AddPassenger(pchar, sld, false);//добавить пассажира
	SetCharacterRemovable(sld, false);
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "sea", "none", "", "", "OpenTheDoors", -1);
	for (int i=5; i<=9; i++)
	{
		sld = characterFromId("Lepricons_pirate_"+i);
		LAi_SetActorType(sld);
		LAi_ActorRunToLocation(sld, "reload", "sea", "none", "", "", "", 10.0);
	}
	AddQuestRecord("Roger_5", "3");
	pchar.quest.mtraxx_merida_shore.win_condition.l1 = "location";
	pchar.quest.mtraxx_merida_shore.win_condition.l1.location = "Shore_ship3";
	pchar.quest.mtraxx_merida_shore.function = "Mtraxx_MeridaArriveShore";
}

void Mtraxx_MeridaArriveShore(string qName) // прибыли на мыс НН
{
	if (pchar.questTemp.Mtraxx == "merida_timeover") // опоздал
	{
		DoQuestFunctionDelay("Mtraxx_MeridaTimeOver", 2.0);
		pchar.quest.mtraxx_merida_sailover.over = "yes";
		return;
	}
	pchar.quest.Mtraxx_MeridaSailTimer.over = "yes";
	chrDisableReloadToLocation = true;
	bQuestDisableMapEnter = true;//закрыть карту
	pchar.GenQuest.MapClosedNoBattle = true;
	sld = characterFromId("Mrt_Rocur");
	sld.dialog.currentnode = "rocur_36";
	ChangeCharacterAddressGroup(sld, "Shore_ship3", "goto", "goto2");
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	sld = characterFromId("Lepricon");
	LAi_SetActorType(sld);
	sld.dialog.currentnode = "lepricon_2";
	ChangeCharacterAddressGroup(sld, "Shore_ship3", "goto", "goto1");
	LAi_SetActorType(sld);
	LAi_ActorFollow(sld, pchar, "", -1);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
}

void Mtraxx_MeridaSeekVillage() // ищем араваков
{
	chrDisableReloadToLocation = false;
	sld = characterFromId("Mrt_Rocur");
	LAi_SetActorType(sld);
	LAi_ActorFollowEverywhere(sld, "", -1);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	sld = characterFromId("Lepricon");
	LAi_SetActorType(sld);
	LAi_ActorFollowEverywhere(sld, "", -1);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	AddQuestRecord("Roger_5", "4");
	pchar.quest.mtraxx_merida_village.win_condition.l1 = "location";
	pchar.quest.mtraxx_merida_village.win_condition.l1.location = "Locono_village";
	pchar.quest.mtraxx_merida_village.function = "Mtraxx_MeridaFindVillage";
}

void Mtraxx_MeridaFindVillage(string qName) // нашли деревню
{
	pchar.questTemp.Mtraxx = "merida_village";
	// вождь Кумвана
	sld = GetCharacter(NPC_GenerateCharacter("Cumvana", "Kumvana", "man", "man", 25, SPAIN, -1, true, "native"));
	SetFantomParamFromRank(sld, 25, true);
	sld.name = StringFromKey("Roger_56");
	sld.lastname = StringFromKey("Roger_57");
	LAi_SetLoginTime(sld, 6.0, 21.99);
	sld.dialog.Filename = "indian_dialog.c";
	sld.dialog.currentnode = "cumvana";
	sld.greeting = "indian_male";
	GiveItem2Character(sld, "blade_02");
	EquipCharacterbyItem(sld, "blade_02");
	ChangeCharacterAddressGroup(sld, "Locono_shack1", "sit", "sit1");
	LAi_SetHuberType(sld);
	AddLandQuestMark(sld, "questmarkmain");
	// Хайами
	sld = GetCharacter(NPC_GenerateCharacter("Hayamee", "squaw_3", "woman", "woman_B", 10, SPAIN, -1, true, "native"));
	SetFantomParamFromRank(sld, 10, true);
	sld.name = StringFromKey("Roger_58");
	sld.lastname = StringFromKey("Roger_59");
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetImmortal(sld, true);
	sld.dialog.Filename = "indian_dialog.c";
	sld.dialog.currentnode = "IndianWoman";
	LAi_CharacterDisableDialog(sld);
	ChangeCharacterAddressGroup(sld, "Locono_village", "quest", "teleport1");
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "MiskitoGroup3");
	// Леприкона - гулять
	sld = characterFromId("Lepricon");
	sld.dialog.currentnode = "lepricon_3";
	LAi_SetWarriorType(sld);
	LAi_warrior_DialogEnable(sld, true);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
}

void Mtraxx_MeridaHayameeTimer(string qName) // ставим Тагофу
{
	sld = characterFromId("Hayamee");
	sld.dialog.currentnode = "hayamee_4";
	LAi_CharacterEnableDialog(sld);
	LAi_RemoveLoginTime(sld);
	ChangeCharacterAddressGroup(sld, "Locono_shack3", "quest", "quest1");
	// Тагофа - проводник
	sld = GetCharacter(NPC_GenerateCharacter("Tagofa", "miskito_6", "man", "man", 25, SPAIN, -1, true, "native"));
	SetFantomParamFromRank(sld, 25, true);
	sld.name = StringFromKey("Roger_60");
	sld.lastname = StringFromKey("Roger_61");
	sld.dialog.Filename = "Quest\Roger.c";
	sld.dialog.currentnode = "tagofa";
	sld.greeting = "indian_male";
	LAi_SetCheckMinHP(sld, 20, true, ""); // скрытое бессмертие
	GiveItem2Character(sld, "topor_05");
	EquipCharacterbyItem(sld, "topor_05");
	ChangeCharacterAddressGroup(sld, "Locono_shack3", "sit", "sit1");
	LAi_SetLayType(sld);
	LAi_CharacterDisableDialog(sld);
	LAi_group_MoveCharacter(sld, "MiskitoGroup3");
}

void Mtraxx_MeridaTagofaHide(string qName) // 
{
	sld = characterFromId("Hayamee");
	sld.dialog.currentnode = "hayamee_14";
	LAi_CharacterEnableDialog(sld);
	sld = characterFromId("Tagofa");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	LAi_SetStayType(sld);
	LAi_group_MoveCharacter(sld, "MiskitoGroup3");
}

void Mtraxx_MeridaPotionLate(string qName) // тянет время до разговора с Хайами
{
	if(bImCasual)
	{
		if(CheckAttribute(pchar,"quest.Mtraxx_MeridaPotionLate.over"))
			DeleteAttribute(pchar,"quest.Mtraxx_MeridaPotionLate.over");
		NewGameTip(StringFromKey("Roger_4"));
		SetFunctionTimerCondition("Mtraxx_MeridaPotionLate", 0, 0, 10, false);
		return;
	}
	sld = characterFromId("Hayamee");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	sld.lifeday = 0;
	if (pchar.location == "Locono_village") DoQuestFunctionDelay("Mtraxx_MeridaPotionOver", 1.0);
	else
	{
		pchar.quest.mtraxx_merida_hayameelate.win_condition.l1 = "location";
		pchar.quest.mtraxx_merida_hayameelate.win_condition.l1.location = "Locono_village";
		pchar.quest.mtraxx_merida_hayameelate.function = "Mtraxx_MeridaPotionOver";
	}
}

void Mtraxx_MeridaHayameeHardTagofaWait(string qName) // ждем сутки по силовому варианту
{
	pchar.quest.mtraxx_merida_HayameeHardTagofa.win_condition.l1 = "location";
	pchar.quest.mtraxx_merida_HayameeHardTagofa.win_condition.l1.location = "Locono_shack1";
	pchar.quest.mtraxx_merida_HayameeHardTagofa.function = "Mtraxx_MeridaHayameeHardTagofa";
}

void Mtraxx_MeridaHayameeHardLepriconDialog(string qName) // после угроз вождю, Леприкон подойдёт к нам с диалогом
{
	pchar.quest.Mtraxx_MeridaPotionLate.over = "yes";
	chrDisableReloadToLocation = true;
	sld = characterFromId("Lepricon");
	sld.dialog.Filename = "Quest\Roger.c";
	sld.dialog.currentnode = "MeridaObsuzhdenie_Bad_1";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void Mtraxx_MeridaHayameeGoodDialog(string qName) // отказались от похода, Красавчик подойдёт к нам с диалогом
{
	pchar.quest.Mtraxx_MeridaPotionLate.over = "yes";
	chrDisableReloadToLocation = true;
	sld = characterFromId("Mrt_Rocur");
	sld.dialog.Filename = "Quest\Roger.c";
	sld.dialog.currentnode = "MeridaObsuzhdenie_Good_1";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	
	sld = characterFromId("Lepricon");
	ChangeCharacterAddressGroup(sld, "Locono_village", "goto", "goto4");
	LAi_SetActorType(sld);
	LAi_ActorFollow(sld, pchar, "", -1);
}

void Mtraxx_MeridaHayameeHardTagofa(string qName) // зашли в хижину
{
	if (GetCharacterIndex("Tagofa") != -1)
	{
		sld = characterFromId("Tagofa");
		ChangeCharacterAddressGroup(sld, "Locono_shack1", "goto", "goto2");
		LAi_CharacterEnableDialog(sld);
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	else
	{
		sld = GetCharacter(NPC_GenerateCharacter("Tagofa", "miskito_6", "man", "man", 25, SPAIN, -1, true, "native"));
		SetFantomParamFromRank(sld, 25, true);
		sld.name = StringFromKey("Roger_60");
		sld.lastname = StringFromKey("Roger_61")
		sld.dialog.Filename = "Quest\Roger.c";
		sld.dialog.currentnode = "tagofa";
		sld.greeting = "indian_male";
		LAi_SetCheckMinHP(sld, 20, true, ""); // скрытое бессмертие
		GiveItem2Character(sld, "topor_05");
		EquipCharacterbyItem(sld, "topor_05");
		ChangeCharacterAddressGroup(sld, "Locono_shack1", "goto", "goto2");
		LAi_SetStayType(sld);
		LAi_group_MoveCharacter(sld, "MiskitoGroup3");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
}

void Mtraxx_MeridaPotionOver(string qName) // затянул время
{
	chrDisableReloadToLocation = true;
	sld = characterFromId("Lepricon");
	LAi_SetActorType(sld);
	sld.dialog.currentnode = "lepricon_10";
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void Mtraxx_MeridaHayameeLate(string qName) // опоздание принести вещи Хайами
{
	if(bImCasual)
	{
		if(CheckAttribute(pchar,"quest.Mtraxx_MeridaHayameeLate.over"))
			DeleteAttribute(pchar,"quest.Mtraxx_MeridaHayameeLate.over");
		NewGameTip(StringFromKey("Roger_4"));
		SetFunctionTimerCondition("Mtraxx_MeridaHayameeLate", 0, 0, 15, false);
		return;
	}
	sld = characterFromId("Hayamee");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	sld.lifeday = 0;
	sld = characterFromId("Tagofa");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	sld.lifeday = 0;
	if (pchar.location == "Locono_village") DoQuestFunctionDelay("Mtraxx_MeridaHayameeOver", 1.0);
	else
	{
		pchar.quest.mtraxx_merida_hayameelate.win_condition.l1 = "location";
		pchar.quest.mtraxx_merida_hayameelate.win_condition.l1.location = "Locono_village";
		pchar.quest.mtraxx_merida_hayameelate.function = "Mtraxx_MeridaHayameeOver";
	}
}

void Mtraxx_MeridaHayameeOver(string qName) // Хайами и Тагофа ушли
{
	chrDisableReloadToLocation = true;
	sld = characterFromId("Lepricon");
	LAi_SetActorType(sld);
	sld.dialog.currentnode = "lepricon_9";
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void Mtraxx_MeridaHayameeFail() // Хайами и Тагофа ушли
{
	chrDisableReloadToLocation = false;
	sld = characterFromId("Lepricon");
	RemovePassenger(pchar, sld);
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 20.0);
	sld.lifeday = 0;
	sld = characterFromId("Mrt_Rocur");
	RemovePassenger(pchar, sld);
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 20.0);
	sld.lifeday = 0;
	Mtraxx_TerraxReset(5);
}

void Mtraxx_MeridaRemoveGifts() // удалить подарки Хайами
{
	PlaySound("interface\important_item.wav");
	for (int i=1; i<=3; i++)
	{
		if (GetCharacterFreeItem(pchar, "spyglass"+i) > 0)
		{	
			RemoveItems(pchar, "spyglass"+i, 1);
			i = 3;
		}
	}
	RemoveItems(pchar, "pistol3", 1);
	RemoveItems(pchar, "pistol5", 1);
	RemoveItems(pchar, "bullet", 30);
	RemoveItems(pchar, "grapeshot", 30);
	RemoveItems(pchar, "gunpowder", 60);
	RemoveItems(pchar, "jewelry41", 1);
	RemoveItems(pchar, "jewelry42", 1);
	ChangeIndianRelation(3.0);
	AddCharacterExpToSkill(pchar, "Leadership", 100);
}

void Mtraxx_MeridaTagofaEnter(string qName) // пришёл Тагофа
{
	sld = characterFromId("Tagofa");
	ChangeCharacterAddressGroup(sld, "Locono_shack3", "reload", "reload1");
	LAi_CharacterEnableDialog(sld);
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void Mtraxx_MeridaBoatLate(string qName) // опоздание построить лодки
{
	if(bImCasual)
	{
		if(CheckAttribute(pchar,"quest.Mtraxx_MeridaBoatLate.over"))
			DeleteAttribute(pchar,"quest.Mtraxx_MeridaBoatLate.over");
		NewGameTip(StringFromKey("Roger_4"));
		SetFunctionTimerCondition("Mtraxx_MeridaBoatLate", 0, 0, 10, false);
		return;
	}
	sld = characterFromId("Hayamee");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	sld.lifeday = 0;
	sld = characterFromId("Tagofa");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	sld.lifeday = 0;
	if (pchar.location == "Maracaibo_river") DoQuestFunctionDelay("Mtraxx_MeridaBoatOver", 1.0);
	else
	{
		pchar.quest.mtraxx_merida_hayameelate.win_condition.l1 = "location";
		pchar.quest.mtraxx_merida_hayameelate.win_condition.l1.location = "Maracaibo_river";
		pchar.quest.mtraxx_merida_hayameelate.function = "Mtraxx_MeridaBoatOver";
	}
}

void Mtraxx_MeridaBoatOver(string qName) // опоздание построить лодки
{
	chrDisableReloadToLocation = true;
	sld = characterFromId("Lepricon");
	LAi_SetActorType(sld);
	sld.dialog.currentnode = "lepricon_11";
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void Mtraxx_MeridaBuildBoats() // строим лодки
{
	pchar.quest.Mtraxx_MeridaBoatLate.over = "yes";
	LocatorReloadEnterDisable("Shore_ship3", "boat", true); // закроем море
	RemoveCharacterGoods(pchar, GOOD_PLANKS, 20);
	RemoveCharacterGoods(pchar, GOOD_LEATHER, 10);
	bDisableCharacterMenu = true;
	pchar.GenQuest.FrameLockEsc = true;
	PlaySound("ambient\ShipYard\Fon_Out_01.wav");
	PlaySound("ambient\ShipYard\pila_001.wav");
	PlaySound("ambient\ShipYard\topor_001.wav");
	pchar.questTemp.Mtraxx = "merida_trip";
	SetLaunchFrameFormParam(StringFromKey("Roger_62", NewStr()), "Mtraxx_MeridaBuildBoats", 0, 5);
	LaunchFrameForm();
	StoreDayUpdate();
	WaitDate("",0,0,2,3,5);
	RecalculateJumpTable();
	RefreshWeather();
	RefreshLandTime();
	int n = Findlocation("Maracaibo_river");
	string sTemp;
	for (int i=1; i<=6; i++)
	{
		sTemp = "Boat"+i;
		locations[n].models.always.(sTemp) = "Boat";
		Locations[n].models.always.(sTemp).locator.group = "quest";
		Locations[n].models.always.(sTemp).locator.name = "boat"+i;
		Locations[n].models.always.(sTemp).tech = "DLightModel";
	}
	sld = characterFromId("Tagofa");
	LAi_CharacterEnableDialog(sld);
	AddCharacterExpToSkill(pchar, "Repair", 200);
}

void Mtraxx_MeridaWarning(string qName) // знак капонгов на тропе
{
	sld = characterFromId("Tagofa");
	sld.dialog.currentnode = "tagofa_13";
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, pchar, "", -1);
}

void Mtraxx_MeridaPrepareCapongAttack(string qName) // готовим атаку капонгов
{
	int i = rand(7)+3;
	DoQuestFunctionDelay("Mtraxx_MeridaCapongAttack", i);
	chrDisableReloadToLocation = true;
}

void Mtraxx_MeridaOurWarriorsAttack() // наши - к бою готовы!
{
	sld = characterFromId("Mrt_Rocur");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	sld = characterFromId("Lepricon");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	for (int i=5; i<=9; i++) // ребята Леприкона
	{
		if (GetCharacterIndex("Lepricons_pirate_"+i) != -1) 
		{
			sld = characterFromId("Lepricons_pirate_"+i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
	}
	for (i=1; i<=8; i++) // наши красавцы
	{
		if (GetCharacterIndex("Merida_pirate_"+i) != -1) 
		{
			sld = characterFromId("Merida_pirate_"+i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
	}
}

void Mtraxx_MeridaCheckOurWarriors() // проверка наших после боев // правки прогона 3
{
	sld = characterFromId("Mrt_Rocur");
	LAi_SetActorType(sld);
	LAi_ActorFollowEverywhere(sld, "", -1);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	sld = characterFromId("Lepricon");
	LAi_SetActorType(sld);
	LAi_ActorFollowEverywhere(sld, "", -1);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	for (int i=5; i<=9; i++) // ребята Леприкона
	{
		if (GetCharacterIndex("Lepricons_pirate_"+i) != -1) 
		{
			sld = characterFromId("Lepricons_pirate_"+i);
			if (LAi_GetCharacterHP(sld) > 0)
			{
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
	}
	}
	for (i=1; i<=8; i++) // наши красавцы
	{
		if (GetCharacterIndex("Merida_pirate_"+i) != -1) 
		{
			sld = characterFromId("Merida_pirate_"+i);
			if (LAi_GetCharacterHP(sld) > 0)
			{
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
		}
	}
}

void Mtraxx_MeridaCapongAttack(string qName) // атака капонгов
{
	PlaySound("interface\abordage_wining.wav");
	// активируем наших
	sld = characterFromId("Tagofa");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
	Mtraxx_MeridaOurWarriorsAttack();
	// ставим капонгов
	LAi_group_Delete("EnemyFight");
	for (i=1; i<=12; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Capong_land_"+i, "canib_"+(rand(5)+1), "man", "man", 18, PIRATE, -1, false, "native"));
		FantomMakeCoolFighter(sld, 18, 55, 55, RandPhraseSimple("blade_01","blade_02"), "", "", 140);
		sld.name = GetIndianName(MAN);
		sld.lastname = "";
		sld.viper = true;
		if (i < 7) ChangeCharacterAddressGroup(sld, "Merida_jungle_01", "goto", "goto10");
		else ChangeCharacterAddressGroup(sld, "Merida_jungle_01", "monsters", "monster10");
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "Mtraxx_MeridaCapongAfterFight");
	LAi_SetFightMode(pchar, true);
}

void Mtraxx_MeridaExitTown(string qName) // у ворот Мериды
{
	chrDisableReloadToLocation = true;
	sld = characterFromId("Tagofa");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "quest", "waterfall", "", -1);
	//LAi_group_MoveCharacter(sld, "TMP_FRIEND"); // правки прогона 3
	LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
	// ставим дозорного
	sld = GetCharacter(NPC_GenerateCharacter("Merida_guard", "mercen_23", "man", "man", 25, SPAIN, -1, true, "quest"));
	FantomMakeCoolFighter(sld, 25, 70, 70, "blade_13", "pistol3", "grapeshot", 150);
	sld.dialog.Filename = "Quest\Roger.c";
	sld.dialog.currentnode = "merida_guard";
	sld.greeting = "";
	LAi_SetImmortal(sld, true);
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	ChangeCharacterAddressGroup(sld, "Merida_ExitTown", "quest", "protector");
	LAi_SetGuardianType(sld);
	sld.protector = true;
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
}

void Mtraxx_MeridaHouseGuards(string qName) // выскочили мушкетеры
{
	LAi_group_Delete("EnemyFight");
	Mtraxx_MeridaOurWarriorsAttack();
	// ставим трёх поселенцев-мушкетеров
	for (int i=1; i<=3; i++) 
	{
		sld = GetCharacter(NPC_GenerateCharacter("Merida_mushketer_"+i, "mush_ctz_"+i, "man", "mushketer", 25, SPAIN, -1, true, "quest"));
		if (i == 1) 
		{
			FantomMakeCoolFighter(sld, 25, 100, 100, "", "grape_mushket", "grenade", 180);
			LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "grenade");
			if (MOD_SKILL_ENEMY_RATE > 2)
			{
				sld.cirassId = Items_FindItemIdx("cirass1");
				sld.MultiShooter = 1.0 + stf(MOD_SKILL_ENEMY_RATE/10);
				sld.MusketerDistance = 5;
			}
		}
		else 
		{
			FantomMakeCoolFighter(sld, 25, 60, 60, "", "mushket1", "cartridge", 150);
			LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "cartridge");
			sld.MusketerDistance = 0;
		}
		SetCharacterPerk(sld, "Gunman");
		SetCharacterPerk(sld, "GunProfessional");
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		ChangeCharacterAddressGroup(sld, "Merida_ExitTown", "quest", "mushketer"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_SetFightMode(pchar, true);
	DoQuestFunctionDelay("Mtraxx_MeridaGateAttack", 10.0);
}

void Mtraxx_MeridaGateAttack(string qName) // драка у ворот
{
	PlaySound("interface\abordage_wining.wav");
	sld = characterFromId("Merida_guard");
	LAi_SetImmortal(sld, false);
	ChangeCharacterAddressGroup(sld, "Merida_ExitTown", "reload", "reload2");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	for (int i=1; i<=12; i++) 
	{
		if (i < 3)
		{
			sld = GetCharacter(NPC_GenerateCharacter("Merida_defender_"+i, "mush_spa_"+i, "man", "mushketer", 25, SPAIN, -1, true, "quest"));
			FantomMakeCoolFighter(sld, 25, 70, 70, "", "mushket1", "cartridge", 170);
			LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "cartridge");
			if (MOD_SKILL_ENEMY_RATE > 2) sld.cirassId = Items_FindItemIdx("cirass1");
		}
		else
		{
			sld = GetCharacter(NPC_GenerateCharacter("Merida_defender_"+i, "sold_spa_"+(rand(7)+1), "man", "man", 25, SPAIN, -1, true, "quest"));
			FantomMakeCoolFighter(sld, 25, 70, 70, LinkRandPhrase("blade_08","blade_12","blade_14"), "pistol3", "grapeshot", 150);
			if (MOD_SKILL_ENEMY_RATE > 2) sld.cirassId = Items_FindItemIdx("cirass2");
		}
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		ChangeCharacterAddressGroup(sld, "Merida_ExitTown", "reload", "reload2");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetCheck("EnemyFight", "Mtraxx_MeridaGateAfterBattle");
}

void Mtraxx_MeridaTown(string qName) // бой в Мериде
{
	PlaySound("interface\abordage_wining.wav");
	LAi_group_Delete("EnemyFight");
	chrDisableReloadToLocation = true;
	Mtraxx_MeridaOurWarriorsAttack();
	for (i=1; i<=3; i++)
	{
		int idx = GetOfficersIndex(pchar, i);
		if (idx < 1) continue;
		sld = &Characters[idx];
		ChangeCharacterAddressGroup(sld, "Merida_Town", "officers", "reload19_"+i);
	}
	// защитники
	for (int i=1; i<=12; i++) 
	{
		if (i > 9)
		{
			sld = GetCharacter(NPC_GenerateCharacter("Merida_citizen_"+i, "mush_spa_"+(i-9), "man", "mushketer", 25, SPAIN, -1, true, "quest"));
			FantomMakeCoolFighter(sld, 25, 70, 70, "", "mushket1", "cartridge", 170);
			LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "cartridge");
			if (MOD_SKILL_ENEMY_RATE > 2) sld.cirassId = Items_FindItemIdx("cirass1");
			sld.MusketerDistance = 0;
			ChangeCharacterAddressGroup(sld, "Merida_Town", "rld", "loc"+(i-10));
		}
		else
		{
			sld = GetCharacter(NPC_GenerateCharacter("Merida_citizen_"+i, "citiz_1"+i, "man", "man", 15, SPAIN, -1, true, "quest"));
			FantomMakeCoolFighter(sld, 15, 40, 40, LinkRandPhrase("blade_09","blade_11","blade_14"), "pistol1", "bullet", 100);
			ChangeCharacterAddressGroup(sld, "Merida_Town", "goto", "goto"+i);
		}
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "Mtraxx_MeridaAfterBattle");
	LAi_SetFightMode(pchar, true);
}

void Mtraxx_MeridaTownhall(string qName) // в резиденции Мериды
{
	chrDisableReloadToLocation = true;
	// ставим мэра
	sld = GetCharacter(NPC_GenerateCharacter("Merida_head", "huber_spa", "man", "man", 20, SPAIN, 1, true, "quest"));
	FantomMakeCoolFighter(sld, 20, 50, 50, "blade_15", "", "", 100);
	sld.dialog.Filename = "Quest\Roger.c";
	sld.dialog.currentnode = "merida_head";
	sld.name = StringFromKey("Roger_63");
	sld.lastname = StringFromKey("Roger_64");
	sld.greeting = "";
	LAi_SetImmortal(sld, true);
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	ChangeCharacterAddressGroup(sld, "Merida_townhall", "goto", "goto1");
	LAi_SetStayType(sld);
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
}

void Mtraxx_MeridaExit(string qName) // покидаем город
{
	DoQuestFunctionDelay("Mtraxx_MeridaGorit_1", 4.0);
	//Mtraxx_MeridaCheckOurWarriors();
	// антураж захваченного города
	for (int i=1; i<=21; i++) // дым
	{
		if (i == 3) continue;
		CreateLocationParticles("large_smoke", "reload", "reload"+i, 0, 0, 0, "");
	}
	for (i=1; i<=21; i++) // огонь
	{
		if (i == 3) continue;
		CreateLocationParticles("shipfire", "reload", "reload"+i, 0, 0, 0, "fortfire");
	}
	for (i=1; i<=18; i++) // дым
	{
		if (i == 3 || i == 16) continue;
		CreateLocationParticles("large_smoke", "goto", "goto"+i, 0, 0, 0, "");
	}
	for (i=32; i<=37; i++) // дым
	{
		CreateLocationParticles("large_smoke", "goto", "goto"+i, 0, 0, 0, "");
	}
	for (i=1; i<=9; i++) // жертвы нападения
	{
		if (i < 6)
		{
			sld = GetCharacter(NPC_GenerateCharacter("Merida_victim_"+i, "citiz_1"+i, "man", "man_dead", 5, SPAIN, 1, true, "quest"));
			SetFantomParamFromRank(sld, 5, true);
		}
		else
		{
			sld = GetCharacter(NPC_GenerateCharacter("Merida_victim_"+i, "women_"+(4+i), "woman", "towngirl", 5, SPAIN, 1, true, "quest"));
			SetFantomParamFromRank(sld, 5, true);
		}
		RemoveAllCharacterItems(sld, true);
		sld.DontClearDead = true;
		LAi_SetStayType(sld);
		ChangeCharacterAddressGroup(sld, "Merida_town", "goto", "goto"+(15+i));
		LAi_KillCharacter(sld);
	}
	for (i=3; i<=10; i++) // жертвы нападения 2
	{
		if (i == 3 || i == 8)
		{
			sld = GetCharacter(NPC_GenerateCharacter("Merida_victim2_"+i, "women_"+(4+i), "woman", "towngirl", 5, SPAIN, 1, true, "quest"));
			SetFantomParamFromRank(sld, 5, true);
		}
		else
		{
			sld = GetCharacter(NPC_GenerateCharacter("Merida_victim2_"+i, "citiz_1"+i, "man", "man_dead", 5, SPAIN, 1, true, "quest"));
			SetFantomParamFromRank(sld, 5, true);
		}
		RemoveAllCharacterItems(sld, true);
		sld.DontClearDead = true;
		sld.DeadWithBlade = true;
		LAi_SetStayType(sld);
		ChangeCharacterAddressGroup(sld, "Merida_town", "goto", "goto"+(i));
		LAi_KillCharacter(sld);
	}
	// открываем локаторы
	LocatorReloadEnterDisable("Merida_ExitTown", "reload1_back", false);
	LocatorReloadEnterDisable("Merida_Town", "gate_back", false);
	pchar.quest.mtraxx_merida_back.win_condition.l1 = "location";
	pchar.quest.mtraxx_merida_back.win_condition.l1.location = "Merida_ExitTown";
	pchar.quest.mtraxx_merida_back.function = "Mtraxx_MeridaBack";
	// НЗГ
	pchar.quest.mtraxx_merida_headhunt.win_condition.l1 = "MapEnter";
	pchar.quest.mtraxx_merida_headhunt.function = "Mtraxx_MeridaHeadHunter";
}

void Mtraxx_MeridaGorit_1(string qName)
{
	LAi_FadeLong("", "");
	DoQuestFunctionDelay("Mtraxx_MeridaGorit_2", 1.0);
	
	CharacterTurnToLoc(pchar, "goto", "goto28");
}

void Mtraxx_MeridaGorit_2(string qName)
{
	locCameraFlyToPositionLookToHero(-4.09, 2.37, 39.60, 7.29, 2.47, 28.49, 0.001300*GetDeltaTime(), -1);
	Pchar.FuncCameraFly = "";
	DoQuestFunctionDelay("Mtraxx_MeridaGorit_3", 10.0);
}

void Mtraxx_MeridaGorit_3(string qName)
{
	LAi_FadeLong("", "");
	DoQuestFunctionDelay("Mtraxx_MeridaGorit_4", 1.0);
}

void Mtraxx_MeridaGorit_4(string qName)
{
	//LAi_SetPlayerType(pchar);
	//EndQuestMovie();
	locCameraResetState();
	LAi_SetStayType(pchar);
	sld = CharacterFromID("Lepricon");
	ChangeCharacterAddressGroup(sld, "Merida_town", "goto", "goto28");
	sld.dialog.currentnode = "lepricon_19";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void Mtraxx_MeridaGorit_5(string qName)
{
	LAi_SetStayType(pchar);
	sld = CharacterFromID("Mrt_Rocur");
	ChangeCharacterAddressGroup(sld, "Merida_town", "reload", "reload3");
	sld.dialog.currentnode = "rocur_100";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 0.5, 0);
}

void Mtraxx_MeridaHeadHunter(string qName) // НЗГ и прочее
{
	ChangeCharacterComplexReputation(pchar, "fame", 10);
	ChangeCharacterComplexReputation(pchar, "authority", 5);
	ChangeCharacterComplexReputation(pchar, "nobility", -20);
	OfficersReaction("bad");
	OfficersReaction("bad");
	ChangeCharacterHunterScore(PChar, "spahunter", 30);
}

void Mtraxx_MeridaBack(string qName) // вышли из Мериды
{
	LocatorReloadEnterDisable("Merida_ExitTown", "reload2", true);
	sld = characterFromId("Tagofa");
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	LAi_ActorFollowEverywhere(sld, "", -1);
	pchar.quest.mtraxx_merida_cave.win_condition.l1 = "location";
	pchar.quest.mtraxx_merida_cave.win_condition.l1.location = "Serpentine_cave";
	pchar.quest.mtraxx_merida_cave.function = "Mtraxx_MeridaCave";
}

void Mtraxx_MeridaCave(string qName) // в пещере
{
	int i = 3 + rand(3);
	chrDisableReloadToLocation = true;
	DoQuestFunctionDelay("Mtraxx_MeridaCaveAttack", i);
}

void Mtraxx_MeridaCaveAttack(string qName) // атака капонгов в пещере
{
	PlaySound("interface\abordage_wining.wav");
	// активируем наших
	sld = characterFromId("Tagofa");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
	Mtraxx_MeridaOurWarriorsAttack();
	// ставим капонгов
	LAi_group_Delete("EnemyFight");
	for (i=1; i<=8; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Capong_cave_"+i, "canib_"+(rand(5)+1), "man", "man", 25, PIRATE, -1, false, "native"));
		FantomMakeCoolFighter(sld, 25, 80, 80, RandPhraseSimple("blade_01","blade_02"), "", "", 150);
		sld.name = GetIndianName(MAN);
		sld.lastname = "";
		sld.viper = true;
		ChangeCharacterAddressGroup(sld, "Serpentine_cave", "monsters", "monster"+i);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "Mtraxx_MeridaCaveVtoryaVolna");
	//LAi_group_SetCheck("EnemyFight", "Mtraxx_MeridaCaveAfterFight");
	LAi_SetFightMode(pchar, true);
}

void Mtraxx_MeridaReturn(string qName) // уплываем назад по реке
{
	bDisableCharacterMenu = true;
	pchar.GenQuest.FrameLockEsc = true;
	SetMusic("music_map");
	SetLaunchFrameFormParam("", "", 0, 15);
	SetLaunchFrameFormPic("loading\River_1.tga");
	LaunchFrameForm();
	WaitDate("", 0, 0, 2, 2, 20); //крутим время
	RecalculateJumpTable();
	StoreDayUpdate();
	RefreshWeather();
	RefreshLandTime();
	DoQuestFunctionDelay("Mtraxx_MeridaReturnEnd", 15.0);
}

void Mtraxx_MeridaReturnEnd(string qName) // уплываем назад по реке
{
	DoQuestReloadToLocation("Maracaibo_river", "reload", "reload2", "Mtraxx_MeridaReturnEnd");
}

void Mtraxx_MeridaFinal(string qName) // на берегу, дележ добычи
{
	chrDisableReloadToLocation = true;
	pchar.GenQuest.Hunter2Pause = true;
	// чистим нпс
	for (int i=5; i<=9; i++) // ребята Леприкона
	{
		if (GetCharacterIndex("Lepricons_pirate_"+i) != -1) 
		{
			sld = characterFromId("Lepricons_pirate_"+i);
			sld.lifeday = 0;
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
	}
	for (i=1; i<=8; i++) // наши красавцы
	{
		if (GetCharacterIndex("Merida_pirate_"+i) != -1) 
		{
			sld = characterFromId("Merida_pirate_"+i);
			sld.lifeday = 0;
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
	}
	sld = characterFromId("Mrt_Rocur");
	sld.dialog.currentnode = "rocur_44";
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void Mtraxx_MeridaReturnLate(string qName) // затянул с возвращением
{
	if(bImCasual)
	{
		if(CheckAttribute(pchar,"quest.Mtraxx_MeridaReturnLate.over"))
			DeleteAttribute(pchar,"quest.Mtraxx_MeridaReturnLate.over");
		NewGameTip(StringFromKey("Roger_4"));
		SetFunctionTimerCondition("Mtraxx_MeridaReturnLate", 0, 0, 40, false);
		return;
	}
	pchar.quest.mtraxx_merida_returnover.win_condition.l1 = "Location_Type";
	pchar.quest.mtraxx_merida_returnover.win_condition.l1.location_type = "town";
	pchar.quest.mtraxx_merida_returnover.function = "Mtraxx_MeridaReturnOver";
	pchar.quest.mtraxx_merida_returnover1.win_condition.l1 = "Location_Type";
	pchar.quest.mtraxx_merida_returnover1.win_condition.l1.location_type = "seashore";
	pchar.quest.mtraxx_merida_returnover1.function = "Mtraxx_MeridaReturnOver";
	pchar.questTemp.Mtraxx = "merida_returnover";
}

void Mtraxx_MeridaReturnOver(string qName) // затянул с возвращением
{
	if (pchar.questTemp.Mtraxx != "merida_returnover") return;
	chrDisableReloadToLocation = true;
	float locx, locy, locz;
	sld = characterFromId("Lepricon");
	LAi_SetActorType(sld);
	sld.dialog.currentnode = "lepricon_12";
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void Mtraxx_MeridaReturnFail() // затянул с возвращением
{
	pchar.quest.mtraxx_merida_lavega.over = "yes";
	chrDisableReloadToLocation = false;
	sld = characterFromId("Lepricon");
	RemovePassenger(pchar, sld);
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload4", "none", "", "", "", 10.0);
	sld.lifeday = 0;
	sld = characterFromId("Mrt_Rocur");
	RemovePassenger(pchar, sld);
	sld.lifeday = 0;
	AddQuestRecord("Roger_5", "21");
	Mtraxx_TerraxReset(5);
}

// Эпизод 6. Двуликий Янус.
void Mtraxx_IgnasioKitty(string qName) // ставим пинас Китти
{
	bQuestDisableMapEnter = true;//закрыть карту
	pchar.GenQuest.MapClosedNoBattle = true;
	pchar.quest.mtraxx_merida_returnover.over = "yes";
	pchar.quest.mtraxx_merida_returnover1.over = "yes";
	pchar.quest.Mtraxx_MeridaReturnLate.over = "yes";
	LocatorReloadEnterDisable("LaVega_port", "boat", true);
	Group_FindOrCreateGroup("Mtr_Kitty");
	sld = GetCharacter(NPC_GenerateCharacter("Mtr_KittyCap", "mercen_10", "man", "man", 20, ENGLAND, -1, false, "soldier"));
	FantomMakeCoolSailor(sld, SHIP_PINNACE, StringFromKey("Roger_65"), CANNON_TYPE_CANNON_LBS16, 50, 50, 50);
	FantomMakeCoolFighter(sld, 20, 40, 40, "blade_11", "pistol1", "bullet", 50);
	SetShipSkill(sld, 30, 90, 40, 45, 65, 55, 20, 50, 45);
	sld.Dialog.Filename = "Quest\Roger.c";
	sld.DeckDialogNode = "kittycap";
	sld.greeting = "captain";
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.Ship.Mode = "pirate";
	SetCharacterPerk(sld, "MusketsShoot");
	UpgradeShipParameter(sld, "Capacity");
	int iSpace = GetCharacterFreeSpace(sld, GOOD_EBONY);
	Fantom_SetCharacterGoods(sld, GOOD_EBONY, iSpace, 1);
	sld.Abordage.Enable = false;
	sld.AlwaysFriend = true;
	sld.ShipEnemyDisable = true; 
	LAi_SetImmortal(sld, true); // сплошная защита от дурака
	sld.DontDeskTalk = true;
	Group_AddCharacter("Mtr_Kitty", "Mtr_KittyCap");
	Group_SetGroupCommander("Mtr_Kitty", "Mtr_KittyCap");
	Group_SetTaskNone("Mtr_Kitty");
	Group_SetAddress("Mtr_Kitty", "Hispaniola1", "quest_ships", "quest_ship_3");
	Group_LockTask("Mtr_Kitty");
}

void Mtraxx_IgnasioTimeOver(string qName) // опоздали
{
	if(bImCasual)
	{
		if(CheckAttribute(pchar,"quest.Mtraxx_IgnasioTimeOver.over"))
			DeleteAttribute(pchar,"quest.Mtraxx_IgnasioTimeOver.over");
		NewGameTip(StringFromKey("Roger_4"));
		SetFunctionTimerCondition("Mtraxx_IgnasioTimeOver", 0, 0, 30, false);
		return;
	}
	pchar.quest.mtraxx_ignasio_sail.over = "yes";
	pchar.quest.mtraxx_ignasio_sinkkitty.over = "yes";
	sld = characterFromId("Mtr_KittyCap");
	RemoveCharacterCompanion(pchar, sld);
	AddQuestRecord("Roger_6", "2");
	Mtraxx_TerraxReset(6);
}

void Mtraxx_IgnasioKittySink(string qName) // потеряли пинас
{
	pchar.quest.mtraxx_ignasio_sail.over = "yes";
	pchar.quest.Mtraxx_IgnasioTimeOver.over = "yes";
	AddQuestRecord("Roger_6", "3");
	Mtraxx_TerraxReset(6);
}

void Mtraxx_IgnasioArrive(string qName) // прибыли на Барбадос
{
	pchar.GenQuest.Hunter2Pause = true;
	pchar.quest.mtraxx_ignasio_sinkkitty.over = "yes";
	pchar.quest.Mtraxx_IgnasioTimeOver.over = "yes";
	chrDisableReloadToLocation = true;
	sld = characterFromId("Mtr_KittyCap");
	sld.dialog.currentnode = "kittycap_3";
	LAi_CharacterEnableDialog(sld);
	ChangeCharacterAddressGroup(sld, "Bridgetown_town", "quest", "quest1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void Mtraxx_IgnasioCreateMarko() // ставим Игнасио Марко
{
	float locx, locy, locz;
	sld = GetCharacter(NPC_GenerateCharacter("Ignasio", "Marco", "man", "man", 30, ENGLAND, -1, false, "soldier"));
	FantomMakeCoolSailor(sld, SHIP_POLACRE_QUEST, StringFromKey("Roger_66"), CANNON_TYPE_CANNON_LBS20, 60, 60, 60);
	FantomMakeCoolFighter(sld, 30, 80, 80, "blade_10", "pistol6", "bullet", 150);
	sld.Dialog.Filename = "Quest\Roger.c";
	sld.dialog.currentnode = "ignasio";
	sld.greeting = "captain";
	sld.name = StringFromKey("Roger_67");
	sld.lastname = StringFromKey("Roger_68");
	SetCharacterPerk(sld, "BasicDefense");
	SetCharacterPerk(sld, "Gunman");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "Doctor1");
	SetCharacterPerk(sld, "Doctor2");
	SetCharacterPerk(sld, "WindCatcher");
	SetCharacterPerk(sld, "SailsMan");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "BasicBattleState");
	SetCharacterPerk(sld, "AdvancedBattleState");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	SetCharacterPerk(sld, "LongRangeGrappling");
	SetCharacterPerk(sld, "GrapplingProfessional");
	int n = 60 + MOD_SKILL_ENEMY_RATE*4;
	SetSPECIAL(sld, 7, 5, 6, 6, 5, 10, 6);
	SetSelfSkill(sld, 65, n, 60, 90, 55);
	SetShipSkill(sld, 45, 50, n, n, 90, 70, 90, n, 70);
	sld.Ship.Crew.Morale = n;
	sld.Ship.Crew.Exp.Sailors = n;
	sld.Ship.Crew.Exp.Cannoners = n;
	sld.Ship.Crew.Exp.Soldiers = n;
	UpgradeShipParameter(sld, "MaxCrew");
	int hcrew = GetMaxCrewQuantity(sld);
	SetCrewQuantity(sld, hcrew);
	if (MOD_SKILL_ENEMY_RATE > 2)
	{
		SetCharacterPerk(sld, "MusketsShoot");
		sld.cirassId = Items_FindItemIdx("cirass1");
		sld.multifighter = 1.2 + stf(MOD_SKILL_ENEMY_RATE/10);
		sld.MultiShooter = 1.0 + stf(MOD_SKILL_ENEMY_RATE/10);
	}
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.AlwaysSandbankManeuver = true;
	sld.ShipHideImmortal = 500; // непотопляемый корабль
	Character_SetAbordageEnable(sld, false); // нельзя абордировать
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, "Bridgetown_town", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz)); // прогона 3
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	// Исла де Коче
	int i = FindIsland("IslaDeCoche");
	Islands[i].visible = true;
	Islands[i].reload_enable = true;
}

void Mtraxx_IgnasioAddMarko() // Игнасио - в эскадру
{
	chrDisableReloadToLocation = false;
	LAI_SetPlayerType(pchar);           
	DoQuestReloadToLocation("Bridgetown_tavern", "tables", "stay2", "");
	sld = CharacterFromID("Ignasio");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	SetCharacterRemovable(sld, false);
	sld.CompanionEnemyEnable = false; //всегда друзья
	SetCompanionIndex(pchar, -1, sti(sld.index));
	sld.loyality = MAX_LOYALITY;
	sld.Tasks.CanBoarding = false; // запрет идти на абордаж - дубль
	sld.Tasks.CanChangeShipAfterBoarding = false; // запрет меняться кораблями - дубль
	if (CheckAttribute(pchar, "questTemp.HWIC.Isladecoche"))
	{
		AddQuestRecord("Roger_6", "4");
		DeleteAttribute(pchar, "questTemp.HWIC.Isladecoche");
	}
	else 
	{
		AddQuestRecord("Roger_6", "5");
	}
	pchar.questTemp.Mtraxx = "ignasio_toisland";
	pchar.quest.mtraxx_ignasio_island.win_condition.l1 = "location";
	pchar.quest.mtraxx_ignasio_island.win_condition.l1.location = "IslaDeCoche";
	pchar.quest.mtraxx_ignasio_island.function = "Mtraxx_IgnasioCreateCaravane";
	if (!bImCasual) SetFunctionTimerCondition("Mtraxx_IgnasioCaravaneTimeOver", 0, 0, 15, false); // таймер для шибко грамотных
	else NewGameTip(StringFromKey("Roger_69"));
	
	// Captain Beltrop, 12.09.21, отключаем морских ОЗГов на время
    pchar.GenQuest.SeaHunter2Pause = true;
    SeaHunter_Delete();
}

void Mtraxx_IgnasioCaravaneTimeOver(string qName) // время вышло - взрываем корабль ГГ
{
	if(bImCasual)
	{
		if(CheckAttribute(pchar,"quest.Mtraxx_IgnasioCaravaneTimeOver.over"))
			DeleteAttribute(pchar,"quest.Mtraxx_IgnasioCaravaneTimeOver.over");
		NewGameTip(StringFromKey("Roger_4"));
		SetFunctionTimerCondition("Mtraxx_IgnasioCaravaneTimeOver", 0, 0, 15, false);
		return;
	}
	pchar.quest.mtraxx_ignasio_island.over = "yes";
	if (bSeaActive) DoQuestFunctionDelay("Mtraxx_MarkusGameOver", 2.0);
	else 
	{
		pchar.quest.mtraxx_ignasio_boom.win_condition.l1 = "EnterToSea";
		pchar.quest.mtraxx_ignasio_boom.function = "Mtraxx_IgnasioTimeOverBoom";
	}
	
	DeleteAttribute(pchar, "GenQuest.SeaHunter2Pause"); // вертаем морских ОЗГов
}

void Mtraxx_IgnasioTimeOverBoom(string qName) // время вышло - взрываем корабль ГГ
{
	bQuestDisableMapEnter = true;
	DoQuestFunctionDelay("Mtraxx_MarkusGameOver", 3.0);
}

void Mtraxx_IgnasioCreateCaravane(string qName) // ставим голландцев
{
	pchar.quest.Mtraxx_IgnasioCaravaneTimeOver.over = "yes";
	AddQuestRecord("Roger_6", "6");
	Island_SetReloadEnableGlobal("IslaDeCoche", false);
	bQuestDisableMapEnter = true;//закрыть карту
	Group_FindOrCreateGroup("Mtr_IgnasioSeaGroup");
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+5;
	int iScl = 30 + 3*sti(pchar.rank);
	int Type, iShip[5], iSpace, iCrew, hcrew;
	int n = 3;
	int iClass = sti(RealShips[sti(pchar.ship.type)].Class) + 1;
	
	if (MOD_SKILL_ENEMY_RATE > 8) iClass -= 1;
	if(iClass < 3) iClass = 3;
	if(iClass > 5) iClass = 5;
	
	iShip[1] = GetRandomShipType(GetClassFlag(iClass), FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
	iShip[2] = GetRandomShipType(GetClassFlag(iClass + 1), FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
	iShip[3] = GetRandomShipType(GetClassFlag(iClass + 1), FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
	iShip[4] = GetRandomShipType(GetClassFlag(iClass + 1), FLAG_SHIP_TYPE_WAR, FLAG_SHIP_NATION_ANY);
	
	if (MOD_SKILL_ENEMY_RATE > 6) n = 4;
	for (int i=1; i<=n; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Mtr_IgnasioSeaCap_"+i, "off_hol_"+(5-i), "man", "man", iRank, HOLLAND, -1, true, "quest"));
		FantomMakeCoolSailor(sld, iShip[i], "", -1, iScl+(25-i*5), iScl+(25-i*5), iScl+(25-i*5));
		FantomMakeCoolFighter(sld, iRank, iScl+(25-i*5), iScl+(25-i*5), LinkRandPhrase("blade_15","blade_16","topor_04"), "pistol1", "bullet", iScl*2);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		sld.DontRansackCaptain = true;
		sld.AnalizeShips = true;
		sld.AlwaysEnemy = true;
		sld.AlwaysSandbankManeuver = true;
		sld.Ship.Mode = "war";
		sld.ship.Crew.Morale = 40+MOD_SKILL_ENEMY_RATE*6;
		sld.Ship.Crew.Exp.Sailors = 40+MOD_SKILL_ENEMY_RATE*6;
		sld.Ship.Crew.Exp.Cannoners = 40+MOD_SKILL_ENEMY_RATE*6;
		sld.Ship.Crew.Exp.Soldiers = 40+MOD_SKILL_ENEMY_RATE*6;
		if (MOD_SKILL_ENEMY_RATE > 2) SetCharacterPerk(sld, "MusketsShoot");
		if (i == 1) 
		{
			hcrew = GetMaxCrewQuantity(sld);
			iCrew = sti(0.8*hcrew);
			SetCrewQuantityOverMax(sld, iCrew);
			SetRandGeraldSail(sld, HOLLAND);
			sld.ship.HP = sti(sld.ship.HP)-makeint(sti(sld.ship.HP)/6);
			AddCharacterGoods(sld, GOOD_SILVER, 350);
			iSpace = GetCharacterFreeSpace(sld, GOOD_MAHOGANY);
			Fantom_SetCharacterGoods(sld, GOOD_MAHOGANY, iSpace, 1);
			if (MOD_SKILL_ENEMY_RATE <= 6)
			{
				sld.ship.masts.mast1 = 1;
				sld.ship.masts.mast2 = 1;
			}
		}
		if (i == 2) 
		{
			hcrew = GetMaxCrewQuantity(sld);
			iCrew = sti(0.7*hcrew);
			SetCrewQuantityOverMax(sld, iCrew);
			sld.ship.HP = sti(sld.ship.HP)-makeint(sti(sld.ship.HP)/5);
			AddCharacterGoods(sld, GOOD_SILVER, 275);
			iSpace = GetCharacterFreeSpace(sld, GOOD_MAHOGANY);
			Fantom_SetCharacterGoods(sld, GOOD_MAHOGANY, iSpace, 1);
		}
		if (i == 3) 
		{
			hcrew = GetMaxCrewQuantity(sld);
			iCrew = sti(0.6*hcrew);
			SetCrewQuantityOverMax(sld, iCrew);
			sld.ship.HP = sti(sld.ship.HP)-makeint(sti(sld.ship.HP)/4);
			AddCharacterGoods(sld, GOOD_SILVER, 175);
			iSpace = GetCharacterFreeSpace(sld, GOOD_MAHOGANY);
			Fantom_SetCharacterGoods(sld, GOOD_MAHOGANY, iSpace, 1);
		}
		Group_AddCharacter("Mtr_IgnasioSeaGroup", "Mtr_IgnasioSeaCap_"+i);
	}
	Group_SetGroupCommander("Mtr_IgnasioSeaGroup", "Mtr_IgnasioSeaCap_1");
	Group_SetAddress("Mtr_IgnasioSeaGroup", "IslaDeCoche", "quest_ships", "quest_ship_5");
	Group_SetTaskAttack("Mtr_IgnasioSeaGroup", PLAYER_GROUP);
	Group_LockTask("Mtr_IgnasioSeaGroup");
	pchar.questTemp.Mtraxx.Mahogany = GetSquadronGoods(pchar, GOOD_MAHOGANY);
	pchar.questTemp.Mtraxx.Silver = GetSquadronGoods(pchar, GOOD_SILVER);
	pchar.quest.mtraxx_ignasio_afterbattle.win_condition.l1 = "Group_Death";
	pchar.quest.mtraxx_ignasio_afterbattle.win_condition.l1.group = "Mtr_IgnasioSeaGroup";
	pchar.quest.mtraxx_ignasio_afterbattle.function = "Mtraxx_IgnasioAfterBattle";
	
	DeleteAttribute(pchar, "GenQuest.SeaHunter2Pause"); // вертаем морских ОЗГов
}

void Mtraxx_IgnasioAfterBattle(string qName) // победили голландцев
{
	DoQuestCheckDelay("sea_victory", 1.5);
	pchar.GenQuest.MapClosedNoBattle = true;
	AddQuestRecord("Roger_6", "7");
	Island_SetReloadEnableGlobal("IslaDeCoche", true);
	pchar.quest.mtraxx_ignasio_land.win_condition.l1 = "location";
	pchar.quest.mtraxx_ignasio_land.win_condition.l1.location = "shore78";
	pchar.quest.mtraxx_ignasio_land.function = "Mtraxx_IgnasioOnLand";
	pchar.quest.mtraxx_ignasio_land1.win_condition.l1 = "location";
	pchar.quest.mtraxx_ignasio_land1.win_condition.l1.location = "shore79";
	pchar.quest.mtraxx_ignasio_land1.function = "Mtraxx_IgnasioOnLand";
	AddComplexSeaExpToScill(100, 100, 100, 100, 100, 100, 0);
}

void Mtraxx_IgnasioOnLand(string qName) // высадились на берег для дележа
{
	pchar.GenQuest.Hunter2Pause = true;
	pchar.quest.mtraxx_ignasio_land.over = "yes";
	pchar.quest.mtraxx_ignasio_land1.over = "yes";
	chrDisableReloadToLocation = true;
	sld = CharacterFromID("Ignasio");
	sld.dialog.currentnode = "ignasio_13";
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	for (int i=1; i<=9; i++) // 
	{
		sld = GetCharacter(NPC_GenerateCharacter("Ignasio_pirate_"+i, "citiz_4"+i, "man", "man", 18, PIRATE, 0, true, "soldier"));
		FantomMakeCoolFighter(sld, 25, 50, 50, LinkRandPhrase("blade_07","blade_08","blade_11"), "pistol1", "bullet", 120);
		LAi_CharacterDisableDialog(sld);
		if (i < 5) ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto"+i);
		else ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
}

void Mtraxx_IgnasioEscape() // Игнасио уходит
{
	sld = CharacterFromID("Ignasio");
	RemoveCharacterCompanion(pchar, sld);
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "sea", "none", "", "", "Mtraxx_IgnasioEscape", -1);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	for (int i=1; i<=5; i++) // 
	{
		sld = CharacterFromID("Ignasio_pirate_"+i);
		LAi_SetActorType(sld);
		LAi_ActorRunToLocation(sld, "reload", "sea", "none", "", "", "", 10);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	DeleteAttribute(pchar, "questTemp.Mtraxx.Silver");
	DeleteAttribute(pchar, "questTemp.Mtraxx.Mahogany");
}

void Mtraxx_IgnasioOurEscape() // убираем наших антуражников
{
	sld = CharacterFromID("Ignasio_spy");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "sea", "none", "", "", "", -1);
	for (int i=6; i<=9; i++) // 
	{
		sld = CharacterFromID("Ignasio_pirate_"+i);
		LAi_SetActorType(sld);
		LAi_ActorRunToLocation(sld, "reload", "sea", "none", "", "", "", 10);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	chrDisableReloadToLocation = false;
	pchar.quest.mtraxx_ignasio_spanish.win_condition.l1 = "location";
	pchar.quest.mtraxx_ignasio_spanish.win_condition.l1.location = "IslaDeCoche";
	pchar.quest.mtraxx_ignasio_spanish.function = "Mtraxx_IgnasioPrepareSpanish";
	AddQuestRecord("Roger_6", "8");
}

void Mtraxx_IgnasioPrepareSpanish(string qName) // ставим убегающего Игнасио Марко
{
	Island_SetReloadEnableGlobal("IslaDeCoche", false); // правки релиза
	DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
	Group_FindOrCreateGroup("IgnasioSeaGroup");
	sld = CharacterFromID("Ignasio");
	DeleteAttribute(sld, "ship.sails");
    DeleteAttribute(sld, "ship.blots");
    DeleteAttribute(sld, "ship.masts");
	sld.Abordage.Enable = false;
	sld.AlwaysFriend = true;
	sld.ShipEnemyDisable = true; 
	LAi_SetImmortal(sld, true); // сплошная защита от дурака
	sld.DontDeskTalk = true;
	sld.nation = SPAIN;
	Group_AddCharacter("IgnasioSeaGroup", "Ignasio");
	Group_SetGroupCommander("IgnasioSeaGroup", "Ignasio");
	Group_SetAddress("IgnasioSeaGroup", "IslaDeCoche", "quest_ships", "quest_ship_5");
	Group_SetTaskRunAway("IgnasioSeaGroup", PLAYER_GROUP);
	Group_LockTask("IgnasioSeaGroup");
	DoQuestFunctionDelay("Mtraxx_IgnasioCreateSpanish", 2.0);
}

void Mtraxx_IgnasioCreateSpanish(string qName) // 
{
	int iShip[4], iRank, iScl;
	
	int iClass = sti(RealShips[sti(pchar.ship.type)].Class) + 1;
	
	if (MOD_SKILL_ENEMY_RATE > 8) iClass -= 1;
	if(iClass < 3) iClass = 3;
	if(iClass > 5) iClass = 5;
	
	iShip[1] = SHIP_GALEON_L;
	iShip[2] = GetRandomShipType(GetClassFlag(iClass), FLAG_SHIP_TYPE_WAR, FLAG_SHIP_NATION_ANY);
	iShip[3] = GetRandomShipType(GetClassFlag(iClass + 1), FLAG_SHIP_TYPE_WAR, FLAG_SHIP_NATION_ANY);
	Group_FindOrCreateGroup("LosadaSeaGroup");
	for (int i=1; i<=3; i++)
	{
		switch (i)
		{
			case 1:
				iRank = 45;
				iScl = 100;
			break;
			
			case 2:
				iRank = 25;
				iScl = 50;
			break;
			
			case 3:
				iRank = 25;
				iScl = 50;
			break;
		}
		sld = GetCharacter(NPC_GenerateCharacter("Losada_Seacap_"+i, "off_spa_"+(7-i), "man", "man", iRank, SPAIN, -1, true, "quest"));
		FantomMakeCoolSailor(sld, iShip[i], "", -1, iScl, iScl, iScl);
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, LinkRandPhrase("blade_18","blade_19","blade_20"), "pistol5", "bullet", 250);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		sld.cirassId = Items_FindItemIdx("cirass4");
		sld.DontRansackCaptain = true;
		sld.AnalizeShips = true;
		sld.AlwaysEnemy = true;
		sld.AlwaysSandbankManeuver = true;
		sld.Ship.Mode = "war";
		sld.ship.Crew.Morale = 50;
		sld.Ship.Crew.Exp.Sailors = 50;
		sld.Ship.Crew.Exp.Cannoners = 50;
		sld.Ship.Crew.Exp.Soldiers = 50;
		SetCharacterGoods(sld,GOOD_GRAPES,0);
		//SetCharacterPerk(sld, "MusketsShoot");
		if(CheckAttribute(sld,"perks.list.MusketsShoot"))
				DeleteAttribute(sld,"perks.list.MusketsShoot");
		if (i == 1) 
		{
			sld.ship.Crew.Morale = 100;
			sld.Ship.Crew.Exp.Sailors = 100;
			sld.Ship.Crew.Exp.Cannoners = 100;
			sld.Ship.Crew.Exp.Soldiers = 100;
			SetShipSkill(sld, 60, 50, 100, 100, 100, 100, 100, 100, 70);
			SetCharacterPerk(sld, "LongRangeShoot");
			SetCharacterPerk(sld, "FastReload");
			SetCharacterPerk(sld, "CannonProfessional");
			SetCharacterPerk(sld, "ShipDefenseProfessional");
			SetCharacterPerk(sld, "WindCatcher");
			SetCharacterPerk(sld, "SailsMan");
			SetCharacterPerk(sld, "SailingProfessional");
			
			SetRandGeraldSail(sld, SPAIN);
			int hcrew = GetMaxCrewQuantity(sld);
			//SetCrewQuantityOverMax(sld, 1.2*hcrew);
			sld.name = StringFromKey("Roger_70");
			sld.lastname = StringFromKey("Roger_71");
			//sld.ship.name = StringFromKey("Roger_72");
			NullCharacterGoods(sld);
			UpgradeShipParameter(sld, "SpeedRate");
			UpgradeShipParameter(sld, "HP");
			DeleteAttribute(sld, "ship.hulls");
			AddCharacterGoods(sld, GOOD_BALLS, 1500);
			//AddCharacterGoods(sld, GOOD_GRAPES, 1000);
			AddCharacterGoods(sld, GOOD_KNIPPELS, 700);
			AddCharacterGoods(sld, GOOD_BOMBS, 200);
			AddCharacterGoods(sld, GOOD_POWDER, 3000);
			AddCharacterGoods(sld, GOOD_WEAPON, 750);
			AddCharacterGoods(sld, GOOD_FOOD, 500);
			AddCharacterGoods(sld, GOOD_MEDICAMENT, 150);
			AddCharacterGoods(sld, GOOD_RUM, 50);
		}
		Group_AddCharacter("LosadaSeaGroup", "Losada_Seacap_"+i);
	}
	Group_SetGroupCommander("LosadaSeaGroup", "Losada_Seacap_1");
	Group_SetAddress("LosadaSeaGroup", "IslaDeCoche", "", "");
	Group_SetTaskAttack("LosadaSeaGroup", PLAYER_GROUP);
	Group_LockTask("LosadaSeaGroup");
	DoQuestFunctionDelay("Mtraxx_IgnasioSetSpanish", 2.0);
	pchar.questTemp.Mtraxx.LosadaEscape = "true";
	// для бравых
	pchar.quest.mtraxx_ignasio_open.win_condition.l1 = "NPC_Death";
	pchar.quest.mtraxx_ignasio_open.win_condition.l1.character = "Losada_Seacap_1";
	pchar.quest.mtraxx_ignasio_open.function = "Mtraxx_IgnasioExit";
	pchar.quest.mtraxx_ignasio_brave.win_condition.l1 = "Group_Death";
	pchar.quest.mtraxx_ignasio_brave.win_condition.l1.group = "LosadaSeaGroup";
	pchar.quest.mtraxx_ignasio_brave.function = "Mtraxx_IgnasioBrave";
}

void Mtraxx_IgnasioSetSpanish(string qName) // 
{
	Sea_LoginGroupCurrentSea("LosadaSeaGroup");
	AddQuestRecord("Roger_6", "9");
}

void Mtraxx_IgnasioExit(string qName) // 
{
	ChangeCharacterHunterScore(PChar, "spahunter", 15);
	DoQuestFunctionDelay("Mtraxx_IgnasioOpenMap", 2.0);
	AddQuestRecord("Roger_6", "12");
	AddComplexSeaExpToScill(100, 100, 100, 100, 100, 100, 0);
}

void Mtraxx_IgnasioBrave(string qName) // 
{
	DoQuestCheckDelay("sea_victory", 1.5);
	Group_DeleteGroup("LosadaSeaGroup");
	pchar.quest.mtraxx_ignasio_map.over = "yes";
	DeleteAttribute(pchar, "questTemp.Mtraxx.LosadaEscape");
	bQuestDisableMapEnter = false;
	AddQuestRecord("Roger_6", "10");
	pchar.quest.mtraxx_ignasio_clear.win_condition.l1 = "MapEnter";
	pchar.quest.mtraxx_ignasio_clear.function = "Mtraxx_IgnasioClearSeaGroup";
	QuestSetCurrentNode("Terrax", "mtraxx_48");
	ChangeCharacterHunterScore(PChar, "spahunter", 10);
	pchar.questTemp.Mtraxx.LosadaSink = "true";
	AddComplexSeaExpToScill(150, 150, 150, 150, 150, 150, 0);
}

void Mtraxx_IgnasioClearSeaGroup(string qName) // 
{
	Group_DelCharacter("IgnasioSeaGroup", "Ignasio");
	Group_DeleteGroup("IgnasioSeaGroup");
	Island_SetReloadEnableGlobal("IslaDeCoche", true); // правки релиза
}

void Mtraxx_IgnasioClearSeaGroups(string qName) // 
{
	Group_DelCharacter("IgnasioSeaGroup", "Ignasio");
	Group_DeleteGroup("IgnasioSeaGroup");
	Island_SetReloadEnableGlobal("IslaDeCoche", true); // правки релиза
	pchar.quest.mtraxx_ignasio_brave.over = "yes";
	pchar.quest.mtraxx_ignasio_open.over = "yes";
	Group_DeleteGroup("LosadaSeaGroup");
	AddQuestRecord("Roger_6", "11");
	QuestSetCurrentNode("Terrax", "mtraxx_48");
	AddCharacterExpToSkill(pchar, "Fortune", 300);
	AddCharacterExpToSkill(pchar, "Sneak", 300);
}

void Mtraxx_IgnasioOpenMap() // 
{
	bQuestDisableMapEnter = false;
	DeleteAttribute(pchar, "questTemp.Mtraxx.LosadaEscape");
	pchar.quest.mtraxx_ignasio_map.win_condition.l1 = "MapEnter";
	pchar.quest.mtraxx_ignasio_map.function = "Mtraxx_IgnasioClearSeaGroups";
}

// эпизод 7-й. Сокровища свободного ярла.
void Mtraxx_WolfreekReadLogbook() // чтение судового журнала
{
	if (pchar.location == Get_My_Cabin())
	{
		if (CheckAttribute(pchar, "questTemp.Mtraxx.Logbook.CanRead"))
		{
			WaitDate("", 0, 0, 0, 3, 30);
			DeleteAttribute(pchar, "questTemp.Mtraxx.Logbook.CanRead");
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Logbook.Page1"))
			{
				AddQuestRecord("Roger_7", "2");
				AddQuestRecordInfo("Wolfreek_Journal", "1");
				DeleteAttribute(pchar, "questTemp.Mtraxx.Logbook.Page1");
				pchar.quest.mtraxx_wolfreek_bay.win_condition.l1 = "location";
				pchar.quest.mtraxx_wolfreek_bay.win_condition.l1.location = "PortoBello";
				pchar.quest.mtraxx_wolfreek_bay.function = "Mtraxx_WolfreekMoskitos";				
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Logbook.Page2"))
			{
				AddQuestRecord("Roger_7", "8");
				AddQuestRecordInfo("Wolfreek_Journal", "2");
				DeleteAttribute(pchar, "questTemp.Mtraxx.Logbook.Page2");
				pchar.questTemp.Mtraxx.Jeweller = "true";		
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Logbook.Page3"))
			{
				DeleteAttribute(pchar, "questTemp.Mtraxx.Logbook.Page3");
				if (CheckAttribute(pchar, "questTemp.HWIC.Jino"))
				{
					pchar.questTemp.Mtraxx.Gord = "true";
					AddQuestRecord("Roger_7", "13");
				}
				else
				{
					QuestSetCurrentNode("Terrax", "mtraxx_59");
					AddQuestRecord("Roger_7", "14");
				}
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Logbook.Page4"))
			{
				AddQuestRecordInfo("Wolfreek_Journal", "3");
				DeleteAttribute(pchar, "questTemp.Mtraxx.Logbook.Page4");
				int i = FindIsland("IslaMona");
				Islands[i].visible = true;
				Islands[i].reload_enable = true;
				pchar.quest.mtraxx_wolfreek_islamona.win_condition.l1 = "location";
				pchar.quest.mtraxx_wolfreek_islamona.win_condition.l1.location = "Shore75";
				pchar.quest.mtraxx_wolfreek_islamona.function = "Mtraxx_WolfreekIslaMona";
				pchar.quest.mtraxx_wolfreek_islamona1.win_condition.l1 = "location";
				pchar.quest.mtraxx_wolfreek_islamona1.win_condition.l1.location = "Shore77";
				pchar.quest.mtraxx_wolfreek_islamona1.function = "Mtraxx_WolfreekIslaMona";
				// характеристики топора викинга
				sld = ItemsFromID("topor_06");
				sld.Balance = 2.0;
				sld.Weight = 3.5;
				sld.Attack = 88.0;
				SetBladeWeightAttack(sld);
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Ignasio.Journal"))
			{
				AddQuestRecord("Roger_8", "11");
				AddQuestRecordInfo("Ignasio_Journal", "1");
				AddQuestUserData("Ignasio_Journal", "sDay", sti(pchar.questTemp.Mtraxx.Corrida.Day));
				AddQuestUserData("Ignasio_Journal", "sMonth", XI_ConvertString("target_month_" + sti(pchar.questTemp.Mtraxx.Corrida.Month)));
				AddQuestUserData("Ignasio_Journal", "sYear", sti(pchar.questTemp.Mtraxx.Corrida.Year));
				DeleteAttribute(pchar, "questTemp.Mtraxx.Ignasio.Journal");
				pchar.questTemp.Mtraxx.Ignasio.Signal = "true";
				pchar.questTemp.Mtraxx.Ignasio.Ship = "true";
				pchar.questTemp.Mtraxx.Ignasio.Dove = "true";
			}
		}
		else PlaySound("interface\knock.wav");
	}
	else 
	{
		PlaySound("interface\knock.wav");
		log_info(StringFromKey("Roger_73"));
	}
}

void Mtraxx_WolfreekMoskitos(string qName) // устанавливаем прерывания на пещеры
{
	pchar.quest.mtraxx_wolfreek_cave.win_condition.l1 = "location";
	pchar.quest.mtraxx_wolfreek_cave.win_condition.l1.location = "PortoBello_Cave"; // грот
	pchar.quest.mtraxx_wolfreek_cave.function = "Mtraxx_WolfreekGrot";
	pchar.quest.mtraxx_wolfreek_grot.win_condition.l1 = "location";
	pchar.quest.mtraxx_wolfreek_grot.win_condition.l1.location = "Panama_Cave";
	pchar.quest.mtraxx_wolfreek_grot.function = "Mtraxx_WolfreekCave";
	// заполним сундук в пещере Панамы
	pchar.GenQuestBox.Panama_Cave = true;
	pchar.GenQuestBox.Panama_Cave.box1.money = 5000;
	pchar.GenQuestBox.Panama_Cave.box1.items.purse2 = 1;
	pchar.GenQuestBox.Panama_Cave.box1.items.jewelry6 = 22;
	pchar.GenQuestBox.Panama_Cave.box1.items.jewelry10 = 5;
	pchar.GenQuestBox.Panama_Cave.box1.items.jewelry12 = 8;
	pchar.GenQuestBox.Panama_Cave.box1.items.jewelry21 = 6;
	pchar.GenQuestBox.Panama_Cave.box1.items.jewelry18 = 4;
}

void Mtraxx_WolfreekGrot(string qName) // в гроте - злые индеи, 6 штук
{
	chrDisableReloadToLocation = true;
	ref rItm = ItemsFromID("fire");
	rItm.shown = true;
	rItm.startLocation = "PortoBello_Cave";
	rItm.startLocator = "fire";
	CreateFireParticles("goto", "fire"); //костер
	//индеи
	for (int i=1; i<=6; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Mtr_indian_grot_"+i, "canib_"+(i+1), "man", "man", 25, PIRATE, -1, true, "native"));
		FantomMakeCoolFighter(sld, 25, 70, 70, LinkRandPhrase("blade_01","blade_02","topor_02"), "", "", 150);
		sld.name = GetIndianName(MAN);
		sld.lastname = "";
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		if (i == 1)
		{
			sld.Dialog.Filename = "Quest\Roger.c";
			sld.dialog.currentnode = "grot_canib";
			GiveItem2Character(sld, "topor_01");
			EquipCharacterbyItem(sld, "topor_01");
			GiveItem2Character(sld, "pistol3");
			EquipCharacterbyItem(sld, "pistol3");
			TakeNItems(sld, "grapeshot", 10);
			LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "grapeshot");
			if (MOD_SKILL_ENEMY_RATE > 2)
			{
				sld.MultiFighter = 1.5;
				sld.MultiShooter = 2.0;
				sld.viper = true;
			}
		}
		if (i < 5) ChangeCharacterAddressGroup(sld, "PortoBello_Cave", "goto", "ass"+i);
		else ChangeCharacterAddressGroup(sld, "PortoBello_Cave", "monsters", "monster"+(i-3));
		LAi_SetActorType(sld);
		if (i == 1) LAi_ActorDialogDelay(sld, pchar, "", 3.0);
		else LAi_ActorAnimation(sld, "Bead", "", -1);
	}
}

void Mtraxx_WolfreekGrotFight(string qName) // битва с карибами
{
	LAi_group_Delete("EnemyFight");
	for (int i=1; i<=6; i++)
	{
		sld = CharacterFromID("Mtr_indian_grot_"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "Mtraxx_WolfreekGrotAfterFight");
	LAi_SetFightMode(pchar, true);
}

void Mtraxx_WolfreekGrotOpenBox() // открыли сундук в гроте
{
	chrDisableReloadToLocation = false;
	DeleteAttribute(pchar, "questTemp.Mtraxx.Grotbox");
	pchar.questTemp.Mtraxx.Grotcheck = "true";
	AddQuestRecord("Roger_7", "4");
	if (CheckAttribute(pchar, "questTemp.Mtraxx.Cavecheck")) Mtraxx_WolfreekReadLogbookSecond();
	AddCharacterExpToSkill(pchar, "Fortune", 20);
}

void Mtraxx_WolfreekCave(string qName) // 
{
	chrDisableReloadToLocation = true;
	pchar.questTemp.Mtraxx.Cavebox = "true";
}

void Mtraxx_WolfreekCaveOpenBox() // открыли сундук в шахте
{
	chrDisableReloadToLocation = false;
	DeleteAttribute(pchar, "questTemp.Mtraxx.Cavebox");
	pchar.questTemp.Mtraxx.Cavecheck = "true";
	AddQuestRecord("Roger_7", "5");
	if (CheckAttribute(pchar, "questTemp.Mtraxx.Grotcheck")) Mtraxx_WolfreekReadLogbookSecond();
	pchar.quest.mtraxx_wolfreek_caveexit.win_condition.l1 = "location";
	pchar.quest.mtraxx_wolfreek_caveexit.win_condition.l1.location = "Panama_CaveEntrance";
	pchar.quest.mtraxx_wolfreek_caveexit.function = "Mtraxx_WolfreekCaveEntrance";
	AddCharacterExpToSkill(pchar, "Fortune", 50);
}

void Mtraxx_WolfreekCaveEntrance(string qName) // у выхода из шахты
{
	chrDisableReloadToLocation = true;
	// босяки
	for (int i=5; i<=9; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Mtr_bandit_cave_"+i, "citiz_4"+i, "man", "man", 20, PIRATE, -1, true, "quest"));
		FantomMakeCoolFighter(sld, 20, 60, 60, LinkRandPhrase("blade_07","blade_08","blade_11"), "pistol1", "bullet", 120);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		if (i == 5)
		{
			sld.Dialog.Filename = "Quest\Roger.c";
			sld.dialog.currentnode = "cave_bandit";
		}
		else LAi_CharacterDisableDialog(sld);
		ChangeCharacterAddressGroup(sld, "Panama_CaveEntrance", "reload", "reload2_back");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
}

void Mtraxx_WolfreekCaveFight(string qName) // драка с босяками
{
	LAi_group_Delete("EnemyFight");
	for (int i=5; i<=9; i++)
	{
		sld = CharacterFromID("Mtr_bandit_cave_"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "Mtraxx_WolfreekCaveAfterFight");
	LAi_SetFightMode(pchar, true);
}

void Mtraxx_WolfreekReadLogbookSecond() // снова идем читать журнал
{
	AddQuestRecord("Roger_7", "7");
	DeleteAttribute(pchar, "questTemp.Mtraxx.Grotcheck");
	DeleteAttribute(pchar, "questTemp.Mtraxx.Cavecheck");
	pchar.questTemp.Mtraxx.Logbook.CanRead = "true";
	pchar.questTemp.Mtraxx.Logbook.Page2 = "true";
	bQuestDisableMapEnter = true;//закрыть карту
	pchar.GenQuest.MapClosedNoBattle = true;
	ref rItm = ItemsFromID("fire");
	rItm.shown = false;
	LocatorReloadEnterDisable("Tortuga_town", "houseS3", true); // Addon 2016-1 Jason пиратская линейка 1
}

void Mtraxx_WolfreekJewellerHouse() // на Тортуге
{
	DeleteAttribute(pchar, "questTemp.Mtraxx.Jeweller");
	AddQuestRecord("Roger_7", "9");
	pchar.quest.mtraxx_wolfreek_house.win_condition.l1 = "locator";
	pchar.quest.mtraxx_wolfreek_house.win_condition.l1.location = "Tortuga_town";
	pchar.quest.mtraxx_wolfreek_house.win_condition.l1.locator_group = "reload";
	pchar.quest.mtraxx_wolfreek_house.win_condition.l1.locator = "houseS3";
	pchar.quest.mtraxx_wolfreek_house.win_condition.l2 = "Day";
	pchar.quest.mtraxx_wolfreek_house.function = "Mtraxx_WolfreekJewellerKnock";
	LocatorReloadEnterDisable("Tortuga_town", "houseS3", true);
}

void Mtraxx_WolfreekJewellerKnock(string qName) // стучимся в дверь
{
	LocatorReloadEnterDisable("Tortuga_town", "houseS3", true);
	LAi_SetActorType(pchar);
	PlaySound("interface\knock.wav");
	DoQuestFunctionDelay("Mtraxx_WolfreekJewellerKnock1", 4.0);
}

void Mtraxx_WolfreekJewellerKnock1(string qName) // тук-тук
{
	PlaySound("interface\knock.wav");
	DoQuestFunctionDelay("Mtraxx_WolfreekJewellerKnock2", 4.0);
}

void Mtraxx_WolfreekJewellerKnock2(string qName) // бах-бах
{
	PlaySound("interface\Door_Kick.wav");
	DoQuestFunctionDelay("Mtraxx_WolfreekJewellerClosed", 5.0);
}

void Mtraxx_WolfreekJewellerClosed(string qName) // наблюдаем за домом
{
	LAi_SetPlayerType(pchar);
	AddQuestRecord("Roger_7", "10");
	pchar.GenQuest.CannotWait = true;
	chrDisableReloadToLocation = true;
	pchar.quest.mtraxx_wolfreek_wait.win_condition.l1 = "locator";
	pchar.quest.mtraxx_wolfreek_wait.win_condition.l1.location = "Tortuga_town";
	pchar.quest.mtraxx_wolfreek_wait.win_condition.l1.locator_group = "reload";
	pchar.quest.mtraxx_wolfreek_wait.win_condition.l1.locator = "basement1";
	pchar.quest.mtraxx_wolfreek_wait.function = "Mtraxx_WolfreekJewellerWait";
	LocatorReloadEnterDisable("Tortuga_town", "basement1", true); // правки прогона 3
}

void Mtraxx_WolfreekJewellerWait(string qName) // ждем
{
	LAi_SetActorType(pchar);
	LAi_ActorTurnToLocator(pchar, "reload", "houseS3");
	DoQuestCheckDelay("Mtraxx_WolfreekJewellerWait", 10.0);
}

void Mtraxx_WolfreekSetPelly(string qName) // явился Тесак
{
	LAi_SetActorType(pchar);
	LAi_ActorTurnToLocator(pchar, "reload", "houseS3");
	sld = CharacterFromID("Pelly");
	ChangeCharacterAddressGroup(sld, "Tortuga_town", "reload", "reload10_back");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "houseS3", "none", "", "", "Mtraxx_WolfreekPelly", -1);
}

void Mtraxx_WolfreekPelly(string qName) // идем к Тесаку за разговором
{
	InterfaceStates.Buttons.Save.enable = true;
	DeleteAttribute(pchar, "GenQuest.FrameLockEsc");
	sld = CharacterFromID("Pelly");
	sld.dialog.currentnode = "Pelly_23";
	sld.greeting = "Pelly_01";
	ChangeCharacterAddressGroup(sld, "Tortuga_town", "reload", "houseS3");
	LAi_SetActorType(pchar);
	LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
	LAi_ActorTurnToCharacter(sld, pchar);
	SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
}

void Mtraxx_WolfreekPellyTalkGems (string qName)
{
	Mtraxx_WolfreekCreateGaspar();
	LAi_SetActorTypeNoGroup(pchar);
	ref sld = CharacterFromID("Pelly");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "houseS3", "none", "", "", "Mtraxx_WolfreekPellyWaitGems", -1);
}

void Mtraxx_WolfreekCreateGaspar()
{
	sld = GetCharacter(NPC_GenerateCharacter("GasparGold", "banker_6", "man", "man", 10, PIRATE, -1, true, "citizen"));
	sld.Merchant.type = "GasparGold";
	sld.dialog.filename = "Quest\Roger.c";
	sld.dialog.currentnode = "GasparGold_meeting";
	sld.name = StringFromKey("Roger_74");
	sld.lastname = StringFromKey("Roger_75");
	sld.money = 5000000;
	AddItems(sld, "gold_dublon", 1000);
	ChangeCharacterAddressGroup(sld, "Tortuga_houseS3", "barmen", "stay");
	LAi_SetOwnerType(sld);
}

void Mtraxx_WolfreekPellyGemsToPrince (string qName)
{
	DeleteAttribute(loadedLocation,"reload.l15.disable");
	LAi_SetPlayerType(pchar);
	sld = CharacterFromID("Pelly");
	sld.dialog.currentnode = "Pelly_28z";
	ChangeCharacterAddressGroup(sld, "Tortuga_town", "reload", "houseS3");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void Mtraxx_WolfreekReadLogbookThird() // снова читать журнал - третий раз
{
	DeleteAttribute(pchar, "GenQuest.CannotWait");
	LAi_SetPlayerType(pchar);
	chrDisableReloadToLocation = false;
	sld = CharacterFromID("Pelly");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload4_back", "none", "", "", "", 20);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	AddQuestRecord("Roger_7", "12");
	pchar.questTemp.Mtraxx.Logbook.CanRead = "true";
	pchar.questTemp.Mtraxx.Logbook.Page3 = "true";
	bQuestDisableMapEnter = true;//закрыть карту
	pchar.GenQuest.MapClosedNoBattle = true;
	AddCharacterExpToSkill(pchar, "Sneak", 100);
	LocatorReloadEnterDisable("Tortuga_town", "basement1", false); // правки прогона 3
	LAi_LocationFightDisable(&Locations[FindLocation("Tortuga_town")], false); // патч 17/1
}

void Mtraxx_WolfreekReadLogbookFourth() // читаем в четвертый раз
{
	AddQuestRecord("Roger_7", "15");
	DeleteAttribute(pchar, "questTemp.Mtraxx.Gord");
	pchar.questTemp.Mtraxx.Logbook.CanRead = "true";
	pchar.questTemp.Mtraxx.Logbook.Page4 = "true";
	bQuestDisableMapEnter = true;//закрыть карту
	pchar.GenQuest.MapClosedNoBattle = true;
}

void Mtraxx_WolfreekTimer(string qName) // 
{
	QuestSetCurrentNode("Terrax", "mtraxx_63");
}

void Mtraxx_WolfreekIslaMona(string qName) // нашли Исла Мону
{
	pchar.quest.mtraxx_wolfreek_islamona.over = "yes";
	pchar.quest.mtraxx_wolfreek_islamona1.over = "yes";
	bQuestDisableMapEnter = true;//закрыть карту
	pchar.GenQuest.MapClosedNoBattle = true;
	AddQuestRecord("Roger_7", "16");
	pchar.quest.mtraxx_wolfreek_jungle.win_condition.l1 = "location";
	pchar.quest.mtraxx_wolfreek_jungle.win_condition.l1.location = "IslaMona_jungle_01";
	pchar.quest.mtraxx_wolfreek_jungle.function = "Mtraxx_WolfreekIslaMonaPirates";
	AddCharacterExpToSkill(pchar, "Sailing", 200);
	AddCharacterExpToSkill(pchar, "Leadership", 200);
	AddCharacterExpToSkill(pchar, "Fortune", 200);
}

void Mtraxx_WolfreekIslaMonaPirates(string qName) // пиратусы в кустах
{
	chrDisableReloadToLocation = true;
	for (int i=1; i<=9; i++) // 
	{
		if (i > 6)
		{
			sld = GetCharacter(NPC_GenerateCharacter("Islamona_pirate_"+i, "mush_ctz_"+i, "man", "mushketer", 20, PIRATE, -1, false, "quest"));
			if (i == 2) 
			{
				FantomMakeCoolFighter(sld, 20, 60, 60, "", "mushket3", "grapeshot", 120);
				LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "grapeshot");
			}
			else 
			{
				FantomMakeCoolFighter(sld, 20, 60, 60, "", "mushket2", "cartridge", 120);
				LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "cartridge");
			}
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "GunProfessional");
			if (MOD_SKILL_ENEMY_RATE > 2) sld.cirassId = Items_FindItemIdx("cirass1");
		}
		else
		{
			sld = GetCharacter(NPC_GenerateCharacter("Islamona_pirate_"+i, "citiz_4"+i, "man", "man", 18, PIRATE, -1, true, "quest"));
			FantomMakeCoolFighter(sld, 18, 50, 50, LinkRandPhrase("blade_07","blade_08","blade_11"), "pistol1", "bullet", 100);
			if (MOD_SKILL_ENEMY_RATE > 4) sld.cirassId = Items_FindItemIdx("cirass2");
		}
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
	}
	DoQuestFunctionDelay("Mtraxx_WolfreekIslaMonaShot", 3.0);
}

void Mtraxx_WolfreekIslaMonaShot(string qName) // мушкетеры стреляют
{
	LAi_group_Delete("EnemyFight");
	for (int i=7; i<=9; i++) // 
	{
		sld = CharacterFromID("Islamona_pirate_"+i);
		ChangeCharacterAddressGroup(sld, "IslaMona_jungle_01", "goto", "ass"+(i-6));
		sld.MusketerDistance = 0;
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "Mtraxx_WolfreekIslaMonaAfterFight");
	DoQuestFunctionDelay("Mtraxx_WolfreekIslaMonaAttack", 3.0);
}

void Mtraxx_WolfreekIslaMonaAttack(string qName) // пиратусы выскочили
{
	PlaySound("interface\abordage_wining.wav");
	for (int i=1; i<=6; i++) // 
	{
		sld = CharacterFromID("Islamona_pirate_"+i);
		if (i < 4) ChangeCharacterAddressGroup(sld, "IslaMona_jungle_01", "goto", "goto5");
		else ChangeCharacterAddressGroup(sld, "IslaMona_jungle_01", "goto", "goto7");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
}

void Mtraxx_WolfreekCpy(string qName) // собираем штурмовую роту
{
	Log_Info(StringFromKey("Roger_76"));
	PlaySound("interface\notebook.wav");
	pchar.quest.mtraxx_wolfreek_march.win_condition.l1 = "location";
	pchar.quest.mtraxx_wolfreek_march.win_condition.l1.location = "Shore75";
	pchar.quest.mtraxx_wolfreek_march.function = "Mtraxx_WolfreekMarch";
	pchar.quest.mtraxx_wolfreek_march1.win_condition.l1 = "location";
	pchar.quest.mtraxx_wolfreek_march1.win_condition.l1.location = "Shore77";
	pchar.quest.mtraxx_wolfreek_march1.function = "Mtraxx_WolfreekMarch";
	pchar.questTemp.Mtraxx.WolfreekCpy = "true";
}

void Mtraxx_WolfreekMarch(string qName) // собираем штурмовую роту
{
	pchar.quest.mtraxx_wolfreek_march.over = "yes";
	pchar.quest.mtraxx_wolfreek_march1.over = "yes";
	for (int i=1; i<=7; i++) 
	{
		if (i == 5)
		{
			sld = GetCharacter(NPC_GenerateCharacter("Islamona_cpy_"+i, "mush_ctz_"+i, "man", "mushketer", 25, PIRATE, -1, false, "quest"));
			FantomMakeCoolFighter(sld, 25, 65, 65, "", "mushket3", "grapeshot", 150);
			LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "grapeshot");
		}
		else
		{
			sld = GetCharacter(NPC_GenerateCharacter("Islamona_cpy_"+i, "citiz_4"+i, "man", "man", 20, PIRATE, -1, true, "quest"));
			FantomMakeCoolFighter(sld, 20, 55, 55, LinkRandPhrase("blade_07","blade_08","blade_11"), "pistol1", "bullet", 120);
		}
		LAi_CharacterDisableDialog(sld);
		ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto1");
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		LAi_ActorFollowEverywhere(sld, "", -1);
	}
	pchar.quest.mtraxx_wolfreek_cpy1.win_condition.l1 = "location";
	pchar.quest.mtraxx_wolfreek_cpy1.win_condition.l1.location = "IslaMona_town";
	pchar.quest.mtraxx_wolfreek_cpy1.function = "Mtraxx_WolfreekCpyInFort";
}

void Mtraxx_WolfreekCpyInFort(string qName) // 
{
	chrDisableReloadToLocation = true;
	for (int i=1; i<=7; i++) 
	{
		sld = CharacterFromID("Islamona_cpy_"+i);
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, "IslaMona_town", "reload", "reload1");
		LAi_ActorFollowEverywhere(sld, "", -1);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
}
}

void Mtraxx_WolfreekCannon(string qName) // в локации форта перед пушкой
{
	if (CheckAttribute(pchar, "questTemp.Mtraxx.WolfreekCpy"))
	{
		DeleteAttribute(pchar, "questTemp.Mtraxx.WolfreekCpy");
		sld = CharacterFromID("Islamona_carpenter");
		LAi_ActorDialogNow(sld, pchar, "", -1);
	}
	else
	{
		CreateLocationParticles("Bombard", "quest", "mortair_battle", 1.0, 90, 90, "cannon_fire_2");
		CreateLocationParticles("blast_dirt", "quest", "mortair_battle", 1.0, 90, 90, "");
		CreateLocationParticles("blast_dirt", "quest", "mortair_battle", 1.0, 90, 90, "");
		DoQuestFunctionDelay("Mtraxx_WolfreekGameover", 0.5);
	}
}

void Mtraxx_WolfreekGameover(string qName) // сунулся без роты
{
	for (int i=1; i<=3; i++)
	{
		int idx = GetOfficersIndex(pchar, i);
		if (idx < 1) continue;
		sld = &Characters[idx];
		LAi_KillImmortalCharacter(sld);
	}
	LAi_KillImmortalCharacter(pchar);
}

void Mtraxx_WolfreekInFort(string qName) // переговоры с Родгаром окончены
{
	sld = CharacterFromID("Islamona_carpenter");
	sld.dialog.currentnode = "carpenter_17";
	sld.greeting = "Rodgar_02";
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	for (int i=1; i<=2; i++) // 
	{
		sld = CharacterFromID("Islamona_fort_pirate_"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	
	IslaMona_SetCannonPeace();
	
	DoQuestReloadToLocation("IslaMona_town", "quest", "detector", "Mtraxx_WolfreekInFort");
	AddCharacterExpToSkill(pchar, "Leadership", 100);
	for (i=1; i<=7; i++) 
	{
		sld = CharacterFromID("Islamona_cpy_"+i);
		LAi_SetWarriorType(sld);
		LAi_CharacterDisableDialog(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
}

void Mtraxx_WolfreekFindTreasure() // нашли клад Вульфрика
{
	DeleteAttribute(pchar, "questTemp.Mtraxx.WolfreekBox");
	pchar.questTemp.Mtraxx.WolfreekGord = "true";
	AddQuestRecord("Roger_7", "19");
	AddCharacterExpToSkill(pchar, "Fortune", 400);
}

void Mtraxx_WolfreekComplete() // завершаем квест
{
	sld = CharacterFromID("Islamona_carpenter");
	sld.dialog.currentnode = "carpenter_17";
	DeleteAttribute(pchar, "questTemp.Mtraxx.WolfreekGord");
	AddQuestRecord("Roger_7", "20");
	if (GetSquadronGoods(pchar, GOOD_FOOD) >= 100) RemoveCharacterGoods(pchar, GOOD_FOOD, 50);
	if (GetSquadronGoods(pchar, GOOD_RUM) >= 20) RemoveCharacterGoods(pchar, GOOD_RUM, 20);
	if (GetSquadronGoods(pchar, GOOD_MEDICAMENT) >= 45) RemoveCharacterGoods(pchar, GOOD_MEDICAMENT, 15);
	bQuestDisableMapEnter = false;//открыть карту
	DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
	QuestSetCurrentNode("Terrax", "mtraxx_66");
	// убираем роту
	for (int i=1; i<=7; i++) 
	{
		sld = CharacterFromID("Islamona_cpy_"+i);
		sld.lifeday = 0;
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
	}
}

// Эпизод 8. Коррида.
void Mtraxx_CorridaStart(string qName) // пришли на Мартинику
{
	Island_SetReloadEnableGlobal("Martinique", false);
	int iRank = 20+MOD_SKILL_ENEMY_RATE;
	int iScl = 55;
	// ставим полакр Марко и корабли пиратов Барбазона - Бродяги и Упыря
	// Марко
	Group_FindOrCreateGroup("IgnasioSeaGroup");
	sld = CharacterFromID("Ignasio");
	DeleteAttribute(sld, "ship.sails");
    DeleteAttribute(sld, "ship.blots");
    DeleteAttribute(sld, "ship.masts");
	DeleteAttribute(sld, "ship.hulls");
	sld.ship.HP = 3750; // не чинится иным путем, хз знает, где собака порылась
	SetCrewQuantityFull(sld);
	sld.Abordage.Enable = false;
	sld.AlwaysFriend = true;
	sld.ShipEnemyDisable = true; 
	LAi_SetImmortal(sld, true); // сплошная защита от дурака
	sld.DontDeskTalk = true;
	sld.nation = PIRATE;
	Group_AddCharacter("IgnasioSeaGroup", "Ignasio");
	// Бродяга
	sld = GetCharacter(NPC_GenerateCharacter("Mtr_Vagrant", "mercen_26", "man", "man", iRank, PIRATE, -1, true, "quest")); 
	FantomMakeSmallSailor(sld, SHIP_CORVETTE, StringFromKey("Roger_77"), CANNON_TYPE_CULVERINE_LBS18, iScl, iScl, iScl, iScl, iScl);
	FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_13", "pistol5", "bullet", iScl*2);
	sld.name = StringFromKey("Roger_78");
	sld.lastname = StringFromKey("Roger_79");
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.AlwaysSandbankManeuver = true;
	sld.Ship.Mode = "pirate";
	sld.Abordage.Enable = false;
	sld.AlwaysFriend = true;
	sld.ShipEnemyDisable = true; 
	LAi_SetImmortal(sld, true); // сплошная защита от дурака
	sld.DontDeskTalk = true;
	Group_AddCharacter("IgnasioSeaGroup", "Mtr_Vagrant");
	// Упырь
	sld = GetCharacter(NPC_GenerateCharacter("Mtr_vampire", "mercen_25", "man", "man", iRank+5, PIRATE, -1, true, "quest")); 
	FantomMakeCoolSailor(sld, SHIP_FRIGATE, StringFromKey("Roger_80"), CANNON_TYPE_CANNON_LBS24, iScl+5, iScl+5, iScl+5);
	FantomMakeCoolFighter(sld, iRank+5, iScl+15, iScl+15, "blade_14", "pistol5", "bullet", iScl*2+100);
	sld.name = StringFromKey("Roger_81");
	sld.lastname = StringFromKey("Roger_82");
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.Ship.Mode = "pirate";
	sld.Abordage.Enable = false;
	sld.AlwaysFriend = true;
	sld.AlwaysSandbankManeuver = true;
	sld.ShipEnemyDisable = true; 
	LAi_SetImmortal(sld, true); // сплошная защита от дурака
	sld.DontDeskTalk = true;
	Group_AddCharacter("IgnasioSeaGroup", "Mtr_vampire");
	Group_SetGroupCommander("IgnasioSeaGroup", "Ignasio");
	Group_SetAddress("IgnasioSeaGroup", "Martinique", "quest_ships", "quest_ship_5");
	Group_SetTaskNone("IgnasioSeaGroup");
	Group_LockTask("IgnasioSeaGroup");
	// информируем
	bQuestDisableMapEnter = true;//закрыть карту
	bDisableCharacterMenu = true;//лочим F2
	InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться
	Log_Info(StringFromKey("Roger_83"));
	PlaySound("interface\notebook.wav");
	DoQuestFunctionDelay("Mtraxx_CorridaSenPierre", 7.0);
}

void Mtraxx_CorridaSenPierre(string qName) // релоад из моря в Сен-Пьер
{
	DoQuestReloadToLocation("FortFrance_town", "reload", "reload1", "Mtraxx_CorridaSenPierre");
}

void Mtraxx_CorridaSeeMarko(string qName) // входит Игнасио в Ле Франсуа
{
	StartQuestMovie(true, false, true);
	locCameraFromToPos(53.88, 3.68, 61.22, true, 53.40, 1.30, 51.00);
	QuestPointerDelLoc("lefransua_town", "quest", "quest2");
	
	LAi_SetActorType(pchar);
	LAi_ActorGoToLocator(pchar, "quest", "quest2", "", -1);
	DoQuestFunctionDelay("Mtraxx_CorridaSeeMarko0", 7.0);
}

void Mtraxx_CorridaSeeMarko0(string qName)	// смотрим на него
{
	LAi_SetActorType(pchar);
	LAi_ActorTurnToLocator(pchar, "reload", "reload1");
	DoQuestFunctionDelay("Mtraxx_CorridaSeeMarko1", 3.0);
}

void Mtraxx_CorridaSeeMarko1(string qName)
{
	EndQuestMovie();
	SetLaunchFrameFormParam(StringFromKey("Roger_84"), "Mtraxx_CorridaControlMarko1", 0, 5);
	LaunchFrameForm();
	WaitDate("", 0, 0, 0, 0, 10);
	RecalculateJumpTable();
	StoreDayUpdate();
	RefreshWeather();
	RefreshLandTime();
}

void Mtraxx_CorridaContinue(string qName) // назад, в Ла Вегу
{
	Island_SetReloadEnableGlobal("Martinique", true);
	DeleteAttribute(pchar, "GenQuest.CannotWait");
	AddQuestRecord("Roger_8", "4");
	QuestSetCurrentNode("Terrax", "mtraxx_73");
	pchar.quest.mtraxx_pasq_check.win_condition.l1 = "location";
	pchar.quest.mtraxx_pasq_check.win_condition.l1.location = "LaVega_town"; // правки прогона 3
	pchar.quest.mtraxx_pasq_check.function = "Mtraxx_PasqualeGrabbingCheck";
}

/*void Mtraxx_CorridaLandTimer(string qName) // 1 час
{
	pchar.questTemp.Mtraxx.Corrida.Timer = "true";
}

void Mtraxx_CorridaCheckTime(string qName) // проверяем 1 час
{
	if (CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Timer")) // задержался на суше
	{
		pchar.quest.mtraxx_corrida_torero.over = "yes";
		return;
	}
	pchar.quest.mtraxx_corrida_landtimer.over = "yes";
	Island_SetReloadEnableGlobal("Hispaniola1", false);
}*/

void Mtraxx_CorridaToreroOnMap(string qName) // запускаем энкаунтер Марко на карте // прогона 3
{
	string sGroup = "Sea_Torero1";
	Group_FindOrCreateGroup(sGroup);
	Group_SetType(sGroup, "pirate");
	sld = characterFromId("Ignasio");
	DeleteAttribute(sld, "AlwaysFriend");
	DeleteAttribute(sld, "ShipEnemyDisable");
	LAi_SetImmortal(sld, false);
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.Alwaysenemy = true; 
	sld.Coastal_Captain = true;
	sld.Ship.Mode = "pirate";
	Character_SetAbordageEnable(sld, true);//можно абордировать
	DeleteAttribute(sld, "ShipHideImmortal"); // можно топить
	SetCrewQuantity(sld, 270);
	if(MOD_SKILL_ENEMY_RATE < 8)
	{
		if(CheckAttribute(sld,"perks.list.MusketsShoot"))
			DeleteAttribute(sld,"perks.list.MusketsShoot");
	}
	SetCharacterGoods(sld, GOOD_BALLS, 800);
	if(MOD_SKILL_ENEMY_RATE > 7) SetCharacterGoods(sld, GOOD_GRAPES, 800);
	else SetCharacterGoods(sld, GOOD_GRAPES, 0);
	SetCharacterGoods(sld, GOOD_KNIPPELS, 600);
	SetCharacterGoods(sld, GOOD_BOMBS, 100);
	SetCharacterGoods(sld, GOOD_POWDER, 2000);
	SetCharacterGoods(sld, GOOD_WEAPON, 300);
	SetCharacterGoods(sld, GOOD_FOOD, 400);
	SetCharacterGoods(sld, GOOD_MEDICAMENT, 300);
	SetCharacterGoods(sld, GOOD_RUM, 50);
	SetCharacterGoods(sld, GOOD_PLANKS, 30);
	SetCharacterGoods(sld, GOOD_SAILCLOTH, 10);
	sld.Nation = SPAIN;
	sld.mapEnc.type = "war";
	sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.Name = StringFromKey("Roger_85");
	Group_AddCharacter(sGroup, "Ignasio");
	Group_SetGroupCommander(sGroup, "Ignasio");
    Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
    Group_LockTask(sGroup);
	Map_CreateTrader("Shore57", "Shore41", "Ignasio", 4);
	
	Mtraxx_CorridaToreroSquadron(); // ставим эскадру у Синт-Маартена
	ChangeItemDescribe("wolfreeks_book", "itmdescr_ignasio_book"); // журнал Игнасио
	pchar.questTemp.Mtraxx.Corrida.Logbook = "true";
	// устанавливаем дату генерации испанского конвоя
	// belamour legendary edition плюс два дня на все дела
	int iDay = 9; 
	int iHour = 18;
	if (MOD_SKILL_ENEMY_RATE < 7) 
	{
		iDay = 13;
		iHour = 12;
	}
	if(bImCasual) 
	{
		NewGameTip(StringFromKey("Roger_86"));
		iDay = 18;
		iHour = 15;
	}
	// запись в СЖ
	pchar.questTemp.Mtraxx.Corrida.Day = GetAddingDataDay(0, 0, iDay);
	pchar.questTemp.Mtraxx.Corrida.Month = GetAddingDataMonth(0, 0, iDay);
	pchar.questTemp.Mtraxx.Corrida.Year = GetAddingDataYear(0, 0, iDay);
	pchar.quest.mtraxx_corrida_hispanios.win_condition.l1 = "Timer";
	pchar.quest.mtraxx_corrida_hispanios.win_condition.l1.date.hour  = iHour;
	pchar.quest.mtraxx_corrida_hispanios.win_condition.l1.date.day   = GetAddingDataDay(0, 0, iDay);
	pchar.quest.mtraxx_corrida_hispanios.win_condition.l1.date.month = GetAddingDataMonth(0, 0, iDay);
	pchar.quest.mtraxx_corrida_hispanios.win_condition.l1.date.year  = GetAddingDataYear(0, 0, iDay);
	pchar.quest.mtraxx_corrida_hispanios.function = "Mtraxx_CorridaTimeHispanios";
	pchar.quest.mtraxx_corrida_hispanios1.win_condition.l1 = "Timer";
	pchar.quest.mtraxx_corrida_hispanios1.win_condition.l1.date.hour  = 1.00;
	pchar.quest.mtraxx_corrida_hispanios1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, iDay+1);
	pchar.quest.mtraxx_corrida_hispanios1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, iDay+1);
	pchar.quest.mtraxx_corrida_hispanios1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, iDay+1);
	pchar.quest.mtraxx_corrida_hispanios1.function = "Mtraxx_CorridaLateHispanios";
	
	pchar.quest.mtraxx_corrida_capture.win_condition.l1 = "Character_Capture";
	pchar.quest.mtraxx_corrida_capture.win_condition.l1.character = "Ignasio";
	pchar.quest.mtraxx_corrida_capture.function = "Mtraxx_CorridaIgnasioCapture";//взяли на абордаж
	pchar.quest.mtraxx_corrida_sink.win_condition.l1 = "Character_sink";
	pchar.quest.mtraxx_corrida_sink.win_condition.l1.character = "Ignasio";
	pchar.quest.mtraxx_corrida_sink.function = "Mtraxx_CorridaIgnasioSink";//потопили
	
	// Captain Beltrop, 12.09.21, отключаем морских ОЗГов на время
    pchar.GenQuest.SeaHunter2Pause = true;
    SeaHunter_Delete();
}

void Mtraxx_CorridaToreroSquadron() // ставим эскадру пиратов у Синт-Маартена
{
	/*Island_SetReloadEnableGlobal("Hispaniola2", false); // патч 17/1
	Island_SetReloadEnableGlobal("SentMartin", false);
	Island_SetReloadEnableGlobal("Bermudes", false);
	Island_SetReloadEnableGlobal("Nevis", false);
	Island_SetReloadEnableGlobal("PuertoRico", false);
	Island_SetReloadEnableGlobal("Tortuga", false);
	Island_SetReloadEnableGlobal("Antigua", false);*/
	pchar.questTemp.Mtraxx.Corrida.IslandLock = "true";
	Group_FindOrCreateGroup("JokerSeaGroup");
	sld = GetCharacter(NPC_GenerateCharacter("Mtr_joker", "mercen_20", "man", "man", 35, HOLLAND, -1, true, "quest")); 
	FantomMakeCoolSailor(sld, SHIP_FRIGATE, StringFromKey("Roger_87"), CANNON_TYPE_CANNON_LBS24, 100, 100, 100);
	FantomMakeCoolFighter(sld, 100, 100, 100, "blade_13", "pistol5", "bullet", 200);
	sld.name = StringFromKey("Roger_88");
	sld.lastname = StringFromKey("Roger_89");
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.Ship.Mode = "pirate";
	sld.Abordage.Enable = false;
	sld.AlwaysFriend = true;
	sld.ShipEnemyDisable = true; 
	LAi_SetImmortal(sld, true); // сплошная защита от дурака
	sld.DontDeskTalk = true;
	Group_AddCharacter("JokerSeaGroup", "Mtr_joker");
	sld = CharacterFromID("Mtr_Vagrant");
	sld.nation = HOLLAND;
	Group_AddCharacter("JokerSeaGroup", "Mtr_Vagrant");
	sld = CharacterFromID("Mtr_vampire");
	sld.nation = HOLLAND;
	Group_AddCharacter("JokerSeaGroup", "Mtr_vampire");
	Group_SetGroupCommander("JokerSeaGroup", "Mtr_joker");
	Group_SetAddress("JokerSeaGroup", "SentMartin", "quest_ships", "quest_ship_1");
	Group_SetTaskNone("JokerSeaGroup");
	Group_LockTask("JokerSeaGroup");
	// атрибут слежения
	pchar.questTemp.Mtraxx.Ignasio.Check = "true";
}

void Mtraxx_CorridaTimeFindTorero(string qName) // упустил Тореро на карте
{
	Mtraxx_CorridaIgnasioFail();
	AddQuestRecord("Roger_8", "24");
	
	DeleteAttribute(pchar, "GenQuest.SeaHunter2Pause"); // вертаем морских ОЗГов
}

void Mtraxx_CorridaIgnasioFail() // провал перехвата Тореро, общие команды
{
	sld = CharacterFromID("Mtr_joker");
	sld.lifeday = 0;
	sld = CharacterFromID("Mtr_Vagrant");
	sld.lifeday = 0;
	sld = CharacterFromID("Mtr_vampire");
	sld.lifeday = 0;
	/*Island_SetReloadEnableGlobal("Hispaniola1", true);
	Island_SetReloadEnableGlobal("Hispaniola2", true); // патч 17/1
	Island_SetReloadEnableGlobal("SentMartin", true);
	Island_SetReloadEnableGlobal("Bermudes", true);
	Island_SetReloadEnableGlobal("Nevis", true);
	Island_SetReloadEnableGlobal("PuertoRico", true);
	Island_SetReloadEnableGlobal("Tortuga", true);
	Island_SetReloadEnableGlobal("Antigua", true);*/
	DeleteAttribute(pchar, "questTemp.Mtraxx.Corrida.IslandLock");
	DeleteAttribute(pchar, "questTemp.Mtraxx.Ignasio.Check");
	// belamour зачищаем Корриду -->
	DeleteAttribute(pchar, "questTemp.Mtraxx.Ignasio.Ship");   
	DeleteAttribute(pchar, "questTemp.Mtraxx.Ignasio.Signal"); 
	DeleteAttribute(pchar, "questTemp.Mtraxx.Ignasio.Flag");  
    // <-- belamour
	pchar.quest.mtraxx_corrida_hispanios.over = "yes";
	pchar.quest.mtraxx_corrida_hispanios1.over = "yes";

	pchar.quest.mtraxx_corrida_sink.over = "yes"; // mitrokosta снимаем уже не нужные прерывания
	pchar.quest.mtraxx_corrida_capture.over = "yes";

	QuestSetCurrentNode("Terrax", "mtraxx_87");
	
	DeleteAttribute(pchar, "GenQuest.SeaHunter2Pause"); // вертаем морских ОЗГов
	// belamour legendary edition забрать флаг обратно
	if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
	{
		DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
		DeleteAttribute(pchar,"perks.list.FlagSpa"); 
		log_info(StringFromKey("Roger_1"));
	}
}

void Mtraxx_CorridaIgnasioCapture(string qName) // захватил, проверяем
{
	pchar.quest.Mtraxx_CorridaTimeFindTorero.over = "yes";
	pchar.quest.mtraxx_corrida_sink.over = "yes"; // mitrokosta если захватили, утопить не можем
	DeleteAttribute(pchar, "questTemp.Mtraxx.Corrida.Logbook");
	// наличие журнала
	if (!CheckCharacterItem(pchar, "wolfreeks_book"))
	{
		AddQuestRecord("Roger_8", "8");
		Mtraxx_CorridaIgnasioFail();
		return;
	}
	// нахождение в акватории ближе 5000 м
	if (CheckAttribute(pchar, "questTemp.Mtraxx.Ignasio.Fail"))
	{
		DeleteAttribute(pchar, "questTemp.Mtraxx.Ignasio.Fail");
		if (CheckCharacterItem(pchar, "wolfreeks_book")) RemoveItems(pchar, "wolfreeks_book", 1);
		AddQuestRecord("Roger_8", "9");
		Mtraxx_CorridaIgnasioFail();
		return;
	}
	AddQuestRecord("Roger_8", "10");
	DeleteAttribute(pchar, "questTemp.Mtraxx.Ignasio.Check");
	pchar.questTemp.Mtraxx.Logbook.CanRead = "true";
	pchar.questTemp.Mtraxx.Ignasio.Journal = "true";
	AddComplexSeaExpToScill(50, 50, 50, 300, 50, 50, 0);
	AddCharacterExpToSkill(pchar, "Fortune", 100);
}

void Mtraxx_CorridaIgnasioSink(string qName) // утопил - провал
{
	pchar.quest.Mtraxx_CorridaTimeFindTorero.over = "yes";
	DeleteAttribute(pchar, "questTemp.Mtraxx.Corrida.Logbook");
	AddQuestRecord("Roger_8", "7");
	Mtraxx_CorridaIgnasioFail();
	
	DeleteAttribute(pchar, "GenQuest.SeaHunter2Pause"); // вертаем морских ОЗГов
}

void Mtraxx_CorridaCheckPolacre() // проверяем правильность корабля
{
	DeleteAttribute(pchar, "questTemp.Mtraxx.Ignasio.Ship");
	if (sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_POLACRE_QUEST || GetCompanionQuantity(pchar) > 1)
	{
		RemoveItems(pchar, "wolfreeks_book", 1);
		AddQuestRecord("Roger_8", "16");
		Mtraxx_CorridaIgnasioFail();
	}
	else log_Testinfo("Проверка на полакр пройдена");
}

void Mtraxx_CorridaIgnasioDove(string qName) // выпускаем голубя - картинка
{
	RemoveItems(pchar, "Dove", 1);
	ResetSound();
	PlayStereoSound("Weather\All_for_Sea_Storm_02.wav");
	SetLaunchFrameFormParam("", "", 0, 8);
	SetLaunchFrameFormPic("loading\Dove.tga");
	LaunchFrameForm();
	bQuestDisableMapEnter = false;
	InterfaceStates.Buttons.Save.enable = true; 
	bDisableCharacterMenu = false;
}

void Mtraxx_CorridaIgnasioFailFlag() // поднял не тот флаг
{
	RemoveItems(pchar, "wolfreeks_book", 1);
	AddQuestRecord("Roger_8", "12");
	Mtraxx_CorridaIgnasioFail();
	
	DeleteAttribute(pchar, "GenQuest.SeaHunter2Pause"); // вертаем морских ОЗГов
}

void Mtraxx_CorridaIgnasioRightFlag() // 
{
	AddQuestRecord("Roger_8", "14");
	sld = CharacterFromID("Mtr_joker");
	sld.lifeday = 0;
	Ship_SetTaskRunAway(SECONDARY_TASK, sti(sld.index), sti(pchar.index));
	sld = CharacterFromID("Mtr_Vagrant");
	sld.lifeday = 0;
	Ship_SetTaskRunAway(SECONDARY_TASK, sti(sld.index), sti(pchar.index));
	sld = CharacterFromID("Mtr_vampire");
	sld.lifeday = 0;
	Ship_SetTaskRunAway(SECONDARY_TASK, sti(sld.index), sti(pchar.index));
	pchar.questTemp.Mtraxx.Corrida.Hispanios = "true"; // разрешение генерации испанского конвоя
	pchar.questTemp.Mtraxx.Corrida.Barbazon = "true"; // для диалога
}

void Mtraxx_CorridaTimeHispanios(string qName) // дата прихода конвоя
{
	log_Testinfo("Время генерации конвоя!");
	if (!CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Hispanios")) return;
	if (CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Late")) return;
	if (bSeaActive) DoQuestFunctionDelay("Mtraxx_CorridaCheckCoordinates", 0.5);
	else
	{
		pchar.quest.mtraxx_corrida_hispconvoy.win_condition.l1 = "EnterToSea";
		pchar.quest.mtraxx_corrida_hispconvoy.function = "Mtraxx_CorridaCheckCoordinates";
	}
}

void Mtraxx_CorridaCheckCoordinates(string qName) // проверяем место
{
	log_Testinfo("Проверяю координаты...");
	if (!CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Hispanios")) return; // доп. проверка
	if (CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Late")) return;
	int degN, degW, minN1, minN2, minW1, minW2;
	degN = 23; // градус широты
	degW = 64; // градус долготы
	if(MOD_SKILL_ENEMY_RATE < 8)
	{
		minN1 = 0; // нижний предел интервала широты
		minN2 = 30; // верхний предел интервала широты
		minW1 = 25; // нижний предел интервала долготы
		minW2 = 55; // верхний предел интервала долготы
	}
	else  // казуалам достаточно попасть в минуту
	{
		minN1 = 0; // нижний предел интервала широты
		minN2 = 60; // верхний предел интервала широты
		minW1 = 0; // нижний предел интервала долготы
		minW2 = 60; // верхний предел интервала долготы
	}
	if (CheckAttribute(pchar, "Ship.pos.x") && !bDisableMapEnter)
	{
		if(GetSeaCoordDegreeZ(makefloat(pchar.Ship.pos.z)) == degN && GetMapCoordMinutesZ(makefloat(worldMap.playerShipZ)) >= minN1 && GetMapCoordMinutesZ(makefloat(worldMap.playerShipZ)) < minN2 && GetSeaCoordDegreeX(makefloat(pchar.Ship.pos.x)) == degW && GetMapCoordMinutesX(makefloat(worldMap.playerShipX)) >= minW1 && GetMapCoordMinutesX(makefloat(worldMap.playerShipX)) < minW2) 
		{	
			if(bImCasual)
			{
				notification(StringFromKey("Roger_90"), "");
			}
			log_Testinfo("Координаты найдены!");
			pchar.questTemp.Mtraxx.Ignasio.Capellan = "true";
			Flag_PIRATE();
			bQuestDisableMapEnter = true;
			pchar.quest.mtraxx_corrida_hispanios1.over = "yes";
			DoQuestFunctionDelay("Mtraxx_CorridaCreateHispanios", 3.0);
		}
		else 
		{
			if(bImCasual)
			{
				notification(StringFromKey("Roger_91"), "");
			}
			log_Testinfo("Координаты не соответствуют");
			pchar.quest.mtraxx_corrida_hispconvoy1.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_corrida_hispconvoy1.function = "Mtraxx_CorridaTimeHispanios";
		}
	}
	else log_Testinfo("Координаты не проверяются");
}

void Mtraxx_CorridaLateHispanios(string qName) // 
{
	pchar.questTemp.Mtraxx.Corrida.Late = "true";
	SetFunctionTimerCondition("Mtraxx_CorridaLate", 0, 0, 1, false);
	Island_SetReloadEnableGlobal("SentMartin", true);
	if (CheckCharacterItem(pchar, "wolfreeks_book")) RemoveItems(pchar, "wolfreeks_book", 1); // прогона 3
}

void Mtraxx_CorridaLate(string qName) // // правки прогона 3
{
	Island_SetReloadEnableGlobal("Hispaniola1", true);
	Island_SetReloadEnableGlobal("Hispaniola2", true); // патч 17/1
	Island_SetReloadEnableGlobal("Bermudes", true);
	Island_SetReloadEnableGlobal("Nevis", true);
	Island_SetReloadEnableGlobal("PuertoRico", true);
	Island_SetReloadEnableGlobal("Tortuga", true);
	Island_SetReloadEnableGlobal("Antigua", true);
	QuestSetCurrentNode("Terrax", "mtraxx_87");
    Mtraxx_CorridaIgnasioFail(); // belamour шишку новогоднюю, а не мушкетон в подземельях
	AddQuestRecord("Roger_8", "15");
	
	DeleteAttribute(pchar, "GenQuest.SeaHunter2Pause"); // вертаем морских ОЗГов
}

void Mtraxx_CorridaCreateHispanios(string qName) // ставим конвой испанцев с золотом
{
	Ship_FlagRefresh(PChar);
	Island_SetReloadEnableGlobal("Hispaniola1", true);
	Island_SetReloadEnableGlobal("Hispaniola2", true); // патч 17/1
	Island_SetReloadEnableGlobal("SentMartin", true);
	Island_SetReloadEnableGlobal("Bermudes", true);
	Island_SetReloadEnableGlobal("Nevis", true);
	Island_SetReloadEnableGlobal("PuertoRico", true);
	Island_SetReloadEnableGlobal("Tortuga", true);
	Island_SetReloadEnableGlobal("Antigua", true);
	DeleteAttribute(pchar, "questTemp.Mtraxx.Corrida.IslandLock");
	DeleteAttribute(pchar, "questTemp.Mtraxx.Corrida.Hispanios");
	log_info(StringFromKey("Roger_92"));
	PlaySound("interface\notebook.wav");
	PlaySound("interface\" + LanguageGetLanguage() + "\_EvEnemy0.wav");
	Group_FindOrCreateGroup("Mtr_GoldSeaGroup");
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+7;
	if (iRank > 45) iRank = 45;
	int iShip, Ship1, Ship2, Ship3, iCannon, Cannon1, Cannon2, iSpace;
	
	switch (MOD_SKILL_ENEMY_RATE)
	{
		case 2:
			Ship1 = SHIP_SHNYAVA;
			Ship3 = SHIP_FLEUT;
			Cannon1 = CANNON_TYPE_CANNON_LBS16;
			Cannon2 = CANNON_TYPE_CANNON_LBS8;
		break;
		
		case 4:
			Ship1 = SHIP_FLEUT;
			Ship3 = SHIP_BRIGANTINE;
			Cannon1 = CANNON_TYPE_CULVERINE_LBS8;
			Cannon2 = CANNON_TYPE_CANNON_LBS12;
		break;
		
		case 6:
			Ship1 = SHIP_GALEON_L;
			Ship3 = SHIP_CORVETTE;
			Cannon1 = CANNON_TYPE_CANNON_LBS24;
			Cannon2 = CANNON_TYPE_CULVERINE_LBS18;
		break;
		
		case 8:
			Ship1 = SHIP_EASTINDIAMAN;
			Ship3 = SHIP_NAVIO;
			Cannon1 = CANNON_TYPE_CANNON_LBS24;
			Cannon2 = CANNON_TYPE_CANNON_LBS20;
		break;
		
		case 10:
			Ship1 = SHIP_GALEON_H;
			Ship3 = SHIP_GALEON_H;
			Cannon1 = CANNON_TYPE_CANNON_LBS32;
			Cannon2 = CANNON_TYPE_CANNON_LBS24;
		break;
	}
	for (int i=1; i<=3; i++)
	{
		switch (i)
		{
			case 1:
				iShip = Ship1;
				iCannon = Cannon1;
			break;
			
			case 2:
				iShip = SHIP_GALEON_H;
				iCannon = CANNON_TYPE_CANNON_LBS36;
				if (MOD_SKILL_ENEMY_RATE < 4) iCannon = CANNON_TYPE_CULVERINE_LBS18;
			break;
			
			case 3:
				iShip = Ship3;
				iCannon = Cannon2;
			break;
		}
		sld = GetCharacter(NPC_GenerateCharacter("Mtr_GoldCap_"+i, "off_spa_"+i, "man", "man", iRank, SPAIN, -1, true, "quest"));
		FantomMakeCoolSailor(sld, iShip, "", iCannon, 80, 80, 80);
		FantomMakeCoolFighter(sld, iRank, 100, 100, LinkRandPhrase("blade_17","blade_20","blade_21"), "pistol5", "bullet", 250);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		sld.DontRansackCaptain = true;
		sld.AnalizeShips = true;
		sld.AlwaysEnemy = true;
		sld.Ship.Mode = "war";
		sld.ship.Crew.Morale = 60+MOD_SKILL_ENEMY_RATE*4;
		sld.Ship.Crew.Exp.Sailors = 60+MOD_SKILL_ENEMY_RATE*4;
		sld.Ship.Crew.Exp.Cannoners = 60+MOD_SKILL_ENEMY_RATE*4;
		sld.Ship.Crew.Exp.Soldiers = 60+MOD_SKILL_ENEMY_RATE*4;
		if (MOD_SKILL_ENEMY_RATE > 4) SetCharacterPerk(sld, "MusketsShoot");
		if (i == 1) 
		{
			iSpace = GetCharacterFreeSpace(sld, GOOD_PAPRIKA);
			iSpace = makeint(iSpace/2 + rand(iSpace/2));
			Fantom_SetCharacterGoods(sld, GOOD_PAPRIKA, iSpace, 1);
		}
		if (i == 2) 
		{
			sld.ship.name = StringFromKey("Roger_93");
			UpgradeShipParameter(sld, "Capacity");
			SetRandGeraldSail(sld, SPAIN);
			NullCharacterGoods(sld);
			AddCharacterGoods(sld, GOOD_BALLS, 1500);
			AddCharacterGoods(sld, GOOD_GRAPES, 1000);
			AddCharacterGoods(sld, GOOD_KNIPPELS, 800);
			AddCharacterGoods(sld, GOOD_BOMBS, 1700);
			AddCharacterGoods(sld, GOOD_POWDER, 5000);
			AddCharacterGoods(sld, GOOD_WEAPON, 700);
			AddCharacterGoods(sld, GOOD_FOOD, 1000);
			AddCharacterGoods(sld, GOOD_MEDICAMENT, 250);
			AddCharacterGoods(sld, GOOD_RUM, 100);
			AddCharacterGoods(sld, GOOD_GOLD, 1100+rand(100));
		}
		if (i == 3) 
		{
			iSpace = GetCharacterFreeSpace(sld, GOOD_TOBACCO);
			iSpace = makeint(iSpace/2 + rand(iSpace/2));
			Fantom_SetCharacterGoods(sld, GOOD_TOBACCO, iSpace, 1);
		}
		Group_AddCharacter("Mtr_GoldSeaGroup", "Mtr_GoldCap_"+i);
	}
	Group_SetGroupCommander("Mtr_GoldSeaGroup", "Mtr_GoldCap_1");
	Group_SetTaskAttack("Mtr_GoldSeaGroup", PLAYER_GROUP);
	Group_LockTask("Mtr_GoldSeaGroup");
	Sea_LoginGroupCurrentSea("Mtr_GoldSeaGroup");
	// на корабль Тиракса
	int Hour = 2;
	if (MOD_SKILL_ENEMY_RATE < 4) Hour = 1;
	if (MOD_SKILL_ENEMY_RATE > 6) Hour = 3;
	pchar.quest.mtraxx_corrida_boss.win_condition.l1 = "Timer";
	pchar.quest.mtraxx_corrida_boss.win_condition.l1.date.hour  = sti(GetTime() + Hour);
	pchar.quest.mtraxx_corrida_boss.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
	pchar.quest.mtraxx_corrida_boss.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
	pchar.quest.mtraxx_corrida_boss.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
	pchar.quest.mtraxx_corrida_boss.function = "Mtraxx_CorridaMarkus";
	// реакции
	pchar.quest.mtraxx_corrida_goldwin.win_condition.l1 = "Character_Capture";
	pchar.quest.mtraxx_corrida_goldwin.win_condition.l1.character = "Mtr_GoldCap_2";
	pchar.quest.mtraxx_corrida_goldwin.function = "Mtraxx_CorridaGoldWin";
	pchar.quest.mtraxx_corrida_goldsink.win_condition.l1 = "Character_sink";
	pchar.quest.mtraxx_corrida_goldsink.win_condition.l1.character = "Mtr_GoldCap_2";
	pchar.quest.mtraxx_corrida_goldsink.function = "Mtraxx_CorridaGoldFail";
	pchar.quest.mtraxx_corrida_goldcheck.win_condition.l1 = "Group_Death";
	pchar.quest.mtraxx_corrida_goldcheck.win_condition.l1.group = "Mtr_GoldSeaGroup";
	pchar.quest.mtraxx_corrida_goldcheck.function = "Mtraxx_CorridaGoldCheck";
	
	DeleteAttribute(pchar, "GenQuest.SeaHunter2Pause"); // вертаем морских ОЗГов
}

void Mtraxx_CorridaMarkus(string qName) // 
{
	Group_FindOrCreateGroup("Terrax_SeaGroup");
	sld = CharacterFromID("Terrax");
	FantomMakeCoolSailor(sld, SHIP_LINESHIP, StringFromKey("Roger_94"), CANNON_TYPE_CULVERINE_LBS36, 110, 110, 110);
	FantomMakeCoolFighter(sld, 50, 110, 110, "blade_19", "pistol4", "bullet", 300);
	sld.DeckDialogNode = "mtraxx_board";
	SetCharacterPerk(sld, "BasicDefense");
	SetCharacterPerk(sld, "Gunman");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "Doctor1");
	SetCharacterPerk(sld, "Doctor2");
	SetCharacterPerk(sld, "ShipSpeedUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "WindCatcher");
	SetCharacterPerk(sld, "SailsMan");
	SetCharacterPerk(sld, "SailingProfessional");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "FastReload");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "BasicBattleState");
	SetCharacterPerk(sld, "AdvancedBattleState");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	SetCharacterPerk(sld, "Carpenter");
	SetCharacterPerk(sld, "Builder");
	SetCharacterPerk(sld, "LongRangeGrappling");
	SetCharacterPerk(sld, "GrapplingProfessional");
	SetCharacterPerk(sld, "Brander");
	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterPerk(sld, "BasicCommerce");
	SetCharacterPerk(sld, "AdvancedCommerce");
    GiveItem2Character(sld, "talisman3");    //belamour некий бонус за Корриду
	EquipCharacterbyItem(sld, "talisman3");  // у протагониста орудия взрываются на раз два
    EquipCharacterbyItem(sld, "pistol4");    // без дела в инвентаре лежит
    LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet"); 
	Mtraxx_MarkusSetShipParameter();
	SetCharacterGoods(sld, GOOD_BALLS, 3500);
	SetCharacterGoods(sld, GOOD_GRAPES, 2000);
	SetCharacterGoods(sld, GOOD_KNIPPELS, 1500);
	SetCharacterGoods(sld, GOOD_BOMBS, 3500);
	SetCharacterGoods(sld, GOOD_POWDER, 10500);
	SetCharacterGoods(sld, GOOD_WEAPON, 1000);
	SetCharacterGoods(sld, GOOD_FOOD, 2000);
	SetCharacterGoods(sld, GOOD_MEDICAMENT, 700);
	SetCharacterGoods(sld, GOOD_RUM, 200);
	SetCharacterGoods(sld, GOOD_PLANKS, 100);
	SetCharacterGoods(sld, GOOD_SAILCLOTH, 50);
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.AlwaysSandbankManeuver = true;
	Character_SetAbordageEnable(sld, false); // нельзя абордировать
	sld.Tasks.CanBoarding = false; // запрет идти на абордаж - дубль
	sld.Tasks.CanChangeShipAfterBoarding = false; // запрет меняться кораблями - дубль
	sld.Ship.Mode = "mercenary";
	sld.Abordage.Enable = false;
	sld.AlwaysFriend = true;
	sld.ShipEnemyDisable = true; 
	sld.DontDeskTalk = true;
	LAi_SetImmortal(sld, false);
	sld.ShipHideImmortal = 1000; // непотопляемый корабль
	sld.SeaBoss = 0.8; // получает на 80% меньше урона корпусу, 10% урона парусам
	Group_AddCharacter("Terrax_SeaGroup", "Terrax");
	Group_SetGroupCommander("Terrax_SeaGroup", "Terrax");
	Group_SetTaskAttack("Terrax_SeaGroup", "Mtr_GoldSeaGroup");
	Group_LockTask("Terrax_SeaGroup");
	Sea_LoginGroupCurrentSea("Terrax_SeaGroup");
	DoQuestFunctionDelay("Mtraxx_CorridaMarkusCommand", 3.0);
	pchar.quest.mtraxx_ship_fail.win_condition.l1 = "NPC_Death";
	pchar.quest.mtraxx_ship_fail.win_condition.l1.character = "Terrax";
	pchar.quest.mtraxx_ship_fail.function = "Mtraxx_MarkusGameOver"; // для шибко грамотных
}

void Mtraxx_MarkusGameOver(string qName) // прибьем корабль особо умных, чтобы не выделывались
{
	Log_Info(StringFromKey("Roger_95", pchar.ship.name));
	Ship_Detonate(pchar, true, true); 
	PlaySound("Sea Battles\Vzriv_fort_001.wav");
	PlaySound("Sea Battles\vzriv_pogreb_002.wav");
	PlaySound("Sea Battles\vzriv_pogreb_002.wav");
}

void Mtraxx_MarkusSetShipParameter()
{
	sld = CharacterFromID("Terrax");
	SetSelfSkill(sld, 90, 90, 90, 90, 90);
	SetShipSkill(sld, 75, 90, 100, 100, 100, 100, 100, 100, 80);
	RealShips[sti(sld.Ship.Type)].MaxCaliber = 36;
	RealShips[sti(sld.Ship.Type)].CannonsQuantityMin = 56;
	RealShips[sti(sld.Ship.Type)].MaxCrew = 800;
	RealShips[sti(sld.Ship.Type)].SpeedRate = 13.5;
	RealShips[sti(sld.Ship.Type)].TurnRate = 29.5;
	RealShips[sti(sld.Ship.Type)].MaxCrew = 800;
	RealShips[sti(sld.Ship.Type)].HP = 8000;
	RealShips[sti(sld.Ship.Type)].WindAgainstSpeed = 0.42;
	RealShips[sti(sld.Ship.Type)].ship.upgrades.hull = 1;
    sld.ship.HP = 8000;    //belamour текущее состояние корпуса в макс.
	SetSailsColor(sld, 8);//черный парус
	UpgradeShipParameter(sld, "SpeedRate");//апгрейдить скорость
	UpgradeShipParameter(sld, "TurnRate");//маневренность
	UpgradeShipParameter(sld, "WindAgainstSpeed");//бейд
	DeleteAttribute(sld, "ship.hulls");
	int hcrew = GetMaxCrewQuantity(sld);
	SetCrewQuantity(sld, hcrew);
	sld.Ship.Crew.Morale = 100;
	sld.Ship.Crew.Exp.Sailors = 100;
	sld.Ship.Crew.Exp.Cannoners = 100;
	sld.Ship.Crew.Exp.Soldiers = 100;
}

void Mtraxx_CorridaMarkusCommand(string qName) // 
{
	ref chr = CharacterFromID("Terrax");
	sld = CharacterFromID("Mtr_GoldCap_1");
	Ship_SetTaskAttack(SECONDARY_TASK, sti(chr.index), sti(sld.index));
	SetCharacterRemovable(chr, false);
	chr.CompanionEnemyEnable = false; //всегда друзья
	SetCompanionIndex(pchar, -1, sti(chr.index));
	chr.loyality = MAX_LOYALITY;
}

void Mtraxx_CorridaGoldWin(string qName) // 
{
	pchar.questTemp.Mtraxx.Corrida.Gold = "true";
}

void Mtraxx_CorridaGoldFail(string qName) // 
{
	pchar.questTemp.Mtraxx.Corrida.Poor = "true";
}

void Mtraxx_CorridaGoldCheck(string qName) // 
{
	pchar.quest.mtraxx_ship_fail.over = "yes"; 
	Group_DeleteGroup("Mtr_GoldSeaGroup");
	pchar.GenQuest.MapClosedNoBattle = true;
	DeleteAttribute(pchar, "questTemp.Mtraxx.Ignasio.Capellan");
	sld = CharacterFromID("Terrax");
	DeleteAttribute(sld, "DontDeskTalk");
	RemoveCharacterCompanion(pchar, sld);
	sld.AlwaysFriend = true;
	sld.ShipEnemyDisable = true; 
	LAi_SetImmortal(sld, true);
	Group_AddCharacter("Terrax_SeaGroup", "Terrax");
	Group_SetGroupCommander("Terrax_SeaGroup", "Terrax");
	Group_SetTaskNone("Terrax_SeaGroup");
	Group_LockTask("Terrax_SeaGroup");
	AddQuestRecord("Roger_8", "17");
}

void Mtraxx_CorridaComplete(string qName) // 
{
	Group_DelCharacter("Terrax_SeaGroup", "Terrax");
	Group_DeleteGroup("Terrax_SeaGroup");
	pchar.questTemp.Mtraxx = "wait_month";
	sld = CharacterFromID("Terrax");
	sld.location = "LaVega_townhall";
	sld.location.group = "sit";
	sld.location.locator = "sit1";
	LAi_SetHuberType(sld);
	LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
	sld.dialog.currentnode = "First time";
	SetFunctionTimerCondition("Mtraxx_CartahenaTavernPrepare", 0, 0, 1, false); // belamour legendary edition увеличим таймер
	SetFunctionTimerCondition("Mtraxx_CartahenaPrepare", 0, 0, 1, false);
	//SetFunctionTimerCondition("Mtraxx_CartahenaLate", 0, 0, 92, false);
	// НЗГ
	ChangeCharacterComplexReputation(pchar, "nobility", -8);
	ChangeCharacterComplexReputation(pchar, "authority", 5);
	ChangeCharacterComplexReputation(pchar, "fame", 5);
	OfficersReaction("bad");
	OfficersReaction("bad");
	ChangeCharacterHunterScore(PChar, "spahunter", 20);
}

// эпизод 9. Город кровавой жатвы.
void Mtraxx_CartahenaPrepare(string qName) // готовим 9 эпизод
{
	QuestSetCurrentNode("Terrax", "mtraxx_90");
	DeleteAttribute(sld, "DontDeskTalk");
}

void Mtraxx_CartahenaTavernPrepare(string qName) // готовим таверну - запрещаем генерацию фантомов
{
	pchar.questTemp.Mtraxx.InTavern = "true";
}

/*void Mtraxx_CartahenaLate(string qName) // не пришли к Тираксу за 9 заданием
{
	if(bImCasual)
	{
		if(CheckAttribute(pchar,"quest.Mtraxx_CartahenaLate.over"))
			DeleteAttribute(pchar,"quest.Mtraxx_CartahenaLate.over");
		NewGameTip(StringFromKey("Roger_4"));
		SetFunctionTimerCondition("Mtraxx_CartahenaLate", 0, 0, 30, false);
		return;
	}
	QuestSetCurrentNode("Terrax", "First time");
	AddQuestRecord("Roger_8", "23");
	CloseQuestHeader("Roger_8");
	DeleteAttribute(pchar, "questTemp.Mtraxx.Corrida");
	DeleteAttribute(pchar, "questTemp.Mtraxx.InTavern");
	LocatorReloadEnterDisable("LaVega_town", "reload6", true); // закрыть на месяц
	SetFunctionTimerCondition("Mtraxx_CartahenaLateOpen", 0, 0, 30, false);
	Mtraxx_TerraxReset(8); // правки 4
	SetFunctionTimerCondition("Mtraxx_DelPirateCrew", 0, 0, 30, false); // Rebbebion, удалить команду пиратов через месяц
}*/

void Mtraxx_CartahenaLateOpen(string qName) // 
{
	LocatorReloadEnterDisable("LaVega_town", "reload6", false);
	sld = CharacterFromID("Terrax");
	sld.location = "LaVega_townhall";
	sld.location.group = "sit";
	sld.location.locator = "sit1";
	LAi_SetHuberType(sld);
	LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
	sld.dialog.currentnode = "First time";
	// капеллан - второй шанс
	if (CheckAttribute(pchar, "questTemp.ShipCapellan") && !CheckAttribute(pchar, "questTemp.ShipCapellan.Yes"))
	{
		DeleteAttribute(pchar, "questTemp.ShipCapellan");
	}
	// правки 4
	if (GetCharacterIndex("Mirabella") != -1)
	{
		sld = characterFromId("Mirabella");
		sld.dialog.currentnode = "mirabelle_29";
	}
}

void Mtraxx_CartahenaSailOver(string qName) // опоздание к Картахене
{
	if(bImCasual)
	{
		if(CheckAttribute(pchar,"quest.Mtraxx_CartahenaSailOver.over"))
			DeleteAttribute(pchar,"quest.Mtraxx_CartahenaSailOver.over");
		NewGameTip(StringFromKey("Roger_4"));
		SetFunctionTimerCondition("Mtraxx_CartahenaSailOver", 0, 0, 30, false);
		return;
	}
	pchar.quest.mtraxx_ship_fail1.over = "yes";
	pchar.quest.mtraxx_cartahena_sail.over = "yes";
	LocatorReloadEnterDisable("LaVega_port", "reload1_back", false); // правки релиза
	LocatorReloadEnterDisable("LaVega_town", "reload6", true); // закрыть на месяц
	SetFunctionTimerCondition("Mtraxx_CartahenaLateOpen", 0, 0, 30, false);
	DeleteAttribute(pchar, "DisableChangeFlagMode");
	pchar.worldmapencountersoff = "0";
	int i = FindColony("Cartahena");
	DeleteAttribute(colonies[i], "DontSetShipInPort");
	sld = CharacterFromID("Terrax");
	LAi_SetImmortal(sld, true);
	RemoveCharacterCompanion(pchar, sld);
	sld = characterFromId("Jeffry");
	RemoveCharacterCompanion(pchar, sld);
	sld.lifeday = 0;
	sld = characterFromId("Pelly");
	RemoveCharacterCompanion(pchar, sld);
	sld.lifeday = 0;
	sld = characterFromId("Mtr_Vensan");
	RemoveCharacterCompanion(pchar, sld);
	sld.lifeday = 0;
	AddQuestRecord("Roger_9", "2");
	Mtraxx_TerraxReset(9);
	
	DeleteAttribute(pchar, "GenQuest.SeaHunter2Pause"); // вертаем морских ОЗГов
	SetFunctionTimerCondition("Mtraxx_DelPirateCrew", 0, 0, 30, false); // Rebbebion, удалить команду пиратов через месяц
}

void Mtraxx_CartahenaArrive(string qName) // прибыли в акваторию Картахены
{
	Log_Info(StringFromKey("Roger_96"));
	PlaySound("interface\notebook.wav");
	pchar.quest.Mtraxx_CartahenaSailOver.over = "yes";
	LocatorReloadEnterDisable("LaVega_port", "reload1_back", false); // правки релиза
	bQuestDisableMapEnter = true;//закрыть карту
	Island_SetReloadEnableGlobal("Cartahena", false);
	locations[FindLocation("Shore25")].DisableEncounters = true;
	locations[FindLocation("Cartahena_ExitTown")].DisableEncounters = true;
	setCharacterShipLocation(pchar, "shore25");
	setWDMPointXZ("shore25");
	// belamour восстановить форт если была осада
	sld = CharacterFromID("Cartahena Fort Commander");
	sld.Fort.Mode = FORT_NORMAL;
	// ставим испанскую эскадру
	Group_FindOrCreateGroup("Mtr_CartahenaSeaGroup");
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE;
	int iShip, Ship1, Ship2, Ship3, iCannon, Cannon1, Cannon2, iSpace;
	
	switch (MOD_SKILL_ENEMY_RATE)
	{
		case 2:
			Ship1 = SHIP_SLOOP;
			Ship2 = SHIP_LUGGER;
			Ship3 = SHIP_WAR_TARTANE;
			Cannon1 = CANNON_TYPE_CANNON_LBS6;
			Cannon2 = CANNON_TYPE_CANNON_LBS3;
		break;
		
		case 4:
			Ship1 = SHIP_SLOOP;
			Ship2 = SHIP_SLOOP;
			Ship3 = SHIP_SCHOONER_W;
			Cannon1 = CANNON_TYPE_CANNON_LBS12;
			Cannon2 = CANNON_TYPE_CANNON_LBS12;
		break;
		
		case 6:
			Ship1 = SHIP_BRIG;
			Ship2 = SHIP_XebekVML;
			Ship3 = SHIP_BRIGANTINE;
			Cannon1 = CANNON_TYPE_CANNON_LBS16;
			Cannon2 = CANNON_TYPE_CANNON_LBS12;
		break;
		
		case 8:
			Ship1 = SHIP_POLACRE;
			Ship2 = SHIP_XebekVML;
			Ship3 = SHIP_GALEON_L;
			Cannon1 = CANNON_TYPE_CANNON_LBS16;
			Cannon2 = CANNON_TYPE_CANNON_LBS24;
		break;
		
		case 10:
			Ship1 = SHIP_NAVIO;
			Ship2 = SHIP_POLACRE;
			Ship3 = SHIP_EASTINDIAMAN;
			Cannon1 = CANNON_TYPE_CULVERINE_LBS18;
			Cannon2 = CANNON_TYPE_CANNON_LBS24;
		break;
	}
	for (int i=1; i<=3; i++)
	{
		switch (i)
		{
			case 1:
				iShip = Ship1;
				iCannon = Cannon1;
			break;
			
			case 2:
				iShip = Ship2;
				iCannon = Cannon1;
				if (MOD_SKILL_ENEMY_RATE == 4 || MOD_SKILL_ENEMY_RATE == 10) iCannon = Cannon2;
			break;
			
			case 3:
				iShip = Ship3;
				iCannon = Cannon2;
			break;
		}
		sld = GetCharacter(NPC_GenerateCharacter("Mtr_CartahenaCap_"+i, "off_spa_"+i, "man", "man", iRank, SPAIN, -1, true, "quest"));
		FantomMakeCoolSailor(sld, iShip, "", iCannon, 50, 50, 50);
		FantomMakeCoolFighter(sld, iRank, 50, 50, LinkRandPhrase("blade_13","blade_13","blade_15"), "pistol1", "bullet", 150);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		sld.DontRansackCaptain = true;
		sld.AnalizeShips = true;
		sld.AlwaysEnemy = true;
		sld.Ship.Mode = "war";
		sld.ship.Crew.Morale = 40+MOD_SKILL_ENEMY_RATE*6;
		sld.Ship.Crew.Exp.Sailors = 40+MOD_SKILL_ENEMY_RATE*6;
		sld.Ship.Crew.Exp.Cannoners = 40+MOD_SKILL_ENEMY_RATE*6;
		sld.Ship.Crew.Exp.Soldiers = 40+MOD_SKILL_ENEMY_RATE*6;
		if (MOD_SKILL_ENEMY_RATE > 4) SetCharacterPerk(sld, "MusketsShoot");
		Group_AddCharacter("Mtr_CartahenaSeaGroup", "Mtr_CartahenaCap_"+i);
	}
	Group_SetGroupCommander("Mtr_CartahenaSeaGroup", "Mtr_CartahenaCap_1");
	Group_SetAddress("Mtr_CartahenaSeaGroup", "Cartahena", "quest_ships", "quest_ship_1");
	Group_SetTaskNone("Mtr_CartahenaSeaGroup");
	Group_LockTask("Mtr_CartahenaSeaGroup");
	pchar.quest.mtraxx_cartahena_squadron.win_condition.l1 = "Group_Death";
	pchar.quest.mtraxx_cartahena_squadron.win_condition.l1.group = "Mtr_CartahenaSeaGroup";
	pchar.quest.mtraxx_cartahena_squadron.function = "Mtraxx_CartahenaDestroyScuadron";
	DoQuestFunctionDelay("Mtraxx_CartahenaAbandon", 10.0);
	
	DeleteAttribute(pchar, "GenQuest.SeaHunter2Pause"); // вертаем морских ОЗГов
}

void Mtraxx_CartahenaAbandon(string qName) // телепорт в бухту Ковеньяс
{
	pchar.GenQuest.Hunter2Pause = true; // прогона 3
	DoQuestReloadToLocation("Shore25", "rld", "loc10", "Mtraxx_CartahenaAbandon");
}

void Mtraxx_CartahenaSquadronAttack(string qName) // к атаке эскадры - готовы! // прогона 3
{
	sld = CharacterFromID("Terrax");
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	LAi_ActorGoToLocation(sld, "reload", "sea", "none", "", "", "", 15.0);
	sld = characterFromId("Jeffry");
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	LAi_ActorGoToLocation(sld, "reload", "sea", "none", "", "", "", 15.0);
	sld = characterFromId("Pelly");
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	LAi_ActorGoToLocation(sld, "reload", "sea", "none", "", "", "", 15.0);
	sld = characterFromId("Mtr_Vensan");
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	LAi_ActorGoToLocation(sld, "reload", "sea", "none", "", "", "", 15.0);
	sld = CharacterFromID("Lepricon");
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 15.0);
	for (i=5; i<=10; i++) // буканьеры Леприкона
	{
		sld = CharacterFromID("Lepricons_bukaneers_"+i);
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 15.0);
	}
	DoQuestCheckDelay("OpenTheDoors", 15.0);
	sld = CharacterFromID("Cartahena Fort Commander");
	LAi_SetImmortal(sld, true); // бессмертный форт
	Character_SetAbordageEnable(sld, false); // неабордируемый форт
	pchar.GenQuest.CannotTakeShip = true; // нельзя брать корабли призом
	AddQuestRecord("Roger_9", "3");
}

void Mtraxx_CartahenaDestroyScuadron(string qName) // потопили эскадру
{
	AddQuestRecord("Roger_9", "4");
	pchar.GenQuest.MapClosedNoBattle = true;
	DeleteAttribute(pchar, "GenQuest.CannotTakeShip");
	sld = characterFromId("Pelly");
	RemoveCharacterCompanion(pchar, sld);
	sld.AlwaysFriend = true;
	sld.ShipEnemyDisable = true; 
	ref chr = characterFromId("Mtr_Vensan");
	Ship_SetTaskDefend(SECONDARY_TASK, sti(sld.index), sti(chr.index));
	sld = CharacterFromID("Terrax");
	DeleteAttribute(sld, "DontDeskTalk");
	sld.DeckDialogNode = "mtraxx_101";
	AddComplexSeaExpToScill(100, 100, 100, 100, 100, 100, 0);
}

void Mtrxtofort(string qName)
{
	DoQuestCheckDelay("Mtraxx_CartahenaPrepareFortBattle_Delay", 600.0);
}

void Mtraxx_CartahenaPrepareFortBattle() // готовим атаку форта - штурм квестовый
{
	DeleteAttribute(pchar, "questTemp.Mtraxx.Cartahena.Fort");
	PlaySound("MUSIC\Victory.mp3");
	Log_Info(StringFromKey("Roger_97"));
	PlaySound("interface\notebook.wav");
	PlaySound("interface\" + LanguageGetLanguage() + "\_GTTown2.wav");
	// расчет числа десанта
	int iCrew1 = GetCrewQuantity(pchar) - GetMinCrewQuantity(pchar));
	if (iCrew1 <= GetMinCrewQuantity(pchar)) iCrew1 = 0; // патч 17/1
	int iCrew2 = GetCrewQuantity(characterFromId("Terrax")) - GetMinCrewQuantity(characterFromId("Terrax"));
	if (iCrew2 <= GetMinCrewQuantity(characterFromId("Terrax"))) iCrew2 = 0; // патч 17/1
	int iCrew3 = GetCrewQuantity(characterFromId("Jeffry")) - GetMinCrewQuantity(characterFromId("Jeffry"));
	if (iCrew3 <= GetMinCrewQuantity(characterFromId("Jeffry"))) iCrew3 = 0; // патч 17/1
	int iCrew4 = GetCrewQuantity(characterFromId("Pelly")) - GetMinCrewQuantity(characterFromId("Pelly"));
	if (iCrew4 <= GetMinCrewQuantity(characterFromId("Pelly"))) iCrew4 = 0; // патч 17/1
	int iCrew = iCrew1 + iCrew2 + iCrew3 + iCrew4;
	log_info(StringFromKey("Roger_98", pchar.ship.name, iCrew1));
	log_info(StringFromKey("Roger_99", iCrew2));
	log_info(StringFromKey("Roger_100", iCrew3));
	log_info(StringFromKey("Roger_101", iCrew4));
	pchar.questTemp.Mtraxx.Cartahena.Crew = iCrew;
	pchar.questTemp.Mtraxx.Cartahena.Crewpercent1 = makeint(100*iCrew1/iCrew); // процент команды ГГ
	pchar.questTemp.Mtraxx.Cartahena.Crewpercent2 = makeint(100*iCrew2/iCrew); // процент команды Тиракса
	pchar.questTemp.Mtraxx.Cartahena.Crewpercent3 = makeint(100*iCrew3/iCrew); // процент команды Джеффри
	pchar.questTemp.Mtraxx.Cartahena.Crewpercent4 = makeint(100*iCrew4/iCrew); // процент команды Тесака
	DoQuestFunctionDelay("Mtraxx_CartahenaFortReload", 10.0);
}

void Mtraxx_CartahenaFortReload(string qName) // перегруз в первую фортовую локацию
{
	MakeCloneFortBoarding("Cartahena_fort");
	DoQuestReloadToLocation("BOARDING_FORT", "goto", "loc14", "Mtraxx_CartahenaFortFirstBattle");
}

void Mtraxx_CartahenaFortReloadNext(string qName) // перегруз во втрорую фортовую локацию
{
	DoQuestReloadToLocation("Boarding_bastion1", "reload", "reload1", "Mtraxx_CartahenaFortSecondBattle");
}

void Mtraxx_CartahenaFortReloadEnd(string qName) // перегруз в третью фортовую локацию
{
	DoQuestReloadToLocation("Boarding_fortyard", "reload", "reload3", "Mtraxx_CartahenaFortThirdBattle");
}

void Mtraxx_CartahenaExittownReload(string qName) // перегруз в локацию выход из города
{
	DoQuestReloadToLocation("Cartahena_ExitTown", "reload", "reload3", "Mtraxx_CartahenaExittownBattle");
}

void Mtraxx_CartahenaTownReload(string qName) // перегруз в локацию города
{
	DoQuestReloadToLocation("Cartahena_Town", "quest", "quest2", "Mtraxx_CartahenaTownBattle");
}

void Mtraxx_CartahenaToResidence(string qName) // перегруз в резиденцию
{
	DoQuestReloadToLocation("Cartahena_Townhall", "reload", "reload1", "Mtraxx_CartahenaResidence");
}

void Mtraxx_CartahenaInResidence(string qName) // Тесак идёт искать
{
	LAi_SetActorType(pchar);
	LAi_ActorTurnToLocator(pchar, "reload", "reload3");
	sld = CharacterFromID("Pelly");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload3", "none", "", "", "", 10.0);
	DoQuestFunctionDelay("Mtraxx_CartahenaResidenceWomen", 12.0);
}

void Mtraxx_CartahenaResidenceWomen(string qName) // женщины губернатора
{
	LAi_SetActorType(pchar);
	LAi_ActorTurnToLocator(pchar, "reload", "reload3");
	string sModel = "women_2";
	for (i=1; i<=3; i++)
	{
		if (i == 2) sModel = "women_6";
		if (i == 3) sModel = "women_14";
		sld = GetCharacter(NPC_GenerateCharacter("Mtr_CartahenaWomen_"+i, sModel, "woman", "towngirl", 1, SPAIN, 3, true, "quest"));
		SetFantomParamFromRank(sld, 1, true);
		RemoveAllCharacterItems(sld, true);
		ChangeCharacterAddressGroup(sld, "Cartahena_Townhall", "reload", "reload3");
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, pchar, "", 3.0);
	}
	DoQuestFunctionDelay("Mtraxx_CartahenaResidencePelly", 3.0);
	
}

void Mtraxx_CartahenaResidencePelly(string qName) // Тесак возвращается
{
	LAi_SetPlayerType(pchar);
	sld = CharacterFromID("Pelly");
	ChangeCharacterAddressGroup(sld, "Cartahena_Townhall", "reload", "reload3");
	LAi_CharacterEnableDialog(sld);
	sld.dialog.currentnode = "Pelly_28";
	sld.greeting = "";
	LAi_SetActorType(sld);
	LAi_ActorDialogDelay(sld, pchar, "", 1.0);
	for (int i=1; i<=3; i++)
	{
		sld = CharacterFromID("Mtr_CartahenaWomen_"+i);
		LAi_SetActorType(sld);
	}
}

void Mtraxx_CartahenaToFort() // в форт
{
	// выход из резиденции
	pchar.quest.mtraxx_cartahena_tofort.win_condition.l1 = "locator";
	pchar.quest.mtraxx_cartahena_tofort.win_condition.l1.location = "Cartahena_Townhall";
	pchar.quest.mtraxx_cartahena_tofort.win_condition.l1.locator_group = "reload";
	pchar.quest.mtraxx_cartahena_tofort.win_condition.l1.locator = "reload1_back";
	pchar.quest.mtraxx_cartahena_tofort.function = "Mtraxx_CartahenaToStreet";
	// на ворота
	pchar.quest.mtraxx_cartahena_tofort1.win_condition.l1 = "locator";
	pchar.quest.mtraxx_cartahena_tofort1.win_condition.l1.location = "Cartahena_Town";
	pchar.quest.mtraxx_cartahena_tofort1.win_condition.l1.locator_group = "reload";
	pchar.quest.mtraxx_cartahena_tofort1.win_condition.l1.locator = "gate_back";
	pchar.quest.mtraxx_cartahena_tofort1.function = "Mtraxx_CartahenaToExittown";
	// на вход в форт
	pchar.quest.mtraxx_cartahena_tofort2.win_condition.l1 = "locator";
	pchar.quest.mtraxx_cartahena_tofort2.win_condition.l1.location = "Cartahena_Exittown";
	pchar.quest.mtraxx_cartahena_tofort2.win_condition.l1.locator_group = "reload";
	pchar.quest.mtraxx_cartahena_tofort2.win_condition.l1.locator = "reload3_back";
	pchar.quest.mtraxx_cartahena_tofort2.function = "Mtraxx_CartahenaGoFort";
	LocatorReloadEnterDisable("Cartahena_Exittown", "reload3_back", true);
	sld = CharacterFromID("Pelly");
	LAi_SetActorType(sld);
	LAi_ActorFollowEverywhere(sld, "", -1);
}

void Mtraxx_CartahenaToStreet(string qName) // перегруз на улицы
{
	DoQuestReloadToLocation("Cartahena_Town", "reload", "reload3", "Mtraxx_CartahenaStreet");
}

void Mtraxx_CartahenaToExittown(string qName) // перегруз за ворота
{
	DoQuestReloadToLocation("Cartahena_Exittown", "reload", "reload4", "");
}

void Mtraxx_CartahenaGoFort(string qName) // перегруз в форт
{
	DoQuestReloadToLocation("Cartahena_fort", "reload", "reload1", "Mtraxx_CartahenaTerraxInFort");
}

void Mtraxx_CartahenaFinal() // завершаем квест, грузим остатки команды кораблей
{
	pchar.ship.crew.quantity = GetMinCrewQuantity(pchar)+sti(pchar.questTemp.Mtraxx.Cartahena.AliveCrew1);
	sld = CharacterFromID("Terrax");
    RemoveCharacterEquip(sld, GUN_ITEM_TYPE); 
    RemoveCharacterEquip(sld, TALISMAN_ITEM_TYPE);
    TakeItemFromCharacter(sld, "talisman3");        // belamour уберем остатки роскоши
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", 10.0);
	sld.ship.crew.quantity = GetMinCrewQuantity(characterFromId("Terrax"))+sti(pchar.questTemp.Mtraxx.Cartahena.AliveCrew2);
	sld = CharacterFromID("Jeffry");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", 10.0);
	sld.ship.crew.quantity = GetMinCrewQuantity(characterFromId("Jeffry"))+sti(pchar.questTemp.Mtraxx.Cartahena.AliveCrew3);
	sld = CharacterFromID("Pelly");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", 10.0);
	sld.ship.crew.quantity = GetMinCrewQuantity(characterFromId("Pelly"))+sti(pchar.questTemp.Mtraxx.Cartahena.AliveCrew4);
	sld = CharacterFromID("Mtr_Vensan");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", 10.0);
	sld.ship.crew.quantity = GetCrewQuantity(sld)-30;
	sld = CharacterFromID("Lepricon");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", 10.0);
	DoQuestFunctionDelay("Mtraxx_CartahenaReloadComplete", 11.0);
}

void Mtraxx_CartahenaReloadComplete(string qName) // перегруз на пирс
{
	DoQuestReloadToLocation("Cartahena_town", "quest", "quest1", "Mtraxx_CartahenaComplete");
}

void Mtraxx_CartahenaShipsGoAway(string qName) // вышли в море у Картахены // 3 прогона
{
	Group_FindOrCreateGroup("Terrax_SeaGroup");
	Group_AddCharacter("Terrax_SeaGroup", "Terrax");
	Group_AddCharacter("Terrax_SeaGroup", "Jeffry");
	Group_AddCharacter("Terrax_SeaGroup", "Pelly");
	Group_AddCharacter("Terrax_SeaGroup", "Mtr_Vensan");
	Group_SetGroupCommander("Terrax_SeaGroup", "Terrax");
	Group_SetTaskRunAway("Terrax_SeaGroup", PLAYER_GROUP);
	Group_SetAddress("Terrax_SeaGroup", "Cartahena", "quest_ships", "quest_ship_6");
	Group_LockTask("Terrax_SeaGroup");
	pchar.quest.mtraxx_cartahena_clear.win_condition.l1 = "MapEnter";
	pchar.quest.mtraxx_cartahena_clear.function = "Mtraxx_CartahenaClear";
	pchar.quest.mtraxx_cartahena_tortuga.win_condition.l1 = "location";
	pchar.quest.mtraxx_cartahena_tortuga.win_condition.l1.location = "Tortuga_town";
	pchar.quest.mtraxx_cartahena_tortuga.function = "Mtraxx_RetributionStart";
	int n = sti(pchar.questTemp.Mtraxx.Cartahena.TownCrew);
	for (int i=1; i<=n; i++)
	{
		if (GetCharacterIndex("Mtr_CartahenaTownPirate_"+i) != -1)
		{
			sld = CharacterFromID("Mtr_CartahenaTownPirate_"+i);
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld.lifeday = 0;
		}
	}
	Achievment_Set("ach_58");
}

void Mtraxx_CartahenaClear(string qName) // чистим все запреты
{
	log_testinfo("Картахена восстановлена");
	DeleteAttribute(pchar, "GenQuest.HunterLongPause");
	pchar.quest.mtraxx_ship_fail1.over = "yes";
	SetFunctionTimerCondition("Mtraxx_CartahenaNormal", 0, 0, 7, false); // таймер на восстановление Картахены
	Group_SetAddress("Terrax_SeaGroup", "Hispaniola1", "quest_ships", "quest_ship_4"); // 3 прогона
	Group_DeleteGroup("Terrax_SeaGroup");
	DeleteAttribute(pchar, "GenQuest.CannotWait");
	LAi_LocationDisableOfficersGen("shore25", false);
	LocatorReloadEnterDisable("shore25", "reload1_back", false);
	DeleteAttribute(pchar, "DisableChangeFlagMode");
	pchar.worldmapencountersoff = "0";
	int i = FindColony("Cartahena");
	DeleteAttribute(colonies[i], "DontSetShipInPort");
	DeleteAttribute(&locations[FindLocation("Cartahena_Town")], "QuestCapture");
	DeleteAttribute(&locations[FindLocation("Cartahena_fort")], "QuestCapture");
	for (i=3; i<=10; i++)
	{
		LocatorReloadEnterDisable("Cartahena_town", "reload"+i+"_back", false);
	}
	LocatorReloadEnterDisable("Cartahena_town", "gate_back", false);
	LocatorReloadEnterDisable("Cartahena_town", "reload_jail", false);
	LAi_LocationFightDisable(&Locations[FindLocation("Cartahena_fort")], false);
	LAi_LocationFightDisable(&Locations[FindLocation("Cartahena_town")], false);
	LAi_LocationFightDisable(&Locations[FindLocation("Cartahena_townhall")], false);
	LAi_LocationDisableOfficersGen("Cartahena_townhall", false);
	sld = CharacterFromID("Cartahena_Mayor");
	ChangeCharacterAddressGroup(sld, "Cartahena_townhall", "sit", "sit1");
	sld = CharacterFromID("Mtr_CartahenaMayorClone");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	sld.lifeday = 0; // патч 17/1
	// вертаем нищеброда
	sld = characterFromId("Cartahena_Poorman");
	ChangeCharacterAddressGroup(sld, "Cartahena_town", "goto", "goto5");
	// НЗГ
	ChangeCharacterComplexReputation(pchar, "nobility", -30);
	ChangeCharacterComplexReputation(pchar, "authority", 10);
	ChangeCharacterComplexReputation(pchar, "fame", 10);
	OfficersReaction("bad");
	OfficersReaction("bad");
	OfficersReaction("bad");
	ChangeCharacterHunterScore(PChar, "spahunter", 40);
	AddComplexSelfExpToScill(200, 200, 200, 200);
	AddCharacterExpToSkill(pchar, "Fortune", 300);
}

void Mtraxx_CartahenaNormal(string qName) // восстанавливаем Картахену в норму
{
	sld = CharacterFromID("Cartahena Fort Commander");
	Character_SetAbordageEnable(sld, true); 
	Island_SetReloadEnableGlobal("Cartahena", true);
}

// Эпизод 10. Длань Немезиды
void Mtraxx_RetributionStart(string qName) // прибыл на Тортугу
{
	chrDisableReloadToLocation = true;
	LAi_SetActorType(pchar);
	LAi_ActorRunToLocator(pchar, "reload", "reload9_back", "Mtraxx_RetributionStart", -1);
}

void Mtraxx_RetributionInBrothel() // релоад в комнату
{
	chrDisableReloadToLocation = true;
	LAi_SetActorType(pchar);
	DoQuestReloadToLocation("Tortuga_Brothel_room", "sit", "sit1", "Mtraxx_RetributionInBrothel");
}

void Mtraxx_RetributionToTavern(string qName) // релоад в таверну
{
	DoQuestReloadToLocation("Tortuga_tavern", "reload", "reload1", "");
}

void Mtraxx_RetributionToRoom(string qName) // релоад в комнату
{
	DoQuestReloadToLocation("Tortuga_tavern_upstairs", "quest", "quest4", "Mtraxx_RetributionToRoom");
	DeleteAttribute(pchar, "GenQuest.CamShuttle");
}

void Mtraxx_RetributionOutRoom() // Камилла уходит
{
	chrDisableReloadToLocation = true; // прогон 4
	sld = characterFromId("Kamilla");
	sld.dialog.currentnode = "camilla_27";
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload1", "Tortuga_church", "goto", "goto1", "Mtraxx_RetributionKamilla", 3.0);
	LAi_SetLoginTime(sld, 10.0, 13.0);
	AddQuestRecord("Roger_10", "1");
	CloseQuestHeader("Roger_9");
	pchar.questTemp.Mtraxx.Retribution = "map";
}

void Mtraxx_RetributionCarataska(string qName) // прибыли в лагуну Каратаска // 3 прогона
{
	bDisableLandEncounters = true;
	pchar.GenQuest.HunterLongPause = true;
	bQuestDisableMapEnter = true;//закрыть карту
	pchar.GenQuest.MapClosedNoBattle = true;
	AddQuestRecord("Roger_10", "3");
	pchar.quest.mtraxx_retribution_barricade.win_condition.l1 = "locator";
	pchar.quest.mtraxx_retribution_barricade.win_condition.l1.location = "Carataska_jungle_02";
	pchar.quest.mtraxx_retribution_barricade.win_condition.l1.locator_group = "quest";
	pchar.quest.mtraxx_retribution_barricade.win_condition.l1.locator = "deadfall";
	pchar.quest.mtraxx_retribution_barricade.function = "Mtraxx_RetributionBarricade";
	Mtraxx_RetributionSetRanditems();// укладываем предметы в рандитемы подземелий
	// запрещаем офицеров
	//LAi_LocationDisableOfficersGen("Shore10", true);
	//LAi_LocationDisableOfficersGen("Carataska_jungle_01", true);
	//LAi_LocationDisableOfficersGen("Carataska_jungle_02", true);
	//LAi_LocationDisableOfficersGen("Carataska_jungle_03", true);
	//LAi_LocationDisableOfficersGen("Carataska_CaveEntrance", true);
	//LAi_LocationDisableOfficersGen("Carataska_Cave", true);
	//LAi_LocationDisableOfficersGen("Ruins", true);
	for (i=1; i<=7; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Mtraxx_Sailor_"+i, "citiz_"+(30+i), "man", "man", sti(pchar.rank), sti(pchar.nation), -1, false, "soldier"));
		FantomMakeCoolFighter(sld, sti(pchar.rank), 40, 40, "blade_14", "pistol1", "bullet", 30);
		LAi_CharacterDisableDialog(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto6");
		LAi_SetActorType(sld);
		LAi_ActorFollowEverywhere(sld, "", -1);
	}
}

void Mtraxx_RetributionSetRanditems() // укладываем предметы в рандитемы подземелий
{
	pchar.GenQuestRandItem.Judgement_dungeon_01 = true;
	pchar.GenQuestRandItem.Judgement_dungeon_01.randitem1 = Mtraxx_RetributionSelectRanditem();
	pchar.GenQuestRandItem.Judgement_dungeon_03 = true;
	pchar.GenQuestRandItem.Judgement_dungeon_03.randitem1 = Mtraxx_RetributionSelectRanditem();
	pchar.GenQuestRandItem.Judgement_dungeon_03.randitem2 = Mtraxx_RetributionSelectRanditem();
	pchar.GenQuestRandItem.Judgement_dungeon_03.randitem3 = Mtraxx_RetributionSelectRanditem();
	pchar.GenQuestRandItem.Judgement_dungeon_03.randitem4 = Mtraxx_RetributionSelectRanditem();
	pchar.GenQuestRandItem.Judgement_dungeon_04 = true;
	pchar.GenQuestRandItem.Judgement_dungeon_04.randitem1 = Mtraxx_RetributionSelectRanditem();
	pchar.GenQuestRandItem.Judgement_dungeon_04.randitem2 = Mtraxx_RetributionSelectRanditem();
	pchar.GenQuestRandItem.Judgement_dungeon_04.randitem3 = Mtraxx_RetributionSelectRanditem();
	pchar.GenQuestRandItem.Judgement_dungeon_04.randitem4 = Mtraxx_RetributionSelectRanditem();
	pchar.GenQuestRandItem.Judgement_dungeon_04.randitem5 = Mtraxx_RetributionSelectRanditem();
	pchar.GenQuestRandItem.Judgement_dungeon_04.randitem6 = Mtraxx_RetributionSelectRanditem();
	pchar.GenQuestRandItem.Judgement_dungeon_05 = true;
	pchar.GenQuestRandItem.Judgement_dungeon_05.randitem1 = Mtraxx_RetributionSelectRanditem();
	pchar.GenQuestRandItem.Judgement_dungeon_06 = true;
	pchar.GenQuestRandItem.Judgement_dungeon_06.randitem1 = Mtraxx_RetributionSelectRanditem();
	pchar.GenQuestRandItem.Judgement_dungeon_06.randitem2 = Mtraxx_RetributionSelectRanditem();
	pchar.GenQuestRandItem.Judgement_dungeon_06.randitem3 = Mtraxx_RetributionSelectRanditem();
	pchar.GenQuestRandItem.Judgement_dungeon_09 = true;
	pchar.GenQuestRandItem.Judgement_dungeon_09.randitem1 = Mtraxx_RetributionSelectRanditem();
	pchar.GenQuestRandItem.Judgement_dungeon_09.randitem2 = Mtraxx_RetributionSelectRanditem();
}

void Mtraxx_RetributionBarricade(string qName) // уперлись в завал
{
	AddQuestRecord("Roger_10", "4");
	pchar.quest.mtraxx_retribution_carataska.win_condition.l1 = "location";
	pchar.quest.mtraxx_retribution_carataska.win_condition.l1.location = "shore10";
	pchar.quest.mtraxx_retribution_carataska.function = "Mtraxx_RetributionPowder";
	pchar.questTemp.Mtraxx.Retribution.Powder = "true";
}

void Mtraxx_RetributionPowder(string qName) // на корабль за порохом
{
	chrDisableReloadToLocation = true;
	DoQuestCheckDelay("TalkSelf_Quest", 3.0);
}

void Mtraxx_RetributionBarrels() // доставка бочонков
{
	SetLaunchFrameFormParam(StringFromKey("Roger_102", NewStr()), "Mtraxx_RetributionBarrels", 0, 5);//табличка
	WaitDate("", 0, 0, 1, 2, 10); //крутим время
	LaunchFrameForm();
	RefreshLandTime();
	RecalculateJumpTable();
	Whr_UpdateWeather();
	int n = Findlocation("Carataska_jungle_02");
	string sTemp;
	for (int i=1; i<=3; i++)
	{
		sTemp = "Barrel"+i;
		locations[n].models.always.(sTemp) = "Barrel";
		Locations[n].models.always.(sTemp).locator.group = "quest";
		Locations[n].models.always.(sTemp).locator.name = "barrel"+i;
		Locations[n].models.always.(sTemp).tech = "DLightModel";
	}
	RemoveCharacterGoods(pchar, GOOD_POWDER, 300);
	pchar.questTemp.Mtraxx.Retribution = "ruins";
}

void Mtraxx_RetributionBurn()
{
	LAi_SetActorType(pchar);
	LAi_FadeLong("", "");
	for (i=1; i<=7; i++)
	{
		sld = CharacterFromID("Mtraxx_Sailor_"+i);
		ChangeCharacterAddressGroup(sld, "none", "", "");
	}
	DoQuestFunctionDelay("Mtraxx_RetributionBurn_2", 1.0);
}

void Mtraxx_RetributionBurn_2(string qName) // поджечь фитиль!
{
	StartQuestMovie(true, false, true);
	locCameraFromToPos(-23.54, 1.21, -54.04, true, -25.12, -2.90, -58.92);
	TeleportCharacterToPosAy(pchar, -26.19, -2.96, -60.12, 0.60);
	DeleteAttribute(pchar, "questTemp.Mtraxx.Retribution.Fire");
	LAi_SetActorType(pchar);
	LAi_ActorAnimation(pchar, "Barman_idle", "", 4.0);
	for (int i=1; i<=3; i++)
	{
		CreateLocationParticles("smoke", "quest", "barrel"+i, 0, 0, 0, "");
	}
	DoQuestFunctionDelay("Mtraxx_RetributionRunAway_1", 4.0);
}

void Mtraxx_RetributionRunAway_1(string qName)
{
	LAi_FadeToBlackStart();
	DoQuestFunctionDelay("Mtraxx_RetributionRunAway_2", 1.0);
}

void Mtraxx_RetributionRunAway_2(string qName) // бежим!
{
	locCameraFlyToPositionLookToHero(-26.42, -1.43, -62.00, -30.26, -2.5, -87.83, 0.001850*GetDeltaTime(), -1);
	Pchar.FuncCameraFly = "";
	LAi_SetActorType(pchar);
	LAi_ActorGoToLocator(pchar, "rld", "aloc21", "", -1);
	DoQuestFunctionDelay("Mtraxx_RetributionRunAway_3", 1.5);
	DoQuestFunctionDelay("Mtraxx_RetributionJungleBoom", 5.0);
}

void Mtraxx_RetributionRunAway_3(string qName)
{
	LAi_FadeToBlackEnd();
}

void Mtraxx_RetributionJungleBoom(string qName) // большой бабах
{
	for (int i=1; i<=3; i++)
	{
		CreateLocationParticles("large_smoke", "quest", "barrel"+i, 0, 0, 0, "");
		CreateLocationParticles("ShipExplode", "quest", "barrel"+i, 1.0, 0, 0, "");
		CreateLocationParticles("blast_inv", "quest", "barrel"+i, 1.0, 0, 0, "");
		CreateLocationParticles("blast_dirt", "quest", "barrel"+i, 1.0, 0, 0, "");
	}
	CreateLocationParticles("large_smoke", "quest", "deadfall", 0, 0, 0, "");
	CreateLocationParticles("ShipExplode", "quest", "deadfall", 1.0, 0, 0, "");
	CreateLocationParticles("blast_inv", "quest", "deadfall", 1.0, 0, 0, "");
	CreateLocationParticles("blast_dirt", "quest", "deadfall", 1.0, 0, 0, "");
	PlaySound("Sea Battles\Vzriv_fort_001.wav");
	PlaySound("Sea Battles\vzriv_pogreb_002.wav");
	//PlaySound("Sea Battles\vzriv_pogreb_002.wav");
	for (i=1; i<=3; i++)
	{
		int idx = GetOfficersIndex(pchar, i);
		if (idx < 1) continue;
		sld = &Characters[idx];
		if (sld.location.locator == "detector1") LAi_KillCharacter(sld);
	}
	DoQuestFunctionDelay("Mtraxx_RetributionJungleBoomReload", 1.00);
}

void Mtraxx_RetributionJungleBoomReload(string qName) // перегруз
{
	EndQuestMovie();
	locCameraResetState();
	LAi_SetPlayerType(pchar);
	DoQuestReloadToLocation("Carataska_jungle_02", "goto", "goto7", "Mtraxx_RetributionGotoRuins");
	int n = Findlocation("Carataska_jungle_02");
	for (int i=1; i<=3; i++)
	{
		DeleteAttribute(&locations[n], "models.always.Barrel"+i);
	}
	DeleteAttribute(&locations[n], "models.always.deadfall");
	locations[n].locators_radius.reload.reload2_back = 2.0;
}

void Mtraxx_RetributionRuins(string qName) // вошли в подземелья правосудия
{
	RemoveItems(pchar, "mapEnrico", 1);
	pchar.GenQuest.CannotWait = true;
	AddQuestRecord("Roger_10", "6");
	QuestPointerToLoc("Judgement_dungeon_01", "reload", "reload2_back");
	QuestPointerToLoc("Judgement_dungeon_02", "reload", "reload2");
	QuestPointerToLoc("Judgement_dungeon_03", "reload", "reload2");
	QuestPointerToLoc("Judgement_dungeon_04", "reload", "reload2");
	QuestPointerToLoc("Judgement_dungeon_05", "quest", "pelly");
	// ставим Тесака и его приспешников у клетки с сокровищами
	LAi_LocationFightDisable(&Locations[FindLocation("Judgement_dungeon_05")], true);//запретить драться
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+3;
	int iScl = 30 + 2*sti(pchar.rank);
	sld = characterFromId("Pelly");
	sld.dialog.currentnode = "Pelly_30";
	sld.greeting = "";
	LAi_CharacterEnableDialog(sld);
	LAi_SetImmortal(sld, false);
	LAi_RemoveCheckMinHP(sld); // Addon 2016-1 Jason пиратская линейка 1
	LAi_SetCurHPMax(sld);
	ChangeCharacterAddressGroup(sld, "Judgement_dungeon_05", "quest", "pelly");
	LAi_SetGuardianType(sld);
	sld.protector = true;
	if (MOD_SKILL_ENEMY_RATE > 2)
	{
		sld.MultiFighter = 1.0+stf(MOD_SKILL_ENEMY_RATE/10);
		sld.MultiShooter = 1.0+stf(MOD_SKILL_ENEMY_RATE/10);
	}
	// предметы-призы
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	RemoveItems(sld, "potion2", GetCharacterItem(sld, "potion2"));
	RemoveItems(sld, "potion3", GetCharacterItem(sld, "potion3"));
	TakeNItems(sld, "potion2", makeint(MOD_SKILL_ENEMY_RATE/2));
	TakeNItems(sld, "potion3", 2);
	TakeNItems(sld, "totem_02", 1);
	TakeNItems(sld, "obereg_5", 1);
	TakeNItems(sld, "indian_4", 1);
	for (int i=1; i<=4; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Pelly_PirateDung_"+i, "citiz_4"+i, "man", "man", iRank, PIRATE, -1, false, "soldier"));
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, LinkRandPhrase("blade_04","blade_06","blade_06"), "pistol1", "bullet", 50);
		if (MOD_SKILL_ENEMY_RATE > 4) sld.cirassId = Items_FindItemIdx("cirass2");
		ChangeCharacterAddressGroup(sld, "Judgement_dungeon_05", "quest", "quest"+i);
		LAi_SetStayType(sld);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		LAi_CharacterDisableDialog(sld);
		if (MOD_SKILL_ENEMY_RATE > 4)
		{
			sld.MultiFighter = 1.0+stf(MOD_SKILL_ENEMY_RATE/20);
			sld.MultiShooter = 1.0+stf(MOD_SKILL_ENEMY_RATE/20);
		}
	}
}

void Mtraxx_RetributionPellyFight(string qName) // бой с Тесаком
{
	LAi_LocationFightDisable(&Locations[FindLocation("Judgement_dungeon_05")], false);
	chrDisableReloadToLocation = true;
	LAi_group_Delete("EnemyFight");
	sld = characterFromId("Pelly");
	if (MOD_SKILL_ENEMY_RATE <= 4) LAi_SetHP(sld, 250, 250);
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	for (int i=1; i<=4; i++)
	{
		sld = characterFromId("Pelly_PirateDung_"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "Mtraxx_RetributionPellyAfterFight");
}

void Mtraxx_RetributionSetJeffry(string qName) // ставим Джеффри в шахту №2
{
	LAi_LocationFightDisable(&Locations[FindLocation("Judgement_dungeon_03")], true);//запретить драться
	chrDisableReloadToLocation = true;
	// ставим Джеффри и его пиратов
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE;
	int iScl = 10 + sti(pchar.rank);
	sld = characterFromId("Jeffry");
	sld.dialog.currentnode = "Jeffry_22";
	LAi_CharacterEnableDialog(sld);
	LAi_SetImmortal(sld, false);
	LAi_RemoveCheckMinHP(sld); // Addon 2016-1 Jason пиратская линейка 1
	LAi_SetCurHPMax(sld);
	ChangeCharacterAddressGroup(sld, "Judgement_dungeon_03", "quest", "jeffry");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	if (MOD_SKILL_ENEMY_RATE > 6)
	{
		sld.MultiFighter = 1.0+stf(MOD_SKILL_ENEMY_RATE/10);
		sld.MultiShooter = 1.0+stf(MOD_SKILL_ENEMY_RATE/10);
	}
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	sld.money = 10400;
	RemoveItems(sld, "potion2", GetCharacterItem(sld, "potion2"));
	RemoveItems(sld, "potion3", GetCharacterItem(sld, "potion3"));
	TakeNItems(sld, "potion2", makeint(MOD_SKILL_ENEMY_RATE/2));
	TakeNItems(sld, "potion3", 2);
	TakeNItems(sld, "totem_12", 1);
	TakeNItems(sld, "indian_1", 1);
	TakeNItems(sld, "amulet_1", 1);
	for (int i=1; i<=4; i++)
	{
		if (i < 4)
		{
			sld = GetCharacter(NPC_GenerateCharacter("Jeffry_PirateDung_"+i, "citiz_4"+(i+4), "man", "man", iRank, PIRATE, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, LinkRandPhrase("blade_04","blade_10","blade_13"), "pistol1", "bullet", 50);
			if (MOD_SKILL_ENEMY_RATE > 6) sld.cirassId = Items_FindItemIdx("cirass2");
		}
		else
		{
			sld = GetCharacter(NPC_GenerateCharacter("Jeffry_PirateDung_"+i, "mush_ctz_9", "man", "mushketer", iRank, PIRATE, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl+5, iScl+5, "", "mushket2", "bullet", 50);
			LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "bullet");
			sld.cirassId = Items_FindItemIdx("cirass1");
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
		}
		ChangeCharacterAddressGroup(sld, "Judgement_dungeon_03", "quest", "quest1");
		LAi_SetStayType(sld);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		LAi_CharacterDisableDialog(sld);
		if (MOD_SKILL_ENEMY_RATE > 6)
		{
			sld.MultiFighter = 1.0+stf(MOD_SKILL_ENEMY_RATE/20);
			sld.MultiShooter = 1.0+stf(MOD_SKILL_ENEMY_RATE/20);
		}
	}
}

void Mtraxx_RetributionWithJeffry(string qName) // вместе с Джеффри к сокровищам
{
	chrDisableReloadToLocation = false;
	sld = characterFromId("Jeffry");
	LAi_SetActorType(sld);
	LAi_ActorFollowEverywhere(sld, "", -1);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	for (int i=1; i<=4; i++)
	{
		sld = characterFromId("Jeffry_PirateDung_"+i);
		LAi_SetActorType(sld);
		LAi_ActorFollowEverywhere(sld, "", -1);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	pchar.quest.mtraxx_retribution_jeffry.win_condition.l1 = "locator";
	pchar.quest.mtraxx_retribution_jeffry.win_condition.l1.location = "Judgement_dungeon_05";
	pchar.quest.mtraxx_retribution_jeffry.win_condition.l1.locator_group = "quest";
	pchar.quest.mtraxx_retribution_jeffry.win_condition.l1.locator = "quest4";
	pchar.quest.mtraxx_retribution_jeffry.function = "Mtraxx_RetributionJeffryTreasure";
	QuestPointerToLoc("Judgement_dungeon_03", "reload", "reload2");
	QuestPointerToLoc("Judgement_dungeon_04", "reload", "reload2");
	QuestPointerToLoc("Judgement_dungeon_05", "quest", "pelly");
}

void Mtraxx_RetributionJeffryTreasure(string qName) // вместе с Джеффри у сокровищ
{
	InterfaceStates.Buttons.Save.enable = false; // правки релиза
	LAi_SetActorType(pchar);
	LAi_ActorTurnToLocator(pchar, "monster", "monster3");
	sld = characterFromId("Jeffry");
	sld.dialog.currentnode = "Jeffry_32";
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "quest", "pelly", "Mtraxx_RetributionJeffryTreasure", -1);
	sld = characterFromId("Jeffry_PirateDung_4");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocator(sld, "quest", "quest2", "", 10);
	for (int i=1; i<=3; i++)
	{
		sld = characterFromId("Jeffry_PirateDung_"+i);
		LAi_SetActorType(sld);
		LAi_ActorRunToLocator(sld, "monsters", "monster"+(i+16), "", 10);
	}
	QuestPointerDelLoc("Judgement_dungeon_03", "reload", "reload2");
	QuestPointerDelLoc("Judgement_dungeon_04", "reload", "reload2");
	QuestPointerDelLoc("Judgement_dungeon_05", "quest", "pelly");
}

void Mtraxx_RetributionJeffryFight(string qName) // бой с Джеффри
{
	sld = characterFromId("Jeffry_PirateDung_4");
	LAi_GunSetUnload(sld, MUSKET_ITEM_TYPE);
	
	// belamour legendary edition
	LAi_LocationFightDisable(&Locations[FindLocation("Judgement_dungeon_03")], false);
	chrDisableReloadToLocation = true;
	LAi_group_Delete("EnemyFight");
	sld = characterFromId("Jeffry");
	if (MOD_SKILL_ENEMY_RATE <= 4) LAi_SetHP(sld, 250, 250);
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	for (int i=1; i<=4; i++)
	{
		sld = characterFromId("Jeffry_PirateDung_"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "Mtraxx_RetributionJeffryAfterFight");
	LAi_SetFightMode(pchar, true);
	InterfaceStates.Buttons.Save.enable = true; // правки релиза
}

void Mtraxx_RetributionMushketers(string qName) // ставим 2 мушкетеров в шахте №3
{
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+3;
	int iScl = 30 + 2*sti(pchar.rank);
	chrDisableReloadToLocation = true;
	LAi_group_Delete("EnemyFight");
	for (int i=1; i<=2; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Mushketer1_PirateDung_"+i, "mush_ctz_"+(6+i), "man", "mushketer", iRank, PIRATE, -1, false, "soldier"));
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "bullet", 50);
		LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "bullet");
		sld.MusketerDistance = 0;
		if (MOD_SKILL_ENEMY_RATE > 4) sld.cirassId = Items_FindItemIdx("cirass1");
		ChangeCharacterAddressGroup(sld, "Judgement_dungeon_04", "quest", "mushketer"+i);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "Mtraxx_RetributionMushAfterFight");
}

void Mtraxx_RetributionNextMushketers(string qName) // ставим 2 мушкетеров в шахте №2
{
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+3;
	int iScl = 30 + 2*sti(pchar.rank);
	chrDisableReloadToLocation = true;
	LAi_group_Delete("EnemyFight");
	for (int i=1; i<=2; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Mushketer2_PirateDung_"+i, "mush_ctz_"+i, "man", "mushketer", iRank, PIRATE, -1, false, "soldier"));
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "bullet", iScl*3);
		LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "bullet");
		sld.MusketerDistance = 0;
		if (MOD_SKILL_ENEMY_RATE > 4) sld.cirassId = Items_FindItemIdx("cirass1");
		ChangeCharacterAddressGroup(sld, "Judgement_dungeon_03", "quest", "mushketer"+i);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "Mtraxx_RetributionNextMushAfterFight");
}

void Mtraxx_RetributionLastMushketers(string qName) // ставим 2 мушкетеров в шахте №1
{
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+5;
	int iScl = 35 + 2*sti(pchar.rank);
	chrDisableReloadToLocation = true;
	LAi_group_Delete("EnemyFight");
	for (int i=1; i<=2; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Mushketer3_PirateDung_"+i, "mush_ctz_"+i, "man", "mushketer", iRank, PIRATE, -1, false, "soldier"));
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket2", "bullet", iScl*3);
		LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "bullet");
		sld.MusketerDistance = 0;
		if (MOD_SKILL_ENEMY_RATE > 2) sld.cirassId = Items_FindItemIdx("cirass1");
		ChangeCharacterAddressGroup(sld, "Judgement_dungeon_02", "quest", "mushketer"+i);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "Mtraxx_RetributionLastMushAfterFight");
}

void Mtraxx_RetributionSetLepricon(string qName) // ставим Леприкона // прогона 3
{
	LAi_LocationFightDisable(&Locations[FindLocation("Judgement_dungeon_01")], true);//запретить драться
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+5;
	int iScl = 30 + 2*sti(pchar.rank);
	sld = characterFromId("Lepricon");
	sld.dialog.currentnode = "lepricon_13";
	sld.greeting = "";
	LAi_CharacterEnableDialog(sld);
	LAi_SetImmortal(sld, false);
	LAi_RemoveCheckMinHP(sld); // Addon 2016-1 Jason пиратская линейка 1
	LAi_SetCurHPMax(sld);
	ChangeCharacterAddressGroup(sld, "Judgement_dungeon_01", "quest", "lepricon");
	LAi_SetGuardianType(sld);
	sld.protector = true;
	sld.protector.CheckAlways = 1;//всегда проверять
	sld.viper = true;
	if (MOD_SKILL_ENEMY_RATE > 2)
	{
		sld.MultiFighter = 1.0+stf(MOD_SKILL_ENEMY_RATE/10);
		sld.MultiShooter = 1.0+stf(MOD_SKILL_ENEMY_RATE/10);
	}
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	sld.money = 2900;
	RemoveItems(sld, "potion2", GetCharacterItem(sld, "potion2"));
	RemoveItems(sld, "potion3", GetCharacterItem(sld, "potion3"));
	TakeNItems(sld, "potion2", makeint(MOD_SKILL_ENEMY_RATE/2));
	TakeNItems(sld, "potion3", 2);
	if (MOD_SKILL_ENEMY_RATE > 4) TakeNItems(sld, "potion4", 2);
	TakeNItems(sld, "purse3", 1);
	TakeNItems(sld, "map_beliz", 1);
	TakeNItems(sld, "cannabis7", 3);
	TakeNItems(sld, "indian_poison", 1); // яд таино
	for (int i=5; i<=7; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Lepricon_PirateDung_"+i, "mercen_"+i, "man", "man", iRank, PIRATE, -1, false, "soldier"));
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, LinkRandPhrase("topor_04","blade_04","topor_02"), "pistol3", "grapeshot", 50);
		if (MOD_SKILL_ENEMY_RATE > 2) sld.cirassId = Items_FindItemIdx("cirass2");
		ChangeCharacterAddressGroup(sld, "Judgement_dungeon_01", "quest", "quest"+i);
		LAi_SetStayType(sld);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		LAi_CharacterDisableDialog(sld);
		if (MOD_SKILL_ENEMY_RATE > 4)
		{
			sld.MultiFighter = 1.0+stf(MOD_SKILL_ENEMY_RATE/20);
			sld.MultiShooter = 1.0+stf(MOD_SKILL_ENEMY_RATE/20);
		}
		if (MOD_SKILL_ENEMY_RATE > 6) sld.viper = true;
	}
}

void Mtraxx_RetributionLepriconFight() // бой с Леприконом
{
	LAi_LocationFightDisable(&Locations[FindLocation("Judgement_dungeon_01")], false);
	chrDisableReloadToLocation = true;
	LAi_group_Delete("EnemyFight");
	sld = characterFromId("Lepricon");
	if (MOD_SKILL_ENEMY_RATE <= 4) LAi_SetHP(sld, 250, 250);
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	for (int i=5; i<=7; i++)
	{
		sld = characterFromId("Lepricon_PirateDung_"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "Mtraxx_RetributionLepriconAfterFight");
	LAi_SetFightMode(pchar, true);
}

void Mtraxx_RetributionExitClosed(string qName) // выход закрыт
{
	PlaySound("interface\Door_Kick.wav");
	DoQuestCheckDelay("TalkSelf_Quest", 0.5);
}

void Mtraxx_RetributionRunToEnrico() // бежим на встречу к Энрико
{
	QuestPointerDelLoc("Judgement_dungeon_01", "reload", "reload1");
	LAi_SetActorType(pchar);
	LAi_ActorRunToLocator(pchar, "quest", "enrico", "Mtraxx_RetributionCreateEnrico", -1);
}

void Mtraxx_RetributionEnricoGo() // Энрико уходит
{
	LAi_SetActorType(pchar);
	sld = characterFromId("Zorro");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "monsters", "monster5", "none", "", "", "Mtraxx_RetributionEnricoGo", 10.0);
}

void Mtraxx_RetributionTwoHoursTime(string qName) // перемотка времени по 2 часа
{
	WaitDate("", 0, 0, 0, 2, rand(30)); //крутим время
	LaunchFrameForm();
	RefreshLandTime();
	RecalculateJumpTable();
	Whr_UpdateWeather();
}

void Mtraxx_RetributionInChurchRuins(string qName) // пришёл в разрушенную церковь
{
	chrDisableReloadToLocation = true;
	DoQuestFunctionDelay("Mtraxx_RetributionChurchLock", 7.0);
}

void Mtraxx_RetributionChurchLock(string qName) // скриптовая сцена закрытых дверей
{
	LAi_SetActorType(pchar);
	LAi_ActorGoToLocator(pchar, "quest", "LLquest2", "Mtraxx_RetributionChurchLock", -1);
}

void Mtraxx_RetributionBead(string qName) // молитва 
{
	StartQuestMovie(true, false, true);
	locCameraFromToPos(-0.04, 1.32, -6.74, true, -2.27, 0.47, -6.30);
	LAi_SetActorType(pchar);
	LAi_ActorGoToLocator(pchar, "quest", "LLquest9", "Mtraxx_RetributionBead", -1);
}

void Mtraxx_RetributionSleep(string qName) // заснул - снится Мерида 
{
	int n = Findlocation("Merida_town");
	locations[n].alwaysStorm = true;
	locations[n].Storm = true;
	LAi_LocationDisableOfficersGen("Merida_town", true);
	DoQuestReloadToLocation("Merida_town", "quest", "stay1", "Mtraxx_RetributionSleep");
}

void Mtraxx_RetributionSetMusic(string qName) // 
{
	ResetSound();
	SetMusic("music_lyric");
	PlaySound("ambient\church\zvon.wav");
	ChangeShowIntarface();
}

void Mtraxx_RetributionSleepSkeletons() // кошмарики
{
	sld = characterFromId("Sleep_Jeffry");
	sld.model = "skel4";
	Characters_RefreshModel(sld);
	sld = characterFromId("Sleep_Pelly");
	sld.model = "skel1";
	Characters_RefreshModel(sld);
	sld = characterFromId("Sleep_Lepricon");
	sld.model = "skel2";
	Characters_RefreshModel(sld);
}

void Mtraxx_RetributionLocatorRadius() // раздвигаем локатор 
{
	int n = Findlocation("Judgement_church");
	locations[n].locators_radius.reload.reload2_back = 2.0;
	AddQuestRecord("Roger_10", "13");
	pchar.quest.mtraxx_retribution_tohell.win_condition.l1 = "locator";
	pchar.quest.mtraxx_retribution_tohell.win_condition.l1.location = "Judgement_church";
	pchar.quest.mtraxx_retribution_tohell.win_condition.l1.locator_group = "reload";
	pchar.quest.mtraxx_retribution_tohell.win_condition.l1.locator = "reload2_back";
	pchar.quest.mtraxx_retribution_tohell.function = "Mtraxx_RetributionGotoHell";
}

void Mtraxx_RetributionGotoHell(string qName) // можно идти 
{
	RemoveItems(pchar, "key_ruins", 1);
	PlaySound("interface\key.wav");
	pchar.quest.mtraxx_retribution_hell.win_condition.l1 = "locator";
	pchar.quest.mtraxx_retribution_hell.win_condition.l1.location = "Judgement_dungeon_09";
	pchar.quest.mtraxx_retribution_hell.win_condition.l1.locator_group = "item";
	pchar.quest.mtraxx_retribution_hell.win_condition.l1.locator = "detector1";
	pchar.quest.mtraxx_retribution_hell.function = "Mtraxx_RetributionInHell";
	pchar.quest.mtraxx_retribution_incave.win_condition.l1 = "location";
	pchar.quest.mtraxx_retribution_incave.win_condition.l1.location = "Carataska_Cave";
	pchar.quest.mtraxx_retribution_incave.function = "Mtraxx_RetributionHellEscape";
}

void Mtraxx_RetributionInHell(string qName) // в адских туннелях
{
	LAi_SetActorType(pchar);
	PlaySound("ambient\land\cough_01.wav");
	LAi_ActorAnimation(pchar, "recoil", "pchar_back_to_player", 3.0);
	AddQuestRecord("Roger_10", "14");
}

void Mtraxx_RetributionHellHotWater(string qName) // горячая вода
{
	if (!CheckAttribute(pchar, "GenQuest.Hotwater")) return;
	int n = 1;
	if (MOD_SKILL_ENEMY_RATE == 10) n = 2;
	if (pchar.location == "Judgement_dungeon_10") LAi_ApplyCharacterDamage(pchar, n, "other");
	else LAi_ApplyCharacterDamage(pchar, n, "other");
	LAi_CheckKillCharacter(pchar);
	DoQuestFunctionDelay("Mtraxx_RetributionHellHotWaterPause", 0.5);
}

void Mtraxx_RetributionHellHotWaterPause(string qName) // горячая вода
{
	DoQuestFunctionDelay("Mtraxx_RetributionHellHotWater", 0.5);
}

void Mtraxx_RetributionHellSplash(string qName) // гейзеры
{
	if (pchar.location != "Judgement_dungeon_09") return;
	// выбираем группу из 10 локаторов, где одновременно произойдет всплеск
	int n = rand(9)+1;
	int m = rand(9)+11;
	int k = rand(9)+21;
	int l = rand(9)+31;
	int p = rand(9)+41;
	int r = rand(9)+51;
	int s = rand(9)+61;
	int t = rand(9)+71;
	int u = rand(9)+81;
	int v = rand(9)+91;
	string locator1 = "splash"+n;
	string locator2 = "splash"+m;
	string locator3 = "splash"+k;
	string locator4 = "splash"+l;
	string locator5 = "splash"+p;
	string locator6 = "splash"+r;
	string locator7 = "splash"+s;
	string locator8 = "splash"+t;
	string locator9 = "splash"+u;
	string locator10 = "splash"+v;
	pchar.questTemp.Mtraxx.HellSplash.l1 = n;
	pchar.questTemp.Mtraxx.HellSplash.l2 = m;
	pchar.questTemp.Mtraxx.HellSplash.l3 = k;
	pchar.questTemp.Mtraxx.HellSplash.l4 = l;
	pchar.questTemp.Mtraxx.HellSplash.l5 = p;
	pchar.questTemp.Mtraxx.HellSplash.l6 = r;
	pchar.questTemp.Mtraxx.HellSplash.l7 = s;
	pchar.questTemp.Mtraxx.HellSplash.l8 = t;
	pchar.questTemp.Mtraxx.HellSplash.l9 = u;
	pchar.questTemp.Mtraxx.HellSplash.l10 = v;
	CreateLocationParticles("splash", "item", locator1, 1, 0, 0, "jump_water");
	CreateLocationParticles("splash", "item", locator2, 1, 0, 0, "jump_water");
	CreateLocationParticles("splash", "item", locator3, 1, 0, 0, "jump_water");
	CreateLocationParticles("splash", "item", locator4, 1, 0, 0, "jump_water");
	CreateLocationParticles("splash", "item", locator5, 1, 0, 0, "jump_water");
	CreateLocationParticles("splash", "item", locator6, 1, 0, 0, "jump_water");
	CreateLocationParticles("splash", "item", locator7, 1, 0, 0, "jump_water");
	CreateLocationParticles("splash", "item", locator8, 1, 0, 0, "jump_water");
	CreateLocationParticles("splash", "item", locator9, 1, 0, 0, "jump_water");
	CreateLocationParticles("splash", "item", locator10, 1, 0, 0, "jump_water");
	if (MOD_SKILL_ENEMY_RATE == 10) DoQuestFunctionDelay("Mtraxx_RetributionHellSplashPause", 1.3);
	else DoQuestFunctionDelay("Mtraxx_RetributionHellSplashPause", 1.8);
}

void Mtraxx_RetributionHellSplashPause(string qName)
{
	DeleteAttribute(pchar, "questTemp.Mtraxx.HellSplash");
	DoQuestFunctionDelay("Mtraxx_RetributionHellSplash", 0.2);
}

void Mtraxx_RetributionHellSplashReaction() // реакция на гейзер
{
	// belamour legendary edition оберег ловца скрытые свойства
	if(IsEquipCharacterByArtefact(pchar, "talisman10")) return;
	int n = 30;
	if (MOD_SKILL_ENEMY_RATE == 10) n = 80;
	if (pchar.location == "Judgement_dungeon_09") 
	{
		LAi_SetActorType(pchar);
		LAi_ActorAnimation(pchar, "hit_fire", "pchar_back_to_player", 1.8);
	}
	AddCharacterHealth(pchar, -3);
	PlaySound("People\hotwater2.wav");
	LAi_ApplyCharacterDamage(pchar, n, "other");
	LAi_CheckKillCharacter(pchar);
}

void Mtraxx_RetributionHellCough(string qName) // кашляет
{
	if (pchar.location != "Judgement_dungeon_09") return;
	if (!CheckAttribute(pchar, "GenQuest.Hotwater")) return;
	LAi_SetActorType(pchar);
	LAi_ActorAnimation(pchar, "recoil", "pchar_back_to_player", 3.0);
	int i = rand(3)+1;
	PlaySound("ambient\land\cough_0"+i+".wav");
	LAi_ApplyCharacterDamage(pchar, 5, "other");
	LAi_CheckKillCharacter(pchar);	
	DoQuestFunctionDelay("Mtraxx_RetributionHellCoughPause", 4);
}

void Mtraxx_RetributionHellCoughPause(string qName)
{
	int n = rand(5)+3;
	if (MOD_SKILL_ENEMY_RATE == 10) n = rand(4)+1;
	DoQuestFunctionDelay("Mtraxx_RetributionHellCough", n);
}
// гейзеры в подземелье-10, 7 шт
void Mtraxx_RetributionHellSplash1(string qName) // гейзер-1
{
	if (pchar.location != "Judgement_dungeon_10") return;
	pchar.questTemp.Mtraxx.Hell1Splash.l1 = "true";
	CreateLocationParticles("splash", "item", "splash1_2", 1.1, 0, 0, "jump_water");
	DoQuestFunctionDelay("Mtraxx_RetributionHellSplash1Pause", 1.0);
}

void Mtraxx_RetributionHellSplash1Pause(string qName) // 
{
	DeleteAttribute(pchar, "questTemp.Mtraxx.Hell1Splash.l1");
	DoQuestFunctionDelay("Mtraxx_RetributionHellSplash1", 4.0);
}

void Mtraxx_RetributionHellSplash2(string qName) // гейзер-2
{
	if (pchar.location != "Judgement_dungeon_10") return;
	pchar.questTemp.Mtraxx.Hell1Splash.l2 = "true";
	CreateLocationParticles("splash", "item", "splash2_2", 1.1, 0, 0, "jump_water");
	DoQuestFunctionDelay("Mtraxx_RetributionHellSplash2Pause", 1.0);
}

void Mtraxx_RetributionHellSplash2Pause(string qName) // 
{
	DeleteAttribute(pchar, "questTemp.Mtraxx.Hell1Splash.l2");
	DoQuestFunctionDelay("Mtraxx_RetributionHellSplash2", 3.0);
}

void Mtraxx_RetributionHellSplash3(string qName) // гейзер-3
{
	if (pchar.location != "Judgement_dungeon_10") return;
	pchar.questTemp.Mtraxx.Hell1Splash.l3 = "true";
	CreateLocationParticles("splash", "item", "splash3_2", 1.1, 0, 0, "jump_water");
	DoQuestFunctionDelay("Mtraxx_RetributionHellSplash3Pause", 1.0);
}

void Mtraxx_RetributionHellSplash3Pause(string qName) // 
{
	int n = 2 + rand(2);
	DeleteAttribute(pchar, "questTemp.Mtraxx.Hell1Splash.l3");
	DoQuestFunctionDelay("Mtraxx_RetributionHellSplash3", n);
}

void Mtraxx_RetributionHellSplash4(string qName) // гейзер-4
{
	if (pchar.location != "Judgement_dungeon_10") return;
	pchar.questTemp.Mtraxx.Hell1Splash.l4 = "true";
	CreateLocationParticles("splash", "item", "splash4_2", 1.1, 0, 0, "jump_water");
	DoQuestFunctionDelay("Mtraxx_RetributionHellSplash4Pause", 1.0);
}

void Mtraxx_RetributionHellSplash4Pause(string qName) // 
{
	int n = 3+rand(1);
	if (rand(4) == 0) n = 1;
	DeleteAttribute(pchar, "questTemp.Mtraxx.Hell1Splash.l4");
	DoQuestFunctionDelay("Mtraxx_RetributionHellSplash4", n);
}

void Mtraxx_RetributionHellSplash5(string qName) // гейзер-5
{
	if (pchar.location != "Judgement_dungeon_10") return;
	pchar.questTemp.Mtraxx.Hell1Splash.l5 = "true";
	CreateLocationParticles("splash", "item", "splash5_2", 1.1, 0, 0, "jump_water");
	DoQuestFunctionDelay("Mtraxx_RetributionHellSplash5Pause", 1.0);
}

void Mtraxx_RetributionHellSplash5Pause(string qName) // 
{
	int n = 1;
	if (rand(5) == 0) n = 5;
	DeleteAttribute(pchar, "questTemp.Mtraxx.Hell1Splash.l5");
	DoQuestFunctionDelay("Mtraxx_RetributionHellSplash5", n);
}

void Mtraxx_RetributionHellSplash6(string qName) // гейзер-6
{
	if (pchar.location != "Judgement_dungeon_10") return;
	int n = 2+rand(2);
	if (rand(3) == 0) n = 1;
	DeleteAttribute(pchar, "questTemp.Mtraxx.Hell1Splash.l7");
	pchar.questTemp.Mtraxx.Hell1Splash.l6 = "true";
	CreateLocationParticles("splash", "item", "splash6", 1.1, 0, 0, "jump_water");
	DoQuestFunctionDelay("Mtraxx_RetributionHellSplash7", n);
}

void Mtraxx_RetributionHellSplash7(string qName) // гейзер-7
{
	if (pchar.location != "Judgement_dungeon_10") return;
	int n = 2+rand(2);
	if (rand(3) == 1) n = 1;
	DeleteAttribute(pchar, "questTemp.Mtraxx.Hell1Splash.l6");
	pchar.questTemp.Mtraxx.Hell1Splash.l7 = "true";
	CreateLocationParticles("splash", "item", "splash7", 1.1, 0, 0, "jump_water");
	DoQuestFunctionDelay("Mtraxx_RetributionHellSplash6", n);
}

void Mtraxx_RetributionHellSplashStatic(string qName) // статичные гейзеры
{
	if (pchar.location != "Judgement_dungeon_10") return;
	for (int i=1; i<=8; i++) 
	{
		CreateLocationParticles("splash", "item", "fontain"+i, 1.1, 0, 0, "fountsml");
	}
	DoQuestFunctionDelay("Mtraxx_RetributionHellSplashStaticPause", 0.5);
}

void Mtraxx_RetributionHellSplashStaticPause(string qName) // статичные гейзеры
{
	if (pchar.location != "Judgement_dungeon_10") return;
	for (int i=1; i<=8; i++) 
	{
		CreateLocationParticles("splash", "item", "fontain"+i, 1.1, 0, 0, "");
	}
	DoQuestFunctionDelay("Mtraxx_RetributionHellSplashStatic", 0.5);
}

void Mtraxx_RetributionHellEscape(string qName) // выплыл в пещеру
{
	DeleteAttribute(pchar, "GenQuest.Hotwater");
	AddCharacterHealth(pchar, -5);
	AddQuestRecord("Roger_10", "15");
	pchar.quest.mtraxx_retribution_shore.win_condition.l1 = "location";
	pchar.quest.mtraxx_retribution_shore.win_condition.l1.location = "Carataska_jungle_01";
	pchar.quest.mtraxx_retribution_shore.function = "Mtraxx_RetributionJungle";
}

void Mtraxx_RetributionJungle(string qName) // в джунглях
{
	AddQuestRecord("Roger_10", "16");
	pchar.quest.mtraxx_retribution_freedom.win_condition.l1 = "location";
	pchar.quest.mtraxx_retribution_freedom.win_condition.l1.location = "shore10";
	pchar.quest.mtraxx_retribution_freedom.win_condition = "Mtraxx_RetributionSvoboda";
}

void Mtraxx_RetributionComplete(string qName) // линейка пройдена полностью // 3 прогона
{
	bDisableLandEncounters = false;
	DeleteAttribute(pchar, "GenQuest.HunterLongPause");
	CloseQuestHeader("Roger_10");
	pchar.questTemp.Mtraxx = "full_complete";
	AddCharacterHealth(pchar, -20);
	LAi_LocationDisableOfficersGen("Ruins", false);//офицеров пускать
	LAi_LocationDisableOfficersGen("Carataska_jungle_03", false);
	LAi_LocationDisableOfficersGen("Carataska_jungle_02", false);
	LAi_LocationDisableOfficersGen("Carataska_Cave", false);
	LAi_LocationDisableOfficersGen("Carataska_CaveEntrance", false);
	LAi_LocationDisableOfficersGen("Carataska_jungle_01", false);
	LAi_LocationDisableOfficersGen("Shore10", false);
	// Тиракса в резиденцию
	LocatorReloadEnterDisable("LaVega_town", "reload6", false);
	sld = CharacterFromID("Terrax");
	sld.location = "LaVega_townhall";
	sld.location.group = "sit";
	sld.location.locator = "sit1";
	LAi_SetHuberType(sld);
	LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
	sld.dialog.currentnode = "First time";
	sld.Ship.Type = SHIP_NOTUSED;
	LAi_SetImmortal(sld, true);
	// капеллан - второй шанс
	if (CheckAttribute(pchar, "questTemp.ShipCapellan") && !CheckAttribute(pchar, "questTemp.ShipCapellan.Yes"))
	{
		DeleteAttribute(pchar, "questTemp.ShipCapellan");
	}
	DeleteAttribute(pchar, "questTemp.Mtraxx.CharleePrince");
	SetFunctionTimerCondition("DelCharleePrince", 1, 0, 0, false);
}

void DelCharleePrince(string qName) // команда пиратов
{
	if(CheckAttribute(pchar, "questTemp.CharleePrince")) DeleteAttribute(pchar, "questTemp.CharleePrince");
}

void Mtraxx_DelPirateCrew(string qName) // известный пират (падение репутации)
{
	DeleteAttribute(pchar, "questTemp.Mtraxx.CharleePrince");
}

//=================================================================
//======================кейсы из quests_reaction===================
//=================================================================
bool Roger_QuestComplete(string sQuestName, string qname)
{

	ref sld, chr;
	int iTemp, i, n, idx, ShipType, iRank, Rank, iScl, iAddTime, iTime, iClass; 
	string  Model, Blade, sTemp, attrName;
	
	
	bool condition = true;
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Addon 2016-1 Jason Пиратская линейка
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// эпизод 2
	if (sQuestName == "Mtraxx_SilkWrongTalk") // неверный вариант диалога с приемщиками шёлка
	{
		chrDisableReloadToLocation = false;
		AddQuestRecord("Roger_2", "14");
		DeleteAttribute(pchar, "questTemp.Mtraxx.Silkfail");
		Mtraxx_TerraxReset(2);
	}
	else if (sQuestName == "Mtraxx_PlantChestReady") // подготовить сундук
	{
		DoQuestCheckDelay("TalkSelf_Quest", 1.5);
	}
	else if (sQuestName == "Mtraxx_PlantChestReadyExit") // сундук готов
	{
		DeleteAttribute(pchar, "questTemp.Mtraxx.Chest");
		pchar.questTemp.Mtraxx.Ammo = "true";
	}
	else if (sQuestName == "Mtraxx_PlantWaitDay") // 
	{
		DoQuestReloadToLocation("Maracaibo_Plantation", "goto", "goto18", "Mtraxx_PlantTrading");
	}
	else if (sQuestName == "Mtraxx_PlantTrading") // торгуем - обмен товарами
	{
		if (GetSquadronGoods(pchar, sti(pchar.questTemp.Mtraxx.PlantGood.Cargo)) < 500) // не хватило товара на торговлю - провал
		{
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "questTemp.Mtraxx.PlantGood");
			DeleteAttribute(pchar, "questTemp.Mtraxx.Weapon");
			sld = characterFromId("Mtr_plantation_boss");
			sld.lifeday = 0;
			sld = characterFromId("Mrt_Rocur");
			sld.lifeday = 0;
			sld = characterFromId("Mrt_Rocur_clone");
			sld.lifeday = 0;
			AddQuestRecord("Roger_3", "11");
			Mtraxx_PlantPellyClear();
			Mtraxx_TerraxReset(3);
		}
		else 
		{
			RemoveCharacterGoods(pchar, sti(pchar.questTemp.Mtraxx.PlantGood.Cargo), 500);
			SetCharacterGoods(pchar, GOOD_SUGAR, GetCargoGoods(pchar, GOOD_SUGAR) + sti(pchar.questTemp.Mtraxx.PlantGood.Sugar));
			SetCharacterGoods(pchar, GOOD_CHOCOLATE, GetCargoGoods(pchar, GOOD_CHOCOLATE) + sti(pchar.questTemp.Mtraxx.PlantGood.Cocoa));
			DeleteAttribute(pchar, "questTemp.Mtraxx.PlantGood");
			sld = characterFromId("Mtr_plantation_boss");
			sld.dialog.currentnode = "mtraxx_9";
			ChangeCharacterAddressGroup(sld, "Maracaibo_Plantation", "goto", "goto17");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		}
		n = Findlocation("Shore37");
		DeleteAttribute(&locations[n], "models.always.chest");
		Locations[n].models.always.locators = "shore03_locators";
		DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
		AddCharacterExpToSkill(pchar, "Leadership", 200);
		AddCharacterExpToSkill(pchar, "Sneak", 300);
	}
	else if (sQuestName == "Mtraxx_PlantPrepareMarch") // готовим к ночному маршу
	{
		DoQuestReloadToLocation("shore37", "goto", "goto3", "Mtraxx_PlantGotoMarch");
		sld = &Locations[FindLocation("shore37")];
		sld.DisableEncounters = false;
		chr = ItemsFromID("fire");
		chr.shown = false;
		DeleteAttribute(sld, "fire");
		for (i=1; i<=4; i++)
		{
			if (GetCharacterIndex("Pelly_sailor_"+i) != -1)
			{
				sld = characterFromId("Pelly_sailor_"+i);
				sld.lifeday = 0;
				ChangeCharacterAddressGroup(sld, "none", "", "");
			}
		}
	}
	else if (sQuestName == "Mtraxx_PlantGotoMarch") // собираем пиратов для похода к плантации
	{
		// ставим наших пиратов
		chrDisableReloadToLocation = true;
		sld = characterFromId("Pelly");
		sld.dialog.currentnode = "Pelly_12";
		ChangeCharacterAddressGroup(sld, "shore37", "goto", "goto6");
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		iRank = sti(pchar.rank)+5;
		iScl = 30 + 2*sti(pchar.rank);
		for (i=1; i<=7; i++)
		{
			if (i == 7)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Mtr_PellyPirate_"+i, "mush_ctz_7", "man", "mushketer", iRank, PIRATE, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket3", "grapeshot", iScl*3);
				TakeNItems(pchar, "grapeshot", 40);
				TakeNItems(pchar, "gunpowder", 40);
				LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "grapeshot");
				ChangeCharacterAddressGroup(sld, "shore37", "goto", "goto5");
			}
			else
			{
				sld = GetCharacter(NPC_GenerateCharacter("Mtr_PellyPirate_"+i, "citiz_4"+i, "man", "man", iRank, PIRATE, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, LinkRandPhrase("blade_08","blade_11","blade_14"), "pistol1", "bullet", iScl*2);
			}
			ChangeCharacterAddressGroup(sld, "shore37", "goto", "goto"+i);
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
	}
	else if (sQuestName == "Mtraxx_PlantJanReady") // снять бессмертие с Пикара
	{
		sld = characterFromId("Mrt_Rocur");
		LAi_SetImmortal(sld, false);
		sld.ReducedDamage = 0.4; // belamour legendary edition снижение урона на 60%
	}
	else if (sQuestName == "Mtraxx_PlantMutinyAfterFight") // перебили охрану на плантации
	{
		pchar.quest.mtraxx_plant_exitopen.win_condition.l1 = "locator";
		pchar.quest.mtraxx_plant_exitopen.win_condition.l1.location = "Maracaibo_Plantation";
		pchar.quest.mtraxx_plant_exitopen.win_condition.l1.locator_group = "reload";
		pchar.quest.mtraxx_plant_exitopen.win_condition.l1.locator = "reload2_back";
		pchar.quest.mtraxx_plant_exitopen.function = "Mtraxx_PlantExitopen";
	}
	else if (sQuestName == "Mtraxx_PlantEscape") // сбежали с плантации
	{
		LAi_group_Delete("EnemyFight");
		chrDisableReloadToLocation = false;
		DeleteAttribute(pchar, "GenQuest.FrameLockEsc");
		bDisableCharacterMenu = false;
		InterfaceStates.Buttons.Save.enable = true;
		LocatorReloadEnterDisable("Maracaibo_ExitTown", "reload2_back", true);
		LocatorReloadEnterDisable("Maracaibo_ExitTown", "reload3_back", true);
		LocatorReloadEnterDisable("Maracaibo_ExitTown", "reload4", true);
		// собираем всех, кто выжил, кроме пиратов Пикара - дают вылет
		sld = characterFromId("Pelly");
		LAi_SetImmortal(sld, false); 
		ChangeCharacterAddressGroup(sld, "Maracaibo_ExitTown", "rld", "loc17");
		LAi_SetActorType(sld);
		LAi_ActorFollowEverywhere(sld, "", -1);
		if (GetCharacterIndex("Mrt_Rocur") != -1)
		{
			sld = characterFromId("Mrt_Rocur");
			ChangeCharacterAddressGroup(sld, "Maracaibo_ExitTown", "rld", "loc16");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
		for (i=1; i<=7; i++)
		{
			if (GetCharacterIndex("Mtr_PellyPirate_"+i) != -1)
			{
				sld = CharacterFromID("Mtr_PellyPirate_"+i);
				ChangeCharacterAddressGroup(sld, "Maracaibo_ExitTown", "rld", "loc18");
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
		}
		pchar.quest.mtraxx_plant_escape.win_condition.l1 = "location";
		pchar.quest.mtraxx_plant_escape.win_condition.l1.location = "shore37";
		pchar.quest.mtraxx_plant_escape.function = "Mtraxx_PlantEscapeInShore";
		AddQuestRecord("Roger_3", "21");
		AddComplexSelfExpToScill(80, 80, 80, 80);
	}
	else if (sQuestName == "Mtraxx_PlantMutinyAfterFortFight") // после боя с подкреплением
	{
		DeleteAttribute(pchar, "questTemp.Mtraxx.PlantFort");
		pchar.quest.mtraxx_plant_exitopen1.win_condition.l1 = "locator";
		pchar.quest.mtraxx_plant_exitopen1.win_condition.l1.location = "Maracaibo_Plantation";
		pchar.quest.mtraxx_plant_exitopen1.win_condition.l1.locator_group = "reload";
		pchar.quest.mtraxx_plant_exitopen1.win_condition.l1.locator = "reload2_back";
		pchar.quest.mtraxx_plant_exitopen1.function = "Mtraxx_PlantExitopen";
	}
	else if (sQuestName == "Mtraxx_PlantCaravanGuadeloupe") // караван с товарами у гваделупы
	{
		Group_FindOrCreateGroup("Mtraxx_PlantCaravanGuadeloupe");
		Group_SetType("Mtraxx_PlantCaravanGuadeloupe", "trade");
		
		iClass = sti(RealShips[sti(pchar.ship.type)].Class);
	
		if(iClass < 3) iClass = 3;
		if(iClass > 5) iClass = 5;
		
		for (i=1; i<=4; i++)
		{
			switch (i)
			{
				case 1:
					ShipType = GetRandomShipType(GetClassFlag(iClass), FLAG_SHIP_TYPE_WAR, FLAG_SHIP_NATION_ANY);
					attrName = StringFromKey("Roger_103");
					Model = "citiz_21";
					Rank = 20;
					Blade = "blade_10";
				break;
				case 2:
					ShipType = GetRandomShipType(GetClassFlag(iClass), FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
					attrName = StringFromKey("Roger_104");
					Model = "trader_2";
					Rank = 15;
					Blade = "blade_05";
				break;
				case 3:
					ShipType = GetRandomShipType(GetClassFlag(iClass + 1), FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
					attrName = StringFromKey("Roger_105");
					Model = "citiz_25";
					Rank = 15;
					Blade = "blade_05";
				break;
				case 4:
					ShipType = GetRandomShipType(GetClassFlag(iClass), FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
					attrName = StringFromKey("Roger_106");
					Model = "trader_6";
					Rank = 15;
					Blade = "blade_05";
				break;
			}
			sld = GetCharacter(NPC_GenerateCharacter("Mtraxx_PCG_cap_"+i, Model, "man", "man", Rank, FRANCE, -1, false, "soldier"));
			FantomMakeCoolSailor(sld, ShipType, attrName, CANNON_TYPE_CANNON_LBS32, 80, 80, 80);
			FantomMakeCoolFighter(sld, Rank, 80, 80, Blade, "pistol1", "grapeshot", 50);
			SetCaptanModelByEncType(sld, "trade");
			sld.Ship.Mode = "trade";
			if (sld.id == "Mtraxx_PCG_cap_1")
			{
				SetCharacterGoods(sld, GOOD_SLAVES, 200+rand(50));
			}
			if (sld.id == "Mtraxx_PCG_cap_2")
			{
				SetCharacterGoods(sld, GOOD_COPRA, 600+rand(100));
			}
			if (sld.id == "Mtraxx_PCG_cap_3")
			{
				SetCharacterGoods(sld, GOOD_CINNAMON, 600+rand(100));
			}
			if (sld.id == "Mtraxx_PCG_cap_4")
			{
				SetCharacterGoods(sld, GOOD_COFFEE, 600+rand(100));
			}
			Group_AddCharacter("Mtraxx_PlantCaravanGuadeloupe", "Mtraxx_PCG_cap_"+i);
		}
		Group_SetGroupCommander("Mtraxx_PlantCaravanGuadeloupe", "Mtraxx_PCG_cap_1");
		Group_SetTaskAttack("Mtraxx_PlantCaravanGuadeloupe", PLAYER_GROUP);
		Group_SetAddress("Mtraxx_PlantCaravanGuadeloupe", "Guadeloupe", "Quest_ships", "Quest_ship_2");
		Group_LockTask("Mtraxx_PlantCaravanGuadeloupe");
	}
	else if (sQuestName == "Mtraxx_PlantCaravanGuadeloupe_time") // караван ушёл
	{
		group_DeleteGroup("Mtraxx_PlantCaravanGuadeloupe");
		for (i=1; i<=4; i++)
		{
			if (CharacterIsAlive("Mtraxx_PCG_cap_"+i))
			{
				sld = CharacterFromID("Mtraxx_PCG_cap_"+i);
				sld.lifeday = 0;
			}
		}
	}
	else if (sQuestName == "Mtraxx_PasqualeNightTalk") // в заливе - старт похода в Ла Вегу
	{
		sld = characterFromId("Mrt_Rocur");
		sld.dialog.currentnode = "rocur_71";
		ChangeCharacterAddressGroup(sld, "Shore34", "goto", "goto1");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	else if (sQuestName == "Mtraxx_PasqualeNightToHouse") // релоад в дом
	{
		DoQuestReloadToLocation("LaVega_TwoFloorHouse", "reload", "reload1", "Mtraxx_PasqualeNightInHouse");
	}
	else if (sQuestName == "Mtraxx_PasqualeNightInHouse") // в доме
	{
		sld = characterFromId("Mrt_Rocur");
		sld.dialog.currentnode = "rocur_73";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 2.0);
	}
	else if (sQuestName == "Mtraxx_PasqualeJanAni") // Жан ковыряется в сундуках
	{
		sld = characterFromId("Mrt_Rocur");
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "Barman_idle", "", 90.0);
		DoQuestFunctionDelay("Mtraxx_PasqualeJanTreasure", 90.0);
	}
	else if (sQuestName == "Mtraxx_PasqualeJanSeeGirl") // Жан видит Мирабель
	{
		sld = characterFromId("Mrt_Rocur");
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
	}
	else if (sQuestName == "Mtraxx_PasqualeJanKillGirl") // Жан убивает Мирабель
	{
		sld = characterFromId("Mirabella");
		LAi_KillCharacter(sld);
		sld = characterFromId("Mrt_Rocur");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocator(sld, "goto", "goto9", "Mtraxx_PasqualeJanGotcha", -1);
	}
	else if (sQuestName == "Mtraxx_PasqualeJanGotcha") // Жан делится добычей
	{
		LAi_SetPlayerType(pchar);
		sld = characterFromId("Mrt_Rocur");
		sld.dialog.currentnode = "rocur_83";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 0.5);
	}
	else if (sQuestName == "Mtraxx_PasqualeNightOutHouse") // релоад из дома
	{
		DoQuestReloadToLocation("LaVega_town", "reload", "reload10", "Mtraxx_PasqualeNightOutLaVega");
	} 
	else if (sQuestName == "Mtraxx_PasqualeNightOutLaVega") // релоад из Ла Веги
	{
		sld = characterFromId("Mrt_Rocur");
		LAi_SetActorType(sld);
		LAi_ActorRunToLocation(sld, "reload", "reload1", "LaVega_Exittown", "reload", "reload3", "Mtraxx_PasqualeNightSuccess", -1);
	}
	else if (sQuestName == "Mtraxx_PasqualeNightSuccess") // завершили поход к Паскуале
	{
		DoQuestReloadToLocation("LaVega_Exittown", "reload", "reload3", "Mtraxx_PasqualeNightReturn");
	}
	else if (sQuestName == "Mtraxx_PasqualeNightReturn") // идем назад в залив Гонаив
	{
		LocatorReloadEnterDisable("LaVega_Exittown", "reload3", true);
		sld = characterFromId("Mrt_Rocur");
		sld.dialog.currentnode = "rocur_89";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	else if (sQuestName == "Mtraxx_MirabellaSex") // секс с Мирабель
	{
		sld = characterFromId("Mirabella");
		ChangeCharacterAddressGroup(sld, "IslaMona_TwoFloorRoom", "goto", "goto4");
		DoQuestFunctionDelay("Mtraxx_MirabellaSex", 1.5);
	}
	else if (sQuestName == "Mtraxx_MeridaAddPicar") // Пикара в пассажиры
	{
		chrDisableReloadToLocation = false;
		sld = characterFromId("Mrt_Rocur");
		AddPassenger(pchar, sld, false);//добавить пассажира
		SetCharacterRemovable(sld, false);
	}
	else if (sQuestName == "Mtraxx_MeridaVozhdDialog") // Кумвана обращается к нам спустя сутки
	{
		sld = characterFromId("Cumvana");
		sld.dialog.currentnode = "cumvana_8";
		LAi_SetActorType(sld);
		LAi_ActorSetHuberMode(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
	}
	else if (sQuestName == "Mtraxx_MeridaGotoRiver") // открываем путь к реке
	{
		chrDisableReloadToLocation = false;
		pchar.quest.mtraxx_merida_gotoriver.win_condition.l1 = "location";
		pchar.quest.mtraxx_merida_gotoriver.win_condition.l1.location = "Locono_village";
		pchar.quest.mtraxx_merida_gotoriver.win_condition = "Mtraxx_MeridaGotoRiver_1";
		n = Findlocation("Maracaibo_jungle_04");
		locations[n].locators_radius.reload.reload2_back = 2.0;
	}
	else if (sQuestName == "Mtraxx_MeridaGotoRiver_1") // Тагофа ведет нас к реке
	{
		chrDisableReloadToLocation = true;
		sld = characterFromId("Tagofa");
		ChangeCharacterAddressGroup(sld, "Locono_village", "quest", "teleport1");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1);
		sld = characterFromId("Lepricon");
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		LAi_ActorFollowEverywhere(sld, "", -1);
		pchar.quest.mtraxx_merida_gotoriver1.win_condition.l1 = "location";
		pchar.quest.mtraxx_merida_gotoriver1.win_condition.l1.location = "Maracaibo_jungle_03";
		pchar.quest.mtraxx_merida_gotoriver1.win_condition = "Mtraxx_MeridaGotoRiver_2";
	}
	else if (sQuestName == "Mtraxx_MeridaGotoRiver_2") // Тагофа ведет нас к реке
	{
		chrDisableReloadToLocation = true;
		sld = characterFromId("Tagofa");
		ChangeCharacterAddressGroup(sld, "Maracaibo_jungle_03", "reload", "reload2_back");
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		LAi_ActorGoToLocation(sld, "reload", "reload3_back", "none", "", "", "OpenTheDoors", -1);
		pchar.quest.mtraxx_merida_gotoriver2.win_condition.l1 = "location";
		pchar.quest.mtraxx_merida_gotoriver2.win_condition.l1.location = "Maracaibo_jungle_04";
		pchar.quest.mtraxx_merida_gotoriver2.win_condition = "Mtraxx_MeridaGotoRiver_3";
	}
	else if (sQuestName == "Mtraxx_MeridaGotoRiver_3") // Тагофа ведет нас к реке
	{
		chrDisableReloadToLocation = true;
		sld = characterFromId("Tagofa");
		ChangeCharacterAddressGroup(sld, "Maracaibo_jungle_04", "reload", "reload1_back");
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		LAi_ActorGoToLocation(sld, "reload", "reload2_back", "none", "", "", "OpenTheDoors", -1);
		pchar.quest.mtraxx_merida_gotoriver3.win_condition.l1 = "location";
		pchar.quest.mtraxx_merida_gotoriver3.win_condition.l1.location = "Maracaibo_river";
		pchar.quest.mtraxx_merida_gotoriver3.win_condition = "Mtraxx_MeridaGotoRiver_4";
	}
	else if (sQuestName == "Mtraxx_MeridaGotoRiver_4") // Тагофа ведет нас к реке
	{
		chrDisableReloadToLocation = true;
		sld = characterFromId("Tagofa");
		ChangeCharacterAddressGroup(sld, "Maracaibo_river", "reload", "reload1_back");
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		LAi_ActorGoToLocator(sld, "goto", "goto10", "Mtraxx_MeridaGotoRiver_5", -1);
	}
	else if (sQuestName == "Mtraxx_MeridaGotoRiver_5") // Тагофа ведет нас к реке
	{
		sld = characterFromId("Tagofa");
		LAi_SetStayType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	else if (sQuestName == "Mtraxx_MeridaBuildBoats") // лодки построены
	{
		bDisableCharacterMenu = false;
		DeleteAttribute(pchar, "GenQuest.FrameLockEsc");
		n = makeint(sti(pchar.questTemp.Mtraxx.Merida.Antidote)/6);
		for (i=5; i<=9; i++) // ребята Леприкона
		{
			sld = characterFromId("Lepricons_pirate_"+i);
			ChangeCharacterAddressGroup(sld, "Maracaibo_river", "goto", "goto"+i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
		for (i=1; i<=8; i++) // наши красавцы
		{
			if (i > 6)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Merida_pirate_"+i, "mush_ctz_"+i, "man", "mushketer", 20, PIRATE, -1, false, "quest"));
				FantomMakeCoolFighter(sld, 20, 60, 60, "", "mushket3", "grapeshot", 150);
				LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "grapeshot");
			}
			else
			{
				sld = GetCharacter(NPC_GenerateCharacter("Merida_pirate_"+i, "citiz_4"+i, "man", "man", 18, PIRATE, -1, true, "quest"));
				FantomMakeCoolFighter(sld, 18, 50, 50, LinkRandPhrase("blade_07","blade_08","blade_11"), "pistol3", "grapeshot", 120);
			}
			TakeNItems(sld, "potion3", n);
			LAi_CharacterDisableDialog(sld);
			ChangeCharacterAddressGroup(sld, "Maracaibo_river", "goto", "goto"+i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
		DoQuestReloadToLocation("Maracaibo_river", "goto", "goto3", "");
		AddQuestRecord("Roger_5", "14");
	}
	else if (sQuestName == "Mtraxx_MeridaRiverTrip") // плывем по реке на лодках
	{
		bDisableCharacterMenu = true;
		pchar.GenQuest.FrameLockEsc = true;
		SetMusic("music_map");
		SetLaunchFrameFormParam("", "", 0, 15);
		SetLaunchFrameFormPic("loading\River_1.tga");
		LaunchFrameForm();
		WaitDate("", 0, 0, 2, 2, 20); //крутим время
		RecalculateJumpTable();
		StoreDayUpdate();
		RefreshWeather();
		RefreshLandTime();
		DoQuestCheckDelay("Mtraxx_MeridaRiverTripEnd", 15.0);
		DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Potion");
		LocatorReloadEnterDisable("Shore_ship3", "boat", false); // выпустим в море
	}
	else if (sQuestName == "Mtraxx_MeridaRiverTripEnd") // приплыли
	{
		n = Findlocation("Serpentine1");
		for (i=1; i<=6; i++)
		{
			sTemp = "Boat"+i;
			locations[n].models.always.(sTemp) = "Boat";
			Locations[n].models.always.(sTemp).locator.group = "quest";
			Locations[n].models.always.(sTemp).locator.name = "boat"+i;
			Locations[n].models.always.(sTemp).tech = "DLightModel";
		}
		n = Findlocation("Serpentine2");
		locations[n].models.always.sign = "StoneMap";
		Locations[n].models.always.sign.locator.group = "quest";
		Locations[n].models.always.sign.locator.name = "quest1";
		Locations[n].models.always.sign.tech = "DLightModel";
		DoQuestReloadToLocation("Serpentine1", "reload", "reload3", "Mtraxx_MeridaSerpentine");
	}
	else if (sQuestName == "Mtraxx_MeridaSerpentine") // прибыли в точку высадки
	{
		bDisableCharacterMenu = false;
		DeleteAttribute(pchar, "GenQuest.FrameLockEsc");
		for (i=1; i<=3; i++)
		{
			idx = GetOfficersIndex(pchar, i);
			if (idx < 1) continue;
			sld = &Characters[idx];
			ChangeCharacterAddressGroup(sld, "Serpentine1", "officers", "reload2_"+i);
		}
		for (i=5; i<=9; i++) // ребята Леприкона
		{
			sld = characterFromId("Lepricons_pirate_"+i);
			ChangeCharacterAddressGroup(sld, "Serpentine1", "goto", "goto11");
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_ActorFollowEverywhere(sld, "", -1);
		}
		for (i=1; i<=8; i++) // наши красавцы
		{
			sld = characterFromId("Merida_pirate_"+i);
			ChangeCharacterAddressGroup(sld, "Serpentine1", "goto", "goto12");
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_ActorFollowEverywhere(sld, "", -1);
		}
		sld = characterFromId("Lepricon");
		ChangeCharacterAddressGroup(sld, "Serpentine1", "goto", "goto10");
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		LAi_ActorFollowEverywhere(sld, "", -1);
		sld = characterFromId("Tagofa");
		sld.dialog.currentnode = "tagofa_11";
		ChangeCharacterAddressGroup(sld, "Serpentine1", "goto", "goto10");
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	else if (sQuestName == "Mtraxx_MeridaWarning") // знак капонгов на тропе
	{
		LAi_SetPlayerType(pchar);
		sld = characterFromId("Tagofa");
		sld.dialog.currentnode = "tagofa_15";
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		LAi_ActorDialogDelay(sld, pchar, "", 1.5);
	}
	else if (sQuestName == "Mtraxx_MeridaWarningCutscene")
	{
		locCameraSleep(false);
		locCameraFromToPos(3.42, 10.88, 8.49, true, 6.46, 8.33, 10.65);
		sld = characterFromId("Tagofa");
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, "Serpentine2", "goto", "goto5");
		LAi_ActorGoToLocator(sld, "quest", "quest1", "Mtraxx_MeridaWarning", -1);
	}
	else if (sQuestName == "Mtraxx_MeridaCapongAfterFight") // после боя с капонгами
	{
		LAi_group_Delete("EnemyFight");
		sld = characterFromId("Tagofa");
		sld.dialog.currentnode = "tagofa_18";
		ChangeCharacterAddressGroup(sld, "Merida_jungle_01", "reload", "reload1_back");
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		AddComplexSelfExpToScill(50, 50, 50, 50);
	}
	else if (sQuestName == "Mtraxx_MeridaGateAfterBattle") // после боя у ворот
	{
		LAi_group_Delete("EnemyFight");
		sld = characterFromId("Mrt_Rocur");
		sld.dialog.currentnode = "rocur_38";
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		AddComplexSelfExpToScill(50, 50, 50, 50);
	}
	else if (sQuestName == "Mtraxx_MeridaAfterBattle") // после боя в городе
	{
		LAi_group_Delete("EnemyFight");
		sld = characterFromId("Mrt_Rocur");
		sld.dialog.currentnode = "rocur_40";
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		AddComplexSelfExpToScill(20, 20, 20, 20);
	}
	else if (sQuestName == "Mtraxx_MeridaOpenChest") // губер открывает свой сундук
	{
		sld = characterFromId("Merida_head");
		LAi_SetActorType(sld);
		CharacterTurnToLoc(sld, "box", "box1");
		LAi_ActorAnimation(sld, "Barman_idle", "Mtraxx_MeridaOpenChest1", 2.5);
	}
	else if (sQuestName == "Mtraxx_MeridaOpenChest1") // губер открывает свой сундук
	{
		PlaySound("interface\key.wav");
		sld = characterFromId("Merida_head");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocator(sld, "goto", "goto1", "Mtraxx_MeridaOpenChest2", -1);
	}
	else if (sQuestName == "Mtraxx_MeridaOpenChest2") // губер открывает свой сундук
	{
		sld = characterFromId("Merida_head");
		CharacterTurnByLoc(sld, "goto", "goto1");
		sld = characterFromId("Mrt_Rocur");
		sld.dialog.currentnode = "merida_head_dobro_vnimatelnost_3";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
	}
	else if (sQuestName == "Mtraxx_MeridaGiveJewelry") // Пикар забирает камни
	{
		//PlaySound("interface\important_item.wav");
		sld = characterFromId("Mrt_Rocur");
		//sld.dialog.currentnode = "rocur_42";
		LAi_SetActorType(sld);
		CharacterTurnToLoc(sld, "box", "box1");
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		//LAi_ActorDialogDelay(sld, pchar, "", 2.0);
	}
	else if (sQuestName == "Mtraxx_MeridaExitResidensia") // выходим из резиденции
	{
		DoQuestReloadToLocation("Merida_town", "goto", "goto29", "Mtraxx_MeridaExitResidensia2");
	}
	else if (sQuestName == "Mtraxx_MeridaExitResidensia2") // выходим из резиденции
	{
		StartQuestMovie(true, false, true);
		locCameraFromToPos(23.08, 0.73, -3.34, true, 15.56, -1.00, 2.64);
	}
	else if (sQuestName == "Mtraxx_MeridaCaveVtoryaVolna") // вторая волна капонгов
	{
		PlaySound("interface\abordage_wining.wav");
		for (i=1; i<=6; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("Capong_cave_podkreplenie_"+i, "canib_"+(rand(5)+1), "man", "man", 25, PIRATE, -1, false, "native"));
			FantomMakeCoolFighter(sld, 25, 80, 80, RandPhraseSimple("blade_01","blade_02"), "", "", 50);
			sld.name = GetIndianName(MAN);
			sld.lastname = "";
			sld.viper = true;
			ChangeCharacterAddressGroup(sld, "Serpentine_cave", "monsters", "monster"+i);
			DeleteAttribute(sld, "SaveItemsForDead");
			DeleteAttribute(sld, "DontClearDead");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "Mtraxx_MeridaCaveAfterFight");
	}
	else if (sQuestName == "Mtraxx_MeridaCaveAfterFight") // после боя в пещере с капонгами
	{
		AddQuestRecord("Roger_5", "13");
		Mtraxx_MeridaCheckOurWarriors();
		chrDisableReloadToLocation = false;
		sld = characterFromId("Tagofa");
		ChangeCharacterAddressGroup(sld, "Serpentine_cave", "reload", "reload1_back");
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		LAi_ActorFollowEverywhere(sld, "", -1);
		pchar.quest.mtraxx_merida_return.win_condition.l1 = "locator";
		pchar.quest.mtraxx_merida_return.win_condition.l1.location = "Serpentine1";
		pchar.quest.mtraxx_merida_return.win_condition.l1.locator_group = "reload";
		pchar.quest.mtraxx_merida_return.win_condition.l1.locator = "reload3";
		pchar.quest.mtraxx_merida_return.function = "Mtraxx_MeridaReturn";
		AddComplexSelfExpToScill(30, 30, 30, 30);
	}
	else if (sQuestName == "Mtraxx_MeridaReturnEnd") // вернулись к Маракайбо
	{
		bDisableCharacterMenu = false;
		DeleteAttribute(pchar, "GenQuest.FrameLockEsc");
		chrDisableReloadToLocation = true;
		sld = characterFromId("Tagofa");
		sld.dialog.currentnode = "tagofa_20";
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	else if (sQuestName == "Mtraxx_IgnasioInTavern") // 
	{
		/* if(CheckAttribute(pchar, "IsMushketer"))
		{
			SetMainCharacterToMushketer("", false);
		} */
		FreeSitLocator("Bridgetown_tavern", "sit_base2");
		DoQuestReloadToLocation("Bridgetown_tavern", "sit", "sit_base2", "");			
		sld = characterFromID("Ignasio");
		sld.dialog.currentnode = "ignasio_4";
		LAi_SetActorType(sld);
		LAi_ActorSetSitMode(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.5);
	}
	else if (sQuestName == "Mtraxx_IgnasioEscape") // 
	{
		sld = GetCharacter(NPC_GenerateCharacter("Ignasio_spy", "Alonso", "man", "man", 25, FRANCE, 0, false, "soldier"));
		sld.name = StringFromKey("Roger_107");
		sld.lastname = StringFromKey("Roger_108");
		FantomMakeCoolFighter(sld, 25, 30, 30, "blade_05", "pistol1", "bullet", 120);
		sld.Dialog.Filename = "Quest\Roger.c";
		sld.dialog.currentnode = "spy_sailor";
		ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0); 
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	else if (sQuestName == "Mtraxx_WolfreekGrotAfterFight") // перебили карибов
	{
		chrDisableReloadToLocation = false;
		LAi_group_Delete("EnemyFight");
		AddQuestRecord("Roger_7", "3");
		pchar.questTemp.Mtraxx.Grotbox = "true";
		AddComplexSelfExpToScill(30, 30, 30, 30);
	}
	else if (sQuestName == "Mtraxx_WolfreekCaveAfterFight") // перебили босяков
	{
		chrDisableReloadToLocation = false;
		LAi_group_Delete("EnemyFight");
		AddQuestRecord("Roger_7", "6");
		AddComplexSelfExpToScill(20, 20, 20, 20);
	}
	else if (sQuestName == "Mtraxx_WolfreekPelly") // 
	{
		AddQuestRecord("Roger_7", "11");
		LAi_SetPlayerType(pchar);
		DoQuestFunctionDelay("Mtraxx_WolfreekPelly", 30.0);
		InterfaceStates.Buttons.Save.enable = false;
		pchar.GenQuest.FrameLockEsc = true; 
	}
	else if (sQuestName == "Mtraxx_WolfreekJewellerWait") // 
	{
		SetLaunchFrameFormParam(StringFromKey("Roger_109"), "", 0, 5);//табличка
		WaitDate("", 0, 0, 0, 3, 20); //крутим время
		LaunchFrameForm();
		RefreshLandTime();
		RecalculateJumpTable();
		Whr_UpdateWeather();
		DoQuestFunctionDelay("Mtraxx_WolfreekSetPelly", 1.0);
	}
	else if (sQuestName == "Mtraxx_WolfreekPellyWaitGems")
	{
		DoQuestFunctionDelay("Mtraxx_WolfreekPellyGemsToPrince", 10.0);
	}
	else if (sQuestName == "Mtraxx_WolfreekIslaMonaAfterFight") // 
	{
		chrDisableReloadToLocation = false;
		AddQuestRecord("Roger_7", "17");
		AddComplexSelfExpToScill(30, 30, 30, 30);
		// ставим троих в форте
		sld = GetCharacter(NPC_GenerateCharacter("Islamona_carpenter", "mercen_30", "man", "man", 25, PIRATE, -1, true, "quest"));
		FantomMakeCoolFighter(sld, 25, 60, 60, "topor_02", "pistol1", "bullet", 100);
		sld.Dialog.Filename = "Quest\Roger.c";
		sld.dialog.currentnode = "carpenter";
		sld.name = StringFromKey("Roger_110");
		sld.lastname = StringFromKey("Roger_111");
		sld.greeting = "Rodgar_01";
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		LAi_SetImmortal(sld, true);
		ChangeCharacterAddressGroup(sld, "IslaMona_town", "goto", "gotoChar1");
		LAi_SetActorType(sld);
		for (i=1; i<=2; i++) // 
		{
			sld = GetCharacter(NPC_GenerateCharacter("Islamona_fort_pirate_"+i, "citiz_4"+(7+i), "man", "man", 18, PIRATE, -1, true, "quest"));
			FantomMakeCoolFighter(sld, 18, 50, 50, LinkRandPhrase("blade_07","blade_08","blade_11"), "pistol1", "bullet", 100);
			LAi_CharacterDisableDialog(sld);
			DeleteAttribute(sld, "SaveItemsForDead");
			DeleteAttribute(sld, "DontClearDead");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "IslaMona_town", "goto", "gotoChar" + (i + 1));
		}
		pchar.quest.mtraxx_wolfreek_cannon.win_condition.l1 = "locator";
		pchar.quest.mtraxx_wolfreek_cannon.win_condition.l1.location = "IslaMona_town";
		pchar.quest.mtraxx_wolfreek_cannon.win_condition.l1.locator_group = "quest";
		pchar.quest.mtraxx_wolfreek_cannon.win_condition.l1.locator = "detector";
		pchar.quest.mtraxx_wolfreek_cannon.function = "Mtraxx_WolfreekCannon";
		pchar.quest.mtraxx_wolfreek_cpy.win_condition.l1 = "location";
		pchar.quest.mtraxx_wolfreek_cpy.win_condition.l1.location = "IslaMona";
		pchar.quest.mtraxx_wolfreek_cpy.function = "Mtraxx_WolfreekCpy";
		
		IslaMona_SetCannonBattle();
	}
	else if (sQuestName == "Mtraxx_WolfreekInFort") // 
	{
		chrDisableReloadToLocation = false;
		AddQuestRecord("Roger_7", "18");
		pchar.questTemp.Mtraxx.WolfreekBox = "true";
	}
	else if (sQuestName == "Mtraxx_WolfreekRepairShore") // // прогона 3
	{
		DoQuestCheckDelay("Mtraxx_WolfreekRepairActivate", 2.0);
	}
	else if (sQuestName == "Mtraxx_WolfreekRepairActivate") // 
	{
		LaunchRepair(pchar);
		chrDisableReloadToLocation = false;
	}
	else if (sQuestName == "Mtraxx_CorridaSenPierre") // 
	{
		InterfaceStates.Buttons.Save.enable = true; // разрешим сохраняться
		bDisableCharacterMenu = false; // разлочим F2
		bQuestDisableMapEnter = false;
		setCharacterShipLocation(pchar, "FortFrance_town");
		setWDMPointXZ("FortFrance_town");
		LocatorReloadEnterDisable("FortFrance_town", "reload1_back", true);
		LocatorReloadEnterDisable("FortFrance_town", "reload2_back", true);
		LocatorReloadEnterDisable("LeFransua_town", "reload3_back", true);
		pchar.GenQuest.CannotWait = true;
		AddQuestRecord("Roger_8", "2");
		pchar.quest.mtraxx_corrida_lefransua.win_condition.l1 = "locator";
		pchar.quest.mtraxx_corrida_lefransua.win_condition.l1.location = "LeFransua_town";
		pchar.quest.mtraxx_corrida_lefransua.win_condition.l1.locator_group = "quest";
		pchar.quest.mtraxx_corrida_lefransua.win_condition.l1.locator = "quest2";
		pchar.quest.mtraxx_corrida_lefransua.function = "Mtraxx_CorridaSeeMarko";
		n = Findlocation("LeFransua_town");
		locations[n].locators_radius.quest.quest2 = 11.0;
		LAi_LocationDisableOfficersGen("LeFransua_town", true);
		QuestPointerToLoc("lefransua_town", "quest", "quest2");
	}
	else if (sQuestName == "Mtraxx_CorridaSeeMarko") // 
	{
		LAi_SetActorType(pchar);
		LAi_ActorTurnToLocator(pchar, "reload", "reload6");
	}
	else if (sQuestName == "Mtraxx_CorridaSeeMarko1") // 
	{
		LAi_SetActorType(pchar);
		LAi_ActorTurnToLocator(pchar, "reload", "reload1");
	}
	else if (sQuestName == "Mtraxx_CorridaControlMarko1")
	{
		StartQuestMovie(true, false, true);
		sld = GetCharacter(CreateCharacterClone(CharacterFromID("Ignasio"), -1));
		sld.id = "IgnasioClone";
		ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocator(sld, "goto", "goto13", "", -1);
		SetCameraDialogMode(sld);
		locCameraFlyToPositionLookToHero(53.88, 3.68, 61.22, 43.42, 7.21, 23.34, -1, 15000/GetDeltaTime());
		Pchar.FuncCameraFly = "";
		DoQuestCheckDelay("Mtraxx_CorridaControlMarko3", 3.0);
		DoQuestCheckDelay("Mtraxx_CorridaControlMarko6", 8.0);
	}
	else if (sQuestName == "Mtraxx_CorridaControlMarko3")
	{
		ChangeCharacterAddressGroup(pchar, PChar.location, "quest", "quest3");
		//Log_Info(StringFromKey("Roger_112"));
		//PlaySound("interface\notebook.wav");
	}
	else if (sQuestName == "Mtraxx_CorridaControlMarko6")
	{
		LAi_Fade("Mtraxx_CorridaControlMarko6_1", "");
	}
	else if (sQuestName == "Mtraxx_CorridaControlMarko6_1")
	{
		sld = CharacterFromID("IgnasioClone");
		LAi_type_actor_Reset(sld);
		ChangeCharacterAddressGroup(sld, PChar.location, "reload", "houseH9");
		LAi_ActorGoToLocation(sld, "reload", "reload3_back", "none", "", "", "Mtraxx_CorridaWaitMarko", -1);
		locCameraResetState();
		locCameraFlyToPositionLookToHero(8.72, 3.33, 32.14, 5.25, 6.12, 30.81, -1, 15000/GetDeltaTime());
		Pchar.FuncCameraFly = "";
	}
	else if (sQuestName == "Mtraxx_CorridaWaitMarko") // 
	{
		DoQuestCheckDelay("Mtraxx_CorridaWaitMarkoFrame", 2.5);
	}
	else if (sQuestName == "Mtraxx_CorridaWaitMarkoFrame") // 
	{
		EndQuestMovie();
		locCameraResetState();
		SetLaunchFrameFormParam(StringFromKey("Roger_113", NewStr()), "Mtraxx_CorridaMarkoExit", 0, 5);
		LaunchFrameForm();
		WaitDate("", 0, 0, 0, 2, 10); //крутим время
		RecalculateJumpTable();
		StoreDayUpdate();
		RefreshWeather();
		RefreshLandTime();
	}
	else if (sQuestName == "Mtraxx_CorridaMarkoExit")
	{
		n = Findlocation("LeFransua_town");
		locations[n].locators_radius.quest.quest2 = 1.0;
		DoQuestReloadToLocation("LeFransua_town", "quest", "quest3", "Mtraxx_CorridaMarkoExit1");
	}
	else if (sQuestName == "Mtraxx_CorridaMarkoExit1")
	{
		StartQuestMovie(true, false, true);
		locCameraFromToPos(5.25, 6.12, 30.81, true, -1.45, 1.90, 21.67);
		
		DoQuestCheckDelay("Mtraxx_CorridaMarkoExit2", 3.5);
	}
	else if (sQuestName == "Mtraxx_CorridaMarkoExit2") // 
	{
		//Log_Info(StringFromKey("Roger_114"));
		//Log_Info(StringFromKey("Roger_115"));
		//PlaySound("interface\notebook.wav");
		sld = CharacterFromID("IgnasioClone");
		ChangeCharacterAddressGroup(sld, "LeFransua_town", "reload", "reload3_back");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "Mtraxx_CorridaMarkoGone", -1);
		sld = CharacterFromID("Mtr_Vagrant");
		ChangeCharacterAddressGroup(sld, "LeFransua_town", "reload", "reload3_back");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
		sld = CharacterFromID("Mtr_vampire");
		ChangeCharacterAddressGroup(sld, "LeFransua_town", "reload", "reload3_back");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
		DoQuestCheckDelay("Mtraxx_CorridaMarkoExit2_1", 2.5);
		locCameraSleep(true);
	}
	else if (sQuestName == "Mtraxx_CorridaMarkoExit2_1")
	{
		locCameraSleep(false);
		locCameraResetState();
		locCameraFlyToPositionLookToPoint(40.09, 4.10, 28.11, 46.58, 3.68, 63.22, 44.19, 2.13, 57.48, -1, 24000/GetDeltaTime());
		sld = CharacterFromID("IgnasioClone");
		LAi_type_actor_Reset(sld);
		TeleportCharacterToPosAy(sld, 42.59, 2.02, 35.65, 0.00);
		LAi_ActorGoToLocation(sld,  "reload", "reload1", "none", "", "", "Mtraxx_CorridaMarkoGone", -1);
		sld = CharacterFromID("Mtr_Vagrant");
		LAi_type_actor_Reset(sld);
		TeleportCharacterToPosAy(sld, 41.59, 2.02, 34.65, 0.00);
		LAi_ActorGoToLocation(sld,  "reload", "reload1", "none", "", "", "Mtraxx_CorridaMarkoGone", -1);
		sld = CharacterFromID("Mtr_vampire");
		LAi_type_actor_Reset(sld);
		TeleportCharacterToPosAy(sld, 43.59, 2.02, 34.65, 0.00);
		LAi_ActorGoToLocation(sld,  "reload", "reload1", "none", "", "", "Mtraxx_CorridaMarkoGone", -1);
		Pchar.FuncCameraFly = "";
	}
	else if (sQuestName == "Mtraxx_CorridaMarkoGone")
	{
		DoQuestCheckDelay("Mtraxx_CorridaMarkoGone_2", 1.5);
	}
	else if (sQuestName == "Mtraxx_CorridaMarkoGone_2")
	{
		EndQuestMovie();
		locCameraResetState();
		DoQuestReloadToLocation("LeFransua_town", "patrol", "patrol7", "Mtraxx_CorridaMarkoGone_3");
	}
	else if (sQuestName == "Mtraxx_CorridaMarkoGone_3")
	{
		
		LAi_LocationDisableOfficersGen("LeFransua_town", false);
		bDisableCharacterMenu = false;
		LAi_SetPlayerType(pchar);
		locCameraFollow();
		AddQuestRecord("Roger_8", "3");
		Group_DelCharacter("IgnasioSeaGroup", "Ignasio");
		Group_DelCharacter("IgnasioSeaGroup", "Mtr_Vagrant");
		Group_DelCharacter("IgnasioSeaGroup", "Mtr_vampire");
		Group_DeleteGroup("IgnasioSeaGroup");
		LocatorReloadEnterDisable("FortFrance_town", "reload1_back", false);
		LocatorReloadEnterDisable("FortFrance_town", "reload2_back", false);
		LocatorReloadEnterDisable("LeFransua_town", "reload3_back", false);
		setCharacterShipLocation(pchar, "FortFrance_town");
		setWDMPointXZ("FortFrance_town");
		pchar.quest.mtraxx_corrida_martinique1.win_condition.l1 = "location";
		pchar.quest.mtraxx_corrida_martinique1.win_condition.l1.location = "Martinique";
		pchar.quest.mtraxx_corrida_martinique1.function = "Mtraxx_CorridaContinue";
		AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
		AddCharacterExpToSkill(pchar, "Sneak", 200);
		sld = CharacterFromID("IgnasioClone");
		sld.lifeday = 0;
		sld = CharacterFromID("Mtr_Vagrant");
		LAi_type_actor_Reset(sld);
		ChangeCharacterAddressGroup(sld, "none", "", "");
		sld = CharacterFromID("Mtr_vampire");
		LAi_type_actor_Reset(sld);
		ChangeCharacterAddressGroup(sld, "none", "", "");
	}
	else if (sQuestName == "Mtraxx_CartahenaReloadInTavern") // телепорт в таверну
	{
		iTime = sti(environment.time);
		if (iTime >= 21) iAddTime = 24 - iTime;
		if (iTime < 7) iAddTime = 21 - iTime;
		if (iTime >= 7 && iTime < 21) iAddTime = 21 - iTime;
		WaitDate("", 0, 0, 0, iAddTime, 5); //крутим время
		RefreshWeather();
		RefreshLandTime();
		pchar.questTemp.Mtraxx.InTavern = "true";
		// чистим все места, если уже был заход в таверну
		for (i=1; i<=4; i++)
		{
			FreeSitLocator("LaVega_tavern", "sit_front" + i);
			FreeSitLocator("LaVega_tavern", "sit_base" + i);
			FreeSitLocator("LaVega_tavern", "sit" + i);
		}
		LAi_LocationDisableOfficersGen("LaVega_tavern", true);
		sld = ItemsFromID("lcheer");
		sld.shown = true;
		sld.startLocation = "LaVega_tavern";
		sld.startLocator = "quest1";
		DoQuestReloadToLocation("LaVega_tavern", "reload", "reload1_back", "Mtraxx_CartahenaInTavern");
	}
	else if (sQuestName == "Mtraxx_CartahenaInTavern") // братва в таверне
	{
		pchar.questTemp.NoFast = true; // запрет ускорения
		// ГГ - пират на весь эпизод
		PChar.nation = PIRATE;
		pchar.DisableChangeFlagMode = true;
		// установим клон Бернара Венсана
		sld = GetCharacter(NPC_GenerateCharacter("Mtr_Vensan", "Vensan", "man", "man", 20, PIRATE, -1, true, "quest"));
		FantomMakeCoolSailor(sld, SHIP_BRIGANTINE, StringFromKey("Roger_116"), CANNON_TYPE_CANNON_LBS12, 50, 50, 50);
		FantomMakeCoolFighter(sld, 20, 50, 50, "blade_16", "pistol5", "bullet", 100);
		sld.name = StringFromKey("Roger_117");
		sld.lastname = StringFromKey("Roger_118");
		sld.rank = 22;
		sld.reputation = 25;
		SetSelfSkill(sld, 80, 30, 30, 70, 50);
		SetShipSkill(sld, 45, 80, 50, 50, 50, 60, 50, 60, 50);
		SetCharacterGoods(sld, GOOD_BALLS, 400);
		SetCharacterGoods(sld, GOOD_GRAPES, 400);
		SetCharacterGoods(sld, GOOD_KNIPPELS, 300);
		SetCharacterGoods(sld, GOOD_BOMBS, 500);
		SetCharacterGoods(sld, GOOD_POWDER, 1600);
		SetCharacterGoods(sld, GOOD_WEAPON, 200);
		SetCharacterGoods(sld, GOOD_FOOD, 400);
		SetCharacterGoods(sld, GOOD_MEDICAMENT, 200);
		SetCharacterGoods(sld, GOOD_RUM, 70);
		SetCharacterGoods(sld, GOOD_PLANKS, 20);
		SetCharacterGoods(sld, GOOD_SAILCLOTH, 10);
		ChangeCharacterAddressGroup(sld, "LaVega_tavern", "sit", "sit_base2");
		LAi_SetSitType(sld);
		sld = characterFromId("Jeffry");
		FantomMakeCoolSailor(sld, SHIP_EASTINDIAMAN, StringFromKey("Roger_14"), CANNON_TYPE_CANNON_LBS24, 80, 80, 80);
		sld.nation = PIRATE;
		ChangeCharacterAddressGroup(sld, "LaVega_tavern", "sit", "sit_front1");
		LAi_SetSitType(sld);
		sld = characterFromId("Terrax");
		ChangeCharacterAddressGroup(sld, "LaVega_tavern", "sit", "sit_base1");
		LAi_SetSitType(sld);
		sld = characterFromId("Pelly");
		FantomMakeCoolSailor(sld, SHIP_CORVETTE, StringFromKey("Roger_26"), CANNON_TYPE_CULVERINE_LBS18, 70, 70, 70);
		sld.nation = PIRATE;
		ChangeCharacterAddressGroup(sld, "LaVega_tavern", "sit", "sit_base5");
		LAi_SetSitType(sld);
		sld = characterFromId("Lepricon");
		ChangeCharacterAddressGroup(sld, "LaVega_tavern", "sit", "sit_front2");
		LAi_SetSitType(sld);
		// девочки
		for (i = 2; i <= 5; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("Mtr_Taverngirl_" + i, "women_2" + i, "woman", "towngirl", 1, PIRATE, 1, true, "quest"));
			ChangeCharacterAddressGroup(sld, "LaVega_tavern", "goto", "goto" + i);
			LAi_SetCitizenType(sld);
		}
		LAi_SetActorType(pchar);
		LAi_ActorGoToLocator(pchar, "tables", "table1", "Mtraxx_CartahenaTavernTurn", -1);
	}
	else if (sQuestName == "Mtraxx_CartahenaTavernTurn") // 
	{
		LAi_ActorTurnToCharacter(pchar, characterFromID("Terrax"));
		DoQuestCheckDelay("Mtraxx_CartahenaTavernSit", 0.5);
	}
	else if (sQuestName == "Mtraxx_CartahenaTavernSit") // как здорово, что все мы здесь сегодня собрались
	{
		LAi_SetSitType(pchar);
		sld = characterFromId("Terrax");
		sld.dialog.currentnode = "mtraxx_97";
		LAi_SetActorType(sld);
		LAi_ActorSetSitMode(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
	}
	else if (sQuestName == "Mtraxx_CartahenaTavernSong") // а теперь... песня!
	{
		ChangeShowIntarface();
		ResetSound();
		SetMusic("music_piratesong");
		InterfaceStates.Buttons.Save.enable = false;
		bDisableCharacterMenu = true;
		locCameraRotateAroundHero(0.0, 1.5, 0.0, 0.005, 0.0, 1.5, 0.0, 10000);
		Pchar.FuncCameraFly = "";
		DoQuestCheckDelay("Mtraxx_CartahenaTavernExit", 60.0);
	}
	else if (sQuestName == "Mtraxx_CartahenaTavernExit") // закончили пьянку
	{
		bDisableCharacterMenu = false;
		InterfaceStates.Buttons.Save.enable = true;
		locCameraResetState();
		iTime = sti(environment.time);
		WaitDate("", 0, 0, 0, 8, 5); //крутим время
		RecalculateJumpTable();
		StoreDayUpdate();
		RefreshWeather();
		RefreshLandTime();
		LAi_SetPlayerType(pchar);
		setCharacterShipLocation(pchar, "Lavega_port");
		setWDMPointXZ("Lavega_port"); // на всякий
		DoQuestReloadToLocation("LaVega_port", "reload", "reload1", "Mtraxx_CartahenaToSea");
	}
	else if (sQuestName == "Mtraxx_CartahenaToSea") // формируем эскадру // 3 прогона
	{
		pchar.GenQuest.HunterLongPause = true;
		DeleteAttribute(pchar, "questTemp.NoFast");
		sld = ItemsFromID("lcheer");
		sld.shown = false;
		chrDisableReloadToLocation = false;
		DeleteAttribute(pchar, "questTemp.Mtraxx.InTavern");
		LAi_LocationDisableOfficersGen("LaVega_tavern", false);
		LocatorReloadEnterDisable("LaVega_port", "reload1_back", true);
		// присоединяем эскадру к ГГ. Тиракс
		sld = characterFromId("Terrax");
		FantomMakeCoolSailor(sld, SHIP_LINESHIP, StringFromKey("Roger_94"), CANNON_TYPE_CULVERINE_LBS36, 110, 110, 110);
		Mtraxx_MarkusSetShipParameter();
		SetCharacterGoods(sld, GOOD_BALLS, 5000);
		SetCharacterGoods(sld, GOOD_GRAPES, 2000);
		SetCharacterGoods(sld, GOOD_KNIPPELS, 1000);
		SetCharacterGoods(sld, GOOD_BOMBS, 3000);
		SetCharacterGoods(sld, GOOD_POWDER, 11000);
		SetCharacterGoods(sld, GOOD_WEAPON, 1000);
		SetCharacterGoods(sld, GOOD_FOOD, 2500);
		SetCharacterGoods(sld, GOOD_MEDICAMENT, 900);
		SetCharacterGoods(sld, GOOD_RUM, 300);
		SetCharacterGoods(sld, GOOD_PLANKS, 300);
		SetCharacterGoods(sld, GOOD_SAILCLOTH, 50);
		SetCharacterPerk(sld, "AdvancedBattleState");
		SetCharacterPerk(sld, "ShipDefenseProfessional");
		SetCharacterPerk(sld, "Carpenter");
		SetCharacterPerk(sld, "Builder"); 
		LAi_SetImmortal(sld, false);
		sld.ShipHideImmortal = 1000; // непотопляемый корабль
		sld.SeaBoss = 0.8;
		Character_SetAbordageEnable(sld, false); // нельзя абордировать
		sld.Tasks.CanBoarding = false; // запрет идти на абордаж - дубль
		sld.Tasks.CanChangeShipAfterBoarding = false; // запрет меняться кораблями - дубль
		LAi_SetCheckMinHP(sld, 10, true, ""); // скрытое бессмертие
		sld.DontDeskTalk = true;
		SetCharacterRemovable(sld, false);
		sld.CompanionEnemyEnable = false; //всегда друзья
		SetCompanionIndex(pchar, -1, sti(sld.index));
		sld.loyality = MAX_LOYALITY;
		pchar.quest.mtraxx_ship_fail1.win_condition.l1 = "NPC_Death";
		pchar.quest.mtraxx_ship_fail1.win_condition.l1.character = "Terrax";
		pchar.quest.mtraxx_ship_fail1.function = "Mtraxx_MarkusGameOver"; // для шибко грамотных
		// Лысый Джеффри
		sld = characterFromId("Jeffry");
		SetCharacterGoods(sld, GOOD_BALLS, 1000);
		SetCharacterGoods(sld, GOOD_GRAPES, 800);
		SetCharacterGoods(sld, GOOD_KNIPPELS, 700);
		SetCharacterGoods(sld, GOOD_BOMBS, 1000);
		SetCharacterGoods(sld, GOOD_POWDER, 3500);
		SetCharacterGoods(sld, GOOD_WEAPON, 700);
		SetCharacterGoods(sld, GOOD_FOOD, 2000);
		SetCharacterGoods(sld, GOOD_MEDICAMENT, 600);
		SetCharacterGoods(sld, GOOD_RUM, 200);
		SetCharacterGoods(sld, GOOD_PLANKS, 100);
		SetCharacterGoods(sld, GOOD_SAILCLOTH, 50);
		RealShips[sti(sld.Ship.Type)].MaxCrew = 460;
		UpgradeShipParameter(sld, "MaxCrew");
		int hcrew = GetMaxCrewQuantity(sld);
		SetCrewQuantity(sld, hcrew);
		sld.Ship.Crew.Morale = 100;
		sld.Ship.Crew.Exp.Sailors = 90;
		sld.Ship.Crew.Exp.Cannoners = 90;
		sld.Ship.Crew.Exp.Soldiers = 90;
		LAi_SetImmortal(sld, false);
		sld.ShipHideImmortal = 800; // непотопляемый корабль
		sld.SeaBoss = 0.8;
		LAi_SetCheckMinHP(sld, 10, true, ""); // скрытое бессмертие
		Character_SetAbordageEnable(sld, false); // нельзя абордировать
		sld.Tasks.CanBoarding = false; // запрет идти на абордаж - дубль
		sld.Tasks.CanChangeShipAfterBoarding = false; // запрет меняться кораблями - дубль
		sld.DontDeskTalk = true;
		SetCharacterRemovable(sld, false);
		sld.CompanionEnemyEnable = false; //всегда друзья
		SetCompanionIndex(pchar, -1, sti(sld.index));
		sld.loyality = MAX_LOYALITY;
		// Тесак Пелли
		sld = characterFromId("Pelly");
		SetCharacterGoods(sld, GOOD_BALLS, 500);
		SetCharacterGoods(sld, GOOD_GRAPES, 700);
		SetCharacterGoods(sld, GOOD_KNIPPELS, 400);
		SetCharacterGoods(sld, GOOD_BOMBS, 700);
		SetCharacterGoods(sld, GOOD_POWDER, 2300);
		SetCharacterGoods(sld, GOOD_WEAPON, 400);
		SetCharacterGoods(sld, GOOD_FOOD, 800);
		SetCharacterGoods(sld, GOOD_MEDICAMENT, 300);
		SetCharacterGoods(sld, GOOD_RUM, 100);
		SetCharacterGoods(sld, GOOD_PLANKS, 50);
		SetCharacterGoods(sld, GOOD_SAILCLOTH, 20);
		RealShips[sti(sld.Ship.Type)].SpeedRate = 17.2;
		SetRandGeraldSail(sld, PIRATE);
		hcrew = GetMaxCrewQuantity(sld);
		SetCrewQuantity(sld, hcrew);
		sld.Ship.Crew.Morale = 100;
		sld.Ship.Crew.Exp.Sailors = 90;
		sld.Ship.Crew.Exp.Cannoners = 90;
		sld.Ship.Crew.Exp.Soldiers = 90;
		LAi_SetImmortal(sld, false);
		sld.ShipHideImmortal = 500; // непотопляемый корабль
		sld.SeaBoss = 0.8;
		LAi_SetCheckMinHP(sld, 10, true, ""); // скрытое бессмертие
		Character_SetAbordageEnable(sld, false); // нельзя абордировать
		sld.Tasks.CanBoarding = false; // запрет идти на абордаж - дубль
		sld.Tasks.CanChangeShipAfterBoarding = false; // запрет меняться кораблями - дубль
		sld.DontDeskTalk = true;
		SetCharacterRemovable(sld, false);
		sld.CompanionEnemyEnable = false; //всегда друзья
		SetCompanionIndex(pchar, -1, sti(sld.index));
		sld.loyality = MAX_LOYALITY;
		// Бернар Венсан
		sld = characterFromId("Mtr_Vensan");
		sld.Ship.Crew.Morale = 100;
		sld.Ship.Crew.Exp.Sailors = 70;
		sld.Ship.Crew.Exp.Cannoners = 70;
		sld.Ship.Crew.Exp.Soldiers = 70;
		LAi_SetImmortal(sld, false);
		sld.ShipHideImmortal = 400; // непотопляемый корабль
		sld.SeaBoss = 0.8;
		LAi_SetCheckMinHP(sld, 10, true, ""); // скрытое бессмертие
		Character_SetAbordageEnable(sld, false); // нельзя абордировать
		sld.Tasks.CanBoarding = false; // запрет идти на абордаж - дубль
		sld.Tasks.CanChangeShipAfterBoarding = false; // запрет меняться кораблями - дубль
		sld.DontDeskTalk = true;
		SetCharacterRemovable(sld, false);
		sld.CompanionEnemyEnable = false; //всегда друзья
		SetCompanionIndex(pchar, -1, sti(sld.index));
		sld.loyality = MAX_LOYALITY;
		// подготовим Картахену
		i = FindColony("Cartahena");
		colonies[i].DontSetShipInPort = true;
		// прерывания на доплыть и таймер 20 дней
		pchar.quest.mtraxx_cartahena_sail.win_condition.l1 = "location";
		pchar.quest.mtraxx_cartahena_sail.win_condition.l1.location = "Cartahena";
		pchar.quest.mtraxx_cartahena_sail.function = "Mtraxx_CartahenaArrive";
		SetFunctionTimerCondition("Mtraxx_CartahenaSailOver", 0, 0, 20, false); 
		AddQuestRecord("Roger_9", "1");
		
		// Captain Beltrop, 12.09.21, отключаем морских ОЗГов на время
		pchar.GenQuest.SeaHunter2Pause = true;
		SeaHunter_Delete();
	} 
	else if (sQuestName == "Mtraxx_CartahenaAbandon") // в бухте Ковеньяс
	{
		chrDisableReloadToLocation = true;
		LAi_LocationDisableOfficersGen("shore25", true); // офицеров не пускать
		LocatorReloadEnterDisable("shore25", "reload1_back", true);
		sld = CharacterFromID("Terrax");
		ChangeCharacterAddressGroup(sld, "shore25", "rld", "loc0");
		CharacterDelAngry(sld);
		sld.dialog.currentnode = "mtraxx_99";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 2.0);
		sld = CharacterFromID("Jeffry");
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, "shore25", "rld", "loc12");
		sld = CharacterFromID("Pelly");
		LAi_SetImmortal(sld, false);
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, "shore25", "rld", "loc11");
		sld = CharacterFromID("Lepricon");
		LAi_SetActorType(sld);
		sld.viper = true;
		ChangeCharacterAddressGroup(sld, "shore25", "rld", "loc9");
		for (i = 5; i <= 10; i++) // буканьеры Леприкона
		{
			sld = GetCharacter(NPC_GenerateCharacter("Lepricons_bukaneers_" + i, "mercen_" + i, "man", "man", 25, PIRATE, -1, true, "quest"));
			FantomMakeCoolFighter(sld, 25, 65, 65, LinkRandPhrase("blade_04", "blade_06", "topor_04"), "pistol3", "grapeshot", 200);
			LAi_CharacterDisableDialog(sld);
			TakeNItems(sld, "potion2", 5);
			TakeNItems(sld, "potion3", 2);
			TakeNItems(sld, "potion4", 2);
			ChangeCharacterAddressGroup(sld, "shore25", "rld", "aloc2");
			LAi_SetWarriorType(sld);
			LAi_CharacterDisableDialog(sld);
		}
		// выводим из компаньонов всех, кроме Тесака
		sld = CharacterFromID("Terrax");
		RemoveCharacterCompanion(pchar, sld);
		sld.AlwaysFriend = true;
		sld.ShipEnemyDisable = true; 
		sld = characterFromId("Jeffry");
		RemoveCharacterCompanion(pchar, sld);
		sld.AlwaysFriend = true;
		sld.ShipEnemyDisable = true; 
		sld = characterFromId("Mtr_Vensan");
		RemoveCharacterCompanion(pchar, sld);
		sld.AlwaysFriend = true;
		sld.ShipEnemyDisable = true; 
		// в группу пиратов
		Group_FindOrCreateGroup("Terrax_SeaGroup");
		Group_AddCharacter("Terrax_SeaGroup", "Terrax");
		Group_AddCharacter("Terrax_SeaGroup", "Jeffry");
		Group_AddCharacter("Terrax_SeaGroup", "Mtr_Vensan");
		Group_SetGroupCommander("Terrax_SeaGroup", "Terrax");
		Group_SetTaskNone("Terrax_SeaGroup");
		Group_SetAddress("Terrax_SeaGroup", "Cartahena", "quest_ships", "quest_ship_6");
		Group_LockTask("Terrax_SeaGroup");
	}
	else if (sQuestName == "Mtraxx_CartahenaPrepareFortBattle_Delay")
	{
		if (!CheckAttribute(pchar, "questTemp.Mtraxx.Cartahena.Fort")) return true;
		sld = CharacterFromID("Cartahena Fort Commander");
		Fort_SetAbordageMode(pchar, sld);
		AutoSave();
		// Mtraxx_CartahenaPrepareFortBattle();
	}
	else if (sQuestName == "Mtraxx_CartahenaFortFirstBattle") // бой в цитадели форта // патч 17/1
	{
		PlaySound("interface\" + LanguageGetLanguage() + "\_GTBoard2.wav");
		iRank = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE + 5;
		bDisableCharacterMenu = true; // лочим F2
		InterfaceStates.Buttons.Save.enable = false; // запретить сохраняться
		locations[FindLocation("Cartahena_Town")].QuestCapture = true;
		locations[FindLocation("Cartahena_Fort")].QuestCapture = true;
		// наши
		sld = CharacterFromID("Terrax"); // Тиракс
		LAi_CharacterDisableDialog(sld);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		ChangeCharacterAddressGroup(sld, "BOARDING_FORT", "rld", "loc0");
		for (i = 1; i <= 3; i++) // офицеры ГГ
		{
			idx = GetOfficersIndex(pchar, i);
			if (idx < 1) continue;
			sld = &Characters[idx];
			ChangeCharacterAddressGroup(sld, "BOARDING_FORT", "rld", "loc" + (i + 3));
		}
		// расчёт количества десанта, 45% от общего числа
		iTotalTemp = makeint((sti(pchar.questTemp.Mtraxx.Cartahena.Crew) / 40) * 0.45);
		if (iTotalTemp < 1) iTotalTemp = 1;
		if (iTotalTemp > 25) iTotalTemp = 25;
		log_Testinfo("Наших с оружием - " + iTotalTemp + " бойцов");
		for (i = 1; i <= iTotalTemp; i++)
		{
			if (i < 3) // мушкетеры, 2 шт
			{
				sld = GetCharacter(NPC_GenerateCharacter("Mtr_CartahenaFort1Pirate_" + i, "mush_ctz_" + (i + 6), "man", "mushketer", iRank, PIRATE, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, iRank, 60, 60, "", "mushket3", "grapeshot", 170);
				LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "grapeshot");
				if (iTotalTemp > 15) sld.cirassId = Items_FindItemIdx("cirass1");
			}
			else
			{
				sld = GetCharacter(NPC_GenerateCharacter("Mtr_CartahenaFort1Pirate_" + i, "citiz_" + (rand(9) + 41), "man", "man", iRank, PIRATE, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, iRank, 60, 60, LinkRandPhrase("blade_03", "blade_05", "blade_07"), "pistol1", "bullet", 150);
				if (iTotalTemp > 15) sld.cirassId = Items_FindItemIdx("cirass2");
			}
			ChangeCharacterAddressGroup(sld, "BOARDING_FORT", "rld", "loc" + i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			DeleteAttribute(sld, "SaveItemsForDead");
			DeleteAttribute(sld, "DontClearDead");
			LAi_CharacterDisableDialog(sld);
		}
		// испанцы
		LAi_group_Delete("EnemyFight");
		for (i = 1; i <= 25; i++)
		{
			if (i == 1 || i == 5 || i == 8 || i == 9 || i == 11 || i == 12) // мушкетеры, 6 шт
			{
				sld = GetCharacter(NPC_GenerateCharacter("Mtr_CartahenaFort1Guard_" + i, "mush_spa_" + (rand(2) + 1), "man", "mushketer", iRank, SPAIN, -1, false, "soldier"));
				if (i < 9) 
				{
					FantomMakeCoolFighter(sld, iRank, 60, 60, "", "mushket1", "cartridge", 170);
					LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "cartridge");
				}
				else 
				{
					FantomMakeCoolFighter(sld, iRank, 60, 60, "", "mushket3", "grapeshot", 170);
					LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "grapeshot");
				}
				if (MOD_SKILL_ENEMY_RATE > 2) sld.cirassId = Items_FindItemIdx("cirass1");
				sld.MusketerDistance = 0;
			}
			else
			{
				if (i == 14) // офицер
				{
					sld = GetCharacter(NPC_GenerateCharacter("Mtr_CartahenaFort1Guard_" + i, "off_spa_4", "man", "man", iRank + 5, SPAIN, -1, false, "soldier"));
					FantomMakeCoolFighter(sld, iRank + 5, 70, 70, "topor_04", "pistol4", "cartridge", 200);
					SetCharacterPerk(sld, "SwordplayProfessional");
					SetCharacterPerk(sld, "Gunman");
					SetCharacterPerk(sld, "GunProfessional");
					sld.cirassId = Items_FindItemIdx("cirass1");
				}
				else
				{
					sld = GetCharacter(NPC_GenerateCharacter("Mtr_CartahenaFort1Guard_" + i, "sold_spa_" + (rand(7) + 1), "man", "man", iRank, SPAIN, -1, false, "soldier"));
					FantomMakeCoolFighter(sld, iRank, 60, 60, LinkRandPhrase("blade_08", "blade_12", "blade_14"), "pistol1", "bullet", 150);
					if (MOD_SKILL_ENEMY_RATE > 2) sld.cirassId = Items_FindItemIdx("cirass2");
				}
			}
			ChangeCharacterAddressGroup(sld, "BOARDING_FORT", "rld", "aloc" + i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			DeleteAttribute(sld, "SaveItemsForDead");
			DeleteAttribute(sld, "DontClearDead");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "Mtraxx_CartahenaFortFirstBattleEnd");
		LAi_SetFightMode(pchar, true);
	}
	else if (sQuestName == "Mtraxx_CartahenaFortFirstBattleEnd") // завершили бой в цитадели
	{
		LAi_SetFightMode(pchar, false);
		PlaySound("interface\abordage_wining.wav");
		// считаем выживших
		n = 0;
		for (i = 1; i <= iTotalTemp; i++)
		{
			if(!CharacterIsAlive("Mtr_CartahenaFort1Pirate_" + i)) continue;
			sld = CharacterFromID("Mtr_CartahenaFort1Pirate_" + i);
			if (LAi_GetCharacterHP(sld) > 0) n++;
			sld.lifeday = 0; // патч 17/1
		}
		log_Testinfo("В бою выжило - " + n + " наших бойцов");
		pchar.questTemp.Mtraxx.Cartahena.Fort1Crew = n; // запоминаем
		DoQuestFunctionDelay("Mtraxx_CartahenaFortReloadNext", 5.0);
	}
	else if (sQuestName == "Mtraxx_CartahenaFortSecondBattle") // бой в бастионе
	{
		PlaySound("interface\" + LanguageGetLanguage() + "\_GTBoard2.wav");
		iRank = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE + 5;
		// наши
		sld = CharacterFromID("Jeffry"); // Лысый
		LAi_CharacterDisableDialog(sld);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		ChangeCharacterAddressGroup(sld, "Boarding_bastion1", "rld", "loc8");
		for (i = 1; i <= 3; i++) // офицеры ГГ
		{
			idx = GetOfficersIndex(pchar, i);
			if (idx < 1) continue;
			sld = &Characters[idx];
			ChangeCharacterAddressGroup(sld, "Boarding_bastion1", "rld", "loc" + i);
		}
		// расчёт количества десанта, 28% от общего числа
		iTotalTemp = makeint((sti(pchar.questTemp.Mtraxx.Cartahena.Crew) / 40) * 0.28);
		if (iTotalTemp < 1) iTotalTemp = 1;
		if (iTotalTemp > 15) iTotalTemp = 15;
		log_Testinfo("Наших с оружием - " + iTotalTemp + " бойцов");
		for (i = 1; i <= iTotalTemp; i++)
		{
			if (i < 3) // мушкетеры, 2 шт
			{
				sld = GetCharacter(NPC_GenerateCharacter("Mtr_CartahenaFort2Pirate_" + i, "mush_ctz_" + (i + 6), "man", "mushketer", iRank, PIRATE, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, iRank, 60, 60, "", "mushket3", "grapeshot", 170);
				LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "grapeshot");
				if (iTotalTemp > 10) sld.cirassId = Items_FindItemIdx("cirass1");
			}
			else
			{
				sld = GetCharacter(NPC_GenerateCharacter("Mtr_CartahenaFort2Pirate_" + i, "citiz_" + (rand(9) + 41), "man", "man", iRank, PIRATE, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, iRank, 60, 60, LinkRandPhrase("blade_03", "blade_05", "blade_07"), "pistol1", "bullet", 150);
				if (iTotalTemp > 10) sld.cirassId = Items_FindItemIdx("cirass2");
			}
			ChangeCharacterAddressGroup(sld, "Boarding_bastion1", "rld", "loc" + i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			DeleteAttribute(sld, "SaveItemsForDead");
			DeleteAttribute(sld, "DontClearDead");
			LAi_CharacterDisableDialog(sld);
		}
		// испанцы
		LAi_group_Delete("EnemyFight");
		for (i = 1; i <= 15; i++)
		{
			if (i == 7 || i == 13 || i == 15) // мушкетеры, 3 шт
			{
				sld = GetCharacter(NPC_GenerateCharacter("Mtr_CartahenaFort2Guard_" + i, "mush_spa_" + (rand(2) + 1), "man", "mushketer", iRank, SPAIN, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, iRank, 60, 60, "", "mushket3", "grapeshot", 170);
				LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "grapeshot");
				if (MOD_SKILL_ENEMY_RATE > 2) sld.cirassId = Items_FindItemIdx("cirass1");
				sld.MusketerDistance = 0;
			}
			else
			{
				if (i == 14) // офицер
				{
					sld = GetCharacter(NPC_GenerateCharacter("Mtr_CartahenaFort2Guard_" + i, "off_spa_5", "man", "man", iRank + 5, SPAIN, -1, false, "soldier"));
					FantomMakeCoolFighter(sld, iRank + 5, 70, 70, "topor_04", "pistol4", "cartridge", 200);
					SetCharacterPerk(sld, "SwordplayProfessional");
					SetCharacterPerk(sld, "Gunman");
					SetCharacterPerk(sld, "GunProfessional");
					sld.cirassId = Items_FindItemIdx("cirass1");
				}
				else
				{
					sld = GetCharacter(NPC_GenerateCharacter("Mtr_CartahenaFort2Guard_" + i, "sold_spa_" + (rand(7) + 1), "man", "man", iRank, SPAIN, -1, false, "soldier"));
					FantomMakeCoolFighter(sld, iRank, 60, 60, LinkRandPhrase("blade_08", "blade_12", "blade_14"), "pistol1", "bullet", 150);
					if (MOD_SKILL_ENEMY_RATE > 2) sld.cirassId = Items_FindItemIdx("cirass2");
				}
			}
			ChangeCharacterAddressGroup(sld, "Boarding_bastion1", "rld", "aloc" + i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			DeleteAttribute(sld, "SaveItemsForDead");
			DeleteAttribute(sld, "DontClearDead");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "Mtraxx_CartahenaFortSecondBattleEnd");
		LAi_SetFightMode(pchar, true);
	}
	else if (sQuestName == "Mtraxx_CartahenaFortSecondBattleEnd") // завершили бой в бастионе
	{
		LAi_SetFightMode(pchar, false);
		PlaySound("interface\abordage_wining.wav");
		// считаем выживших
		n = 0;
		for (i = 1; i <= iTotalTemp; i++)
		{
			if(!CharacterIsAlive("Mtr_CartahenaFort2Pirate_" + i)) continue;
			sld = CharacterFromID("Mtr_CartahenaFort2Pirate_" + i);
			if (LAi_GetCharacterHP(sld) > 0) n++;
			sld.lifeday = 0; // патч 17/1
		}
		log_Testinfo("В бою выжило - " + n + " наших бойцов");
		pchar.questTemp.Mtraxx.Cartahena.Fort2Crew = n; // запоминаем
		DoQuestFunctionDelay("Mtraxx_CartahenaFortReloadEnd", 5.0);
	}
	else if (sQuestName == "Mtraxx_CartahenaFortThirdBattle") // бой во дворе
	{
		PlaySound("interface\" + LanguageGetLanguage() + "\_GTBoard2.wav");
		iRank = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE + 5;
		// наши
		sld = CharacterFromID("Pelly"); // Тесак
		LAi_CharacterDisableDialog(sld);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		ChangeCharacterAddressGroup(sld, "Boarding_fortyard", "rld", "loc8");
		for (i = 1; i <= 3; i++) // офицеры ГГ
		{
			idx = GetOfficersIndex(pchar, i);
			if (idx < 1) continue;
			sld = &Characters[idx];
			ChangeCharacterAddressGroup(sld, "Boarding_fortyard", "rld", "loc" + i);
		}
		// расчёт количества десанта, 27% от общего числа
		iTotalTemp = makeint((sti(pchar.questTemp.Mtraxx.Cartahena.Crew) / 40) * 0.27);
		if (iTotalTemp < 1) iTotalTemp = 1;
		if (iTotalTemp > 15) iTotalTemp = 15;
		log_Testinfo("Наших с оружием - " + iTotalTemp + " бойцов");
		for (i = 1; i <= iTotalTemp; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("Mtr_CartahenaFort3Pirate_" + i, "citiz_" + (rand(9) + 41), "man", "man", iRank, PIRATE, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, 60, 60, LinkRandPhrase("blade_03", "blade_05", "blade_07"), "pistol1", "bullet", 150);
			if (iTotalTemp > 10) sld.cirassId = Items_FindItemIdx("cirass2");
			ChangeCharacterAddressGroup(sld, "Boarding_fortyard", "rld", "loc" + i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			DeleteAttribute(sld, "SaveItemsForDead");
			DeleteAttribute(sld, "DontClearDead");
			LAi_CharacterDisableDialog(sld);
		}
		// испанцы
		LAi_group_Delete("EnemyFight");
		for (i = 1; i <= 15; i++)
		{
			if (i == 14) // офицер
			{
				sld = GetCharacter(NPC_GenerateCharacter("Mtr_CartahenaFort3Guard_" + i, "off_spa_3", "man", "man", iRank + 5, SPAIN, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, iRank + 5, 70, 70, "topor_04", "pistol4", "cartridge", 200);
				SetCharacterPerk(sld, "SwordplayProfessional");
				SetCharacterPerk(sld, "Gunman");
				SetCharacterPerk(sld, "GunProfessional");
				sld.cirassId = Items_FindItemIdx("cirass1");
			}
			else
			{
				sld = GetCharacter(NPC_GenerateCharacter("Mtr_CartahenaFort3Guard_" + i, "sold_spa_" + (rand(7) + 1), "man", "man", iRank, SPAIN, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, iRank, 60, 60, LinkRandPhrase("blade_08", "blade_12", "blade_14"), "pistol1", "bullet", 150);
				if (MOD_SKILL_ENEMY_RATE > 2) sld.cirassId = Items_FindItemIdx("cirass2");
			}
			ChangeCharacterAddressGroup(sld, "Boarding_fortyard", "rld", "aloc" + i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			DeleteAttribute(sld, "SaveItemsForDead");
			DeleteAttribute(sld, "DontClearDead");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "Mtraxx_CartahenaFortThirdBattleEnd");
		LAi_SetFightMode(pchar, true);
	}
	else if (sQuestName == "Mtraxx_CartahenaFortThirdBattleEnd") // завершили бой во дворе
	{
		LAi_SetFightMode(pchar, false);
		PlaySound("interface\abordage_wining.wav");
		// считаем выживших
		n = 0;
		for (i = 1; i <= iTotalTemp; i++)
		{
			if(!CharacterIsAlive("Mtr_CartahenaFort3Pirate_" + i)) continue;
			sld = CharacterFromID("Mtr_CartahenaFort3Pirate_" + i); // belamour: убрать пиратов Тесака из Бастиона
			if (LAi_GetCharacterHP(sld) > 0) n++;
			sld.lifeday = 0; // патч 17/1
		}
		log_Testinfo("В бою выжило - " + n + " наших бойцов");
		pchar.questTemp.Mtraxx.Cartahena.Fort3Crew = n; // запоминаем
		DoQuestFunctionDelay("Mtraxx_CartahenaExittownReload", 5.0);
	}
	else if (sQuestName == "Mtraxx_CartahenaExittownBattle") // бой на выходе из города
	{
		PlaySound("interface\" + LanguageGetLanguage() + "\_GTBoard2.wav");
		iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+5;
		chrDisableReloadToLocation = true;
		// наши
		for (i=1; i<=3; i++) // офицеры ГГ
		{
			idx = GetOfficersIndex(pchar, i);
			if (idx < 1) continue;
			sld = &Characters[idx];
			ChangeCharacterAddressGroup(sld, "Cartahena_ExitTown", "officers", "reload3_"+i);
		}
		sld = CharacterFromID("Lepricon"); // Леприкон
		LAi_CharacterDisableDialog(sld);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		ChangeCharacterAddressGroup(sld, "Cartahena_ExitTown", "rld", "aloc12");
		for (i=5; i<=10; i++) // буканьеры Леприкона
		{
			sld = CharacterFromID("Lepricons_bukaneers_"+i);
			if (i < 10) ChangeCharacterAddressGroup(sld, "Cartahena_ExitTown", "rld", "aloc"+(i-4));
			else ChangeCharacterAddressGroup(sld, "Cartahena_ExitTown", "rld", "aloc11");
			LAi_CharacterDisableDialog(sld);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			sld.lifeday = 3;
		}
		// испанцы
		LAi_group_Delete("EnemyFight");
		for (i=1; i<=12; i++)
		{
			if (i < 3) // мушкетеры, 2 шт
			{
				sld = GetCharacter(NPC_GenerateCharacter("Mtr_CartahenaExittownGuard_"+i, "mush_spa_"+(rand(2)+1), "man", "mushketer", iRank, SPAIN, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, iRank, 60, 60, "", "mushket1", "cartridge", 170);
				LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "cartridge");
				if (MOD_SKILL_ENEMY_RATE > 2) sld.cirassId = Items_FindItemIdx("cirass1");
				ChangeCharacterAddressGroup(sld, "Cartahena_ExitTown", "reload", "reload4");
			}
			else
			{
				if (i == 12) // офицер
				{
					sld = GetCharacter(NPC_GenerateCharacter("Mtr_CartahenaExittownGuard_"+i, "off_spa_5", "man", "man", iRank+5, SPAIN, -1, false, "soldier"));
					FantomMakeCoolFighter(sld, iRank+5, 70, 70, "topor_04", "pistol4", "cartridge", 200);
					SetCharacterPerk(sld, "SwordplayProfessional");
					SetCharacterPerk(sld, "Gunman");
					SetCharacterPerk(sld, "GunProfessional");
					sld.cirassId = Items_FindItemIdx("cirass1");
					ChangeCharacterAddressGroup(sld, "Cartahena_ExitTown", "rld", "aloc15");
				}
				else
				{
					sld = GetCharacter(NPC_GenerateCharacter("Mtr_CartahenaExittownGuard_"+i, "sold_spa_"+(rand(7)+1), "man", "man", iRank, SPAIN, -1, false, "soldier"));
					FantomMakeCoolFighter(sld, iRank, 60, 60, LinkRandPhrase("blade_08","blade_12","blade_14"), "pistol1", "bullet", 150);
					if (MOD_SKILL_ENEMY_RATE > 2) sld.cirassId = Items_FindItemIdx("cirass2");
					if (i > 5 && i < 11) ChangeCharacterAddressGroup(sld, "Cartahena_ExitTown", "rld", "aloc"+i);
					else ChangeCharacterAddressGroup(sld, "Cartahena_ExitTown", "rld", "aloc14");
				}
			}
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			DeleteAttribute(sld, "SaveItemsForDead");
			DeleteAttribute(sld, "DontClearDead");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "Mtraxx_CartahenaExittownBattleEnd");
		LAi_SetFightMode(pchar, true);
	}
	else if (sQuestName == "Mtraxx_CartahenaExittownBattleEnd") // завершили бой у ворот
	{
		LAi_SetFightMode(pchar, false);
		PlaySound("interface\abordage_wining.wav");
		setCharacterShipLocation(pchar, "Cartahena_Town");
		setWDMPointXZ("Cartahena_Town");
		locations[FindLocation("Cartahena_Town")].QuestCapture = true;
		locations[FindLocation("Cartahena_Townhall")].QuestCapture = true;
		DoQuestFunctionDelay("Mtraxx_CartahenaTownReload", 5.0);
		for (i = 5; i <= 10; i++) // патч 17/1
		{
			if(!CharacterIsAlive("Lepricons_bukaneers_" + i)) continue;
			sld = CharacterFromID("Lepricons_bukaneers_" + i);
			sld.lifeday = 0; 
		}
		// суммируем всех оставшихся бойцов
		iTotalTemp = sti(pchar.questTemp.Mtraxx.Cartahena.Fort1Crew) + sti(pchar.questTemp.Mtraxx.Cartahena.Fort2Crew) + sti(pchar.questTemp.Mtraxx.Cartahena.Fort3Crew);
		pchar.questTemp.Mtraxx.Cartahena.FortAliveCrew = iTotalTemp; // выживший десант в форте, из него идут на город
	}
	else if (sQuestName == "Mtraxx_CartahenaTownBattle") // бой в городе
	{
		// прячем нищеброда
		sld = characterFromId("Cartahena_Poorman");
		ChangeCharacterAddressGroup(sld, "none", "", "");
		PlaySound("interface\" + LanguageGetLanguage() + "\_GTBoard2.wav");
		iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+5;
		// считаем выживших бойцов. Участвует только 20 рыл. Их запоминаем.
		if (iTotalTemp > 20) n = 20;
		else n = iTotalTemp;
		iTotalTemp = n; // запомнили в глобальную переменную
		pchar.questTemp.Mtraxx.Cartahena.TownCrew = n;
		// наши
		for (i=1; i<=3; i++) // офицеры ГГ
		{
			idx = GetOfficersIndex(pchar, i);
			if (idx < 1) continue;
			sld = &Characters[idx];
			ChangeCharacterAddressGroup(sld, "Cartahena_Town", "officers", "gate_back_"+i);
		}
		sld = CharacterFromID("Terrax"); // Тиракс
		LAi_CharacterDisableDialog(sld);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		ChangeCharacterAddressGroup(sld, "Cartahena_Town", "reload", "houseSp2");
		sld = CharacterFromID("Jeffry"); // Лысый
		LAi_CharacterDisableDialog(sld);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		ChangeCharacterAddressGroup(sld, "Cartahena_Town", "reload", "houseSp1");
		sld = CharacterFromID("Pelly"); // Тесак
		LAi_CharacterDisableDialog(sld);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		ChangeCharacterAddressGroup(sld, "Cartahena_Town", "reload", "houseF2");
		sld = CharacterFromID("Lepricon"); // Леприкон
		LAi_CharacterDisableDialog(sld);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		ChangeCharacterAddressGroup(sld, "Cartahena_Town", "reload", "houseS2");
		log_Testinfo("Наших с оружием - "+iTotalTemp+" бойцов");
		for (i=1; i<=iTotalTemp; i++)
		{
			if (i < 3) // мушкетеры, 2 шт
			{
				sld = GetCharacter(NPC_GenerateCharacter("Mtr_CartahenaTownPirate_"+i, "mush_ctz_"+(i+6), "man", "mushketer", iRank, PIRATE, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, iRank, 60, 60, "", "mushket3", "grapeshot", 170);
				LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "grapeshot");
				if (iTotalTemp > 17) sld.cirassId = Items_FindItemIdx("cirass1");
			}
			else
			{
					sld = GetCharacter(NPC_GenerateCharacter("Mtr_CartahenaTownPirate_"+i, "citiz_"+(rand(9)+41), "man", "man", iRank, PIRATE, -1, false, "soldier"));
					FantomMakeCoolFighter(sld, iRank, 60, 60, LinkRandPhrase("blade_03","blade_05","blade_07"), "pistol1", "bullet", 150);
					if (iTotalTemp > 17) sld.cirassId = Items_FindItemIdx("cirass2");
			}
			ChangeCharacterAddressGroup(sld, "Cartahena_Town", "goto", "goto"+i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			DeleteAttribute(sld, "SaveItemsForDead");
			DeleteAttribute(sld, "DontClearDead");
			LAi_CharacterDisableDialog(sld);
		}
		// испанцы
		LAi_group_Delete("EnemyFight");
		// офицер
		sld = GetCharacter(NPC_GenerateCharacter("Mtr_CartahenaTownOfficer_"+i, "off_spa_5", "man", "man", iRank+7, SPAIN, -1, false, "soldier"));
		FantomMakeCoolFighter(sld, iRank+7, 75, 75, "topor_04", "pistol4", "cartridge", 220);
		SetCharacterPerk(sld, "SwordplayProfessional");
		SetCharacterPerk(sld, "Gunman");
		SetCharacterPerk(sld, "GunProfessional");
		sld.cirassId = Items_FindItemIdx("cirass1");
		ChangeCharacterAddressGroup(sld, "Cartahena_Town", "quest", "quest1");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		// мушкетеры
		for (i=3; i<=8; i++)
		{
			
			sld = GetCharacter(NPC_GenerateCharacter("Mtr_CartahenaTownMushketer_"+i, "mush_spa_"+(rand(2)+1), "man", "mushketer", iRank, SPAIN, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, 60, 60, "", "mushket1", "cartridge", 170);
			LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "cartridge");
			if (MOD_SKILL_ENEMY_RATE > 2) sld.cirassId = Items_FindItemIdx("cirass1");
			sld.MusketerDistance = 0;
			ChangeCharacterAddressGroup(sld, "Cartahena_Town", "reload", "reload"+i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			DeleteAttribute(sld, "SaveItemsForDead");
			DeleteAttribute(sld, "DontClearDead");
		}
		for (i=1; i<=20; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("Mtr_CartahenaTownGuard_"+i, "sold_spa_"+(rand(7)+1), "man", "man", iRank, SPAIN, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, 60, 60, LinkRandPhrase("blade_08","blade_12","blade_14"), "pistol1", "bullet", 150);
			if (MOD_SKILL_ENEMY_RATE > 2) sld.cirassId = Items_FindItemIdx("cirass2");
			ChangeCharacterAddressGroup(sld, "Cartahena_Town", "patrol", "patrol"+i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			DeleteAttribute(sld, "SaveItemsForDead");
			DeleteAttribute(sld, "DontClearDead");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "Mtraxx_CartahenaTownBattleEnd");
		LAi_SetFightMode(pchar, true);
		// огонь и дым
		CreateLocationParticles("large_smoke", "reload", "houseF1", 3, 0, 0, "torch_deck");
		CreateLocationParticles("shipfire", "reload", "houseF1", 0, 0, 0, "fortfire");
		CreateLocationParticles("large_smoke", "reload", "houseS4", 3, 0, 0, "torch_deck");
		CreateLocationParticles("shipfire", "reload", "houseS4", 0, 0, 0, "fortfire");
		CreateLocationParticles("large_smoke", "reload", "houseH2", 3, 0, 0, "torch_deck");
		CreateLocationParticles("shipfire", "reload", "houseH2", 0, 0, 0, "fortfire");
		CreateLocationParticles("large_smoke", "reload", "houseS3", 3, 0, 0, "torch_deck");
		CreateLocationParticles("shipfire", "reload", "houseS3", 0, 0, 0, "fortfire");
		CreateLocationParticles("large_smoke", "reload", "houseH1", 3, 0, 0, "torch_deck");
		CreateLocationParticles("shipfire", "reload", "houseH1", 0, 0, 0, "fortfire");
	}
	else if (sQuestName == "Mtraxx_CartahenaTownBattleEnd") // закончили бой в городе
	{
		LAi_SetFightMode(pchar, false);
		PlaySound("interface\abordage_wining.wav");
		InterfaceStates.Buttons.Save.enable = true; // разрешить сохраняться
		// считаем выживших
		n = 0;
		for (i = 1; i <= iTotalTemp; i++)
		{
			if(!CharacterIsAlive("Mtr_CartahenaTownPirate_" + i)) continue;
			sld = CharacterFromID("Mtr_CartahenaTownPirate_" + i);
			if (LAi_GetCharacterHP(sld) > 0) n++;
			sld.lifeday = 3;
		}
		log_Testinfo("В бою выжило - " + n + " наших бойцов");
		int DeadCrew = iTotalTemp - n; // погибшие в городской боевке
		// бои окончены, считаем всех выживших бойцов по итогу
		int AliveCrew = sti(pchar.questTemp.Mtraxx.Cartahena.FortAliveCrew) - DeadCrew; // выжившие
		pchar.questTemp.Mtraxx.Cartahena.AliveCrew1 = makeint(AliveCrew * 40 * sti(pchar.questTemp.Mtraxx.Cartahena.Crewpercent1) / 100) + 1; // команда ГГ
		pchar.questTemp.Mtraxx.Cartahena.AliveCrew2 = makeint(AliveCrew * 40 * sti(pchar.questTemp.Mtraxx.Cartahena.Crewpercent2) / 100) + 1; // команда Тиракса
		pchar.questTemp.Mtraxx.Cartahena.AliveCrew3 = makeint(AliveCrew * 40 * sti(pchar.questTemp.Mtraxx.Cartahena.Crewpercent3) / 100) + 1; // команда Лысого
		pchar.questTemp.Mtraxx.Cartahena.AliveCrew4 = makeint(AliveCrew * 40 * sti(pchar.questTemp.Mtraxx.Cartahena.Crewpercent4) / 100) + 1; // команда Тесака
		// главарей - в кучу, Тиракса позже, во избежание сбоя
		sld = CharacterFromID("Jeffry");
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, pchar, "", 8.0);
		sld = CharacterFromID("Pelly");
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, pchar, "", 8.0);
		sld = CharacterFromID("Lepricon");
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, pchar, "", 8.0);
		DoQuestCheckDelay("Mtraxx_CartahenaToGovernor", 8.0);
	}
	else if (sQuestName == "Mtraxx_CartahenaToGovernor") // к губеру
	{
		sld = CharacterFromID("Terrax");
		LAi_CharacterEnableDialog(sld);
		sld.dialog.currentnode = "mtraxx_104";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0); 
	}
	else if (sQuestName == "Mtraxx_CartahenaResidence") // в резиденции Картахены
	{
		// прячем настоящего губера и ставим его клон
		sld = CharacterFromID("Cartahena_Mayor");
		ChangeCharacterAddressGroup(sld, "none", "", "");
		sld = GetCharacter(NPC_GenerateCharacter("Mtr_CartahenaMayorClone", "huber_22", "man", "man", 30, SPAIN, -1, false, "officer"));
		SetFantomParamFromRank(sld, 30, true);
		RemoveAllCharacterItems(sld, true);
		sld.name = StringFromKey("Roger_119");
		sld.lastname = StringFromKey("Roger_120");
		sld.dialog.FileName = "Quest\Roger.c";
		sld.dialog.currentnode = "CartahenaMayor";
		ChangeCharacterAddressGroup(sld, "Cartahena_townhall", "goto", "governor1");
		LAi_SetStayType(sld);
	}
	else if (sQuestName == "Mtraxx_CartahenaResidenceWait") // ждём выкупа от губернатора
	{
		DoQuestCheckDelay("Mtraxx_CartahenaResidenceWait1", 5.0);
	}
	else if (sQuestName == "Mtraxx_CartahenaResidenceWait1") // ждём выкупа от губернатора
	{
		SetLaunchFrameFormParam(StringFromKey("Roger_121", NewStr()), "Mtraxx_CartahenaResidenceMayor", 0, 5); // табличка
		WaitDate("", 0, 0, 1, 1, 10); // крутим время
		LaunchFrameForm();
		RefreshLandTime();
		RecalculateJumpTable();
		Whr_UpdateWeather();
	}
	else if (sQuestName == "Mtraxx_CartahenaResidenceMayor") // 
	{
		sld = CharacterFromID("Mtr_CartahenaMayorClone");
		sld.lifeday = 1;
		ChangeCharacterAddressGroup(sld, "Cartahena_Townhall", "reload", "reload1");
		sld.dialog.currentnode = "CartahenaMayor_12";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		OfficersReaction("bad");
	}
	else if (sQuestName == "Mtraxx_CartahenaStreet") // антураж захваченной Картахены
	{
		// огонь и дым
		for (i = 4; i <= 10; i++)
		{
			if (i == 9) continue;
			CreateLocationParticles("large_smoke", "reload", "reload" + i + "_back", 0, 0, 0, "torch_deck");
			CreateLocationParticles("shipfire", "reload", "reload" + i + "_back", 0, 0, 0, "fortfire");
		}
		CreateLocationParticles("large_smoke", "reload", "houseF1", 0, 0, 0, "torch_deck");
		CreateLocationParticles("shipfire", "reload", "houseF1", 0, 0, 0, "fortfire");
		CreateLocationParticles("large_smoke", "reload", "houseS4", 0, 0, 0, "torch_deck");
		CreateLocationParticles("shipfire", "reload", "houseS4", 0, 0, 0, "fortfire");
		CreateLocationParticles("large_smoke", "reload", "houseH2", 0, 0, 0, "torch_deck");
		CreateLocationParticles("shipfire", "reload", "houseH2", 0, 0, 0, "fortfire");
		CreateLocationParticles("large_smoke", "reload", "houseS3", 0, 0, 0, "torch_deck");
		CreateLocationParticles("shipfire", "reload", "houseS3", 0, 0, 0, "fortfire");
		CreateLocationParticles("large_smoke", "reload", "houseH1", 0, 0, 0, "torch_deck");
		CreateLocationParticles("shipfire", "reload", "houseH1", 0, 0, 0, "fortfire");
		for (i = 1; i <= 19; i++) // жертвы нападения
		{
			if (i < 10)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Cartahena_victim_" + i, "citiz_1" + i, "man", "man", 1, SPAIN, 1, true, "quest"));
				SetFantomParamFromRank(sld, 1, true);
				ChangeCharacterAddressGroup(sld, "Cartahena_town", "patrol", "patrol" + i);
			}
			else
			{
				sld = GetCharacter(NPC_GenerateCharacter("Cartahena_victim_" + i, "women_" + (i - 3), "woman", "towngirl", 1, SPAIN, 1, true, "quest"));
				SetFantomParamFromRank(sld, 1, true);
				ChangeCharacterAddressGroup(sld, "Cartahena_town", "goto", "goto" + i);
			}
			RemoveAllCharacterItems(sld, true);
			sld.DontClearDead = true;
			LAi_SetStayType(sld);
			LAi_KillCharacter(sld);
		}
		OfficersReaction("bad");
	}
	else if (sQuestName == "Mtraxx_CartahenaTerraxInFort") // пираты в форте
	{
		sld = CharacterFromID("Terrax");
		sld.dialog.currentnode = "mtraxx_106";
		LAi_SetStayType(sld);
		ChangeCharacterAddressGroup(sld, "Cartahena_fort", "goto", "goto11");
		sld = CharacterFromID("Jeffry");
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, "Cartahena_fort", "goto", "goto21");
		sld = CharacterFromID("Lepricon");
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, "Cartahena_fort", "goto", "goto01");
		sld = CharacterFromID("Mtr_Vensan");
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, "Cartahena_fort", "goto", "goto31");
		// тут делаем расчёт команд кораблей для дележа добычи. Тиракс забирает 50%, остальные 4 корабля - в пропорции от числа команд
		int iCrew1 = GetCrewQuantity(pchar);
		int iCrew2 = GetCrewQuantity(characterFromId("Jeffry"));
		int iCrew3 = GetCrewQuantity(characterFromId("Pelly"));
		int iCrew4 = GetCrewQuantity(characterFromId("Mtr_Vensan"));
		int iCrewT = iCrew1 + iCrew2 + iCrew3 + iCrew4;
		pchar.questTemp.Mtraxx.Cartahena.Gold = makeint(iCrew1 * 100 / iCrewT) * 25; // золото ГГ
		pchar.questTemp.Mtraxx.Cartahena.Money = makeint(iCrew1 * 100 / iCrewT) * 1500; // деньги ГГ
		LocatorReloadEnterDisable("Cartahena_Exittown", "reload3_back", false);
	}
	else if (sQuestName == "Mtraxx_CartahenaComplete") // в городе перед отплытием
	{
		bDisableCharacterMenu = false;
		AddQuestRecord("Roger_9", "8");
		AddQuestUserData("Roger_9", "sGold", sti(pchar.questTemp.Mtraxx.Cartahena.Gold));
		AddQuestUserData("Roger_9", "sMoney", sti(pchar.questTemp.Mtraxx.Cartahena.Money));
		chrDisableReloadToLocation = false;
		for (i = 3; i <= 10; i++)
		{
			LocatorReloadEnterDisable("Cartahena_town", "reload" + i + "_back", true);
		}
		LocatorReloadEnterDisable("Cartahena_town", "gate_back", true);
		LocatorReloadEnterDisable("Cartahena_town", "reload_jail", true);
		AddMoneyToCharacter(pchar, sti(pchar.questTemp.Mtraxx.Cartahena.Money));
		SetCharacterGoods(pchar, GOOD_GOLD, GetCargoGoods(pchar, GOOD_GOLD) + sti(pchar.questTemp.Mtraxx.Cartahena.Gold));
		bQuestDisableMapEnter = false; // открыть карту
		DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		for (i = 4; i <= 10; i++)
		{
			if (i == 9) continue;
			CreateLocationParticles("large_smoke", "reload", "reload" + i + "_back", 3, 0, 0, "torch_deck");
			CreateLocationParticles("shipfire", "reload", "reload" + i + "_back", 0, 0, 0, "fortfire");
		}
		CreateLocationParticles("large_smoke", "reload", "houseF1", 3, 0, 0, "torch_deck");
		CreateLocationParticles("shipfire", "reload", "houseF1", 0, 0, 0, "fortfire");
		CreateLocationParticles("large_smoke", "reload", "houseS4", 3, 0, 0, "torch_deck");
		CreateLocationParticles("shipfire", "reload", "houseS4", 0, 0, 0, "fortfire");
		CreateLocationParticles("large_smoke", "reload", "houseH2", 3, 0, 0, "torch_deck");
		CreateLocationParticles("shipfire", "reload", "houseH2", 0, 0, 0, "fortfire");
		CreateLocationParticles("large_smoke", "reload", "houseS3", 3, 0, 0, "torch_deck");
		CreateLocationParticles("shipfire", "reload", "houseS3", 0, 0, 0, "fortfire");
		CreateLocationParticles("large_smoke", "reload", "houseH1", 3, 0, 0, "torch_deck");
		CreateLocationParticles("shipfire", "reload", "houseH1", 0, 0, 0, "fortfire");
		pchar.quest.mtraxx_cartahena_complete.win_condition.l1 = "location";
		pchar.quest.mtraxx_cartahena_complete.win_condition.l1.location = "Cartahena";
		pchar.quest.mtraxx_cartahena_complete.function = "Mtraxx_CartahenaShipsGoAway";
	}
	else if (sQuestName == "Mtraxx_RetributionStart") // телепорт к бордельмаман
	{
		DoQuestReloadToLocation("Tortuga_SecBrRoom", "reload", "reload1", "");
		pchar.questTemp.Mtraxx.Retribution = "brothel";
		bQuestDisableMapEnter = true; // закрыть карту
		pchar.GenQuest.MapClosedNoBattle = true;
		LAi_SetPlayerType(pchar);
	}
	else if (sQuestName == "Mtraxx_RetributionInBrothel") // в комнате с девочками
	{
		LAi_SetSitType(pchar);
		for (i = 1; i <= 6; i++)
		{
			if (i == 3 || i == 5) continue;
			sld = GetCharacter(NPC_GenerateCharacter("Mtr_TortugaGirl_" + i, "women_" + (i + 19), "woman", "towngirl", 1, FRANCE, 0, true, "quest"));
			SetFantomParamFromRank(sld, 1, true);
			if (i < 3) ChangeCharacterAddressGroup(sld, "Tortuga_Brothel_room", "goto", "goto" + i);
			else ChangeCharacterAddressGroup(sld, "Tortuga_Brothel_room", "reload", "reload1_back");
			LAi_SetCitizenType(sld);
		}
		DoQuestCheckDelay("Mtraxx_RetributionRestInBrothel", 1.3);
	}
	else if (sQuestName == "Mtraxx_RetributionRestInBrothel") // отдых в борделе
	{
		ChangeShowIntarface();
		ResetSound();
		SetMusic("music_piratemusic");
		InterfaceStates.Buttons.Save.enable = false;
		bDisableCharacterMenu = true;
		locCameraRotateAroundHero(0.0, 1.5, 0.0, 0.005, 0.0, 1.5, 0.0, 10000);
		Pchar.FuncCameraFly = "";
		DoQuestCheckDelay("Mtraxx_RetributionFrameInBrothel", 30.0);
		for (i = 1; i <= 3; i++)
		{
			DoQuestCheckDelay("Mtraxx_RetributionVoiceInBrothel_" + i, 2 + i * 6);
		}
	}
	else if (sQuestName == "Mtraxx_RetributionVoiceInBrothel_1") // голоса
	{
		PlaySound("VOICE\Russian\brothel\Shluhi-11.wav");
		PlaySound("ambient\tavern\krujki_003.wav");
		PlaySound("ambient\tavern\naliv_001.wav");
	}
	else if (sQuestName == "Mtraxx_RetributionVoiceInBrothel_2") // голоса
	{
		PlaySound("VOICE\Russian\brothel\Shluhi-12.wav");
		PlaySound("ambient\tavern\krujki_004.wav");
		PlaySound("ambient\tavern\naliv_002.wav");
	}
	else if (sQuestName == "Mtraxx_RetributionVoiceInBrothel_3") // голоса
	{
		PlaySound("VOICE\Russian\brothel\Shluhi-13.wav");
		PlaySound("ambient\tavern\krujki_005.wav");
		PlaySound("ambient\tavern\naliv_003.wav");
	}
	else if (sQuestName == "Mtraxx_RetributionFrameInBrothel") // нагулялся
	{
		PlaySound("ambient\tavern\orijka_003.wav");
		bDisableCharacterMenu = false;
		InterfaceStates.Buttons.Save.enable = true;
		locCameraResetState();
		iTime = sti(environment.time);
		SetLaunchFrameFormParam(StringFromKey("Roger_122", NewStr()), "Mtraxx_RetributionTortugaReload", 0, 5);
		if (IsEquipCharacterByArtefact(pchar, "totem_03")) 	
		{
			AddCharacterHealth(pchar, 16);
			AddCharacterMaxHealth(pchar, 1.0);
		}
		else AddCharacterHealth(pchar, 8);
		LaunchFrameForm();
		RecalculateJumpTable();
		StoreDayUpdate();
		RefreshWeather();
		RefreshLandTime();
		LAi_SetPlayerType(pchar);
		pchar.GenQuest.CamShuttle = 2;
	}
	else if (sQuestName == "Mtraxx_RetributionTortugaReload") // релоад на улицы
	{
		WaitDate("", 0, 0, 2, 6, 5); // крутим время
		DoQuestReloadToLocation("Tortuga_town", "reload", "reload9", "Mtraxx_RetributionTortugaStreets");
	}
	else if (sQuestName == "Mtraxx_RetributionTortugaStreets") // ставим Камиллу
	{
		pchar.questTemp.Mtraxx.Retribution = "tavern";
		PlaySound("ambient\tavern\orijka_002.wav");
		sld = GetCharacter(NPC_GenerateCharacter("Kamilla", "women_16", "woman", "towngirl", 15, FRANCE, -1, true, "quest"));
		SetFantomParamFromRank(sld, 15, true);
		sld.name = StringFromKey("Roger_123");
		sld.lastname = StringFromKey("Roger_124");
		sld.dialog.FileName = "Quest\Roger.c";
		sld.dialog.currentnode = "camilla";
		sld.greeting = "";
		ChangeCharacterAddressGroup(sld, "Tortuga_town", "goto", "goto25");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	else if (sQuestName == "Mtraxx_RetributionToRoom") // в комнате таверны
	{
		sld = characterFromId("Kamilla");
		sld.dialog.currentnode = "camilla_7";
		ChangeCharacterAddressGroup(sld, "Tortuga_tavern_upstairs", "quest", "quest3");
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 2.0);
	}
	else if (sQuestName == "Mtraxx_RetributionRoomSex") // после секса с Камиллой
	{
		bDisableCharacterMenu = false;
		DeleteAttribute(pchar, "GenQuest.FrameLockEsc");
		sld = characterFromId("Kamilla");
		sld.dialog.currentnode = "camilla_12";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
	}
	else if (sQuestName == "Mtraxx_RetributionKamilla") // Камиллу - в церковь
	{
		sld = characterFromId("Kamilla");
		LAi_SetStayType(sld);
		chrDisableReloadToLocation = false;
	}
	else if (sQuestName == "Mtraxx_RetributionBarrels") // 
	{
		DoQuestReloadToLocation("Carataska_jungle_02", "goto", "goto5", "Mtraxx_RetributionFire");
	}
	else if (sQuestName == "Mtraxx_RetributionFire") // осталось только поджечь
	{
		for (i=1; i<=3; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("Mtr_FirePirate_"+i, "citiz_4"+i, "man", "man", 10, PIRATE, 1, false, "soldier"));
			SetFantomParamFromRank(sld, 10, true);
			ChangeCharacterAddressGroup(sld, "Carataska_jungle_02", "quest", "detector1");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 20.0);
		}
		AddQuestRecord("Roger_10", "5");
		pchar.questTemp.Mtraxx.Retribution.Fire = "true";
	}
	else if (sQuestName == "Mtraxx_RetributionGotoRuins") // прерывание на вход в подземелья
	{
		CreateLocationParticles("large_smoke", "quest", "deadfall", 0, 0, 0, "");
		CreateLocationParticles("large_smoke", "reload", "reload2_back", 0, 0, 0, "");
		//AddQuestRecord("Roger_10", "5-1");
		pchar.quest.mtraxx_retribution_ruins.win_condition.l1 = "location";
		pchar.quest.mtraxx_retribution_ruins.win_condition.l1.location = "Judgement_dungeon_01";
		pchar.quest.mtraxx_retribution_ruins.function = "Mtraxx_RetributionRuins";
		pchar.quest.mtraxx_retribution_bezhim.win_condition.l1 = "location";
		pchar.quest.mtraxx_retribution_bezhim.win_condition.l1.location = "Carataska_jungle_03";
		PChar.quest.mtraxx_retribution_bezhim.win_condition = "Mtraxx_RetributionBezhim";
		pchar.quest.mtraxx_retribution_zasada.win_condition.l1 = "location";
		pchar.quest.mtraxx_retribution_zasada.win_condition.l1.location = "Ruins";
		PChar.quest.mtraxx_retribution_zasada.win_condition = "Mtraxx_RetributionBezhim2";
		
		chrDisableReloadToLocation = true;
		/*for (i=1; i<=7; i++)
		{
			sld = CharacterFromID("Mtraxx_Sailor_"+i);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload2");
			TeleportCharacterToPos(sld, 4.84, 5.12, 23.35);
			LAi_type_actor_Reset(sld);
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
		}*/
		
		for(i=1; i<=3; i++)
		{
			idx = GetOfficersIndex(pchar, i);
			if(idx < 0) continue;
			sld = &Characters[idx];
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload2");
			TeleportCharacterToPos(sld, -28.59, -2.12, -94.21);
		}
		if (CharacterIsAlive("Tonzag") && CheckPassengerInCharacter(pchar, "Tonzag"))
		{
			sld = CharacterFromID("Tonzag");
			LAi_SetImmortal(sld, true);
			if (!CharacterIsHere("Tonzag"))
			{
				ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload2");
				TeleportCharacterToPos(sld, -28.59, -2.12, -94.21);
			}
			sld.dialog.filename = "Quest\Roger.c";
			sld.dialog.currentnode = "Nemezida_Tonzag_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 1.5, 0);
		}
		else if (CharacterIsAlive("Knippel") && CheckPassengerInCharacter(pchar, "Knippel"))
		{
			sld = CharacterFromID("Knippel");
			LAi_SetImmortal(sld, true);
			if (!CharacterIsHere("Knippel"))
			{
				ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload2");
				TeleportCharacterToPos(sld, -28.59, -2.12, -94.21);
			}
			sld.dialog.filename = "Quest\Roger.c";
			sld.dialog.currentnode = "Nemezida_Knippel_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		}
		else if (CharacterIsAlive("Longway") && CheckPassengerInCharacter(pchar, "Longway"))
		{
			sld = CharacterFromID("Longway");
			LAi_SetImmortal(sld, true);
			if (!CharacterIsHere("Longway"))
			{
				ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload2");
				TeleportCharacterToPos(sld, -28.59, -2.12, -94.21);
			}
			sld.dialog.filename = "Quest\Roger.c";
			sld.dialog.currentnode = "Nemezida_Longway_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		}
		else if (CharacterIsAlive("Tichingitu") && CheckPassengerInCharacter(pchar, "Tichingitu"))
		{
			sld = CharacterFromID("Tichingitu");
			LAi_SetImmortal(sld, true);
			if (!CharacterIsHere("Tichingitu"))
			{
				ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload2");
				TeleportCharacterToPos(sld, -28.59, -2.12, -94.21);
			}
			sld.dialog.filename = "Quest\Roger.c";
			sld.dialog.currentnode = "Nemezida_Tichingitu_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		}
		else if (CharacterIsAlive("Irons") && CheckPassengerInCharacter(pchar, "Irons"))
		{
			sld = CharacterFromID("Irons");
			LAi_SetImmortal(sld, true);
			if (!CharacterIsHere("Irons"))
			{
				ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload2");
				TeleportCharacterToPos(sld, -28.59, -2.12, -94.21);
			}
			sld.dialog.filename = "Quest\Roger.c";
			sld.dialog.currentnode = "Nemezida_Irons_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		}
		else
		{
			sld = GetCharacter(NPC_GenerateCharacter("Alonso", "Alonso", "man", "man", sti(pchar.rank), pchar.nation, -1, true, "soldier"));
			LAi_SetImmortal(sld, true);
			sld.name = StringFromKey("Roger_107");
			sld.lastname = StringFromKey("Roger_108");
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload2");
			TeleportCharacterToPos(sld, -28.59, -2.12, -94.21);
			sld.dialog.filename = "Quest\Roger.c";
			sld.dialog.currentnode = "Nemezida_Alonso_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		}
	}
	else if (sQuestName == "Mtraxx_RetributionZasada2") // засада
	{
		if (CharacterIsAlive("Tonzag") && CheckPassengerInCharacter(pchar, "Tonzag")) 
			Return_TonzagOfficer();
		
		if (CharacterIsAlive("Knippel") && CheckPassengerInCharacter(pchar, "Knippel")) 
			Return_KnippelOfficer();
		
		if (CharacterIsAlive("Longway") && CheckPassengerInCharacter(pchar, "Longway")) 
			Return_LongwayOfficer();
		
		if (CharacterIsAlive("Tichingitu") && CheckPassengerInCharacter(pchar, "Tichingitu")) 
			Return_TichingituOfficer();
		
		if (CharacterIsAlive("Irons") && CheckPassengerInCharacter(pchar, "Irons")) 
			Return_IronsOfficer();
		
		LAi_SetFightMode(pchar, true);
		
		for(i=1; i<=3; i++)
		{
			idx = GetOfficersIndex(pchar, i);
			if(idx < 0) continue;
			sld = &Characters[idx];
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
		
		for (i=1; i<=7; i++)
		{
			sld = CharacterFromID("Mtraxx_Sailor_"+i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
		
		for (i=1; i<=10; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("Mtraxx_EnemyPirate_"+i, "citiz_4"+(rand(8)+1), "man", "man", sti(pchar.rank), sti(pchar.nation), 0, false, "soldier"));
			FantomMakeCoolFighter(sld, sti(pchar.rank), 50, 50, "blade_14", "pistol1", "bullet", 70);
			LAi_CharacterDisableDialog(sld);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			ChangeCharacterAddressGroup(sld, pchar.location, "rld", "loc8");
			//TeleportCharacterToPos(sld, 26.97, 4.41, -3.68);
		}
		
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		LAi_group_SetCheck("EnemyFight", "Mtraxx_RetributionZasada3");
		PlaySound("interface\abordage_wining.wav");
	}
	else if (sQuestName == "Mtraxx_RetributionZasada3")
	{
		for(i=1; i<=3; i++)
		{
			idx = GetOfficersIndex(pchar, i);
			if(idx < 0) continue;
			sld = &Characters[idx];
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
		}
		for (i=1; i<=7; i++)
		{
			if (CharacterIsAlive("Mtraxx_Sailor_"+i))
			{
				sld = CharacterFromID("Mtraxx_Sailor_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
			}
		}
		
		if (CharacterIsAlive("Tonzag") && CheckPassengerInCharacter(pchar, "Tonzag"))
		{
			sld = CharacterFromID("Tonzag");
			sld.dialog.filename = "Quest\Roger.c";
			sld.dialog.currentnode = "Nemezida_Tonzag_3";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			// break; // заменено на return
			return true;
		}
		if (CharacterIsAlive("Knippel") && CheckPassengerInCharacter(pchar, "Knippel"))
		{
			sld = CharacterFromID("Knippel");
			sld.dialog.filename = "Quest\Roger.c";
			sld.dialog.currentnode = "Nemezida_Knippel_3";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			// break; // заменено на return
			return true;
		}
		if (CharacterIsAlive("Longway") && CheckPassengerInCharacter(pchar, "Longway"))
		{
			sld = CharacterFromID("Longway");
			sld.dialog.filename = "Quest\Roger.c";
			sld.dialog.currentnode = "Nemezida_Longway_3";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			// break; // заменено на return
			return true;
		}
		if (CharacterIsAlive("Tichingitu") && CheckPassengerInCharacter(pchar, "Tichingitu"))
		{
			sld = CharacterFromID("Tichingitu");
			sld.dialog.filename = "Quest\Roger.c";
			sld.dialog.currentnode = "Nemezida_Tichingitu_3";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			// break; // заменено на return
			return true;
		}
		if (CharacterIsAlive("Irons") && CheckPassengerInCharacter(pchar, "Irons"))
		{
			sld = CharacterFromID("Irons");
			sld.dialog.filename = "Quest\Roger.c";
			sld.dialog.currentnode = "Nemezida_Irons_3";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			// break; // заменено на return
			return true;
		}
		sld = CharacterFromID("Alonso");
		sld.dialog.filename = "Quest\Roger.c";
		sld.dialog.currentnode = "Nemezida_Alonso_3";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	else if (sQuestName == "Mtraxx_RetributionZasada4")
	{
		PlaySound("interface\abordage_wining.wav");
		chrDisableReloadToLocation = false;
		LocatorReloadEnterDisable("Carataska_jungle_02", "reload1_back", true);
		LocatorReloadEnterDisable("Carataska_jungle_03", "reload1_back", true);
		LocatorReloadEnterDisable("Ruins", "reload1_back", true);
		for (i=1; i<=7; i++)
		{
			if (CharacterIsAlive("Mtraxx_Sailor_"+i))
			{
				sld = CharacterFromID("Mtraxx_Sailor_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			}
		}
		for(i=1; i<=3; i++)
		{
			idx = GetOfficersIndex(pchar, i);
			if(idx < 0) continue;
			sld = &Characters[idx];
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
		}
		for (i=11; i<=25; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("Mtraxx_EnemyPirate_"+i, "citiz_4"+(rand(8)+1), "man", "man", sti(pchar.rank), sti(pchar.nation), 0, false, "soldier"));
			LAi_SetImmortal(sld, true);
			FantomMakeCoolFighter(sld, sti(pchar.rank), 50, 50, "blade_14", "pistol1", "bullet", 70);
			LAi_CharacterDisableDialog(sld);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			ChangeCharacterAddressGroup(sld, pchar.location, "rld", "loc8");
			TeleportCharacterToPos(sld, -16.00, -2.20, -130.00);
		}
	}
	else if (sQuestName == "Mtraxx_RetributionBezhim")
	{
		for(i=1; i<=3; i++)
		{
			idx = GetOfficersIndex(pchar, i);
			if(idx < 0) continue;
			sld = &Characters[idx];
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
		}
		for (i=1; i<=7; i++)
		{
			if (CharacterIsAlive("Mtraxx_Sailor_"+i))
			{
				sld = CharacterFromID("Mtraxx_Sailor_"+i);
				ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
			}
		}
	}
	else if (sQuestName == "Mtraxx_RetributionBezhim2")
	{
		for(i=1; i<=3; i++)
		{
			idx = GetOfficersIndex(pchar, i);
			if(idx < 0) continue;
			sld = &Characters[idx];
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload2");
			TeleportCharacterToPos(sld, 4.84, 5.12, 26.35);
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
		}
		for (i=1; i<=7; i++)
		{
			if (CharacterIsAlive("Mtraxx_Sailor_"+i))
			{
				sld = CharacterFromID("Mtraxx_Sailor_"+i);
				ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload2");
				TeleportCharacterToPos(sld, 4.84, 5.12, 26.35);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
			}
		}
		
		PChar.quest.Mtraxx_RetributionZasada5.win_condition.l1 = "locator";
		PChar.quest.Mtraxx_RetributionZasada5.win_condition.l1.location = "Ruins";
		PChar.quest.Mtraxx_RetributionZasada5.win_condition.l1.locator_group = "randitem";
		PChar.quest.Mtraxx_RetributionZasada5.win_condition.l1.locator = "randitem2";
		PChar.quest.Mtraxx_RetributionZasada5.win_condition = "Mtraxx_RetributionZasada5";
	}
	else if (sQuestName == "Mtraxx_RetributionZasada5")
	{
		LAi_SetStayType(pchar);
		LAi_FadeLong("Mtraxx_RetributionZasada5_1", "");
	}
	else if (sQuestName == "Mtraxx_RetributionZasada5_1")
	{
		TeleportCharacterToPos(pchar, -12.00, 5.22, -9.50);
		LAi_SetStayType(pchar);
		for(i=1; i<=3; i++)
		{
			idx = GetOfficersIndex(pchar, i);
			if(idx < 0) continue;
			sld = &Characters[idx];
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload2");
			TeleportCharacterToPos(sld, -8.81, 5.22, -9.80);
		}
		for (i=1; i<=7; i++)
		{
			if (CharacterIsAlive("Mtraxx_Sailor_"+i))
			{
				sld = CharacterFromID("Mtraxx_Sailor_"+i);
				TeleportCharacterToPos(sld, -8.81, 5.22, -9.80);
			}
		}
		
		if (CharacterIsAlive("Tonzag") && CheckPassengerInCharacter(pchar, "Tonzag"))
		{
			sld = CharacterFromID("Tonzag");
			LAi_SetImmortal(sld, false);
			sld.dialog.filename = "Quest\Roger.c";
			sld.dialog.currentnode = "Nemezida_Tonzag_5";
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1_back");
			TeleportCharacterToPos(sld, -10.86, 5.22, -8.73);
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		}
		else if (CharacterIsAlive("Knippel") && CheckPassengerInCharacter(pchar, "Knippel"))
		{
			sld = CharacterFromID("Knippel");
			LAi_SetImmortal(sld, false);
			sld.dialog.filename = "Quest\Roger.c";
			sld.dialog.currentnode = "Nemezida_Knippel_5";
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1_back");
			TeleportCharacterToPos(sld, -10.86, 5.22, -8.73);
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		}
		else if (CharacterIsAlive("Longway") && CheckPassengerInCharacter(pchar, "Longway"))
		{
			sld = CharacterFromID("Longway");
			LAi_SetImmortal(sld, false);
			sld.dialog.filename = "Quest\Roger.c";
			sld.dialog.currentnode = "Nemezida_Longway_5";
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1_back");
			TeleportCharacterToPos(sld, -10.86, 5.22, -8.73);
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		}
		else if (CharacterIsAlive("Tichingitu") && CheckPassengerInCharacter(pchar, "Tichingitu"))
		{
			sld = CharacterFromID("Tichingitu");
			LAi_SetImmortal(sld, false);
			sld.dialog.filename = "Quest\Roger.c";
			sld.dialog.currentnode = "Nemezida_Tichingitu_5";
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1_back");
			TeleportCharacterToPos(sld, -10.86, 5.22, -8.73);
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		}
		else if (CharacterIsAlive("Irons") && CheckPassengerInCharacter(pchar, "Irons"))
		{
			sld = CharacterFromID("Irons");
			LAi_SetImmortal(sld, false);
			sld.dialog.filename = "Quest\Roger.c";
			sld.dialog.currentnode = "Nemezida_Irons_5";
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1_back");
			TeleportCharacterToPos(sld, -10.86, 5.22, -8.73);
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		}
		else
		{
			sld = CharacterFromID("Alonso");
			sld.dialog.filename = "Quest\Roger.c";
			sld.dialog.currentnode = "Nemezida_Alonso_5";
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1_back");
			TeleportCharacterToPos(sld, -10.86, 5.22, -8.73);
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		}
	}
	else if (sQuestName == "Mtraxx_RetributionZasada6")
	{
		StartQuestMovie(true, false, true);
		locCameraFromToPos(-5.27, 8.23, 1.95, true, -8.62, 5.44, -6.61);
		
		if (CharacterIsAlive("Tonzag") && CheckPassengerInCharacter(pchar, "Tonzag")) Return_TonzagOfficer();
		else if (CharacterIsAlive("Knippel") && CheckPassengerInCharacter(pchar, "Knippel")) Return_KnippelOfficer();
		else if (CharacterIsAlive("Longway") && CheckPassengerInCharacter(pchar, "Longway")) Return_LongwayOfficer();
		else if (CharacterIsAlive("Tichingitu") && CheckPassengerInCharacter(pchar, "Tichingitu")) Return_TichingituOfficer();
		else if (CharacterIsAlive("Irons") && CheckPassengerInCharacter(pchar, "Irons")) Return_IronsOfficer();
		
		for (i=1; i<=12; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("Mtraxx_Sailor_"+i, "citiz_3"+(rand(8)+1), "man", "man", sti(pchar.rank), sti(pchar.nation), 0, false, "soldier"));
			FantomMakeCoolFighter(sld, sti(pchar.rank), 40, 40, "blade_14", "pistol1", "bullet", 30);
			LAi_CharacterDisableDialog(sld);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload2");
			TeleportCharacterToPos(sld, -8.81, 5.22, -9.80);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
		for (i=11; i<=26; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("Mtraxx_EnemyPirate_"+i, "citiz_4"+(rand(8)+1), "man", "man", sti(pchar.rank), sti(pchar.nation), 0, false, "soldier"));
			FantomMakeCoolFighter(sld, sti(pchar.rank), 50, 50, "blade_14", "pistol1", "bullet", 70);
			LAi_CharacterDisableDialog(sld);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			ChangeCharacterAddressGroup(sld, pchar.location, "item", "flower1");
			TeleportCharacterToPos(sld, -4.13, 5.22, 0.57);
		}
		
		LAi_SetActorType(pchar);
		LAi_ActorGoToLocator(pchar, "reload", "reload2", "", -1);
		DoQuestCheckDelay("Mtraxx_RetributionZasada7", 5.5);
	}
	else if (sQuestName == "Mtraxx_RetributionZasada7")
	{
		locCameraFromToPos(-6.37, 7.53, -17.12, true, -9.34, 4.50, -15.65);
		LAi_SetActorType(pchar);
		LAi_ActorRunToLocator(pchar, "reload", "reload2", "Mtraxx_RetributionZasada8", -1);
	}
	else if (sQuestName == "Mtraxx_RetributionZasada8")
	{
		EndQuestMovie();
		LocatorReloadEnterDisable("Judgement_dungeon_01", "reload1", true);
		LAi_SetPlayerType(pchar);
		chrDisableReloadToLocation = false;
		DoQuestReloadToLocation("Judgement_dungeon_01", "reload", "reload1", "");
	}
	else if (sQuestName == "Mtraxx_RetributionPellyAfterFight") // окончили бой с Тесаком
	{
		LAi_group_Delete("EnemyFight");
		chrDisableReloadToLocation = false;
		AddQuestRecord("Roger_10", "7");
		QuestPointerToLoc("Judgement_dungeon_05", "reload", "reload1");
		QuestPointerToLoc("Judgement_dungeon_04", "reload", "reload1");
		pchar.quest.mtraxx_retribution_ruins1.win_condition.l1 = "location";
		pchar.quest.mtraxx_retribution_ruins1.win_condition.l1.location = "Judgement_dungeon_03";
		pchar.quest.mtraxx_retribution_ruins1.function = "Mtraxx_RetributionSetJeffry";
	}
	else if (sQuestName == "Mtraxx_RetributionJeffryTreasure") // с Джеффри у сокровищ - любуется
	{
		sld = characterFromId("Jeffry");
		LAi_SetActorType(sld);
		LAi_ActorTurnToLocator(sld, "monster", "monster3");
		DoQuestCheckDelay("Mtraxx_RetributionJeffryTreasure1", 7.0);
		sld = characterFromId("Jeffry_PirateDung_4");
		LAi_SetActorType(sld);
		LAi_ActorTurnToLocator(sld, "quest", "quest4");
	}
	else if (sQuestName == "Mtraxx_RetributionJeffryTreasure1") // с Джеффри у сокровищ - идёт в позицию
	{
		sld = characterFromId("Jeffry");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocator(sld, "quest", "quest5", "Mtraxx_RetributionJeffryTreasure2", -1);
	}
	else if (sQuestName == "Mtraxx_RetributionJeffryTreasure2") // с Джеффри у сокровищ
	{
		LAi_SetPlayerType(pchar);
		sld = characterFromId("Jeffry");
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
	}
	else if (sQuestName == "Mtraxx_RetributionJeffryMushketer") // выстрел в ГГ
	{
		sld = characterFromId("Jeffry_PirateDung_4");
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "shot", "Mtraxx_RetributionJeffryShot", 1.0);
		LAi_GunSetUnload(sld, MUSKET_ITEM_TYPE);
	}
	else if (sQuestName == "Mtraxx_RetributionJeffryShot") // выстрел в ГГ - реакция
	{
		LAi_SetActorType(pchar);
		LAi_ActorAnimation(pchar, "hit_fire", "pchar_back_to_player", 0.8);
		CreateLocationParticles("blood_big", "quest", "quest4", 2.0, 0, 0, "");
		PlaySound("People Fight\Damage_NPC_03.wav");
		i = makeint(LAi_GetCharacterHP(pchar)/2); // 3 прогона
		LAi_ApplyCharacterDamage(pchar, i, "fire");
		n = MOD_SKILL_ENEMY_RATE; // 3 прогона
		AddCharacterHealth(pchar, -n);
		DoQuestCheckDelay("Mtraxx_RetributionJeffryAngry", 1.0);
	}
	else if (sQuestName == "Mtraxx_RetributionJeffryAngry") // Джеффри перед боем
	{
		sld = characterFromId("Jeffry");
		sld.dialog.currentnode = "Jeffry_35";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 0.2);
	}
	else if (sQuestName == "Mtraxx_RetributionJeffryAfterFight") // окончили бой с Джеффри
	{
		LAi_group_Delete("EnemyFight");
		chrDisableReloadToLocation = false;
		AddQuestRecord("Roger_10", "8");
		QuestPointerToLoc("Judgement_dungeon_05", "reload", "reload1");
		QuestPointerToLoc("Judgement_dungeon_04", "reload", "reload1");
		QuestPointerToLoc("Judgement_dungeon_03", "reload", "reload1");
		QuestPointerToLoc("Judgement_dungeon_02", "reload", "reload1");
		QuestPointerToLoc("Judgement_dungeon_01", "quest", "lepricon");
		pchar.quest.mtraxx_retribution_ruins2.win_condition.l1 = "location";
		pchar.quest.mtraxx_retribution_ruins2.win_condition.l1.location = "Judgement_dungeon_04";
		pchar.quest.mtraxx_retribution_ruins2.function = "Mtraxx_RetributionMushketers";
		n = MOD_SKILL_ENEMY_RATE; // 3 прогона
		AddCharacterHealth(pchar, -n);
	}
	else if (sQuestName == "Mtraxx_RetributionMushAfterFight") // окончили бой с 1-мушкетерами
	{
		LAi_group_Delete("EnemyFight");
		chrDisableReloadToLocation = false;
		pchar.quest.mtraxx_retribution_ruins3.win_condition.l1 = "location";
		pchar.quest.mtraxx_retribution_ruins3.win_condition.l1.location = "Judgement_dungeon_03";
		pchar.quest.mtraxx_retribution_ruins3.function = "Mtraxx_RetributionNextMushketers";
	}
	else if (sQuestName == "Mtraxx_RetributionNextMushAfterFight") // окончили бой с 2-мушкетерами
	{
		LAi_group_Delete("EnemyFight");
		chrDisableReloadToLocation = false;
		pchar.quest.mtraxx_retribution_ruins4.win_condition.l1 = "location";
		pchar.quest.mtraxx_retribution_ruins4.win_condition.l1.location = "Judgement_dungeon_02";
		pchar.quest.mtraxx_retribution_ruins4.function = "Mtraxx_RetributionLastMushketers";
	}
	else if (sQuestName == "Mtraxx_RetributionLastMushAfterFight") // окончили бой с 3-мушкетерами
	{
		LAi_group_Delete("EnemyFight");
		chrDisableReloadToLocation = false;
		pchar.quest.mtraxx_retribution_ruins5.win_condition.l1 = "location";
		pchar.quest.mtraxx_retribution_ruins5.win_condition.l1.location = "Judgement_dungeon_01";
		pchar.quest.mtraxx_retribution_ruins5.function = "Mtraxx_RetributionSetLepricon";
	}
	else if (sQuestName == "Mtraxx_RetributionLepriconAfterFight") // окончили бой с Леприконом 3 прогона
	{
		LAi_group_Delete("EnemyFight");
		bNoEatNoRats = true;
		chrDisableReloadToLocation = false;
		LocatorReloadEnterDisable("Judgement_dungeon_01", "reload1", true);
		LocatorReloadEnterDisable("Ruins", "reload2_back", true);
		n = Findlocation("Ruins");
		locations[n].models.always.blockade = "ruins1_blockade";
		Locations[n].models.always.blockade.tech = "DLightModel";
		Locations[n].models.day.charactersPatch = "ruins1_qpatch";
		Locations[n].models.night.charactersPatch = "ruins1_qpatch";
		LAi_LocationDisableOfficersGen("Ruins", true);//офицеров не пускать
		LAi_LocationDisableOfficersGen("Carataska_jungle_03", true);
		LAi_LocationDisableOfficersGen("Carataska_jungle_02", true);
		LAi_LocationDisableOfficersGen("Carataska_Cave", true);
		LAi_LocationDisableOfficersGen("Carataska_CaveEntrance", true);
		LAi_LocationDisableOfficersGen("Carataska_jungle_01", true);
		LAi_LocationDisableOfficersGen("Shore10", true);
		pchar.quest.mtraxx_retribution_exit.win_condition.l1 = "locator";
		pchar.quest.mtraxx_retribution_exit.win_condition.l1.location = "Judgement_dungeon_01";
		pchar.quest.mtraxx_retribution_exit.win_condition.l1.locator_group = "reload";
		pchar.quest.mtraxx_retribution_exit.win_condition.l1.locator = "reload1";
		pchar.quest.mtraxx_retribution_exit.function = "Mtraxx_RetributionExitClosed";
		pchar.questTemp.Mtraxx.Retribution.ExitClosed = "true";
		AddQuestRecord("Roger_10", "9");
		QuestPointerToLoc("Judgement_dungeon_01", "reload", "reload1");
	}
	else if (sQuestName == "Mtraxx_RetributionCreateEnrico") // ставим Энрико
	{
		LAi_SetActorType(pchar);
		LAi_ActorTurnToLocator(pchar, "quest", "door");
		sld = GetCharacter(NPC_GenerateCharacter("Zorro", "Enrique_1", "man", "man", 40, SPAIN, -1, false, "quest"));
		FantomMakeCoolFighter(sld, 40, 110, 110, "blade_17", "pistol5", "cartridge", 250);
		LAi_SetHP(sld, 750.0, 750.0);
		sld.viper = true;
		GiveItem2Character(sld, "cirass3");
		EquipCharacterByItem(sld, "cirass3");
		sld.Dialog.Filename = "Quest\Roger.c";
		sld.dialog.currentnode = "enrico";
		sld.name = StringFromKey("Roger_125");
		sld.lastname = StringFromKey("Roger_126");
		LAi_SetImmortal(sld, true);
		ChangeCharacterAddressGroup(sld, "Judgement_dungeon_01", "monsters", "monster5");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocator(sld, "quest", "zorro", "Mtraxx_RetributionEnrico", -1);
	}
	else if (sQuestName == "Mtraxx_RetributionEnrico") // разговор с Энрико
	{
		LAi_SetStayType(pchar);
		sld = characterFromId("Zorro");
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		ResetSound();
		SetMusic("music_teleport");
	}
	else if (sQuestName == "Mtraxx_RetributionEnricoGo") // Энрико ушёл
	{
		PlaySound("ambient\jail\jail_door2.wav");
		LAi_SetPlayerType(pchar);
		ResetSound();
		SetMusic("music_alcove");
		AddQuestRecord("Roger_10", "10");
		for (i=2; i<=7; i++)
		{
			sTemp = "mtraxx_retribution_time"+i;
			pchar.quest.(sTemp).win_condition.l1 = "location";
			pchar.quest.(sTemp).win_condition.l1.location = "Judgement_dungeon_0"+i;
			pchar.quest.(sTemp).function = "Mtraxx_RetributionTwoHoursTime";
		}
		pchar.quest.mtraxx_retribution_church.win_condition.l1 = "location";
		pchar.quest.mtraxx_retribution_church.win_condition.l1.location = "Judgement_church";
		pchar.quest.mtraxx_retribution_church.function = "Mtraxx_RetributionInChurchRuins";
		pchar.questTemp.Mtraxx.Retribution.DoorOpen = "true";
		QuestPointerToLoc("Judgement_dungeon_01", "reload", "reload2_back");
		QuestPointerToLoc("Judgement_dungeon_02", "reload", "reload2");
		QuestPointerToLoc("Judgement_dungeon_03", "reload", "reload2");
		QuestPointerToLoc("Judgement_dungeon_04", "reload", "reload2");
		if (!CheckCharacterItem(PChar, "key_scotland"))
		{
			QuestPointerToLoc("Judgement_dungeon_05", "box", "private1");
			PChar.quest.Mtraxx_QuestMarkKayScotland.win_condition.l1 = "locator";
			PChar.quest.Mtraxx_QuestMarkKayScotland.win_condition.l1.location = "Judgement_dungeon_05";
			PChar.quest.Mtraxx_QuestMarkKayScotland.win_condition.l1.locator_group = "box";
			PChar.quest.Mtraxx_QuestMarkKayScotland.win_condition.l1.locator = "private1";
			PChar.quest.Mtraxx_QuestMarkKayScotland.win_condition = "Mtraxx_QuestMarkKayScotland";
		}
		else QuestPointerToLoc("Judgement_dungeon_05", "reload", "reload2");
	}
	else if (sQuestName == "Mtraxx_QuestMarkKayScotland") // квестмарка на дверь вниз
	{
		QuestPointerToLoc("Judgement_dungeon_05", "reload", "reload2");
		QuestPointerDelLoc("Judgement_dungeon_01", "reload", "reload2_back");
		QuestPointerDelLoc("Judgement_dungeon_02", "reload", "reload2");
		QuestPointerDelLoc("Judgement_dungeon_03", "reload", "reload2");
		QuestPointerDelLoc("Judgement_dungeon_04", "reload", "reload2");
		QuestPointerDelLoc("Judgement_dungeon_05", "box", "private1");
	}
	else if (sQuestName == "Mtraxx_RetributionEnricoAndTonzag")
	{
		StartQuestMovie(true, false, true);
		locCameraFromToPos(14.91, 1.64, -1.28, true, 18.10, -0.30, -0.32);
		PlaySound("ambient\jail\jail_door2.wav");
		LAi_SetStayType(pchar);
		
		sld = CharacterFromID("Tonzag");
		ChangeCharacterAddressGroup(sld, PChar.location, "quest", "door");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocator(sld, "quest", "zorro", "Mtraxx_RetributionEnricoAndTonzag1", -1);
		DoQuestCheckDelay("Mtraxx_RetributionEnricoAndTonzag1", 3.0);
		LAi_LocationDisableOfficersGen("Judgement_dungeon_01", false);
	}
	else if (sQuestName == "Mtraxx_RetributionEnricoAndTonzag1")
	{
		sld = CharacterFromID("Tonzag");
		sld.greeting = "";
		sld.Dialog.Filename = "Quest\Roger.c";
		sld.dialog.currentnode = "enrico_Tonzag_1";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
	}
	else if (sQuestName == "Mtraxx_RetributionEnricoAndTonzag2")
	{
		locCameraSleep(true);
		sld = CharacterFromID("Tonzag");
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "Shot", "1", 1.8);
		
		sld = CharacterFromID("Zorro");
		CharacterTurnByChr(sld, characterFromID("Tonzag"));
		DoQuestCheckDelay("Mtraxx_RetributionEnricoAndTonzag3", 0.9);
	}
	else if (sQuestName == "Mtraxx_RetributionEnricoAndTonzag3")
	{
		sld = CharacterFromID("Zorro");
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "death_8", "1", -1);
		CharacterTurnByChr(sld, characterFromID("Tonzag"));
		
		DoQuestCheckDelay("Mtraxx_RetributionEnricoAndTonzag4", 1.0);
	}
	else if (sQuestName == "Mtraxx_RetributionEnricoAndTonzag4")
	{
		LAi_FadeLong("Mtraxx_RetributionEnricoAndTonzag5", "");
	}
	else if (sQuestName == "Mtraxx_RetributionEnricoAndTonzag5")
	{
		locCameraSleep(false);
		locCameraFromToPos(11.57, 1.40, -1.20, true, 16.33, -0.20, -0.85);
		SetMainCharacterIndex(GetCharacterIndex("Blaze"));
		PChar = GetMainCharacter();
		LAi_SetPlayerType(PChar);
		//TeleportCharacterToPos(PChar, 16.33, 0.00, -1.08);
		sld = CharacterFromID("Tonzag");
		sld.Dialog.Filename = "Quest\Roger.c";
		sld.dialog.currentnode = "enrico_Tonzag_14";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
		
		sld = CharacterFromID("Zorro");
		ChangeCharacterAddressGroup(sld, PChar.location, "quest", "door");
		TeleportCharacterToPosAy(sld, 22.52, 0.00, -0.75, -1.50);
		LAi_SetActorType(sld);
		LAi_ActorSetGroundSitMode(sld);
	}
	else if (sQuestName == "Mtraxx_RetributionEnricoAndTonzag6")
	{
		locCameraSleep(false);
		TeleportCharacterToPos(pchar, 11.59, 0.0, -2.08);
		
		sld = CharacterFromID("Tonzag");
		TeleportCharacterToPos(sld, 13.05, 0.0, 0.06);
		CharacterTurnToLoc(sld, "quest", "enrico");

		sld = CharacterFromID("Zorro");
		TeleportCharacterToPosAy(sld, 14.07, 0.00, -0.70, -1.50);
		sld.Dialog.Filename = "Quest\Roger.c";
		sld.dialog.currentnode = "enrico_Tonzag_20";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
	}
	else if (sQuestName == "Mtraxx_RetributionEnricoAndTonzag7")
	{
		sld = CharacterFromID("Tonzag");
		sld.Dialog.Filename = "Quest\Roger.c";
		sld.dialog.currentnode = "enrico_Tonzag_29";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	else if (sQuestName == "Mtraxx_RetributionEnricoAndTonzag8")
	{
		sld = CharacterFromID("Tonzag");
		LAi_UseAtidoteBottle(sld);
		LAi_SetImmortal(sld, false);
		LAi_RemoveCheckMinHP(sld);
		ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto3");
		TeleportCharacterToPos(sld, 4.01, 0.74, -4.17);
		sld.Dialog.Filename = "Quest\Roger.c";
		sld.dialog.currentnode = "Nemezida_Tonzag_7";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		LAi_LocationDisableOfficersGen("Judgement_dungeon_01", true);
	}
	else if (sQuestName == "Mtraxx_RetributionDoorOpen") // открыли дверь вниз
	{
		AddQuestRecord("Roger_10", "11");
	}
	else if (sQuestName == "Mtraxx_RetributionChurchLock") // сцена закрытых дверей
	{
		PlaySound("interface\knock.wav");
		LAi_ActorGoToLocator(pchar, "quest", "LLquest3", "Mtraxx_RetributionChurchLock1", -1);
	}
	else if (sQuestName == "Mtraxx_RetributionChurchLock1") // сцена закрытых дверей
	{
		PlaySound("interface\knock.wav");
		LAi_ActorGoToLocator(pchar, "quest", "LLquest1", "Mtraxx_RetributionChurchLock2", -1);
	}
	else if (sQuestName == "Mtraxx_RetributionChurchLock2") // беседа самого с собой
	{
		pchar.questTemp.Mtraxx.Retribution.Bead = "true";
		LAi_SetPlayerType(pchar);
		DoQuestCheckDelay("TalkSelf_Quest", 1.0);
	}
	else if (sQuestName == "Mtraxx_RetributionBead") // молитва
	{
		bDisableCharacterMenu = true;//лочим F2
		InterfaceStates.Buttons.Save.enable = false;
		pchar.questTemp.NoFast = true;
		ResetSound();
		SetMusic("music_terrain");
		LAi_SetActorType(pchar);
		LAi_ActorAnimation(pchar, "Bead", "", -1);
		DoQuestCheckDelay("Mtraxx_RetributionGotoSleep1", 5.0);
	}
	else if (sQuestName == "Mtraxx_RetributionGotoSleep1")
	{
		locCameraFromToPos(-2.49, 0.63, -4.26, true, -0.50, 1.13, -8.12);
		DoQuestCheckDelay("Mtraxx_RetributionGotoSleep2", 6.5);
	}
	else if (sQuestName == "Mtraxx_RetributionGotoSleep2")
	{
		locCameraFromToPos(0.48, 2.88, -3.99, true, -1.55, -0.50, -5.83);
		LAi_SetActorType(pchar);
		LAi_ActorAnimation(pchar, "Ground_SitDown", "Mtraxx_RetributionGotoSleep4", 3.0);
		DoQuestCheckDelay("Mtraxx_RetributionGotoSleep3", 2.0);
	}
	else if (sQuestName == "Mtraxx_RetributionGotoSleep3")
	{
		LAi_FadeLong("Mtraxx_RetributionGotoSleep4", "");
	}
	else if (sQuestName == "Mtraxx_RetributionGotoSleep4") // ложится спать
	{
		LAi_SetActorType(pchar);
		LAi_ActorSetLayMode(pchar);
		DoQuestFunctionDelay("Mtraxx_RetributionSleep", 5.0);
	}
	else if (sQuestName == "Mtraxx_RetributionSleep") // снится Мерида
	{
		locCameraFromToPos(27.55, 2.15, -1.92, true, 20.83, -0.32, 0.58);
		LAi_SetActorType(pchar);
		PlaySound("ambient\church\zvon.wav");
		DoQuestFunctionDelay("Mtraxx_RetributionSetMusic", 1.2);
		for (i=1; i<=21; i++) // дым
		{
			if (i == 3) continue;
			CreateLocationParticles("large_smoke", "reload", "reload"+i, 0, 0, 0, "");
		}
		for (i=1; i<=21; i++) // огонь
		{
			if (i == 3) continue;
			CreateLocationParticles("shipfire", "reload", "reload"+i, 0, 0, 0, "fortfire");
		}
		for (i=1; i<=18; i++) // дым
		{
			if (i == 3 || i == 16) continue;
			CreateLocationParticles("large_smoke", "goto", "goto"+i, 0, 0, 0, "");
		}
		for (i=32; i<=37; i++) // дым
		{
			CreateLocationParticles("large_smoke", "goto", "goto"+i, 0, 0, 0, "");
		}
		for (i=1; i<=8; i++) // жертвы
		{
			if (i < 5) sld = GetCharacter(NPC_GenerateCharacter("Sleep_Meridavictim_"+i, "women_"+(9+i), "woman", "towngirl", 1, SPAIN, 1, true, "quest"));
			else sld = GetCharacter(NPC_GenerateCharacter("Sleep_Meridavictim_"+i, "citiz_1"+i, "man", "man", 1, SPAIN, 1, true, "quest"));
			ChangeCharacterAddressGroup(sld, "Merida_town", "quest", "quest"+i);
			LAi_SetActorType(sld);
			if (i < 8) LAi_ActorGoToLocation(sld, "merchant", "merchant3", "none", "", "", "", 40);
			else LAi_ActorGoToLocation(sld, "merchant", "merchant3", "none", "", "", "Mtraxx_RetributionSleep1", 40);
		}
	}
	else if (sQuestName == "Mtraxx_RetributionSleep1") // 
	{
		PlaySound("ambient\church\zvon.wav");
		sld = GetCharacter(NPC_GenerateCharacter("Sleep_Meridahead", "huber_spa", "man", "man", 1, SPAIN, 1, true, "quest"));
		sld.name = StringFromKey("Roger_63");
		sld.lastname = StringFromKey("Roger_64");
		sld.dialog.Filename = "Quest\Roger.c";
		sld.dialog.currentnode = "merida_head_sleep";
		ChangeCharacterAddressGroup(sld, "Merida_town", "reload", "reload3");
		LAi_SetActorType(sld);
		LAi_SetStayType(pchar);
		LAi_ActorDialogDelay(sld, pchar, "", 2.5);
	}
	else if (sQuestName == "Mtraxx_RetributionSleep2") // 
	{
		locCameraSleep(true);
		PlaySound("ambient\church\zvon.wav");
		//LAi_SetActorType(pchar);
		sld = characterFromId("Sleep_Meridahead");    
		ChangeCharacterAddressGroup(sld, "none", "", "");
		CreateLocationParticles("large_smoke", "reload", "reload3", 3, 0, 0, "torch_deck");
		CreateLocationParticles("shipfire", "reload", "reload3", 0, 0, 0, "fortfire");
		DoQuestCheckDelay("Mtraxx_RetributionSleep3", 2.0);
	}
	else if (sQuestName == "Mtraxx_RetributionSleep3") // 
	{
		locCameraSleep(false);
		PlaySound("ambient\church\zvon.wav");
		sld = GetCharacter(NPC_GenerateCharacter("Sleep_Camilla", "women_16", "man", "towngirl", 1, SPAIN, 1, true, "quest"));
		sld.name = StringFromKey("Roger_123");
		sld.lastname = StringFromKey("Roger_124");
		sld.dialog.Filename = "Quest\Roger.c";
		sld.dialog.currentnode = "camilla_sleep";
		RemoveAllCharacterItems(sld, true);
		ChangeCharacterAddressGroup(sld, "Merida_town", "merchant", "merchant1");
		LAi_SetActorType(sld);
		//DoQuestCheckDelay("pchar_back_to_player", 2.0);
		LAi_ActorDialogDelay(sld, pchar, "", 0.0);
	}
	else if (sQuestName == "Mtraxx_RetributionSleep4") // 
	{
		PlaySound("ambient\church\zvon.wav");
		//LAi_SetActorType(pchar);
		sld = characterFromId("Sleep_Camilla");    
		ChangeCharacterAddressGroup(sld, "none", "", "");
		sld = GetCharacter(NPC_GenerateCharacter("Sleep_Mishelle", "Migel_1", "man", "man", 1, FRANCE, 2, true, "quest"));
		sld.name = StringFromKey("Roger_127");
		sld.lastname = StringFromKey("Roger_128");
		sld.dialog.Filename = "Quest\Roger.c";
		sld.dialog.currentnode = "mishelle_sleep";
		RemoveAllCharacterItems(sld, true);
		ChangeCharacterAddressGroup(sld, "Merida_town", "quest", "stay2");
		LAi_SetActorType(sld);
		//DoQuestCheckDelay("pchar_back_to_player", 2.0);
		LAi_ActorDialogDelay(sld, pchar, "", 0.0);
	}
	else if (sQuestName == "Mtraxx_RetributionSleep5") // 
	{
		locCameraSleep(true);
		CharacterTurnToLoc(pchar, "goto", "goto30");
		PlaySound("ambient\church\zvon.wav");
		//DoQuestCheckDelay("pchar_back_to_player", 2.0);
		sld = characterFromId("Sleep_Mishelle");    
		ChangeCharacterAddressGroup(sld, "none", "", "");
		sld = GetCharacter(NPC_GenerateCharacter("Sleep_Terrax", "Terrax", "man", "man", 1, PIRATE, 1, true, "quest"));
		FantomMakeCoolFighter(sld, 50, 110, 110, "blade_19", "pistol4", "bullet", 300);
		sld.name = StringFromKey("Roger_129");
		sld.lastname = StringFromKey("Roger_130");
		sld.dialog.Filename = "Quest\Roger.c";
		sld.dialog.currentnode = "terrax_sleep";
		ChangeCharacterAddressGroup(sld, "Merida_town", "goto", "goto25");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		sld = GetCharacter(NPC_GenerateCharacter("Sleep_Jeffry", "Jeffry", "man", "man", 35, PIRATE, 1, true, "marginal"));
		sld.name = StringFromKey("Roger_15");
		sld.lastname = StringFromKey("Roger_16");
		ChangeCharacterAddressGroup(sld, "Merida_town", "goto", "goto15");
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, characterFromId("Sleep_Terrax"), "", 8.0);
		sld = GetCharacter(NPC_GenerateCharacter("Sleep_Pelly", "Tesak", "man", "man", 35, PIRATE, 1, true, "marginal"));
		sld.name = StringFromKey("Roger_27");
		sld.lastname = StringFromKey("Roger_28");
		ChangeCharacterAddressGroup(sld, "Merida_town", "goto", "goto15");
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, characterFromId("Sleep_Terrax"), "", 8.0);
		sld = GetCharacter(NPC_GenerateCharacter("Sleep_Lepricon", "Leprechaun", "man", "man", 35, PIRATE, 1, true, "marginal"));
		sld.name = StringFromKey("Roger_54");
		sld.lastname = StringFromKey("Roger_55");
		ChangeCharacterAddressGroup(sld, "Merida_town", "goto", "goto15");
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, characterFromId("Sleep_Terrax"), "", 8.0);
	}
	else if (sQuestName == "Mtraxx_RetributionSleep6") // 
	{
		PlaySound("ambient\church\zvon.wav");
		//LAi_SetActorType(pchar);
		sld = characterFromId("Sleep_Terrax");    
		ChangeCharacterAddressGroup(sld, "none", "", "");
		sld = characterFromId("Sleep_Jeffry");    
		ChangeCharacterAddressGroup(sld, "none", "", "");
		sld = characterFromId("Sleep_Pelly");    
		ChangeCharacterAddressGroup(sld, "none", "", "");
		sld = characterFromId("Sleep_Lepricon");    
		ChangeCharacterAddressGroup(sld, "none", "", "");
		if (GetCharacterIndex("Mirabella") != -1) // спасли Мирабель
		{
			sld = GetCharacter(NPC_GenerateCharacter("Sleep_Mirabella", "Mirabelle", "woman", "towngirl", 1, SPAIN, 1, true, "quest"));
			sld.name = StringFromKey("Roger_51");
			sld.lastname = StringFromKey("Roger_52");
			sld.dialog.Filename = "Quest\Roger.c";
			sld.dialog.currentnode = "mirabelle_sleep";
			ChangeCharacterAddressGroup(sld, "Merida_town", "goto", "goto29");
			LAi_SetActorType(sld);
			//DoQuestCheckDelay("pchar_back_to_player", 2.0);
			LAi_ActorDialogDelay(sld, pchar, "", 0.0);
		}
		else
		{
			sld = characterFromId("Sleep_Mishelle");    
			ChangeCharacterAddressGroup(sld, "Merida_town", "merchant", "merchant1");
			sld.dialog.currentnode = "mishelle_sleep_1";
			//DoQuestCheckDelay("pchar_back_to_player", 2.0);
			LAi_ActorDialogDelay(sld, pchar, "", 0.0);
		}
	}
	else if (sQuestName == "Mtraxx_RetributionSleep6_1") // 
	{
		PlaySound("ambient\church\zvon.wav");
		sld = characterFromId("Sleep_Mirabella");    
		ChangeCharacterAddressGroup(sld, "none", "", "");
		sld = characterFromId("Sleep_Mishelle");    
		ChangeCharacterAddressGroup(sld, "Merida_town", "merchant", "merchant1");
		sld.dialog.currentnode = "mishelle_sleep_1";
		//DoQuestCheckDelay("pchar_back_to_player", 2.0);
		LAi_ActorDialogDelay(sld, pchar, "", 0.0);
	}
	else if (sQuestName == "Mtraxx_RetributionSleep7") // 
	{
		locCameraSleep(true);
		CharacterTurnToLoc(pchar, "merchant", "merchant1");
		PlaySound("ambient\church\zvon.wav");
		//LAi_SetActorType(pchar);
		sld = characterFromId("Sleep_Mishelle");    
		ChangeCharacterAddressGroup(sld, "none", "", "");
		DoQuestCheckDelay("Mtraxx_RetributionSleep8", 1.0);
	}
	else if (sQuestName == "Mtraxx_RetributionSleep8") // 
	{
		EndQuestMovie();
		locCameraSleep(false);
		PlaySound("ambient\church\zvon.wav");
		WaitDate("", 0, 0, 0, 18, rand(30)); //крутим время
		RefreshLandTime();
		RecalculateJumpTable();
		Whr_UpdateWeather();
		DoQuestReloadToLocation("Judgement_church", "quest", "LLquest9", "Mtraxx_RetributionAwake");
	}
	else if (sQuestName == "Mtraxx_RetributionAwake") // просыпается
	{
		chrDisableReloadToLocation = false;
		AddCharacterHealth(pchar, -10);
		bDisableCharacterMenu = false;
		InterfaceStates.Buttons.Save.enable = true;
		DeleteAttribute(pchar, "questTemp.NoFast");
		LAi_SetPlayerType(pchar);
		AddQuestRecord("Roger_10", "12");
		sld = ItemsFromID("key_ruins");
		sld.shown = true;
		sld.startLocation = "Judgement_dungeon_07";
		sld.startLocator = "item"+(rand(4)+1);
	}
	else if (sQuestName == "Mtraxx_RetributionSvoboda") // вернулся в бухту - свобода!
	{
		if (CharacterIsAlive("Knippel") && CheckPassengerInCharacter(pchar, "Knippel"))
		{
			sld = CharacterFromID("Knippel");
			LAi_SetImmortal(sld, false);
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto1");
			sld.dialog.filename = "Quest\Roger.c";
			sld.dialog.currentnode = "Nemezida_Knippel_7";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			
			pchar.questTemp.Mtraxx.Retribution = "freedom";
			pchar.questTemp.Mtraxx.Retribution.Freedom = "true";
			return true;
		}
		if (CharacterIsAlive("Longway") && CheckPassengerInCharacter(pchar, "Longway"))
		{
			sld = CharacterFromID("Longway");
			LAi_SetImmortal(sld, false);
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto1");
			sld.dialog.filename = "Quest\Roger.c";
			sld.dialog.currentnode = "Nemezida_Longway_7";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			
			pchar.questTemp.Mtraxx.Retribution = "freedom";
			pchar.questTemp.Mtraxx.Retribution.Freedom = "true";
			return true;
		}
		if (CharacterIsAlive("Tichingitu") && CheckPassengerInCharacter(pchar, "Tichingitu"))
		{
			sld = CharacterFromID("Tichingitu");
			LAi_SetImmortal(sld, false);
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto1");
			sld.dialog.filename = "Quest\Roger.c";
			sld.dialog.currentnode = "Nemezida_Tichingitu_7";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			
			pchar.questTemp.Mtraxx.Retribution = "freedom";
			pchar.questTemp.Mtraxx.Retribution.Freedom = "true";
			return true;
		}
		if (CharacterIsAlive("Irons") && CheckPassengerInCharacter(pchar, "Irons"))
		{
			sld = CharacterFromID("Irons");
			LAi_SetImmortal(sld, false);
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto1");
			sld.dialog.filename = "Quest\Roger.c";
			sld.dialog.currentnode = "Nemezida_Irons_7";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			
			pchar.questTemp.Mtraxx.Retribution = "freedom";
			pchar.questTemp.Mtraxx.Retribution.Freedom = "true";
			return true;
		}
		pchar.GenQuest.Hunter2Pause = true; // прогона 3
		DoQuestFunctionDelay("Mtraxx_RetributionSetMusic", 1.2);
		LAi_SetActorType(pchar);
		// belamour legendary edition -->
		LAi_ActorGoToLocator(pchar, "goto", "goto1", "TalkSelf_Quest", -1); 
		pchar.questTemp.Mtraxx.Retribution.Choice = "to_choice";
		// <-- legendary edition
		pchar.questTemp.Mtraxx.Retribution = "freedom";
		pchar.questTemp.Mtraxx.Retribution.Freedom = "true";
	}
	else if (sQuestName == "Mtraxx_RetributionFreedom") // молится за спасение
	{
		LAi_SetActorType(pchar);
		LAi_ActorAnimation(pchar, "Bead", "", -1);
		InterfaceStates.Buttons.Save.enable = false;
		bDisableCharacterMenu = true;
		locCameraRotateAroundHero(0.0, 1.5, 0.0, 0.005, 0.0, 1.5, 0.0, 10000);
		Pchar.FuncCameraFly = "";
		DoQuestCheckDelay("Mtraxx_RetributionPromice", 5.0);
		PlaySound("ambient\church\zvon.wav");
	}
	else if (sQuestName == "Mtraxx_RetributionPromice") // 
	{
		PlaySound("ambient\church\zvon.wav");
		Log_Info(StringFromKey("Roger_131"));
		DoQuestCheckDelay("Mtraxx_RetributionPromice1", 6.0);
	}
	else if (sQuestName == "Mtraxx_RetributionPromice1") // 
	{
		PlaySound("ambient\church\zvon.wav");
		Log_Info(StringFromKey("Roger_132"));
		DoQuestCheckDelay("Mtraxx_RetributionPromice2", 6.0);
	}
	else if (sQuestName == "Mtraxx_RetributionPromice2") // 
	{
		PlaySound("ambient\church\zvon.wav");
		Log_Info(StringFromKey("Roger_133"));
		DoQuestCheckDelay("Mtraxx_RetributionPromice3", 6.0);
	}
	else if (sQuestName == "Mtraxx_RetributionPromice3") // 
	{
		PlaySound("ambient\church\zvon.wav");
		Log_Info(StringFromKey("Roger_134"));
		DoQuestCheckDelay("Mtraxx_RetributionPromice4", 6.0);
	}
	else if (sQuestName == "Mtraxx_RetributionPromice4") // 
	{
		PlaySound("ambient\church\zvon.wav");
		Log_Info(StringFromKey("Roger_135"));
		DoQuestCheckDelay("Mtraxx_RetributionPromice5", 6.0);
	}
	else if (sQuestName == "Mtraxx_RetributionPromice5") // 
	{
		PlaySound("ambient\church\zvon.wav");
		Log_Info(StringFromKey("Roger_136"));
		DoQuestCheckDelay("Mtraxx_RetributionPromice6", 6.0);
	}
	else if (sQuestName == "Mtraxx_RetributionPromice6") // 
	{
		PlaySound("ambient\church\zvon.wav");
		Log_Info(StringFromKey("Roger_137"));
		DoQuestCheckDelay("Mtraxx_RetributionPromice7", 6.0);
	}
	else if (sQuestName == "Mtraxx_RetributionPromice7") //
	{
		PlaySound("ambient\church\zvon.wav");
		Log_Info(StringFromKey("Roger_138"));
		DoQuestCheckDelay("Mtraxx_RetributionFinal", 6.0);
	}
	else if (sQuestName == "Mtraxx_RetributionFinal") // завершение линейки квестов
	{
		locCameraResetState();
		PlaySound("ambient\church\zvon.wav");
		InterfaceStates.Buttons.Save.enable = true;
		bDisableCharacterMenu = false;
		bNoEatNoRats = false;
		LAi_SetPlayerType(pchar);
		AddQuestRecord("Roger_10", "17");
		bQuestDisableMapEnter = false;//открыть карту
		DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		DeleteAttribute(pchar, "GenQuest.CannotWait");
		if (GetCharacterIndex("Mirabella") != -1)
		{
			AddQuestUserData("Roger_10", "sText", StringFromKey("Roger_139"));
			sld = characterFromId("Mirabella");
			sld.dialog.currentnode = "mirabelle_29";
		}
		pchar.quest.mtraxx_line_complete.win_condition.l1 = "MapEnter";
		pchar.quest.mtraxx_line_complete.function = "Mtraxx_RetributionComplete";
	}
	else if (sQuestName == "Mtraxx_RetributionFinal_Tonzag") // завершение линейки квестов вместе с Тонзагом
	{
		Achievment_Set("ach_CL_97"); // не раскаились в грехах Чарли Принца
		Return_TonzagOfficer();
		bNoEatNoRats = false;
		LAi_SetPlayerType(pchar);
		AddQuestRecord("Roger_10", "20");
		bQuestDisableMapEnter = false;//открыть карту
		DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		DeleteAttribute(pchar, "GenQuest.CannotWait");
		if (GetCharacterIndex("Mirabella") != -1)
		{
			sld = characterFromId("Mirabella");
			sld.dialog.currentnode = "mirabelle_29";
		}
		pchar.quest.mtraxx_line_complete.win_condition.l1 = "MapEnter";
		pchar.quest.mtraxx_line_complete.function = "Mtraxx_RetributionComplete";
	}
	else if (sQuestName == "Mtraxx_RetributionFinal_Officers") // завершение линейки квестов вместе с Книппелем, Лонгвэем, Тичингиту, Томми
	{
		bNoEatNoRats = false;
		LAi_SetPlayerType(pchar);
		bQuestDisableMapEnter = false;//открыть карту
		DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		DeleteAttribute(pchar, "GenQuest.CannotWait");
		if (GetCharacterIndex("Mirabella") != -1)
		{
			sld = characterFromId("Mirabella");
			sld.dialog.currentnode = "mirabelle_29";
		}
		pchar.quest.mtraxx_line_complete.win_condition.l1 = "MapEnter";
		pchar.quest.mtraxx_line_complete.function = "Mtraxx_RetributionComplete";
		AddQuestRecord("Roger_10", "19");
		
		if (CharacterIsAlive("Knippel") && CheckPassengerInCharacter(pchar, "Knippel"))
		{
			Return_KnippelOfficer();
			AddQuestUserData("Roger_10", "sText", StringFromKey("Roger_140"));
		}
		else if (CharacterIsAlive("Longway") && CheckPassengerInCharacter(pchar, "Longway"))
		{
			Return_LongwayOfficer();
			AddQuestUserData("Roger_10", "sText", StringFromKey("Roger_141"));
		}
		else if (CharacterIsAlive("Tichingitu") && CheckPassengerInCharacter(pchar, "Tichingitu"))
		{
			Return_TichingituOfficer();
			AddQuestUserData("Roger_10", "sText", StringFromKey("Roger_142"));
		}
		else if (CharacterIsAlive("Irons") && CheckPassengerInCharacter(pchar, "Irons"))
		{
			Return_IronsOfficer();
			AddQuestUserData("Roger_10", "sText", StringFromKey("Roger_143"));
		}
	}
	else
	{
		condition = false;
	}
	
	return condition;
}