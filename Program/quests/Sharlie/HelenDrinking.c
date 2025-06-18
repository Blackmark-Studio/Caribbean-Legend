// HelenDrinking / Попойка
void HelenDrinking_NoVisit(string qName) {
	DeleteAttribute(pchar, "questTemp.HelenDrinking.CanDrink");
	pchar.questTemp.HelenDrinking.Result = "no_visit";
	//pchar.questTemp.HelenDrinking = "no_visit";
	CloseQuestHeader("HelenDrinking");
}

void HelenDrinking_GoToHouse() {
	chrDisableReloadToLocation = true;
	pchar.GenQuest.HunterLongPause = true;
	
	sld = CharacterFromID("Helena");
	LAi_SetActorType(sld);
	
	LAi_ActorRunToLocation(sld, "reload", "reload1", "SantaCatalina_houseSp3", "reload", "reload2", "OpenTheDoors", -1);
	SetFunctionLocationCondition("HelenDrinking_GoToStreet", "SantaCatalina_houseSp3", false);
}

void HelenDrinking_GoToStreet(string qName) {
	chrDisableReloadToLocation = true;
	
	sld = CharacterFromID("Helena");
	LAi_ActorRunToLocation(sld, "reload", "reload1", "SantaCatalina_town", "reload", "houseSp3", "OpenTheDoors", -1);
	SetFunctionLocationCondition("HelenDrinking_GoToTavern", "SantaCatalina_town", false);
}

void HelenDrinking_GoToTavern(string qName) {
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(&locations[FindLocation("SantaCatalina_town")], true);
	
	sld = CharacterFromID("Helena");
	FreeSitLocator("SantaCatalina_tavern", "sit6");
	LAi_ActorRunToLocation(sld, "reload", "reload4_back", "SantaCatalina_tavern", "sit", "sit6", "", -1);
	
	int iRank = sti(pchar.rank) + 10;
	int iScl = 60;
	sld = GetCharacter(NPC_GenerateCharacter("HelenDrinking_Francois", "off_fra_4", "man", "man", iRank, FRANCE, -1, false, "quest"));
	sld.name = StringFromKey("HelenDrinking_1");
	sld.lastname = StringFromKey("HelenDrinking_2");
	FantomMakeCoolFighter(sld, iRank, iScl, iScl, "saber", "", "grapeshot", iScl*2);
	sld.rank = iRank;
	sld.cirassId = Items_FindItemIdx("cirass3");
	sld.MultiFighter = 1.4;
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	if (MOD_SKILL_ENEMY_RATE > 7) sld.MultiFighter = 1.8; // мультифайтер
	sld.viper = true;
	ChangeCharacterAddressGroup(sld, "SantaCatalina_town", "reload", "houseSp21");
	LAi_SetActorType(sld);
	FreeSitLocator("SantaCatalina_tavern", "sit4");
	LAi_ActorRunToLocation(sld, "reload", "reload4_back", "SantaCatalina_tavern", "sit", "sit4", "", -1);
	
	sld = GetCharacter(NPC_GenerateCharacter("HelenDrinking_Gypsy", "gipsy_" + (rand(3)+1), "woman", "woman", 1, ENGLAND, 0, false, "quest"));
	sld.dialog.filename = "Quest\Saga\OtherNPC.c";
	sld.dialog.currentnode = "helendrinking_gypsy";
	sld.greeting = "gipsy";
	sld.talker = true;
	ChangeCharacterAddressGroup(sld, "SantaCatalina_town", "officers", "reload4_1");
	LAi_SetStayType(sld);
}

void HelenDrinking_TalkedToGypsy() {
	sld = CharacterFromID("HelenDrinking_Gypsy");
	LAi_CharacterDisableDialog(sld);
	LAi_SetCitizenType(sld);
	
	sld = CharacterFromID("Helena");
	if (sld.location != "SantaCatalina_tavern") {
		ChangeCharacterAddressGroup(sld, "SantaCatalina_tavern", "sit", "sit6");
	}
	
	sld = CharacterFromID("HelenDrinking_Francois");
	if (sld.location != "SantaCatalina_tavern") {
		ChangeCharacterAddressGroup(sld, "SantaCatalina_tavern", "sit", "sit4");
	}
	
	chrDisableReloadToLocation = false;
	bDisableFastReload = true;
	LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", true);
	LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", true);
	LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", true);
	SetFunctionLocationCondition("HelenDrinking_InTavern", "SantaCatalina_tavern", false);
}

void HelenDrinking_InTavern(string qName) {
	chrDisableReloadToLocation = true;
	bDisableFastReload = false;
	LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", false);
	LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", false);
	LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", false);
	
	FreeSitLocator("SantaCatalina_tavern", "sit1");
	FreeSitLocator("SantaCatalina_tavern", "sit2");
	FreeSitLocator("SantaCatalina_tavern", "sit3");
	
	sld = CharacterFromID("HelenDrinking_Francois");
	LAi_SetActorType(sld);
	LAi_ActorSetSitMode(sld);
	
	FreeSitLocator("SantaCatalina_tavern", "sit7");
	ChangeCharacterAddressGroup(pchar, "SantaCatalina_tavern", "sit", "sit7");
	LAi_SetSitType(pchar);
	
	sld = CharacterFromID("Helena");
	LAi_SetActorType(sld);
	LAi_ActorSetSitMode(sld);
	sld.dialog.currentnode = "drinking_in_tavern";
	LAi_ActorDialogDelay(sld, pchar, "", 1.0);
}

void HelenDrinking_TavernChange() {
	pchar.questTemp.HelenDrinking.InTavern = true;
	
	if (GetHour() < 19) {
		WaitDate("", 0, 0, 0, 19 - GetHour(), 0);
	}
	
	bOk = false;
			
	for (i = 0; i < MAX_CHARACTERS; i++) {
		sld = GetCharacter(i);
		
		if (sld.id == "Blaze" || sld.id == "Helena" || sld.id == "HelenDrinking_Francois") {
			continue;
		}
		
		if (sld.id == "SantaCatalina_tavernkeeper" || sld.id == "SantaCatalina_waitress") {
			continue;
		}
		
		if (sld.location != "SantaCatalina_tavern") {
			continue;
		}
		
		if (CheckAttribute(sld, "CityType") && !bOk && sld.location.locator != "sit1" && sld.location.locator != "sit3") {
			bOk = true;
			continue;
		}
		
		ChangeCharacterAddressGroup(sld, "none", "", "");
	}
	
	sld = CharacterFromID("Helena");
	ChangeCharacterAddressGroup(sld, "SantaCatalina_tavern", "sit", "sit1");
	
	DoFunctionReloadToLocation("SantaCatalina_tavern", "sit", "sit3", "HelenDrinking_TavernSpeak");
}

void HelenDrinking_TavernSpeak() {
	sld = CharacterFromID("Helena");
	sld.dialog.currentnode = "drinking_my_background";
	LAi_ActorDialogDelay(sld, pchar, "", 1.0);
}

void HelenDrinking_TavernEmpty() {
	if (GetHour() < 23) {
		WaitDate("", 0, 0, 0, 23 - GetHour(), 0);
	}
	
	for (i = 0; i < MAX_CHARACTERS; i++) {
		sld = GetCharacter(i);
		
		if (sld.id == "Blaze" || sld.id == "Helena") {
			continue;
		}
		
		if (sld.location != "SantaCatalina_tavern") {
			continue;
		}
		
		ChangeCharacterAddressGroup(sld, "none", "", "");
	}
	
	sld = CharacterFromID("Helena");
	ChangeCharacterAddressGroup(sld, "SantaCatalina_tavern", "sit", "sit_front4");
	
	DoFunctionReloadToLocation("SantaCatalina_tavern", "sit", "sit_base4", "HelenDrinking_TavernSpeak1");
}

void HelenDrinking_TavernSpeak1() {
	sld = CharacterFromID("Helena");
	sld.dialog.currentnode = "drinking_game";
	LAi_ActorDialogDelay(sld, pchar, "", 1.0);
}

void HelenDrinking_GoToTavernRoom() {
	pchar.questTemp.HelenDrinking.Result = "refused_game";
	//pchar.questTemp.HelenDrinking = "refused_game";
	DoFunctionReloadToLocation("SantaCatalina_tavern_upstairs", "goto", "goto1", "HelenDrinking_SelfDialog");
}

void HelenDrinking_SelfDialog() {
	pchar.questTemp.HelenDrinking.RefusedGame = true;
	LAi_SetPlayerType(pchar);
	DoQuestCheckDelay("TalkSelf_Quest", 1.0);
}

void HelenDrinking_Sleep() {
	DeleteAttribute(pchar, "questTemp.HelenDrinking.InTavern");
	
	sld = CharacterFromID("Helena");
	ChangeCharacterAddressGroup(sld, "SantaCatalina_houseSp3_bedroom", "goto", "goto1");
	sld.dialog.currentnode = "Helena_wait";
	LAi_SetStayType(sld);
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	
	sld = CharacterFromID("SantaCatalina_tavernkeeper");
	ChangeCharacterAddressGroup(sld, "SantaCatalina_Tavern", "barmen", "stay");
	sld = CharacterFromID("SantaCatalina_waitress");
	ChangeCharacterAddressGroup(sld, "SantaCatalina_Tavern", "waitress", "barmen");
	
	//pchar.questTemp.HelenDrinking = "sleep";
	
	LAi_SetPlayerType(pchar);
	
	chrDisableReloadToLocation = false;
	bDisableFastReload = true;
	SetFunctionLocationCondition("HelenSleep_InTavern", "Clone_location_1", false);
	LAi_LocationDisableOfficersGen("Clone_location_1", true);
}

void HelenDrinking_LightsOut() {
	pchar.questTemp.HelenDrinking.Result = "lost";
	//pchar.questTemp.HelenDrinking = "lost";
	
	LAi_SetActorType(pchar);
	LAi_ActorSetSitMode(pchar);
	LAi_ActorAnimation(pchar, "Sit_Death", "", 2.7);
	DoQuestFunctionDelay("HelenDrinking_LightsOut1", 2.7);
}

void HelenDrinking_LightsOut1NoArg() {
	HelenDrinking_LightsOut1("");
}

void HelenDrinking_LightsOut1(string qName) {
	CloneLocation("SantaCatalina_tavern_upstairs", "Clone_location");
	ref loc = &locations[FindLocation("Clone_location")];
	loc.reload.l1.go = "Clone_location_1";
	LAi_LocationFightDisable(loc, true);
	
	DeleteAttribute(loc, "box1");
	loc.box1 = Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear());
	loc.box1.items.jewelry28 = 1;
	
	CloneLocation("SantaCatalina_tavern", "Clone_location_1");
	loc = &locations[FindLocation("Clone_location_1")];
	loc.reload.l1.go = "Clone_location";
	DeleteAttribute(loc, "reload.l2");
	DeleteAttribute(loc, "habitues");
	
	DeleteAttribute(pchar, "GenQuest.CamShuttle");
	
	EndQuestMovie();
	SetCurrentTime(12, 0);
	pchar.questTemp.TimeLock = true;
	InterfaceStates.Buttons.Save.enable = false;
	bDisableCharacterMenu = true;
	DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
	DoFunctionReloadToLocation("Clone_location", "goto", "goto1", "HelenDrinking_Sleep");
	
	ResetSound();
	SetMusic("");
	pchar.questTemp.lockedMusic = true;
}

void HelenDrinking_ExitTavern() {
	if (GetHour() > 0) {
		WaitDate("", 0, 0, 0, 2, 0);
	}
	
	DoFunctionReloadToLocation("SantaCatalina_town", "reload", "reload4", "HelenDrinking_GoToSvenson");
}

void HelenDrinking_GoToSvenson() {
	pchar.questTemp.HelenDrinking.Result = "won";
	
	LAi_SetPlayerType(pchar);
	
	sld = CharacterFromID("Helena");
	ChangeCharacterAddressGroup(sld, "SantaCatalina_town", "goto", "goto20");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocator(sld, "reload", "houseS1", "HelenDrinking_WaitAtSvenson", -1);
	
	//sld = CharacterFromID("HelenDrinking_Francois");
	//ChangeCharacterAddressGroup(sld, "SantaCatalina_town", "goto", "goto12");
	//LAi_SetActorType(sld);
	//LAi_ActorRunToLocation(sld, "reload", "gate_back", "none", "", "", "", -1);
}

void HelenDrinking_EnterSvenson() {
	DoFunctionReloadToLocation("SantaCatalina_houseS1", "reload", "reload1", "HelenDrinking_AtSvenson");
}

void HelenDrinking_AtSvenson() {
	sld = CharacterFromID("JS_girl");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	
	sld = CharacterFromID("Svenson");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	
	sld = CharacterFromID("Helena");
	ChangeCharacterAddressGroup(sld, "SantaCatalina_houseS1", "goto", "goto1");
	LAi_SetActorType(sld);
	sld.dialog.currentnode = "drinking_give_key";
	LAi_ActorDialogDelay(sld, pchar, "", 1.0);
}

