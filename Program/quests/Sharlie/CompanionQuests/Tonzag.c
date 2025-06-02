void Tonzag_AtTortuga(string qName) {
	if (GetCharacterIndex("Tonzag") < 0) {
		return;
	}
	
	if (!CheckPassengerInCharacter(pchar, "Tonzag")) {
		return;
	}
	
	DeleteQuestCondition("Terrapin_LateTortuga");
	pchar.questTemp.Tonzag.TerrapinBlock = true;
	
	chrDisableReloadToLocation = true;
	
	rCharacter = GetCharacter(NPC_GenerateCharacter("Tonzag_StartOfficer", "off_fra_" + (1 + rand(2)), "man", "man", 40, FRANCE, 0, true, "officer"));
	rCharacter.dialog.filename = "Quest\CompanionQuests\Tonzag.c";
	rCharacter.dialog.currentnode = "startoff";
	rCharacter.greeting = "soldier_arest";
	PlaceCharacter(rCharacter, "goto", "random_must_be_near");
	LAi_SetActorType(rCharacter);
	LAi_ActorDialog(rCharacter, pchar, "", -1, 0);
	
	// ходячие мушкетеры
	for (i = 1; i <= 3; i++) {
		sld = GetCharacter(NPC_GenerateCharacter("Tonzag_StartSoldier_" + i, "mush_fra_" + (1 + rand(5)), "man", "mushketer", 30, FRANCE, 0, true, "soldier"));
		FantomMakeCoolFighter(sld, 30, 60, 60, "", "mushket1", "cartridge", 150);
		PlaceCharacter(sld, "goto", "random_must_be_near");
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, rCharacter, "", -1);
	}
}

void Tonzag_Arrested() {
	WaitDate("", 0, 0, 1, rand(3), 0);
	
	for (int i = 1; i <= 3; i++) {
		int index = GetOfficersIndex(pchar, i);
		
		string attr = "o" + i;
		pchar.questTemp.Tonzag.Officers.(attr) = index;
		
		if (index < 0) {
			continue;
		}
		
		SetOfficersIndex(pchar, i, -1);
	}
	
	DoFunctionReloadToLocation("Tortuga_prison", "goto", "goto9", "Tonzag_InJail");
}

void Tonzag_SaveStash(ref chr) {
	aref itemsFrom, itemsTo, stash;
	
	makearef(stash, chr.quest.stash);
	DeleteAttribute(stash, "");
	
	if (IsMainCharacter(chr)) {
		if (CheckAttribute(chr, "IsMushketer")) {
			stash.MushketID = chr.IsMushketer.MushketID;
			SetMainCharacterToMushketer("", false);
		}
	} else {
		if (CheckAttribute(chr, "IsMushketer")) {
			stash.MushketID = chr.IsMushketer.MushketID;
			SetOfficerToMushketer(chr, "", false);
		}
	}
	
	stash.blade = GetCharacterEquipByGroup(chr, BLADE_ITEM_TYPE);
	stash.gun = GetCharacterEquipByGroup(chr, GUN_ITEM_TYPE);
	stash.cirass = GetCharacterEquipByGroup(chr, CIRASS_ITEM_TYPE);
	//stash.money = chr.money;
	stash.dublon = chr.dublon;
	
	RemoveCharacterEquip(chr, BLADE_ITEM_TYPE);
	RemoveCharacterEquip(chr, GUN_ITEM_TYPE);
	RemoveCharacterEquip(chr, CIRASS_ITEM_TYPE);
	//chr.money = 0;
	chr.dublon = 0;
	
	makearef(itemsFrom, chr.items);
	makearef(itemsTo, stash.items);
	
	CopyAttributes(itemsTo, itemsFrom);
	DeleteAttribute(itemsFrom, "");
	
	int doubloons = GetCharacterItem(stash, "gold_dublon");
	TakeNItems(stash, "gold_dublon", -doubloons);
	TakeNItems(chr, "gold_dublon", doubloons);
}

void Tonzag_PopStash(ref chr) {
	aref itemsFrom, itemsTo, stash;
	
	makearef(stash, chr.quest.stash);
	
	int doubloons = GetCharacterItem(chr, "gold_dublon");
	chr.dublon = 0;
	
	makearef(itemsFrom, stash.items);
	makearef(itemsTo, chr.items);
	CopyAttributes(itemsTo, itemsFrom);
	
	TakeNItems(chr, "gold_dublon", doubloons);
	
	if (stash.blade != "") EquipCharacterByItem(chr, stash.blade);
	if (stash.gun != "") EquipCharacterByItem(chr, stash.gun);
	if (stash.cirass != "") EquipCharacterByItem(chr, stash.cirass);
	
	if (IsMainCharacter(chr)) {
		if (CheckAttribute(stash, "MushketID")) {
			SetMainCharacterToMushketer(stash.MushketID, true);
		}
	} else {
		if (CheckAttribute(stash, "MushketID")) {
			SetOfficerToMushketer(chr, stash.MushketID, true);
		}
	}
	
	//chr.money = stash.money;
	//chr.dublon = stash.dublon;
	
	DeleteAttribute(chr, "quest.stash");
}

void Tonzag_InJail() {
	bDisableCharacterMenu = true;
	// отбираем предметы и деньги, снимаем эквип
	Tonzag_SaveStash(pchar);
	
	if (CheckPassengerInCharacter(pchar, "Tichingitu")) {
		sld = CharacterFromID("Tichingitu");
		Tonzag_SaveStash(sld);
		ChangeCharacterAddressGroup(sld, pchar.location, "quest", "tichingitu");
		LAi_SetGroundSitType(sld);
		pchar.questTemp.TonzagQuest.JailChrs.Tichingitu = true;
		pchar.questTemp.TonzagQuest.JailDialog.Tichingitu = true;
	}
	
	if (CheckPassengerInCharacter(pchar, "Helena")) {
		sld = CharacterFromID("Helena");
		Tonzag_SaveStash(sld);
		ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto24");
		LAi_SetStayType(sld);
		pchar.questTemp.TonzagQuest.JailChrs.Helena = true;
		pchar.questTemp.TonzagQuest.JailDialog.Helena = true;
	}
	
	if (CheckPassengerInCharacter(pchar, "Mary")) {
		sld = CharacterFromID("Mary");
		Tonzag_SaveStash(sld);
		ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto24");
		LAi_SetStayType(sld);
		pchar.questTemp.TonzagQuest.JailChrs.Mary = true;
		pchar.questTemp.TonzagQuest.JailDialog.Mary = true;
	}
	
	sld = CharacterFromID("Tonzag");
	Tonzag_SaveStash(sld);
	ChangeCharacterAddressGroup(sld, pchar.location, "prison", "prison10lay");
	LAi_SetGroundSitType(sld);
	
	pchar.questTemp.TonzagQuest.JailDialog.FirstTime = true;
	pchar.questTemp.TonzagQuest.JailDialog.Tonzag = true;
	
	LAi_SetActorType(pchar);
	LAi_ActorTurnToLocator(pchar, "goto", "goto24");
	DoQuestFunctionDelay("Tonzag_OdinVKamere", 0.2);
	DoQuestCheckDelay("TalkSelf_Quest", 3.0);
	
	AddQuestRecord("Tonzag", "1");
	locCameraFromToPos(-9.82, 1.65, -2.35, true, -14.00, -0.10, -2.70);
}

void Tonzag_OdinVKamere(string qName)
{
	sld = CharacterFromID("Tonzag")
	int iTemp = LAi_FindNearestVisCharacter(sld, 3);
	ref characterRef;
	if(iTemp != -1)
	{
		characterRef = &Characters[iTemp];

		if(!LAi_IsImmortal(characterRef)) // Квестовые
		{
			ChangeCharacterAddressGroup(characterRef, "none", "", "");
			characterRef.lifeday = 0;
		}
	}
}

void Tonzag_InJailDialog() {
	pchar.GenQuest.BlockDialogCamera = true;
	sld = CharacterFromID(pchar.questTemp.Tonzag.JailDialog.ID);
	sld.dialog.currentnode = "tonzag_jailed";
	LAi_SetActorType(pchar);
	LAi_ActorDialogNow(pchar, sld, "Tonzag_InJailRepeat", -1);
}

void Tonzag_CreateKiller() {
	if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailChrs.Tichingitu")) {
		sld = CharacterFromID("Tichingitu");
		LAi_CharacterDisableDialog(sld);
	}
	
	if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailChrs.Helena")) {
		sld = CharacterFromID("Helena");
		LAi_CharacterDisableDialog(sld);
	}
	
	if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailChrs.Mary")) {
		sld = CharacterFromID("Mary");
		LAi_CharacterDisableDialog(sld);
	}
	
	sld = CharacterFromID("Tonzag");
	LAi_CharacterDisableDialog(sld);
	
	DeleteAttribute(pchar, "questTemp.TonzagQuest.JailDialog");
	
	// from goto22 to goto23 to reload11
	sld = GetCharacter(NPC_GenerateCharacter("Tonzag_Killer", "killer_" + (1 + rand(1)) + "_mush", "man", "mushketer", 20, PIRATE, -1, false, "soldier"));
	FantomMakeCoolFighter(sld, 45, 100, 100, "", "mushket3", "grapeshot", 500);
	sld.viper = true;
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto22");
	LAi_ActorGoToLocator(sld, "goto", "goto23", "Tonzag_KillerLookAtUs", -1);
}

void Tonzag_KillerGoToTonzag(string qName) {
	sld = CharacterFromID("Tonzag_Killer");
	LAi_ActorGoToLocator(sld, "goto", "goto25", "Tonzag_KillerPrepareShot", -1);
}

void Tonzag_KillerShoots(string qName) {
	sld = CharacterFromID("Tonzag_Killer");
	LAi_ActorAnimation(sld, "Shot", "Tonzag_KillerGoAway", 1.0);
	
	pchar.questTemp.TonzagQuest.JailPanic = true;
	DoQuestCheckDelay("TalkSelf_Quest", 3.0);
	
	AddQuestRecord("Tonzag", "2");
}

void Tonzag_GFAfterShot() {
	if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailChrs.Helena")) {
		sld = CharacterFromID("Helena");
		LAi_CharacterEnableDialog(sld);
		
		LAi_SetActorType(sld);
		sld.dialog.currentnode = "tonzag_aftershot";
		pchar.GenQuest.BlockDialogCamera = true;
		LAi_ActorDialogNow(sld, pchar, "", -1);
	} else {
		if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailChrs.Mary")) {
			sld = CharacterFromID("Mary");
			LAi_CharacterEnableDialog(sld);
			
			LAi_SetActorType(sld);
			sld.dialog.currentnode = "tonzag_aftershot";
			pchar.GenQuest.BlockDialogCamera = true;
			LAi_ActorDialogNow(sld, pchar, "", -1);
		} else {
			Tonzag_TichingituAfterShot();
		}
	}
}

void Tonzag_TichingituAfterShot() {
	if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailChrs.Tichingitu")) {
		sld = CharacterFromID("Tichingitu");
		LAi_CharacterEnableDialog(sld);
		
		//ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto9");
		LAi_SetActorType(sld);
		LAi_ActorSetGroundSitMode(sld);
		sld.dialog.currentnode = "tonzag_aftershot";
		pchar.GenQuest.BlockDialogCamera = true;
		LAi_ActorDialogNow(sld, pchar, "", -1);
	} else {
		DoQuestFunctionDelay("Tonzag_JailOffComes", 40.0);
	}
}

void Tonzag_JailOffComes(string qName) {
	DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
	
	sld = CharacterFromID("TortugaJailOff");
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto22");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "goto", "goto23", "Tonzag_JailOffSpeak", -1);
}

void Tonzag_JailFear() {
	sld = CharacterFromID("Tichingitu");
	LAi_ActorAnimation(sld, "Ground_Afraid", "1", 1.5);
	DoQuestFunctionDelay("Tonzag_JailOffComes", 60.0);
}

