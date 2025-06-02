
//=================================================================
//======================кейсы из quests_reaction===================
//=================================================================
bool BlackMark_QuestComplete(string sQuestName, string qname)
{
	ref sld;
	int i, n;
	
	string sTemp;
	
	bool condition = true;
	
	// Квест "Чёрная Метка" ==>
	if (sQuestName == "BM_StartQuest") {
		pchar.questTemp.BM_StartQuest = true;
		PChar.quest.BM_BarbadosKontrabandisty.win_condition.l1 = "location";
		PChar.quest.BM_BarbadosKontrabandisty.win_condition.l1.location = "Mayak2";
		PChar.quest.BM_BarbadosKontrabandisty.win_condition = "BM_BarbadosKontrabandisty";
		AddMapQuestMarkShore("Mayak2", true);
		AddGeometryToLocation("Mayak2", "smg");
		sld = &Locations[FindLocation("Mayak2")];
		sld.locators_radius.goto.goto31 = 50.0;
		locations[FindLocation("Mayak2")].DisableEncounters = true;
		LAi_LocationDisableOfficersGen("Mayak2", true);
		pchar.questTemp.BM_BlockSmuggler = true;
	}
	
	else if (sQuestName == "BM_BarbadosKontrabandisty") {
		/*for (i = 0; i < MAX_CHARACTERS; i++)	//Убираем всех лишних из локации
		{
			sld = GetCharacter(i);
			if (sld.id != "Blaze" && sld.location == "Mayak2") ChangeCharacterAddressGroup(sld, "none", "", "");
		}*/
		for (i=1; i<=4; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("BM_Contra_"+i, "citiz_" + (rand(9) + 21), "man", "man", sti(pchar.rank), PIRATE, -1, true, "pirate"));
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(sld, pchar.location, "smugglers",  "smuggler0"+i);
			if (i==1)
			{
				sld.name = StringFromKey("BlackMark_1");
				sld.lastname = StringFromKey("BlackMark_2");
			}
			if (i==4)
			{
				sld.dialog.filename = "Quest\BlackMark.c";
				sld.dialog.currentnode = "BM_Contra_1";
				sld.SaveItemsForDead = true;
				ChangeCharacterAddressGroup(sld, pchar.location, "smugglers",  "smugglerload");
				LAi_ActorDialog(sld, pchar, "", -1, 0);
				AddLandQuestMark(sld, "questmarkmain");
				RemoveAllCharacterItems(sld, true);
				AddMoneyToCharacter(sld, 15000);
				GiveItem2Character(sld, "slave_02");
				EquipCharacterByItem(sld, "slave_02");
				LAi_SetStayType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
		}
		//SetTimerCondition("BM_BarbadosKontrabandisty_TimeOver", 0, 0, 3, false);
	}
	
	/*else if (sQuestName == "BM_BarbadosKontrabandisty_TimeOver") {
		RemoveGeometryFromLocation("Mayak2", "smg");
		sld = &Locations[FindLocation("Mayak2")];
		sld.locators_radius.goto.goto31 = 0.5;
		locations[FindLocation("Mayak2")].DisableEncounters = false;
		LAi_LocationDisableOfficersGen("Mayak2", false);
	}*/
	
	else if (sQuestName == "BM_BarbadosPatrolPribegaet") {
		StartQuestMovie(true, false, true);
		LAi_SetStayType(pchar);
		LAi_FadeLong("BM_BarbadosPatrolPribegaet2", "");
	}
	
	else if (sQuestName == "BM_BarbadosPatrolPribegaet2") {
		locCameraFromToPos(-57.92, 4.97, -68.06, true, -42.71, 4.38, -69.22);
		//LAi_SetStayType(pchar);
		
		sld = GetCharacter(NPC_GenerateCharacter("BM_PatrolZhitel", "citiz_19", "man", "man", sti(pchar.rank), ENGLAND, -1, false, "soldier"));
		sld.name = StringFromKey("BlackMark_3");
		sld.lastname = StringFromKey("BlackMark_4");
		ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto5");
		LAi_SetActorType(sld);
		LAi_ActorRunToLocator(sld, "goto", "goto2", "", -1);
		AddItems(sld, "purse2", 2);
		sld.SaveItemsForDead = true;
		sld.DontClearDead = true;
		
		sld = GetCharacter(NPC_GenerateCharacter("BM_PatrolOff", "off_eng_2", "man", "man", sti(pchar.rank), ENGLAND, -1, true, "soldier"));
		ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto5");
		LAi_SetActorType(sld);
		LAi_ActorRunToLocator(sld, "goto", "goto2", "", -1);
		
		for (i=1; i<=4; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("BM_Patrol_"+i, "sold_eng_"+(rand(7)+1), "man", "man", sti(pchar.rank), ENGLAND, -1, true, "soldier"));
			ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto5");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, characterFromID("BM_PatrolOff"), "", -1);
		}
		DoQuestCheckDelay("BM_BarbadosPatrolPribegaet3", 5.0);
	}
	
	else if (sQuestName == "BM_BarbadosPatrolPribegaet3") {
		LAi_FadeLong("BM_BarbadosPatrolPribegaet4", "");
	}
	
	else if (sQuestName == "BM_BarbadosPatrolPribegaet4") {
		sld = CharacterFromID("BM_PatrolZhitel");
		TeleportCharacterToPosAy(sld, -80.71, 4.41, -66.67, -1.05);
		LAi_SetActorType(sld);
		
		sld = CharacterFromID("BM_PatrolOff");
		TeleportCharacterToPosAy(sld, -79.51, 4.41, -65.64, -1.15);
		LAi_SetActorType(sld);
		
		for (i=1; i<=4; i++)
		{
			sld = CharacterFromID("BM_Patrol_"+i);
			TeleportCharacterToPosAy(sld, -74.81, 4.41, -66.12, -1.15);
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, characterFromID("BM_PatrolOff"), "", -1);
		}
		for (i=1; i<=4; i++)
		{
			sld = CharacterFromID("BM_Contra_"+i);
			LAi_SetActorType(sld);
			LAi_ActorTurnToLocator(sld, "goto", "goto5");
		}
		CharacterTurnToLoc(pchar, "goto", "goto5");
	
		locCameraFromToPos(-90.73, 7.44, -60.18, true, -82.36, 3.21, -65.69);
		DoQuestCheckDelay("BM_BarbadosPatrolPribegaet5", 2.5);
	}
	
	else if (sQuestName == "BM_BarbadosPatrolPribegaet5") {
		pchar.GenQuest.BlockDialogCamera = true;
		locCameraFromToPos(-83.01, 6.31, -65.33, true, -73.80, 3.36, -67.73);
		sld = CharacterFromID("BM_PatrolOff");
		sld.dialog.filename = "Quest\BlackMark.c";
		sld.dialog.currentnode = "BM_Contra_3";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
	}
	
	else if (sQuestName == "BM_BarbadosMayakVystrel") {
		PlaySound("People Fight\rifle_fire1.wav");
		sld = CharacterFromID("BM_PatrolZhitel");
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "death_8", "1", -1);
		CharacterTurnByChr(sld, characterFromID("BM_PatrolOff"));
		LaunchBlood(sld, 1.0, true, "fight");
		LaunchBlood(sld, 1.0, true, "fight");
		DoQuestCheckDelay("BM_BarbadosMayakVystrel2", 1.2);
	}
	
	else if (sQuestName == "BM_BarbadosMayakVystrel2") {
		LAi_FadeToBlackStart();
		DoQuestCheckDelay("BM_BarbadosMayakVystrel3", 1.0);
		//LAi_Fade("BM_BarbadosMayakVystrel3", "");
	}
	
	else if (sQuestName == "BM_BarbadosMayakVystrel3") {
		locCameraFromToPos(-77.72, 6.40, -69.95, true, -81.00, 3.29, -64.05);
		sld = CharacterFromID("BM_PatrolZhitel");
		TeleportCharacterToPosAy(sld, -80.71, 4.41, -66.67, -2.05);
		//LAi_SetActorType(sld);
		//LAi_ActorSetLayMode(sld);
		//LAi_SetImmortal(sld, true);
		LAi_KillCharacter(sld);
		
		DoQuestCheckDelay("BM_BarbadosMayakVystrel4", 2.5);
	}
	
	else if (sQuestName == "BM_BarbadosMayakVystrel4") {
		LAi_FadeToBlackEnd();
		sld = CharacterFromID("BM_PatrolOff");
		sld.dialog.filename = "Quest\BlackMark.c";
		sld.dialog.currentnode = "BM_Contra_7";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
	}
	
	else if (sQuestName == "BM_BarbadosMayakBoinya") {
		EndQuestMovie();
		InterfaceStates.Buttons.Save.enable = true;
		DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
		LAi_SetPlayerType(pchar);
		locCameraTarget(PChar);
		locCameraFollow();
		LAi_SetFightMode(pchar, true);
		sld = CharacterFromID("BM_PatrolOff");
		sld.lifeday = 0;
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		for (i=1; i<=4; i++)
		{
			sld = CharacterFromID("BM_Patrol_"+i);
			sld.lifeday = 0;
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		for (i=1; i<=4; i++)
		{
			sld = CharacterFromID("BM_Contra_"+i);
			sld.lifeday = 0;
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "TmpEnemy");
		}
		
		LAi_group_SetRelation("EnemyFight", "TmpEnemy", LAI_GROUP_ENEMY);
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_SetRelation("TmpEnemy", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", "TmpEnemy", false);
		
		PChar.quest.BM_BarbadosMayakSniper.win_condition.l1 = "locator";
		PChar.quest.BM_BarbadosMayakSniper.win_condition.l1.location = "Mayak2";
		PChar.quest.BM_BarbadosMayakSniper.win_condition.l1.locator_group = "goto";
		PChar.quest.BM_BarbadosMayakSniper.win_condition.l1.locator = "goto31";
		PChar.quest.BM_BarbadosMayakSniper.win_condition = "BM_BarbadosMayakSniper";
		
		PChar.quest.BM_UbezhalSMayaka.win_condition.l1 = "ExitFromLocation";
		PChar.quest.BM_UbezhalSMayaka.win_condition.l1.location = PChar.location;
		PChar.quest.BM_UbezhalSMayaka.win_condition = "BM_UbezhalSMayaka";
		
		RemoveGeometryFromLocation("Mayak2", "smg");
		DeleteAttribute(pchar, "questTemp.BM_BlockSmuggler");
		//DeleteQuestCondition("BM_BarbadosKontrabandisty_TimeOver");
	}
	
	else if (sQuestName == "BM_BarbadosMayakSniper") {
		PlaySound("People Fight\rifle_fire1.wav");
		LAi_SetActorType(pchar);
		LAi_ActorAnimation(pchar, "hit_fire", "1", 1.8);
		LaunchBlood(pchar, 1.0, true, "fight");
		LaunchBlood(pchar, 1.0, true, "fight");
		LAi_SetCurHP(pchar, GetCharacterBaseHPValue(pchar));
		DoQuestCheckDelay("BM_BarbadosMayakSniper2", 2.0);
	}
	
	else if (sQuestName == "BM_BarbadosMayakSniper2") {
		LAi_SetPlayerType(pchar);
		LAi_SetFightMode(pchar, true);
		//DoQuestCheckDelay("BM_BarbadosMayakSniper_Smert1", 30.0);
		DoQuestCheckDelay("BM_BarbadosMayakSniper_Obnovka", 3.0);
		
		//Айронс - новый офицер
		sld = GetCharacter(NPC_GenerateCharacter("Irons", "Irons", "man", "Irons", 12, ENGLAND, -1, false, "quest"));
		sld.name = StringFromKey("BlackMark_5");
		sld.lastname = StringFromKey("BlackMark_6");
		sld.rank = 12;
		sld.CanTakeMushket = true;
		sld.PriorityMode = 2;
		sld.MusketerDistance = 0;
		SetSPECIAL(sld, 6, 9, 6, 3, 7, 6, 9);
		SetSelfSkill(sld, 15, 15, 50, 60, 20);
		SetShipSkill(sld, 5, 1, 4, 6, 1, 1, 7, 1, 10);
		SetCharacterPerk(sld, "Energaiser");
		SetCharacterPerk(sld, "Tireless");
		SetCharacterPerk(sld, "BasicDefense");
		SetCharacterPerk(sld, "CriticalHit");
		SetCharacterPerk(sld, "Gunman");
		SetCharacterPerk(sld, "Jager"); //Егерь
		SetCharacterPerk(sld, "Sniper"); //Снайпер
		GiveItem2Character(sld, "cirass10");
		EquipCharacterByItem(sld, "cirass10");
		GiveItem2Character(sld, "blade_42");
		EquipCharacterByItem(sld, "blade_42");
		GiveItem2Character(sld, "indian_2");
		GiveItem2Character(sld, "mushket1");
		EquipCharacterByItem(sld, "mushket1");
		AddItems(sld, "potionrum", 5);
		AddItems(sld, "GunPowder", 15);
		AddItems(sld, "bullet", 15);
		LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "bullet");
		sld.SaveItemsForDead = true;
		sld.DontClearDead = true;
		
		sld = GetCharacter(CreateCharacterClone(CharacterFromID("Irons"), 0));	//Создание клона важного персонажа
		sld.id = "IronsClone";
		ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
		TeleportCharacterToPosAy(sld, -0.74, 23.40, -5.96, 0.00);
		sld.CantLoot = true;
		PChar.quest.BM_BarbadosMayakSniper3.win_condition.l1 = "NPC_Death";
		PChar.quest.BM_BarbadosMayakSniper3.win_condition.l1.character = "IronsClone";
		PChar.quest.BM_BarbadosMayakSniper3.win_condition = "BM_BarbadosMayakSniper3";
		LAi_SetWarriorType(sld);
		sld.MusketerDistance = 0;
		LAi_group_MoveCharacter(sld, "EnemyFight");
		
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
	}
	
	else if (sQuestName == "BM_BarbadosMayakSniper_Obnovka") {
		sld = CharacterFromID("IronsClone");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		AddItems(sld, "GunPowder", -15);
		AddItems(sld, "bullet", -15);
		AddItems(sld, "cartridge", 1);
		LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "cartridge");
	}
	
	else if (sQuestName == "BM_BarbadosMayakSniper3") {
		Event("QuestDelayExit","sl", "", 0);
		DeleteQuestCondition("BM_UbezhalSMayaka");
		LAi_SetStayType(pchar);
		sld = CharacterFromID("Irons");
		LAi_SetActorType(sld);
		LAi_SetCurHPMax(sld);
		LAi_FadeToBlackStart();
		LAi_group_Delete("EnemyFight");
		LAi_group_Delete("TmpEnemy");
		
		if (CharacterIsAlive("BM_PatrolOff"))
		{
			sld = CharacterFromID("BM_PatrolOff");
			sld.lifeday = 0;
			ChangeCharacterAddressGroup(sld, "none", "", "");
		}
		for (i=1; i<=4; i++)
		{
			if (CharacterIsAlive("BM_Patrol_"+i))
			{
				sld = CharacterFromID("BM_Patrol_"+i);
				sld.lifeday = 0;
				ChangeCharacterAddressGroup(sld, "none", "", "");
			}
		}
		for (i=1; i<=4; i++)
		{
			if (CharacterIsAlive("BM_Contra_"+i))
			{
				sld = CharacterFromID("BM_Contra_"+i);
				sld.lifeday = 0;
				ChangeCharacterAddressGroup(sld, "none", "", "");
			}
		}
		
		DoQuestCheckDelay("BM_BarbadosMayakSniper3_1", 1.5);
	}
	
	else if (sQuestName == "BM_BarbadosMayakSniper3_1") {
		PlaySound("Sea Battles\machta_pad_002.wav");
		PlaySound("Sea Battles\machta_pad_002.wav");
		sld = &Locations[FindLocation("Mayak2")];
		sld.locators_radius.goto.goto31 = 0.5;
		locations[FindLocation("Mayak2")].DisableEncounters = false;
		LAi_LocationDisableOfficersGen("Mayak2", false);
		LAi_SetStayType(pchar);
		TeleportCharacterToPosAy(pchar, 1.05, 16.92, -7.56, -0.50);
		sld = CharacterFromID("Irons");
		ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
		TeleportCharacterToPosAy(sld, -0.44, 16.92, -5.69, 2.50);
		LAi_SetActorType(sld);
		//Убираем клона
		sld = CharacterFromID("IronsClone");
		ChangeCharacterAddressGroup(sld, "none", "", "");
		DoQuestCheckDelay("BM_BarbadosMayakSniper4", 3.0);
	}
	
	else if (sQuestName == "BM_BarbadosMayakSniper4") {
		LAi_FadeToBlackEnd();
		sld = CharacterFromID("Irons");
		sld.dialog.filename = "Quest\BlackMark.c";
		sld.dialog.currentnode = "BM_Irons_1";
		LAi_SetActorType(sld);
		//sld.MusketerDistance = 10;
		LAi_ActorDialog(sld, pchar, "", 1, 0);
	}
	
	/*else if (sQuestName == "BM_BarbadosMayakSniper_Smert1") {
		chrDisableReloadToLocation = true;
		sld = CharacterFromID("Irons");
		LAi_SetImmortal(sld, true);
		LAi_SetActorType(sld);
		LAi_ActorTurnToCharacter(sld, pchar);
		LAi_ActorAnimation(sld, "Shot", "1", 1.5);
		DoQuestCheckDelay("BM_BarbadosMayakSniper_Smert2", 1.5);
		SetMusic("");
	}
	
	else if (sQuestName == "BM_BarbadosMayakSniper_Smert2") {
		LaunchBlood(pchar, 1.0, true, "fight");
		LaunchBlood(pchar, 1.0, true, "fight");
		LAi_KillCharacter(pchar);
	}*/
	
	else if (sQuestName == "BM_UbezhalSMayaka") {
		DeleteQuestCondition("BM_BarbadosMayakSniper");
		DeleteQuestCondition("BM_BarbadosMayakSniper3");
		Event("QuestDelayExit","sl", "", 0);
		sld = characterFromID("Irons");
		sld.lifeday = 0;
		sld = &Locations[FindLocation("Mayak2")];
		sld.locators_radius.goto.goto31 = 0.5;
		locations[FindLocation("Mayak2")].DisableEncounters = false;
		LAi_LocationDisableOfficersGen("Mayak2", false);
	}
	
	else if (sQuestName == "BM_IronsGoodbye") {
		LAi_SetPlayerType(pchar);
		
		sld = characterFromID("Irons");
		LAi_SetWarriorType(sld);
		sld.lifeday = 0;
		LAi_CharacterDisableDialog(sld);
	}
	
	else if (sQuestName == "BM_IronsToCave") {
		chrDisableReloadToLocation = true;
		LAi_SetPlayerType(pchar);
		
		sld = characterFromID("Irons");
		LAi_SetActorType(sld);
		LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "BM_IronsToCave2", -1);
		AddQuestRecord("BlackMark", "2");
		AddQuestUserData("BlackMark", "sSex", GetSexPhrase(StringFromKey("BlackMark_7"),StringFromKey("BlackMark_8")));
	}
	
	else if (sQuestName == "BM_IronsToCave2") {
		chrDisableReloadToLocation = false;
		sld = characterFromID("Irons");
		sld.dialog.currentnode = "BM_Irons_WaitInCave1";
		ChangeCharacterAddressGroup(sld, "Barbados_cave", "goto", "goto3");
		LAi_SetWarriorType(sld);
		LAi_warrior_SetStay(sld, true);
		AddLandQuestMark(sld, "questmarkmain");
		
		SetTimerCondition("BM_IronsTimeOver", 0, 0, 2, false); // два дня на сбор дублонов
	}
	
	else if (sQuestName == "BM_IronsTimeOver") {
		sld = characterFromID("Irons");
		sld.lifeday = 0;
	
		AddQuestRecord("BlackMark", "3");
		AddQuestUserData("BlackMark", "sSex", GetSexPhrase(StringFromKey("BlackMark_9"),StringFromKey("BlackMark_10")));
		CloseQuestHeader("BlackMark");
	}
	
	else if (sQuestName == "BM_FirstJungle_Time") {
		bDisableLandEncounters = true;
		PChar.quest.BM_FirstJungle.win_condition.l1 = "Location_Type";
		PChar.quest.BM_FirstJungle.win_condition.l1.location_type = "jungle";
		PChar.quest.BM_FirstJungle.win_condition = "BM_FirstJungle";
	}
	
	else if (sQuestName == "BM_FirstJungle") {
		if(CheckAttribute(pchar,"questTemp.BlackMark.IronsBlock"))
		{
			SetTimerCondition("BM_FirstJungle_Time", 0, 0, 1, false);
			return true;
		}
		chrDisableReloadToLocation = true;
		
		sld = characterFromID("Irons");
		sld.dialog.filename = "Quest\BlackMark.c";
		sld.dialog.currentnode = "BM_IronsFirstJungle_1";
		if (!CharacterIsHere("Irons")) ChangeCharacterAddressGroup(sld, PChar.location, "reload", LAi_FindNearestFreeLocator2Pchar("reload"));
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	
	else if (sQuestName == "BM_SecondJungle_Time") {
		bDisableLandEncounters = true;
		PChar.quest.BM_SecondJungle.win_condition.l1 = "Location_Type";
		PChar.quest.BM_SecondJungle.win_condition.l1.location_type = "jungle";
		PChar.quest.BM_SecondJungle.win_condition = "BM_SecondJungle";
	}
	
	else if (sQuestName == "BM_SecondJungle") {
		if(CheckAttribute(pchar,"questTemp.BlackMark.IronsBlock"))
		{
			SetTimerCondition("BM_SecondJungle_Time", 0, 0, 1, false);
			return true;
		}
		chrDisableReloadToLocation = true;
		
		sld = characterFromID("Irons");
		sld.dialog.filename = "Quest\BlackMark.c";
		sld.dialog.currentnode = "BM_IronsSecondJungle_1";
		if (!CharacterIsHere("Irons")) ChangeCharacterAddressGroup(sld, PChar.location, "reload", LAi_FindNearestFreeLocator2Pchar("reload"));
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	
	else if (sQuestName == "BM_ThirdJungle_Time") {
		if (!GetDLCenabled(DLC_APPID_3)) return;
		bDisableLandEncounters = true;
		PChar.quest.BM_SecondJungle.win_condition.l1 = "Location_Type";
		PChar.quest.BM_SecondJungle.win_condition.l1.location_type = "jungle";
		PChar.quest.BM_SecondJungle.win_condition = "BM_ThirdJungle";
	}
	
	else if (sQuestName == "BM_ThirdJungle") {
		if(CheckAttribute(pchar,"questTemp.BlackMark.IronsBlock"))
		{
			SetTimerCondition("BM_ThirdJungle_Time", 0, 0, 1, false);
			return true;
		}
		chrDisableReloadToLocation = true;
		
		sld = characterFromID("Irons");
		sld.dialog.filename = "Quest\BlackMark.c";
		sld.dialog.currentnode = "BM_IronsThirdJungle_1";
		if (!CharacterIsHere("Irons")) ChangeCharacterAddressGroup(sld, PChar.location, "reload", LAi_FindNearestFreeLocator2Pchar("reload"));
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	
	else if (sQuestName == "BM_SeaVariant") {	//Морской вариант
		chrDisableReloadToLocation = false;
		bDisableLandEncounters = false;
		Return_IronsOfficer();
		
		// Сюда прописываем продолжение морского варианта
		AddQuestRecord("BlackMark", "7");
		AddQuestUserData("BlackMark", "sSex1", GetSexPhrase(StringFromKey("BlackMark_9"),StringFromKey("BlackMark_10")));
		
		pchar.quest.BM_SeaCheckBarque.win_condition.l1 = "location";
		pchar.quest.BM_SeaCheckBarque.win_condition.l1.location = "Jamaica";
		pchar.quest.BM_SeaCheckBarque.win_condition = "BM_SeaCheckBarque";
	}
	
	else if (sQuestName == "BM_SeaCheckBarque") {
		if (!GetDLCenabled(DLC_APPID_3)) return;
		if (GetCompanionQuantity(pchar) < 2)
		{
			if (sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_BARQUE || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_BARKENTINE)
			{
				if (pchar.nation == SPAIN || pchar.nation == HOLLAND)
				{
					Log_TestInfo("Проверка пройдена!");
					bQuestDisableMapEnter = true; //закрываем карту
					Island_SetReloadEnableGlobal("Jamaica", false);
					sld = GetCharacter(NPC_GenerateCharacter("BM_GabeCallow", "off_eng_1", "man", "man", 10, ENGLAND, -1, false, "quest"));
					sld.name = StringFromKey("BlackMark_11");
					sld.lastname = StringFromKey("BlackMark_12");
					FantomMakeCoolSailor(sld, SHIP_PINK, StringFromKey("BlackMark_13"), CANNON_TYPE_CANNON_LBS6, 50, 50, 50);
					FantomMakeCoolFighter(sld, 50, 50, 50, "blade_14", "pistol14", "cartridge", 50);
					GiveItem2Character(sld, "indian_2");
					sld.DontRansackCaptain = true;
					sld.AnalizeShips = true;
					sld.DontClearDead = true;
					sld.Ship.Mode = "war";
					sld.AlwaysEnemy = true;
					sld.Coastal_Captain = true;
					sld.SaveItemsForDead = true;
					AddItems(sld, "indian_2", 2);
					EquipCharacterByItem(sld, "indian_2");
					AddItems(sld, "purse2", 2);
					AddItems(sld, "bullet", 20);
					AddItems(sld, "GunPowder", 20);
					
					Group_FindOrCreateGroup("GabeCallowGroup");
					Group_AddCharacter("GabeCallowGroup", "BM_GabeCallow");
					Group_SetType("GabeCallowGroup", "war");
					Group_SetGroupCommander("GabeCallowGroup", "BM_GabeCallow");
					Group_SetAddress("GabeCallowGroup", "Jamaica", "", "");
					Group_SetPursuitGroup("GabeCallowGroup", PLAYER_GROUP);
					Group_SetTaskAttack("GabeCallowGroup", PLAYER_GROUP);
					Group_LockTask("GabeCallowGroup");
					
					PChar.quest.BM_PinkZahvatil.win_condition.l1 = "Character_Capture";
					PChar.quest.BM_PinkZahvatil.win_condition.l1.character = "BM_GabeCallow";
					PChar.quest.BM_PinkZahvatil.win_condition = "BM_PinkZahvatil";
					
					PChar.quest.BM_PinkPotopil.win_condition.l1 = "Character_sink";
					PChar.quest.BM_PinkPotopil.win_condition.l1.character = "BM_GabeCallow";
					PChar.quest.BM_PinkPotopil.win_condition = "BM_PinkPotopil";
				}
				else
				{
					Log_TestInfo("Проверка НЕ пройдена!");
					pchar.quest.BM_RepeatBarqueCheck.win_condition.l1 = "MapEnter";
					pchar.quest.BM_RepeatBarqueCheck.win_condition = "BM_RepeatBarqueCheck";
				}
			}
			else
			{
				Log_TestInfo("Проверка НЕ пройдена!");
				pchar.quest.BM_RepeatBarqueCheck.win_condition.l1 = "MapEnter";
				pchar.quest.BM_RepeatBarqueCheck.win_condition = "BM_RepeatBarqueCheck";
			}
		}
		else
		{
			Log_TestInfo("Проверка НЕ пройдена!");
			pchar.quest.BM_RepeatBarqueCheck.win_condition.l1 = "MapEnter";
			pchar.quest.BM_RepeatBarqueCheck.win_condition = "BM_RepeatBarqueCheck";
		}
	}
	
	else if (sQuestName == "BM_RepeatBarqueCheck") {
		pchar.quest.BM_SeaCheckBarque.win_condition.l1 = "location";
		pchar.quest.BM_SeaCheckBarque.win_condition.l1.location = "Jamaica";
		pchar.quest.BM_SeaCheckBarque.win_condition = "BM_SeaCheckBarque";
	}
	
	else if (sQuestName == "BM_CabinDialog") {
		LAi_FadeToBlackStart();
		DoQuestCheckDelay("BM_CabinDialog2", 1.0);
		LAi_SetStayType(pchar);
	}
	
	else if (sQuestName == "BM_CabinDialog2") {
		locCameraFromToPos(1.15, 4.95, -0.93, true, -1.96, 2.83, 0.48);
		pchar.GenQuest.BlockDialogCamera = true;
		ChangeCharacterAddressGroup(pchar, PChar.location, "rld", "aloc0");
		
		sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
		ChangeCharacterAddressGroup(sld, PChar.location, "rld", "loc2");
		LAi_SetActorType(sld);
		
		DoQuestCheckDelay("BM_CabinDialog3", 1.0);
	}
	
	else if (sQuestName == "BM_CabinDialog3") {
		LAi_FadeToBlackEnd();
		sld = GetCharacter(CreateCharacterClone(CharacterFromID("Irons"), 0));
		sld.id = "IronsClone";
		ChangeCharacterAddressGroup(sld, PChar.location, "rld", "loc1");
		sld.location = "None";
		
		sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
		sld.dialog.filename = "Quest\BlackMark.c";
		sld.dialog.currentnode = "BM_IronsClone1";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
	}
	
	else if (sQuestName == "BM_CabinDialog4") {
		DoQuestCheckDelay("hide_weapon", 1.2);
		sld = CharacterFromID("IronsClone");
		sld.MusketerDistance = 5;
		sld.dialog.filename = "Quest\BlackMark.c";
		sld.dialog.currentnode = "BM_IronsClone8";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	
	else if (sQuestName == "BM_IronsCloneMushket") {
		sld = CharacterFromID("IronsClone");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	
	else if (sQuestName == "BM_PinkZahvatil") {		//Захватили пинк Принципио
		AddQuestRecord("BlackMark", "11");
		AddQuestUserData("BlackMark", "sSex", GetSexPhrase(StringFromKey("BlackMark_9"),StringFromKey("BlackMark_10")));
		CloseQuestHeader("BlackMark");
		bQuestDisableMapEnter = false;
		Island_SetReloadEnableGlobal("Jamaica", true);
		pchar.questTemp.BlackMarkQuestCompleted = true;
		DeleteQuestCondition("BM_PinkPotopil");
		
		sld = CharacterFromID("Irons");
		LAi_RemoveCheckMinHP(sld);
		LAi_SetImmortal(sld, false);
		DeleteAttribute(pchar, "questTemp.IronsItemsBlock");
		
		// итальянская рапира в сундуке
		pchar.GenQuestBox.PortRoyal_houseSp3Room = true;
		pchar.GenQuestBox.PortRoyal_houseSp3Room.box1.items.blade_40 = 1;
		
		SetTimerCondition("BM_DeleteItalianRapier", 0, 0, 7, false); // через неделю рапирка тю-тю
		
		//Проверка на наличие захваченного пинка
		if (CheckShipTypeInSquadron(SHIP_PINK) > 0)
		{
			DoQuestCheckDelay("BM_PinkZahvatil_SetMusic", 0.1);
			Achievment_Set("ach_CL_131");
			Achievment_Set("ach_CL_133");
			if (startHeroType == 4) Achievment_Set("ach_CL_135");
		}
	}
	
	else if (sQuestName == "BM_DeleteItalianRapier") {
		DeleteAttribute(pchar, "GenQuestBox.PortRoyal_houseSp3Room");
		DeleteAttribute(&locations[FindLocation("PortRoyal_houseSp3Room")], "box1");
	}
	
	else if (sQuestName == "BM_PinkZahvatil_SetMusic") {
		Start_TrackNonStop("music_SeaDogs1_MainTheme_Sea", 145)
	}
	
	else if (sQuestName == "BM_PinkPotopil") {
		pchar.GenQuest.CabinLock = true;
		DoQuestCheckDelay("BM_PinkPotopil_2", 2.5);
	}
	
	else if (sQuestName == "BM_PinkPotopil_2") {
		DeleteAttribute(pchar, "GenQuest.CabinLock");
		pchar.GenQuest.DontSetCabinOfficer = true;
		chrDisableReloadToLocation = true;
		Sea_CabinStartNow();
		
		sld = CharacterFromID("Irons");
		ChangeCharacterAddressGroup(sld, Get_My_Cabin(), "rld", "loc1");
		DoQuestCheckDelay("BM_PinkPotopil_3", 1.8);
	}
	
	else if (sQuestName == "BM_PinkPotopil_3") {
		sld = CharacterFromID("Irons");
		sld.dialog.filename = "Quest\BlackMark.c";
		sld.dialog.currentnode = "BM_IronsPinkPotopil1";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	
	else if (sQuestName == "BM_PinkPotopil_4") {	//Потопили пинк Принципио
		AddQuestRecord("BlackMark", "12");
		CloseQuestHeader("BlackMark");
		Achievment_Set("ach_CL_131");
		bQuestDisableMapEnter = false;
		Island_SetReloadEnableGlobal("Jamaica", true);
		pchar.questTemp.BlackMarkQuestCompleted = true;
		DeleteQuestCondition("BM_PinkZahvatil");
		
		DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
		chrDisableReloadToLocation = false;
		
		sld = CharacterFromID("Irons");
		LAi_RemoveCheckMinHP(sld);
		LAi_SetImmortal(sld, false);
		DeleteAttribute(pchar, "questTemp.IronsItemsBlock");
		
		// итальянская рапира в сундуке
		pchar.GenQuestBox.PortRoyal_houseSp3Room = true;
		pchar.GenQuestBox.PortRoyal_houseSp3Room.box1.items.blade_40 = 1;
		
		SetTimerCondition("BM_DeleteItalianRapier", 0, 0, 7, false); // через неделю рапирка тю-тю
	}
	
	else if (sQuestName == "BM_LandVariant") {	//Сухопутный вариант
		chrDisableReloadToLocation = false;
		bDisableLandEncounters = false;
		Return_IronsOfficer();
		
		// Сюда прописываем продолжение сухопутного варианта
		AddQuestRecord("BlackMark", "8");
		AddQuestUserData("BlackMark", "sSex", GetSexPhrase(StringFromKey("BlackMark_9"),StringFromKey("BlackMark_10")));
		AddQuestUserData("BlackMark", "sSex1", GetSexPhrase(StringFromKey("BlackMark_14"),StringFromKey("BlackMark_15")));
		
		pchar.quest.BM_JamaicaShoreDialog.win_condition.l1 = "location";
		pchar.quest.BM_JamaicaShoreDialog.win_condition.l1.location = "Shore36";
		pchar.quest.BM_JamaicaShoreDialog.win_condition = "BM_JamaicaShoreDialog";
	}
	
	else if (sQuestName == "BM_JamaicaShoreDialog") {
		chrDisableReloadToLocation = true;
		bDisableLandEncounters = true;
		pchar.GenQuest.Hunter2Pause = true;
	
		if (GetCharacterIndex("Irons") != -1 && CheckPassengerInCharacter(pchar, "Irons"))
		{
			sld = characterFromID("Irons");
			sld.dialog.currentnode = "BM_IronsJamaicaShore1";
			PlaceCharacter(sld, "goto", "random_must_be_near");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		}
	}
	
	else if (sQuestName == "BM_IronsJamaicaGo") {
		chrDisableReloadToLocation = false;
		sld = characterFromID("Irons");
		RemovePassenger(pchar, sld);
		LAi_SetActorType(sld);
		LAi_ActorRunToLocation(sld, "reload", "reload1_back", "", "", "", "", -1);
		sld.location = "None";
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		
		//FreeSitLocator("PortRoyal_tavern", "sit3");
		sld = GetCharacter(NPC_GenerateCharacter("BM_Pyanitsa", "panhandler_6", "man", "man", 10, ENGLAND, -1, false, "quest"));
		sld.dialog.filename = "Quest\BlackMark.c";
		sld.dialog.currentnode = "BM_Pyanitsa_0";
		sld.greeting = "poorman_male";
		LAi_SetSitType(sld);
		LAi_SetImmortal(sld, true);
		ChangeCharacterAddressGroup(sld, "PortRoyal_tavern", "sit", "sit3");
		AddLandQuestMark(sld, "questmarkmain");
	}
	
	else if (sQuestName == "BM_SearchGabeHouse") {
		if (sti(pchar.reputation.nobility) >= 61)
		{
			AddQuestRecord("BlackMark", "9");
			AddQuestUserData("BlackMark", "sSex1", GetSexPhrase(StringFromKey("BlackMark_9"),StringFromKey("BlackMark_10")));
		}
		else
		{
			AddQuestRecord("BlackMark", "10");
		}
		
		pchar.quest.BM_GabeHouseCheck.win_condition.l1 = "location";
		pchar.quest.BM_GabeHouseCheck.win_condition.l1.location = "PortRoyal_houseSp3";
		pchar.quest.BM_GabeHouseCheck.win_condition = "BM_GabeHouseCheck";
		
		sld = CharacterFromID("BM_Pyanitsa");
		sld.lifeday = 0;
		LAi_CharacterDisableDialog(sld);
	}
		
	else if (sQuestName == "BM_GabeHouseCheck") {
		if (!GetDLCenabled(DLC_APPID_3)) return;
		chrDisableReloadToLocation = true;
		
		if (BlackMark_CheckTimeInGabeHouse())
		{
			Log_TestInfo("Проверка пройдена, Гейб у себя дома");
			
			sld = GetCharacter(NPC_GenerateCharacter("BM_GabeCallow", "off_eng_1", "man", "man", 10, ENGLAND, -1, false, "quest"));
			sld.name = StringFromKey("BlackMark_11");
			sld.lastname = StringFromKey("BlackMark_12");
			sld.dialog.filename = "Quest\BlackMark.c";
			if (sti(pchar.reputation.nobility) > 61) sld.dialog.currentnode = "BM_GabeHouseGood1";
			else sld.dialog.currentnode = "BM_GabeHouseNeutral1";
			FantomMakeCoolFighter(sld, 10, 50, 50, "blade_14", "pistol14", "cartridge", 50);
			ChangeCharacterAddressGroup(sld, "PortRoyal_houseSp3", "barmen", "bar1");
			GiveItem2Character(sld, "indian_2");
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		}
		else
		{
			Log_TestInfo("Проверка не пройдена, Гейб отсутствует");
			
			// итальянская рапира в сундуке
			pchar.GenQuestBox.PortRoyal_houseSp3Room = true;
			pchar.GenQuestBox.PortRoyal_houseSp3Room.box1.items.blade_40 = 1;
			
			SetTimerCondition("BM_DeleteItalianRapier", 0, 0, 7, false); // через неделю рапирка тю-тю
			
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "barmen", "bar2", "BlackMark_LeaveLetterAlone1", -1);
		}
	}
	
	else if (sQuestName == "BlackMark_LeaveLetterAlone1") {
		LAi_SetActorType(pchar);
		LAi_ActorAnimation(pchar, "Barman_idle", "BlackMark_LeaveLetterAlone2", 3);
	}
	
	else if (sQuestName == "BlackMark_LeaveLetterAlone2") {
		notification(StringFromKey("BlackMark_16"), "None");
		PlaySound("interface\notebook.wav");
		DoQuestCheckDelay("BlackMark_LeaveLetterAlone3", 1.5);
	}
			
	else if (sQuestName == "BlackMark_LeaveLetterAlone3") {
		chrDisableReloadToLocation = false;
		
		LAi_SetPlayerType(pchar);
		
		AddQuestRecord("BlackMark", "13");
		
		pchar.quest.BM_ToJamaicaJungle.win_condition.l1 = "location";
		pchar.quest.BM_ToJamaicaJungle.win_condition.l1.location = "Jamaica_jungle_02";
		pchar.quest.BM_ToJamaicaJungle.win_condition = "BM_TommyJungleDialog";
	}
	
	else if (sQuestName == "BM_TommyJungleDialog") {
		LAi_LocationFightDisable(loadedLocation, true);
		chrDisableReloadToLocation = true;
		
		sld = characterFromID("Irons");
		sld.dialog.currentnode = "BM_IronsJamaicaJungle1";
		ChangeCharacterAddressGroup(sld, "Jamaica_jungle_02", "reload", "reload1_back");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	
	else if (sQuestName == "BM_CreateGabeInJungle") {
		if (GetHour() >= 5 && GetHour() <= 20)
		{
			SetLaunchFrameFormParam(StringFromKey("BlackMark_17"), "Reload_To_Location", 0, 4.0);
			WaitDate("", 0, 0, 0, 2, 0);
		}
		else
		{
			SetLaunchFrameFormParam(StringFromKey("BlackMark_18"), "Reload_To_Location", 0, 4.0);
			WaitDate("", 0, 0, 0, 10, 0);
		}
		RecalculateJumpTable();
		RefreshWeather();
		RefreshLandTime();
		SetLaunchFrameReloadLocationParam(pchar.location, "goto", "goto2", "BM_CreateGabeInJungle2");
		LaunchFrameForm();
	}
	
	else if (sQuestName == "BM_CreateGabeInJungle2") {
		sld = characterFromID("Irons");
		ChangeCharacterAddressGroup(sld, "Jamaica_jungle_02", "goto", "goto13");
		Return_IronsOfficer();
		if (CharacterIsAlive("BM_GabeCallow"))
		{
			sld = characterFromID("BM_GabeCallow");
			sld.dialog.currentnode = "BM_GabeJungle1";
			ChangeCharacterAddressGroup(sld, "Jamaica_jungle_02", "reload", "reload3_back");
			LAi_SetActorType(sld);
			//LAi_ActorDialog(sld, pchar, "", -1, 0);
			LAi_ActorFollow(sld, pchar, "BM_CreateGabeInJungle3", -1);
		}
		else
		{
			sld = GetCharacter(NPC_GenerateCharacter("BM_GabeCallow", "off_eng_1", "man", "man", 10, ENGLAND, -1, false, "quest"));
			sld.name = StringFromKey("BlackMark_11");
			sld.lastname = StringFromKey("BlackMark_12");
			sld.dialog.filename = "Quest\BlackMark.c";
			sld.dialog.currentnode = "BM_GabeJungle1";
			FantomMakeCoolFighter(sld, 10, 50, 50, "blade_14", "pistol14", "cartridge", 50);
			ChangeCharacterAddressGroup(sld, "Jamaica_jungle_02", "reload", "reload3_back");
			GiveItem2Character(sld, "indian_2");
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			LAi_SetActorType(sld);
			//LAi_ActorDialog(sld, pchar, "", -1, 0);
			LAi_ActorFollow(sld, pchar, "BM_CreateGabeInJungle3", -1);
		}
		
		for (i = 1; i <= 2; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("BM_GabeJungleSoldier" + i, "mush_eng_" + (rand(5) + 1), "man", "mushketer", 5, ENGLAND, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, 5, 25, 25, "", "mushket1", "cartridge", 0);
			ChangeCharacterAddressGroup(sld, "Jamaica_jungle_02", "reload", "reload3_back");
			LAi_CharacterDisableDialog(sld);
			LAi_SetWarriorType(sld);
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, characterFromID("BM_GabeCallow"), "", -1);
			LAi_SetHP(sld, 100.0, 100.0);
		}
	}
	
	else if (sQuestName == "BM_CreateGabeInJungle3") {
		LAi_FadeLong("BM_CreateGabeInJungle4", "");
	}
	
	else if (sQuestName == "BM_CreateGabeInJungle4") {
		locCameraFromToPos(3.07, 3.26, -1.33, true, 1.49, 0.69, -6.07);
		TeleportCharacterToPosAy(pchar, 6.26, 1.66, -4.49, -1.50);
		sld = characterFromID("Irons");
		TeleportCharacterToPosAy(sld, 3.12, 1.27, -3.07, -2.50);
		LAi_SetActorType(sld);
		
		sld = characterFromID("BM_GabeCallow");
		TeleportCharacterToPosAy(sld, 1.96, 1.16, -4.65, 0.50);
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
		
		for (i = 1; i <= 2; i++)
		{
			sld = characterFromID("BM_GabeJungleSoldier"+i);
			TeleportCharacterToPosAy(sld, 1.18, 0.98, -7.24, 0.50);
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, characterFromID("BM_GabeCallow"), "", -1);
		}
		
	}
	
	else if (sQuestName == "BM_GabeJungleFight") {
		LAi_LocationFightDisable(loadedLocation, false);
		sld = characterFromID("Irons");
		LAi_SetCheckMinHP(sld, 1, true, "");
		//sld.MusketerDistance = 10;
		Return_IronsOfficer();
	
		sld = characterFromID("BM_GabeCallow");
		LAi_group_MoveCharacter(sld, "EnemyFight");
		
		for (i = 1; i <= 2; i++)
		{
			sld = characterFromID("BM_GabeJungleSoldier" + i);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		
		LAi_group_FightGroups(LAI_GROUP_PLAYER, "EnemyFight", true);
		LAi_group_SetCheck("EnemyFight", "BM_TommyDialogAfterJungleFight");
	}
	
	else if (sQuestName == "BM_TommyDialogAfterJungleFight") {
		DoQuestCheckDelay("hide_weapon", 1.2);
		sld = characterFromID("Irons");
		sld.dialog.currentnode = "BM_IronsJamaicaJungle4";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	
	else if (sQuestName == "BM_FinalInJungleWithTommy") {
		chrDisableReloadToLocation = false;
		bDisableLandEncounters = false;
		
		sld = characterFromID("Irons");
		LAi_RemoveCheckMinHP(sld);
		LAi_SetImmortal(sld, false);
		DeleteAttribute(pchar, "questTemp.IronsItemsBlock");
		AddPassenger(pchar, sld, false);
		Return_IronsOfficer();
		
		AddQuestRecord("BlackMark", "14");
		AddQuestUserData("BlackMark", "sSex1", GetSexPhrase(StringFromKey("BlackMark_9"),StringFromKey("BlackMark_10")));
		CloseQuestHeader("BlackMark");
		pchar.questTemp.BlackMarkQuestCompleted = true;
		Achievment_Set("ach_CL_131");
	}
	
	else if (sQuestName == "BM_GoToJamaicaJungle_TommiPlan") {
		chrDisableReloadToLocation = false;
		
		AddQuestRecord("BlackMark", "15");
		AddQuestUserData("BlackMark", "sSex1", GetSexPhrase(StringFromKey("BlackMark_19"),StringFromKey("BlackMark_20")));
		AddQuestUserData("BlackMark", "sSex2", GetSexPhrase(StringFromKey("BlackMark_7"),StringFromKey("BlackMark_8")));
		AddQuestUserData("BlackMark", "sSex3", GetSexPhrase(StringFromKey("BlackMark_9"),StringFromKey("BlackMark_10")));
		
		pchar.quest.BM_ToJamaicaJungle.win_condition.l1 = "location";
		pchar.quest.BM_ToJamaicaJungle.win_condition.l1.location = "Jamaica_jungle_02";
		pchar.quest.BM_ToJamaicaJungle.win_condition = "BM_TommyJungleDialog";
	}
	
	else if (sQuestName == "BM_GoToJamaicaJungle_GabePlan") {
		chrDisableReloadToLocation = false;
		pchar.questTemp.BM_GabePlan = true;
		
		AddQuestRecord("BlackMark", "16");
		AddQuestUserData("BlackMark", "sSex", GetSexPhrase(StringFromKey("BlackMark_9"),StringFromKey("BlackMark_10")));
		
		pchar.quest.BM_ToJamaicaJungle.win_condition.l1 = "location";
		pchar.quest.BM_ToJamaicaJungle.win_condition.l1.location = "Jamaica_jungle_02";
		pchar.quest.BM_ToJamaicaJungle.win_condition = "BM_TommyJungleDialog";
	}
	
	else if (sQuestName == "BM_GabePlan_BitvaSTommi") {
		if (GetHour() >= 5 && GetHour() <= 20)
		{
			WaitDate("", 0, 0, 0, 2, 0);
		}
		else
		{
			WaitDate("", 0, 0, 0, 10, 0);
		}
		DoQuestReloadToLocation(pchar.location, "goto", "goto2", "BM_GabePlan_BitvaSTommi2");
		LaunchFrameForm();
	}
	
	else if (sQuestName == "BM_GabePlan_BitvaSTommi2") {
		LAi_LocationFightDisable(loadedLocation, false);
		LAi_SetFightMode(pchar, true);
		sld = characterFromID("Irons");
		ChangeCharacterAddressGroup(sld, "Jamaica_jungle_02", "goto", "goto13");
		DeleteAttribute(sld, "OfficerImmortal");
		if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
		if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
		sTemp = "RestoreHealth_" + sld.index;
		if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		LAi_group_SetCheck("EnemyFight", "BM_GabePlan_BitvaSTommi3");
	}
	
	else if (sQuestName == "BM_GabePlan_BitvaSTommi3") {
		LAi_LocationFightDisable(loadedLocation, true);
		DoQuestCheckDelay("hide_weapon", 1.2);
		
		sld = characterFromID("BM_GabeCallow");
		sld.dialog.currentnode = "BM_GabePlan_TommiMertv";
		ChangeCharacterAddressGroup(sld, "Jamaica_jungle_02", "reload", "reload3_back");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		
		for (i = 1; i <= 2; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("BM_GabeJungleSoldier" + i, "mush_eng_" + (rand(5) + 1), "man", "mushketer", 5, ENGLAND, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, 5, 25, 25, "", "mushket1", "cartridge", 0);
			ChangeCharacterAddressGroup(sld, "Jamaica_jungle_02", "reload", "reload3_back");
			LAi_CharacterDisableDialog(sld);
			LAi_SetWarriorType(sld);
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, characterFromID("BM_GabeCallow"), "", -1);
			LAi_SetHP(sld, 100.0, 100.0);
		}
	}
	
	else if (sQuestName == "BM_GabePlan_BitvaCallowSoloConflict") {
		LAi_LocationFightDisable(loadedLocation, false);
		LAi_SetFightMode(pchar, true);
	
		sld = characterFromID("BM_GabeCallow");
		LAi_SetImmortal(sld, false);
		LAi_RemoveCheckMinHP(sld);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		
		for (i = 1; i <= 2; i++)
		{
			sld = characterFromID("BM_GabeJungleSoldier" + i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		LAi_group_SetCheck("EnemyFight", "BM_GabePlan_BitvaCallowSoloConflict2");
	}
	
	else if (sQuestName == "BM_GabePlan_BitvaCallowSoloConflict2") {
		chrDisableReloadToLocation = false;
		bDisableLandEncounters = false;
		DoQuestCheckDelay("hide_weapon", 1.2);
		
		if (CheckAttribute(pchar, "questTemp.BM_GabeCallow_Conflict"))
		{
			AddQuestRecord("BlackMark", "17");
			AddQuestUserData("BlackMark", "sSex", GetSexPhrase(StringFromKey("BlackMark_9"),StringFromKey("BlackMark_10")));
			ChangeCharacterNationReputation(pchar, ENGLAND, -7);
		}
		if (CheckAttribute(pchar, "questTemp.BM_GabeCallow_Rapira"))
		{
			AddQuestRecord("BlackMark", "18");
			Achievment_Set("ach_CL_134");
		}
		CloseQuestHeader("BlackMark");
		Achievment_Set("ach_CL_131");
	}
	
	else if (sQuestName == "BM_GabePlan_CallowDruzhba") {
		LAi_LocationFightDisable(loadedLocation, false);
		chrDisableReloadToLocation = false;
		bDisableLandEncounters = false;
		DoQuestCheckDelay("hide_weapon", 1.2);
		
		AddQuestRecord("BlackMark", "19");
		AddQuestUserData("BlackMark", "sSex", GetSexPhrase(StringFromKey("BlackMark_9"),StringFromKey("BlackMark_10")));
		AddQuestUserData("BlackMark", "sSex1", GetSexPhrase(StringFromKey("BlackMark_7"),StringFromKey("BlackMark_7")));
		AddQuestUserData("BlackMark", "sSex2", GetSexPhrase(StringFromKey("BlackMark_14"),StringFromKey("BlackMark_15")));
		CloseQuestHeader("BlackMark");
		Achievment_Set("ach_CL_131");
		
		sld = characterFromID("BM_GabeCallow");
		LAi_SetActorType(sld);
		LAi_ActorRunToLocation(sld, "reload", "reload3_back", "", "", "", "", -1);
		sld.lifeday = 0;
		sld.location = "None";
		LAi_SetImmortal(sld, true);
		
		for (i = 1; i <= 2; i++)
		{
			sld = characterFromID("BM_GabeJungleSoldier" + i);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload3_back", "", "", "", "", -1);
			sld.lifeday = 0;
			sld.location = "None";
			LAi_SetImmortal(sld, true);
		}
	}
	
	else if (sQuestName == "BM_GabePlan_GazgovorTommiAndGabe") {
		if (GetHour() >= 5 && GetHour() <= 20)
		{
			SetLaunchFrameFormParam(StringFromKey("BlackMark_17"), "Reload_To_Location", 0, 4.0);
			WaitDate("", 0, 0, 0, 2, 0);
		}
		else
		{
			SetLaunchFrameFormParam(StringFromKey("BlackMark_18"), "Reload_To_Location", 0, 4.0);
			WaitDate("", 0, 0, 0, 10, 0);
		}
		RecalculateJumpTable();
		RefreshWeather();
		RefreshLandTime();
		SetLaunchFrameReloadLocationParam(pchar.location, "goto", "goto2", "BM_GabePlan_GazgovorTommiAndGabe2");
		LaunchFrameForm();
	}
	
	else if (sQuestName == "BM_GabePlan_GazgovorTommiAndGabe2") {
		sld = characterFromID("Irons");
		ChangeCharacterAddressGroup(sld, "Jamaica_jungle_02", "goto", "goto13");
		Return_IronsOfficer();
		sld = characterFromID("BM_GabeCallow");
		sld.dialog.currentnode = "BM_GabePlan_GazgovorTommiAndGabe_1";
		ChangeCharacterAddressGroup(sld, "Jamaica_jungle_02", "reload", "reload3_back");
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, pchar, "BM_GabePlan_GazgovorTommiAndGabe3", -1);
		
		for (i = 1; i <= 2; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("BM_GabeJungleSoldier" + i, "mush_eng_" + (rand(5) + 1), "man", "mushketer", 5, ENGLAND, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, 5, 25, 25, "", "mushket1", "cartridge", 0);
			ChangeCharacterAddressGroup(sld, "Jamaica_jungle_02", "reload", "reload3_back");
			LAi_CharacterDisableDialog(sld);
			LAi_SetWarriorType(sld);
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, characterFromID("BM_GabeCallow"), "", -1);
			LAi_SetHP(sld, 100.0, 100.0);
		}
	}
	
	else if (sQuestName == "BM_GabePlan_GazgovorTommiAndGabe3") {
		LAi_FadeLong("BM_GabePlan_GazgovorTommiAndGabe4", "");
	}
	
	else if (sQuestName == "BM_GabePlan_GazgovorTommiAndGabe4") {
		locCameraFromToPos(3.07, 3.26, -1.33, true, 1.49, 0.69, -6.07);
		TeleportCharacterToPosAy(pchar, 6.26, 1.66, -4.49, -1.50);
		sld = characterFromID("Irons");
		TeleportCharacterToPosAy(sld, 3.12, 1.27, -3.07, -2.50);
		LAi_SetActorType(sld);
		
		sld = characterFromID("BM_GabeCallow");
		TeleportCharacterToPosAy(sld, 1.96, 1.16, -4.65, 0.50);
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
		
		for (i = 1; i <= 2; i++)
		{
			sld = characterFromID("BM_GabeJungleSoldier"+i);
			TeleportCharacterToPosAy(sld, 1.18, 0.98, -7.24, 0.50);
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, characterFromID("BM_GabeCallow"), "", -1);
		}
	}
	
	else if (sQuestName == "BM_GabePlan_GazgovorTommiAndGabe_Fight") {
		LAi_LocationFightDisable(loadedLocation, false);
		LAi_SetFightMode(pchar, true);
		sld = characterFromID("BM_GabeCallow");
		LAi_SetCheckMinHP(sld, 1, true, "");
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		
		for (i = 1; i <= 2; i++)
		{
			sld = characterFromID("BM_GabeJungleSoldier" + i);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
	
		sld = characterFromID("Irons");
		DeleteAttribute(sld, "OfficerImmortal");
		if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
		if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
		sTemp = "RestoreHealth_" + sld.index;
		if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
		LAi_group_MoveCharacter(sld, "EnemyFight");
		
		LAi_group_FightGroups(LAI_GROUP_PLAYER, "EnemyFight", true);
		LAi_group_SetCheck("EnemyFight", "BM_GabePlan_GazgovorTommiAndGabe_Win");
	}
	
	else if (sQuestName == "BM_GabePlan_GazgovorTommiAndGabe_Win") {
		DoQuestCheckDelay("hide_weapon", 1.2);
		sld = characterFromID("BM_GabeCallow");
		sld.dialog.currentnode = "BM_GabePlan_GabeWin_1";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
		// <== Квест "Чёрная метка"
	else
	{
		condition = false;
	}
	
	return condition;
}