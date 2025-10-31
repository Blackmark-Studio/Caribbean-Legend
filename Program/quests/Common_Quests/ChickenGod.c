void ChickenGod_PreInit() {
	pchar.quest.ChickenGod_Init.win_condition.l1 = "locator";
	pchar.quest.ChickenGod_Init.win_condition.l1.location = "Temple";
	pchar.quest.ChickenGod_Init.win_condition.l1.locator_group = "reload";
	pchar.quest.ChickenGod_Init.win_condition.l1.locator = "reload2";
	pchar.quest.ChickenGod_Init.function = "ChickenGod_Init";
	
	for (int i = 2; i <= 7; i++) {
		SetItemInLocation("talisman11", "Temple", "item" + i);
	}
	
	SetItemInLocation("talisman11", "LeFransua_Town", "qflower1");//добавить локатор
	SetItemInLocation("talisman11", "Shore39", "qflower1");
}

void ChickenGod_Init(string qName) {
	if (!GetDLCenabled(DLC_APPID_2)) {
		return;
	}
	
	sld = GetCharacter(NPC_GenerateCharacter("Joruba", "Chavinavi_1", "man", "man", 100, PIRATE, -1, false, "quest"));
	sld.name = StringFromKey("ChickenGod_1");
	sld.lastname = StringFromKey("ChickenGod_2");
	FantomMakeCoolFighter(sld, 100, 100, 100, "khopesh2", "", "", 1000);
	LAi_SetImmortal(sld, true);
	sld.dialog.FileName = "Quest\ChickenGod.c";
	sld.dialog.currentnode = "joruba";
	ChangeCharacterAddressGroup(sld, "Temple_Inside", "goto", "goto1");
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "Joruba");
	
	pchar.quest.ChickenGod_OpenTemple.win_condition.l1 = "locator";
	pchar.quest.ChickenGod_OpenTemple.win_condition.l1.location = "Temple";
	pchar.quest.ChickenGod_OpenTemple.win_condition.l1.locator_group = "reload";
	pchar.quest.ChickenGod_OpenTemple.win_condition.l1.locator = "reload2";
	pchar.quest.ChickenGod_OpenTemple.function = "ChickenGod_OpenTemple";
	pchar.quest.ChickenGod_OpenTemple.again = true;
}

/*void ChickenGod_JorubaChangeModel(string qName) {
	if (GetCharacterIndex("Joruba") < 0) {
		return;
	}
	
	sld = CharacterFromID("Joruba");
	sld.model = "citiz_" + (1 + rand(59));
	
	SetFunctionTimerCondition("ChickenGod_JorubaChangeModel", 0, 0, 1, true);
}*/

void ChickenGod_BrothelCheck(string qName)
{
	if (!GetDLCenabled(DLC_APPID_2)) return;
	if (!CheckAttribute(pchar, "questTemp.CG_SpawnAguebana"))
	{
		pchar.questTemp.CG_SpawnAguebana = true;
		sld = GetCharacter(NPC_GenerateCharacter("ChickenGod_Native", "Aguebana", "man", "man", 1, PIRATE, -1, true, "native"));
		sld.name = StringFromKey("ChickenGod_3");
		sld.lastname = StringFromKey("ChickenGod_4");
		sld.greeting = "indian_male";
		sld.dialog.FileName = "Quest\ChickenGod.c";
		sld.dialog.currentnode = "native";
		sld.DontClearDead = true;
		sld.SaveItemsForDead = true;
		TakeNItems(sld, "talisman11", 99);
		GiveItem2Character(sld, "cannabis7");
		ChangeCharacterAddressGroup(sld, "Panama_brothel", "goto", "goto1");
		LAi_SetCitizenType(sld);
		LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
		AddLandQuestMark(sld, "questmarkmain");
		AddMapQuestMarkCity("Panama", false);
		
		SetItemInLocation("talisman11", "Panama_Brothel", "item1");
		SetItemInLocation("talisman11", "Panama_SecBrRoom", "item1");
		SetItemInLocation("talisman11", "Panama_SecBrRoom", "item6");
		
		Locations[FindLocation("Panama_SecBrRoom")].locators_radius.item.item6 = 1.0;
		
		sld = CharacterFromID("Panama_Hostess");
		SetNPCQuestDate(sld, "quest.date");
	}
}

