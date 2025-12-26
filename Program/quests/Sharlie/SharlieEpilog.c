/////////////////////////////////////////////////////////////////////////////////////////////////////////
// --------------------------------------------- ЭПИЛОГ ------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void SharlieEpilog_Start(string qName)
{
	pchar.quest.SharlieEpilog_Cureer.win_condition.l1 = "Nation_City";
	pchar.quest.SharlieEpilog_Cureer.win_condition.l1.nation = FRANCE;
	pchar.quest.SharlieEpilog_Cureer.function = "SharlieEpilog_Cureer";
	pchar.questTemp.SharlieEpilog_Start = true;
}

void SharlieEpilog_Cureer(string qName)
{
	chrDisableReloadToLocation = true;
	sld = GetCharacter(NPC_GenerateCharacter("SharlieEpilog_cureer", "mercen_11", "man", "man", 25, FRANCE, 0, true, "quest"));
	FantomMakeCoolFighter(sld, 25, 60, 60, "blade_10", "pistol5", "bullet", 100);
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	sld.dialog.filename = "Quest\Sharlie\Epilog.c";
	sld.dialog.currentnode = "SharlieEpilog_Cureer";
	LAi_SetImmortal(sld, true);
    ChangeCharacterAddressGroup(sld, pchar.location, "quest", "quest1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void SharlieEpilog_Cureer_2()
{
	chrDisableReloadToLocation = false;
	sld = CharacterFromID("SharlieEpilog_cureer");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 10.0);
	
	//
	pchar.questTemp.SharlieEpilog_Benua = true;
	AddLandQuestMark(characterFromId("Benua"), "questmarkmain");
	AddMapQuestMarkCity("BasTer", false);
}

void SharlieEpilog_Benua_TimeLater_1()
{
	SetLaunchFrameFormParam(GetConvertStr("Frame_MinutePassed_20", "Frame.txt")+ NewStr() +StringFromKey("SharlieFinal_85"), "Run_Function", 0, 4.0);
	SetLaunchFrameRunFunctionParam("SharlieEpilog_Benua_TimeLater_2", 0.0);
	LaunchFrameForm();
}

void SharlieEpilog_Benua_TimeLater_2()
{
	sld = CharacterFromID("Benua");
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "", 0, 0);
}

void SharlieEpilog_Benua_Dlg_1()
{
	DeleteAttribute(pchar, "questTemp.SharlieEpilog_Benua_back");
	sld = CharacterFromID("Benua");
	if (!CheckAttribute(sld, "SharlieEpilog_BenuaRazgovor_3"))
	{
		SetQuestHeader("SharlieEpilog");
		AddQuestRecord("SharlieEpilog", "1_1");
		sld.SharlieEpilog_BenuaRazgovor_3 = true;
	}
}

void SharlieEpilog_Benua_DlgExit_2()
{
	pchar.questTemp.SharlieEpilog_Benua_back = true;
	sld = CharacterFromID("Benua");
	if (!CheckAttribute(sld, "SharlieEpilog_BenuaRazgovor_3"))
	{
		SetQuestHeader("SharlieEpilog");
		AddQuestRecord("SharlieEpilog", "1_2");
		sld.SharlieEpilog_BenuaRazgovor_3 = true;
	}
}

void SharlieEpilog_Benua_DlgExit_3()
{
	pchar.questTemp.SharlieEpilog_Benua_DublonsLater = true;
	sld = CharacterFromID("Benua");
	if (!CheckAttribute(sld, "SharlieEpilog_BenuaRazgovor_4"))
	{
		AddQuestRecord("SharlieEpilog", "2");
		sld.SharlieEpilog_BenuaRazgovor_4 = true;
	}
}

void SharlieEpilog_PU_Ulysse_1()
{
	sld = CharacterFromID("Benua");
	LAi_SetStayTypeNoGroup(sld);
	DeleteAttribute(sld, "SharlieEpilog_BenuaRazgovor_2");
	
	pchar.questTemp.SharlieEpilog_PU_Ulysse = true;
	AddLandQuestMark(characterFromId("FortFrance_PortMan"), "questmarkmain");
	AddQuestRecord("SharlieEpilog", "10");
}

void SharlieEpilog_SpawnPikar()
{
	chrDisableReloadToLocation = true;
	DeleteAttribute(pchar, "questTemp.SharlieEpilog_PU_Ulysse");
	
	// создаём Пикара
	sld = GetCharacter(NPC_GenerateCharacter("SharlieEpilog_Pikar", "Jan_Pikar", "man", "man", sti(pchar.rank), FRANCE, -1, true, "quest"));
	sld.name = GetCharacterName("Jean");
	sld.lastname = GetCharacterName("Picard");
	if (CheckAttributeEqualTo(pchar, "questTemp.Mtraxx", "full_complete_end") || CheckAttributeEqualTo(pchar, "questTemp.Mtraxx", "full_complete"))
	{
		pchar.questTemp.SharlieEpilog_Pikar = true;
		if (!CheckAttribute(pchar, "questTemp.Mtraxx.RocurDie"))
		{
			pchar.questTemp.SharlieEpilog_PikarAlive = true;
			sld.dialog.filename = "Quest\Sharlie\Epilog.c";
			sld.dialog.currentnode = "SharlieEpilog_Pikar_1";
		}
		else
		{
			pchar.questTemp.SharlieEpilog_PikarResurrected = true;
			sld.dialog.filename = "Quest\Sharlie\Epilog.c";
			sld.dialog.currentnode = "SharlieEpilog_Pikar_1";
		}
	}
	else
	{
		sld.dialog.filename = "Quest\Sharlie\Epilog.c";
		sld.dialog.currentnode = "SharlieEpilog_Captain_1";
	}
	ChangeCharacterAddressGroup(sld, "FortFrance_PortOffice", "reload", "reload1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	
	// также создаём Алонсо
	sld = GetCharacter(NPC_GenerateCharacter("SharlieEpilog_Alonso", "Alonso", "man", "Alonso", 5, FRANCE, -1, false, "pirate"));
	sld.name = GetCharacterName("Alonso");
	sld.lastname = "";
	pchar.questTemp.SharlieEpilog_Friends = 1;
}

void SharlieEpilog_WithPikarToTavern()
{
	FreeSitLocator("Fortfrance_tavern", "sit_front4");
	FreeSitLocator("Fortfrance_tavern", "sit_base4");
	DoFunctionReloadToLocation("Fortfrance_tavern", "sit", "sit_base4", "");	
	sld = characterFromID("SharlieEpilog_Pikar");
	if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
	{
		if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive"))
		{
			sld.dialog.filename = "Quest\Sharlie\Epilog.c";
			sld.dialog.currentnode = "SharlieEpilog_Pikar_5";
		}
		else
		{
			sld.dialog.filename = "Quest\Sharlie\Epilog.c";
			sld.dialog.currentnode = "SharlieEpilog_PikarResurrected_3";
		}
	}
	else
	{
		sld.dialog.filename = "Quest\Sharlie\Epilog.c";
		sld.dialog.currentnode = "SharlieEpilog_Captain_5";
	}
	ChangeCharacterAddressGroup(sld, "Fortfrance_tavern", "sit", "sit_front4");
	LAi_SetActorType(sld);
	LAi_ActorSetSitMode(sld);
	LAi_ActorDialogDelay(sld, pchar, "", 1.5);
	LAi_SetSitType(Pchar);
}

void SharlieEpilog_OutTavern()
{
	chrDisableReloadToLocation = false;
	LAI_SetPlayerType(pchar);           
	DoFunctionReloadToLocation("Fortfrance_tavern", "tables", "stay1", "");
	sld = characterFromID("SharlieEpilog_Pikar");
	sld.dialog.filename = "Quest\Sharlie\Epilog.c";
	sld.dialog.currentnode = "SharlieEpilog_Pikar_WaitInTavern";
	LAi_SetSitType(sld);
	// ChangeCharacterAddressGroup(sld, "none", "", "");
	
	if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
	{
		if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
		{
			sld = CharacterFromID("Mary");
			sld.dialog.filename = "Quest\Sharlie\Epilog.c";
			sld.dialog.currentnode = "SharlieEpilog_Mary_1";
			AddLandQuestMark(sld, "questmarkmain");
		}
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
		{
			sld = CharacterFromID("Helena");
			sld.dialog.filename = "Quest\Sharlie\Epilog.c";
			sld.dialog.currentnode = "SharlieEpilog_Helena_1";
			AddLandQuestMark(sld, "questmarkmain");
		}
	}
	else
	{
		SharlieEpilog_FarewellOfficers();
	}
}

void SharlieEpilog_FarewellOfficers()
{
	if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) AddQuestRecord("SharlieEpilog", "12");
	if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && CharacterIsAlive("Helena")) ReturnOfficer_Helena();
	if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && CharacterIsAlive("Mary")) ReturnOfficer_Mary();
	pchar.questTemp.SharlieEpilog_FarewellOfficers = true;
	if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar")) // только если знаком с Пикаром
	{
		sld = characterFromID("SharlieEpilog_Pikar");
		AddLandQuestMark(sld, "questmarkmain");
	}
}

void SharlieEpilog_Irons_exit()
{
	sld = CharacterFromID("Irons");
	RemovePassenger(pchar, sld);
	LAi_SetCitizenType(sld);
	LAi_CharacterDisableDialog(sld);
	sld.location = "None";
	LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
	sld.quest.SharlieEpilog_FarewellOfficers = true;
	pchar.questTemp.SharlieEpilog_Irons = true;
}

void SharlieEpilog_Baker_exit()
{
	sld = CharacterFromID("Baker");
	RemovePassenger(pchar, sld);
	LAi_SetCitizenType(sld);
	LAi_CharacterDisableDialog(sld);
	sld.location = "None";
	LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
	sld.quest.SharlieEpilog_FarewellOfficers = true;
	pchar.questTemp.SharlieEpilog_Baker = true;
}

void SharlieEpilog_Folke_exit()
{
	sld = CharacterFromID("Folke");
	RemovePassenger(pchar, sld);
	LAi_SetCitizenType(sld);
	LAi_CharacterDisableDialog(sld);
	sld.location = "None";
	LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
	sld.quest.SharlieEpilog_FarewellOfficers = true;
	pchar.questTemp.SharlieEpilog_Folke = true;
}

void SharlieEpilog_Duran_exit()
{
	sld = CharacterFromID("Duran");
	RemovePassenger(pchar, sld);
	LAi_SetCitizenType(sld);
	LAi_CharacterDisableDialog(sld);
	sld.location = "None";
	LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
	sld.quest.SharlieEpilog_FarewellOfficers = true;
	pchar.questTemp.SharlieEpilog_Duran = true;
}

void SharlieEpilog_Alonso_exit()
{
	if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
	{
		FreeSitLocator("FortFrance_tavern", "sit4"); 
		sld = CharacterFromID("SharlieEpilog_Alonso");
		sld.dialog.filename = "Quest\Sharlie\Epilog.c";
		sld.dialog.currentnode = "SharlieEpilog_AlonsoInTavern";
		ChangeCharacterAddressGroup(sld, "FortFrance_tavern", "sit", "sit4");
		LAi_SetSitType(sld);
		AddLandQuestMark(sld, "questmarkmain");
	}
	pchar.questTemp.SharlieEpilog_Alonso = true;
}


void SharlieEpilog_FrameInSea() // здесь запускается фейд
{
	locCameraSleep(true);
	LAi_SetStayType(pchar);
	EndBattleLandInterface();

	CreateEntity(&LAi_QuestFader, "fader");
	SendMessage(&LAi_QuestFader, "lfl", FADER_OUT, 2.0, false);
    SetEventHandler("SharlieEpilog_FrameInSea_1", "SharlieEpilog_FrameInSea_1", 0);
    PostEvent("SharlieEpilog_FrameInSea_1", 2150);
}

void SharlieEpilog_FrameInSea_1() // здесь запускается заставка
{
    ResetSound();
    DeleteClass(&LAi_QuestFader);
    DelEventHandler("SharlieEpilog_FrameInSea_1", "SharlieEpilog_FrameInSea_1");
    SetLaunchFrameFormParam(StringFromKey("SharlieFinal_86"), "Run_Function", 0, 4.0);
    SetLaunchFrameRunFunctionParam("SharlieEpilog_UlysseInSea", 0.0);
    LaunchFrameForm();
}

void SharlieEpilog_UlysseInSea() // в Антлантическом океане на пинасе Улисс
{
	bDisableCharacterMenu = true;
	InterfaceStates.Buttons.Save.enable = false;
	bQuestDisableMapEnter = true;
	pchar.systeminfo.BLIoff = true;
	
	SetCurrentTime(19, 00);
	WeatherParams.Rain 			= false;
	WeatherParams.Rain.ThisDay 	= false;
	pchar.questTemp.TimeLock = true;
	CreateSky(3);
	// Корабль
	pchar.Ship.Type = GenerateShipExt(SHIP_PINNACE, true, pchar);
	pchar.Ship.name = GetShipName("Ulysse");
	SetBaseShipData(pchar);
	RealShips[sti(pchar.Ship.Type)].ship.upgrades.hull = 2;
	SetShipSailsFromFile(pchar, "ships/parus_silk.tga");
	realships[sti(pchar.ship.type)].WaterLine = 1.3;
	realships[sti(pchar.ship.type)].Capacity = 6500;
	realships[sti(pchar.ship.type)].SpeedRate = 11.65;
	realships[sti(pchar.ship.type)].TurnRate = 78.65;
	realships[sti(pchar.ship.type)].WindAgainstSpeed = 1.75;
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
	
	SeaCameras_SetShipCameraAy(115.0);
	
	QuestToSeaLogin_Prepare(0.0, 0.0, "");
	QuestToSeaLogin_Launch();
	
	DoQuestFunctionDelay("SharlieEpilog_UlysseInSea_2", 10.0);
}

