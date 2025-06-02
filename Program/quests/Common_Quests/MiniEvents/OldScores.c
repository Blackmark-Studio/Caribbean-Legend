void OS_ShipWolf(string qName)
{
	sld = GetCharacter(NPC_GenerateCharacter("OS_Pirate", "mercen_11", "man", "man", sti(PChar.rank), PIRATE, -1, true, "pirate"));
	FantomMakeSmallSailor(sld, SHIP_BRIG, StringFromKey("Neutral_5"), CANNON_TYPE_CANNON_LBS16, 40, 40, 40, 40, 40);
	LAi_SetHP(sld, 200.0, 200.0);
	sld.AlwaysFriend = true;
	sld.ShipEnemyDisable  = true;
	LAi_SetImmortal(sld, true);
	sld.AlwaysSandbankManeuver = true;
	sld.DontRansackCaptain = true;
	sld.DontDeskTalk = true;
	
	Group_FindOrCreateGroup("OS_AttackSea");
	Group_SetType("OS_AttackSea", "pirate");
	Group_AddCharacter("OS_AttackSea", "OS_Pirate");
	Group_SetGroupCommander("OS_AttackSea", "OS_Pirate");
	Group_SetTaskNone("OS_AttackSea");
	Group_SetAddress("OS_AttackSea", "Cuba1", "Quest_Ships", "Quest_Ship_10");
	
	for (i=2; i<=3; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("OS_Matros_"+i, "citiz_3"+i, "man", "man", sti(pchar.rank), PIRATE, -1, true, "pirate"));
		sld.dialog.filename = "Quest\MiniEvents\OldScores_dialog.c";
		sld.dialog.currentnode = "OS_Matros_sluh";
		sld.City = "PuertoPrincipe";
		ChangeCharacterAddressGroup(sld, "PuertoPrincipe_town", "goto", "goto"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
	}
}

void OS_Zasada(string qName)
{
	chrDisableReloadToLocation = true;
	
	sld = GetCharacter(NPC_GenerateCharacter("OS_Jack", "mercen_8", "man", "man", sti(pchar.rank), PIRATE, 0, true, "pirate"));
	sld.name = StringFromKey("Neutral_3");
	sld.lastname = StringFromKey("Neutral_4");
	ChangeCharacterAddressGroup(sld, "PuertoPrincipe_QuestHouse_1", "reload", "reload2");
	TeleportCharacterToPosAy(sld, 0.00, 0.00, -2.15, 2.00);
	LAi_SetActorType(sld);
	LAi_ActorFollow(sld, pchar, "", -1);
	
	sld = GetCharacter(NPC_GenerateCharacter("OS_capWolf", "mercen_15", "man", "man", sti(pchar.rank), PIRATE, 0, true, "pirate"));
	ChangeCharacterAddressGroup(sld, "PuertoPrincipe_QuestHouse_1", "reload", "reload1");
	TeleportCharacterToPosAy(sld, 0.40, 0.00, -1.40, 2.80);
	sld.dialog.filename = "Quest\MiniEvents\OldScores_dialog.c";
	sld.dialog.currentnode = "OS_Dialog_1";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void OS_VernuliBochonok(string qName)
{
	chrDisableReloadToLocation = false;
	
	pchar.questTemp.OS_Tavern_3 = true;
	AddLandQuestMark(characterFromId("PuertoPrincipe_tavernkeeper"), "questmarkmain");
	
	sld = CharacterFromID("PuertoPrincipe_waitress");
	ChangeCharacterAddressGroup(sld, "none", "", "");
}

void OS_RazgovorTavern(string qName)
{
	sld = CharacterFromID("PuertoPrincipe_tavernkeeper");
	sld.dialog.filename = "Quest\MiniEvents\OldScores_dialog.c";
	sld.dialog.currentnode = "Tavern_1";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 0, 0);
}

void OS_AttackSea(string qName)
{
	bQuestDisableMapEnter = true;
	Island_SetReloadEnableGlobal("Cuba1", false);
	DoQuestFunctionDelay("OS_AttackSea_2", 3.0);
}

void OS_AttackSea_2(string qName)
{
	Log_Info(StringFromKey("Neutral_11"));
	PlaySound("interface\notebook.wav");
}

void OS_Pobeda(string qName)
{
	AddQuestRecordInfo("Useful_Acquaintances", "6");
	AddQuestRecord("OS", "6");
	CloseQuestHeader("OS");
	bQuestDisableMapEnter = false;
	Island_SetReloadEnableGlobal("Cuba1", true);
	
	sld = CharacterFromID("PuertoPrincipe_waitress");
	ChangeCharacterAddressGroup(sld, "PuertoPrincipe_tavern", "waitress", "barmen");
}