void HelenDrinking_GotKey() {
	bDisableFastReload = true;
	chrDisableReloadToLocation = false;
	LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload1", true);
	
	sld = ItemsFromID("cask_whisky");
	sld.pricebak = sld.price;
	sld.price = 0;
	
	sld = &locations[FindLocation("SantaCatalina_houseS1_residence")];
	DeleteAttribute(sld, "private1");
	
	sld.private1 = Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear());
	sld.private1.key = "key3";
	sld.private1.key.delItem = true;
	sld.private1.items.cask_whisky = 1;
	sld.private1.items.chest = 2;
	
	pchar.quest.HelenDrinking_GotWhiskey.win_condition.l1 = "item";
	pchar.quest.HelenDrinking_GotWhiskey.win_condition.l1.item = "cask_whisky";
	pchar.quest.HelenDrinking_GotWhiskey.function = "HelenDrinking_GotWhiskey";
}

void HelenDrinking_GotWhiskey(string qName) {
	sld = CharacterFromID("Helena");
	LAi_SetStayType(sld);
	sld.dialog.currentnode = "drinking_got_whiskey";
}

void HelenDrinking_JoanEnter() {
	chrDisableReloadToLocation = true;
	bDisableFastReload = false;
	LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload1", false);
	
	sld = CharacterFromID("Helena");
	LAi_SetActorType(sld);
	
	sld = &locations[FindLocation("SantaCatalina_houseS1_residence")];
	DeleteAttribute(sld, "private1");
	sld.private1.key = "key3";
	
	sld = CharacterFromID("JS_girl");
	ChangeCharacterAddressGroup(sld, "SantaCatalina_houseS1", "reload", "reload1");
	LAi_SetActorType(sld);
	LAi_ActorTurnToCharacter(sld, pchar);
	DoQuestFunctionDelay("HelenDrinking_JoanDialog", 1.0);
}

void HelenDrinking_JoanDialog(string qName) {
	sld = CharacterFromID("JS_girl");
	sld.greeting = "";
	sld.dialog.currentnode = "helendrinking_joan";
	LAi_CharacterPlaySound(sld, "w_death5");
	LAi_ActorDialogDelay(sld, pchar, "", 1.0);
}

void HelenDrinking_JoanDialog1() {
	sld = CharacterFromID("Helena");
	sld.dialog.currentnode = "joan";
	LAi_ActorDialogDelay(sld, pchar, "", 1.0);
}

void HelenDrinking_JoanDialog2() {
	sld = CharacterFromID("JS_girl");
	sld.dialog.currentnode = "helendrinking_joan_2";
	LAi_ActorDialogDelay(sld, pchar, "", 1.0);
}

void HelenDrinking_JoanDialog3() {
	sld = CharacterFromID("Helena");
	sld.dialog.currentnode = "joan_1";
	LAi_ActorDialogDelay(sld, pchar, "", 1.0);
}

void HelenDrinking_GoToShipyard() {
	//if (GetHour() < 7) {
	//	WaitDate("", 0, 0, 0, 7 - GetHour(), 0);
	//}
	if (GetHour() < 24) {
		WaitDate("", 0, 0, 0, 24 - GetHour(), 0);
	}
	
	sld = CharacterFromID("SantaCatalina_shipyarder");
	LAi_RemoveLoginTime(sld);
	DoFunctionReloadToLocation("SantaCatalina_shipyard", "goto", "goto3", "HelenDrinking_ShipyardDialog");
	
	sld = CharacterFromID("JS_girl");
	sld.greeting = "joanna";
	sld.dialog.currentnode = "js_girl";
	ChangeCharacterAddressGroup(sld, "SantaCatalina_houseS1", "barmen", "stay");
	LAi_SetOwnerType(sld);
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	
	sld = CharacterFromID("Svenson");
	ChangeCharacterAddressGroup(sld, "Santacatalina_houseS1_residence", "sit", "sit1");
}

void HelenDrinking_ShipyardDialog() {
	sld = CharacterFromID("SantaCatalina_shipyarder");
	sld.dialog.currentnode = "helendrinking_buy_rainbow";
	LAi_SetActorType(pchar);
	LAi_ActorDialogDelay(pchar, sld, "", 0.0);
}

void HelenDrinking_GoToFort() {
	//if (GetHour() < 12) {
	//	WaitDate("", 0, 0, 0, 12 - GetHour(), 0);
	//}
	if (GetHour() < 21) {
		WaitDate("", 0, 0, 0, 21 - GetHour(), 0);
	}
	
	DoFunctionReloadToLocation("SantaCatalina_fort", "goto", "goto43", "HelenDrinking_AtFort");
}

void HelenDrinking_AtFort() {
	StartQuestMovie(true, false, true);
	for (i = 0; i < MAX_CHARACTERS; i++) {
		sld = GetCharacter(i);
		
		if (sld.location != "SantaCatalina_fort") {
			continue;
		}
		
		if (!CheckAttribute(sld, "CityType")) {
			continue;
		}
		
		if (sld.CityType == "soldier" || sld.CityType == "fortPatrol") {
			ChangeCharacterAddressGroup(sld, "none", "", "");
		}
	}
	
	sld = CharacterFromID("Helena");
	ChangeCharacterAddressGroup(sld, "SantaCatalina_fort", "goto", "goto23");
	LAi_SetActorType(sld);
	LAi_ActorTurnToLocator(sld, "goto", "goto03");	
	LAi_ActorSetGroundSitMode(sld);
	sld.dialog.currentnode = "drinking_at_fort";
	LAi_ActorDialogDelay(sld, pchar, "", 4.0);
	
	LAi_SetActorType(pchar);
	LAi_ActorTurnToLocator(pchar, "goto", "goto02");
	LAi_SetGroundSitType(pchar);
	
	string sitLocs[6];
	string sitGroups[6];
	sitLocs[0] = "goto33";
	sitGroups[0] = "goto";
	sitLocs[1] = "goto03";
	sitGroups[1] = "goto";
	sitLocs[2] = "goto53";
	sitGroups[2] = "goto";
	sitLocs[3] = "soldier13";
	sitGroups[3] = "soldiers";
	sitLocs[4] = "goto13";
	sitGroups[4] = "goto";
	sitLocs[5] = "goto63";
	sitGroups[5] = "goto";
	string layLocs[2];
	string layGroups[2];
	layLocs[0] = "patrol03";
	layGroups[0] = "patrol";
	layLocs[1] = "soldier12";
	layGroups[1] = "soldiers";
	
	for (int i = 0; i < 6; i++) {
		sld = GetCharacter(NPC_GenerateCharacter("HelenDrinking_SitSoldier_" + i, "sold_eng_" + (1 + rand(7)), "man", "man", 1, ENGLAND, 0, true, "soldier"));
		ChangeCharacterAddressGroup(sld, "SantaCatalina_fort", sitGroups[i], sitLocs[i]);
		LAi_SetGroundSitType(sld);
	}
	
	for (i = 0; i < 2; i++) {
		sld = GetCharacter(NPC_GenerateCharacter("HelenDrinking_LaySoldier_" + i, "sold_eng_" + (1 + rand(7)), "man", "man", 1, ENGLAND, 0, true, "soldier"));
		ChangeCharacterAddressGroup(sld, "SantaCatalina_fort", layGroups[i], layLocs[i]);
		LAi_SetLayType(sld);
	}
	locCameraFromToPos(0.37, 44.35, 75.87, true, -6.18, 43.18, 76.87);
	pchar.GenQuest.CamShuttle = 0;
	SetCamShuttle(loadedLocation);
}

void HelenDrinking_OfficerAtFort() {
	sld = GetCharacter(NPC_GenerateCharacter("HelenDrinking_FortOfficer", "off_eng_" + (1 + rand(3)), "man", "man", 1, ENGLAND, 0, true, "soldier"));
	ChangeCharacterAddressGroup(sld, "SantaCatalina_fort", "goto", "goto22");
	LAi_SetActorType(sld);
	sld.dialog.FileName = "Quest\Saga\OtherNPC.c";
	sld.greeting = "soldier_arest";
	sld.dialog.currentnode = "helendrinking_fort_officer";
	//sld.GenQuest.CantRun = true;
	//CheckAndSetOverloadMode(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	LAi_Fade("", "");
	DoQuestFunctionDelay("HelenDrinking_OfficerAtFort_2", 0.5);
	DoQuestFunctionDelay("HelenDrinking_OfficerAtFort_3", 1.0);
}

void HelenDrinking_OfficerAtFort_2(string qName)
{	
	locCameraFromToPos(0.37, 44.35, 75.87, true, -6.18, 43.18, 76.87);
}
void HelenDrinking_OfficerAtFort_3(string qName)
{	
	locCameraSleep(true);
}

void HelenDrinking_FortDialog() {
	sld = CharacterFromID("Helena");
	sld.dialog.currentnode = "drinking_at_fort_7_1";
	LAi_ActorDialogDelay(sld, pchar, "", 1.5);
}

void HelenDrinking_FortDialog2() {
	sld = CharacterFromID("HelenDrinking_FortOfficer");
	sld.dialog.currentnode = "helendrinking_fort_officer_1";
	LAi_ActorDialogDelay(sld, pchar, "", 1.5);
}

void HelenDrinking_FortDialog4() {
	sld = CharacterFromID("HelenDrinking_FortOfficer");
	sld.dialog.currentnode = "helendrinking_fort_officer_2";
	LAi_ActorDialogDelay(sld, pchar, "", 1.5);
}

void HelenDrinking_FortDialog1() {
	sld = CharacterFromID("Helena");
	sld.dialog.currentnode = "drinking_at_fort_8";
	LAi_ActorDialogDelay(sld, pchar, "", 1.5);
}

void HelenDrinking_FortDialog3() {
	sld = CharacterFromID("Helena");
	sld.dialog.currentnode = "drinking_at_fort_7_2";
	LAi_ActorDialogDelay(sld, pchar, "", 1.5);
}

void HelenDrinking_GoToVillage() {
	//if (GetHour() < 18) {
	//	WaitDate("", 0, 0, 0, 18 - GetHour(), 0);
	//}
	if (GetHour() < 22) {
		WaitDate("", 0, 0, 0, 22 - GetHour(), 0);
	}
	
	DoFunctionReloadToLocation("Miskito_village", "sit", "ground2", "HelenDrinking_AtMiskito");
}

void HelenDrinking_AtMiskito() {
	sld = CharacterFromID("Helena");
	ChangeCharacterAddressGroup(sld, "Miskito_village", "sit", "ground1");
	TeleportCharacterToLocatorIgnoreCollision(sld, "sit", "ground1");
	LAi_SetActorType(sld);
	LAi_ActorSetGroundSitMode(sld);
	sld.dialog.currentnode = "drinking_at_miskito";
	LAi_ActorDialogDelay(sld, pchar, "", 0.0);
	
	sld = GetCharacter(NPC_GenerateCharacter("HelenDrinking_Native", "Miskito_" + (1 + rand(5)), "man", "man", 1, ENGLAND, 0, true, "native"));
	//sld.dialog.FileName = "Quest\Saga\OtherNPC.c";
	//sld.dialog.currentnode = "helendrinking_native";
	//sld.greeting = "indian_male";
	sld.name = GetIndianName(MAN);
	sld.lastname = "";
	ChangeCharacterAddressGroup(sld, "Miskito_village", "quest", "teleport1");
	LAi_SetActorType(sld);
	LAi_ActorSetGroundSitMode(sld);
	CharacterTurnByLocInstant(sld, "soldiers", "protector1");
	
	for (int i = 1; i <= 2; i++) {
		if (GetCharacterIndex("MiskitoSit1_" + i) >= 0) {
			sld = CharacterFromID("MiskitoSit1_" + i);
			ChangeCharacterAddressGroup(sld, "none", "", "");
		}
	}
	
	TeleportCharacterToLocatorIgnoreCollision(pchar, "sit", "ground2");
	locCameraFromToPos(-12.00, 1.94, 4.50, true, 10.00, -5.20, 10.00);
}

void HelenDrinking_GoToPerlas() {
	sld = CharacterFromID("SantaCatalina_shipyarder");
	LAi_SetLoginTime(sld, 6.0, 21.99);
	
	if (CheckAttribute(pchar, "quest.contraband.CurrentPlace") && pchar.quest.contraband.CurrentPlace == "Shore54") {
		RemoveSmugglersFromShore();
		pchar.Quest.Rand_Smuggling.Over = "yes";
	}
	
	WaitDate("", 0, 0, 0, 5, 0);
	
	sld = ItemsFromID("fire");
	sld.shown = true;
	sld.startLocation = "Shore54";
	sld.startLocator = "fire";
	
	sld = &locations[FindLocation("Shore54")];
	sld.fire = true;
	
	DoFunctionReloadToLocation("Shore54", "smugglers", "smuggler02", "HelenDrinking_AtPerlas");
}

