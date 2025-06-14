///////////////////////////////////////////////////////////////////////////////////////////////////////////	
///Sinistra---------------------------Вступительное обучение на палубе корабля----------------------------
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void SharlieTutorial_StartGameInPaluba(string qName)
{
	//После диалога с матросом Шарль получает полный контроль над персонажем
	EndQuestMovie();
	locCameraSleep(false);
	ChangeCharacterAddressGroup(pchar, "Quest_Ship_deck_Medium_trade", "quest", "quest2");
	LAi_SetPlayerType(pchar);
	LAi_SetCurHPMax(pchar);
	AddQuestRecord("SharlieTutorial", "0");
	AddQuestRecordInfo("Sharlie_Father", "1");
	AddQuestRecordInfo("Sharlie_Shevallie", "1");
	AddQuestRecordInfo("Sharlie_Lover", "1");
	
	DeleteAttribute(pchar, "TutorialToDeck_1");
	Achievment_Set("Test_Ach");
	
	// убираем корабль
	pchar.Ship.Type = SHIP_NOTUSED;
	// прописываем локации
	sld = &Locations[FindLocation("Quest_Ship_deck_Medium_trade")];
	
	// активируемые объекты на корабле
	SetLocatorEvent(sld.id, "event1", "SharlieTutorial_windlass_1");
	
	SetItemInLocation("potionrum", "Quest_Cabin_Medium", "item1");
	SetItemInLocation("potionrum", "Quest_Deck", "item1");
	
	// лут в сундуках на корабле
	sld = &Locations[FindLocation("Quest_Cabin_Medium")];
	sld.private1.items.gold = 4500;
	//sld.private1.items.purse1 = 1;
	sld.private1.key = "tutorial_key";
	sld.private1.key.delItem = true;
	sld.private2.items.Mineral21 = 1;
	sld.private2.items.Mineral3 = 3;
	sld.private2.items.Tutorial_journal = 1;
	sld.private3.items.hat3 = 1;
	sld.private3.items.cirass5 = 1;
	sld = &locations[FindLocation("Quest_Ship_deck_Medium_trade")];
	sld.private1.items.Mineral16 = 1;
	sld.private1.items.Mineral26 = 1;
	sld.private1.items.Mineral17 = 1;
	sld.private2.items.potion5 = 1;
	sld.private2.items.bullet = 1;
	sld.private3.items.potion2 = 1;
	sld.private3.items.Mineral8 = 2;
	sld.private3.items.Mineral18 = 2;
	sld.private3.items.Mineral22 = 3;
	sld.private3.items.Mineral23 = 5;
	sld = &locations[FindLocation("Quest_Campus")];
	sld.private1.items.grapeshot = 1;
	sld.private2.items.Mineral26 = 1;
	sld.private2.items.Mineral17 = 1;
	sld.private2.items.Mineral19 = 1;
	sld.private3.items.jewelry6 = 1;
	sld.private4.items.Mineral33 = 1;
	sld = &Locations[FindLocation("Quest_Deck_Medium")];
	sld.private1.items.bullet = 1;
	sld.private2.items.potion5 = 1;
	sld.private3.items.Mineral17 = 1;
	sld.private3.items.potion1 = 1;
	sld.private3.items.jewelry5 = 1;
	sld.private4.items.Mineral33 = 1;
	sld = &locations[FindLocation("Quest_Deck")];
	sld.private1.items.Mineral17 = 1;
	sld.private1.items.bullet = 1;
	sld.private2.items.potion5 = 1;
	sld.private2.items.grapeshot = 1;
	sld.private3.items.Mineral17 = 1;
	sld.private4.items.BoxOfBalls = 1;
	Box_OnLoadLocation(loadedLocation);
	
	// матросы на корабле
	sld = GetCharacter(NPC_GenerateCharacter("SharlieTutorial_Captain", "mercen_20", "man", "man", 10, FRANCE, -1, false, "quest")); // капитан корабля
	sld.name = StringFromKey("SharlieTutorial_1");
	sld.lastname = "";
	SetFantomParamFromRank(sld, 10, true);
	RemoveAllCharacterItems(sld, true);
	GiveItem2Character(sld, "blade_12");
	EquipCharacterbyItem(sld, "blade_12");
	GiveItem2Character(sld, "pistol5");
	EquipCharacterByItem(sld, "pistol5");
	if (MOD_SKILL_ENEMY_RATE > 4) SetCharacterPerk(sld, "Sliding");
	sld.Dialog.Filename = "Quest\Sharlie\Tutorial.c";
	sld.Dialog.currentnode = "Captain";
	sld.watchglass = true;
	ChangeCharacterAddressGroup(sld, "Quest_Ship_deck_Medium_trade", "quest", "quest3");
	LAi_SetStayType(sld);
	AddLandQuestMark(sld, "questmarkmain");
	for (i=2; i<=4; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("SharlieTutorial_Sailor_"+i, "citiz_3"+i, "man", "man", 5, FRANCE, -1, false, "pirate")); // матросы статисты
		sld.name 	= StringFromKey("SharlieTutorial_2");
		sld.lastname = "";
		ChangeCharacterAddressGroup(sld, "Quest_Ship_deck_Medium_trade", "goto", "goto"+i);
		LAi_SetStayType(sld);
		LAi_CharacterDisableDialog(sld);
		if (i==4) // матрос хочет рома
		{
			sld.name 	= StringFromKey("SharlieTutorial_8");
			sld.Dialog.Filename = "Quest\Sharlie\Tutorial.c";
			sld.Dialog.currentnode = "SailorWantRum";
			AddLandQuestMark(sld, "questmarkgen");
			LAi_CharacterEnableDialog(sld);
		}
	}
	sld = GetCharacter(NPC_GenerateCharacter("SharlieTutorial_Sailor_5", "citiz_34", "man", "man", 5, FRANCE, -1, false, "pirate")); // матрос гуляет по палубе
	sld.name 	= StringFromKey("SharlieTutorial_2");
	sld.lastname = "";
	ChangeCharacterAddressGroup(sld, "Quest_Ship_deck_Medium_trade", "goto", "goto5");
	LAi_SetCitizenType(sld);
	LAi_CharacterDisableDialog(sld);
	
	sld = GetCharacter(NPC_GenerateCharacter("SharlieTutorial_Sailor_6", "citiz_35", "man", "man", 10, FRANCE, -1, true, "pirate")); // охранник каюты
	sld.name 	= StringFromKey("SharlieTutorial_2");
	sld.lastname = "";
	ChangeCharacterAddressGroup(sld, "Quest_Ship_deck_Medium_trade", "quest", "quest4");
	LAi_SetStayType(sld);
	sld.Dialog.Filename = "Quest\Sharlie\Tutorial.c";
	sld.Dialog.currentnode = "OhrannikCabin";
	AddLandQuestMark(sld, "questmarkgen");
	SetFunctionLocatorCondition("SharlieTutorial_OhrannikStopaet", "Quest_Ship_deck_Medium_trade", "reload", "reload_cabin", false)
	
	//Брашпиль
	sld = GetCharacter(NPC_GenerateCharacter("SharlieTutorial_Windlass", "windlass", "man", "windlass", 15, FRANCE, -1, false, "quest"));
    sld.name = "";
    sld.lastname = "";
	ChangeCharacterAddressGroup(sld, "Quest_Ship_deck_Medium_trade", "quest", "quest5");
	LAi_CharacterDisableDialog(sld);
	
	//Матрос в трюме
	sld = GetCharacter(NPC_GenerateCharacter("SharlieTutorial_Sailor_7", "citiz_37", "man", "man", 5, FRANCE, -1, false, "pirate")); // старый матрос
	sld.name 	= StringFromKey("SharlieTutorial_2");
	sld.lastname = "";
	ChangeCharacterAddressGroup(sld, "Quest_Deck", "goto", "goto1");
	LAi_SetGroundSitType(sld);
	sld.Dialog.Filename = "Quest\Sharlie\Tutorial.c";
	sld.Dialog.currentnode = "OldSailor";
	
	//Матросы на орудийной палубе
	sld = GetCharacter(NPC_GenerateCharacter("SharlieTutorial_Sailor_8", "citiz_40", "man", "man", 5, FRANCE, -1, false, "pirate")); // матросу нужен ящик
	sld.name 	= StringFromKey("SharlieTutorial_7");
	sld.lastname = "";
	ChangeCharacterAddressGroup(sld, "Quest_Deck_Medium", "goto", "goto5");
	LAi_SetCitizenType(sld);
	sld.Dialog.Filename = "Quest\Sharlie\Tutorial.c";
	sld.Dialog.currentnode = "SailorNeedBox";
	AddLandQuestMark(sld, "questmarkgen");
	
	sld = GetCharacter(NPC_GenerateCharacter("SharlieTutorial_Sailor_9", "citiz_39", "man", "man", 5, FRANCE, -1, false, "pirate")); // матросу нужно золото
	sld.name 	= StringFromKey("SharlieTutorial_2");
	sld.lastname = "";
	ChangeCharacterAddressGroup(sld, "Quest_Deck_Medium", "goto", "goto2");
	LAi_SetCitizenType(sld);
	//sld.Dialog.Filename = "Quest\Sharlie\Tutorial.c";
	//sld.Dialog.currentnode = "EvilSailor";
	LAi_CharacterDisableDialog(sld);
	
	//офицеры в кают-компании
	sld = GetCharacter(NPC_GenerateCharacter("SharlieTutorial_Officer_1", "mercen_5", "man", "man", 10, FRANCE, -1, false, "quest")); // офицер спит
	ChangeCharacterAddressGroup(sld, "Quest_Campus", "lay", "lay1");
	LAi_SetLayType(sld);
	LAi_CharacterDisableDialog(sld);
	
	sld = GetCharacter(NPC_GenerateCharacter("SharlieTutorial_Officer_2", "mercen_8", "man", "man", 10, FRANCE, -1, false, "quest")); // офицер-торговец
	sld.name 	= StringFromKey("SharlieTutorial_3");
	sld.lastname = "";
	sld.Merchant.type = "SharlieTurorial";
	GiveItemToTrader(sld);
	ChangeCharacterAddressGroup(sld, "Quest_Campus", "quest", "quest1");
	LAi_SetStayType(sld);
	sld.Dialog.Filename = "Quest\Sharlie\Tutorial.c";
	sld.Dialog.currentnode = "OfficerTorgovets";
	AddMoneyToCharacter(sld, 1000);
	sld.Unpushable = "";
	
	sld = GetCharacter(NPC_GenerateCharacter("SharlieTutorial_Officer_3", "trader_8", "man", "man", 10, FRANCE, -1, false, "quest")); // офицер-казначей
	sld.name 	= StringFromKey("SharlieTutorial_9");
	sld.lastname = StringFromKey("SharlieTutorial_10");
	//sld.tutorial.overload = true;
	ChangeCharacterAddressGroup(sld, "Quest_Campus", "sit", "sit5");
	LAi_SetSitType(sld);
	sld.nonTable = true;
	sld.Dialog.Filename = "Quest\Sharlie\Tutorial.c";
	sld.Dialog.currentnode = "OfficerKaznachey";
	AddLandQuestMark(sld, "questmarkgen");
	
	//матрос моет полы
	sld = GetCharacter(NPC_GenerateCharacter("SharlieTutorial_Sailor_11", "citiz_37", "man", "man", 5, FRANCE, -1, false, "quest"));
	sld.name 	= StringFromKey("SharlieTutorial_2");
	sld.lastname = "";
	sld.Unpushable = "";
	ChangeCharacterAddressGroup(sld, "Quest_Ship_deck_Medium_trade", "quest", "quest8");
	SendMessage(sld, "lslssl", MSG_CHARACTER_EX_MSG, "TieItem", FindItem("Brush_Props"), "Brush_Props", "Saber_hand", 1);
	LAi_SetActorType(sld);
	LAi_ActorAnimation(sld, "tutorial_4", "", -1.0);
	SetFunctionLocationCondition("SharlieTutorial_SailorCleansFloors", "Quest_Ship_deck_Medium_trade", true);
	
	// матрос, который разговаривал с Шарлем, отходит в сторону
	sld = CharacterFromID("SharlieTutorial_Sailor_10");
	ChangeCharacterAddressGroup(sld, "Quest_Ship_deck_Medium_trade", "goto", "goto7");
	sld.Dialog.Filename = "Quest\Sharlie\Tutorial.c";
	sld.Dialog.currentnode = "AlonsoWait";
	LAi_SetStayType(sld);
	//LAi_ActorGoToLocator(sld, "goto", "goto7", "", -1);
	
	// остальное
	chrDisableReloadToLocation = false;
	bGameMenuStart = false;
	pchar.GenQuest.NoExp = true;
	pchar.GenQuest.BlockTalkSelf = true;
	pchar.GenQuest.CannotWait = true;
	bDisableCharacterMenu = false;
	InterfaceStates.Buttons.Save.enable = true;
	DeleteAttribute(pchar, "questTemp.NoFast");
	//InterfaceStates.Buttons.Save.enable = false;
	LAi_LocationFightDisable(loadedLocation, true);
	QuestPointerToLoc("Quest_Deck_Medium", "reload", "reload_deck");
	
	QuestPointerToLoc("Quest_Deck", "box", "private4");
	PChar.quest.SharlieTutorial_BoxOfBallsFind.win_condition.l1 = "item";
	PChar.quest.SharlieTutorial_BoxOfBallsFind.win_condition.l1.item = "BoxOfBalls";
	PChar.quest.SharlieTutorial_BoxOfBallsFind.function = "SharlieTutorial_BoxOfBallsFind";
	
	PChar.quest.SharlieTutorial_journal.win_condition.l1 = "item";
	PChar.quest.SharlieTutorial_journal.win_condition.l1.item = "Tutorial_journal";
	PChar.quest.SharlieTutorial_journal.function = "SharlieTutorial_journal";
	DoQuestFunctionDelay("SharlieTutorial_ResetInterface", 0.1);
	DoQuestFunctionDelay("Tutorial_CameraControl", 1.5);
	
	sld = &Locations[FindLocation("Quest_Deck_Medium")];
	sld.type = "quest_deck";
	sld = &Locations[FindLocation("Quest_Campus")];
	sld.type = "quest_deck";
	sld = &Locations[FindLocation("Quest_Deck")];
	sld.type = "quest_deck";
	sld = &Locations[FindLocation("Quest_Cabin_Medium")];
	sld.type = "quest_deck";
	sld = &Locations[FindLocation("Quest_Ship_deck_Medium_trade")];
	sld.type = "quest_deck";
	
	pchar.systeminfo.tutorial.OverLoad = true;
	pchar.systeminfo.tutorial.prologue_amulet = true;
	
	pchar.quest.Tutorial_Amulet.win_condition.l1 = "ItemGroup";
	pchar.quest.Tutorial_Amulet.win_condition.l1.group = ITEM_SLOT_TYPE;
	pchar.quest.Tutorial_Amulet.function = "Tutorial_Prologue_Amulet";
	
	pchar.quest.Tutorial_Talisman.win_condition.l1 = "ItemGroup";
	pchar.quest.Tutorial_Talisman.win_condition.l1.group = TALISMAN_ITEM_TYPE;
	pchar.quest.Tutorial_Talisman.function = "Tutorial_Prologue_Amulet";
	
	TEV.Tutor.PopUpLogbook = true;
	TEV.Tutor.PopUpTrading = true;
	
	DoQuestFunctionDelay("AutoSaveDelay", 4.0);
}