void Tonzag_Bailed() {
	LAi_Fade("Tonzag_BailedFadeOut", "");
	pchar.questTemp.jailCanMove = true;
	pchar.GenQuest.CannotWait = true;
	LocatorReloadEnterDisable("Tortuga_town", "gate_back", true);
	LocatorReloadEnterDisable("Tortuga_town", "reload1_back", true);
	
	sld = CharacterFromID("Tortuga_Usurer");
	sld.dialog.currentnode = "tonzag_bail";
}

void Tonzag_GetOut() {
	bDisableCharacterMenu = false;
	chrDisableReloadToLocation = false;
	DeleteAttribute(pchar, "GenQuest.CannotWait");
	
	LocatorReloadEnterDisable("Tortuga_town", "gate_back", false);
	LocatorReloadEnterDisable("Tortuga_town", "reload1_back", false);
	
	Island_SetReloadEnableGlobal("Tortuga", false);
	
	Tonzag_PopStash(pchar);
	
	if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailChrs.Tichingitu")) {
		sld = CharacterFromID("Tichingitu");
		LAi_CharacterEnableDialog(sld);
		sld.dialog.currentnode = "Tichingitu_officer";
		Tonzag_PopStash(sld);
	}
	
	if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailChrs.Helena")) {
		sld = CharacterFromID("Helena");
		LAi_CharacterEnableDialog(sld);
		sld.dialog.currentnode = "Helena_officer";
		Tonzag_PopStash(sld);
	}
	
	if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailChrs.Mary")) {
		sld = CharacterFromID("Mary");
		LAi_CharacterEnableDialog(sld);
		sld.dialog.currentnode = "Mary_officer";
		Tonzag_PopStash(sld);
	}
	
	for (int i = 1; i <= 3; i++) {
		string attr = "o" + i;
		
		if (!CheckAttribute(pchar, "questTemp.Tonzag.Officers." + attr)) {
			continue;
		}
		int index = sti(pchar.questTemp.Tonzag.Officers.(attr));
		if (index < 0) {
			continue;
		}
		
		SetOfficersIndex(pchar, i, index);
	}
	OfficersFollow();
	
	sld = CharacterFromID("Tonzag");
	LAi_CharacterEnableDialog(sld);
	sld.dialog.currentnode = "Tonzag_officer";
	ChangeCharacterAddressGroup(sld, "none", "", "");
	Tonzag_PopStash(sld);
	CheckForReleaseOfficer(sti(sld.index));
	SetCharacterRemovable(sld, false);
	
	AddQuestRecord("Tonzag", "4");
	
	int shipType;
	int cannon;
	
	int class = GetCharacterShipClass(pchar);
	if (class <= 2) {
		shipType = SHIP_FRIGATE_H;
		cannon = CANNON_TYPE_CANNON_LBS36;
	} else {
		if (class == 3) {
			shipType = SHIP_CORVETTE;
			cannon = CANNON_TYPE_CANNON_LBS24;
		} else {
			shipType = SHIP_BRIG;
			cannon = CANNON_TYPE_CANNON_LBS20;
		}
	}
	
	string sCapId = "Tonzag_Hunter_";
    string sGroup = "Sea_" + sCapId + "1";
	sld = GetCharacter(NPC_GenerateCharacter(sCapId + "1", "mercen_23", "man", "man", 20, PIRATE, -1, false, "quest"));
	FantomMakeCoolSailor(sld, shipType, "", cannon, 60, 60, 60);
	FantomMakeCoolFighter(sld, 30, 80, 80, "blade_06", "pistol1", "bullet", 100);
	UpgradeShipParameter(sld, "SpeedRate");
	UpgradeShipParameter(sld, "TurnRate");
	UpgradeShipParameter(sld, "HP");
	UpgradeShipParameter(sld, "WindAgainstSpeed");
	UpgradeShipParameter(sld, "Capacity");
	UpgradeShipParameter(sld, "MaxCrew");
	UpgradeShipParameter(sld, "Cannons");
	SetCrewQuantityFull(sld);
	//sld.AnalizeShips = true;
	DeleteAttribute(sld, "AnalizeShips");
	sld.DontRansackCaptain = true;
	//sld.WatchFort = true;
	DeleteAttribute(sld, "WatchFort");
	sld.AlwaysEnemy = true;
	sld.Abordage.Enable = false;
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	sld.mapEnc.type = "war";
    sld.mapEnc.Name = StringFromKey("Tonzag_1");
	Map_CreateCoolWarrior("", sld.id, -1);
	sld.ShipHideImmortal = makeint(GetCharacterShipHP(sld) / 2);
	pchar.questTemp.TonzagQuest.Hunter = true;
	
	DoReloadCharacterToLocation("Tortuga_town", "reload", "reload_jail");
}

void Tonzag_UnlockTortuga() {
	Island_SetReloadEnableGlobal("Tortuga", true);
	DeleteAttribute(pchar, "questTemp.Tonzag.TerrapinBlock");
}

void Tonzag_SpawnBrander() {
	sld = GetCharacter(NPC_GenerateCharacter("Tonzag_Brander", "mercen_23", "man", "man", 30, PIRATE, -1, true, "quest"));
	LAi_SetImmortal(sld, true);
	FantomMakeCoolSailor(sld, SHIP_CAREERLUGGER, "", CANNON_TYPE_CANNON_LBS3, 100, 10, 10);
	SetShipSkill(sld, 30, 10, 10, 10, 100, 10, 10, 10, 10);
	UpgradeShipParameter(sld, "SpeedRate");
	UpgradeShipParameter(sld, "Capacity");
	UpgradeShipParameter(sld, "WindAgainstSpeed");
	UpgradeShipParameter(sld, "TurnRate");
	
	ref ship = GetRealShip(sld.ship.type);
	
	//sld.AlwaysEnemy = true;
	sld.ShipTaskLock = true;
	sld.Abordage.Enable = false;
	//sld.SinkTenPercent = true;
	sld.FixedShipSpeed = 20.0;
	DeleteAttribute(sld, "SinkTenPercent");
	NullCharacterGoods(sld);
	SetCharacterGoods(sld, GOOD_POWDER, 200);
	Group_AddCharacter("Tonzag_Brander", "Tonzag_Brander");
	Group_SetGroupCommander("Tonzag_Brander", "Tonzag_Brander");
	Sea_LoginGroupCurrentSea("Tonzag_Brander");
	SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);
	Ship_SetTaskBrander(PRIMARY_TASK, sti(sld.index), GetMainCharacterIndex());
	
	pchar.quest.Tonzag_BranderDead.win_condition.l1 = "Group_Death";
	pchar.quest.Tonzag_BranderDead.win_condition.l1.group = "Tonzag_Brander";
	pchar.quest.Tonzag_BranderDead.function = "Tonzag_BranderDead";
}

void Tonzag_BranderDead(string qName) {
	if (!LAi_IsDead(pchar)) {
		PlaySound("interface\abordage2.wav");
		DoQuestFunctionDelay("Tonzag_GotBoarded", 10.0);
	}
}

