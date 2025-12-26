void LEDR_Start()
{
	SetQuestHeader("LEDR");
	AddQuestRecord("LEDR", "1");
	pchar.questTemp.LEDR_Start = true;
	
	sld = GetCharacter(NPC_GenerateCharacter("LEDR_Gonsalo", "barmen_9", "man", "man", 10, PIRATE, -1, false, "citizen"));
	sld.name = StringFromKey("Neutral_35");
	sld.lastname = StringFromKey("Neutral_36");
	ChangeCharacterAddressGroup(sld, "Pirates_town", "goto", "goto19");
	sld.dialog.filename = "Quest\MiniEvents\LaEspadaDelRey_dialog.c";
	sld.dialog.currentnode = "LEDR_Gonsalo_1";
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
	AddLandQuestMark(sld, "questmarkmain");
	LAi_SetImmortal(sld, true);
	GiveItem2Character(sld, "blade_05");
	EquipCharacterByItem(sld, "blade_05");
}

void LEDR_End()
{
	if (CharacterIsAlive("LEDR_Gonsalo"))
	{
		sld = CharacterFromID("LEDR_Gonsalo");
		sld.lifeday = 0;
		LAi_CharacterDisableDialog(sld);
		LAi_SetCitizenType(sld);
		LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
	}
	CloseQuestHeader("LEDR");
}

