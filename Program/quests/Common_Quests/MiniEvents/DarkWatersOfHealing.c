void DWH_Grot(string qName)
{
	LAi_SetActorType(pchar);
	
	sld = GetCharacter(NPC_GenerateCharacter("DWH_Bandit_1", "citiz_45", "man", "man", sti(pchar.rank), PIRATE, 0, true, "pirate"));
	sld.name = StringFromKey("Neutral_1");
	sld.lastname = "";
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, "Antigua_Grot", "goto", "ass2");
	
	sld = GetCharacter(NPC_GenerateCharacter("DWH_Bandit_2", "citiz_43", "man", "man", sti(pchar.rank), PIRATE, 0, true, "pirate"));
	sld.name = StringFromKey("Neutral_1");
	sld.lastname = "";
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, "Antigua_Grot", "goto", "ass4");
	
	DoQuestFunctionDelay("DWH_Grot_1", 0.1);
}

void DWH_Grot_1(string qName)
{
	StartQuestMovie(true, false, true);
	locCameraFromToPos(2.96, 0.16, 5.80, false, 4.67, -0.90, 0.80);
	LAi_SetStayType(pchar);
	
	sld = CharacterFromID("DWH_Bandit_1");
	sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
	sld.dialog.currentnode = "Bandit_1";
	LAi_ActorDialog(sld, pchar, "", 0, 0);
	
	if (CheckAttribute(pchar, "questTemp.DWH_GoodChoice"))
	{
		Locations[FindLocation(pchar.location)].box1.items.cannabis7 = 3;
		Locations[FindLocation(pchar.location)].box1.items.jewelry3 = 2;
		Locations[FindLocation(pchar.location)].box1.items.jewelry40 = 5;
		Locations[FindLocation(pchar.location)].box1.items.Mineral22 = 2;
		Locations[FindLocation(pchar.location)].box1.items.jewelry52 = 5;
		Locations[FindLocation(pchar.location)].box1.items.jewelry53 = 10;
		Locations[FindLocation(pchar.location)].box1.items.Mineral9 = 10;
		Locations[FindLocation(pchar.location)].box1.items.pistol1 = 1;
		Locations[FindLocation(pchar.location)].box1.items.GunPowder = 10;
		Locations[FindLocation(pchar.location)].box1.items.bullet = 10;
	}
	
	SetFunctionExitFromLocationCondition("DWH_Grot_5", PChar.location, false);
}

void DWH_Grot_2(string qName)
{
	sld = CharacterFromID("DWH_Bandit_1");
	CharacterTurnToLoc(sld, "reload", "reload1");
	sld = CharacterFromID("DWH_Bandit_2");
	CharacterTurnToLoc(sld, "reload", "reload1");
	DoQuestFunctionDelay("DWH_Grot_3", 4.5);
}

void DWH_Grot_3(string qName)
{
	LAi_SetPlayerType(pchar);
	sld = CharacterFromID("DWH_Bandit_1");
	sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
	sld.dialog.currentnode = "Bandit_3";
	LAi_ActorDialog(sld, pchar, "", 0, 0);
}

void DWH_Grot_4(string qName)
{
	chrDisableReloadToLocation = false;
	sld = CharacterFromID("DWH_gypsy");
	LAi_SetStayType(sld);
	sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
	sld.dialog.currentnode = "gypsy_3";
	AddLandQuestMark(sld, "questmarkmain");
	LAi_LocationDisableOfficersGen("Antigua_Grot", false);
	locations[FindLocation("Antigua_Grot")].DisableEncounters = false;
}

void DWH_Grot_5(string qName)
{
	DeleteAttribute(&locations[FindLocation("Antigua_Grot")], "box1");
	DeleteQuestCondition("DWH_VorovstvoSunduk");
}

void DWH_TomasGovotitAgain(string qName)
{
	sld = CharacterFromID("DWH_Tomas");
	sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
	sld.dialog.currentnode = "Tomas_27";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 0, 0);
}

void DWH_GypsyPrigotovilaZelie(string qName)
{
	sld = CharacterFromID("DWH_gypsy");
	LAi_CharacterEnableDialog(sld);
	sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
	sld.dialog.currentnode = "gypsy_31";
	AddLandQuestMark(sld, "questmarkmain");
}

void DWH_Vizdorovela(string qName)	// выздоровела
{
	SetFunctionLocationCondition("DWH_Vizdorovela_2", "SentJons_town", false);
}

void DWH_Vizdorovela_2(string qName)
{
	chrDisableReloadToLocation = true;
	
	sld = CharacterFromID("DWH_Tomas");
	sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
	sld.dialog.currentnode = "Tomas_41";
	ChangeCharacterAddressGroup(sld, "SentJons_town", "quest", "quest1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	
	sld = CharacterFromID("DWH_gypsy");
	LAi_SetCitizenType(sld);
	LAi_CharacterDisableDialog(sld);
	ChangeCharacterAddressGroup(sld, "SentJons_town", "goto", "goto23");
}

void DWH_Vizdorovela_3(string qName)
{
	sld = CharacterFromID("DWH_Tomas");
	sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
	sld.dialog.currentnode = "Tomas_51";
	ChangeCharacterAddressGroup(sld, "SentJons_houseS3", "goto", "goto1");
	LAi_SetStayType(sld);
	LAi_CharacterEnableDialog(sld);
}

void DWH_Tomas_HelloAgain(string qName)
{
	sld = CharacterFromID("DWH_Tomas");
	sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
	sld.dialog.currentnode = "Tomas_51";
}

void DWH_Mangarosa(string qName)	// через 30 дней можно снова покупать мангаросу
{
	pchar.questTemp.DWH_Mangarosa = true;
	Log_TestInfo("Цыганка в Сент-Джонсе снова готова продать мангаросу");
}

void DWH_VorovstvoSunduk(string qName)
{
	chrDisableReloadToLocation = true;
	DoQuestCheckDelay("DWH_Podkreplenie", 3.5);
	for (i=1; i<=2; i++)
	{
		sld = CharacterFromID("DWH_Bandit_"+i);
		LAi_RemoveCheckMinHP(sld);
	}
}

bool DarkWatersOfHealing_QuestComplete(string sQuestName, string qname)
{
	ref sld;
	
	bool condition = true;
	
	if (sQuestName == "DWH_Podkreplenie")
	{
		DeleteQuestCondition("DWH_Podkreplenie");
		DeleteQuestCondition("DWH_VorovstvoSunduk");
		chrDisableReloadToLocation = true;
		for (i=1; i<=2; i++)
		{
			sld = CharacterFromID("DWH_Bandit_"+i);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		for (i=3; i<=4; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("DWH_Bandit_"+i, "citiz_48", "man", "man", sti(pchar.rank), PIRATE, 0, true, "pirate"));
			if (i==4) sld.model = "citiz_49";
			ChangeCharacterAddressGroup(sld, "Antigua_Grot", "reload", "reload1");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}	
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		LAi_group_SetCheckFunction("EnemyFight", "DWH_Grot_4");
	}
	else
	{
		condition = false;
	}
	
	return condition;
}