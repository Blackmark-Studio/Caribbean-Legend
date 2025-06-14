void DTSG_Knippel_36()
{
	bDisableFastReload = false;
	chrDisableReloadToLocation = false;
	QuestCloseSeaExit()
	
	LocatorReloadEnterDisable("PortPax_town", "houseS2", false);
	
	sld = CharacterFromID("DTSG_PiterAdams");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	
	sld = GetCharacter(NPC_GenerateCharacter("DTSG_FrederikStouks", "mercen_26", "man", "man", 30, ENGLAND, -1, false, "quest"));
	sld.name = StringFromKey("Knippel_21");
	sld.lastname = StringFromKey("Knippel_22");
	GiveItem2Character(sld, "blade_13");
	EquipCharacterByItem(sld, "blade_13");
	GiveItem2Character(sld, "pistol5");
	EquipCharacterByItem(sld, "pistol5");
	GiveItem2Character(sld, "cirass1");
	EquipCharacterByItem(sld, "cirass1");
	AddItems(sld, "purse2", 1);
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	ChangeCharacterAddressGroup(sld, "PortPax_houseS2", "goto", "goto7");
	LAi_SetActorType(sld);
	SetSelfSkill(sld, 80, 80, 80, 80, 80);
	LAi_SetHP(sld, 225+MOD_SKILL_ENEMY_RATE*10, 200+MOD_SKILL_ENEMY_RATE*10);
	
	sld = GetCharacter(NPC_GenerateCharacter("DTSG_RalfFaggl", "mush_ctz_12", "man", "mushketer", 30, ENGLAND, -1, false, "quest"));
	sld.name = StringFromKey("Knippel_23");
	sld.lastname = StringFromKey("Knippel_24");
	SetCharacterPerk(sld, "Gunman");
	SetCharacterPerk(sld, "GunProfessional");
	GiveItem2Character(sld, "mushket2");
	EquipCharacterbyItem(sld, "mushket2");
	AddItems(sld, "purse2", 1);
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	//sld.MushketType = "mushket2";
	//sld.MushketBulletType = "cartridge";
	LAi_SetStayType(sld);
	ChangeCharacterAddressGroup(sld, "PortPax_houseS2", "goto", "goto1");
	sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
	sld.dialog.currentnode = "DTSG_RalfFaggl";
	SetSelfSkill(sld, 80, 80, 80, 80, 80);
	LAi_SetHP(sld, 250+MOD_SKILL_ENEMY_RATE*10, 200+MOD_SKILL_ENEMY_RATE*10);
	
	PChar.quest.DTSG_Sosedi.win_condition.l1 = "location";
	PChar.quest.DTSG_Sosedi.win_condition.l1.location = "PortPax_houseS2";
	PChar.quest.DTSG_Sosedi.win_condition = "DTSG_Sosedi";
	
	PChar.quest.DTSG_PoP_DuelTime.win_condition.l1 = "Timer";
	PChar.quest.DTSG_PoP_DuelTime.win_condition.l1.date.hour = sti(GetTime() + 2);
	PChar.quest.DTSG_PoP_DuelTime.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0);
	PChar.quest.DTSG_PoP_DuelTime.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
	PChar.quest.DTSG_PoP_DuelTime.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
	PChar.quest.DTSG_PoP_DuelTime.win_condition = "DTSG_PoP_DuelTime";
	
	PChar.quest.DTSG_PoP_Duel.win_condition.l1 = "location";
	PChar.quest.DTSG_PoP_Duel.win_condition.l1.location = "PortPax_ExitTown";
	PChar.quest.DTSG_PoP_Duel.win_condition = "DTSG_PoP_Duel";
	LAi_LocationDisableOfficersGen("PortPax_ExitTown", true);
	pchar.questTemp.DTSG_ZovemMatrosov = true;
	AddQuestRecord("DTSG", "4");
}

void DTSG_Knippel_64()
{
	Return_KnippelOfficer();
	bDisableFastReload = false;
	chrDisableReloadToLocation = false;
	
	ChangeItemName("letter_1", "itmname_specialletter");
	ChangeItemDescribe("letter_1", "itmdescr_DTSG_letter2");
	
	LocatorReloadEnterDisable("PortPax_town", "houseF1", false);
	
	pchar.GenQuestBox.PortPax_houseF1.box1.items.gold = 8000;
	pchar.GenQuestBox.PortPax_houseF1.box1.items.chest = 1;
	pchar.GenQuestBox.PortPax_houseF1.box1.items.jewelry2 = 10;
	pchar.GenQuestBox.PortPax_houseF1.box1.items.jewelry3 = 5;
	pchar.GenQuestBox.PortPax_houseF1.box1.items.jewelry4 = 5;
	pchar.GenQuestBox.PortPax_houseF1.box1.items.jewelry8 = 1;
	pchar.GenQuestBox.PortPax_houseF1.box1.items.letter_1 = 1;
	
	PChar.quest.DTSG_Duel_SundukPismo.win_condition.l1 = "item";
	PChar.quest.DTSG_Duel_SundukPismo.win_condition.l1.item = "letter_1";
	PChar.quest.DTSG_Duel_SundukPismo.win_condition = "DTSG_Duel_SundukPismo";
}