void ChickenGod_Game1() {
	sld = CharacterFromID("ChickenGod_Native");
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorTurnToCharacter(sld, pchar);
	sld.money = 20000;
	pchar.GenQuest.Cards.npcharIdx = sld.index;
	pchar.GenQuest.Cards.iRate = 1000;
	pchar.GenQuest.Cards.SitType = false;
	pchar.GenQuest.Cards.OnWin = "ChickenGod_Game1Win";
	pchar.GenQuest.Cards.OnLoss = "ChickenGod_Game1Loss";
	pchar.GenQuest.Cards.DontStop = true;
	LaunchCardsGame();
}

void ChickenGod_Game1Win(string qName) {
	chrDisableReloadToLocation = true;
	sld = CharacterFromID("ChickenGod_Native");
	sld.dialog.currentnode = "native_cards_win";
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialogNow(sld, pchar, "", -1);
}

void ChickenGod_Game1Loss(string qName) {
	chrDisableReloadToLocation = true;
	sld = CharacterFromID("ChickenGod_Native");
	sld.dialog.currentnode = "native_cards_loss";
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialogNow(sld, pchar, "", -1);
}

void ChickenGod_Game1LossGoAway() {
	sld = CharacterFromID("ChickenGod_Native");
	TakeNItems(sld, "talisman11", -1);
	TakeNItems(pchar, "talisman11", 1);
	sld.lifeday = 0;
	AddMoneyToCharacter(sld, 30000);
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload2_back", "none", "", "", "ChickenGod_NativeGone", -1);
	LAi_LocationFightDisable(&locations[FindLocation("Panama_Brothel")], false);
	LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld) - 1, false, "ChickenGod_BrothelFight");
}

void ChickenGod_BrothelFightWin(string qName) {
	chrDisableReloadToLocation = false;
	LAi_LocationFightDisable(&locations[FindLocation("Panama_Brothel")], true);
}

void ChickenGod_Game1WinNoRematch() {
	sld = CharacterFromID("ChickenGod_Native");
	sld.lifeday = 0;
	AddMoneyToCharacter(sld, 30000);
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "ChickenGod_NativeGone", -1);
	LAi_LocationFightDisable(&locations[FindLocation("Panama_Brothel")], false);
	LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld) - 1, false, "ChickenGod_BrothelFight");
}

void ChickenGod_Game1WinRematch() {
	pchar.questTemp.ChickenGod.HostessDialog = true;
	sld = CharacterFromID("ChickenGod_Native");
	DeleteAttribute(sld, "lifeday");
	AddMoneyToCharacter(sld, 30000);
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload2_back", "Panama_Brothel_room", "goto", "goto1", "OpenTheDoors", -1);
	
	LocatorReloadEnterDisable("Panama_Brothel", "reload1_back", true);
	LocatorReloadEnterDisable("Panama_SecBrRoom", "reload2", true);
}

void ChickenGod_PayForRoom() {
	AddMoneyToCharacter(pchar, -10000);
	LocatorReloadEnterDisable("Panama_Brothel", "reload2_back", false);
	
	ChangeCharacterComplexReputation(pchar, "nobility", -3);
	ChangeCharacterComplexReputation(pchar, "authority", -3);
	
	sld = CharacterFromID("ChickenGod_Native");
	LAi_SetCitizenTypeNoGroup(sld);
	sld.dialog.currentnode = "native_dice";
	
	SetItemInLocation("talisman11", "Panama_Brothel_room", "item3");
}