void SharlieTutorial_StartKino()
{
	DontRefreshBLI = false;
	StartQuestMovie(true, false, true);
	pchar.questTemp.NoFast = true;
	SetMusic("music_Quest_Deck");
	
	//TeleportCharacterToPosAy(pchar, -11.39, 4.55, 6.08, -1.50);
	locCameraFromToPos(-8.74, 6.30, 7.38, true, -14.34, 4.16, 6.56);
	//locCameraFromToPos(-14.85, 4.73, 5.82, true, -10.30, 4.52, 6.14);
	//LAi_SetStayType(pchar);
	TeleportCharacterToPos(pchar, -11.64, 4.51, 6.28);
	LAi_SetActorType(pchar);
	LAi_ActorAnimation(pchar, "tutorial_4", "", -1);
	
	DoQuestFunctionDelay("SharlieTutorial_StartKino_2", 5.0);
}

void SharlieTutorial_StartKino_2(string qName)
{
	LAi_FadeLong("", "");
	DoQuestFunctionDelay("SharlieTutorial_StartKino_3", 1.0);
}

void SharlieTutorial_StartKino_3(string qName)
{
	locCameraFromToPos(-14.85, 4.73, 5.82, true, -10.30, 4.52, 6.14);
	//LAi_FadeLong("", "");
	//DoQuestFunctionDelay("SharlieTutorial_StartKino_3", 1.0);
	//LAi_SetActorType(pchar);
	//LAi_ActorAnimation(pchar, "tutorial_4", "1", 7.2);
	
	sld = GetCharacter(NPC_GenerateCharacter("SharlieTutorial_Sailor_10", "Alonso", "man", "man", 5, FRANCE, -1, false, "pirate"));
	sld.name 	= StringFromKey("HollandGambit_23");
	sld.lastname = "";
	ChangeCharacterAddressGroup(sld, "Quest_Ship_deck_Medium_trade", "quest", "quest7");
	//TeleportCharacterToPos(sld, -11.73, 4.46, 5.60);
	TeleportCharacterToPos(sld, -11.73, 4.46, 5.58);
	LAi_SetActorType(sld);
	LAi_ActorAnimation(sld, "tutorial_3", "", -1);
	
	DoQuestFunctionDelay("SharlieTutorial_StartKino_4", 6.2);
}

void SharlieTutorial_StartKino_4(string qName)
{
	LAi_FadeLong("", "");
	DoQuestFunctionDelay("SharlieTutorial_StartKino_5", 1.0);
}

void SharlieTutorial_StartKino_5(string qName)
{
	locCameraFromToPos(-8.74, 6.30, 7.38, true, -14.34, 4.16, 6.56);
	
	LAi_SetStayType(pchar);
	/*pchar.QuestDiag = "tutorial_4";
	LAi_SetActorType(pchar);
	LAi_ActorWaitDialog(pchar, sld);
	BeginChangeCharacterActions(pchar);
	DeleteAttribute(pchar, "actions.idle");
	pchar.actions.idle.i1 = "tutorial_4";
	EndChangeCharacterActions(pchar);*/
	
	sld = CharacterFromID("SharlieTutorial_Sailor_10");
	//ChangeCharacterAddressGroup(sld, "Quest_Ship_deck_Medium_trade", "quest", "quest7");
	//TeleportCharacterToPos(sld, -11.73, 4.46, 5.60);
	sld.Dialog.Filename = "Quest\Sharlie\Tutorial.c";
	sld.Dialog.currentnode = "StartSailor";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 0, 0);
	/*BeginChangeCharacterActions(sld);
	DeleteAttribute(sld, "actions.idle");
	sld.actions.idle.i1 = "tutorial_3";
	EndChangeCharacterActions(sld);*/
}

void SharlieTutorial_StartKino_6()
{
	locCameraSleep(true);
	LAi_FadeLong("", "");
	//sld = CharacterFromID("SharlieTutorial_Sailor_10");
	//CharacterTurnByChr(sld, pchar);
	//CharacterTurnByChr(pchar, sld);
	DoQuestFunctionDelay("SharlieTutorial_StartGameInPaluba", 1.0);
}

void SharlieTutorial_ResetInterface(string qName)
{
	StartBattleLandInterface();
}

void SharlieTutorial_PrinestiRum()
{
	AddQuestRecord("SharlieTutorial", "1");
	sld = CharacterFromID("SharlieTutorial_Sailor_4");
	AddLandQuestMark(sld, "questmarkquestion");
}

void SharlieTutorial_PrinestiRumFinal()
{
	AddQuestRecord("SharlieTutorial", "2");
	sld = CharacterFromID("SharlieTutorial_Sailor_4");
	sld.Dialog.Filename = "Quest\Sharlie\Tutorial.c";
	sld.dialog.currentnode = "SailorWantRum_PrinestiRum";
	DelLandQuestMark(sld);
	pchar.SharlieTutorial.FullyCompleted = sti(pchar.SharlieTutorial.FullyCompleted) + 1;
}

void SharlieTutorial_SailorNeedBoxOfBalls()
{
	AddQuestRecord("SharlieTutorial", "3");
	sld = CharacterFromID("SharlieTutorial_Sailor_8");
	AddLandQuestMark(sld, "questmarkquestion");
}

void SharlieTutorial_SailorNeedBoxOfBallsFinal()
{
	AddQuestRecord("SharlieTutorial", "4");
	sld = CharacterFromID("SharlieTutorial_Sailor_8");
	DelLandQuestMark(sld);
	pchar.SharlieTutorial.FullyCompleted = sti(pchar.SharlieTutorial.FullyCompleted) + 1;
}

void SharlieTutorial_QuestRazdatZoloto()
{
	pchar.questTemp.SharlieTutorial_KaznacheyQuestActive = true;
	
	sld = CharacterFromID("SharlieTutorial_Officer_3");
	sld.Dialog.Filename = "Quest\Sharlie\Tutorial.c";
	sld.Dialog.currentnode = "OfficerKaznachey_12_Wait";
	AddLandQuestMark(sld, "questmarkquestion");
	
	sld = CharacterFromID("SharlieTutorial_Sailor_4");
	AddLandQuestMark(sld, "questmarkgen");
	
	sld = CharacterFromID("SharlieTutorial_Sailor_8");
	AddLandQuestMark(sld, "questmarkgen");
	
	sld = CharacterFromID("SharlieTutorial_Sailor_10");
	AddLandQuestMark(sld, "questmarkgen");
	
	if(bGlobalTutor)
	{
		TW_InitLand_Craft_1_Inventory();
		TW_Open("land_craft");
	}
}

void SharlieTutorial_journal(string qName)
{
	TakeItemFromCharacter(pchar, "Tutorial_journal");
	AddQuestRecordInfo("SharlieTutorial_Journal", "1");
}

void SharlieTutorial_OldSailorKey()
{
	sld = CharacterFromID("SharlieTutorial_Sailor_7");
	LAi_CharacterDisableDialog(sld);
	
	// прячем ключ
	switch (rand(2))
	{
		case 0: 
			SetItemInLocation("Tutorial_key", "Quest_Cabin_Medium", "item2") 
			Log_TestInfo("Ключ в каюте капитана");
		break;
		case 1:
			SetItemInLocation("Tutorial_key", "Quest_Ship_deck_Medium_trade", "item1") 
			Log_TestInfo("Ключ на верхней палубе");
		break;
		case 2:
			SetItemInLocation("Tutorial_key", "Quest_Deck_Medium", "item2") 
			Log_TestInfo("Ключ на орудийной палубе");
		break;
	}
	
	PChar.quest.SharlieTutorial_FoundTheKey.win_condition.l1 = "item";
	PChar.quest.SharlieTutorial_FoundTheKey.win_condition.l1.item = "Tutorial_key";
	PChar.quest.SharlieTutorial_FoundTheKey.function = "SharlieTutorial_FoundTheKey";
}

void SharlieTutorial_FoundTheKey(string qName)
{
	pchar.SharlieTutorial.FullyCompleted = sti(pchar.SharlieTutorial.FullyCompleted) + 1;
}

void SharlieTutorial_Trevoga()
{
	TW_Release();
	StartQuestMovie(true, false, true);
	pchar.questTemp.NoFast = true;
	LAi_SetStayType(pchar);
	locCameraFlyToPositionLookToPoint(-16.28, 4.59, -30.48, -11.40, 16.56, 2.02, -4.80, 32.74, 45.99, -1, 5000/GetDeltaTime());
	Pchar.FuncCameraFly = "SharlieTutorial_Trevoga_2";
	sld = CharacterFromID("SharlieTutorial_Sailor_3");
	ChangeCharacterAddressGroup(sld, "Quest_Ship_deck_Medium_trade", "quest", "quest9");
	DelLandQuestMark(sld);
}

void SharlieTutorial_Trevoga_2()
{
	locCameraResetState();
	locCameraFromToPos(-14.10, 20.49, 12.63, true, -7.60, 18.33, 11.55);
	sld = CharacterFromID("SharlieTutorial_Sailor_3");
	LAi_SetActorType(sld);
	LAi_ActorAnimation(sld, "tutorial_2", "1", 20.0);
	DelLandQuestMark(sld);
	DoQuestFunctionDelay("SharlieTutorial_Trevoga_3", 6.5);
}

void SharlieTutorial_Trevoga_3(string qName)
{
	PlaySound("PEOPLE\whistling.wav");
	PlaySound("PEOPLE\whistling.wav");
	DoQuestFunctionDelay("SharlieTutorial_Trevoga_4", 1.0);
}

void SharlieTutorial_Trevoga_4(string qName)
{
	DoQuestFunctionDelay("SharlieTutorial_Trevoga_5", 0.5);
}

void SharlieTutorial_Trevoga_5(string qName)
{
	LAi_FadeLong("", "");
	DoQuestFunctionDelay("SharlieTutorial_Trevoga_6", 1.0);
}

void SharlieTutorial_Trevoga_6(string qName)
{
	locCameraFollowEx(true);
	sld = CharacterFromID("SharlieTutorial_Sailor_10");
	TeleportCharacterToPosAy(sld, -9.69, 7.93, -21.64, 1.50);
	sld.Dialog.Filename = "Quest\Sharlie\Tutorial.c";
	sld.Dialog.currentnode = "Sailor_Trevoga";
	LAi_CharacterEnableDialog(sld);
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 0, 0);
}

void SharlieTutorial_Trevoga_7()
{
	EndQuestMovie();
	DeleteAttribute(pchar, "questTemp.NoFast");
	locCameraSleep(false);
	SharlieTutorial_TrumLoad();
}