void SharlieEpilog_UlysseInSea_2(string qName)
{
	ResetSound();
	SetSoundScheme("deck");
	DoFunctionReloadToLocation("Quest_Ship_deck_Medium_trade", "quest", "quest2", "SharlieEpilog_UlysseInSea_3");
}

void SharlieEpilog_UlysseInSea_3()
{
    ref sld;
	pchar.Ship.Type = SHIP_NOTUSED;
	DontRefreshBLI = false;
	StartQuestMovie(true, false, true);
	pchar.questTemp.NoFast = true;
	LAi_LocationFightDisable(loadedLocation, true);
	SetMusic("music_Quest_Deck");
	
	locCameraFromToPos(-8.74, 6.30, 7.38, true, -14.34, 4.16, 6.56);
	TeleportCharacterToPos(pchar, -11.64, 4.51, 6.28);
	LAi_SetActorType(pchar);
	LAi_ActorAnimation(pchar, "tutorial_4", "", -1.0);
	
	if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
	{
		sld = CharacterFromID("Helena");
		RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
		ChangeCharacterAddressGroup(sld, PChar.location, "quest", "quest10");
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "epilogue_1", "", -1.0);
        sld.chr_ai.tmpl.ignorecol = "";
	}
	
	if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
	{
		sld = CharacterFromID("Mary");
		RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
		ChangeCharacterAddressGroup(sld, PChar.location, "quest", "quest11");
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "epilogue_1", "", -1.0);
        sld.chr_ai.tmpl.ignorecol = "";
	}
	
	DoQuestFunctionDelay("SharlieEpilog_UlysseInSea_4", 5.0);
}

void SharlieEpilog_UlysseInSea_4(string qName)
{
	LAi_FadeEx(1.0, 0.0, 1.0, "SharlieEpilog_UlysseInSea_5", "", "");
}

void SharlieEpilog_UlysseInSea_5(string qName)
{
	locCameraFromToPos(-14.85, 4.73, 5.82, true, -10.30, 4.52, 6.14);
	
	if (!CharacterIsAlive("SharlieEpilog_Alonso"))
	{
		sld = GetCharacter(NPC_GenerateCharacter("SharlieEpilog_Alonso", "Alonso", "man", "Alonso", 5, FRANCE, -1, false, "pirate"));
		sld.name = GetCharacterName("Alonso");
		sld.lastname = "";
	}
	else
	{
		sld = CharacterFromID("SharlieEpilog_Alonso");
	}
	ChangeCharacterAddressGroup(sld, "Quest_Ship_deck_Medium_trade", "quest", "quest7");
	TeleportCharacterToPos(sld, -11.73, 4.46, 5.58);
	LAi_SetActorType(sld);
	LAi_ActorAnimation(sld, "tutorial_3", "", -1);
	
	DoQuestFunctionDelay("SharlieEpilog_UlysseInSea_6", 6.2);
}

void SharlieEpilog_UlysseInSea_6(string qName)
{
	LAi_FadeEx(1.0, 0.0, 1.0, "SharlieEpilog_UlysseInSea_7", "", "");
}

void SharlieEpilog_UlysseInSea_7(string qName)
{
	locCameraFromToPos(-8.74, 6.30, 7.38, true, -14.34, 4.16, 6.56);
	
	LAi_SetStayType(pchar);
	
	sld = CharacterFromID("SharlieEpilog_Alonso");
	sld.dialog.filename = "Quest\Sharlie\Epilog.c";
	sld.Dialog.currentnode = "SharlieEpilog_Alonso_1";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 0, 0);
}

void SharlieEpilog_UlysseInSea_8()
{
	locCameraSleep(true);
	LAi_FadeEx(1.0, 0.5, 1.0, "SharlieEpilog_UlysseInSea_8_1", "SharlieEpilog_UlysseInSea_9", "");
}

void SharlieEpilog_UlysseInSea_8_1(string qName)
{
	//Алонсо уходит в трюм
	sld = CharacterFromID("SharlieEpilog_Alonso");
	ChangeCharacterAddressGroup(sld, "Quest_Ship_deck_Medium_trade", "goto", "goto7");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload_arsenal", "", "", "", "", -1);
	sld.location = "None";
}

void SharlieEpilog_UlysseInSea_9(string qName)
{
	// Оказываемся на палубе Улисса в Эпилоге
	EndQuestMovie();
	locCameraSleep(false);
	ChangeCharacterAddressGroup(pchar, "Quest_Ship_deck_Medium_trade", "quest", "quest2");
	LAi_SetPlayerType(pchar);
	
	SetFunctionLocationCondition("SharlieEpilog_MaryHelena_Animation", "Quest_Ship_deck_Medium_trade", false);
	
	//Капитан Пикар
	sld = CharacterFromID("SharlieEpilog_Pikar");
	sld.dialog.filename = "Quest\Sharlie\Epilog.c";
	sld.dialog.currentnode = "SharlieEpilog_PikarOnUliss";
	ChangeCharacterAddressGroup(sld, "Quest_Ship_deck_Medium_trade", "quest", "quest3");
	LAi_SetStayType(sld);
	
	//Матрос 1 на верхней палубе
	sld = GetCharacter(NPC_GenerateCharacter("SharlieEpilog_Sailor_1", "citiz_32", "man", "man", 5, FRANCE, -1, false, "citizen"));
	sld.dialog.filename = "Quest\Sharlie\Epilog.c";
	sld.dialog.currentnode = "SharlieEpilog_Sailor_1";
	ChangeCharacterAddressGroup(sld, "Quest_Ship_deck_Medium_trade", "goto", "goto8");
	LAi_SetStayType(sld);
	
	//Матрос 2 на верхней палубе
	sld = GetCharacter(NPC_GenerateCharacter("SharlieEpilog_Sailor_2", "citiz_33", "man", "man", 5, FRANCE, -1, false, "citizen"));
	sld.dialog.filename = "Quest\Sharlie\Epilog.c";
	sld.dialog.currentnode = "SharlieEpilog_Sailor_2";
	ChangeCharacterAddressGroup(sld, "Quest_Ship_deck_Medium_trade", "goto", "goto4");
	LAi_SetStayType(sld);
	
	//Матрос 3 на орудийной палубе
	sld = GetCharacter(NPC_GenerateCharacter("SharlieEpilog_Sailor_3", "citiz_40", "man", "man", 5, FRANCE, -1, false, "citizen"));
	sld.dialog.filename = "Quest\Sharlie\Epilog.c";
	sld.dialog.currentnode = "SharlieEpilog_Sailor_3";
	ChangeCharacterAddressGroup(sld, "Quest_Deck_Medium", "goto", "goto1");
	LAi_SetCitizenType(sld);
	
	//Матрос 4 на орудийной палубе
	sld = GetCharacter(NPC_GenerateCharacter("SharlieEpilog_Sailor_4", "citiz_34", "man", "man", 5, FRANCE, -1, false, "citizen"));
	sld.dialog.filename = "Quest\Sharlie\Epilog.c";
	sld.dialog.currentnode = "SharlieEpilog_Sailor_4";
	ChangeCharacterAddressGroup(sld, "Quest_Deck_Medium", "goto", "goto4");
	LAi_SetCitizenType(sld);
	
	//Старший матрос
	sld = GetCharacter(NPC_GenerateCharacter("SharlieEpilog_HighSailor", "citiz_25", "man", "man", sti(pchar.rank), FRANCE, -1, true, "citizen"));
	sld.dialog.filename = "Quest\Sharlie\Epilog.c";
	sld.dialog.currentnode = "SharlieEpilog_HighSailor_1";
	ChangeCharacterAddressGroup(sld, "Quest_Ship_deck_Medium_trade", "reload", "reload_gundeck");
	LAi_SetStayType(sld);
	
	//Боцман Моко
	sld = GetCharacter(NPC_GenerateCharacter("SharlieEpilog_Moko", "Tamango", "man", "man", sti(pchar.rank), FRANCE, -1, true, "citizen"));
	sld.name = GetCharacterName("Moko");
	sld.lastname = "";
	sld.dialog.filename = "Quest\Sharlie\Epilog.c";
	sld.dialog.currentnode = "SharlieEpilog_Moko_1";
	ChangeCharacterAddressGroup(sld, "Quest_Campus", "quest", "quest1");
	LAi_SetStayType(sld);
	
	//Дворянин пассажир Бернард Трокмортон
	sld = GetCharacter(NPC_GenerateCharacter("SharlieEpilog_Bernard", "Mercen_21", "man", "man", 5, FRANCE, -1, false, "citizen"));
	sld.name = GetCharacterName("Bernard");
	sld.lastname = GetCharacterName("Throckmorton");
	sld.dialog.filename = "Quest\Sharlie\Epilog.c";
	sld.dialog.currentnode = "SharlieEpilog_Bernard_1";
	ChangeCharacterAddressGroup(sld, "Quest_Campus", "goto", "goto6");
	LAi_SetCitizenType(sld);
	
	if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
	{
		//Гамбитник
		if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel"))
		{
			ref chr = CharacterFromID("Knippel");
			chr.dialog.filename = "Quest\Sharlie\Epilog.c";
			chr.dialog.currentnode = "SharlieEpilog_Knippel_1";
		}
		if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway"))
		{
			chr = CharacterFromID("Longway");
			chr.dialog.filename = "Quest\Sharlie\Epilog.c";
			chr.dialog.currentnode = "SharlieEpilog_Longway_1";
		}
		if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
		{
			chr = CharacterFromID("Tonzag");
			chr.dialog.filename = "Quest\Sharlie\Epilog.c";
			chr.dialog.currentnode = "SharlieEpilog_Tonzag_1";
		}
		ChangeCharacterAddressGroup(chr, "Quest_Deck_Medium", "rld", "loc3");
		LAi_SetStayType(chr);
	}
	
	//Брашпиль
	sld = GetCharacter(NPC_GenerateCharacter("SharlieEpilog_Windlass", "windlass", "man", "windlass", 15, FRANCE, -1, false, "quest"));
    sld.name = "";
    sld.lastname = "";
	ChangeCharacterAddressGroup(sld, "Quest_Ship_deck_Medium_trade", "quest", "quest5");
	LAi_CharacterDisableDialog(sld);
	
	//Остальное
	chrDisableReloadToLocation = false;
	bGameMenuStart = false;
	pchar.GenQuest.BlockTalkSelf = true;
	pchar.GenQuest.CannotWait = true;
	bDisableCharacterMenu = false;
	InterfaceStates.Buttons.Save.enable = true;
	DeleteAttribute(pchar, "questTemp.NoFast");
	
	// активируемые объекты на корабле
	sld = &Locations[FindLocation("Quest_Ship_deck_Medium_trade")];
	SetLocatorEvent(sld.id, "event1", "SharlieEpilog_windlass_1");
	
	// добавляем в трюм куча золота
	ref sld = &Locations[FindLocation("Quest_Deck")];
	//Models
	sld.filespath.models = "locations\decks\inside_hold_epilogue";
	//Always
	sld.models.always.main = "inside_hold_epilogue";
	sld.models.always.parts = "inside_hold_epilogue_parts";
	sld.models.always.outside = "inside_hold_epilogue_outside";
	sld.models.always.locators = "inside_hold_epilogue_locators";
	if (CheckAttribute(pchar, "questTemp.SharlieEpilog_gold_S")) // cокровища (мало)
	{
		sld.models.always.gold = "inside_hold_epilogue_gold_S";
		sld.models.day.charactersPatch = "inside_hold_epilogue_patch_S";
		sld.models.night.charactersPatch = "inside_hold_epilogue_patch_S";
	}
	if (CheckAttribute(pchar, "questTemp.SharlieEpilog_gold_M")) // cокровища (средне)
	{
		sld.models.always.gold = "inside_hold_epilogue_gold_M";
		sld.models.day.charactersPatch = "inside_hold_epilogue_patch_M";
		sld.models.night.charactersPatch = "inside_hold_epilogue_patch_M";
	}
	if (CheckAttribute(pchar, "questTemp.SharlieEpilog_gold_L")) // cокровища (много)
	{
		sld.models.always.gold = "inside_hold_epilogue_gold_L";
		sld.models.day.charactersPatch = "inside_hold_epilogue_patch_L";
		sld.models.night.charactersPatch = "inside_hold_epilogue_patch_L";
	}
	sld.models.always.rays = "inside_hold_epilogue_rays"; // лучи
	sld.models.always.rays.uvslide.v0 = 0.08;
	sld.models.always.rays.uvslide.v1 = 0.0;
	sld.models.always.rays.tech = "LocationWaterFall";
	sld.models.always.rays.level = 99950;
	sld.models.always.camcollider = "inside_hold_epilogue_camcollider";
	sld.models.always.camcollider.tech = "LocationWindows";
	sld.models.always.camcollider.level = 65539;
	//Day
	sld.models.day.fonar = "inside_hold_epilogue_fn"; // тоже ночные
	//Night
	sld.models.night.fonar = "inside_hold_epilogue_fn";
	
	// катсцена в трюме
	SetFunctionLocationCondition("SharlieEpilog_GoldInTheDeck", "Quest_Deck", false);
}

