void WildRose_Start(string qName)
{
	if (!CheckAttribute(pchar, "questTemp.WildRose_Start"))
	{
		pchar.quest.WildRose_Start_2.win_condition.l1 = "location";
		pchar.quest.WildRose_Start_2.win_condition.l1.location = "Bridgetown_town";
		pchar.quest.WildRose_Start_2.function = "WildRose_Start_2";
		AddMapQuestMarkCity("Bridgetown", true);
		
		pchar.questTemp.WildRose_Start = true;
	}
}

void WildRose_Start_2(string qName)
{
	// bool bOk1, bOk2, bOk3;
	// bOk1 = CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "done";
	// bOk2 = CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "end";
	// bOk2 = CheckAttribute(pchar, "questTemp.GoldenGirl_Ready");
	// if (bOk1 && bOk2 && bOk3)
	// if (CheckAttributeEqualTo(pchar, "questTemp.Sharlie", "escape") && CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && CharacterIsAlive("Mary") && CheckAttribute(pchar, "questTemp.GoldenGirl_Ready") && ChangeCharacterNationReputation(pchar, ENGLAND, 0) >= -5 && !CheckAttribute(pchar, "questTemp.Tieyasal_final"))
	if (CheckAttributeEqualTo(pchar, "questTemp.Sharlie", "escape") && CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && CharacterIsAlive("Mary") && CheckPassengerInCharacter(pchar, "Mary") && ChangeCharacterNationReputation(pchar, ENGLAND, 0) >= -5)
	{
		chrDisableReloadToLocation = true;
		DeleteQuestCondition("WildRose_Start");
		
		pchar.questTemp.WildRose_DialogeWithSoldierOnPier = true;
	}
	else
	{
		SetFunctionTimerCondition("WildRose_Start", 0, 0, 14, true); // таймер
	}
}

void WildRose_MaryFollowing()
{
	sld = CharacterFromID("Mary");
	LAi_SetActorType(sld);
	LAi_ActorFollowEverywhere(sld, "", -1);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
}

// =================================================================
// ================== ЭТАП 1. «ЛОЩИНА ВЛЮБЛЁННЫХ» ==================
// =================================================================
void WildRose_Etap1_EscapeSlaves(string qName)
{
	SetQuestHeader("WildRose");
	AddQuestRecord("WildRose", "1");
	chrDisableReloadToLocation = false;
	QuestCloseSeaExit();
	pchar.questTemp.MarySexBlock = "true";
	Achievment_Set("ach_CL_169");
	
	locations[FindLocation("Barbados_jungle_03")].DisableEncounters = true;
	locations[FindLocation("Shore5")].DisableEncounters = true;
	SetFunctionLocationCondition("WildRose_Etap1_EscapeSlaves_2", "Barbados_jungle_03", false);
	
	AddSimpleRumourCity(StringFromKey("WildRose_1"), "Bridgetown", 7, 1, "");
}

void WildRose_Etap1_EscapeSlaves_2(string qName)
{
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(loadedLocation, true);
	
	sld = GetCharacter(NPC_GenerateCharacter("WildRose_DiedCitiz_1", "Citiz_12", "man", "man", 1, ENGLAND, 0, false, "quest"));
	sld.name = StringFromKey("WildRose_6");
	sld.lastname = StringFromKey("WildRose_7");
	ChangeCharacterAddressGroup(sld, "Barbados_jungle_03", "goto", "goto5");
	TeleportCharacterToPosAy(sld, 16.96, 0.00, 19.16, -0.00);
	sld.DontClearDead = true;
	sld.CantLoot = true;
	SetCharacterActionAnimation(sld, "dead", "lay_1");
	LAi_KillCharacter(sld);
	
	sld = GetCharacter(NPC_GenerateCharacter("WildRose_DiedCitiz_2", "Women_15", "woman", "woman", 1, ENGLAND, 0, false, "quest"));
	ChangeCharacterAddressGroup(sld, "Barbados_jungle_03", "goto", "goto5");
	TeleportCharacterToPosAy(sld, 16.75, 0.00, 18.85, 2.50);
	sld.DontClearDead = true;
	sld.CantLoot = true;
	LAi_SetActorType(sld);
	LAi_ActorSetLayMode(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
	
	pchar.questTemp.CameraDialogMode = true;
	
	sld = CharacterFromID("Mary");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	if (CharacterIsHere("Mary"))
	{
		sld.dialog.currentnode = "Mary_1";
	}
	else
	{
		ChangeCharacterAddressGroup(sld, "Barbados_jungle_03", "reload", LAi_FindNearestLocator2Pchar("reload"));
		sld.dialog.currentnode = "Mary_2";
	}
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 3, 0);
	sld.QuestImmortal = true;
}

void WildRose_Etap1_EscapeSlaves_3()
{
	// EndBattleLandInterface();
	LAi_SetActorType(pchar);
	LAi_ActorFollow(pchar, CharacterFromID("WildRose_DiedCitiz_2"), "WildRose_Etap1_EscapeSlaves_4", 6);
	sld = CharacterFromID("Mary");
	LAi_SetActorType(sld);
	LAi_ActorFollow(sld, CharacterFromID("WildRose_DiedCitiz_2"), "", -1);
}

void WildRose_Etap1_EscapeSlaves_5()
{
	sld = CharacterFromID("Mary");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "Mary_4";
	LAi_SetActorType(sld);
	LAi_ActorWaitDialog(pchar, sld);
	LAi_ActorDialogNow(sld, Pchar, "", -1);
}

void WildRose_Etap1_EscapeSlaves_6()
{
	CharacterTurnToLoc(pchar, "reload", "reload2");
	CharacterTurnToLoc(CharacterFromID("Mary"), "reload", "reload2");
	
	sld = GetCharacter(NPC_GenerateCharacter("WildRose_Naemnik_1", "mush_ctz_9", "man", "mushketer", sti(pchar.rank), PIRATE, 0, false, "pirate"));
	sld.name = StringFromKey("WildRose_2");
	sld.lastname = StringFromKey("WildRose_3");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "Naemnik_1";
	GiveItem2Character(sld, "mushket1");
	EquipCharacterByItem(sld, "mushket1");
	ChangeCharacterAddressGroup(sld, "Barbados_jungle_03", "reload", "reload2");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	LAi_ActorWaitDialog(pchar, sld);
	
	sld = GetCharacter(NPC_GenerateCharacter("WildRose_Naemnik_Rab", "Chard3", "man", "man", sti(pchar.rank), PIRATE, 0, false, "pirate"));
	sld.name = StringFromKey("WildRose_4");
	sld.lastname = StringFromKey("WildRose_5");
	ChangeCharacterAddressGroup(sld, "Barbados_jungle_03", "reload", "reload2");
	LAi_SetActorType(sld);
	LAi_ActorFollow(sld, CharacterFromID("WildRose_DiedCitiz_2"), "", -1);
	
	for (i=2; i<=5; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("WildRose_Naemnik_"+i, "citiz_4"+(rand(8)+1), "man", "man", sti(pchar.rank), PIRATE, 0, true, "pirate"));
		ChangeCharacterAddressGroup(sld, "Barbados_jungle_03", "reload", "reload2");
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, CharacterFromID("WildRose_Naemnik_1"), "", -1);
	}
}

void WildRose_Etap1_EscapeSlaves_6_1(string qName)
{
	sld = CharacterFromID("Mary");
	LAi_ActorAnimation(sld, "fight to normal", "1", 2.0);
}

void WildRose_Etap1_EscapeSlaves_7()
{
	LAi_LocationFightDisable(loadedLocation, false);
	LAi_SetPlayerType(pchar);
	LAi_SetFightMode(pchar, true);
	if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && CharacterIsAlive("Mary")) ReturnOfficer_Mary();
	
	sld = CharacterFromID("WildRose_Naemnik_Rab");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
	// LAi_ActorAfraid(sld, Pchar, true);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
	
	for (i=1; i<=5; i++)
	{
		sld = CharacterFromID("WildRose_Naemnik_"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
	LAi_group_SetCheckFunction("EnemyFight", "WildRose_Etap1_EscapeSlaves_8");
	
	sld = CharacterFromID("WildRose_DiedCitiz_2");
	SetCharacterActionAnimation(sld, "dead", "lay_1");
	LAi_KillCharacter(sld);
}

void WildRose_Etap1_EscapeSlaves_8(string qName)
{
	DoQuestCheckDelay("hide_weapon", 1.2);
	
	// sld = CharacterFromID("WildRose_Naemnik_Rab");
	sld = GetCharacter(NPC_GenerateCharacter("WildRose_Naemnik_Rab_mushketer", "Chard3_mush", "man", "mushketer", sti(pchar.rank), PIRATE, -1, false, "pirate"));
	sld.name = StringFromKey("WildRose_4");
	sld.lastname = StringFromKey("WildRose_5");
	GiveItem2Character(sld, "mushket1");
	EquipCharacterByItem(sld, "mushket1");
	ChangeCharacterAddressGroup(sld, "Barbados_jungle_03", "reload", "reload2");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "Djerry_1";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
}

void WildRose_Etap1_EscapeSlaves_9()
{
	LAi_LocationFightDisable(loadedLocation, true);
	LAi_SetStayType(pchar);
	
	sld = CharacterFromID("WildRose_Naemnik_Rab_mushketer");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "reload", "reload2", "", -1);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
	
	DoQuestFunctionDelay("WildRose_Etap1_EscapeSlaves_10", 2.5);
}

void WildRose_Etap1_EscapeSlaves_10(string qName)
{
	sld = CharacterFromID("Mary");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "Mary_11";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void WildRose_Etap1_EscapeSlaves_11()
{
	sld = CharacterFromID("WildRose_Naemnik_Rab_mushketer");
	LAi_SetActorType(sld);
	LAi_ActorAnimation(sld, "shot", "1", 1.5);
	CharacterTurnByChr(sld, pchar);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
	DoQuestFunctionDelay("WildRose_Etap1_EscapeSlaves_12", 2.0);
}

void WildRose_Etap1_EscapeSlaves_12(string qName)
{
	sld = CharacterFromID("WildRose_Naemnik_Rab_mushketer");
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "", 5);
	
	chrDisableReloadToLocation = false;
	LocatorReloadEnterDisable("Barbados_jungle_03", "reload1_back", true);
	LocatorReloadEnterDisable("Barbados_jungle_03", "reload3_back", true);
	
	SetFunctionLocationCondition("WildRose_Etap1_EscapeSlaves_13", "Shore5", false);
	
	LAi_SetPlayerType(pchar);
	if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && CharacterIsAlive("Mary")) ReturnOfficer_Mary();
}

void WildRose_Etap1_EscapeSlaves_13(string qName)
{
	chrDisableReloadToLocation = true;
	
	sld = CharacterFromID("WildRose_Naemnik_Rab_mushketer");
	ChangeCharacterAddressGroup(sld, "Shore5", "goto", "goto6");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
	LAi_group_SetCheckFunction("EnemyFight", "WildRose_Etap1_EscapeSlaves_14");
}

void WildRose_Etap1_EscapeSlaves_14(string qName)
{
	sld = CharacterFromID("Mary");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "Mary_21";
	if (!CharacterIsHere("Mary")) ChangeCharacterAddressGroup(sld, pchar.location, "reload", LAi_FindNearestLocator2Pchar("reload"));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 3, 0);
}

void WildRose_Etap1_EscapeSlaves_15()
{
	chrDisableReloadToLocation = false;
	LocatorReloadEnterDisable("Barbados_jungle_03", "reload1_back", false);
	LocatorReloadEnterDisable("Barbados_jungle_03", "reload3_back", false);
	LAi_LocationFightDisable(&Locations[FindLocation("Barbados_jungle_03")], false);
	locations[FindLocation("Barbados_jungle_03")].DisableEncounters = false;
	locations[FindLocation("Shore5")].DisableEncounters = false;
	if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && CharacterIsAlive("Mary")) ReturnOfficer_Mary();
	
	SetFunctionLocationCondition("WildRose_Etap1_City_1", "Bridgetown_town", false);
}

void WildRose_Etap1_City_1(string qName)
{
	chrDisableReloadToLocation = true;
	sld = CharacterFromID("Mary");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "Mary_23";
	if (!CharacterIsHere("Mary")) ChangeCharacterAddressGroup(sld, pchar.location, "reload", LAi_FindNearestLocator2Pchar("reload"));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 3, 0);
}

void WildRose_Etap1_City_2()
{
	WaitDate("", 0, 0, 0, 3, 0);
	CreateWeatherEnvironment();
	SetLaunchFrameFormParam(GetConvertStr("Frame_HourPassed_3", "Frame.txt"), "Run_Function", 0, 4.0);
	SetLaunchFrameRunFunctionParam("WildRose_Etap1_City_3", 0.0);
	LaunchFrameForm();
}

void WildRose_Etap1_City_3(string qName)
{
	DoFunctionReloadToLocation("Bridgetown_tavern_upstairs", "goto", "goto2", "WildRose_Etap1_City_4");
}

void WildRose_Etap1_City_4(string qName)
{
	sld = CharacterFromID("Mary");
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto2");
	if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && CharacterIsAlive("Mary")) ReturnOfficer_Mary();
	
	sld = GetCharacter(CreateCharacterClone(CharacterFromID("Bridgetown_tavernkeeper"), 0));
	sld.id = "Bridgetown_tavernkeeper_clone";
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "Barmen_1";
	ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	
	CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Bridgetown_tavernkeeper_clone"));
	CharacterTurnByChr(pchar, CharacterFromID("Bridgetown_tavernkeeper_clone"));
}

void WildRose_Etap1_City_5(string qName)
{
	sld = CharacterFromID("Bridgetown_tavernkeeper_clone");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "WildRose_Etap1_City_6", 3);
}

void WildRose_Etap1_City_7(string qName)
{
	sld = GetCharacter(NPC_GenerateCharacter("WildRose_Lewis", "Citiz_12", "man", "man", 1, ENGLAND, -1, false, "quest"));
	sld.name = StringFromKey("WildRose_6");
	sld.lastname = StringFromKey("WildRose_7");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "Lewis_1";
	ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1_back");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void WildRose_Etap1_City_8(string qName)
{
	sld = CharacterFromID("WildRose_Lewis");
	LAi_SetActorType(sld);
	LAi_ActorAnimation(sld, "ground_sitdown", "WildRose_Etap1_City_8_2", 3.0);
}

void WildRose_Etap1_City_9()
{
	sld = CharacterFromID("WildRose_Lewis");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "Lewis_7";
	LAi_SetActorType(sld);
	LAi_ActorSetGroundSitMode(sld);
	LAi_ActorDialogNow(sld, Pchar, "", -1);
}

void WildRose_Etap1_City_10(string qName)
{
	sld = CharacterFromID("WildRose_Lewis");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "WildRose_Etap1_City_11", 3);
}