void SharlieTutorial_TrumLoad()
{
	sld = CharacterFromID("SharlieTutorial_Sailor_7");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	DoFunctionReloadToLocation("Quest_Deck", "rld", "loc0", "SharlieTutorial_TrumLoad_2");
}

void SharlieTutorial_TrumLoad_2()
{
	ChangeShowIntarface();
	LAi_SetStayType(pchar);
	pchar.questTemp.SharlieTutorial_TrumDialogSamSoboi_1 = true;
	DoQuestCheckDelay("TalkSelf_Quest", 2.0);
}

void SharlieTutorial_TrumLoad_3()
{
	LAi_SetStayType(pchar);
	if (CheckAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuestActive"))
	{
		sld = CharacterFromID("SharlieTutorial_Officer_3");
		LAi_CharacterEnableDialog(sld);
		sld.Dialog.Filename = "Quest\Sharlie\Tutorial.c";
		sld.Dialog.currentnode = "OfficerKaznachey_16_Proval";
		ChangeCharacterAddressGroup(sld, "Quest_Deck", "reload", "reload_gundeck2");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		DelLandQuestMark(sld);
	}
	else
	{
		DoQuestFunctionDelay("SharlieTutorial_TrumLoad_5", 2.0);
	}
}

void SharlieTutorial_TrumLoad_4()
{
	sld = CharacterFromID("SharlieTutorial_Officer_3");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "reload", "reload_gundeck1", "", -1);
	DoQuestFunctionDelay("SharlieTutorial_TrumLoad_5", 2.0);
}

void SharlieTutorial_TrumLoad_5(string qName)
{
	PlaySound("Sea Battles\cannon_24_01.wav");
	//PlaySound("Sea Battles\cannon_24_01.wav");
	DoQuestFunctionDelay("SharlieTutorial_StartShip", 2.0);
}

void SharlieTutorial_StartShip(string qName)//начинается морское стартовое сражение на Пинасе
{	
	// Корабль
	pchar.Ship.Type = GenerateShipExt(SHIP_PINNACE, true, pchar);
	pchar.Ship.name = StringFromKey("SharlieTutorial_6");
	SetBaseShipData(pchar);
	RealShips[sti(pchar.Ship.Type)].ship.upgrades.hull = 2;
	SetShipSailsFromFile(pchar, "ships/parus_silk.tga");
	realships[sti(pchar.ship.type)].SpeedRate = 15.5;
	realships[sti(pchar.ship.type)].TurnRate = 52.5;
	realships[sti(pchar.ship.type)].WaterLine = 1.3;
	realships[sti(pchar.ship.type)].Capacity = 6500;
	realships[sti(pchar.ship.type)].WindAgainstSpeed = 1.1;
	pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS32;
	SetCrewQuantityFull(pchar);
	pchar.ship.Crew.Morale = 100;
	ChangeCrewExp(pchar, "Sailors", 100);
	ChangeCrewExp(pchar, "Cannoners", 100);
	ChangeCrewExp(pchar, "Soldiers", 100);
	SetCharacterGoods(pchar, GOOD_BALLS, 0);
	SetCharacterGoods(pchar, GOOD_GRAPES, 0);
	SetCharacterGoods(pchar, GOOD_KNIPPELS, 0);
	SetCharacterGoods(pchar, GOOD_WEAPON, 0);
	SetCharacterGoods(pchar, GOOD_BOMBS, 2000);
	SetCharacterGoods(pchar, GOOD_POWDER, 2000);
	Ship_ChangeCharge(pchar, GOOD_BOMBS);
	pchar.GenQuest.MaxSailing = true;
	bDisableCharacterMenu = true;
	InterfaceStates.Buttons.Save.enable = false;
	QuestToSeaLogin_Launch();
	DoQuestFunctionDelay("SharlieTutorial_StartShip_2", 1.5);
	DoQuestFunctionDelay("SharlieTutorial_StartShip_3", 3.0);
	DoQuestFunctionDelay("SharlieTutorial_StartShip_4", 4.5);
	DoQuestFunctionDelay("SharlieTutorial_StartShip_5", 6.0);
	
	// Очищаем палубу и возвращаем её в исходное состояние
	for (i=1; i<=11; i++)
	{
		if (CharacterIsAlive("SharlieTutorial_Sailor_"+i))
		{
			sld = CharacterFromID("SharlieTutorial_Sailor_"+i);
			sld.lifeday = 0;
		}
	}
	for (i=1; i<=2; i++)
	{
		if (CharacterIsAlive("SharlieTutorial_Officer_"+i))
		{
			sld = CharacterFromID("SharlieTutorial_Officer_"+i);
			sld.lifeday = 0;
		}
	}
	if (CharacterIsAlive("SharlieTutorial_Captain"))
	{
		sld = CharacterFromID("SharlieTutorial_Captain");
		sld.lifeday = 0;
	}
	sld = CharacterFromID("SharlieTutorial_Officer_3");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	
	CloseQuestHeader("SharlieTutorial");
	DeleteQuestCondition("SharlieTutorial_journal");
	DeleteQuestCondition("SharlieTutorial_SailorCleansFloors");
	sld = ItemsFromID("tutorial_key");
	sld.shown = false;
	sld = ItemsFromID("map_full");
	sld.price = 0;
	sld = &Locations[FindLocation("Quest_Ship_deck_Medium_trade")];
	sld.reload.l1.disable = true;
	sld.reload.l2.disable = true;
	QuestPointerDelLoc("Quest_Deck_Medium", "reload", "reload_deck");
}

void SharlieTutorial_StartShip_2(string qName)
{
	// evganat - туториал
	if(bGlobalTutor)
	{
		bCanSwitchCameras = false;
		LaunchTutorial("Prologue_AutoFire", 1);
	}
}

void SharlieTutorial_StartShip_3(string qName)
{
	LAi_FadeToBlackStart();
}

void SharlieTutorial_StartShip_4(string qName)
{
	LAi_SetImmortal(pchar, true);
	//pchar.HullDamageTutorial = true;
	bCannonsRangeShow = true;
	SendMessage(&AISea, "lllllffl", AI_MESSAGE_CANNONS_RANGE, argb(0,255,255,255), argb(25,255,255,255), argb(0,255,0,0), argb(75,255,0,0), 0.002, 0.002, bCannonsRangeShow);
	// вражеский флот -->
	Group_FindOrCreateGroup("SharlieTutorial_SeaAttack");
	Group_SetType("SharlieTutorial_SeaAttack", "war");
	
	// корабль 1
	sld = GetCharacter(NPC_GenerateCharacter("EnemyCaptainStart_1", "mercen_"+(rand(14)+14), "man", "man", 1, PIRATE, -1, true, "quest"));
	FantomMakeSmallSailor(sld, SHIP_SHNYAVA, "", CANNON_TYPE_CANNON_LBS3, 5, 5, 5, 5, 5);
	realships[sti(sld.ship.type)].SpeedRate = realships[sti(sld.ship.type)].SpeedRate - 2.5;
	Character_SetAbordageEnable(sld, false);
	sld.SeaBoss = -3.0; 
	SetSailsColor(sld, 8);
	Group_AddCharacter("SharlieTutorial_SeaAttack", "EnemyCaptainStart_1");
	// корабль 2
	sld = GetCharacter(NPC_GenerateCharacter("EnemyCaptainStart_2", "mercen_"+(rand(14)+14), "man", "man", 1, PIRATE, -1, true, "quest"));
	FantomMakeSmallSailor(sld, SHIP_BRIG, "", CANNON_TYPE_CANNON_LBS3, 5, 5, 5, 5, 5);
	realships[sti(sld.ship.type)].SpeedRate = realships[sti(sld.ship.type)].SpeedRate - 2.5;
	Character_SetAbordageEnable(sld, false);
	sld.SeaBoss = -3.0; 
	SetSailsColor(sld, 8);
	Group_AddCharacter("SharlieTutorial_SeaAttack", "EnemyCaptainStart_2");
	// корабль 3
    sld = GetCharacter(NPC_GenerateCharacter("EnemyCaptainStart_3", "mercen_"+(rand(14)+14), "man", "man", 1, PIRATE, -1, true, "quest"));
	FantomMakeSmallSailor(sld, SHIP_BRIG, "", CANNON_TYPE_CANNON_LBS3, 5, 5, 5, 5, 5);
	realships[sti(sld.ship.type)].SpeedRate = realships[sti(sld.ship.type)].SpeedRate - 2.5;
	Character_SetAbordageEnable(sld, false);
	sld.SeaBoss = -3.0;
	SetSailsColor(sld, 8);
	Group_AddCharacter("SharlieTutorial_SeaAttack", "EnemyCaptainStart_3");
	// корабль 4
	sld = GetCharacter(NPC_GenerateCharacter("EnemyCaptainStart_4", "mercen_"+(rand(14)+14), "man", "man", 1, PIRATE, -1, true, "quest"));
	FantomMakeSmallSailor(sld, SHIP_GALEON_L, "", CANNON_TYPE_CANNON_LBS16, 5, 5, 5, 5, 5);
	realships[sti(sld.ship.type)].SpeedRate = realships[sti(sld.ship.type)].SpeedRate - 2.5;
	Character_SetAbordageEnable(sld, false);
	sld.SeaBoss = -3.0;
	SetSailsColor(sld, 8);
	Group_AddCharacter("SharlieTutorial_SeaAttack", "EnemyCaptainStart_4");
	// корабль 5
	sld = GetCharacter(NPC_GenerateCharacter("EnemyCaptainStart_5", "mercen_"+(rand(14)+14), "man", "man", 1, PIRATE, -1, true, "quest"));
	FantomMakeSmallSailor(sld, SHIP_SCHOONER, "", CANNON_TYPE_CANNON_LBS3, 5, 5, 5, 5, 5);
	realships[sti(sld.ship.type)].SpeedRate = realships[sti(sld.ship.type)].SpeedRate - 2.5;
	Character_SetAbordageEnable(sld, false);
	sld.SeaBoss = -3.0;
	SetSailsColor(sld, 8);
	Group_AddCharacter("SharlieTutorial_SeaAttack", "EnemyCaptainStart_5");
		
	Group_SetGroupCommander("SharlieTutorial_SeaAttack", "EnemyCaptainStart_1");
	Group_SetAddress("SharlieTutorial_SeaAttack", "Cuba2", "", "");
	Group_SetTaskAttack("SharlieTutorial_SeaAttack", PLAYER_GROUP);
	Group_LockTask("SharlieTutorial_SeaAttack");
	SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);
	
	Sea_LoginGroupCurrentSeaEx("SharlieTutorial_SeaAttack", 150.0, 0);
	//log_info("Враг на горизонте!");
	PlaySound("interface\" + LanguageGetLanguage() + "\_EvEnemy1.wav");
	// вражеский флот <--
	PChar.quest.SharlieTutorial_AttackDead.win_condition.l1 = "Group_Death";
	PChar.quest.SharlieTutorial_AttackDead.win_condition.l1.group = "SharlieTutorial_SeaAttack";
	PChar.quest.SharlieTutorial_AttackDead.function = "SharlieTutorial_AttackDead";
}

void SharlieTutorial_StartShip_5(string qName)
{
	LAi_FadeToBlackEnd();
	TW_InitSea_Battle_1_AutoFire();
	TW_Open("sea_battle");
}

void SharlieTutorial_AttackDead(string qName)
{
	DoQuestCheckDelay("sea_victory_2", 1.2);
	PlaySound("interface\abordage_wining.wav");
	DoQuestFunctionDelay("SharlieTutorial_ActivateButtonInTheSea_2", 12.0);
}

void SharlieTutorial_ActThree()
{
	// убираем корабль и запреты
	pchar.Ship.Type = SHIP_NOTUSED;
	DeleteAttribute(pchar, "GenQuest.MaxSailing");
	bDisableCharacterMenu = false;
	InterfaceStates.Buttons.Save.enable = true;
	chrDisableReloadToLocation = true;
	LAi_SetImmortal(pchar, false);
	//DeleteAttribute(pchar, "HullDamageTutorial");
	DeleteAttribute(pchar, "TutorialToDeck_2");
	sld = &locations[FindLocation("Quest_Deck")];
	sld.private4.items.BoxOfBalls = 0;
	QuestPointerDelLoc("Quest_Deck", "box", "private4");
	sld = ItemsFromID("quest_potion");
	sld.name = "itmname_Suspicious_Potion";
	sld.describe = "itmdescr_Suspicious_Potion";
	
	//меняем музыку на боевую
	SetMusic("music_abordage");
	sld = &Locations[FindLocation("Quest_Deck_Medium")];
	sld.boarding = "false";	// даём возможность офицеру находиться здесь
	sld.type = "boarding_cabine";
	sld = &Locations[FindLocation("Quest_Campus")];
	sld.type = "boarding_cabine";
	sld = &Locations[FindLocation("Quest_Deck")];
	sld.type = "boarding_cabine";
	sld = &Locations[FindLocation("Quest_Cabin_Medium")];
	sld.type = "boarding_cabine";
	sld = &Locations[FindLocation("Quest_Ship_deck_Medium_trade")];
	sld.type = "boarding_cabine";
	
	LAi_SetPlayerType(pchar);
	
	sld = GetCharacter(NPC_GenerateCharacter("SharlieTutorial_EnemyPirate_0", "citiz_48", "man", "man", 1, PIRATE, -1, false, "pirate"));
	sld.name 	= StringFromKey("SharlieTutorial_5");
	sld.lastname = "";
	sld.Dialog.Filename = "Quest\Sharlie\Tutorial.c";
	sld.Dialog.currentnode = "EnemyPirate_1";
	LAi_SetHP(sld, 25.0, 25.0);
	GiveItem2Character(sld, "blade_05");
	EquipCharacterByItem(sld, "blade_05");
	AddMoneyToCharacter(sld, 20);
	GiveItem2Character(sld, "Mineral8");
	ChangeCharacterAddressGroup(sld, "quest_deck", "rld", "aloc0");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 0, 0);
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	sld.CantLootBlade = true;
}