void LEDR_1()
{
	if (CharacterIsAlive("LEDR_Gonsalo"))
	{
		sld = CharacterFromID("LEDR_Gonsalo");
		// AddPassenger(pchar, sld, false);	// нет иконки у персонажа
		// SetCharacterRemovable(sld, false);
		// LAi_CharacterDisableDialog(sld);
		sld.location = "None";
		LAi_SetActorType(sld);
		LAi_ActorGoToLocation(sld, "reload", "reload1", "", "", "", "", -1);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	SetFunctionLocationCondition("LEDR_2", "Shore_Ship1", false);
}

void LEDR_2(string qName)
{
	sld = CharacterFromID("LEDR_Gonsalo");
	sld.dialog.filename = "Quest\MiniEvents\LaEspadaDelRey_dialog.c";
	sld.dialog.currentnode = "LEDR_Gonsalo_11";
	ChangeCharacterAddressGroup(sld, "Shore_ship1", "goto", "goto4");
	LAi_CharacterEnableDialog(sld);
	LAi_SetStayType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	AddLandQuestMark(sld, "questmarkmain");
}

void LEDR_3()
{
	chrDisableReloadToLocation = true;
	sld = CharacterFromID("LEDR_Gonsalo");
	LAi_CharacterDisableDialog(sld);
	LAi_SetWarriorType(sld);
	// LAi_SetActorTypeNoGroup(sld);
	DoQuestFunctionDelay("LEDR_4", 10.0);
}

void LEDR_4(string qName)
{
	sld = CharacterFromID("LEDR_Gonsalo");
	sld.dialog.filename = "Quest\MiniEvents\LaEspadaDelRey_dialog.c";
	sld.dialog.currentnode = "LEDR_Gonsalo_21";
	LAi_CharacterEnableDialog(sld);
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void LEDR_5()
{
	sld = CharacterFromID("LEDR_Gonsalo");
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload2", "none", "", "", "LEDR_5_1", -1);
}

void LEDR_5_2()
{
	chrDisableReloadToLocation = false;
	LocatorReloadEnterDisable("Shore_ship1", "reload1_back", true);
	LocatorReloadEnterDisable("Shore_ship1", "boat", true);
	LocatorReloadEnterDisable("Shore_ship1", "reload2", false);
	SetFunctionLocationCondition("LEDR_6_kino_1", "Bermudes_DelRey", false);
}

void LEDR_6_kino_1(string qName)
{
	StartQuestMovie(true, false, true);
	LAi_FadeToBlackStartInstantly();
	chrDisableReloadToLocation = true;
	LAi_SetActorType(pchar);
	sld = CharacterFromID("LEDR_Gonsalo");
	ChangeCharacterAddressGroup(sld, "Bermudes_DelRey", "reload", "reload1");
	LAi_SetActorTypeNoGroup(sld);
	DoQuestFunctionDelay("LEDR_6_kino_2", 1.0);
	SetMusic("music_Approach_of_the_Storm");
	pchar.questTemp.lockedMusic = true;
	
	sld = ItemsFromID("LEDR_key");
	sld.shown = true;
	sld.startLocation = "Bermudes_DelRey";
	sld.startLocator = "item1";
	Item_OnLoadLocation("Bermudes_DelRey");
}

void LEDR_6_kino_2(string qName)
{
	locCameraFromToPos(10.97, 4.22, 160.52, true, 9.03, 1.40, 163.83);
	LAi_FadeToBlackEnd();
	EndBattleLandInterface();
	sld = CharacterFromID("LEDR_Gonsalo");
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorGoToLocator(sld, "quest", "quest1", "LEDR_6_kino_2_1", -1);
	LAi_ActorGoToLocator(pchar, "quest", "quest2", "LEDR_6_kino_2_2", -1);
}

void LEDR_6_kino_2_3()
{
	sld = CharacterFromID("LEDR_Gonsalo");
	CharacterTurnAy(sld, 0.45);
	DoQuestFunctionDelay("LEDR_6_kino_3", 0.4);
}

void LEDR_6_kino_2_4()
{
	CharacterTurnToLoc(pchar, "goto", "goto4");
}

void LEDR_6_kino_3(string qName)
{
	locCameraFromToPos(10.72, 3.99, 162.71, true, 11.47, 1.06, 162.11);
	DoQuestFunctionDelay("LEDR_6_kino_4", 2.0);
}

void LEDR_6_kino_4(string qName)
{
	locCameraFromToPos(15.86, 2.14, 165.17, true, 15.07, 0.38, 164.89);
	DoQuestFunctionDelay("LEDR_6_kino_5", 2.0);
}

void LEDR_6_kino_5(string qName)
{
	locCameraFromToPos(9.62, 3.04, 164.85, true, 9.78, 0.52, 164.32);
	DoQuestFunctionDelay("LEDR_6_kino_6", 2.0);
}

void LEDR_6_kino_6(string qName)
{
	locCameraFromToPos(9.35, 2.12, 165.83, true, 10.14, 0.23, 166.43);
	DoQuestFunctionDelay("LEDR_6_kino_7", 2.0);
}

void LEDR_6_kino_7(string qName)
{
	locCameraFromToPos(10.65, 3.63, 164.09, true, 10.39, 1.00, 165.99);
	sld = CharacterFromID("LEDR_Gonsalo");
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorAnimation(sld, "cross", "1", 5.0);
	
	DoQuestFunctionDelay("LEDR_6_kino_8", 3.0);
}

void LEDR_6_kino_8(string qName)
{
	locCameraFromToPos(15.30, 3.35, 163.38, true, 18.30, 1.80, 163.29);
	// DoQuestFunctionDelay("LEDR_6_kino_9", 0.2);
	DoQuestFunctionDelay("LEDR_6_kino_10", 0.5);
}

void LEDR_6_kino_9(string qName)
{
	CreateLocationParticles("large_smoke", "goto", "goto2", 0.5, 0, 0, "");
	DoQuestFunctionDelay("LEDR_6_kino_10", 5.0);
}

void LEDR_6_kino_10(string qName)
{
	pchar.questTemp.Quest_BitvaSkeletMusic = true;
	PlaySound("Types\skel.wav");
	CreateLocationParticles("fire_incas_Simple", "goto", "goto2", 0.5, 0, 0, "");
	for (i=1; i<=4; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("LEDR_Skel_"+i, "Chavinavi_1", "man", "skeleton", 10, PIRATE, -1, true, "pirate"));
		sld.monster = true;
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto2");
	}
	DoQuestFunctionDelay("LEDR_6_kino_11", 2.5);
}

void LEDR_6_kino_11(string qName)
{
	DeleteAttribute(pchar, "questTemp.lockedMusic");
	EndQuestMovie();
	locCameraFollowEx(true);
	LAi_SetPlayerType(pchar);
	LAi_SetFightMode(pchar, true);
	
	sld = CharacterFromID("LEDR_Gonsalo");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	LAi_SetImmortal(sld, false);
	sld.QuestImmortal = true;
	
	for (i=1; i<=4; i++)
	{
		sld = CharacterFromID("LEDR_Skel_"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
	LAi_group_SetCheckFunction("EnemyFight", "LEDR_7");
	
	AutoSave();
}

void LEDR_7(string qName)
{
	DoQuestCheckDelay("hide_weapon", 1.2);
	LAi_LocationFightDisable(loadedLocation, true);
	
	sld = CharacterFromID("LEDR_Gonsalo");
	sld.dialog.filename = "Quest\MiniEvents\LaEspadaDelRey_dialog.c";
	sld.dialog.currentnode = "LEDR_Gonsalo_24";
	LAi_SetGroundSitType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	LAi_SetImmortal(sld, true);
	DeleteAttribute(sld, "QuestImmortal");
	AddLandQuestMark(sld, "questmarkmain");
	
	PChar.quest.LEDR_9.win_condition.l1 = "item";
	PChar.quest.LEDR_9.win_condition.l1.item = "LEDR_Book";
	PChar.quest.LEDR_9.function = "LEDR_9";
}

void LEDR_8()
{
	sld = CharacterFromID("LEDR_Gonsalo");
	LAi_SetWarriorType(sld);
	LAi_CharacterDisableDialog(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
}

void LEDR_9(string qName)
{
	AddQuestRecord("LEDR", "3");
	if (LanguageGetLanguage() == "russian") AddQuestUserData("LEDR", "sSex", GetSexPhrase("","ла"));
	AddQuestRecordInfo("LEDR_Book_1", "1");
	
	sld = CharacterFromID("LEDR_Gonsalo");
	sld.dialog.filename = "Quest\MiniEvents\LaEspadaDelRey_dialog.c";
	sld.dialog.currentnode = "LEDR_Gonsalo_27";
	LAi_CharacterEnableDialog(sld);
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
}

void LEDR_10()
{
	chrDisableReloadToLocation = false;
	sld = CharacterFromID("LEDR_Gonsalo");
	LAi_SetActorType(sld);
	LAi_ActorFollow(sld, pchar, "", -1);
	
	//
	sld = ItemsFromID("fire");
	sld.shown = true;
	sld.startLocation = "Shore_ship1";
	sld.startLocator = "fire";	
	sld = &locations[FindLocation("Shore_ship1")];
	sld.fire = true;
	
	LAi_LocationDisableOfficersGen("Shore_Ship1", true);
	locations[FindLocation("Shore_Ship1")].DisableEncounters = true;
	locations[FindLocation("Pirates_town")].DisableEncounters = true;
	SetFunctionLocationCondition("LEDR_11_kino_1", "Shore_Ship1", false);
}

void LEDR_11_kino_1(string qName)
{
	StartQuestMovie(true, false, true);
	LAi_FadeToBlackStartInstantly();
	chrDisableReloadToLocation = true;
	sld = CharacterFromID("LEDR_Gonsalo");
	ChangeCharacterAddressGroup(sld, "Shore_Ship1", "reload", "reload1");
	LAi_SetActorTypeNoGroup(sld);
	TeleportCharacterToPosAy(pchar, -6.83, 1.66, 2.71, -1.70);
	TeleportCharacterToPosAy(sld, -8.78, 1.66, 3.33, 2.40);
	
	DoQuestFunctionDelay("LEDR_11_kino_2", 1.0);
}

void LEDR_11_kino_2(string qName)
{
	locCameraFromToPos(-7.95, 2.97, -1.00, true, -7.89, 0.95, 3.20);
	LAi_FadeToBlackEnd();
	EndBattleLandInterface();
	LAi_SetStayType(pchar);
	
	DoQuestFunctionDelay("LEDR_11_kino_3", 1.0);
}

void LEDR_11_kino_3(string qName)
{
	sld = CharacterFromID("LEDR_Gonsalo");
	SetAnimationInDialog(pchar, "", true);
	SetAnimationInDialog(sld, "", true);
	sld.dialog.filename = "Quest\MiniEvents\LaEspadaDelRey_dialog.c";
	sld.dialog.currentnode = "LEDR_Gonsalo_31";
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, Pchar, "", -1);
}

void LEDR_12()
{
	EndQuestMovie();
	locCameraFollowEx(true);
	LAi_SetPlayerType(pchar);
	SetAnimationInDialog(pchar, "", false);
	
	sld = CharacterFromID("LEDR_Gonsalo");
	SetAnimationInDialog(sld, "", false);
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "officers", "sea_3", "none", "", "", "OpenTheDoors", 5);
	
	sld = &locations[FindLocation("Shore_ship1")];
	DeleteAttribute(sld, "fire");
	sld = ItemsFromID("fire");
	sld.fire = false;
	sld.shown = false;
	
	DeleteAttribute(pchar, "questTemp.Quest_BitvaSkeletMusic");
	LAi_LocationDisableOfficersGen("Shore_Ship1", false);
	locations[FindLocation("Shore_Ship1")].DisableEncounters = false;
	locations[FindLocation("Pirates_town")].DisableEncounters = false;
	LocatorReloadEnterDisable("Shore_ship1", "reload1_back", false);
	LocatorReloadEnterDisable("Shore_ship1", "boat", false);
	LocatorReloadEnterDisable("Shore_Ship1", "reload2", true); 
	
	SetFunctionLocationCondition("LEDR_13", "Pirates_town", false);
}

void LEDR_13(string qName)
{
	chrDisableReloadToLocation = true;
	sld = CharacterFromID("LEDR_Gonsalo");
	ChangeCharacterAddressGroup(sld, "Pirates_town", "quest", "quest1");
	sld.dialog.filename = "Quest\MiniEvents\LaEspadaDelRey_dialog.c";
	sld.dialog.currentnode = "LEDR_Gonsalo_37";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void LEDR_14()
{
	chrDisableReloadToLocation = false;
	sld = CharacterFromID("LEDR_Gonsalo");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload4_back", "none", "", "", "", -1);
	sld.lifeday = 0;
	LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
	
	CloseQuestHeader("LEDR");
	AddQuestRecord("LEDR", "4");
	pchar.questTemp.LEDR_QuestCompleted = true;
	pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // завершено событие
	Achievment_Set("ach_CL_174"); // ачивка за завершённое событие
	Achievment_Set("ach_CL_179"); // ачивка за LaEspadaDelRey
	if (GetAttributeInt(pchar, "questTemp.MiniEvents") > GetStat("stat_CL_175")) Achievment_SetStat(175, 1); // ачивка за 10 завершённых событий
}

bool LaEspadaDelRey_QuestComplete(string sQuestName, string qname)
{
	ref sld;
	aref arOldMapPos, arAll, arPass;
	int     iTemp, i, n, iRank, Rank;
    float locx, locy, locz;
	string  attrName, sTemp; // любые строки для вычислений
	bool   bOk;
	
	bool condition = true;
	
	if (sQuestName == "LEDR_6_kino_2_1") {
		LEDR_6_kino_2_3();
	}
	
	else if (sQuestName == "LEDR_6_kino_2_2") {
		LEDR_6_kino_2_4();
	}
	
	else if (sQuestName == "LEDR_5_1") {
		LEDR_5_2();
	}
	
	else if (sQuestName == "LEDR_GonsaloStay") {
		sld = CharacterFromID("LEDR_Gonsalo");
		LAi_SetActorType(sld);
	}
	
	else
	{
		condition = false;
	}
	
	return condition;
}