void HelenDrinking_AtPerlas() {
	DeleteAttribute(pchar, "questTemp.lockedMusic");
	ResetSound();
	SetMusic("music_way_back_then");
	
	LAi_SetActorType(pchar);
	LAi_ActorSetGroundSitMode(pchar);
	CharacterTurnByLocInstant(pchar, "smugglers", "smugglerload");
	
	sld = CharacterFromID("Helena");
	ChangeCharacterAddressGroup(sld, "Shore54", "smugglers", "smuggler03");
	LAi_SetActorType(sld);
	LAi_ActorSetGroundSitMode(sld);
	CharacterTurnByLocInstant(sld, "smugglers", "smugglerload");
	LAi_Actor2WaitDialog(pchar, sld);
	sld.dialog.currentnode = "drinking_at_perlas";
	LAi_ActorDialogDelay(sld, pchar, "", 0.0);
	
	sld = GetCharacter(NPC_GenerateCharacter("HelenDrinking_Poorman", "panhandler_6", "man", "man", 1, ENGLAND, -1, false, "quest"));
	SetSPECIAL(sld, 7, 7, 7, 7, 7, 7, 7);
	InitStartParam(sld);
	sld.rank = 1;
	sld.name = StringFromKey("HelenDrinking_3");
	sld.lastname = StringFromKey("HelenDrinking_4");
	SetCharacterPerk(sld, "HPPlus");
	SetCharacterPerk(sld, "EnergyPlus");
	SetCharacterPerk(sld, "Brander");
	SetCharacterPerk(sld, "Troopers");
	sld.dialog.FileName = "Quest\Saga\OtherNPC.c";
	sld.dialog.currentnode = "helendrinking_poorman";
	sld.greeting = "poorman_male";
	GiveItem2Character(sld, "unarmed");
	EquipCharacterbyItem(sld, "unarmed"); 
	ChangeCharacterAddressGroup(sld, "Shore54", "smugglers", "smuggler01");
	LAi_SetActorType(sld);
	LAi_ActorSetGroundSitMode(sld);
	locCameraFromToPos(11.49, 2.29, -6.92, true, 6.93, -2.49, 3.89);
}

void HelenDrinking_PoormanTalk() {
	ChangeShowIntarface();
	sld = CharacterFromID("HelenDrinking_Poorman");
	LAi_Actor2WaitDialog(pchar, sld);
	LAi_ActorDialogDelay(sld, pchar, "", 0.0);
	locCameraFromToPos(7.03, 1.97, -2.43, true, 14.37, -0.70, -6.17);
}

void HelenDrinking_AddRainbow() {
	sld = ItemsFromID("fire");
	sld.shown = false;
	sld = &locations[FindLocation("Shore54")];
	DeleteAttribute(sld, "fire");
	
	if (!CheckAttribute(pchar, "questTemp.HelenDrinking.BoughtRainbow")) {
		sld = CharacterFromID("HelenDrinking_Poorman");
		sld.lifeday = 0;
		return;
	}
	
	ref shipOwner;
	if (pchar.ship.type == SHIP_NOTUSED) {
		shipOwner = GetMainCharacter();
	} else {
		shipOwner = CharacterFromID("HelenDrinking_Poorman");
	}
	
	shipOwner.ship.type = GenerateShipExt(SHIP_TARTANE, true, shipOwner);
	pchar.questTemp.HelenDrinking.Rainbow = shipOwner.ship.type;
	shipOwner.ship.name = StringFromKey("HelenDrinking_5");
	SetBaseShipData(shipOwner);
	NullCharacterGoods(shipOwner);
	SetCrewQuantityOverMax(shipOwner, 0);
	UpgradeShipParameter(shipOwner, "SpeedRate");
	UpgradeShipParameter(shipOwner, "TurnRate");
	UpgradeShipParameter(shipOwner, "HP");
	UpgradeShipParameter(shipOwner, "WindAgainstSpeed");
	UpgradeShipParameter(shipOwner, "Capacity");
	UpgradeShipParameter(shipOwner, "MaxCrew");
	
	NullCharacterGoods(shipOwner);
	SetCharacterGoods(shipOwner, GOOD_RUM, GetCharacterFreeSpace(shipOwner, GOOD_RUM) / 2);
	SetCharacterGoods(shipOwner, GOOD_WINE, GetCharacterFreeSpace(shipOwner, GOOD_WINE));
	
	sld = CharacterFromID("HelenDrinking_Poorman");
	sld.Dialog.Filename = "Enc_Officer_dialog.c";
	sld.Dialog.currentnode = "hired";
	sld.greeting = "officer_hire";
	LAi_SetOfficerType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	
	sld.quest.OfficerPrice = sti(pchar.rank) * 100;
	sld.loyality = MAX_LOYALITY;
	sld.OfficerWantToGo.DontGo = true;
	sld.Payment = true;
	sld.location = "none";
	sld.DontClearDead = true;
	SaveCurrentNpcQuestDateParam(sld, "HiredDate");
	
	if (sld.ship.type != SHIP_NOTUSED) {
		SetCompanionIndex(pchar, -1, sti(sld.index));
	} else {
		AddPassenger(pchar, sld, false);
	}
}

void HelenSleep_InTavern(string qName) {
	CloneLocation("SantaCatalina_town", "Clone_location");
	ref loc = &locations[FindLocation("Clone_location")];
	
	loc.DisableCitizens = true;
	LAi_LocationDisableOfficersGen("Clone_location", true);
	
	DeleteAttribute(loc, "reload");
	
	loc.reload.l11.name = "houseS1";
	loc.reload.l11.go = "Clone_location_1";
	loc.reload.l11.emerge = "reload1";
	loc.reload.l11.autoreload = "0";
	loc.reload.l11.label = "Svensons_house";
	
	SetFunctionLocationCondition("HelenSleep_InTown", "Clone_location", false);
}

void HelenSleep_InTown(string qName) {
	CloneLocation("SantaCatalina_houseS1", "Clone_location_1");
	ref loc = &locations[FindLocation("Clone_location_1")];
	
	DeleteAttribute(loc, "reload");
	loc.reload.l2.name = "reload2";
	loc.reload.l2.go = "Clone_location_2";
	loc.reload.l2.emerge = "reload1";
	loc.reload.l2.autoreload = "0";
	loc.reload.l2.label = "Cabinet";
	
	CloneLocation("SantaCatalina_houseS1_residence", "Clone_location_2");
	loc = &locations[FindLocation("Clone_location_2")];
	DeleteAttribute(loc, "reload");
	loc.type = "none";
	
	sld = CharacterFromID("Svenson");
	sld = GetCharacter(CreateCharacterClone(sld, -1));
	sld.id = "SvensonClone";
	ChangeCharacterAddressGroup(sld, "Clone_location_2", "sit", "sit1");
	LAi_SetHuberType(sld);
	sld.dialog.currentnode = "helensleep";
	
	Log_info(StringFromKey("HelenDrinking_6"));
	Log_info(StringFromKey("HelenDrinking_7"));
	SetMusic("music_terrain");
}

void HelenSleep_SvensonThrowOut() {
	sld = CharacterFromID("SvensonClone");
	sld.lifeday = 0;
	
	ref loc = &locations[FindLocation("Clone_location")];
	DeleteAttribute(loc, "reload");
	loc.type = "none";
	
	loc.reload.l3.name = "reload3_back";
	loc.reload.l3.go = "Clone_location_1";
	loc.reload.l3.emerge = "reload1";
	loc.reload.l3.autoreload = "0";
	loc.reload.l3.label = "Residence";
	
	loc.reload.l7.name = "reload7_back";
	loc.reload.l7.go = "Clone_location_2";
	loc.reload.l7.emerge = "reload1";
	loc.reload.l7.autoreload = "0";
	loc.reload.l7.label = "Church";
	
	DoFunctionReloadToLocation("Clone_location", "officers", "houseS1_1", "HelenSleep_SvensonThrownOut");
}

void HelenSleep_SvensonThrownOut() {
	LAi_SetActorType(pchar);
	LAi_ActorTurnToLocator(pchar, "goto", "goto11");
	
	sld = CharacterFromID("Helena");
	sld = GetCharacter(CreateCharacterClone(sld, 0));
	sld.id = "HelenaClone";
	ChangeCharacterAddressGroup(sld, "Clone_location", "quest", "helen");
	CharacterTurnByLocInstant(sld, "quest", "mary");
	
	rCharacter = CharacterFromID("Mary");
	rCharacter = GetCharacter(CreateCharacterClone(rCharacter, 0));
	rCharacter.id = "MaryClone";
	ChangeCharacterAddressGroup(rCharacter, "Clone_location", "quest", "mary");
	CharacterTurnByLocInstant(rCharacter, "quest", "helen");
	
	LAi_SetActorType(sld);
	LAi_SetActorType(rCharacter);
	LAi_Actor2WaitDialog(rCharacter, sld);
	LAi_ActorDialogDelay(sld, rCharacter, "", 1.0);
	
	DoQuestFunctionDelay("HelenSleep_GirlsGoAway", 8.0);
	
	CloneLocation("SantaCatalina_townhall", "Clone_location_1");
	ref loc = &locations[FindLocation("Clone_location_1")];
	DeleteAttribute(loc, "reload");
	loc.type = "helensleep_townhall";
	
	CloneLocation("SantaCatalina_church", "Clone_location_2");
	loc = &locations[FindLocation("Clone_location_2")];
	DeleteAttribute(loc, "reload");
	loc.type = "helensleep_church";
	loc.DisableCitizens = true;
}

void HelenSleep_GirlsGoAway(string qName) {
	sld = CharacterFromID("HelenaClone");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload3_back", "none", "", "", "", -1);
	
	sld = CharacterFromID("MaryClone");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload7_back", "none", "", "", "", -1);
	
	DoQuestCheckDelay("pchar_back_to_player", 3.0);
	
	sld = GetCharacter(NPC_GenerateCharacter("HelenSleep_AmeliaHelen", "gipsy_3", "woman", "towngirl", 10, PIRATE, -1, false, "citizen"));
	sld.name = StringFromKey("HelenDrinking_8");
	sld.lastname = StringFromKey("HelenDrinking_9");
	sld.dialog.FileName = "Quest\Saga\OtherNPC.c";
	sld.dialog.currentnode = "helensleep_amelia_helen";
	ChangeCharacterAddressGroup(sld, "Clone_location_1", "goto", "governor1");
	LAi_SetStayType(sld);
	
	sld = GetCharacter(NPC_GenerateCharacter("HelenSleep_AmeliaMary", "gipsy_3", "woman", "towngirl", 10, PIRATE, -1, false, "citizen"));
	sld.name = StringFromKey("HelenDrinking_8");
	sld.lastname = StringFromKey("HelenDrinking_9");
	sld.dialog.FileName = "Quest\Saga\OtherNPC.c";
	sld.dialog.currentnode = "helensleep_amelia_mary";
	ChangeCharacterAddressGroup(sld, "Clone_location_2", "barmen", "stay");
	LAi_SetStayType(sld);
}

void HelenSleep_WakeUp() {
	sld = CharacterFromID("HelenSleep_AmeliaHelen");
	sld.lifeday = 0;
	sld = CharacterFromID("HelenSleep_AmeliaMary");
	sld.lifeday = 0;
	
	pchar.GenQuest.CamShuttle = 3;
	
	SetCurrentTime(8, 0);
	DeleteAttribute(pchar, "questTemp.TimeLock");
	InterfaceStates.Buttons.Save.enable = true;
	bDisableCharacterMenu = false;
	
	DoFunctionReloadToLocation("SantaCatalina_tavern_upstairs", "goto", "goto1", "HelenSleep_WokeUp");
}

void HelenSleep_WokeUp() {
	chrDisableReloadToLocation = true;
	DeleteAttribute(pchar, "GenQuest.HunterLongPause");
	TakeItemFromCharacter(pchar, "jewelry28");
	
	sld = CharacterFromID("SantaCatalina_waitress");
	ChangeCharacterAddressGroup(sld, "SantaCatalina_tavern_upstairs", "reload", "reload1");
	sld.dialog.currentnode = "helendrinking";
	
	LAi_SetActorType(pchar);
	LAi_Actor2WaitDialog(pchar, sld);
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialogDelay(sld, pchar, "", 1.0);
	
	DeleteAttribute(pchar, "questTemp.lockedMusic");
	ResetSound();
}

void HelenDrinking_WaitressSex() {
	pchar.questTemp.HelenDrinking.WaitressSex = true;
	DoQuestCheckDelay("PlaySex_1", 1.0);
}

void HelenDrinking_WaitressNoSex() {
	sld = CharacterFromID("SantaCatalina_waitress");
	LAi_ActorGoToLocation(sld, "reload", "reload1", "SantaCatalina_Tavern", "waitress", "barmen", "HelenDrinking_ResetWaitress", -1);
}

void HelenDrinking_WaitressExit() {
	LAi_SetPlayerType(pchar);
	AddQuestRecord("HelenDrinking", "2");
	SetFunctionLocationCondition("HelenDrinking_SoldierDialog", "SantaCatalina_town", false);
}

void HelenDrinking_SoldierDialog(string qName) {
	chrDisableReloadToLocation = true;
	
	sld = GetCharacter(NPC_GenerateCharacter("HelenDrinking_Notifier", "sold_eng_" + (1 + rand(7)), "man", "man", 1, ENGLAND, 0, true, "soldier"));
	sld.dialog.FileName = "Quest\Saga\OtherNPC.c";
	sld.dialog.currentnode = "helendrinking_notifier";
	sld.greeting = "soldier";
	PlaceCharacter(sld, "goto", "random_must_be_near");
	LAi_SetActorType(sld);
	SetActorDialogAny2Pchar(sld.id, "pchar_back_to_player", 0, -1);
	LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", -1);
}

