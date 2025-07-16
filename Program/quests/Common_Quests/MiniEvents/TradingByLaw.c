void TPZ_SpawnShip(string qName)
{
	sld = CharacterFromID("TPZ_Kristian");
	LAi_CharacterDisableDialog(sld);
	AddQuestRecord("TPZ", "8");
	AddQuestRecordInfo("Useful_Acquaintances", "4");
	
	PChar.quest.TPZ_AttackSea.win_condition.l1 = "location";
	PChar.quest.TPZ_AttackSea.win_condition.l1.location = "Guadeloupe";
	PChar.quest.TPZ_AttackSea.function = "TPZ_AttackSea";
	
	sld = GetCharacter(NPC_GenerateCharacter("TPZ_Pirate", "mercen_17", "man", "man", sti(PChar.rank), PIRATE, -1, true, "pirate"));
	FantomMakeSmallSailor(sld, SHIP_BRIG, "", CANNON_TYPE_CANNON_LBS16, 40, 40, 40, 40, 40);
	LAi_SetHP(sld, 200.0, 200.0);
	sld.AlwaysEnemy = true;
	sld.AlwaysSandbankManeuver = true;
	sld.DontRansackCaptain = true;
	
	Group_FindOrCreateGroup("TPZ_AttackSea");
	Group_SetType("TPZ_AttackSea", "pirate");
	Group_AddCharacter("TPZ_AttackSea", "TPZ_Pirate");

	Group_SetGroupCommander("TPZ_AttackSea", "TPZ_Pirate");
	Group_SetTaskAttack("TPZ_AttackSea", PLAYER_GROUP);
	Group_SetAddress("TPZ_AttackSea", "Guadeloupe", "Quest_Ships", "reload_fort1_siege");
	Group_LockTask("TPZ_AttackSea");
	
	PChar.quest.TPZ_Potopil.win_condition.l1 = "Character_sink";
	PChar.quest.TPZ_Potopil.win_condition.l1.character = "TPZ_Pirate";
	PChar.quest.TPZ_Potopil.function = "TPZ_Potopil";	
	PChar.quest.TPZ_Abordage.win_condition.l1 = "Character_Capture";
	PChar.quest.TPZ_Abordage.win_condition.l1.character = "TPZ_Pirate";
	PChar.quest.TPZ_Abordage.function = "TPZ_Abordage";
}

void TPZ_AttackSea(string qName)
{
	bQuestDisableMapEnter = true;
	Island_SetReloadEnableGlobal("Guadeloupe", false);
	
	Log_Info(StringFromKey("Neutral_20"));
	PlaySound("interface\notebook.wav");
}

void TPZ_Abordage(string qName)
{
	DeleteQuestCondition("TPZ_Potopil");
	AddQuestRecord("TPZ", "9");
	AddQuestUserData("TPZ", "sSex", GetSexPhrase("","а"));
	CloseQuestHeader("TPZ");
	bQuestDisableMapEnter = false;
	Island_SetReloadEnableGlobal("Guadeloupe", true);
	
	sld = CharacterFromID("TPZ_Kristian");
	LAi_CharacterEnableDialog(sld);
	sld.dialog.filename = "Quest\MiniEvents\TradingByLaw_dialog.c";
	sld.dialog.currentnode = "Kristian_41";
	pchar.questTemp.TPZ_TradeVinoAndRom = true;
}

void TPZ_Potopil(string qName)
{
	DeleteQuestCondition("TPZ_Abordage");
	AddQuestRecord("TPZ", "10");
	CloseQuestHeader("TPZ");
	bQuestDisableMapEnter = false;
	Island_SetReloadEnableGlobal("Guadeloupe", true);
	
	sld = CharacterFromID("TPZ_Kristian");
	LAi_CharacterEnableDialog(sld);
	sld.dialog.filename = "Quest\MiniEvents\TradingByLaw_dialog.c";
	sld.dialog.currentnode = "Kristian_41";
	pchar.questTemp.TPZ_TradeVinoAndRom = true;
}

void TPZ_KristianReturn(string qName)
{
	pchar.questTemp.TPZ_TradeVinoAndRom = true;
}

void TPZ_GoToPogreb(string qName)
{
	DoFunctionReloadToLocation("BasTer_WineCellar", "reload", "reload1", "TPZ_GoToPogreb_2");
}

void TPZ_GoToPogreb_2(string qName)
{
	TeleportCharacterToPosAy(pchar, 1.12, -2.83, 1.07, -1.50);
	sld = CharacterFromID("TPZ_Kristian");
	sld.dialog.filename = "Quest\MiniEvents\TradingByLaw_dialog.c";
	sld.dialog.currentnode = "Kristian_15";
	ChangeCharacterAddressGroup(sld, "BasTer_WineCellar", "goto", "goto3");
	LAi_SetActorType(sld);
	TeleportCharacterToPosAy(sld, -1.78, -2.83, 1.80, 1.50);
	LAi_ActorDialog(sld, pchar, "", 0, 0);
}