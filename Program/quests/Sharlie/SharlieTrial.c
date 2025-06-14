///////////////////////////////////////////////////////////////////////////////////////////////////////////	
///Jason----------------------------Бремя гасконца - макроквест Шарля де Мора-----------------------------
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void Sharlie_enterSoldiers()//арестовывающие солдаты
{
	chrDisableReloadToLocation = true;//закрыть локацию
	for (i=1; i<=3; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter("ShSold"+i, "sold_fra_"+i, "man", "man", 20, FRANCE, 0, true, "soldier"));
		SetFantomParamFromRank(sld, 20, true);         
		LAi_SetWarriorType(sld); 
		LAi_warrior_DialogEnable(sld, false);
        ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
    }
    sld = GetCharacter(NPC_GenerateCharacter("ShOfficer", "off_fra_3", "man", "man", 30, FRANCE, 0, true, "soldier"));
	SetFantomParamFromRank(sld, 30, true);
	sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
	sld.dialog.currentnode = "Sharlie_arest";
	sld.greeting = "soldier_arest";
    LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
	LAi_ActorDialog(sld, pchar, "", 1.0, 0);
}

void Puancie_InJail(string qName)//Пуанси в тюрьме //Sinistra Катсцена
{
    StartQuestMovie(true, false, true);
	locCameraFromToPos(-11.50, 1.37, -3.37, false, -16.89, -0.30, -2.73);
	LAi_SetStayType(pchar);
	DoQuestFunctionDelay("Puancie_Cutscene_1", 3.0);
}

void Puancie_Cutscene_1(string qName)
{
	LAi_FadeLong("", "");
	DoQuestFunctionDelay("Puancie_Cutscene_2", 1.0);
}

void Puancie_Cutscene_2(string qName)
{
	locCameraFromToPos(-11.09, 0.65, 3.05, true, -12.59, 0.09, -4.66);
	
	sld = characterFromID("Puancie");
	LAi_SetActorType(sld);
    LAi_ActorGoToLocator(sld, "goto", "goto23", "", -1);
	DoQuestFunctionDelay("Puancie_InJailTalk", 3.5);
}

void Puancie_InJailTalk(string qName)//Пуанси в тюрьме
{
    sld = characterFromID("Puancie");
	LAi_SetActorType(sld);
    LAi_ActorDialog(sld, pchar, "", 0, 0);
	
	locCameraFromToPos(-14.88, 1.42, -3.04, true, -11.71, 0.00, -2.76);
}

void Sharlie_PardonOver(string qName)//извинений больше нет
{
    DeleteAttribute(pchar, "questTemp.Sharlie.Pardon");
	if(!CheckAttribute(pchar, "questTemp.Sharlie.Junglejew"))
	{
		DelLandQuestMark(characterFromId("FortFrance_Mayor"));
	}
}

void Sharlie_BenuaMaltie(string qName)//в церкви наутро
{
    sld = characterFromId("Benua");
	sld.dialog.currentnode = "Benua_maltie";
}

void Sharlie_enterMaltie()//мальтийский рыцарь
{
	chrDisableReloadToLocation = true;//закрыть локацию
    sld = GetCharacter(NPC_GenerateCharacter("Sh_Maltie", "off_Malt_2", "man", "man", 30, FRANCE, -1, true, "soldier"));
	SetFantomParamFromRank(sld, 30, true);
	AddLandQuestMark(sld, "questmarkmain");
	sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
	sld.dialog.currentnode = "Sharlie_maltie";
	sld.greeting = "patrol";
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	LAi_SetImmortal(sld, true);
    LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, pchar.location, "quest", "quest1");
	LAi_ActorDialog(sld, pchar, "", 1.0, -1);
}

void Sharlie_MaltieAfterJail(string qName)//мальтийский рыцарь
{
	chrDisableReloadToLocation = true;//закрыть локацию
    sld = GetCharacter(NPC_GenerateCharacter("Sh_Maltie", "off_Malt_2", "man", "man", 30, FRANCE, -1, true, "soldier"));
	SetFantomParamFromRank(sld, 30, true);
	AddLandQuestMark(sld, "questmarkmain");
	sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
	sld.dialog.currentnode = "Sharlie_maltieA";
	sld.greeting = "patrol";
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	LAi_SetImmortal(sld, true);
    LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, pchar.location, "reload", "basement1");
	LAi_ActorDialog(sld, pchar, "", 4.0, -1);
}

void Sharlie_BenuaLoanTime(string qName)//займ у Бенуа // Addon 2016-1 Jason пиратская линейка 1
{
	if (!CheckAttribute(pchar, "questTemp.Sharlie.BenuaLoan")) return;
    pchar.questTemp.Sharlie.BenuaLoan.Late = "true";
	log_info(StringFromKey("SharlieTrial_1"));
}

//------------------------------------------мини-квесты для сбора денег---------------------------------------
//найти помощника для торговца
void Sharlie_CreateStorehelper()//создаем помощника торговца
{
	sld = GetCharacter(NPC_GenerateCharacter("Storehelper", "Fugitive", "man", "man", 10, FRANCE, 3, true, "soldier"));
	SetFantomParamFromRank(sld, 10, true);
	sld.Dialog.Filename = "Quest\Sharlie\StartMiniQuests.c";
	sld.name = StringFromKey("SharlieTrial_2");
	sld.lastname = StringFromKey("SharlieTrial_3");
	sld.greeting = "town_pirate";
	LAi_SetImmortal(sld, true);
	AddLandQuestMark(sld, "questmarkmain");
	LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
	switch (sti(pchar.questTemp.Sharlie.Storehelper.Chance))
	{
		case 0: //в таверне
			sld.dialog.currentnode = "Storehelper";
			LAi_SetSitType(sld);
			FreeSitLocator("LeFransua_tavern", "sit3");
			ChangeCharacterAddressGroup(sld, "LeFransua_tavern", "sit", "sit3");
		break;
		
		case 1: //в городе
			sld.dialog.currentnode = "Storehelper_4";
			LAi_SetCitizenType(sld);
			sld.City = "LeFransua";
			ChangeCharacterAddressGroup(sld, "LeFransua_town", "goto", "goto14");
			LAi_SetLoginTime(sld, 6.0, 21.99);
		break;
		
		case 2: //в магазине
			sld.dialog.currentnode = "Storehelper_8";
			LAi_SetOwnerType(sld);
			ChangeCharacterAddressGroup(sld, "LeFransua_store", "goto", "goto1");
		break;
	}
	SetFunctionTimerCondition("StorehelperOver", 0, 0, 3, false);
	GiveItem2Character(pchar, "map_martiniqua");
	RefreshEquippedMaps(GetMainCharacter());
	DoQuestFunctionDelay("Tutorial_LandMap", 1.0);
}

void Tutorial_LandMap(string qName)
{
	LaunchTutorial("LandMap", 1);
}

void StorehelperOver(string qName)
{
	DeleteAttribute(pchar, "questTemp.Sharlie.Storehelper");
	CloseQuestHeader("SharlieA");
}

void Storehelper_hire(string qName)//кандидаты
{
	chrDisableReloadToLocation = true;
	for (i=1; i<=3; i++)
    {
		sld = GetCharacter(NPC_GenerateCharacter("Newstorehelper_"+i, "citiz_"+(23+i), "man", "man", 10, FRANCE, 1, true, "soldier"));
		SetFantomParamFromRank(sld, 10, true);
		sld.Dialog.Filename = "Quest\Sharlie\StartMiniQuests.c";
		sld.dialog.currentnode = "Newstorehelper_"+i;
		sld.greeting = "town_pirate";
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
		ChangeCharacterAddressGroup(sld, "LeFransua_tavern", "reload", "reload1_back");
		LAi_ActorGoToLocator(sld, "goto", "goto2", "", -1);
		DoQuestCheckDelay("Newstorehelper_ready", 4.5);
	}
}