void WildRose_Etap1_City_12(string qName)
{
	sld = CharacterFromID("Mary");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "Mary_31";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void WildRose_Etap1_Morning_1()
{
	SetLaunchFrameFormParam(GetConvertStr("Frame_NextMorning", "Frame.txt"), "Run_Function", 0, 4.0);
	SetLaunchFrameRunFunctionParam("WildRose_Etap1_Morning_2", 0.0);
	LaunchFrameForm();
}

void WildRose_Etap1_Morning_2(string qName)
{
	TavernWaitDateEx(6);
	chrDisableReloadToLocation = false;
	bDisableFastReload = true;
	
	AddQuestRecord("WildRose", "2");
	sld = CharacterFromID("Mary");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	RemovePassenger(pchar, sld);
	
	sld = GetCharacter(CreateCharacterClone(CharacterFromID("Bridgetown_waitress"), -1));
	sld.id = "Bridgetown_waitress_clone";
	ChangeCharacterAddressGroup(sld, "Bridgetown_tavern", "waitress", "barmen");
	sld = CharacterFromID("Bridgetown_waitress");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	
	SetFunctionLocationCondition("WildRose_Etap1_Morning_3", "Bridgetown_tavern", false);
}

void WildRose_Etap1_Morning_3(string qName)
{
	chrDisableReloadToLocation = true;
	
	sld = CharacterFromID("Bridgetown_waitress_clone");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "Waitress_1";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void WildRose_Etap1_Morning_4()
{
	sld = CharacterFromID("Bridgetown_waitress_clone");
	LAi_CharacterDisableDialog(sld);
	sld.lifeday = 0;
	
	chrDisableReloadToLocation = false;
	SetFunctionExitFromLocationCondition("WildRose_Etap1_Morning_5", PChar.location, false);
}

void WildRose_Etap1_Morning_5(string qName)
{
	sld = CharacterFromID("Bridgetown_waitress");
	ChangeCharacterAddressGroup(sld, "Bridgetown_tavern", "waitress", "barmen");
	
	sld = CharacterFromID("Mary");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "Mary_41";
	LAi_SetStayType(sld);
	ChangeCharacterAddressGroup(sld, "Bridgetown_town", "quest", "quest3");
	AddLandQuestMark(sld, "questmarkmain");
}

void WildRose_Etap1_Morning_6()
{
	sld = CharacterFromID("Mary");
	AddPassenger(pchar, sld, false);
	sld.OfficerImmortal = true;
	sld.Health.HP       = 60.0;
	sld.Health.maxHP    = 60.0;

	DeleteAttribute(sld, "QuestImmortal");
	ReturnOfficer_Mary();
	DeleteAttribute(pchar, "questTemp.MarySexBlock");
	
	AddQuestRecord("WildRose", "3");
	DeleteAttribute(pchar, "questTemp.CameraDialogMode");
	QuestOpenSeaExit();
	bDisableFastReload = false;
	
	//
	SetFunctionLocationCondition("WildRose_Etap2_IslandOfJustice_1", "LostShipsCity_town", false);
}

// ============================================================
// ================== ЭТАП 2. «ДИТЯ ОСТРОВА» ==================
// ============================================================

void WildRose_Etap2_IslandOfJustice_1(string qName)
{
	QuestCloseSeaExit();
	
	sld = CharacterFromID("Mary");
	ChangeCharacterAddressGroup(sld, pchar.location, "reload", LAi_FindNearestLocator2Pchar("reload"));
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "Mary_61";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void WildRose_Etap2_IslandOfJustice_2()
{
	AddQuestRecord("WildRose", "4");
	sld = CharacterFromID("Mary");
	RemovePassenger(pchar, sld);
	WildRose_MaryFollowing();
	
	//На Эсмеральду
	bDisableFastReload = true;
	LocatorReloadEnterDisable("LostShipsCity_town", "reload46", true);
	LocatorReloadEnterDisable("LostShipsCity_town", "reload46", true);
	LocatorReloadEnterDisable("LostShipsCity_town", "reload47", true);
	LocatorReloadEnterDisable("LostShipsCity_town", "reload48", true);
	LocatorReloadEnterDisable("LostShipsCity_town", "reload49", true);
	LocatorReloadEnterDisable("LostShipsCity_town", "reload50", true);
	SetFunctionLocatorCondition("WildRose_Etap2_IslandOfJustice_2_1", "LostShipsCity_town", "reload", "reload48", false);
	// QuestsCheck();
	
	sld = CharacterFromID("NarvalProt_1");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	
	sld = CharacterFromID("NarvalProt_3");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	
	sld = CharacterFromID("NarvalMush_1");
	ChangeCharacterAddressGroup(sld, "none", "", "");
}

void WildRose_Etap2_IslandOfJustice_2_1(string qName)
{
	chrDisableReloadToLocation = true;
	sld = GetCharacter(CreateCharacterClone(CharacterFromID("Schmidt"), 0));
	sld.id = "Schmidt_Clone";
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto04_7");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "Schmidt_1";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	AddLandQuestMark(sld, "questmarkmain");
}

void WildRose_Etap2_IslandOfJustice_3()
{
	chrDisableReloadToLocation = false;
	AddQuestRecord("WildRose", "5");
	WildRose_MaryFollowing();
	
	sld = CharacterFromID("Schmidt_Clone");
	LAi_SetCitizenType(sld);
	LAi_CharacterDisableDialog(sld);
	
	// в каюту «Церес Смити»
	SetFunctionLocationCondition("WildRose_Etap2_IslandOfJustice_4", "CeresSmithy", false);
}

void WildRose_Etap2_IslandOfJustice_4(string qName)
{
	sld = CharacterFromID("Mary");
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto11");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "Mary_71";
	LAi_SetStayType(sld);
	AddLandQuestMark(sld, "questmarkmain");
}

void WildRose_Etap2_IslandOfJustice_5()
{
	//катсцена секса
	//
	StartQuestMovie(true, false, true);
	LAi_FadeLong("", "");
	ref sld = CharacterFromID("Mary");
	LAi_SetActorType(sld);
	LAi_SetActorType(pchar);
	
	DoQuestFunctionDelay("WildRose_Etap2_IslandOfJustice_5_sex_1", 1.0);
}

void WildRose_Etap2_IslandOfJustice_5_sex_1(string qName)
{
    ref sld = CharacterFromID("Mary");
	pchar.quest.sex_partner = sld.id;
    SyncPlaybackDlt(PChar, sld);
	TeleportCharacterToLocatorIgnoreCollision(pchar, "quest", "quest3");
    TeleportCharacterToLocatorIgnoreCollision(sld, "quest", "quest4");
	LAi_ActorAnimation(pchar, "sharle_mary_kiss", "", -1.0);
	LAi_ActorAnimation(sld, "sharle_mary_kiss", "", -1.0);
	locCameraFromToPos(44.53, 4.61, 94.14, true, 42.39, 2.51, 95.61);
	
	DoQuestFunctionDelay("WildRose_Etap2_IslandOfJustice_5_sex_2", 3.5);
}

void WildRose_Etap2_IslandOfJustice_5_sex_2(string qName)
{
	locCameraFromToPos(45.18, 4.74, 96.27, true, 42.64, 2.45, 94.60);
	DoQuestFunctionDelay("WildRose_Etap2_IslandOfJustice_5_sex_3", 9.0);
}

void WildRose_Etap2_IslandOfJustice_5_sex_3(string qName)
{
	locCameraFromToPos(44.88, 4.52, 94.57, true, 42.20, 2.75, 96.16);
	DoQuestFunctionDelay("WildRose_Etap2_IslandOfJustice_5_sex_4", 10.0);
}

void WildRose_Etap2_IslandOfJustice_5_sex_4(string qName)
{
	SetLaunchFrameFormParam("", "", 0, 15);
	SetLaunchFrameFormPic("loading\inside\censored1.tga");
	PlayStereoSound("sex\sex" + (rand(9) + 1) + ".wav");
	LaunchFrameForm();
	// SetLaunchFrameFormParam(GetConvertStr("Frame_NextMorning", "Frame.txt"), "Run_Function", 0, 4.0);
	// SetLaunchFrameRunFunctionParam("WildRose_Etap2_IslandOfJustice_6_1", 0.0);
	// LaunchFrameForm();
	TavernWaitDateEx(6);
	LoveSex_Bonus();
	WildRose_Etap2_IslandOfJustice_6();
}

void WildRose_Etap2_IslandOfJustice_6()
{
	EndQuestMovie();
	LAi_SetPlayerType(pchar);
	ChangeCharacterAddressGroup(pchar, pchar.location, "goto", "goto10");
	locCameraFollowEx(true);
	sld = CharacterFromID("Mary");
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto11");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "Mary_81";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 0, 0);
}

void WildRose_Etap2_IslandOfJustice_7()
{
	chrDisableReloadToLocation = false;
	bDisableFastReload = false;
	WildRose_MaryFollowing();
	
	sld = CharacterFromID("Grinspy");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "Grinspy_1";
	AddLandQuestMark(sld, "questmarkmain");
	
	LocatorReloadEnterDisable("LostShipsCity_town", "reload46", false);
	LocatorReloadEnterDisable("LostShipsCity_town", "reload46", false);
	LocatorReloadEnterDisable("LostShipsCity_town", "reload47", false);
	LocatorReloadEnterDisable("LostShipsCity_town", "reload48", false);
	LocatorReloadEnterDisable("LostShipsCity_town", "reload49", false);
	LocatorReloadEnterDisable("LostShipsCity_town", "reload50", false);
	
	sld = CharacterFromID("NarvalProt_1");
	ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "soldiers", "protector1");
	
	sld = CharacterFromID("NarvalProt_3");
	ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "soldiers", "protector3");
	
	sld = CharacterFromID("NarvalMush_1");
	ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "soldiers", "mushketer1");
}

void WildRose_Etap2_IslandOfJustice_9()
{
	AddQuestRecord("WildRose", "6");
	chrDisableReloadToLocation = false;
	WildRose_MaryFollowing();
	
	sld = CharacterFromID("Grinspy");
	sld.dialog.filename = "Quest\LSC\Grinspy_Narval.c";
	sld.dialog.currentnode = "First time";
	
	//на Плуто
	sld = CharacterFromID("LSC_Oreli");
	sld.location.hours = 999999;
	LAi_RemoveLoginTime(sld);
	ChangeCharacterAddressGroup(sld, "none", "", "");
	
	sld = GetCharacter(CreateCharacterClone(CharacterFromID("LSC_Jillian"), -1));
	sld.id = "LSC_Jillian_clone";
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "Jillian_1";
	LAi_SetStayType(sld);
	ChangeCharacterAddressGroup(sld, "PlutoStoreSmall", "barmen", "bar1");
	AddLandQuestMark(sld, "questmarkmain");
	
	LocatorReloadEnterDisable("LostShipsCity_town", "reload11", true);
	LocatorReloadEnterDisable("LostShipsCity_town", "reload12", true);
}

void WildRose_Etap2_IslandOfJustice_10()
{
	SetFunctionTimerCondition("WildRose_Etap2_IslandOfJustice_10_1", 0, 0, 1, false);
	sld = CharacterFromID("LSC_Jillian_clone");
	LAi_SetActorType(sld);
	
	WildRose_MaryFollowing();
	
	ref sld = &Locations[FindLocation("LostShipsCity_town")];
	sld.reload.l47.close_for_night = 0;
}

void WildRose_Etap2_IslandOfJustice_10_1(string qName)
{
	sld = CharacterFromID("LSC_Oreli");
	sld.location.hours = 999999;
	LAi_RemoveLoginTime(sld);
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, "PlutoStoreSmall", "barmen", "bar1");
	
	sld = CharacterFromID("LSC_Jillian_clone");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "Jillian_26";
	LAi_SetStayType(sld);
	AddLandQuestMark(sld, "questmarkmain");
}

void WildRose_Etap2_IslandOfJustice_10_2()
{
	SetLaunchFrameFormParam(GetConvertStr("Frame_BeenWhile", "Frame.txt"), "Reload_To_Location", 0, 4.0);
	SetLaunchFrameReloadLocationParam("LostShipsCity_town", "goto", "goto10_0", "WildRose_Etap2_IslandOfJustice_10_3");
	LaunchFrameForm();
}

void WildRose_Etap2_IslandOfJustice_10_4()
{
	// TavernWaitDateEx(1);
	pchar.GenQuest.CannotWait = true;
	pchar.GenQuest.BlockTalkSelf = true;
	
	sld = CharacterFromID("Mary");
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto10_0");
	
	sld = CharacterFromID("LSC_Oreli");
	sld.location.hours = 999999;
	LAi_RemoveLoginTime(sld);
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto10_0");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "Oreli_1";
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, Pchar, "", -1);
	
	ref sld = &Locations[FindLocation("LostShipsCity_town")];
	sld.reload.l48.close_for_night = 0;
}

void WildRose_Etap2_IslandOfJustice_11()
{
	sld = CharacterFromID("LSC_Oreli");
	LAi_SetActorType(sld);
	LAi_ActorFollowEverywhere(sld, "", -1);
	
	WildRose_MaryFollowing();
	
	sld = CharacterFromID("Eddy");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "Eddy_1";
	LAi_SetStayType(sld);
	AddLandQuestMark(sld, "questmarkmain");
}

void WildRose_Etap2_IslandOfJustice_12()
{
	sld = CharacterFromID("Chimiset");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "Chimset_1";
	AddLandQuestMark(sld, "questmarkmain");
	
	sld = CharacterFromID("LSC_Oreli");
	LAi_SetActorType(sld);
	LAi_ActorFollowEverywhere(sld, "", -1);
	
	sld = CharacterFromID("Eddy");
	LAi_SetActorType(sld);
}

void WildRose_Etap2_IslandOfJustice_13()
{
	chrDisableReloadToLocation = true;
	WildRose_MaryFollowing();
	
	sld = CharacterFromID("LSC_Oreli");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
	
	sld = CharacterFromID("Zikomo");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
	
	sld = CharacterFromID("Chimiset");
	ChangeCharacterAddressGroup(sld, pchar.location, "barmen", "stay");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "WildRose_Etap2_IslandOfJustice_13_1", 10);
}

void WildRose_Etap2_IslandOfJustice_13_2()
{
	sld = CharacterFromID("LSC_Oreli");
	LAi_SetActorType(sld);
	LAi_type_actor_Reset(sld);
	sld.location.hours = 999999;
	ChangeCharacterAddressGroup(sld, "none", "", "");
	
	sld = CharacterFromID("Zikomo");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	
	sld = CharacterFromID("Chimiset");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	
	SetFunctionTimerConditionParam("WildRose_Etap2_IslandOfJustice_14", 0, 0, 0, sti(GetTime() + 5), false);
	
	chrDisableReloadToLocation = false;
	DeleteAttribute(pchar, "GenQuest.BlockTalkSelf");
	DeleteAttribute(pchar, "GenQuest.CannotWait");
}

void WildRose_Etap2_IslandOfJustice_14(string qName)
{
	sld = CharacterFromID("Chimiset");
	ChangeCharacterAddressGroup(sld, "ProtectorFisher", "sit", "sit1");
	LAi_SetHuberType(sld);
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "Chimset_11";
	AddLandQuestMark(sld, "questmarkmain");
	
	sld = CharacterFromID("LSC_Oreli");
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, "ProtectorFisher", "goto", "goto1");
	
	sld = CharacterFromID("Zikomo");
	LAi_SetStayType(sld);
	LAi_group_MoveCharacter(sld, "LSC_RIVADOS");
	ChangeCharacterAddressGroup(sld, "ProtectorFisher", "goto", "goto4");
	
	sld = CharacterFromID("Eddy");
	LAi_SetStayType(sld);
	sld.dialog.filename = "Quest\LSC\Eddy_Rivados.c";
	sld.dialog.currentnode = "Total_info";
}

void WildRose_Etap2_IslandOfJustice_14_1()
{
	// EndBattleLandInterface();
	sld = CharacterFromID("Chimiset");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "Chimset_13";
	LAi_SetActorType(sld);
	LAi_ActorSetHuberMode(sld);
	LAi_ActorDialogNow(sld, Pchar, "", -1);
}