void SharlieTutorial_TrumBitva_2()
{
	LAi_LocationFightDisable(loadedLocation, false);
	LAi_SetFightMode(pchar, true);
	LAi_SetCheckMinHP(pchar, 1, true, "SkritoeBessmertie");
	
	sld = CharacterFromID("SharlieTutorial_EnemyPirate_0");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
	LAi_group_SetCheckFunction("EnemyFight", "SharlieTutorial_TrumBitva_3");
	
	// evganat - туториал
	if(bGlobalTutor)
    {
		SetDummy(sld, true);
		TEV.Tutor.BackControlsTips = iControlsTips;
		iControlsTips = 0;
        TW_InitLand_Fight_1_Attack();
        TW_Open("land_fight");
	}
}

void SharlieTutorial_TrumBitva_3(string qName)
{
	DoQuestFunctionDelay("SharlieTutorial_TrumBitva_3_1", 1.5);
}

void SharlieTutorial_TrumBitva_3_1(string qName)
{
	if(bGlobalTutor)
	{
		objTask.land_fight = "";
		PostEvent("TW_Release", 2000);
	}
	chrDisableReloadToLocation = false;
	LAi_RemoveCheckMinHP(pchar);
	sld = &Locations[FindLocation("Quest_Deck_Medium")];
	sld.locators_radius.item.item1 = 0.5;
	sld.locators_radius.item.item2 = 0.5;
	SetFunctionLocationCondition("SharlieTutorial_TrumBitva_4", "Quest_Deck_Medium", false);
	QuestPointerToLoc("Quest_Deck", "reload", "reload_gundeck1");
	AutoSave();
}

void SharlieTutorial_TrumBitva_4(string qName)
{
	chrDisableReloadToLocation = true;
	InterfaceStates.Buttons.Save.enable = false;
	QuestPointerDelLoc("Quest_Deck", "reload", "reload_gundeck1");
	LAi_SetCheckMinHP(pchar, 1, true, "SharlieTutorial_Ranen");
	for (i=1; i<=8; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("SharlieTutorial_DeadSailor_"+i, "citiz_3"+i, "man", "man_dead", 1, FRANCE, 0, true, "pirate"));
		ChangeCharacterAddressGroup(sld, "Quest_Deck_Medium", "rld", "loc"+i);
		if(i==7) ChangeCharacterAddressGroup(sld, "Quest_Deck_Medium", "goto", "goto1");
		if(i==8) ChangeCharacterAddressGroup(sld, "Quest_Deck_Medium", "goto", "goto6");
		//TeleportCharacterToPosAy(sld, 10.31, 2.87, 34.36, 1.50);
		sld.DontClearDead = true;
		sld.CantLoot = true;
		sld.DeadWithBlade = true;
		LAi_SetFightMode(sld, true);
		LAi_KillCharacter(sld);
	}
	
	sld = CharacterFromID("SharlieTutorial_Officer_3");
	LAi_SetActorType(sld);
	sld.model.animation = "man_dead";
	Characters_RefreshModel(sld);
	DelLandQuestMark(sld);
	ChangeCharacterAddressGroup(sld, "Quest_Deck_Medium", "rld", "loc0");
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	RemoveAllCharacterItems(sld, true);
	GiveItem2Character(sld, "Mineral21");
	GiveItem2Character(sld, "chest_open");
	
	sld = GetCharacter(NPC_GenerateCharacter("SharlieTutorial_Alonso", "Alonso", "man", "man", 1, FRANCE, 0, true, "pirate"));	// раненый Алонсо
	sld.name 	= StringFromKey("HollandGambit_23");
	sld.lastname = "";
	sld.Dialog.Filename = "Quest\Sharlie\Tutorial.c";
	sld.Dialog.currentnode = "SailorAlive_1";
	LAi_SetHP(sld, 50.0, 50.0);
	LAi_SetCheckMinHP(sld, 10, true, "SharlieTutorial_AlonsoSkritoeBessmertie");
	ChangeCharacterAddressGroup(sld, "Quest_Deck_Medium", "goto", "goto5");
	//TeleportCharacterToPosAy(sld, -5.80, 14.32, 1.53, 1.50);
	TeleportCharacterToPosAy(sld, 2.98, 4.04, -1.92, -1.50);
	LAi_SetGroundSitType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
	AddLandQuestMark(sld, "questmarkmain");
	sld.Unpushable = "";
	
	/*CreateLocationParticles("large_smoke", "reload", "reload_hold3", 0, 0, 0, "");
	CreateLocationParticles("shipfire", "reload", "reload_hold3", 0, 0, 0, "fortfire");
	CreateLocationParticles("large_smoke", "reload", "reload_hold2", 0, 0, 0, "");
	CreateLocationParticles("shipfire", "reload", "reload_hold2", 0, 0, 0, "fortfire");*/
	
	DoQuestFunctionDelay("SharlieTutorial_TrumBitva_4_1", 0.1);	// убиваем казначея с задержкой, а то его облутать нельзя
}

void SharlieTutorial_TrumBitva_4_1(string qName)
{
	sld = CharacterFromID("SharlieTutorial_Officer_3");
	LAi_KillCharacter(sld);
}

void SharlieTutorial_TrumBitva_5()
{
	LAi_LocationFightDisable(loadedLocation, false);
	LAi_SetFightMode(pchar, true);
	for (i=1; i<=3; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("SharlieTutorial_EnemyPirate_"+i, "citiz_4"+i, "man", "man", 1, PIRATE, 0, true, "pirate"));
		ChangeCharacterAddressGroup(sld, "Quest_Deck_Medium", "reload", "reload_camp");
		if(i==1)
		{
			GiveItem2Character(sld, "quest_potion");
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			sld.CantLootBlade = true;
			sld.DeathQuestmark = true;
			/* pchar.quest.SharlieTutorial_TrumBitva_5_1.win_condition.l1 = "NPC_Death";
			pchar.quest.SharlieTutorial_TrumBitva_5_1.win_condition.l1.character = sld.id;
			pchar.quest.SharlieTutorial_TrumBitva_5_1.win_condition = "SharlieTutorial_TrumBitva_5_1"; */
			//LAi_SetCheckMinHP(sld, 1, true, "SharlieTutorial_TrumBitva_5_1");
		}
		LAi_SetHP(sld, 10.0, 10.0);
		sld.MultiFighter = 0.3;
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		LAi_group_SetCheckFunction("EnemyFight", "SharlieTutorial_TrumBitva_6");
	}
	
	TEV.Tutor.Loot.Pirate2 = 1;
	TEV.Tutor.Loot.Pirate3 = 1;
	
	sld = CharacterFromID("SharlieTutorial_Alonso");
	LAi_SetActorType(sld);
	LAi_ActorSetGroundSitMode(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
	
	LaunchTutorial("Prologue_Marksmanship", 1);
}

void SharlieTutorial_TrumBitva_6(string qName)
{
	DoQuestCheckDelay("hide_weapon", 1.2);
	LAi_LocationFightDisable(loadedLocation, true);
	sld = CharacterFromID("SharlieTutorial_Alonso");
	sld.loyality = MAX_LOYALITY;
	sld.Dialog.Filename = "Quest\Sharlie\Tutorial.c";
	sld.Dialog.currentnode = "SailorAlive_11";
	LAi_SetGroundSitType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
	PChar.quest.SharlieTutorial_TrumBitva_6_1.win_condition.l1 = "item";
	PChar.quest.SharlieTutorial_TrumBitva_6_1.win_condition.l1.item = "quest_potion";
	PChar.quest.SharlieTutorial_TrumBitva_6_1.function = "SharlieTutorial_TrumBitva_6_1";
	DoQuestFunctionDelay("Tutorial_DeadSearch", 1.5);
}

void SharlieTutorial_TrumBitva_6_1(string qName)
{
	sld = CharacterFromID("SharlieTutorial_Alonso");
	AddLandQuestMark(sld, "questmarkmain");
}

/*void SharlieTutorial_TrumBitva_7() // здесь нужен туториал на назначение офицера в абордажники
{
	sld = CharacterFromID("SharlieTutorial_Alonso");
	sld.Dialog.Filename = "Quest\Sharlie\Tutorial.c";
	sld.Dialog.currentnode = "SailorAlive_13";
	//LAi_SetCheckMinHP(sld, 1, true, "");
	AddPassenger(pchar, sld, false);
	SetCharacterRemovable(sld, true);
	LAi_SetOfficerType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	//LaunchTutorial("Fighter", 1);
}*/

void SharlieTutorial_TrumBitva_8()
{
	TW_Release();
	LAi_GunSetChargeQuant(pchar, GUN_ITEM_TYPE, 1);
	DoQuestFunctionDelay("SharlieTutorial_TrumBitva_8_1", 2.5);
}

void SharlieTutorial_TrumBitva_8_1(string qName)
{
	SetMusic("music_abordage");
	PlaySound("interface\abordage_wining.wav");
	PlaySound("Sea Battles\popadan_bomb_002.wav");
	LAi_LocationFightDisable(loadedLocation, false);
	LAi_SetFightMode(pchar, true);
	sld = CharacterFromID("SharlieTutorial_Alonso");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	for (i=4; i<=6; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("SharlieTutorial_EnemyPirate_"+i, "citiz_4"+(rand(8)+1), "man", "man", 1, PIRATE, 0, true, "pirate"));
		ChangeCharacterAddressGroup(sld, "Quest_Deck_Medium", "reload", "reload_camp");
		LAi_SetHP(sld, 20.0, 20.0);
		sld.lifeday = 0;
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		LAi_group_SetCheckFunction("EnemyFight", "SharlieTutorial_TrumBitva_9");
	}
}

void SharlieTutorial_TrumBitva_9(string qName)
{
	DoQuestFunctionDelay("SharlieTutorial_TrumBitva_9_1", 1.5);
}

void SharlieTutorial_TrumBitva_9_1(string qName)
{
	/*for (i=1; i<=2; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("SharlieTutorial_AllySailor_"+i, "citiz_3"+i, "man", "man", 1, FRANCE, 0, true, "pirate"));
		ChangeCharacterAddressGroup(sld, "Quest_Deck_Medium", "reload", "reload_camp");
		GiveItem2Character(sld, "pistol1");
		EquipCharacterByItem(sld, "pistol1");
		AddItems(sld, "bullet", 1);
		AddItems(sld, "GunPowder", 1);
		LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
		LAi_GunSetChargeQuant(sld, GUN_ITEM_TYPE, 1);
		LAi_SetHP(sld, 10.0, 10.0);
		LAi_CharacterDisableDialog(sld);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}*/
	sld = GetCharacter(NPC_GenerateCharacter("SharlieTutorial_AllySailor_1", "citiz_31", "man", "man", 1, FRANCE, 0, true, "pirate"));
	ChangeCharacterAddressGroup(sld, "Quest_Deck_Medium", "reload", "reload_camp");
	GiveItem2Character(sld, "pistol1");
	EquipCharacterByItem(sld, "pistol1");
	AddItems(sld, "bullet", 1);
	AddItems(sld, "GunPowder", 1);
	LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
	LAi_GunSetChargeQuant(sld, GUN_ITEM_TYPE, 1);
	LAi_SetHP(sld, 10.0, 10.0);
	LAi_CharacterDisableDialog(sld);
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	
	for (i=7; i<=10; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("SharlieTutorial_EnemyPirate_"+i, "citiz_4"+(rand(8)+1), "man", "man", 1, PIRATE, 0, true, "pirate"));
		ChangeCharacterAddressGroup(sld, "Quest_Deck_Medium", "reload", "reload_hold1");
		LAi_SetHP(sld, 20.0, 20.0);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
	LAi_group_SetCheckFunction("EnemyFight", "SharlieTutorial_TrumBitva_10");
}

void SharlieTutorial_TrumBitva_10(string qName)
{
	DoQuestFunctionDelay("SharlieTutorial_TrumBitva_10_1", 1.5);
}