void Tonzag_GotBoarded(string qName) {
	pchar.questTemp.TonzagQuest.ShipPos.x = pchar.ship.pos.x;
	pchar.questTemp.TonzagQuest.ShipPos.z = pchar.ship.pos.z;
	pchar.questTemp.TonzagQuest.ShipPos.Island = AISea.Island;
	
	LAi_LocationFightDisable(&Locations[FindLocation("Deck_Galeon_Ship")], false);
	PlaySound("Voice\" + LanguageGetLanguage() + "\evilpirates01.wav");
	sld = &locations[FindLocation("Deck_Galeon_Ship")];
	DeleteAttribute(sld, "lockCamAngle");
	DoFunctionReloadToLocation("Deck_Galeon_Ship", "quest", "quest7", "Tonzag_LoadDeck");
}

void Tonzag_LoadDeck() {
	ClearAllLogStrings();
	bDisableCharacterMenu = true;
	InterfaceStates.Buttons.Save.enable = false;
	
	sld = CharacterFromID("Tonzag_Hunter_1");
	sld.lifeday = 0;
	
	if (CheckPassengerInCharacter(pchar, "Helena")) {
		sld = CharacterFromID("Helena");
		ChangeCharacterAddressGroup(sld, pchar.location, "rld", "aloc1");
		LAi_SetActorType(sld);
		LAi_ActorTurnToLocator(sld, "quest", "quest6");
		
		pchar.questTemp.TonzagQuest.BoardingGF = "Helena";
	} else {
		if (CheckPassengerInCharacter(pchar, "Mary")) {
			sld = CharacterFromID("Mary");
			ChangeCharacterAddressGroup(sld, pchar.location, "rld", "aloc1");
			LAi_SetActorType(sld);
			LAi_ActorTurnToLocator(sld, "quest", "quest6");
			
			pchar.questTemp.TonzagQuest.BoardingGF = "Mary";
		} else {
			bool found = false;
			for (int i = 1; i <= 3; i++) {
				int index = GetOfficersIndex(pchar, i);
				
				if (index < 0) {
					continue;
				}
				
				sld = GetCharacter(index);
				if (sld.Dialog.FileName == "Enc_Officer_dialog.c") {
					found = true;
					pchar.questTemp.TonzagQuest.BoardingGF = sld.id;
					break;
				}
			}
			
			if (!found) {
				index = sti(pchar.Fellows.Passengers.boatswain);
				if (index >= 0) {
					sld = GetCharacter(index);
					if (sld.Dialog.FileName == "Enc_Officer_dialog.c") {
						found = true;
						pchar.questTemp.TonzagQuest.BoardingGF = sld.id;
					}
				}
			}
			
			if (!found) {
				sld = GetCharacter(NPC_GenerateCharacter("Tonzag_Alonso", "citiz_36_mush", "man", "mushketer", sti(pchar.rank), FRANCE, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, iRank, 60, 60, "", "mushket1", "cartridge", 150);
				LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "cartridge");
				
				sld.name = StringFromKey("Tonzag_2");
				sld.lastname = StringFromKey("Tonzag_3");
				sld.greeting = "hambit_other_4";
				sld.dialog.FileName = "Quest\CompanionQuests\Tonzag.c";
				
				ChangeCharacterAddressGroup(sld, pchar.location, "rld", "aloc1");
				LAi_SetActorType(sld);
				LAi_ActorTurnToLocator(sld, "quest", "quest6");
				
				pchar.questTemp.TonzagQuest.BoardingGF = "Tonzag_Alonso";
			}
		}
	}
	
	for (i = 1; i <= 3; i++) {
		index = GetOfficersIndex(pchar, i);
		
		if (index < 0) {
			continue;
		}
		
		sld = GetCharacter(index);
		if (sld.id == pchar.questTemp.TonzagQuest.BoardingGF) {
			continue;
		}
		
		ChangeCharacterAddressGroup(sld, pchar.location, "quest", "quest" + (i + 2));
		LAi_SetActorType(sld);
		LAi_ActorTurnToLocator(sld, "quest", "quest6");
	}
	
	LAi_SetActorType(pchar);
	LAi_ActorTurnToLocator(pchar, "quest", "quest6");
	
	// десант
	int iRank = MOD_SKILL_ENEMY_RATE + sti(pchar.rank);
	int iScl = 10 + 2 * sti(pchar.rank);
	for (i = 1; i <= 10; i++) {
		sld = GetCharacter(NPC_GenerateCharacter("Tonzag_LigaMushketer_" + i, "killer_" + (1 + rand(1)) + "_mush", "man", "mushketer", 20, PIRATE, 0, false, "quest"));
		sld.viper = true;
		sld.MusketerDistance = 0;
		FantomMakeCoolFighter(sld, 15, 80, 80, "", "mushket3", "grapeshot", 0);
		ChangeCharacterAddressGroup(sld, pchar.location, "quest", "liga" + ((i - 1) / 2 + 1));
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		LAi_ActorTurnToLocator(sld, "quest", "quest7");
	}
	
	// наши
	aref locators;
	makearef(locators, loadedLocation.locators.rld);
	int locCount = GetAttributesNum(locators);
	int sailorsCount = 0;
	for (i = 1; i <= locCount; i++) {
		aref loc = GetAttributeN(locators, i - 1);
		// знаю, охуенная идея, но не вручную же локаторы вписывать
		if (stf(loc.z) > 7.6 || stf(loc.z) < -22.0) {
			continue;
		}
		
		for (int j = 1; j <= 2; j++) {
			sld = GetCharacter(NPC_GenerateCharacter("Tonzag_OurSailor_" + (sailorsCount + 1), "citiz_" + (rand(9)+31), "man", "man", 10, FRANCE, 0, true, "pirate"));
			LAi_SetHP(sld, 100, 100);
			ChangeCharacterAddressGroup(sld, pchar.location, "rld", GetAttributeName(loc));
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_ActorTurnToLocator(sld, "quest", "quest6");
			
			sailorsCount++;
		}
	}
	
	pchar.questTemp.TonzagQuest.SailorsCount = sailorsCount;
	
	DoQuestFunctionDelay("Tonzag_BoardingShot", 2.0);
}

void Tonzag_BoardingShot(string qName) {
	for (i = 1; i <= 10; i++) {
		sld = CharacterFromID("Tonzag_LigaMushketer_" + i);
		LAi_ActorAnimation(sld, "Shot", "nothing", 1.0);
		LAi_GunSetUnload(sld, MUSKET_ITEM_TYPE);
	}
	
	DoQuestFunctionDelay("Tonzag_BoardingShotResult", 1.0);
}

void Tonzag_BoardingShotResult(string qName) {
	int sailorsCount = sti(pchar.questTemp.TonzagQuest.SailorsCount);
	Log_TestInfo("До выстрела " + sailorsCount + " матросов");
	for (i = 1; i < sailorsCount; i++) {
		sld = CharacterFromID("Tonzag_OurSailor_" + i);
		
		float locx, locy, locz;
		GetCharacterPos(sld, &locx, &locy, &locz);
		if (locz > 0) {
			LAi_KillCharacter(sld);
		}
	}
	
	DoQuestFunctionDelay("Tonzag_BoardingFight", 1.0);
}

void Tonzag_BoardingFight(string qName) {
	PlaySound("interface\abordage_wining.wav");
	
	
	sld = CharacterFromID(pchar.questTemp.TonzagQuest.BoardingGF);
	//LAi_SetImmortal(sld, true);
	LAi_SetCheckMinHP(sld, 1, true, "");
	LAi_SetOfficerType(sld);
	
	for (int i = 1; i <= 3; i++) {
		int index = GetOfficersIndex(pchar, i);
		
		if (index < 0) {
			continue;
		}
		
		sld = GetCharacter(index);
		if (sld.id == pchar.questTemp.TonzagQuest.BoardingGF) {
			continue;
		}
		
		LAi_SetOfficerType(sld);
	}
	
	pchar.OfficerAttRange = 1000.0;
	OfficersFollow();
	
	LAi_SetPlayerType(pchar);
	LAi_SetFightMode(pchar, true);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheckFunction("EnemyFight", "Tonzag_BoardingFightEnd");
}

void Tonzag_BoardingFightEnd(string qName) {
	LAi_LocationFightDisable(loadedLocation, true);
	//LAi_SetActorType(pchar);
	LAi_UseAtidoteBottle(pchar);
	//DoQuestCheckDelay("pchar_back_to_player", 1.0);
	
	sld = CharacterFromID(pchar.questTemp.TonzagQuest.BoardingGF);
	LAi_UseAtidoteBottle(sld);
	//LAi_Actor2WaitDialog(pchar, sld);
	sld.dialog.currentnode = "tonzag_after_boarding";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	AddLandQuestMark(sld, "questmarkmain");
	
	int totalSailors = sti(pchar.questTemp.TonzagQuest.SailorsCount);
	int aliveSailors = totalSailors;
	for (int i = 1; i <= totalSailors; i++) {
		sld = CharacterFromID("Tonzag_OurSailor_" + i);
		if (LAi_IsDead(sld)) {
			aliveSailors--;
			continue;
		}
		
		LAi_UseAtidoteBottle(sld);
		LAi_SetWarriorTypeNoGroup(sld);
	}
	
	int qty = GetCrewQuantity(pchar);
	SetCrewQuantity(pchar, qty * 0.5 + (qty * 0.5 * (aliveSailors * 1.0 / totalSailors)));
}

void Tonzag_GoToGunDeck() {
	sld = &locations[FindLocation("Deck_Galeon_Ship")];
	sld.lockCamAngle = 0.4;
	
	CloneLocation("Boarding_GunDeck", "Clone_location");
	DeleteAttribute(&locations[FindLocation("Clone_location")], "boarding");
	locations[FindLocation("Clone_location")].type = "clone";
	DoFunctionReloadToLocation("Clone_location", "quest", "mc_spawn", "Tonzag_SpawnGunDeck");
}

void Tonzag_SpawnGunDeck() {
	object spawnedOffs;
	
	for (int i = 1; i <= 3; i++) {
		int index = GetOfficersIndex(pchar, i);
		
		if (index < 0) {
			continue;
		}
		
		sld = GetCharacter(index);
		if (sld.id == pchar.questTemp.TonzagQuest.BoardingGF) {
			continue;
		}
		
		id = sld.id;
		spawnedOffs.(id) = true;
		
		ChangeCharacterAddressGroup(sld, "Clone_location", "quest", "mc_spawn");
		LAi_SetOfficerType(sld);
	}
	
	aref locators;
	makearef(locators, loadedLocation.locators.rld);
	int locCount = GetAttributesNum(locators);
	for (i = 1; i <= locCount; i++) {
		aref loc = GetAttributeN(locators, i - 1);
		string locatorName = GetAttributeName(loc);
		
		if (i % 5 != 1 && i % 5 != 4) {
			sld = GetCharacter(NPC_GenerateCharacter("Tonzag_DeadManOur_" + i, "citiz_" + (rand(9)+31), "man", "man_dead", 10, FRANCE, 0, true, "pirate"));
			sld.DontClearDead = true;
			sld.DeadWithBlade = true;
			ChangeCharacterAddressGroup(sld, pchar.location, "rld", locatorName);
			LAi_SetFightMode(sld, true);
			LAi_KillCharacter(sld);
			
			sld = GetCharacter(NPC_GenerateCharacter("Tonzag_DeadManEnemy_" + i, "killer_" + (1 + rand(4)), "man", "man_dead", 10, PIRATE, 0, false, "pirate"));
			sld.DontClearDead = true;
			sld.DeadWithBlade = true;
			sTemp = GetGeneratedItem("topor_04");
			GiveItem2Character(sld, sTemp);
			EquipCharacterByItem(sld, sTemp);
			ChangeCharacterAddressGroup(sld, pchar.location, "rld", locatorName);
			LAi_SetFightMode(sld, true);
			LAi_KillCharacter(sld);
			continue;
		}
		
		sld = GetCharacter(NPC_GenerateCharacter("Tonzag_AliveMan_" + i, "killer_" + (1 + rand(4)), "man", "man", 10, PIRATE, 0, false, "pirate"));
		ChangeCharacterAddressGroup(sld, pchar.location, "rld", locatorName);
		sTemp = GetGeneratedItem("topor_04");
		GiveItem2Character(sld, sTemp);
		EquipCharacterByItem(sld, sTemp);
		sld.viper = true;
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	
	string officers[6];
	officers[0] = "navigator";
	officers[1] = "boatswain";
	officers[2] = "cannoner";
	officers[3] = "doctor";
	officers[4] = "treasurer";
	officers[5] = "carpenter";
	
	for (i = 0; i < 6; i++) {
		string off = officers[i];
		
		index = sti(pchar.Fellows.Passengers.(off));
		
		if (index < 0) {
			continue;
		}
		
		sld = GetCharacter(index);
		if (sld.id == pchar.questTemp.TonzagQuest.BoardingGF) {
			continue;
		}
		
		string id = sld.id;
		if (CheckAttribute(&spawnedOffs, id)) {
			continue;
		}
		
		spawnedOffs.(id) = true;
		
		ChangeCharacterAddressGroup(sld, "Clone_location", "rld", "aloc" + (i + 1));
		LAi_SetOfficerType(sld);
	}
	
	OfficersFollow();
	
	LAi_SetPlayerType(pchar);
	LAi_SetFightMode(pchar, true);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheckFunction("EnemyFight", "Tonzag_GunDeckFightEnd");
}

void Tonzag_GunDeckFightEnd(string qName) {
	for (int i = 1; i <= 3; i++) {
		int index = GetOfficersIndex(pchar, i);
		
		if (index < 0) {
			continue;
		}
		
		sld = GetCharacter(index);
		if (sld.id == pchar.questTemp.TonzagQuest.BoardingGF) {
			continue;
		}
				
		LAi_UseAtidoteBottle(sld);
		sld.location = "none";
	}
	
	string officers[6];
	officers[0] = "navigator";
	officers[1] = "boatswain";
	officers[2] = "cannoner";
	officers[3] = "doctor";
	officers[4] = "treasurer";
	officers[5] = "carpenter";
	
	for (i = 0; i < 6; i++) {
		string off = officers[i];
		
		index = sti(pchar.Fellows.Passengers.(off));
		
		if (index < 0) {
			continue;
		}
		
		sld = GetCharacter(index);
		if (sld.id == pchar.questTemp.TonzagQuest.BoardingGF) {
			continue;
		}
		
		LAi_UseAtidoteBottle(sld);
		sld.location = "none";
	}
	
	LAi_SetActorType(pchar);
	LAi_UseAtidoteBottle(pchar);
	LAi_ActorRunToLocator(pchar, "reload", "reload_cabin", "Tonzag_TeleportToCabin", -1);
}

void Tonzag_SeeCabin() {
	chrDisableReloadToLocation = true;
	sld = CharacterFromID("Tonzag");
	ChangeCharacterAddressGroup(sld, pchar.location, "rld", "aloc2");
	LAi_SetActorType(pchar);
	LAi_SetActorType(sld);
	LAi_ActorTurnToLocator(sld, "reload", "reload1");
	LAi_CharacterEnableDialog(sld);
	//LAi_Actor2WaitDialog(pchar, sld);
	sld.dialog.currentnode = "tonzag_killed_hunters";
	SetActorDialogAny2Pchar(sld.id, "", -1, 0.0);
	LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 3.0);
	//LAi_ActorDialogDelay(sld, pchar, "", 3.0);
	
	for (i = 1; i <= 3; i++) {
		sld = GetCharacter(NPC_GenerateCharacter("Tonzag_DeadMan_" + i, "killer_" + (1 + rand(4)), "man", "man_dead", 10, PIRATE, 0, false, "pirate"));
		sTemp = GetGeneratedItem("topor_04");
		GiveItem2Character(sld, sTemp);
		EquipCharacterByItem(sld, sTemp);
		sld.DontClearDead = true;
		sld.CantLoot = true;
		sld.DeadWithBlade = true;
		ChangeCharacterAddressGroup(sld, pchar.location, "rld", "loc" + (i - 1));
		LAi_SetFightMode(sld, true);
		LAi_KillCharacter(sld);
	}
}

void Tonzag_Victory() {
	PlaySound("interface\abordage_wining.wav");
	DoQuestFunctionDelay("Tonzag_HelenaAfterVictory", 2.0);
}

void Tonzag_HelenaAfterVictory(string qName) {
	sld = CharacterFromID(pchar.questTemp.TonzagQuest.BoardingGF);
	ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
	LAi_SetActorType(sld);
	LAi_Actor2WaitDialog(pchar, sld);
	sld.dialog.currentnode = "tonzag_after_victory";
	LAi_ActorDialogNow(sld, pchar, "", -1);
}

void Tonzag_HelenBoardingDialog() {
	sld = CharacterFromID("Tonzag");
	LAi_SetActorType(sld);
	LAi_Actor2WaitDialog(pchar, sld);
	sld.dialog.currentnode = "tonzag_after_victory_helena";
	LAi_ActorDialogDelay(sld, pchar, "", 1.0);
}

void Tonzag_MaryBoardingDialog() {
	sld = CharacterFromID("Tonzag");
	LAi_SetActorType(sld);
	LAi_Actor2WaitDialog(pchar, sld);
	sld.dialog.currentnode = "tonzag_after_victory_mary";
	LAi_ActorDialogDelay(sld, pchar, "", 1.0);
}

void Tonzag_MaryBoardingDialog1() {
	LAi_SetPlayerType(pchar);
	
	sld = CharacterFromID("Tonzag");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "Tonzag_CabinMaryDialog", -1);
	
	sld = CharacterFromID("Mary");
	LAi_SetActorType(sld);
	LAi_ActorFollow(sld, pchar, "", -1);
}

