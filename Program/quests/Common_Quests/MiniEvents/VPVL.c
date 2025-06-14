
// andre39966
bool VPVL_QuestComplete(string sQuestName, string qname)
{
	ref sld;
	int i, n;
	
	string sTemp;
	
	bool condition = true;
	
	// Квест "В плену великого улова" ==>
	
	if (sQuestName == "VPVL_Gegerate_Lea") {
		sld = GetCharacter(NPC_GenerateCharacter("VPVL_Lea_girl", "women_16", "woman", "towngirl", 10, ENGLAND, -1, false, "soldier"));
		sld.name = StringFromKey("Neutral_17");
		sld.lastname = StringFromKey("Neutral_18");
		ChangeCharacterAddressGroup(sld, "FortFrance_town", "goto", "goto26"); 
		LAi_SetStayType(sld); 
		sld.dialog.Filename = "Quest\MiniEvents\VPVL_dialog.c"; 
		sld.dialog.currentnode = "First Time"; 
		LAi_SetImmortal(sld, true);
		AddLandQuestMark(sld, "questmarkmain");
	}

	else if (sQuestName == "VPVL_Start") {
		pchar.quest.VPVL_SetFollowAfterLoad.win_condition.l1 = "location";
		pchar.quest.VPVL_SetFollowAfterLoad.win_condition.l1.location = "Shore39"; 
		pchar.quest.VPVL_SetFollowAfterLoad.win_condition = "VPVL_SetFollowAfterLoad";
		LAi_LocationFightDisable(&Locations[FindLocation("Shore39")], true); // для особо умных выкл боевой режим
		locations[FindLocation("Shore39")].DisableEncounters = true;
	}
	
	else if (sQuestName == "VPVL_SetFollowAfterLoad") {
			sld = GetCharacter(NPC_GenerateCharacter("VPVL_contr_1", "citiz_42", "man", "man", 1, PIRATE, 0, false, "soldier"));
			FantomMakeCoolFighter(sld, 5, 40, 40, "blade_14", "pistol1", "bullet", 70);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			ChangeCharacterAddressGroup(sld, "Shore39", "goto", "goto2");
			TeleportCharacterToPosAy(sld, 3.88, 1.26, 2.68, 0.00);
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			chrDisableReloadToLocation = true;	
			LAi_SetActorType(pchar);
			LAi_ActorTurnToCharacter(pchar, sld);
			
			sld = GetCharacter(NPC_GenerateCharacter("VPVL_contr_2", "citiz_43", "man", "man", 1, PIRATE, 0, false, "soldier"));
			FantomMakeCoolFighter(sld, 5, 20, 20, "blade_14", "pistol1", "bullet", 20);
			ChangeCharacterAddressGroup(sld, "Shore39", "goto", "goto1");
			sld.dialog.filename = "Quest\MiniEvents\VPVL_dialog.c";
			sld.dialog.currentnode = "Kontr Le Maren";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			DoQuestCheckDelay("VPVL_StayType", 0.1);
			
			for (i=4; i<=5; i++)
			{
			sld = GetCharacter(NPC_GenerateCharacter("VPVL_contr_"+i, "citiz_" + (rand(9) + 21), "man", "man", sti(pchar.rank), PIRATE, -1, true, "pirate"));
			FantomMakeCoolFighter(sld, 5, 20, 20, "blade_14", "none", "none", 20);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyGroup");
			ChangeCharacterAddressGroup(sld, "Shore39", "smugglers", LAi_FindRandomLocator("smugglers")););
			}
	}
	
	else if (sQuestName == "VPVL_StayType") {
		LAi_SetStayType(pchar);
		//locCameraFromToPos(-5.40, 2.0, 8.80, false, 25, -2, -20);
		locCameraFromToPos(-4.81, 1.06, 15.32, false, -2.64, 0.70, 7.15);
		StartQuestMovie(true, true, true);
	}
	
	else if (sQuestName == "VPVL_Pistol_Murder") {
		sld = CharacterFromID("VPVL_contr_1");
		LAi_SetActorType(pchar);
		LAi_ActorTurnToCharacter(pchar, sld);
		LAi_ActorAnimation(pchar, "Shot", "VPVL_contr_1_die", 0.8);
		DoQuestCheckDelay("VPVL_Fight_on_the_bich", 1);
	}
	
	else if (sQuestName == "VPVL_contr_1_die") {
		sld = CharacterFromID("VPVL_contr_1");
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "death_7", "1", -1);
		LaunchBlood(sld, 1.0, true, "fight");
		LAi_LocationFightDisable(&Locations[FindLocation("Shore39")], false); 
		EndQuestMovie(); 
		LAi_SetHP(sld, 10.0, 100.0);    //Чтобы не восставал из мёртвых
		LAi_ApplyCharacterDamage(sld, 112, "fire"); 
		LAi_CheckKillCharacter(sld);
	}
	
	else if (sQuestName == "VPVL_Fight_on_the_bich") {
		locCameraTarget(pchar);
		locCameraFollow();
		LAi_SetPlayerType(pchar);
		sld = CharacterFromID("VPVL_contr_2");
        LAi_SetWarriorType(sld); 
        LAi_group_MoveCharacter(sld, "EnemyGroup");
		LAi_group_SetRelation("EnemyGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY); 
		LAi_group_FightGroups("EnemyGroup", LAI_GROUP_PLAYER, true); 
		LAi_SetFightMode(pchar, true);
		LAi_group_SetCheck("EnemyGroup", "VPVL_Start_Generate_Pier");
	}
	
	else if (sQuestName == "VPVL_EveryoneFight") {
		locCameraTarget(pchar);
		locCameraFollow();
		LAi_SetPlayerType(pchar);
		sld = CharacterFromID("VPVL_contr_1");
        LAi_SetWarriorType(sld); 
        LAi_group_MoveCharacter(sld, "EnemyGroup");
		
		sld = CharacterFromID("VPVL_contr_2");
        LAi_SetWarriorType(sld); 
        LAi_group_MoveCharacter(sld, "EnemyGroup");
		LAi_group_SetRelation("EnemyGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY); 
		LAi_group_FightGroups("EnemyGroup", LAI_GROUP_PLAYER, true); 
		LAi_SetFightMode(pchar, true);
		LAi_group_SetCheck("EnemyGroup", "VPVL_Start_Generate_Pier")
	}
	
	else if (sQuestName == "VPVL_Start_Generate_Pier") {
		chrDisableReloadToLocation = false;
		AddQuestRecord("VPVL", "3");
		pchar.quest.PierInGrot.win_condition.l1 = "location";
		pchar.quest.PierInGrot.win_condition.l1.location = "Martinique_Grot"; 
		pchar.quest.PierInGrot.win_condition = "VPVL_Generate_Pier";
		LocatorReloadEnterDisable("Shore39", "boat", true);
		DeleteAttribute(&locations[FindLocation("Shore39")], "DisableEncounters");
	}
	
	else if (sQuestName == "VPVL_Generate_Pier") {
		
		sld = GetCharacter(NPC_GenerateCharacter("VPVL_contr_3", "citiz_41", "man", "man", 1, PIRATE, -1, false, "quest"));
		FantomMakeCoolFighter(sld, 10, 50, 50, "blade_19", "pistol5", "bullet", 20);
		TakeNItems(sld, "bullet", 5);
		AddItems(sld, "gunpowder", 5);
		ChangeCharacterAddressGroup(sld, "Martinique_Grot", "goto", "goto2"); 
		LAi_SetWarriorType(sld); 
		LAi_group_MoveCharacter(sld, "EnemyFight"); 
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY); 
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true); 
		LAi_SetFightMode(pchar, true);
		
		sld = GetCharacter(NPC_GenerateCharacter("VPVL_Pier_carno", "citiz_38", "man", "man", 1, PIRATE, -1, false, "quest"));  // Пьер Карно
		ChangeCharacterAddressGroup(sld, "Martinique_Grot", "goto", "goto5"); 
		sld.name = StringFromKey("Neutral_19");
		sld.lastname = StringFromKey("Neutral_18");
		sld.dialog.FileName = "Quest\MiniEvents\VPVL_dialog.c";
		sld.dialog.currentnode = "PierFirstTalk";
		LAi_CharacterDisableDialog(sld);
		LAi_SetGroundSitType(sld);
		LAi_group_MoveCharacter(sld, "PLAYER_GROUP");
		LAi_SetImmortal(sld, true);
		AddLandQuestMark(sld, "questmarkmain");
		LAi_group_SetCheck("EnemyFight", "VPVL_AfterFight"); 
		LAi_LocationDisableOfficersGen("Martinique_Grot", true);
		locations[FindLocation("Martinique_Grot")].DisableEncounters = true;
		chrDisableReloadToLocation = true;

	}
	
	else if (sQuestName == "VPVL_AfterFight") {
		LAi_SetStayType(pchar);
		DoQuestCheckDelay("VPVL_PlayerType", 1);//убрать оружие, (если убрать стандартным способом, после убийства пистолетом - не убирает)
		LAi_LocationFightDisable(&Locations[FindLocation("Martinique_Grot")], true);
		
		sld = CharacterFromID("VPVL_Pier_carno");
		LAi_CharacterEnableDialog(sld);
		
	}
	
	else if (sQuestName == "VPVL_PlayerType") {
		LAi_SetPlayerType(pchar);
	}
	
	else if (sQuestName == "VPVL_ClearLea") {
		sld = CharacterFromID("VPVL_Lea_girl");
		ChangeCharacterAddress(sld, "none", "");
	}
	
	else if (sQuestName == "VPVL_PierStay") {
		sld = CharacterFromID("VPVL_Pier_carno");
		LAi_SetActorType(sld);
	}
	
	else if (sQuestName == "VPVL_PierFollow") {
		sld = CharacterFromID("VPVL_Pier_carno");
		LAi_SetActorType(sld);
		LAi_ActorFollowEverywhere(sld, "pchar", -1);
		chrDisableReloadToLocation = false;
		AddPassenger(pchar, sld, false);
		LAi_LocationFightDisable(&Locations[FindLocation("Martinique_Grot")], false);
		sld = CharacterFromID("VPVL_Lea_girl");
		sld.dialog.currentnode = "FindPier";
		pchar.quest.SecondTalkWithLea.win_condition.l1 = "location";
		pchar.quest.SecondTalkWithLea.win_condition.l1.location = "FortFrance_Town";
		pchar.quest.SecondTalkWithLea.win_condition = "VPVL_LeaSecondTalk";
		LocatorReloadEnterDisable("Martinique_jungle_01", "reload2_back", true);//закрыть выход к городу
		LAi_LocationDisableOfficersGen("Martinique_Grot", false);
		locations[FindLocation("Martinique_Grot")].DisableEncounters = false;
		LocatorReloadEnterDisable("Shore39", "boat", false);
		
		sld = CharacterFromID("VPVL_Lea_girl");
		ChangeCharacterAddressGroup(sld, "FortFrance_Town", "rld", "loc0");
	}
	
	else if (sQuestName == "VPVL_LeaSecondTalk") {
		sld = CharacterFromID("VPVL_Pier_carno");
		ChangeCharacterAddressGroup(sld, "FortFrance_Town", "officers", "reload2_2");
		ChangeCharacterAddressGroup(pchar, "FortFrance_Town", "officers", "reload2_3");
		CharacterTurnToLoc(sld, "rld", "loc0");
		sld = CharacterFromID("VPVL_Lea_girl");
		sld.dialog.currentnode = "Lea second talk";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		LAi_SetStayType(pchar);
		CharacterTurnToLoc(pchar, "rld", "loc0");
		DoQuestCheckDelay("VPVL_FortFranceVPVLcamera", 0.1);
		LocatorReloadEnterDisable("Martinique_jungle_01", "reload2_back", false);
	}
	
	else if (sQuestName == "VPVL_FortFranceVPVLcamera") {
		locCameraFromToPos(-7.48, 3.1, 83.93, false, 0, -8, 0);
		StartQuestMovie(true, true, true);
	}
	
	else if (sQuestName == "VPVL_PierTalkOnThePirs") {
		sld = CharacterFromID("VPVL_Pier_carno");
		sld.dialog.currentnode = "PierInThePirs";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		locCameraFromToPos(-9.48, 3.1, 84.93, false, 40, -15, 0);
		CharacterTurnToLoc(pchar, "rld", "loc0");
		RemovePassenger(Pchar, sld);
	}
	
	else if (sQuestName == "VPVL_KarnoGoHome") {
		EndQuestMovie();
		LAi_SetPlayerType(pchar);
		sld = CharacterFromID("VPVL_Pier_carno");
		LAi_SetActorType(sld);
		LAi_ActorRunToLocation(sld, "reload", "houseK16", "none", "", "", "OpenTheDoors", 7);
		chrDisableReloadToLocation = true;
		InterfaceStates.Buttons.Save.enable = true;
		bDisableCharacterMenu = true;
		sld = CharacterFromID("VPVL_Lea_girl");
		LAi_SetActorType(sld);
		LAi_ActorRunToLocation(sld, "reload", "houseK16", "none", "", "", "OpenTheDoors", 7);
		DoQuestCheckDelay("VPVL_SpawnPierInTavern", 7);
	}
	
	else if (sQuestName == "VPVL_SpawnPierInTavern") {
		pchar.quest.SpawnPier.win_condition.l1 = "Timer";
		pchar.quest.SpawnPier.win_condition.l1.date.hour = 18; 
		pchar.quest.SpawnPier.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1); 
		pchar.quest.SpawnPier.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1); // Текущий месяц
		pchar.quest.SpawnPier.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1); // Текущий год
		pchar.quest.SpawnPier.win_condition.l2 = "location";
		pchar.quest.SpawnPier.win_condition.l2.location = "FortFrance_Tavern";
		pchar.quest.SpawnPier.win_condition = "VPVL_SpawnPierAtTime";
		pchar.quest.SpawnRumCap.win_condition.l1 = "Timer";
		pchar.quest.SpawnRumCap.win_condition.l1.date.hour = 18; 
		pchar.quest.SpawnRumCap.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0); // Сегодняшний день
		pchar.quest.SpawnRumCap.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
		pchar.quest.SpawnRumCap.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
		pchar.quest.SpawnRumCap.win_condition = "VPVL_SpawnVPVLcontrShip"; 
		bDisableCharacterMenu = false;
		pchar.questTemp.VPVL_Magor_Dialogue = true;
		AddLandQuestMark(characterFromId("FortFrance_Mayor"), "questmarkmain");
	}
	
	else if (sQuestName == "VPVL_SpawnPierAtTime") {
		FreeSitLocator("FortFrance_Tavern", "sit5");
		sld = CharacterFromID("VPVL_Pier_carno");
		ChangeCharacterAddressGroup(sld, "FortFrance_Tavern", "sit", "sit5");
		LAi_SetSitType(sld);
		sld.dialog.currentnode = "PierTalkTavern";
		AddLandQuestMark(characterFromId("VPVL_Pier_carno"), "questmarkmain");
		DoQuestCheckDelay("VPVL_ClearPleaceForGG", 0.1);
	}
	
	else if (sQuestName == "VPVL_ClearPleaceForGG") {
		FreeSitLocator("FortFrance_Tavern", "sit6");
	}
	
	else if (sQuestName == "VPVL_SitOnTheTable") {
		ChangeCharacterAddressGroup(pchar, "FortFrance_tavern", "sit", "sit6");
		LAi_SetSitType(pchar);
	}
	
	else if (sQuestName == "VPVL_ExitFromTableVPVL") {
		ChangeCharacterAddressGroup(pchar, "FortFrance_tavern", "tables", "stay5");
		LAi_SetPlayerType(pchar);
	}
	
	else if (sQuestName == "VPVL_PierLivingTavern") {
		pchar.quest.RemovePierOnExit.win_condition.l1 = "ExitFromLocation";
		pchar.quest.RemovePierOnExit.win_condition.l1.location = pchar.location;
		pchar.quest.RemovePierOnExit.win_condition = "VPVL_RemovePierFromTavern";
		SetTimerCondition("VPVL_PierSpawnInTheCity", 0, 0, 1, false);
	}
	
	else if (sQuestName == "VPVL_RemovePierFromTavern") {
		sld = CharacterFromID("VPVL_Pier_carno");
		ChangeCharacterAddress(sld, "none", "");
	}
	
	else if (sQuestName == "VPVL_PierSpawnInTheCity") {
		sld = CharacterFromID("VPVL_Pier_carno");
		ChangeCharacterAddressGroup(sld, "FortFrance_Town", "goto", "goto30");
		LAi_SetCitizenType(sld);
		LAi_SetLoginTime(sld, 12.0, 21.99);
		sld.dialog.currentnode = "MeetingInTneCity";
		LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	}
	
	else if (sQuestName == "VPVL_SetGovernorDialogueFlag") {
		pchar.quest.GovernorDialogueReady.win_condition.l1 = "Timer";
		pchar.quest.GovernorDialogueReady.win_condition.l1.date.day = GetAddingDataDay(0, 0, 3); // Текущий день + 3
		pchar.quest.GovernorDialogueReady.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
		pchar.quest.GovernorDialogueReady.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
		pchar.quest.GovernorDialogueReady.win_condition = "VPVL_ActivateGovernorFlag";
	}
	
	else if (sQuestName == "VPVL_ActivateGovernorFlag") {
		pchar.questTemp.VPVL_GovernorDialogueAvailable = true;
		AddLandQuestMark(characterFromId("FortFrance_Mayor"), "questmarkmain");
	}
	
	else if (sQuestName == "VPVL_SpawnVPVLcontrShip") {       // Ставим корабль
		if (CheckAttribute(pchar, "questTemp.VPVL_DontSpawnSmugglersShip") && sti(pchar.questTemp.VPVL_DontSpawnSmugglersShip) == true)
		{
			if (CheckAttribute(pchar, "questTemp.VPVL_RumCap_DontSpawnSmugglersShipPier") && sti(pchar.questTemp.VPVL_DontSpawnSmugglersShipPier) == true)
			{
				// Здесь может быть ваша реклама, andre39966
			}
		}
		else
		{
		Group_FindOrCreateGroup("VPVL_CapGroup");
		Group_SetType("VPVL_CapGroup", "VPVL_pirate");//тип группы
		sld = GetCharacter(NPC_GenerateCharacter("VPVL_Cap", "mercen_5", "man", "man", 25, PIRATE, 5, true, "quest"));
		FantomMakeSmallSailor(sld, SHIP_SCHOONER, StringFromKey("Neutral_24"),  CANNON_TYPE_CANNON_LBS16, 45, 40, 40, 50, 50);
		FantomMakeCoolFighter(sld, 20, 50, 50, "blade_05", "pistol1", "bullet", 100);
		AddMoneyToCharacter(sld, 10000);
		SetCharacterGoods(sld, GOOD_SHIPSILK, 100);
		SetCharacterGoods(sld, GOOD_WEAPON, 200);
		Group_AddCharacter("VPVL_CapGroup", "VPVL_Cap");
		Group_SetGroupCommander("VPVL_CapGroup", "VPVL_Cap");
		Group_SetAddress("VPVL_CapGroup", "Martinique", "Quest_Ships", "Quest_Ship_3");
		Group_SetTaskAttack("VPVL_CapGroup", PLAYER_GROUP); // Устанавливаем задачу атаковать ГГ
		Group_LockTask("VPVL_CapGroup"); // Блокируем задачу, чтобы не переключалась
		SetTimerCondition("VPVL_KillCapitanOfSmuggler", 0, 0, 2, false);
		pchar.questTemp.VPVL_ContersShipIsCreate = true;
		
		PChar.quest.VPVL_Dno.win_condition.l1 = "Character_sink";
		PChar.quest.VPVL_Dno.win_condition.l1.character = "VPVL_Cap";
		PChar.quest.VPVL_Dno.win_condition = "VPVL_Dno";	
		PChar.quest.VPVL_Zahvat.win_condition.l1 = "Character_Capture";
		PChar.quest.VPVL_Zahvat.win_condition.l1.character = "VPVL_Cap";
		PChar.quest.VPVL_Zahvat.win_condition = "VPVL_Zahvat";
		}
	}
	
	else if (sQuestName == "VPVL_KillCapitanOfSmuggler") {
		DeleteAttribute(pchar, "questTemp.VPVL_Magor_Dialogue");
		DelLandQuestMark(characterFromId("FortFrance_Mayor"));
		if (CheckAttribute(pchar, "questTemp.VPVL_ContersShipIsCreate") && sti(pchar.questTemp.VPVL_ContersShipIsCreate) == true)
			{
				sld = characterFromId("VPVL_Cap");
				LAi_KillCharacter(sld); 
				DeleteAttribute(pchar, "questTemp.VPVL_ContersShipIsCreate");
			}
	}
	
	else if (sQuestName == "VPVL_Dno") {
		DeleteQuestCondition("VPVL_Zahvat");
		DeleteAttribute(pchar, "questTemp.VPVL_Magor_Dialogue");
		DelLandQuestMark(characterFromId("FortFrance_Mayor"));
	}
	
	else if (sQuestName == "VPVL_Zahvat") {
		DeleteQuestCondition("VPVL_Dno");
		DeleteAttribute(pchar, "questTemp.VPVL_Magor_Dialogue");
		DelLandQuestMark(characterFromId("FortFrance_Mayor"));
	}
		
	else
	{
		condition = false;
	}
	
	return condition;
}    