void NewstorehelperRegard(string qName)//пришли в магазин
{
	chrDisableReloadToLocation = true;//закрыть локацию
	sld = characterFromId(pchar.questTemp.Sharlie.Storehelper.id);
	sld.dialog.currentnode = "Newstorehelper_regard";
	LAi_SetActorType(sld);
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, "FortFrance_store", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void StorehelperFinal(string qName)//спустя час
{
	pchar.questTemp.Sharlie.Storehelper = "final";
	log_Testinfo("можно идти в магазин");
}

//привезти ром контрабандой для бармена
void Rum_CreateBarkas(string qName)//баркас у пирса
{
	//log_info("Баркас поставлен к пирсу");
	AddQuestRecord("SharlieB", "7");
	pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
	pchar.Ship.name = StringFromKey("SharlieTrial_4");
	SetBaseShipData(pchar);
	NullCharacterGoods(pchar);
	AddCharacterGoods(pchar, GOOD_FOOD, 10);
	AddCharacterGoods(pchar, GOOD_MEDICAMENT, 10);
	ref shTo = &RealShips[sti(Pchar.Ship.Type)];
	shTo.SpeedRate = 13.0;
	SetCrewQuantityOverMax(PChar, 5);
	pchar.Ship.Crew.Exp.Sailors = 50;
	pchar.quest.Sharlie_rum1.win_condition.l1 = "location";
	pchar.quest.Sharlie_rum1.win_condition.l1.location = "Martinique";
	pchar.quest.Sharlie_rum1.function = "Rum_FindLugger";
	//установить радиус доплыть до на остров
	i = FindIsland("Martinique");
	Islands[i].EffectRadius = 3500-MOD_SKILL_ENEMY_RATE*100;
}

void NgtBarkas(string qName)
{
	DoQuestFunctionDelay("NgtBarkas2", 2.0);
}

void NgtBarkas2(string qName)
{
	NewGameTip(StringFromKey("SharlieTrial_5"));
}

void Rum_CreateBarkasOver(string qName)//опоздали
{
	pchar.Ship.Type = SHIP_NOTUSED;
	pchar.quest.Sharlie_rum.over = "yes";
	AddQuestRecord("SharlieB", "3");
	CloseQuestHeader("SharlieB");
	DeleteAttribute(pchar, "questTemp.Sharlie.Rum");
}

void Rum_FindLugger(string qName)//вышли в море - ставим люггер
{
	Weather.Wind.Speed = 16.0;
	pchar.wind.speed = Weather.Wind.Speed;
	fWeatherSpeed = stf(Weather.Wind.Speed);//халява первого выхода
	
	Weather.Wind.Angle = 0.0;
	pchar.wind.angle = Weather.Wind.Angle;
	fWeatherAngle = stf(Weather.Wind.Angle);//халява первого выхода
	
	LAi_LocationFightDisable(&Locations[FindLocation("Deck_Near_Ship")], true);//запретить драться
	pchar.quest.Rum_CreateBarkasOver.over = "yes"; //снять таймер
	Group_FindOrCreateGroup("Rum_CapGroup");
	Group_SetType("Rum_CapGroup", "pirate");//тип группы
	sld = GetCharacter(NPC_GenerateCharacter("Rum_Cap", "mercen_5", "man", "man", 20, FRANCE, 5, true, "quest"));
	FantomMakeSmallSailor(sld, SHIP_LUGGER, StringFromKey("SharlieTrial_6"), CANNON_TYPE_CANNON_LBS3, 50, 45, 45, 40, 45);
	FantomMakeCoolFighter(sld, 20, 50, 50, "blade_05", "pistol1", "bullet", 100);
	sld.Dialog.Filename = "Quest\Sharlie\StartMiniQuests.c";
	sld.dialog.currentnode = "Rum_Cap";
	sld.greeting = "captain";
	LAi_SetImmortal(sld, true);
	Group_AddCharacter("Rum_CapGroup", "Rum_Cap");
    Group_SetGroupCommander("Rum_CapGroup", "Rum_Cap");
	Group_SetAddress("Rum_CapGroup", "Martinique", "Quest_Ships", "Quest_Ship_10");
	pchar.quest.Sharlie_rum2.win_condition.l1 = "Timer";
	pchar.quest.Sharlie_rum2.win_condition.l1.date.hour  = 5.0;
	pchar.quest.Sharlie_rum2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
	pchar.quest.Sharlie_rum2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
	pchar.quest.Sharlie_rum2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
	pchar.quest.Sharlie_rum2.function = "Rum_FindLuggerOver";
	DoQuestFunctionDelay("Rum_NewGameTip1", 2.0);
	pchar.questTemp.Sharlie.Rum.Tip0 = true;
	pchar.questTemp.Sharlie.Rum.Tip1 = true;
	QuestPointerDelLoc("fortfrance_town", "reload", "reload1_back");
}

void Rum_NewGameTip0(string qName) // Обучение уехало в новый туториал 
{
	LaunchTutorial("Prologue_Navigation", 1);
    if(bGlobalTutor)
    {
        DontRefreshBLI = false;
        DeleteAttribute(pchar, "systeminfo.BLIoff");
        TW_InitSea_1_Turn();
        TW_Open("sea");
	}
	else
	{
		DoQuestFunctionDelay("SharlieTutorial_ActivateButtonInTheSea_1", 15.0);
	}
	//if(!SandBoxMode) DoQuestFunctionDelay("Rum_NewGameTip1", 15.0);
}

void Rum_NewGameTip1(string qName) {
	//NewGameTip("Черные стрелочки на мини-карте обозначают ваш оптимальный курс относительно ветра.");
	if(!SandBoxMode) DoQuestFunctionDelay("Rum_NewGameTip2", 10.0);
	if(!SandBoxMode) NewGameTip(StringFromKey("SharlieTrial_7"));
}

void Rum_NewGameTip2(string qName) {
	if(!SandBoxMode) DoQuestFunctionDelay("Rum_NewGameTip3", 1.0);
	LaunchTutorial("OptKurs", 1);
}

void Rum_NewGameTip3(string qName) {
	//if(!SandBoxMode) DoQuestFunctionDelay("Rum_NewGameTip4", 20.0);
	//if(IsEquipCharacterByMap(pchar, "map_martiniqua")) 
	//LaunchTutorial("LandMapAtSea", 0);
	//LaunchTutorial("SeaTimeScaleUp", 1);
	pchar.questTemp.Sharlie.Rum.TipT = true;
}

void Rum_NewGameTip4(string qName) {
	NewGameTip(StringFromKey("SharlieTrial_8"));
}

void Rum_FindLuggerOver(string qName)//не нашли
{
	Log_Info(StringFromKey("SharlieTrial_9"));
	PlaySound("interface\notebook.wav");
	sld = characterFromId("Rum_Cap");
	sld.dialog.currentnode = "Rum_Cap_Over";
	pchar.quest.Sharlie_rum3.win_condition.l1 = "Location_Type";
	pchar.quest.Sharlie_rum3.win_condition.l1.location_type = "town";
	pchar.quest.Sharlie_rum3.function = "Rum_RemoveBarkas";
	AddQuestRecord("SharlieB", "2");
}

void Rum_RemoveBarkas(string qName)//удаляем баркас
{
	int i = FindIsland("Martinique");
	DeleteAttribute(Islands[i], "EffectRadius");
	Group_DeleteGroup("Rum_CapGroup");
	pchar.Ship.Type = SHIP_NOTUSED;
	DeleteAttribute(pchar, "questTemp.Sharlie.Rum");
	CloseQuestHeader("SharlieB");
	i = FindLocation("Fortfrance_town");
	setCharacterShipLocation(pchar, GetCityFrom_Sea(locations[i].fastreload));
	setWDMPointXZ(GetCityFrom_Sea(locations[i].fastreload));
}

void Rum_CarrierEnter()//погрузка
{
	SetLaunchFrameFormParam(StringFromKey("SharlieTrial_10", NewStr()), "", 0, 5);
	LaunchFrameForm();
    WaitDate("", 0, 0, 0, 1, 10); //крутим время
    DeleteAttribute(pchar, "questTemp.TimeLock");
    Whr_UpdateWeather();
    pchar.questTemp.TimeLock = true;
    RecalculateJumpTable();
    DoQuestCheckDelay("Rum_CapGoodbye", 1.0);
}

void MessageRum1(string qName) 
{
	NewGameTip(StringFromKey("SharlieTrial_11"));
}

void MessageRum2(string qName) 
{
	DoQuestFunctionDelay("MessageRum2d", 5.0);
}

void MessageRum2d(string qName) 
{
	NewGameTip(StringFromKey("SharlieTrial_12"));
}

void Rum_RemoveRum(string qName)//высадились в Ле Франсуа
{
	chrDisableReloadToLocation = true;
	i = FindIsland("Martinique");
	DeleteAttribute(Islands[i], "EffectRadius");
	Islands[i].EffectRadius = 5000;
	Group_DeleteGroup("Rum_CapGroup");
	pchar.Ship.Type = SHIP_NOTUSED;
	for (i=1; i<=3; i++)
    {
		sld = GetCharacter(NPC_GenerateCharacter("Rum_Carrier2_"+i, "citiz_"+(21+i), "man", "man", 5, FRANCE, 1, true, "soldier"));
		SetFantomParamFromRank(sld, 10, true);
		if (i != 1) LAi_CharacterDisableDialog(sld);
		sld.Dialog.Filename = "Quest\Sharlie\StartMiniQuests.c";
		sld.dialog.currentnode = "Rum_Carrier";
		sld.greeting = "smuggler";
		LAi_SetImmortal(sld, true);
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, "LeFransua_town", "goto", "goto16");
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	/* NewGameTip("В локациях иногда доступны случайные предметы");
	Log_Info("Внимательнее смотрите по сторонам"); */
}

//доставить девочку из борделя дворянину
void Sharlie_CreateGigoloMan(string qName)//ставим дворянина и прерывание на джунгли
{
	
}

void Sharlie_CreateGigoloGirl()//ставим девочку
{
	sld = GetCharacter(NPC_GenerateCharacter("GigoloGirl", "women_24", "woman", "towngirl", 3, FRANCE, -1, false, "soldier"));
	sld.name = StringFromKey("SharlieTrial_13");
	sld.lastname = StringFromKey("SharlieTrial_14");
	sld.City = "Fortfrance";
	sld.CityType = "horse";
	LAi_SetLoginTime(sld, 23.0, 0.0);
	sld.Dialog.Filename = "Quest\Sharlie\StartMiniQuests.c";
	sld.dialog.currentnode = "GigoloGirl";
	sld.greeting = "whore";
	LAi_SetImmortal(sld, true);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	ChangeCharacterAddressGroup(sld, "Fortfrance_Brothel", "goto", "goto1");
	AddLandQuestMark(sld, "questmarkmain");
	LocatorReloadEnterDisable("Fortfrance_town", "reload4_back", false);// таверна
	AddLandQuestMark(characterFromId("Fortfrance_tavernkeeper"), "questmarkmain");
}

void Sharlie_GigoloGirlOver(string qName)//нет прогулкам под луной
{
	sld = characterFromId("GigoloGirl");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload9_back", "Fortfrance_Brothel", "goto", "goto1", "GigoloGirl_SetCitizen", 20.0);
	QuestPointerDelLoc("fortfrance_town", "reload", "houseSp1");
}

void Sharlie_GiveGigoloGirl(string qName)//
{
	sld = characterFromId("GigoloGirl");
	sld.dialog.currentnode = "GigoloGirl_3";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void Sharlie_CreatShipyardMarker(string qName)
{
	QuestPointerToLoc("fortfrance_town", "reload", "reload5_back");
}

void FortfranceJailOff_AddQuestMark(string qName)
{
	DoQuestFunctionDelay("FortfranceJailOff_AddQuestMark_Delay", 1.0);
}

void FortfranceJailOff_AddQuestMark_Delay(string qName)
{
	AddLandQuestMark(characterFromId("FortfranceJailOff"), "questmarkmain");
}

void PortPaxAmmoOff_AddQuestMark(string qName)
{
	DoQuestFunctionDelay("PortPaxAmmoOff_AddQuestMark_Delay", 1.0);
}

void PortPaxAmmoOff_AddQuestMark_Delay(string qName)
{
	AddLandQuestMark(characterFromId("PortPaxAmmoOff"), "questmarkmain");
}

void Captive_Timer(string qName)//ставим ступенчатое прерывание на бухту - иначе вылет
{
	pchar.quest.Sharlie_captive_Tut.over = "yes";//снять прерывание
	pchar.quest.Sharlie_captive1.win_condition.l1 = "location";
	pchar.quest.Sharlie_captive1.win_condition.l1.location = "Shore39";
	pchar.quest.Sharlie_captive1.function = "Captive_CreatePirates";
}

//освободить испанца для ростовщика
void Captive_CreatePirates(string qName)//устанавливаем пиратусов
{
	int iRank = MOD_SKILL_ENEMY_RATE;
	pchar.quest.Captive_CreatePiratesOver.over = "yes";//снять таймер
	pchar.quest.Captive_CreatePiratesOver2.over = "yes";//снять таймер
	if (pchar.location.from_sea == "Shore39")
	{
		AddQuestRecord("SharlieD", "2");
		CloseQuestHeader("SharlieD");
		DeleteAttribute(pchar, "questTemp.Sharlie.Captive");
		pchar.questTemp.Sharlie = "bankskipermoney";
	}
	else
	{
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
		chrDisableReloadToLocation = true;//закрыть локацию
		LAi_group_Delete("EnemyFight");
		int n = makeint(MOD_SKILL_ENEMY_RATE/2);
		if (n <= 1) n = 2;
		for (i=1; i<=n; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("CaptivePirate_"+i, "citiz_"+(40+i), "man", "man", 2, PIRATE, -1, false, "soldier"));
			sld.Dialog.Filename = "Quest\Sharlie\StartMiniQuests.c";
			sld.dialog.currentnode = "CaptivePirate";
			sld.greeting = "town_pirate";
			LAi_SetStayType(sld);
			sld.talker = 9;
			GiveItem2Character(sld, "slave_02");
			EquipCharacterbyItem(sld, "slave_02");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			if (i == 1 || i == 2 || i == 3) ChangeCharacterAddressGroup(sld, "Shore39", "smugglers", "smuggler0"+i);
			if (i == 4) ChangeCharacterAddressGroup(sld, "Shore39", "goto", "goto3");
			if (i == 5)
			{
				ChangeCharacterAddressGroup(sld, "Shore39", "goto", "goto5");
				LAi_CharacterDisableDialog(sld);
			}
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			if(i == 1)
			{
				TakeNItems(sld, "gold_dublon", 5);
				TakeNItems(sld, "jewelry44", 1);
				TakeNItems(sld, "jewelry42", 2);
			}
			if(i == 2)
			{
				TakeNItems(sld, "gold_dublon", 5);
				TakeNItems(sld, "jewelry44", 1);
				TakeNItems(sld, "jewelry42", 1);
				TakeNItems(sld, "jewelry41", 1);
			}
		}
		ref chr = GetCharacter(NPC_GenerateCharacter("CaptiveSpain", "q_spa_Ingenier", "man", "man", iRank+MOD_SKILL_ENEMY_RATE/2, SPAIN, -1, false, "quest"));
		SetFantomParamFromRank(chr, iRank+MOD_SKILL_ENEMY_RATE/2, true);
		RemoveCharacterEquip(chr, BLADE_ITEM_TYPE);
		RemoveCharacterEquip(chr, GUN_ITEM_TYPE);
		LAi_CharacterDisableDialog(chr);
		LAi_SetStayType(chr);
		ChangeCharacterAddressGroup(chr, "Shore39", "smugglers", "smugglerload");
		pchar.quest.Sharlie_captive2.win_condition.l1 = "NPC_Death";
		pchar.quest.Sharlie_captive2.win_condition.l1.character = "CaptiveSpain";
		pchar.quest.Sharlie_captive2.function = "Captive_failed";
	}
	NewGameTip(StringFromKey("SharlieTrial_15"));
}

void Captive_CreatePiratesOver(string qName)//просрочили
{
	if (GetHour() >= 4)
	{
		DoQuestFunctionDelay("Captive_CreatePiratesOver2", 1.0);
	}
	else
	{
		pchar.quest.Sharlie_captive.win_condition.l1 = "HardHour";
		pchar.quest.Sharlie_captive.win_condition.l1.hour = 0.00;
		pchar.quest.Sharlie_captive.function = "Captive_Timer";
		
		pchar.quest.Captive_CreatePiratesOver2.win_condition.l1 = "HardHour";
		pchar.quest.Captive_CreatePiratesOver2.win_condition.l1.hour = 4.00;
		pchar.quest.Captive_CreatePiratesOver2.function = "Captive_CreatePiratesOver2";
	}
}

void Captive_CreatePiratesOver2(string qName)//просрочили
{
	pchar.quest.Sharlie_captive.over = "yes";//снять прерывание
	pchar.quest.Sharlie_captive1.over = "yes";//снять прерывание
	AddQuestRecord("SharlieD", "3");
	CloseQuestHeader("SharlieD");
	DeleteAttribute(pchar, "questTemp.Sharlie.Captive");
	pchar.questTemp.Sharlie = "bankskipermoney";
}

void Captive_failed(string qName)//убили испанца, хотя это маловероятно
{
	chrDisableReloadToLocation = false;
	AddQuestRecord("SharlieD", "4");
	CloseQuestHeader("SharlieD");
	DeleteAttribute(pchar, "questTemp.Sharlie.Captive");
	pchar.questTemp.Sharlie = "bankskipermoney";
}

void CaptiveSpain_removeGuard(string qName)// убрать сражников с ворот 
{
	int num = FindNearCharacters(pchar, 5.5, -1.0, -1.0, 0.001, false, true);
	for (int j = 0; j < num; j++)
	{
		int idx = -1;
		if(CheckAttribute(chrFindNearCharacters[j], "index")) idx = sti(chrFindNearCharacters[j].index);	
		if(idx == -1) continue;
		ref findCh;
		findCh = GetCharacter(idx);
		if(CheckAttribute(findCh,"protector"))
		{
			ChangeCharacterAddressGroup(findCh, "none", "", "");
		}
	}
}

void CaptiveSpain_saveTip(string qName)// подсказка сохраниться
{
	DoQuestFunctionDelay("CaptiveSpain_saveTip2", 5.0);
}

void CaptiveSpain_saveTip2(string qName) 
{
	LaunchTutorial("Stealth", 1);
}

void CaptiveSpain_reload(string qName)//телепорт, если ночь на дворе
{
	PlaySound("Interface\knock.wav");
	DoQuestReloadToLocation("Fortfrance_bank", "reload", "reload1", "");
}

//драгоценность с мертвого вора
void Junglejew_CreateIndians(string qName) // Sinistra Нападение индейцев на жителя
{
	sld = GetCharacter(NPC_GenerateCharacter("JunglejewVict", "citiz_49", "man", "man", 5, PIRATE, 0, true, "soldier"));
	RemoveAllCharacterItems(sld, true);
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	sld.money = 560;
	TakeNItems(sld, "jewelry25", 1);
	TakeNItems(sld, "jewelry44", 1);
	TakeNItems(sld, "jewelry46", 1);
	TakeNItems(sld, "Mineral7", 1);
	TakeNItems(sld, "Mineral10", 1);
	TakeNItems(sld, "potion1", 2);
	LAi_SetHP(sld, 1.0, 1.0);
	ChangeCharacterAddressGroup(sld, "Martinique_jungle_01", "goto", "goto13");
	TeleportCharacterToPosAy(sld, -0.67, 0.20, 6.27, 0.99);
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "goto", "goto1", "", -1);
	LAi_group_MoveCharacter(sld, "Vor");
	for (i=1; i<=2; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("JunglejewInd_"+i, "canib_"+(i+4), "man", "man", 5, PIRATE, 0, true, "soldier"));
		SetFantomParamFromRank(sld, 5, true);
		LAi_SetImmortal(sld, true);
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, "Martinique_jungle_01", "goto", "goto1");
		TeleportCharacterToPosAy(sld, -8.55, 1.63, 27.74, -3.76);
		GiveItem2Character(sld, "slave_02");
		EquipCharacterbyItem(sld, "slave_02");
		RemoveCharacterEquip(sld, GUN_ITEM_TYPE);
	}
	LAi_SetActorType(pchar);
	DoQuestFunctionDelay("Junglejew_Cam", 0.1);
	DoQuestFunctionDelay("Junglejew_KillVictim", 3.8);
}

void Junglejew_Cam(string qName)
{
	StartQuestMovie(true, false, true);
	locCameraFromToPos(-10.37, 3.43, 26.69, true, 10.00, -1.00, 12.00);
}

void Junglejew_KillVictim(string qName)
{
	for (i=1; i<=2; i++)
	{
		sld = characterFromId("JunglejewInd_"+i);
		LAi_SetActorType(sld);
		LAi_ActorAttack(sld, CharacterFromID("JunglejewVict"), "");
	}
	
	DoQuestFunctionDelay("Junglejew_KillVictim_2", 2.2);
	PChar.quest.Junglejew_KillVictim_3.win_condition.l1 = "NPC_Death";
	PChar.quest.Junglejew_KillVictim_3.win_condition.l1.character = "JunglejewVict";
	PChar.quest.Junglejew_KillVictim_3.function = "Junglejew_KillVictim_3";
}

void Junglejew_KillVictim_2(string qName)
{
	sld = characterFromId("JunglejewVict");
	LAi_SetActorType(sld);
	LAi_ActorAnimation(sld, "afraid", "", -1);
	LAi_group_MoveCharacter(sld, "Vor");
}

void Junglejew_KillVictim_3(string qName)
{
	pchar.quest.Jungle_jew1.win_condition.l1 = "item";
	pchar.quest.Jungle_jew1.win_condition.l1.item = "jewelry25";
	pchar.quest.Jungle_jew1.function = "Junglejew_Findjew";
	DoQuestFunctionDelay("Junglejew_KillVictim_4", 2.0);
}

void Junglejew_KillVictim_4(string qName)
{
	for (i=1; i<=2; i++)
	{
		sld = characterFromId("JunglejewInd_"+i);
		LAi_SetActorType(sld);
		LAi_ActorRunToLocation(sld, "reload", "reload3_back", "none", "", "", "", -1);
	}
	DoQuestFunctionDelay("Junglejew_KillVictim_5", 1.7);
}

void Junglejew_KillVictim_5(string qName)
{
	LAi_SetPlayerType(pchar);
	EndQuestMovie();
	locCameraToPos(47.45, 2.40, -33.20, true);
	locCameraTarget(PChar);
	locCameraFollow();
}

void Junglejew_Findjew(string qName)//нашли драгоценность
{
	pchar.questTemp.Sharlie.Junglejew = "find";
	AddQuestRecord("SharlieE", "1");
	AddLandQuestMark(characterFromId("FortFrance_Mayor"), "questmarkmain");
}

//спасение дочери горожанина
void RescueDaughter_CreateProsper()//создаем Проспера
{
	sld = GetCharacter(NPC_GenerateCharacter("RD_Prosper", "Prospero_mush", "man", "mushketer", 10, FRANCE, -1, true, "soldier"));
	SetFantomParamFromRank(sld, 10, true);
	GiveItem2Character(sld, "unarmed");
	sld.equip.blade = "unarmed";
	GiveItem2Character(sld, "mushket1");
	EquipCharacterbyItem(sld, "mushket1");
	sld.MushketType = "mushket1";
	sld.MushketBulletType = "bullet";
	TakeNItems(sld, "bullet", 50);
	AddItems(sld, "gunpowder", 50);
	TakeNItems(sld, "potion1", 5);
	LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "bullet");
	LAi_SetHP(sld, 150, 150);
	SetSelfSkill(sld, 10, 10, 10, 100, 50);
	SetCharacterPerk(sld, "Gunman");
	SetCharacterPerk(sld, "BasicDefense");
	sld.MusketerDistance = 20;
	sld.SuperShooter = true;
	if(bImCasual) sld.MultiShooter = 2.0;
	AddLandQuestMark(sld, "questmarkmain");
	sld.name = StringFromKey("SharlieTrial_17");
	sld.lastname = StringFromKey("SharlieTrial_18");
	sld.Dialog.Filename = "Quest\Sharlie\StartMiniQuests.c";
	sld.dialog.currentnode = "Prosper";
	sld.greeting = "prosper_netvremeni";
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	LAi_SetStayType(sld);
	ChangeCharacterAddressGroup(sld, "Fortfrance_town", "quest", "quest2");
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	LAi_SetImmortal(sld, true);
	//таймер на просрочку
	pchar.quest.Sharlie_RescueDaughter.win_condition.l1 = "Timer";
	pchar.quest.Sharlie_RescueDaughter.win_condition.l1.date.hour  = sti(GetTime()+2);
	pchar.quest.Sharlie_RescueDaughter.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
	pchar.quest.Sharlie_RescueDaughter.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
	pchar.quest.Sharlie_RescueDaughter.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
	pchar.quest.Sharlie_RescueDaughter.function = "RescueDaughter_Over";
}

void RescueDaughter_Over(string qName)//опоздали
{
	sld = characterFromId("RD_Prosper");
	sld.lifeday = 0;
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "gate_back", "none", "", "", "", 10.0);
	AddQuestRecord("SharlieF", "2");
	CloseQuestHeader("SharlieF");
}

void RescueDaughter_CaveOver(string qName)//не пошли к пещере
{
	sld = characterFromId("RD_Prosper");
	sld.lifeday = 0;
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload2_back", "none", "", "", "", 10.0);
	AddQuestRecord("SharlieF", "4");
	CloseQuestHeader("SharlieF");
	ChangeCharacterComplexReputation(pchar, "nobility", -5);
	ChangeCharacterComplexReputation(pchar, "authority", -3);
}

void RescueDaughter_NearCave(string qName)//джунгли-4
{
	LocatorReloadEnterDisable("Martinique_jungle_04", "reload2_back", true);
	pchar.quest.Sharlie_RescueDaughter3.win_condition.l1 = "locator";
	pchar.quest.Sharlie_RescueDaughter3.win_condition.l1.location = "Martinique_jungle_04";
	pchar.quest.Sharlie_RescueDaughter3.win_condition.l1.locator_group = "reload";
	pchar.quest.Sharlie_RescueDaughter3.win_condition.l1.locator = "reload2_back";
	pchar.quest.Sharlie_RescueDaughter3.function = "RescueDaughter_Advice";
}

void RescueDaughter_Advice(string qName)//у входа в пещеру
{
	sld = characterFromId("RD_Prosper");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	pchar.quest.Sharlie_RescueDaughter4.win_condition.l1 = "location";
	pchar.quest.Sharlie_RescueDaughter4.win_condition.l1.location = "Martinique_CaveEntrance";
	pchar.quest.Sharlie_RescueDaughter4.function = "RescueDaughter_CreateIndiansLand";
}