void WildRose_Etap2_IslandOfJustice_15()
{
	SetLaunchFrameFormParam(GetConvertStr("Frame_MinutePassed_20", "Frame.txt"), "Reload_To_Location", 0, 4.0);
	SetLaunchFrameReloadLocationParam("PlutoStoreSmall", "barmen", "stay", "WildRose_Etap2_IslandOfJustice_15_1");
	LaunchFrameForm();
}

void WildRose_Etap2_IslandOfJustice_15_2()
{
	WaitDate("", 0, 0, 0, 0, 20);
		
	sld = CharacterFromID("Mary");
	ChangeCharacterAddressGroup(sld, pchar.location, "barmen", "bar1");
	
	sld = CharacterFromID("LSC_Oreli");
	ChangeCharacterAddressGroup(sld, pchar.location, "barmen", "bar1");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "Oreli_11";
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, Pchar, "", -1);
}

void WildRose_Etap2_IslandOfJustice_16()
{
	// SetLaunchFrameFormParam(GetConvertStr("Frame_MinutePassed_5", "Frame.txt"), "Reload_To_Location", 0, 4.0);
	// SetLaunchFrameReloadLocationParam("LostShipsCity_town", "goto", "goto09_7", "WildRose_Etap2_IslandOfJustice_16_1");
	// LaunchFrameForm();
	SetFunctionLocationCondition("WildRose_Etap2_IslandOfJustice_16_2", "LostShipsCity_town", false);
	WildRose_MaryFollowing();
	
	sld = CharacterFromID("LSC_Jillian_clone");
	LAi_SetActorType(sld);
	sld.lifeday = 0;
	
	sld = CharacterFromID("LSC_Oreli");
	sld.dialog.filename   = "Quest\LSC\Citizen\LSC_Oreli.c";
	sld.dialog.currentnode   = "First time";
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetOwnerType(sld);
	LAi_group_MoveCharacter(sld, "LSC_CITIZEN");
}

void WildRose_Etap2_IslandOfJustice_16_2(string qName)
{
	chrDisableReloadToLocation = true;
	sld = CharacterFromID("Mary");
	// ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto09_7");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "Mary_91";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void WildRose_Etap2_IslandOfJustice_17()
{
	chrDisableReloadToLocation = false;
	WildRose_MaryFollowing();
	AddQuestRecord("WildRose", "14");
	
	sld = CharacterFromID("Grinspy");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "Grinspy_31";
	AddLandQuestMark(sld, "questmarkmain");
}

void WildRose_Etap2_IslandOfJustice_18()
{
	WildRose_MaryFollowing();
	AddQuestRecord("WildRose", "15");
	
	sld = CharacterFromID("Grinspy");
	sld.dialog.filename = "Quest\LSC\Grinspy_Narval.c";
	sld.dialog.currentnode = "First time";
	
	sld = CharacterFromID("Dexter");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "WildRose_Dexter_1";
	AddLandQuestMark(sld, "questmarkmain");
}

void WildRose_Etap2_IslandOfJustice_19()
{
	WildRose_MaryFollowing();
	AddQuestRecord("WildRose", "16");
	
	sld = CharacterFromID("Dexter");
	sld.dialog.filename = "Quest\LSC\Dexter.c";
	sld.dialog.currentnode = "First time";
	
	sld = CharacterFromID("LSC_Betancur");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "WildRose_Betancur_1";
	AddLandQuestMark(sld, "questmarkmain");
}

void WildRose_Etap2_IslandOfJustice_19_1()
{
	LAi_SetStayType(pchar);
	sld = CharacterFromID("LSC_Betancur");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "barmen", "bar3", "WildRose_Etap2_Antonio_Finding", -1);
}

void WildRose_Etap2_IslandOfJustice_19_2()
{
	sld = CharacterFromID("LSC_Betancur");
	LAi_SetActorType(sld);
	CharacterTurnByLoc(sld, "barmen", "bar3");
	LAi_ActorAnimation(sld, "Barman_idle", "WildRose_Etap2_Antonio_Finding_2", 2.0);
}

void WildRose_Etap2_IslandOfJustice_19_3()
{
	sld = CharacterFromID("LSC_Betancur");
	sld.dialog.currentnode = "WildRose_Betancur_19";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void WildRose_Etap2_IslandOfJustice_20()
{
	chrDisableReloadToLocation = true;
	LAi_SetPlayerType(pchar);
	
	sld = CharacterFromID("Mary");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "WildRose_Mary_101";
	AddLandQuestMark(sld, "questmarkmain");
	
	sld = CharacterFromID("LSC_Betancur");
	LAi_SetActorType(sld);
}

void WildRose_Etap2_IslandOfJustice_21()
{
	chrDisableReloadToLocation = false;
	WildRose_MaryFollowing();
	AddQuestRecord("WildRose", "17");
	
	sld = CharacterFromID("Chimiset");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "WildRose_Chimiset_21";
	LAi_SetHuberType(sld);
	AddLandQuestMark(sld, "questmarkmain");
	
	sld = CharacterFromID("LSC_Betancur");
	sld.dialog.filename = "Quest\LSC\Citizen\LSC_Betancur.c";
	sld.dialog.currentnode = "First time";
	LAi_SetOwnerType(sld);
	LAi_group_MoveCharacter(sld, "LSC_CITIZEN");
}

void WildRose_Etap2_IslandOfJustice_22()
{
	WildRose_MaryFollowing();
	AddQuestRecord("WildRose", "18");
	
	sld = CharacterFromID("Julian");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "WildRose_Julian_1";
	AddLandQuestMark(sld, "questmarkmain");
	
	sld = CharacterFromID("Chimiset");
	sld.dialog.filename = "Quest\LSC\Chimiset.c";
	sld.dialog.currentnode = "Chimiset_wait";
}

void WildRose_Etap2_IslandOfJustice_23()
{
	chrDisableReloadToLocation = true;
	
	sld = CharacterFromID("Mary");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "WildRose_Mary_111";
	LAi_SetStayType(sld);
	AddLandQuestMark(sld, "questmarkmain");
	
	sld = CharacterFromID("Julian");
	sld.dialog.filename = "Quest\LSC\Julian_priest.c";
	sld.dialog.currentnode = "First time";
}

void WildRose_Etap2_IslandOfJustice_24()
{
	chrDisableReloadToLocation = false;
	WildRose_MaryFollowing();
	AddQuestRecord("WildRose", "19");
	
	sld = CharacterFromID("LSC_Sesil");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "WildRose_Sesil_1";
	AddLandQuestMark(sld, "questmarkmain");
	
	sld = CharacterFromID("Julian");
	sld.dialog.filename = "Quest\LSC\Julian_priest.c";
	sld.dialog.currentnode = "First time";
}

void WildRose_Etap2_IslandOfJustice_25()
{
	chrDisableReloadToLocation = false;
	WildRose_MaryFollowing();
	AddQuestRecord("WildRose", "20");
	
	sld = CharacterFromID("LSC_Sesil");
	sld.dialog.filename = "Quest\LSC\Citizen\LSC_Sesil.c";
	sld.dialog.currentnode = "First time";
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "LSC_CITIZEN");
	
	SetFunctionLocationCondition("WildRose_Etap2_IslandOfJustice_26", "LostShipsCity_town", false);
}

void WildRose_Etap2_IslandOfJustice_26(string qName)
{
	QuestOpenSeaExit();
	LocatorReloadEnterDisable("LostShipsCity_town", "reload11", false);
	LocatorReloadEnterDisable("LostShipsCity_town", "reload12", false);
	ref sld = &Locations[FindLocation("LostShipsCity_town")];
	sld.reload.l47.close_for_night = 1;
	sld = CharacterFromID("Mary");
	AddPassenger(pchar, sld, false);
	ReturnOfficer_Mary();
	
	// Продолжение у Бенуа
	SetFunctionLocationCondition("WildRose_Etap2_IslandOfJustice_27", "FortFrance_church", false);
}

void WildRose_Etap2_IslandOfJustice_27(string qName)
{
	AddLandQuestMark(characterFromId("Benua"), "questmarkmain");
	pchar.questTemp.WildRose_Etap3_Benua = true;
	sld = CharacterFromID("Mary");
	ChangeCharacterAddressGroup(sld, "FortFrance_church", "reload", "reload1");
	ReturnOfficer_Mary();
}

// =================================================================
// =================== ЭТАП 3. «БУМАЖНАЯ РАБОТА» ===================
// =================================================================
void WildRose_Etap3_Paperwork_1()
{
	AddQuestRecord("WildRose", "22");
	SetFunctionExitFromLocationCondition("WildRose_Etap3_Paperwork_2", PChar.location, false);
}

void WildRose_Etap3_Paperwork_2(string qName)
{
	chrDisableReloadToLocation = true;
	sld = CharacterFromID("Mary");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "WildRose_Mary_131";
	if (!CharacterIsHere("Mary")) ChangeCharacterAddressGroup(sld, pchar.location, "reload", LAi_FindNearestLocator2Pchar("reload"));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 3, 0);
}

void WildRose_Etap3_Paperwork_3()
{
	chrDisableReloadToLocation = false;
	if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && CharacterIsAlive("Mary")) ReturnOfficer_Mary();
	SetFunctionTimerCondition("WildRose_Etap3_Paperwork_4", 0, 2, 0, false);
}

void WildRose_Etap3_Paperwork_4(string qName)
{
	SetFunctionLocationCondition("WildRose_Etap3_Paperwork_4_1", "FortFrance_church", false);
}

void WildRose_Etap3_Paperwork_4_1(string qName)
{
	AddLandQuestMark(characterFromId("Benua"), "questmarkmain");
	pchar.questTemp.WildRose_Etap3_Benua_3 = true;
	sld = CharacterFromID("Mary");
	ChangeCharacterAddressGroup(sld, "FortFrance_church", "reload", "reload1");
	ReturnOfficer_Mary();
}

void WildRose_Etap3_Paperwork_5()
{
	SetFunctionExitFromLocationCondition("WildRose_Etap3_Paperwork_6", PChar.location, false);
}

void WildRose_Etap3_Paperwork_6(string qName)
{
	chrDisableReloadToLocation = true;
	sld = CharacterFromID("Mary");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "WildRose_Mary_134";
	if (!CharacterIsHere("Mary")) ChangeCharacterAddressGroup(sld, pchar.location, "reload", LAi_FindNearestLocator2Pchar("reload"));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 3, 0);
}

void WildRose_Etap3_Paperwork_7()
{
	SetLaunchFrameFormParam(GetConvertStr("Frame_MinutePassed_10", "Frame.txt"), "Run_Function", 0, 4.0);
	SetLaunchFrameRunFunctionParam("WildRose_Etap3_Paperwork_8", 0.0);
	LaunchFrameForm();
}

void WildRose_Etap3_Paperwork_8(string qName)
{
	sld = CharacterFromID("Mary");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "WildRose_Mary_139";
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, Pchar, "", -1);
	
}

void WildRose_Etap3_Paperwork_9()
{
	AddQuestRecord("WildRose", "23");
	chrDisableReloadToLocation = false;
	if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && CharacterIsAlive("Mary")) ReturnOfficer_Mary();
	SetFunctionLocationCondition("WildRose_Etap4_PathToLight_1", "LostShipsCity_town", false);
}

// =================================================================
// ==================== ЭТАП 4. «ПУТЬ К СВЕТУ» =====================
// =================================================================
void WildRose_Etap4_PathToLight_1(string qName)
{
	QuestCloseSeaExit();
	
	sld = CharacterFromID("Mary");
	ChangeCharacterAddressGroup(sld, pchar.location, "reload", LAi_FindNearestLocator2Pchar("reload"));
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "WildRose_Mary_161";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void WildRose_Etap4_PathToLight_2()
{
	sld = CharacterFromID("Mary");
	RemovePassenger(pchar, sld);
	WildRose_MaryFollowing();
	
	sld = GetCharacter(CreateCharacterClone(CharacterFromID("LSC_Jillian"), -1));
	sld.id = "LSC_Jillian_clone";
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "WildRose_Jillian_31";
	LAi_SetStayType(sld);
	ChangeCharacterAddressGroup(sld, "PlutoStoreSmall", "barmen", "bar1");
	AddLandQuestMark(sld, "questmarkmain");
	
	sld = CharacterFromID("LSC_Oreli");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	
	SetFunctionLocationCondition("WildRose_Etap4_PathToLight_3", "PlutoStoreSmall", false);
}

void WildRose_Etap4_PathToLight_3(string qName)
{
	sld = CharacterFromID("Mary");
	ChangeCharacterAddressGroup(sld, pchar.location, "reload", LAi_FindNearestLocator2Pchar("reload"));
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "WildRose_Mary_162";
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, Pchar, "", -1);
}

void WildRose_Etap4_PathToLight_4()
{
	WildRose_MaryFollowing();
}

void WildRose_Etap4_PathToLight_5()
{
	EndBattleLandInterface();
	sld = CharacterFromID("Mary");
	LAi_SetStayType(pchar);
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload5", "none", "", "", "", -1);
	
	DoQuestFunctionDelay("WildRose_Etap4_PathToLight_6", 2.0);
}

void WildRose_Etap4_PathToLight_6(string qName)
{
	sld = CharacterFromID("LSC_Jillian_clone");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "WildRose_Jillian_41";
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, Pchar, "", -1);
}

void WildRose_Etap4_PathToLight_7()
{
	bDisableFastReload = true;
	StartBattleLandInterface();
	LAi_SetPlayerType(pchar);
	SetFunctionLocationCondition("WildRose_Etap4_PathToLight_8", "LostShipsCity_town", false);
}

void WildRose_Etap4_PathToLight_8(string qName)
{
	sld = CharacterFromID("Mary");
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestLocator2Pchar("goto"));
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "WildRose_Mary_163";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void WildRose_Etap4_PathToLight_9()
{
	bDisableFastReload = false;
	WildRose_MaryFollowing();
	
	sld = CharacterFromID("LSC_Oreli");
	ChangeCharacterAddressGroup(sld, "GloriaChurch", "goto", "goto6");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "WildRose_Oreli_61";
	LAi_SetStayType(sld);
	AddLandQuestMark(sld, "questmarkmain");
}

void WildRose_Etap4_PathToLight_hat_1()
{
	EndBattleLandInterface();
	LAi_SetStayType(pchar);
	WildRose_MaryFollowing();
	LAi_FadeLong("", "");
	DoQuestFunctionDelay("WildRose_Etap4_PathToLight_hat_2", 1.0);
}

void WildRose_Etap4_PathToLight_hat_2(string qName)
{
	sld = CharacterFromID("Mary");
	GiveItem2Character(sld, "hat11");
	EquipCharacterByItem(sld, "hat11");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "WildRose_Mary_166";
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, Pchar, "", -1);
}

void WildRose_Etap4_PathToLight_10()
{
	StartBattleLandInterface();
	LAi_SetPlayerType(pchar);
	WildRose_MaryFollowing();
	sld = CharacterFromID("LSC_Oreli");
	LAi_SetActorType(sld);
	
	bDisableFastReload = true;
	SetFunctionLocationCondition("WildRose_Etap4_PathToLight_11", "LostShipsCity_town", false);
}