void ChickenGod_NotPayForRoom() {
	sld = CharacterFromID("ChickenGod_Native");
	sld.lifeday = 0;
	
	DoReloadCharacterToLocation("Panama_town", "reload", "reload9");
	
	LocatorReloadEnterDisable("Panama_Brothel", "reload1_back", false);
	LocatorReloadEnterDisable("Panama_SecBrRoom", "reload2", false);
}

void ChickenGod_Game2() {
	sld = CharacterFromID("ChickenGod_Native");
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorTurnToCharacter(sld, pchar);
	pchar.GenQuest.Dice.npcharIdx = sld.index;
	pchar.GenQuest.Dice.iRate = 1000;
	pchar.GenQuest.Dice.SitType = false;
	pchar.GenQuest.Dice.OnWin = "ChickenGod_Game2Win";
	pchar.GenQuest.Dice.OnLoss = "ChickenGod_Game2Loss";
	pchar.GenQuest.Dice.DontStop = true;
	LaunchDiceGame();
}

void ChickenGod_Game2Win(string qName) {
	chrDisableReloadToLocation = true;
	sld = CharacterFromID("ChickenGod_Native");
	sld.dialog.currentnode = "native_dice_win";
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialogNow(sld, pchar, "", -1);
	
	LocatorReloadEnterDisable("Panama_Brothel", "reload2_back", true);
}

void ChickenGod_Game2Loss(string qName) {
	chrDisableReloadToLocation = true;
	sld = CharacterFromID("ChickenGod_Native");
	sld.dialog.currentnode = "native_dice_loss";
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialogNow(sld, pchar, "", -1);
	
	LocatorReloadEnterDisable("Panama_Brothel", "reload2_back", true);
}

void ChickenGod_NotBuyAmulets() {
	chrDisableReloadToLocation = false;
	sld = CharacterFromID("ChickenGod_Native");
	sld.lifeday = 0;
	LAi_CharacterDisableDialog(sld);
	
	TakeNItems(sld, "talisman11", -1);
	TakeNItems(pchar, "talisman11", 1);
	
	LocatorReloadEnterDisable("Panama_Brothel", "reload1_back", false);
	LocatorReloadEnterDisable("Panama_SecBrRoom", "reload2", false);
	
	SetFunctionLocationCondition("ChickenGod_CloseBrothel", "Panama_town", false);
}

void ChickenGod_BuyAmulets() {
	sld = CharacterFromID("ChickenGod_Native");
	sld.lifeday = 0;
	
	LocatorReloadEnterDisable("Panama_Brothel", "reload1_back", false);
	LocatorReloadEnterDisable("Panama_SecBrRoom", "reload2", false);
	
	//AddMoneyToCharacter(pchar, -50000);
	TakeNItems(pchar, "talisman11", 99);
	
	TavernWaitDate("wait_day");
	DoFunctionReloadToLocation("Panama_tavern_upstairs", "goto", "goto1", "ChickenGod_JorubaExitTavern");
}

void ChickenGod_JorubaExitTavern() {
	if (!GetDLCenabled(DLC_APPID_2)) return;
	sld = GetCharacter(NPC_GenerateCharacter("JorubaClon", "Chavinavi_1", "man", "man", 100, PIRATE, 0, false, "quest"));
	sld.name = StringFromKey("ChickenGod_1");
	sld.lastname = StringFromKey("ChickenGod_2");
	ChangeCharacterAddressGroup(sld, "Panama_tavern_upstairs", "goto", "goto3");
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "ChickenGod_JorubaExitTavern", -1);
}