void RescueDaughter_CreateIndiansLand(string qName)//бой с индеями у пещеры
{
	int iRank = MOD_SKILL_ENEMY_RATE*2-2;
	pchar.quest.Sharlie_RescueDaughter2.over = "yes"; //снять прерывание
	//закрываем локаторы
	LocatorReloadEnterDisable("Martinique_CaveEntrance", "reload1_back", true);
	LocatorReloadEnterDisable("Martinique_CaveEntrance", "reload2_back", true);
	sld = characterFromId("RD_Prosper");
	ChangeCharacterAddressGroup(sld, "Martinique_CaveEntrance", "officers", "reload2_1");
	LAi_SetImmortal(sld, false);
	LAi_SetWarriorType(sld);
	sld.MusketerDistance = 0;
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	for (i=1; i<=3; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("RD_Ind_"+i, "canib_"+i, "man", "man", iRank, PIRATE, 0, true, "soldier"));
		
		if (MOD_SKILL_ENEMY_RATE <= 4) { // mitrokosta халява
			SetSelfSkill(sld, 1, 1, 1, 1, 1);
		}
		
		// Rebbebion, новый лут
		switch (i)
		{
			case 1:
				GiveItem2Character(sld, "jewelry42");
			break;
			
			case 2:
				TakeNItems(sld, "cannabis1", 2);
			break;
			
			case 3:
				TakeNItems(sld, "potion5", 5);
			break;
		}
		
		GiveItem2Character(sld, "slave_02");
		EquipCharacterbyItem(sld, "slave_02");
		RemoveCharacterEquip(sld, GUN_ITEM_TYPE);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		ChangeCharacterAddressGroup(sld, "Martinique_CaveEntrance", "officers", "reload1_"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "RescueDaughter_KillIndiansLand");
	LAi_SetFightMode(pchar, true);
	DoQuestFunctionDelay("RescueDaughter_NewGameTip", 2.5);
}

void RescueDaughter_NewGameTip(string qName) {
	LaunchTutorial("LandTimeScaleDown", 1);
}

void RescueDaughter_CreateIndiansGrot(string qName)//бой с индеями в гроте
{
	int iRank = MOD_SKILL_ENEMY_RATE*2-2;
	LocatorReloadEnterDisable("Martinique_CaveEntrance", "reload2_back", false);
	chrDisableReloadToLocation = true;//закрыть локацию
	if (!CheckAttribute(pchar, "questTemp.Sharlie.RescueDaughter.KillProsper"))
	{
		sld = characterFromId("RD_Prosper");
		LAi_SetWarriorType(sld);
		sld.MusketerDistance = 0;
		ChangeCharacterAddressGroup(sld, "Martinique_Grot", "reload", "reload1_back");
	}
	ref rItm = ItemsFromID("fire");
	rItm.shown = true;
	rItm.startLocation = "Martinique_Grot";
	rItm.startLocator = "fire";
	CreateFireParticles("goto", "fire"); //костер
	//Селина
	sld = GetCharacter(NPC_GenerateCharacter("RD_Selina", "Selena", "woman", "towngirl", 1, FRANCE, -1, true, "quest"));
	SetFantomParamFromRank(sld, 1, true);
	sld.name = StringFromKey("SharlieTrial_19");
	sld.lastname = StringFromKey("SharlieTrial_20");
	sld.Dialog.Filename = "Quest\Sharlie\StartMiniQuests.c";
	sld.greeting = "rapers_girl_2";
	LAi_SetImmortal(sld, true);
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, "Martinique_Grot", "goto", "goto2");
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	//Жильберт
	sld = GetCharacter(NPC_GenerateCharacter("RD_Jilberte", "citiz_17", "man", "man", 5, FRANCE, -1, true, "quest"));
	FantomMakeCoolFighter(sld, 5, 5, 5, "", "", "", 10);
	sld.name = StringFromKey("SharlieTrial_21");
	sld.lastname = StringFromKey("SharlieTrial_22");
	sld.Dialog.Filename = "Quest\Sharlie\StartMiniQuests.c";
	sld.dialog.currentnode = "Jilberte";
	LAi_SetImmortal(sld, true);
	LAi_SetActorType(sld);
	LAi_ActorSetLayMode(sld);
	ChangeCharacterAddressGroup(sld, "Martinique_Grot", "monsters", "monster3");
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	//индеи
	for (i=1; i<=4; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("RD_IndCave_"+i, "canib_"+(i+1), "man", "man", iRank, PIRATE, 0, true, "soldier"));
		
		if (MOD_SKILL_ENEMY_RATE <= 8) { // mitrokosta халява
			SetSelfSkill(sld, 1, 1, 1, 1, 1);
		}
		
		RemoveAllCharacterItems(sld, true);
		GiveItem2Character(sld, "slave_02");
		EquipCharacterbyItem(sld, "slave_02");
		if (i == 4)
		{
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			TakeNItems(sld, "indian_3", 1);
			TakeNItems(sld, "cannabis1", 2);
			TakeNItems(sld, "potion3", 1);
		}
		else
		{
			DeleteAttribute(sld, "SaveItemsForDead");
			DeleteAttribute(sld, "DontClearDead");
		}
		ChangeCharacterAddressGroup(sld, "Martinique_Grot", "goto", "ass"+i);
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "Ground_sitting", "RescueDaughter_IndFight", 3);
	}
	DoQuestFunctionDelay("RescueDaughter_NewGameTip1", 1.0);
}

void RescueDaughter_NewGameTip1(string qName) {
	LaunchTutorial("OneToOneCave", 1);
}

