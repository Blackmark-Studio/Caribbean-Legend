void LFD_Sailor_end()
{
	sld = CharacterFromID("LFD_sailor");
	sld.lifeday = 0;
	LAi_CharacterDisableDialog(sld);
	CloseQuestHeader("LFD");
}

void LFD_Sailor_accept()
{
	sld = CharacterFromID("LFD_sailor");
	sld.lifeday = 0;
	LAi_CharacterDisableDialog(sld);
	
	pchar.questTemp.LFD_Tavern_1 = true;
	AddLandQuestMark(characterFromId("PortoBello_tavernkeeper"), "questmarkmain");
}

void LFD_Tavern_1()
{
	AddQuestRecord("LFD", "3");
	DeleteAttribute(pchar, "questTemp.LFD_Tavern_1");
	
	pchar.questTemp.LFD_Church_1 = true;
	AddLandQuestMark(characterFromId("PortoBello_priest"), "questmarkmain");
}

void LFD_Church_1()
{
	AddQuestRecord("LFD", "4");
	DeleteAttribute(pchar, "questTemp.LFD_Church_1");
	
	sld = GetCharacter(NPC_GenerateCharacter("LFD_Dolores", "girl_6", "woman", "woman", 5, SPAIN, -1, false, "quest"));
	sld.name = StringFromKey("Neutral_25");
	sld.lastname = StringFromKey("Neutral_26");
	sld.City = "PortoBello";
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	sld.dialog.filename = "Quest\MiniEvents\LetterFromDeadman_dialog.c";
	sld.dialog.currentnode = "Dolores_1";
	LAi_SetStayType(sld);
	ChangeCharacterAddressGroup(sld, "PortoBello_houseSp1", "barmen", "stay");
	AddLandQuestMark(sld, "questmarkmain");
}

void LFD_Dolores_1()
{
	AddQuestRecord("LFD", "5");
	
	sld = CharacterFromID("LFD_Dolores");
	LAi_CharacterDisableDialog(sld);
	
	SetTimerFunction("LFD_Dolores_2", 0, 0, 1);
}

void LFD_Dolores_2(string qName)
{
	sld = GetCharacter(NPC_GenerateCharacter("LFD_Marisa", "girl_5", "woman", "woman", 5, SPAIN, -1, false, "quest"));
	sld.name = StringFromKey("Neutral_27");
	sld.lastname = StringFromKey("Neutral_28");
	sld.City = "PortoBello";
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	sld.dialog.filename = "Quest\MiniEvents\LetterFromDeadman_dialog.c";
	sld.dialog.currentnode = "Marisa_1";
	LAi_SetStayType(sld);
	ChangeCharacterAddressGroup(sld, "PortoBello_houseSp1", "goto", "goto1");
	AddLandQuestMark(sld, "questmarkmain");
	LAi_SetLoginTime(sld, 23.0, 23.99);
	LAi_SetImmortal(sld, true);
}

