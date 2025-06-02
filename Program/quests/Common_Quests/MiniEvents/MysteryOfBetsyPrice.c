void TBP_Poorman(string qName)
{
	DeleteAttribute(pchar, "questTemp.TBP_Tavern");
	bDisableFastReload = true;
	AddQuestRecord("TBP", "2");
	AddQuestUserData("TBP", "sSex", GetSexPhrase("ся","ась"));
	SetFunctionLocationCondition("TBP_Poorman_2", "Villemstad_town", false);
}

void TBP_Poorman_2(string qName)
{
	chrDisableReloadToLocation = true;
	
	if (CharacterIsAlive("Villemstad_Poorman"))
	{
		sld = CharacterFromID("Villemstad_Poorman");
	}
	else
	{
		sld = GetCharacter(NPC_GenerateCharacter("Villemstad_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, HOLLAND, -1, false, "slave"));
	}
	//LAi_RemoveLoginTime(sld);
	sld.dialog.filename = "Quest\MiniEvents\MysteryOfBetsyPrice_dialog.c";
	sld.dialog.currentnode = "Poorman_1";
	ChangeCharacterAddressGroup(sld, "Villemstad_town", "goto", "goto9");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void TBP_Poorman_reset(string qName)
{
	sld = CharacterFromID("Villemstad_Poorman");
	sld.city = "Villemstad";
	sld.location	= "Villemstad_town";
	sld.location.group = "goto";
	sld.location.locator = "goto16";
	sld.forStay.locator = "goto16";
	sld.forSit.locator0 = "goto12";
	sld.forSit.locator1 = "goto22";
	sld.forSit.locator2 = "goto30";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "poorman_male";
	LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
}

void TBP_PismoVDome(string qName)
{
	sld = CharacterFromID("Villemstad_Poorman");
	sld.Dialog.Filename = "Common_poorman.c";
	sld.dialog.currentnode = "First time";
	LAi_SetCitizenType(sld);
	
	chrDisableReloadToLocation = false;
	bDisableFastReload = false;
	SetFunctionExitFromLocationCondition("TBP_Poorman_reset", PChar.location, false);
	
	sld = &locations[FindLocation("Villemstad_hut3")];
	DeleteAttribute(sld, "box1");
	sld.box1 = Items_MakeTime(0, 0, 0, 2025);
	sld.box1.items.TBP_letter = 1;
	
	PChar.quest.TBP_TakeLetter.win_condition.l1 = "item";
	PChar.quest.TBP_TakeLetter.win_condition.l1.item = "TBP_letter";
	PChar.quest.TBP_TakeLetter.function = "TBP_TakeLetter";
	
	SetFunctionLocationCondition("TBP_Uved_V_Dome", "Villemstad_hut3", false);
}

void TBP_Uved_V_Dome(string qName)
{
	notification(StringFromKey("Neutral_23"), "None");
	PlaySound("interface\notebook.wav");
}

void TBP_TakeLetter(string qName)
{
	//TakeItemFromCharacter(pchar, "TBP_letter");
	AddQuestRecord("TBP", "3");
	pchar.questTemp.TBP_Tavern2 = true;
	AddLandQuestMark(CharacterFromID("Villemstad_tavernkeeper"), "questmarkmain");
}

void TBP_SearchHouseWithFonar(string qName)
{
	GiveItem2Character(PChar, "jewelry24");
	if (CheckAttribute(pchar, "questTemp.TBP_BuyKulon"))
	{
		AddQuestRecord("TBP", "4");
		pchar.questTemp.TBP_BuyKulon2 = true;
	}
	pchar.questTemp.TBP_BuyKulon3 = true;
	DeleteAttribute(pchar, "questTemp.TBP_Tavern2");
	SetFunctionLocationCondition("TBP_HouseBetsi", "Villemstad_houseS2", false);
}

void TBP_HouseBetsi(string qName)
{
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(&Locations[FindLocation("Villemstad_houseS2")], true);
	DeleteAttribute(pchar, "questTemp.TBP_BuyKulon");
	DeleteAttribute(pchar, "questTemp.TBP_BuyKulon2");
	DeleteAttribute(pchar, "questTemp.TBP_BuyKulon3");
	for (i=1; i<=2; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("TBP_Bandit_"+i, "citiz_4"+(rand(8)+1), "man", "man", sti(pchar.rank), PIRATE, -1, true, "pirate"));
		if(i==1)
		{
			sld.dialog.filename = "Quest\MiniEvents\MysteryOfBetsyPrice_dialog.c";
			sld.dialog.currentnode = "Pirate_1";
			ChangeCharacterAddressGroup(sld, "Villemstad_houseS2", "barmen", "stay");
			LAi_SetActorType(sld);
			//LAi_ActorDialog(sld, pchar, "", -1, 0);
			LAi_SetActorType(pchar);
			SetActorDialogAny2Pchar(sld.id, "", -1, 0.0);
			//LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 2.0);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 2.0);
		}
		if(i==2) ChangeCharacterAddressGroup(sld, "Villemstad_houseS2", "goto", "goto2");
		//if(i==3) ChangeCharacterAddressGroup(sld, "Villemstad_houseS2", "reload", "reload3");
		//if(i==4) ChangeCharacterAddressGroup(sld, "Villemstad_houseS2", "reload", "reload4");
	}
}

void TBP_HouseBetsi_2(string qName)
{
	LAi_SetPlayerType(pchar);
	
	sld = GetCharacter(NPC_GenerateCharacter("TBP_BetsiPrice", "Marquesa", "woman", "towngirl", 5, HOLLAND, -1, false, "quest"));
	sld.name = StringFromKey("Neutral_12");
	sld.lastname = "";
	sld.dialog.filename = "Quest\MiniEvents\MysteryOfBetsyPrice_dialog.c";
	sld.dialog.currentnode = "BetsiPrice_1";
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, "Villemstad_houseS2", "reload", "reload2");
	TeleportCharacterToPos(sld, 2.00, 25.00, -4.50);
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 0, 0);
	
	PlaySound("Interface\Door_Kick.wav");
	DoQuestFunctionDelay("TBP_HouseBetsi_2_1", 0.3);
}