void RescueDaughter_GoHome(string qName)//проводим домой
{
	chrDisableReloadToLocation = true;//закрыть локацию
	if (CheckAttribute(pchar, "questTemp.Sharlie.RescueDaughter.KillProsper"))
	{
		sld = characterFromId("RD_Selina");
		sld.dialog.currentnode = "Selina_8";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	else
	{
		sld = characterFromId("RD_Prosper");
		sld.dialog.currentnode = "Prosper_20";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	pchar.quest.Sharlie_RescueDaughter6.win_condition.l1 = "location";
	pchar.quest.Sharlie_RescueDaughter6.win_condition.l1.location = "Fortfrance_town";
	pchar.quest.Sharlie_RescueDaughter6.function = "RescueDaughter_Final";
}

void RescueDaughter_Final(string qName)//пришли в город
{
	chrDisableReloadToLocation = true;//закрыть локацию
	if (CheckAttribute(pchar, "questTemp.Sharlie.RescueDaughter.KillProsper"))
	{
		sld = characterFromId("RD_Selina");
		sld.dialog.currentnode = "Selina_11";
		ChangeCharacterAddressGroup(sld, "Fortfrance_town", "goto", "goto4");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	else
	{
		sld = characterFromId("RD_Prosper");
		sld.dialog.currentnode = "Prosper_23";
		ChangeCharacterAddressGroup(sld, "Fortfrance_town", "goto", "goto4");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		sld = characterFromId("RD_Selina");
		ChangeCharacterAddressGroup(sld, "Fortfrance_town", "goto", "goto4");
	}
	sld = characterFromId("RD_Jilberte");
	sld.dialog.currentnode = "Jilberte_4";
	ChangeCharacterAddressGroup(sld, "Fortfrance_town", "goto", "goto4");
	LAi_SetActorType(sld);
	LAi_ActorFollow(sld, pchar, "", -1);
	//LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void SharlieJungleNative(string qName)
{
	chrDisableReloadToLocation = true;
	sld = GetCharacter(NPC_GenerateCharacter("SJN_Ind", "canib_"+1, "man", "man", 2, PIRATE, 0, true, "soldier"));
	if (MOD_SKILL_ENEMY_RATE <= 4) SetSelfSkill(sld, 1, 1, 1, 1, 1);
	LAi_SetHP(sld, GetCharacterBaseHPValue(sld)/4, GetCharacterBaseHPValue(sld));
	RemoveAllCharacterItems(sld, true);
	GiveItem2Character(sld, "slave_02");
	EquipCharacterbyItem(sld, "slave_02");
	for(i = 1; i < 7; i++)
	{
		TakeNItems(sld, "cannabis"+i, 1);
	}
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	ChangeCharacterAddressGroup(sld, "Martinique_Jungle_01", "goto", "goto4");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "SharlieJungleNative_kill");
	LAi_SetFightMode(pchar, true);
	
}

void SharlieJungleBandos(string qName)
{
	chrDisableReloadToLocation = true;
	sld = GetCharacter(NPC_GenerateCharacter("SJB_Ind", "citiz_44", "man", "man", 2, PIRATE, 0, true, "marginal"));
	if (MOD_SKILL_ENEMY_RATE <= 4) SetSelfSkill(sld, 1, 1, 1, 1, 1);
	LAi_SetHP(sld, 40.0, 40.0);
	TakeNItems(sld, "bullet", 5);
	TakeNItems(sld, "gunpowder", 5);
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	ChangeCharacterAddressGroup(sld, "Martinique_Jungle_01", "goto", "goto1");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "SharlieJungleBandos_kill");
	LAi_SetFightMode(pchar, true);
}

void Sharlie_removeLocks(string qName)
{
	LocatorReloadEnterDisable("Fortfrance_town", "reload5_back", false);//откроем верфь
	LocatorReloadEnterDisable("Fortfrance_town", "reload7_back", false);// ЦЕРКОВЬ
	if(CheckAttribute(pchar,"questTemp.LockHouseEnc"))
	DeleteAttribute(pchar,"questTemp.LockHouseEnc");
	if(CheckAttribute(pchar,"questTemp.TimeLock"))
	DeleteAttribute(pchar,"questTemp.TimeLock");
	if(CheckAttribute(pchar,"GenQuest.CannotWait"))
	DeleteAttribute(pchar,"GenQuest.CannotWait");
	//NewGameTip("Доступна функция перемотки времени! Она доступна через опцию 'мысли вслух' в меню действий (ENTER).");
	if(!CheckAttribute(pchar, "questTemp.Sharlie.Gigolo") && !CheckAttribute(pchar, "questTemp.Sharlie.FastStart")) DoQuestFunctionDelay("Tutorial_rest", 1.0);
}
//<-- мини-квесты для сбора денег

void SharlieSeabattle_agent(string qName)//пиратский агент
{
	int iRank = MOD_SKILL_ENEMY_RATE+3;
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
	chrDisableReloadToLocation = true;//закрыть локацию
	sld = GetCharacter(NPC_GenerateCharacter("Seabattle_pirate", "citiz_46", "man", "man", iRank, PIRATE, -1, false, "soldier"));
	SetFantomParamFromRank(sld, iRank, true);
	FantomMakeSmallSailor(sld, SHIP_WAR_TARTANE, "", CANNON_TYPE_CANNON_LBS3, 15, 10, 15, 10, 10);
	if(MOD_SKILL_ENEMY_RATE < 9)
	{
		SetCharacterGoods(sld,GOOD_BOMBS,0);
		SetCharacterGoods(sld,GOOD_GRAPES,0);
	}
	sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
	sld.Dialog.currentnode = "Seabattle_pirate";
	sld.name = StringFromKey("SharlieTrial_23");
	sld.lastname = StringFromKey("SharlieTrial_24");
	sld.greeting = "town_pirate";
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, "Fortfrance_town", "goto", LAi_FindNearestLocator("goto", locx, locy, locz));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void SharlieSeabattle_ship(string qName)
{
	DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
	AddQuestRecord("Sharlie", "17");
	Island_SetReloadEnableGlobal("Martinique", false);
	bQuestDisableMapEnter = true;
	Group_FindOrCreateGroup("Pirate_Attack");
	Group_AddCharacter("Pirate_Attack", "Seabattle_pirate");
	Group_SetType("Pirate_Attack", "pirate");
	if (MOD_SKILL_ENEMY_RATE > 8)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Seabattle_pirate_1", "citiz_45", "man", "man", 10, PIRATE, -1, false, "soldier"));
		SetFantomParamFromRank(sld, 10, true);
		FantomMakeSmallSailor(sld, SHIP_WAR_TARTANE, "", CANNON_TYPE_CANNON_LBS3, 20, 25, 25, 30, 30);
		Group_AddCharacter("Pirate_Attack", "Seabattle_pirate_1");
	}
	Group_SetGroupCommander("Pirate_Attack", "Seabattle_pirate");
	Group_SetAddress("Pirate_Attack", "Martinique", "quest_ships", "quest_ship_5");
	Group_SetTaskAttack("Pirate_Attack", PLAYER_GROUP);
	Group_LockTask("Pirate_Attack");
	pchar.quest.SharlieSea_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.SharlieSea_AfterBattle.win_condition.l1.group = "Pirate_Attack";
	pchar.quest.SharlieSea_AfterBattle.function = "SharlieSea_AfterBattle";
	
	//NewGameTip("Управление в морском бою можно посмотреть в настройках");
	DoQuestFunctionDelay("SharlieSeabattle_NewGameTip1", 5.0);
	
	Weather.Wind.Speed = 16.0;
	pchar.wind.speed = Weather.Wind.Speed;
	fWeatherSpeed = stf(Weather.Wind.Speed);//халява первого выхода
	
	Weather.Wind.Angle = 0.0;
	pchar.wind.angle = Weather.Wind.Angle;
	fWeatherAngle = stf(Weather.Wind.Angle);//халява первого выхода
	
	pchar.systeminfo.tutorial.secondboarding1 = true;
}

void SharlieSeabattle_NewGameTip1(string qName) {
	DoQuestFunctionDelay("SharlieSeabattle_NewGameTip2", 10.0);
	LaunchTutorial("SeaBattle", 1);
}

void SharlieSeabattle_NewGameTip2(string qName) {
	NewGameTip(StringFromKey("SharlieTrial_25"));
}

void Sharlie_SkiperTalk(string qName)//штурман в каюте
{
    sld = characterFromId("Folke");
	if (pchar.questTemp.Sharlie.Ship == "sloop") sld.dialog.currentnode = "Folke_7";
	else sld.dialog.currentnode = "Folke_6";
	ChangeCharacterAddressGroup(sld, "My_Cabin_Small", "rld", "aloc1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void SharlieSea_AfterBattle(string qName)//после боя
{
	DoQuestCheckDelay("sea_victory", 1.5);
	Island_SetReloadEnableGlobal("Martinique", true);
	
	bDisableFastReload = false;
	DeleteAttribute(pchar, "GenQuest.CannotWait");
	i = FindColony("Fortfrance");
	DeleteAttribute(colonies[i], "DontSetShipInPort");//ставить корабли
	bNoEatNoRats  = false; // включаем еду и крыс
	Group_DeleteGroup("Pirate_Attack");
	AddQuestRecord("Sharlie", "18");
	pchar.questTemp.Sharlie = "fadey";//к Фадею на Гваделупу
	AddMapQuestMarkCity("BasTer", true);
	AddLandQuestMark(characterFromId("Fadey"), "questmarkmain");
	QuestPointerToLoc("baster_town", "reload", "houseSp1");
	bQuestDisableMapEnter = false; // если делюк мёртв по какой то причине
	NewGameTip(StringFromKey("SharlieTrial_26"));
	pchar.quest.Tut_WorldMap.win_condition.l1          = "MapEnter";
	pchar.quest.Tut_WorldMap.function                  = "Tutorial_WorldMap";
}

void SharlieSea_ReloadToCabin(string qName) {
	chrDisableReloadToLocation = true;
	pchar.GenQuest.DontSetCabinOfficer = true;
	Sea_CabinStartNow();
	sld = GetCharacter(CreateCharacterClone(CharacterFromID("Folke"), 0));
	sld.dialog.FileName = "Quest\Sharlie\OtherNPC.c";
	sld.dialog.currentnode = "Folke_clone";
	ChangeCharacterAddressGroup(sld, "My_Cabin_Small", "rld", "aloc1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, -1);
}

void FreeTichingituOver(string qName)//удаляем Тичингиту
{
	AddQuestRecord("Tichingitu", "6");
	CloseQuestHeader("Tichingitu");
	DeleteAttribute(pchar, "questTemp.Sharlie.Tichingitu");
	if (CheckCharacterItem(pchar, "letter_1")) RemoveItems(pchar, "letter_1", 1); // 170712
	QuestPointerDelLoc("BasTer_town", "reload", "reload_jail");
	QuestPointerDelLoc("baster_town", "reload", "houseSp1");
}

void SetTichingituJail()//ставим Тичингиту
{
	sld = GetCharacter(NPC_GenerateCharacter("Tichingitu", "maskog", "man", "man", 1, FRANCE, 10, false, "quest"));
	sld.name = StringFromKey("SharlieTrial_27"); // 270912
	sld.lastname = StringFromKey("SharlieTrial_28");
	sld.greeting = "Tichingitu";
    sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
	sld.dialog.currentnode = "Tichingitu";
	sld.rank = 12;
	LAi_SetHP(sld, 140.0, 140.0);
	SetSPECIAL(sld, 4, 9, 5, 5, 10, 8, 8);
	SetSelfSkill(sld, 30, 30, 30, 50, 20);
    SetShipSkill(sld, 5, 5, 2, 5, 1, 2, 1, 1, 10);
	SetCharacterPerk(sld, "Energaiser");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "BasicDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Gunman");
	GiveItem2Character(sld, "unarmed");
	sld.equip.blade = "unarmed";
	sld.equip.gun = "";
	ChangeCharacterAddressGroup(sld, "BasTer_prison", "goto", "goto9");
	LAi_SetStayType(sld);
	LAi_SetImmortal(sld, true); // 170712
	AddLandQuestMark(sld, "questmarkmain");
	SetFunctionLocationCondition("Tichingitu_AddQuestMark", "baster_prison", false);
	QuestPointerToLoc("BasTer_town", "reload", "reload_jail");
}

void Tichingitu_AddQuestMark(string qName)
{
	DoQuestFunctionDelay("Tichingitu_AddQuestMark_Delay", 2.5);
}

void Tichingitu_AddQuestMark_Delay(string qName)
{
	AddLandQuestMark(characterFromId("BasterJailOff"), "questmarkmain");
}

void Sharlie_GambitStage_level_9(string qName)//переход на голландский гамбит
{
	pchar.questTemp.Sharlie = "gambitstage";
	sld = characterFromId("Mishelle");
	sld.dialog.currentnode = "First time";
	sld.greeting = "mishelle_2";
	AddQuestRecord("Sharlie", "20_1");
}

void Sharlie_GambitStage_level_12(string qName)
{
	AddLandQuestMark(sld, "questmarkmain");
	AddMapQuestMarkCity("FortFrance", false);
	AddQuestRecord("Sharlie", "20_2");
}

void Persian_FindSkimitar(string qName)// скимитар 021012
{
	DeleteAttribute(pchar, "questTemp.Persian.skimitar");
}

void Persian_CirassLamport(string qName)// плетеный доспех
{
	pchar.questTemp.Persian = "cirass";
	SetFunctionTimerCondition("Persian_CirassLamportOver", 0, 0, 16, false); // таймер
}

void Persian_CirassLamportOver(string qName)// просрочка
{
	pchar.questTemp.Persian = "end";
}

// Sinistra - "Встреча с Диего" ==>
void VsD_DiegoInTaverna(string qName)
{
	DoQuestFunctionDelay("VsD_DiegoInTaverna_2", 0.0);
}

void VsD_DiegoInTaverna_2(string qName)
{
	FreeSitLocator("PortPax_tavern", "sit4");
	FreeSitLocator("PortPax_tavern", "sit5");
}

void VsD_GoToCity(string qName)
{
	sld = CharacterFromID("GiumDyubua");
	sld.location = "None";
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload1_back", "", "", "", "", -1);
			
	PChar.quest.VsD_Vzriv.win_condition.l1 = "location";
	PChar.quest.VsD_Vzriv.win_condition.l1.location = "PortPax_ExitTown";
	PChar.quest.VsD_Vzriv.function = "VsD_Vzriv";
}

void VsD_Vzriv(string qName)
{
	SetLocationCapturedState("PortPax_town", true);
	Locations[FindLocation("PortPax_town")].locators_radius.quest.quest1 = 1.5;
	Locations[FindLocation("PortPax_town")].locators_radius.patrol.patrol14 = 1.5;
	LocatorReloadEnterDisable("PortPax_ExitTown", "reload2_back", true);
	LocatorReloadEnterDisable("PortPax_ExitTown", "reload1_back", true);
	LAi_LocationFightDisable(&Locations[FindLocation("PortPax_town")], true);
		
	PChar.quest.VsD_Vzriv_2.win_condition.l1 = "location";
	PChar.quest.VsD_Vzriv_2.win_condition.l1.location = "PortPax_town";
	PChar.quest.VsD_Vzriv_2.function = "VsD_Vzriv_2";
	PChar.quest.VsD_DiegoInTaverna.over = "yes";
	
	for (i=1; i<=5; i++)
	{				
		sld = GetCharacter(NPC_GenerateCharacter("VsD_Guard_"+i, "sold_fra_"+(rand(7)+1), "man", "man", 5, FRANCE, -1, true, "soldier"));
		LAi_SetGuardianType(sld);
		LAi_CharacterDisableDialog(sld);
		LAi_LoginInCaptureTown(sld, true);
		ChangeCharacterAddressGroup(sld, "PortPax_town", "soldiers", "protector"+i);
	}
	
	for (i=1; i<=8; i++)
	{				
		sld = GetCharacter(NPC_GenerateCharacter("VsD_Sold_"+i, "sold_fra_"+(rand(7)+1), "man", "man", 5, FRANCE, -1, true, "soldier"));
		LAi_SetWarriorType(sld);
		LAi_CharacterDisableDialog(sld);
		LAi_LoginInCaptureTown(sld, true);
		ChangeCharacterAddressGroup(sld, "PortPax_town", "patrol", "patrol"+i);
	}
	
	for (i=1; i<=8; i++)
	{				
		sld = GetCharacter(NPC_GenerateCharacter("VsD_MirnyeMan_"+i, "citiz_"+(rand(59)+1), "man", "man", 5, FRANCE, -1, false, ""));
		LAi_SetCitizenType(sld);
		LAi_CharacterDisableDialog(sld);
		LAi_LoginInCaptureTown(sld, true);
		ChangeCharacterAddressGroup(sld, "PortPax_town", "goto", "goto"+(rand(19)+1));
	}
	
	for (i=1; i<=6; i++)
	{				
		sld = GetCharacter(NPC_GenerateCharacter("VsD_MirnyeWoman_"+i, "girl_"+(rand(10)+1), "woman", "woman", 5, FRANCE, -1, false, "quest"));
		LAi_SetCitizenType(sld);
		LAi_CharacterDisableDialog(sld);
		LAi_LoginInCaptureTown(sld, true);
		ChangeCharacterAddressGroup(sld, "PortPax_town", "goto", "goto"+(rand(19)+1));
	}
	
	sld = GetCharacter(NPC_GenerateCharacter("VsD_Tsyganka", "gipsy_1", "woman", "woman", 1, FRANCE, -1, false, "quest"));
	LAi_SetCitizenType(sld);
	LAi_CharacterDisableDialog(sld);
	LAi_LoginInCaptureTown(sld, true);
	ChangeCharacterAddressGroup(sld, "PortPax_town", "reload", "houseH1");
	
	sld = GetCharacter(NPC_GenerateCharacter("VsD_MirnyeQuest_1", "citiz_1"+(rand(9)+1), "man", "man", 5, FRANCE, -1, false, "quest"));
	LAi_SetStayType(sld);
	LAi_CharacterDisableDialog(sld);
	LAi_LoginInCaptureTown(sld, true);
	ChangeCharacterAddressGroup(sld, "PortPax_town", "rld", "loc0");
	
	sld = GetCharacter(NPC_GenerateCharacter("VsD_MirnyeQuest_2", "girl_"+(rand(10)+1), "woman", "woman", 5, FRANCE, -1, false, "quest"));
	LAi_SetStayType(sld);
	LAi_CharacterDisableDialog(sld);
	LAi_LoginInCaptureTown(sld, true);
	ChangeCharacterAddressGroup(sld, "PortPax_town", "reload", "reload1_back");
	
	sld = GetCharacter(NPC_GenerateCharacter("VsD_MirnyeQuest_3", "sold_fra_"+(rand(7)+1), "man", "man", 5, FRANCE, -1, true, "soldier"));
	LAi_SetStayType(sld);
	LAi_CharacterDisableDialog(sld);
	LAi_LoginInCaptureTown(sld, true);
	ChangeCharacterAddressGroup(sld, "PortPax_town", "patrol", "patrol14");
	
	sld = GetCharacter(NPC_GenerateCharacter("VsD_MirnyeQuest_4", "girl_"+(rand(10)+1), "woman", "woman", 5, FRANCE, -1, false, "quest"));
	LAi_SetStayType(sld);
	LAi_CharacterDisableDialog(sld);
	LAi_LoginInCaptureTown(sld, true);
	ChangeCharacterAddressGroup(sld, "PortPax_town", "officers", "reload5_2");
	
	sld = GetCharacter(NPC_GenerateCharacter("VsD_MirnyeQuest_5", "citiz_2"+(rand(1)+1), "man", "man", 5, FRANCE, -1, false, "quest"));
	LAi_SetStayType(sld);
	LAi_CharacterDisableDialog(sld);
	LAi_LoginInCaptureTown(sld, true);
	ChangeCharacterAddressGroup(sld, "PortPax_town", "officers", "reload5_3");
	
	sld = GetCharacter(NPC_GenerateCharacter("VsD_Rybak", "fisherman_1", "man", "fisher", 1, FRANCE, -1, false, "quest"));
	LAi_SetFisherSitType(sld);
	LAi_CharacterDisableDialog(sld);
	LAi_LoginInCaptureTown(sld, true);
	ChangeCharacterAddressGroup(sld, "PortPax_town", "fisher", "fisher1");
	
	PChar.quest.VsD_Vzriv_41.win_condition.l1 = "locator";
	PChar.quest.VsD_Vzriv_41.win_condition.l1.location = "PortPax_town";
	PChar.quest.VsD_Vzriv_41.win_condition.l1.locator_group = "quest";
	PChar.quest.VsD_Vzriv_41.win_condition.l1.locator = "quest1";
	PChar.quest.VsD_Vzriv_41.function = "VsD_Vzriv_4";
	PChar.quest.VsD_Vzriv_42.win_condition.l1 = "locator";
	PChar.quest.VsD_Vzriv_42.win_condition.l1.location = "PortPax_town";
	PChar.quest.VsD_Vzriv_42.win_condition.l1.locator_group = "patrol";
	PChar.quest.VsD_Vzriv_42.win_condition.l1.locator = "patrol14";
	PChar.quest.VsD_Vzriv_42.function = "VsD_Vzriv_4_alt";
}

void VsD_Vzriv_2(string qName)
{
	chrDisableReloadToLocation = true;
	DoQuestFunctionDelay("VsD_Vzriv_3", 1.0);
	
	if (GetCharacterIndex("Folke") != -1 && CheckPassengerInCharacter(pchar, "Folke"))
	{
		sld = CharacterFromID("Folke");
		LAi_SetActorType(sld);
		LAi_LoginInCaptureTown(sld, true);
		ChangeCharacterAddressGroup(sld, "PortPax_town", "reload", "reload1_back");
	}
	else
	{
		sld = GetCharacter(NPC_GenerateCharacter("Alonso", "Alonso", "man", "man", 25, pchar.nation, -1, true, "soldier"));
		sld.name 	= StringFromKey("SharlieTrial_29");
		sld.lastname = StringFromKey("SharlieTrial_30");
		LAi_SetActorType(sld);
		LAi_LoginInCaptureTown(sld, true);
		ChangeCharacterAddressGroup(sld, "PortPax_town", "reload", "reload1_back");
	}
}

void VsD_Vzriv_3(string qName)
{
	sld = CharacterFromID("VsD_MirnyeQuest_1");
	LAi_SetActorType(sld);
	LAi_ActorTurnToCharacter(sld, CharacterFromID("VsD_Guard_3"));
	
	sld = CharacterFromID("VsD_MirnyeQuest_4");
	LAi_SetActorType(sld);
	LAi_ActorTurnToCharacter(sld, CharacterFromID("VsD_MirnyeQuest_5"));
	
	sld = CharacterFromID("VsD_MirnyeQuest_5");
	LAi_SetActorType(sld);
	LAi_ActorTurnToCharacter(sld, CharacterFromID("VsD_MirnyeQuest_4"));
	
	if (GetCharacterIndex("Folke") != -1 && CheckPassengerInCharacter(pchar, "Folke"))
	{
		sld = CharacterFromID("Folke");
		LAi_SetActorType(sld);
		LAi_ActorTurnToCharacter(sld, CharacterFromID("VsD_MirnyeQuest_2"));
	}
	else
	{
		sld = CharacterFromID("Alonso");
		LAi_SetActorType(sld);
		LAi_ActorTurnToCharacter(sld, CharacterFromID("VsD_MirnyeQuest_2"));
	}
}

void VsD_Vzriv_4(string qName)
{
	StartQuestMovie(true, false, true);
	locCameraFromToPos(-1.88, 6.25, -33.43, false, -30.00, 1.60, -60.00);
	SetTimeScale(1.0);
	LAi_SetActorType(pchar);
	LAi_ActorGoToLocator(pchar, "reload", "reload1", "", -1);
	PChar.quest.VsD_Vzriv_41.over = "yes";
	PChar.quest.VsD_Vzriv_42.over = "yes";
	sld = CharacterFromID("VsD_MirnyeQuest_3");
	LAi_SetActorType(sld);
	LAi_ActorTurnToCharacter(sld, pchar);
	
	DoQuestFunctionDelay("VsD_Vzriv_5", 4.0);
	DoQuestFunctionDelay("VsD_Vzriv_5_1", 3.4);
}
void VsD_Vzriv_4_alt(string qName)
{
	StartQuestMovie(true, false, true);
	locCameraFromToPos(-1.88, 6.25, -33.43, false, -30.00, 1.60, -60.00);
	SetTimeScale(1.0);
	LAi_SetActorType(pchar);
	LAi_ActorGoToLocator(pchar, "reload", "reload1", "", -1);
	PChar.quest.VsD_Vzriv_41.over = "yes";
	PChar.quest.VsD_Vzriv_42.over = "yes";
	sld = CharacterFromID("VsD_MirnyeQuest_3");
	LAi_SetActorType(sld);
	LAi_ActorTurnToCharacter(sld, pchar);
	
	DoQuestFunctionDelay("VsD_Vzriv_5", 3.0);
	DoQuestFunctionDelay("VsD_Vzriv_5_1", 2.4);
}
void VsD_Vzriv_5_1(string qName)
{
	SetMusic("music_teleport");
}
void VsD_Vzriv_5(string qName)
{
	LAi_SetActorType(pchar);
	Ship_Detonate(pchar, false, false);
	PlaySound("Sea Battles\Vzriv_fort_001.wav");
	PlaySound("Sea Battles\vzriv_pogreb_002.wav");
	PlaySound("Sea Battles\vzriv_pogreb_002.wav");
	DoQuestFunctionDelay("VsD_Vzriv_6", 0.3);
}
void VsD_Vzriv_6(string qName)
{
	sld = CharacterFromID("VsD_MirnyeQuest_1");
	sld.CantLoot = true;
	LAi_KillCharacter(sld);
	sld = CharacterFromID("VsD_MirnyeQuest_2");
	sld.CantLoot = true;
	LAi_KillCharacter(sld);
	sld = CharacterFromID("VsD_MirnyeQuest_3");
	sld.CantLoot = true;
	LAi_KillCharacter(sld);
	sld = CharacterFromID("VsD_Rybak");
	sld.CantLoot = true;
	LAi_KillCharacter(sld);
	for (i=4; i<=5; i++)
	{				
		sld = CharacterFromID("VsD_MirnyeQuest_"+i);
		LAi_SetActorType(pchar);
		LAi_ActorAnimation(sld, "afraid", "", -1);
	}
	if (GetCharacterIndex("Folke") != -1 && CheckPassengerInCharacter(pchar, "Folke"))
	{
		sld = CharacterFromID("Folke");
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "afraid", "", -1);
	}
	else
	{
		sld = CharacterFromID("Alonso");
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "afraid", "", -1);
	}
	sld = CharacterFromID("Tichingitu");
	if (sld.location == pchar.location && !LAi_IsDead(sld))
	{
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "afraid", "", -1);
	}
	LAi_SetActorType(pchar);
	LAi_ActorAnimation(pchar, "afraid", "", -1);
	
	DoQuestFunctionDelay("VsD_Vzriv_7", 1.2);
}
void VsD_Vzriv_7(string qName)
{
	Ship_Detonate(pchar, false, false);
	PlaySound("Sea Battles\vzriv_pogreb_002.wav");
	PlaySound("Sea Battles\vzriv_pogreb_002.wav");
	DoQuestFunctionDelay("VsD_Vzriv_8", 1.5);
}
void VsD_Vzriv_8(string qName)
{
	for (i=4; i<=5; i++)
	{				
		sld = CharacterFromID("VsD_MirnyeQuest_"+i);
		sld.lifeday = 0;
		LAi_SetActorType(sld);
		LAi_ActorRunToLocation(sld, "reload", "houseF3", "none", "", "", "", -1);
	}
	for (i=1; i<=2; i++)
	{				
		sld = CharacterFromID("VsD_MirnyeMan_"+i);
		sld.lifeday = 0;
		LAi_SetActorType(sld);
		LAi_ActorRunToLocation(sld, "reload", "reload4_back", "none", "", "", "", -1);
	}
	for (i=3; i<=8; i++)
	{				
		sld = CharacterFromID("VsD_MirnyeMan_"+i);
		sld.lifeday = 0;
		LAi_SetActorType(sld);
		LAi_ActorRunToLocator(sld, "goto", "goto23", "", -1);
	}
	for (i=1; i<=2; i++)
	{				
		sld = CharacterFromID("VsD_MirnyeWoman_"+i);
		sld.lifeday = 0;
		LAi_SetActorType(sld);
		LAi_ActorRunToLocation(sld, "reload", "houseSp4", "none", "", "", "", -1);
	}
	for (i=3; i<=6; i++)
	{				
		sld = CharacterFromID("VsD_MirnyeWoman_"+i);
		sld.lifeday = 0;
		LAi_SetActorType(sld);
		LAi_ActorRunToLocator(sld, "goto", "goto15", "", -1);
	}
	for (i=1; i<=6; i++)
	{				
		sld = CharacterFromID("VsD_Sold_"+i);
		sld.lifeday = 0;
		LAi_SetActorType(sld);
		LAi_ActorRunToLocator(sld, "quest", "quest1", "", -1);
	}
	sld = CharacterFromID("VsD_Tsyganka");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocator(sld, "goto", "goto10", "", -1);
	DoQuestFunctionDelay("VsD_Vzriv_9", 2.0);
}
void VsD_Vzriv_9(string qName)
{
	locCameraFromToPos(-15.48, 5.74, -42.69, true, 50.00, 1.60, -16.00);
	if (GetCharacterIndex("Folke") != -1 && CheckPassengerInCharacter(pchar, "Folke"))
	{
		sld = CharacterFromID("Folke");
		LAi_SetActorType(sld);
	}
	else
	{
		sld = CharacterFromID("Alonso");
		LAi_SetActorType(sld);
	}
	sld = CharacterFromID("Tichingitu");
	if (sld.location == pchar.location && !LAi_IsDead(sld))
	{
		LAi_SetActorType(sld);
	}
	LAi_SetActorType(pchar);
	DoQuestFunctionDelay("VsD_Vzriv_10", 6.5);
}
void VsD_Vzriv_10(string qName)
{
	EndQuestMovie();
	LAi_SetPlayerType(pchar);
	locCameraToPos(-5.35, 5.14, -38.53, true);
	CreateLocationParticles("shipfire", "reload", "reload5_back", 3, 0, 0, "");
	if (GetCharacterIndex("Folke") != -1 && CheckPassengerInCharacter(pchar, "Folke"))
	{
		sld = CharacterFromID("Folke");
		sld.dialog.filename = "Quest\Sharlie\OtherNPC.c";
		sld.dialog.currentnode = "VsD_FolkeAlonso";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 0.1);
	}
	else
	{
		sld = CharacterFromID("Alonso");
		sld.dialog.filename = "Quest\Sharlie\OtherNPC.c";
		sld.dialog.currentnode = "VsD_FolkeAlonso";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 0.1);
	}
	
	for (i=7; i<=8; i++)
	{				
		sld = CharacterFromID("VsD_Sold_"+i);
		sld.lifeday = 0;
		LAi_SetActorType(sld);
		LAi_ActorRunToLocator(sld, "rld", "loc0", "", -1);
	}
}
// <== "Встреча с Диего"