//=================================================================
//======================кейсы из quests_reaction===================
//=================================================================
bool Knippel_QuestComplete(string sQuestName, string qname)
{
	ref sld;
	int  i, n;
	
	bool condition = true;
	
	if (sQuestName == "DTSG_Start") {
		if (GetCharacterIndex("Knippel") != -1 && CheckPassengerInCharacter(pchar, "Knippel") && !CheckAttribute(pchar, "questTemp.DTSG_Start"))
		{
			PChar.quest.DTSG_Nachalo.win_condition.l1 = "location";
			PChar.quest.DTSG_Nachalo.win_condition.l1.location = "BasTer_town";
			PChar.quest.DTSG_Nachalo.win_condition = "DTSG_Nachalo";
			AddMapQuestMarkCity("BasTer", true);
			pchar.questTemp.DTSG_Start = true;
		}
	}
	
	else if (sQuestName == "DTSG_Nachalo") {
		if (GetCharacterIndex("Knippel") != -1 && CheckPassengerInCharacter(pchar, "Knippel"))
		{
			sld = characterFromId("Knippel");
			ChangeCharacterAddressGroup(sld, "BasTer_town", "goto", "goto20");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Knippel_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
			DelMapQuestMarkCity("BasTer");
			pchar.quest.Mary_giveme_sex1.over = "yes";
		}
	}
	
	else if (sQuestName == "DTSG_BasTerTavern_Chistim") {
		FreeSitLocator("BasTer_tavern", "sit2");
		FreeSitLocator("BasTer_tavern", "sit6");
		FreeSitLocator("BasTer_tavern", "sit_base8");
		FreeSitLocator("BasTer_tavern", "sit_front8");
	}
	
	else if (sQuestName == "DTSG_BasTerTavern") {
		LAi_LocationDisableOfficersGen("BasTer_tavern", true);
		DoQuestReloadToLocation("BasTer_tavern", "goto", "goto1", "DTSG_BasTerTavern_2");
	}
	
	else if (sQuestName == "DTSG_BasTerTavern_2") {
		DoQuestCheckDelay("DTSG_BasTerTavern_Chistim", 1.0);
		DoQuestCheckDelay("DTSG_BasTerTavern_3", 3.0);
		StartQuestMovie(true, false, true);
		locCameraFromToPos(2.40, 3.59, 3.21, true, 13.11, -0.3, -0.73);
		LAi_SetActorType(pchar);
		LAi_ActorGoToLocator(pchar, "tables", "stay3", "", -1);
		sld = CharacterFromID("Knippel");
		ChangeCharacterAddressGroup(sld, "BasTer_tavern", "reload", "reload1_back");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocator(sld, "tables", "stay3", "", -1);
	}
	
	else if (sQuestName == "DTSG_BasTerTavern_3") {
		LAi_Fade("", "");
		DoQuestCheckDelay("DTSG_BasTerTavern_4", 0.5);
	}
	
	else if (sQuestName == "DTSG_BasTerTavern_4") {
		LAi_SetSitType(pchar);
		ChangeCharacterAddressGroup(pchar, "BasTer_tavern", "sit", "sit6");
		sld = CharacterFromID("Knippel");
		LAi_SetSitType(sld);
		ChangeCharacterAddressGroup(sld, "BasTer_tavern", "sit", "sit2");
		locCameraFromToPos(5.71, 2.61, -5.49, true, 5.45, 0.73, 2.77);
		DoQuestCheckDelay("DTSG_BasTerTavern_5", 4.0);
	}
	
	else if (sQuestName == "DTSG_BasTerTavern_5") {
		sld = GetCharacter(NPC_GenerateCharacter("DTSG_Ohotnik", "citiz_27", "man", "man", 5, ENGLAND, -1, true, "quest"));
		LAi_SetHP(sld, 30, 30);
		AddMoneyToCharacter(sld, 2000);
		AddItems(sld, "gold_dublon", 50);
		GiveItem2Character(sld, "blade_15");
		EquipCharacterByItem(sld, "blade_15");
		GiveItem2Character(sld, "pistol6");
		EquipCharacterByItem(sld, "pistol6");
		AddItems(sld, "indian_10", 1);
		sld.SaveItemsForDead = true;
		sld.DontClearDead = true;
		sld.CantLoot = true;
		ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocator(sld, "tables", "stay6", "DTSG_BasTerTavern_6", -1);
	}
	
	else if (sQuestName == "DTSG_BasTerTavern_6") {
		sld = CharacterFromID("DTSG_Ohotnik");
		sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
		sld.dialog.currentnode = "DTSG_Ohotnik_1";
		LAi_ActorDialog(sld, pchar, "", 1, 0);
	}
	
	else if (sQuestName == "DTSG_BasTerTavern_7") {
		locCameraSleep(false);
		locCameraFromToPos(9.74, 3.18, -2.37, true, 7.63, 1.22, 0.54);
		
		sld = CharacterFromID("DTSG_Ohotnik");
		ChangeCharacterAddressGroup(sld, "BasTer_tavern", "tables", "stay7");
		TeleportCharacterToPosAy(sld, 8.95, 1.00, 0.00, 3.00);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		
		sld = CharacterFromID("Knippel");
		ChangeCharacterAddressGroup(sld, "BasTer_tavern", "tables", "stay6");
		TeleportCharacterToPosAy(sld, 7.28, 1.00, -0.71, 0.00);
		LAi_SetImmortal(sld, true);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		if (FindCharacterItemByGroup(sld, BLADE_ITEM_TYPE) == "")
		{
			GiveItem2Character(sld, "slave_02");
			EquipCharacterByItem(sld, "slave_02");
		}
		
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		LAi_group_SetCheck("EnemyFight", "DTSG_BasTerTavern_8");
	}
	
	else if (sQuestName == "DTSG_BasTerTavern_8") {
		DoQuestCheckDelay("DTSG_BasTerTavern_8_1", 1.5);
	}
	
	else if (sQuestName == "DTSG_BasTerTavern_8_1") {
		EndQuestMovie();
		DoQuestReloadToLocation("BasTer_tavern", "tables", "stay6", "DTSG_BasTerTavern_9");
	}
	
	else if (sQuestName == "DTSG_BasTerTavern_9") {
		LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], true);
		LAi_SetPlayerType(pchar);
		
		sld = CharacterFromID("Knippel");
		LAi_RemoveCheckMinHP(sld);
		LAi_SetImmortal(sld, false);
		sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
		sld.dialog.currentnode = "DTSG_Knippel_l0";
		ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto3");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	
	else if (sQuestName == "DTSG_BasTerDom_Timer") {
		PChar.quest.DTSG_BasTerDom.over = "yes";
		RemoveItems(pchar, "Key1", 1);
	}
	
	else if (sQuestName == "DTSG_BasTerDom") {
		DoQuestReloadToLocation("BasTer_HutFish1", "reload", "reload1", "DTSG_BasTerDom_2");
	}
	
	else if (sQuestName == "DTSG_BasTerDom_2") {
		PChar.quest.DTSG_BasTerDom_Timer.over = "yes";
		if (GetCharacterIndex("Knippel") != -1)
		{
			sld = characterFromId("Knippel");
			PlaceCharacter(sld, "goto", PChar.location);
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			sld.location = "None";
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
		}
		Locations[FindLocation(pchar.location)].box1.items.gold = 10000;
		Locations[FindLocation(pchar.location)].box1.items.gold_dublon = 200;
		Locations[FindLocation(pchar.location)].box1.items.indian_10 = 1;
		Locations[FindLocation(pchar.location)].box1.items.DTSG_letter1 = 1;
		
		PChar.quest.DTSG_BasTerDom.win_condition.l1 = "locator";
		PChar.quest.DTSG_BasTerDom.win_condition.l1.location = "BasTer_HutFish1";
		PChar.quest.DTSG_BasTerDom.win_condition.l1.locator_group = "box";
		PChar.quest.DTSG_BasTerDom.win_condition.l1.locator = "box1";
		PChar.quest.DTSG_BasTerDom.win_condition = "DTSG_BasTerDom_4";
	}
	
	else if (sQuestName == "DTSG_BasTerDom_3") {
		if (GetCharacterIndex("Knippel") != -1)
		{
			sld = CharacterFromID("Knippel");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Knippel_20";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		}
	}
	
	else if (sQuestName == "DTSG_BasTerDom_4") {
		RemoveItems(pchar, "Key1", 1);
		Log_info(StringFromKey("Knippel_1"));
		PlaySound("interface\key.wav");
		DoQuestCheckDelay("DTSG_BasTerDom_3", 3.0);
	}
	
	else if (sQuestName == "DTSG_Etap2") {			//КОНЕЦ ЭТАПА 1
		PChar.quest.DTSG_PoP.win_condition.l1 = "location";
		PChar.quest.DTSG_PoP.win_condition.l1.location = "PortPax_town";
		PChar.quest.DTSG_PoP.win_condition = "DTSG_PoP";
		AddMapQuestMarkCity("PortPax", true);
	}
	
	else if (sQuestName == "DTSG_PoP") {
		PChar.quest.DTSG_PoP2.win_condition.l1 = "ExitFromLocation";
		PChar.quest.DTSG_PoP2.win_condition.l1.location = PChar.location;
		PChar.quest.DTSG_PoP2.win_condition = "DTSG_PoP2";
		DelMapQuestMarkCity("PortPax");
	}
	
	else if (sQuestName == "DTSG_PoP2") {
		PChar.quest.DTSG_PoP3.win_condition.l1 = "location";
		PChar.quest.DTSG_PoP3.win_condition.l1.location = "PortPax_town";
		PChar.quest.DTSG_PoP3.win_condition = "DTSG_PoP3";
		LAi_LocationDisableOfficersGen("PortPax_town", true);
	}
	
	else if (sQuestName == "DTSG_PoP3") {
		bDisableFastReload = true;
		chrDisableReloadToLocation = true;
		InterfaceStates.Buttons.Save.enable = false;
		
		if (GetCharacterIndex("Knippel") != -1)
		{
			sld = CharacterFromID("Knippel");
			ChangeCharacterAddressGroup(sld, "PortPax_town", "officers", "reload4_1");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
		}
		
		sld = GetCharacter(NPC_GenerateCharacter("DTSG_PiterAdams", "keeper_8", "man", "man_B", sti(pchar.rank), ENGLAND, -1, true, "quest"));
		sld.name = StringFromKey("Knippel_2");
		sld.lastname = StringFromKey("Knippel_3");
		LAi_SetHP(sld, 200+MOD_SKILL_ENEMY_RATE*10, 200+MOD_SKILL_ENEMY_RATE*10);
		ChangeCharacterAddressGroup(sld, "PortPax_town", "reload", "houseF1");
		sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
		sld.dialog.currentnode = "DTSG_PiterAdams_1";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	
	else if (sQuestName == "DTSG_PiterAdams_VDom") {
		LAi_SetPlayerType(pchar);
		sld = CharacterFromID("DTSG_PiterAdams");
		sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
		sld.dialog.currentnode = "DTSG_PiterAdamsRyadomSDomom_1";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
	}
	
	else if (sQuestName == "DTSG_PiterAdams_VDom_2") {
		LAi_SetPlayerType(pchar);
		
		sld = GetCharacter(NPC_GenerateCharacter("DTSG_JeinAdams", "girl_9", "woman", "woman", sti(pchar.rank), ENGLAND, 0, false, "quest"));
		sld.name = StringFromKey("Knippel_4");
		sld.lastname = StringFromKey("Knippel_5");
		ChangeCharacterAddressGroup(sld, "PortPax_houseF1", "barmen", "bar1");
		sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
		sld.dialog.currentnode = "DTSG_JeinAdams_1";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
		
		sld = CharacterFromID("DTSG_PiterAdams");
		ChangeCharacterAddressGroup(sld, "PortPax_houseF1", "goto", "goto1");
		LAi_SetActorType(sld);
		
		if (GetCharacterIndex("Knippel") != -1)
		{
			sld = CharacterFromID("Knippel");
			ChangeCharacterAddressGroup(sld, "PortPax_houseF1", "goto", "goto2");
			LAi_SetActorType(sld);
			sld.location = "None";
		}
	}
	
	else if (sQuestName == "DTSG_PiterAdams_IsDoma") {
		if (GetCharacterIndex("Knippel") != -1)
		{
			sld = CharacterFromID("Knippel");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Knippel_30";
			ChangeCharacterAddressGroup(sld, "PortPax_town", "officers", "houseF1_1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
			sld.location = "None";
		}
	}
	
	else if (sQuestName == "DTSG_Sosedi") {
		sld = CharacterFromID("DTSG_RalfFaggl");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
		
		sld = CharacterFromID("DTSG_FrederikStouks");
		CharacterTurnByChr(sld, pchar);
		
		bDisableFastReload = true;
		chrDisableReloadToLocation = true;
	}
	
	else if (sQuestName == "DTSG_FrederikStouks_ranen") {
		if (GetCharacterIndex("Knippel") != -1)
		{
			sld = CharacterFromID("Knippel");
			ChangeCharacterAddressGroup(sld, "PortPax_houseS2", "reload", "reload1");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			Log_info(StringFromKey("Knippel_6"));
			LAi_SetCheckMinHP(sld, 10, true, "");
		}
		sld = CharacterFromID("DTSG_FrederikStouks");
		LAi_SetActorType(sld);
		LAi_ActorSetGroundSitMode(sld);
		
		sld = CharacterFromID("DTSG_RalfFaggl");
		LAi_RemoveCheckMinHP(sld);
		LAi_SetImmortal(sld, false);
		
		PChar.quest.DTSG_RalfFaggl_kill.win_condition.l1 = "NPC_Death";
		PChar.quest.DTSG_RalfFaggl_kill.win_condition.l1.character = "DTSG_RalfFaggl";
		PChar.quest.DTSG_RalfFaggl_kill.win_condition = "DTSG_RalfFaggl_kill";
	}
	
	else if (sQuestName == "DTSG_RalfFaggl_ubit") {			
		if (GetCharacterIndex("Knippel") != -1)
		{
			sld = CharacterFromID("Knippel");
			ChangeCharacterAddressGroup(sld, "PortPax_houseS2", "reload", "reload1");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			Log_info(StringFromKey("Knippel_6"));
			LAi_SetCheckMinHP(sld, 10, true, "");
		}
		
		sld = CharacterFromID("DTSG_FrederikStouks");
		LAi_SetCheckMinHP(sld, 1, true, "DTSG_FrederikStouks_ranenVtorym");
	}
	
	else if (sQuestName == "DTSG_RalfFaggl_kill") {
		DoQuestCheckDelay("hide_weapon", 1.2);
		sld = CharacterFromID("Knippel");
		LAi_SetActorType(sld);
	
		sld = CharacterFromID("DTSG_PiterAdams");
		sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
		sld.dialog.currentnode = "DTSG_PiterAdams_11";
		ChangeCharacterAddressGroup(sld, "PortPax_houseS2", "reload", "reload1");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
	}
	
	else if (sQuestName == "DTSG_FrederikStouks_ranenVtorym") {
		DoQuestCheckDelay("hide_weapon", 1.2);
		sld = CharacterFromID("Knippel");
		LAi_SetActorType(sld);
	
		sld = CharacterFromID("DTSG_PiterAdams");
		sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
		sld.dialog.currentnode = "DTSG_PiterAdams_11";
		ChangeCharacterAddressGroup(sld, "PortPax_houseS2", "reload", "reload1");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
		
		sld = CharacterFromID("DTSG_FrederikStouks");
		LAi_SetActorType(sld);
		LAi_ActorSetGroundSitMode(sld);
	}
	
	else if (sQuestName == "DTSG_Sosedi_Pobeda") {
		sld = CharacterFromID("Knippel");
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, pchar, "", -1);
		
		DoQuestCheckDelay("hide_weapon", 1.2);
		PChar.quest.DTSG_Sosedi_Pobeda_2.win_condition.l1 = "item";
		PChar.quest.DTSG_Sosedi_Pobeda_2.win_condition.l1.item = "letter_1";
		PChar.quest.DTSG_Sosedi_Pobeda_2.win_condition = "DTSG_Sosedi_Pobeda_2";
	}
	
	else if (sQuestName == "DTSG_Sosedi_Pobeda_2") {
		sld = CharacterFromID("Knippel");
		sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
		sld.dialog.currentnode = "DTSG_Knippel_40";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		LAi_RemoveCheckMinHP(sld);
		LAi_SetImmortal(sld, false);
	}
	
	else if (sQuestName == "DTSG_PoP_ProverimSunduk") {
		LocatorReloadEnterDisable("PortPax_town", "houseF1", false);
		
		pchar.GenQuestBox.PortPax_houseF1.box1.items.gold = 8000;
		pchar.GenQuestBox.PortPax_houseF1.box1.items.chest = 1;
		pchar.GenQuestBox.PortPax_houseF1.box1.items.jewelry2 = 10;
		pchar.GenQuestBox.PortPax_houseF1.box1.items.jewelry3 = 5;
		pchar.GenQuestBox.PortPax_houseF1.box1.items.jewelry4 = 5;
		pchar.GenQuestBox.PortPax_houseF1.box1.items.jewelry8 = 1;
		
		PChar.quest.DTSG_PoP_ProverimSunduk_2.win_condition.l1 = "locator";
		PChar.quest.DTSG_PoP_ProverimSunduk_2.win_condition.l1.location = "PortPax_houseF1";
		PChar.quest.DTSG_PoP_ProverimSunduk_2.win_condition.l1.locator_group = "box";
		PChar.quest.DTSG_PoP_ProverimSunduk_2.win_condition.l1.locator = "box1";
		PChar.quest.DTSG_PoP_ProverimSunduk_2.win_condition = "DTSG_PoP_ProverimSunduk_2";
	}
	
	else if (sQuestName == "DTSG_PoP_ProverimSunduk_2") {
		bDisableFastReload = true;
		chrDisableReloadToLocation = true;
		sld = CharacterFromID("Knippel");
		sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
		sld.dialog.currentnode = "DTSG_Knippel_50";
		ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto2");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	
	else if (sQuestName == "DTSG_PoP_Duel") {
		PChar.quest.DTSG_PoP_DuelTime.over = "yes";
		PChar.quest.DTSG_Sosedi.over = "yes";
		bDisableFastReload = true;
		chrDisableReloadToLocation = true;
		LAi_LocationFightDisable(&Locations[FindLocation("PortPax_ExitTown")], true);
		if (GetCharacterIndex("Knippel") != -1)
		{
			sld = CharacterFromID("Knippel");
			ChangeCharacterAddressGroup(sld, "PortPax_ExitTown", "reload", "reload3");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
		sld = CharacterFromID("DTSG_PiterAdams");
		sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
		sld.dialog.currentnode = "DTSG_PiterAdams_20";
		ChangeCharacterAddressGroup(sld, "PortPax_ExitTown", "goto", "goto7");
		TeleportCharacterToPos(sld, -1.1, -2.55, 31.3);
		LAi_SetActorType(sld);
		LAi_ActorTurnToCharacter(sld, pchar);
		LAi_SetStayType(sld);
		sld.talker = 2;
		
		sld = GetCharacter(NPC_GenerateCharacter("DTSG_FrederikStouks", "mercen_26", "man", "man", sti(pchar.rank), ENGLAND, -1, false, "quest"));
		sld.name = StringFromKey("Knippel_7");
		sld.lastname = StringFromKey("Knippel_8");
		GiveItem2Character(sld, "blade_13");
		EquipCharacterByItem(sld, "blade_13");
		GiveItem2Character(sld, "pistol5");
		EquipCharacterByItem(sld, "pistol5");
		GiveItem2Character(sld, "cirass1");
		EquipCharacterByItem(sld, "cirass1");
		AddItems(sld, "purse2", 1);
		sld.SaveItemsForDead = true;
		sld.DontClearDead = true;
		LAi_SetHP(sld, 225+MOD_SKILL_ENEMY_RATE*10, 200+MOD_SKILL_ENEMY_RATE*10);
		ChangeCharacterAddressGroup(sld, "PortPax_ExitTown", "goto", "goto7");
		TeleportCharacterToPos(sld, -2.5, -2.52, 31.2);
		LAi_SetActorType(sld);
		LAi_ActorTurnToCharacter(sld, pchar);
		
		sld = CharacterFromID("DTSG_RalfFaggl");
		sld.lifeday = 0;
		
		sld = GetCharacter(NPC_GenerateCharacter("DTSG_RalfFaggl2", "citiz_53", "man", "man", sti(pchar.rank), ENGLAND, -1, false, "quest"));
		sld.name = StringFromKey("Knippel_9");
		sld.lastname = StringFromKey("Knippel_10");
		GiveItem2Character(sld, "blade_12");
		EquipCharacterByItem(sld, "blade_12");
		GiveItem2Character(sld, "pistol6");
		EquipCharacterByItem(sld, "pistol6");
		AddItems(sld, "purse2", 1);
		sld.SaveItemsForDead = true;
		sld.DontClearDead = true;
		LAi_SetHP(sld, 250+MOD_SKILL_ENEMY_RATE*10, 200+MOD_SKILL_ENEMY_RATE*10);
		ChangeCharacterAddressGroup(sld, "PortPax_ExitTown", "goto", "goto7");
		
		TeleportCharacterToPos(sld, -3.8, -2.55, 31.3);
		LAi_SetActorType(sld);
		LAi_ActorTurnToCharacter(sld, pchar);
		LAi_SetHP(sld, 250+MOD_SKILL_ENEMY_RATE*10, 200+MOD_SKILL_ENEMY_RATE*10);
	}
	
	else if (sQuestName == "DTSG_PoP_Duel_Podkreplenie") {
		locCameraFromToPos(-3.00, -0.50, 35.50, true, -2.80, -1.20, 12.53);
		EndQuestMovie();
		sld = CharacterFromID("DTSG_PiterAdams");
		sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
		sld.dialog.currentnode = "DTSG_PiterAdams_Nastoroje_29";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
	}
	
	else if (sQuestName == "KnippelRanen") {
		sld = CharacterFromID("Knippel");
		LAi_SetActorType(sld);
		LAi_ActorSetGroundSitMode(sld);
	}
	
	else if (sQuestName == "TonzagRanen") {
		sld = CharacterFromID("Tonzag");
		LAi_SetActorType(sld);
		LAi_ActorSetGroundSitMode(sld);
	}
	
	else if (sQuestName == "LongwayRanen") {
		sld = CharacterFromID("Longway");
		LAi_SetActorType(sld);
		LAi_ActorSetGroundSitMode(sld);
	}
	
	else if (sQuestName == "DTSG_PiterAdams_Duel_Pobeda") {
		DoQuestCheckDelay("hide_weapon", 1.2);
		sld = CharacterFromID("Knippel");
		sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
		sld.dialog.currentnode = "DTSG_Knippel_60";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		
		for (i=1; i<=5; i++)
		{
			if (GetCharacterIndex("DTSG_PoP_Matrosy_"+i) != -1)
			{
				sld = CharacterFromID("DTSG_PoP_Matrosy_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
				sld.lifeday = 0;
			}
		}
	}
	
	else if (sQuestName == "DTSG_Duel_SundukPismo") {
		bDisableFastReload = true;
		chrDisableReloadToLocation = true;
		sld = CharacterFromID("Knippel");
		sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
		sld.dialog.currentnode = "DTSG_Knippel_70";
		ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto2");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	
	else if (sQuestName == "DTSG_PoP_DuelTime") {
		DoQuestReloadToLocation("PortPax_town", "quest", "quest1", "DTSG_PoP_DuelTime_2");
	}
	
	else if (sQuestName == "DTSG_PoP_DuelTime_2") {
		if (GetCharacterIndex("Knippel") != -1)
		{
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
			sld = CharacterFromID("Knippel");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Knippel_PoPDuelTime";
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		}
	}
	
	else if (sQuestName == "DTSG_Etap3_Start") {
		AddQuestRecord("DTSG", "7");
		
		LAi_LocationDisableOfficersGen("SentJons_town", true);
		LAi_LocationDisableOfficersGen("SentJons_bank", true);
		LAi_LocationFightDisable(&Locations[FindLocation("SentJons_town")], true);
		
		PChar.quest.DTSG_Etap3_Start2.win_condition.l1 = "location";
		PChar.quest.DTSG_Etap3_Start2.win_condition.l1.location = "SentJons_town";
		PChar.quest.DTSG_Etap3_Start2.win_condition = "DTSG_Etap3_Start2";
		
		Pchar.GenQuest.Hunter2Pause = true;
	}
	
	else if (sQuestName == "DTSG_Etap3_Start2") {
		DelMapQuestMarkCity("SentJons");
		bDisableFastReload = true;
		chrDisableReloadToLocation = true;
		bQuestDisableMapEnter = true;
		if (GetHour() >= 6.0 && GetHour() <= 21.0)
		{
			//Дневной вариант
			sld = CharacterFromID("Knippel");
			PlaceCharacter(sld, "reload", PChar.location);
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			
			for (i=1; i<=3; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("DTSG_AntiguaSold_"+i, "sold_eng_"+(rand(7)+1), "man", "man", 10, ENGLAND, 0, true, "soldier"));
				ChangeCharacterAddressGroup(sld, "SentJons_town", "goto", "goto15");
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
				if (i == 3)
				{
					sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
					sld.dialog.currentnode = "DTSG_AntiguaArest";
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
			}
		}
		else
		{
			//Ночной вариант
			sld = CharacterFromID("Knippel");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_AntiguaNightPirs";
			PlaceCharacter(sld, "reload", PChar.location);
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			sld.location = "None";
		}
	}
	
	else if (sQuestName == "DTSG_AntiguaStrazhBank_Ubili") {
		DoQuestCheckDelay("hide_weapon", 1.2);
		sld = CharacterFromID("SentJons_usurer");
		sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
		sld.dialog.currentnode = "DTSG_AntiguaUsurer_PosleDraki";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
		LAi_group_Delete("EnemyFight");
	}
	
	else if (sQuestName == "DTSG_AntiguaTrevoga") {
		bDisableFastReload = false;
		sld = CharacterFromID("SentJons_usurer");
		sld.Dialog.Filename = "Usurer_dialog.c";
		sld.dialog.currentnode = "First time";
		LAi_SetOwnerType(sld);
		/*sld = CharacterFromID("SentJons_Mayor");
		LAi_group_Attack(sld, Pchar);*/
		pchar.questTemp.DTSG_AntiguaTrevoga = true;
	}
	
	else if (sQuestName == "DTSG_TurmaDayPobeda") {
		sld = CharacterFromID("Knippel");
		sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
		sld.dialog.currentnode = "DTSG_KnippelDaySpasen";
		LAi_SetStayType(sld);
		AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
	}
	
	else if (sQuestName == "DTSG_TurmaDayPobeda_2") {
		LAi_Fade("", "");
		DoQuestCheckDelay("DTSG_TurmaDayPobeda_2_1", 0.5);
	}
	
	else if (sQuestName == "DTSG_TurmaDayPobeda_2_1") {
		sld = CharacterFromID("Knippel");
		ChangeCharacterAddressGroup(sld, "SentJons_prison", "reload", "reload12");
		LAi_SetActorType(sld);
		DoQuestCheckDelay("DTSG_TurmaDayPobeda_3", 1.5);
	}
	
	else if (sQuestName == "DTSG_TurmaDayPobeda_3") {
		LAi_SetPlayerType(pchar);
		sld = CharacterFromID("Knippel");
		sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
		sld.dialog.currentnode = "DTSG_KnippelDaySpasen_5";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
	}
	
	else if (sQuestName == "DTSG_KnippelRazgovorVKaute") {
		pchar.GenQuest.CabinLock = true;
		Island_SetReloadEnableGlobal("Antigua", false);
		DoQuestCheckDelay("DTSG_KnippelRazgovorVKaute_2", 2.5);
	}
	
	else if (sQuestName == "DTSG_KnippelRazgovorVKaute_2") {
		DeleteAttribute(pchar, "GenQuest.CabinLock");
		pchar.GenQuest.DontSetCabinOfficer = true;
		chrDisableReloadToLocation = true;
		Sea_CabinStartNow();
		
		sld = CharacterFromID("Knippel");
		sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
		sld.dialog.currentnode = "DTSG_KnippelRazgovorOProshlom";
		LAi_SetStayType(sld);
		ChangeCharacterAddressGroup(sld, Get_My_Cabin(), "rld", "loc1");
		CharacterTurnByChr(sld, pchar);	
		AddLandQuestMark(sld, "questmarkmain");
	}
	
	else if (sQuestName == "DTSG_AntiguaSpat_3") {
		Statistic_AddValue(pchar, "TavernSleep", 1);
		Achievment_SetStat(24, 1);
		chrDisableReloadToLocation = false;
		PChar.quest.DTSG_Etap3_StartDay.win_condition.l1 = "location";
		PChar.quest.DTSG_Etap3_StartDay.win_condition.l1.location = "SentJons_town";
		PChar.quest.DTSG_Etap3_StartDay.win_condition = "DTSG_Etap3_StartDay";
		Pchar.GenQuest.Hunter2Pause = true;
	}
	
	else if (sQuestName == "DTSG_Etap3_StartDay") {
		//Дневной вариант
		bDisableFastReload = true;
		chrDisableReloadToLocation = true;
		sld = CharacterFromID("Knippel");
		PlaceCharacter(sld, "reload", PChar.location);
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, pchar, "", -1);
			
		for (i=1; i<=3; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_AntiguaSold_"+i, "sold_eng_"+(rand(7)+1), "man", "man", 10, ENGLAND, 0, true, "soldier"));
			ChangeCharacterAddressGroup(sld, "SentJons_town", "goto", "goto15");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			if (i == 3)
			{
				sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
				sld.dialog.currentnode = "DTSG_AntiguaArest";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
		}
	}
	
	else if (sQuestName == "DTSG_NightDom") {
		DoQuestReloadToLocation("SentJons_houseSP3", "reload", "reload1", "DTSG_NightDom_2");
	}
	
	else if (sQuestName == "DTSG_NightDom_2") {
		chrDisableReloadToLocation = true;
		sld = GetCharacter(CreateCharacterClone(CharacterFromID("SentJons_usurer"), 0));
		sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
		sld.dialog.currentnode = "DTSG_NightRostovshik";
		ChangeCharacterAddressGroup(sld, "SentJons_houseSP3", "goto", "goto1");
		LAi_SetStayType(sld);
		AddLandQuestMark(sld, "questmarkmain");
	}
	
	else if (sQuestName == "DTSG_NightDom_3") {
		DoQuestReloadToLocation("SentJons_town", "reload", "houseSp3", "DTSG_NightDom_4");
	}
	
	else if (sQuestName == "DTSG_NightDom_4") {
		sld = CharacterFromID("Knippel");
		ChangeCharacterAddressGroup(sld, "SentJons_town", "goto", "goto1");
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, pchar, "", -1);
		sld.location = "None";
		LAi_SetCheckMinHP(sld, 1, true, "KnippelRanen");
		
		for (i=1; i<=4; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_Killers_"+i, "sold_eng_"+(rand(7)+1), "man", "man", sti(pchar.rank), ENGLAND, 0, true, "soldier"));
			ChangeCharacterAddressGroup(sld, "SentJons_town", "goto", "goto23");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			if (i == 4)
			{
				sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
				sld.dialog.currentnode = "DTSG_NightKiller";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
				sld.rank = 30;
				LAi_SetHP(sld, 200+MOD_SKILL_ENEMY_RATE*20, 200+MOD_SKILL_ENEMY_RATE*20);
				SetSelfSkill(sld, 80, 80, 80, 80, 80);
				GiveItem2Character(sld, "blade_14");
				EquipCharacterbyItem(sld, "blade_14");
				GiveItem2Character(sld, "pistol4");
				EquipCharacterbyItem(sld, "pistol4");
				AddItems(sld, "purse2", 1);
				sld.SaveItemsForDead = true;
				sld.DontClearDead = true;
			}
		}
	}
	
	else if (sQuestName == "DTSG_NightKiller_Pobeda") {
		DoQuestCheckDelay("hide_weapon", 1.2);
		sld = CharacterFromID("Knippel");
		sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
		sld.dialog.currentnode = "DTSG_Knippel_80";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		LAi_RemoveCheckMinHP(sld);
		LAi_SetImmortal(sld, false);
	}
	
	else if (sQuestName == "DTSG_KnippelDoma") {
		StartQuestMovie(true, false, true);
		locCameraFromToPos(-2.13, 1.36, -2.72, false, 1.45, -0.20, -2.70);
		LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], true);
		LAi_SetStayType(pchar);
		bDisableCharacterMenu = true;
		LAi_SetCurHPMax(pchar);
		pchar.GenQuest.CannotWait = true;
		pchar.questTemp.TimeLock = true;
		InterfaceStates.Buttons.Save.enable = false;
		pchar.BaseNation = ENGLAND;
		//DoQuestCheckDelay("DTSG_KnippelDoma_1", 0.2);
		DoQuestCheckDelay("DTSG_KnippelDoma_2", 4.0);
		DoQuestCheckDelay("DTSG_KnippelDoma_3", 1.0);
		DoQuestCheckDelay("DTSG_KnippelDoma_4", 5.5);
	}
	
	else if (sQuestName == "DTSG_KnippelDoma_1") {
		//SetLaunchFrameFormParam(StringFromKey("Knippel_11", NewStr()), "", 0, 4.0);
		//LaunchFrameForm();
		//StartQuestMovie(true, false, true);
		//locCameraFromToPos(-2.13, 1.36, -2.72, false, 1.45, -0.20, -2.70);
	}
	
	else if (sQuestName == "DTSG_KnippelDoma_2") {
		sld = GetCharacter(NPC_GenerateCharacter("DTSG_Kurier", "sold_eng_"+(rand(7)+1), "man", "man", sti(pchar.rank), ENGLAND, 0, true, "soldier"));
		sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
		sld.dialog.currentnode = "DTSG_Kurier";
		ChangeCharacterAddressGroup(sld, "SentJons_houseH1", "reload", "reload1");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		locCameraFromToPos(1.73, 1.78, -3.80, true, -0.08, -0.30, -1.20);
	}
	
	else if (sQuestName == "DTSG_KnippelDoma_3") {
		SetMusic("music_way_back_then");
		pchar.questTemp.lockedMusic = true;
	}
	
	else if (sQuestName == "DTSG_KnippelDoma_4") {
		CharacterTurnToLoc(pchar, "barmen", "stay");
	}
	
	else if (sQuestName == "DTSG_KD1") {
		SetLaunchFrameFormParam(StringFromKey("Knippel_20", NewStr()), "Reload_To_Location", 0, 4.0);
		SetLaunchFrameReloadLocationParam("SentJons_houseSP3", "reload", "reload1", "DTSG_KD3");
		LaunchFrameForm();
	}
	
	else if (sQuestName == "DTSG_KD2") {
		DoQuestReloadToLocation("SentJons_houseSP3", "reload", "reload1", "DTSG_KD3");
	}
	
	else if (sQuestName == "DTSG_KD3") {
		locCameraFromToPos(3.44, 1.93, 0.84, false, -0.11, -0.50, -1.00);
		DoQuestCheckDelay("DTSG_KD3_1", 2.5);
		sld = GetCharacter(NPC_GenerateCharacter("DTSG_Cortny", "off_eng_5", "man", "man", 1, FRANCE, -1, false, "quest"));
		sld.name = StringFromKey("Knippel_12");
		sld.lastname = StringFromKey("Knippel_13");
		GiveItem2Character(sld, "blade_18");
		sld.equip.blade = "blade_18";
		sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
		sld.dialog.currentnode = "DTSG_Cortny";
		ChangeCharacterAddressGroup(sld, "SentJons_houseSP3", "reload", "reload2");
		LAi_SetActorType(pchar);
		LAi_SetActorType(sld);
		SetActorDialogAny2Pchar(sld.id, "", -1, 0.0);
		LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 2.0);
		LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 2.0);
	}
	
	else if (sQuestName == "DTSG_KD3_1") {
		locCameraFromToPos(-3.41, 1.32, -3.05, true, -2.35, 0.23, -0.03);
	}
	
	else if (sQuestName == "DTSG_KD3_2") {
		LAi_SetActorType(pchar);
		LAi_ActorGoToLocator(pchar, "reload", "reload2", "", -1);
		DoQuestCheckDelay("DTSG_KD4", 3.0);
	}
	
	else if (sQuestName == "DTSG_KD4") {
		DoQuestReloadToLocation("SentJons_houseSP3_room", "reload", "reload1", "DTSG_KD4_1");
	}
	
	else if (sQuestName == "DTSG_KD4_1") {
		locCameraFromToPos(1.42, 1.28, -3.27, true, -1.67, -0.30, -1.67);
		sld = CharacterFromID("Fleetwood");
		LAi_SetActorType(pchar);
		LAi_SetActorType(sld);
		SetActorDialogAny2Pchar(sld.id, "", -1, 0.0);
		//LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 2.0);
		LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
	}
	
	else if (sQuestName == "DTSG_KD5") {
		DeleteAttribute(pchar,"questTemp.TimeLock");
		SetCurrentTime(11, 00);
		RecalculateJumpTable();
		RefreshWeather();
		RefreshLandTime();
		DoQuestReloadToLocation("SentJons_houseH1", "reload", "reload1", "DTSG_KD6");
	}
	
	else if (sQuestName == "DTSG_KD6") {
		locCameraFromToPos(0.36, 1.40, -3.90, true, -0.13, -0.50, 0.17);
		LAi_SetActorType(pchar);
		LAi_ActorGoToLocator(pchar, "goto", "goto3", "DTSG_KD7", -1);
	}
	
	else if (sQuestName == "DTSG_KD7") {
		pchar.dialog.filename = "Quest\CompanionQuests\Knippel.c";
		pchar.dialog.currentnode = "DTSG_Knippel_SamSoboi";
		LAi_ActorSelfDialog(pchar, "pchar_back_to_player");
	}
	
	else if (sQuestName == "DTSG_ProshloeDominika_2") {
		//StartQuestMovie(true, false, true);
		LAi_SetActorType(pchar);
		TeleportCharacterToPosAy(pchar, -5.91, 4.56, 6.02, 1.50);
		locCameraToPos(-0.99, 6.15, 7.09, true);
		locCameraFromToPos(-0.99, 6.15, 7.09, true, -8.37, 4.16, 5.90);
		
		for (i=1; i<=4; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_ValkSold_"+i, "sold_eng_"+(rand(7)+1), "man", "man", sti(pchar.rank), ENGLAND, 0, true, "soldier"));
			PlaceCharacter(sld, "goto", "random_free");
			LAi_SetWarriorType(sld);
			LAi_CharacterDisableDialog(sld);
		}
		for (i=5; i<=8; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_ValkSold_"+i, "citiz_"+(rand(9)+31), "man", "man", sti(pchar.rank), ENGLAND, 0, true, "soldier"));
			PlaceCharacter(sld, "goto", "random_free");
			LAi_SetWarriorType(sld);
			LAi_CharacterDisableDialog(sld);
		}
		
		DoQuestCheckDelay("DTSG_ProshloeDominika_3", 5.0);
	}
	
	else if (sQuestName == "DTSG_ProshloeDominika_3") {
		//Log_info(StringFromKey("Knippel_14"));
		PlaySound("interface\" + LanguageGetLanguage() + "\_EvEnemy1.wav");
		
		DoQuestCheckDelay("DTSG_ProshloeDominika_4", 2.5);
	}
	
	else if (sQuestName == "DTSG_ProshloeDominika_4") {
		LAi_FadeLong("DTSG_ProshloeDominika_5", "");
		
	}
	
	else if (sQuestName == "DTSG_ProshloeDominika_5") {
		locCameraFromToPos(-6.02, 9.83, -20.76, true, -12.06, 7.21, -21.45);
		LAi_SetPlayerType(pchar);
		TeleportCharacterToPosAy(pchar, -7.83, 7.95, -21.59, -1.50);
		sld = CharacterFromID("Fleetwood");
		sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
		sld.dialog.currentnode = "DTSG_Fleetwood_10";
		ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto1");
		TeleportCharacterToPosAy(sld, -9.81, 7.84, -20.79, 1.50);
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
	}
	
	else if (sQuestName == "DTSG_ProshloeDominika_12") {
		locCameraFromToPos(1.05, 18.74, -15.47, true, -3.05, 16.40, -14.08);
		//LAi_SetCheckMinHP(pchar, 1, false, "DTSG_Knippel_Smert");
		LAi_SetCheckMinHP(pchar, 1, true, "SkritoeBessmertie");
		//LAi_SetFightMode(pchar, true);
		LAi_SetWarriorType(pchar);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	
		for (i=1; i<=5; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_ValkSold_"+i, "sold_eng_"+(rand(7)+1), "man", "man", sti(pchar.rank), ENGLAND, 0, true, "soldier"));
			PlaceCharacter(sld, "rld", "random");
			LAi_SetWarriorType(sld);
			LAi_CharacterDisableDialog(sld);
			sld.CantLoot = true;
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_SetHP(sld, 60.0, 60.0);
		}
		for (i=6; i<=8; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_ValkSold_"+i, "citiz_"+(rand(9)+31), "man", "man", sti(pchar.rank), ENGLAND, 0, true, "soldier"));
			PlaceCharacter(sld, "rld", "random");
			LAi_SetWarriorType(sld);
			LAi_CharacterDisableDialog(sld);
			sld.CantLoot = true;
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_SetHP(sld, 60.0, 60.0);
		}
		sld = CharacterFromID("Fleetwood");
		LAi_SetCheckMinHP(sld, 10, true, "");
		ChangeCharacterAddressGroup(sld, PChar.location, "rld", "aloc2");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		
		for (i=1; i<=7; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_SasseksSold_"+i, "sold_eng_"+(rand(7)+1), "man", "man", sti(pchar.rank), ENGLAND, 0, true, "soldier"));
			PlaceCharacter(sld, "rld", "random");
			LAi_SetWarriorType(sld);
			LAi_CharacterDisableDialog(sld);
			sld.CantLoot = true;
			sld.location = "None";
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetHP(sld, 60.0, 60.0);
		}
		for (i=8; i<=10; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_SasseksSold_"+i, "citiz_"+(rand(9)+31), "man", "man", sti(pchar.rank), ENGLAND, 0, true, "soldier"));
			PlaceCharacter(sld, "rld", "random");
			LAi_SetWarriorType(sld);
			LAi_CharacterDisableDialog(sld);
			sld.CantLoot = true;
			sld.location = "None";
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetHP(sld, 60.0, 60.0);
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		//LAi_group_SetCheck("EnemyFight", "DTSG_ProshloeDominika_13");
		DoQuestCheckDelay("DTSG_ProshloeDominika_13", 5.0);
	}
	
	else if (sQuestName == "DTSG_Knippel_Smert") {
		LAi_KillCharacter(pchar);
		LAi_KillCharacter(pchar);
		ClearAllLogStrings();
		DoQuestCheckDelay("DTSG_Knippel_Smert_2", 1.5);
	}
	
	else if (sQuestName == "DTSG_Knippel_Smert_2") {
		GameOver("sea");
	}
	
	else if (sQuestName == "DTSG_ProshloeDominika_13") {
		for (i=1; i<=8; i++)
		{
			if (GetCharacterIndex("DTSG_ValkSold_"+i) != -1)
			{
				sld = CharacterFromID("DTSG_ValkSold_"+i);
				sld.lifeday = 0;
				sld.location = "None";
			}
		}
		
		n = Findlocation("Location_reserve_06");
		DeleteAttribute(&locations[n], "IslandId");
		DeleteAttribute(&locations[n], "type");
		DeleteAttribute(&locations[n], "models");
		DeleteAttribute(&locations[n], "environment");
		DeleteAttribute(&locations[n], "Box1");
		DeleteAttribute(&locations[n], "Box2");
		DeleteAttribute(&locations[n], "Box3");
		locations[n].id.label = "cabine";
		locations[n].filespath.models = "locations\inside\cabin01";
		locations[n].image = "loading\Capdeck_" + rand(4) + ".tga";
		//Sound
		locations[n].type = "boarding_cabine";
		//Models
		//Always
		locations[n].models.always.l1 = "cabin01";
		locations[n].models.always.l1.level = 65538;
		locations[n].models.always.locators = "cabin01_locators";

		locations[n].models.always.window = "cabin01_fonar";
		Locations[n].models.always.window.tech = "LocationWindows";
		locations[n].models.always.window.level = 65539;

		//Day
		locations[n].models.day.charactersPatch = "cabin01_patch";

		//Night
		locations[n].models.night.charactersPatch = "cabin01_patch";

		//Environment
		locations[n].environment.weather = "true";
		locations[n].environment.sea = "true";
		
		DoQuestReloadToLocation("Location_reserve_06", "rld", "loc2", "DTSG_ProshloeDominika_14");
	}
	
	else if (sQuestName == "DTSG_ProshloeDominika_14") {
		locCameraFromToPos(5.18, 22.17, 0.00, true, 1.96, 19.90, -2.00);
		DoQuestCheckDelay("DTSG_ProshloeDominika_14_1", 3.5);
		LAi_SetCurHPMax(pchar);
		LAi_GetCharacterMaxEnergy(pchar);
		//LAi_SetFightMode(pchar, true);
		LAi_SetFightMode(pchar, true);
		LAi_SetWarriorType(pchar);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		
		sld = CharacterFromID("Fleetwood");
		GiveItem2Character(sld, "pistol6");
		EquipCharacterByItem(sld, "pistol6");
		ChangeCharacterAddressGroup(sld, PChar.location, "rld", "aloc6");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		
		sld = GetCharacter(NPC_GenerateCharacter("DTSG_Graf_Sheffild", "huber_0", "man", "man", sti(pchar.rank), ENGLAND, -1, false, "quest"));
		sld.name = StringFromKey("Knippel_15");
		sld.lastname = StringFromKey("Knippel_16");
		ChangeCharacterAddressGroup(sld, PChar.location, "rld", "aloc2");
		LAi_SetWarriorType(sld);
		GiveItem2Character(sld, "blade_17");
		EquipCharacterByItem(sld, "blade_17");
		LAi_SetImmortal(sld, true);
		sld.CantLoot = true;
		LAi_SetHP(sld, 250.0, 250.0);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		
		sld = GetCharacter(NPC_GenerateCharacter("DTSG_MicleUinti", "off_eng_4", "man", "man", sti(pchar.rank), ENGLAND, -1, false, "quest"));
		sld.name = StringFromKey("Knippel_17");
		sld.lastname = StringFromKey("Knippel_18");
		ChangeCharacterAddressGroup(sld, PChar.location, "rld", "aloc4");
		GiveItem2Character(sld, "blade_15");
		EquipCharacterByItem(sld, "blade_15");
		GiveItem2Character(sld, "pistol6");
		EquipCharacterByItem(sld, "pistol6");
		LAi_SetHP(sld, 125.0, 125.0);
		sld.CantLoot = true;
		LAi_SetActorType(sld);
		LAi_ActorAttack(sld, PChar, "");
		LAi_group_MoveCharacter(sld, "EnemyFight");
		
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		
		PChar.quest.DTSG_MicleUinti_Ubit.win_condition.l1 = "NPC_Death";
		PChar.quest.DTSG_MicleUinti_Ubit.win_condition.l1.character = "DTSG_MicleUinti";
		PChar.quest.DTSG_MicleUinti_Ubit.win_condition = "DTSG_ProshloeDominika_15";
		
		DoQuestCheckDelay("DTSG_ProshloeDominika_14_0", 7.0);
	}
	
	else if (sQuestName == "DTSG_ProshloeDominika_14_0") {
		if (CharacterIsAlive("DTSG_MicleUinti"))
		{
			sld = CharacterFromID("DTSG_MicleUinti");
			LAi_KillCharacter(sld);
		}
	}
	
	else if (sQuestName == "DTSG_ProshloeDominika_14_1") {
		locCameraFromToPos(9.68, 21.90, -3.31, true, 7.03, 19.70, -1.37);
	}
	
	else if (sQuestName == "DTSG_ProshloeDominika_14_2") {
		locCameraFromToPos(0.02, 22.28, -3.61, true, 2.93, 19.70, -1.06);
	}
	
	else if (sQuestName == "DTSG_ProshloeDominika_15") {
		sld = CharacterFromID("DTSG_Graf_Sheffild");
		LAi_SetCurHP(sld, 150.0);
		LAi_SetImmortal(sld, false);
		LAi_SetCheckMinHP(sld, 1, true, "DTSG_ProshloeDominika_16");
		DoQuestCheckDelay("DTSG_ProshloeDominika_14_2", 1.0);
	}
	
	else if (sQuestName == "DTSG_ProshloeDominika_16") {
		LAi_RemoveCheckMinHP(pchar);
		LAi_SetActorType(pchar);
		sld = CharacterFromID("DTSG_Graf_Sheffild");
		LAi_SetActorType(sld);
		sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
		sld.dialog.currentnode = "DTSG_Graf_Sheffild_1";
		SetActorDialogAny2Pchar(sld.id, "", -1, 0.0);
		LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 2.0);
		
		sld = CharacterFromID("Fleetwood");
		LAi_SetActorType(sld);
	}
	
	else if (sQuestName == "DTSG_Graf_Sheffild_20") {
		sld = CharacterFromID("DTSG_Graf_Sheffild");
		LAi_KillCharacter(sld);
		DoQuestCheckDelay("DTSG_Graf_Sheffild_21", 2.7);
	}
	
	else if (sQuestName == "DTSG_Graf_Sheffild_21") {
		LAi_RemoveCheckMinHP(pchar);
		LAi_SetPlayerType(pchar);
		sld = CharacterFromID("Fleetwood");
		LAi_SetActorType(sld);
		sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
		sld.dialog.currentnode = "DTSG_Graf_Sheffild_22";
		LAi_SetActorType(sld);		
		LAi_ActorDialog(sld, pchar, "", 0, 0);
	}
	
	else if (sQuestName == "DTSG_SegodnyaVremya") {
		sld = CharacterFromID("Fleetwood");
		ChangeCharacterAddressGroup(sld, "none", "", "");
		SetMainCharacterIndex(GetCharacterIndex("Blaze"));
		PChar = GetMainCharacter();
		LAi_SetPlayerType(PChar);
		
		pchar.GenQuest.CabinLock = true;
		EndQuestMovie();
		QuestToSeaLogin_Launch();
		QuestToSeaLogin_PrepareLoc("Antigua", "Quest_Ships", "Quest_ship_1", false);
		DoQuestCheckDelay("DTSG_SegodnyaVremya_2", 3.5);
	}
	
	else if (sQuestName == "DTSG_SegodnyaVremya_2") {
		DeleteAttribute(pchar, "GenQuest.CabinLock");
		Sea_CabinStartNow();
		DoQuestCheckDelay("DTSG_SegodnyaVremya_3", 1.8);
	}
	
	else if (sQuestName == "DTSG_SegodnyaVremya_3") {			//ЭТАП 4
		sld = CharacterFromID("Knippel");
		sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
		sld.dialog.currentnode = "DTSG_Knippel_101";
		ChangeCharacterAddressGroup(sld, PChar.location, "rld", "loc1");
		LAi_SetActorType(pchar);
		LAi_SetActorType(sld);
		SetActorDialogAny2Pchar(sld.id, "", -1, 0.0);
		LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 2.0);
		LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 2.0);
	}
	
	else if (sQuestName == "DTSG_PikarRanen") {
		sld = CharacterFromID("DTSG_Mrt_Rocur");
		LAi_SetActorType(sld);
		LAi_ActorSetGroundSitMode(sld);
	}
	
	else if (sQuestName == "DTSG_KortniRanen") {
		DoQuestCheckDelay("hide_weapon", 1.2);
		LAi_group_Delete("EnemyFight");
		
		sld = CharacterFromID("DTSG_Mrt_Rocur");
		LAi_SetActorType(sld);
		
		sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
		sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
		sld.dialog.currentnode = "DTSG_Kortni_1";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
	}
	
	else if (sQuestName == "DTSG_Kortni_Vyprygnul") {
		PlaySound("Sea Battles\bolshoy_vsplesk_001.wav");
		DoQuestCheckDelay("DTSG_Kortni_Vyprygnul_2", 1.5);
	}
	
	else if (sQuestName == "DTSG_Kortni_Vyprygnul_2") {
		LAi_SetPlayerType(pchar);
		sld = CharacterFromID("DTSG_Mrt_Rocur");
		sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
		sld.dialog.currentnode = "DTSG_Kortni_PkCh_8";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
	}
	
	else if (sQuestName == "DTSG_Kortni_Vyprygnul_3") {
		DoQuestCheckDelay("hide_weapon", 1.2);
		DoQuestCheckDelay("DTSG_Kortni_Vyprygnul_4", 1.3);
	}
	
	else if (sQuestName == "DTSG_Kortni_Vyprygnul_4") {
		//sld = CharacterFromID("Knippel");
		sld = GetCharacter(CreateCharacterClone(CharacterFromID("Knippel"), 0));
		sld.id = "KnippelClone";
		sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
		sld.dialog.currentnode = "DTSG_Kortni_PkCh_12";
		ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		sld.location = "None";
	}
	
	else if (sQuestName == "DTSG_Kortni_Vyprygnul_5") {
		DoQuestCheckDelay("DTSG_Kortni_Vyprygnul_6", 2.5);
	}
	
	else if (sQuestName == "DTSG_Kortni_Vyprygnul_6") {
		//sld = CharacterFromID("Knippel");
		sld = CharacterFromID("KnippelClone");
		sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
		sld.dialog.currentnode = "DTSG_Kortni_PkCh_14";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	
	else if (sQuestName == "DTSG_Kortni_Vyprygnul_7") {
		LAi_EnableReload();
		Log_SetActiveAction("Reload");
		ChangeOfficersLoyality("good_all", 5);
		ChangeCharacterComplexReputation(pchar, "nobility", 5);
		ChangeCharacterComplexReputation(pchar, "authority", 5);
		ChangeCharacterComplexReputation(pchar, "fame", 5);
		ChangeCharacterHunterScore(PChar, "enghunter", 200);
		pchar.questTemp.DTSG_Kech = true;
		AddQuestRecord("DTSG", "18");
		CloseQuestHeader("DTSG");
		sld = CharacterFromID("Knippel");
		SetCharacterPerk(sld, "Bombardier");
		notification(StringFromKey("Knippel_19"), "Knippel");
	}
	
	else if (sQuestName == "DTSG_Kortni_Otkup_1") {
		StartQuestMovie(true, false, true);
		locCameraFromToPos(0.41, 3.87, 0.34, true, 0.20, 1.55, -3.74);
		LAi_SetActorType(pchar);
		ChangeCharacterAddressGroup(pchar, PChar.location, "rld", "loc2");
		
		sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
		sld.lifeday = 0;
		ChangeCharacterAddressGroup(sld, "none", "", "");
		
		sld = CharacterFromID("DTSG_Mrt_Rocur");
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, PChar.location, "rld", "aloc0");
		CharacterTurnToLoc(sld, "rld", "loc0");
		
		sld = GetCharacter(NPC_GenerateCharacter("DTSG_KortniClone", "off_eng_5", "man", "man", sti(PChar.rank), ENGLAND, -1, false, "quest"));
		sld.name = StringFromKey("Knippel_12");
		sld.lastname = StringFromKey("Knippel_13");
		GiveItem2Character(sld, "blade_16");
		EquipCharacterByItem(sld, "blade_16");
		GiveItem2Character(sld, "pistol5");
		EquipCharacterByItem(sld, "pistol5");
		sld.lifeday = 0;
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, PChar.location, "rld", "loc0");
		CharacterTurnToLoc(sld, "rld", "aloc0");
		
		DoQuestCheckDelay("DTSG_Kortni_Otkup_2", 1.1);
	}
	
	else if (sQuestName == "DTSG_Kortni_Otkup_2") {
		pchar.GenQuest.BlockDialogCamera = true;
		LAi_SetPlayerType(pchar);
		sld = CharacterFromID("DTSG_KortniClone");
		sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
		sld.dialog.currentnode = "DTSG_Kortni_LT_10";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
	}
	
	else if (sQuestName == "DTSG_Kortni_Otkup_3") {
		sld = CharacterFromID("DTSG_Mrt_Rocur");
		LAi_KillCharacter(sld);
		DoQuestCheckDelay("DTSG_Kortni_Otkup_4", 2.5);
	}
	
	else if (sQuestName == "DTSG_Kortni_Otkup_4") {
		EndQuestMovie();
		DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
		LAi_SetPlayerType(pchar);
		locCameraSleep(false);
		locCameraTarget(PChar);
		locCameraFollow();
		sld = CharacterFromID("DTSG_KortniClone");
		sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
		sld.dialog.currentnode = "DTSG_Kortni_LT_22";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	
	else if (sQuestName == "DTSG_Kortni_KechNeNash") {
		DeleteAttribute(pchar, "GenQuest.CannotTakeShip");
	}
	
	else if (sQuestName == "DTSG_KortniPotopil") {
		ChangeCharacterHunterScore(PChar, "enghunter", 200);
		CloseQuestHeader("DTSG");
		AddQuestRecord("DTSG", "22");
		Island_SetReloadEnableGlobal("Antigua", true);
		bQuestDisableMapEnter = false;
		LAi_LocationDisableOfficersGen("SentJons_town", false);
		Achievment_Set("ach_CL_114");
		sld = CharacterFromID("Knippel");
		SetCharacterPerk(sld, "Bombardier");
		notification(StringFromKey("Knippel_19"), "Knippel");
	}
	else
	{
		condition = false;
	}
	
	return condition;
}