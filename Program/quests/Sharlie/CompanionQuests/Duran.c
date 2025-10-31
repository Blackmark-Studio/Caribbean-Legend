void Duran_Anri_DlgExit_1()
{
	locCameraFromToPos(3.47, 2.41, 0.10, false, -1.05, 0.20, -0.07);
			
	sld = CharacterFromID("SKD_Anri");
	CharacterTurnByLoc(sld, "barmen", "stay");
	
	sld = CharacterFromID("SKD_Alisia");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload2", "", "", "", "", -1);
	sld.location = "None";
	sld.lifeday = 0;
	LAi_SetActorType(pchar);
	DoQuestCheckDelay("SKD_DomAnri_2", 4.0);
}

void Duran_Anri_DlgExit_2()
{
	EndQuestMovie();
			
	sld = CharacterFromID("Duran");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	
	sld = CharacterFromID("SKD_Anri");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	
	LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
	LAi_SetFightMode(pchar, true);
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
	LAi_group_SetCheck("EnemyFight", "SKD_DomAnri_6");
}

void Duran_Duran_DlgExit_1()
{
	sld = CharacterFromID("Duran");
	chrDisableReloadToLocation = false;
	sld.loyality = makeint(sld.loyality) + 10;
	ReturnOfficer_Duran();
}

void Duran_Duran_DlgExit_2()
{
	SetQuestHeader("TheFormerKnight");
	AddQuestRecord("TheFormerKnight", "1");
	chrDisableReloadToLocation = false;
	sld = CharacterFromID("Duran");
	sld.loyality = makeint(sld.loyality) + 15;
	ReturnOfficer_Duran();
	PChar.quest.SKD_DomAnri.win_condition.l1 = "location";
	PChar.quest.SKD_DomAnri.win_condition.l1.location = "PortRoyal_houseSp1";
	PChar.quest.SKD_DomAnri.win_condition = "SKD_DomAnri";
	pchar.GenQuestBox.PortRoyal_houseSp1.box1.items.chest = 1;
}

void Duran_Duran_DlgExit_3()
{
	sld = CharacterFromID("Duran");
	LAi_SetCurHPMax(sld);
	LAi_GetCharacterMaxEnergy(sld);
	RemovePassenger(pchar, sld);
	sld.SaveItemsForDead = true;
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	
	LAi_SetFightMode(pchar, true);
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
	LAi_group_SetCheck("EnemyFight", "SKD_DomAnri_DuranDraka");
}

void Duran_Duran_DlgExit_4()
{
	LocatorReloadEnterDisable("PortRoyal_houseSp1", "reload2", true);
	chrDisableReloadToLocation = false;
	LAi_LocationDisableOfficersGen("PortRoyal_town", true);
	
	sld = CharacterFromID("Duran");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
	
	PChar.quest.SKD_DomAnri_DuranDruzhba.win_condition.l1 = "location";
	PChar.quest.SKD_DomAnri_DuranDruzhba.win_condition.l1.location = "PortRoyal_town";
	PChar.quest.SKD_DomAnri_DuranDruzhba.win_condition = "SKD_DomAnri_DuranDruzhba";
}

void Duran_Duran_DlgExit_5()
{
	EndQuestMovie();
	locCameraTarget(PChar);
	locCameraFollow();
	LAi_LocationDisableOfficersGen("PortRoyal_town", false);
	chrDisableReloadToLocation = false;
	AddQuestRecord("TheFormerKnight", "3");
	CloseQuestHeader("TheFormerKnight");
	ChangeCharacterComplexReputation(pchar, "nobility", -1);
	
	sld = CharacterFromID("Duran");	//Клод Дюран становится постоянным офицером
	sld.OfficerWantToGo.DontGo = true;
	sld.loyality = MAX_LOYALITY;
	LAi_SetOfficerType(sld);
	sld.Dialog.Filename = "Enc_Officer_dialog.c";
	sld.Dialog.CurrentNode = "hired";
	sld.OfficerImmortal = true;
	sld.Health.HP       = 60.0;
	sld.Health.maxHP    = 60.0;

	pchar.questTemp.SKD_DuranDruzhba = true;
	pchar.questTemp.SKD_DevushkaUbita = true;
	sld.reputation = sti(sld.reputation) - 15;
	OfficersFollow();
}

void Duran_Duran_DlgExit_6()
{
	AddQuestRecord("TheFormerKnight", "2");
	CloseQuestHeader("TheFormerKnight");
	chrDisableReloadToLocation = false;
	ChangeCharacterComplexReputation(pchar, "nobility", 1);
	LocatorReloadEnterDisable("PortRoyal_houseSp1", "reload2", true);
	
	sld = CharacterFromID("Duran");	//Клод Дюран становится постоянным офицером
	sld.OfficerWantToGo.DontGo = true;
	sld.loyality = MAX_LOYALITY;
	LAi_SetOfficerType(sld);
	sld.Dialog.Filename = "Enc_Officer_dialog.c";
	sld.Dialog.CurrentNode = "hired";
	sld.OfficerImmortal = true;
	sld.Health.HP       = 60.0;
	sld.Health.maxHP    = 60.0;

	pchar.questTemp.SKD_DuranDruzhba = true;
	sld.reputation = 60;
	OfficersFollow();
}