void TBP_HouseBetsi_2_1(string qName)
{
	PlaySound("Voice\Russian\other\RapersGirl-01.wav");
	//PlaySound("Voice\Spanish\other\RapersGirl-01.wav");
}

void TBP_HouseBetsi_3(string qName)
{
	sld = CharacterFromID("TBP_Bandit_1");
	sld.dialog.filename = "Quest\MiniEvents\MysteryOfBetsyPrice_dialog.c";
	sld.dialog.currentnode = "Pirate_3";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 0, 0);
}

void TBP_HouseBetsi_4(string qName)
{
	LAi_LocationFightDisable(&Locations[FindLocation("Villemstad_houseS2")], false);
	LAi_SetFightMode(pchar, true);
	sld = CharacterFromID("TBP_Bandit_2");
	LAi_SetCheckMinHP(sld, 1, true, "TBP_HouseBetsi_5");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	for (i=1; i<=3; i++)
	{
		sld = CharacterFromID("TBP_Bandit_"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
}

void TBP_HouseBetsi_6(string qName)
{
	LAi_LocationFightDisable(&Locations[FindLocation("Villemstad_houseS2")], true);
	LAi_group_Delete("EnemyFight");
	sld = CharacterFromID("TBP_Bandit_2");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "reload", "reload2", "TBP_HouseBetsi_7", 7);
}

void TBP_HouseBetsi_8(string qName)
{
	PlaySound("interface\key.wav");
	DoQuestFunctionDelay("TBP_HouseBetsi_9", 1.0);
}

void TBP_HouseBetsi_9(string qName)
{
	sld = CharacterFromID("TBP_Bandit_2");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "barmen", "bar1", "TBP_HouseBetsi_10", 7);
}

void TBP_HouseBetsi_11(string qName)
{
	sld = CharacterFromID("TBP_Bandit_2");
	sld.dialog.filename = "Quest\MiniEvents\MysteryOfBetsyPrice_dialog.c";
	sld.dialog.currentnode = "Pirate_6";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 0, 0);
}

void TBP_HouseBetsi_12(string qName)
{
	sld = CharacterFromID("TBP_Bandit_2");
	sld.lifeday = 0;
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "TBP_HouseBetsi_13", 7);
}

void TBP_ProvodimDoDoma(string qName)
{
	DoFunctionReloadToLocation("Villemstad_town", "officers", "hut3_1", "TBP_ProvodimDoDoma_2");
}