void HelenDrinking_End() {
	DeleteAttribute(pchar, "GenQuest.CamShuttle");
	pchar.questTemp.HelenDrinking.Dialogs.Gladys = true;
	pchar.questTemp.HelenDrinking.Dialogs.Svenson = true;
	if (pchar.questTemp.HelenDrinking.Result == "won") {
		pchar.questTemp.HelenDrinking.Dialogs.Joan = true;
	}
	//pchar.questTemp.HelenDrinking = "end";
	
	sld = CharacterFromID("HelenDrinking_Notifier");
	LAi_CharacterDisableDialog(sld);
	LAi_SetPatrolType(sld);
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");

	chrDisableReloadToLocation = false;
	bDisableFastReload = false;
	LAi_LocationFightDisable(&locations[FindLocation("SantaCatalina_town")], false);
	LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", false);
	LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", false);
	LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", false);
	
	LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", true);
}

void HelenDrinking_IslaTesoroAmbush(string qName) {
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(&locations[FindLocation("Pirates_town")], true);
	
	sld = CharacterFromID("Norman");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	
	sld = CharacterFromID("Helena");
	PlaceCharacter(sld, "goto", "random_must_be_near");
	LAi_SetActorType(sld);
	sld.dialog.currentnode = "ambush";
	SetActorDialogAny2Pchar(sld.id, "pchar_back_to_player", 0, -1);
	LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", -1);
}

void HelenDrinking_IslaTesoroPrepareAmbush() {
	sld = CharacterFromID("Helena");
	LAi_ActorFollow(sld, pchar, "", -1);
	
	pchar.quest.HelenDrinking_IslaTesoroSpawnFirst.win_condition.l1 = "locator";
	pchar.quest.HelenDrinking_IslaTesoroSpawnFirst.win_condition.l1.location = "Pirates_town";
	pchar.quest.HelenDrinking_IslaTesoroSpawnFirst.win_condition.l1.locator_group = "quest";
	pchar.quest.HelenDrinking_IslaTesoroSpawnFirst.win_condition.l1.locator = "detector1";
	pchar.quest.HelenDrinking_IslaTesoroSpawnFirst.function = "HelenDrinking_IslaTesoroSpawnFirst";
}

void HelenDrinking_IslaTesoroSpawnFirst(string qName) {
	int iRank = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE;
	for (int i = 1; i <= 5; i++) {
		sld = GetCharacter(NPC_GenerateCharacter("HelenDrinking_IslaTesoroPirate1_" + i, "citiz_" + (41 + rand(9)), "man", "man", iRank, PIRATE, -1, true, "pirate"));
		
		LAi_SetActorType(pchar);
		LAi_SetActorType(sld);
		//LAi_group_MoveCharacter(sld, "HelenDrinking_Pirate1");
		
		ChangeCharacterAddressGroup(sld, "Pirates_town", "reload", "reload3");
		
		if (i == 1) {
			sld.name = StringFromKey("HelenDrinking_10");
			sld.lastname = StringFromKey("HelenDrinking_11");
			sld.dialog.FileName = "Quest\Saga\OtherNPC.c";
			sld.dialog.currentnode = "islatesoro_pirate1";
			sld.greeting = "hunter";
			
			SetActorDialogAny2Pchar(sld.id, "pchar_back_to_player", 0, -1);
			LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", -1);
		} else {
			LAi_ActorFollow(sld, pchar, "", -1);
		}
	}
}

void HelenDrinking_IslaTesoroSpawnSecond() {
	sld = CharacterFromID("HelenDrinking_IslaTesoroPirate1_1");
	LAi_ActorFollow(sld, pchar, "", -1);
	
	int iRank = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE;
	for (int i = 1; i <= 7; i++) {
		sld = GetCharacter(NPC_GenerateCharacter("HelenDrinking_IslaTesoroPirate2_" + i, "citiz_" + (41 + rand(9)), "man", "man", iRank, PIRATE, -1, true, "pirate"));
		
		LAi_SetActorType(sld);
		//LAi_group_MoveCharacter(sld, "HelenDrinking_Pirate2");
		
		ChangeCharacterAddressGroup(sld, "Pirates_town", "goto", "goto11");
		
		if (i == 1) {
			sld.name = StringFromKey("HelenDrinking_12");
			sld.lastname = StringFromKey("HelenDrinking_13");
			sld.dialog.FileName = "Quest\Saga\OtherNPC.c";
			sld.dialog.currentnode = "islatesoro_pirate2";
			sld.greeting = "hunter";
			
			SetActorDialogAny2Pchar(sld.id, "pchar_back_to_player", 0, -1);
			LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", -1);
		} else {
			LAi_ActorFollow(sld, pchar, "", -1);
		}
	}
	LAi_SetActorType(pchar);
	LAi_ActorTurnToLocator(pchar, "reload", "reload1");
}

void HelenDrinking_IslaTesoroPirateDialog() {
	sld = CharacterFromID("HelenDrinking_IslaTesoroPirate1_1");
	sld.dialog.currentnode = "islatesoro_pirate1_2";
	LAi_ActorDialogDelay(sld, pchar, "", 0.0);
}

void HelenDrinking_IslaTesoroPirateDialog1() {
	sld = CharacterFromID("HelenDrinking_IslaTesoroPirate2_1");
	sld.dialog.currentnode = "islatesoro_pirate2_1";
	LAi_ActorDialogDelay(sld, pchar, "", 0.0);
}

void HelenDrinking_IslaTesoroPirateDialog2() {
	sld = CharacterFromID("HelenDrinking_IslaTesoroPirate1_1");
	sld.dialog.currentnode = "islatesoro_pirate1_3";
	LAi_ActorDialogDelay(sld, pchar, "", 0.0);
}

void HelenDrinking_IslaTesoroPirateDialog3() {
	sld = CharacterFromID("HelenDrinking_IslaTesoroPirate2_1");
	sld.dialog.currentnode = "islatesoro_pirate2_2";
	LAi_ActorDialogDelay(sld, pchar, "", 0.0);
}

void HelenDrinking_IslaTesoroPirateDialog4() {
	sld = CharacterFromID("HelenDrinking_IslaTesoroPirate1_1");
	sld.dialog.currentnode = "islatesoro_pirate_a_1";
	LAi_ActorDialogDelay(sld, pchar, "", 0.0);
}

