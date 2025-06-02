void GS_Peshera(string qName)
{
	chrDisableReloadToLocation = true;
	
	sld = GetCharacter(NPC_GenerateCharacter("GS_Naemnik", "citiz_60", "man", "man", sti(pchar.rank), PIRATE, -1, false, "pirate"));
	FantomMakeCoolFighter(sld, sti(pchar.rank), 30, 30, "blade_15", "pistol6", "bullet", 60);
	ChangeCharacterAddressGroup(sld, "Beliz_Cave", "goto", "goto5");
	LAi_SetCheckMinHP(sld, 1, true, "GS_NaemnikRazgovor");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	AddItems(sld, "potion1", 4);
	AddItems(sld, "potion2", 4);
	AddItems(sld, "potion3", 1);
	AddItems(sld, "bullet", 30);
	AddItems(sld, "GunPowder", 30);
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	
	LAi_SetFightMode(pchar, true);
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
	DeleteQuestCondition("GS_Peshera_pusto");
}

void GS_UbivaemNaemnika(string qName)
{
	chrDisableReloadToLocation = false;
	locations[FindLocation("Beliz_Cave")].DisableEncounters = false;
	AddQuestRecord("GS", "3");
	pchar.questTemp.GS_NaemnikMertv = true;
	AddLandQuestMark(characterFromId("Beliz_portman"), "questmarkmain");
}

void GS_SoldatyDoma(string qName)
{
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(loadedLocation, false);
	LAi_SetFightMode(pchar, true);
	
	for (i=1; i<=2; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("GS_soldier_"+i, "sold_eng_"+(rand(7)+1), "man", "man", sti(pchar.rank), ENGLAND, 0, true, "soldier"));
		ChangeCharacterAddressGroup(sld, "Beliz_houseS5", "goto", "goto1");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
	LAi_group_SetCheckFunction("EnemyFight", "GS_SoldatyDoma_2");
}

void GS_SoldatyDoma_2(string qName)
{
	chrDisableReloadToLocation = false;
	LocatorReloadEnterDisable("Beliz_houseS5", "reload1", true);
	LocatorReloadEnterDisable("Beliz_houseS5", "reload4", true);
	ChangeCharacterNationReputation(pchar, ENGLAND, -2);
	
	PChar.quest.GS_Naverh.win_condition.l2 = "location";
	PChar.quest.GS_Naverh.win_condition.l2.location = "Beliz_houseS5_room2";
	PChar.quest.GS_Naverh.function = "GS_Naverh";
}

void GS_Naverh(string qName)
{
	chrDisableReloadToLocation = true;
	
	sld = GetCharacter(CreateCharacterClone(CharacterFromID("Beliz_portman"), -1));
	sld.id = "Beliz_portman_clone";
	FantomMakeCoolFighter(sld, sti(pchar.rank), 50, 50, "blade_04", "pistol1", "bullet", 50);
	ChangeCharacterAddressGroup(sld, "Beliz_houseS5_room2", "goto", "goto1");
	sld.dialog.filename = "Quest\MiniEvents\EdgesJustice_dialog.c";
	sld.dialog.currentnode = "Portman_1";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
}

void GS_PortmanDead(string qName)
{
	if (CheckAttribute(pchar, "questTemp.GS_Proverka"))
	{
		LocatorReloadEnterDisable("Beliz_houseS5", "reload1", false);
		LocatorReloadEnterDisable("Beliz_houseS5", "reload4", false);
		LAi_LocationFightDisable(&Locations[FindLocation("Beliz_houseS5")], false);
		LAi_LocationFightDisable(&Locations[FindLocation("Beliz_houseS5_room2")], false);
		chrDisableReloadToLocation = false;
		
		PChar.quest.GS_Peshera.win_condition.l1 = "location";
		PChar.quest.GS_Peshera.win_condition.l1.location = "Beliz_Cave";
		PChar.quest.GS_Peshera.function = "GS_Spravedlivost";
		locations[FindLocation("Beliz_Cave")].DisableEncounters = true;
		
		sld = &Locations[FindLocation("Beliz_town")];
		sld.reload.l11.open_for_night = 0;
	}
	else pchar.questTemp.GS_Proverka = true;
	
	AddQuestRecord("GS", "6");
	
	sld = CharacterFromID("Beliz_portman");
	sld.model = "citiz_14";
	SetRandomNameToCharacter(sld);
	sld.quest.meeting = "0"
}

void GS_PolozhilZapiski()
{
	if (CheckAttribute(pchar, "questTemp.GS_Proverka"))
	{
		LocatorReloadEnterDisable("Beliz_houseS5", "reload1", false);
		LocatorReloadEnterDisable("Beliz_houseS5", "reload4", false);
		LAi_LocationFightDisable(&Locations[FindLocation("Beliz_houseS5")], false);
		LAi_LocationFightDisable(&Locations[FindLocation("Beliz_houseS5_room2")], false);
		chrDisableReloadToLocation = false;
		
		PChar.quest.GS_Peshera.win_condition.l1 = "location";
		PChar.quest.GS_Peshera.win_condition.l1.location = "Beliz_Cave";
		PChar.quest.GS_Peshera.function = "GS_Spravedlivost";
		locations[FindLocation("Beliz_Cave")].DisableEncounters = true;
		
		sld = &Locations[FindLocation("Beliz_town")];
		sld.reload.l11.open_for_night = 0;
	}
	else pchar.questTemp.GS_Proverka = true;
	
	Log_Info(StringFromKey("Neutral_2"));
	PlaySound("interface\important_item.wav");
}

void GS_Spravedlivost(string qName)
{
	chrDisableReloadToLocation = true;
	
	sld = CharacterFromID("GS_Naemnik");
	sld.dialog.filename = "Quest\MiniEvents\EdgesJustice_dialog.c";
	sld.dialog.currentnode = "Naemnik_21";
	ChangeCharacterAddressGroup(sld, "Beliz_Cave", "goto", "goto5");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
}

void GS_Peshera_pusto(string qName)
{	
	notification(StringFromKey("Neutral_22"), "NONE");
	PlaySound("interface\notebook.wav");
}

void GS_Spravedlivost_2(string qName)
{
	sld = CharacterFromID("GS_Naemnik");
	sld.dialog.filename = "Quest\MiniEvents\EdgesJustice_dialog.c";
	sld.dialog.currentnode = "Naemnik_27";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 0, 0);
}

bool EdgesJustice_QuestComplete(string sQuestName, string qname)
{
	ref sld;
	
	bool condition = true;
	
	if (sQuestName == "GS_NaemnikRazgovor")
	{
		DoQuestCheckDelay("hide_weapon", 1.2);
		
		sld = CharacterFromID("GS_Naemnik");
		sld.dialog.filename = "Quest\MiniEvents\EdgesJustice_dialog.c";
		sld.dialog.currentnode = "Naemnik";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	else
	{
		condition = false;
	}
	
	return condition;
}