void SharlieEpilog_MaryHelena_Animation(string qName)
{
	if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
	{
		sld = CharacterFromID("Helena");
		ChangeCharacterAddressGroup(sld, PChar.location, "quest", "quest10");
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "epilogue_1", "", -1.0);
        sld.chr_ai.tmpl.ignorecol = "";
	}

	if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
	{
		sld = CharacterFromID("Mary");
		ChangeCharacterAddressGroup(sld, PChar.location, "quest", "quest11");
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "epilogue_1", "", -1.0);
        sld.chr_ai.tmpl.ignorecol = "";
	}
	
	SetFunctionExitFromLocationCondition("SharlieEpilog_MaryHelena_Animation_cancel", PChar.location, false);
}

void SharlieEpilog_MaryHelena_Animation_cancel(string qName)
{
	SetFunctionLocationCondition("SharlieEpilog_MaryHelena_Animation", "Quest_Ship_deck_Medium_trade", false);
}

void SharlieEpilog_windlass_1() //активация брашпиля
{
	StartQuestMovie(true, false, true);
	LAi_SetStayType(pchar);
	LAi_FadeEx(1.0, 0.3, 1.0, "SharlieEpilog_windlass_1_1", "", "");
	pchar.questTemp.SharlieEpilog_ActivateWindlass = true;
	pchar.questTemp.NoFast = true;
	
	//
	sld = CharacterFromID("SharlieEpilog_Alonso");
	ChangeCharacterAddressGroup(sld, pchar.location, "quest", "quest1");
	TeleportCharacterToPosAy(sld, -10.59, 2.50, -1.35, 1.50);
	
	sld = CharacterFromID("SharlieEpilog_HighSailor");
	TeleportCharacterToPosAy(sld, -8.59, 2.50, -1.35, -1.50);
}

void SharlieEpilog_windlass_1_1(string qName)
{
	locCameraFromToPos(-13.04, 9.19, -15.04, true, -10.22, 6.91, -17.96);
	TeleportCharacterToPosAy(pchar, -7.36, 5.37, -15.81, 3.00);
	LAi_SetActorType(pchar);
	LAi_ActorFollow(pchar, CharacterFromID("SharlieEpilog_Pikar"), "SharlieEpilog_windlass_1_2", -1);
}

void SharlieEpilog_windlass_1_2()
{
	LAi_FadeEx(1.0, 0.3, 1.0, "SharlieEpilog_windlass_2", "", "");
}

void SharlieEpilog_windlass_2(string qName)
{
	LAi_SetStayType(pchar);
	TeleportCharacterToPosAy(pchar, -8.60, 7.80, -20.41, -1.50);
	sld = CharacterFromID("SharlieEpilog_Pikar");
	sld.dialog.filename = "Quest\Sharlie\Epilog.c";
	sld.dialog.currentnode = "SharlieEpilog_windlass_1";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 0, 0);
}

void SharlieEpilog_windlass_3()
{
	locCameraSleep(true);
	LAi_FadeEx(1.0, 0.0, 1.0, "SharlieEpilog_windlass_4", "", "");
}

void SharlieEpilog_windlass_4(string qName)
{
	locCameraSleep(false);
	locCameraFromToPos(-10.44, 4.86, -7.03, true, -8.82, 2.37, -9.96);
	
	
	sld = GetCharacter(CreateCharacterClone(CharacterFromID("SharlieEpilog_Bernard"), 0));
	sld.id = "SharlieEpilog_Bernard_Clone";
	ChangeCharacterAddressGroup(sld, "Quest_Ship_deck_Medium_trade", "goto", "goto1");
	TeleportCharacterToPosAy(sld, -7.30, 2.94, -10.69, 3.00);
	LAi_SetActorType(sld);
	LAi_ActorAnimation(sld, "Breaks the windlass", "1", 15);
	
	DoQuestFunctionDelay("SharlieEpilog_windlass_5", 5.0);
}

void SharlieEpilog_windlass_5(string qName)
{
	locCameraFromToPos(-6.25, 4.52, -7.54, true, -8.99, 1.94, -11.17);
	DoQuestFunctionDelay("SharlieEpilog_windlass_6", 1.00);
}

void SharlieEpilog_windlass_6(string qName)
{
	sld = CharacterFromID("SharlieEpilog_Windlass");
	LAi_SetActorType(sld);
	LAi_ActorAnimation(sld, "rotate_1", "", 15);
	DoQuestFunctionDelay("SharlieEpilog_windlass_7", 1.00);
	PlaySound("Ship\windlass_activate.wav");
}

void SharlieEpilog_windlass_7(string qName)
{
	locCameraFlyToPositionLookToPoint(-6.25, 4.52, -7.54, -7.88, 3.84, -9.70, -8.99, 3.38, -11.17, -1, 3500/GetDeltaTime());
	Pchar.FuncCameraFly = "SharlieEpilog_windlass_8";
}

void SharlieEpilog_windlass_8()
{
	locCameraSleep(true);
	LAi_FadeEx(1.0, 1.0, 1.0, "", "SharlieEpilog_windlass_9", "");
}

void SharlieEpilog_windlass_9(string qName)
{
	locCameraSleep(false);
	sld = &Locations[FindLocation("Quest_Ship_deck_Medium_trade")];
	DelLocatorEvent(sld.id, "event1");
	
	sld = CharacterFromID("SharlieEpilog_Windlass");
	LAi_SetActorType(sld);
	LAi_ActorAnimation(sld, "idle_1", "1", 5);
	
	sld = CharacterFromID("SharlieEpilog_Bernard_Clone");
	TeleportCharacterToPosAy(sld, -9.22, 7.90, -21.97, 0.00);
	
	sld = CharacterFromID("SharlieEpilog_Pikar");
	sld.dialog.filename = "Quest\Sharlie\Epilog.c";
	sld.dialog.currentnode = "SharlieEpilog_windlass_3";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 0, 0);
}

void SharlieEpilog_windlass_9_1()
{
	locCameraFromToPos(-7.57, 9.68, -21.21, true, -9.79, 7.76, -20.01);
	CharacterTurnByChr(CharacterFromID("SharlieEpilog_Pikar"), pchar);
	CharacterTurnByChr(pchar, CharacterFromID("SharlieEpilog_Pikar"));
	sld = CharacterFromID("SharlieEpilog_Bernard_Clone");
	ChangeCharacterAddressGroup(sld, "none", "", "");
}

void SharlieEpilog_windlass_10()
{
	locCameraFromToPos(-9.34, 8.28, -16.03, true, -9.33, 7.32, -20.48);
	CharacterTurnByChr(pchar, CharacterFromID("SharlieEpilog_HighSailor"));
	CharacterTurnByChr(CharacterFromID("SharlieEpilog_Pikar"), CharacterFromID("SharlieEpilog_HighSailor"));
}

void SharlieEpilog_AlonsoTrollingHighSailor_camera_1()
{
	locCameraFromToPos(-9.68, 4.36, -1.61, true, -8.22, 2.70, -1.25);
}

void SharlieEpilog_AlonsoTrollingHighSailor_camera_2()
{
	locCameraFromToPos(-9.48, 4.30, -1.74, true, -10.45, 2.67, -1.33);
}

void SharlieEpilog_AlonsoTrollingHighSailor_1()
{
	// sld = CharacterFromID("SharlieEpilog_HighSailor");
	sld = GetCharacter(NPC_GenerateCharacter("Invisible", "Invisible", "man", "man", 5, FRANCE, 0, false, "citizen"));
	ChangeCharacterAddressGroup(sld, "Quest_Ship_deck_Medium_trade", "goto", "goto1");
	TeleportCharacterToPos(sld, 1000.00, 50.00, 1000.00);
	sld.name = "";
	sld.lastname = "";
	sld.dialog.filename = "Quest\Sharlie\Epilog.c";
	sld.dialog.currentnode = "SharlieEpilog_AlonsoTrollingHighSailor_2";
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, Pchar, "", -1);
}

void SharlieEpilog_AlonsoTrollingHighSailor_2()
{
	locCameraSleep(true);
	LAi_FadeEx(1.0, 0.5, 1.0, "SharlieEpilog_AlonsoTrollingHighSailor_3", "SharlieEpilog_AlonsoTrollingHighSailor_4", "");
}

void SharlieEpilog_AlonsoTrollingHighSailor_3(string qName)
{
	sld = CharacterFromID("SharlieEpilog_HighSailor");
	ChangeCharacterAddressGroup(sld, "Quest_Ship_deck_Medium_trade", "reload", "reload_gundeck");
	LAi_SetStayType(sld);
	
	TeleportCharacterToPosAy(pchar, -9.48, 2.50, -2.39, -0.75);
}

void SharlieEpilog_AlonsoTrollingHighSailor_4(string qName)
{
	locCameraSleep(false);
	sld = CharacterFromID("SharlieEpilog_Alonso");
	sld.dialog.filename = "Quest\Sharlie\Epilog.c";
	sld.dialog.currentnode = "SharlieEpilog_AlonsoTrollingHighSailor_9";
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, Pchar, "", -1);
}

void SharlieEpilog_AlonsoTrollingHighSailor_5()
{
	locCameraSleep(true);
	LAi_FadeEx(1.0, 0.5, 1.0, "SharlieEpilog_AlonsoTrollingHighSailor_6", "SharlieEpilog_AlonsoTrollingHighSailor_7", "");
}

void SharlieEpilog_AlonsoTrollingHighSailor_6(string qName)
{
	sld = CharacterFromID("SharlieEpilog_Alonso");
	ChangeCharacterAddressGroup(sld, "none", "", "");
}

void SharlieEpilog_AlonsoTrollingHighSailor_7(string qName)
{
	EndQuestMovie();
	locCameraSleep(false);
	LAi_SetPlayerType(pchar);
	locCameraFollowEx(true);
	
	sld = CharacterFromID("SharlieEpilog_Pikar");
	sld.dialog.filename = "Quest\Sharlie\Epilog.c";
	sld.dialog.currentnode = "SharlieEpilog_PikarOnUliss";
	ChangeCharacterAddressGroup(sld, PChar.location, "quest", "quest3");
	LAi_SetStayType(sld);
}

void SharlieEpilog_GoldInTheDeck_music(string qName)
{
	SetMusic("music_Gorod_02_sd2");
}

void SharlieEpilog_GoldInTheDeck(string qName)
{
	ResetSound();
	StartQuestMovie(true, false, true);
	locCameraFromToPos(1.63, 7.51, -3.24, true, 0.69, 5.58, -5.60);
	LAi_FadeEx(0.0, 3.0, 1.0, "", "SharlieEpilog_GoldInTheDeck_0_1", "");
	LAi_SetActorType(pchar);
	
	sld = CharacterFromID("SharlieEpilog_Alonso");
	ChangeCharacterAddressGroup(sld, "Quest_Deck", "quest", "quest4");
	DoQuestFunctionDelay("SharlieEpilog_GoldInTheDeck_music", 2.0);
}

void SharlieEpilog_GoldInTheDeck_0_1(string qName)
{
	LAi_SetActorType(pchar);
	LAi_ActorGoToLocator(pchar, "quest", "quest4", "", -1);
	DoQuestFunctionDelay("SharlieEpilog_GoldInTheDeck_0_2", 2.0);
}

void SharlieEpilog_GoldInTheDeck_0_2(string qName)
{
	LAi_FadeEx(1.0, 0.5, 1.0, "SharlieEpilog_GoldInTheDeck_0_3", "", "");
}

void SharlieEpilog_GoldInTheDeck_0_3(string qName)
{
	// StartQuestMovie(true, false, true);
	// LAi_FadeEx(0.0, 1.5, 1.0, "", "SharlieEpilog_GoldInTheDeck_1", "");
	chrDisableReloadToLocation = true;
	LAi_SetStayType(pchar);
	
	ChangeCharacterAddressGroup(pchar, "Quest_Deck", "reload", "reload1");
	TeleportCharacterToPos(pchar, -0.38, 5.60, 9.85);
	sld = CharacterFromID("SharlieEpilog_Alonso");
	ChangeCharacterAddressGroup(sld, "Quest_Deck", "reload", "reload1");
	LAi_SetActorType(sld);
	TeleportCharacterToPos(sld, -0.38, 5.60, 8.85);
	
	ref chr = GetCharacter(CreateCharacterClone(pchar, 0));
	chr.id = "Sharle_Clone";
	
	ref sld = GetCharacter(CreateCharacterClone(CharacterFromID("SharlieEpilog_Alonso"), 0));
	sld.id = "Alonso_Clone";
	
	chr = CharacterFromID("Sharle_Clone");
	LAi_SetActorType(chr);
	ChangeCharacterAddressGroup(chr, "Quest_Deck", "quest", "quest1");
	TeleportCharacterToLocatorIgnoreCollision(chr, "quest", "quest1");
	sld = CharacterFromID("Alonso_Clone");
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, "Quest_Deck", "quest", "quest2");
	TeleportCharacterToLocatorIgnoreCollision(sld, "quest", "quest2");
	
	//////
	// StartQuestMovie(true, false, true);
	// LAi_FadeEx(0.0, 1.5, 1.0, "", "SharlieEpilog_GoldInTheDeck_1", "");
	// chrDisableReloadToLocation = true;
	
	// sld = CharacterFromID("SharlieEpilog_Alonso");
	// LAi_SetStayType(pchar);
	// LAi_SetActorType(sld);
	// TeleportCharacterToLocatorIgnoreCollision(PChar, "quest", "quest1");
	// ChangeCharacterAddressGroup(sld, "Quest_Deck", "quest", "quest2");
	// TeleportCharacterToLocatorIgnoreCollision(sld, "quest", "quest2");
	
	locCameraFromToPos(0.04, 7.95, -6.26, true, 0.66, 5.36, -8.94);
	sld = CharacterFromID("SharlieEpilog_Alonso");
	sld.dialog.filename = "Quest\Sharlie\Epilog.c";
	sld.dialog.currentnode = "SharlieEpilog_Alonso_11";
	LAi_ActorDialog(sld, pchar, "", 0, 0);
}