void SharlieTutorial_TrumBitva_10_1(string qName)
{
	for (i=3; i<=4; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("SharlieTutorial_AllySailor_"+i, "citiz_3"+i, "man", "man", 1, FRANCE, 0, true, "pirate"));
		ChangeCharacterAddressGroup(sld, "Quest_Deck_Medium", "reload", "reload_hold1");
		LAi_SetHP(sld, 25.0, 25.0);
		LAi_CharacterDisableDialog(sld);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	
	for (i=11; i<=15; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("SharlieTutorial_EnemyPirate_"+i, "citiz_4"+(rand(8)+1), "man", "man", 1, PIRATE, 0, true, "pirate"));
		ChangeCharacterAddressGroup(sld, "Quest_Deck_Medium", "reload", "reload_camp");
		LAi_SetHP(sld, 40.0, 40.0);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
	LAi_group_SetCheckFunction("EnemyFight", "SharlieTutorial_TrumBitva_11");
}

void SharlieTutorial_TrumBitva_11(string qName)
{
	chrDisableReloadToLocation = false;
	LocatorReloadEnterDisable("Quest_Deck_Medium", "reload_camp", true);
	LocatorReloadEnterDisable("Quest_Deck_Medium", "reload_hold1", true);
	sld = &Locations[FindLocation("Quest_Deck_Medium")];
	sld.type = "quest_deck";
	sld = &Locations[FindLocation("Quest_Campus")];
	sld.type = "quest_deck";
	sld = &Locations[FindLocation("Quest_Deck")];
	sld.type = "quest_deck";
	sld = &Locations[FindLocation("Quest_Cabin_Medium")];
	sld.type = "quest_deck";
	sld = &Locations[FindLocation("Quest_Ship_deck_Medium_trade")];
	sld.type = "quest_deck";
	SetMusicOnce("music_ship_victory2");
	PlaySound("interface\abordage_wining.wav");
	SetFunctionLocationCondition("SharlieTutorial_PobedaPaluba", "Quest_Ship_deck_Medium_trade", false);
	QuestPointerToLoc("Quest_Deck_Medium", "reload", "reload_deck");
}

void SharlieTutorial_PobedaPaluba_NoParam()
{
    SharlieTutorial_PobedaPaluba("");
}

void SharlieTutorial_PobedaPaluba(string qName)
{
	worldMap.date.month = 9;
	worldMap.date.day   = 24;
	Environment.date.month = 9;
	Environment.date.day = 24;
	SetCurrentTime(14, 00);
	CreateWeatherEnvironment();
	
	ChangeCharacterAddressGroup(pchar, "Quest_Ship_deck_Medium_trade", "quest", "quest6");
	TeleportCharacterToPos(pchar, -11.64, 4.51, 6.28);
	chrDisableReloadToLocation = true;
	QuestPointerDelLoc("Quest_Deck_Medium", "reload", "reload_cabin");
	DoQuestFunctionDelay("SharlieTutorial_PobedaPaluba_2", 0.1);
	LAi_SetStayType(pchar);
	LAi_SetCurHPMax(pchar);
	LAi_GetCharacterMaxEnergy(pchar);
	LAi_RemoveCheckMinHP(pchar);
	LAi_SetImmortal(pchar, false);
	
	sld = CharacterFromID("SharlieTutorial_Alonso");
	LAi_CharacterEnableDialog(sld);
	sld.Dialog.Filename = "Quest\Sharlie\Tutorial.c";
	sld.Dialog.currentnode = "AfterBattle_Alonso_1";
	ChangeCharacterAddressGroup(sld, "Quest_Ship_deck_Medium_trade", "quest", "quest7");
	TeleportCharacterToPos(sld, -11.73, 4.46, 5.58);
	//RemovePassenger(pchar, sld);
	sld.lifeday = 0;
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 0, 0);
	
	// очищаем
	sld = &Locations[FindLocation("Quest_Ship_deck_Medium_trade")];
	DelLocatorEvent(sld.id, "event1");
	DelLocatorEvent(sld.id, "event3");
	LocatorReloadEnterDisable("Quest_Deck_Medium", "reload_camp", false);
	LocatorReloadEnterDisable("Quest_Deck_Medium", "reload_hold1", false);
	QuestPointerDelLoc("Quest_Deck_Medium", "reload", "reload_deck");
	// Расставляем людей
	/*sld = CharacterFromID("SharlieTutorial_Captain");
	sld.lifeday = 0;
	sld.Dialog.Filename = "Quest\Sharlie\Tutorial.c";
	sld.dialog.currentnode = "CaptainFinal_1";
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, "Quest_Ship_deck_Medium_trade", "quest", "quest2");
	TeleportCharacterToPosAy(sld, -8.66, 2.56, 2.84, 3.00);
	DeleteAttribute(sld, "watchglass");
	LAi_SetStayType(sld);
	//DelLandQuestMark(sld);
	AddLandQuestMark(sld, "questmarkmain");
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	//DoQuestFunctionDelay("SharlieTutorial_ShootingTraining_1", 1.5);
	
	sld = GetCharacter(NPC_GenerateCharacter("SharlieTutorial_prisoner", "panhandler_1", "man", "man", 5, PIRATE, 0, false, "pirate"));
	ChangeCharacterAddressGroup(sld, "Quest_Ship_deck_Medium_trade", "reload", "reload4");
	TeleportCharacterToPosAy(sld, -8.56, 2.80, -5.05, 0.0);
	LAi_SetActorType(sld);
	LAi_CharacterDisableDialog(sld);
	LAi_SetHP(sld, 1.0, 1.0);
	
	for (i=1; i<=8; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("SharlieTutorial_DeadSailor_"+i, "citiz_3"+i, "man", "man_dead", 1, FRANCE, 0, true, "pirate"));
		ChangeCharacterAddressGroup(sld, "Quest_Ship_deck_Medium_trade", "goto", "goto"+i);
		if(i==4) TeleportCharacterToPosAy(sld, -8.06, 2.45, 0.98, 1.40);
		if(i==5) TeleportCharacterToPosAy(sld, -8.16, 2.51, -2.03, 2.80);
		if(i==6) TeleportCharacterToPosAy(sld, -9.40, 2.48, 1.68, 0.10);
		if(i==8) TeleportCharacterToPosAy(sld, -7.03, 4.87, 8.82, 0.30);
		sld.DontClearDead = true;
		sld.CantLoot = true;
		sld.DeadWithBlade = true;
		LAi_SetFightMode(sld, true);
		LAi_KillCharacter(sld);
	}
	
	for (i=1; i<=8; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("SharlieTutorial_Sailor_"+i, "citiz_3"+i, "man", "man", 5, FRANCE, 0, false, "pirate"));
		ChangeCharacterAddressGroup(sld, "Quest_Ship_deck_Medium_trade", "reload", "reload3");
		LAi_SetStayType(sld);
		LAi_CharacterDisableDialog(sld);
		LAi_SetImmortal(sld, true);	
		LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
		if (i==1) TeleportCharacterToPosAy(sld, -10.60, 2.69, -6.30, 0.50);
		if (i==2) TeleportCharacterToPosAy(sld, -6.61, 2.69, -6.20, -0.50);
		if (i==3) TeleportCharacterToPosAy(sld, -6.63, 2.56, -2.00, -1.50);
		if (i==4) TeleportCharacterToPosAy(sld, -6.63, 2.56, -0.50, -1.50);
		if (i==5) TeleportCharacterToPosAy(sld, -6.63, 2.56, 1.00, -1.50);
		if (i==6) TeleportCharacterToPosAy(sld, -10.50, 2.56, 1.00, 1.50);
		if (i==7) TeleportCharacterToPosAy(sld, -10.50, 2.56, -0.50, 1.50);
		if (i==8) TeleportCharacterToPosAy(sld, -10.50, 2.56, -2.00, 1.50);
	}
	
	CreateLocationParticles("large_smoke", "quest", "quest4", 0, 0, 0, "");
	CreateLocationParticles("shipfire", "quest", "quest4", 0, 0, 0, "fortfire");
	CreateLocationParticles("large_smoke", "goto", "goto8", 0, 0, 0, "");
	CreateLocationParticles("shipfire", "goto", "goto8", 0, 0, 0, "fortfire");*/
}

void SharlieTutorial_PobedaPaluba_2(string qName)
{
	StartQuestMovie(true, false, true);
	pchar.questTemp.NoFast = true;
	SetMusic("music_Quest_Deck");
	//locCameraFromToPos(-8.74, 6.30, 7.38, true, -14.34, 4.16, 6.56);
	//locCameraFromToPos(-14.85, 4.73, 5.82, true, -10.30, 4.52, 6.14);
	//locCameraFromToPos(-14.90, 5.43, 5.86, true, -9.98, 4.22, 6.01);
	locCameraFromToPos(-14.75, 5.59, 4.96, true, -10.14, 4.30, 6.47);
}

/*void SharlieTutorial_PobedaPaluba_Kazn_1(string qName)
{
	StartQuestMovie(true, false, true);
	pchar.questTemp.NoFast = true;
	LAi_FadeLong("", "");
	LAi_SetStayType(pchar);
	DoQuestFunctionDelay("SharlieTutorial_PobedaPaluba_Kazn_2", 1.0);
}

void SharlieTutorial_PobedaPaluba_Kazn_2(string qName)
{
	TeleportCharacterToPosAy(pchar, -7.03, 2.48, 3.91, -2.75);
	locCameraFromToPos(-8.31, 4.38, 1.12, true, -8.03, 2.26, 3.88);
	DoQuestFunctionDelay("SharlieTutorial_PobedaPaluba_Kazn_3", 3.5);
}

void SharlieTutorial_PobedaPaluba_Kazn_3(string qName)
{
	locCameraFromToPos(-8.48, 3.91, -2.33, true, -8.72, 2.89, -5.30);
	DoQuestFunctionDelay("SharlieTutorial_PobedaPaluba_Kazn_4", 2.5);
}

void SharlieTutorial_PobedaPaluba_Kazn_4(string qName)
{
	TeleportCharacterToPosAy(pchar, -8.65, 4.73, 5.73, 3.00);
	locCameraFromToPos(-7.22, 4.31, 4.45, true, -9.36, 1.82, -0.78);
	DoQuestFunctionDelay("SharlieTutorial_PobedaPaluba_Kazn_5", 2.5);
}

void SharlieTutorial_PobedaPaluba_Kazn_5(string qName)
{
	sld = CharacterFromID("SharlieTutorial_Captain");
	CharacterTurnByChr(sld, CharacterFromID("SharlieTutorial_prisoner"));
	LAi_SetActorType(sld);
	LAi_ActorAnimation(sld, "Shot", "1", 1.8);
	DoQuestFunctionDelay("SharlieTutorial_PobedaPaluba_Kazn_6", 0.9);
}

void SharlieTutorial_PobedaPaluba_Kazn_6(string qName)
{
	sld = CharacterFromID("SharlieTutorial_prisoner");
	LAi_KillCharacter(sld);
	PlaySound("interface\abordage_wining.wav");
	DoQuestFunctionDelay("SharlieTutorial_PobedaPaluba_Kazn_7", 3.5);
}

void SharlieTutorial_PobedaPaluba_Kazn_7(string qName)
{
	EndQuestMovie();
	DeleteAttribute(pchar, "questTemp.NoFast");
	DoQuestReloadToLocation("My_Campus", "rld", "loc2", "Sharlie_Start");
}*/