void TBP_ProvodimDoDoma_2(string qName)
{
	sld = CharacterFromID("TBP_BetsiPrice");
	sld.dialog.filename = "Quest\MiniEvents\MysteryOfBetsyPrice_dialog.c";
	sld.dialog.currentnode = "BetsiPrice_11";
	ChangeCharacterAddressGroup(sld, "Villemstad_town", "officers", "hut3_3");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 0, 0);
	
	if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && CharacterIsAlive("Helena"))
	{
		sld = characterFromId("Helena");
		ChangeCharacterAddressGroup(sld, "Villemstad_town", "officers", "houseS4_1");
		LAi_SetActorType(sld);
		return;
	}
	if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && CharacterIsAlive("Mary"))
	{
		sld = characterFromId("Mary");
		ChangeCharacterAddressGroup(sld, "Villemstad_town", "officers", "houseS4_1");
		LAi_SetActorType(sld);
		return;
	}
}

void TBP_ProvodimDoDoma_3(string qName)
{
	sld = CharacterFromID("TBP_BetsiPrice");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "Hut3", "none", "", "", "TBP_ProvodimDoDoma_4", 7);
	DeleteAttribute(pchar, "questTemp.TBP_BuyKulonOtdatBetsy");
}

void TBP_ProvodimDoDoma_5(string qName)
{
	if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && CharacterIsAlive("Helena")) Return_HelenaOfficer();
	if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && CharacterIsAlive("Mary")) Return_MaryOfficer();
	
	chrDisableReloadToLocation = false;
	LAi_LocationFightDisable(&Locations[FindLocation("Villemstad_houseS2")], false);
	AddQuestRecord("TBP", "5");
	pchar.questTemp.TBP_Tavern3 = true;
	AddLandQuestMark(CharacterFromID("Villemstad_tavernkeeper"), "questmarkmain");
}

void TBP_BetsiBackToWork(string qName)
{
	DeleteAttribute(pchar, "questTemp.TBP_Tavern3");
	AddQuestRecord("TBP", "6");
	CloseQuestHeader("TBP");
	TakeItemFromCharacter(pchar, "TBP_letter");
	SetTimerFunction("TBP_BetsiBackToWork_2", 0, 0, 1);
	pchar.questTemp.TBP_BetsiPrice = true;
}

void TBP_BetsiBackToWork_2(string qName)
{
	sld = CharacterFromID("Villemstad_waitress");
	sld.name = StringFromKey("Neutral_13");
	sld.lastname = StringFromKey("Neutral_14");
	sld.model = "Marquesa";
	Characters_RefreshModel(sld);
}

/*void TBP_Betsi_sex_1(string qName)
{
	DoFunctionReloadToLocation("Villemstad_tavern_upstairs", "quest", "quest4", "TBP_Betsi_sex_2");
}*/

void TBP_Betsi_sex_2(string qName)
{
	pchar.questTemp.TBP_BetsiPrice_Sex = true;
	chrDisableReloadToLocation = true;
	LAi_SetStayType(pchar);
	
	sld = CharacterFromID("TBP_BetsiPrice");
	sld.model.animation = "woman";
	Characters_RefreshModel(sld);
	sld.dialog.filename = "Quest\MiniEvents\MysteryOfBetsyPrice_dialog.c";
	sld.dialog.currentnode = "BetsiPrice_sex_1";
	ChangeCharacterAddressGroup(sld, "Villemstad_tavern_upstairs", "quest", "quest3");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 0, 0);
}

void TBP_Betsi_sex_3(string qName)
{
	LAi_FadeLong("", "");
	DoQuestFunctionDelay("TBP_Betsi_sex_4", 1.0);
}

void TBP_Betsi_sex_4(string qName)
{
	StartQuestMovie(true, false, true);
	locCameraFromToPos(-0.64, 1.72, -0.90, true, 1.53, -0.20, -3.08);
	TeleportCharacterToPosAy(pchar, 0.10, 0.00, -1.50, 3.00);
	LAi_SetActorType(pchar);
	LAi_ActorAnimation(pchar, "kiss", "1", 7.5);
	
	sld = characterFromId("TBP_BetsiPrice");
	TeleportCharacterToPosAy(sld, 0.10, 0.00, -2.10, 0.00);
	LAi_SetActorType(sld);
	LAi_ActorAnimation(sld, "kiss", "1", 7.5);
	
	DoQuestFunctionDelay("TBP_Betsi_sex_5", 1.7);
	DoQuestFunctionDelay("TBP_Betsi_sex_6", 7.5);
}

void TBP_Betsi_sex_5(string qName)
{
	locCameraFromToPos(-0.92, 1.57, -2.40, true, 2.14, -0.20, -0.37);
}