void ChickenGod_OpenTemple(string qName) {
	if (!GetDLCenabled(DLC_APPID_2)) return;
	if (GetCharacterItem(pchar, "talisman11") < 113) {
		if (!CheckAttribute(pchar, "questTemp.ChickenGod.Temple.FirstTime")) {
			pchar.questTemp.ChickenGod.Temple.FirstTime = true;
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.SawJoruba")) {
				AddQuestRecord("ChickenGod", "2");
			}
		}
	} else {
		TakeNItems(pchar, "talisman11", -113);
		
		LocatorReloadEnterDisable("Temple", "reload2", false);
		PlaySound("Ambient\Teno_inside\big_ring.wav");
		DeleteQuestCondition("ChickenGod_OpenTemple");
		
		sld = &locations[FindLocation("Temple_Inside")];
		LAi_LocationFightDisable(sld, true);
		sld.timeLock = true;
		sld.CannotWait = true;
		
		if (CheckAttribute(pchar, "questTemp.ChickenGod.SawJoruba")) {
			AddQuestRecord("ChickenGod", "3");
			if (LanguageGetLanguage() == "russian") AddQuestUserData("ChickenGod", "sSex1", GetSexPhrase("","а"));
		} else {
			AddQuestRecord("ChickenGod", "4");
			if (LanguageGetLanguage() == "russian") AddQuestUserData("ChickenGod", "sSex1", GetSexPhrase("","а"));
		}
	}
}

void ChickenGod_GiveFirstTask() {
	pchar.questTemp.ChickenGod.Tasks.p1 = true;
	
	pchar.questTemp.ChickenGod.Tasks.o2.Counter = 0;
	pchar.questTemp.ChickenGod.Tasks.o3 = true;
	pchar.questTemp.ChickenGod.Tasks.o4 = true;
	pchar.questTemp.ChickenGod.Tasks.o5 = true;

	if (CheckAttribute(pchar, "questTemp.ChickenGod.SawJoruba")) {
		AddQuestRecord("ChickenGod", "5");
		if (LanguageGetLanguage() == "russian") AddQuestUserData("ChickenGod", "sSex1", GetSexPhrase("ен","на"));
	} else {
		AddQuestRecord("ChickenGod", "5.1");
		if (LanguageGetLanguage() == "russian") AddQuestUserData("ChickenGod", "sSex1", GetSexPhrase("ен","на"));
	}
	
	AddQuestRecordInfo("ChickenGodOptionalQuests", "1");
	AddQuestUserData("ChickenGodOptionalQuests", "sName", GetFullName(pchar));
	
	ChickenGod_InTemple("");
	
	//SetFunctionTimerCondition("ChickenGod_JorubaChangeModel", 0, 0, 1, true);
}

void ChickenGod_GiveSecondTask() {
	pchar.questTemp.ChickenGod.Tasks.p2 = true;
	AddQuestRecord("ChickenGod", "6");
	if (LanguageGetLanguage() == "russian") AddQuestUserData("ChickenGod", "sSex1", GetSexPhrase("","а"));
	if (LanguageGetLanguage() == "russian") AddQuestUserData("ChickenGod", "sSex2", GetSexPhrase("","а"));
}

void ChickenGod_GiveThirdTask() {
	pchar.questTemp.ChickenGod.Tasks.p3 = true;
	AddQuestRecord("ChickenGod", "7");
}

void ChickenGod_GiveFourthTask() {
	pchar.questTemp.ChickenGod.Tasks.p4 = true;
	AddQuestRecord("ChickenGod", "8");
}

void ChickenGod_GiveFifthTask() {
	pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices = 0;
	AddQuestRecord("ChickenGod", "9");
	if (LanguageGetLanguage() == "russian") AddQuestUserData("ChickenGod", "sSex1", GetSexPhrase("","а"));
}

void ChickenGod_ModifyStats(float mod) {
	IncreaseChrModifier(pchar, M_ENERGY_MAX, mod, "ChickenGod");
	IncreaseChrModifier(pchar, M_HP_MAX, mod, "ChickenGod");
	CT_UpdateCashTables(pchar);
	float hp = LAi_GetCharacterMaxHP(pchar);
	LAi_SetHP(pchar, hp, hp);
}

void ChickenGod_CloseTemple(string qName) {
	LocatorReloadEnterDisable("Temple", "reload2", true);
	SetFunctionTimerCondition("ChickenGod_ReopenTemple", 0, 0, 1, false);
}