/*void SharlieTutorial_ShootingTraining_1(string qName)
{
	sld = CharacterFromID("SharlieTutorial_Captain");
	sld.Dialog.Filename = "Quest\Sharlie\Tutorial.c";
	sld.Dialog.currentnode = "ShootingTraining_1";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 0, 0);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
}

void SharlieTutorial_ShootingTraining_2(string qName)
{
	LAi_LocationFightDisable(loadedLocation, false);
	LAi_SetPlayerType(pchar);
	GiveItem2Character(PChar, "pistol1");
	EquipCharacterbyItem(PChar, "pistol1");
	AddItems(pchar, "bullet", 50);
	AddItems(pchar, "GunPowder", 50);
	LAi_GunSetChargeQuant(pchar, GUN_ITEM_TYPE, 1);
	
	SetFunctionNPCDeathCondition("SharlieTutorial_FencingTraining_1", "SharlieTutorial_prisoner", false);
}

void SharlieTutorial_ShootingTraining_3(string qName)
{
	DoQuestFunctionDelay("SharlieTutorial_FencingTraining_1", 2.0);
}

void SharlieTutorial_FencingTraining_1(string qName)
{
	LAi_SetStayType(pchar);
	DoQuestFunctionDelay("SharlieTutorial_FencingTraining_2", 3.0);
}

void SharlieTutorial_FencingTraining_2(string qName)
{
	LAi_SetPlayerType(pchar);
	sld = CharacterFromID("SharlieTutorial_Captain");
	sld.Dialog.Filename = "Quest\Sharlie\Tutorial.c";
	sld.Dialog.currentnode = "FencingTraining_1";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 0, 0);
}

void SharlieTutorial_FencingTraining_3(string qName)
{
	LAi_FadeLong("", "");
	DoQuestFunctionDelay("SharlieTutorial_FencingTraining_3_1", 1.0);
	CharacterTurnToLoc(pchar, "quest", "quest2");
}

void SharlieTutorial_FencingTraining_3_1(string qName)
{
	DoFunctionReloadToLocation("Quest_Ship_deck_Medium_trade", "goto", "goto6", "SharlieTutorial_FencingTraining_4");
}

void SharlieTutorial_FencingTraining_4(string qName)
{
	for (i=1; i<=8; i++)
	{
		sld = CharacterFromID("SharlieTutorial_Sailor_"+i);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
		if (i==1) TeleportCharacterToPosAy(sld, -10.60, 2.69, -6.30, 0.50);
		if (i==2) TeleportCharacterToPosAy(sld, -6.61, 2.69, -6.20, -0.50);
		if (i==3) TeleportCharacterToPosAy(sld, -6.63, 2.56, -2.00, -1.50);
		if (i==4) TeleportCharacterToPosAy(sld, -6.63, 2.56, -0.50, -1.50);
		if (i==5) TeleportCharacterToPosAy(sld, -6.63, 2.56, 1.00, -1.50);
		if (i==6) TeleportCharacterToPosAy(sld, -10.50, 2.56, 1.00, 1.50);
		if (i==7) TeleportCharacterToPosAy(sld, -10.50, 2.56, -0.50, 1.50);
		if (i==8) TeleportCharacterToPosAy(sld, -10.50, 2.56, -2.00, 1.50);
	}
	
	sld = CharacterFromID("SharlieTutorial_Captain");
	TeleportCharacterToPosAy(pchar, -8.70, 4.74, 5.96, 0.00);
	TeleportCharacterToPosAy(sld, -8.70, 5.02, 9.98, 3.00);
	LAi_SetStayType(pchar);
	DoQuestFunctionDelay("SharlieTutorial_FencingTraining_5", 1.5);
}

void SharlieTutorial_FencingTraining_5(string qName)
{
	LAi_SetPlayerType(pchar);
	LAi_SetFightMode(pchar, true);
	LAi_SetCurHPMax(pchar); 
	LAi_GetCharacterMaxEnergy(pchar);
	sld = CharacterFromID("SharlieTutorial_Captain");
	LAi_SetCurHPMax(sld); 
	LAi_GetCharacterMaxEnergy(sld);
	LAi_SetImmortal(sld, false);
	LAi_group_Delete("EnemyFight");
	if (MOD_SKILL_ENEMY_RATE <= 10)
	{
		LAi_SetHP(sld, LAi_GetCharacterMaxHP(sld) * 0.7, LAi_GetCharacterMaxHP(sld) * 0.7);
		sld.rank = 1;
		SetSelfSkill(sld, 1, 1, 1, 1, 1);
	}
	DialogExit();
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	// ставим проверяльщики
	LAi_SetCheckMinHP(pchar, 1, true, "SharlieTutorial_HeroFail");
	LAi_SetCheckMinHP(sld, 1, true, "SharlieTutorial_HeroWin");
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
}

void SharlieTutorial_Training_Exit(string qName)
{
	DeleteAttribute(&locations[FindLocation("Quest_Ship_deck_Medium_trade")], "reload");
	LAi_LocationFightDisable(&Locations[FindLocation("Quest_Ship_deck_Medium_trade")], true);
	LAi_SetCurHPMax(pchar); 
	LAi_GetCharacterMaxEnergy(pchar);
	for (i=1; i<=8; i++)
	{
		sld = CharacterFromID("SharlieTutorial_Sailor_"+i);
		sld.lifeday = 0;
	}
	for (i=1; i<=3; i++)
	{
		sld = CharacterFromID("SharlieTutorial_Officer_"+i);
		sld.lifeday = 0;
	}
	sld = CharacterFromID("SharlieTutorial_Captain");
	sld.lifeday = 0;
	DoQuestReloadToLocation("My_Campus", "rld", "loc2", "Sharlie_Start");
}*/

void SharlieTutorial_Music(string qName)
{
	SetMusic("music_Quest_Sea");
}

void SharlieTutorial_PogodaRefresh(string qName)
{
	CreateWeatherEnvironment();
}

void SharlieTutorial_RadiusCannonsOff(string qName)
{
	pchar.wind.speed = 18.0;
	fWeatherSpeed = stf(18.0);
	pchar.wind.angle = 0.0;
	fWeatherAngle = stf(0.0);
	DontRefreshBLI = true;
}

void SharlieTutorial_windlass_1() //активация брашпиля
{
	LAi_SetActorType(pchar);
	LAi_FadeLong("", "");
	CharacterTurnToLoc(pchar, "event", "event1");
	DoQuestFunctionDelay("SharlieTutorial_windlass_2", 1.0);
	pchar.questTemp.SharlieTutorial_ActivateWindlass = true;
	//DoQuestFunctionDelay("SharlieTutorial_windlass_2", 1.5);
}

void SharlieTutorial_windlass_2(string qName)
{
	StartQuestMovie(true, false, true);
	pchar.questTemp.NoFast = true;
	locCameraFromToPos(-10.44, 4.86, -7.03, true, -8.82, 2.37, -9.96);
	//TeleportCharacterToPosAy(pchar, -8.30, 2.94, -10.69, 3.00);
	TeleportCharacterToPosAy(pchar, -7.30, 2.94, -10.69, 3.00);
	LAi_ActorAnimation(pchar, "tutorial_3", "1", 15);
	
	sld = CharacterFromID("SharlieTutorial_Sailor_2");
	ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto5");
	
	DoQuestFunctionDelay("SharlieTutorial_windlass_3", 5.0);
}

void SharlieTutorial_windlass_3(string qName)
{
	locCameraFromToPos(-6.25, 4.52, -7.54, true, -8.99, 1.94, -11.17);
	DoQuestFunctionDelay("SharlieTutorial_windlass_4", 1.00);
}

void SharlieTutorial_windlass_4(string qName)
{
	sld = CharacterFromID("SharlieTutorial_Windlass");
	LAi_SetActorType(sld);
	LAi_ActorAnimation(sld, "rotate_1", "", 15);
	DoQuestFunctionDelay("SharlieTutorial_windlass_5", 1.00);
	PlaySound("Ship\windlass_activate.wav");
	//PlaySound("Ship\windlass_activate.wav");
}

void SharlieTutorial_windlass_5(string qName)
{
	//locCameraFlyToPositionLookToPoint(-6.25, 4.52, -7.54, -8.99, 3.38, -11.17, -8.99, 3.38, -11.17, -1, 6000/GetDeltaTime());
	locCameraFlyToPositionLookToPoint(-6.25, 4.52, -7.54, -7.88, 3.84, -9.70, -8.99, 3.38, -11.17, -1, 3500/GetDeltaTime());
	Pchar.FuncCameraFly = "SharlieTutorial_windlass_6";
}

void SharlieTutorial_windlass_6(string qName)
{
	locCameraSleep(true);
	LAi_FadeLong("", "");
	DoQuestFunctionDelay("SharlieTutorial_windlass_7", 1.00);
}

void SharlieTutorial_windlass_7(string qName)
{
	locCameraSleep(false);
	locCameraResetState();
	TeleportCharacterToPosAy(pchar, -7.54, 3.01, -11.90, 3.00);
	//TeleportCharacterToPosAy(pchar, -10.27, 2.88, -9.80, 1.50);
	sld = CharacterFromID("SharlieTutorial_Windlass");
	LAi_SetActorType(sld);
	LAi_ActorAnimation(sld, "idle_1", "1", 5);
	
	LAi_SetStayType(pchar);
	sld = CharacterFromID("SharlieTutorial_Sailor_2");
	ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto2");
	sld.Dialog.Filename = "Quest\Sharlie\Tutorial.c";
	sld.Dialog.currentnode = "SailorWithWindlass_1";
	LAi_CharacterEnableDialog(sld);
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 0, 0);
}

void SharlieTutorial_windlass_8()
{
	locCameraSleep(true);
	LAi_FadeLong("", "");
	DoQuestFunctionDelay("SharlieTutorial_windlass_9", 1.00);
}

void SharlieTutorial_windlass_9(string qName)
{
	EndQuestMovie();
	DeleteAttribute(pchar, "questTemp.NoFast");
	locCameraSleep(false);
	locCameraFollowEx(true);
	LAi_SetPlayerType(pchar);
	sld = &Locations[FindLocation("Quest_Ship_deck_Medium_trade")];
	DelLocatorEvent(sld.id, "event1");
	pchar.SharlieTutorial.FullyCompleted = sti(pchar.SharlieTutorial.FullyCompleted) + 1;
}

/*void SharlieTutorial_windlass_2(string qName)
{
	LAi_ActorAnimation(pchar, "tutorial_3", "1", 15);
	DoQuestFunctionDelay("SharlieTutorial_windlass_3", 3.0);
}

void SharlieTutorial_windlass_3(string qName)
{
	PlaySound("Ships\snasti_skrp_002.wav");
	PlaySound("Ships\snasti_skrp_002.wav");
	DoQuestFunctionDelay("SharlieTutorial_windlass_4", 3.0);
}

void SharlieTutorial_windlass_4(string qName)
{
	LAi_SetStayType(pchar);
	sld = CharacterFromID("SharlieTutorial_Sailor_2");
	sld.Dialog.Filename = "Quest\Sharlie\Tutorial.c";
	sld.Dialog.currentnode = "SailorWithWindlass_1";
	LAi_CharacterEnableDialog(sld);
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 0, 0);
}

*/

void SharlieTutorial_cannon_1() //активация пушки
{
	LAi_SetStayType(pchar);
	LAi_FadeLong("", "");
	DoQuestFunctionDelay("SharlieTutorial_cannon_2", 1.0);
}

void SharlieTutorial_cannon_2(string qName)
{
	StartQuestMovie(true, false, true);
	pchar.questTemp.NoFast = true;
	//TeleportCharacterToPosAy(pchar, -10.03, 5.04, 11.56, 0.00);
	TeleportCharacterToPosAy(pchar, -10.00, 5.04, 11.26, 0.00);
	sld = CharacterFromID("SharlieTutorial_Sailor_10");
	sld.Dialog.Filename = "Quest\Sharlie\Tutorial.c";
	sld.Dialog.currentnode = "SailorWithCannon_1";
	LAi_CharacterEnableDialog(sld);
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 0, 0);
}

void SharlieTutorial_cannon_3()
{
	LAi_FadeLong("", "");
	DoQuestFunctionDelay("SharlieTutorial_cannon_4", 1.0);
}

void SharlieTutorial_cannon_4(string qName)
{
	locCameraSleep(false);
	sld = GetCharacter(CreateCharacterClone(CharacterFromID("SharlieTutorial_Captain"), 0));
	sld.id = "SharlieTutorial_Captain_clone";
	ChangeCharacterAddressGroup(sld, "Quest_Ship_deck_Medium_trade", "goto", "goto8");
	TeleportCharacterToPosAy(sld, -9.23, 4.97, 9.45, -0.30);
	DelLandQuestMark(sld);
	sld.Dialog.Filename = "Quest\Sharlie\Tutorial.c";
	sld.Dialog.currentnode = "CaptainWithCannon_1";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 0, 0);
	
	sld = CharacterFromID("SharlieTutorial_Captain");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	
	sld = CharacterFromID("SharlieTutorial_Sailor_5");
	LAi_SetActorType(sld);
}

void SharlieTutorial_cannon_5()
{
	locCameraSleep(true);
	LAi_FadeLong("", "");
	DoQuestFunctionDelay("SharlieTutorial_cannon_6", 1.0);
	CharacterTurnByChr(CharacterFromID("SharlieTutorial_Captain_clone"), pchar);
	CharacterTurnByChr(CharacterFromID("SharlieTutorial_Sailor_10"), pchar);
}

void SharlieTutorial_cannon_6(string qName)
{
	locCameraSleep(false);
	locCameraFromToPos(-15.77, 7.37, 14.79, true, -11.47, 4.82, 12.36);
	TeleportCharacterToPosAy(pchar, -10.00, 5.04, 11.26, 0.00);
	LAi_SetActorType(pchar);
	LAi_ActorAnimation(pchar, "tutorial_1", "1", 10);
	DoQuestFunctionDelay("SharlieTutorial_cannon_6_1", 1.5);
	DoQuestFunctionDelay("SharlieTutorial_cannon_7", 4.2);
}

void SharlieTutorial_cannon_6_1(string qName)
{
	SendMessage(pchar, "lslssl", MSG_CHARACTER_EX_MSG, "TieItem", FindItem("Wick"), "Wick", "Saber_hand", 1);
}

void SharlieTutorial_cannon_7(string qName)
{
	locCameraFromToPos(-11.38, 6.74, 8.60, true, -10.28, 4.55, 12.93);
	LAi_SetActorType(pchar);
	LAi_ActorAnimation(pchar, "tutorial_2", "1", 10);
	DoQuestFunctionDelay("SharlieTutorial_cannon_7_1", 2.7);
	DoQuestFunctionDelay("SharlieTutorial_cannon_8", 4.5);
}