///////////////////////////////////////////////////////////////////////////////////////////////////////////	
///Jason------------------------------------- Карибские нравы ----------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void Sharlie_TrialOver(string qName)// пропустил сроки
{
	DelLandQuestMark(characterFromId("Fadey"));
	DelMapQuestMarkCity("BasTer");
	
	pchar.questTemp.Trial.late = true;
	pchar.questTemp.TrialEnd = true;
}

void Trial_StartLine(string qName)// начало линейки
{
	sld = GetCharacter(NPC_GenerateCharacter("Lecrua", "trader_8", "man", "man", 10, FRANCE, -1, true, "citizen"));
	SetFantomParamFromRank(sld, 10, true);
	sld.name = StringFromKey("SharlieTrial_31");
	sld.lastname = StringFromKey("SharlieTrial_32");
	sld.dialog.FileName = "Quest\Sharlie\Trial.c";
	sld.dialog.currentnode = "Lecrua";
	sld.greeting = "captain_trader";
	LAi_SetStayType(sld);
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, "baster_store", "goto", "goto4");
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	AddLandQuestMark(sld, "questmarkmain");
	SetFunctionTimerCondition("Trial_LineOver", 0, 0, 1, false); // таймер
}

void Trial_LineOver(string qName)// пропустил сроки
{
	sld = characterFromId("Lecrua");
	LAi_CharacterDisableDialog(sld);//запрет диалога
	sld.lifeday = 0;
	AddQuestRecord("Trial", "2");
	CloseQuestHeader("Trial");
	DeleteAttribute(pchar, "questTemp.Trial");
	pchar.questTemp.TrialEnd = true;
}

void Trial_LecruaHide(string qName)// 
{
	sld = characterFromId("Lecrua");
	ChangeCharacterAddressGroup(sld, "none", "", "");
}

void Trial_FrahtFail(string qName)// провалил 1 задание
{
	sld = characterFromId("Lecrua");
	sld.lifeday = 0;
	AddQuestRecord("Trial", "5");
	CloseQuestHeader("Trial");
	DeleteAttribute(pchar, "questTemp.Trial");
	pchar.questTemp.TrialEnd = true;
	PChar.quest.VsD_DiegoNachalo.over = "yes";
	ChangeCharacterNationReputation(pchar, FRANCE, -12);
	DelMapQuestMarkCity("PortPax");
	DeleteAttribute(pchar,"worldmapencountersoff");
}

void Trial_CreateFlorianFrigate(string qName)// ставим фрегат Флориана Шоке
{
	Group_FindOrCreateGroup("Florian_group");
	Group_SetType("Florian_group", "war");//тип группы
	sld = GetCharacter(NPC_GenerateCharacter("Florian", "off_fra_3", "man", "man", 40, FRANCE, -1, true, "quest"));
	FantomMakeCoolSailor(sld, SHIP_FRIGATE, StringFromKey("SharlieTrial_33"), CANNON_TYPE_CANNON_LBS24, 105, 105, 105);
	FantomMakeCoolFighter(sld, 40, 100, 100, "blade_13", "pistol1", "bullet", 250);
	sld.name = StringFromKey("SharlieTrial_34");
	sld.lastname = StringFromKey("SharlieTrial_35");
	sld.dialog.FileName = "Quest\Sharlie\Trial.c";
	sld.DeckDialogNode = "florian_deck";
	sld.greeting = "captain";
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.Ship.Mode = "war";
	sld.DontHitInStorm = true; //не ломается в шторм
	sld.Abordage.Enable = false;
	sld.SinkTenPercent = false;
	sld.AlwaysSandbankManeuver = true;
	sld.MultiFighter = 2.5; // мультифайтер
	sld.ship.Crew.Morale = 100;
	sld.Ship.Crew.Exp.Sailors = 100;
	sld.Ship.Crew.Exp.Cannoners = 100;
	sld.Ship.Crew.Exp.Soldiers = 100;
	SetCharacterPerk(sld, "MusketsShoot");
	Group_AddCharacter("Florian_group", "Florian");
	Group_SetGroupCommander("Florian_group", "Florian");
	Group_SetTaskNone("Florian_group");
	Group_SetAddress("Florian_group", "Portobello", "quest_ships", "quest_ship_8");
	Group_LockTask("Florian_group");
	
	pchar.quest.Trial_Florian_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.Trial_Florian_AfterBattle.win_condition.l1.group = "Florian_group";
	pchar.quest.Trial_Florian_AfterBattle.function = "Trial_FlorianAfterBattle";
	DelMapQuestMarkShore("shore47");
	AddLandQuestMark(sld, "questmarkmain");
}

void Trial_CannonFail(string qName)// провалил 2 задание
{
	pchar.quest.Trial_cannon.over = "yes"; 
	sld = characterFromId("Lecrua");
	sld.lifeday = 0;
	AddQuestRecord("Trial", "8");
	CloseQuestHeader("Trial");
	DeleteAttribute(pchar, "questTemp.Trial");
	pchar.questTemp.TrialEnd = true;
	ChangeCharacterNationReputation(pchar, FRANCE, -15);
	//DelMapQuestMarkCity("PortoBello");
	DelMapQuestMarkShore("shore47");
	sld = CharacterFromID("PortRoyal_shipyarder");
	if(CheckAttribute(sld, "TrialDelQuestMark"))
	{
		DeleteAttribute(sld, "TrialDelQuestMark");
		DelLandQuestMark(sld);
		DelMapQuestMarkCity("PortRoyal");
	}
	DeleteAttribute(pchar,"worldmapencountersoff");
}

void Trial_FlorianAfterBattle(string qName)// напал на Флориана Шоке
{
	bQuestDisableMapEnter = false;
	sld = characterFromId("Lecrua");
	sld.lifeday = 0;
	AddQuestRecord("Trial", "9");
	CloseQuestHeader("Trial");
	DeleteAttribute(pchar, "questTemp.Trial");
	pchar.questTemp.TrialEnd = true;
	ChangeCharacterNationReputation(pchar, FRANCE, -60);
	DelMapQuestMarkShore("shore47");
	sld = CharacterFromID("PortRoyal_shipyarder");
	if(CheckAttribute(sld, "TrialDelQuestMark"))
	{
		DeleteAttribute(sld, "TrialDelQuestMark");
		DelLandQuestMark(sld);
		DelMapQuestMarkCity("PortRoyal");
	}
	DeleteAttribute(pchar,"worldmapencountersoff");
}

void Trial_TakeCannons()// выгрузка
{
	SetLaunchFrameFormParam(StringFromKey("SharlieTrial_36", NewStr()), "", 0, 5);
	LaunchFrameForm();
	WaitDate("", 0, 0, 0, 3, 10); //крутим время
	RecalculateJumpTable();
	DoQuestFunctionDelay("Trial_TakeCannonsEnd", 1.0);
}

void Trial_TakeCannonsEnd()// 
{
	RemoveCharacterGoods(pchar, GOOD_CANNON_24, 15);
	sld = characterFromId("Florian");
	sld.dialog.currentnode = "florian_deck_4";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 1.0, -1);
}

void Trial_CreatHabitue(string qName)// создадим пьяницу со слухом
{
	FreeSitLocator("PortoBello_tavern", "sit_base3");
	FreeSitLocator("PortoBello_tavern", "sit_front3");
	iTemp = NPC_GeneratePhantomCharacter("citizen", SPAIN, MAN, 10);
	sld = &characters[iTemp];
	sld.City = Colonies[FindColony(loadedLocation.fastreload)].id;
	//sld.CityType = "citizen";
	ChangeCharacterAddressGroup(sld, loadedLocation.id, "sit", "sit_base3");
	sld.Default           = loadedLocation.id;
	sld.Default.group     = "sit";
	sld.Default.ToLocator = "sit_front3";
	LAi_SetLoginTime(sld, 0.0, 24.0);
	LAi_SetSitType(sld);
	//LAi_group_MoveCharacter(sld, slai_group);
	sld.quest.last_theme = 0;
	sld.dialog.filename = "Habitue_dialog.c";
	sld.dialog.currentnode = "first time";
	sld.greeting = "habitue"; // пьянтос
	AddLandQuestMark(sld, "questmarkmain");
	AddLandQuestMark(characterFromID("PortoBello_tavernkeeper"), "questmarkmain"); // Rebbebion, на трактирщика тоже
	pchar.questTemp.trialHabitueId = sld.id;
	DoQuestFunctionDelay("Trial_FreeSitlocator", 1.0);
	QuestPointerDelLoc("shore47", "reload", "reload1_back");
	QuestPointerDelLoc("PortoBello_Jungle_02", "reload", "reload1_back");
	QuestPointerDelLoc("PortoBello_Jungle_01", "reload", "reload3_back");
	QuestPointerDelLoc("PortoBello_ExitTown", "reload", "reload4");
	QuestPointerDelLoc("PortoBello_Town", "reload", "reload41_back");
	QuestPointerDelLoc("PortoBello_Town", "reload", "reload4_back");
}

void Trial_FreeSitlocator(string qName)// очистить локатор дубль
{
	FreeSitLocator("PortoBello_tavern", "sit_front3");
}

void Trial_RemoveFlorian(string qName)// трем Флориана
{
	if (GetCharacterIndex("Florian") != -1)
	{
		pchar.quest.Trial_Florian_AfterBattle.over = "yes"; //снять прерывание
		sld = characterFromId("Florian");
		sld.DontDeskTalk = true;
		sld.lifeday = 0;
	}
	pchar.quest.Trial_CreatHabitue.over = "yes";
	if(CheckAttribute(pchar,"questTemp.trialHabitueId"))
	{
		if (GetCharacterIndex(pchar.questTemp.trialHabitueId) != -1)
		{
			sld = characterFromId(pchar.questTemp.trialHabitueId);
			sld.lifeday = 0;
			DeleteAttribute(pchar,"questTemp.trialHabitueId");
		}
	}
}

void Trial_SpyTimeOver(string qName) //время на шпионаж вышло
{
	QuestPointerDelLoc("shore47", "reload", "reload1_back");
	QuestPointerDelLoc("PortoBello_Jungle_02", "reload", "reload1_back");
	QuestPointerDelLoc("PortoBello_Jungle_01", "reload", "reload3_back");
	QuestPointerDelLoc("PortoBello_ExitTown", "reload", "reload4");
	QuestPointerDelLoc("PortoBello_Town", "reload", "reload41_back");
	QuestPointerDelLoc("PortoBello_Town", "reload", "reload4_back");
	
	QuestPointerDelLoc("PortoBello_Town", "reload", "gate_back");
	QuestPointerDelLoc("PortoBello_ExitTown", "reload", "reload1_back");
	QuestPointerDelLoc("PortoBello_Jungle_01", "reload", "reload2_back");
	QuestPointerDelLoc("PortoBello_Jungle_02", "reload", "reload3_back");
	QuestPointerDelLoc("shore47", "reload", "boat");
	
	bQuestDisableMapEnter = false;//открыть карту
	DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle"); // patch-7
	DoQuestFunctionDelay("Trial_RemoveFlorian", 0.5);
	AddQuestRecord("Trial", "18");
	CloseQuestHeader("Trial");
	DeleteAttribute(pchar, "questTemp.Trial");
	pchar.questTemp.TrialEnd = true;
	pchar.quest.Trial_CreatHabitue.over = "yes";
	if(CheckAttribute(pchar,"questTemp.trialHabitueId"))
	{
		if (GetCharacterIndex(pchar.questTemp.trialHabitueId) != -1)
		{
			sld = characterFromId(pchar.questTemp.trialHabitueId);
			sld.lifeday = 0;
			DeleteAttribute(pchar,"questTemp.trialHabitueId");
		}
	}
	DeleteAttribute(pchar,"worldmapencountersoff");
}

void Trial_TavernEnterSoldiers() //неверный путь в таверне
{	
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+5;
	for (i=1; i<=3; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter("TTSold"+i, "sold_spa_"+(rand(1)+1), "man", "man", iRank, SPAIN, 0, true, "soldier"));
		SetFantomParamFromRank(sld, iRank, true);         
		LAi_SetWarriorType(sld); 
		LAi_warrior_DialogEnable(sld, false);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
    }
    sld = GetCharacter(NPC_GenerateCharacter("TTOfficer", "off_spa_"+(rand(1)+1), "man", "man", iRank, SPAIN, 0, true, "quest"));
	FantomMakeCoolFighter(sld, iRank, iRank+30, iRank+30, "blade_19", "pistol3", "grapeshot", 50);
	sld.name = StringFromKey("SharlieTrial_37");
	sld.lastname = StringFromKey("SharlieTrial_38");
	sld.dialog.FileName = "Quest\Sharlie\Trial.c";
	sld.dialog.currentnode = "tavern_officer";
	sld.greeting = "soldier_arest";
    LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
	LAi_ActorDialog(sld, pchar, "", 1.0, 0);
	
	sld = characterFromId("Florian");
	sld.DeckDialogNode = "florian_failspy";
	pchar.questTemp.Trial = "spy_fail";
	if(CheckAttribute(pchar,"questTemp.trialHabitueId"))
	{
		if (GetCharacterIndex(pchar.questTemp.trialHabitueId) != -1)
		{
			sld = characterFromId(pchar.questTemp.trialHabitueId);
			sld.lifeday = 0;
			DeleteAttribute(pchar,"questTemp.trialHabitueId");
		}
	}
}

void Trial_Spyfail_NextStage(string qName)//активируем следующий квест, если попался шпионом
{
	sld = characterFromId("Florian");
	sld.DeckDialogNode = "florian_17";
}

void Trial_SetPoormanInPort(string qName)//ставим нищеброда
{
	sld = characterFromId("PortoBello_Poorman");
	sld.dialog.currentnode = "trial_6";
	ChangeCharacterAddressGroup(sld, "Portobello_town", "reload", "reload5");
	LAi_SetStayType(sld);
	AddLandQuestMark(sld, "questmarkmain");
}

void Trial_CreatePueblaBarqueInWorld()//запускаем барк 'Пуэбла' на карте
{
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE/2;
	int iScl = MOD_SKILL_ENEMY_RATE+3*sti(pchar.rank);
    string sCapId = "PueblaCap";
    string sGroup = "Sea_" + sCapId + "1";
	Group_DeleteGroup(sGroup);
	Group_FindOrCreateGroup(sGroup);
	sld = GetCharacter(NPC_GenerateCharacter(sCapId, "off_spa_"+(rand(1)+1), "man", "man", iRank, SPAIN, 3, true, "soldier"));
	FantomMakeSmallSailor(sld, SHIP_BARKENTINE, StringFromKey("SharlieTrial_39"), CANNON_TYPE_CANNON_LBS3, iScl+10, iScl, iScl, iScl, iScl);
	FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_14", "pistol1", "bullet", iScl*2);
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "BasicBattleState");
	SetCharacterPerk(sld, "AdvancedBattleState");
	SetCharacterPerk(sld, "ShipSpeedUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	UpgradeShipParameter(sld, "Capacity");
	AddCharacterGoods(sld,GOOD_POWDER, GetCharacterFreeSpace(sld, GOOD_POWDER));
	sld.AlwaysEnemy = true;
	sld.DontRansackCaptain = true;
	sld.Ship.Mode = "war";
	sld.AnalizeShips = true;
	sld.mapEnc.type = "war";
	sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.Name = StringFromKey("SharlieTrial_40");
	Group_AddCharacter(sGroup, sCapId);
    Group_SetGroupCommander(sGroup, sCapId);
    Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
    Group_LockTask(sGroup);
	Map_CreateTrader("Shore25", "Portobello", sld.id, 3);
	// --> 170712
	pchar.quest.Trial_Puebla_barque_Check.win_condition.l1 = "Group_Death";
	pchar.quest.Trial_Puebla_barque_Check.win_condition.l1.group = sGroup;
	pchar.quest.Trial_Puebla_barque_Check.function = "Trial_Pueblabarque_Check";
	
	//на захват либо потопление абордажем
	pchar.quest.Trial_Puebla_barque_abordage.win_condition.l1 = "Character_Capture";
	pchar.quest.Trial_Puebla_barque_abordage.win_condition.l1.character = "PueblaCap";
	pchar.quest.Trial_Puebla_barque_abordage.function = "Trial_Pueblabarque_AfterBattle";//взяли на абордаж
	//на потопление орудиями
	pchar.quest.Trial_Puebla_barque_Sink.win_condition.l1 = "Character_sink";
	pchar.quest.Trial_Puebla_barque_Sink.win_condition.l1.character = "PueblaCap";
	pchar.quest.Trial_Puebla_barque_Sink.function = "Trial_Pueblabarque_AfterBattle";//потопили
	
	pchar.questTemp.Trial.Tip = true;
	
	/* pchar.quest.Tutorial_Mushket.win_condition.l1 = "mushket";
	pchar.quest.Tutorial_Mushket.function = "Tutorial_Mushket"; */
}