void SharlieEpilog_GoldInTheDeck_1_1()
{
	ref chr = CharacterFromID("Sharle_Clone");
	LAi_SetActorType(chr);
	LAi_ActorAnimation(chr, "gold_1", "", -1);
	CharacterTurnByLoc(chr, "quest", "quest1");
	ref sld = CharacterFromID("Alonso_Clone");
	LAi_SetActorType(sld );
	LAi_ActorAnimation(sld , "gold_1", "", -1);
	CharacterTurnByLoc(sld , "quest", "quest2");
}

void SharlieEpilog_GoldInTheDeck_2()
{
	locCameraFromToPos(-0.03, 7.85, -7.25, true, 0.52, 5.52, -8.51);
	ref chr = CharacterFromID("Sharle_Clone");
	ref sld = CharacterFromID("Alonso_Clone");
	SyncPlaybackDlt(chr, sld);
	LAi_SetActorType(chr);
	LAi_SetActorType(sld);
	LAi_ActorAnimation(chr, "gold_2", "", 100.0);
	LAi_ActorAnimation(sld, "gold_2", "", 100.0);
	DoQuestFunctionDelay("SharlieEpilog_GoldInTheDeck_3", 3.5);
}

void SharlieEpilog_GoldInTheDeck_3(string qName)
{
	locCameraFromToPos(-1.42, 7.80, -8.62, true, -0.18, 5.69, -9.05);
	DoQuestFunctionDelay("SharlieEpilog_GoldInTheDeck_4", 13.0);
	
	LAi_SetStayType(pchar);
	sld = CharacterFromID("SharlieEpilog_Alonso");
	sld.dialog.filename = "Quest\Sharlie\Epilog.c";
	sld.dialog.currentnode = "SharlieEpilog_Alonso_21";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 0, 0);
}

void SharlieEpilog_GoldInTheDeck_4(string qName)
{
	ref chr = CharacterFromID("Sharle_Clone");
	LAi_ActorAnimation(chr, "gold_3", "", -1);
	CharacterTurnByLoc(chr, "quest", "quest1");
	ref sld = CharacterFromID("Alonso_Clone");
	LAi_ActorAnimation(sld, "gold_3", "", -1);
	CharacterTurnByLoc(sld, "quest", "quest2");
}

void SharlieEpilog_GoldInTheDeck_7()
{
	Event("QuestDelayExit","sl", "", 0);
	locCameraFromToPos(-0.00, 7.75, -7.47, true, 0.55, 5.41, -8.82);
	ref chr = CharacterFromID("Sharle_Clone");
	ref sld = CharacterFromID("Alonso_Clone");
	SyncPlaybackDlt(chr, sld);
	LAi_SetActorType(chr);
	LAi_SetActorType(sld);
	LAi_ActorAnimation(chr, "gold_4", "", 100.0);
	LAi_ActorAnimation(sld, "gold_4", "", 100.0);
	DoQuestFunctionDelay("SharlieEpilog_GoldInTheDeck_8", 6.5);
}

void SharlieEpilog_GoldInTheDeck_8(string qName)
{
	LAi_FadeEx(1.0, 0.3, 1.0, "SharlieEpilog_GoldInTheDeck_9", "", "");
}

void SharlieEpilog_GoldInTheDeck_9(string qName)
{
	LAi_SetStayType(pchar);
	sld = CharacterFromID("SharlieEpilog_Alonso");
	sld.dialog.filename = "Quest\Sharlie\Epilog.c";
	sld.dialog.currentnode = "SharlieEpilog_Alonso_31";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 0, 0);
}

void SharlieEpilog_GoldInTheDeck_10()
{
	ref chr = CharacterFromID("Sharle_Clone");
	LAi_SetActorType(chr);
	LAi_ActorAnimation(chr, "gold_5", "", -1);
	CharacterTurnByLoc(chr, "quest", "quest1");
	ref sld = CharacterFromID("Alonso_Clone");
	LAi_SetActorType(sld);
	LAi_ActorAnimation(sld, "gold_5", "", -1);
	CharacterTurnByLoc(sld, "quest", "quest2");
	locCameraFromToPos(0.80, 8.00, -7.57, true, 0.82, 5.62, -8.52);
}

void SharlieEpilog_GoldInTheDeck_11()
{
	LAi_FadeEx(1.0, 0.5, 1.0, "SharlieEpilog_GoldInTheDeck_12", "SharlieEpilog_GoldInTheDeck_13", "");
}

void SharlieEpilog_GoldInTheDeck_12(string qName)
{
	ref chr = CharacterFromID("Sharle_Clone");
	ChangeCharacterAddressGroup(chr, "none", "", "");
	ref sld = CharacterFromID("Alonso_Clone");
	ChangeCharacterAddressGroup(sld, "none", "", "");
}

void SharlieEpilog_GoldInTheDeck_13(string qName)
{
	SetMusic("music_Quest_Deck");
	SetSoundScheme("deck");
	EndQuestMovie();
	locCameraSleep(false);
	chrDisableReloadToLocation = false;
	LAi_SetPlayerType(pchar);
	ChangeCharacterAddressGroup(pchar, PChar.location, "quest", "quest1");
	locCameraFollowEx(true);
	
	ref sld = CharacterFromID("SharlieEpilog_Alonso");
	LAi_SetActorType(sld);
	// LAi_CharacterDisableDialog(sld);
	ChangeCharacterAddressGroup(sld, "none", "", "");
	
	// теперь доступна катсцена в каюте капитана
	if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
	{
		SetFunctionLocationCondition("SharlieEpilog_LoveInCabin", "Quest_Ship_deck_Medium_trade", false);
	}
	
	//Тичингиту сторожит золото
	if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
	{
		ref chr = CharacterFromID("Tichingitu");
		chr.dialog.filename = "Quest\Sharlie\Epilog.c";
		chr.dialog.currentnode = "SharlieEpilog_Tichingitu_21";
		ChangeCharacterAddressGroup(chr, "Quest_Deck", "quest", "quest4");
		LAi_SetStayType(chr);
		return;
	}
	//Гамбитник
	if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel"))
	{
		chr = CharacterFromID("Knippel");
		chr.dialog.filename = "Quest\Sharlie\Epilog.c";
		chr.dialog.currentnode = "SharlieEpilog_Knippel_21";
	}
	if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway"))
	{
		chr = CharacterFromID("Longway");
		chr.dialog.filename = "Quest\Sharlie\Epilog.c";
		chr.dialog.currentnode = "SharlieEpilog_Longway_21";
	}
	if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
	{
		chr = CharacterFromID("Tonzag");
		chr.dialog.filename = "Quest\Sharlie\Epilog.c";
		chr.dialog.currentnode = "SharlieEpilog_Tonzag_21";
	}
	ChangeCharacterAddressGroup(chr, "Quest_Deck", "quest", "quest4");
	LAi_SetStayType(chr);
}

void SharlieEpilog_LoveInCabin(string qName)
{
	if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
	{
		sld = CharacterFromID("Helena");
		sld.dialog.filename = "Quest\Sharlie\Epilog.c";
		sld.dialog.currentnode = "SharlieEpilog_Helena_11";
	}
	if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
	{
		sld = CharacterFromID("Mary");
		sld.dialog.filename = "Quest\Sharlie\Epilog.c";
		sld.dialog.currentnode = "SharlieEpilog_Mary_11";
	}
	ChangeCharacterAddressGroup(sld, "Quest_Ship_deck_Medium_trade", "quest", "quest10");
	LAi_SetStayType(sld);
	AddLandQuestMark(sld, "questmarkmain");
}

void SharlieEpilog_LoveInCabin_1()
{
	DoFunctionReloadToLocation("Quest_Cabin_Medium", "reload", "reload1", "SharlieEpilog_LoveInCabin_2");
}

void SharlieEpilog_LoveInCabin_2()
{
	StartQuestMovie(true, false, true);
	LAi_FadeEx(0.0, 1.5, 1.0, "", "SharlieEpilog_LoveInCabin_3", "");
	chrDisableReloadToLocation = true;
	LAi_SetStayType(pchar);
}

void SharlieEpilog_LoveInCabin_3(string qName)
{	
	if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
	{
		sld = CharacterFromID("Helena");
	}
	if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
	{
		sld = CharacterFromID("Mary");
	}
	IgnoreCollision(sld, true);
	SyncPlaybackDlt(PChar, sld);
	ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
	TeleportCharacterToLocatorIgnoreCollision(pchar, "quest", "kiss2");
	TeleportCharacterToLocatorIgnoreCollision(sld, "quest", "kiss1");
	LAi_SetActorType(pchar);
	LAi_SetActorType(sld);
	LAi_ActorAnimation(pchar, "kiss", "1", 8.5);
	LAi_ActorAnimation(sld, "kiss", "1", 8.5);
	CharacterTurnByChr(pchar, sld);
	CharacterTurnByChr(sld, pchar);
	locCameraFromToPos(-2.32, 6.81, -1.75, true, -1.65, 5.00, 0.49);
	DoQuestFunctionDelay("SharlieEpilog_LoveInCabin_4", 4.5);
	DoQuestFunctionDelay("SharlieEpilog_LoveInCabin_5", 8.5);
}

void SharlieEpilog_LoveInCabin_4(string qName)
{	
	locCameraFromToPos(-4.26, 6.55, 1.19, true, -0.89, 4.65, -0.20);
}

void SharlieEpilog_LoveInCabin_5(string qName)
{	
	ResetSound();
	SetLaunchFrameFormParam("", "Run_Function", 0, 15);
	SetLaunchFrameRunFunctionParam("SharlieEpilog_LoveInCabin_5_1", 0.0);
	SetLaunchFrameFormPic("loading\inside\censored1.tga");
	if(bSFW) PlayStereoSound("sex\sex_sfw.wav");
	else PlayStereoSound("sex\sex" + (rand(14) + 1) + ".wav");
	LaunchFrameForm();
	WaitDate("", 0, 0, 0, 0, 30);
}

void SharlieEpilog_LoveInCabin_5_1()
{	
	LAi_SetStayType(pchar);
	if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
	{
		sld = CharacterFromID("Helena");
		sld.dialog.filename = "Quest\Sharlie\Epilog.c";
		sld.dialog.currentnode = "SharlieEpilog_Helena_21";
	}
	if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
	{
		sld = CharacterFromID("Mary");
		sld.dialog.filename = "Quest\Sharlie\Epilog.c";
		sld.dialog.currentnode = "SharlieEpilog_Mary_21";
	}
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, Pchar, "", -1);
}

void SharlieEpilog_LoveInCabin_6()
{	
	if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
	{
		sld = CharacterFromID("Helena");
	}
	if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
	{
		sld = CharacterFromID("Mary");
	}
	SyncPlaybackDlt(PChar, sld);
	LAi_SetActorType(pchar);
	LAi_SetActorType(sld);
	LAi_ActorAnimation(pchar, "kiss", "1", 8.5);
	LAi_ActorAnimation(sld, "kiss", "1", 8.5);
	SharlieEpilog_LoveInCabin_CameraKiss();
	DoQuestFunctionDelay("SharlieEpilog_LoveInCabin_7", 3.0);
}

void SharlieEpilog_LoveInCabin_CameraDialog()
{	
	locCameraFromToPos(-0.80, 6.84, -0.96, true, -2.35, 4.92, 0.13);
}

void SharlieEpilog_LoveInCabin_CameraKiss()
{	
	locCameraFromToPos(-0.69, 6.81, 0.26, true, -2.02, 5.00, -0.77);
}

void SharlieEpilog_LoveInCabin_7(string qName)
{	
	LAi_FadeEx(1.0, 0.3, 1.0, "SharlieEpilog_LoveInCabin_8", "", "");
}

void SharlieEpilog_LoveInCabin_8(string qName)
{	
	LAi_SetStayType(pchar);
	if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
	{
		sld = CharacterFromID("Helena");
		sld.dialog.filename = "Quest\Sharlie\Epilog.c";
		sld.dialog.currentnode = "SharlieEpilog_Helena_31";
	}
	if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
	{
		sld = CharacterFromID("Mary");
		sld.dialog.filename = "Quest\Sharlie\Epilog.c";
		sld.dialog.currentnode = "SharlieEpilog_Mary_31";
	}
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, Pchar, "", -1);
}

void SharlieEpilog_LoveInCabin_9()
{	
	locCameraFromToPos(-3.74, 6.92, 0.30, true, -2.63, 5.19, 0.02);
	
	if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
	{
		sld = CharacterFromID("Helena");
	}
	if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
	{
		sld = CharacterFromID("Mary");
	}
	SyncPlaybackDlt(PChar, sld);
	LAi_SetActorType(pchar);
	LAi_SetActorType(sld);
	LAi_ActorAnimation(pchar, "kiss", "1", 8.5);
	LAi_ActorAnimation(sld, "kiss", "1", 8.5);
	
	DoQuestFunctionDelay("SharlieEpilog_LoveInCabin_10", 1.5);
}

void SharlieEpilog_LoveInCabin_10(string qName)
{	
	sld = characterFromID("SharlieEpilog_Pikar");
	ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "rld", "aloc1", "", -1);
	
	DoQuestFunctionDelay("SharlieEpilog_LoveInCabin_11", 3.0);
}

void SharlieEpilog_LoveInCabin_11(string qName)
{	
	LAi_FadeEx(1.0, 0.3, 1.0, "SharlieEpilog_LoveInCabin_12", "", "");
}