void HelenDrinking_IslaTesoroA() {
	pchar.questTemp.HelenDrinking.IslaTesoroAmbush = "A";
	
	sld = CharacterFromID("Helena");
	LAi_SetCheckMinHP(sld, 1, true, "");
	LAi_SetOfficerType(sld);
	
	LAi_LocationFightDisable(&locations[FindLocation("Pirates_town")], false);
	LAi_group_Delete("EnemyFight");
	
	for (int i = 1; i <= 5; i++) {
		sld = CharacterFromID("HelenDrinking_IslaTesoroPirate1_" + i);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	
	for (i = 1; i <= 7; i++) {
		sld = CharacterFromID("HelenDrinking_IslaTesoroPirate2_" + i);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	
	for (i = 0; i < MAX_CHARACTERS; i++) {
		sld = GetCharacter(i);
		
		if (sld.location == "Pirates_town" && CheckAttribute(sld, "City") && sld.City == "Pirates" && CheckAttribute(sld, "CityType") && sld.CityType == "soldier") {
			LAi_CharacterReincarnation(sld, false, true);
		}
	}
	
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheckFunction("EnemyFight", "HelenDrinking_AfterFight");
	LAi_SetFightMode(pchar, true);
}

void HelenDrinking_IslaTesoroB() {
	pchar.questTemp.HelenDrinking.IslaTesoroAmbush = "B";
	
	sld = CharacterFromID("Helena");
	LAi_SetCheckMinHP(sld, 1, true, "");
	LAi_SetOfficerType(sld);
	
	LAi_LocationFightDisable(&locations[FindLocation("Pirates_town")], false);
	
	for (int i = 1; i <= 5; i++) {
		sld = CharacterFromID("HelenDrinking_IslaTesoroPirate1_" + i);
		LAi_group_MoveCharacter(sld, "IslaTesoroPirate1");
	}
	
	for (i = 1; i <= 7; i++) {
		sld = CharacterFromID("HelenDrinking_IslaTesoroPirate2_" + i);
		LAi_group_MoveCharacter(sld, "IslaTesoroPirate2");
	}
	
	for (i = 0; i < MAX_CHARACTERS; i++) {
		sld = GetCharacter(i);
		
		if (sld.location == "Pirates_town" && CheckAttribute(sld, "City") && sld.City == "Pirates" && CheckAttribute(sld, "CityType") && sld.CityType == "soldier") {
			LAi_CharacterReincarnation(sld, false, true);
		}
	}
	
	LAi_group_FightGroups("IslaTesoroPirate1", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheckFunction("IslaTesoroPirate1", "HelenDrinking_AfterFight1");
	LAi_group_FightGroups("IslaTesoroPirate2", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheckFunction("IslaTesoroPirate2", "HelenDrinking_AfterFight2");
	LAi_SetFightMode(pchar, true);
}

void HelenDrinking_IslaTesoroC() {
	PlaySound("interface\abordage_wining.wav");
	
	pchar.questTemp.HelenDrinking.IslaTesoroAmbush = "C";
	
	sld = CharacterFromID("Helena");
	LAi_SetCheckMinHP(sld, 1, true, "");
	LAi_SetOfficerType(sld);
	
	LAi_LocationFightDisable(&locations[FindLocation("Pirates_town")], false);
	LAi_group_Delete("EnemyFight");
	
	for (int i = 1; i <= 5; i++) {
		sld = CharacterFromID("HelenDrinking_IslaTesoroPirate1_" + i);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	
	for (i = 1; i <= 7; i++) {
		sld = CharacterFromID("HelenDrinking_IslaTesoroPirate2_" + i);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	
	for (i = 0; i < MAX_CHARACTERS; i++) {
		sld = GetCharacter(i);
		
		if (sld.location == "Pirates_town" && CheckAttribute(sld, "City") && sld.City == "Pirates") {
			LAi_CharacterReincarnation(sld, false, true);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
	}
	
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheckFunction("EnemyFight", "HelenDrinking_AfterFight");
	LAi_SetFightMode(pchar, true);
}

void HelenDrinking_AfterFight(string qName) {
	LAi_group_SetRelation(LAI_GROUP_PLAYER, "PIRATE_CITIZENS", LAI_GROUP_NEITRAL);
	
	sld = CharacterFromID("Helena");
	LAi_RemoveCheckMinHP(sld);
	LAi_SetImmortal(sld, false);
	sld.dialog.currentnode = "after_ambush";
	
	SetActorDialogAny2Pchar(sld.id, "pchar_back_to_player", 0, -1);
	LAi_SetActorType(sld);
	LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", -1);
}

void HelenDrinking_AfterFight1(string qName) {
	pchar.questTemp.HelenDrinking.Group1 = true;
	HelenDrinking_AfterFightCommon();
}

void HelenDrinking_AfterFight2(string qName) {
	pchar.questTemp.HelenDrinking.Group2 = true;
	HelenDrinking_AfterFightCommon();
}

void HelenDrinking_AfterFightCommon() {
	if (CheckAttribute(pchar, "questTemp.HelenDrinking.Group1") && CheckAttribute(pchar, "questTemp.HelenDrinking.Group2")) {
		DeleteAttribute(pchar, "questTemp.HelenDrinking.Group1");
		DeleteAttribute(pchar, "questTemp.HelenDrinking.Group2");
		
		HelenDrinking_AfterFight("HelenDrinking_AfterFight");
	}
}

void HelenDrinking_IslaTesoroGoToResidence() {
	DeleteAttribute(pchar, "questTemp.HelenDrinking.IslaTesoroAmbush");
	chrDisableReloadToLocation = false;
	
	sld = CharacterFromID("Helena");
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	LAi_ActorFollowEverywhere(sld, "", -1);
	
	LocatorReloadEnterDisable("Pirates_town", "reload1_back", true);
	LocatorReloadEnterDisable("Pirates_town", "reload3_back", false);
	
	SetFunctionLocationCondition("HelenDrinking_IslaTesoroInResidence", "Pirates_townhall", false);
}

void HelenDrinking_IslaTesoroInResidence(string qName) {
	SetItemInLocation("pirate_cutlass", "Pirates_townhall_upstairs", "item1");
	//sld = ItemsFromID("pirate_cutlass_ground");
	//sld.shown = true;
	//sld.startLocation = "Pirates_townhall_upstairs";
	//sld.startLocator = "item1";
	
	locations[FindLocation("Pirates_townhall_upstairs")].locators_radius.item.item1 = 1.0;
	
	LocatorReloadEnterDisable("Pirates_town", "reload1_back", false);
	chrDisableReloadToLocation = true;
	LAi_LocationDisableOfficersGen("Pirates_townhall", true);
	
	sld = CharacterFromID("Helena");
	sld.dialog.currentnode = "Helena_officer";
	LAi_SetOfficerType(sld);
	ChangeCharacterAddressGroup(sld, "none", "", "");
	
	sld = GetCharacter(CreateCharacterClone(sld, -1));
	sld.id = "HelenaClone";
	sld.dialog.currentnode = "ambush_inresidence";
	ChangeCharacterAddressGroup(sld, "Pirates_townhall", "sit", "sit1");
	LAi_SetSitType(sld);
}

void HelenDrinking_IslaTesoroBeforeExit() {
	chrDisableReloadToLocation = false;
	bDisableFastReload = true;
	
	SetFunctionLocationCondition("HelenDrinking_IslaTesoroClear", "Pirates_town", false);
	
	AddQuestRecord("HelenDrinking", "4");
	
	sld = CharacterFromID("HelenaClone");
	sld.dialog.currentnode = "ambush_inresidence_wait";
}

void HelenDrinking_IslaTesoroClear(string qName) {
	bDisableFastReload = false;
	
	sld = CharacterFromID("HelenaClone");
	sld.lifeday = 0;
	
	LAi_LocationDisableOfficersGen("Pirates_townhall", false);
}

void HelenDrinking_JungleDialog() {
	sld = CharacterFromID("Helena");
	if (sld.location != pchar.location) {
		return;
	}
	
	chrDisableReloadToLocation = true;
	sld.dialog.currentnode = "arrive";
	SetActorDialogAny2Pchar(sld.id, "pchar_back_to_player", 0, -1);
	LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", -1);
}

void HelenDrinking_JungleDialog1() {
	sld = CharacterFromID("Danielle");
	LAi_SetActorTypeNoGroup(sld);
	sld.dialog.currentnode = "before_kiss";
	LAi_ActorDialogDelay(sld, pchar, "", 1.0);
}

void HelenDrinking_JungleDialog2() {
	sld = CharacterFromID("Helena");
	LAi_SetActorTypeNoGroup(sld);
	sld.dialog.currentnode = "arrive_2";
	LAi_ActorDialogDelay(sld, pchar, "", 1.0);
}

// Sinistra катсцена с поцелуями
void HelenDrinking_FirstKiss()
{
	StartQuestMovie(true, false, true);
	LAi_SetActorType(pchar);
	LAi_Fade("", "");
	DoQuestFunctionDelay("HelenDrinking_FirstKiss_2", 0.5);
}

void HelenDrinking_FirstKiss_2(string qName)
{
	//if(CheckAttribute (pchar, "IsMushketer")) SetMainCharacterToMushketer("", false);
	locCameraFromToPos(-8.77, 1.75, 6.35, true, -3.30, -1.15, 13.42);
	sld = characterFromId("Helena");
	TeleportCharacterToPosAy(sld, -7.30, 0.23, 8.84, 1.50);
	LAi_SetActorType(sld);
	LAi_ActorAnimation(sld, "kiss", "1", 4.5);
	TeleportCharacterToPosAy(pchar, -6.70, 0.23, 8.84, -1.50);
	LAi_SetActorType(pchar);
	LAi_ActorAnimation(pchar, "kiss", "1", 4.5);
	DoQuestFunctionDelay("HelenDrinking_FirstKiss_3", 4.0);
}

void HelenDrinking_FirstKiss_3(string qName)
{
	InterfaceStates.Buttons.Save.enable = true;
	LAi_Fade("", "");
	WaitDate("", 0, 0, 0, 0, 10);
	DoQuestFunctionDelay("HelenDrinking_AfterKiss", 0.5);
}

void HelenDrinking_AfterKiss(string qName) {
	EndQuestMovie();
	bDisableCharacterMenu = false;
	LAi_SetPlayerType(pchar);
	ChangeCharacterAddressGroup(pchar, PChar.location, "goto", "goto4");
	sld = CharacterFromID("Helena");
	TeleportCharacterToPosAy(sld, -18.20, 0.00, 18.91, -1.50);
	LAi_SetActorType(sld);
	sld.dialog.currentnode = "after_kiss";
	LAi_ActorDialog(sld, pchar, "", 0, 0);
}

void HelenDrinking_AfterKiss1() {
	sld = CharacterFromID("Helena");
	sld.dialog.currentnode = "Helena_officer";
	LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "HelenDrinking_AfterKiss", -1);
	
	DoQuestFunctionDelay("HelenDrinking_AfterKiss2", 5.0);
}

void HelenDrinking_AfterKiss2(string qName) {
	sld = CharacterFromID("Helena");
	
	if (sld.location == pchar.location) {
		LAi_SetStayType(sld);
		LAi_SetActorType(sld);
		LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "HelenDrinking_AfterKiss", -1);
	}
}

void HelenDrinking_AfterKiss3() {
	AddQuestRecord("HelenDrinking", "5");
	if (GetCharacterIndex("Mary") >= 0 && CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive") {
		AddQuestUserData("HelenDrinking", "sMary", StringFromKey("HelenDrinking_14"));
	} else {
		AddQuestUserData("HelenDrinking", "sMary", "");
	}
	
	pchar.questTemp.HelenDrinking.Kiss = true;
	Return_HelenaOfficer();
}

void HelenDrinking_PortRoyalDialog(string qName) {
	bDisableFastReload = false;
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(&locations[FindLocation("PortRoyal_town")], true);
	
	sld = CharacterFromID("Helena");
	PlaceCharacter(sld, "goto", "random_must_be_near");
	LAi_SetActorTypeNoGroup(sld);
	if (sti(pchar.questTemp.Saga.HelenRelation) >= 6) {
		sld.dialog.currentnode = "loot_good";
	} else {
		sld.dialog.currentnode = "loot_bad";
	}
	SetActorDialogAny2Pchar(sld.id, "pchar_back_to_player", 0, -1);
	LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", -1);
}

void HelenDrinking_CreateLoot() {
	AddQuestRecord("HelenDrinking", "6");
	
	sld = CharacterFromID("Helena");
	LAi_SetOfficerType(sld);
	sld.dialog.currentnode = "Helena_officer";
	
	sld = CharacterFromID("HelenDrinking_Francois");
	ChangeCharacterAddressGroup(sld, "PortRoyal_town", "goto", "goto3");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "HelenDrinking_PortRoyalClear", -1);
	
	string boxes[2];
	aref treasureBoxes;
	makearef(treasureBoxes, NullCharacter.TravelMap.Islands.SantaCatalina.Treasure.SantaCatalina_PearlCave);
	
	ref itm = ItemsFromID("map_full");	
	aref box;
	int boxCount = GetAttributesNum(treasureBoxes);
	int realBoxCount = 0;
	SetArraySize(&boxes, boxCount);
	
	for (int i = 0; i < boxCount; i++) {
		box = GetAttributeN(treasureBoxes, i);
		string boxId = GetAttributeValue(box);
		string boxAttr = GetAttributeName(box);
		
		if (itm.MapLocId == "SantaCatalina_PearlCave" && itm.MapBoxId == boxId) {
			continue;
		}
		
		boxes[realBoxCount] = boxAttr;
		realBoxCount++;
	}
	
	int selectedBox = rand(realBoxCount - 1);
	string selectedBoxAttr = boxes[selectedBox];
	string selectedBoxId = treasureBoxes.(selectedBoxAttr);
	pchar.questTemp.HelenDrinking.Loot.Box.Attr = selectedBoxAttr;
	pchar.questTemp.HelenDrinking.Loot.Box.Id = selectedBoxId;
	DeleteAttribute(treasureBoxes, "selectedBoxAttr"); // не класть сюда клад
	
	sld = &locations[FindLocation("SantaCatalina_PearlCave")];
	DeleteAttribute(sld, selectedBoxId);
	sld.(selectedBoxId) = Items_MakeTime(0, 0, 0, 2024);
	makearef(box, sld.(selectedBoxId));
	box.items.chest = 5;
	box.items.talisman11 = 1;
	
	SetFunctionLocationCondition("HelenDrinking_AtSHDN", "Shore55", false);
}

void HelenDrinking_AtSHDN(string qName) {
	bDisableLandEncounters = true;
	pchar.GenQuest.CannotWait = true;
	LocatorReloadEnterDisable("Shore55", "boat", true);
	LAi_LocationDisableOfficersGen("SantaCatalina_PearlCaveEntrance", true);
	
	sld = CharacterFromID("Helena");
	PlaceCharacter(sld, "goto", "random_must_be_near");
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	LAi_ActorFollowEverywhere(sld, "", -1);
	
	int iRank = sti(pchar.rank);
	for (int i = 0; i < 3; i++) {
		string model;
		if (i == 0) {
			model = "citiz_36_mush";
		} else {
			model = "mush_ctz_" + (4 + rand(2));
		}
		
		sld = GetCharacter(NPC_GenerateCharacter("HelenDrinking_SDHN_OwnMush_" + i, model, "man", "mushketer", iRank, FRANCE, -1, false, "soldier"));
		FantomMakeCoolFighter(sld, iRank, 60, 60, "", "mushket1", "cartridge", 150);
		LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "cartridge");
		
		if (i == 0) {
			sld.name = StringFromKey("HelenDrinking_15");
			sld.lastname = StringFromKey("HelenDrinking_16");
			sld.greeting = "hambit_other_4";
			sld.dialog.FileName = "Quest\Saga\OtherNPC.c";
		}
		
		ChangeCharacterAddressGroup(sld, "Shore55", "goto", "goto2");
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		LAi_ActorFollowEverywhere(sld, "", -1);
	}
	
	SetFunctionLocationCondition("HelenDrinking_AtCave", "SantaCatalina_PearlCaveEntrance", false);
}

void HelenDrinking_AtCave(string qName) {
	chrDisableReloadToLocation = true;
	
	sld = CharacterFromID("Helena");
	PlaceCharacter(sld, "goto", "random_must_be_near");
	LAi_SetActorTypeNoGroup(sld);
	sld.dialog.currentnode = "shdn";
	SetActorDialogAny2Pchar(sld.id, "pchar_back_to_player", 0, -1);
	LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", -1);
	
	LAi_LocationDisableOfficersGen("SantaCatalina_PearlCave", true);
	LAi_LocationFightDisable(&locations[FindLocation("SantaCatalina_PearlCave")], true);
	LAi_LocationFightDisable(&locations[FindLocation("SantaCatalina_PearlCaveEntrance")], true);
}

void HelenDrinking_GoForLoot() {
	chrDisableReloadToLocation = false;
	LocatorReloadEnterDisable("SantaCatalina_PearlCaveEntrance", "reload2_back", true);
	LocatorReloadEnterDisable("SantaCatalina_PearlCave", "reload1_back", true);
	LocatorReloadEnterDisable("SantaCatalina_PearlCave", "reload2", true);
	
	sld = CharacterFromID("Helena");
	LAi_SetCitizenTypeNoGroup(sld);
	LAi_CharacterDisableDialog(sld);
	
	pchar.questTemp.HelenDrinking.GoForLoot = true;
}

void HelenDrinking_GotLoot() {
	DeleteAttribute(pchar, "questTemp.HelenDrinking.GoForLoot");
	LocatorReloadEnterDisable("SantaCatalina_PearlCave", "reload1_back", false);
	LocatorReloadEnterDisable("SantaCatalina_PearlCave", "reload2", false);
	
	SetFunctionLocationCondition("HelenDrinking_CaveAmbush", "SantaCatalina_PearlCaveEntrance", false);
}

void HelenDrinking_ClearLootChest() {
	aref treasureBoxes;
	makearef(treasureBoxes, NullCharacter.TravelMap.Islands.SantaCatalina.Treasure.SantaCatalina_PearlCave);
	
	string selectedBoxAttr = pchar.questTemp.HelenDrinking.Loot.Box.Attr;
	string selectedBoxId = pchar.questTemp.HelenDrinking.Loot.Box.Id;
	
	treasureBoxes.(selectedBoxAttr) = selectedBoxId;
	
	DeleteAttribute(pchar, "questTemp.HelenDrinking.Loot.Box");
}

void HelenDrinking_CaveAmbush(string qName) {
	LAi_LocationDisableOfficersGen("SantaCatalina_PearlCave", false);
	LAi_LocationFightDisable(&locations[FindLocation("SantaCatalina_PearlCave")], false);
	
	chrDisableReloadToLocation = true;
	InterfaceStates.Buttons.Save.enable = false;
	
	sld = CharacterFromID("Helena");
	PlaceCharacter(sld, "goto", "random_must_be_near");
	LAi_SetStayTypeNoGroup(sld);
	LAi_SetActorTypeNoGroup(sld);
	LAi_CharacterEnableDialog(sld);
	sld.dialog.currentnode = "shdn_ambush";
	SetActorDialogAny2Pchar(sld.id, "pchar_back_to_player", 0, -1);
	LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", -1);
	
	for (int i = 0; i < 3; i++) {
		sld = CharacterFromID("HelenDrinking_SDHN_OwnMush_" + i);
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, "SantaCatalina_PearlCaveEntrance", "quest", "our");
		CharacterTurnToLoc(sld, "quest", "francois");
	}
}

void HelenDrinking_SpawnAmbushSoldiers() {
	StartQuestMovie(true, false, true);
	locCameraFromToPos(-7.01, 2.31, -10.81, true, -5.64, -0.20, -6.97);
	LAi_SetActorType(pchar);
	LAi_ActorGoToLocator(pchar, "quest", "player", "HelenDrinking_SharlePovorot", -1);
	
	sld = CharacterFromID("Helena");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "quest", "helen", "HelenDrinking_HelenPovorot", -1);
	
	int iRank = sti(pchar.rank);
	rCharacter = GetCharacter(NPC_GenerateCharacter("HelenDrinking_Richard", "off_eng_" + (1 + rand(3)), "man", "man", iRank + 10, ENGLAND, 0, true, "officer"));
	rCharacter.name = StringFromKey("HelenDrinking_17");
	rCharacter.lastname = StringFromKey("HelenDrinking_18");
	rCharacter.greeting = "soldier";
	rCharacter.dialog.FileName = "Quest\Saga\OtherNPC.c";
	ChangeCharacterAddressGroup(rCharacter, "SantaCatalina_PearlCaveEntrance", "reload", "reload2");
	LAi_SetActorType(rCharacter);
	LAi_ActorGoToLocator(rCharacter, "quest", "richard", "HelenDrinking_RichardPovorot", -1);
	
	sld = CharacterFromID("HelenDrinking_Francois");
	ChangeCharacterAddressGroup(sld, "SantaCatalina_PearlCaveEntrance", "reload", "reload2");
	sld.greeting = "helendrinking_francois";
	sld.dialog.FileName = "Quest\Saga\OtherNPC.c";
	sld.dialog.currentnode = "francois";
	LAi_ActorGoToLocator(sld, "quest", "francois", "HelenDrinking_FrancoisRazgovor", -1);
	
	for (int i = 0; i < 3; i++) {
		sld = GetCharacter(NPC_GenerateCharacter("HelenDrinking_SDHN_EnemyMush_" + i, "mush_eng_" + (1 + rand(5)), "man", "mushketer", iRank, ENGLAND, 0, false, "soldier"));
		FantomMakeCoolFighter(sld, iRank, 60, 60, "", "mushket1", "cartridge", 150);
		LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "cartridge");
		
		ChangeCharacterAddressGroup(sld, "SantaCatalina_PearlCaveEntrance", "reload", "reload2");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocator(sld, "quest", "enemy", "", -1);
	}
}