void Trial_Pueblabarque_AfterBattle(string qName)// уничтожили
{
	DoQuestCheckDelay("sea_victory", 1.5);
	AddQuestRecord("Trial", "21");
	pchar.questTemp.Trial = "next_round";
	sld = characterFromId("BasTer_trader");
	sld.quest.trial_usurer = true;
	AddLandQuestMark(sld, "questmarkmain");
	AddMapQuestMarkCity("BasTer", true);
	pchar.questTemp.Trial.PueblaDie = "true";
	AddComplexSeaExpToScill(50, 50, 50, 50, 50, 50, 0);
	ChangeCharacterNationReputation(pchar, SPAIN, -3);
	ChangeCharacterComplexReputation(pchar, "fame", 1);
	DeleteAttribute(pchar,"worldmapencountersoff");
}

void Trial_Pueblabarque_Check(string qName)// истекло время энкаунтера или уничтожен
{
	SetFunctionTimerCondition("Trial_Pueblabarque_Result", 0, 0, 1, false); // таймер
}

void Trial_Pueblabarque_Result(string qName) // результаты
{
	Group_DeleteGroup("Sea_PueblaCap1");
	pchar.quest.Trial_Puebla_barque_abordage.over = "yes"; // mitrokosta фикс двойной награды за пуэблу
	pchar.quest.Trial_Puebla_barque_Sink.over = "yes";
	if (CheckAttribute(pchar, "questTemp.Trial.PueblaDie")) // уничтожен
	{
		return;
	}
	else // упущен
	{
		sld = characterFromId("Lecrua");
		sld.lifeday = 0;
		AddQuestRecord("Trial", "20");
		CloseQuestHeader("Trial");
		DeleteAttribute(pchar, "questTemp.Trial");
		pchar.questTemp.TrialEnd = true;
		DeleteAttribute(pchar,"worldmapencountersoff");
	}
} // <-- 170712