void SharlieEpilog_LoveInCabin_12(string qName)
{	
	LAi_SetStayType(pchar);
	sld = characterFromID("SharlieEpilog_Pikar");
	sld.dialog.filename = "Quest\Sharlie\Epilog.c";
	sld.dialog.currentnode = "SharlieEpilog_PikarInCabin_1";
	TeleportCharacterToPosAy(sld, -0.40, 5.00, -0.67, -1.50);
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, Pchar, "", -1);
	
	if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
	{
		sld = CharacterFromID("Helena");
	}
	if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
	{
		sld = CharacterFromID("Mary");
	}
	LAi_SetActorType(sld);
	LAi_type_actor_Reset(sld);
	CharacterTurnByChr(sld, characterFromID("SharlieEpilog_Pikar"));
}

void SharlieEpilog_PikarInCabin_camera_1()
{	
	locCameraFromToPos(-0.10, 6.96, 0.86, true, -0.58, 5.29, 0.21);
}

void SharlieEpilog_PikarInCabin_camera_2()
{	
	locCameraFromToPos(-2.95, 6.93, -1.34, true, -1.64, 5.14, -0.93);
}

void SharlieEpilog_LoveInCabin_13()
{	
	locCameraSleep(true);
	ref chr = characterFromID("SharlieEpilog_Pikar");
	LAi_SetActorType(chr);
	LAi_ActorGoToLocation(chr, "reload", "reload1", "Quest_Ship_deck_Medium_trade", "quest", "quest3", "SharlieEpilog_LoveInCabin_15", 5);
	
	if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
	{
		sld = CharacterFromID("Helena");
	}
	if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
	{
		sld = CharacterFromID("Mary");
	}
	CharacterTurnByChr(sld, pchar);
	CharacterTurnByChr(pchar, sld);
	DoQuestFunctionDelay("SharlieEpilog_LoveInCabin_14", 1.0);
}

void SharlieEpilog_LoveInCabin_14(string qName)
{	
	locCameraSleep(false);
	locCameraFromToPos(-3.74, 6.92, 0.30, true, -2.63, 5.19, 0.02);
	
	if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
	{
		sld = CharacterFromID("Helena");
	}
	if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
	{
		sld = CharacterFromID("Mary");
	}
	SyncPlaybackDlt(PChar, sld);
	LAi_SetActorType(pchar);
	LAi_SetActorType(sld);
	LAi_ActorAnimation(pchar, "kiss", "1", 8.5);
	LAi_ActorAnimation(sld, "kiss", "1", 8.5);
}

void SharlieEpilog_LoveInCabin_15()
{	
	ResetSound();
	SetLaunchFrameFormParam("", "Run_Function", 0, 15);
	SetLaunchFrameRunFunctionParam("SharlieEpilog_LoveInCabin_16", 0.0);
	SetLaunchFrameFormPic("loading\inside\censored1.tga");
	if(bSFW) PlayStereoSound("sex\sex_sfw.wav");
	else PlayStereoSound("sex\sex" + (rand(14) + 1) + ".wav");
	LaunchFrameForm();
	WaitDate("", 0, 0, 0, 0, 30);
}

void SharlieEpilog_LoveInCabin_16()
{	
	LAi_FadeEx(0.0, 0.5, 1.0, "", "SharlieEpilog_LoveInCabin_17", "");
}

void SharlieEpilog_LoveInCabin_17(string qName)
{	
	EndQuestMovie();
	LAi_SetPlayerType(pchar);
	ChangeCharacterAddressGroup(pchar, PChar.location, "quest", "lay2");
	locCameraFollowEx(true);
	chrDisableReloadToLocation = false;
	
	if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
	{
		sld = CharacterFromID("Helena");
	}
	if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
	{
		sld = CharacterFromID("Mary");
	}
	ChangeCharacterAddressGroup(sld, "none", "", "");
	
	sld = characterFromID("SharlieEpilog_Pikar");
	sld.dialog.filename = "Quest\Sharlie\Epilog.c";
	sld.dialog.currentnode = "SharlieEpilog_PikarZalp_1";
	LAi_SetStayType(sld);
	AddLandQuestMark(sld, "questmarkmain");
}

void SharlieEpilog_ZalpInSea(string qName)
{	
	EndBattleLandInterface();
	locCameraSleep(true);
	LAi_FadeEx(1.0, 4.0, 0.0, "SharlieEpilog_ZalpInSea_2", "SharlieEpilog_ZalpInSea_3", "");
}

void SharlieEpilog_ZalpInSea_2(string qName)
{	
	PlaySound("Sea Battles_01\Cannon_Fire_festive.wav");
	PlaySound("PEOPLE\victory-01.wav");
}

void SharlieEpilog_ZalpInSea_3(string qName)
{	
	SharlieEpilog_InEstateDeMonpe();
}

void SharlieEpilog_InEstateDeMonpe()  // в поместье де Монпе
{
	if(IsEntity(&LAi_QuestFader)) DeleteClass(&LAi_QuestFader);
	SetLaunchFrameFormParam(GetConvertStr("Frame_MonthPassed_2", "Frame.txt")+ NewStr() +GetConvertStr("DeMonpe_Estate", "LocLables.txt")+", "+GetConvertStr("France", "LocLables.txt")+".", "Run_Function", 0, 4.0);
	SetLaunchFrameRunFunctionParam("SharlieEpilog_InEstateDeMonpe_1", 0.0);
	LaunchFrameForm();
}

void SharlieEpilog_InEstateDeMonpe_music(string qName)
{
	SetMusic("music_MainMenu_coas");
}

void SharlieEpilog_InEstateDeMonpe_1()
{
	SetCurrentTime(17, 00);
	DoFunctionReloadToLocation("EstateDM1", "goto", "stay1", "SharlieEpilog_InEstateDeMonpe_2");
}

void SharlieEpilog_InEstateDeMonpe_2()
{
	ResetSound();
	StartQuestMovie(true, false, true);
	LAi_FadeEx(0.0, 3.0, 1.0, "", "SharlieEpilog_InEstateDeMonpe_3", "");
	locCameraFlyToPositionLookToPoint(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 100/GetDeltaTime());
	DoQuestFunctionDelay("SharlieEpilog_InEstateDeMonpe_music", 2.0);
	CreateSnow();
	
	ref sld = GetCharacter(NPC_GenerateCharacter("HenriDeMonper", "Dad", "man", "man", 30, FRANCE, -1, false, "quest"));
	sld.name = GetCharacterName("Henri");
	sld.lastname = GetCharacterName("de Monper");
	ChangeCharacterAddressGroup(sld, "EstateDM1", "goto", "goto4");
	
	LAi_SetActorType(pchar);
	CharacterTurnByChr(pchar, sld);
	
	//рядом стоит жена
	if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
	{
		sld = CharacterFromID("Helena");
		ChangeCharacterAddressGroup(sld, "EstateDM1", "reload", "reload1");
		TeleportCharacterToPosAy(sld, -20.3, 6.00, -1.06, 1.50);
		LAi_SetActorType(sld);
		DelLandQuestMark(sld);
	}
	if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
	{
		sld = CharacterFromID("Mary");
		ChangeCharacterAddressGroup(sld, "EstateDM1", "reload", "reload1");
		TeleportCharacterToPosAy(sld, -20.3, 6.00, -1.06, 1.50);
		LAi_SetActorType(sld);
		DelLandQuestMark(sld);
	}
	
	//и сзади офицеры-гамбитники
	if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel"))
	{
		sld = CharacterFromID("Knippel");
		ChangeCharacterAddressGroup(sld, "EstateDM1", "reload", "reload1");
		TeleportCharacterToPosAy(sld, -21.4, 6.00, -1.70, 1.50);
		LAi_SetActorType(sld);
	}
	if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway"))
	{
		sld = CharacterFromID("Longway");
		ChangeCharacterAddressGroup(sld, "EstateDM1", "reload", "reload1");
		TeleportCharacterToPosAy(sld, -21.4, 6.00, -1.70, 1.50);
		LAi_SetActorType(sld);
	}
	if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
	{
		sld = CharacterFromID("Tonzag");
		ChangeCharacterAddressGroup(sld, "EstateDM1", "reload", "reload1");
		TeleportCharacterToPosAy(sld, -21.4, 6.00, -1.70, 1.50);
		LAi_SetActorType(sld);
	}
	
	//Тичингиту
	if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
	{
		sld = CharacterFromID("Tichingitu");
		ChangeCharacterAddressGroup(sld, "EstateDM1", "reload", "reload1");
		TeleportCharacterToPosAy(sld, -21.4, 6.00, 0.50, 1.50);
		LAi_SetActorType(sld);
	}
	
	//Алонсо
	if (!CharacterIsAlive("SharlieEpilog_Alonso"))
	{
		sld = GetCharacter(NPC_GenerateCharacter("SharlieEpilog_Alonso", "Alonso", "man", "Alonso", 5, FRANCE, -1, false, "pirate"));
		sld.name = GetCharacterName("Alonso");
		sld.lastname = "";
	}
	else
	{
		sld = CharacterFromID("SharlieEpilog_Alonso");
	}
	ChangeCharacterAddressGroup(sld, "EstateDM1", "reload", "reload1");
	TeleportCharacterToPosAy(sld, -21.4, 6.00, -0.60, 1.50);
	LAi_SetActorType(sld);
}

void SharlieEpilog_InEstateDeMonpe_3(string qName)
{
	locCameraFromToPos(-17.82, 7.91, -0.67, true, -19.18, 6.21, -0.64);
	DoQuestFunctionDelay("SharlieEpilog_InEstateDeMonpe_4", 3.0);
}

void SharlieEpilog_InEstateDeMonpe_4(string qName)
{
	locCameraFromToPos(-6.14, 7.61, -0.25, true, -3.98, 6.22, 0.68);
	DoQuestFunctionDelay("SharlieEpilog_InEstateDeMonpe_5", 3.0);
}

void SharlieEpilog_InEstateDeMonpe_5(string qName)
{
	LAi_ActorGoToLocator(pchar, "goto", "goto4", "", -1);
	locCameraFlyToPositionLookToPoint(-20.65, 7.74, -2.51, -2.45, 7.61, -4.76, -6.55, 7.00, 0.30, -1, 20000/GetDeltaTime());
	Pchar.FuncCameraFly = "CameraSleep";
	DoQuestFunctionDelay("SharlieEpilog_InEstateDeMonpe_6", 6.0);
}

void SharlieEpilog_InEstateDeMonpe_6(string qName)
{
	LAi_FadeEx(1.0, 0.1, 1.0, "SharlieEpilog_InEstateDeMonpe_7", "", "");
}

void SharlieEpilog_InEstateDeMonpe_7(string qName)
{
	locCameraSleep(false);
	locCameraResetState();
	sld = CharacterFromID("HenriDeMonper");
	IgnoreCollision(sld, true);
	SyncPlaybackDlt(PChar, sld);
	TeleportCharacterToPosAy(sld, -7.87, 6.00, 0.16, 1.50);
	LAi_SetActorType(sld);
	LAi_ActorAnimation(sld, "meeting_dad", "1", 30.0);
	
	TeleportCharacterToPosAy(pchar, -7.87, 6.00, 0.16, 1.50);
	LAi_SetActorType(pchar);
	LAi_ActorAnimation(pchar, "meeting_dad", "1", 30.0);
	
	locCameraFromToPos(-7.70, 7.92, 1.77, true, -6.55, 5.82, -0.34);
	DoQuestFunctionDelay("SharlieEpilog_InEstateDeMonpe_8", 7.0);
}

void SharlieEpilog_InEstateDeMonpe_8(string qName)
{
	LAi_FadeEx(1.0, 0.0, 1.0, "SharlieEpilog_InEstateDeMonpe_9", "", "");
}

void SharlieEpilog_InEstateDeMonpe_9(string qName)
{
	LAi_SetStayType(pchar);
	
	sld = CharacterFromID("HenriDeMonper");
	sld.dialog.filename = "Quest\Sharlie\Epilog.c";
	sld.dialog.currentnode = "SharlieEpilog_HenriDeMonper_1";
	TeleportCharacterToPosAy(sld, -6.87, 6.00, 0.16, -1.50);
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, Pchar, "", -1);
}

void SharlieEpilog_InEstateDeMonpe_10()
{
	locCameraSleep(true);
	LAi_FadeEx(1.0, 0.0, 1.0, "SharlieEpilog_InEstateDeMonpe_11", "", "");
}

void SharlieEpilog_InEstateDeMonpe_11(string qName)
{
	locCameraSleep(false);
	locCameraFlyToPositionLookToPoint(-13.89, 7.67, -0.37, -10.40, 7.67, -0.65, -7.20, 7.67, 0.33, -1.0, 2800/GetDeltaTime());
	Pchar.FuncCameraFly = "SharlieEpilog_InEstateDeMonpe_11_1";
	TeleportCharacterToPosAy(pchar, -6.87, 6.00, 1.16, -1.50);
	
	//рядом стоит жена
	if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
	{
		sld = CharacterFromID("Helena");
	}
	if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
	{
		sld = CharacterFromID("Mary");
	}
	TeleportCharacterToPosAy(sld, -12.87, 6.00, 0.16, 1.50);
	LAi_SetActorType(sld);
	LAi_ActorFollow(sld, CharacterFromID("HenriDeMonper"), "SharlieEpilog_InEstateDeMonpe_12", -1);
}

void SharlieEpilog_InEstateDeMonpe_11_1()
{
	locCameraFromToPos(-9.26, 7.84, 1.86, true, -6.74, 5.61, -0.17);
}