void HelenDrinking_AmbushDialog() {
	sld = CharacterFromID("Helena");
	sld.dialog.currentnode = "shdn_ambush_1";
	LAi_ActorDialogDelay(sld, pchar, "", 0.0);
}

void HelenDrinking_AmbushDialog1() {
	sld = CharacterFromID("HelenDrinking_Francois");
	sld.dialog.currentnode = "francois_3";
	LAi_ActorDialogDelay(sld, pchar, "", 0.0);
}

void HelenDrinking_AmbushDialog2() {
	sld = CharacterFromID("HelenDrinking_Richard");
	sld.dialog.currentnode = "richard";
	LAi_ActorDialogDelay(sld, pchar, "", 0.0);
}

void HelenDrinking_AmbushDialog3() {
	sld = CharacterFromID("HelenDrinking_Francois");
	sld.dialog.currentnode = "francois_6";
	LAi_ActorDialogDelay(sld, pchar, "", 0.0);
}

void HelenDrinking_AmbushDialog4() {
	sld = CharacterFromID("HelenDrinking_Richard");
	sld.dialog.currentnode = "richard_1";
	LAi_ActorDialogDelay(sld, pchar, "", 0.0);
}

void HelenDrinking_AmbushDialog5() {
	sld = CharacterFromID("HelenDrinking_SDHN_OwnMush_0");
	sld.dialog.currentnode = "alonso";
	LAi_ActorDialogDelay(sld, pchar, "", 0.0);
}

void HelenDrinking_AmbushDialog6() {
	sld = CharacterFromID("HelenDrinking_Francois");
	sld.dialog.currentnode = "francois_7";
	LAi_ActorDialogDelay(sld, pchar, "", 0.0);
}

void HelenDrinking_AmbushDialog7() {
	sld = CharacterFromID("HelenDrinking_Richard");
	sld.dialog.currentnode = "richard_2";
	LAi_ActorDialogDelay(sld, pchar, "", 0.0);
}

void HelenDrinking_AmbushDialog8() {
	sld = CharacterFromID("HelenDrinking_SDHN_OwnMush_0");
	sld.dialog.currentnode = "alonso_1";
	LAi_ActorDialogDelay(sld, pchar, "", 0.0);
}

void HelenDrinking_AmbushDialog9() {
	sld = CharacterFromID("Helena");
	sld.dialog.currentnode = "shdn_ambush_2";
	LAi_ActorDialogDelay(sld, pchar, "", 0.0);
}

void HelenDrinking_HelenKillFrancois() 
{
	locCameraFromToPos(-8.97, 0.91, -3.73, true, -7.62, -0.68, -4.08);
	sld = CharacterFromID("Helena");
	LAi_ActorTurnToLocator(sld, "quest", "francois");
	sld = CharacterFromID("HelenDrinking_Francois");
	LAi_ActorTurnToLocator(sld, "quest", "helen");
	DoQuestFunctionDelay("HelenDrinking_HelenKillFrancois_2", 1.3);
}

void HelenDrinking_HelenKillFrancois_2(string qName) 
{
	locCameraSleep(true);
	pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
	notification(StringFromKey("HelenDrinking_19"), "Helena");
	
	ChangeCharacterComplexReputation(pchar, "nobility", -10);
	ChangeCharacterComplexReputation(pchar, "authority", -10);
	AddCrewMorale(pchar, -20);
	
	sld = CharacterFromID("Helena");
	rCharacter = CharacterFromID("HelenDrinking_Francois");
	LAi_CharacterDisableDialog(rCharacter);
	
	if(GetCharacterEquipByGroup(sld, GUN_ITEM_TYPE) == "") {
		GiveItem2Character(sld, "pistol1");
		EquipCharacterbyItem(sld, "pistol1");
	}
	
	QuestSceneStartShot(sld, rCharacter, "HelenDrinking_FrancoisGotShot", "HelenDrinking_AfterFrancoisDeath");
}

void HelenDrinking_FrancoisGotShot(ref chr) {
	LAi_SetGroundSitType(chr);
	LAi_CharacterPlaySound(chr, "N_fight_death1");
}

void HelenDrinking_AfterFrancoisDeath() {
	sld = CharacterFromID("Helena");
	sld.dialog.currentnode = "shdn_ambush_3";
	LAi_ActorDialogDelay(sld, pchar, "", 1.5);
}

void HelenDrinking_AfterFrancoisDeath2() {
	sld = CharacterFromID("HelenDrinking_Richard");
	sld.dialog.currentnode = "richard_3";
	LAi_ActorDialogDelay(sld, pchar, "", 0.0);
}

void HelenDrinking_AfterFrancoisDeath1() {
	sld = CharacterFromID("Helena");
	sld.dialog.currentnode = "shdn_ambush_4";
	LAi_ActorDialogDelay(sld, pchar, "", 0.0);
}

void HelenDrinking_AfterFrancoisDeath3() {
	EndQuestMovie();
	chrDisableReloadToLocation = false;
	LocatorReloadEnterDisable("SantaCatalina_PearlCaveEntrance", "reload2_back", false);
	LocatorReloadEnterDisable("SantaCatalina_PearlCaveEntrance", "reload1_back", true);
	
	sld = CharacterFromID("HelenDrinking_Francois");
	sld.lifeday = 0;
	LAi_CharacterEnableDialog(sld);
	sld.dialog.currentnode = "francois_sit";
	
	sld = CharacterFromID("HelenDrinking_Richard");
	LAi_SetCitizenTypeNoGroup(sld);
	LAi_CharacterDisableDialog(sld);
	
	for (int i = 0; i < 3; i++) {
		sld = CharacterFromID("HelenDrinking_SDHN_EnemyMush_" + i);
		LAi_SetCitizenTypeNoGroup(sld);
		LAi_CharacterDisableDialog(sld);
	}
	
	SetFunctionLocationCondition("HelenDrinking_SHDNCleanup", "SantaCatalina_jungle_03", false);
}

void HelenDrinking_FinishFrancois() {
	sld = CharacterFromID("HelenDrinking_Francois");
	
	if(GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE) == "") {
		GiveItem2Character(pchar, "pistol1");
		EquipCharacterbyItem(pchar, "pistol1");
	}
	
	QuestSceneStartShot(pchar, sld, "LAi_KillCharacter", "HelenDrinking_AfterFrancoisExecution");
}

void HelenDrinking_SpareFrancois() {
	sld = CharacterFromID("HelenDrinking_Francois");
	LAi_CharacterDisableDialog(sld);
}

void HelenDrinking_SetupDuelDialog() {
	sld = CharacterFromID("HelenDrinking_Richard");
	sld.dialog.currentnode = "richard_duel";
	LAi_ActorDialogDelay(sld, pchar, "", 0.0);
}

void HelenDrinking_SetupDuel() {
	EndQuestMovie();
	LAi_group_Delete("EnemyFight");
	pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 2;
	notification(StringFromKey("HelenDrinking_20"), "Helena");
	pchar.questTemp.HelenDrinking.Duel = true;
	
	LAi_Fade("", "");
	
	LAi_LocationFightDisable(&locations[FindLocation("SantaCatalina_PearlCaveEntrance")], false);
	
	ChangeCharacterAddressGroup(pchar, "SantaCatalina_PearlCaveEntrance", "quest", "player");
	LAi_SetPlayerType(pchar);
	LAi_SetFightMode(pchar, true);
	
	rCharacter = CharacterFromID("HelenDrinking_Francois");
	ChangeCharacterAddressGroup(rCharacter, "SantaCatalina_PearlCaveEntrance", "quest", "francois");
	LAi_group_MoveCharacter(rCharacter, "EnemyFight");
	
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheckFunction("EnemyFight", "HelenDrinking_DuelWin");
	
	sld = CharacterFromID("HelenDrinking_Richard");
	ChangeCharacterAddressGroup(sld, "SantaCatalina_PearlCaveEntrance", "quest", "richard");
	LAi_SetActorType(sld);
	LAi_ActorTurnToCharacter(sld, pchar);
	LAi_SetImmortal(sld, true);
	
	sld = CharacterFromID("Helena");
	ChangeCharacterAddressGroup(sld, "SantaCatalina_PearlCaveEntrance", "quest", "helen");
	LAi_SetActorType(sld);
	LAi_ActorTurnToCharacter(sld, rCharacter);
	LAi_SetImmortal(sld, true);
	
	aref locator;
	makearef(locator, loadedLocation.locators.quest.our);
	float x = stf(locator.x);
	float y = stf(locator.y);
	float z = stf(locator.z);
	
	float dx = 1.0;
	float dy = 0.0;
	float dz = 1.0;
	
	for (int i = 0; i < 3; i++) {
		sld = CharacterFromID("HelenDrinking_SDHN_OwnMush_" + i);
		TeleportCharacterToPos(sld, x + i * dx, y + i * dy, z + i * dz);
		//ChangeCharacterAddressGroup(sld, "SantaCatalina_PearlCaveEntrance", "quest", "our" + i);
		LAi_SetActorType(sld);
		LAi_ActorTurnToCharacter(sld, rCharacter);
		LAi_SetImmortal(sld, true);
	}
	
	makearef(locator, loadedLocation.locators.quest.enemy);
	x = stf(locator.x);
	y = stf(locator.y);
	z = stf(locator.z);
	
	for (i = 0; i < 3; i++) {
		sld = CharacterFromID("HelenDrinking_SDHN_EnemyMush_" + i);
		TeleportCharacterToPos(sld, x + i * dx, y + i * dy, z + i * dz);
		//ChangeCharacterAddressGroup(sld, "SantaCatalina_PearlCaveEntrance", "quest", "our" + i);
		LAi_SetActorType(sld);
		LAi_ActorTurnToCharacter(sld, pchar);
		LAi_SetImmortal(sld, true);
	}
}

void HelenDrinking_DuelWin(string qName) {
	sld = CharacterFromID("HelenDrinking_Richard");
	sld.dialog.currentnode = "richard_4";
	SetActorDialogAny2Pchar(sld.id, "pchar_back_to_player", 0, -1);
	LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", -1);
}

void HelenDrinking_DuelVictory() {	
	sld = CharacterFromID("HelenDrinking_Richard");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "", 5.0);
	
	for (i = 0; i < 3; i++) {
		sld = CharacterFromID("HelenDrinking_SDHN_EnemyMush_" + i);
		LAi_SetActorType(sld);
		LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "", 5.0);
	}
	
	sld = CharacterFromID("Helena");
	LAi_Actor2WaitDialog(pchar, sld);
	sld.dialog.currentnode = "duel_victory";
	LAi_ActorDialogDelay(sld, pchar, "", 1.5);
}

void HelenDrinking_DuelVictory1() {
	chrDisableReloadToLocation = false;
	LocatorReloadEnterDisable("SantaCatalina_PearlCaveEntrance", "reload2_back", false);
	LocatorReloadEnterDisable("SantaCatalina_PearlCaveEntrance", "reload1_back", true);
	LAi_SetPlayerType(pchar);
	
	sld = CharacterFromID("Helena");
	LAi_SetActorType(sld);
	LAi_ActorFollow(sld, pchar, "", -1);
	
	for (i = 0; i < 3; i++) {
		sld = CharacterFromID("HelenDrinking_SDHN_OwnMush_" + i);
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, pchar, "", -1);
	}
	
	SetFunctionLocationCondition("HelenDrinking_SHDNCleanup", "SantaCatalina_jungle_03", false);
}