void Tonzag_AlonsoBoardingDialog() {
	sld = CharacterFromID("Tonzag");
	LAi_SetActorType(sld);
	LAi_Actor2WaitDialog(pchar, sld);
	sld.dialog.currentnode = "tonzag_after_victory_alonso";
	LAi_ActorDialogDelay(sld, pchar, "", 1.0);
}

void Tonzag_HelenBoardingDialog1() {
	LAi_SetPlayerType(pchar);
	
	sld = CharacterFromID("Tonzag");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "Tonzag_CabinHelenaDialog", -1);
	
	sld = CharacterFromID("Helena");
	LAi_SetActorType(sld);
	LAi_ActorFollow(sld, pchar, "", -1);
}

void Tonzag_ShowFrame() {
	CloneLocation("My_Campus", "Clone_location");
	DeleteAttribute(&locations[FindLocation("Clone_location")], "boarding");
	
	SetLaunchFrameFormParam(StringFromKey("Tonzag_4"), "Reload_To_Location", 0, 4);
	SetLaunchFrameReloadLocationParam("Clone_location", "sit", "sit2", "Tonzag_Drink");
	LaunchFrameForm();
	WaitDate("", 0, 0, 0, 6, 0);
}

void Tonzag_ExitToSea() {
	aref arTmp;
	makearef(arTmp, pchar.questTemp.TonzagQuest.ShipPos);
	QuestToSeaLogin_Prepare(stf(arTmp.x), stf(arTmp.z), arTmp.Island);
	DeleteAttribute(pchar, "questTemp.TonzagQuest.ShipPos");
	QuestToSeaLogin_Launch();
	
	sld = CharacterFromID("Tonzag");
	LAi_SetOfficerType(sld);
	sld.dialog.currentnode = "tonzag_officer";
	sld.location = "none";
	SetCharacterRemovable(sld, true);
	sld.CompanionDisable = true;
	
	if (pchar.questTemp.TonzagQuest.BoardingGF == "Helena") {
		sld = CharacterFromID("Helena");
		LAi_SetOfficerType(sld);
		sld.dialog.currentnode = "helena_officer";
		sld.location = "none";
		LAi_SetImmortal(sld, false);
		LAi_RemoveCheckMinHP(sld);
	} else {		
		if (pchar.questTemp.TonzagQuest.BoardingGF == "Mary") {
			sld = CharacterFromID("Mary");
			LAi_SetOfficerType(sld);
			sld.dialog.currentnode = "mary_officer";
			sld.location = "none";
			LAi_SetImmortal(sld, false);
			LAi_RemoveCheckMinHP(sld);
		} else {
			if (pchar.questTemp.TonzagQuest.BoardingGF == "Tonzag_Alonso") {
				sld = CharacterFromID("Tonzag_Alonso");
				sld.lifeday = 0;
			} else {
				sld = CharacterFromID(pchar.questTemp.TonzagQuest.BoardingGF);
				LAi_SetOfficerType(sld);
				sld.dialog.currentnode = "hired";
				sld.location = "none";
				LAi_SetImmortal(sld, false);
				LAi_RemoveCheckMinHP(sld);
			}
		}
	}
		
	bDisableCharacterMenu = false;
	InterfaceStates.Buttons.Save.enable = true;
	bQuestDisableMapEnter = false;
	
	LAi_SetPlayerType(pchar);
	chrDisableReloadToLocation = false;
	
	locations[FindLocation("LosTeques_town")].QuestCapture = true;
	locations[FindLocation("LosTeques_town")].locators_radius.quest.detector1 = 6.0;
	locations[FindLocation("LosTeques_town")].locators_radius.reload = 0.0;
	locations[FindLocation("LosTeques_town")].locators_radius.reload.reload1_back = 1.0;
	Locations[FindLocation("LosTeques_town")].locators_radius.goto.goto8 = 15.0;
	Locations[FindLocation("LosTeques_town")].locators_radius.goto.goto35 = 15.0;
	SetFunctionLocationCondition("Tonzag_SetMine", "LosTeques_town", false);
	SetFunctionLocatorCondition("Tonzag_LookAtDead", "LosTeques_town", "quest", "detector1", false);
	
	PChar.quest.Tonzag_Rolik1.win_condition.l1 = "locator";
	PChar.quest.Tonzag_Rolik1.win_condition.l1.location = "LosTeques_town";
	PChar.quest.Tonzag_Rolik1.win_condition.l1.locator_group = "goto";
	PChar.quest.Tonzag_Rolik1.win_condition.l1.locator = "goto8";
	PChar.quest.Tonzag_Rolik1.function = "Tonzag_Rolik";
	
	PChar.quest.Tonzag_Rolik2.win_condition.l1 = "locator";
	PChar.quest.Tonzag_Rolik2.win_condition.l1.location = "LosTeques_town";
	PChar.quest.Tonzag_Rolik2.win_condition.l1.locator_group = "goto";
	PChar.quest.Tonzag_Rolik2.win_condition.l1.locator = "goto35";
	PChar.quest.Tonzag_Rolik2.function = "Tonzag_Rolik";
	
	AddQuestRecord("Tonzag", "6");
}
// Sinistra - Катсцена на руднике ==>
void Tonzag_Rolik(string qName) 
{
	StartQuestMovie(true, false, true);
	PChar.quest.Tonzag_Rolik1.over = "yes";
	PChar.quest.Tonzag_Rolik2.over = "yes";
	Locations[FindLocation("LosTeques_town")].locators_radius.goto.goto8 = 0.5;
	Locations[FindLocation("LosTeques_town")].locators_radius.goto.goto35 = 0.5;
	TeleportCharacterToPos(pchar, 27.57, 19.46, -28.39);
	LAi_SetActorType(pchar);
	LAi_ActorGoToLocator(pchar, "quest", "quest1", "", -1);
	locCameraFlyToPositionLookToHero(-4.8, 4.5, 7.25, 21.5, 24.0, -25.6, 1, 15000/GetDeltaTime());
	Pchar.FuncCameraFly = "Tonzag_Rolik_2";
}

void Tonzag_Rolik_2(string qName) 
{
	locCameraSleep(true);
	DoQuestFunctionDelay("Tonzag_Rolik_3", 3.5);
}

void Tonzag_Rolik_3(string qName) 
{
	EndQuestMovie();
	LAi_SetPlayerType(pchar);
	locCameraSleep(false);
	locCameraTarget(PChar);
	locCameraFollow();
	InterfaceStates.Buttons.Save.enable = false;
}
// <== Sinistra - Катсцена на руднике
void Tonzag_SetSong(string qName) {
	SetMusic("music_way_back_then");
}

void Tonzag_SetMine(string qName) {
	InterfaceStates.Buttons.Save.enable = false;
	chrDisableReloadToLocation = true;
	OfficersFollow();
	sld = CharacterFromID("Tonzag");
	PlaceCharacter(sld, "goto", "random_must_be_near");
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorFollow(sld, pchar, "", -1);
	//LocatorReloadEnterDisable("LosTeques_town", "gate_back", true);
	
	float centerX = -1.8;
	float centerY = -2.15;
	float centerZ = 2.65;
	float radius = 10.0;
	
	for (int i = 0; i < 42; i++) {
		string model, anim;
		bool equip = false;
		switch (rand(2)) {
			case 0:
				model = "prizon_" + (rand(3) + 5);
				anim = "man_B_dead";
			break;
			
			case 1:
				model = "sold_spa_" + (rand(15) + 1);
				anim = "man_dead";
				equip = true;
			break;
			
			case 2:
				model = "Miskito_" + (rand(5) + 1);
				anim = "man_dead";
			break;
		}
		
		sld = GetCharacter(NPC_GenerateCharacter("Tonzag_DeadMan_" + i, model, "man", anim, 10, SPAIN, -1, equip, "soldier"));
		sld.DontClearDead = true;
		if (equip) {
			sld.DeadWithBlade = true;
		}
		ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
		float ay = frand(PIm2) - PI;
		TeleportCharacterToPosAy(sld, centerX + frand(2 * radius) - radius, centerY, centerZ + frand(2 * radius) - radius, ay);
		if (equip) {
			LAi_SetFightMode(sld, true);
		}
		
		float x, y, z;
		GetCharacterPos(sld, &x, &y, &z);
		if (y > centerY + 1) {
			CharacterExitFromLocation(sld);
			sld.lifeday = 0;
		}
		sld.quest.pos.x = x;
		sld.quest.pos.y = y;
		sld.quest.pos.z = z;
		sld.quest.pos.ay = ay;
		
		SetCharacterTask_Dead(sld);
	}
	
	ChangeItemName("MerdokArchive", "itmname_MineArchive");
	ChangeItemDescribe("MerdokArchive", "itmdescr_MineArchive");
	pchar.GenQuestBox.LosTeques_mine = true;
	pchar.GenQuestBox.LosTeques_mine.box1.items.MerdokArchive = 1;
	pchar.GenQuestBox.LosTeques_mine.box1.items.chest = 1;
	if (!CheckCharacterItem(pchar, "map_full")) {
		pchar.GenQuestBox.LosTeques_mine.box1.items.map_full = 1;
	}
}

void Tonzag_CreateLoot() {
	pchar.GenQuestBox.IslaDeCoche_Grot = true;
	pchar.GenQuestBox.IslaDeCoche_Grot.box1.items.gold_dublon = 2000;
	pchar.GenQuestBox.IslaDeCoche_Grot.box1.items.suit4 = 1;
	
	sld = ItemsFromID("MerdokArchive");
	sld.price = 1;
}

void Tonzag_LookAtDead(string qName) {
	PChar.quest.Tonzag_Rolik1.over = "yes";
	PChar.quest.Tonzag_Rolik2.over = "yes";
	Locations[FindLocation("LosTeques_town")].locators_radius.goto.goto8 = 0.5;
	Locations[FindLocation("LosTeques_town")].locators_radius.goto.goto35 = 0.5;
	LAi_SetActorType(pchar);
	LAi_ActorTurnToLocator(pchar, "goto", "goto31");
	
	/*bOk = (GetCharacterIndex("Helena") >= 0);
	if (bOK) {
		sld = CharacterFromID("Helena");
	}
	
	if (bOK && sld.location == pchar.location) {
		sld.dialog.currentnode = "tonzag_dead";
		LAi_ActorDialogDelay(pchar, sld, "Tonzag_TichingituAboutDead", 3.0);
	} else {
		bOk = (GetCharacterIndex("Mary") >= 0);
		if (bOK) {
			sld = CharacterFromID("Mary");
		}
		
		if (bOk && sld.location == pchar.location) {
			sld.dialog.currentnode = "tonzag_dead";
			LAi_ActorDialogDelay(pchar, sld, "Tonzag_TichingituAboutDead", 3.0);
		} else {
			DoQuestCheckDelay("Tonzag_TichingituAboutDead", 3.0);
		}
	}*/
	
	sld = CharacterFromID("Tonzag");
	sld.dialog.currentnode = "tonzag_dead";
	LAi_Actor2WaitDialog(sld, pchar);
	LAi_ActorDialogDelay(pchar, sld, "pchar_back_to_player", 3.0);
}