void SharlieEpilog_InEstateDeMonpe_11_2()
{
	locCameraFromToPos(-9.05, 7.68, -0.99, true, -7.64, 5.91, 0.07);
}

void SharlieEpilog_InEstateDeMonpe_12()
{
	DoQuestFunctionDelay("SharlieEpilog_InEstateDeMonpe_13", 1.5);
}

void SharlieEpilog_InEstateDeMonpe_13(string qName)
{
	sld = CharacterFromID("HenriDeMonper");
	sld.dialog.filename = "Quest\Sharlie\Epilog.c";
	sld.dialog.currentnode = "SharlieEpilog_HenriDeMonper_4";
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, Pchar, "", -1);
}

void SharlieEpilog_InEstateDeMonpe_14()
{
	if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
	{
		sld = CharacterFromID("Helena");
	}
	if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
	{
		sld = CharacterFromID("Mary");
	}
	sld.dialog.filename = "Quest\Sharlie\Epilog.c";
	sld.dialog.currentnode = "SharlieEpilog_HenriDeMonper_7";
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, Pchar, "", -1);
}

void SharlieEpilog_HenriDeMonper_Helena_1()
{
	sld = CharacterFromID("Helena");
	sld.dialog.filename = "Quest\Sharlie\Epilog.c";
	sld.dialog.currentnode = "SharlieEpilog_HenriDeMonper_Helena_2";
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, Pchar, "", -1);
	CharacterTurnByChr(CharacterFromID("Helena"), CharacterFromID("HenriDeMonper"));
	CharacterTurnByChr(CharacterFromID("HenriDeMonper"), CharacterFromID("Helena"));
}

void SharlieEpilog_HenriDeMonper_Helena_2_1()
{
	sld = CharacterFromID("HenriDeMonper");
	sld.dialog.filename = "Quest\Sharlie\Epilog.c";
	sld.dialog.currentnode = "SharlieEpilog_HenriDeMonper_Helena_3";
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, Pchar, "", -1);
	CharacterTurnByChr(CharacterFromID("Helena"), CharacterFromID("HenriDeMonper"));
	CharacterTurnByChr(CharacterFromID("HenriDeMonper"), CharacterFromID("Helena"));
}

void SharlieEpilog_HenriDeMonper_Mary_1()
{
	sld = CharacterFromID("Mary");
	sld.dialog.filename = "Quest\Sharlie\Epilog.c";
	sld.dialog.currentnode = "SharlieEpilog_HenriDeMonper_Mary_2";
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, Pchar, "", -1);
	CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("HenriDeMonper"));
	CharacterTurnByChr(CharacterFromID("HenriDeMonper"), CharacterFromID("Mary"));
}

void SharlieEpilog_HenriDeMonper_Mary_2_1()
{
	sld = CharacterFromID("HenriDeMonper");
	sld.dialog.filename = "Quest\Sharlie\Epilog.c";
	sld.dialog.currentnode = "SharlieEpilog_HenriDeMonper_Mary_3";
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, Pchar, "", -1);
	CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("HenriDeMonper"));
	CharacterTurnByChr(CharacterFromID("HenriDeMonper"), CharacterFromID("Mary"));
}

void SharlieEpilog_InEstateDeMonpe_15()
{
	locCameraSleep(true);
	LAi_FadeEx(1.0, 0.0, 1.0, "SharlieEpilog_InEstateDeMonpe_16", "", "");
}

void SharlieEpilog_InEstateDeMonpe_16(string qName)
{
	locCameraSleep(false);
	locCameraFlyToPositionLookToPoint(-12.76, 9.22, 2.80, -11.72, 8.98, 2.50, 7.50, 7.42, -0.50, -1.0, 7000/GetDeltaTime());
	Pchar.FuncCameraFly = "CameraSleep";
	
	LAi_SetActorType(pchar);
	LAi_ActorGoToLocator(pchar, "goto", "goto8", "", -1);
	
	sld = CharacterFromID("HenriDeMonper");
	IgnoreCollision(sld, false);
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "goto", "goto8", "", -1);
	
	if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
	{
		sld = CharacterFromID("Helena");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocator(sld, "goto", "goto8", "", -1);
	}
	if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
	{
		sld = CharacterFromID("Mary");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocator(sld, "goto", "goto8", "", -1);
	}
	
	if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel"))
	{
		sld = CharacterFromID("Knippel");
		TeleportCharacterToPosAy(sld, -9.4, 6.00, -1.70, 1.50);
		LAi_SetActorType(sld);
		LAi_ActorGoToLocator(sld, "goto", "goto8", "", -1);
	}
	if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway"))
	{
		sld = CharacterFromID("Longway");
		TeleportCharacterToPosAy(sld, -9.4, 6.00, -1.70, 1.50);
		LAi_SetActorType(sld);
		LAi_ActorGoToLocator(sld, "goto", "goto8", "", -1);
	}
	if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
	{
		sld = CharacterFromID("Tonzag");
		TeleportCharacterToPosAy(sld, -9.4, 6.00, -1.70, 1.50);
		LAi_SetActorType(sld);
		LAi_ActorGoToLocator(sld, "goto", "goto8", "", -1);
	}
	
	if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
	{
		sld = CharacterFromID("Tichingitu");
		TeleportCharacterToPosAy(sld, -9.4, 6.00, 0.50, 1.50);
		LAi_SetActorType(sld);
		LAi_ActorGoToLocator(sld, "goto", "goto8", "", -1);
	}
	
	sld = CharacterFromID("SharlieEpilog_Alonso");
	TeleportCharacterToPosAy(sld, -9.4, 6.00, -0.60, 1.50);
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "goto", "goto8", "", -1);
	
	DoQuestFunctionDelay("SharlieEpilog_InEstateDeMonpe_17", 6.0);
}

void SharlieEpilog_InEstateDeMonpe_17(string qName)
{
	EndQuestMovie();
	DeleteSnow();
	locCameraSleep(false);
	DoFunctionReloadToLocation("EstateDM1_Kitchen", "sit", "sit5", "SharlieEpilog_InKitchenDeMonpe_1");
}

// на ужине в поместье де Монпе
void SharlieEpilog_InKitchenDeMonpe_1()
{
	LAi_FadeEx(0.0, 1.5, 1.0, "SharlieEpilog_InKitchenDeMonpe_2", "", "");
}

void SharlieEpilog_InKitchenDeMonpe_2(string qName)
{
	StartQuestMovie(true, false, true);
	locCameraResetState();
	locCameraFromToPos(4.00, 13.40, 15.95, true, 4.91, 11.65, 17.19);
	pchar.nonTable = true;
	LAi_SetSitType(pchar);
	
	sld = CharacterFromID("HenriDeMonper");
	LAi_SetSitType(sld);
	sld.nonTable = true;
	ChangeCharacterAddressGroup(sld, "EstateDM1_Kitchen", "sit", "sit6");
	
	if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
	{
		sld = CharacterFromID("Helena");
		LAi_SetHuberType(sld);
		ChangeCharacterAddressGroup(sld, "EstateDM1_Kitchen", "sit", "girl1");
	}
	if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
	{
		sld = CharacterFromID("Mary");
		LAi_SetHuberType(sld);
		ChangeCharacterAddressGroup(sld, "EstateDM1_Kitchen", "sit", "girl1");
	}
	
	if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel"))
	{
		sld = CharacterFromID("Knippel");
		LAi_SetSitType(sld);
		sld.nonTable = true;
		ChangeCharacterAddressGroup(sld, "EstateDM1_Kitchen", "sit", "sit2");
	}
	if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway"))
	{
		sld = CharacterFromID("Longway");
		LAi_SetSitType(sld);
		sld.nonTable = true;
		ChangeCharacterAddressGroup(sld, "EstateDM1_Kitchen", "sit", "sit2");
	}
	if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
	{
		sld = CharacterFromID("Tonzag");
		LAi_SetSitType(sld);
		sld.nonTable = true;
		ChangeCharacterAddressGroup(sld, "EstateDM1_Kitchen", "sit", "sit2");
	}
	
	if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
	{
		sld = CharacterFromID("Tichingitu");
		LAi_SetSitType(sld);
		sld.nonTable = true;
		ChangeCharacterAddressGroup(sld, "EstateDM1_Kitchen", "sit", "sit4");
	}
	
	sld = CharacterFromID("SharlieEpilog_Alonso");
	LAi_SetSitType(sld);
	sld.nonTable = true;
	ChangeCharacterAddressGroup(sld, "EstateDM1_Kitchen", "sit", "sit3");
	
	sld = GetCharacter(NPC_GenerateCharacter("Invisible", "Invisible", "man", "man", 5, FRANCE, 0, false, "citizen"));
	ChangeCharacterAddressGroup(sld, "EstateDM1_Kitchen", "goto", "goto1");
	TeleportCharacterToPos(sld, 1000.00, 50.00, 1000.00);
	sld.name = "";
	sld.lastname = "";
	
	DoQuestFunctionDelay("SharlieEpilog_InKitchenDeMonpe_3", 6.0);
}

void SharlieEpilog_InKitchenDeMonpe_3(string qName)
{
	sld = CharacterFromID("Invisible");
	sld.dialog.filename = "Quest\Sharlie\Epilog.c";
	sld.dialog.currentnode = "SharlieEpilog_InKitchenDeMonpe";
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, Pchar, "", -1);
}

void SharlieEpilog_InKitchenDeMonpe_camera_Sharle()
{
	locCameraFromToPos(5.55, 12.87, 18.74, true, 5.55, 11.40, 17.10);
}

void SharlieEpilog_InKitchenDeMonpe_camera_Wife()
{
	locCameraFromToPos(5.12, 12.93, 18.36, true, 6.87, 11.34, 18.27);
}

void SharlieEpilog_InKitchenDeMonpe_camera_Tichingitu()
{
	locCameraFromToPos(6.07, 12.96, 18.44, true, 4.59, 11.35, 18.40);
}

void SharlieEpilog_InKitchenDeMonpe_camera_Gambitnik()
{
	locCameraFromToPos(5.29, 12.83, 19.35, true, 6.68, 11.32, 19.39);
}

void SharlieEpilog_InKitchenDeMonpe_camera_Alonso()
{
	locCameraFromToPos(6.28, 12.98, 19.38, true, 4.47, 11.39, 19.49);
}

void SharlieEpilog_InKitchenDeMonpe_camera_Father()
{
	locCameraFromToPos(5.55, 12.95, 19.16, true, 5.61, 11.40, 20.55);
}

void SharlieEpilog_toast()
{
	locCameraFlyToPositionLookToPoint(4.00, 13.40, 15.95, 3.25, 13.71, 14.85, 4.91, 13.09, 17.19, -1.0, 6000/GetDeltaTime());
	Pchar.FuncCameraFly = "CameraSleep";
	DoQuestFunctionDelay("SharlieEpilog_toast_2", 3.5);
}

void SharlieEpilog_toast_2(string qName)
{
	if (CheckAttribute(pchar, "questTemp.SharlieEpilog_ChooseEstate")) LAi_FadeEx(2.0, 0.0, 0.0, "SharlieEpilog_ChooseEstate", "", "");
	else LAi_FadeEx(2.0, 0.0, 0.0, "SharlieEpilog_ChooseCaribbean", "", "");
}

void SharlieEpilog_ChooseCaribbean(string qName)
{
	DeleteClass(&LAi_QuestFader);
	SetLaunchFrameFormParam(GetConvertStr("Frame_YearPassed_3", "Frame.txt")+ NewStr() +UpperFirst(GetConvertStr("Shore67", "LocLables.txt"))+".", "Run_Function", 0, 4.0);
	SetLaunchFrameRunFunctionParam("SharlieEpilog_ChooseCaribbean_2", 0.0);
	LaunchFrameForm();
}

void SharlieEpilog_ChooseCaribbean_2()
{
	i = FindIsland("RockIsland");
	Islands[i].visible = true;
	Islands[i].reload_enable = true;
	SetCurrentTime(0, 00);
	
	locCameraSleep(false);
	locCameraResetState();
	DoFunctionReloadToLocation("Shore67", "quest", "bridge1", "SharlieEpilog_OnReefs");
}

void SharlieEpilog_OnReefs()
{
	DeleteClass(&LAi_QuestFader);
	locCameraFromToPos(-14.47, 9.71, 5.20, true, -4.31, 7.27, 6.19);
	LAi_FadeEx(0.0, 2.0, 1.0, "", "SharlieEpilog_OnReefs_2", "");
	
	ref sld = GetCharacter(NPC_GenerateCharacter("SharlieEpilog_Mishelle", "Migel_1", "man", "man", 30, PIRATE, -1, true, "quest"));
	sld.name = StringFromKey("QuestsUtilite_48");
	sld.lastname = StringFromKey("QuestsUtilite_49");
	ChangeCharacterAddressGroup(sld, "Shore67", "quest", "bridge2");
	CharacterTurnByChr(sld, pchar);
	CharacterTurnByChr(pchar, sld);
	LAi_SetStayType(pchar);
}

void SharlieEpilog_OnReefs_2(string qName)
{
	locCameraFlyToPositionLookToPoint(-14.47, 9.71, 5.20, -13.05, 9.53, 5.34, -4.31, 8.71, 6.19, -1.0, 10000/GetDeltaTime());
	Pchar.FuncCameraFly = "CameraSleep";
	DoQuestFunctionDelay("SharlieEpilog_OnReefs_3", 5.0);
}

void SharlieEpilog_OnReefs_3(string qName)
{
	locCameraSleep(false);
	locCameraResetState();
	locCameraFlyToPositionLookToPoint(-1.31, 8.50, 3.10, -1.44, 8.50, 2.80, -2.39, 8.49, 0.65, -1.0, 10000/GetDeltaTime());
	Pchar.FuncCameraFly = "CameraSleep";
	DoQuestFunctionDelay("SharlieEpilog_OnReefs_4", 3.0);
}