//=================================================================
//======================кейсы из quests_reaction===================
//=================================================================
bool Duran_QuestComplete(string sQuestName, string qname)
{
	ref sld;
	string sTemp;
	bool condition = true;
	
	// Sinistra - Событие с Клодом Дюраном ==>
	if (sQuestName == "SKD_DuranTavern") {
		if (CharacterIsAlive("Duran"))
		{
			PChar.quest.SKD_DuranTavern_podhodit.win_condition.l1 = "Location_Type";
			PChar.quest.SKD_DuranTavern_podhodit.win_condition.l1.location_type = "tavern";
			PChar.quest.SKD_DuranTavern_podhodit.win_condition = "SKD_DuranTavern_podhodit";
			pchar.questTemp.SKD_SobytieKlodDuran = true;
			DeleteQuestCondition("SKD_DuranTavern");
		}
	}

	else if (sQuestName == "SKD_DuranTavern_podhodit") {
		if (CharacterIsAlive("Duran"))
		{
			chrDisableReloadToLocation = true;
			sld = CharacterFromID("Duran");
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto2");
			sld.dialog.filename = "Quest\CompanionQuests\Duran.c";
			sld.dialog.currentnode = "SKD_KlodDuran";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			DoQuestCheckDelay("SKD_DuranTavern_podhodit_proverka", 0.5);
		}
	}

	else if (sQuestName == "SKD_DuranTavern_podhodit_proverka") {
		if (loadedLocation.type != "tavern")
		{
			chrDisableReloadToLocation = false;
			PChar.quest.SKD_DuranTavern_podhodit.win_condition.l1 = "Location_Type";
			PChar.quest.SKD_DuranTavern_podhodit.win_condition.l1.location_type = "tavern";
			PChar.quest.SKD_DuranTavern_podhodit.win_condition = "SKD_DuranTavern_podhodit";
		}
	}

	else if (sQuestName == "SKD_DomAnri") {
		if (CharacterIsAlive("Duran"))
		{
			sld = CharacterFromID("Duran");
			ChangeCharacterAddressGroup(sld, "PortRoyal_houseSp1", "reload", "reload2");
			TeleportCharacterToPosAy(sld, -2.64, 1.02, -1.51, 0.50);
			
			sld = GetCharacter(NPC_GenerateCharacter("SKD_Anri", "citiz_12", "man", "man", 25, FRANCE, -1, false, "quest"));
			sld.name = GetCharacterName("Henri");
			sld.lastname = GetCharacterName("d'Aubuisson");
            sTemp = GetGeneratedItem("blade_38");
            GiveItem2Character(sld, sTemp);
            EquipCharacterbyItem(sld, sTemp);
			GiveItem2Character(sld, "pistol2");
			EquipCharacterByItem(sld, "pistol2");
			AddItems(sld, "bullet", rand(10)+20);
			AddItems(sld, "gunpowder", rand(10)+20);
			LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
			GiveItem2Character(sld, "amulet_3");
			GiveItem2Character(sld, "purse1");
			GiveItem2Character(sld, "cirass3");
			EquipCharacterByItem(sld, "cirass3");
			AddItems(sld, "potion4", 5);
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			ForceAutolevel(sld, GEN_TYPE_ENEMY, GEN_BOSS, GEN_ARCHETYPE_RANDOM, GEN_ARCHETYPE_RANDOM, GEN_RANDOM_PIRATES, 0.6);
			ChangeCharacterAddressGroup(sld, "PortRoyal_houseSp1", "barmen", "stay");
			sld.dialog.filename = "Quest\CompanionQuests\Duran.c";
			sld.dialog.currentnode = "SKD_DomAnri";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
			
			sld = GetCharacter(NPC_GenerateCharacter("SKD_Alisia", "Women_13", "woman", "woman", 5, ENGLAND, -1, false, "quest"));
			sld.name = GetCharacterName("Alicia");
			sld.lastname = GetCharacterName("Chardon");
			ChangeCharacterAddressGroup(sld, "PortRoyal_houseSp1", "goto", "goto1");
			LAi_SetActorType(sld);
			
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], true);
			
			PChar.quest.SKD_Vernut.win_condition.l1 = "location";
			PChar.quest.SKD_Vernut.win_condition.l1.location = "PortRoyal_town";
			PChar.quest.SKD_Vernut.win_condition = "SKD_Vernut";
		}
	}

	else if (sQuestName == "SKD_DomAnri_2") {
		sld = CharacterFromID("Duran");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocator(sld, "goto", "goto3", "SKD_DomAnri_3", -1);
		
		LAi_SetActorType(pchar);
		LAi_ActorGoToLocator(pchar, "goto", "goto2", "SKD_DomAnri_4", -1);
	}

	else if (sQuestName == "SKD_DomAnri_3") {
		sld = CharacterFromID("Duran");
		LAi_SetActorType(sld);
		LAi_ActorTurnToLocator(sld, "barmen", "stay");
		
		DoQuestCheckDelay("SKD_DomAnri_5", 1.5);
	}

	else if (sQuestName == "SKD_DomAnri_4") {
		LAi_SetActorType(pchar);
		LAi_ActorTurnToLocator(pchar, "barmen", "stay");
	}

	else if (sQuestName == "SKD_DomAnri_5") {
		LAi_SetPlayerType(pchar);
		sld = CharacterFromID("SKD_Anri");
		sld.dialog.filename = "Quest\CompanionQuests\Duran.c";
		sld.dialog.currentnode = "SKD_DomAnri_6";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
	}

	else if (sQuestName == "SKD_DomAnri_6") {
		sld = CharacterFromID("Duran");
		if (!LAi_IsDead(sld))
		{
			chrDisableReloadToLocation = true;
			DoQuestCheckDelay("hide_weapon", 1.2);
			sld = CharacterFromID("Duran");
			sld.dialog.filename = "Quest\CompanionQuests\Duran.c";
			sld.dialog.currentnode = "SKD_DomAnri_12";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		}
		else
		{
			chrDisableReloadToLocation = false;
			DoQuestCheckDelay("hide_weapon", 1.2);
			LocatorReloadEnterDisable("PortRoyal_houseSp1", "reload2", true);
			CloseQuestHeader("TheFormerKnight");
		}
	}

	else if (sQuestName == "SKD_Vernut") {
		LocatorReloadEnterDisable("PortRoyal_houseSp1", "reload2", false);
	}

	else if (sQuestName == "SKD_DomAnri_DuranDraka") {
		chrDisableReloadToLocation = false;
		DoQuestCheckDelay("hide_weapon", 1.2);
		LocatorReloadEnterDisable("PortRoyal_houseSp1", "reload2", true);
		AddQuestRecord("TheFormerKnight", "4");
		CloseQuestHeader("TheFormerKnight");
	}

	else if (sQuestName == "SKD_DomAnri_DuranDruzhba") {
		LAi_SetActorType(pchar);
		DoQuestCheckDelay("SKD_DomAnri_DuranDruzhba_2", 0.1);
	}

	else if (sQuestName == "SKD_DomAnri_DuranDruzhba_2") {
		StartQuestMovie(true, false, true);
		locCameraFromToPos(-66.07, 6.11, 49.81, false, -60.74, 3.06, 48.80);
		DoQuestCheckDelay("SKD_DomAnri_DuranDruzhba_2_1", 2.0);
	}

	else if (sQuestName == "SKD_DomAnri_DuranDruzhba_2_1") {
		locCameraSleep(true);
		LAi_ActorGoToLocator(pchar, "officers", "houseSp1_3", "SKD_DomAnri_DuranDruzhba_3", -1);
		SetMusic("");
	}

	else if (sQuestName == "SKD_DomAnri_DuranDruzhba_3") {
		DoQuestCheckDelay("SKD_DomAnri_DuranDruzhba_4", 3.0);
	}

	else if (sQuestName == "SKD_DomAnri_DuranDruzhba_4") {
		locCameraSleep(false);
		locCameraFromToPos(-66.07, 6.11, 49.81, false, -59.25, 5.86, 46.70);
		DoQuestCheckDelay("SKD_DomAnri_DuranDruzhba_5", 3.0);
	}

	else if (sQuestName == "SKD_DomAnri_DuranDruzhba_5") {
		PlaySound("People Fight\PistolShot.wav");
		DoQuestCheckDelay("SKD_DomAnri_DuranDruzhba_6", 0.7);
	}

	else if (sQuestName == "SKD_DomAnri_DuranDruzhba_6") {
		//CreateLocationParticles("GunFire", "quest", "effect1", 3.9, -90, -45, "");
		PlaySound("People Fight\Peace_woman_death_02.wav");
		DoQuestCheckDelay("SKD_DomAnri_DuranDruzhba_7", 2.5);
	}

	else if (sQuestName == "SKD_DomAnri_DuranDruzhba_7") {
		locCameraFromToPos(-66.07, 6.11, 49.81, false, -60.74, 3.06, 48.80);
		DoQuestCheckDelay("SKD_DomAnri_DuranDruzhba_8", 3.0);
	}

	else if (sQuestName == "SKD_DomAnri_DuranDruzhba_8") {
		chrDisableReloadToLocation = true;
		LAi_SetPlayerType(pchar);
		sld = CharacterFromID("Duran");
		ChangeCharacterAddressGroup(sld, "PortRoyal_town", "reload", "houseSp1");
		sld.dialog.filename = "Quest\CompanionQuests\Duran.c";
		sld.dialog.currentnode = "SKD_DomAnri_DuranDruzhba_3";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
	}
	// <== Событие с Клодом Дюраном - Sinistra
	else
	{
		condition = false;
	}
	
	return condition;
}