void WildRose_Etap4_PathToLight_11(string qName)
{
	chrDisableReloadToLocation = true;
	sld = CharacterFromID("Mary");
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestLocator2Pchar("goto"));
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "WildRose_Mary_171";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void WildRose_Etap4_PathToLight_12()
{
	chrDisableReloadToLocation = false;
	bDisableFastReload = false;
	WildRose_MaryFollowing();
	
	SetLaunchFrameFormParam(GetConvertStr("Frame_NextMorning", "Frame.txt"), "Reload_To_Location", 0, 4.0);
	SetLaunchFrameReloadLocationParam("CeresSmithy", "goto", "goto10", "WildRose_Etap4_PathToLight_12_1");
	LaunchFrameForm();
}

void WildRose_Etap4_PathToLight_13()
{
	AddQuestRecord("WildRose", "27");
		
	sld = CharacterFromID("LSC_Jillian_clone");
	ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "quest", "quest2");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "WildRose_Jillian_51";
	LAi_SetStayType(sld);
	AddLandQuestMark(sld, "questmarkmain");
	
	sld = CharacterFromID("LSC_Oreli");
	sld.lifeday = 0;
}

void WildRose_Etap4_PathToLight_14()
{
	chrDisableReloadToLocation = true;
	AddQuestRecord("WildRose", "28");
	
	sld = CharacterFromID("Mary");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", 7);
	
	sld = CharacterFromID("LSC_Jillian_clone");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
	
	sld = CharacterFromID("Chimiset");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "WildRose_Chimiset_61";
	AddLandQuestMark(sld, "questmarkmain");
}

void WildRose_Etap4_PathToLight_15()
{
	bDisableFastReload = true;
	SetFunctionLocationCondition("WildRose_Etap4_PathToLight_16", "LostShipsCity_town", false);
	
	sld = CharacterFromID("Chimiset");
	sld.dialog.filename = "Quest\LSC\Chimiset.c";
	sld.dialog.currentnode = "Chimiset_wait";
}

void WildRose_Etap4_PathToLight_16(string qName)
{
	chrDisableReloadToLocation = true;
	sld = CharacterFromID("Mary");
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestLocator2Pchar("goto"));
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "WildRose_Mary_191";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void WildRose_Etap4_PathToLight_17()
{
	chrDisableReloadToLocation = false;
	bDisableFastReload = false;
	WildRose_MaryFollowing();
	
	SetCurrentTime(19, 00);
	CreateWeatherEnvironment();
	
	SetLaunchFrameFormParam(GetConvertStr("Frame_NextDay", "Frame.txt"), "Reload_To_Location", 0, 4.0);
	SetLaunchFrameReloadLocationParam("Quest_ShipboardFuneral", "goto", "goto1", "WildRose_Etap4_PathToLight_17_1");
	LaunchFrameForm();
}

void WildRose_Etap4_PathToLight_18()
{
	CreateSea(EXECUTE, REALIZE);
	CreateWeather(EXECUTE,REALIZE);
	
	LAi_FadeToBlackStartInstantly();
	CreateRain(90, false, false);
	CreateWeatherEnvironment();
	ClearAllLogStrings();
	
	// sld = GetCharacter(CreateCharacterClone(CharacterFromID("Julian"), 0));
	// sld.id = "Julian_Clone";
	// ChangeCharacterAddressGroup(sld, "Quest_ShipboardFuneral", "quest", "quest1");
	
	LAi_SetStayType(pchar);
	TeleportCharacterToPosAy(pchar, 0.51, 2.16, 3.09, 3.70);
	
	sld = CharacterFromID("Mary");
	ChangeCharacterAddressGroup(sld, "Quest_ShipboardFuneral", "reload", "reload1");
	LAi_SetActorType(sld);
	TeleportCharacterToPosAy(sld, -0.31, 2.16, 3.73, 3.40);
	
	sld = GetCharacter(CreateCharacterClone(CharacterFromID("Dexter"), 0));
	sld.id = "Dexter_Clone";
	ChangeCharacterAddressGroup(sld, "Quest_ShipboardFuneral", "reload", "reload1");
	TeleportCharacterToPosAy(sld, -1.74, 2.16, 4.54, 3.10);
	LAi_SetActorType(sld);
	
	sld = GetCharacter(CreateCharacterClone(CharacterFromID("Axel"), 0));
	sld.id = "Axel_Clone";
	ChangeCharacterAddressGroup(sld, "Quest_ShipboardFuneral", "reload", "reload1");
	TeleportCharacterToPosAy(sld, -0.74, 2.16, 4.54, 3.30);
	LAi_SetActorType(sld);
	
	sld = GetCharacter(CreateCharacterClone(CharacterFromID("Facio"), 0));
	sld.id = "Facio_Clone";
	ChangeCharacterAddressGroup(sld, "Quest_ShipboardFuneral", "reload", "reload1");
	TeleportCharacterToPosAy(sld, -0.69, 2.16, 10.62, 3.30);
	LAi_SetActorType(sld);
	
	sld = GetCharacter(CreateCharacterClone(CharacterFromID("Mechanic"), 0));
	sld.id = "Mechanic_Clone";
	ChangeCharacterAddressGroup(sld, "Quest_ShipboardFuneral", "reload", "reload1");
	TeleportCharacterToPosAy(sld, 1.35, 2.16, 2.57, 3.90);
	LAi_SetActorType(sld);
	
	sld = GetCharacter(CreateCharacterClone(CharacterFromID("Schmidt"), 0));
	sld.id = "Schmidt_Clone";
	ChangeCharacterAddressGroup(sld, "Quest_ShipboardFuneral", "reload", "reload1");
	TeleportCharacterToPosAy(sld, 1.58, 2.16, -0.08, 4.70);
	LAi_SetActorType(sld);
	
	sld = GetCharacter(CreateCharacterClone(CharacterFromID("Grinspy"), 0));
	sld.id = "Grinspy_Clone";
	ChangeCharacterAddressGroup(sld, "Quest_ShipboardFuneral", "reload", "reload1");
	TeleportCharacterToPosAy(sld, 1.59, 2.16, 1.71, 4.30);
	LAi_SetActorType(sld);
	
	sld = GetCharacter(CreateCharacterClone(CharacterFromID("Carpentero"), 0));
	sld.id = "Carpentero_Clone";
	ChangeCharacterAddressGroup(sld, "Quest_ShipboardFuneral", "reload", "reload1");
	TeleportCharacterToPosAy(sld, 0.42, 2.16, 5.32, 3.40);
	LAi_SetActorType(sld);
	
	sld = GetCharacter(CreateCharacterClone(CharacterFromID("Natalie_Waitress"), 0));
	sld.id = "Natalie_Waitress_Clone";
	ChangeCharacterAddressGroup(sld, "Quest_ShipboardFuneral", "reload", "reload1");
	TeleportCharacterToPosAy(sld, 1.01, 2.16, 4.61, 3.40);
	LAi_SetActorType(sld);
	
	sld = GetCharacter(CreateCharacterClone(CharacterFromID("LSC_Alvaro"), 0));
	sld.id = "LSC_Alvaro_Clone";
	ChangeCharacterAddressGroup(sld, "Quest_ShipboardFuneral", "reload", "reload1");
	TeleportCharacterToPosAy(sld, -1.23, 2.16, 5.47, 3.10);
	LAi_SetActorType(sld);
	
	sld = GetCharacter(CreateCharacterClone(CharacterFromID("LSC_Betancur"), 0));
	sld.id = "LSC_Betancur_Clone";
	ChangeCharacterAddressGroup(sld, "Quest_ShipboardFuneral", "reload", "reload1");
	TeleportCharacterToPosAy(sld, -0.25, 2.16, 5.91, 3.10);
	LAi_SetActorType(sld);
	
	sld = GetCharacter(CreateCharacterClone(CharacterFromID("LSC_Gherad"), 0));
	sld.id = "LSC_Gherad_Clone";
	ChangeCharacterAddressGroup(sld, "Quest_ShipboardFuneral", "reload", "reload1");
	TeleportCharacterToPosAy(sld, 1.88, 2.16, 3.78, 4.10);
	LAi_SetActorType(sld);
	
	sld = GetCharacter(CreateCharacterClone(CharacterFromID("LSC_Jacklin"), 0));
	sld.id = "LSC_Jacklin_Clone";
	ChangeCharacterAddressGroup(sld, "Quest_ShipboardFuneral", "reload", "reload1");
	TeleportCharacterToPosAy(sld, 1.37, 2.16, 6.12, 3.50);
	LAi_SetActorType(sld);
	
	sld = GetCharacter(CreateCharacterClone(CharacterFromID("LSC_Lorenzo"), 0));
	sld.id = "LSC_Lorenzo_Clone";
	ChangeCharacterAddressGroup(sld, "Quest_ShipboardFuneral", "reload", "reload1");
	TeleportCharacterToPosAy(sld, 2.48, 2.16, 1.18, 4.60);
	LAi_SetActorType(sld);
	
	sld = GetCharacter(CreateCharacterClone(CharacterFromID("LSC_Jillian"), 0));
	sld.id = "LSC_Jillian_Clone";
	ChangeCharacterAddressGroup(sld, "Quest_ShipboardFuneral", "reload", "reload1");
	TeleportCharacterToPosAy(sld, 2.28, 2.16, 5.17, 3.80);
	LAi_SetActorType(sld);
	
	sld = GetCharacter(CreateCharacterClone(CharacterFromID("LSC_Jasper"), 0));
	sld.id = "LSC_Jasper_Clone";
	ChangeCharacterAddressGroup(sld, "Quest_ShipboardFuneral", "reload", "reload1");
	TeleportCharacterToPosAy(sld, 1.41, 2.16, 7.89, 3.50);
	LAi_SetActorType(sld);
	
	sld = GetCharacter(CreateCharacterClone(CharacterFromID("LSC_Oelart"), 0));
	sld.id = "LSC_Oelart_Clone";
	ChangeCharacterAddressGroup(sld, "Quest_ShipboardFuneral", "reload", "reload1");
	TeleportCharacterToPosAy(sld, 2.27, 2.16, 3.02, 4.20);
	LAi_SetActorType(sld);
	
	sld = GetCharacter(CreateCharacterClone(CharacterFromID("LSC_Ramona"), 0));
	sld.id = "LSC_Ramona_Clone";
	ChangeCharacterAddressGroup(sld, "Quest_ShipboardFuneral", "reload", "reload1");
	TeleportCharacterToPosAy(sld, -2.03, 2.16, 7.10, 3.10);
	LAi_SetActorType(sld);
	
	sld = GetCharacter(CreateCharacterClone(CharacterFromID("LSC_Rishard"), 0));
	sld.id = "LSC_Rishard_Clone";
	ChangeCharacterAddressGroup(sld, "Quest_ShipboardFuneral", "reload", "reload1");
	TeleportCharacterToPosAy(sld, -0.63, 2.16, 7.09, 3.20);
	LAi_SetActorType(sld);
	
	sld = GetCharacter(CreateCharacterClone(CharacterFromID("LSC_Sesil"), 0));
	sld.id = "LSC_Sesil_Clone";
	ChangeCharacterAddressGroup(sld, "Quest_ShipboardFuneral", "reload", "reload1");
	TeleportCharacterToPosAy(sld, 2.15, 2.16, 6.82, 3.70);
	LAi_SetActorType(sld);
	
	StartQuestMovie(true, false, true);
	locCameraFromToPos(-1.50, 3.86, 0.57, true, 0.92, 1.58, 5.23);
	
	DoQuestFunctionDelay("WildRose_Etap4_PathToLight_18_funeral_music", 0.5);
	DoQuestFunctionDelay("WildRose_Etap4_PathToLight_18_funeral_0", 1.5);
}

void WildRose_Etap4_PathToLight_18_funeral_music(string qName)
{
	SetMusic("music_LostShipsCity_old");
}

void WildRose_Etap4_PathToLight_18_funeral_0(string qName)
{
	LAi_FadeToBlackEnd();
	DoQuestFunctionDelay("WildRose_Etap4_PathToLight_18_funeral_1", 4.5);
	Achievment_Set("ach_CL_170");
}

void WildRose_Etap4_PathToLight_18_funeral_1(string qName)
{
	sld = CharacterFromID("Mary");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "WildRose_Mary_201";
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, Pchar, "", -1);
}

void WildRose_Etap4_PathToLight_18_funeral_2(string qName)
{
	sld = GetCharacter(CreateCharacterClone(CharacterFromID("Julian"), 0));
	sld.id = "Julian_Clone";
	ChangeCharacterAddressGroup(sld, "Quest_ShipboardFuneral", "reload", "reload1");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "quest", "quest1", "WildRose_Etap4_PathToLight_18_funeral_2_1", -1);
	
	sld = CharacterFromID("Mary");
	CharacterTurnToLoc(sld, "quest", "quest1");
	
	locCameraFromToPos(1.39, 4.85, 7.34, true, -0.82, 1.83, 1.75);
}

void WildRose_Etap4_PathToLight_18_funeral_3()
{
	DoQuestFunctionDelay("WildRose_Etap4_PathToLight_18_funeral_4", 1.0);
}

void WildRose_Etap4_PathToLight_18_funeral_4(string qName)
{
	locCameraFromToPos(-0.29, 4.17, 2.98, true, -2.85, 1.41, -0.14);
	DoQuestFunctionDelay("WildRose_Etap4_PathToLight_18_funeral_5", 2.5);
	
	sld = CharacterFromID("Julian_Clone");
	LAi_ActorAnimation(sld, "cross", "1", 5.0);
	CharacterTurnByLoc(sld, "quest", "quest1");
}

void WildRose_Etap4_PathToLight_18_funeral_5(string qName)
{
	locCameraFromToPos(-4.87, 4.64, -0.51, true, -1.57, 1.92, 1.99);
	DoQuestFunctionDelay("WildRose_Etap4_PathToLight_18_funeral_6", 1.0);
}

void WildRose_Etap4_PathToLight_18_funeral_6(string qName)
{
	sld = CharacterFromID("Julian_Clone");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "WildRose_funeral_1";
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, Pchar, "", -1);
}

void WildRose_Etap4_PathToLight_18_funeral_6_1()
{
	sld = CharacterFromID("Julian_Clone");
	LAi_ActorAnimation(sld, "cross", "WildRose_Etap4_PathToLight_18_funeral_6_2", 7.0);
	CharacterTurnByLoc(sld, "quest", "quest1");
	
	if (pchar.chr_ai.type != LAI_TYPE_ACTOR) LAi_SetActorType(pchar);
	LAi_ActorAnimation(pchar, "cross", "1", 7.0);
	
	sld = CharacterFromID("Mary");
	LAi_ActorAnimation(sld, "cross", "1", 7.0);
	
	sld = CharacterFromID("Dexter_Clone");
	if (rand(1) == 0) LAi_ActorAnimation(sld, "cross", "1", 7.0);
	
	sld = CharacterFromID("Axel_Clone");
	if (rand(1) == 0) LAi_ActorAnimation(sld, "cross", "1", 7.0);
	
	sld = CharacterFromID("Mechanic_Clone");
	if (rand(1) == 0) LAi_ActorAnimation(sld, "cross", "1", 7.0);
	
	sld = CharacterFromID("Schmidt_Clone");
	if (rand(1) == 0) LAi_ActorAnimation(sld, "cross", "1", 7.0);
	
	sld = CharacterFromID("Grinspy_Clone");
	if (rand(1) == 0) LAi_ActorAnimation(sld, "cross", "1", 7.0);
	
	sld = CharacterFromID("Carpentero_Clone");
	if (rand(1) == 0) LAi_ActorAnimation(sld, "cross", "1", 7.0);
	
	sld = CharacterFromID("LSC_Alvaro_Clone");
	if (rand(1) == 0) LAi_ActorAnimation(sld, "cross", "1", 7.0);
	
	sld = CharacterFromID("LSC_Lorenzo_Clone");
	if (rand(1) == 0) LAi_ActorAnimation(sld, "cross", "1", 7.0);
	
	sld = CharacterFromID("LSC_Ramona_Clone");
	if (rand(1) == 0) LAi_ActorAnimation(sld, "cross", "1", 7.0);
	
	sld = CharacterFromID("LSC_Rishard_Clone");
	if (rand(1) == 0) LAi_ActorAnimation(sld, "cross", "1", 7.0);
}