void SharlieEpilog_OnReefs_4(string qName)
{
	locCameraSleep(false);
	locCameraResetState();
	locCameraFlyToPositionLookToPoint(-2.43, 9.03, 10.45, -2.70, 9.04, 10.74, -4.81, 9.13, 12.78, -1.0, 10000/GetDeltaTime());
	Pchar.FuncCameraFly = "CameraSleep";
	DoQuestFunctionDelay("SharlieEpilog_OnReefs_5", 3.0);
}

void SharlieEpilog_OnReefs_5(string qName)
{
	sld = CharacterFromID("SharlieEpilog_Mishelle");
	sld.greeting = "mishelle-04";
	sld.dialog.filename = "Quest\Sharlie\Epilog.c";
	sld.dialog.currentnode = "SharlieEpilog_Mishelle_1";
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, Pchar, "", -1);
}

void SharlieEpilog_OnReefs_6()
{
	locCameraSleep(false);
	locCameraResetState();
	SharlieEpilog_OnReefs_7();
}

void SharlieEpilog_OnReefs_7()
{
	locCameraFlyToPositionLookToPoint(-14.47, 9.71, 5.20, -13.05, 9.53, 5.34, -4.31, 8.71, 6.19, -1.0, 13000/GetDeltaTime());
	Pchar.FuncCameraFly = "SharlieEpilog_OnReefs_8";
}

void SharlieEpilog_OnReefs_8()
{
	locCameraFlyToPositionLookToPoint(-13.05, 9.53, 5.34, -14.47, 9.71, 5.20, -4.31, 8.71, 6.19, -1.0, 13000/GetDeltaTime());
	Pchar.FuncCameraFly = "SharlieEpilog_OnReefs_7";
}

void SharlieEpilog_OnReefs_9()
{
	LAi_SetActorType(pchar);
	LAi_ActorAnimation(pchar, "normal to fight", "1", 2.5);
	DoQuestFunctionDelay("SharlieEpilog_OnReefs_10", 2.5);
}

void SharlieEpilog_OnReefs_10(string qName)
{
	LAi_ActorAnimation(pchar, "fight to normal", "1", 2.0);
	sld = CharacterFromID("SharlieEpilog_Mishelle");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	
	DoQuestFunctionDelay("SharlieEpilog_OnReefs_11", 2.0);
}

void SharlieEpilog_OnReefs_11(string qName)
{
	Islands[FindIsland("RockIsland")].storm = true;
	LAi_FadeEx(2.0, 0.5, 0.0, "", "SharlieEpilog_OnReefs_12", "");
}

void SharlieEpilog_OnReefs_12(string qName)
{
	EndQuestMovie();
	EndBattleLandInterface();
	DontRefreshBLI = true;
	InterfaceStates.Buttons.Save.enable = false;
	bDisableCharacterMenu = true;
	locCameraResetState();
	locCameraFollowEx(true);
	LAi_SetPlayerType(pchar);
	pchar.GenQuest.CabinLock = true;
	bQuestDisableMapEnter = true;
	DeleteAttribute(pchar,"questTemp.TimeLock");
	DeleteAttribute(pchar, "GenQuest.CannotWait");
	DeleteAttribute(pchar, "GenQuest.BlockTalkSelf");
	Island_SetReloadEnableGlobal("RockIsland", false);
	
	pchar.Ship.Type = GenerateShipExt(SHIP_CURSED_FDM, true, pchar);
	pchar.Ship.name = GetShipName("Flying Heart");
	SetBaseShipData(pchar);
	pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS36;
	SetCrewQuantityFull(pchar);
	SetCharacterGoods(pchar, GOOD_FOOD, 5000);
	
	setCharacterShipLocation(pchar, "Shore67");
	setWDMPointXZ("Shore67");
	
	SetFunctionLocationCondition("SharlieEpilog_OnReefs_13", "RockIsland", false);
	SeaCameras_SetShipCameraAy(115.0);
	// QuestToSeaLogin_Launch();
	// QuestToSeaLogin_Prepare(630.0, -20.0, "RockIsland");
}

void SharlieEpilog_OnReefs_13(string qName)
{
	DontRefreshBLI = false;
	pchar.systeminfo.BLIoff = true;
	SetCurrentTime(7, 00);
	DoQuestFunctionDelay("SharlieEpilog_logo", 10.0);
}

void SharlieEpilog_ChooseEstate(string qName)
{
	DeleteClass(&LAi_QuestFader);
	SetLaunchFrameFormParam(GetConvertStr("Frame_YearPassed_3", "Frame.txt")+ NewStr() +GetConvertStr("FortFrance_town", "LocLables.txt")+".", "Run_Function", 0, 4.0);
	SetLaunchFrameRunFunctionParam("SharlieEpilog_ChooseEstate_2", 0.0);
	LaunchFrameForm();
}

void SharlieEpilog_ChooseEstate_2()
{
	ref sld = CharacterFromID("FortFrance_Mayor");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	
	DoFunctionReloadToLocation("FortFrance_townhall", "sit", "sit1", "SharlieEpilog_GuberOnMartinique");
}

void SharlieEpilog_GuberOnMartinique()
{
	LAi_FadeEx(0.0, 2.0, 1.0, "", "SharlieEpilog_GuberOnMartinique_1", "");
	locCameraSleep(false);
	locCameraFlyToPositionLookToPoint(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 100/GetDeltaTime());
	Pchar.FuncCameraFly = "";
	LAi_SetHuberType(pchar);
	pchar.model = "Sharle_governor";
	Characters_RefreshModel(pchar);
}

void SharlieEpilog_GuberOnMartinique_1(string qName)
{
	locCameraFromToPos(-0.33, 3.70, -7.00, true, -3.08, 2.04, -6.71);
	DoQuestFunctionDelay("SharlieEpilog_GuberOnMartinique_2", 3.5);
}

void SharlieEpilog_GuberOnMartinique_2(string qName)
{
	locCameraFromToPos(-1.03, 4.23, -5.96, true, -0.64, 2.19, -3.17);
	DoQuestFunctionDelay("SharlieEpilog_GuberOnMartinique_3", 2.0);

	ref sld = GetCharacter(NPC_GenerateCharacter("SharlieEpilog_GreenCaptain", "Devlin", "man", "man", 30, FRANCE, -1, true, "quest"));
	sld.role = "captain";
	ChangeCharacterAddressGroup(sld, "FortFrance_Townhall", "reload", "reload1");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "goto", "goto2", "", -1);
	
	DoQuestFunctionDelay("SharlieEpilog_GuberOnMartinique_3", 5.0);
}

void SharlieEpilog_GuberOnMartinique_3(string qName)
{
	LAi_FadeEx(1.0, 0.0, 1.0, "SharlieEpilog_GuberOnMartinique_4", "", "");
}

void SharlieEpilog_GuberOnMartinique_4(string qName)
{
	locCameraFromToPos(-1.03, 4.23, -5.96, true, -0.64, 2.19, -3.17);
	// DoQuestFunctionDelay("SharlieEpilog_GuberOnMartinique_3", 2.0);

	ref sld = CharacterFromID("SharlieEpilog_GreenCaptain");
	sld.dialog.filename = "Quest\Sharlie\Epilog.c";
	sld.dialog.currentnode = "SharlieEpilog_GreenCaptain";
	ChangeCharacterAddressGroup(sld, "FortFrance_Townhall", "quest", "quest2");
	// TeleportCharacterToPosAy(sld, -2.00, 2.43, -6.00, -2.65);
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, Pchar, "", -1);
}

void SharlieEpilog_GuberOnMartinique_5()
{
	locCameraSleep(true);
	ref sld = CharacterFromID("SharlieEpilog_GreenCaptain");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", 10);
	DoQuestFunctionDelay("SharlieEpilog_GuberOnMartinique_6", 2.0);
}

void SharlieEpilog_GuberOnMartinique_6(string qName)
{
	SharlieEpilog_GuberOnMartinique_8();
}

void SharlieEpilog_GuberOnMartinique_7()
{
	ref sld = CharacterFromID("SharlieEpilog_Alonso");
	sld.dialog.filename = "Quest\Sharlie\Epilog.c";
	sld.dialog.currentnode = "SharlieEpilog_Alonso35";
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, Pchar, "", -1);
}

void SharlieEpilog_GuberOnMartinique_8()
{
	// ref sld = GetCharacter(CreateCharacterClone(CharacterFromID("FortFranceAmmoOff"), 0));
	// sld.id = "SharlieEpilog_KomendantFort";
	sld = GetCharacter(NPC_GenerateCharacter("SharlieEpilog_KomendantFort", "off_fra_1", "man", "man", 15, FRANCE, 0, true, "soldier"));
	sld.role = "comandante";
	ChangeCharacterAddressGroup(sld, "FortFrance_Townhall", "reload", "reload1");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "quest", "quest3", "SharlieEpilog_GuberOnMartinique_9", -1);
}

void SharlieEpilog_GuberOnMartinique_9()
{
	ref sld = CharacterFromID("SharlieEpilog_KomendantFort");
	sld.dialog.filename = "Quest\Sharlie\Epilog.c";
	sld.dialog.currentnode = "SharlieEpilog_KomendantFort";
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, Pchar, "", -1);
}

void SharlieEpilog_GuberOnMartinique_10(string qName)
{
	ref sld = GetCharacter(NPC_GenerateCharacter("SharlieEpilog_Guard", "Invisible", "man", "man", 30, FRANCE, 0, true, "quest"));
	sld.name = "";
	sld.lastname = "";
	sld.dialog.filename = "Quest\Sharlie\Epilog.c";
	sld.dialog.currentnode = "SharlieEpilog_Guard";
	ChangeCharacterAddressGroup(sld, "FortFrance_Townhall", "goto", "goto1");
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, Pchar, "", -1);
}

void SharlieEpilog_GuberOnMartinique_11()
{
	ref sld = CharacterFromID("SharlieEpilog_KomendantFort");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", 10);
	DoQuestFunctionDelay("SharlieEpilog_GuberOnMartinique_10", 2.0);
}

void SharlieEpilog_GuberOnMartinique_12()
{
	locCameraSleep(true);
	LAi_FadeEx(2.0, 0.0, 0.0, "SharlieEpilog_GuberOnMartinique_13", "", "");
}

void SharlieEpilog_GuberOnMartinique_13()
{
	ResetSound();
	SetMusic("");
	pchar.questTemp.lockedMusic = true;
	DoFunctionReloadToLocation("FortFrance_town", "goto", "goto8", "SharlieEpilog_SharlePreparingArmy_1");
}

void SharlieEpilog_SharlePreparingArmy_music(string qName)
{
	DeleteAttribute(pchar, "questTemp.lockedMusic");
	ResetSound();
	SetMusic("music_MainMenu");
}

void SharlieEpilog_AlonsoArrive()
{
	DoQuestFunctionDelay("SharlieEpilog_AlonsoArrive1", 1.0);
}

void SharlieEpilog_AlonsoArrive1(string qName)
{
	ref sld = CharacterFromID("SharlieEpilog_Alonso");
	ChangeCharacterAddressGroup(sld, "FortFrance_Townhall", "reload", "reload1");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "quest", "quest2", "SharlieEpilog_GuberOnMartinique_7", -1);
}

void SharlieEpilog_SharlePreparingArmy_1()
{
	DoQuestFunctionDelay("SharlieEpilog_SharlePreparingArmy_music", 1.0);
	LAi_FadeEx(0.0, 1.5, 1.0, "", "SharlieEpilog_SharlePreparingArmy_2", "");
	for (i = 0; i < MAX_CHARACTERS; i++)
	{
		sld = GetCharacter(i);
		if (sld.id != "Blaze" && sld.location == "FortFrance_town") ChangeCharacterAddressGroup(sld, "none", "", "");
	}
	
	for (i=1; i<=60; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("SharlieEpilog_FraArmy_"+i, "sold_fra_"+(rand(7)+1), "man", "man", 30, FRANCE, 0, true, "soldier"));
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto2");
        if (i < 21) TeleportCharacterToPosAy(sld, 20.0 + i, 2.0, 21.0, 0.0);
        else if (i < 41) TeleportCharacterToPosAy(sld, MakeFloat(i), 2.0, 22.0, 0.0);
        else TeleportCharacterToPosAy(sld, MakeFloat(i - 20), 2.0, 23.0, 0.0);
		
		if (i >= 56 && i <= 60)
		{
			sld.model = "mush_fra_"+(rand(2)+1);
			sld.model.animation = "mushketer";
			Characters_RefreshModel(sld);
			GiveItem2Character(sld, "mushket1");
			EquipCharacterByItem(sld, "mushket1");
		}
		else if (i >= 36 && i <= 40)
		{
			sld.model = "mush_fra_"+(rand(2)+1);
			sld.model.animation = "mushketer";
			Characters_RefreshModel(sld);
			GiveItem2Character(sld, "mushket1");
			EquipCharacterByItem(sld, "mushket1");
		}
		else if (i >= 16 && i <= 20)
		{
			sld.model = "mush_fra_"+(rand(2)+1);
			sld.model.animation = "mushketer";
			Characters_RefreshModel(sld);
			GiveItem2Character(sld, "mushket1");
			EquipCharacterByItem(sld, "mushket1");
		}
	}
	
	LAi_SetActorType(pchar);
	TeleportCharacterToPosAy(pchar, 30.00, 2.00, 30.00, 3.00);
	/*if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
	{
		ref sld = CharacterFromID("Helena");
		ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto2");
		TeleportCharacterToPosAy(sld, 31.00, 2.00, 30.00, 3.00);
	}
	else if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
	{
		sld = CharacterFromID("Mary");
		ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto2");
		TeleportCharacterToPosAy(sld, 31.00, 2.00, 30.00, 3.00);
	}*/
}

