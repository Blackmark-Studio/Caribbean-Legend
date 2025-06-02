void UV_GoldSeagull(string qName)
{
	AddQuestRecord("UV", "3");
	
	Group_FindOrCreateGroup("UV_GoldSeagull_Group");
	Group_SetType("UV_GoldSeagull_Group", "trade");
	sld = GetCharacter(NPC_GenerateCharacter("UV_GoldSeagull_starpom", "mercen_7", "man", "man", 10, FRANCE, -1, false, "pirate"));
	sld.dialog.filename = "Quest\MiniEvents\StolenMemory_dialog.c";
	sld.DeckDialogNode = "Starpom_1";
	FantomMakeCoolSailor(sld, SHIP_FLEUT, StringFromKey("Neutral_8"), CANNON_TYPE_CANNON_LBS12, 40, 40, 40);
	FantomMakeCoolFighter(sld, 10, 40, 40, "blade_10", "pistol1", "bullet", 50);
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.Ship.Mode = "trade";
	sld.Abordage.Enable = true;
	sld.AlwaysFriend = true;
	sld.ShipEnemyDisable = true; 
	LAi_SetImmortal(sld, true);
	AddLandQuestMark(sld, "questmarkmain");
	Group_AddCharacter("UV_GoldSeagull_Group", "UV_GoldSeagull_starpom");
	Group_SetGroupCommander("UV_GoldSeagull_Group", "UV_GoldSeagull_starpom");
	Group_SetTaskNone("UV_GoldSeagull_Group");
	Group_SetAddress("UV_GoldSeagull_Group", "Hispaniola2", "quest_ships", "quest_ship_1");
	Group_LockTask("UV_GoldSeagull_Group");
}

void UV_GoldSeagull_RasprashivaemZhiteley(string qName)
{
	AddQuestRecord("UV", "4");
	pchar.questTemp.UV_DialogCitizen = true;
	AddLandQuestMark(CharacterFromID("PortPax_tavernkeeper"), "questmarkmain");
}

void UV_GoldSeagull_RoomInTavern(string qName)
{
	DeleteAttribute(pchar, "questTemp.UV_DialogCitizen");
	LocatorReloadEnterDisable("PortPax_tavern", "reload2_back", false);
	
	sld = GetCharacter(NPC_GenerateCharacter("UV_GoldSeagull_cap", "mercen_1", "man", "man", 15, PIRATE, -1, false, "quest"));
	sld.name = StringFromKey("Neutral_9"));
	sld.lastname = StringFromKey("Neutral_10"));
	FantomMakeCoolFighter(sld, 15, 50, 50, "blade_15", "pistol1", "bullet", 50);
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	GiveItem2Character(sld, "SM_necklace_Julie");
	sld.dialog.filename = "Quest\MiniEvents\StolenMemory_dialog.c";
	sld.dialog.currentnode = "Captain_1";
	ChangeCharacterAddressGroup(sld, "PortPax_tavern_upstairs", "goto", "goto1");
	LAi_SetStayType(sld);
	LAi_SetImmortal(sld, true);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
	AddLandQuestMark(sld, "questmarkmain");
}

void UV_Ozherelie(string qName)
{
	AddQuestRecord("UV", "5");
	LocatorReloadEnterDisable("PortPax_tavern", "reload2_back", true);
	
	sld = CharacterFromID("UV_Juli");
	AddLandQuestMark(sld, "questmarkmain");
	sld = CharacterFromID("PortPax_Mayor");
	AddLandQuestMark(sld, "questmarkmain");
	
	pchar.questTemp.UV_DialogMayor = true;
	
	if (CharacterIsAlive("UV_GoldSeagull_cap"))
	{
		sld = CharacterFromID("UV_GoldSeagull_cap");
		sld.lifeday = 0;
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
	}
	
	if (CharacterIsAlive("UV_GoldSeagull_starpom"))
	{
		sld = CharacterFromID("UV_GoldSeagull_starpom");
		sld.lifeday = 0;
	}
}

void UV_Ozherelie_Duel(string qName)
{
	LAi_SetFightMode(pchar, true);
	sld = CharacterFromID("UV_GoldSeagull_cap");
	LAi_SetImmortal(sld, false);
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
	LAi_group_SetCheckFunction("EnemyFight", "UV_Ozherelie");
}

void UV_Juli_GoodEnd(string qName)
{
	pchar.questTemp.UV_ojerelie_Julie = true;
	AddQuestRecord("UV", "6");
	AddQuestUserData("UV", "sSex", GetSexPhrase("","а"));
	CloseQuestHeader("UV");
	
	sld = CharacterFromID("PortPax_Mayor");
	DelLandQuestMark(sld);
	DeleteAttribute(pchar, "questTemp.UV_DialogMayor");
	
	sld = CharacterFromID("UV_Juli");
	LAi_CharacterDisableDialog(sld);	
	SetFunctionExitFromLocationCondition("UV_JuliInResidensia", PChar.location, false);
}

void UV_End(string qName)
{
	CloseQuestHeader("UV");
	
	sld = CharacterFromID("PortPax_Mayor");
	DelLandQuestMark(sld);
	DeleteAttribute(pchar, "questTemp.UV_DialogMayor");
	
	SetFunctionExitFromLocationCondition("UV_JuliInResidensia", PChar.location, false);
}

void UV_JuliInResidensia(string qName)
{
	sld = CharacterFromID("UV_Juli");
	LAi_CharacterEnableDialog(sld);
	sld.dialog.filename = "Quest\MiniEvents\StolenMemory_dialog.c";
	sld.dialog.currentnode = "Juli_31";
	ChangeCharacterAddressGroup(sld, "PortPax_townhall", "goto", "goto5");
	DelLandQuestMark(sld);
}

void UV_Julie_HelloAgain(string qName)
{
	sld = CharacterFromID("UV_Juli");
	sld.dialog.filename = "Quest\MiniEvents\StolenMemory_dialog.c";
	sld.dialog.currentnode = "Juli_31";
}