void SharlieTutorial_cannon_7_1(string qName)
{
	PlaySound("Sea Battles_01\Cannon_fire_tutorial.wav");
	PlaySound("Sea Battles_01\Cannon_fire_tutorial.wav");
}

void SharlieTutorial_cannon_8(string qName)
{
	CreateLocationParticles("Ship_cannon_fire", "effect", "effect2", 0, 10, 0, "");
	DoQuestFunctionDelay("SharlieTutorial_cannon_9", 2.5);
	AddCharacterSkillPoints(pchar, "Cannons", 1);
}

void SharlieTutorial_cannon_9(string qName)
{
	LAi_FadeLong("", "");
	DoQuestFunctionDelay("SharlieTutorial_cannon_10", 1.0);
}

void SharlieTutorial_cannon_10(string qName)
{
	EndQuestMovie();
	DeleteAttribute(pchar, "questTemp.NoFast");
	SendMessage(pchar, "lsl", MSG_CHARACTER_EX_MSG, "UntieItem", FindItem("Wick"));
	locCameraTarget(PChar);
	locCameraFollow();
	LAi_SetPlayerType(pchar);
	
	sld = CharacterFromID("SharlieTutorial_Captain");
	ChangeCharacterAddressGroup(sld, "Quest_Ship_deck_Medium_trade", "quest", "quest3");
	
	sld = CharacterFromID("SharlieTutorial_Captain_clone");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	
	sld = CharacterFromID("SharlieTutorial_Sailor_5");
	LAi_SetCitizenType(sld);
	
	sld = CharacterFromID("SharlieTutorial_Sailor_10");
	sld.Dialog.Filename = "Quest\Sharlie\Tutorial.c";
	sld.Dialog.currentnode = "AlonsoWait";
	LAi_SetStayType(sld);
	
	sld = &Locations[FindLocation("Quest_Ship_deck_Medium_trade")];
	DelLocatorEvent(sld.id, "event3");
	pchar.SharlieTutorial.FullyCompleted = sti(pchar.SharlieTutorial.FullyCompleted) + 1;
}

void SharlieTutorial_cannon_11()
{
	EndQuestMovie();
	DeleteAttribute(pchar, "questTemp.NoFast");
	LAi_SetPlayerType(pchar);
	sld = CharacterFromID("SharlieTutorial_Sailor_10");
	LAi_SetStayType(sld);
	sld.Dialog.Filename = "Quest\Sharlie\Tutorial.c";
	sld.Dialog.currentnode = "AlonsoWait";
	
	sld = &Locations[FindLocation("Quest_Ship_deck_Medium_trade")];
	DelLocatorEvent(sld.id, "event3");
}

void SharlieTutorial_StartGameInMartinique()
{
	SharlieTutorial_ShowLogo_End();
	
	// Очищаем палубу и возвращаем её в исходное состояние
	if (CharacterIsAlive("SharlieTutorial_Captain"))
	{
		sld = CharacterFromID("SharlieTutorial_Captain");
		sld.lifeday = 0;
	}
	for (i=1; i<=11; i++)
	{
		if (CharacterIsAlive("SharlieTutorial_Sailor_"+i))
		{
			sld = CharacterFromID("SharlieTutorial_Sailor_"+i);
			sld.lifeday = 0;
		}
	}
	for (i=1; i<=3; i++)
	{
		if (CharacterIsAlive("SharlieTutorial_Officer_"+i))
		{
			sld = CharacterFromID("SharlieTutorial_Officer_"+i);
			sld.lifeday = 0;
		}
	}
	sld = &Locations[FindLocation("Quest_Ship_deck_Medium_trade")];
	DelLocatorEvent(sld.id, "event1");
	DelLocatorEvent(sld.id, "event3");
	DeleteAttribute(&locations[FindLocation("Quest_Ship_deck_Medium_trade")], "reload");
	LAi_LocationFightDisable(&Locations[FindLocation("Quest_Ship_deck_Medium_trade")], true);
	QuestPointerDelLoc("Quest_Deck_Medium", "reload", "reload_cabin");
	// закрываем запись в СЖ
	CloseQuestHeader("SharlieTutorial");
	// убираем ключ с Туториала
	sld = ItemsFromID("tutorial_key");
	sld.shown = false;
	// возвращаем ванильную цену за карту
	sld = ItemsFromID("map_full");
	sld.price = 0;
    if(GetCharacterItem(PChar, "map_full") == 0)
    {
        // Стереть конды и карту
        locations[FindLocation(sld.MapLocId)].DisableEncounters = false;
        DeleteAttribute(sld, "MapIslId");
        DeleteAttribute(sld, "MapLocId");
        DeleteAttribute(sld, "MapBoxId");
        DeleteAttribute(sld, "BoxTreasure");
        DeleteAttribute(PChar, "GenQuest.Treasure.Vario");
        DeleteAttribute(PChar, "quest.SetTreasureFromMap");
    }
	// возвращаем предмету ванильное описание
	sld = ItemsFromID("quest_potion");
	sld.name = "itmname_quest_potion";
	sld.describe = "itmdescr_quest_potion";
	// удаляем проверки
	DeleteQuestCondition("SharlieTutorial_journal");
	DeleteQuestCondition("SharlieTutorial_OhrannikStopaet");
	DeleteQuestCondition("SharlieTutorial_TrumBitva_4");
	DeleteQuestCondition("SharlieTutorial_PobedaPaluba");
	DeleteQuestCondition("SharlieTutorial_AttackDead");
	DeleteQuestCondition("SharlieTutorial_SailorCleansFloors");
	// чистим сундуки и возвращаем стандартную музыку на палубах
	sld = &Locations[FindLocation("Quest_Deck_Medium")];
	sld.type = "residence";
	DeleteAttribute(sld, "private1");
	DeleteAttribute(sld, "private2");
	DeleteAttribute(sld, "private3");
	DeleteAttribute(sld, "private4");
	sld = &Locations[FindLocation("Quest_Campus")];
	sld.type = "residence";
	DeleteAttribute(sld, "private1");
	DeleteAttribute(sld, "private2");
	DeleteAttribute(sld, "private3");
	DeleteAttribute(sld, "private4");
	sld = &Locations[FindLocation("Quest_Deck")];
	sld.type = "residence";
	DeleteAttribute(sld, "private1");
	DeleteAttribute(sld, "private2");
	DeleteAttribute(sld, "private3");
	DeleteAttribute(sld, "private4");
	sld = &Locations[FindLocation("Quest_Cabin_Medium")];
	sld.type = "residence";
	DeleteAttribute(sld, "private1");
	DeleteAttribute(sld, "private2");
	DeleteAttribute(sld, "private3");
	DeleteAttribute(sld, "private4");
	sld = &Locations[FindLocation("Quest_Ship_deck_Medium_trade")];
	sld.type = "residence";
	DeleteAttribute(sld, "private1");
	DeleteAttribute(sld, "private2");
	DeleteAttribute(sld, "private3");
	DeleteAttribute(sld, "private4");
	// удаляем лишние атрибуты
	DeleteAttribute(pchar, "GenQuest.MaxSailing");
	DeleteAttribute(pchar, "GenQuest.CabinLock");
	DeleteAttribute(pchar, "GenQuest.NoExp");
	DeleteAttribute(pchar, "questTemp.NoFast");
	DeleteAttribute(pchar, "TutorialToPort");
	DeleteAttribute(pchar, "GenQuest.BlockTalkSelf");
	// без корабля
	pchar.Ship.Type = SHIP_NOTUSED;
	// ставим время суток
	worldMap.date.day   = STARTGAME_DAY;
	worldMap.date.month = STARTGAME_MONTH;
	Environment.date.day = STARTGAME_DAY;
	Environment.date.month = STARTGAME_MONTH;
	SetCurrentTime(11, 30);
	CreateWeatherEnvironment();
	// полное здоровье и энергия
	LAi_SetCurHPMax(pchar); 
	LAi_GetCharacterMaxEnergy(pchar);
	// забираем тромбон
	if (!IsCharacterPerkOn(pchar, "HT4"))
	{
		RemoveCharacterEquip(PChar, GUN_ITEM_TYPE);
		TakeItemFromCharacter(pchar, "pistol3");
	}
	// остальные настройки
	Event("QuestDelayExit","sl", "", 0);
	bDisableCharacterMenu = false;
	InterfaceStates.Buttons.Save.enable = true;
    bGlobalTutor = false;
	chrDisableReloadToLocation = false;
	Island_SetReloadEnableGlobal("Martinique", true);
	setCharacterShipLocation(pchar, "Fortfrance_town");
	setWDMPointXZ("Fortfrance_town");
	DoQuestReloadToLocation("Fortfrance_town", "reload", "reload1", "Sharlie_onLand");
}

void SharlieTutorial_ActivateButtonInTheSea_1(string qName)
{
	pchar.TutorialToDeck_1 = true;
	Log_SetActiveAction("Deck");
}

void SharlieTutorial_ActivateButtonInTheSea_2(string qName)
{
	pchar.TutorialToDeck_2 = true;
	Log_SetActiveAction("Deck");
}

void SharlieTutorial_ActivateButtonInTheSea_3(string qName)
{
	pchar.TutorialToPort = true;
	ILogAndActions.ActiveActions.Deck.Text = XI_ConvertString("for_quick_action_To_Martinique");//Палуба
	Log_SetActiveAction("Deck");
	DoQuestFunctionDelay("SharlieTutorial_SeaNearMartinique_AutoTeleport", 60.0);
}

void SharlieTutorial_Ranen_2(string qName)
{
	DoFunctionReloadToLocation("Quest_Ship_deck_Medium_trade", "goto", "goto8", "SharlieTutorial_PobedaPaluba_NoParam");
}

void SharlieTutorial_OhrannikStopaet(string qName)
{
	sld = CharacterFromID("SharlieTutorial_Sailor_6");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 0, 0);
}

void SharlieTutorial_BoxOfBallsFind(string qName)
{
	QuestPointerDelLoc("Quest_Deck", "box", "private4");
}

void SharlieTutorial_SailorCleansFloors(string qName)
{
	sld = CharacterFromID("SharlieTutorial_Sailor_11");
	SendMessage(sld, "lslssl", MSG_CHARACTER_EX_MSG, "TieItem", FindItem("Brush_Props"), "Brush_Props", "Saber_hand", 1);
	LAi_SetActorType(sld);
	LAi_ActorAnimation(sld, "tutorial_4", "", -1.0);
}

void SharlieTutorial_SailorSnore(string qName)
{
	DeleteAttribute(&TEV, "SharlieTutorial_SailorSnore");
}

void SharlieTutorial_AlonsoHired(string qName)
{
	if (!CheckAttribute(pchar, "questTemp.SharlieTutorial_AlonsoOfficer"))
	{
		sld = CharacterFromID("SharlieTutorial_Alonso");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		pchar.questTemp.SharlieTutorial_AlonsoOfficer = true;
	}
}

/*void SharlieTutorial_Logotip()
{
	locCameraFlyToPositionLookToPoint(-14.75, 5.59, 4.96, -85.73, 1.55, -18.54, -10.14, 5.74, 6.47, -1, 15000/GetDeltaTime());
	Pchar.FuncCameraFly = "SharlieTutorial_Logotip_2";
	
	for (i=1; i<=5; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("SharlieTutorial_Sailor_"+i, "citiz_3"+i, "man", "man", 5, FRANCE, 0, false, "pirate"));
		sld.name 	= StringFromKey("SharlieTutorial_2");
		sld.lastname = "";
		ChangeCharacterAddressGroup(sld, "Quest_Ship_deck_Medium_trade", "goto", "goto"+i);
		LAi_SetCitizenType(sld);
	}
}

void SharlieTutorial_Logotip_2()
{
	EndQuestMovie();
	DeleteAttribute(pchar, "questTemp.NoFast");
	//LAi_SetStayType(pchar);
	SharlieTutorial_StartGameInMartinique();
}*/