void ChickenGod_ReopenTemple(string qName) {
	if (!GetDLCenabled(DLC_APPID_2)) return;
	LocatorReloadEnterDisable("Temple", "reload2", false);
	SetFunctionLocationCondition("ChickenGod_InTemple", "Temple_Inside", false);
	
	sld = CharacterFromID("Joruba");
	LAi_SetCitizenTypeNoGroup(sld);
}

void ChickenGod_InTemple(string qName) {
	pchar.quest.ChickenGod_CloseTemple.win_condition.l1 = "ExitFromLocation";
	pchar.quest.ChickenGod_CloseTemple.win_condition.l1.location = "Temple_Inside";
	pchar.quest.ChickenGod_CloseTemple.function = "ChickenGod_CloseTemple";
}

void ChickenGod_Respec() {
	pchar.SystemInfo.ChangePIRATES = true;
	pchar.SystemInfo.ChangePIRATES.NotFirstTime = true;
	LaunchCharacter(pchar);
}

void ChickenGod_NotTakeLadyConsequence(string qName) {
	ChangeCharacterComplexReputation(pchar, "nobility", 30);
	ChangeCharacterHunterScore(pchar, "spahunter", -30);
}

void ChickenGod_LadyRefuse() {
	LAi_group_AttackGroup(LAI_GROUP_PLAYER, "SPAIN_CITIZENS");
	SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
}

void ChickenGod_TakeLady() {
	sld = CharacterFromID(pchar.questTemp.ChickenGod.Tasks.o2.Lady);
	LAi_CharacterDisableDialog(sld);
	LAi_SetImmortal(sld, true);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	sld.location = "none";
	DeleteAttribute(sld, "lifeday");
	AddPassenger(pchar, sld, false);
	SetCharacterRemovable(sld, false);
}

void ChickenGod_RemovePrisoners() {
	int prisoners[PASSENGERS_MAX];
	int prisonersFound = 0;
	
	int passengersQty = GetPassengersQuantity(pchar);
	for(int i = 0; i < passengersQty; i++)
	{
		if (prisonersFound >= 30) {
			break;
		}
		
		int idx = GetPassenger(pchar, i);
		if (idx < 0) {
			continue;
		}
		
		sld = GetCharacter(idx);
		if (!CheckAttribute(sld, "prisoned") || !sti(sld.prisoned) || !GetRemovable(sld)) {
			continue;
		}
		
		prisoners[prisonersFound] = idx;
		prisonersFound++;
	}
	
	for (i = 0; i < prisonersFound; i++) {
		ReleasePrisoner(GetCharacter(prisoners[i]));
	}
}

bool ChickenGod_IsDone() {
	for (int i = 2; i <= 6; i++) {
		if (!CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o" + i + ".Completed")) {
			return false;
		}
	}
	
	return true;
}

void ChickenGod_Cleanup() {
	sld = CharacterFromID("Joruba");
	sld.lifeday = 0;
	
	if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o2.Lady")) {
		int index = GetCharacterIndex(pchar.questTemp.ChickenGod.Tasks.o2.Lady);
		if (index >= 0) {			
			sld = GetCharacter(index);
			RemovePassenger(pchar, sld);
			sld.lifeday = 0;
		}
	}
	
	pchar.questTemp.ChickenGod.Tasks.o2.Done = true;
	
	DeleteQuestCondition("ChickenGod_ReopenTemple");
	DeleteQuestCondition("ChickenGod_CloseTemple");
	DeleteQuestCondition("ChickenGod_InTemple");
	LocatorReloadEnterDisable("Temple", "reload2", true);
}