void TBP_Betsi_sex_6(string qName)
{
	EndQuestMovie();
	locCameraTarget(PChar);
	locCameraFollow();
	LAi_SetPlayerType(pchar);
	ChangeCharacterAddressGroup(pchar, PChar.location, "quest", "quest4");
	sld = characterFromId("TBP_BetsiPrice");
	LAi_SetStayType(sld);
	ChangeCharacterAddressGroup(sld, PChar.location, "quest", "quest3");
	sld.dialog.currentnode = "BetsiPrice_sex_2";
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	
	SetLaunchFrameFormParam("", "", 0, 15);
	SetLaunchFrameFormPic("loading\inside\censored1.tga");
	PlayStereoSound("sex\sex"+(rand(9)+1)+".wav");
	LaunchFrameForm();
	WaitDate("", 0, 0, 0, 3, 10); //крутим время
	RecalculateJumpTable();
	LAi_SetCurHPMax(pchar);
	if(IsEquipCharacterByArtefact(pchar, "totem_03"))
	{
		AddCharacterHealth(pchar, 12);
		AddCharacterMaxHealth(pchar, 2.0);
	}
	else 
	{
		AddCharacterHealth(pchar, 6);
		AddCharacterMaxHealth(pchar, 1.0);
	}
}

void TBP_Betsi_sex_7(string qName)
{
	sld = characterFromId("TBP_BetsiPrice");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "TBP_Betsi_sex_8", 7);
}

void TBP_Betsi_sex_9(string qName)
{
	DeleteAttribute(pchar, "questTemp.TBP_BetsiPrice_Sex");
}


bool MysteryOfBetsyPrice_QuestComplete(string sQuestName, string qname)
{
	ref sld;
	aref arOldMapPos, arAll, arPass;
	int     iTemp, i, n, iRank, Rank;
    float locx, locy, locz;
	string  attrName, sTemp; // любые строки для вычислений
	bool   bOk;
	
	bool condition = true;
	
	if (sQuestName == "TBP_HouseBetsi_5") {
		sld = CharacterFromID("TBP_Bandit_2");
		sld.dialog.filename = "Quest\MiniEvents\MysteryOfBetsyPrice_dialog.c";
		sld.dialog.currentnode = "Pirate_5";
		LAi_SetStayType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
	}
	
	else if (sQuestName == "TBP_HouseBetsi_7") {
		sld = CharacterFromID("TBP_Bandit_2");
		LAi_SetActorType(sld);
		LAi_ActorTurnToCharacter(sld, CharacterFromID("TBP_BetsiPrice"));
		DoQuestFunctionDelay("TBP_HouseBetsi_8", 1.0);
	}
	
	else if (sQuestName == "TBP_HouseBetsi_10") {
		sld = CharacterFromID("TBP_BetsiPrice");
		sld.name = StringFromKey("Neutral_13");
		sld.lastname = StringFromKey("Neutral_14");
		sld.dialog.filename = "Quest\MiniEvents\MysteryOfBetsyPrice_dialog.c";
		sld.dialog.currentnode = "BetsiPrice_2";
		ChangeCharacterAddressGroup(sld, "Villemstad_houseS2", "reload", "reload2");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	
	else if (sQuestName == "TBP_HouseBetsi_13") {
		sld = CharacterFromID("TBP_BetsiPrice");
		sld.dialog.filename = "Quest\MiniEvents\MysteryOfBetsyPrice_dialog.c";
		sld.dialog.currentnode = "BetsiPrice_8";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	
	else if (sQuestName == "TBP_ProvodimDoDoma_4") {
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && CharacterIsAlive("Helena"))
		{
			sld = characterFromId("Helena");
			sld.dialog.filename = "Quest\MiniEvents\MysteryOfBetsyPrice_dialog.c";
			sld.dialog.currentnode = "TBP_Helena_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			return;
		}
		if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && CharacterIsAlive("Mary"))
		{
			sld = characterFromId("Mary");
			sld.dialog.filename = "Quest\MiniEvents\MysteryOfBetsyPrice_dialog.c";
			sld.dialog.currentnode = "TBP_Mary_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			return;
		}
		DoQuestFunctionDelay("TBP_ProvodimDoDoma_5", 0.1);
	}
	
	else if (sQuestName == "TBP_Betsi_sex_8") {
		chrDisableReloadToLocation = false;
		SetTimerFunction("TBP_Betsi_sex_9", 0, 0, 1);
		if (!CheckAttribute(pchar, "questTemp.TBP_QuestCompleted"))
		{
			pchar.questTemp.TBP_QuestCompleted = true;
			AddQuestRecordInfo("Useful_Acquaintances", "2");
		}
	}
	
	else
	{
		condition = false;
	}
	
	return condition;
}