void HelenDrinking_SHDNCleanup(string qName) {
	bDisableLandEncounters = false;
	InterfaceStates.Buttons.Save.enable = true;
	DeleteAttribute(pchar, "GenQuest.CannotWait");
	LocatorReloadEnterDisable("Shore55", "boat", false);
	LAi_LocationDisableOfficersGen("SantaCatalina_PearlCaveEntrance", false);
	LocatorReloadEnterDisable("SantaCatalina_PearlCaveEntrance", "reload1_back", false);
	LAi_LocationFightDisable(&locations[FindLocation("SantaCatalina_PearlCaveEntrance")], false);
	
	sld = CharacterFromID("Helena");
	LAi_SetOfficerType(sld);
	sld.dialog.currentnode = "Helena_officer";
	LAi_RemoveCheckMinHP(sld);
	LAi_SetImmortal(sld, false);
	ChangeCharacterAddressGroup(sld, "none", "", "");
	
	for (i = 0; i < 3; i++) {
		sld = CharacterFromID("HelenDrinking_SDHN_OwnMush_" + i);
		sld.lifeday = 0;
		ChangeCharacterAddressGroup(sld, "none", "", "");
	}
	
	Log_Info(StringFromKey("HelenDrinking_21"));
	AddCharacterGoods(pchar, GOOD_SANDAL, 60);
	
	if (CheckAttribute(pchar, "questTemp.HelenDrinking.Duel")) {
		AddQuestRecord("HelenDrinking", "7");
	} else {
		AddQuestRecord("HelenDrinking", "7N");
	}
	
	SetFunctionLocationCondition("HelenDrinking_InBlueweldAfterCave", "SantaCatalina_town", false);
}

void HelenDrinking_InBlueweldAfterCave(string qName) {
	chrDisableReloadToLocation = true;
	
	sld = CharacterFromID("Gladis");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	
	sld = CharacterFromID("Helena");
	PlaceCharacter(sld, "goto", "random_must_be_near");
	LAi_SetActorTypeNoGroup(sld);
	sld.dialog.currentnode = "after_cave";
	SetActorDialogAny2Pchar(sld.id, "pchar_back_to_player", 0, -1);
	LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", -1);
}

// Sinistra катсцена с поцелуями
void HelenDrinking_SecondKiss()
{
	StartQuestMovie(true, false, true);
	LAi_SetActorType(pchar);
	LAi_Fade("", "");
	DoQuestFunctionDelay("HelenDrinking_SecondKiss_2", 0.5);
}

void HelenDrinking_SecondKiss_2(string qName)
{
	//if(CheckAttribute (pchar, "IsMushketer")) SetMainCharacterToMushketer("", false);
	locCameraFromToPos(2.82, 3.59, 12.90, true, 12.31, 1.38, 17.19);
	sld = characterFromId("Helena");
	TeleportCharacterToPosAy(sld, 6.10, 2.10, 14.00, 0.00);
	LAi_SetActorType(sld);
	LAi_ActorAnimation(sld, "kiss", "1", 7.5);
	TeleportCharacterToPosAy(pchar, 6.10, 2.10, 14.60, 3.00);
	LAi_SetActorType(pchar);
	LAi_ActorAnimation(pchar, "kiss", "1", 7.5);
	DoQuestFunctionDelay("HelenDrinking_SecondKiss_3", 3.5);
	DoQuestFunctionDelay("HelenDrinking_SecondKiss_4", 7.0);
}

void HelenDrinking_SecondKiss_3(string qName)
{
	locCameraFromToPos(4.89, 3.77, 13.96, true, 11.80, 1.54, 16.31);
}

void HelenDrinking_SecondKiss_4(string qName) 
{
	InterfaceStates.Buttons.Save.enable = true;
	LAi_Fade("", "");
	DoQuestFunctionDelay("HelenDrinking_AfterSecondKiss", 0.5);
}

void HelenDrinking_AfterSecondKiss(string qName)
{
	EndQuestMovie();
	bDisableCharacterMenu = false;
	LAi_SetPlayerType(pchar);
	TeleportCharacterToPosAy(pchar, 5.00, 2.10, 16.30, 3.00);
	sld = CharacterFromID("Helena");
	TeleportCharacterToPosAy(sld, 5.00, 2.10, 15.33, 0.00);
	if (sti(pchar.questTemp.Saga.HelenRelation) > 8) 
	{
		sld.dialog.currentnode = "after_second_kiss1";
	} 
	else 
	{
		sld.dialog.currentnode = "after_second_kiss";
	}
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 0, 0);
}

void HelenDrinking_AfterCaveMild() {
	Achievment_Set("ach_CL_82");
	
	sld = CharacterFromID("Helena");
	LAi_ActorRunToLocation(sld, "reload", "houseSp3", "none", "", "", "OpenTheDoors", -1);
	
	AddQuestRecord("HelenDrinking", "8");
	CloseQuestHeader("HelenDrinking");
	
	LocatorReloadEnterDisable("SantaCatalina_town", "houseSp3", true);
	SetFunctionTimerCondition("HelenDrinking_ReopenHouseSp3", 0, 0, 1, false); 
}

void HelenDrinking_ReopenHouseSp3(string qName) {
	LocatorReloadEnterDisable("SantaCatalina_town", "houseSp3", false);
}

void HelenDrinking_AfterCaveCold() {
	Achievment_Set("ach_CL_82");
	
	sld = CharacterFromID("Helena");
	LAi_ActorRunToLocation(sld, "reload", "houseSp3", "none", "", "", "OpenTheDoors", -1);
	
	AddQuestRecord("HelenDrinking", "9");
	CloseQuestHeader("HelenDrinking");
	
	LocatorReloadEnterDisable("SantaCatalina_town", "houseSp3", true);
	SetFunctionTimerCondition("HelenDrinking_ReopenHouseSp3", 0, 0, 1, false); 
}

void HelenDrinking_AfterCaveRefuseMild() {
	Achievment_Set("ach_CL_82");
	
	sld = CharacterFromID("Helena");
	LAi_ActorRunToLocation(sld, "reload", "houseSp3", "none", "", "", "OpenTheDoors", -1);
	
	AddQuestRecord("HelenDrinking", "9A");
	CloseQuestHeader("HelenDrinking");
	
	LocatorReloadEnterDisable("SantaCatalina_town", "houseSp3", true);
	SetFunctionTimerCondition("HelenDrinking_ReopenHouseSp3", 0, 0, 1, false); 
}

void HelenDrinking_AfterCaveRefuseMary() {
	Achievment_Set("ach_CL_82");
	
	sld = CharacterFromID("Helena");
	LAi_ActorRunToLocation(sld, "reload", "houseSp3", "none", "", "", "OpenTheDoors", -1);
	
	AddQuestRecord("HelenDrinking", "9B");
	CloseQuestHeader("HelenDrinking");
	
	LocatorReloadEnterDisable("SantaCatalina_town", "houseSp3", true);
	SetFunctionTimerCondition("HelenDrinking_ReopenHouseSp3", 0, 0, 1, false); 
}

void HelenDrinking_AfterCaveAccept() {
	LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", true);
	LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", true);
	LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", true);
	
	sld = CharacterFromID("Helena");
	LAi_ActorRunToLocation(sld, "reload", "houseSp3", "none", "", "", "OpenTheDoors", -1);
	SetFunctionLocationCondition("HelenDrinking_AfterCaveInBedroom", "SantaCatalina_houseSp3_bedroom", false);
}

void HelenDrinking_AfterCaveInBedroom(string qName) {
	chrDisableReloadToLocation = true;
	
	ChangeCharacterAddressGroup(pchar, "SantaCatalina_houseSp3_bedroom", "goto", "goto2");
	
	sld = CharacterFromID("Helena");
	ChangeCharacterAddressGroup(sld, "SantaCatalina_houseSp3_bedroom", "goto", "goto1");
	sld.dialog.currentnode = "after_cave_bedroom";
	LAi_ActorDialogDelay(sld, pchar, "", 1.5);
}

void HelenDrinking_AfterCaveSex1()
{
	pchar.questTemp.HelenDrinking.AfterCaveSex1 = true;
	DoQuestCheckDelay("PlaySex_1", 1.0);
	
	StartQuestMovie(true, true, true);
	pchar.GenQuest.BlockDialogCamera = true;
	locCameraFromToPos(-0.62, 1.93, -0.39, true, -2.46, -1.20, 1.01);	// Sinistra - постельная камера
}

void HelenDrinking_AfterCaveSex2() {
	pchar.questTemp.HelenDrinking.AfterCaveSex2 = true;
	DoQuestCheckDelay("PlaySex_1", 1.0);
}

void HelenDrinking_AfterCaveGladysEnter() {
	sld = CharacterFromID("Gladis");
	ChangeCharacterAddressGroup(sld, "SantaCatalina_houseSp3_bedroom", "reload", "reload1");
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorTurnToCharacter(sld, pchar);
	
	LAi_CharacterPlaySound(sld, "w_death5");
	LAi_SetStayType(pchar);
	sld.dialog.currentnode = "saw_sex";
	sld.greetingbak = sld.greeting;
	sld.greeting = "";
	LAi_ActorDialogDelay(sld, pchar, "", 1.5);
	locCameraFromToPos(3.01, 2.70, -1.00, true, 3.03, -0.30, 2.23);	// Sinistra
}

void HelenDrinking_AfterCaveGladysTalk() {
	sld = CharacterFromID("Gladis");
	sld.dialog.currentnode = "First time";
	ChangeCharacterAddressGroup(sld, "SantaCatalina_houseSp3", "goto", "goto1");
	sld.greeting = sld.greetingbak;
	DeleteAttribute(sld, "greetingbak");
	LAi_SetOwnerTypeNoGroup(sld);
	
	sld = CharacterFromID("Helena");
	sld.dialog.currentnode = "after_cave_gladys";
	LAi_ActorDialogDelay(sld, pchar, "", 1.5);
}

void HelenDrinking_AfterCaveFin() {
	EndQuestMovie();
	bDisableCharacterMenu = false;
	DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
	
	Achievment_Set("ach_CL_82");
	
	sld = CharacterFromID("Helena");
	LAi_SetOfficerType(sld);
	sld.dialog.currentnode = "Helena_officer";
	LAi_SetPlayerType(pchar);
	locCameraTarget(pchar);
	locCameraFollow();
	
	chrDisableReloadToLocation = false;
	LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", false);
	LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", false);
	LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", false);
	
	AddQuestRecord("HelenDrinking", "10");
	CloseQuestHeader("HelenDrinking");
	
	WaitDate("", 0, 0, 1, 0, 0);
	DoReloadCharacterToLocation("SantaCatalina_town", "reload", "houseSp3");
}

void HelenDrinking_GivePotionsDlg() {
	chrDisableReloadToLocation = true;
	sld = CharacterFromID("Helena");
	sld.dialog.currentnode = "give_potions";
	LAi_SetActorTypeNoGroup(sld);
	PlaceCharacter(sld, "goto", "random_must_be_near");
	SetActorDialogAny2Pchar(sld.id, "pchar_back_to_player", 0, -1);
	LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", -1);
}

void HelenDrinking_GivePotionsKey() {
	chrDisableReloadToLocation = false;
	sld = CharacterFromID("Helena");
	LAi_SetCitizenTypeNoGroup(sld);
	sld.dialog.currentnode = "Helena_officer";
	sld.location = "none";
	
	sld = &locations[FindLocation("SantaCatalina_houseSp3_bedroom")];
	DeleteAttribute(sld, "box1");
	sld.box1 = Items_MakeTime(0, 0, 0, 2024);
	
	string item;
	for (int i = 1; i <= 11; i++) {
		item = "indian_" + i;
		sld.box1.items.(item) = 1;
		item = "amulet_" + i;
		sld.box1.items.(item) = 1;
		item = "obereg_" + i;
		sld.box1.items.(item) = 1;
	}
}

void HelenUpgradeShip(string qName) {
	if (GetCharacterIndex("Helena") < 0) {
		return;
	}
	
	if (chrDisableReloadToLocation || LAi_IsCapturedLocation || !CheckPassengerInCharacter(pchar, "Helena")) {
		pchar.quest.HelenUpgradeShip.win_condition.l1 = "Timer";
		pchar.quest.HelenUpgradeShip.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
		pchar.quest.HelenUpgradeShip.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
		pchar.quest.HelenUpgradeShip.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
		pchar.quest.HelenUpgradeShip.win_condition.l2 = "location";
		pchar.quest.HelenUpgradeShip.win_condition.l2.location = "PortRoyal_town";
		pchar.quest.HelenUpgradeShip.function = "HelenUpgradeShip";
		DeleteAttribute(pchar, "quest.HelenUpgradeShip.over");
		return;
	}
	
	pchar.quest.HelenUpgradeShip.over = "yes";
	chrDisableReloadToLocation = true;
	sld = CharacterFromID("Helena");
	
	PlaceCharacter(sld, "goto", "random_must_be_near");
	sld.dialog.currentnode = "upgrade";
	LAi_SetActorTypeNoGroup(sld);
	SetActorDialogAny2Pchar(sld.id, "pchar_back_to_player", 0, -1);
	LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", -1);
}

void HelenUpgradeShip1() {
	chrDisableReloadToLocation = false;
	sld = CharacterFromID("Helena");
	sld.dialog.currentnode = "Helena_officer";
	LAi_SetCitizenTypeNoGroup(sld);
	sld = CharacterFromID("PortRoyal_shipyarder");
	sld.quest.upgradeship = true;
}