void ChickenGod_FinalGood() {
	chrDisableReloadToLocation = true;
	
	ChickenGod_Cleanup();
	
	sld = CharacterFromID("Joruba");
	sld.model = "diego_6";
	Characters_RefreshModel(sld);
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
	
	AddQuestRecord("ChickenGod", "10");
	if (LanguageGetLanguage() == "russian") AddQuestUserData("ChickenGod", "sSex1", GetSexPhrase("ен","на"));
	CloseQuestHeader("ChickenGod");
	Achievment_Set("ach_CL_86");
	if (pchar.rank <= 17) Achievment_Set("ach_CL_117");
	
	SetItemInLocation("khopesh1",  "Temple_inside", "item1");
	Item_OnUnLoadLocation();
	Item_OnLoadLocation("Temple_inside");
	
	PChar.quest.ChickenGod_TheInquisition.win_condition.l1 = "location";
	PChar.quest.ChickenGod_TheInquisition.win_condition.l1.location = "Temple";
	PChar.quest.ChickenGod_TheInquisition.function = "ChickenGod_TheInquisition";
}

void ChickenGod_TheInquisition(string qName)
{
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(&Locations[FindLocation("Temple")], true);
	
	sld = GetCharacter(NPC_GenerateCharacter("ChickenGod_Inquisitor", "priest_sp1", "man", "man2", 30, SPAIN, -1, false, "quest"));
	sld.name = StringFromKey("ChickenGod_9");
	sld.lastname = StringFromKey("ChickenGod_10");
	sld.dialog.filename = "Quest\ChickenGod.c";
	sld.dialog.currentnode = "ChickenGod_TheInquisition_1";
	ChangeCharacterAddressGroup(sld, "Temple", "reload", "reload1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);	
	
	for (i=1; i<=6; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("ChickenGod_Inquisition"+i, "sold_spa_"+(rand(7)+1), "man", "man", 10, SPAIN, -1, false, "quest"));
		GiveItem2Character(sld, "blade_13");
		EquipCharacterByItem(sld, "blade_13");
		ChangeCharacterAddressGroup(sld, "Temple", "reload", "reload1");
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, CharacterFromID("ChickenGod_Inquisitor"), "", -1);
	}
	for (i=7; i<=10; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("ChickenGod_Inquisition"+i, "mush_spa_"+(rand(2)+1), "man", "mushketer", 10, SPAIN, -1, false, "quest"));
		GiveItem2Character(sld, "mushket1");
		EquipCharacterByItem(sld, "mushket1");
		ChangeCharacterAddressGroup(sld, "Temple", "reload", "reload1");
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, CharacterFromID("ChickenGod_Inquisitor"), "", -1);
	}
}

void ChickenGod_Insult() {
	string loc = "FortFrance_Brothel_room";
	if (CheckAttribute(pchar, "questTemp.ChickenGod.SelectedBrothel")) {
		loc = pchar.questTemp.ChickenGod.SelectedBrothel + "_room";
	}
	
	DoFunctionReloadToLocation(loc, "goto", "goto3", "ChickenGod_WaitForJaguars");
}

void ChickenGod_WaitForJaguars() {
	chrDisableReloadToLocation = true;
	bDisableCharacterMenu = true;
	
	LAi_SetActorType(pchar);
	LAi_ActorTurnToLocator(pchar, "box", "box1");
	DoQuestFunctionDelay("ChickenGod_JaguarsEnter", 3.0);
}

void ChickenGod_JaguarsEnter(string qName) {
	LAi_ActorTurnToLocator(pchar, "reload", "reload1_back");
	
	for (int i = 0; i < 3; i++) {
		sld = GetCharacter(NPC_GenerateCharacter("ChickenGod_Jaguar_" + i, "Itza_" + (1 + rand(7)), "man", "man", 1, PIRATE, 0, true, "native"));
		sld.name = GetIndianName(MAN);
		sld.lastname = "";
		FantomMakeCoolFighter(sld, 1, 1, 1, LinkRandPhrase("topor_01", "blade_01", "blade_02"), "", "", 50);
		ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
		
		LAi_SetActorType(sld);
		
		if (i == 0) {
			LAi_ActorFollow(sld, pchar, "ChickenGod_JaguarsArrive", -1);
		} else {
			LAi_ActorFollow(sld, pchar, "", -1);
		}
	}
}

void ChickenGod_JaguarsBoarding(string qName) {
	SetMusicAlarm("");
	PlaySound("interface\abordage2.wav");
}