void WildRose_Etap4_PathToLight_18_funeral_7()
{
	LAi_type_actor_Reset(pchar);
	sld = CharacterFromID("Mary");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "WildRose_funeral_2";
	LAi_SetActorType(sld);
	LAi_type_actor_Reset(sld);
	SetActorDialogAny2Pchar(sld.id, "", -1, 0.0);
	LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 2.0);
}

void WildRose_Etap4_PathToLight_18_funeral_7_1()
{
	sld = CharacterFromID("Mary");
	LAi_SetActorType(pchar);
	LAi_SetActorType(sld);
	LAi_ActorAnimation(pchar, "cross", "1", 7.0);
	LAi_ActorAnimation(sld, "cross", "1", 7.0);
	CharacterTurnToLoc(pchar, "quest", "quest1");
	CharacterTurnToLoc(sld, "quest", "quest1");
	locCameraFromToPos(-0.80, 3.80, 1.87, true, 0.67, 2.04, 4.20);
}

void WildRose_Etap4_PathToLight_18_funeral_8()
{
	sld = CharacterFromID("Julian_Clone");
	LAi_SetActorType(sld);
	LAi_type_actor_Reset(sld);
	Event("QuestDelayExit","sl", "", 0);
	locCameraSleep(true);
	DoQuestFunctionDelay("WildRose_Etap4_PathToLight_18_funeral_9", 1.0);
}

void WildRose_Etap4_PathToLight_18_funeral_9(string qName)
{
	LAi_FadeToBlackStart();
	DoQuestFunctionDelay("WildRose_Etap4_PathToLight_18_funeral_10", 1.5);
}

void WildRose_Etap4_PathToLight_18_funeral_10(string qName)
{
	PlaySound("Sea Battles\bolshoy_vsplesk_002.wav");
	DoQuestFunctionDelay("WildRose_Etap4_PathToLight_18_funeral_11", 3.0);
}

void WildRose_Etap4_PathToLight_18_funeral_11(string qName)
{
	LAi_FadeToBlackEndInstantly();
	ref sld = &Locations[FindLocation("Quest_ShipboardFuneral")];
	sld.models.always.table_corpse = "outside_deck_QuestMary_table_empty";
	DoFunctionReloadToLocation("Quest_ShipboardFuneral", "quest", "quest1", "WildRose_Etap4_PathToLight_18_funeral_12");
}

void WildRose_Etap4_PathToLight_18_funeral_12(string qName)
{
	CreateSea(EXECUTE, REALIZE);
	CreateWeather(EXECUTE,REALIZE);
	DoQuestFunctionDelay("ChangeInterface", 0.1);
	LAi_SetStayType(pchar);
	
	locCameraFromToPos(0.56, 3.85, 1.02, true, -2.27, 1.79, 1.06);
	
	sld = CharacterFromID("Mary");
	ChangeCharacterAddressGroup(sld, "Quest_ShipboardFuneral", "quest", "quest3");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "WildRose_funeral_3";
	LAi_SetActorType(sld);
	LAi_type_actor_Reset(sld);
	LAi_ActorDialogNow(sld, Pchar, "", -1);
}

void WildRose_Etap4_PathToLight_18_funeral_13()
{
	EndQuestMovie();
	WaitDate("", 0, 0, 0, 2, 0);
	CreateWeatherEnvironment();
	SetLaunchFrameFormParam(GetConvertStr("Frame_HourPassed_2", "Frame.txt"), "Reload_To_Location", 0, 4.0);
	SetLaunchFrameReloadLocationParam("LostShipsCity_town", "quest", "quest1", "WildRose_Etap4_PathToLight_18_funeral_13_1");
	LaunchFrameForm();
}

void WildRose_Etap4_PathToLight_19()
{
	LAi_SetStayType(pchar);
	sld = CharacterFromID("Mary");
	ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "quest", "quest2");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "WildRose_Mary_211";
	LAi_SetActorType(sld);
	LAi_type_actor_Reset(sld);
	LAi_ActorDialogNow(sld, Pchar, "", -1);
}

void WildRose_Etap4_PathToLight_20(string qName)
{
	LAi_SetPlayerType(pchar);
	QuestOpenSeaExit();
	AddQuestRecord("WildRose", "29");
	sld = CharacterFromID("Mary");
	AddPassenger(pchar, sld, false);
	sld.OfficerImmortal = true;						
	sld.Health.HP       = 60.0; 						
	sld.Health.maxHP    = 60.0;						

	ReturnOfficer_Mary();
	
	// Продолжение у Фадея
	SetFunctionLocationCondition("WildRose_Etap4_PathToLight_21", "BasTer_houseSp1", false);
}

void WildRose_Etap4_PathToLight_21(string qName)
{
	AddLandQuestMark(characterFromId("Fadey"), "questmarkmain");
	pchar.questTemp.WildRose_Etap5_Fadey = true;
	sld = CharacterFromID("Mary");
	ChangeCharacterAddressGroup(sld, "BasTer_houseSp1", "reload", "reload1");
	ReturnOfficer_Mary();
}

// =================================================================
// ==================== ЭТАП 5. «ЧУЖИМИ РУКАМИ» ====================
// =================================================================
void WildRose_Etap5_Fadey_1()
{
	AddQuestRecord("WildRose", "30");
	SetFunctionExitFromLocationCondition("WildRose_Etap5_Fadey_2", PChar.location, false);
}

void WildRose_Etap5_Fadey_2(string qName)
{
	chrDisableReloadToLocation = true;
	sld = CharacterFromID("Mary");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "WildRose_Mary_231";
	if (!CharacterIsHere("Mary")) ChangeCharacterAddressGroup(sld, pchar.location, "reload", LAi_FindNearestLocator2Pchar("reload"));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 3, 0);
}

void WildRose_Etap5_Fadey_3()
{
	chrDisableReloadToLocation = false;
	if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && CharacterIsAlive("Mary")) ReturnOfficer_Mary();
	SetFunctionTimerCondition("WildRose_Etap5_Fadey_4", 0, 1, 0, false);
}

void WildRose_Etap5_Fadey_4(string qName)
{
	SetFunctionLocationCondition("WildRose_Etap5_Fadey_4_1", "BasTer_houseSp1", false);
}

void WildRose_Etap5_Fadey_4_1(string qName)
{
	AddLandQuestMark(characterFromId("Fadey"), "questmarkmain");
	pchar.questTemp.WildRose_Etap5_Fadey_3 = true;
	sld = CharacterFromID("Mary");
	ChangeCharacterAddressGroup(sld, "BasTer_houseSp1", "reload", "reload1");
	ReturnOfficer_Mary();
}

void WildRose_Etap5_Fadey_5()
{
	SetFunctionExitFromLocationCondition("WildRose_Etap5_Fadey_6", PChar.location, false);
}

void WildRose_Etap5_Fadey_6(string qName)
{
	chrDisableReloadToLocation = true;
	sld = CharacterFromID("Mary");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "WildRose_Mary_235";
	if (!CharacterIsHere("Mary")) ChangeCharacterAddressGroup(sld, pchar.location, "reload", LAi_FindNearestLocator2Pchar("reload"));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 3, 0);
}

void WildRose_Etap5_Fadey_7()
{
	AddQuestRecord("WildRose", "32");
	chrDisableReloadToLocation = false;
	if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && CharacterIsAlive("Mary")) ReturnOfficer_Mary();
	//
	SetFunctionLocationCondition("WildRose_Etap6_LifeAfterDeath_1", "Beliz_town", false);
}

// =================================================================
// ================= ЭТАП 6. «ЖИЗНЬ ПОСЛЕ СМЕРТИ» ==================
// =================================================================
void WildRose_Etap6_LifeAfterDeath_1(string qName)
{
	chrDisableReloadToLocation = true;
	sld = CharacterFromID("Mary");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "WildRose_Mary_241";
	if (!CharacterIsHere("Mary")) ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestLocator2Pchar("goto"));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 3, 0);
}

void WildRose_Etap6_LifeAfterDeath_2()
{
	AddQuestRecord("WildRose", "33");
	chrDisableReloadToLocation = false;
	pchar.questTemp.WildRose_Etap6_Beliz = true;
	pchar.questTemp.WildRose_Beliz_Citizen = true;
	AddLandQuestMark(characterFromId("Beliz_tavernkeeper"), "questmarkmain");
	ReturnOfficer_Mary();
}

void WildRose_Etap6_LifeAfterDeath_3_tavern()
{
	pchar.questTemp.WildRose_Etap6_BadEnd = true;
	WildRose_Etap6_LifeAfterDeath_3_next();
}

void WildRose_Etap6_LifeAfterDeath_3_citizen()
{
	pchar.questTemp.WildRose_Etap6_GoodEnd = true;
	WildRose_Etap6_LifeAfterDeath_3_next();
}

void WildRose_Etap6_LifeAfterDeath_3_next()
{
	DeleteAttribute(pchar, "questTemp.WildRose_Etap6_Beliz");
	DeleteAttribute(pchar, "questTemp.WildRose_Beliz_Citizen");
	DeleteAttribute(pchar, "questTemp.WildRose_Beliz_Citizen_2");
	DeleteAttribute(pchar, "questTemp.WildRose_Beliz_Citizen_3");
	DelLandQuestMark(characterFromId("Beliz_tavernkeeper"));
	
	SetFunctionLocationCondition("WildRose_Etap6_LifeAfterDeath_4", "Beliz_houseSp1", false);
	LocatorReloadEnterDisable("Beliz_town", "houseSp1", false);
}

void WildRose_Etap6_LifeAfterDeath_4(string qName)
{
	sld = GetCharacter(NPC_GenerateCharacter("WildRose_Bandit_1", "citiz_22", "man", "man", 30, PIRATE, -1, false, "pirate"));
	sld.name = StringFromKey("WildRose_8");
	sld.lastname = StringFromKey("WildRose_9");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "WildRose_BanditBeliz_1";
	GiveItem2Character(sld, "blade_13");
	EquipCharacterByItem(sld, "blade_13");
	GiveItem2Character(sld, "pistol4");
	EquipCharacterByItem(sld, "pistol4");
	ChangeCharacterAddressGroup(sld, "Beliz_houseSp1", "barmen", "stay");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 0, 0);
	
	sld = GetCharacter(NPC_GenerateCharacter("WildRose_Bandit_3", "citiz_45", "man", "man", 15, PIRATE, -1, true, "pirate"));
	ChangeCharacterAddressGroup(sld, "Beliz_houseSp1", "goto", "goto1");
	LAi_SetStayType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	LAi_SetCheckMinHP(sld, 1, true, "WildRose_Etap6_LifeAfterDeath_5_1");
	
	sld = CharacterFromID("Mary");
	ChangeCharacterAddressGroup(sld, "Beliz_houseSp1", "reload", "reload1");
	CharacterTurnByChr(sld, CharacterFromID("WildRose_Bandit_1"));
}

void WildRose_Etap6_LifeAfterDeath_5()
{
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(loadedLocation, false);
	LAi_SetFightMode(pchar, true);
	
	sld = CharacterFromID("WildRose_Bandit_1");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	
	sld = CharacterFromID("WildRose_Bandit_3");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	LAi_CharacterDisableDialog(sld);
	
	sld = GetCharacter(NPC_GenerateCharacter("WildRose_Bandit_2", "citiz_46", "man", "man", 15, PIRATE, -1, true, "pirate"));
	ChangeCharacterAddressGroup(sld, "Beliz_houseSp1", "reload", "reload2");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
	
	pchar.quest.WildRose_Etap6_LifeAfterDeath_6_1.win_condition.l1 = "NPC_Death";
	pchar.quest.WildRose_Etap6_LifeAfterDeath_6_1.win_condition.l1.character = "WildRose_Bandit_1";
	pchar.quest.WildRose_Etap6_LifeAfterDeath_6_1.win_condition.l2 = "NPC_Death";
	pchar.quest.WildRose_Etap6_LifeAfterDeath_6_1.win_condition.l2.character = "WildRose_Bandit_2";
	pchar.quest.WildRose_Etap6_LifeAfterDeath_6_1.function = "WildRose_Etap6_LifeAfterDeath_6_1";
}

void WildRose_Etap6_LifeAfterDeath_6()
{
	sld = CharacterFromID("WildRose_Bandit_3");
	LAi_SetStayType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
}