//=================================================================
//======================кейсы из quests_reaction===================
//=================================================================
bool SharlieTrial_QuestComplete(string sQuestName, string qname)
{
///////////////////////////////////////////////////////////////////////////////////////////////////
///  Jason  								Бремя гасконца
//////////////////////////////////////////////////////////////////////////////////////////////////

	ref sld, chr;
	int iTemp, i;
	string sTemp;
	
	bool condition = true;
	
	if (sQuestName == "Sharlie_Start")
	{
			SetCurrentTime(11, 30);
			CreateWeatherEnvironment();
			CreateSea(EXECUTE, REALIZE);
			CreateWeather(EXECUTE,REALIZE);
			//LoadMainCharacterInFirstLocationGroup("My_Campus", "rld", "loc2");
			sld = GetCharacter(NPC_GenerateCharacter("Sh_startsailor", "citiz_39", "man", "man", 10, FRANCE, 0, false, "quest"));
			FantomMakeCoolFighter(sld, 10, 10, 10, "blade_10", "pistol1", "bullet", 10);
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.Dialog.currentnode = "Startsailor";
			sld.name = StringFromKey("SharlieTrial_41");
			sld.lastname = StringFromKey("SharlieTrial_42");
			sld.greeting = "start_sailor";
			ChangeCharacterAddressGroup(sld, "My_Campus", "rld", "aloc2");
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
			chrDisableReloadToLocation = true;//закрыть локацию на всякий
			bGameMenuStart = false;
	}
	else if (sQuestName == "Sharlie_onLand")//старт линейки
	{
			SetMusic("classic_fra_music_day");
			LAi_SetPlayerType(pchar);
			TeleportCharacterToPos(pchar, 0.81, 0.60, 78.65);
			LocatorReloadEnterDisable("Fortfrance_town", "reload5_back", true);//закроем верфь
			LocatorReloadEnterDisable("Fortfrance_town", "basement1", true);//закроем подземелье
			LocatorReloadEnterDisable("Fortfrance_town", "reloadPr1", true);//закроем базу
			bDisableFastReload = true;//закрыть переход
			pchar.questTemp.LockHouseEnc = true; // блокируем энкаунтеры для разграбления домов
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			bQuestDisableMapEnter = true;//закрыть карту
			i = FindColony("Fortfrance");
			colonies[i].DontSetShipInPort = true;//не ставить в порту корабли
			AddQuestRecord("Sharlie", "1");
			pchar.questTemp.Sharlie = "Start";
			pchar.questTemp.Sharlie.Lock = "true";
			pchar.NoNavyPenalty = true; // не штрафовать за нехватку навигации
			pchar.questTemp.Sharlie.Citcount = 0;//туповато, но пусть хоть поспрашивает числом
			LocatorReloadEnterDisable("Charles_townhall", "reload3", true);//закроем вход к Пуанси
			// закрываем все острова, кроме Гваделупы и Мартиники
			for (i=0; i<MAX_ISLANDS; i++)
			{				
				if (Islands[i].id != "Guadeloupe" && Islands[i].id != "Martinique")
				{
					Island_SetReloadEnableGlobal(Islands[i].id, false);
				}
			}
			// 170712 закроем склад магазина
			LocatorReloadEnterDisable("FortFrance_store", "reload2", true);
			// ставим гида
			sld = GetCharacter(NPC_GenerateCharacter("Guide", "Guide_1", "man", "man", 10, FRANCE, -1, true, "officer"));
			SetFantomParamFromRank(sld, 10, true);
			RemoveAllCharacterItems(sld, true);
			GiveItem2Character(sld, "blade_12");
			EquipCharacterbyItem(sld, "blade_12");
			sld.name = StringFromKey("SharlieTrial_43");
			sld.lastname = StringFromKey("SharlieTrial_44");
			sld.dialog.FileName = "Quest\Sharlie\Guide.c";
			sld.dialog.currentnode = "guide_0";
			LAi_SetImmortal(sld, true);
			if (MOD_SKILL_ENEMY_RATE > 4) SetCharacterPerk(sld, "Sliding");
			ChangeCharacterAddressGroup(sld, "Fortfrance_town", "quest", "quest1");
			sld.protector = true;
			LAi_SetGuardianType(sld);
			sld.protector.CheckAlways = true; 
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			AddLandQuestMark(sld, "questmarkmain");
			// не ставить корабли на Тортуге
			i = FindColony("Tortuga");
			colonies[i].DontSetShipInPort = true;//не ставить в порту корабли
			pchar.GenQuest.MapClosedNoBattle = true;
			//pchar.questTemp.TimeLock = true; // cle
			AddLandQuestMark(characterFromId("FortFrance_shipyarder"), "questmarkmain");
			AddLandQuestMark(characterFromId("FortFrance_Mayor"), "questmarkmain");
			//DoQuestCheckDelay("NgtF3", 3.0);
			// генерируем персонажа отдельно (знает, где брат)
			sld = GetCharacter(NPC_GenerateCharacter("SharlieKnown", "citiz_"+(rand(6)+11), "man", "man", 10, FRANCE, -1, true, "citizen"));
			FantomMakeCoolFighter(sld, 10, 20, 20, RandPhraseSimple("blade_04","blade_06"), "", "", 10);
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "Benuatalker";
			sld.greeting = "citizen";
			LAi_SetWarriorType(sld);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "FortFrance_town", "patrol", "patrol"+(rand(13)+1));
			LAi_SetLoginTime(sld, 6.0, 21.99);
			AddLandQuestMark(sld, "questmarkmain");
			SetFunctionTimerCondition("Tutorial_Salary", 0, 0, 28, true);
			pchar.systeminfo.tutorial.health = true;
			pchar.systeminfo.tutorial.Perk = true;
			pchar.systeminfo.tutorial.BoardingTactics = true;
			pchar.quest.Tutorial_Mushket.win_condition.l1 = "ItemGroup";
			pchar.quest.Tutorial_Mushket.win_condition.l1.group = MUSKET_ITEM_TYPE;
			pchar.quest.Tutorial_Mushket.function = "Tutorial_Mushket";
			//DoQuestFunctionDelay("Tutorial_CameraControl", 1.0);
			//SetFunctionTimerCondition("TorrentEddy", 8, 0, 0, false);
			// остальное
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_town")], true);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_townhall")], true);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_prison")], true);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_fort")], true);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_ammo")], true);
			LAi_LocationFightDisable(&Locations[FindLocation("LeFransua_town")], true);
			LocatorReloadEnterDisable("FortFrance_townhall", "reload2", true);
			LocatorReloadEnterDisable("FortFrance_townhall", "reload3", true);
			sld = &Locations[FindLocation("FortFrance_prison")];
			sld.locators_radius.item.detector1 = 0;
			DoQuestFunctionDelay("AutoSaveDelay", 1.5);
	}
	else if (sQuestName == "NgtF3")
	{
			NewGameTip(StringFromKey("SharlieTrial_45"));
	}
	else if (sQuestName == "Sharlie_GoFromPrison")//выпускаем из тюрьмы и ставим Мишеля
	{
			EndQuestMovie();
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Sharlie", "2");
			pchar.questTemp.jailCanMove = true; //разрешить пройти мимо стражи
			DoQuestReloadToLocation(pchar.location, "goto", "goto23", "");
			LocatorReloadEnterDisable("Fortfrance_town", "reloadPr1", false);//откроем базу
			sld = characterFromId("Mishelle");
			sld.dialog.currentnode = "Mishelle_prisoner";
			AddLandQuestMark(sld, "questmarkmain");
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "FortFrance_Dungeon", "quest", "quest1");
			pchar.questTemp.Sharlie = "basement";
			pchar.questTemp.Sharlie.Pardon = "true";
			SetFunctionTimerCondition("Sharlie_PardonOver", 0, 0, 2, false);
			if(CheckAttribute(pchar, "questTemp.Sharlie.Citcount"))
				DeleteAttribute(pchar, "questTemp.Sharlie.Citcount");
			SetFunctionExitFromLocationCondition("Sharlie_MaltieAfterJail", pchar.location, false);
			if (CheckAttribute(pchar, "Sharlie.KnifeMonpe")) 
			{
				GiveItem2Character(PChar, "knife_03");
				EquipCharacterbyItem(PChar, "knife_03");
			}
			sld = characterFromId("FortFrance_Mayor");
			LAi_CharacterEnableDialog(sld);
			QuestPointerDelLoc("FortFrance_town", "reload", "reload3_back");
			QuestPointerDelLoc("FortFrance_town", "reload", "reload7_back");
			QuestPointerToLoc("FortFrance_prison", "reload", "reload1");
	}
	else if (sQuestName == "Sharlie_SetBenua") //ноду аббату Бенуа
	{
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "Benua_meeting";
			AddQuestRecord("Sharlie", "3");
			AddLandQuestMark(sld, "questmarkmain");
	}
	else if (sQuestName == "Maltie_GoTown")//
	{
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("FortFrance_town", "reload4_back", true);//таверну закрыть
			LocatorReloadEnterDisable("FortFrance_town", "gate_back", true);//ворота закрыть
			Pchar.quest.Sharlie_Maltie.win_condition.l1 = "location";
			Pchar.quest.Sharlie_Maltie.win_condition.l1.location = "FortFrance_town";
			Pchar.quest.Sharlie_Maltie.win_condition = "Maltie_GoBasement";
			QuestPointerDelLoc("FortFrance_town", "reload", "reload3_back");
			QuestPointerDelLoc("FortFrance_town", "reload", "reload7_back");
			QuestPointerToLoc("FortFrance_church", "reload", "reload1_back");
	}
	else if (sQuestName == "Maltie_GoBasement")//идем по городу
	{
			chrDisableReloadToLocation = true;
			sld = characterFromId("Sh_Maltie");
			LAi_ActorGoToLocation(sld, "reload", "reloadPr1", "FortFrance_Dungeon", "reload", "reload1", "Maltie_OpenBasement", -1);
			Pchar.quest.Sharlie_Maltie1.win_condition.l1 = "location";
			Pchar.quest.Sharlie_Maltie1.win_condition.l1.location = "FortFrance_Dungeon";
			Pchar.quest.Sharlie_Maltie1.win_condition = "Maltie_InBasement";
			QuestPointerDelLoc("FortFrance_church", "reload", "reload1_back");
	}
	else if (sQuestName == "Maltie_OpenBasement")//ставим Мишеля
	{
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Fortfrance_town", "reloadPr1", false);//откроем базу
			sld = characterFromId("Mishelle");
			sld.dialog.currentnode = "Mishelle_prisoner";
			AddLandQuestMark(sld, "questmarkmain");
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "FortFrance_Dungeon", "quest", "quest1");
			pchar.questTemp.Sharlie = "basement";
			LAi_SetPlayerType(pchar);
			QuestPointerToLoc("FortFrance_town", "reload", "reloadPr1");
	}
	else if (sQuestName == "Maltie_InBasement")//В здании Ордена
	{
			chrDisableReloadToLocation = true;//закрыть локацию
			LocatorReloadEnterDisable("FortFrance_town", "reload4_back", false);//таверну открыть
			LocatorReloadEnterDisable("FortFrance_town", "gate_back", false);//ворота открыть
			sld = characterFromId("Sh_Maltie");
			sld.dialog.currentnode = "Sharlie_maltie_3";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 1.0, -1);
			QuestPointerDelLoc("FortFrance_town", "reload", "reloadPr1");
	}
	
	//------------------------------------------ гид - знакомство с игрой ---------------------------------------
	
	else if (sQuestName == "Guide_tavern")
	{
			sld = characterFromId("Guide");
			sld.dialog.currentnode = "guide_tavern";
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			LAi_SetStayType(pchar);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
	}
	else if (sQuestName == "Guide_store")
	{
			sld = characterFromId("Guide");
			sld.dialog.currentnode = "guide_tavern";
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			LAi_SetStayType(pchar);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
	}
	else if (sQuestName == "Guide_prison")
	{
			sld = characterFromId("Guide");
			sld.dialog.currentnode = "guide_prison";
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			LAi_SetStayType(pchar);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
	}
	else if (sQuestName == "Guide_market")
	{
			sld = characterFromId("Guide");
			sld.dialog.currentnode = "guide_market";
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			LAi_SetStayType(pchar);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
	}
	else if (sQuestName == "Guide_townhall")
	{
			sld = characterFromId("Guide");
			sld.dialog.currentnode = "guide_townhall";
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			LAi_SetPlayerType(pchar);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
	}
	else if (sQuestName == "Guide_bank")
	{
			sld = characterFromId("Guide");
			sld.dialog.currentnode = "guide_bank";
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			LAi_SetStayType(pchar);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
	}
	else if (sQuestName == "Guide_brothel")
	{
			sld = characterFromId("Guide");
			sld.dialog.currentnode = "guide_brothel";
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			LAi_SetStayType(pchar);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
	}
	else if (sQuestName == "Guide_next")
	{
			sld = characterFromId("Guide");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "guide_21";
			ChangeCharacterAddressGroup(sld, "Fortfrance_town", "reload", "basement1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	else if (sQuestName == "Guide_shipyard")
	{
			sld = characterFromId("Guide");
			sld.dialog.currentnode = "guide_shipyard";
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			LAi_SetStayType(pchar);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
	}
	else if (sQuestName == "Guide_port")
	{
			sld = characterFromId("Guide");
			sld.dialog.currentnode = "guide_port";
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			LAi_SetStayType(pchar);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
	}
	else if (sQuestName == "Guide_portoffice")
	{
			sld = characterFromId("Guide");
			sld.dialog.currentnode = "guide_portoffice";
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			LAi_SetStayType(pchar);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
	}
	else if (sQuestName == "Guide_gate")
	{
			sld = characterFromId("Guide");
			sld.dialog.currentnode = "guide_gate";
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			LAi_SetStayType(pchar);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
	}
	else if (sQuestName == "Guide_ExitTown")
	{
			chrDisableReloadToLocation = true;//закрыть локацию
			sld = characterFromId("Guide");
			sld.dialog.currentnode = "guide_49";
			ChangeCharacterAddressGroup(sld, "FortFrance_ExitTown", "goto", "goto7");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			LAi_SetStayType(pchar);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
	}
	else if (sQuestName == "Guide_HeroWin") // ГГ выиграл фехт
	{
			LAi_group_Delete("EnemyFight");
			DoQuestCheckDelay("hide_weapon", 1.2);
			LAi_RemoveCheckMinHP(pchar); // вот где собака порылась 251116
			sld = characterFromId("Guide");
			if (sti(sld.quest.guide_win == 0)) sld.dialog.currentnode = "guide_57"; // с первого раза побил
			else sld.dialog.currentnode = "guide_58"; 
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
	}
	else if (sQuestName == "Guide_HeroFail") // ГГ проиграл фехт
	{
			LAi_group_Delete("EnemyFight");
			DoQuestCheckDelay("hide_weapon", 0.5);
			sld = characterFromId("Guide");
			sld.quest.guide_win = sti(sld.quest.guide_win)+1;
			if (sti(sld.quest.guide_win == 1)) sld.dialog.currentnode = "guide_59"; // один раз побили
			else 
			{
				if (sti(sld.quest.guide_win == 2)) sld.dialog.currentnode = "guide_60"; // два раза побили
				else sld.dialog.currentnode = "guide_61"; //три раза побили
			}
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
			LAi_SetImmortal(pchar, false);
	}
	else if (sQuestName == "Guide_HeroKill") // Sinistra ГГ убил Валинье
	{
			LAi_group_Delete("EnemyFight");
			DoQuestCheckDelay("hide_weapon", 1.2);
			Log_info(StringFromKey("SharlieTrial_46"));
			Achievment_Set("ach_CL_107");
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			AddCharacterExpToSkill(pchar, "Sneak", 150);
			AddCharacterExpToSkill(pchar, "FencingL", 150);
			AddCharacterExpToSkill(pchar, "FencingS", 150);
			AddCharacterExpToSkill(pchar, "FencingH", 150);
			AddCharacterExpToSkill(pchar, "Pistol", 150);
			AddCharacterExpToSkill(pchar, "Fortune", 150);
			ChangeCharacterComplexReputation(pchar, "nobility", -10);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
			chrDisableReloadToLocation = false;
			pchar.questTemp.GuideDeath = true;
	}
	// <-- гид

	else if (sQuestName == "Rum_CapGoodbye")
	{
			sld = characterFromId("Rum_Cap");
			sld.dialog.currentnode = "Rum_Cap_3";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 1.0, -1);
	}
	else if (sQuestName == "Rum_RemoveBark")
	{
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("Deck_Near_Ship")], false);
			Island_SetReloadEnableGlobal("Martinique", true);
			i = FindIsland("Martinique");
			Islands[i].EffectRadius = 5000; // new
			Group_DeleteGroup("Rum_CapGroup");
			pchar.Ship.Type = SHIP_NOTUSED;
			DeleteAttribute(pchar, "questTemp.Sharlie.Rum");
			AddQuestRecord("SharlieB", "6");
			CloseQuestHeader("SharlieB");
			i = FindLocation("Fortfrance_town");
			setCharacterShipLocation(pchar, GetCityFrom_Sea(locations[i].fastreload));
			setWDMPointXZ(GetCityFrom_Sea(locations[i].fastreload));
	}
	else if (sQuestName == "GigoloGirl_Sex")	// Sinistra поцелуй с Люсиль
	{
			DialogExit();
				
			StartQuestMovie(true, false, true);
			//if(CheckAttribute (pchar, "IsMushketer")) SetMainCharacterToMushketer("", false);
			TeleportCharacterToPosAy(pchar, 1.50, 0.00, -2.49, 0.00);
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "kiss", "1", 7.5);
			sld = characterFromId("GigoloGirl");
			TeleportCharacterToPosAy(sld, 1.50, 0.00, -1.89, 3.00);
			sld.model.animation = "woman";
			Characters_RefreshModel(sld);
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "kiss", "1", 7.5);
			locCameraFromToPos(2.37, 1.48, -1.02, true, -0.29, -0.14, -3.85);
			DoQuestCheckDelay("GigoloGirl_Sex1", 7.5);
	}
	else if (sQuestName == "GigoloGirl_Sex1")
	{
			SetLaunchFrameFormParam("", "Reload_To_Location", 0, 15);
			SetLaunchFrameFormPic("loading\inside\censored1.tga");
			SetLaunchFrameReloadLocationParam("FortFrance_Brothel_room", "goto", "goto1", "GigoloGirl_Sex2");
			PlayStereoSound("sex\sex"+(rand(9)+1)+".wav");
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 8, 0); //крутим время
			RecalculateJumpTable();
			if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	
			{
				AddCharacterHealth(pchar, 8);
				AddCharacterMaxHealth(pchar, 1.0);
			}
			else AddCharacterHealth(pchar, 4); 
			LAi_SetCurHPMax(pchar);
			EndQuestMovie();
			sld = characterFromId("GigoloGirl");
			sld.lifeday = 0;
			pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1; //счетчик
			ChangeCharacterAddressGroup(sld, "none", "", "");
	}
	else if (sQuestName == "GigoloGirl_Sex2") 
	{
			chrDisableReloadToLocation = false;
			locCameraTarget(PChar);
			locCameraFollow();
			LAi_SetPlayerType(pchar);
			ChangeCharacterComplexReputation(pchar, "nobility", -10);
			AddCharacterExpToSkill(pchar, "Sneak", 120);
			DeleteAttribute(pchar, "questTemp.Sharlie.Gigolo");
			AddQuestRecord("SharlieC", "4");
			CloseQuestHeader("SharlieC");
	}
	else if (sQuestName == "GigoloGirl_SetCitizen")
	{
			sld = characterFromId("GigoloGirl");
			LAi_SetCitizenType(sld);
	}
	else if (sQuestName == "GigoloGirl_Remove")
	{
			sld = characterFromId("GigoloGirl");
			sld.lifeday = 0;
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 80);//везение
			DeleteAttribute(pchar, "questTemp.Sharlie.Gigolo");
			AddQuestRecord("SharlieC", "3");
			CloseQuestHeader("SharlieC");
	}
	else if (sQuestName == "SharlieA_TeleportLF")
	{
			AddQuestRecord("SharlieA", "3");
			pchar.quest.storehelper.win_condition.l1 = "Timer";
			pchar.quest.storehelper.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.storehelper.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 5);
			pchar.quest.storehelper.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 5);
			pchar.quest.storehelper.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 5);
			pchar.quest.storehelper.function = "StorehelperOver";
			pchar.questTemp.Sharlie.Storehelper = "hire";
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			AddLandQuestMark(characterFromId("LeFransua_tavernkeeper"), "questmarkmain");
	}
	else if (sQuestName == "Captive_PiratesDead")
	{
			LAi_group_Delete("EnemyFight");
			pchar.GenQuest.Notsearchbody = true; // 170712
			sld = characterFromId("CaptiveSpain");
			GiveItem2Character(sld, "blade_03");
			EquipCharacterbyItem(sld, "blade_03");
			LAi_CharacterEnableDialog(sld);
			sld.Dialog.Filename = "Quest\Sharlie\StartMiniQuests.c";
			sld.Dialog.currentnode = "CaptiveSpain";
			sld.greeting = "spa_engineer";
			LAi_SetActorType(pchar);
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			LAi_SetCurHPMax(PChar);
	}
	else if (sQuestName == "CaptiveSpain_capture")
	{
			DoQuestCheckDelay("hide_weapon", 1.2);
			LAi_group_Delete("EnemyFight");
			sld = characterFromId("CaptiveSpain");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	else if (sQuestName == "FolkeStay")
	{
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Folke");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0); // 170712
	}
	else if (sQuestName == "Seabattle_pirate_open")
	{
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			chrDisableReloadToLocation = false;//открыть локацию
	}
	else if (sQuestName == "TichingituFree")
	{
			sld = characterFromId("Tichingitu");
			sld.dialog.currentnode = "Tichingitu_9";
			ChangeCharacterAddressGroup(sld, "BasTer_exittown", "rld", "aloc14"); // 170712
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			RemoveAllCharacterItems(sld, true);
			GiveItem2Character(sld, "topor_05");
			EquipCharacterbyItem(sld, "topor_05"); // 151012
	}
	else if (sQuestName == "ZsI_TPvGorod")
	{
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			pchar.questTemp.ZsI_PokupaemPistolety = true;
			SetTimerCondition("ZsI_Timer", 0, 0, 1, false);
			LocatorReloadEnterDisable("BasTer_town", "gate_back", true);
		
			sld = CharacterFromID("ListKakao");
			LAi_SetStayType(sld);
			LAi_CharacterDisableDialog(sld);
				
			sld = characterFromId("Tichingitu");
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
			sld.Dialog.CurrentNode = "Tichingitu_officer";
			
			sld = GetCharacter(NPC_GenerateCharacter("ZsI_Kostyl", "shipowner_5", "man", "man", 1, FRANCE, -1, false, "quest"));
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "BasTer_town", "merchant", "mrcActive3");
			DoQuestCheckDelay("ZsI_LotokMarka", 0.5);
	}
	else if (sQuestName == "ZsI_LotokMarka")
	{
			sld = CharacterFromID("ZsI_Kostyl");
			LAi_SetCitizenType(sld);
			LAi_CharacterDisableDialog(sld);
			sld.lifeday = 0;
			int characterIndex = LAi_FindNearestVisCharacter(sld, 25);
			ref characterRef;

			if(characterIndex != -1)
			{
				characterRef = &Characters[characterIndex];

				if(!LAi_IsImmortal(characterRef))
				{
					AddLandQuestMark(characterRef, "questmarkmain");
					pchar.BasTer_Orujeinek.id = characterRef.id;
				}
			}
			LaunchTutorial("Fighter", 1);
	}
	else if (sQuestName == "ZsI_Draka")
	{
			Log_info(StringFromKey("SharlieTrial_47"));
			sld = characterFromId("Tichingitu");
			RemovePassenger(pchar, sld);
			LAi_SetWarriorType(sld);
			DeleteAttribute(sld, "OfficerImmortal");
			if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
			if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
			sTemp = "RestoreHealth_" + sld.index;
			if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "ZsI_Draka_2");
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
	}
	else if (sQuestName == "ZsI_Draka_2")
	{
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
	}
	else if (sQuestName == "ZsI_Mir")
	{
			PChar.quest.ZsI_Draka.over = "yes";
	}
	else if (sQuestName == "ZsI_Timer")
	{
			sld = CharacterFromID(pchar.BasTer_Orujeinek.id);
			DelLandQuestMark(sld);
			sld = CharacterFromID("ListKakao");
			sld.lifeday = 0;
			LAi_CharacterDisableDialog(sld);
			DeleteAttribute(pchar, "questTemp.ZsI_PokupaemPistolety");
			PChar.quest.ZsI_Patrul.over = "yes";
			PChar.quest.ZsI_NePrines.over = "yes";
			LocatorReloadEnterDisable("BasTer_town", "gate_back", false);
	}
	else if (sQuestName == "ZsI_Patrul")
	{
			LAi_LocationFightDisable(&Locations[FindLocation("BasTer_ExitTown")], true);
			for (i=1; i<=2; i++)
			{
				sTemp = "sold_fra_"+(rand(7)+1);					
				sld = GetCharacter(NPC_GenerateCharacter("ZsI_Patrul_"+i, sTemp, "man", "man", sti(pchar.rank), FRANCE, -1, true, "soldier"));
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, pchar.location, "item",  "item7");
			}
			sld = GetCharacter(NPC_GenerateCharacter("ZsI_Patrul_off", "off_fra_1", "man", "man", sti(pchar.rank), FRANCE, -1, false, "soldier"));
			GiveItem2Character(sld, "blade_08");
			EquipCharacterByItem(sld, "blade_08");
			GiveItem2Character(sld, "pistol1");
			EquipCharacterByItem(sld, "pistol1");
			GiveItem2Character(sld, "cirass5");
			EquipCharacterByItem(sld, "cirass5");
			AddItems(sld, "bullet", 6);
			AddItems(sld, "GunPowder", 6);
			AddItems(sld, "potion1", 2);
			GiveItem2Character(sld, "purse2");
			GiveItem2Character(sld, "indian_2");
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, pchar.location, "item",  "item3");
			sld = CharacterFromID("ListKakao");
			LAi_SetActorType(sld);
			DoQuestCheckDelay("ZsI_Patrul_2", 0.2);
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
			PChar.quest.ZsI_Timer.over = "yes";
			pchar.questTemp.CameraDialogMode = true;
	}
	else if (sQuestName == "ZsI_Patrul_2")
	{
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("ZsI_Patrul_"+i);
				LAi_SetActorType(sld);
				LAi_ActorTurnToCharacter(sld, CharacterFromID("ListKakao"));
			}
			sld = CharacterFromID("ZsI_Patrul_off");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("ListKakao"));
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "ZsI_officer";
			sld.talker = 5;
	}
	else if (sQuestName == "ZsI_officer_Draka_3")
	{
			sld = CharacterFromID("ListKakao");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			sld.dialog.filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "ZsI_Final";
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
	}
	else if (sQuestName == "ZsI_officerKIll_1")
	{
			StartQuestMovie(true, false, true);
			locCameraFromToPos(-32.61, 3.09, -11.19, true, -4.00, -5.40, -4.00);
	}
	else if (sQuestName == "ZsI_officerKIll_2")
	{
			sld = CharacterFromID("ZsI_Patrul_off");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Shot", "1", 1.8);
			DoQuestCheckDelay("ZsI_officerKIll_3", 0.9);
	}
	else if (sQuestName == "ZsI_officerKIll_3")
	{
			sld = CharacterFromID("ListKakao");
			RemoveItems(sld, "jewelry53", 200);
			LAi_KillCharacter(sld);
			DoQuestCheckDelay("ZsI_officerKIll_4", 2.2);
	}
	else if (sQuestName == "ZsI_officerKIll_4")
	{
			sld = CharacterFromID("ZsI_Patrul_off");
			LAi_SetActorType(sld);
			sld.lifeday = 0;
			LAi_SetImmortal(sld, true);
			LAi_ActorGoToLocation(sld, "reload", "reload4", "none", "", "", "", -1);
				
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("ZsI_Patrul_"+i);
				LAi_SetActorType(sld);
				sld.lifeday = 0;
				LAi_SetImmortal(sld, true);
				LAi_ActorGoToLocation(sld, "reload", "reload4", "none", "", "", "", -1);
			}
			DoQuestCheckDelay("ZsI_officerKIll_5", 1.4);
	}
	else if (sQuestName == "ZsI_officerKIll_5")
	{
			EndQuestMovie();
			LAi_SetPlayerType(pchar);
			locCameraTarget(PChar);
			locCameraFollow();
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("BasTer_ExitTown")], false);
			ChangeCharacterNationReputation(pchar, FRANCE, 2);
	}
	// <== Квест "Знакомство с индейцами"

	// Sinistra - Квест "Деньги на деревьях" ==>
	else if (sQuestName == "MOT_BarbieSpawn")
	{
			sld = GetCharacter(NPC_GenerateCharacter("SharlieBarbie", "trader_7", "man", "man", 5, FRANCE, -1, true, "quest"));
			sld.name = StringFromKey("SharlieTrial_48");
			sld.lastname = StringFromKey("SharlieTrial_49");
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			sld.dialog.filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "MOT_Barbie";
			ChangeCharacterAddressGroup(sld, "BasTer_town", "goto", "goto19");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
	}
	else if (sQuestName == "MOT_Zahvatili")
	{
			PChar.quest.MOT_ZadanieProvaleno.over = "yes";
			PChar.quest.MOT_Dostavili.over = "yes";
			AddQuestRecord("MoneyOnTrees", "2");
			CloseQuestHeader("MoneyOnTrees");
			pchar.questTemp.MOT_SharlyBad = true;
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterNationReputation(pchar, FRANCE, -2);
			pchar.Achievment.Barbie = true;
	}
	else if (sQuestName == "MOT_ZadanieProvaleno")
	{
			PChar.quest.MOT_Zahvatili.over = "yes";
			PChar.quest.MOT_Dostavili.over = "yes";
			AddQuestRecord("MoneyOnTrees", "3");
			CloseQuestHeader("MoneyOnTrees");
			sld = CharacterFromID("SharlieBarbie");
			RemoveCharacterCompanion(pchar, sld);
			sld.lifeday = 0;
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
	}
	else if (sQuestName == "MOT_Dostavili")
	{
			PChar.quest.MOT_ZadanieProvaleno.over = "yes";
			PChar.quest.MOT_Zahvatili.over = "yes";
			sld = CharacterFromID("SharlieBarbie");
			PlaceCharacter(sld, "goto", PChar.location);
			sld.dialog.filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "MOT_Barbie_101";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
	}
	else if (sQuestName == "MOT_UbratMarku")
	{
			DelLandQuestMark(characterFromId("FortFrance_Smuggler"));
	}
	// <== Квест "Деньги на деревьях"

	// Sinistra - Миниквест "Делюк" ==>
	else if (sQuestName == "Del_Alonso")
	{
			sld = GetCharacter(NPC_GenerateCharacter("Alonso", "Alonso", "man", "man", 25, pchar.nation, -1, true, "soldier"));
			sld.name 	= StringFromKey("SharlieTrial_29");
			sld.lastname = StringFromKey("SharlieTrial_30");
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "Del_Alonso";
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(sld, "FortFrance_town", "reload", "reload4_back");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
	}
	else if (sQuestName == "Del_Turma")
	{
			locCameraFromToPos(-13.10, 3.09, 6.43, true, -10.00, -3.20, -10.00);
			DoQuestCheckDelay("Del_Turma_2", 3.0);
			DoQuestCheckDelay("Del_Turma_3", 3.5);
	}
	else if (sQuestName == "Del_Turma_2")
	{
			LAi_Fade("", "");
	}
	else if (sQuestName == "Del_Turma_3")
	{
			sld = CharacterFromID("Folke");
			ChangeCharacterAddressGroup(sld, "Fortfrance_prison", "item", "detector1");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "reload", "reload1", "FolkeStay", -1);
			
			sld = CharacterFromID("Del_Ohranik");
			ChangeCharacterAddressGroup(sld, "Fortfrance_prison", "reload", "reload3");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, CharacterFromID("Folke"), "", -1);
			
			locCameraFromToPos(12.83, 2.28, 3.64, true, 0.00, -3.20, -25.00);
			DoQuestCheckDelay("Del_Turma_4", 3.5);
			DoQuestCheckDelay("Del_Turma_5", 4.0);
	}
	else if (sQuestName == "Del_Turma_4")
	{
			LAi_Fade("", "");
	}
	else if (sQuestName == "Del_Turma_5")
	{
			locCameraFromToPos(17.33, 2.89, -12.15, true, 0.00, -3.20, -10.00);
			DoQuestCheckDelay("FolkeStay", 3.3);
	}
	// <== Миниквест "Делюк"

	// Sinistra, квест "Травля крысы" ==>	
	else if (sQuestName == "TK_Timer")
	{
			pchar.quest.TK_Timer.win_condition.l1 = "Rank";
			pchar.quest.TK_Timer.win_condition.l1.value = 10;
			pchar.quest.TK_Timer.win_condition.l1.operation = ">=";
			PChar.quest.TK_Timer.win_condition = "TK_Timer_2";
	}
	else if (sQuestName == "TK_Timer_2")
	{
			DeleteAttribute(pchar, "questTemp.TK_TravlyaKrys");
			DelLandQuestMark(characterFromId("FortFrance_Mayor"));
	}
	else if (sQuestName == "TK_Potopil")
	{
			AddQuestRecord("TravlyaKrys", "2");
			pchar.questTemp.TK_Potopil = true;
	}
	else if (sQuestName == "TK_KapitanSidit_1")
	{
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Ground_SitDown", "1", 3.5);
			DoQuestCheckDelay("TK_KapitanSidit_2", 3.5);
	}
	else if (sQuestName == "TK_KapitanSidit_2")
	{
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			LAi_SetSitPoorAnimation(sld);
			sld.lifeday = 0;
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
			pchar.questTemp.TK_Plen = true;
			AddQuestRecord("TravlyaKrys", "3");
	}
	else if (sQuestName == "TK_GenrihSpawn")
	{
			Group_FindOrCreateGroup("TK_GroupGenrih");
			sld = GetCharacter(NPC_GenerateCharacter("TK_Genrih", "trader_6", "man", "man", 5, ENGLAND, -1, true, "quest"));
			FantomMakeSmallSailor(sld, SHIP_BARQUE, StringFromKey("SharlieTrial_50"), CANNON_TYPE_CANNON_LBS3, 20, 25, 25, 20, 30);
			sld.Ship.Mode = "trade";
			realships[sti(sld.ship.type)].Capacity = 2200;
			sld.Ship.Crew.Quantity = 40;
			SetCharacterGoods(sld, GOOD_CHOCOLATE, 100 + rand(100));
			SetCharacterGoods(sld, GOOD_SUGAR, 100 + rand(100));
			SetCharacterGoods(sld, GOOD_CINNAMON, 100 + rand(100));
			SetCharacterGoods(sld, GOOD_COPRA, 100 + rand(100));
			SetCharacterGoods(sld, GOOD_PAPRIKA, 100 + rand(100));
			sld.DontRansackCaptain = true;
			sld.AnalizeShips = true;
			sld.CanDropSails = false;

			SetCaptanModelByEncType(sld, "trade");
			sld.CompanionEnemyEnable = true;
			sld.mapEnc.type = "war";
			sld.mapEnc.worldMapShip = "quest_ship";
			sld.mapEnc.Name = StringFromKey("SharlieTrial_51");
			Group_AddCharacter("TK_GroupGenrih", "TK_Genrih");
			Group_SetGroupCommander("TK_GroupGenrih", "TK_Genrih");
			Group_SetTaskAttackInMap("TK_GroupGenrih", PLAYER_GROUP);
			Group_LockTask("TK_GroupGenrih");
			Map_CreateTrader("LeFransua", "Villemstad", "TK_Genrih", 8);
			
			SetTimerCondition("TK_Genrih_NeUspel", 0, 0, 9, false);	
			
			PChar.quest.TK_Genrih_Zahvat.win_condition.l1 = "Character_Capture";
			PChar.quest.TK_Genrih_Zahvat.win_condition.l1.character = "TK_Genrih";
			PChar.quest.TK_Genrih_Zahvat.win_condition = "TK_Genrih_Zahvat";

			PChar.quest.TK_Genrih_Potopil.win_condition.l1 = "Character_sink";
			PChar.quest.TK_Genrih_Potopil.win_condition.l1.character = "TK_Genrih";
			PChar.quest.TK_Genrih_Potopil.win_condition = "TK_Genrih_Potopil";
	}
	else if (sQuestName == "TK_Genrih_NeUspel")
	{
			AddQuestRecord("TravlyaKrys", "5");
			CloseQuestHeader("TravlyaKrys");
			DeleteQuestCondition("TK_Genrih_Zahvat");
			DeleteQuestCondition("TK_Genrih_Potopil");
			pchar.questTemp.TK_Potopil = true;
	}
	else if (sQuestName == "TK_Genrih_Potopil")
	{
			AddQuestRecord("TravlyaKrys", "6");
			CloseQuestHeader("TravlyaKrys");
			DeleteQuestCondition("TK_Genrih_NeUspel");
			DeleteQuestCondition("TK_Genrih_Zahvat");
			pchar.questTemp.TK_Potopil = true;
	}
	else if (sQuestName == "TK_Genrih_Zahvat")
	{
			AddQuestRecord("TravlyaKrys", "7");
			CloseQuestHeader("TravlyaKrys");
			DeleteQuestCondition("TK_Genrih_NeUspel");
			DeleteQuestCondition("TK_Genrih_Potopil");
			pchar.questTemp.TK_Potopil = true;
			pchar.Achievment.Genrih = true;
	}
	// <== Квест "Травля крысы"

	// Sinistra - квест "Встреча с Диего" ==>
	else if (sQuestName == "VsD_DiegoNachalo")
	{
			sld = CharacterFromID("Diego");
			LAi_SetImmortal(sld, true);
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "houseF1");
			LAi_ActorRunToLocation(sld, "reload", "reload4_back", "none", "", "", "VsD_DiegoNachalo_2", -1);
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
			DelMapQuestMarkCity("PortPax");
			PChar.quest.KN_AmmoOffMarka.win_condition.l1 = "location";
			PChar.quest.KN_AmmoOffMarka.win_condition.l1.location = "PortPax_ammo";
			PChar.quest.KN_AmmoOffMarka.function = "PortPaxAmmoOff_AddQuestMark";
			QuestPointerToLoc("portpax_town", "reload", "gate_back");
			QuestPointerToLoc("portpax_exittown", "reload", "reload2_back");
			QuestPointerToLoc("portpax_fort", "reload", "reload2");
	}
	else if (sQuestName == "VsD_DiegoNachalo_2")
	{
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			FreeSitLocator("PortPax_tavern", "sit_base2");
			FreeSitLocator("PortPax_tavern", "sit_front2");
			
			sld = CharacterFromID("Diego");
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "VsD_DiegoAndErnat";
			ChangeCharacterAddressGroup(sld, "PortPax_tavern", "sit", "sit_front2");
			LAi_SetSitType(sld);
			
			sld = GetCharacter(NPC_GenerateCharacter("GiumDyubua", "off_fra_2", "man", "man", 5, FRANCE, -1, true, "soldier"));
			sld.name = StringFromKey("SharlieTrial_53");
			sld.lastname = StringFromKey("SharlieTrial_54");
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "PortPax_tavern", "sit", "sit_base2");
			LAi_SetSitType(sld);
			LAi_CharacterDisableDialog(sld);
			
			PChar.quest.VsD_DiegoInTaverna.win_condition.l1 = "location";
			PChar.quest.VsD_DiegoInTaverna.win_condition.l1.location = "PortPax_tavern";
			PChar.quest.VsD_DiegoInTaverna.function = "VsD_DiegoInTaverna";
	}
	else if (sQuestName == "VsD_GiumDyubua")
	{
			sld = CharacterFromID("GiumDyubua");
			LAi_CharacterEnableDialog(sld);
			ChangeCharacterAddressGroup(sld, "PortPax_Fort", "rld", "loc0");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto61", "", -1);
			DoQuestCheckDelay("VsD_GiumDyubua_2", 0.5);
			LAi_LocationFightDisable(&Locations[FindLocation("PortPax_Fort")], true);
	}
	else if (sQuestName == "VsD_GiumDyubua_2")
	{
			sld = CharacterFromID("GiumDyubua");
			LAi_CharacterEnableDialog(sld);
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "VsD_GiumDyubua";
			sld.talker = 7;
			AddLandQuestMark(sld, "questmarkmain");
	}
	else if (sQuestName == "VsD_VerfOtkryt")
	{
			LocatorReloadEnterDisable("PortPax_Town", "reload5_back", false);
	}
	else if (sQuestName == "VsD_TrupPredatelya")
	{
			sld = CharacterFromID("GiumDyubua");
			RemoveAllCharacterItems(sld, true);
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			AddMoneyToCharacter(sld, 30);
			ChangeCharacterAddressGroup(sld, "PortPax_ExitTown", "goto", "goto14");
			DoQuestCheckDelay("VsD_TrupPredatelya_2", 0.1);
			PChar.quest.VsD_TrupPredatelya_3.over = "yes";
	}
	else if (sQuestName == "VsD_TrupPredatelya_2")
	{
			sld = CharacterFromID("GiumDyubua");
			LAi_KillCharacter(sld);
	}
	else if (sQuestName == "VsD_TrupPredatelya_3")
	{
			PChar.quest.VsD_TrupPredatelya.over = "yes";
	}
	// <== Квест "Встреча с Диего"

	// New store helper
	else if (sQuestName == "Newstorehelper_ready")
	{
			for (i=1; i<=3; i++)
			{
				sld = characterFromId("Newstorehelper_"+i);
				LAi_SetStayType(sld);
				CharacterTurnByChr(sld, pchar);
			}
	}
	else if (sQuestName == "RescueDaughter_ProsperGateOutReload")
	{
			chrDisableReloadToLocation = true;
			sld = characterFromId("RD_Prosper");
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "Martinique_Jungle_01", "officers", "reload2_2", "OpenTheDoors", 20.0);
			
			PChar.quest.RescueDaughter_ProsperExitTownOutReload.win_condition.l1 = "location";
			PChar.quest.RescueDaughter_ProsperExitTownOutReload.win_condition.l1.location = "Martinique_Jungle_01";
			PChar.quest.RescueDaughter_ProsperExitTownOutReload.win_condition = "RescueDaughter_ProsperExitTownOutReload";
	}
	else if (sQuestName == "RescueDaughter_ProsperExitTownOutReload")
	{
			chrDisableReloadToLocation = true;
			sld = characterFromId("RD_Prosper");
			LAi_ActorRunToLocation(sld, "reload", "reload3_back", "Martinique_Jungle_04", "goto", "goto8", "OpenTheDoors", 20.0);
			
			PChar.quest.RescueDaughter_ProsperJung1Reload.win_condition.l1 = "location";
			PChar.quest.RescueDaughter_ProsperJung1Reload.win_condition.l1.location = "Martinique_Jungle_04";
			PChar.quest.RescueDaughter_ProsperJung1Reload.win_condition = "RescueDaughter_ProsperJung1Reload";
	}
	else if (sQuestName == "RescueDaughter_ProsperJung1Reload")
	{
			sld = characterFromId("RD_Prosper");
			LAi_ActorRunToLocator(sld, "reload", "reload2_back", "RescueDaughter_ProsperJung4Player", -1);
	}
	else if (sQuestName == "RescueDaughter_ProsperJung4Player")
	{
			sld = characterFromId("RD_Prosper");
			LAi_ActorTurnToCharacter(sld, pchar);
	}
	else if (sQuestName == "RescueDaughter_KillIndiansLand")
	{
			LAi_group_Delete("EnemyFight");
			sld = characterFromId("RD_Prosper");
			if (LAi_GetCharacterHP(sld) > 0)
			{
				LAi_SetActorType(sld);
				sld.MusketerDistance = 20;
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else
			{
				AddQuestRecord("Sharlie", "F6");
				LocatorReloadEnterDisable("Martinique_CaveEntrance", "reload1_back", false);
				pchar.quest.Sharlie_RescueDaughter2.win_condition.l1 = "location";
				pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.location = "Martinique_Grot";
				pchar.quest.Sharlie_RescueDaughter2.function = "RescueDaughter_CreateIndiansGrot";
				pchar.questTemp.Sharlie.RescueDaughter.KillProsper = "true";
			}
	}
	else if (sQuestName == "RescueDaughter_IndFight")
	{
			if (!CheckAttribute(pchar, "questTemp.Sharlie.RescueDaughter.KillProsper"))
			{
				sld = characterFromId("RD_Prosper");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			LAi_SetFightMode(pchar, true);
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("RD_IndCave_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "RescueDaughter_KillIndiansGrot");
	}
	else if (sQuestName == "RescueDaughter_KillIndiansGrot")
	{
			LAi_group_Delete("EnemyFight");
			sld = characterFromId("RD_Selina");
			LAi_SetActorType(sld);
			if (!CheckAttribute(pchar, "questTemp.Sharlie.RescueDaughter.KillProsper"))
			{
				chr = characterFromId("RD_Prosper");
				if (LAi_GetCharacterHP(chr) > 0)
				{
					sld.dialog.currentnode = "Selina";
					chr.MusketerDistance = 20;
					LAi_SetActorType(chr);
					LAi_ActorFollow(sld, chr, "", -1);
					LAi_ActorDialog(chr, pchar, "", -1, 0);
				}
				else
				{
					sld.dialog.currentnode = "Selina_3";
					LAi_ActorDialog(sld, pchar, "", -1, 0);
					pchar.questTemp.Sharlie.RescueDaughter.KillProsper = "true";
				}
			}
			else
			{
				sld.dialog.currentnode = "Selina_3";
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			DoQuestCheckDelay("NgtBody", 3.0);
			if(CheckAttribute(pchar,"systeminfo.tutorial.Amulet"))
			{
				pchar.quest.Tutorial_Amulet.win_condition.l1 = "item";
				pchar.quest.Tutorial_Amulet.win_condition.l1.item = "indian_3";
				pchar.quest.Tutorial_Amulet.function = "Tutorial_Amulet";
			}
	}
	else if (sQuestName == "NgtBody")
	{
			NewGameTip(StringFromKey("SharlieTrial_52"));
	}
	else if (sQuestName == "SharlieJungleNative_kill")
	{
			LAi_group_Delete("EnemyFight");
			chrDisableReloadToLocation = false;
	}
	else if (sQuestName == "SharlieJungleBandos_kill")
	{
			LAi_group_Delete("EnemyFight");
			chrDisableReloadToLocation = false;
			sld = characterFromId(pchar.questTemp.Sharlie.Storehelper.id);
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
	}
	// выпивка с Фадеем
	else if (sQuestName == "Sharlie_DrinkWithFadey")
	{
			LAi_SetActorType(pchar);
			LAi_ActorSetSitMode(pchar);
			InterfaceStates.Buttons.Save.enable = false;
			bDisableCharacterMenu = true;//лоченые интерфейсы
			DoQuestCheckDelay("Sharlie_DrinkWithFadey_music", 0.8);
			DoQuestCheckDelay("Sharlie_DrinkWithFadey_1", 33.0);
	}
	else if (sQuestName == "Sharlie_DrinkWithFadey_music")
	{
			SetMusic("hol_music_tavern");
	}
	else if (sQuestName == "Sharlie_DrinkWithFadey_1")
	{
			LAi_SetPlayerType(pchar);
			InterfaceStates.Buttons.Save.enable = true;
			bDisableCharacterMenu = false;//лоченые интерфейсы
			pchar.GenQuest.CamShuttle = 3;
			WaitDate("",0,0,0,5,5);
			DoQuestReloadToLocation("BasTer_houseSp1", "goto", "goto1", "Sharlie_DrinkWithFadey_2");
	}
	else if (sQuestName == "Sharlie_DrinkWithFadey_2")
	{
			sld = characterFromId("Fadey");
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
	}
	// Jason------------------------------------- Карибские нравы ----------------------------------------
	else if (sQuestName == "Trial_AfterTavernFight")
	{
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			AddQuestRecord("Trial", "13");
	}
	else if (sQuestName == "Trial_ReturnPoormanNorm")
	{
			chrDisableReloadToLocation = false;//открыть локацию
			sld = characterFromId("PortoBello_Poorman");
			sld.dialog.currentnode = "First time";
			LAi_SetLoginTime(sld, 9.0, 21.99);
			ChangeCharacterAddressGroup(sld, "Portobello_town", "goto", "goto15");
			LAi_SetPoorType(sld);
			LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
			DelLandQuestMark(sld);
	}
	// belamour legendary edition -->
	else if (sQuestName == "RIP_Bomzh") // минус бомж
	{
			SendMessage(pchar, "lsl", MSG_CHARACTER_EX_MSG, "GunBelt", true);
			sld = characterFromId("PortoBello_Poorman");
			LAi_KillCharacter(sld);
			pchar.questTemp.Trial = "spy_win";
			AddQuestRecord("Trial", "17");
			sld = characterFromId("Florian");
			sld.DeckDialogNode = "florian_12";
			AddLandQuestMark(sld, "questmarkmain");
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			AddCharacterExpToSkill(pchar, "Sneak", 100);
			AddCharacterExpToSkill(pchar, "FencingL", 30);
			AddCharacterExpToSkill(pchar, "FencingS", 30);
			AddCharacterExpToSkill(pchar, "FencingH", 30);
			AddCharacterExpToSkill(pchar, "Pistol", 30);
			LAi_SetPlayerType(pchar);
			// новый нищий
			sld = GetCharacter(NPC_GenerateCharacter("PortoBello_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, SPAIN, -1, false, "slave"));
			sld.city = "PortoBello";
			sld.location	= "PortoBello_town";
			sld.location.group = "goto";
			sld.location.locator = "goto15";
			sld.forStay.locator = "goto15"; //где генеримся в случае стояния
			sld.forSit.locator0 = "goto3";
			sld.forSit.locator1 = "goto25"; //три локатора, где генеримся в случае сидения
			sld.forSit.locator2 = "goto12";
			LAi_SetLoginTime(sld, 9.0, 21.99);
			sld.Dialog.Filename = "Common_poorman.c";
			LAi_SetPoorType(sld);
			LAi_SetHP(sld, 50.0, 50.0);
			sld.greeting = "poorman_male";
			LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
			Achievment_SetStat(95, 1);
	}
	// <-- legendary edition
	else
	{
		condition = false;
	}
	
	return condition;
}