void ChickenGod_AmeliaOpenChest() {
	sld = &locations[FindLocation("Amelia_house")];
	DeleteAttribute(sld, "box1");
	sld.box1 = Items_MakeTime(0, 0, 0, 2024);
	
	sld.box1.items.cannabis1 = 30;
	sld.box1.items.cannabis2 = 30;
	sld.box1.items.cannabis3 = 30;
	sld.box1.items.cannabis4 = 30;
	sld.box1.items.cannabis5 = 30;
	sld.box1.items.cannabis6 = 30;
	sld.box1.items.cannabis7 = 3; // Rebbebion, три стебля мангаросы
	sld.box1.items.mineral17 = 30;
	sld.box1.items.mineral3 = 100;
	sld.box1.items.potionrum = 30;
	sld.box1.items.potion5 = 30;
	sld.box1.items.potionwine = 30;
	sld.box1.items.potion2 = 30;
	sld.box1.items.bullet = 30;
	sld.box1.items.gunpowder = 30;
	sld.box1.items.grapeshot = 30;
	sld.box1.items.mineral1 = 30;
	sld.box1.items.mineral22 = 30;
	sld.box1.items.slave_01 = 100;
	sld.box1.items.mineral23 = 100;
	sld.box1.items.mineral9 = 30;
	sld.box1.items.mineral13 = 30;
	sld.box1.items.mineral18 = 30;
	sld.box1.items.mineral14 = 30;
	sld.box1.items.mineral4 = 30;
	sld.box1.items.mineral30 = 30;
	sld.box1.items.mineral24 = 30;
	sld.box1.items.mineral2 = 30;
	sld.box1.items.mineral8 = 30;
	sld.box1.items.mineral7 = 30;
	sld.box1.items.mineral25 = 30;
	sld.box1.items.mineral15 = 30;
	sld.box1.items.mineral31 = 30;
	sld.box1.items.mineral12 = 30;
}

void ChickenGod_KillOfficer() {
	//ChangeCharacterComplexReputation(pchar, "nobility", -200);
	//AddCrewMorale(pchar, -200);
	
	sld = CharacterFromID(pchar.questTemp.ChickenGod.Sacrifice);
	RemovePassenger(pchar, sld);
	sld.lifeday = 0;
	
	if (!CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6")) {
		WaitDate("", 0, 0, 0, 1, 0);
		DeleteQuestCondition("ChickenGod_CloseTemple");
		DoFunctionReloadToLocation("Temple", "reload", "reload2", "ChickenGod_WaitHour");
	}
}

void ChickenGod_KickedFromTemple() {
	DoReloadCharacterToLocation("Temple", "reload", "reload2");
}

void ChickenGod_KickedFromTemple1(string qName) {
	DoReloadCharacterToLocation("Temple", "reload", "reload2");
}

void ChickenGod_WaitHour() {
	ChickenGod_ReopenTemple("");
}

void ChickenGod_ShootJoruba() {
	if(GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE) == "") {
		GiveItem2Character(pchar, "pistol1");
		EquipCharacterbyItem(pchar, "pistol1");
	}
	
	sld = CharacterFromID("Joruba");
	LAi_SetStayTypeNoGroup(sld);
	QuestSceneStartShot(pchar, sld, "", "ChickenGod_TalkToJoruba");
}

void ChickenGod_GetHit() {
	QuestSceneStartMelee(CharacterFromID("Joruba"), pchar, "ChickenGod_HitConsequence", "ChickenGod_JorubaSheathe");
}

void ChickenGod_HitConsequence(ref mc) {
	LAi_Fade("ChickenGod_HitConsequence", "");
}

void ChickenGod_JorubaToNormal() {
	sld = CharacterFromID("Joruba");
	LAi_SetCitizenTypeNoGroup(sld);
	LAi_SetPlayerType(pchar);
}