void WildRose_Etap6_LifeAfterDeath_6_1(string qName)
{
	LAi_LocationFightDisable(loadedLocation, true);
	DoQuestCheckDelay("hide_weapon", 1.2);
	sld = CharacterFromID("WildRose_Bandit_3");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "WildRose_BanditBeliz_2";
	LAi_SetGroundSitType(sld);
	LAi_CharacterEnableDialog(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
	AddLandQuestMark(sld, "questmarkmain");
}

void WildRose_Etap6_LifeAfterDeath_7()
{
	LAi_SetActorType(pchar);
	LAi_ActorAnimation(pchar, "Shot", "1", 1.8);
	CharacterTurnByChr(pchar, CharacterFromID("WildRose_Bandit_3"));
	DoQuestFunctionDelay("WildRose_Etap6_LifeAfterDeath_Hit", 0.8);
}

void WildRose_Etap6_LifeAfterDeath_8()
{
	sld = CharacterFromID("WildRose_Bandit_3");
	LAi_SetActorType(sld);
	LAi_ActorSetGroundSitMode(sld);
//	LAi_ActorAnimation(sld, "Ground_Death2", "", -1);
	SetCharacterActionAnimation(sld, "dead", "Ground_Death2");
	LAi_KillCharacter(sld);
	DoQuestFunctionDelay("WildRose_Etap6_LifeAfterDeath_9", 2.5);
}

void WildRose_Etap6_LifeAfterDeath_Hit(string qName)
{
	sld = CharacterFromID("WildRose_Bandit_3");
	LAi_SetActorType(sld);
	LAi_ActorSetGroundSitMode(sld);
	LAi_KillCharacter(sld);
	DoQuestFunctionDelay("WildRose_Etap6_LifeAfterDeath_9", 2.5);
}

void WildRose_Etap6_LifeAfterDeath_9(string qName)
{
	LAi_SetStayType(pchar);
	sld = CharacterFromID("Mary");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "WildRose_Mary_251";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void WildRose_Etap6_LifeAfterDeath_10_Tichingitu()
{
	pchar.questTemp.WildRose_Etap6_Tichingitu = true;
	WildRose_Etap6_LifeAfterDeath_10_next();
}

void WildRose_Etap6_LifeAfterDeath_10_Duran()
{
	pchar.questTemp.WildRose_Etap6_Duran = true;
	WildRose_Etap6_LifeAfterDeath_10_next();
}

void WildRose_Etap6_LifeAfterDeath_10_Tonzag()
{
	pchar.questTemp.WildRose_Etap6_Tonzag = true;
	WildRose_Etap6_LifeAfterDeath_10_next();
}

void WildRose_Etap6_LifeAfterDeath_10_Irons()
{
	pchar.questTemp.WildRose_Etap6_Irons = true;
	WildRose_Etap6_LifeAfterDeath_10_next();
}

void WildRose_Etap6_LifeAfterDeath_10_Longway()
{
	pchar.questTemp.WildRose_Etap6_Longway = true;
	WildRose_Etap6_LifeAfterDeath_10_next();
}

void WildRose_Etap6_LifeAfterDeath_10_Alonso()
{
	pchar.questTemp.WildRose_Etap6_Alonso = true;
	WildRose_Etap6_LifeAfterDeath_10_next();
}

void WildRose_Etap6_LifeAfterDeath_10_next()
{
	chrDisableReloadToLocation = false;
	LAi_SetPlayerType(pchar);
	ReturnOfficer_Mary();
	
	SetFunctionLocationCondition("WildRose_Etap6_LifeAfterDeath_11", "Beliz", false);
}

void WildRose_Etap6_LifeAfterDeath_11(string qName)
{
	pchar.GenQuest.CabinLock = true;
	Island_SetReloadEnableGlobal("Beliz", false);
	bQuestDisableMapEnter = true;
	
	DoQuestFunctionDelay("WildRose_Etap6_LifeAfterDeath_12", 2.5);
}

void WildRose_Etap6_LifeAfterDeath_12(string qName)
{
	DeleteAttribute(pchar, "GenQuest.CabinLock");
	pchar.GenQuest.DontSetCabinOfficer = true;
	chrDisableReloadToLocation = true;
	Sea_CabinStartNow();
	
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Tichingitu"))
	{
		sld = CharacterFromID("Tichingitu");
	}
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Duran"))
	{
		sld = CharacterFromID("Duran");
	}
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Tonzag"))
	{
		sld = CharacterFromID("Tonzag");
	}
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Irons"))
	{
		sld = CharacterFromID("Irons");
	}
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Longway"))
	{
		sld = CharacterFromID("Longway");
	}	
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Alonso"))
	{
		sld = GetCharacter(NPC_GenerateCharacter("WildRose_Alonso", "Alonso", "man", "man", sti(pchar.rank), FRANCE, -1, false, "soldier"));
		sld.name = GetCharacterName("Alonso");
		sld.lastname = "";
		GiveItem2Character(sld, "blade_10");
		EquipCharacterByItem(sld, "blade_10");
	}
	
	ChangeCharacterAddressGroup(sld, Get_My_Cabin(), "rld", "loc1");
	DoQuestFunctionDelay("WildRose_Etap6_LifeAfterDeath_13", 1.8);
}

void WildRose_Etap6_LifeAfterDeath_13(string qName)
{
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Tichingitu"))
	{
		sld = CharacterFromID("Tichingitu");
		sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
		sld.dialog.currentnode = "WildRose_Tichingitu_1";
	}
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Duran"))
	{
		sld = CharacterFromID("Duran");
		sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
		sld.dialog.currentnode = "WildRose_Duran_1";
	}
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Tonzag"))
	{
		sld = CharacterFromID("Tonzag");
		sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
		sld.dialog.currentnode = "WildRose_Tonzag_1";
	}
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Irons"))
	{
		sld = CharacterFromID("Irons");
		sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
		sld.dialog.currentnode = "WildRose_Irons_1";
	}
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Longway"))
	{
		sld = CharacterFromID("Longway");
		sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
		sld.dialog.currentnode = "WildRose_Longway_1";
	}
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Alonso"))
	{
		sld = CharacterFromID("WildRose_Alonso");
		sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
		sld.dialog.currentnode = "WildRose_Alonso_1";
	}
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void WildRose_Etap6_LifeAfterDeath_14()
{
	DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
	pchar.GenQuest.CabinLock = true;
	chrDisableReloadToLocation = false;
	
	SetFunctionLocationCondition("WildRose_Etap6_LifeAfterDeath_15", "Beliz", false);
	
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Tichingitu"))
	{
		sld = CharacterFromID("Tichingitu");
	}
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Duran"))
	{
		sld = CharacterFromID("Duran");
	}
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Tonzag"))
	{
		sld = CharacterFromID("Tonzag");
	}
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Irons"))
	{
		sld = CharacterFromID("Irons");
	}
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Longway"))
	{
		sld = CharacterFromID("Longway");
	}
	RemovePassenger(pchar, sld);
	LAi_SetActorType(sld);
}

void WildRose_Etap6_LifeAfterDeath_15(string qName)
{
	DoQuestFunctionDelay("WildRose_Etap6_LifeAfterDeath_16", 2.5);
}

void WildRose_Etap6_LifeAfterDeath_16(string qName)
{
	SetLaunchFrameFormParam(GetConvertStr("Frame_NextDay", "Frame.txt") + NewStr() + StringFromKey("WildRose_13"), "Run_Function", 0, 4.0);
	SetLaunchFrameRunFunctionParam("WildRose_Etap6_LifeAfterDeath_17", 0.0);
	LaunchFrameForm();
}

void WildRose_Etap6_LifeAfterDeath_17()
{
	WaitDate("", 0, 0, 1, 0, 0);
	SetCurrentTime(12, 00);
	CreateWeatherEnvironment();
	// setCharacterShipLocation(pchar, "Shore8");
	locations[FindLocation("Shore8")].DisableEncounters = true;
	locations[FindLocation("Beliz_jungle_03")].DisableEncounters = true;
	LAi_LocationFightDisable(&Locations[FindLocation("Shore8")], true);
	LAi_LocationFightDisable(&Locations[FindLocation("Beliz_jungle_03")], true);
	LAi_LocationDisableOfficersGen("Shore8", true);
	LAi_LocationDisableOfficersGen("Beliz_jungle_03", true);
	
	// SetFunctionLocationCondition("WildRose_Etap6_LifeAfterDeath_18", "Shore8", false);
	// DoReloadFromSeaToLocation("Shore8", "reload", "sea");
	Island_SetReloadEnableGlobal("Beliz", true);
	bQuestDisableMapEnter = false;
	DeleteAttribute(pchar, "GenQuest.CabinLock");
	
	SetFunctionLocationCondition("WildRose_Etap6_LifeAfterDeath_18", "Shore8", false);
}

void WildRose_Etap6_LifeAfterDeath_18(string qName)
{
	QuestCloseSeaExit();
	chrDisableReloadToLocation = true;
	
	sld = CharacterFromID("Mary");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "WildRose_Mary_256";
	ChangeCharacterAddressGroup(sld, "Shore8", "goto", "goto6");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 3, 0);
	
	sld = GetCharacter(NPC_GenerateCharacter("WildRose_EnemySoldier_0", "citiz_49", "man", "man", sti(pchar.rank), PIRATE, -1, true, "pirate"));
	ChangeCharacterAddressGroup(sld, "Shore8", "goto", "goto4");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
	
	SetFunctionLocationCondition("WildRose_Etap6_LifeAfterDeath_19", "Beliz_jungle_03", false);
}

void WildRose_Etap6_LifeAfterDeath_18_1()
{
	ReturnOfficer_Mary();
}

void WildRose_Etap6_LifeAfterDeath_19(string qName)
{
	StartQuestMovie(true, false, true);
	chrDisableReloadToLocation = true;
	pchar.questTemp.CameraDialogMode = true;
	DoQuestFunctionDelay("ChangeInterface", 0.1);
	
	sld = GetCharacter(NPC_GenerateCharacter("WildRose_Rupert", "Azzy", "man", "man", 30, PIRATE, -1, false, "pirate"));
	sld.name = StringFromKey("WildRose_10");
	sld.lastname = StringFromKey("WildRose_11");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "WildRose_Rupert_1";
	ChangeCharacterAddressGroup(sld, "Beliz_jungle_03", "goto", "goto4");
	TeleportCharacterToPosAy(sld, 6.54, 0.29, 2.61, 3.00);
	FantomMakeCoolFighter(sld, 30, 100, 100, "blade_WR", "pistol8", "harpoon", 0);
	LAi_SetHP(sld, 1000.0, 1000.0);
	AddBonusEnergyToCharacter(sld, 50);
	AddItems(sld, "harpoon", 20);
	AddItems(sld, "GunPowder", 20);
	AddItems(sld, "gold_dublon", 2000);
	AddItems(sld, "potion1", 5);	
	GiveItem2Character(sld, "talisman21");
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	LAi_SetActorType(sld);
	// AddLandQuestMark(sld, "questmarkmain");
	
	LAi_SetActorType(pchar);
	SetActorDialogAny2Pchar(sld.id, "", -1, 0.0);
	LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
	
	for (i=1; i<=4; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("WildRose_EnemySoldier_"+i, "mushketer_"+(rand(4)+1), "man", "mushketer", 20, PIRATE, 0, false, "soldier"));
		ChangeCharacterAddressGroup(sld, "Beliz_jungle_03", "goto", "goto4");
		FantomMakeCoolFighter(sld, 20, 75, 75, "", "mushket2", "bullet", 0);
		LAi_SetHP(sld, 100.0, 100.0);
		if (i==1) TeleportCharacterToPosAy(sld, 10.01, 0.29, 4.70, 3.00);
		if (i==2) TeleportCharacterToPosAy(sld, 8.01, 0.29, 4.70, 3.00);
		if (i==3) TeleportCharacterToPosAy(sld, 4.71, 0.29, 4.70, 3.00);
		if (i==4) TeleportCharacterToPosAy(sld, 2.71, 0.29, 4.70, 3.00);
	}
	
	for (i=5; i<=13; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("WildRose_EnemySoldier_"+i, "citiz_4"+(rand(7)+1), "man", "man", 20, PIRATE, 0, true, "pirate"));
		ChangeCharacterAddressGroup(sld, "Beliz_jungle_03", "goto", "goto4");
		LAi_SetHP(sld, 250.0, 250.0);
		if (i==5) TeleportCharacterToPosAy(sld, 22.28, 0.00, -14.16, -1.50);
		if (i==6) TeleportCharacterToPosAy(sld, 22.28, 0.00, -12.16, -1.50);
		if (i==7) TeleportCharacterToPosAy(sld, 22.28, 0.00, -10.16, -1.50);
		if (i==8) TeleportCharacterToPosAy(sld, -11.90, 0.00, -5.27, 1.50);
		if (i==9) TeleportCharacterToPosAy(sld, -11.90, 0.00, -3.27, 1.50);
		if (i==10) TeleportCharacterToPosAy(sld, -11.90, 0.00, -1.27, 1.50);
		if (i==11) TeleportCharacterToPosAy(sld, -8.90, 0.00, 19.80, 2.50);
		if (i==12) TeleportCharacterToPosAy(sld, -10.90, 0.00, 18.40, 2.50);
		if (i==13) TeleportCharacterToPosAy(sld, -12.90, 0.00, 17.00, 2.50);
	}
	
	sld = CharacterFromID("Mary");
	ChangeCharacterAddressGroup(sld, "Beliz_jungle_03", "reload", "reload1");
	LAi_SetActorType(sld);
	LAi_ActorFollow(sld, CharacterFromID("WildRose_Rupert"), "", -1);
}

void WildRose_Etap6_LifeAfterDeath_20()
{
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_BadEnd"))
	{
		EndBattleLandInterface();
		DoQuestFunctionDelay("WildRose_Etap6_LifeAfterDeath_21", 3.0);
	}
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_GoodEnd"))
	{
		WildRose_Etap6_LifeAfterDeath_29();
	}
}

void WildRose_Etap6_LifeAfterDeath_21(string qName)
{
	LAi_SetStayType(pchar);
	sld = CharacterFromID("WildRose_Rupert");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "WildRose_Rupert_87";
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, Pchar, "", -1);
}

void WildRose_Etap6_LifeAfterDeath_22()
{
	LAi_FadeLong("", "");
	DoQuestFunctionDelay("WildRose_Etap6_LifeAfterDeath_23", 1.0);
}

void WildRose_Etap6_LifeAfterDeath_23(string qName)
{
	locCameraFromToPos(2.80, 1.35, 13.16, true, 1.77, -0.70, 18.19);
	
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Tichingitu"))
	{
		sld = CharacterFromID("Tichingitu");
	}
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Duran"))
	{
		sld = CharacterFromID("Duran");
	}
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Tonzag"))
	{
		sld = CharacterFromID("Tonzag");
	}
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Irons"))
	{
		sld = CharacterFromID("Irons");
	}
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Longway"))
	{
		sld = CharacterFromID("Longway");
	}
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Alonso"))
	{
		sld = GetCharacter(NPC_GenerateCharacter("WildRose_Prisoner", "citiz_35", "man", "prisoner", sti(pchar.rank), FRANCE, 0, false, "quest"));
	}
	sld.model.animation = "prisoner";
	Characters_RefreshModel(sld);
	ChangeCharacterAddressGroup(sld, "Beliz_jungle_03", "goto", "goto4");
	TeleportCharacterToPosAy(sld, 1.37, 0.00, 19.84, 3.00);
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "goto", "goto7", "", -1);
	sld.CantLoot = true;
	DeleteAttribute(sld, "OfficerImmortal");
	SendMessage(sld, "lslssl", MSG_CHARACTER_EX_MSG, "TieItem", FindItem("Shackles"), "Shackles", "Saber_hand", 1);
	
	sld = GetCharacter(NPC_GenerateCharacter("WildRose_EnemySoldier_14", "citiz_42", "man", "man", 20, PIRATE, 0, true, "pirate"));
	ChangeCharacterAddressGroup(sld, "Beliz_jungle_03", "goto", "goto4");
	LAi_SetHP(sld, 250.0, 250.0);
	TeleportCharacterToPosAy(sld, 0.37, 0.00, 19.84, 3.00);
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "goto", "goto7", "", -1);
	
	sld = GetCharacter(NPC_GenerateCharacter("WildRose_EnemySoldier_15", "citiz_50", "man", "man", 20, PIRATE, 0, true, "pirate"));
	ChangeCharacterAddressGroup(sld, "Beliz_jungle_03", "goto", "goto4");
	LAi_SetHP(sld, 250.0, 250.0);
	TeleportCharacterToPosAy(sld, 2.37, 0.00, 19.84, 3.00);
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "goto", "goto7", "", -1);
	
	DoQuestFunctionDelay("WildRose_Etap6_LifeAfterDeath_23_prisoner_1", 2.5);
}

void WildRose_Etap6_LifeAfterDeath_23_prisoner_1(string qName)
{
	LAi_FadeToBlackStart();
	DoQuestFunctionDelay("WildRose_Etap6_LifeAfterDeath_23_prisoner_2", 1.0);
}