void SharlieEpilog_SharlePreparingArmy_2(string qName)
{
	locCameraFlyToPositionLookToAngle(20.50, 3.00, 27.25, 37.50, 3.00, 27.25, 5.0, 165.0, -1.0, 17000/GetDeltaTime());
	Pchar.FuncCameraFly = "SharlieEpilog_SharlePreparingArmy_3";
}

void SharlieEpilog_SharlePreparingArmy_3()
{
	locCameraFlyToPositionLookToPoint(29.26, 3.43, 27.72, 29.41, 3.46, 28.08, 30.57, 3.72, 30.89, -1.0, 13000/GetDeltaTime());
	Pchar.FuncCameraFly = "CameraSleep";
	DoQuestFunctionDelay("SharlieEpilog_SharlePreparingArmy_4", 4.0);
}

void SharlieEpilog_SharlePreparingArmy_4(string qName)
{
	locCameraResetState();
	locCameraFlyToPositionLookToPoint(29.18, 4.30, 32.82, 29.32, 4.14, 32.09, 29.72, 3.64, 29.88, -1.0, 10000/GetDeltaTime());
	Pchar.FuncCameraFly = "CameraSleep";
	DoQuestFunctionDelay("SharlieEpilog_SharlePreparingArmy_5", 4.0);
}

void SharlieEpilog_SharlePreparingArmy_5(string qName)
{
	locCameraResetState();
	locCameraFlyToPositionLookToPoint(44.06, 4.32, 23.85, 42.94, 4.05, 23.92, 39.97, 3.60, 24.14, -1.0, 6000/GetDeltaTime());
	Pchar.FuncCameraFly = "SharlieEpilog_SharlePreparingArmy_6";
}

void SharlieEpilog_SharlePreparingArmy_6()
{
	locCameraResetState();
	locCameraFlyToPositionLookToPoint(31.74, 5.52, 27.89, 55.51, 34.42, 7.47, 30.20, 3.41, 29.86, -1.0, 18000/GetDeltaTime());
	Pchar.FuncCameraFly = "CameraSleep";
	DoQuestFunctionDelay("SharlieEpilog_logo", 10.0);
}

void SharlieEpilog_logo(string qName)
{
	aref arImage, arLogo;
	makearef(arLogo, ILogAndActions.TutorialLogo);
	makearef(arImage, arLogo.images.logo);
	
	string sAdd = "";
	if(LanguageGetLanguage() == "Chinese") sAdd = "_cn";
	arImage.texture = "interfaces\le\cle_logo2"+sAdd+".tga";
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
	
	SetEventHandler("SharlieEpilog_Refresh", "SharlieEpilog_Refresh", 0);
	Event("SharlieEpilog_Refresh");
}

void SharlieEpilog_Refresh()
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
		SharlieEpilog_ShowLogo_End();
		return;
	}
	PostEvent("SharlieEpilog_Refresh", delta);
}

void SharlieEpilog_ShowLogo_End()
{
	DoQuestFunctionDelay("SharlieEpilog_TitlesStart", 0.5);
	SendMessage(&ILogAndActions , "ll", LI_MSG_TUTORIAL_SHOW, false);
	DeleteAttribute(&ILogAndActions, "TutorialLogo");
	DelEventHandler("SharlieEpilog_Refresh", "SharlieEpilog_Refresh");
}

// титры -->
void SharlieEpilog_TitlesStart(string qName)
{
	if (CheckAttribute(pchar, "questTemp.SharlieEpilog_ChooseCaribbean")) Achievment_Set("ach_CL_203");
	if (CheckAttribute(pchar, "questTemp.SharlieEpilog_ChooseEstate")) Achievment_Set("ach_CL_204");
	GameOver("complete");
}
// титры <--












void SharlieEpilog_TEST()
{
	LAi_SetPlayerType(pchar);
	InterfaceStates.Buttons.Save.enable = true;
	bGameMenuStart = false;
	StartBattleLandInterface();
	RemoveAllCharacterItems(pchar, true);
	AddMoneyToCharacter(pchar, 10000000);
	pchar.rank = 30;
	LAi_SetHP(pchar, 400.0, 400.0);
	SetSPECIAL(PChar, 10, 10, 10, 10, 10, 10, 10);
	SetSelfSkill(PChar, 50, 50, 50, 50, 50);
	SetShipSkill(PChar, 50, 75, 50, 50, 100, 50, 50, 50, 75);
	LAi_SetHP(pchar, 400.0, 400.0);
	
	GiveItem2Character(PChar, "blade_16");
	GiveItem2Character(PChar, "blade_13");
	EquipCharacterByItem(Pchar, "blade_13");
	GiveItem2Character(PChar, "pistol5");
	EquipCharacterByItem(Pchar, "pistol5");
	GiveItem2Character(PChar, "cirass8");
	EquipCharacterByItem(Pchar, "cirass8");
	GiveItem2Character(PChar, "spyglass4");
	EquipCharacterByItem(Pchar, "spyglass4");
	GiveItem2Character(PChar, "talisman2");
	EquipCharacterByItem(Pchar, "talisman2");
	GiveItem2Character(PChar, "talisman13");
	AddItems(Pchar, "cartridge", 50);
	AddItems(Pchar, "potion4", 20);
	LAi_SetCharacterUseBullet(Pchar, GUN_ITEM_TYPE, "cartridge");
	AddItems(pchar, "gold_dublon", 500);
	
	setCharacterShipLocation(pchar, "FortFrance_town");
	setWDMPointXZ("FortFrance_town");
	
	//выключить сторонние квесты
	PChar.quest.Red_Chieftain.over = "yes";
	PChar.quest.False_Trace.over = "yes";
	PChar.quest.FalseTrace_Prepare.over = "yes";
	//Нужные атрибуты для квеста
	pchar.questTemp.Terrapin = "done";
	pchar.questTemp.Saga = "end";
	pchar.questTemp.Sharlie = "escape";
	pchar.questTemp.GoldenGirl_Ready = true;
	sld = characterFromId("Benua");
	sld.quest.help = "true";
	sld.quest.meet = true;
	sld.quest.relation_info = "true";
	
	if (CheckCharacterItem(PChar, "patent_fra")) EquipCharacterbyItem(pchar, "patent_fra");
	pchar.questTemp.SharlieEpilog_Start = true;
	pchar.questTemp.SharlieEpilog_Benua = true;
	AddLandQuestMark(characterFromId("Benua"), "questmarkmain");
	
	//Исла Мона
	pchar.questTemp.IslaMona.Plantation = "true";
	//Пиратский барон
	pchar.questTemp.LongHappy.Baron = "true";
	//Прошли ПЧФ
	pchar.questTemp.Mtraxx = "full_complete_end";
}

void SharlieEpilog_TEST_Mary()
{
	SharlieEpilog_TEST();
	
	// Мэри:
	pchar.questTemp.LSC.Mary_officer = "true";
	sld = characterFromId("Mary");
	sld.quest.OfficerPrice = sti(pchar.rank) * 500;
	sld.OfficerWantToGo.DontGo = true;
	sld.CompanionDisable = true;
	sld.loyality = MAX_LOYALITY;
	AddPassenger(pchar, sld, false);
	SetCharacterRemovable(sld, true);
	sld.Payment = true;
	sld.DontClearDead = true;
	sld.SpecialRole = "fgirl";
	sld.dialog.currentnode = "Mary_officer";
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	SaveCurrentNpcQuestDateParam(sld, "HiredDate");
	sld.rank = 35;
	LAi_SetHP(sld, 500.0, 500.0);
	SetSelfSkill(sld, 100, 90, 100, 100, 90);
	SetShipSkill(sld, 100, 40, 40, 40, 40, 40, 40, 40, 40);
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "ByWorker");

	SetCharacterPerk(sld, "Grus");
	GiveItem2Character(sld, "blade_31");
	sld.equip.blade = "blade_31";
	GiveItem2Character(sld, "pistol4");
	sld.equip.gun = "pistol4";
	GiveItem2Character(sld, "cirass4");
	EquipCharacterbyItem(sld, "cirass4");
	AddItems(sld, "cartridge", 50);
	AddItems(sld, "potion2", 10);
	AddItems(sld, "potion4", 5);
	sld.OfficerImmortal = true;
	sld.Health.HP       = 60.0;
	sld.Health.maxHP    = 60.0;
}

void SharlieEpilog_TEST_Helena()
{
	SharlieEpilog_TEST();
	
	// Элен:
    pchar.questTemp.Saga.Helena_officer = "true";
    sld = characterFromId("Helena");
    sld.greeting = "helena_hire";
	sld.Dialog.Filename = "Quest\Saga\Helena.c";
	sld.Dialog.CurrentNode = "Helena_officer";
	sld.quest.OfficerPrice = sti(pchar.rank) * 20;
    sld.OfficerWantToGo.DontGo = true;
    sld.loyality = MAX_LOYALITY;
    AddPassenger(pchar, sld, false);
    SetCharacterRemovable(sld, true);
    sld.Payment = true;
    sld.DontClearDead = true;
    sld.dialog.currentnode = "Helena_officer";
    LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
    SaveCurrentNpcQuestDateParam(sld, "HiredDate");
	sld.OfficerImmortal = true;
	sld.Health.HP       = 60.0; 
	sld.Health.maxHP    = 60.0;

    sld.rank = 35;
    LAi_SetHP(sld, 400.0, 400.0);
    SetSelfSkill(sld, 100, 90, 100, 100, 90);
    SetShipSkill(sld, 100, 90, 90, 90, 90, 90, 90, 90, 90);
    SetCharacterPerk(sld, "HardHitter");
    SetCharacterPerk(sld, "ByWorker");

    SetCharacterPerk(sld, "Grus");
    GiveItem2Character(sld, "pirate_cutlass");
    sld.equip.blade = "pirate_cutlass";
    GiveItem2Character(sld, "pistol4");
    sld.equip.gun = "pistol4";
    GiveItem2Character(sld, "cirass4");
    EquipCharacterbyItem(sld, "cirass4");
    AddItems(sld, "cartridge", 50);
    AddItems(sld, "potion2", 10);
    AddItems(sld, "potion4", 5);
}

void SharlieEpilog_Test_Tichingitu()
{
	SharlieEpilog_TEST();
	
	// Тичингиту:
    sld = GetCharacter(NPC_GenerateCharacter("Tichingitu", "maskog", "man", "man", 5, FRANCE, -1, false, "quest"));
    SetHeroAutolevel(sld);
    sld.name = GetCharacterName("Tichingitu");
    sld.lastname = "";
    sld.greeting = "Tichingitu";
    sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
	sld.Dialog.CurrentNode = "Tichingitu_officer";
	sld.quest.OfficerPrice = sti(pchar.rank) * 20;
    sld.OfficerWantToGo.DontGo = true;
    sld.CompanionDisable = true;
    sld.loyality = MAX_LOYALITY;
    AddPassenger(pchar, sld, false);
    SetCharacterRemovable(sld, true);
    sld.Payment = true;
    LAi_SetOfficerType(sld);
    LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
    SaveCurrentNpcQuestDateParam(sld, "HiredDate");
	sld.OfficerImmortal = true;
	sld.Health.HP       = 60.0; 
	sld.Health.maxHP    = 60.0;

    sld.rank = 30;
    LAi_SetHP(sld, 380.0, 380.0);
    SetSPECIAL(sld, 4, 9, 5, 5, 10, 8, 8);
    SetSelfSkill(sld, 50, 50, 50, 100, 50);
	SetShipSkill(sld, 100, 50, 50, 50, 100, 50, 50, 50, 100);
	SetHalfPerksToChar(sld, false);
    AddItems(sld, "mushket6", 1);
    sld.CanTakeMushket = true;
    GiveItem2Character(sld, "blade_21");
    sld.equip.blade = "blade_21";
    GiveItem2Character(sld, "pistol5");
    sld.equip.gun = "pistol5";
    GiveItem2Character(sld, "cirass1");
    EquipCharacterbyItem(sld, "cirass1");
    AddItems(sld, "cartridge", 30);
    AddItems(sld, "GunEchin", 30);
    AddItems(sld, "GunPowder", 30);
    AddItems(sld, "potion2", 7);
    AddItems(sld, "potion4", 3);
}



bool SharlieEpilog_QuestComplete(string sQuestName, string qname)
{
	ref sld, chr;
	int iTemp, i, n, idx, iRank, iScl, iAddTime;
    float locx, locy, locz, fMft;
	string sTemp;
	
	bool condition = true;
	
	if (sQuestName == "SharlieEpilog_windlass_1_2")
	{
		SharlieEpilog_windlass_1_2();
	}
	else if (sQuestName == "SharlieEpilog_LoveInCabin_15")
	{
		SharlieEpilog_LoveInCabin_15();
	}
	else if (sQuestName == "SharlieEpilog_InEstateDeMonpe_12")
	{
		SharlieEpilog_InEstateDeMonpe_12();
	}
	else if (sQuestName == "SharlieEpilog_GuberOnMartinique_7")
	{
		SharlieEpilog_GuberOnMartinique_7();
	}
	else if (sQuestName == "SharlieEpilog_GuberOnMartinique_9")
	{
		SharlieEpilog_GuberOnMartinique_9();
	}
	else
	{
		condition = false;
	}
	
	return condition;
}