void SharlieTutorial_SeaNearMartinique()
{
	pchar.systeminfo.BLIoff = true;
	SeaCameras_SetShipCameraAy(180.0);
	
	pchar.Ship.Type = GenerateShipExt(SHIP_PINNACE, true, pchar);
	pchar.Ship.name = StringFromKey("SharlieTutorial_6");
	SetBaseShipData(pchar);
	RealShips[sti(pchar.Ship.Type)].ship.upgrades.hull = 2;
	SetShipSailsFromFile(pchar, "ships/parus_silk.tga");
	realships[sti(pchar.ship.type)].SpeedRate = 15.5;
	realships[sti(pchar.ship.type)].TurnRate = 52.5;
	realships[sti(pchar.ship.type)].WaterLine = 1.3;
	realships[sti(pchar.ship.type)].Capacity = 6500;
	realships[sti(pchar.ship.type)].WindAgainstSpeed = 1.1;
	pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS32;
	SetCrewQuantityFull(pchar);
	pchar.ship.Crew.Morale = 100;
	ChangeCrewExp(pchar, "Sailors", 100);
	ChangeCrewExp(pchar, "Cannoners", 100);
	ChangeCrewExp(pchar, "Soldiers", 100);
	SetCharacterGoods(pchar, GOOD_BALLS, 0);
	SetCharacterGoods(pchar, GOOD_GRAPES, 0);
	SetCharacterGoods(pchar, GOOD_KNIPPELS, 0);
	SetCharacterGoods(pchar, GOOD_WEAPON, 0);
	SetCharacterGoods(pchar, GOOD_BOMBS, 0);
	SetCharacterGoods(pchar, GOOD_POWDER, 0);
	pchar.GenQuest.MaxSailing = true;
	bDisableCharacterMenu = true;
	bCannonsRangeShow = false;
	
	EndQuestMovie();
	worldMap.date.day   = STARTGAME_DAY;
	worldMap.date.month = STARTGAME_MONTH;
	Environment.date.day = STARTGAME_DAY;
	Environment.date.month = STARTGAME_MONTH;
	SetCurrentTime(10, 00);
	CreateWeatherEnvironment();
	DoQuestFunctionDelay("SharlieTutorial_SeaNearMartinique_4", 17.0);
	
	SetFunctionLocationCondition("SharlieTutorial_SeaNearMartinique_2", "Martinique", false);
	QuestToSeaLogin_Launch();
	QuestToSeaLogin_Prepare(500, -4160, "Martinique");
}

void SharlieTutorial_SeaNearMartinique_2(string qName)
{
	DoQuestFunctionDelay("SharlieTutorial_SeaNearMartinique_music", 0.1);
	DoQuestFunctionDelay("SharlieTutorial_SeaNearMartinique_Logo", 5.0);
	pchar.wind.speed = 18.0;
	fWeatherSpeed = stf(18.0);
	pchar.wind.angle = 0.0;
	fWeatherAngle = stf(0.0);
	Island_SetReloadEnableGlobal("Martinique", false);
	InterfaceStates.Buttons.Save.enable = false;
}

void SharlieTutorial_SeaNearMartinique_Logo(string qName)
{
	SharlieTutorial_ShowLogo_Start();
	Achievment_Set("ach_CL_162");
	if (CheckAttribute(PChar, "SharlieTutorial.FullyComplete") && sti(pchar.SharlieTutorial.FullyCompleted) == 6) Achievment_Set("ach_CL_163");
}

void SharlieTutorial_SeaNearMartinique_AutoTeleport(string qName)
{
	SharlieTutorial_StartGameInMartinique();
}

void SharlieTutorial_SeaNearMartinique_music(string qName)
{
	SetMusic("music_MainMenu");
	SendMessage(&AISea, "lllllffl", AI_MESSAGE_CANNONS_RANGE, argb(0,255,255,255), argb(0,255,255,255), argb(0,255,0,0), argb(0,255,0,0), 0.002, 0.002, 0);
}

bool SharlieTutorial_QuestComplete(string sQuestName, string qname)
{
	ref sld, chr;
	int iTemp, i;
	string sTemp;
	
	bool condition = true;
	
	if (sQuestName == "SharlieTutorial_StartGame")
	{
		bBettaTestMode = false;		// ПОТОМ УДАЛИТЬ
		DoQuestFunctionDelay("Rum_NewGameTip0", 10.0);
		worldMap.date.day   = 23;
		worldMap.date.month = 9;
		Environment.date.day = 23;
		Environment.date.month = 9;
	}
	else if (sQuestName == "SharlieTutorial_Ranen")
	{
		for (i=1; i<=15; i++)
		{
			if (CharacterIsAlive("SharlieTutorial_EnemyPirate_"+i))
			{
				sld = CharacterFromID("SharlieTutorial_EnemyPirate_"+i);
				//LAi_SetActorType(sld);
				sld.lifeday = 0;
			}
		}
		
		LAi_SetActorType(pchar);
		LAi_ActorAnimation(pchar, "death_1", "1", -1);
		DoQuestFunctionDelay("SharlieTutorial_Ranen_2", 4.8);
		
		pchar.questTemp.SharlieTutorial_Ranen = true;
	}
	/*else if (sQuestName == "SharlieTutorial_HeroWin")
	{
		LAi_group_Delete("EnemyFight");
		DoQuestCheckDelay("hide_weapon", 2.0);
		LAi_RemoveCheckMinHP(pchar);
		sld = characterFromId("SharlieTutorial_Captain");
		if (sti(sld.quest.SharlieTutorial_win == 0)) sld.dialog.currentnode = "FencingTraining_4";
		else sld.dialog.currentnode = "FencingTraining_5"; 
		LAi_SetActorType(sld);
		LAi_ActorTurnToCharacter(sld, pchar);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
	}
	else if (sQuestName == "SharlieTutorial_HeroFail")
	{
		LAi_group_Delete("EnemyFight");
		DoQuestCheckDelay("hide_weapon", 2.0);
		sld = characterFromId("SharlieTutorial_Captain");
		sld.quest.SharlieTutorial_win = sti(sld.quest.SharlieTutorial_win)+1;
		if (sti(sld.quest.SharlieTutorial_win == 1)) sld.dialog.currentnode = "FencingTraining_6";
		else 
		{
			if (sti(sld.quest.SharlieTutorial_win == 2)) sld.dialog.currentnode = "FencingTraining_7";
			else sld.dialog.currentnode = "FencingTraining_8";
		}
		LAi_SetActorType(sld);
		LAi_ActorTurnToCharacter(sld, pchar);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		LAi_SetImmortal(pchar, false);
	}*/
	/* else if (sQuestName == "SharlieTutorial_TrumBitva_5_1")
	{
		
		for(i = 0; i <= Dead_Char_num; i++)
		{
			if(Dead_Characters[i].id == "SharlieTutorial_EnemyPirate_1")
			{
				ref rDchar;
				makeref(rDchar, Dead_Characters[i]);
				log_info("Над персонажем " +rDchar.id+ " скоро появится маркер");
			}
		}
		//sld = CharacterFromID("SharlieTutorial_EnemyPirate_1");
		//AddLandQuestMark(sld, "questmarkmain");
		//DoQuestCheckDelay("SharlieTutorial_TrumBitva_5_2", 0.1);
	}
	else if (sQuestName == "SharlieTutorial_TrumBitva_5_2")
	{
		sld = CharacterFromID("SharlieTutorial_EnemyPirate_1");
		LAi_SetImmortal(sld, false);
		LAi_KillCharacter(sld);
	} */
	else if (sQuestName == "SharlieTutorial_AlonsoSkritoeBessmertie")
	{
		sld = CharacterFromID("SharlieTutorial_Alonso");
		LAi_SetCurHP(sld, 20.0);
		LAi_SetImmortal(sld, false);
		LAi_SetCheckMinHP(sld, 10, true, "SharlieTutorial_AlonsoSkritoeBessmertie");
	}
	else
	{
		condition = false;
	}
	
	return condition;
}

void SharlieTutorial_ShowLogo_Start()
{
	aref arImage, arLogo;
	makearef(arLogo, ILogAndActions.TutorialLogo);
	makearef(arImage, arLogo.images.logo);
	
	arImage.texture = "interfaces\le\cle_logo2.tga";
	arImage.uv = "0.0,0.0,1.0,1.0";
	
	arImage.pos = "560,140,1360,940";
	arImage.pos.step = 1;
	arImage.pos.maxStep = 1;
	arImage.pos.time = 0.0;
	
	arImage.color = argb(0, 128, 128, 128);
	arImage.color.step = 1;
	arImage.color.maxStep = 3;
	arImage.color.time = 0.0;

	SendMessage(&ILogAndActions , "lla", LI_MSG_TUTORIAL_SHOW, true, arLogo);
	
	SetEventHandler("TutorialLogo_Refresh", "TutorialLogo_Refresh", 0);
	Event("TutorialLogo_Refresh");
}

void TutorialLogo_Refresh()
{
	int delta = GetDeltaTime();
	
	aref arImage, arColor, arPos;
	makearef(arImage, ILogAndActions.TutorialLogo.images.logo);
	makearef(arColor, arImage.color);
	makearef(arPos, arImage.pos);
	float time, timer;
	float fHtRatio = stf(Render.screen_y) / iHudScale;

	// меняем цвет
	int color_step = sti(arColor.step);
	if(color_step <= sti(arColor.maxStep))
	{
		int alpha_start, alpha_end;
		switch(color_step)
		{
			case 1:
				alpha_start = 0;
				alpha_end = 255;
				timer = 2.0;
			break;
		
			case 2:
				alpha_start = 255;
				timer = 3.0;
				alpha_end = 255;
			break;
			
			case 3:
				alpha_start = 255;
				alpha_end = 0;
				timer = 2.0;
			break;
		}
		time = stf(arColor.time);
		time += delta * 0.001;
		int alpha = makeint(Bring2Range(alpha_start * 1.0, alpha_end * 1.0, 0.0, timer, time));
		arImage.color = argb(alpha, 128, 128, 128);
		if(time >= timer)
		{
			color_step++;
			arColor.step = color_step;
			time = 0.0;
		}
		arColor.time = time;
	}
	
	// меняем позицию
	int pos_step = sti(arPos.step);
	if(pos_step <= sti(arPos.maxStep))
	{
		int x1_start, y1_start, x2_start, y2_start;
		int x1_end, y1_end, x2_end, y2_end;
		int addStart = makeint(400 * fHtRatio);
		int addEnd = makeint(512 * fHtRatio);
		switch(pos_step)
		{
			case 1:
				x1_start = sti(showWindow.right) / 2 - RecalculateHIcon(addStart);
				y1_start = sti(showWindow.bottom) / 2 - RecalculateVIcon(addStart);
				x2_start = sti(showWindow.right) / 2 + RecalculateHIcon(addStart);
				y2_start = sti(showWindow.bottom) / 2 + RecalculateVIcon(addStart);
				x1_end = sti(showWindow.right) / 2 - RecalculateHIcon(addEnd);
				y1_end = sti(showWindow.bottom) / 2 - RecalculateVIcon(addEnd);
				x2_end = sti(showWindow.right) / 2 + RecalculateHIcon(addEnd);
				y2_end = sti(showWindow.bottom) / 2 + RecalculateVIcon(addEnd);
				timer = 2.0;
			break;
		}
		time = stf(arPos.time);
		time += delta * 0.001;
		int x1 = makeint(Bring2Range(x1_start * 1.0, x1_end * 1.0, 0.0, timer, time));
		int y1 = makeint(Bring2Range(y1_start * 1.0, y1_end * 1.0, 0.0, timer, time));
		int x2 = makeint(Bring2Range(x2_start * 1.0, x2_end * 1.0, 0.0, timer, time));
		int y2 = makeint(Bring2Range(y2_start * 1.0, y2_end * 1.0, 0.0, timer, time));
		arImage.pos = x1 + "," + y1 + "," + x2 + "," + y2;
		if(time >= timer)
		{
			pos_step++;
			arPos.step = pos_step;
			time = 0.0;
		}
		arPos.time = time;
	}
	
	if(color_step > sti(arColor.maxStep) && pos_step > sti(arPos.maxStep))
	{
		SharlieTutorial_ShowLogo_End();
		return;
	}
	PostEvent("TutorialLogo_Refresh", delta);
}

void SharlieTutorial_ShowLogo_End()
{
	DoQuestFunctionDelay("SharlieTutorial_ActivateButtonInTheSea_3", 0.5);
	SendMessage(&ILogAndActions , "ll", LI_MSG_TUTORIAL_SHOW, false);
	DeleteAttribute(&ILogAndActions, "TutorialLogo");
	DelEventHandler("TutorialLogo_Refresh", "TutorialLogo_Refresh");
}

void SharlieTutorial_GenerateTreasureMap(ref item)
{
    // Уже заполнена
    if(CheckAttribute(PChar, "quest.SetTreasureFromMap")) return;

    string sIsland = GetIslandForTreasure();
    while (sIsland == "Martinique") 
           sIsland = GetIslandForTreasure();

    item.MapIslId = sIsland;
    item.MapLocId = GetLocationForTreasure(item.MapIslId);
    item.MapBoxId = GetBoxForTreasure(item.MapIslId, item.MapLocId);
    DeleteAttribute(item, "BoxTreasure");

    FillBoxForTreasure(item);

    // Выставим конды сразу. Если карта не будет приобретена, то потом удалим
    PChar.quest.SetTreasureFromMap.win_condition.l1          = "location";
    PChar.quest.SetTreasureFromMap.win_condition.l1.location = item.MapLocId;
    PChar.quest.SetTreasureFromMap.win_condition             = "SetTreasureFromMap";
    PChar.GenQuest.Treasure.Vario = rand(5); // Определяем событие (33% скип)
    locations[FindLocation(item.MapLocId)].DisableEncounters = true;
}