void WildRose_Etap6_LifeAfterDeath_23_prisoner_2(string qName)
{
	// locCameraFollowEx(true);
	locCameraFromToPos(4.39, 1.70, 1.25, true, 5.74, -0.70, 2.69);
	
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Tichingitu"))
	{
		sld = CharacterFromID("Tichingitu");
	}
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Duran"))
	{
		sld = CharacterFromID("Duran");
	}
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Tonzag"))
	{
		sld = CharacterFromID("Tonzag");
	}
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Irons"))
	{
		locCameraFromToPos(3.77, 1.73, 0.72, true, 5.44, -0.40, 2.38);	// Для Айронса отдельный ракурс камеры, так как у него исчезает голова!!!!!!!!!!1111
		sld = CharacterFromID("Irons");
	}
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Longway"))
	{
		sld = CharacterFromID("Longway");
	}	
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Alonso"))
	{
		sld = CharacterFromID("WildRose_Prisoner");
	}
	TeleportCharacterToPosAy(sld, 5.54, 0.29, 2.61, 3.00);
	LAi_SetActorType(sld);
	LAi_ActorSetGroundSitMode(sld);
	// CharacterTurnByChr(sld, pchar);
	
	sld = CharacterFromID("WildRose_EnemySoldier_14");
	ChangeCharacterAddressGroup(sld, "Beliz_jungle_03", "goto", "ass3");
	LAi_type_actor_Reset(sld);
	CharacterTurnByChr(sld, pchar);
	
	sld = CharacterFromID("WildRose_EnemySoldier_15");
	ChangeCharacterAddressGroup(sld, "Beliz_jungle_03", "goto", "ass4");
	LAi_type_actor_Reset(sld);
	CharacterTurnByChr(sld, pchar);
	
	DoQuestFunctionDelay("WildRose_Etap6_LifeAfterDeath_23_prisoner_3", 0.5);
}

void WildRose_Etap6_LifeAfterDeath_23_prisoner_3(string qName)
{
	LAi_FadeToBlackEnd();
	DoQuestFunctionDelay("WildRose_Etap6_LifeAfterDeath_24", 3.0);
	// DoQuestFunctionDelay("WildRose_Etap6_LifeAfterDeath_24", 1.2);
}

void WildRose_Etap6_LifeAfterDeath_24(string qName)
{
	locCameraFollowEx(true);
	// locCameraSleep(true);
	sld = CharacterFromID("WildRose_Rupert");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "WildRose_Rupert_88";
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, Pchar, "", -1);
	// SetActorDialogAny2Pchar(sld.id, "", -1, 0.0);
	// LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 2.0);
}

// void WildRose_Etap6_LifeAfterDeath_24_1()
// {
	// sld = CharacterFromID("WildRose_Prisoner");
	// LAi_SetActorType(sld);
	// LAi_ActorSetGroundSitMode(sld);
// }

void WildRose_Etap6_LifeAfterDeath_25()
{
	locCameraFromToPos(3.05, 1.12, 3.86, true, 7.47, -0.38, 0.79);
	
	sld = CharacterFromID("WildRose_Rupert");
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Tichingitu")) CharacterTurnByChr(sld, CharacterFromID("Tichingitu"));
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Duran")) CharacterTurnByChr(sld, CharacterFromID("Duran"));
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Tonzag")) CharacterTurnByChr(sld, CharacterFromID("Tonzag"));
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Irons")) CharacterTurnByChr(sld, CharacterFromID("Irons"));
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Longway")) CharacterTurnByChr(sld, CharacterFromID("Longway"));
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Alonso")) CharacterTurnByChr(sld, CharacterFromID("WildRose_Prisoner"));
	DoQuestFunctionDelay("WildRose_Etap6_LifeAfterDeath_26", 1.5);
}

void WildRose_Etap6_LifeAfterDeath_26(string qName)
{
	sld = CharacterFromID("WildRose_Rupert");
	LAi_ActorAnimation(sld, "Shot", "1", 1.8);
	DoQuestFunctionDelay("WildRose_Etap6_LifeAfterDeath_27", 0.8);
}

void WildRose_Etap6_LifeAfterDeath_27(string qName)
{
	sld = CharacterFromID("Mary");
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Tichingitu")) CharacterTurnByChr(pchar, CharacterFromID("Tichingitu"));
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Duran")) CharacterTurnByChr(pchar, CharacterFromID("Duran"));
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Tonzag")) CharacterTurnByChr(pchar, CharacterFromID("Tonzag"));
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Irons")) CharacterTurnByChr(pchar, CharacterFromID("Irons"));
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Longway")) CharacterTurnByChr(pchar, CharacterFromID("Longway"));
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Alonso")) CharacterTurnByChr(pchar, CharacterFromID("WildRose_Prisoner"));
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Tichingitu")) CharacterTurnByChr(sld, CharacterFromID("Tichingitu"));
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Duran")) CharacterTurnByChr(sld, CharacterFromID("Duran"));
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Tonzag")) CharacterTurnByChr(sld, CharacterFromID("Tonzag"));
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Irons")) CharacterTurnByChr(sld, CharacterFromID("Irons"));
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Longway")) CharacterTurnByChr(sld, CharacterFromID("Longway"));
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Alonso")) CharacterTurnByChr(sld, CharacterFromID("WildRose_Prisoner"));
	
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Tichingitu"))
	{
		sld = CharacterFromID("Tichingitu");
	}
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Duran"))
	{
		sld = CharacterFromID("Duran");
	}
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Tonzag"))
	{
		sld = CharacterFromID("Tonzag");
	}
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Irons"))
	{
		sld = CharacterFromID("Irons");
	}
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Longway"))
	{
		sld = CharacterFromID("Longway");
	}	
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Alonso"))
	{
		sld = CharacterFromID("WildRose_Prisoner");
	}
	LaunchBlood(sld, 1.0, true, "fight");
	LaunchBlood(sld, 1.0, true, "fight");
	LaunchBlood(sld, 1.0, true, "fight");
	// LAi_KillCharacter(sld);
	LAi_ActorAnimation(sld, "Ground_Death", "", 5.0);
	
	DoQuestFunctionDelay("WildRose_Etap6_LifeAfterDeath_28", 2.5);
}

void WildRose_Etap6_LifeAfterDeath_28(string qName)
{
	sld = CharacterFromID("Mary");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "WildRose_Rupert_90";
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, Pchar, "", -1);
	// SetActorDialogAny2Pchar(sld.id, "", -1, 0.0);
	// LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 2.0);
}

void WildRose_Etap6_LifeAfterDeath_29()
{
	EndQuestMovie();
	LAi_LocationFightDisable(loadedLocation, false);
	StartBattleLandInterface();
	LAi_SetPlayerType(pchar);
	LAi_SetFightMode(pchar, true);
	
	sld = CharacterFromID("WildRose_Rupert");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	for (i=1; i<=15; i++)
	{
		if (CharacterIsAlive("WildRose_EnemySoldier_"+i))
		{
			sld = CharacterFromID("WildRose_EnemySoldier_"+i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
	}
	ReturnOfficer_Mary();
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_BadEnd"))
	{
		if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Tichingitu"))
		{
			sld = CharacterFromID("Tichingitu");
		}
		if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Duran"))
		{
			sld = CharacterFromID("Duran");
		}
		if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Tonzag"))
		{
			sld = CharacterFromID("Tonzag");
		}
		if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Irons"))
		{
			sld = CharacterFromID("Irons");
		}
		if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Longway"))
		{
			sld = CharacterFromID("Longway");
		}	
		if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Alonso"))
		{
			sld = CharacterFromID("WildRose_Prisoner");
		}
		RemovePassenger(pchar, sld);
		sld.lifeday = 0;
		ChangeCharacterAddressGroup(sld, "none", "", "");
		
		LAi_LocationDisableOfficersGen("Beliz_jungle_03", false);
		for(int i=1; i<=3; i++)
		{
			int idx = GetOfficersIndex(pchar, i);
			if(idx < 0) continue;
			sld = &Characters[idx];
			if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_BadEnd"))
			{
				if (!CharacterIsHere(sld)) ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			}
			if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_GoodEnd"))
			{
				if (!CharacterIsHere(sld)) ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload2");
			}
		}
	}
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_GoodEnd"))
	{
		if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Tichingitu"))
		{
			sld = CharacterFromID("Tichingitu");
			ReturnOfficer_Tichingitu();
		}
		if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Duran"))
		{
			sld = CharacterFromID("Duran");
			ReturnOfficer_Duran();
		}
		if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Tonzag"))
		{
			sld = CharacterFromID("Tonzag");
			ReturnOfficer_Tonzag();
		}
		if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Irons"))
		{
			sld = CharacterFromID("Irons");
			ReturnOfficer_Irons();
		}
		if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Longway"))
		{
			sld = CharacterFromID("Longway");
			ReturnOfficer_Longway();
		}
		ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload2");
		sld.QuestImmortal = true;
	
	}
	pchar.OfficerAttRange = 35.0;
	OfficersFollow();
	for (i=1; i<=10; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("WildRose_OurSoldier_"+i, "citiz_3"+(rand(7)+1), "man", "man", 15, FRANCE, 0, true, "pirate"));
		if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_BadEnd")) ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
		if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_GoodEnd")) ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload2");
		LAi_SetHP(sld, 175.0, 175.0);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	sld = GetCharacter(NPC_GenerateCharacter("WildRose_Alonso", "Alonso", "man", "man", 20, FRANCE, 0, false, "pirate"));
	sld.name = GetCharacterName("Alonso");
	sld.lastname = "";
	GiveItem2Character(sld, "blade_10");
	EquipCharacterByItem(sld, "blade_10");
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_BadEnd")) ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_GoodEnd")) ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload2");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	sld.QuestImmortal = true;
	
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
	LAi_group_SetCheckFunction("EnemyFight", "WildRose_Etap6_LifeAfterDeath_30");
	//
	AutoSave();
}

void WildRose_Etap6_LifeAfterDeath_30(string qName)
{
	LAi_group_Delete("EnemyFight");
	DoQuestCheckDelay("hide_weapon", 1.2);
	LAi_LocationFightDisable(loadedLocation, true);
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_BadEnd"))
	{
		sld = CharacterFromID("WildRose_Alonso");
		sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
		sld.dialog.currentnode = "WildRose_Alonso_11";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		AddLandQuestMark(sld, "questmarkmain");
	}
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_GoodEnd"))
	{
		if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Tichingitu"))
		{
			sld = CharacterFromID("Tichingitu");
			sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
			sld.dialog.currentnode = "WildRose_Tichingitu_Final_1";
		}
		if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Duran"))
		{
			sld = CharacterFromID("Duran");
			sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
			sld.dialog.currentnode = "WildRose_Duran_Final_1";
		}
		if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Tonzag"))
		{
			sld = CharacterFromID("Tonzag");
			sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
			sld.dialog.currentnode = "WildRose_Tonzag_Final_1";
		}
		if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Irons"))
		{
			sld = CharacterFromID("Irons");
			sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
			sld.dialog.currentnode = "WildRose_Irons_Final_1";
		}
		if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Longway"))
		{
			sld = CharacterFromID("Longway");
			sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
			sld.dialog.currentnode = "WildRose_Longway_Final_1";
		}
		if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Alonso"))
		{
			sld = CharacterFromID("WildRose_Alonso");
			sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
			sld.dialog.currentnode = "WildRose_Alonso_Final_1";
		}
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		AddLandQuestMark(sld, "questmarkmain");
	}
}

void WildRose_Etap6_LifeAfterDeath_31()
{
	sld = CharacterFromID("WildRose_Alonso");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "WildRose_Etap6_LifeAfterDeath_31_1", 10);
	for (i=1; i<=10; i++)
	{
		if (CharacterIsAlive("WildRose_OurSoldier_"+i))
		{
			sld = CharacterFromID("WildRose_OurSoldier_"+i);
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, CharacterFromID("WildRose_Alonso"), "", -1);
		}
	}
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_GoodEnd"))
	{
		if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Tichingitu")) sld = CharacterFromID("Tichingitu");
		if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Duran")) sld = CharacterFromID("Duran");
		if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Tonzag")) sld = CharacterFromID("Tonzag");
		if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Irons")) sld = CharacterFromID("Irons");
		if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Longway")) sld = CharacterFromID("Longway");
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, CharacterFromID("WildRose_Alonso"), "", -1);
	}
}

void WildRose_Etap6_LifeAfterDeath_32()
{
	for (i=1; i<=10; i++)
	{
		if (CharacterIsAlive("WildRose_OurSoldier_"+i))
		{
			sld = CharacterFromID("WildRose_OurSoldier_"+i);
			ChangeCharacterAddressGroup(sld, "none", "", "");
		}
	}
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Tichingitu")) sld = CharacterFromID("Tichingitu");
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Duran")) sld = CharacterFromID("Duran");
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Tonzag")) sld = CharacterFromID("Tonzag");
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Irons")) sld = CharacterFromID("Irons");
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Longway")) sld = CharacterFromID("Longway");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	SetFunctionLocatorCondition("WildRose_Etap6_LifeAfterDeath_33", "Beliz_jungle_03", "reload", "reload1_back", false);
}

void WildRose_Etap6_LifeAfterDeath_33(string qName)
{
	TavernWaitDateEx(15);
	SetLaunchFrameFormParam(GetConvertStr("Frame_HourPassed_?", "Frame.txt"), "Run_Function", 0, 4.0);
	SetLaunchFrameRunFunctionParam("WildRose_Etap6_LifeAfterDeath_34", 0.0);
	LaunchFrameForm();
}

void WildRose_Etap6_LifeAfterDeath_34(string qName)
{
	DoFunctionReloadToLocation("Shore8", "quest", "quest1", "WildRose_Etap6_LifeAfterDeath_35");
}

void WildRose_Etap6_LifeAfterDeath_35()
{
	StartQuestMovie(true, false, true);
	LAi_FadeToBlackStartInstantly();
	ClearAllLogStrings();
	
	TeleportCharacterToLocatorIgnoreCollision(pchar, "quest", "quest1");
	CharacterTurnAy(pchar, 6.00);
	LAi_SetActorType(pchar);
	
	sld = CharacterFromID("Mary");
	sld.dialog.filename = "Quest\CompanionQuests\WildRose.c";
	sld.dialog.currentnode = "WildRose_Mary_261";
	IgnoreCollision(sld, true);
	ChangeCharacterAddressGroup(sld, "Shore8", "reload", "reload1");
	TeleportCharacterToLocatorIgnoreCollision(sld, "quest", "quest2");
	CharacterTurnAy(sld, 6.00);
	LAi_SetActorType(sld);
	SetActorDialogAny2Pchar(sld.id, "", 0, 0.0);
	LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 0.0);
	
	DoQuestFunctionDelay("WildRose_Etap6_LifeAfterDeath_36", 1.0);
}

void WildRose_Etap6_LifeAfterDeath_36(string qName)
{
	LAi_FadeToBlackEnd();
	locCameraSleep(true);
}

void WildRose_Etap6_LifeAfterDeath_38()
{
	TavernWaitDateEx(7);
	SetLaunchFrameFormParam(GetConvertStr("Frame_NextMorning", "Frame.txt"), "Run_Function", 0, 4.0);
	SetLaunchFrameRunFunctionParam("WildRose_Etap6_LifeAfterDeath_39", 0.0);
	LaunchFrameForm();
}