//=================================================================
//======================кейсы из quests_reaction===================
//=================================================================
bool ChickenGod_QuestComplete(string sQuestName, string qname)
{
	ref sld;
	int i;
	
	bool condition = true;
	
	if (sQuestName == "ChickenGod_BrothelFight") {
		sld = CharacterFromID("ChickenGod_Native");
		LAi_SetWarriorTypeNoGroup(sld);
		chrDisableReloadToLocation = true;
		SetFunctionNPCDeathCondition("ChickenGod_BrothelFightWin", "ChickenGod_Native", false);
	}
	
	else if (sQuestName == "ChickenGod_NativeGone") {
		chrDisableReloadToLocation = false;
		LAi_LocationFightDisable(&locations[FindLocation("Panama_Brothel")], true);
	}
	
	else if (sQuestName == "ChickenGod_JorubaExitTavern") {
		chrDisableReloadToLocation = false;
		//sld = CharacterFromID("Joruba");
		//LAi_SetCitizenTypeNoGroup(sld);
		
		pchar.questTemp.ChickenGod.SawJoruba = true;
		AddQuestRecord("ChickenGod", "1");
		AddQuestUserData("ChickenGod", "sSex1", GetSexPhrase("ёл","ела"));
		AddQuestUserData("ChickenGod", "sSex2", GetSexPhrase("","а"));
	}
	
	else if (sQuestName == "ChickenGod_JaguarsArrive") {
		pchar.GenQuest.FrameLockEsc = true;
		SetLaunchFrameFormParam("", "ChickenGod_JaguarsFinished", 0, 16);
		LaunchFrameForm();
		WaitDate("", 0, 0, 0, 3, 5);
		PlaySound("People fight\Afraid_01.wav");
		DoQuestFunctionDelay("ChickenGod_JaguarsBoarding", 1.0);
	}
	
	else if (sQuestName == "ChickenGod_JaguarsFinished") {
		DeleteAttribute(pchar, "GenQuest.FrameLockEsc");
		chrDisableReloadToLocation = false;
		bDisableCharacterMenu = false;
		LAi_SetPlayerType(pchar);
		DoReloadCharacterToLocation("Temple", "reload", "reload2");
		ChickenGod_Cleanup();
		LAi_SetHP(pchar, LAi_GetCharacterMaxHP(pchar) - 1, LAi_GetCharacterMaxHP(pchar) - 1);
		CloseQuestHeader("ChickenGod");
		Achievment_Set("ach_CL_85");
	}
	
	else if (sQuestName == "ChickenGod_TalkToJoruba") {
		LAi_SetActorType(pchar);
		LAi_ActorDialogDelay(pchar, CharacterFromID("Joruba"), "", 1.5);
	}
	
	else if (sQuestName == "ChickenGod_JorubaSheathe") {
		SendMessage(CharacterFromID("Joruba"), "ll", MSG_CHARACTER_BLADEHAND, 0);
	}
	
	else if (sQuestName == "ChickenGod_HitConsequence") {
		LAi_SetGroundSitType(pchar);
		ChickenGod_ModifyStats(-55.0);
		LAi_SetHP(pchar, 1, LAi_GetCharacterMaxHP(pchar));
		AddCharacterHealth(pchar, -200.0);
		ChangeCharacterComplexReputation(pchar, "nobility", 30);
		
		sld = CharacterFromID("Joruba");
		LAi_ActorDialogDelay(sld, pchar, "", 1.5);
	}
	
	else if (sQuestName == "ChickenGod_TheInquisitionLeave") {
		LAi_LocationFightDisable(&Locations[FindLocation("Temple")], false);
	
		sld = CharacterFromID("ChickenGod_Inquisitor");
		sld.lifeday = 0;
		//ChangeCharacterAddressGroup(sld, "none", "", "");
		
		for (i=1; i<=10; i++)
		{
			sld = CharacterFromID("ChickenGod_Inquisition"+i);
			sld.lifeday = 0;
			//ChangeCharacterAddressGroup(sld, "none", "", "");
		}
	}
	else
	{
		condition = false;
	}
	
	return condition;
}