void Tonzag_AfterDead() {
	sld = CharacterFromID("Tonzag");
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorFollow(sld, pchar, "", -1);
	
	chrDisableReloadToLocation = false;
	locations[FindLocation("LosTeques_mine")].QuestCapture = true;
	//locations[FindLocation("LosTeques_townhall")].QuestCapture = true;
	//locations[FindLocation("LosTeques_tavern")].QuestCapture = true;
	//locations[FindLocation("LosTeques_church")].QuestCapture = true;
	//locations[FindLocation("LosTeques_store")].QuestCapture = true;
	SetFunctionLocationCondition("Tonzag_InMine", "LosTeques_mine", false);
}

void Tonzag_InMine(string qName) {
	InterfaceStates.Buttons.Save.enable = true;
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(&locations[FindLocation("LosTeques_mine")], true);
	
	sld = CharacterFromID("Tonzag");
	PlaceCharacter(sld, "goto", "random_must_be_near");
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorFollow(sld, pchar, "", -1);
	
	aref locators;
	makearef(locators, loadedLocation.locators.goto);
	int locCount = GetAttributesNum(locators);
	for (i = 1; i <= locCount; i++) {
		aref loc = GetAttributeN(locators, i - 1);
		string locatorName = GetAttributeName(loc);
		
		string model, anim;
		bool equip = false;
		switch (rand(1)) {
			case 0:
				model = "prizon_" + (rand(3) + 5);
				anim = "man_B_dead";
			break;
			
			case 1:
				model = "sold_spa_" + (rand(15) + 1);
				anim = "man_dead";
				equip = true;
			break;
		}
		
		sld = GetCharacter(NPC_GenerateCharacter("Tonzag_MineDeadMan_" + i, model, "man", anim, 10, SPAIN, 0, equip, "soldier"));
		sld.DontClearDead = true;
		if (equip) {
			sld.DeadWithBlade = true;
		}
		ChangeCharacterAddressGroup(sld, pchar.location, "goto", locatorName);
		if (equip) {
			LAi_SetFightMode(sld, true);
		}		
		LAi_KillCharacter(sld);
	}
	
	sld = CharacterFromID("Tonzag_Killer");
	LAi_group_Delete("EnemyFight");
	ChangeCharacterAddressGroup(sld, pchar.location, "quest", "quest1");
	sld.talker = 10;
	sld.dialog.filename = "Quest\CompanionQuests\Tonzag.c";
	sld.dialog.currentnode = "killer";
	LAi_SetStayType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	
	for (i = 1; i <= 2; i++) {
		sld = GetCharacter(NPC_GenerateCharacter("Tonzag_KillerHelper_" + i, "killer_" + (1 + rand(4)), "man", "man", 10, PIRATE, 0, false, "pirate"));
		FantomMakeCoolFighter(sld, 30, 90, 90, "topor_04", "pistol2", "grapeshot", 350);
		ChangeCharacterAddressGroup(sld, pchar.location, "soldiers", "soldier" + i);
		sld.viper = true;
		LAi_SetStayType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
}

void Tonzag_FightInMine() {
	LAi_LocationFightDisable(&locations[FindLocation("LosTeques_mine")], false);
	sld = CharacterFromID("Tonzag");
	LAi_SetOfficerType(sld);
	LAi_SetCheckMinHP(sld, 1, true, "");
	
	aref locators;
	makearef(locators, loadedLocation.locators.monsters);
	int locCount = GetAttributesNum(locators);
	for (i = 1; i <= 20; i++) {
		aref loc = GetAttributeN(locators, i - 1);
		string locatorName = GetAttributeName(loc);
		
		sld = GetCharacter(NPC_GenerateCharacter("Tonzag_KillerMan_" + i, "killer_" + (1 + rand(4)), "man", "man", 15, PIRATE, 0, false, "pirate"));
		if (i <= 10) {
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
		} else {
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto5");
		}
		sTemp = GetGeneratedItem("topor_04");
		GiveItem2Character(sld, sTemp);
		EquipCharacterByItem(sld, sTemp);
		sld.viper = true;
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	
	PlaySound("interface\abordage_wining.wav");
	
	LAi_SetFightMode(pchar, true);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheckFunction("EnemyFight", "Tonzag_AfterMineFight");
	
	SetFunctionLocationCondition("Tonzag_ExitMine", "LosTeques_town", false);
}

void Tonzag_ExitMine(string qName) {
	sld = CharacterFromID("Tonzag");
	LAi_SetOfficerType(sld);
	LAi_LocationFightDisable(&locations[FindLocation("LosTeques_town")], true);
	DeleteAttribute(pchar, "GenQuestBox.LosTeques_mine");
	DeleteAttribute(&locations[FindLocation("LosTeques_town")], "box1");
	
	OfficersFollow();
	LAi_group_Delete("EnemyFight");
	LocatorReloadEnterDisable("LosTeques_town", "reload1_back", true);
	LocatorReloadEnterDisable("LosTeques_ExitTown", "reload4", true);
	
	for (int i = 0; i < 42; i++) {
		if (GetCharacterIndex("Tonzag_DeadMan_" + i) < 0) {
			continue;
		}
		
		sld = CharacterFromID("Tonzag_DeadMan_" + i);
		aref pos;
		makearef(pos, sld.quest.pos);
		TeleportCharacterToPosAy(sld, stf(pos.x), stf(pos.y), stf(pos.z), stf(pos.ay));
		
		LAi_KillCharacter(sld);
	}
	
	for (i = 1; i <= 2; i++) {
		sld = GetCharacter(NPC_GenerateCharacter("MineProtector_"+i, "sold_spa_"+(rand(7)+1), "man", "man", 30, SPAIN, -1, true, "soldier"));
		ChangeCharacterAddressGroup(sld, pchar.location, "quest", "soldier"+i);
		LAi_SetActorType(sld);
		LAi_ActorTurnToLocator(sld, "goto", "goto32");
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}	
	
	sld = GetCharacter(NPC_GenerateCharacter("MineHead", "off_spa_5", "man", "man", 35, SPAIN, -1, false, "soldier"));
	FantomMakeCoolFighter(sld, 35, 100, 100, "blade_17", "pistol4", "bullet", 250);
	sld.dialog.Filename = "Quest\CompanionQuests\Tonzag.c";
	sld.dialog.currentnode = "mine_head";
	sld.greeting = "soldier_arest";
	ChangeCharacterAddressGroup(sld, pchar.location, "quest", "mineHead");
	LAi_SetStayType(sld);
	sld.talker = 10;
	LAi_group_MoveCharacter(sld, "EnemyFight");
	CharacterTurnToLoc(sld, "goto", "goto32");
	
	SetFunctionLocationCondition("Tonzag_AssignHuntersTimer", "LosTeques_ExitTown", false);
	SetFunctionLocationCondition("Tonzag_CleanupMine", "LosTeques_ExitTown", false);
	SetFunctionLocationCondition("Tonzag_SeaAfterMine", "Cumana", false);
}

void Tonzag_AfterMineFight(string qName) {
	LAi_UseAtidoteBottle(pchar);
	sld = CharacterFromID("Tonzag");
	LAi_UseAtidoteBottle(sld);
	LAi_SetImmortal(sld, false);
	LAi_RemoveCheckMinHP(sld);
	LAi_SetActorTypeNoGroup(sld);
	sld.dialog.currentnode = "tonzag_afterminefight";
	SetActorDialogAny2Pchar(sld.id, "pchar_back_to_player", 0.0, 1.0);
	LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", -1);
}

void Tonzag_LetMineHeadGo() {
	sld = CharacterFromID("MineHead");
	sld.lifeday = 0;
	LAi_SetActorType(sld);
	LAi_SetImmortal(sld, true);
	LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
	
	for (i = 1; i <= 2; i++) {
		sld = CharacterFromID("MineProtector_"+i);
		sld.lifeday = 0;
		LAi_SetActorType(sld);
		LAi_SetImmortal(sld, true);
		LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
	}
}

void Tonzag_FightMineHead() {
	LAi_LocationFightDisable(&locations[FindLocation("LosTeques_town")], false);
	
	chrDisableReloadToLocation = true;
	LAi_SetFightMode(pchar, true);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
	DeleteQuestCheck("Tonzag_AssignHuntersTimer");
}

void Tonzag_AssignHunters(string qName) {
	ChangeCharacterHunterScore(pchar, "spahunter", 50);
}

void Tonzag_AssignHuntersTimer(string qName) {
	LAi_LocationFightDisable(&locations[FindLocation("LosTeques_town")], false);
	
	if (GetCharacterIndex("MineHead") >= 0) {
		sld = CharacterFromID("MineHead");
		sld.lifeday = 0;
		ChangeCharacterAddressGroup(sld, "none", "", "");
	}
	
	for (i = 1; i <= 2; i++) {
		if (GetCharacterIndex("MineProtector_"+i) >= 0) {
			sld = CharacterFromID("MineProtector_"+i);
			sld.lifeday = 0;
			ChangeCharacterAddressGroup(sld, "none", "", "");
		}
	}
	
	SetFunctionTimerCondition("Tonzag_AssignHunters", 0, 0, 1, false);
}

void Tonzag_CleanupMine(string qName) {
	SetFunctionTimerCondition("Tonzag_ResetMine", 0, 0, 30, false);
	sld = CharacterFromID("Tonzag");
	LAi_SetImmortal(sld, false);
	LAi_RemoveCheckMinHP(sld);
	
	LAi_LocationFightDisable(&locations[FindLocation("LosTeques_town")], false);
	
	AddQuestRecord("Tonzag", "7");
	
	//DeleteAttribute(&locations[FindLocation("LosTeques_mine")], "box1");
}

void Tonzag_ResetMineGuy(string id) {
	sld = CharacterFromID(id);
	SetRandomNameToCharacter(sld);
	sld.quest.meeting = "0";
}

void Tonzag_ResetMine(string qName) {
	LocatorReloadEnterDisable("LosTeques_town", "reload1_back", false);
	LocatorReloadEnterDisable("LosTeques_ExitTown", "reload4", false);
	
	DeleteAttribute(&locations[FindLocation("LosTeques_town")], "QuestCapture");
	DeleteAttribute(&locations[FindLocation("LosTeques_mine")], "QuestCapture");
	locations[FindLocation("LosTeques_town")].locators_radius.reload = 1.0;
	//DeleteAttribute(&locations[FindLocation("LosTeques_townhall")], "QuestCapture");
	//DeleteAttribute(&locations[FindLocation("LosTeques_tavern")], "QuestCapture");
	//DeleteAttribute(&locations[FindLocation("LosTeques_church")], "QuestCapture");
	//DeleteAttribute(&locations[FindLocation("LosTeques_store")], "QuestCapture");
	Tonzag_ResetMineGuy("LosTeques_Mayor");
	Tonzag_ResetMineGuy("LosTeques_trader");
	Tonzag_ResetMineGuy("LosTeques_tavernkeeper");
	Tonzag_ResetMineGuy("LosTeques_Priest");
}

void Tonzag_PrepareJournal() {
	sld = CharacterFromID("Tonzag");
	LAi_SetCitizenTypeNoGroup(sld);
	LAi_CharacterDisableDialog(sld);
	if (RemoveOfficersIndex(pchar, sti(sld.index))) {
		sld.isbusy = sti(sld.isbusy) - 1;
		if (sti(sld.isbusy) <= 0) {
			DeleteAttribute(sld, "isbusy");
		}
		DeleteAttribute(sld, "fighter");
	}
	SetCharacterRemovable(sld, false);
	
	chrDisableReloadToLocation = false;
}

void Tonzag_SeaAfterMine(string qName) {
	sld = CharacterFromID("Tonzag");
	LAi_SetOfficerType(sld);
	LAi_CharacterEnableDialog(sld);
	SetCharacterRemovable(sld, true);
	
	bQuestDisableMapEnter = true;
	Island_SetReloadEnableGlobal("Cumana", false);
	DoQuestFunctionDelay("Tonzag_GoToHold", 2.5);
	
	pchar.questTemp.TonzagQuest.ShipPos.x = pchar.ship.pos.x;
	pchar.questTemp.TonzagQuest.ShipPos.z = pchar.ship.pos.z;
	pchar.questTemp.TonzagQuest.ShipPos.Island = AISea.Island;
}

void Tonzag_GoToHold(string qName) {
	bQuestDisableMapEnter = false;
	Island_SetReloadEnableGlobal("Cumana", true);
	
	CloneLocation("My_deck", "Clone_location");
	DeleteAttribute(&locations[FindLocation("Clone_location")], "boarding");
	
	DoFunctionReloadToLocation("Clone_location", "rld", "aloc2", "Tonzag_SetHold");
}

void Tonzag_SetHold() {
	chrDisableReloadToLocation = true;
	
	sld = GetCharacter(NPC_GenerateCharacter("Tonzag_Captive", "killer_" + (1 + rand(4)), "man", "man", 15, PIRATE, -1, false, "pirate"));
	ChangeCharacterAddressGroup(sld, "Clone_location", "goto", "goto10");
	LAi_SetLayType(sld);
	
	LAi_SetActorType(pchar);
	LAi_ActorTurnToCharacter(pchar, sld);
	
	rCharacter = CharacterFromID("Tonzag");
	ChangeCharacterAddressGroup(rCharacter, "Clone_location", "rld", "aloc3");
	LAi_SetActorTypeNoGroup(rCharacter);
	LAi_ActorTurnToCharacter(rCharacter, sld);
	
	LAi_Actor2WaitDialog(pchar, rCharacter);
	rCharacter.dialog.currentnode = "tonzag_in_hold";
	LAi_ActorDialogDelay(rCharacter, pchar, "", 3.0);
}

void Tonzag_EnterAlonso() {
	LAi_ActorTurnToCharacter(pchar, CharacterFromID("Tonzag_Captive"));
	LAi_ActorTurnToCharacter(CharacterFromID("Tonzag"), CharacterFromID("Tonzag_Captive"));
	
	sld = GetCharacter(NPC_GenerateCharacter("Tonzag_Alonso", "citiz_36", "man", "man", 25, FRANCE, -1, true, "pirate"));
	sld.name = StringFromKey("Tonzag_2");
	sld.lastname = StringFromKey("Tonzag_3");
	sld.greeting = "hambit_other_4";
	sld.Dialog.Filename = "Quest\CompanionQuests\Tonzag.c";
	sld.dialog.currentnode = "alonso";
	ChangeCharacterAddressGroup(sld, "Clone_location", "reload", "reload1");
	LAi_SetActorType(sld);
	LAi_Actor2WaitDialog(pchar, sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void Tonzag_DrinkAgain() {
	CloneLocation("My_Campus", "Clone_location_1");
	DeleteAttribute(&locations[FindLocation("Clone_location_1")], "boarding");
	
	DoFunctionReloadToLocation("Clone_location_1", "sit", "sit2", "Tonzag_DrinkAgain1");
}

void Tonzag_DrinkAgain1() {
	LAi_SetSitType(pchar);
	sld = CharacterFromID("Tonzag");
	sld.dialog.currentnode = "tonzag_drink_again";
	ChangeCharacterAddressGroup(sld, pchar.location, "sit", "sit1");
	LAi_SetActorType(sld);
	LAi_ActorSetSitMode(sld);
	LAi_ActorDialogDelay(sld, pchar, "", 3.0);
	DoQuestFunctionDelay("Tonzag_SetSong", 0.5);
}

void Tonzag_ReturnToHold() {
	DoFunctionReloadToLocation("Clone_location", "rld", "aloc2", "Tonzag_SetHoldAfterDrink");
}

void Tonzag_SetHoldAfterDrink() {
	ResetSound();
	
	sld = CharacterFromID("Tonzag_Captive");
	sld.dialog.Filename = "Quest\CompanionQuests\Tonzag.c";
	sld.dialog.currentnode = "captive";
	LAi_SetGroundSitType(sld);
	CharacterTurnToLoc(sld, "rld", "aloc2");
	
	LAi_SetActorType(pchar);
	LAi_ActorTurnToCharacter(pchar, sld);
	
	rCharacter = CharacterFromID("Tonzag");
	ChangeCharacterAddressGroup(rCharacter, "Clone_location", "rld", "aloc3");
	LAi_SetActorType(rCharacter);
	LAi_ActorTurnToCharacter(rCharacter, sld);
	
	rCharacter = CharacterFromID("Tonzag_Alonso");
	ChangeCharacterAddressGroup(rCharacter, "Clone_location", "rld", "loc3");
	LAi_SetActorType(rCharacter);
	LAi_ActorTurnToCharacter(rCharacter, sld);
	
	LAi_ActorDialogDelay(pchar, sld, "", 3.0);
}

void Tonzag_HoldDialog() {
	sld = CharacterFromID("Tonzag");
	LAi_SetActorTypeNoGroup(sld);
	sld.dialog.currentnode = "tonzag_hold";
	LAi_Actor2WaitDialog(pchar, sld);
	LAi_ActorDialogDelay(sld, pchar, "", 1.0);
}

void Tonzag_HoldDialog2() {
	sld = CharacterFromID("Tonzag");
	LAi_SetActorTypeNoGroup(sld);
	sld.dialog.currentnode = "tonzag_hold_1";
	LAi_Actor2WaitDialog(pchar, sld);
	LAi_ActorDialogDelay(sld, pchar, "", 1.0);
}

void Tonzag_HoldDialog1() {
	sld = CharacterFromID("Tonzag_Captive");
	sld.dialog.currentnode = "captive_9";
	LAi_ActorDialogDelay(pchar, sld, "", 1.0);
}

void Tonzag_HoldDialog3() {
	sld = CharacterFromID("Tonzag_Captive");
	sld.dialog.currentnode = "captive_10";
	LAi_ActorDialogDelay(pchar, sld, "", 1.0);
}

void Tonzag_ExecuteCaptive() {
	sld = CharacterFromID("Tonzag_Captive");
	LAi_SetActorType(sld);
	LAi_ActorSetGroundSitMode(sld);
	LAi_ActorAnimation(sld, "Ground_Afraid", "", -1);
	
	if(GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE) == "") {
		GiveItem2Character(pchar, "pistol1");
		EquipCharacterbyItem(pchar, "pistol1");
	}
	
	QuestSceneStartShot(pchar, sld, "LAi_KillCharacter", "Tonzag_CaptiveDie");
}

void Tonzag_ReturnToCabin() {
	sld = CharacterFromID("Tonzag_Alonso");
	sld.lifeday = 0;
	sld = CharacterFromID("Tonzag_Captive");
	sld.lifeday = 0;
	
	Set_My_Cabin();
	CloneLocation(Get_My_Cabin(), "Clone_location");
	DeleteAttribute(&locations[FindLocation("Clone_location")], "boarding");
	DoFunctionReloadToLocation("Clone_location", "reload", "reload1", "Tonzag_AfterInterrogation");
}

void Tonzag_ReturnToCabin1(string qName) {
	sld = CharacterFromID("Tonzag_Alonso");
	sld.lifeday = 0;
	sld = CharacterFromID("Tonzag_Captive");
	sld.lifeday = 0;
	
	pchar.questTemp.TonzagQuest.Interrogated = true;
	Set_My_Cabin();
	CloneLocation(Get_My_Cabin(), "Clone_location_1");
	DeleteAttribute(&locations[FindLocation("Clone_location_1")], "boarding");
	DoFunctionReloadToLocation("Clone_location_1", "reload", "reload1", "Tonzag_AfterInterrogation");
}

void Tonzag_ReturnToCabin2() {
	sld = CharacterFromID("Tonzag_Alonso");
	sld.lifeday = 0;
	sld = CharacterFromID("Tonzag_Captive");
	sld.lifeday = 0;
	
	pchar.questTemp.TonzagQuest.Interrogated = true;
	Set_My_Cabin();
	CloneLocation(Get_My_Cabin(), "Clone_location_1");
	DeleteAttribute(&locations[FindLocation("Clone_location_1")], "boarding");
	DoFunctionReloadToLocation("Clone_location_1", "reload", "reload1", "Tonzag_AfterInterrogation");
}

void Tonzag_AfterInterrogation() {
	ResetSound();
	
	sld = CharacterFromID("Tonzag");
	PlaceCharacter(sld, "rld", "random_must_be_near");
	LAi_SetActorType(sld);
	LAi_SetActorType(pchar);
	LAi_Actor2WaitDialog(pchar, sld);
	
	if (CheckAttribute(pchar, "questTemp.TonzagQuest.Interrogated")) {
		sld.dialog.currentnode = "tonzag_after_hold";
	} else {
		sld.dialog.currentnode = "tonzag_after_drink";
	}
	DeleteAttribute(pchar, "questTemp.TonzagQuest.Interrogated");
	
	LAi_ActorDialogDelay(sld, pchar, "", 2.0);
}

void Tonzag_GoToCaracas() {
	SetFunctionLocationCondition("Tonzag_InCaracas", "Caracas_town", false);
	sld = CharacterFromID("Tonzag");
	LAi_SetOfficerType(sld);
	sld.dialog.currentnode = "tonzag_officer";
	
	LAi_SetPlayerType(pchar);
	
	bQuestDisableMapEnter = false;
	Island_SetReloadEnableGlobal("Cumana", true);
	chrDisableReloadToLocation = false;
	
	aref arTmp;
	makearef(arTmp, pchar.questTemp.TonzagQuest.ShipPos);
	QuestToSeaLogin_Prepare(stf(arTmp.x), stf(arTmp.z), arTmp.Island);
	DeleteAttribute(pchar, "questTemp.TonzagQuest.ShipPos");
	QuestToSeaLogin_Launch();
	
	if (!bImCasual) {
		SetFunctionTimerCondition("Tonzag_LateCaracas", 0, 1, 0, false);
	}
	else NewGameTip(StringFromKey("Tonzag_5"));
	
	AddQuestRecord("Tonzag", "7.1");
}

void Tonzag_LateCaracas(string qName) {
	DeleteQuestCheck("Tonzag_InCaracas");
	DeleteQuestCondition("Tonzag_InCaracas_2");
	
	sld = CharacterFromID("Tonzag");
	DeleteAttribute(sld, "CompanionDisable");
	
	CloseQuestHeader("Tonzag");
	//Открыт 'Медный всадник'
	notification(StringFromKey("Tonzag_6"), "Tonzag");
	Tonzag_UnlockTortuga();
}

void Tonzag_InCaracas(string qName) {
	if (GetHour() >= 6 && GetHour() <= 20)
	{
		chrDisableReloadToLocation = true;
		
		OfficersFollow();
		LAi_SetPlayerType(pchar);
		
		sld = CharacterFromID("Tonzag");
		PlaceCharacter(sld, "goto", "random_must_be_near");
		LAi_SetActorTypeNoGroup(sld);
		LAi_ActorFollow(sld, pchar, "", -1);
		
		sld = GetCharacter(NPC_GenerateCharacter("Tonzag_Cureer", "mercen_11", "man", "man", 25, PIRATE, 0, true, "quest"));
		sld.Dialog.Filename = "Quest\CompanionQuests\Tonzag.c";
		sld.dialog.currentnode = "cureer";
		LAi_SetImmortal(sld, true);
		PlaceCharacter(sld, "goto", "random_must_be_near");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 5);
	}
	else SetTimerFunction("Tonzag_InCaracas_2", 0, 0, 1);
}

void Tonzag_InCaracas_2(string qName) {
	SetFunctionLocationCondition("Tonzag_InCaracas", "Caracas_town", false);
}

void Tonzag_CureerGoAway() {
	sld = CharacterFromID("Tonzag_Cureer");
	LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
	
	pchar.GenQuest.CannotWait = true;
	//chrDisableReloadToLocation = false;
	
	SetFunctionLocatorCondition("Tonzag_NextToChurch", "Caracas_town", "reload", "reload7_back", false);
}

void Tonzag_NextToChurch(string qName) {
	//chrDisableReloadToLocation = true;
	
	sld = CharacterFromID("Tonzag");
	LAi_SetActorTypeNoGroup(sld);
	sld.dialog.currentnode = "tonzag_church";
	LAi_ActorDialog(sld, pchar, "", -1, 5);
}

void Tonzag_ChurchBad() {
	sld = CharacterFromID("Tonzag");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload7_back", "Caracas_church", "reload", "reload1", "Tonzag_GetAchievementBad", 5);
}

void Tonzag_BadEnd(string qName) {
	AddQuestRecord("Tonzag", "8");
	CloseQuestHeader("Tonzag");
	
	Tonzag_UnlockTortuga();
	
	aref rld;
	makearef(rld, locations[FindLocation("Caracas_town")].reload);
	
	string model;
	string animation;
	string sex;
	for (int i = 20; i <= 28; i++) {
		if (i == 20) {
			sld = CharacterFromID("Caracas_Priest");
			model = sld.model;
			animation = sld.model.animation;
			sex = sld.sex;
		} else {
			if (rand(1) == 0) {
				model = "citiz_" + (rand(9) + 11);
				animation = "man";
				sex = "man";
			} else {
				model = "women_" + (rand(11) + 7);
				animation = "woman";
				sex = "woman";
			}
		}
		
		sld = GetCharacter(NPC_GenerateCharacter("Tonzag_Citizen_" + i, model, sex, animation, 1, SPAIN, 0, false, "citizen"));
		ChangeCharacterAddressGroup(sld, "Caracas_town", "reload", "reload7");
		string locator = "l" + i;
		LAi_SetActorType(sld);
		LAi_ActorRunToLocation(sld, "reload", rld.(locator).name, "none", "", "", "", -1);
		LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	}
	
	chrDisableReloadToLocation = false;
	LAi_SetPlayerType(pchar);
	DeleteAttribute(pchar, "GenQuest.CannotWait");
	
	sld = &locations[FindLocation("Caracas_church")];
	sld.QuestCapture = true;
	
	sld = CharacterFromID("Caracas_Priest");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	
	SetFunctionLocationCondition("Tonzag_ShowTonzagBody", "Caracas_church", false);
	
	SetFunctionTimerCondition("Tonzag_ReopenChurch", 0, 0, 1, false);
	
	//Tonzag_CutScene();
}

void Tonzag_ShowTonzagBody(string qName) {
	DoQuestFunctionDelay("Tonzag_ShowTonzagBody1", 0.1);
}

void Tonzag_ShowTonzagBody1(string qName) {
	sld = CharacterFromID("Tonzag");
	sld.model.animation = "man_dead";
	ChangeCharacterAddressGroup(sld, "Caracas_church", "quest", "quest3");
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	LAi_KillCharacter(sld);
}

void Tonzag_ReopenChurch(string qName) {
	//LAi_group_SetRelation(LAI_GROUP_PLAYER, "SPAIN_CITIZENS", LAI_GROUP_NEITRAL);
	//LocatorReloadEnterDisable("Caracas_town", "reload7_back", false);
	sld = &locations[FindLocation("Caracas_church")];
	DeleteAttribute(sld, "QuestCapture");
	
	DeleteQuestCondition("Tonzag_ShowTonzagBody");
	
	if (GetCharacterIndex("Tonzag") >= 0) {
		sld = CharacterFromID("Tonzag");
		sld.lifeday = 0;
	}
	
	sld = CharacterFromID("Caracas_priest");
	ChangeCharacterAddressGroup(sld, "Caracas_church", "barmen", "stay");
}

void Tonzag_ResetTonzag() {
	chrDisableReloadToLocation = false;
	SetLocationCapturedState("Caracas_town", false);
	for (i=1; i<=20; i++)
	{
		if (CharacterIsAlive("Tonzag_MirnyeManChurch_"+i))
		{
			sld = CharacterFromID("Tonzag_MirnyeManChurch_"+i);
			sld.lifeday = 0;
		}
	}
	
	DeleteAttribute(pchar, "GenQuest.CannotWait");
	sld = CharacterFromID("Tonzag");
	SetCharacterPerk(sld, "Dragoon");
	Return_TonzagOfficer();
	
	Achievment_Set("ach_CL_91");
	AddQuestRecord("Tonzag", "9");
	CloseQuestHeader("Tonzag");
	Tonzag_UnlockTortuga();

	PChar.quest.Tonzag_CaracasTownBitva.win_condition.l1 = "location";
	PChar.quest.Tonzag_CaracasTownBitva.win_condition.l1.location = "Caracas_town";
	PChar.quest.Tonzag_CaracasTownBitva.function = "Tonzag_CaracasTownBitva";
}

void Tonzag_CaracasTownBitva(string qName) {
	Pchar.GenQuest.Hunter2Pause = true;
	CreateLocationParticles("shipfire", "reload", "reload7_back", 0, 0, 0, "");
	CreateLocationParticles("large_smoke", "reload", "reload7_back", 0, 0, 0, "");
	
	for (i = 1; i <= 18; i++) {
		sld = GetCharacter(NPC_GenerateCharacter("Tonzag_TownGuard_"+i, "sold_spa_"+(rand(7)+1), "man", "man", 10, SPAIN, 0, true, "soldier"));
		if (i>=1 && i<=6) ChangeCharacterAddressGroup(sld, "Caracas_town", "goto", "goto13");
		if (i>=7 && i<=12) ChangeCharacterAddressGroup(sld, "Caracas_town", "reload", "houseS1");
		if (i>=13 && i<=18) ChangeCharacterAddressGroup(sld, "Caracas_town", "reload", "houseS2");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	}
	for (i = 1; i <= 3; i++) {
		sld = GetCharacter(NPC_GenerateCharacter("Tonzag_TownCaptain_"+i, "off_spa_"+(rand(1)+1), "man", "man", 30, SPAIN, 0, true, "soldier"));
		LAi_SetHP(sld, 400.0, 400.0);
		if (i==1) ChangeCharacterAddressGroup(sld, "Caracas_town", "goto", "goto13");
		if (i==2) ChangeCharacterAddressGroup(sld, "Caracas_town", "reload", "houseS1");
		if (i==3) ChangeCharacterAddressGroup(sld, "Caracas_town", "reload", "houseS2");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	}
}

void Tonzag_ChurchGood() {
	sld = CharacterFromID("Tonzag");
	LAi_LoginInCaptureTown(sld, true);
	LAi_SetOfficerType(sld);
	OfficersFollow();
	SetLocationCapturedState("Caracas_town", true);
	
	LAi_SetActorType(pchar);
	LAi_ActorGoToLocator(pchar, "reload", "reload7_back", "Tonzag_InChurch", 5);
	
	sld = GetCharacter(NPC_GenerateCharacter("Tonzag_Ostin", "Ostin", "man", "man", 30, SPAIN, -1, false, "quest"));
	FantomMakeCoolFighter(sld, 30, 100, 70, "blade_13", "howdah", "GunEchin", 250);
	sld.name = StringFromKey("Tonzag_7");
	sld.lastname = StringFromKey("Tonzag_8");
	sld.dialog.filename = "Quest\CompanionQuests\Tonzag.c";
	sld.dialog.currentnode = "ostin";
	sld.SaveItemsForDead  = true; 
	sld.DontClearDead = true;
	sld.nonTable = true;
	sld.viper = true;
	GiveItem2Character(sld, "cirass9");
	if (!CheckCharacterItem(pchar, "map_full")) {
		GiveItem2Character(sld, "map_full");
	}
	ChangeCharacterAddressGroup(sld, "Caracas_church", "sit", "sit12");
	LAi_SetSitType(sld);
	LAi_LoginInCaptureTown(sld, true);
	
	sld = CharacterFromID("Caracas_priest");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	sld = GetCharacter(CreateCharacterClone(sld, -1));
	sld.id = "Caracas_priest_clone";
	ChangeCharacterAddressGroup(sld, "Caracas_church", "barmen", "stay");
	LAi_SetPriestType(sld);
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	LAi_LoginInCaptureTown(sld, true);
	LAi_SetHP(sld, 1.0, 1.0);
	
	for (i=1; i<=20; i++)
	{				
		sld = GetCharacter(NPC_GenerateCharacter("Tonzag_MirnyeManChurch_"+i, "citiz_"+(rand(19)+1), "man", "man", 1, FRANCE, -1, false, ""));
		LAi_SetSitType(sld);
		if (i==17 || i==19) sld.nonTable = true;
		else
		{
			sld.nonTable = true;
			sld.inChurch = true;
		}
		LAi_CharacterDisableDialog(sld);
		ChangeCharacterAddressGroup(sld, "Caracas_church", "sit", "sit"+i);
		LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
		LAi_LoginInCaptureTown(sld, true);
		LAi_SetHP(sld, 1.0, 1.0);
		if (i==2 || i==5 || i==6 || i==8 || i==11 || i==12 || i==13 || i==14 || i==15 || i==18 || i==20) sld.lifeday = 0;
		if (i==16)
		{
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "church_stay_1", "", 1.8);
		}
	}
	SetFunctionTimerCondition("Tonzag_ResetPriest", 0, 0, 14, false);
	
	LocatorReloadEnterDisable("Caracas_town", "reload7_back", true);
}

void Tonzag_CreateOstin() {
	chrDisableReloadToLocation = true;
	LAi_SetPlayerType(pchar);
	sld = CharacterFromID("Tonzag");
	ChangeCharacterAddressGroup(sld, "Caracas_church", "goto", "goto2");
	LAi_SetActorType(sld);
	LAi_ActorFollow(sld, pchar, "", -1);
	LAi_SetOfficerType(sld);
	OfficersFollow();
}

void Tonzag_ChurchVystrel() {
	//locCameraFromToPos(-0.65, 1.46, 1.77, true, 3.10, -0.50, 4.84);
	//locCameraFromToPos(-0.23, 1.18, 2.82, true, 3.54, -0.23, 5.15);
	locCameraFromToPos(-1.82, 1.36, 2.57, true, 3.13, -0.17, 4.79);
	LAi_SetActorType(pchar);
	DoQuestFunctionDelay("Tonzag_ChurchVystrel_2", 1.7);
	
	sld = GetCharacter(NPC_GenerateCharacter("Tonzag_OstinMan_7", "killer_" + (1 + rand(1)) + "_mush", "man", "mushketer", 25, PIRATE, 0, false, "pirate"));
	FantomMakeCoolFighter(sld, 25, 60, 80, "", "mushket3", "grapeshot", 200);
	sld.MusketerDistance = 0;
	LAi_LoginInCaptureTown(sld, true);
	ChangeCharacterAddressGroup(sld, "Caracas_church", "reload", "reload1");
	TeleportCharacterToPosAy(sld, 3.50, 0.00, 4.62, -1.90);
	sld.viper = true;
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
}

void Tonzag_ChurchVystrel_2(string qName) {
	sld = CharacterFromID("Tonzag_OstinMan_7");
	LAi_SetActorType(sld);
	LAi_ActorAnimation(sld, "Shot", "1", 1.5);
	DoQuestFunctionDelay("Tonzag_ChurchVystrel_3", 1.1);
}

void Tonzag_ChurchVystrel_3(string qName) {
	for (i=16; i<=20; i++)
	{				
		sld = GetCharacter(NPC_GenerateCharacter("Tonzag_MirnyeManChurch_"+i, "citiz_"+(rand(19)+1), "man", "man", 1, FRANCE, -1, false, ""));
		LAi_KillCharacter(sld);
	}
	//DoQuestFunctionDelay("Tonzag_ChurchVystrel_4", 0.2);
	DoQuestFunctionDelay("Tonzag_ChurchFight", 1.0);
}

void Tonzag_ChurchFight(string qName) {
	EndQuestMovie();
	PlaySound("People Fight\Boarding_People_02.wav");
	PlaySound("People Fight\Peace_woman_death_05.wav");
	locCameraTarget(PChar);
	locCameraFollow();
	LAi_SetPlayerType(pchar);
	LAi_LocationFightDisable(loadedLocation, false);
	LAi_SetFightMode(pchar, true);
	sld = CharacterFromID("Tonzag_Ostin");
	ChangeCharacterAddressGroup(sld, "Caracas_church", "goto", "mayor1");
	TeleportCharacterToPos(sld, -3.21, 0.00, 3.16);
	LAi_SetWarriorType(sld);
	LAi_group_Delete("EnemyFight");
	LAi_group_MoveCharacter(sld, "EnemyFight");
	
	sld = CharacterFromID("Tonzag");
	LAi_SetOfficerType(sld);
	OfficersFollow();
	LAi_SetCheckMinHP(sld, 1, true, "");
	
	for (i=1; i<=4; i++)
	{			
		if (CharacterIsAlive("Tonzag_MirnyeManChurch_"+i))
		{
			sld = CharacterFromID("Tonzag_MirnyeManChurch_"+i);
			LAi_SetActorType(sld);
			LAi_ActorAfraid(sld, Pchar, true);
			ChangeCharacterAddressGroup(sld, "Caracas_church", "goto", "tich");
		}
	}
	for (i=7; i<=10; i++)
	{
		if (CharacterIsAlive("Tonzag_MirnyeManChurch_"+i))
		{
			sld = CharacterFromID("Tonzag_MirnyeManChurch_"+i);
			LAi_SetActorType(sld);
			LAi_ActorAfraid(sld, Pchar, true);
			ChangeCharacterAddressGroup(sld, "Caracas_church", "goto", "pater2");
		}
	}
	
	for (int i = 1; i <= 6; i++) {
		if (i == 3 || i == 4) {
			sld = GetCharacter(NPC_GenerateCharacter("Tonzag_OstinMan_" + i, "killer_" + (1 + rand(1)) + "_mush", "man", "mushketer", 25, PIRATE, 0, false, "pirate"));
			FantomMakeCoolFighter(sld, 25, 60, 80, "", "mushket3", "grapeshot", 200);
			sld.MusketerDistance = 0;
		} else {	
			sld = GetCharacter(NPC_GenerateCharacter("Tonzag_OstinMan_" + i, "killer_" + (1 + rand(4)), "man", "man", 25, PIRATE, 0, false, "pirate"));
			FantomMakeCoolFighter(sld, 25, 80, 60, "topor_04", "pistol2", "grapeshot", 200);
		}
		LAi_LoginInCaptureTown(sld, true);
		ChangeCharacterAddressGroup(sld, "Caracas_church", "reload", "reload" + (1 + (i <= 3)));
		sld.viper = true;
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	sld = CharacterFromID("Tonzag_OstinMan_7");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_SetRelation("EnemyFight", "SPAIN_CITIZENS", LAI_GROUP_ENEMY);
	//LAi_group_SetRelation("SPAIN_CITIZENS", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_AttackGroup(LAI_GROUP_PLAYER, "SPAIN_CITIZENS");
	SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
	
	sld = CharacterFromID("Caracas_priest_clone");
	LAi_SetImmortal(sld, false);
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorAnimation(sld, "afraid", "", -1);
	
	DoQuestFunctionDelay("Tonzag_ChurchAddSoldiers", 30.0);
}

void Tonzag_ResetPriest(string qName) {
	LocatorReloadEnterDisable("Caracas_town", "reload7_back", false);
	
	rCharacter = CharacterFromID("Caracas_priest");
	ChangeCharacterAddressGroup(rCharacter, "Caracas_church", "barmen", "stay");
	
	if (GetCharacterIndex("Caracas_priest_clone") >= 0) {
		sld = CharacterFromID("Caracas_priest_clone");
		sld.lifeday = 0;
	} else {
		rCharacter.model = "priest_4";
		SetRandomNameToCharacter(rCharacter);
	}
}

void Tonzag_ChurchAddSoldiers(string qName) {
	for (i = 1; i <= 6; i++) {
		sld = GetCharacter(NPC_GenerateCharacter("Tonzag_ChurchGuard_"+i, "sold_spa_"+(rand(7)+1), "man", "man", 30, SPAIN, -1, true, "soldier"));
		LAi_LoginInCaptureTown(sld, true);
		ChangeCharacterAddressGroup(sld, "Caracas_church", "reload", "reload" + (1 + (i <= 3)));
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	}
	
	pchar.quest.Tonzag_WinInChurch.win_condition.l1 = "NPC_Death";
	pchar.quest.Tonzag_WinInChurch.win_condition.l1.character = "Tonzag_Ostin";
	
	for (int i = 1; i <= 6; i++) {
		string c1 = "l" + (2 * i);
		string c2 = "l" + (2 * i + 1);
		pchar.quest.Tonzag_WinInChurch.win_condition.(c1) = "NPC_Death";
		pchar.quest.Tonzag_WinInChurch.win_condition.(c1).character = "Tonzag_OstinMan_" + i;
		pchar.quest.Tonzag_WinInChurch.win_condition.(c2) = "NPC_Death";
		pchar.quest.Tonzag_WinInChurch.win_condition.(c2).character = "Tonzag_ChurchGuard_" + i;
	}
	
	pchar.quest.Tonzag_WinInChurch.function = "Tonzag_WinInChurch";
}

void Tonzag_WinInChurch(string qName) {
	LAi_LocationFightDisable(loadedLocation, true);
	
	LAi_UseAtidoteBottle(pchar);
	
	sld = CharacterFromID("Tonzag");
	LAi_UseAtidoteBottle(sld);
	LAi_RemoveCheckMinHP(sld);
	LAi_SetImmortal(sld, false);
	DeleteAttribute(sld, "CompanionDisable");
	
	LAi_SetActorType(sld);
	sld.dialog.currentnode = "tonzag_afterchurchfight";
	SetActorDialogAny2Pchar(sld.id, "pchar_back_to_player", 0.0, 1.0);
	LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", -1);
}

//=================================================================
//======================кейсы из quests_reaction===================
//=================================================================
bool Tonzag_QuestComplete(string sQuestName, string qname)
{
	ref sld;
	
	bool condition = true;
	
	if (sQuestName == "Tonzag_InJailRepeat") {
		DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
		LAi_SetActorType(pchar); // чтоб не убежал
		DoQuestCheckDelay("TalkSelf_Quest", 1.0);
	}
	
	else if (sQuestName == "Tonzag_KillerLookAtUs") {
		sld = CharacterFromID("Tonzag_Killer");
		LAi_ActorTurnToLocator(sld, "goto", "goto24");
		DoQuestFunctionDelay("Tonzag_KillerGoToTonzag", 3.0);
	}
	
	else if (sQuestName == "Tonzag_KillerPrepareShot") {
		sld = CharacterFromID("Tonzag_Killer");
		LAi_ActorTurnToCharacter(sld, CharacterFromID("Tonzag"));
		DoQuestFunctionDelay("Tonzag_KillerShoots", 1.0);
	}
	
	else if (sQuestName == "Tonzag_KillerGoAway") {
		sld = CharacterFromID("Tonzag_Killer");
		LAi_ActorGoToLocation(sld, "goto", "goto22", "none", "", "", "", -1);
		
		sld = CharacterFromID("Tonzag");
		SetCharacterTask_Dead(sld);
		PlaySound("People Fight\Death_NPC_08.wav");
	}
	
	else if (sQuestName == "Tonzag_JailOffSpeak") {
		sld = CharacterFromID("TortugaJailOff");
		sld.dialog.currentnode = "tonzag_bail";
		LAi_ActorDialogNow(sld, pchar, "", -1);
	}
	
	else if (sQuestName == "Tonzag_BailedFadeOut") {
		if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailChrs.Helena")) {
			sld = CharacterFromID("Helena");
			LAi_CharacterDisableDialog(sld);
			LAi_SetStayType(sld);
		}
		
		if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailChrs.Mary")) {
			sld = CharacterFromID("Mary");
			LAi_CharacterDisableDialog(sld);
			LAi_SetStayType(sld);
		}
		
		if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailChrs.Tichingitu")) {
			sld = CharacterFromID("Tichingitu");
			LAi_CharacterDisableDialog(sld);
			ChangeCharacterAddressGroup(sld, pchar.location, "quest", "tichingitu");
			LAi_SetGroundSitType(sld);
		}
		
		sld = CharacterFromID("TortugaJailOff");
		ChangeCharacterAddressGroup(sld, pchar.location, "sit", "sit1");
		LAi_SetHuberType(sld);
		LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
		LAi_CharacterDisableDialog(sld);
		
		ChangeCharacterAddressGroup(pchar, pchar.location, "goto", "goto23");
		chrDisableReloadToLocation = false;
	}
	
	else if (sQuestName == "Tonzag_TeleportToCabin") {
		Set_My_Cabin();
		CloneLocation(Get_My_Cabin(), "Clone_location_1");
		DeleteAttribute(&locations[FindLocation("Clone_location_1")], "boarding");
		DoFunctionReloadToLocation("Clone_location_1", "reload", "reload1", "Tonzag_SeeCabin");
	}
	
	else if (sQuestName == "Tonzag_CabinMaryDialog") {
		sld = CharacterFromID("Mary");
		sld.dialog.currentnode = "tonzag_after_victory_2";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	
	else if (sQuestName == "Tonzag_CabinHelenaDialog") {
		sld = CharacterFromID("Helena");
		sld.dialog.currentnode = "tonzag_after_victory_3";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	
	else if (sQuestName == "Tonzag_Drink") {
		LAi_SetSitType(pchar);
		sld = CharacterFromID("Tonzag");
		sld.dialog.currentnode = "tonzag_drink";
		ChangeCharacterAddressGroup(sld, pchar.location, "sit", "sit1");
		LAi_SetActorType(sld);
		LAi_ActorSetSitMode(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 3.0);
		DoQuestFunctionDelay("Tonzag_SetSong", 0.5);
	}
	
	/*else if (sQuestName == "Tonzag_TichingituAboutDead") {
		bOk = (GetCharacterIndex("Tichingitu") >= 0);
		if (bOk) {
			sld = CharacterFromID("Tichingitu");
		}
		
		if (bOk && sld.location == pchar.location) {
			sld.dialog.currentnode = "tonzag_dead";
			LAi_ActorDialogDelay(pchar, sld, "Tonzag_TonzagAboutDead", 1.0);
		} else {
			DoQuestCheckDelay("Tonzag_TonzagAboutDead", 1.0);
		}
	}
	
	else if (sQuestName == "Tonzag_TonzagAboutDead") {
		sld = CharacterFromID("Tonzag");
		sld.dialog.currentnode = "tonzag_dead";
		LAi_Actor2WaitDialog(sld, pchar);
		LAi_ActorDialogDelay(pchar, sld, "pchar_back_to_player", 1.0);
	}*/
	
	else if (sQuestName == "Tonzag_CaptiveDie") {
		Achievment_SetStat(95, 1);
		DoQuestFunctionDelay("Tonzag_ReturnToCabin1", 2.0);
	}
	
	else if (sQuestName == "Tonzag_GetAchievementBad") {
		Achievment_Set("ach_CL_91");
		LAi_SetActorType(pchar);
		pchar.questTemp.TonzagQuest.BadEnd = true;
		LAi_ActorGoToLocator(pchar, "goto", "goto11", "Tonzag_BadEnd", -1);
	}
	
	else if (sQuestName == "Tonzag_BadEnd") {
		sld = CharacterFromID("Tonzag");
		sld.location = "none";
		RemovePassenger(pchar, sld);
		DeleteAttribute(sld, "OfficerImmortal");
		if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
		if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
		sTemp = "RestoreHealth_" + sld.index;
		if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
		//LAi_KillCharacter(sld);
		PlaySound3D("pistol_shot", -7.8, 6.75, -46.74);
		LAi_SetActorType(pchar);
		LAi_ActorTurnToLocator(pchar, "reload", "reload7_back");
		DoQuestFunctionDelay("Tonzag_BadEnd", 3.0);
	}
	
	else if (sQuestName == "Tonzag_InChurch") {
		DoFunctionReloadToLocation("Caracas_church", "reload", "reload1", "Tonzag_CreateOstin");
	}
	else
	{
		condition = false;
	}
	
	return condition;
}