void WildRose_Etap6_LifeAfterDeath_39()
{
	EndQuestMovie();
	LAi_SetPlayerType(pchar);
	sld = CharacterFromID("Mary");
	IgnoreCollision(sld, false);
	ReturnOfficer_Mary();
	
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_GoodEnd"))
	{
		if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Tichingitu"))
		{
			ReturnOfficer_Tichingitu();
			sld = CharacterFromID("Tichingitu");
		}
		if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Duran"))
		{
			ReturnOfficer_Duran();
			sld = CharacterFromID("Duran");
		}
		if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Tonzag"))
		{
			ReturnOfficer_Tonzag();
			sld = CharacterFromID("Tonzag");
		}
		if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Irons"))
		{
			ReturnOfficer_Irons();
			sld = CharacterFromID("Irons");
		}
		if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Longway"))
		{
			ReturnOfficer_Longway();
			sld = CharacterFromID("Longway");
		}
		AddPassenger(pchar, sld, false);
		DeleteAttribute(sld, "QuestImmortal");	
	}
	
	bQuestDisableMapEnter = true;
	Island_SetReloadEnableGlobal("Beliz", false);
	chrDisableReloadToLocation = false;
	QuestOpenSeaExit();
	locations[FindLocation("Shore8")].DisableEncounters = false;
	locations[FindLocation("Beliz_jungle_03")].DisableEncounters = false;
	LAi_LocationFightDisable(&Locations[FindLocation("Shore8")], false);
	LAi_LocationFightDisable(&Locations[FindLocation("Beliz_jungle_03")], false);
	LAi_LocationDisableOfficersGen("Shore8", false);
	LAi_LocationDisableOfficersGen("Beliz_jungle_03", false);
	DeleteAttribute(pchar, "GenQuest.CabinLock");
	DeleteAttribute(pchar, "questTemp.CameraDialogMode");
	
	AddQuestRecord("WildRose", "35");
	ChangeContrabandRelation(PChar, -30);
	
	// Корабль Корвет "Еретик"
	sld = GetCharacter(NPC_GenerateCharacter("WildRose_ShipRupert_cap", "officer_15", "man", "man", 30, PIRATE, -1, false, "pirate"));
	FantomMakeCoolFighter(sld, 30, 70, 70, "blade_14", "pistol3", "grapeshot", 100);
	FantomMakeCoolSailor(sld, SHIP_CORVETTE, StringFromKey("WildRose_12"), CANNON_TYPE_CANNON_LBS16, 70, 70, 70);
	sld.AlwaysEnemy = true;
	sld.DontRansackCaptain = true;
	sld.DontHitInStorm = true;
	sld.AlwaysSandbankManeuver = true;
	sld.SinkTenPercent = false;
	Ship_SetTaskAttack(SECONDARY_TASK, sti(sld.index), sti(pchar.index));
	sld.Ship.Mode = "pirate";
	SetCharacterGoods(sld, GOOD_SANDAL, 200 + rand(20));
	SetCharacterGoods(sld, GOOD_OIL, 300 + rand(20));
	SetCharacterGoods(sld, GOOD_SHIPSILK, 300 + rand(20));
	SetCharacterGoods(sld, GOOD_ROPES, 200 + rand(20));
	
	Group_FindOrCreateGroup("WildRose_ShipRupert_Group");
	Group_SetType("WildRose_ShipRupert_Group", "war");
	Group_AddCharacter("WildRose_ShipRupert_Group", "WildRose_ShipRupert_cap");
	Group_SetGroupCommander("WildRose_ShipRupert_Group", "WildRose_ShipRupert_cap");
	Group_SetTaskNone("WildRose_ShipRupert_Group");
	Group_SetAddress("WildRose_ShipRupert_Group", "Beliz", "quest_ships", "quest_ship_4");
	Group_LockTask("WildRose_ShipRupert_Group");
	
	PChar.quest.WildRose_Etap6_LifeAfterDeath_40.win_condition.l1 = "Group_Death";
	PChar.quest.WildRose_Etap6_LifeAfterDeath_40.win_condition.l1.group = "WildRose_ShipRupert_Group";
	PChar.quest.WildRose_Etap6_LifeAfterDeath_40.function = "WildRose_Etap6_LifeAfterDeath_40";
}

void WildRose_Etap6_LifeAfterDeath_40(string qName)
{
	Island_SetReloadEnableGlobal("Beliz", true);
	bQuestDisableMapEnter = false;
	CloseQuestHeader("WildRose");
	if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_GoodEnd")) Achievment_Set("ach_CL_171");
}

void WildRose_Test()
{
	LAi_SetPlayerType(pchar);
	InterfaceStates.Buttons.Save.enable = true;
	bGameMenuStart = false;
	RemoveAllCharacterItems(pchar, true);
	AddMoneyToCharacter(pchar, 10000000);
	pchar.rank = 35;
	LAi_SetHP(pchar, 400.0, 400.0);
	SetSPECIAL(PChar, 10, 10, 10, 10, 10, 10, 10);
	SetSelfSkill(PChar, 50, 50, 50, 50, 50);
	SetShipSkill(PChar, 50, 75, 50, 50, 100, 50, 50, 50, 75);
	LAi_SetHP(pchar, 400.0, 400.0);
	SetCharacterPerk(pchar, "BasicDefense");
	SetCharacterPerk(pchar, "AdvancedDefense");
	SetCharacterPerk(pchar, "Ciras");
	SetCharacterPerk(pchar, "CriticalHit");
	SetCharacterPerk(pchar, "AgileMan");
	SetCharacterPerk(pchar, "BladeDancer");
	SetCharacterPerk(pchar, "Sliding");
	SetCharacterPerk(pchar, "HardHitter");
	SetCharacterPerk(pchar, "EnergyPlus");
	SetCharacterPerk(pchar, "Medic");
	SetCharacterPerk(pchar, "Gunman");
	SetCharacterPerk(pchar, "GunProfessional");
	SetCharacterPerk(pchar, "Tireless");
	SetCharacterPerk(pchar, "IronWill");
	SetCharacterPerk(pchar, "CrewDamageUp");
	SetCharacterPerk(pchar, "CriticalShoot");
	SetCharacterPerk(pchar, "LongRangeShoot");
	SetCharacterPerk(pchar, "CannonProfessional");
	SetCharacterPerk(pchar, "LongRangeGrappling");
	SetCharacterPerk(pchar, "MusketsShoot");
	SetCharacterPerk(pchar, "GrapplingProfessional");
	SetCharacterPerk(pchar, "ShipDefenseProfessional");
	SetCharacterPerk(pchar, "ShipSpeedUp");
	SetCharacterPerk(pchar, "ShipTurnRateUp");
	SetCharacterPerk(pchar, "BasicBattleState");
	SetCharacterPerk(pchar, "AdvancedBattleState");
	SetCharacterPerk(pchar, "ShipDefenseProfessional");
	SetCharacterPerk(pchar, "SailingProfessional");
	SetCharacterPerk(pchar, "SailsMan");
	SetCharacterPerk(pchar, "WindCatcher");
	SetCharacterPerk(pchar, "SeaDogProfessional");
	SetCharacterPerk(pchar, "Trustworthy");
	GiveItem2Character(PChar, "blade_16");
	GiveItem2Character(PChar, "blade_13");
	EquipCharacterByItem(Pchar, "blade_13");
	GiveItem2Character(PChar, "pistol5");
	EquipCharacterByItem(Pchar, "pistol5");
	GiveItem2Character(PChar, "cirass8");
	EquipCharacterByItem(Pchar, "cirass8");
	GiveItem2Character(PChar, "spyglass4");
	EquipCharacterByItem(Pchar, "spyglass4");
	GiveItem2Character(PChar, "talisman2");
	EquipCharacterByItem(Pchar, "talisman2");
	GiveItem2Character(PChar, "talisman13");
	AddItems(Pchar, "cartridge", 50);
	AddItems(Pchar, "potion4", 20);
	LAi_SetCharacterUseBullet(Pchar, GUN_ITEM_TYPE, "cartridge");
	AddItems(pchar, "gold_dublon", 500);
	// Мой корабль
	pchar.Ship.Type = GenerateShipExt(SHIP_LINESHIP, true, pchar);
	pchar.Ship.name = "Авентура";
	SetSailsColor(pchar, 0); //белый хлопковый парус
	SetBaseShipData(pchar);
	pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS24;
	SetCrewQuantityFull(pchar);
	pchar.Ship.Crew.Morale = 100;
	pchar.Ship.Crew.Exp.Sailors = 100;
	pchar.Ship.Crew.Exp.Cannoners = 100;
	pchar.Ship.Crew.Exp.Soldiers = 100;
	UpgradeShipParameter(pchar, "SpeedRate"); //апгрейдить скорость
	UpgradeShipParameter(pchar, "TurnRate");  //маневренность
	UpgradeShipParameter(pchar, "HP");        //корпус
	ChangeCrewExp(pchar, "Sailors", 100);
	ChangeCrewExp(pchar, "Cannoners", 100);
	ChangeCrewExp(pchar, "Soldiers", 100);
	SetCharacterGoods(pchar, GOOD_BALLS, 2000);
	SetCharacterGoods(pchar, GOOD_GRAPES, 700);
	SetCharacterGoods(pchar, GOOD_KNIPPELS, 600);
	SetCharacterGoods(pchar, GOOD_BOMBS, 2000);
	SetCharacterGoods(pchar, GOOD_FOOD, 2000);
	SetCharacterGoods(pchar, GOOD_POWDER, 5000);
	SetCharacterGoods(pchar, GOOD_WEAPON, 750);
	SetCharacterGoods(pchar, GOOD_MEDICAMENT, 900);
	SetCharacterGoods(pchar, GOOD_RUM, 800);
	
	// Мэри:
	pchar.questTemp.LSC.Mary_officer = "true";
	sld = characterFromId("Mary");
	sld.quest.OfficerPrice = sti(pchar.rank) * 500;
	sld.OfficerWantToGo.DontGo = true;
	sld.CompanionDisable = true;
	sld.loyality = MAX_LOYALITY;
	AddPassenger(pchar, sld, false);
	SetCharacterRemovable(sld, true);
	sld.Payment = true;
	sld.DontClearDead = true;
	sld.SpecialRole = "fgirl";
	sld.dialog.currentnode = "Mary_officer";
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	SaveCurrentNpcQuestDateParam(sld, "HiredDate");
	sld.rank = 35;
	LAi_SetHP(sld, 500.0, 500.0);
	SetSelfSkill(sld, 100, 90, 100, 100, 90);
	SetShipSkill(sld, 100, 40, 40, 40, 40, 40, 40, 40, 40);
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "ByWorker");

	SetCharacterPerk(sld, "Grus");
	GiveItem2Character(sld, "blade_31");
	sld.equip.blade = "blade_31";
	GiveItem2Character(sld, "pistol4");
	sld.equip.gun = "pistol4";
	GiveItem2Character(sld, "cirass4");
	EquipCharacterbyItem(sld, "cirass4");
	AddItems(sld, "cartridge", 50);
	AddItems(sld, "potion2", 10);
	AddItems(sld, "potion4", 5);
	sld.OfficerImmortal = true;
	sld.Health.HP       = 60.0;
	sld.Health.maxHP    = 60.0;

	//выключить сторонние квесты
	PChar.quest.Red_Chieftain.over = "yes";
	PChar.quest.False_Trace.over = "yes";
	PChar.quest.FalseTrace_Prepare.over = "yes";
	//Нужные атрибуты для квеста
	pchar.questTemp.Terrapin = "done";
	pchar.questTemp.Saga = "end";
	pchar.questTemp.Sharlie = "escape";
	pchar.questTemp.GoldenGirl_Ready = true;
	LocatorReloadEnterDisable("CeresSmithy", "reload3", false);
	LocatorReloadEnterDisable("CeresSmithy", "reload4", false);
	LocatorReloadEnterDisable("LostShipsCity_town", "reload62", false);
	LocatorReloadEnterDisable("LostShipsCity_town", "reload63", false);
	LocatorReloadEnterDisable("LostShipsCity_town", "reload1", false);
	LocatorReloadEnterDisable("LostShipsCity_town", "reload3", false);
	pchar.questTemp.LSC.rvd_friend = "true"; //флаг на проход по кораблям ривадос
	pchar.questTemp.LSC.nrv_friend = "true"; //флаг на проход по кораблям нарвалов
	LSC_CreateStateCitizens();
	sld = CharacterFromID("Chimiset");
	ChangeCharacterAddressGroup(sld, "ProtectorFisher", "sit", "sit1");
	LAi_SetHuberType(sld);
	sld = characterFromId("Benua");
	sld.quest.help = "true";
	sld.quest.meet = true;
	pchar.questTemp.Saga.BaronReturn = "return_LSC";
	i = FindIsland("LostShipsCity");
	Islands[i].visible = true;
	Islands[i].reload_enable = true;
}

bool WildRose_QuestComplete(string sQuestName, string qname)
{
	ref sld;
	int i;
	
	bool condition = true;
	
	if (sQuestName == "WildRose_Etap1_EscapeSlaves_4")
	{
		DoQuestFunctionDelay("WildRose_Etap1_EscapeSlaves_5", 2.0);
	}
	
	else if (sQuestName == "WildRose_Etap1_City_6")
	{
		DoQuestFunctionDelay("WildRose_Etap1_City_7", 1.5);
	}
	
	else if (sQuestName == "WildRose_Etap1_City_8_1")
	{
		sld = CharacterFromID("WildRose_Lewis");
		LAi_SetActorType(sld);
	}
	
	else if (sQuestName == "WildRose_Etap1_City_8_2")
	{
		WildRose_Etap1_City_9();
	}
	
	else if (sQuestName == "WildRose_Etap1_City_11")
	{
		DoQuestFunctionDelay("WildRose_Etap1_City_12", 1.5);
	}
	
	else if (sQuestName == "WildRose_Etap2_IslandOfJustice_10_3")
	{
		WildRose_Etap2_IslandOfJustice_10_4();
	}
	
	else if (sQuestName == "WildRose_Etap2_IslandOfJustice_13_1")
	{
		WildRose_Etap2_IslandOfJustice_13_2();
	}
	
	else if (sQuestName == "WildRose_Etap2_IslandOfJustice_15_1")
	{
		WildRose_Etap2_IslandOfJustice_15_2();
	}
	
	// else if (sQuestName == "WildRose_Etap2_IslandOfJustice_16_1")
	// {
		// WildRose_Etap2_IslandOfJustice_16_2();
	// }
	
	else if (sQuestName == "WildRose_Etap2_Antonio_Finding")
	{
		WildRose_Etap2_IslandOfJustice_19_2();
	}
	
	else if (sQuestName == "WildRose_Etap2_Antonio_Finding_2")
	{
		WildRose_Etap2_IslandOfJustice_19_3();
	}
	
	else if (sQuestName == "WildRose_Etap4_PathToLight_12_1")
	{
		WildRose_Etap4_PathToLight_13();
	}
	
	else if (sQuestName == "WildRose_Etap4_PathToLight_17_1")
	{
		WildRose_Etap4_PathToLight_18();
	}
	
	else if (sQuestName == "WildRose_Etap4_PathToLight_18_funeral_2_1")
	{
		WildRose_Etap4_PathToLight_18_funeral_3();
	}
	
	else if (sQuestName == "WildRose_Etap4_PathToLight_18_funeral_6_2")
	{
		DoQuestFunctionDelay("WildRose_Etap4_PathToLight_18_funeral_6_1", 5.0);
	}
	
	else if (sQuestName == "WildRose_Etap4_PathToLight_18_funeral_13_1")
	{
		WildRose_Etap4_PathToLight_19();
	}
	
	else if (sQuestName == "WildRose_Etap6_LifeAfterDeath_5_1")
	{
		WildRose_Etap6_LifeAfterDeath_6();
	}
	
	else if (sQuestName == "WildRose_Etap6_LifeAfterDeath_31_1")
	{
		WildRose_Etap6_LifeAfterDeath_32();
	}
	
	else
	{
		condition = false;
	}
	
	return condition;
}