void LFD_Dolores_3(string qName)
{
	sld = CharacterFromID("LFD_Marisa");
	sld.dialog.filename = "Quest\MiniEvents\LetterFromDeadman_dialog.c";
	sld.dialog.currentnode = "Marisa_11";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void LFD_Marisa_end()
{
	CloseQuestHeader("LFD");
	sld = CharacterFromID("LFD_Marisa");
	sld.lifeday = 0;
	LAi_CharacterDisableDialog(sld);
	sld = CharacterFromID("LFD_Dolores");
	sld.lifeday = 0;
	LAi_CharacterDisableDialog(sld);
}

void LFD_Marisa_1()
{
	AddQuestRecord("LFD", "6");
	sld = CharacterFromID("LFD_Marisa");
	sld.dialog.filename = "Quest\MiniEvents\LetterFromDeadman_dialog.c";
	sld.dialog.currentnode = "Marisa_21";
	LAi_RemoveLoginTime(sld);
	sld = CharacterFromID("LFD_Dolores");
	sld.lifeday = 0;
	LAi_CharacterDisableDialog(sld);
}

void LFD_Marisa_2()
{
	QuestCloseSeaExit();
	Pchar.GenQuest.Hunter2Pause = true;
	locations[FindLocation("PortoBello_cave")].DisableEncounters = true;
	LAi_LocationFightDisable(&Locations[FindLocation("PortoBello_cave")], true);
	
	sld = CharacterFromID("LFD_Marisa");
	LAi_SetActorType(sld);
	LAi_ActorFollowEverywhere(sld, "", -1);
	
	SetFunctionLocationCondition("LFD_Marisa_3", "PortoBello_cave", false);
	SetFunctionLocationCondition("LFD_Ne_Ta_Peshera", "Panama_Cave", false);
}

void LFD_Marisa_3(string qName)
{
	chrDisableReloadToLocation = true;
	
	sld = CharacterFromID("LFD_Marisa");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	sld.dialog.filename = "Quest\MiniEvents\LetterFromDeadman_dialog.c";
	sld.dialog.currentnode = "Marisa_31";
}

void LFD_Marisa_4()
{
	sld = CharacterFromID("LFD_Marisa");
	LAi_ActorFollow(sld, pchar, "", -1);
	
	ref sld = &locations[FindLocation("PortoBello_cave")];
	sld.box1 = Items_MakeTime(0, 0, 0, 2025);
	sld.box1.items.gold_dublon = 400;
	sld.box1.items.mushket1 = 1;
	sld.box1.items.jewelry2 = 10;
	sld.box1.items.jewelry3 = 10;
	sld.box1.items.obereg_7 = 1;
	sld.box1.items.amulet_11 = 1;
	
	SetFunctionLocatorCondition("LFD_Marisa_5", "PortoBello_cave", "box", "box1", false)
}

void LFD_Ne_Ta_Peshera(string qName)
{	
	sld = CharacterFromID("LFD_Marisa");
	sld.dialog.currentnode = "Marisa_Ne_Ta_Peshera";
	ChangeCharacterAddressGroup(sld, "Panama_Cave", "officers", "reload1_1");
	DoQuestFunctionDelay("LFD_Ne_Ta_Peshera_1", 0.5);
}

void LFD_Ne_Ta_Peshera_1(string qName)
{	
	sld = CharacterFromID("LFD_Marisa");
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	
}

void LFD_Marisa_5(string qName)
{
	DoQuestFunctionDelay("LFD_Marisa_5_1", 5.0);
	DeleteQuestCondition("LFD_Ne_Ta_Peshera");
}

void LFD_Marisa_5_1(string qName)
{
	sld = CharacterFromID("LFD_Marisa");
	LAi_SetStayType(sld);
	sld.dialog.filename = "Quest\MiniEvents\LetterFromDeadman_dialog.c";
	sld.dialog.currentnode = "Marisa_32";
	AddLandQuestMark(sld, "questmarkmain");
}

void LFD_Marisa_6()
{
	LAi_LocationFightDisable(loadedLocation, true);
	
	sld = GetCharacter(NPC_GenerateCharacter("LFD_Naemnik", "citiz_58", "man", "man", sti(pchar.rank), PIRATE, -1, true, "hunter"));
	sld.dialog.filename = "Quest\MiniEvents\LetterFromDeadman_dialog.c";
	sld.dialog.currentnode = "Naemnik_1";
	ChangeCharacterAddressGroup(sld, "PortoBello_cave", "reload", "reload1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	
	sld = CharacterFromID("LFD_Marisa");
	LAi_SetActorType(sld);
	LAi_ActorFollow(sld, pchar, "", -1);
}

void LFD_Naemnik_bitva()
{
	LAi_LocationFightDisable(loadedLocation, false);
	LAi_SetFightMode(pchar, true);
	
	sld = CharacterFromID("LFD_Naemnik");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	
	sld = CharacterFromID("LFD_Marisa");
	LAi_SetActorType(sld);
	LAi_ActorAfraid(sld, Pchar, true);
	
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
	LAi_group_SetCheckFunction("EnemyFight", "LFD_Naemnik_bitva_2");
}

void LFD_Naemnik_bitva_2(string qName)
{
	sld = CharacterFromID("LFD_Marisa");
	sld.dialog.filename = "Quest\MiniEvents\LetterFromDeadman_dialog.c";
	sld.dialog.currentnode = "Marisa_41";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void LFD_Naemnik_bitva_3()
{
	chrDisableReloadToLocation = false;
	sld = CharacterFromID("LFD_Marisa");
	LAi_SetActorType(sld);
	LAi_ActorFollowEverywhere(sld, "", -1);
	AddQuestRecord("LFD", "7");
	SetFunctionLocationCondition("LFD_Finish_In_Town_NaemnikDead", "PortoBello_town", false);
}

void LFD_Finish_In_Town_NaemnikDead(string qName)
{
	chrDisableReloadToLocation = true;
	sld = CharacterFromID("LFD_Marisa");
	sld.dialog.filename = "Quest\MiniEvents\LetterFromDeadman_dialog.c";
	sld.dialog.currentnode = "Marisa_51";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	
	pchar.questTemp.LFD_NaemnikDead = true;
}

void LFD_Naemnik_mir()
{
	LAi_LocationFightDisable(loadedLocation, false);
	chrDisableReloadToLocation = false;
	sld = CharacterFromID("LFD_Marisa");
	LAi_SetActorType(sld);
	LAi_ActorFollowEverywhere(sld, "", -1);
	AddQuestRecord("LFD", "8");
	SetFunctionLocationCondition("LFD_Finish_In_Town_NaemnikAlive", "PortoBello_town", false);
}

void LFD_Finish_In_Town_NaemnikAlive(string qName)
{
	chrDisableReloadToLocation = true;
	sld = CharacterFromID("LFD_Marisa");
	sld.dialog.filename = "Quest\MiniEvents\LetterFromDeadman_dialog.c";
	sld.dialog.currentnode = "Marisa_54";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void LFD_Finish_In_Town_NaemnikAlive_2(string qName)
{
	SetLaunchFrameFormParam(GetConvertStr("Frame_HourPassed", "Frame.txt"), "Run_Function", 0, 4.0);
	SetLaunchFrameRunFunctionParam("LFD_Finish_In_Town_NaemnikAlive_3", 0.0);
	LaunchFrameForm();
}

void LFD_Finish_In_Town_NaemnikAlive_3(string qName)
{
	sld = CharacterFromID("LFD_Marisa");
	sld.dialog.filename = "Quest\MiniEvents\LetterFromDeadman_dialog.c";
	sld.dialog.currentnode = "Marisa_55";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 0, 0);
}

void LFD_Marisa_In_Church()
{
	chrDisableReloadToLocation = false;
	sld = CharacterFromID("LFD_Marisa");
	LAi_SetCitizenType(sld);
	LAi_CharacterDisableDialog(sld);
	
	CloseQuestHeader("LFD");
	QuestOpenSeaExit();
	SetFunctionExitFromLocationCondition("LFD_Marisa_In_Church_2", PChar.location, false);
}

void LFD_Marisa_In_Church_2(string qName)
{
	sld = CharacterFromID("LFD_Marisa");
	LAi_CharacterEnableDialog(sld);
	sld.dialog.filename = "Quest\MiniEvents\LetterFromDeadman_dialog.c";
	sld.dialog.currentnode = "Marisa_61";
	LAi_SetStayType(sld);
	LAi_SetLoginTime(sld, 8.0, 11.99);
	ChangeCharacterAddressGroup(sld, "PortoBello_Church", "goto", "prosper");
}

void LFD_Marisa_HelloAgain(string qName)
{
	sld = CharacterFromID("LFD_Marisa");
	sld.dialog.filename = "Quest\MiniEvents\LetterFromDeadman_dialog.c";
	sld.dialog.currentnode = "Marisa_61";
}