void HelenUpgradeShip2() {
	sld = CharacterFromID("PortRoyal_shipyarder");
	DeleteAttribute(sld, "quest.upgradeship");
	
	UpgradeShipParameter(pchar, "SpeedRate");
	UpgradeShipParameter(pchar, "TurnRate");
	UpgradeShipParameter(pchar, "HP");
	UpgradeShipParameter(pchar, "WindAgainstSpeed");
	UpgradeShipParameter(pchar, "Capacity");
	UpgradeShipParameter(pchar, "MaxCrew");
	UpgradeShipParameter(pchar, "Cannons");
}

void HelenDrinking_GiveCutlass() {
	pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
	notification(StringFromKey("HelenDrinking_19"), "Helena");
	pchar.questTemp.HelenDrinking.GaveCutlass = true;
	string item = GetCharacterGenerableItem(pchar, "pirate_cutlass");
	TakeItemFromCharacter(pchar, item);
	
	sld = CharacterFromID("Helena");
	GiveItem2Character(sld, item);
	EquipCharacterbyItem(sld, item);
	sld.HoldEquip = true;
	
	SetFunctionTimerCondition("HelenDrinking_CutlassTraining", 0, 1, 0, false);
}

void HelenDrinking_CutlassTraining(string qName) {
	sld = CharacterFromID("Helena");
	int skill = GetSkillValue(sld, SKILL_TYPE, SKILL_FENCING);
	if (skill < 80) {
		AddCharacterSkill(sld, SKILL_FENCING, 80 - skill);
		pchar.questTemp.HelenDrinking.CutlassTraining = true;
	}
}

void Helena_ClearRefuseSex(string qName) {
	DeleteAttribute(CharacterFromID("Helena"), "quest.refusesex");
	pchar.GenQuest.BrothelCount = 0;
	
	pchar.quest.Helen_GiveSex.win_condition.l1 = "Timer";
	pchar.quest.Helen_GiveSex.win_condition.l1.date.day = GetAddingDataDay(0, 2, 0);
	pchar.quest.Helen_GiveSex.win_condition.l1.date.month = GetAddingDataMonth(0, 2, 0);
	pchar.quest.Helen_GiveSex.win_condition.l1.date.year  = GetAddingDataYear(0, 2, 0);
	pchar.quest.Helen_GiveSex.win_condition.l2 = "Location_Type";
	pchar.quest.Helen_GiveSex.win_condition.l2.location_type = "town";
	pchar.quest.Helen_GiveSex.function = "Helen_GiveSex";
}

void Helen_GiveSex(string qName) {
	if (GetCharacterIndex("Helena") < 0) {
		return;
	}
	
	if (chrDisableReloadToLocation || LAi_IsCapturedLocation || !CheckAttribute(loadedLocation, "fastreload") || FindLocation(loadedLocation.fastreload + "_tavern") < 0 || FindLocation(loadedLocation.fastreload + "_tavern_upstairs") < 0 || !CheckPassengerInCharacter(pchar, "Helena")) {
		pchar.quest.Helen_GiveSex.win_condition.l1 = "Timer";
		pchar.quest.Helen_GiveSex.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
		pchar.quest.Helen_GiveSex.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
		pchar.quest.Helen_GiveSex.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
		pchar.quest.Helen_GiveSex.win_condition.l2 = "Location_Type";
		pchar.quest.Helen_GiveSex.win_condition.l2.location_type = "town";
		pchar.quest.Helen_GiveSex.function = "Helen_GiveSex";
		DeleteAttribute(pchar, "quest.Helen_GiveSex.over");
		return;
	}
	
	chrDisableReloadToLocation = true;
	sld = CharacterFromID("Helena");
	PlaceCharacter(sld, "goto", "random_must_be_near");
	sld.dialog.currentnode = "give_sex";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void Helen_GiveSexGoToTavern() {
	FreeSitLocator(loadedLocation.fastreload + "_tavern", "sit_base4");
	FreeSitLocator(loadedLocation.fastreload + "_tavern", "sit_front4");
	sld = CharacterFromID("Helena");
	ChangeCharacterAddressGroup(sld, loadedLocation.fastreload + "_tavern", "sit", "sit_front4");
	DoFunctionReloadToLocation(loadedLocation.fastreload + "_tavern", "sit", "sit_base4", "Helen_GiveSexDrink");
}

void Helen_GiveSexDrink() {
	sld = CharacterFromID("Helena");
	LAi_SetActorType(sld);
	LAi_ActorSetSitMode(sld);
	LAi_SetSitType(pchar);
	
	SetPitch(0.90);
	DoQuestFunctionDelay("Helen_GiveSexGoToRoom", 6.0);
}

void Helen_GiveSexGoToRoom(string qName) {
	sld = CharacterFromID("Helena");
	ChangeCharacterAddressGroup(sld, loadedLocation.fastreload + "_tavern_upstairs", "quest", "quest3");
	pchar.quest.sex_partner = "Helena";
	DoFunctionReloadToLocation(loadedLocation.fastreload + "_tavern_upstairs", "quest", "quest4", "GiveKissInRoom");
}

// Sinistra катсцена с поцелуями в комнате таверны
void GiveKissInRoom()
{
	StartQuestMovie(true, false, true);
	locCameraFromToPos(-0.64, 1.72, -0.90, true, 1.53, -0.20, -3.08);
	//if(CheckAttribute (pchar, "IsMushketer")) SetMainCharacterToMushketer("", false);
	TeleportCharacterToPosAy(pchar, 0.10, 0.00, -1.50, 3.00);
	LAi_SetActorType(pchar);
	LAi_ActorAnimation(pchar, "kiss", "1", 7.5);
	
	ref sld = characterFromId(pchar.quest.sex_partner);

	TeleportCharacterToPosAy(sld, 0.10, 0.00, -2.10, 0.00);
	LAi_SetActorType(sld);
	LAi_ActorAnimation(sld, "kiss", "1", 7.5);
	
	DoQuestFunctionDelay("GiveKissInRoom_2", 2.9);
	DoQuestFunctionDelay("GiveSexInRoom", 7.5);
}

void GiveKissInRoom_2(string qName)
{
	locCameraFromToPos(-0.92, 1.57, -2.40, true, 2.14, -0.20, -0.37);
}

void GiveSexInRoom() 
{
	EndQuestMovie();
	locCameraTarget(PChar);
	locCameraFollow();
	LAi_SetPlayerType(pchar);
	ChangeCharacterAddressGroup(pchar, PChar.location, "quest", "quest4");
	
	
	ref sld = characterFromId(pchar.quest.sex_partner);
	
	int addHealthQuantity = 6;
	float addMaxHealthQuantity = 1;
	
	if (pchar.quest.sex_partner == "Mary")
	{
		addHealthQuantity *= 2;
	}
	
	if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	
	{
		addHealthQuantity *= 2;
		addMaxHealthQuantity *= 2;
	}
	
	AddCharacterHealth(pchar, addHealthQuantity);
	AddCharacterMaxHealth(pchar, addMaxHealthQuantity);

	ChangeCharacterAddressGroup(sld, PChar.location, "quest", "quest3");
	sld.dialog.currentnode = "sex_after";
	LAi_SetOfficerType(sld);
	
	SetLaunchFrameFormParam("", "", 0, 15);
	SetLaunchFrameFormPic("loading\inside\censored1.tga");
	PlayStereoSound("sex\sex"+(rand(9)+1)+".wav");
    LaunchFrameForm();
	WaitDate("", 0, 0, 0, 3, 10); //крутим время
	RecalculateJumpTable();
	LAi_SetCurHPMax(pchar);
	if (rand(2) == 0)
	{
		pchar.GenQuest.CamShuttle = 2;
		SetCamShuttle(loadedLocation);
	}
	
	AddMoneyToCharacter(pchar, -1000);
	
	string skill;
	
	switch (rand(5)) {
		case 0:
			skill = SKILL_ACCURACY;
		break;
		
		case 1:
			skill = SKILL_CANNONS;
		break;
		
		case 2:
			skill = SKILL_SAILING;
		break;
		
		case 3:
			skill = SKILL_REPAIR;
		break;
		
		case 4:
			skill = SKILL_GRAPPLING;
		break;
		
		case 5:
			skill = SKILL_DEFENCE;
		break;
	}
	
	AddCharacterSkill(pchar, skill, 1);
	Log_Info(""+pchar.name + StringFromKey("HelenDrinking_22") + XI_ConvertString(skill)+"");
	
	switch (rand(2)) {
		case 0:
			skill = SKILL_F_LIGHT;
		break;
		
		case 1:
			skill = SKILL_FENCING;
		break;
		
		case 2:
			skill = SKILL_F_HEAVY;
		break;
	}
	
	
	if (pchar.quest.sex_partner == "Mary")
	{
		pchar.quest.Mary_giveme_sex.over = "yes"; //снять прерывание
		pchar.quest.Mary_giveme_sex1.over = "yes"; //снять прерывание лесник. 
	}
	if (pchar.quest.sex_partner == "Helena")
	{
		pchar.quest.Helen_GiveSex.win_condition.l1 = "Timer";
		pchar.quest.Helen_GiveSex.win_condition.l1.date.day = GetAddingDataDay(0, 2, 0);
		pchar.quest.Helen_GiveSex.win_condition.l1.date.month = GetAddingDataMonth(0, 2, 0);
		pchar.quest.Helen_GiveSex.win_condition.l1.date.year  = GetAddingDataYear(0, 2, 0);
		pchar.quest.Helen_GiveSex.win_condition.l2 = "Location_Type";
		pchar.quest.Helen_GiveSex.win_condition.l2.location_type = "town";
		pchar.quest.Helen_GiveSex.function = "Helen_GiveSex";
	}
	AddCharacterSkill(sld, skill, 1);
	Log_Info(""+sld.name + StringFromKey("HelenDrinking_23") + XI_ConvertString(skill));
}

//=================================================================
//======================кейсы из quests_reaction===================
//=================================================================
bool HelenDrinking_QuestComplete(string sQuestName, string qname)
{
	ref sld;
	int i;
	
	bool condition = true;
	
	if (sQuestName == "HelenDrinking_WaitAtSvenson") {
		sld = CharacterFromID("Helena");
		LAi_ActorTurnToLocator(sld, "goto", "goto11");
		LAi_SetStayType(sld);
		sld.talker = true;
		sld.dialog.currentnode = "drinking_at_svenson";
	}
	
	else if (sQuestName == "HelenDrinking_ResetWaitress") {
		sld = CharacterFromID("SantaCatalina_waitress");
		LAi_SetWaitressTypeNoGroup(sld);
		sld.dialog.currentnode = "First time";
		chrDisableReloadToLocation = false;
		HelenDrinking_WaitressExit();
	}
	
	else if (sQuestName == "HelenDrinking_AfterKiss") {
		sld = CharacterFromID("Danielle");
		LAi_SetActorTypeNoGroup(sld);
		sld.dialog.currentnode = "after_kiss";
		SetActorDialogAny2Pchar(sld.id, "pchar_back_to_player", 0, -1);
		LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", -1);
	}
	
	else if (sQuestName == "HelenDrinking_PortRoyalClear") {
		chrDisableReloadToLocation = false;
		LAi_LocationFightDisable(&locations[FindLocation("PortRoyal_town")], false);
	}
	
	else if (sQuestName == "HelenDrinking_SharlePovorot") {
		LAi_ActorTurnToLocator(pchar, "quest", "francois");
	}
	
	else if (sQuestName == "HelenDrinking_HelenPovorot") {
		sld = CharacterFromID("Helena");
		LAi_ActorTurnToLocator(sld, "quest", "francois");
	}
	
	else if (sQuestName == "HelenDrinking_RichardPovorot") {
		sld = CharacterFromID("HelenDrinking_Richard");
		LAi_ActorTurnToLocator(sld, "quest", "player");
	}
	
	else if (sQuestName == "HelenDrinking_FrancoisRazgovor") {
		LAi_SetPlayerType(pchar);
		sld = CharacterFromID("HelenDrinking_Francois");
		LAi_ActorDialog(sld, pchar, "", 0, 0);
	}
	
	else if (sQuestName == "HelenDrinking_AfterFrancoisDeath") {
		sld = CharacterFromID("Helena");
		sld.dialog.currentnode = "shdn_ambush_3";
		LAi_ActorDialogDelay(sld, pchar, "", 1.5);
	}
	
	else if (sQuestName == "HelenDrinking_AfterFrancoisExecution") {
		Achievment_SetStat(95, 1);
	
		chrDisableReloadToLocation = true;
		LAi_SetPlayerType(pchar);
		LAi_LocationFightDisable(&locations[FindLocation("SantaCatalina_PearlCaveEntrance")], false);
		LAi_SetFightMode(pchar, true);
		
		sld = CharacterFromID("Helena");
		LAi_SetCheckMinHP(sld, 10, true, "");
		LAi_SetOfficerType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		for (i = 0; i < 3; i++) {
			sld = CharacterFromID("HelenDrinking_SDHN_OwnMush_" + i);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
		
		LAi_group_Delete("EnemyFight");
		sld = CharacterFromID("HelenDrinking_Richard");
		LAi_group_MoveCharacter(sld, "EnemyFight");
		for (i = 0; i < 3; i++) {
			sld = CharacterFromID("HelenDrinking_SDHN_EnemyMush_" + i);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
	}
	else
	{
		condition = false;
	}
	
	return condition;
}