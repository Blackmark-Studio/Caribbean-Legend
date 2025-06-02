/// Jason ----------------------------------------------------------- Долго и счастливо ------------------------------------------------------------------
// belamour legendary edition
void LongHappy_Prepare(string qName) // подготвка квеста
{
	if (!CheckAttribute(pchar, "questTemp.LongHappy") && LongHappy_CheckCondisiones())
	{
		LongHappy_Start();
		log_Testinfo("Стартовал квест Долго и счастливо");
	}
	else 
	{
		if(CheckAttribute(pchar,"quest.LongHappy_Prepare.over"))
		DeleteAttribute(pchar,"quest.LongHappy_Prepare.over");
		SetFunctionTimerCondition("LongHappy_Prepare", 0, 0, 1, false);
		log_Testinfo("Отложен квест Долго и счастливо");
	}
}

void LongHappy_Start() // инициализация
{
	pchar.quest.longhappy_start.win_condition.l1 = "Nation_City";
	pchar.quest.longhappy_start.win_condition.l1.nation = FRANCE;
	pchar.quest.longhappy_start.function = "LongHappy_StartGo";
	pchar.questTemp.LongHappy = "init";
}

void LongHappy_StartGo(string qName) // 
{
	log_testinfo("Вестовой капитан для Долго и Счастливо запущен");
	// проверка на наличие Элен или Мэри
	if (!LongHappy_CheckGirls()) return;
	chrDisableReloadToLocation = true;//закрыть локацию
	sld = GetCharacter(NPC_GenerateCharacter("LongHappy_cureer", "mercen_11", "man", "man", 25, FRANCE, 0, true, "quest"));
	FantomMakeCoolFighter(sld, 25, 60, 60, "blade_10", "pistol5", "bullet", 100);
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	sld.Dialog.Filename = "Quest\LongHappy.c";
	sld.dialog.currentnode = "cureer";
	LAi_SetImmortal(sld, true);
	//GetCharacterPos(pchar, &locx, &locy, &locz);
	//ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
    ChangeCharacterAddressGroup(sld, pchar.location, "quest", "quest1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	pchar.questTemp.LongHappy = "start";
}

void LongHappy_RecibeLetter() // 
{
	AddQuestRecordInfo("Letter_France", "1");
	if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
	else sld = characterFromId("Mary");
	LAi_SetCheckMinHP(sld, 10, true, ""); // скрытое бессмертие
	string sTemp = sld.name;
	AddQuestRecord("LongHappy", "1");
	AddQuestUserData("LongHappy", "sName", sTemp);
	pchar.questTemp.LongHappy = "letter";
	// прячем аббата Бенуа
	sld = characterFromId("Benua");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	log_info(StringFromKey("LongHappy_1"));
}

void LongHappy_GoToSantiago() // 
{
	pchar.quest.longhappy_santiago.win_condition.l1 = "location";
	pchar.quest.longhappy_santiago.win_condition.l1.location = "Santiago";
	pchar.quest.longhappy_santiago.function = "LongHappy_SantiagoArrive";
	pchar.questTemp.LongHappy.Santiago = "true";
	AddQuestRecord("LongHappy", "4");
}

void LongHappy_SantiagoArrive(string qName) // 
{
	AddQuestRecord("LongHappy", "5");
}

void LongHappy_SantiagoBenua() // 
{
	DeleteAttribute(pchar, "questTemp.LongHappy.Santiago");
	sld = characterFromId("Benua");
	sld.dialog.currentnode = "LH_abbat";
	LAi_SetLoginTime(sld, 18.0, 20.0);
	ChangeCharacterAddressGroup(sld, "Santiago_church", "barmen", "bar1"); 
	AddQuestRecord("LongHappy", "6");
}

void LongHappy_SantiagoBenuaEscape() // 
{
	sld = characterFromId("Benua");
	sld.dialog.currentnode = "First time";
	LAi_RemoveLoginTime(sld);
	LAi_SetActorType(sld);
	LAi_ActorFollowEverywhere(sld, "", -1);
	pchar.quest.longhappy_santiago1.win_condition.l1 = "location";
	pchar.quest.longhappy_santiago1.win_condition.l1.location = "Santiago_town";
	pchar.quest.longhappy_santiago1.function = "LongHappy_SantiagoSoldiers";
	AddQuestRecord("LongHappy", "7");
}

void LongHappy_SantiagoSoldiers(string qName) // 
{
	chrDisableReloadToLocation = true;
	pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
	// ставим испанцев
	int iRank = 25+MOD_SKILL_ENEMY_RATE*2;
	int iScl = 60;
	for (int i=1; i<=4; i++)
	{
		if (i == 1)
		{
			sld = GetCharacter(NPC_GenerateCharacter("LH_escort_"+i, "off_spa_"+i, "man", "man", iRank+5, SPAIN, 0, true, "soldier"));
			FantomMakeCoolFighter(sld, iRank+5, iScl+5, iScl+5, "blade_16", "pistol4", "bullet", iScl*2+50);
			sld.Dialog.Filename = "Quest\LongHappy.c";
			sld.dialog.currentnode = "spa_officer";
			ChangeCharacterAddressGroup(sld, "Santiago_town", "patrol", "patrol13");
		}
		else
		{
			sld = GetCharacter(NPC_GenerateCharacter("LH_escort_"+i, "sold_spa_"+i, "man", "man", iRank, SPAIN, -1, true, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, RandPhraseSimple("blade_12","blade_14"), "pistol1", "bullet", iScl*2);
			ChangeCharacterAddressGroup(sld, "Santiago_town", "patrol", "patrol13"); 
			LAi_CharacterDisableDialog(sld);
		}
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
}

void LongHappy_SantiagoSail(string qName) // 
{
	pchar.quest.longhappy_santiago2.over = "yes"; //снять прерывание
	pchar.quest.longhappy_santiago3.over = "yes"; //снять прерывание
	sld = characterFromId("Benua");
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, "none", "", "");
	AddPassenger(pchar, sld, false);
	SetCharacterRemovable(sld, false);
	AddQuestRecord("LongHappy", "8");
	Island_SetReloadEnableGlobal("Cuba1", false);
	Island_SetReloadEnableGlobal("Cuba2", false);
	SetFunctionTimerCondition("LongHappy_SantiagoQuestHunter", 0, 0, 2, false);
	pchar.quest.longhappy_fortfrance.win_condition.l1 = "location";
	pchar.quest.longhappy_fortfrance.win_condition.l1.location = "FortFrance_town";
	pchar.quest.longhappy_fortfrance.function = "LongHappy_SantiagoFin";
}

void LongHappy_SantiagoQuestHunter(string qName) // 
{
	Map_NationQuestHunter(SPAIN);
}

void LongHappy_SantiagoFin(string qName) // 
{
	log_info(StringFromKey("LongHappy_2"));
	sld = characterFromId("Benua");
	RemovePassenger(pchar, sld);
	LAi_SetLoginTime(sld, 6.0, 21.0);
	LAi_SetStayType(sld);
	ChangeCharacterAddressGroup(sld, "FortFrance_church", "reload", "reload2_back");
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	pchar.questTemp.LongHappy = "marry_offer"; // 28-03-20
}

void LongHappy_MarryOffer() // 
{
	chrDisableReloadToLocation = true;
	if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
	else sld = characterFromId("Mary");
	sld.dialog.currentnode = "LongHappy";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void LongHappy_MarryToSenPierre() // 
{
	AddQuestRecord("LongHappy", "9");
	pchar.questTemp.LongHappy = "toSenPierre";
	pchar.quest.longhappy_fortfrance1.win_condition.l1 = "location";
	pchar.quest.longhappy_fortfrance1.win_condition.l1.location = "FortFrance_town";
	pchar.quest.longhappy_fortfrance1.function = "LongHappy_ToBenua";
}

void LongHappy_ToBenua(string qName) // 
{
	pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу
	chrDisableReloadToLocation = true;
	if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
	else sld = characterFromId("Mary");
	sld.dialog.currentnode = "LongHappy_7";
	ChangeCharacterAddressGroup(sld, "FortFrance_town", "quest", "quest1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void LongHappy_MarryGoToBenua() // 
{
	if (CheckAttribute(pchar, "questTemp.LongHappy.MarryRum")) // праздник в Сен-Пьер
	{
		AddQuestUserData("LongHappy", "sGoods", StringFromKey("LongHappy_3", sti(pchar.questTemp.LongHappy.MarryRum), sti(pchar.questTemp.LongHappy.MarryMoney)));
	}
	else
	{
		if (CheckAttribute(pchar, "questTemp.LongHappy.SmallMarry")) AddQuestUserData("LongHappy", "sGoods", StringFromKey("LongHappy_4"));
		else AddQuestUserData("LongHappy", "sGoods", StringFromKey("LongHappy_5"));
	}
	sld = characterFromId("Benua");
	sld.dialog.currentnode = "LH_abbat_8";
	LocatorReloadEnterDisable("FortFrance_town", "reload1_back", true);
	LocatorReloadEnterDisable("FortFrance_town", "reload2_back", true);
	LocatorReloadEnterDisable("FortFrance_town", "gate_back", true);//закрыть выходы из города
}

void LongHappy_SenPierreGuests(string qName) // 
{
	pchar.quest.longhappy_fortfrance2.win_condition.l1 = "location";
	pchar.quest.longhappy_fortfrance2.win_condition.l1.location = "FortFrance_town";
	pchar.quest.longhappy_fortfrance2.function = "LongHappy_MarryBegin";
	AddQuestRecord("LongHappy", "13");
	if (!CheckAttribute(pchar, "questTemp.LongHappy.DrinkReady")) 
	{
		if (CheckAttribute(pchar, "questTemp.LongHappy.MarryRum")) AddQuestUserData("LongHappy", "sText", StringFromKey("LongHappy_6"));
		else AddQuestUserData("LongHappy", "sText", StringFromKey("LongHappy_7"));
	}
}

void LongHappy_OnIslaTesoro() // 
{
	chrDisableReloadToLocation = true;
	if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
	else sld = characterFromId("Mary");
	sld.dialog.currentnode = "LongHappy_13";
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void LongHappy_IslaTesoroRemoveGoods() // 
{
	if (CheckAttribute(pchar, "questTemp.LongHappy.SmallMarry"))
	{
		RemoveCharacterGoods(pchar, GOOD_RUM, 50);
		RemoveCharacterGoods(pchar, GOOD_WINE, 20);
		AddMoneyToCharacter(pchar, -300000);
	}
	else
	{
		RemoveCharacterGoods(pchar, GOOD_RUM, 100);
		RemoveCharacterGoods(pchar, GOOD_WINE, 50);
		AddMoneyToCharacter(pchar, -500000);
	}
}

void LongHappy_MarryBegin(string qName) // 
{
	if (CheckAttribute(pchar, "questTemp.LongHappy.DrinkReady"))
	{
	pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу
	chrDisableReloadToLocation = true;
	if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
	else sld = characterFromId("Mary");
	sld.dialog.currentnode = "LongHappy_17";
	ChangeCharacterAddressGroup(sld, "FortFrance_town", "quest", "quest1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	sld = characterFromId("Benua");
	sld.dialog.currentnode = "LH_abbat_19";
	LocatorReloadEnterDisable("FortFrance_town", "reload1_back", true);
	LocatorReloadEnterDisable("FortFrance_town", "reload2_back", true);
	LocatorReloadEnterDisable("FortFrance_town", "gate_back", true);//закрыть выходы из города
		pchar.questTemp.LongHappy.MarryBegin = "true";
	}
	else
	{
		if (CheckAttribute(pchar, "questTemp.LongHappy.MarryRum"))
		{
			log_info(StringFromKey("LongHappy_8"));
			pchar.quest.longhappy_recharge.win_condition.l1 = "location";
			pchar.quest.longhappy_recharge.win_condition.l1.location = "FortFrance_tavern";
			pchar.quest.longhappy_recharge.function = "LongHappy_MarrySPRecharge";
		}
		else
		{
			log_info(StringFromKey("LongHappy_9"));
			pchar.quest.longhappy_recharge.win_condition.l1 = "location";
			pchar.quest.longhappy_recharge.win_condition.l1.location = "Martinique";
			pchar.quest.longhappy_recharge.function = "LongHappy_MarrySPRecharge";
		}
	}
}

void LongHappy_MarrySPRecharge(string qName) // 
{
	pchar.quest.longhappy_fortfrance2.win_condition.l1 = "location";
	pchar.quest.longhappy_fortfrance2.win_condition.l1.location = "FortFrance_town";
	pchar.quest.longhappy_fortfrance2.function = "LongHappy_MarryBegin";
}

void LongHappy_MarryMusic(string qName) // 
{
	ResetSound();
	SetMusic("music_marry");
	PlaySound("ambient\church\zvon.wav");
}

void LongHappy_MarryKiss() // 
{
	SetLaunchFrameFormParam("", "", 0, 5);
	SetLaunchFrameFormPic("loading\inside\kiss.tga");
	LaunchFrameForm();
	WaitDate("", 0, 0, 0, 0, 10); //крутим время
	RecalculateJumpTable();
	// всех не готовых - к разговору
	if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
	else sld = characterFromId("Mary");
	sld.dialog.currentnode = "LongHappy_34";
	LAi_SetStayType(sld);
	sld = characterFromId("Benua");
	sld.dialog.currentnode = "LH_abbat_37";
	LAi_SetStayType(sld);
	DoQuestFunctionDelay("LongHappy_MarryMusic", 5.1);
}

void LongHappy_MarryComplete() // 
{
	chrDisableReloadToLocation = false;
	// ориентируем на ночь
	int iTime, iAddTime;
	iTime = sti(environment.time);
	if (iTime >= 21) iAddTime = 24 - iTime + 1;
	if (iTime < 7) iAddTime = iTime + 13;
	if (iTime >= 7 && iTime < 21) iAddTime = 24 - iTime + 1;
	StoreDayUpdate();
	WaitDate("",0,0,0,iAddtime,5);
	RecalculateJumpTable();
	RefreshWeather();
	RefreshLandTime();
	pchar.quest.longhappy_marry_complete.win_condition.l1 = "ExitFromLocation";
	pchar.quest.longhappy_marry_complete.win_condition.l1.location = pchar.location;
	pchar.quest.longhappy_marry_complete.function = "LongHappy_MarryClear";
	if (!CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
	{
	pchar.quest.longhappy_marry_complete1.win_condition.l1 = "Ship_location";
	pchar.quest.longhappy_marry_complete1.win_condition.l1.location = "Pirates_town";
	pchar.quest.longhappy_marry_complete1.function = "LongHappy_IslaTesoroArrive";
	pchar.quest.longhappy_marry_complete2.win_condition.l1 = "location";
	pchar.quest.longhappy_marry_complete2.win_condition.l1.location = "Bermudes";
	pchar.quest.longhappy_marry_complete2.function = "LongHappy_IslaTesoroSetShips";
	}
	pchar.questTemp.LongHappy = "marry_done";
	if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) Achievment_Set("ach_81");
	else Achievment_Set("ach_80");
}

void LongHappy_MarryClear(string qName) // 
{
	bDisableCharacterMenu = false;
	InterfaceStates.Buttons.Save.enable = true;
	DeleteAttribute(pchar, "GenQuest.CantRun");
	CheckAndSetOverloadMode(GetMainCharacter());
	DeleteAttribute(pchar, "GenQuest.FrameLockEsc"); 
	LocatorReloadEnterDisable("FortFrance_town", "reload1_back", false);
	LocatorReloadEnterDisable("FortFrance_town", "reload2_back", false);
	LocatorReloadEnterDisable("FortFrance_town", "gate_back", false);
	DeleteAttribute(pchar, "GenQuest.CannotWait");
	sld = characterFromId("FortFrance_Priest");
	ChangeCharacterAddressGroup(sld, "FortFrance_church", "barmen", "stay");
	sld = characterFromId("Benua");
	sld.Dialog.Filename = "Quest\Sharlie\Benua.c";
	sld.dialog.currentnode = "First time";
	LAi_CharacterEnableDialog(sld);
	ChangeCharacterAddressGroup(sld, "FortFrance_church", "reload", "reload2_back");
	LAi_SetStayType(sld);
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	sld = characterFromId("Fadey");
	sld.Dialog.Filename = "Quest\Sharlie\Fadey.c";
	sld.dialog.currentnode = "First time";
	LAi_CharacterEnableDialog(sld);
	ChangeCharacterAddressGroup(sld, "BasTer_houseSp1", "sit", "sit1");
	LAi_SetSitType(sld);
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor")) 
	{
		sld = characterFromId("Noel");
		sld.Dialog.Filename = "Quest\Patria_NPC.c";
		sld.dialog.currentnode = "First time";
		LAi_CharacterEnableDialog(sld);
		ChangeCharacterAddressGroup(sld, "none", "", "");
	}
	else 
	{
		sld = characterFromId("Puancie");
		sld.Dialog.Filename = "Governor\Puancie.c";
		sld.dialog.currentnode = "First time";
		LAi_CharacterEnableDialog(sld);
		ChangeCharacterAddressGroup(sld, "Charles_Roomtownhall", "sit", "sit1");
		LAi_SetHuberType(sld);
		LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	}
	if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
	{
		sld = characterFromId("Svenson");
		LAi_CharacterEnableDialog(sld);
		ChangeCharacterAddressGroup(sld, "none", "", "");
	}
	sld = characterFromId("Gladis");
	sld.Dialog.Filename = "Quest\Saga\Gladis.c";
	sld.dialog.currentnode = "First time";
	LAi_CharacterEnableDialog(sld);
	ChangeCharacterAddressGroup(sld, "SantaCatalina_houseSp3", "goto", "goto1");
	LAi_SetOwnerType(sld);
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	sld = characterFromId("FortFrance_Mayor");
	sld.Dialog.Filename = "Common_Mayor.c";
	sld.dialog.currentnode = "First time";
	LAi_CharacterEnableDialog(sld);
	ChangeCharacterAddressGroup(sld, "FortFrance_townhall", "sit", "sit1");
	LAi_SetHuberType(sld);
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	sld = characterFromId("BasTer_Mayor");
	sld.Dialog.Filename = "Common_Mayor.c";
	sld.dialog.currentnode = "First time";
	LAi_CharacterEnableDialog(sld);
	ChangeCharacterAddressGroup(sld, "BasTer_townhall", "sit", "sit1");
	LAi_SetHuberType(sld);
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	sld = characterFromId("PortPax_Mayor");
	sld.Dialog.Filename = "Common_Mayor.c";
	sld.dialog.currentnode = "First time";
	LAi_CharacterEnableDialog(sld);
	ChangeCharacterAddressGroup(sld, "PortPax_townhall", "sit", "sit1");
	LAi_SetHuberType(sld);
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	sld = characterFromId("Tortuga_Mayor");
	sld.Dialog.Filename = "Common_Mayor.c";
	sld.dialog.currentnode = "First time";
	LAi_CharacterEnableDialog(sld);
	ChangeCharacterAddressGroup(sld, "Tortuga_townhall", "sit", "sit1");
	LAi_SetHuberType(sld);
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	sld = characterFromId("PortRoyal_Mayor");
	sld.Dialog.Filename = "Common_Mayor.c";
	sld.dialog.currentnode = "First time";
	LAi_CharacterEnableDialog(sld);
	ChangeCharacterAddressGroup(sld, "PortRoyal_townhall", "sit", "sit1");
	LAi_SetHuberType(sld);
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	if (GetCharacterIndex("LH_Prosper") != -1)
	{
		sld = characterFromId("LH_Prosper");
		ChangeCharacterAddressGroup(sld, "none", "", "");
	}
	if (GetCharacterIndex("Tichingitu") != -1)
	{
		sld = characterFromId("Tichingitu");
		sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
		sld.dialog.currentnode = "Tichingitu_officer";
		LAi_CharacterEnableDialog(sld);
		LAi_SetOfficerType(sld); // fix 01-04-20
	}
	if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) 
	{
		chrDisableReloadToLocation = true;
		DoQuestFunctionDelay("LongHappy_ReloadToSPtavern", 1.8);
	}
}

//--> ------------------------------------ блок празднования в таверне Сен-Пьер -------------------------------------------
void LongHappy_ReloadToSPtavern(string qName)
{
	DoQuestReloadToLocation("FortFrance_tavern", "reload", "reload1", "LongHappy_InSPtavern");
}

//<-- блок празднования в таверне Сен-Пьер

void LongHappy_IslaTesoroSetShips(string qName)
{
	LAi_LocationDisableOfficersGen("Pirates_town", true);
	LAi_LocationDisableOfficersGen("Bermudes_Dungeon", true);
	pchar.questTemp.LongHappy.InTavern = "true";
	bQuestDisableMapEnter = true;//закрыть карту
	pchar.GenQuest.MapClosedNoBattle = true;
	// корвет Свенсона
	sld = GetCharacter(NPC_GenerateCharacter("LH_Svenson_sea", "Svenson", "man", "man", 45, PIRATE, -1, true, "quest"));
	FantomMakeCoolSailor(sld, SHIP_CORVETTE, StringFromKey("LongHappy_10"), CANNON_TYPE_CANNON_LBS20, 110, 110, 110);
	FantomMakeCoolFighter(sld, 45, 100, 100, "blade_21", "pistol5", "bullet", 400);
	sld.name = StringFromKey("LongHappy_11");
	sld.lastname = StringFromKey("LongHappy_12");
	sld.Abordage.Enable = false;
	sld.AlwaysFriend = true;
	sld.ShipEnemyDisable = true; 
	LAi_SetImmortal(sld, true); // сплошная защита от дурака
	sld.DontDeskTalk = true;
	sld.nation = PIRATE;
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	sld.AlwaysSandbankManeuver = true;
	sld.ship.Crew.Morale = 95;
	sld.Ship.Crew.Exp.Sailors = 95;
	sld.Ship.Crew.Exp.Cannoners = 95;
	sld.Ship.Crew.Exp.Soldiers = 95;
	SetCharacterPerk(sld, "MusketsShoot");
	RealShips[sti(sld.Ship.Type)].ship.upgrades.hull = 1;
	Group_AddCharacter("Barons_SeaGroup", "LH_Svenson_sea");
	// фрегат Тиракса
	Group_FindOrCreateGroup("Barons_SeaGroup");
	sld = GetCharacter(NPC_GenerateCharacter("LH_Terrax_sea", "Terrax", "man", "man", 45, PIRATE, -1, true, "quest"));
	FantomMakeCoolSailor(sld, SHIP_FRIGATE, StringFromKey("LongHappy_13"), CANNON_TYPE_CANNON_LBS24, 110, 110, 110);
	FantomMakeCoolFighter(sld, 45, 100, 100, "blade_21", "pistol5", "bullet", 400);
	sld.name = StringFromKey("LongHappy_14");
	sld.lastname = StringFromKey("LongHappy_15");
	sld.Abordage.Enable = false;
	sld.AlwaysFriend = true;
	sld.ShipEnemyDisable = true; 
	LAi_SetImmortal(sld, true); // сплошная защита от дурака
	sld.DontDeskTalk = true;
	sld.nation = PIRATE;
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	sld.AlwaysSandbankManeuver = true;
	sld.ship.Crew.Morale = 95;
	sld.Ship.Crew.Exp.Sailors = 95;
	sld.Ship.Crew.Exp.Cannoners = 95;
	sld.Ship.Crew.Exp.Soldiers = 95;
	SetCharacterPerk(sld, "MusketsShoot");
	RealShips[sti(sld.Ship.Type)].ship.upgrades.hull = 1;
	Group_AddCharacter("Barons_SeaGroup", "LH_Terrax_sea");
	// фрегат Додсона
	if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie"))
	{
		sld = GetCharacter(NPC_GenerateCharacter("LH_Dodson_sea", "Shark", "man", "man", 45, PIRATE, -1, true, "quest"));
		if(CheckAttribute(pchar, "questTemp.SharkGoldFleet.KGBB"))
		{
			FantomMakeCoolSailor(sld, SHIP_FRIGATE_H, pchar.questTemp.SharkGoldFleet.KGBB, CANNON_TYPE_CANNON_LBS36, 105, 105, 105);
			if(CheckAttribute(&RealShips[sti(sld.Ship.Type)], "Tuning.Capacity"))
			DeleteAttribute(&RealShips[sti(sld.Ship.Type)], "Tuning.Capacity")); 
			RealShips[sti(sld.Ship.Type)].MaxCaliber = 36;
			RealShips[sti(sld.Ship.Type)].CannonsQuantity = 50;
			RealShips[sti(sld.Ship.Type)].CannonsQuantityMin = 50;
			RealShips[sti(sld.Ship.Type)].CannonsQuantityMax = 50;
			RealShips[sti(sld.Ship.Type)].CannonDiff = 0;
			SetShipCannonsDamagesNull(sld);
			RealShips[sti(sld.Ship.Type)].SpeedRate = 16.0;
			RealShips[sti(sld.Ship.Type)].TurnRate = 35.0;
			RealShips[sti(sld.Ship.Type)].MinCrew = 50; 
			RealShips[sti(sld.Ship.Type)].OptCrew = 408; 
			RealShips[sti(sld.Ship.Type)].MaxCrew = 510; 
			RealShips[sti(sld.Ship.Type)].HP = 6000;
			RealShips[sti(sld.Ship.Type)].ship.upgrades.hull = 1;
			sld.ship.HP = 6000;
			SetSailsColor(sld, 8);//черный парус
			UpgradeShipParameter(sld, "SpeedRate");//апгрейдить скорость
			UpgradeShipParameter(sld, "Capacity");//апгрейдить трюм
			RealShips[sti(sld.Ship.Type)].Capacity = 6000;
		}
		else
		{
			FantomMakeCoolSailor(sld, SHIP_FRIGATE_H, StringFromKey("LongHappy_16"), CANNON_TYPE_CANNON_LBS32, 105, 105, 105);
		}
		FantomMakeCoolFighter(sld, 45, 100, 100, "blade_21", "pistol5", "bullet", 100);
		sld.name = StringFromKey("LongHappy_17");
		sld.lastname = StringFromKey("LongHappy_18");
		sld.Abordage.Enable = false;
		sld.AlwaysFriend = true;
		sld.ShipEnemyDisable = true; 
		LAi_SetImmortal(sld, true); // сплошная защита от дурака
		sld.DontDeskTalk = true;
		sld.nation = PIRATE;
		sld.DontRansackCaptain = true;
		sld.AnalizeShips = true;
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		sld.AlwaysSandbankManeuver = true;
		sld.ship.Crew.Morale = 95;
		sld.Ship.Crew.Exp.Sailors = 95;
		sld.Ship.Crew.Exp.Cannoners = 95;
		sld.Ship.Crew.Exp.Soldiers = 95;
		SetCharacterPerk(sld, "MusketsShoot");
		Group_AddCharacter("Barons_SeaGroup", "LH_Dodson_sea");
	}
	Group_SetGroupCommander("Barons_SeaGroup", "LH_Svenson_sea");
	Group_SetAddress("Barons_SeaGroup", "Bermudes", "quest_ships", "quest_ship_2");
	Group_SetTaskNone("Barons_SeaGroup");
}

void LongHappy_IslaTesoroArrive(string qName) // 
{
	pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу
	chrDisableReloadToLocation = true;
	// меняем внутрянку таверны и открываем её
	int n = Findlocation("Pirates_Tavern");
	locations[n].filespath.models = "locations\inside\tavern03";
	locations[n].models.always.tavern = "tavern03";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.locators = "tavern03_locators";
	locations[n].models.always.window = "tavern03_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "tavern03_patch";
	//Night
	locations[n].models.night.charactersPatch = "tavern03_patch";
	LocatorReloadEnterDisable("Pirates_town", "reload4_back", false);
	LAi_LocationDisableOfficersGen("Pirates_tavern", true);
	// меняем комнату в резиденции
	n = Findlocation("Pirates_townhall");
	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "Location_reserve_04";
	n = Findlocation("Location_reserve_04");
	locations[n].id.label = "Room";
	locations[n].filespath.models = "locations\inside\Doubleflour_house";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].townsack = "Pirates";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Bermudes";
	//Always
	locations[n].filespath.models = "locations\inside\Doubleflour_house";
	DeleteAttribute(&locations[n], "models");
	DeleteAttribute(&locations[n], "reload");
	locations[n].models.always.largehouse01 = "LH_Floor2";
	locations[n].models.always.largehouse01.level = 65538;
	locations[n].models.always.locators = "LH_Floor2_locators";
	Locations[n].models.always.largehouse01windows = "LH_Floor2_window";
	Locations[n].models.always.largehouse01windows.tech = "LocationWindows";
	locations[n].models.always.largehouse01windows.level = 65539;
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "LH_Floor2_patch";
	//Night
	locations[n].models.night.fonar = "LH_Floor2_fn";
	locations[n].models.night.charactersPatch = "LH_Floor2_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Pirates_townhall";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "House";
	// вычистить ненужных статиков
	sld = characterFromId("Pirates_tavernkeeper");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	sld = characterFromId("Pirates_waitress");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	sld = characterFromId("Norman");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	// Тиракс встречает
	sld = characterFromId("Terrax");
	sld.Dialog.Filename = "Quest\LongHappy.c";
	sld.dialog.currentnode = "Terrax";
	ChangeCharacterAddressGroup(sld, "Pirates_town", "quest", "quest1"); // определить локатор
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void LongHappy_IslaTesoroToVine()
{
	pchar.questTemp.LongHappy.Continue = "true";
	SetLaunchFrameFormParam(StringFromKey("LongHappy_19", NewStr()), "", 0.1, 5.0);
	LaunchFrameForm();
	WaitDate("", 0, 0, 0, 2, 0);
	sld = characterFromId("Svenson");
	sld.dialog.currentnode = "Svenson_12";
	if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
	else sld = characterFromId("Mary");
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, "Location_reserve_04", "goto", "goto4");
	sld = characterFromId("Danielle");
	ChangeCharacterAddressGroup(sld, "Location_reserve_04", "goto", "goto2");
	if (GetCharacterIndex("Tichingitu") != -1)
	{
		sld = characterFromId("Tichingitu");
		DeleteAttribute(sld, "Payment");
		RemovePassenger(pchar, sld); // вывести из офицеров
		LAi_SetStayType(sld);
		if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Rum")) ChangeCharacterAddressGroup(sld, "Shore_ship1", "randitem", "randitem2");
		else ChangeCharacterAddressGroup(sld, "Pirates_town", "quest", "quest1"); 
	}
	AddQuestRecord("LongHappy", "15");
}

void LongHappy_IslaTesoroToVineGo()
{
	sld = characterFromId("Nathaniel");
	sld.dialog.currentnode = "Nathaniel_4";
	ChangeCharacterAddressGroup(sld, "Pirates_Tavern", "tables", "stay1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	// ориентируем на ночь
	int iTime, iAddTime;
	iTime = sti(environment.time);
	if (iTime >= 21) iAddTime = 24 - iTime + 1;
	if (iTime < 7) iAddTime = iTime + 13;
	if (iTime >= 7 && iTime < 21) iAddTime = 24 - iTime + 1;
	StoreDayUpdate();
	WaitDate("",0,0,0,iAddtime,5);
	RecalculateJumpTable();
	RefreshWeather();
	RefreshLandTime();
}

void LongHappy_IslaTesoroToAlexus(string qName) // 
{
	int n = Findlocation("Pirates_town");
	DeleteAttribute(&locations[n], "reload.l5.close_for_night");
	LocatorReloadEnterDisable("Pirates_town", "reload5_back", false);
	DeleteAttribute(&locations[n], "reload.l6.close_for_night");
	LocatorReloadEnterDisable("Pirates_town", "reload1_back", true);
	LocatorReloadEnterDisable("Pirates_town", "reload3_back", true);
	LocatorReloadEnterDisable("Pirates_town", "reload6_back", true);
	LocatorReloadEnterDisable("Pirates_town", "houseH1", true);
	LocatorReloadEnterDisable("Pirates_town", "houseSp1", true);
	LocatorReloadEnterDisable("Pirates_town", "houseS1", true);
	LocatorReloadEnterDisable("Pirates_town", "houseF1", true);
	LocatorReloadEnterDisable("Bermudes_Dungeon", "reload2_back", true);
	LAi_LocationDisableOfficersGen("Pirates_town", true);
	for(int i=0; i<MAX_LOCATIONS; i++)
	{	
		sld = &characters[i];
		if (sld.location == "Pirates_town" && CheckAttribute(sld, "CityType"))
		{
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld.lifeday = 0;
		}
	}
	if (GetCharacterIndex("Tichingitu") != -1) // fix 25-03-20
	{
	if (!CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Rum"))
	{
		chrDisableReloadToLocation = true;
		sld = characterFromId("Tichingitu");
		sld.dialog.currentnode = "Tichingitu_5";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	}
	sld = characterFromId("Pirates_shipyarder");
	sld.Dialog.Filename = "Quest\LongHappy.c";
	sld.dialog.currentnode = "Alexus";
}

void LongHappy_IslaTesoroDungeon(string qName) // 
{
	chrDisableReloadToLocation = true;
	sld = characterFromId("Nathaniel");
	sld.dialog.currentnode = "Nathaniel_7";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void LongHappy_SetBandosInDungeon() // 
{
	LAi_group_Delete("EnemyFight");
	for (int i=1; i<=7; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("LH_DungeonPirate_"+i, "citiz_"+(40+i), "man", "man", 35, PIRATE, -1, false, "soldier"));
		FantomMakeCoolFighter(sld, 35, 60, 60, "blade_10", "pistol1", "bullet", 200);
		if (i == 1)
		{
			sld.Dialog.Filename = "Quest\LongHappy.c";
			sld.dialog.currentnode = "DungeonPirate";
		}
		else LAi_CharacterDisableDialog(sld);
		ChangeCharacterAddressGroup(sld, "Bermudes_Dungeon", "reload", "reload2_back");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
}

void LongHappy_BandosInDungeonFight() // 
{
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
	sld = characterFromId("Nathaniel");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	if (GetCharacterIndex("Tichingitu") != -1 && !CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Rum")) // fix 25-03-20
	{
		sld = characterFromId("Tichingitu");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	for (int i=1; i<=7; i++)
	{
		sld = characterFromId("LH_DungeonPirate_"+i);
		if (i == 7)
		{
			LAi_SetImmortal(sld, true);
			sld.lifeday = 0;
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "", 20.0);
		}
		else
		{
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "LongHappy_BandosInDungeonAfterFight");
	LAi_SetFightMode(pchar, true);
}

void LongHappy_TavernAlarm(string qName) // 
{
	chrDisableReloadToLocation = true;
	sld = characterFromId("Svenson");
	sld.dialog.currentnode = "Svenson_17";
	ChangeCharacterAddressGroup(sld, "Pirates_tavern", "goto", "goto1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	// фикс офицера Гамбита-абордажника и офицера-Бейкера
	if (CheckAttribute(pchar, "questTemp.LongHappy.HambitOfficer") && IsOfficer(characterFromId(pchar.questTemp.LongHappy.HambitOfficer)))
	{
		sld = characterFromId(pchar.questTemp.LongHappy.HambitOfficer);
		ChangeCharacterAddressGroup(sld, "Pirates_tavern", "tables", "stay4");
		LAi_SetOfficerType(sld);
		if (pchar.questTemp.LongHappy.HambitOfficer == "Longway") sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
		if (pchar.questTemp.LongHappy.HambitOfficer == "Knippel") sld.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
		if (pchar.questTemp.LongHappy.HambitOfficer == "Tonzag") sld.Dialog.Filename = "Quest\HollandGambit\Tonzag.c";
		sld.dialog.currentnode = sld.id+"_officer";
	}
	if (CheckAttribute(pchar, "questTemp.LongHappy.BigMarry") && GetCharacterIndex("Baker") != -1) //&& IsOfficer(characterFromId("Baker"))
	{
		sld = characterFromId("Baker");
		ChangeCharacterAddressGroup(sld, "Pirates_tavern", "tables", "stay6");
		LAi_SetOfficerType(sld);
		sld.Dialog.Filename = "Quest\Saga\Baker.c";
		sld.dialog.currentnode = "Baker_officer";
	}
}

void LongHappy_TavernFight() // 
{
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
	LAi_group_Delete("EnemyFight");
	// всех на ноги и поставить, Джино спрятать
	sld = characterFromId("Jino");
	LAi_SetStayType(sld);
	ChangeCharacterAddressGroup(sld, "Pirates_tavern_upstairs", "goto", "goto1");
	for(int i=0; i<MAX_LOCATIONS; i++)
	{	
		sld = &characters[i];
		if (sld.location == "Pirates_tavern" && sld.id != "Blaze") 
		{
			LAi_SetWarriorType(sld);
			if (sld.id != "Terrax") ChangeCharacterAddressGroup(sld, "Pirates_tavern", "tables", "stay"+(rand(7+1)));
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
	}
	// пиратусы
	for (i=1; i<=10; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("LH_TavernPirate_"+i, "citiz_"+(40+i), "man", "man", 35, PIRATE, -1, false, "soldier"));
		FantomMakeCoolFighter(sld, 35, 70, 70, "blade_10", "pistol1", "bullet", 150);
		ChangeCharacterAddressGroup(sld, "Pirates_tavern", "reload", "reload1");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "LongHappy_TavernAfterFight");
	LAi_SetFightMode(pchar, true);
}

void LongHappy_TavernReload() // 
{
	LAi_LocationDisableOfficersGen("Pirates_town", false);
	LAi_LocationDisableOfficersGen("Bermudes_Dungeon", false);
	LocatorReloadEnterDisable("Bermudes_Dungeon", "reload2_back", false);
	for(int i=0; i<MAX_LOCATIONS; i++)
	{	
		sld = &characters[i];
		if (sld.location == "Pirates_tavern" && sld.id != "Blaze") 
		{
			ChangeCharacterAddressGroup(sld, "Pirates_town", "rld", "loc1");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
	}
	DoQuestReloadToLocation("Pirates_town", "reload", "reload4", "LongHappy_IslaTesoroTownFight");
}

void LongHappy_TownRepose() // 
{
	// Свенсона, Акулу и Тиракса на корабли
	sld = characterFromId("Svenson");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
	sld = characterFromId("Terrax");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
	if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie"))
	{
		sld = characterFromId("Dodson");
		LAi_SetActorType(sld);
		LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
	}
	// если есть Венсан - в магазин
	if (CheckAttribute(pchar, "questTemp.LongHappy.BigMarry") && !CheckAttribute(pchar, "questTemp.Saga.DodsonDie"))
	{
		sld = characterFromId("Vensan");
		sld.dialog.currentnode = "Vensan_6";
		ChangeCharacterAddressGroup(sld, "Pirates_store", "goto", "goto1");
		LAi_SetActorType(sld);
	}
	sld = characterFromId("Pirates_trader");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	// Тичингиту если есть - с нами
	if (!CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Rum") && GetCharacterIndex("Tichingitu") != -1)
	{
		sld = characterFromId("Tichingitu");
		if (LAi_GetCharacterHP(sld) > 0)
		{
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			pchar.questTemp.LongHappy.Tichingitu_Warrior = "true";
		}
	}
	// если есть Бейкер не в абордажниках - убираем
	if (CheckAttribute(pchar, "questTemp.LongHappy.BigMarry") && GetCharacterIndex("Baker") != -1 && !IsOfficer(characterFromId("Baker")))
	{
		sld = characterFromId("Baker");
		LAi_SetOfficerType(sld);
		ChangeCharacterAddressGroup(sld, "none", "", "");
	}
	// в резиденцию
	pchar.quest.longhappy_isla_residence.win_condition.l1 = "location";
	pchar.quest.longhappy_isla_residence.win_condition.l1.location = "Pirates_townhall";
	pchar.quest.longhappy_isla_residence.function = "LongHappy_IslaTesoroResidence";
}

void LongHappy_IslaTesoroResidence(string qName) // 
{
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(&Locations[FindLocation("Pirates_townhall")], true);
	for (int i=1; i<=4; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("LH_killer_"+i, "killer_"+i, "man", "man", 35, PIRATE, -1, true, "quest"));
		FantomMakeCoolFighter(sld, 35, 70, 70, "blade_19", "pistol4", "bullet", 250);
		ChangeCharacterAddressGroup(sld, "Pirates_townhall", "goto", "goto"+i);
		LAi_SetActorType(sld);
		if (i == 4)
		{
			sld.Dialog.Filename = "Quest\LongHappy.c";
			sld.dialog.currentnode = "killer";
			LAi_ActorDialogDelay(sld, pchar, "", 2.0);
		}
	}
}

void LongHappy_ResidenceFight() // 
{
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
	sld = characterFromId("Nathaniel");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Warrior"))
	{
		sld = characterFromId("Tichingitu");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	for (int i=1; i<=4; i++)
	{
		sld = characterFromId("LH_killer_"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "LongHappy_ResidenceAfterFight");
	LAi_SetFightMode(pchar, true);
}

void LongHappy_IslaTesoroBedroom(string qName) // 
{
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(&Locations[FindLocation("Location_reserve_04")], true);
	bDisableCharacterMenu = true;//лочим F2
	InterfaceStates.Buttons.Save.enable = false;
	// жены
	sld = characterFromId("Danielle");
	RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
	RemoveCharacterEquip(sld, GUN_ITEM_TYPE);
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, "Location_reserve_04", "goto", "goto2");
	LAi_SetActorType(sld);
	LAi_ActorTurnToLocator(sld, "goto", "goto8");
	if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
	else sld = characterFromId("Mary");
	pchar.questTemp.LongHappy.GBlade = GetCharacterEquipByGroup(sld, BLADE_ITEM_TYPE);
	pchar.questTemp.LongHappy.GGun = GetCharacterEquipByGroup(sld, GUN_ITEM_TYPE);
	RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
	RemoveCharacterEquip(sld, GUN_ITEM_TYPE);
	ChangeCharacterAddressGroup(sld, "Location_reserve_04", "goto", "goto4");
	LAi_SetActorType(sld);
	LAi_ActorTurnToLocator(sld, "goto", "goto8");
	if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim"))
	{
		sld = characterFromId("Nathaniel");
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, "Location_reserve_04", "goto", "goto3");
		LAi_ActorTurnToLocator(sld, "goto", "goto2");
		sld = characterFromId("Tichingitu");
		ChangeCharacterAddressGroup(sld, "none", "", "");
		string sModel = "maskog";
		string sName = StringFromKey("LongHappy_20");
		string animation = "man";
	}
	else
	{
		sld = characterFromId("Nathaniel");
		ChangeCharacterAddressGroup(sld, "none", "", "");
		sModel = "Hawk_2";
		sName = StringFromKey("LongHappy_21");
		animation = "man_B";
	}
	sld = GetCharacter(NPC_GenerateCharacter("LH_Victim", sModel, "man", animation, 20, PIRATE, -1, true, "quest"));
	FantomMakeCoolFighter(sld, 20, 50, 50, "blade_11", "", "bullet", 100);
	sld.name = sName;
	sld.lastname = "";
	sld.DontClearDead = true;
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, "Location_reserve_04", "goto", "goto5");
	LAi_ActorTurnToLocator(sld, "goto", "goto2");
	// Ангерран или Дюссак
	if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angerran") && CharacterIsAlive("Angerran"))  // fix 02-04-20
	{
		sld = characterFromId("Angerran");
		sld.dialog.currentnode = "Shivo";
		LAi_SetImmortal(sld, false);
	}
	else
	{
		sld = GetCharacter(NPC_GenerateCharacter("LH_Dussak", "killer_2", "man", "man", 40, PIRATE, -1, true, "quest"));
		FantomMakeCoolFighter(sld, 40, 70, 70, "blade_20", "pistol6", "bullet", 350);
		sld.name = StringFromKey("LongHappy_22");
		sld.lastname = StringFromKey("LongHappy_23");
		sld.dialog.currentnode = "Dussak";
	}
	sld.Dialog.Filename = "Quest\LongHappy.c";
	ChangeCharacterAddressGroup(sld, "Location_reserve_04", "goto", "goto1");
	LAi_SetActorType(sld);
	// ГГ
	LAi_SetActorType(pchar);
	LAi_ActorGoToLocator(pchar, "goto", "goto8", "LongHappy_IslaTesoroBedroom", -1);
}

void LongHappy_BedroomShot() // 
{
	LAi_SetActorType(pchar);
	sld = characterFromId("LH_Victim");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocator(sld, "goto", "goto1", "", -1);
	DoQuestCheckDelay("LongHappy_BedroomShot", 1.0);
}

void LongHappy_BedroomFight() // 
{
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
	LAi_SetPlayerType(pchar);
	if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim"))
	{
		sld = characterFromId("Nathaniel");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angerran") && CharacterIsAlive("Angerran")) sld = characterFromId("Angerran"); // fix 02-04-20
	else sld = characterFromId("LH_Dussak");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "LongHappy_BedroomAfterFight");
	LAi_SetFightMode(pchar, true);
}

void LongHappy_OutOfBedroom() // 
{
	if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
	else sld = characterFromId("Mary");
	string sTemp = sld.name;
	if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angerran") && CharacterIsAlive("Angerran")) AddQuestRecord("LongHappy", "16"); // fix 02-04-20
	else AddQuestRecord("LongHappy", "16_1");
	AddQuestUserData("LongHappy", "sName", sTemp);
	if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim")) sld = characterFromId("Tichingitu");
	else sld = characterFromId("Nathaniel");
	string sName = sld.name;
	AddQuestUserData("LongHappy", "sName1", sName);
	DoQuestReloadToLocation("Pirates_town", "reload", "reload3_back", "LongHappy_FindJinoHurry");
}

void LongHappy_KillersInStore(string qName) // 
{
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(&Locations[FindLocation("Pirates_store")], false);
	sld = characterFromId("Vensan");
	LAi_SetImmortal(sld, false);
	LAi_SetCheckMinHP(sld, 10, true, ""); // скрытое бессмертие
	ChangeCharacterAddressGroup(sld, "Pirates_store", "barmen", "stay");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	for (int i=2; i<=4; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("LH_store_killer_"+i, "killer_"+i, "man", "man", 35, PIRATE, -1, true, "quest"));
		FantomMakeCoolFighter(sld, 35, 70, 70, "blade_19", "pistol4", "bullet", 180);
		ChangeCharacterAddressGroup(sld, "Pirates_store", "goto", "goto"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "LongHappy_StoreAfterFight");
	LAi_SetFightMode(pchar, true);
}

void LongHappy_KillersInTavern(string qName) // 
{
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(&Locations[FindLocation("Pirates_tavern")], true);
	for (int i=1; i<=3; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("LH_tavern_killer_"+i, "killer_"+i, "man", "man", 35, PIRATE, -1, true, "quest"));
		FantomMakeCoolFighter(sld, 35, 70, 70, "blade_19", "pistol4", "bullet", 180);
		ChangeCharacterAddressGroup(sld, "Pirates_tavern", "goto", "goto"+i);
		LAi_SetActorType(sld);
		if (i == 1)
		{
			sld.Dialog.Filename = "Quest\LongHappy.c";
			sld.dialog.currentnode = "killer_1";
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
		}
	}
}

void LongHappy_TavernKillerFight() // 
{
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
	for (int i=1; i<=3; i++)
	{
		sld = characterFromId("LH_tavern_killer_"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "LongHappy_TavernKillerAfterFight");
	LAi_SetFightMode(pchar, true);
}

void LongHappy_FindJinoTavern(string qName) // 
{
	chrDisableReloadToLocation = true;
	sld = characterFromId("Jino");
	sld.dialog.currentnode = "Jino_4";
	LAi_SetActorType(sld);
	LAi_ActorDialogDelay(sld, pchar, "", 1.5);
}

void LongHappy_SeaBattle(string qName) // морская боевка
{
	pchar.quest.longhappy_isla_hurry1.over = "yes"; //снять прерывание на таверну fix 26-03-20
	pchar.quest.longhappy_isla_hurry2.over = "yes"; //снять прерывание на магазин
	int iShip, iCannon, iCrew, hcrew;
	string sModel;
	Island_SetReloadEnableGlobal("Bermudes", false);//закрыть остров	
	DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
	Group_SetAddress("Barons_SeaGroup", "Bermudes", "reload", "reload_1");
	// наша эскадра - Тиракс, Свенсон и Акула
	sld = characterFromId("LH_Terrax_sea");
	LAi_SetImmortal(sld, false);
	sld = characterFromId("LH_Svenson_sea");
	LAi_SetImmortal(sld, false);
	if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie"))
	{
		sld = characterFromId("LH_Dodson_sea");
		LAi_SetImmortal(sld, false);
	}
	if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_alive"))
	{
		AddQuestRecord("LongHappy", "19");
		pchar.questTemp.LongHappy.Terrax.Prisoner = "true";
		sld = characterFromId("LH_Terrax_sea");
		LAi_KillCharacter(sld);
		sld = characterFromId("LH_Svenson_sea");
		hcrew = GetMaxCrewQuantity(sld);
		iCrew = sti((0.3+frand(0.1))*hcrew);
		SetCrewQuantityOverMax(sld, iCrew);
		sld.ship.HP = sti(sld.ship.HP)/2;
		if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie"))
		{
			sld = characterFromId("LH_Dodson_sea");
			hcrew = GetMaxCrewQuantity(sld);
			iCrew = sti((0.3+frand(0.1))*hcrew);
			SetCrewQuantityOverMax(sld, iCrew);
			sld.ship.HP = sti(sld.ship.HP)/2;
		}
	}
	else
	{
		AddQuestRecord("LongHappy", "20");
		sld = characterFromId("LH_Terrax_sea");
		hcrew = GetMaxCrewQuantity(sld);
		iCrew = sti((0.5+frand(0.1))*hcrew);
		SetCrewQuantityOverMax(sld, iCrew);
		sld.ship.HP = sti(sld.ship.HP)-makeint(sti(sld.ship.HP)/4);
		sld = characterFromId("LH_Svenson_sea");
		hcrew = GetMaxCrewQuantity(sld);
		iCrew = sti((0.5+frand(0.1))*hcrew);
		SetCrewQuantityOverMax(sld, iCrew);
		sld.ship.HP = sti(sld.ship.HP)-makeint(sti(sld.ship.HP)/4);
		if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie"))
		{
			sld = characterFromId("LH_Dodson_sea");
			hcrew = GetMaxCrewQuantity(sld);
			iCrew = sti((0.5+frand(0.1))*hcrew);
			SetCrewQuantityOverMax(sld, iCrew);
			sld.ship.HP = sti(sld.ship.HP)-makeint(sti(sld.ship.HP)/4);
		}
	}
	// эскадра ГГ fix 26-03-20 убрано
	// эскадра Барбазона. 4 корабля.
	sld = characterFromId("Barbazon");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	Group_FindOrCreateGroup("LH_BarbazonSeaGroup");
	for (int i=1; i<=4; i++)
	{
		switch (i)
		{
			case 1:
				iShip = SHIP_LINESHIP;
				iCannon = CANNON_TYPE_CANNON_LBS32;
				sModel = "Barbazon";
			break;
			
			case 2:
				iShip = SHIP_FRIGATE_H;
				iCannon = CANNON_TYPE_CANNON_LBS24;
				sModel = "mercen_27";
			break;
			
			case 3:
				iShip = SHIP_FRIGATE;
				iCannon = CANNON_TYPE_CANNON_LBS24;
				sModel = "mercen_20";
			break;
			
			case 4:
				iShip = SHIP_CORVETTE;
				iCannon = CANNON_TYPE_CULVERINE_LBS18;
				sModel = "mercen_19";
			break;
		}
		sld = GetCharacter(NPC_GenerateCharacter("LH_BarbSeaCap_"+i, sModel, "man", "man", 50-i*5, PIRATE, -1, true, "quest"));
		FantomMakeCoolSailor(sld, iShip, "", iCannon, 80-i*5, 80-i*5, 80-i*5);
		FantomMakeCoolFighter(sld, 50-i*5, 80-i*5, 80-i*5, LinkRandPhrase("blade_18","blade_19","blade_21"), "pistol5", "bullet", 400-i*25);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		sld.DontRansackCaptain = true;
		sld.AnalizeShips = true;
		sld.AlwaysEnemy = true;
		sld.AlwaysSandbankManeuver = true;
		sld.Ship.Mode = "war";
		sld.ship.Crew.Morale = 70+MOD_SKILL_ENEMY_RATE*3;
		sld.Ship.Crew.Exp.Sailors = 70+MOD_SKILL_ENEMY_RATE*3;
		sld.Ship.Crew.Exp.Cannoners = 70+MOD_SKILL_ENEMY_RATE*3;
		sld.Ship.Crew.Exp.Soldiers = 70+MOD_SKILL_ENEMY_RATE*3;
		if (MOD_SKILL_ENEMY_RATE > 2) SetCharacterPerk(sld, "MusketsShoot");
		if (i == 1) 
		{
			sld.name = StringFromKey("LongHappy_24");
			sld.lastname = StringFromKey("LongHappy_25");
			sld.ship.name = StringFromKey("LongHappy_26");
			sld.MultiFighter = 1.0+MOD_SKILL_ENEMY_RATE/10; // мультифайтер
			GiveItem2Character(sld, "shamshir");
			EquipCharacterbyItem(sld, "shamshir"); // fix 25-03-20
			GiveItem2Character(sld, "howdah");
			EquipCharacterbyItem(sld, "howdah");
			LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "grapeshot");
			TakeNItems(sld, "grapeshot", 5);
			AddItems(sld, "gunpowder", 5);
			RealShips[sti(sld.Ship.Type)].ship.upgrades.hull = 3;
			SetSailsColor(sld, 8);//черный парус
			UpgradeShipParameter(sld, "SpeedRate");//апгрейдить скорость
			UpgradeShipParameter(sld, "TurnRate");//маневренность
			UpgradeShipParameter(sld, "WindAgainstSpeed");//бейд
			hcrew = GetMaxCrewQuantity(sld);
			iCrew = sti(0.9*hcrew);
			SetCrewQuantityOverMax(sld, iCrew);
			sld.ship.HP = sti(sld.ship.HP)-makeint(sti(sld.ship.HP)/10);
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			AddItems(sld, "potion2", 3);
			AddItems(sld, "totem_04", 1);
			AddItems(sld, "totem_11", 1);
		}
		else
		{
			hcrew = GetMaxCrewQuantity(sld);
			iCrew = sti((0.7+frand(0.2))*hcrew);
			SetCrewQuantityOverMax(sld, iCrew);
			sld.ship.HP = sti(sld.ship.HP)-makeint(sti(sld.ship.HP)/(5+rand(5)));
			if (CheckAttribute(pchar, "questTemp.HWIC.Detector"))
			{
				if (pchar.questTemp.HWIC.Detector == "eng_win" && GetCharacterIndex("Knippel") != -1) 
				{
					if (i == 2)
					{
						hcrew = GetMaxCrewQuantity(sld);
						iCrew = sti(0.5*hcrew);
						SetCrewQuantityOverMax(sld, iCrew);
						sld.ship.HP = sti(sld.ship.HP)/2;
					}
				}
			}
		}
		Group_AddCharacter("LH_BarbazonSeaGroup", "LH_BarbSeaCap_"+i);
	}
	Group_SetGroupCommander("LH_BarbazonSeaGroup", "LH_BarbSeaCap_1");
	Group_SetAddress("LH_BarbazonSeaGroup", "Bermudes", "reload", "reload_1");
	Group_SetTaskAttack("LH_BarbazonSeaGroup", "Barons_SeaGroup");
	Group_LockTask("LH_BarbazonSeaGroup");
	
	Group_SetTaskAttack("Barons_SeaGroup", "LH_BarbazonSeaGroup");
	Group_LockTask("Barons_SeaGroup");
	// на Барбазона
	pchar.quest.longhappy_destroy_barbazon.win_condition.l1 = "Group_Death";
	pchar.quest.longhappy_destroy_barbazon.win_condition.l1.group = "LH_BarbazonSeaGroup";
	pchar.quest.longhappy_destroy_barbazon.function = "LongHappy_AfterSeaBattle";
	// на Свенсона и Акулу
	pchar.quest.longhappy_destroy_svensonship.win_condition.l1 = "NPC_Death";
	pchar.quest.longhappy_destroy_svensonship.win_condition.l1.character = "LH_Svenson_sea";
	pchar.quest.longhappy_destroy_svensonship.function = "LongHappy_SvensonsShipSink";
	if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie"))
	{
		pchar.quest.longhappy_destroy_sharkship.win_condition.l1 = "NPC_Death";
		pchar.quest.longhappy_destroy_sharkship.win_condition.l1.character = "LH_Dodson_sea";
		pchar.quest.longhappy_destroy_sharkship.function = "LongHappy_SharksShipSink";
	}
	if (!CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner"))
	{
		pchar.quest.longhappy_destroy_terraxship.win_condition.l1 = "NPC_Death";
		pchar.quest.longhappy_destroy_terraxship.win_condition.l1.character = "LH_Terrax_sea";
		pchar.quest.longhappy_destroy_terraxship.function = "LongHappy_TerraxShipSink";
	}
	DoQuestFunctionDelay("LongHappy_BaronsShipsCommand", 3.0);
}

void LongHappy_SvensonsShipSink(string qName) // 
{
	log_info(StringFromKey("LongHappy_27"));
	pchar.questTemp.LongHappy.SvensonsShipSink = "true";
}

void LongHappy_SharksShipSink(string qName) // 
{
	log_info(StringFromKey("LongHappy_28"));
	pchar.questTemp.LongHappy.SharksShipSink = "true";
}

void LongHappy_TerraxShipSink(string qName) // 
{
	log_info(StringFromKey("LongHappy_29"));
	pchar.questTemp.LongHappy.TerraxShipSink = "true";
}

void LongHappy_BaronsShipsCommand(string qName) // 
{
	ref chr = CharacterFromID("LH_BarbSeaCap_2");
	sld = CharacterFromID("LH_Svenson_sea");
	SetCharacterRemovable(sld, false);
	sld.CompanionEnemyEnable = false; //всегда друзья
	SetCompanionIndex(pchar, -1, sti(sld.index));
	sld.loyality = MAX_LOYALITY;
	Ship_SetTaskAttack(SECONDARY_TASK, sti(sld.index), sti(chr.index));
	if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie"))
	{
		sld = CharacterFromID("LH_Dodson_sea");
		SetCharacterRemovable(sld, false);
		sld.CompanionEnemyEnable = false; //всегда друзья
		SetCompanionIndex(pchar, -1, sti(sld.index));
		sld.loyality = MAX_LOYALITY;
		Ship_SetTaskAttack(SECONDARY_TASK, sti(sld.index), sti(chr.index));
	}
	if (!CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner"))
	{
		sld = CharacterFromID("LH_Terrax_sea");
		SetCharacterRemovable(sld, false);
		sld.CompanionEnemyEnable = false; //всегда друзья
		SetCompanionIndex(pchar, -1, sti(sld.index));
		sld.loyality = MAX_LOYALITY;
		Ship_SetTaskAttack(SECONDARY_TASK, sti(sld.index), sti(chr.index));
	}
}

void LongHappy_AfterSeaBattle(string qName) // 
{
	pchar.quest.longhappy_destroy_svensonship.over = "yes"; 
	pchar.quest.longhappy_destroy_sharkship.over = "yes";
	pchar.quest.longhappy_destroy_terraxship.over = "yes";
	RemoveCharacterCompanion(pchar, characterFromID("LH_Svenson_sea"));
	if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) RemoveCharacterCompanion(pchar, characterFromID("LH_Dodson_sea"));
	if (!CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) RemoveCharacterCompanion(pchar, characterFromID("LH_Terrax_sea"));
	pchar.GenQuest.MapClosedNoBattle = true;
	Island_SetReloadEnableGlobal("Bermudes", true);
	pchar.quest.longhappy_victoria.win_condition.l1 = "Ship_location";
	pchar.quest.longhappy_victoria.win_condition.l1.location = "Pirates_town";
	pchar.quest.longhappy_victoria.function = "LongHappy_Victory";
}

void LongHappy_Victory(string qName) // 
{
	// fix 26-03-20 убрать блокировку локации
	pchar.GenQuest.Hunter2Pause = true;
	Group_DeleteGroup("LH_BarbazonSeaGroup");
	if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim"))
	{
		sld = characterFromId("Nathaniel");
		RemovePassenger(pchar, sld);
	}
	// стереть Джино и Венсана, если не нашли
	if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie") || CheckAttribute(pchar, "questTemp.LongHappy.BigMarry"))
	{
		if (!CheckAttribute(pchar, "questTemp.LongHappy.Vensan_alive")) 
		{
			sld = characterFromId("Vensan");
			sld.lifeday = 0;
			ChangeCharacterAddressGroup(sld, "none", "", "");
		}
	}
	if (!CheckAttribute(pchar, "questTemp.LongHappy.Jino_alive"))
	{
		sld = characterFromId("Jino");
		sld.lifeday = 0; // fix 26-03-20
		ChangeCharacterAddressGroup(sld, "none", "", "");
	}
	sld = characterFromId("Svenson");
	sld.dialog.currentnode = "Svenson_22";
	ChangeCharacterAddressGroup(sld, "Pirates_town", "quest", "quest1"); // определить локатор
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void LongHappy_LogBook()
{
	AddQuestRecord("LongHappy", "21");
	if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie") || CheckAttribute(pchar, "questTemp.LongHappy.BigMarry"))
	{
		if (!CheckAttribute(pchar, "questTemp.LongHappy.Vensan_alive")) AddQuestUserData("LongHappy", "sText1", StringFromKey("LongHappy_30"));
	}
	if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Lost")) AddQuestUserData("LongHappy", "sText2", StringFromKey("LongHappy_31"));
	if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died") && !CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died")) AddQuestUserData("LongHappy", "sText3", StringFromKey("LongHappy_32"));
	if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died")) AddQuestUserData("LongHappy", "sText4", StringFromKey("LongHappy_33"));
	if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Rum")) AddQuestUserData("LongHappy", "sText5", StringFromKey("LongHappy_34"));
}

void LongHappy_IslaTesoroClear()
{
	bDisableFastReload = false;//открыть переход 29-03-20
	// открыть локаторы всех помещений и нормализовать их
	int n = Findlocation("Pirates_town");
	LocatorReloadEnterDisable("Pirates_town", "reload3_back", false);
	LocatorReloadEnterDisable("Pirates_town", "reload4_back", false);
	LocatorReloadEnterDisable("Pirates_town", "reload5_back", false);
	locations[n].reload.l5.close_for_night = 1;
	LocatorReloadEnterDisable("Pirates_town", "reload6_back", false);
	locations[n].reload.l6.close_for_night = 1;
	LocatorReloadEnterDisable("Pirates_town", "houseH1", false);
	LocatorReloadEnterDisable("Pirates_town", "houseSp1", false);
	LocatorReloadEnterDisable("Pirates_town", "houseS1", false);
	LocatorReloadEnterDisable("Pirates_town", "houseF1", false);
	LocatorReloadEnterDisable("Pirates_townhall", "reload1_back", false);
	// вернуть всех положенных неписей Исла Тесоро на места
	sld = characterFromId("Pirates_tavernkeeper");
	ChangeCharacterAddressGroup(sld, "Pirates_Tavern", "barmen", "stay");
	sld = characterFromId("Pirates_waitress");
	ChangeCharacterAddressGroup(sld, "Pirates_Tavern", "waitress", "barmen");
	sld = characterFromId("Pirates_trader");
	ChangeCharacterAddressGroup(sld, "Pirates_Store", "barmen", "stay");
	sld = characterFromId("Pirates_shipyarder");
	sld.Dialog.Filename = "Common_Shipyard.c";
	sld.dialog.currentnode = "First time";
	ChangeCharacterAddressGroup(sld, "Pirates_Shipyard", "goto", "goto3");
	sld = characterFromId("Norman");
	ChangeCharacterAddressGroup(sld, "Pirates_town", "goto", "goto1");
	// вернуть всех гостей по домам, кроме Свенсона
	Group_DeleteGroup("Barons_SeaGroup");
	// Тиракс
	if (!CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Lost"))
	{
		sld = characterFromId("Terrax");
		sld.Dialog.Filename = "Mayor\Terrax.c";
		sld.dialog.currentnode = "I_know_you_good";
		if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) ChangeCharacterAddressGroup(sld, "LaVega_townhall", "sit", "sit1");
		else ChangeCharacterAddressGroup(sld, "Pirates_townhall", "sit", "sit1");
		LAi_SetHuberType(sld);
		LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
	}
	// Натаниэль и Даниэль
	sld = characterFromId("Nathaniel");
	sld.Dialog.Filename = "Quest\Saga\Nathaniel.c";
	sld.dialog.currentnode = "marun_town_4";
	ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "sit", "sit1");
	LAi_SetHuberType(sld);
	LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
	sld = characterFromId("Danielle");
	sld.Dialog.Filename = "Quest\Saga\Danielle.c"; // fix 25-03-20
	sld.dialog.currentnode = "marun_town_3";
	ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "goto", "goto1");
	LAi_SetStayType(sld);
	LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
	// Додсон
	if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie"))
	{
		sld = characterFromId("Dodson");
		sld.Dialog.Filename = "Quest\LSC\Dodson.c";
		sld.dialog.currentnode = "First time";
		ChangeCharacterAddressGroup(sld, "Pirates_townhall", "sit", "sit1");
		LAi_SetHuberType(sld);
		LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
	}
	// Джино
	if (!CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
	{
		sld = characterFromId("Jino");
		sld.Dialog.Filename = "Quest\HollandGambit\Jino.c";
		sld.dialog.currentnode = "First time";
		ChangeCharacterAddressGroup(sld, "SentJons_HouseF3_Room", "goto", "goto1");
		LAi_SetCitizenType(sld);
		LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	}
	// Венсан
	if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie") && CheckAttribute(pchar, "questTemp.LongHappy.Vensan_alive"))
	{
		sld = characterFromId("Vensan");
		sld.dialog.FileName = "Mayor\LaVega_Mayor.c";
		sld.dialog.currentnode = "I_know_you_good";
		sld.greeting = "town_pirate";
		ChangeCharacterAddressGroup(sld, "LaVega_townhall", "sit", "sit1");
		LAi_SetHuberType(sld);
		LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
		LAi_SetImmortal(sld, true);
	}
	// снять скрытое бессмертие
	if (GetCharacterIndex("Tichingitu") != -1)
	{
		sld = characterFromId("Tichingitu");
		LAi_RemoveCheckMinHP(sld);
		LAi_SetImmortal(sld, false);
	}
	if (GetCharacterIndex("Baker") != -1)
	{
		sld = characterFromId("Baker");
		LAi_RemoveCheckMinHP(sld);
		LAi_SetImmortal(sld, false);
	}
	// мадам де Мор belamour
	if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
	{
		pchar.quest.Mary_giveme_sex.win_condition.l1 = "Timer";
		pchar.quest.Mary_giveme_sex.win_condition.l1.date.hour  = sti(GetTime());
		pchar.quest.Mary_giveme_sex.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 14);
		pchar.quest.Mary_giveme_sex.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 14);
		pchar.quest.Mary_giveme_sex.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 14);
		pchar.quest.Mary_giveme_sex.function = "Mary_GiveMeSex";
		sld = characterFromId("Mary");
	}
	else sld = characterFromId("Helena");
	LAi_RemoveCheckMinHP(sld);
	LAi_SetImmortal(sld, false);
	sld.CompanionDisable = false; //Desperado: можно назначать Элен компаньоном
	DeleteAttribute(pchar, "questTemp.LongHappy.InTavern");
	SetFunctionTimerCondition("LongHappy_SetLefransuaBoss", 0, 0, 30, false); // новый босс Ле Франсуа
}

void LongHappy_SetShoreGirl(string qName) // 
{
	chrDisableReloadToLocation = true;
	pchar.GenQuest.Hunter2Pause = true;
	sld = characterFromId("Tichingitu");
	sld.dialog.currentnode = "Tichingitu_10";
	ChangeCharacterAddressGroup(sld, "Shore_ship1", "goto", "goto6");
	LAi_SetActorType(sld);
	LAi_ActorFollow(sld, pchar, "", 10.0);
	ref chr = characterFromId("Pirates_waitress");
	sld = GetCharacter(NPC_GenerateCharacter("LH_waitress", "women_7", "woman", "woman", 5, PIRATE, -1, true, "quest"));
	sld.name = chr.name;
	sld.lastname = chr.lastname;
	sld.Dialog.Filename = "Quest\LongHappy.c";
	sld.dialog.currentnode = "waitress";
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, "Shore_ship1", "goto", "goto4");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void LongHappy_ReturnShoreGirl(string qName) // 
{
	chrDisableReloadToLocation = true;
	pchar.GenQuest.Hunter2Pause = true;
	sld = characterFromId("LH_waitress");
	sld.dialog.currentnode = "waitress_1";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void LongHappy_SetTichingituDelay() // 
{
	sld = characterFromId("Tichingitu");
	AddPassenger(pchar, sld, false);
	SetCharacterRemovable(sld, false);
	SetFunctionTimerCondition("LongHappy_SetTichingituOfficer", 0, 0, 5, false);
}

void LongHappy_SetTichingituOfficer(string qName) // 
{
	log_info(StringFromKey("LongHappy_35"));
	sld = characterFromId("Tichingitu");
	SetCharacterRemovable(sld, true);
	LAi_SetImmortal(sld, false);
	sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
	sld.OfficerWantToGo.DontGo = true;
	sld.CompanionDisable = true;
	sld.loyality = MAX_LOYALITY;
	LAi_SetOfficerType(sld);
	sld.Payment = true;
	sld.DontClearDead = true;
	sld.dialog.currentnode = "Tichingitu_officer";
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	SaveCurrentNpcQuestDateParam(sld, "HiredDate");
}

void LongHappy_SetLefransuaBoss(string qName) // 
{
	sld = GetCharacter(NPC_GenerateCharacter("JanDavid", "mercen_20", "man", "man", 30, PIRATE, -1, true, "quest"));
	FantomMakeCoolFighter(sld, 40, 70, 70, "blade_21", "pistol4", "bullet", 250);
	sld.name = StringFromKey("LongHappy_36");
	sld.lastname = StringFromKey("LongHappy_37");
	sld.Dialog.Filename = "Quest\LongHappy.c";
	sld.dialog.currentnode = "JanDavid";
	ChangeCharacterAddressGroup(sld, "LeFransua_townhall", "sit", "sit1");
	LAi_SetHuberType(sld);
	LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
	LAi_SetImmortal(sld, true);
}

void LongHappy_GiveBaronPart()
{
	int iMoney;
	iMoney = hrand(50000) + 50000;
	pchar.questTemp.LongHappy.BaronMoney = sti(pchar.questTemp.LongHappy.BaronMoney)+iMoney;
}

//=================================================================
//======================кейсы из quests_reaction===================
//=================================================================
bool LongHappy_QuestComplete(string sQuestName, string qname)
{

	ref sld;
	int i, iAddTime, iTime;
	string sTemp;
	
	bool condition = true;
	
	if (sQuestName == "LongHappy_GirlNorm") 
	{
		chrDisableReloadToLocation = false;//открыть локацию
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
		{
			sld = characterFromId("Helena");
			sld.dialog.currentnode = "Helena_officer";
		}
		else 
		{
			sld = characterFromId("Mary");
			sld.dialog.currentnode = "Mary_officer";
		}
		LAi_SetOfficerType(sld);
	} 
	else if (sQuestName == "LongHappy_MarryInit") 
	{
		chrDisableReloadToLocation = true;//закрыть локацию
		bDisableCharacterMenu = true;//лочим F2
		InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться
		pchar.GenQuest.CantRun = true;
		CheckAndSetOverloadMode(GetMainCharacter()); // бег запрещаем
		pchar.GenQuest.FrameLockEsc = true; // блокировать Esc
		// запустим музыку
		DoQuestFunctionDelay("LongHappy_MarryMusic", 1.2);
		// очистим церковь
		for(i=0; i<MAX_LOCATIONS; i++)
		{	
			sld = &characters[i];
			if (sld.location == "FortFrance_church" && CheckAttribute(sld, "CityType")) ChangeCharacterAddressGroup(sld, "none", "", "");
		}
		RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
		if (CheckCharacterItem(pchar, "suit1")) EquipCharacterbyItem(pchar, "suit1");
		LAi_SetActorType(pchar);
		// убираем попа и ставим Бенуа в центр
		sld = characterFromId("FortFrance_Priest");
		ChangeCharacterAddressGroup(sld, "none", "", "");
		sld = characterFromId("Benua");
		sld.dialog.currentnode = "LH_abbat_22";
		ChangeCharacterAddressGroup(sld, "FortFrance_church", "barmen", "bar1");
		// ставим невесту
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
		else sld = characterFromId("Mary");
		sld.dialog.currentnode = "LongHappy_20";
		ChangeCharacterAddressGroup(sld, "FortFrance_church", "reload", "reload1");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocator(sld, "goto", "girl", "LongHappy_MarryContinue", -1);
		// ставим гостей
		// патер ГГ
		sld = characterFromId(pchar.questTemp.LongHappy.Pater2);
		sld.dialog.currentnode = "LongHappyPater2";
		ChangeCharacterAddressGroup(sld, "FortFrance_church", "goto", "pater2");
		LAi_SetStayType(sld);
		// патер невесты
		sld = characterFromId(pchar.questTemp.LongHappy.Pater1);
		sld.dialog.currentnode = "LongHappyPater1";
		ChangeCharacterAddressGroup(sld, "FortFrance_church", "goto", "pater1");
		LAi_SetStayType(sld);
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) // фиксированные для Элен
		{
			// Свенсон
			sld = characterFromId("Svenson");
			sld.Dialog.Filename = "Quest\LongHappy.c";
			sld.dialog.currentnode = "Svenson";
			// Глэдис
			sld = characterFromId("Gladis");
			sld.Dialog.Filename = "Quest\LongHappy.c";
			sld.dialog.currentnode = "Gladis";
			ChangeCharacterAddressGroup(sld, "FortFrance_church", "goto", "gladys");
			LAi_SetStayType(sld);
			if (pchar.questTemp.LongHappy.Pater2 == "Fadey") 
			{
				sld = characterFromId("Fadey"); // патер ГГ
				sld.Dialog.Filename = "Quest\LongHappy.c";
				sld.dialog.currentnode = "fadey";
				// Пуанси либо Форже
				if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor")) 
				{
					sld = characterFromId("Noel");
					sld.dialog.currentnode = "forge_5"; // гость
				}
				else 
				{
					sld = characterFromId("Puancie");
					sld.dialog.currentnode = "puancie_4"; // гость
				}
				sld.Dialog.Filename = "Quest\LongHappy.c";
				ChangeCharacterAddressGroup(sld, "FortFrance_church", "goto", "governor");
				LAi_SetStayType(sld);
			}
			else
			{
				// Фадей гость
				sld = characterFromId("Fadey");
				sld.Dialog.Filename = "Quest\LongHappy.c";
				sld.dialog.currentnode = "fadey_3";
				ChangeCharacterAddressGroup(sld, "FortFrance_church", "goto", "governor");
				LAi_SetStayType(sld);
				// Пуанси либо Форже
				if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor")) 
				{
					sld = characterFromId("Noel");
					sld.Dialog.Filename = "Quest\LongHappy.c"; // 28-03-20
					sld.dialog.currentnode = "forge_3"; // патер
				}
				else 
				{
					sld = characterFromId("Puancie");
					sld.Dialog.Filename = "Quest\LongHappy.c"; // 28-03-20
					sld.dialog.currentnode = "puancie_2"; // патер
				}
			}
		}
		else // фиксированные для Мэри
		{
			// Пуанси либо Форже
			if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor")) 
			{
				sld = characterFromId("Noel");
				sld.dialog.currentnode = "forge"; // патер
			}
			else 
			{
				sld = characterFromId("Puancie");
				sld.dialog.currentnode = "puancie"; // патер
			}
			sld.Dialog.Filename = "Quest\LongHappy.c";
			sld = characterFromId("Fadey"); // патер ГГ
			sld.Dialog.Filename = "Quest\LongHappy.c";
			sld.dialog.currentnode = "fadey";
			// при свадьбе в Сен-Пьер
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) 
			{
				sld = characterFromId("Jino");
				sld.Dialog.Filename = "Quest\LongHappy.c";
				sld.dialog.currentnode = "Jino_7";
				ChangeCharacterAddressGroup(sld, "FortFrance_church", "goto", "gladys");
				LAi_SetStayType(sld);
			}
		}
		// общие для обоих
		// губернаторы
		sld = characterFromId("FortFrance_Mayor");
		sld.Dialog.Filename = "Quest\LongHappy.c";
		sld.dialog.currentnode = "FortFrance_Mayor";
		ChangeCharacterAddressGroup(sld, "FortFrance_church", "goto", "mayor1");
		LAi_SetStayType(sld);
		sld = characterFromId("BasTer_Mayor");
		sld.Dialog.Filename = "Quest\LongHappy.c";
		sld.dialog.currentnode = "BasTer_Mayor";
		ChangeCharacterAddressGroup(sld, "FortFrance_church", "goto", "mayor2");
		LAi_SetStayType(sld);
		sld = characterFromId("PortPax_Mayor");
		sld.Dialog.Filename = "Quest\LongHappy.c";
		sld.dialog.currentnode = "PortPax_Mayor";
		ChangeCharacterAddressGroup(sld, "FortFrance_church", "goto", "mayor4");
		LAi_SetStayType(sld);
		sld = characterFromId("Tortuga_Mayor");
		sld.Dialog.Filename = "Quest\LongHappy.c";
		sld.dialog.currentnode = "Tortuga_Mayor";
		ChangeCharacterAddressGroup(sld, "FortFrance_church", "goto", "mayor3");
		LAi_SetStayType(sld);
		// д'Ойли
		if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "end" && ChangeCharacterHunterScore(Pchar, "enghunter", 0) < 1)
		{
			sld = characterFromId("PortRoyal_Mayor");
			sld.Dialog.Filename = "Quest\LongHappy.c";
			sld.dialog.currentnode = "PortRoyal_Mayor";
			ChangeCharacterAddressGroup(sld, "FortFrance_church", "goto", "mayor5");
			LAi_SetStayType(sld);
		}
		// Проспер
		if (CheckAttribute(pchar, "questTemp.Prosper_fmql") && !CheckAttribute(pchar, "questTemp.FMQL.ProsperDead"))
		{
			sld = GetCharacter(NPC_GenerateCharacter("LH_Prosper", "Prospero_mush", "man", "man", 30, FRANCE, 1, false, "soldier"));
			sld.name = StringFromKey("LongHappy_38");
			sld.lastname = StringFromKey("LongHappy_39");
			sld.Dialog.Filename = "Quest\LongHappy.c";
			sld.dialog.currentnode = "Prosper";
			sld.greeting = "prosper_lh";
			ChangeCharacterAddressGroup(sld, "FortFrance_church", "goto", "prosper");
			LAi_SetStayType(sld);
		}
		// Тичингиту
		if (GetCharacterIndex("Tichingitu") != -1)
		{
			sld = characterFromId("Tichingitu"); // fix 01-04-20 снятие мушкета убираем
			sld.Dialog.Filename = "Quest\LongHappy.c";
			sld.dialog.currentnode = "Tichingitu";
			ChangeCharacterAddressGroup(sld, "FortFrance_church", "goto", "tich");
			LAi_SetStayType(sld);
		}
	} 
	else if (sQuestName == "LongHappy_MarryContinue") 
	{
		LAi_SetActorType(pchar);
		LAi_ActorGoToLocator(pchar, "goto", "charles", "LongHappy_MarryContinue1", -1);
	} 
	else if (sQuestName == "LongHappy_MarryContinue1") 
	{
		LAi_SetPlayerType(pchar);
		sld = characterFromId("Benua");
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 0.5);
	}
	
	//--> -------- блок празднования в таверне Сен-Пьер -------------------
	else if (sQuestName == "LongHappy_InSPtavern") 
	{
		pchar.questTemp.LongHappy.Count = 0; // не нужно, но чтобы не выводило ошибок
		// вычистим всех НПС
		for(i=0; i<MAX_LOCATIONS; i++)
		{	
			sld = &characters[i];
			if (sld.location == "FortFrance_tavern" && CheckAttribute(sld, "CityType"))
			{
				ChangeCharacterAddressGroup(sld, "none", "", "");
				sld.lifeday = 0;
			}
			if (sld.location == "FortFrance_tavern" && sld.greeting == "officer_hire")
			{
				ChangeCharacterAddressGroup(sld, "none", "", "");
				sld.lifeday = 0;
			}
		}
		// рассадим матросню для антуражу
		for (i=1; i<=10; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("LH_sailor_"+i, "citiz_"+(rand(9)+31), "man", "man", 20, FRANCE, 1, false, "soldier"));
			SetFantomParamFromRank(sld, 20, true);
			sld.Dialog.Filename = "Quest\LongHappy.c";
			sld.dialog.currentnode = "sailor";
			sld.greeting = "habitue";
			LAi_SetSitType(sld);
			sld.City = "FortFrance";
			sld.CityType = "citizen";
			sTemp = PlaceCharacter(sld, "sit", "random_free");
			ReSitCharacterOnFree(sld, "FortFrance_tavern", sTemp);
		}
		// меняем диалог тавернщику
		sld = characterFromId("FortFrance_tavernkeeper");
		sld.Dialog.Filename = "Quest\LongHappy.c";
		sld.dialog.currentnode = "tavernkeeper";
		// Мэри
		sld = characterFromId("Mary");
		sld.dialog.currentnode = "LongHappy_38";
		ChangeCharacterAddressGroup(sld, "FortFrance_tavern", "waitress", "stay2");
		LAi_SetCitizenType(sld);
		// установим офицеров
		// офицер гамбита
		if (CheckAttribute(pchar, "questTemp.HWIC.Detector"))
		{
			if (pchar.questTemp.HWIC.Detector == "holl_win" && GetCharacterIndex("Longway") != -1) 
			{
				sld = characterFromId("Longway");
				sld.dialog.currentnode = "Longway";
			}
			if (pchar.questTemp.HWIC.Detector == "eng_win" && GetCharacterIndex("Knippel") != -1) 
			{
				sld = characterFromId("Knippel");
				sld.dialog.currentnode = "Knippel";
			}
			if (pchar.questTemp.HWIC.Detector == "self_win" && GetCharacterIndex("Tonzag") != -1)
			{
				sld = characterFromId("Tonzag");
				sld.dialog.currentnode = "Tonzag";
			}
			pchar.questTemp.LongHappy.HambitOfficer = sld.id;
			sld.Dialog.Filename = "Quest\LongHappy.c";
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern", "goto", "goto2");
			LAi_SetActorType(sld);
		}
		// Бейкер
		if (GetCharacterIndex("Baker") != -1)
		{
			sld = characterFromId("Baker");
			sld.Dialog.Filename = "Quest\LongHappy.c";
			sld.dialog.currentnode = "Baker";
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern", "tables", "stay3");
			LAi_SetActorType(sld);
		}
		// Тичингиту
		if (GetCharacterIndex("Tichingitu") != -1)
		{
			sld = characterFromId("Tichingitu"); // fix 01-04-20 снятие мушкета убираем
			LAi_CharacterEnableDialog(sld);
			sld.Dialog.Filename = "Quest\LongHappy.c";
			sld.dialog.currentnode = "Tichingitu_18";
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern", "goto", "goto1");
			LAi_SetActorType(sld);
		}
		// Джино
		sld = characterFromId("Jino");
		LAi_CharacterEnableDialog(sld);
		sld.dialog.currentnode = "Jino_9";
		ChangeCharacterAddressGroup(sld, "FortFrance_tavern", "tables", "stay4");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0); // запускаем с Джино
	} 
	else if (sQuestName == "LongHappy_InSPcabin") 
	{
		// нормализуем таверну Сен-Пьер
		for (i=1; i<=10; i++)
		{
			sld = characterFromId("LH_sailor_"+i);
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld.lifeday = 0;
		}
		// тавернщик
		sld = characterFromId("FortFrance_tavernkeeper");
		sld.Dialog.Filename = "Common_Tavern.c";
		sld.dialog.currentnode = "First time";
		// Джино
		sld = characterFromId("Jino");
		sld.Dialog.Filename = "Quest\HollandGambit\Jino.c";
		sld.dialog.currentnode = "First time";
		ChangeCharacterAddressGroup(sld, "SentJons_HouseF3_Room", "goto", "goto1");
		LAi_SetCitizenType(sld);
		LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
		// Бейкер
		if (GetCharacterIndex("Baker") != -1)
		{
			sld = characterFromId("Baker");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Quest\Saga\Baker.c";
			sld.dialog.currentnode = "Baker_officer";
		}
		// офицер Гамбита
		if (CheckAttribute(pchar, "questTemp.LongHappy.HambitOfficer"))
		{
			sld = characterFromId(pchar.questTemp.LongHappy.HambitOfficer);
			ChangeCharacterAddressGroup(sld, "none", "", "");
			LAi_SetOfficerType(sld);
			if (pchar.questTemp.LongHappy.HambitOfficer == "Longway") sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			if (pchar.questTemp.LongHappy.HambitOfficer == "Knippel") sld.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			if (pchar.questTemp.LongHappy.HambitOfficer == "Tonzag") sld.Dialog.Filename = "Quest\HollandGambit\Tonzag.c";
			sld.dialog.currentnode = sld.id+"_officer";
		}
		// Тичингиту
		if (GetCharacterIndex("Tichingitu") != -1)
		{
			sld = characterFromId("Tichingitu");
			sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
			sld.dialog.currentnode = "Tichingitu_officer";
			ChangeCharacterAddressGroup(sld, "none", "", "");
			LAi_SetOfficerType(sld);
		}
		sld = characterFromId("Mary");
		sld.dialog.currentnode = "LongHappy_59";
		ChangeCharacterAddressGroup(sld, "My_Cabin", "rld", "aloc1");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	else if (sQuestName == "LongHappy_InSPComplete") //
	{
		chrDisableReloadToLocation = false;
		iTime = sti(environment.time);
		if (iTime >= 21) iAddTime = 24 - iTime + 12;
		if (iTime < 7) iAddTime = 12 - iTime;
		if (iTime >= 7 && iTime < 21) iAddTime = 24  + 12 - iTime;
		StoreDayUpdate();
		WaitDate("",0,0,0,iAddtime,5);
		RecalculateJumpTable();
		RefreshWeather();
		RefreshLandTime();
		CloseQuestHeader("LongHappy");
		pchar.questTemp.LongHappy = "end";
	}
	//<-- блок празднования в таверне Сен-Пьер
	else if (sQuestName == "LongHappy_IslaTesoroTavern") //
	{
		pchar.GenQuest.CannotWait = true;//запрет ожидания
		// вычистим всех НПС
		for(i=0; i<MAX_LOCATIONS; i++)
		{	
			sld = &characters[i];
			if (sld.location == "Pirates_tavern" && CheckAttribute(sld, "CityType"))
			{
				ChangeCharacterAddressGroup(sld, "none", "", "");
				sld.lifeday = 0;
			}
			if (sld.location == "Pirates_tavern" && sld.greeting == "officer_hire")
			{
				ChangeCharacterAddressGroup(sld, "none", "", "");
				sld.lifeday = 0;
			}
		}
		// fix 25-03-20 уберем Элен из резиденции, если жена - Мэри
		if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
		{
			if (GetCharacterIndex("Helena") != -1)
			{
				sld = characterFromId("Helena");
				ChangeCharacterAddressGroup(sld, "LosTeques_tavern", "waitress", "stay1"); // fix 01-04-20
			}
		}
		pchar.questTemp.LongHappy.Count = 0;
		pchar.questTemp.LongHappy.CountNeed = 6;
		if (CheckAttribute(pchar, "questTemp.LongHappy.BigMarry")) 
		// ставим жену ГГ
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
		else sld = characterFromId("Mary");
		sld.dialog.currentnode = "LongHappy_38";
		ChangeCharacterAddressGroup(sld, "Pirates_Tavern", "waitress", "barmen");
		LAi_SetCitizenType(sld);
		RemovePassenger(pchar, sld); // выводим её из офицеров
		// Даниэль Хоук встречает
		sld = characterFromId("Danielle");
		sld.Dialog.Filename = "Quest\LongHappy.c";
		sld.dialog.currentnode = "Danielle";
		LAi_SetCheckMinHP(sld, 10, true, ""); // скрытое бессмертие
		ChangeCharacterAddressGroup(sld, "Pirates_Tavern", "tables", "stay1");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		// Свенсон бармен
		sld = characterFromId("Svenson");
		sld.Dialog.Filename = "Quest\LongHappy.c";
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld.dialog.currentnode = "Svenson_2";
		else sld.dialog.currentnode = "Svenson_7";
		ChangeCharacterAddressGroup(sld, "Pirates_Tavern", "barmen", "stay");
		LAi_SetBarmanType(sld);
		// Тиракс
		sld = characterFromId("Terrax");
		sld.dialog.currentnode = "Terrax_3";
		ChangeCharacterAddressGroup(sld, "Pirates_Tavern", "sit", "sit10"); // определить локаторы для всех гостей
		LAi_SetSitType(sld);
		// Натаниэль Хоук
		sld = characterFromId("Nathaniel");
		sld.Dialog.Filename = "Quest\LongHappy.c";
		sld.dialog.currentnode = "Nathaniel";
		ChangeCharacterAddressGroup(sld, "Pirates_Tavern", "sit", "sit_base1");
		LAi_SetSitType(sld);
		// Додсон или Венсан
		if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie"))
		{
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "Dodson";
			LAi_SetCheckMinHP(sld, 10, true, ""); // скрытое бессмертие
		}
		else
		{
			if (GetCharacterIndex("Vensan") == -1)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Vensan", "Vensan", "man", "man", 30, PIRATE, -1, true, "quest"));
				sld.name = StringFromKey("LongHappy_40");
				sld.lastname = StringFromKey("LongHappy_41");
			}
			else sld = characterFromId("Vensan");
			sld.dialog.currentnode = "Vensan";
				FantomMakeCoolFighter(sld, 35, 70, 70, "blade_21", "pistol5", "bullet", 250);
				LAi_SetCheckMinHP(sld, 10, true, ""); // скрытое бессмертие
		}
		sld.Dialog.Filename = "Quest\LongHappy.c";
		ChangeCharacterAddressGroup(sld, "Pirates_Tavern", "sit", "sit1");
		LAi_SetSitType(sld);
		// Джино
		sld = characterFromId("Jino");
		sld.Dialog.Filename = "Quest\LongHappy.c";
		sld.dialog.currentnode = "Jino";
		ChangeCharacterAddressGroup(sld, "Pirates_Tavern", "sit", "sit5");
		LAi_SetSitType(sld);
		// Тичингиту
		if (GetCharacterIndex("Tichingitu") != -1)
		{
			sld = characterFromId("Tichingitu"); // fix 01-04-20 снятие мушкета убираем
			sld.Dialog.Filename = "Quest\LongHappy.c";
			sld.dialog.currentnode = "Tichingitu_2";
			ChangeCharacterAddressGroup(sld, "Pirates_Tavern", "tables", "stay3"); // fix 01-04-20
			LAi_SetCheckMinHP(sld, 10, true, ""); // скрытое бессмертие
			LAi_SetStayType(sld); // fix 01-04-20
			pchar.questTemp.LongHappy.CountNeed = sti(pchar.questTemp.LongHappy.CountNeed)+1;
		} 
		// при большой свадьбе
		if (CheckAttribute(pchar, "questTemp.LongHappy.BigMarry"))
		{
			// офицер гамбита
			if (CheckAttribute(pchar, "questTemp.HWIC.Detector"))
			{
				if (pchar.questTemp.HWIC.Detector == "holl_win" && GetCharacterIndex("Longway") != -1) 
				{
					sld = characterFromId("Longway");
					sld.dialog.currentnode = "Longway";
					pchar.questTemp.LongHappy.HambitOfficer = sld.id;
					sld.Dialog.Filename = "Quest\LongHappy.c";
					ChangeCharacterAddressGroup(sld, "Pirates_Tavern", "sit", "sit4");
					LAi_SetSitType(sld);
					pchar.questTemp.LongHappy.CountNeed = sti(pchar.questTemp.LongHappy.CountNeed)+1;
				}
				if (pchar.questTemp.HWIC.Detector == "eng_win" && GetCharacterIndex("Knippel") != -1) 
				{
					sld = characterFromId("Knippel");
					sld.dialog.currentnode = "Knippel";
					pchar.questTemp.LongHappy.HambitOfficer = sld.id;
					sld.Dialog.Filename = "Quest\LongHappy.c";
					ChangeCharacterAddressGroup(sld, "Pirates_Tavern", "sit", "sit4");
					LAi_SetSitType(sld);
					pchar.questTemp.LongHappy.CountNeed = sti(pchar.questTemp.LongHappy.CountNeed)+1;
				}
				if (pchar.questTemp.HWIC.Detector == "self_win" && GetCharacterIndex("Tonzag") != -1)
				{
					sld = characterFromId("Tonzag");
					sld.dialog.currentnode = "Tonzag";
					pchar.questTemp.LongHappy.HambitOfficer = sld.id;
					sld.Dialog.Filename = "Quest\LongHappy.c";
					ChangeCharacterAddressGroup(sld, "Pirates_Tavern", "sit", "sit4");
					LAi_SetSitType(sld);
					pchar.questTemp.LongHappy.CountNeed = sti(pchar.questTemp.LongHappy.CountNeed)+1;
				}
			}
			// Бейкер
			if (GetCharacterIndex("Baker") != -1)
			{
				sld = characterFromId("Baker");
				sld.Dialog.Filename = "Quest\LongHappy.c";
				sld.dialog.currentnode = "Baker";
				LAi_SetCheckMinHP(sld, 10, true, ""); // скрытое бессмертие
				ChangeCharacterAddressGroup(sld, "Pirates_Tavern", "sit", "sit9");
				LAi_SetSitType(sld);
				pchar.questTemp.LongHappy.CountNeed = sti(pchar.questTemp.LongHappy.CountNeed)+1;
			}
			// Венсан при Додсоне
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie"))
			{
				if (GetCharacterIndex("Vensan") == -1)
				{
					sld = GetCharacter(NPC_GenerateCharacter("Vensan", "Vensan", "man", "man", 30, PIRATE, -1, true, "quest"));
					sld.name = StringFromKey("LongHappy_40");
					sld.lastname = StringFromKey("LongHappy_41");
				}
				else sld = characterFromId("Vensan");
				sld.Dialog.Filename = "Quest\LongHappy.c";
				sld.dialog.currentnode = "Vensan_3";
				FantomMakeCoolFighter(sld, 35, 70, 70, "blade_21", "pistol5", "bullet", 250);
				LAi_SetCheckMinHP(sld, 10, true, ""); // скрытое бессмертие
				ChangeCharacterAddressGroup(sld, "Pirates_Tavern", "sit", "sit7");
				LAi_SetSitType(sld);
				pchar.questTemp.LongHappy.CountNeed = sti(pchar.questTemp.LongHappy.CountNeed)+1;
			}
		}
	}
	else if (sQuestName == "LongHappy_DannyNorm") //
	{
		sld = characterFromId("Danielle");
		sld.dialog.currentnode = "Danielle_2";
		LAi_SetCitizenType(sld);
	}
	else if (sQuestName == "LongHappy_BandosInDungeonAfterFight") //
	{
		LAi_group_Delete("EnemyFight");
		DoQuestCheckDelay("hide_weapon", 1.3);
		sld = characterFromId("Nathaniel");
		sld.dialog.currentnode = "Nathaniel_10";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		if (!CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Rum") && GetCharacterIndex("Tichingitu") != -1)
		{
			sld = characterFromId("Tichingitu");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		}
		sld = characterFromId("Pirates_shipyarder");
		ChangeCharacterAddressGroup(sld, "none", "", "");
	}
	else if (sQuestName == "LongHappy_TavernAfterFight") //
	{
		LAi_group_Delete("EnemyFight");
		DoQuestCheckDelay("hide_weapon", 1.3);
		sld = characterFromId("Terrax");
		sld.dialog.currentnode = "Terrax_9";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	else if (sQuestName == "LongHappy_IslaTesoroTownFight") //
	{
		// установить группировку наших пиратов
		for (i=1; i<=10; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("LH_OurPirate_"+i, "citiz_"+(40+i), "man", "man", 30, PIRATE, 0, false, "soldier"));
			FantomMakeCoolFighter(sld, 30, 55, 55, LinkRandPhrase("blade_07","blade_08","blade_09"), "pistol1", "bullet", 150);
			ChangeCharacterAddressGroup(sld, "Pirates_town", "reload", "houseS1");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
		// установить группировку пиратов Барбазона
		for (i=1; i<=15; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("LH_BarbPirate_"+i, "citiz_4"+(rand(8)+1), "man", "man", 35, PIRATE, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, 35, 60, 60, LinkRandPhrase("blade_07","blade_08","blade_09"), "pistol1", "bullet", 180);
			ChangeCharacterAddressGroup(sld, "Pirates_town", "rld", "loc0");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "LongHappy_TownAfterFight");
		LAi_SetFightMode(pchar, true);
	}
	else if (sQuestName == "LongHappy_TownAfterFight") //
	{
		LAi_group_Delete("EnemyFight");
		DoQuestCheckDelay("hide_weapon", 1.3);
		sld = characterFromId("Nathaniel");
		sld.dialog.currentnode = "Nathaniel_12";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		// фикс Бейкера не офицера
		if (CheckAttribute(pchar, "questTemp.LongHappy.BigMarry") && GetCharacterIndex("Baker") != -1 && !IsOfficer(characterFromId("Baker")))
		{
			sld = characterFromId("Baker");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			LAi_SetOfficerType(sld);
		}
	}
	else if (sQuestName == "LongHappy_ResidenceAfterFight") //
	{
		LAi_group_Delete("EnemyFight");
		DoQuestCheckDelay("hide_weapon", 1.3);
		if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Warrior"))
		{
			pchar.questTemp.LongHappy.Tichingitu_Victim = "true";
			DeleteAttribute(pchar, "questTemp.LongHappy.Tichingitu_Warrior");
		}
		sld = characterFromId("Nathaniel");
		sld.dialog.currentnode = "Nathaniel_15";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	else if (sQuestName == "LongHappy_IslaTesoroBedroom") //
	{
		LAi_SetPlayerType(pchar);
		if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angerran") && CharacterIsAlive("Angerran")) sld = characterFromId("Angerran"); // fix 02-04-20
		else sld = characterFromId("LH_Dussak");
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 0.5);
	}
	else if (sQuestName == "LongHappy_BedroomShot") //
	{
		if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angerran") && CharacterIsAlive("Angerran")) sld = characterFromId("Angerran"); // fix 02-04-20
		else sld = characterFromId("LH_Dussak");
		LAi_ActorAnimation(sld, "shot", "LongHappy_BedroomShot_1", 1.2);
	}
	else if (sQuestName == "LongHappy_BedroomShot_1") //
	{
		sld = characterFromId("LH_Victim");
		LAi_KillCharacter(sld);
		LAi_SetPlayerType(pchar);
		if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angerran") && CharacterIsAlive("Angerran"))  // fix 02-04-20
		{
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Shivo_7";
		}
		else
		{
			sld = characterFromId("LH_Dussak");
			sld.dialog.currentnode = "Dussak_6";
		}
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 0.5);
	}
	else if (sQuestName == "LongHappy_BedroomAfterFight") //
	{
		LAi_group_Delete("EnemyFight");
		DoQuestCheckDelay("hide_weapon", 1.3);
		if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim"))
		{
			sld = characterFromId("Nathaniel");
			sld.dialog.currentnode = "Nathaniel_17";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
		}
		else
		{
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_7";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
		}
	}
	else if (sQuestName == "LongHappy_FindJinoHurry") //
	{
		chrDisableReloadToLocation = false;//открыть локацию
		bDisableCharacterMenu = false;
		InterfaceStates.Buttons.Save.enable = true;
		// ставим Натана или жену и в офицеры
		if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim"))
		{
			sld = characterFromId("Nathaniel");
			ChangeCharacterAddressGroup(sld, "Pirates_town", "reload", "reload3"); 
			sld.dialog.currentnode = "Nathaniel_20";
			LAi_SetOfficerType(sld);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, true);
			sld.CompanionDisable = true;
			sld.loyality = MAX_LOYALITY;
			sld.Payment = true;
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			log_info(StringFromKey("LongHappy_42", GetFullName(sld)));
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			EquipCharacterbyItem(sld, pchar.questTemp.LongHappy.GBlade);
			EquipCharacterbyItem(sld, pchar.questTemp.LongHappy.GGun);
		}
		else
		{
			sld = characterFromId("Nathaniel");
			LAi_SetLayType(sld);
			ChangeCharacterAddressGroup(sld, "Location_reserve_04", "goto", "goto1"); 
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			ChangeCharacterAddressGroup(sld, "Pirates_town", "reload", "reload3"); 
			sld.OfficerWantToGo.DontGo = true; //не пытаться уйти
			LAi_SetOfficerType(sld);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, true);
			sld.loyality = MAX_LOYALITY;
			sld.Payment = true;
			sld.CompanionDisable = true;
			sld.dialog.currentnode = "LongHappy_43";
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(sld, "HiredDate");
			EquipCharacterbyItem(sld, pchar.questTemp.LongHappy.GBlade);
			EquipCharacterbyItem(sld, pchar.questTemp.LongHappy.GGun);
			log_info(StringFromKey("LongHappy_43", GetFullName(sld)));
		}
		// открыть магазин, порт, комнату таверны, закрыть резиденцию
		LocatorReloadEnterDisable("Pirates_town", "reload1_back", false);
		LocatorReloadEnterDisable("Pirates_town", "reload6_back", false);
		LocatorReloadEnterDisable("Pirates_town", "reload3_back", true);
		LocatorReloadEnterDisable("Pirates_tavern", "reload2_back", false);
		// на море
		pchar.quest.longhappy_isla_hurry.win_condition.l1 = "location";
		pchar.quest.longhappy_isla_hurry.win_condition.l1.location = "Bermudes";
		pchar.quest.longhappy_isla_hurry.function = "LongHappy_SeaBattle";
		// на таверну
		pchar.quest.longhappy_isla_hurry1.win_condition.l1 = "location";
		pchar.quest.longhappy_isla_hurry1.win_condition.l1.location = "Pirates_tavern";
		pchar.quest.longhappy_isla_hurry1.function = "LongHappy_KillersInTavern";
		if (CheckAttribute(pchar, "questTemp.LongHappy.BigMarry") && !CheckAttribute(pchar, "questTemp.Saga.DodsonDie"))
		{
			// на магазин
			pchar.quest.longhappy_isla_hurry2.win_condition.l1 = "location";
			pchar.quest.longhappy_isla_hurry2.win_condition.l1.location = "Pirates_store";
			pchar.quest.longhappy_isla_hurry2.function = "LongHappy_KillersInStore";
		}
	}
	else if (sQuestName == "LongHappy_StoreAfterFight") //
	{
		LAi_group_Delete("EnemyFight");
		DoQuestCheckDelay("hide_weapon", 0.5);
		LAi_LocationFightDisable(&Locations[FindLocation("Pirates_store")], true);
		sld = characterFromId("Vensan");
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.5);
	}
	else if (sQuestName == "LongHappy_TavernKillerAfterFight") //
	{
		LAi_group_Delete("EnemyFight");
		DoQuestCheckDelay("hide_weapon", 1.3);
		chrDisableReloadToLocation = false;
		LocatorReloadEnterDisable("Pirates_tavern", "reload1_back", true);
		AddQuestRecord("LongHappy", "17");
		pchar.quest.longhappy_isla_hurry3.win_condition.l1 = "location";
		pchar.quest.longhappy_isla_hurry3.win_condition.l1.location = "Pirates_tavern_upstairs";
		pchar.quest.longhappy_isla_hurry3.function = "LongHappy_FindJinoTavern";
	}
	else if (sQuestName == "LongHappy_BarbAfterFight") // 
	{
		pchar.GenQuest.CannotReloadBoarding = true; // нельзя перегружаться
		if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim"))
		{
			sld = characterFromId("Nathaniel");
			sld.dialog.currentnode = "Nathaniel_21";
		}
		else
		{
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_44";
		}
		ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	else if (sQuestName == "LongHappy_BarbExit") //
	{
		if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) pchar.questTemp.LongHappy.Terrax.Free = "true";
		DeleteAttribute(pchar, "GenQuest.CannotReloadBoarding"); // можно выходить
		if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim"))
		{
			sld = characterFromId("Nathaniel");
			sld.dialog.currentnode = "Nathaniel_20";
			LAi_SetOfficerType(sld);
		}
		else
		{
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_43";
			LAi_SetOfficerType(sld);
		}
	}
	else if (sQuestName == "LongHappy_DannyInResidence") //
	{
		sld = characterFromId("Svenson");
		ChangeCharacterAddressGroup(sld, "Pirates_townhall", "goto", "goto1");
		sld = characterFromId("Danielle");
		sld.dialog.currentnode = "Danielle_11";
		ChangeCharacterAddressGroup(sld, "Pirates_townhall", "goto", "goto4");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	else if (sQuestName == "LongHappy_WifeInTown") //
	{
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
		else sld = characterFromId("Mary");
		if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Rum")) sld.dialog .currentnode = "LongHappy_52";
		else sld.dialog.currentnode = "LongHappy_49";
		ChangeCharacterAddressGroup(sld, "Pirates_town", "rld", "loc1");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim") && !CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died")) LongHappy_SetTichingituDelay(); 
	}
	else if (sQuestName == "LongHappy_MarryFinalizing") 
	{
		LSC_MaryLoveWaitTime();
		SetLaunchFrameFormParam(StringFromKey("LongHappy_44"), "", 0, 4);
		LaunchFrameForm();
		DoQuestCheckDelay("LongHappy_MarryFinalizingReload", 4.0);
	}
	else if (sQuestName == "LongHappy_MarryFinalizingReload") //
	{
		DoQuestReloadToLocation("Pirates_town", "quest", "quest1", "LongHappy_IslaMarryFinal");
	}
	else if (sQuestName == "LongHappy_IslaMarryFinal") //
	{
		LongHappy_IslaTesoroClear(); // нормализация города
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
		else sld = characterFromId("Mary");
		ChangeCharacterAddressGroup(sld, "Pirates_town", "goto", "goto4"); // найти локатор рядом с ГГ
		sld = characterFromId("Svenson");
		ChangeCharacterAddressGroup(sld, "Pirates_town", "goto", "goto8");
		sld.dialog.currentnode = "Svenson_45";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	else if (sQuestName == "LongHappy_IslaMarryComplete") //
	{
		chrDisableReloadToLocation = false;
		bQuestDisableMapEnter = false;//открыть карту
		DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		DeleteAttribute(pchar, "GenQuest.CannotWait");
		sld = characterFromId("Svenson");
		sld.Dialog.Filename = "Quest\Saga\Svenson.c";
		sld.dialog.currentnode = "First time";
		ChangeCharacterAddressGroup(sld, "Santacatalina_houseS1_residence", "sit", "sit1");
		LAi_SetHuberType(sld);
		LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
		else sld = characterFromId("Mary");
		LAi_SetImmortal(sld, false);
		sld.OfficerWantToGo.DontGo = true;
		sld.loyality = MAX_LOYALITY;
		AddPassenger(pchar, sld, false);
		SetCharacterRemovable(sld, true);
		LAi_SetOfficerType(sld);
		sld.Payment = true;
		sld.DontClearDead = true;
		sld.dialog.currentnode = sld.id+"_officer";
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld.CompanionDisable = true; // fix 25-03-20 блок компаньона у Мэри
		CloseQuestHeader("LongHappy");
		pchar.questTemp.LongHappy = "end";
	}
	else
	{
		condition = false;
	}
	
	return condition;
}