void IslaMona_SetCannonBattle() {
	ref loc = &locations[FindLocation("IslaMona_town")];
	
	loc.models.always.mortair = "mortair";
	loc.models.always.mortair.locator.group = "quest";
	loc.models.always.mortair.locator.name = "mortair_battle";
	
	loc.models.day.charactersPatch = loc.models.day.charactersPatch + "Q";
	loc.models.night.charactersPatch = loc.models.night.charactersPatch + "Q";
}

void IslaMona_SetCannonPeace() {
	ref loc = &locations[FindLocation("IslaMona_town")];
	
	loc.models.always.mortair = "mortair";
	loc.models.always.mortair.locator.group = "quest";
	loc.models.always.mortair.locator.name = "mortair";
	
	loc.models.day.charactersPatch = strleft(loc.models.day.charactersPatch, strlen(loc.models.day.charactersPatch) - 1);
	loc.models.night.charactersPatch = strleft(loc.models.night.charactersPatch, strlen(loc.models.night.charactersPatch) - 1);
}

void IslaMona_AdvanceStageToTwo() {
	ref loc = &locations[FindLocation("IslaMona_town")];
	
	loc.filespath.models = "Locations\Town_IslaMona\City\Second";
	loc.models.always.building = "building";
	loc.models.always.fence = "fence";
	loc.models.always.mortair = "mortair";
	loc.models.always.mortair.locator.group = "quest";
	loc.models.always.mortair.locator.name = "mortair";
	loc.models.always.locators = "locators";
	//loc.fastreload = "IslaMona";
	//loc.type = "Town";
	//loc.id.label = "Street"; 
	loc.houseEnc = true;
	// Day
	loc.models.day.charactersPatch = "patch";
	// Night
	loc.models.night.charactersPatch = "patch";		

	DeleteAttribute(loc, "models.always.kotelok");
	DeleteAttribute(loc, "models.always.locnap");

	loc.reload.l3.go = "CommonDoubleflourHouse_2";
	loc.reload.l4.go = "CommonStoneHouse";
	loc.reload.l5.go = "CommonDoubleflourHouse_1";
	
	loc.reload.l6.name = "reload6";
	loc.reload.l6.go = "CommonRoom_MH3";
	loc.reload.l6.emerge = "reload1";
	loc.reload.l6.label = "House";
	
	loc.reload.l7.name = "reload7";
	loc.reload.l7.go = "CommonFlamHouse";
	loc.reload.l7.emerge = "reload1";
	loc.reload.l7.label = "House";
	
	loc.reload.l8.name = "reload8";
	loc.reload.l8.go = "CommonStoneHouse";
	loc.reload.l8.emerge = "reload1";
	loc.reload.l8.label = "House";
}

void IslaMona_AdvanceStageToThree() {
	ref loc = &locations[FindLocation("IslaMona_town")];
	
	loc.filespath.models = "Locations\Town_IslaMona\City\Third";
	loc.models.always.building = "building";
	loc.models.always.fence = "fence";
	loc.models.always.mortair = "mortair";
	loc.models.always.mortair.locator.group = "quest";
	loc.models.always.mortair.locator.name = "mortair";
	loc.models.always.tavern = "tavern";
	loc.models.always.easterEGG = "easterEGG";
	loc.models.always.locators = "locators";
	// Day
	loc.models.day.charactersPatch = "patch";
	// Night
	loc.models.night.charactersPatch = "patch";	
	
	DeleteAttribute(loc, "models.always.kotelok");
	DeleteAttribute(loc, "models.always.locnap");

	loc.reload.l2.go = "IslaMona_town";
	loc.reload.l2.emerge = "reload1_inside";

	loc.reload.l3.go = "CommonDoubleflourHouse_2";
	loc.reload.l4.go = "CommonStoneHouse";
	loc.reload.l5.go = "CommonDoubleflourHouse_1";

	loc.reload.l6.name = "reload6";
	loc.reload.l6.go = "CommonRoom_MH3";
	loc.reload.l6.emerge = "reload1";
	loc.reload.l6.label = "House";
	
	loc.reload.l7.name = "reload7";
	loc.reload.l7.go = "CommonFlamHouse";
	loc.reload.l7.emerge = "reload1";
	loc.reload.l7.label = "House";
	
	loc.reload.l9.name = "reload1_inside";
	loc.reload.l9.go = "IslaMona_town";
	loc.reload.l9.emerge = "reload2";
	loc.reload.l9.label = "Jungle Fort";
	
	loc.reload.l10.name = "reload3_inside";
	loc.reload.l10.go = "IslaMona_TwoFloorRoom";
	loc.reload.l10.emerge = "reload1";
	loc.reload.l10.label = "Room";
	
	loc.reload.l11.name = "reload9";
	loc.reload.l11.go = "IslaMona_Basement";
	loc.reload.l11.emerge = "reload1";
	loc.reload.l11.autoreload = "0";
	loc.reload.l11.label = "Basement";
	
	
	loc = &locations[FindLocation("IslaMona_TwoFloorRoom")];
	loc.reload.l1.go = "IslaMona_town";
	loc.reload.l1.emerge = "reload3_inside";
	
	
	loc = &locations[FindLocation("IslaMona_Basement")];
	loc.reload.l1.go = "IslaMona_town";
	loc.reload.l1.emerge = "reload9";
	loc.reload.l1.label = "Jungle Fort";
}

void IslaMona_AdvanceStageToFourth() {
	Achievment_Set("ach_CL_92");
	// Добавить модель церкви
	ref loc = &locations[FindLocation("IslaMona_town")];
	loc.filespath.models = "Locations\Town_IslaMona\City\Fourth";														  
	loc.models.always.church = "church";
	// Day
	//loc.models.day.locators = "locators_church";
	loc.models.day.charactersPatch = "patch_church";
	// Night
	//loc.models.night.locators = "locatorsn_church";
	//loc.models.night.locators = "locators_church";
	loc.models.night.charactersPatch = "patch_church";	
	
	
	loc.reload.l12.name = "reload10";
	loc.reload.l12.go = "IslaMona_Church";
	loc.reload.l12.emerge = "reload1";
	loc.reload.l12.autoreload = "0";
	loc.reload.l12.label = "Church";
	
	// Бухта губернатора второй уровень
	int n = FindLocation("Shore75");
	//ReinitLocation(n);
	
	locations[n].id = "Shore75";
	locations[n].id.label = "Shore75";
	locations[n].image = "loading\outside\harbor3.tga";
	locations[n].worldmap = "Shore75";
	//Sound
	locations[n].type = "questisland";
	locations[n].islandId = "IslaMona";
	locations[n].onUninhabitedIsland = true;
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Shores\Shore07";
	Locations[n].models.always.shore07 = "shore07";

	Locations[n].models.always.pier = "shore07_pier";
	Locations[n].models.always.dock = "shore07_dock";

	locations[n].models.always.shore07.sea_reflection = 1;
	Locations[n].models.always.shore07seabed = "shore07_sb";    
	
	Locations[n].models.always.locators = "Shore07_locators_pier";
	
	Locations[n].models.always.grassPatch = "shore07_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";

	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";    

	//Day
	locations[n].models.day.charactersPatch = "shore07_patch_dock_day";
	Locations[n].models.day.jumpPatch = "shore07_jump";
	locations[n].models.day.fonar = "shore07_fd";

	//Night
	locations[n].models.night.charactersPatch = "shore07_patch_dock_night";
	Locations[n].models.night.jumpPatch = "shore07_jump";
	locations[n].models.night.fonar = "shore07_fn";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "IslaMona_Jungle_01";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "boat";
	locations[n].reload.l2.go = "IslaMona";
	locations[n].reload.l2.emerge = "reload_1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Sea";
    locations[n].locators_radius.reload.boat = 9.0;
	Locations[n].DisableEncounters = true;
	
	n = FindLocation("IslaMona_Jungle_01");
	
	locations[n].filespath.models = "locations\Outside\Jungles\jungle13";
	Locations[n].models.always.jungle = "jungle13";	
	Locations[n].models.always.locators = "jungle13L_locators";		
	Locations[n].models.always.grassPatch = "jungle13_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";	
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";
	//Day
	locations[n].models.day.charactersPatch = "jungle13_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle13_patch";
	
	/// СРАЗУ ЖЕ СТАВИТЬ ВАРИАНТ С БОЕВЫМ ПОЛОЖЕНИЕМ ОРУДИЯ И ПАТЧЕМ НЕ ПОЗВОЛЯЮЩИМ ПРОХОД В ПОСЕЛОК
	/// ВНУТРЕННЯЯ ЛОКАЦИЯ ЦЕРКВИ ИСПОЛЬЗОВАНА ВО ВРЕМЕННОМ ПОЛОЖЕНИИ В ЛОКАТОРЕ ХИЖИНЫ релоад5 - ЗАМЕНИТЬ НА НУЖНЫЙ ЛОКАТОР
	
	/* int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE;
	int iScl = 20 + 2*sti(pchar.rank);
	pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу */
	//chrDisableReloadToLocation = true;
	//bQuestDisableMapEnter = true;//закрыть карту
	//pchar.GenQuest.MapClosedNoBattle = true;
	/// -->
	n = Findlocation("IslaMona_town");
	locations[n].models.always.mortair = "mortair";
	Locations[n].models.always.mortair.locator.group = "quest";
	Locations[n].models.always.mortair.locator.name = "mortair_battle"; /// ЭТО КОСТЫЛЬ ДЛЯ ТЕСТОВ, В НОВОЙ ЛОКАЦИИ УБРАТЬ
	Locations[n].models.day.charactersPatch = "PatchQ";
	Locations[n].models.night.charactersPatch = "PatchQ";
	locations[n].locators_radius.quest.detector1 = 7.0;
	/// <--
}

/// Jason ----------------------------------------------------------- Исла Мона ------------------------------------------------------------

void IslaMona_SelectShipyard() // выбрать рандомную верфь из столиц
{
	string sTemp;
	int i = hrand(3);
	switch (i)
	{
		case 0: sTemp = "PortRoyal"; break;
		case 1: sTemp = "Havana"; break;
		case 2: sTemp = "Villemstad"; break;
		case 3: sTemp = "Charles"; break;
	}
	pchar.questTemp.IslaMona.Shipyarder = sTemp+"_shipyarder";
	log_Testinfo(sTemp);
}

void IslaMona_TerksCreateHimenes() // активируем прерывание на создание Хименеса на Терксе
{
	if (pchar.questTemp.IslaMona != "rumours") return;
	pchar.questTemp.IslaMona = "terks";
	AddQuestRecord("IslaMona", "3-1");
	pchar.quest.islamona_terks.win_condition.l1 = "location";
	pchar.quest.islamona_terks.win_condition.l1.location = "Shore57";
	pchar.quest.islamona_terks.function = "IslaMona_TerksSetHimenes";
}

void IslaMona_TerksSetHimenes(string qName) // ставим Хименеса и его людей
{
	pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу
	LAi_LocationFightDisable(&Locations[FindLocation("Shore57")], true);//запретить драться
	chrDisableReloadToLocation = true;
	// Хименес
	sld = GetCharacter(NPC_GenerateCharacter("Himenes", "trader_14", "man", "man", 20, PIRATE, -1, true, "quest"));
	FantomMakeCoolFighter(sld, 10, 20, 20, "", "", "", 50);
	sld.name = StringFromKey("IslaMona_1");
	sld.lastname = StringFromKey("IslaMona_2");
	sld.Dialog.Filename = "Quest\IslaMona_NPC.c";
	sld.dialog.currentnode = "Himenes";
	sld.greeting = "Himenes_01";
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, "Shore57", "goto", "goto7");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	// его компания
	for (int i=1; i<=6; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Himenes_companion_"+i, "citiz_1"+i, "man", "man", 10, PIRATE, -1, true, "quest"));
		FantomMakeCoolFighter(sld, 10, 10, 10, "", "", "", 20);
		sld.Dialog.Filename = "Quest\IslaMona_NPC.c";
		sld.dialog.currentnode = "island_man";
		///sld.greeting = "citizen_male"; ОЗВУЧКУ ЛУЧШЕ СДЕЛАТЬ ДРУГУЮ ИЛИ ВОВСЕ НЕ ВКЛЮЧАТЬ
		ChangeCharacterAddressGroup(sld, "Shore57", "reload", "reload1_back");
		LAi_SetImmortal(sld, true);
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, characterFromID("Himenes"), "", 10.0);
	}
	for (i=7; i<=12; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Himenes_companion_"+i, "women_"+(i+4), "woman", "towngirl", 5, PIRATE, -1, true, "quest"));
		FantomMakeCoolFighter(sld, 5, 5, 5, "", "", "", 20);
		sld.Dialog.Filename = "Quest\IslaMona_NPC.c";
		sld.dialog.currentnode = "island_woman";
		///sld.greeting = "citizen_female"; ОЗВУЧКУ ЛУЧШЕ СДЕЛАТЬ ДРУГУЮ ИЛИ ВОВСЕ НЕ ВКЛЮЧАТЬ
		ChangeCharacterAddressGroup(sld, "Shore57", "reload", "reload1_back");
		LAi_SetImmortal(sld, true);
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, characterFromID("Himenes"), "", 10.0);
	}
}

void IslaMona_TerksHimenesOnBoard() // забираем Хименеса
{
	for (int i=1; i<=12; i++)
	{
		sld = characterFromId("Himenes_companion_"+i);
		LAi_SetActorType(sld);
		LAi_ActorRunToLocation(sld, "goto", "goto1", "none", "", "", "", 10.0);
	}
	LAi_LocationFightDisable(&Locations[FindLocation("Shore57")], false);
	chrDisableReloadToLocation = false;
	AddQuestRecord("IslaMona", "4");
	pchar.questTemp.IslaMona = "himenes";
	pchar.quest.islamona_gohome.win_condition.l1 = "location";
	pchar.quest.islamona_gohome.win_condition.l1.location = "IslaMona_town";
	pchar.quest.islamona_gohome.function = "IslaMona_HimenesArrive";
}

void IslaMona_HimenesArrive(string qName) // Хименес на Исла-Моне
{
	LAi_LocationFightDisable(&Locations[FindLocation("IslaMona_town")], true); // с этого момента драки тут запрещены до последующего разрешения
	chrDisableReloadToLocation = true;
	sld = characterFromId("Himenes");
	sld.greeting = "Himenes_02";
	RemovePassenger(pchar, sld);
	//PlaceCharacter(sld, "goto", "random_must_be_near");
	ChangeCharacterAddressGroup(sld, "IslaMona_town", "goto", "gotoChar3");
	LAi_SetActorType(sld);
	LAi_ActorFollowEverywhere(sld, "", -1);
}

void IslaMona_HimenesWait() // ждать сутки на Исла Моне
{
	pchar.GenQuest.CannotWait = 1;
	sld = characterFromId("Himenes");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload2", "IslaMona_TwoFloorHouse", "goto", "goto1", "OpenTheDoors", 10.0);
	DoQuestFunctionDelay("IslaMona_Himenes_remove_cannotwait", 15.0); 
	pchar.quest.islamona_wait.win_condition.l1 = "Timer";
	pchar.quest.islamona_wait.win_condition.l1.date.hour  = sti(GetTime());
	pchar.quest.islamona_wait.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
	pchar.quest.islamona_wait.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
	pchar.quest.islamona_wait.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
	pchar.quest.islamona_wait.function = "IslaMona_HimenesNextDay";
	AddQuestRecord("IslaMona", "5");
	pchar.questTemp.IslaMona = "wait";
	pchar.questTemp.IslaMona.TownStage = 0;
	for (i=1; i<=2; i++)
	{
		if (GetCharacterIndex("Islamona_fort_pirate_"+i) != -1)
		{
			sld = characterFromId("Islamona_fort_pirate_"+i);
			sld.Dialog.Filename = "Quest\IslaMona_NPC.c";
			sld.dialog.currentnode = "fort_pirate";
			LAi_CharacterEnableDialog(sld);
		}
	}
}

void IslaMona_Himenes_remove_cannotwait(string qName) // можно мотать время
{
	DeleteAttribute(pchar, "GenQuest.CannotWait");
}

void IslaMona_HimenesNextDay(string qName) // снова надо говорить с Родгаром
{
	sld = characterFromId("Himenes");
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, "none", "", "");
	pchar.questTemp.IslaMona = "nextday";
	// пустить народ гулять по поселку
	for (int i=1; i<=12; i++)
	{
		sld = characterFromId("Himenes_companion_"+i);
		ChangeCharacterAddressGroup(sld, "IslaMona_town", "goto", "goto"+i);
		LAi_SetLoginTime(sld, 6.0, 22.0);
		LAi_SetCitizenType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
}

void IslaMona_SetHimenesNextDay() // ставим Хименеса
{
	sld = characterFromId("Himenes");
	sld.dialog.currentnode = "Himenes_23";
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, "IslaMona_town", "goto", LAi_FindFarFreeLocator("goto", locx, locy, locz));
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	pchar.questTemp.IslaMona = "wait";
}

void IslaMona_StalkFin(string qName) // разведка окончена можно говорить с Хименесом и чинить корабли
{
	sld = characterFromId("Himenes");
	sld.dialog.currentnode = "Himenes_31";
	sld = characterFromId("Islamona_carpenter");
	DeleteAttribute(sld, "quest.stalk");
}

void IslaMona_RemoveFood() // удалить со склада продукты и лекарства Родгара
{
	sld = &stores[IslaMona_STORE];
	RemoveStorageGoods(sld, GOOD_FOOD, 2000);
	RemoveStorageGoods(sld, GOOD_MEDICAMENT, 300);
}

void IslaMona_RemoveBuild() // удалить со склада материалы для стройки
{
	sld = &stores[IslaMona_STORE];
	RemoveStorageGoods(sld, GOOD_PLANKS, 1000);
	RemoveStorageGoods(sld, GOOD_BRICK, 500);
	RemoveStorageGoods(sld, GOOD_LEATHER, 200);
	RemoveStorageGoods(sld, GOOD_SAILCLOTH, 300);
	RemoveStorageGoods(sld, GOOD_OIL, 50);
	RemoveStorageGoods(sld, GOOD_CLOTHES, 200);
	setCharacterShipLocation(pchar, "Shore75");
	setWDMPointXZ("Shore75");
	Island_SetReloadEnableLocal("IslaMona", "reload_3", false);
	int n = FindLocation("IslaMona_Jungle_01");
	locations[n].locators_radius.reload.reload2_back = 0;
}

void IslaMona_BuildDone(string qName) // первая перестройка поселка завершена
{
	Log_TestInfo("На Исламону пришла цивилизация");
	/// ------- ТУТ ПРОПИСЫВАЕМ НОВУЮ ЛОКАЦИЮ ПОСЕЛКА, когда она будет готова -----------
	/// ------- ТАКЖЕ СДЕЛАТЬ РЕСЕТ 12 ГУЛЯЮЩИХ ПОСЕЛЕНЦЕВ ПРИ НЕОБХОДИМОСТИ ------
	IslaMona_AdvanceStageToTwo();
	
	sld = CharacterFromID("Islamona_carpenter");
	ChangeCharacterAddressGroup(sld, "IslaMona_town", "goto", "goto1");
	
	sld = CharacterFromID("Islamona_fort_pirate_1");
	ChangeCharacterAddressGroup(sld, "IslaMona_town", "goto", "goto2");
	
	sld = CharacterFromID("Islamona_fort_pirate_2");
	ChangeCharacterAddressGroup(sld, "IslaMona_town", "goto", "goto3");
	
	pchar.quest.islamona_newvillage.win_condition.l1 = "locator";
	pchar.quest.islamona_newvillage.win_condition.l1.location = "IslaMona_town";
	pchar.quest.islamona_newvillage.win_condition.l1.locator_group = "quest";
	pchar.quest.islamona_newvillage.win_condition.l1.locator = "detector"; 
	pchar.quest.islamona_newvillage.function = "IslaMona_BuildComplete";
	
	pchar.questTemp.IslaMona.TownStage = 1;
}

void IslaMona_BuildComplete(string qName) // Хименеса к разговору
{
	chrDisableReloadToLocation = true;
	sld = characterFromId("Himenes");
	sld.dialog.currentnode = "Himenes_38";
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, "IslaMona_town", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void IslaMona_HouseDialogFin() // заканчиваем разговор всех в посёлок
{
	if (GetCharacterIndex("Mirabella") != -1)
	{
		sld = characterFromId("Mirabella");
		ChangeCharacterAddressGroup(sld, "IslaMona_TwoFloorHouse", "goto", "goto1");
	}
	sld = characterFromId("Himenes");
	sld.dialog.currentnode = "Himenes_72";
	ChangeCharacterAddressGroup(sld, "IslaMona_town", "goto", "goto4");
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	sld = characterFromId("Islamona_carpenter");
	sld.dialog.currentnode = "carpenter_17";
	ChangeCharacterAddressGroup(sld, "IslaMona_town", "goto", "goto1");
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	DoQuestReloadToLocation("IslaMona_town", "reload", "reload2", "OpenTheDoors");
	AddQuestRecord("IslaMona", "13");
	AddQuestRecordInfo("IslaMonaData", "2");
	pchar.questTemp.IslaMona = "choose_build";
}

void IslaMona_RemoveHarbour() // удалить со склада материалы для стройки пристани
{
	sld = &stores[29];
	RemoveStorageGoods(sld, GOOD_PLANKS, 300);
	RemoveStorageGoods(sld, GOOD_BRICK, 50);
	RemoveStorageGoods(sld, GOOD_SAILCLOTH, 150);
	RemoveStorageGoods(sld, GOOD_OIL, 20);
}

void IslaMona_RemoveTavern() // удалить со склада материалы для стройки таверны
{
	sld = &stores[29];
	RemoveStorageGoods(sld, GOOD_PLANKS, 200);
	RemoveStorageGoods(sld, GOOD_BRICK, 200);
	RemoveStorageGoods(sld, GOOD_LEATHER, 100);
	RemoveStorageGoods(sld, GOOD_SAILCLOTH, 50);
	RemoveStorageGoods(sld, GOOD_OIL, 10);
	RemoveStorageGoods(sld, GOOD_RUM, 1000);
	RemoveStorageGoods(sld, GOOD_WINE, 1000);
}

void IslaMona_RemovePlantation() // удалить со склада материалы для стройки фактории
{
	sld = &stores[29];
	RemoveStorageGoods(sld, GOOD_PLANKS, 500);
	RemoveStorageGoods(sld, GOOD_BRICK, 250);
	RemoveStorageGoods(sld, GOOD_LEATHER, 200);
	RemoveStorageGoods(sld, GOOD_SAILCLOTH, 100);
	RemoveStorageGoods(sld, GOOD_OIL, 30);
}

void IslaMona_BuildHarbour(string qName) // постройка пристани завершена
{
	Log_testinfo("Бухта губернатора отстроена");
	// меняем бухту Губернатора
	int n = Findlocation("Shore75"); 
	Locations[n].models.always.pier = "shore07_pier";
	//Locations[n].models.always.dock = "shore07_dock";
	locations[n].models.always.locators = "Shore07_locators_pier";
	locations[n].models.day.fonar = "shore07_fd";
	locations[n].models.day.charactersPatch = "shore07_patch_pier_day";
	Locations[n].models.day.jumpPatch = "shore07_jump"; 	
	locations[n].models.night.fonar = "shore07_fn";
	locations[n].models.night.charactersPatch = "shore07_patch_pier_night";
	Locations[n].models.night.jumpPatch = "shore07_jump";
	locations[n].reload.l2.name = "reload2_back";
	locations[n].locators_radius.reload.boat = 2.5;
	pchar.quest.islamona_newharbour.win_condition.l1 = "location";
	pchar.quest.islamona_newharbour.win_condition.l1.location = "Shore75";
	pchar.quest.islamona_newharbour.function = "IslaMona_HarbourComplete";
	pchar.questTemp.IslaMona.Harbour = "complete";
}

void IslaMona_HarbourComplete(string qName) // принимаем работу по перестройке пристани
{
	pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу
	chrDisableReloadToLocation = true;
	sld = characterFromId("Himenes");
	sld.dialog.currentnode = "Himenes_harbour_2";
	ChangeCharacterAddressGroup(sld, "Shore75", "goto", "goto4");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	sld = characterFromId("Islamona_carpenter");
	ChangeCharacterAddressGroup(sld, "Shore75", "goto", "goto3");
	LAi_SetActorType(sld);
	LAi_ActorFollow(sld, characterFromID("Himenes"), "", 5.0);
}

void IslaMona_HarbourClear() // пристань готова
{
	chrDisableReloadToLocation = false;
	sld = characterFromId("Islamona_carpenter");
	sld.dialog.currentnode = "carpenter_17";
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 7.0);
	sld = characterFromId("Himenes");
	sld.dialog.currentnode = "Himenes_72";
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "IslaMona_HarbourClear", 12.0);
}

void IslaMona_BuildTavern(string qName) // постройка таверны завершена
{
	Log_testinfo("Таверна отстроена");
	// перенести все барахло из сундука наверх
	ref location = &Locations[FindLocation("IslaMona_TwoFloorHouse")];
	ref room = &Locations[FindLocation("IslaMona_TwoFloorRoom")];
	aref boxItems, roomItems;
	string sName;
	makearef(boxItems, location.private1.items);
	makearef(roomItems, room.private1.items);
	int iItemsNum = GetAttributesNum(boxItems);
	for(int i=0; i<iItemsNum; i++)
	{
		sName = GetAttributeName(GetAttributeN(boxItems, i));
		roomItems.(sName) = boxItems.(sName);
	}
	DeleteAttribute(location, "private1.items");
	location.private1.items = "";
	// меняем 1 этаж дома ГГ
	IslaMona_AdvanceStageToThree();
	sld = characterFromId("Himenes");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	sld = characterFromId("Islamona_carpenter");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	if (GetCharacterIndex("Mirabella") != -1)
	{
		sld = characterFromId("Mirabella");
		ChangeCharacterAddressGroup(sld, "none", "", "");
	}
	pchar.quest.islamona_newtavern.win_condition.l1 = "location";
	pchar.quest.islamona_newtavern.win_condition.l1.location = "IslaMona_town";
	//pchar.quest.islamona_newtavern.win_condition.l1.locator_group = "reload";
	//pchar.quest.islamona_newtavern.win_condition.l1.locator = "reload2";
	pchar.quest.islamona_newtavern.function = "IslaMona_TavernComplete";
	pchar.questTemp.IslaMona.Tavern = "complete"; 
	pchar.questTemp.IslaMona.TownStage = 2;
	//IslaMona_TavernComplete("");
	
}

void IslaMona_TavernComplete(string qName) // принимаем работу по перестройке таверны
{
	chrDisableReloadToLocation = true;
	loadedLocation.fastreload = "IslaMona";
	sld = characterFromId("Himenes");
	sld.dialog.currentnode = "Himenes_tavern_2";
	sld.greeting = "Himenes_03";
	ChangeCharacterAddressGroup(sld, "IslaMona_town", "sit", "sit_base2");
	LAi_SetSitType(sld);
	sld = characterFromId("Islamona_carpenter");
	sld.dialog.currentnode = "IslaMona_56";
	sld.greeting = "Rodgar_03";
	ChangeCharacterAddressGroup(sld, "IslaMona_town", "sit", "sit_front2");
	LAi_SetSitType(sld);
}

void IslaMona_ReloadTavern() // ночевка после попойки
{
	SetLaunchFrameFormParam(StringFromKey("IslaMona_3"), "", 0, 5);
	LaunchFrameForm();
	int iTime, iAddTime;
	iTime = sti(environment.time);
	if (iTime >= 21) iAddTime = 24 - iTime + 8;
	if (iTime < 7) iAddTime = 8 - iTime;
	if (iTime >= 7 && iTime < 21) iAddTime = 24  + 8 - iTime;
	StoreDayUpdate();
	WaitDate("",0,0,0,iAddtime,5);
	RecalculateJumpTable();
	RefreshWeather();
	RefreshLandTime();
	DoQuestCheckDelay("IslaMona_ReloadTavern", 5.0);
}

void IslaMona_MirabellaWaitress(string qName) // вернуть Мирабель вниз
{
	sld = characterFromId("Mirabella");
	ChangeCharacterAddressGroup(sld, "IslaMona_Town", "waitress", "barmen");
	LAi_SetWaitressType(sld);
	LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
}

/* void IslaMona_TavernAddCrew() // добавление команды в таверну Исла Моны
{
	sld = characterFromId("Islamona_carpenter");
	int crew = sti(sld.crew.qty); // столько сейчас на постое
	int add = sti(sld.crew.add); // столько добавляем
	int total = crew + add;
	sld.Ship.Crew.Exp.Sailors = (stf(pchar.Ship.Crew.Exp.Sailors)*add + stf(sld.Ship.Crew.Exp.Sailors)*crew) / total; 
	sld.Ship.Crew.Exp.Cannoners = (stf(pchar.Ship.Crew.Exp.Cannoners)*add + stf(sld.Ship.Crew.Exp.Cannoners)*crew) / total;
	sld.Ship.Crew.Exp.Soldiers = (stf(pchar.Ship.Crew.Exp.Soldiers)*add + stf(sld.Ship.Crew.Exp.Soldiers)*crew) / total; 
	sld.Ship.Crew.Morale = (stf(pchar.Ship.Crew.Morale)*add + stf(sld.Ship.Crew.Morale)*crew) / total;
	sld.crew.qty = total;
	pchar.ship.crew.quantity = sti(pchar.ship.crew.quantity)-add;
} */

/* void IslaMona_TavernRemoveCrew() // удаление команды из таверны Исла Моны
{
	sld = characterFromId("Islamona_carpenter");
	int add = sti(sld.crew.add); // столько удаляем
	int total = sti(pchar.ship.crew.quantity)+add;
	pchar.Ship.Crew.Exp.Sailors = (stf(sld.Ship.Crew.Exp.Sailors)*add + stf(pchar.Ship.Crew.Exp.Sailors)*sti(pchar.ship.crew.quantity)) / total;
	pchar.Ship.Crew.Exp.Cannoners = (stf(sld.Ship.Crew.Exp.Cannoners)*add + stf(pchar.Ship.Crew.Exp.Cannoners)*sti(pchar.ship.crew.quantity)) / total;
	pchar.Ship.Crew.Exp.Soldiers = (stf(sld.Ship.Crew.Exp.Soldiers)*add + stf(pchar.Ship.Crew.Exp.Soldiers)*sti(pchar.ship.crew.quantity)) / total;
	pchar.Ship.Crew.Morale = (stf(sld.Ship.Crew.Morale)*add + stf(pchar.Ship.Crew.Morale)*sti(pchar.ship.crew.quantity)) / total;
	sld.crew.qty = sti(sld.crew.qty)-add;
	pchar.ship.crew.quantity = total;
} */

void IslaMona_BuildPlantation(string qName) // постройка фактории завершена
{
	Log_testinfo("Фактория построена");
	ref loc = &locations[FindLocation("IslaMona_Jungle_02")];
	loc.locators_radius.reload.reload3_back = 2.0;
	
	pchar.quest.islamona_newfactory.win_condition.l1 = "location";
	pchar.quest.islamona_newfactory.win_condition.l1.location = "Shore75";
	pchar.quest.islamona_newfactory.function = "IslaMona_PlantationComplete";
	pchar.questTemp.IslaMona.Plantation = "complete";
}

void IslaMona_PlantationComplete(string qName) // принимаем работу по постройке фактории
{
	int n = FindLocation("IslaMona_Jungle_01");
	locations[n].locators_radius.reload.reload2_back = 4;
	if (CheckAttribute(pchar, "questTemp.IslaMona.Harbour") && pchar.questTemp.IslaMona.Harbour == "complete") return; // наложилась сдача пристани и фактории
	pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу
	chrDisableReloadToLocation = true;
	sld = characterFromId("Islamona_carpenter");
	sld.dialog.currentnode = "IslaMona_53";
	ChangeCharacterAddressGroup(sld, "Shore75", "goto", "goto4");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void IslaMona_PlantationGo() // отвести на факторию
{
	chrDisableReloadToLocation = false;
	sld = characterFromId("Islamona_carpenter");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload1_back", "IslaMona_Jungle_01", "goto", "goto1", "", -1);
	pchar.quest.islamona_plantation_go.win_condition.l1 = "location";
	pchar.quest.islamona_plantation_go.win_condition.l1.location = "IslaMona_Jungle_01";
	pchar.quest.islamona_plantation_go.function = "IslaMona_PlantationGoNext";
	if (CheckAttribute(pchar, "questTemp.IslaMona.Plantation.Harbour"))
	{
		sld = characterFromId("Himenes");
		LAi_SetActorType(sld);
		LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 7.0);
	}
}

void IslaMona_PlantationGoNext(string qName) // продолжение функции выше
{
	LocatorReloadEnterDisable("IslaMona_Jungle_01", "reload3_back", true); // в посёлок не пускать на случай наложения с таверной
	sld = characterFromId("Islamona_carpenter");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload2_back", "IslaMona_Jungle_02", "goto", "goto4", "", -1);
	pchar.quest.islamona_plantation_go1.win_condition.l1 = "location";
	pchar.quest.islamona_plantation_go1.win_condition.l1.location = "IslaMona_Jungle_02";
	pchar.quest.islamona_plantation_go1.function = "IslaMona_PlantationGoNext1";
	if (CheckAttribute(pchar, "questTemp.IslaMona.Plantation.Harbour"))
	{
		sld = characterFromId("Himenes");
		ChangeCharacterAddressGroup(sld, "IslaMona_Jungle_01", "goto", "goto1");
		LAi_SetActorType(sld);
		LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "", 15.0);
	}
}

void IslaMona_PlantationGoNext1(string qName) {
	sld = characterFromId("Islamona_carpenter");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload3_back", "IslaMona_factoria", "goto", "goto13", "", -1);
	pchar.quest.islamona_plantation_go2.win_condition.l1 = "location";
	pchar.quest.islamona_plantation_go2.win_condition.l1.location = "IslaMona_factoria";
	pchar.quest.islamona_plantation_go2.function = "IslaMona_PlantationGoFin";
	if (CheckAttribute(pchar, "questTemp.IslaMona.Plantation.Harbour"))
	{
		sld = characterFromId("Himenes");
		ChangeCharacterAddressGroup(sld, "IslaMona_Jungle_02", "goto", "goto7");
		LAi_SetActorType(sld);
		LAi_ActorRunToLocation(sld, "reload", "reload3_back", "none", "", "", "", 15.0);
	}
}

void IslaMona_PlantationGoFin(string qName) // продолжение функции выше - пришли на факторию
{
	chrDisableReloadToLocation = true;
	sld = characterFromId("Islamona_carpenter");
	LAi_SetActorType(sld);
	LAi_ActorFollow(sld, pchar, "", 5.0);
	sld = characterFromId("Himenes");
	sld.dialog.currentnode = "Himenes_plantation_4";
	ChangeCharacterAddressGroup(sld, "IslaMona_factoria", "goto", "goto13"); 
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	if (CheckAttribute(pchar, "questTemp.IslaMona.Plantation.Harbour")) DeleteAttribute(pchar, "questTemp.IslaMona.Plantation.Harbour");
	LocatorReloadEnterDisable("IslaMona_Jungle_01", "reload3_back", false);
}

void IslaMona_RemoveSlave() // удалить товары и рабов и запустить факторию, если текущая дата от 16
{
	aref arItems;
	string sName;
	makearef(arItems, pchar.items);
	int iItemsNum = GetAttributesNum(arItems);
	for(int i=0; i<iItemsNum; i++)
	{
		sName = GetAttributeName(GetAttributeN(arItems, i));
		if (findsubstr(sName, "mushket" , 0) != -1 && GetCharacterEquipByGroup(pchar, MUSKET_ITEM_TYPE) != sName)
		{
			RemoveItems(pchar, sName, 1);
			pchar.questTemp.IslaMona.Mushket = sName;
			i = iItemsNum;
		}
	}
	RemoveItems(pchar, "mineral30", 15);
	RemoveCharacterGoods(pchar, GOOD_SLAVES, 15);
	if (GetDataDay() <= 15) SetFunctionTimerCondition("IslaMona_FactoryStart", 0, 0, 20, false);
	else 
	{
		pchar.questTemp.IslaMona.Factory = "true";
		pchar.questTemp.IslaMona.Factory.Part = 0;
	}
	// через сутки оживим факторию - пусть ходят охранники и рабы
	SetFunctionTimerCondition("IslaMona_FactoryHabitants", 0, 0, 1, false); 
}

void IslaMona_FactoryStart(string qName) // запустить факторию, если текущая дата была менее 16
{
	pchar.questTemp.IslaMona.Factory = "true";
	pchar.questTemp.IslaMona.Factory.Part = 0;
}

void IslaMona_FactoryHabitants(string qName) // персонажи на фактории
{
	// два охранника-пирата с мушкетами
	sld = characterFromId("Islamona_fort_pirate_1");
	sld.model = "mush_ctz_8";
	sld.model.animation = "mushketer";
	characters_refreshmodel(sld);
	FantomMakeCoolFighter(sld, 18, 50, 50, "", "mushket1", "bullet", 100);
	AddItems(sld, "bullet", 20);
	AddItems(sld, "gunpowder", 20);
	LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "bullet");
	ChangeCharacterAddressGroup(sld, "IslaMona_factoria", "goto", "goto10"); 
	sld = characterFromId("Islamona_fort_pirate_2");
	sld.model = "mush_ctz_7";
	sld.model.animation = "mushketer";
	characters_refreshmodel(sld);
	FantomMakeCoolFighter(sld, 30, 70, 95, "", pchar.questTemp.IslaMona.Mushket, "", 250);
	AddItems(sld, "bullet", 20);
	AddItems(sld, "grapeshot", 20);
	AddItems(sld, "grenade", 10);
	AddItems(sld, "gunpowder", 20);
	ChangeCharacterAddressGroup(sld, "IslaMona_factoria", "goto", "goto11"); /// НАЗНАЧИТЬ ЛОКАТОРЫ НОВОЙ ЛОКАЦИИ
	// рабы 5 шт
	for(int i=1; i<=5; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Factory_slave_"+i, "prizon_"+(rand(7)+1), "man", "man_B", 5, PIRATE, -1, true, "quest"));
		FantomMakeCoolFighter(sld, 5, 10, 10, "slave_02", "", "", 10);
		sld.Dialog.Filename = "Quest\IslaMona_NPC.c";
		sld.dialog.currentnode = "slave";
		sld.greeting = "convict";
		LAi_SetLoginTime(sld, 6.0, 22.99);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		LAi_SetImmortal(sld, true);
		ChangeCharacterAddressGroup(sld, "IslaMona_factoria", "goto", "goto"+(2+i)); /// НАЗНАЧИТЬ ЛОКАТОРЫ НОВОЙ ЛОКАЦИИ
		LAi_SetCitizenType(sld);
		LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
	}  
	DeleteAttribute(pchar, "questTemp.IslaMona.Mushket");
}

void IslaMona_FactoryReActivar() // перезапуск фактории после защиты Исла Моны
{
	RemoveCharacterGoods(pchar, GOOD_SLAVES, 10);
	pchar.questTemp.IslaMona.Factory = "true"; // запустить факторию
	pchar.questTemp.IslaMona.Factory.Part = sti(pchar.questTemp.IslaMona.RecordPart);
	DeleteAttribute(pchar, "questTemp.IslaMona.RecordPart");
	pchar.questTemp.IslaMona.Factory.Goods = 20*sti(pchar.questTemp.IslaMona.Factory.Part);
	pchar.questTemp.IslaMona.Factory.Dublon = 200*sti(pchar.questTemp.IslaMona.Factory.Part);
	pchar.questTemp.IslaMona.Factory.Bottle = 5*sti(pchar.questTemp.IslaMona.Factory.Part);
	for(int i=1; i<=5; i++)
	{
		sld = characterFromId("Factory_slave_"+i);
		ChangeCharacterAddressGroup(sld, "IslaMona_factoria", "goto", "goto"+(2+i)); /// НАЗНАЧИТЬ ЛОКАТОРЫ НОВОЙ ЛОКАЦИИ
		LAi_SetCitizenType(sld);
		LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
	}
	sld = characterFromId("Islamona_fort_pirate_1");
	ChangeCharacterAddressGroup(sld, "IslaMona_factoria", "goto", "goto10"); /// НАЗНАЧИТЬ ЛОКАТОРЫ НОВОЙ ЛОКАЦИИ
	if (GetCharacterIndex("Islamona_fort_pirate_2") != -1)
	{
		sld = characterFromId("Islamona_fort_pirate_2");
		ChangeCharacterAddressGroup(sld, "IslaMona_factoria", "goto", "goto11"); /// НАЗНАЧИТЬ ЛОКАТОРЫ НОВОЙ ЛОКАЦИИ
	}
}

void IslaMona_FactoryPart() // партия бакаута
{
	if (sti(pchar.questTemp.IslaMona.Factory.Part) > 5) return;
	//log_info("Родриго Хименес подготовил очередную партию бакаута на Исла Мона");
	LaunchMessage(StringFromKey("IslaMona_4"));
	pchar.questTemp.IslaMona.Factory.Part = sti(pchar.questTemp.IslaMona.Factory.Part)+1;
	pchar.questTemp.IslaMona.Factory.Goods = 20*sti(pchar.questTemp.IslaMona.Factory.Part);
	pchar.questTemp.IslaMona.Factory.Dublon = 200*sti(pchar.questTemp.IslaMona.Factory.Part);
	pchar.questTemp.IslaMona.Factory.Bottle = 5*sti(pchar.questTemp.IslaMona.Factory.Part);
}

void IslaMona_FactoryTrade()
{
	PlaySound("interface\notebook.wav");
	RemoveDublonsFromPCharTotal(sti(pchar.questTemp.IslaMona.Factory.Dublon));
	RemoveItemsFromPCharTotal("potionrum", sti(pchar.questTemp.IslaMona.Factory.Bottle));
	RemoveItemsFromPCharTotal("potionwine", sti(pchar.questTemp.IslaMona.Factory.Bottle));
	notification(StringFromKey("IslaMona_5", sti(pchar.questTemp.IslaMona.Factory.Bottle)), "None");
	notification(StringFromKey("IslaMona_6", sti(pchar.questTemp.IslaMona.Factory.Bottle)), "None");
	//Log_Info("Вы отдали "+sti(pchar.questTemp.IslaMona.Factory.Bottle)+" бутылок рома");
	//Log_Info("Вы отдали "+sti(pchar.questTemp.IslaMona.Factory.Bottle)+" бутылок вина");
	sld = &stores[29];
	AddStorageGoods(sld, GOOD_SANDAL, sti(pchar.questTemp.IslaMona.Factory.Goods));
	//Log_Info("На ваш склад загружено "+sti(pchar.questTemp.IslaMona.Factory.Goods)+" бревен бакаута");
	LaunchMessage(StringFromKey("IslaMona_7", sti(pchar.questTemp.IslaMona.Factory.Goods)));
	pchar.questTemp.IslaMona.Factory.Part = 0;
	Achievment_SetStat(94, 1);
}

void IslaMona_RemoveChurch() // удалить со склада материалы для стройки церкви
{
	sld = &stores[29];
	RemoveStorageGoods(sld, GOOD_PLANKS, 300);
	RemoveStorageGoods(sld, GOOD_BRICK, 100);
	RemoveStorageGoods(sld, GOOD_OIL, 10);
	RemoveStorageGoods(sld, GOOD_SANDAL, 20);
	RemoveStorageGoods(sld, GOOD_MAHOGANY, 100);
	/* RemoveItems(pchar, "jewelry5", 50);
	RemoveItems(pchar, "mineral3", 100);
	RemoveItems(pchar, "jewelry8", 30);
	RemoveItems(pchar, "jewelry7", 1);
	PlaySound("interface\important_item.wav");
	Log_Info("Вы отдали 50 золотых самородков");
	Log_Info("Вы отдали 100 свечей");
	Log_Info("Вы отдали 30 янтаря");
	Log_Info("Вы отдали 1 голубой янтарь"); */
}

void IslaMona_ChurchComplete(string qName) // церковь построена - начало защиты Исла Моны
{
	/// СЮДА СТАВИМ ОБНОВЛЕНИЕ ЛОКАЦИИ ПОСЕЛКА С ПОСТРОЕННОЙ ЦЕРКОВЬЮ
	Log_testinfo("Церковь построена");
	
	pchar.questTemp.IslaMonaDisableFantom = true;
	
	IslaMona_AdvanceStageToFourth();
	
	// расставляем весь наш бомонд
	sld = characterFromId("Himenes"); // Хименеса из фактории в посёлок
	ChangeCharacterAddressGroup(sld, "IslaMona_town", "quest", "QuestChar2"); /// НАЗНАЧИТЬ ЛОКАТОР НОВОЙ ЛОКАЦИИ У ПУШКИ
	LAi_SetActorType(sld);
	sld = GetColonyByIndex(FindColony("islamona"));
	int n = GetCrewQuantity(sld);
	sld = characterFromId("Islamona_carpenter"); // Родгар
	ChangeCharacterAddressGroup(sld, "IslaMona_town", "quest", "QuestChar3"); /// НАЗНАЧИТЬ ЛОКАТОР НОВОЙ ЛОКАЦИИ У ПУШКИ
	LAi_SetActorType(sld);
	if (n >= 50) // антуражные матросы
	{
		for (int i=1; i<=2; i++) // 
		{
			sld = GetCharacter(NPC_GenerateCharacter("IM_sailor_"+i, "citiz_3"+(7+i), "man", "man", 18, PIRATE, -1, true, "quest"));
			FantomMakeCoolFighter(sld, 18, 50, 50, LinkRandPhrase("blade_07","blade_08","blade_11"), "pistol1", "bullet", 100);
			LAi_CharacterDisableDialog(sld);
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "IslaMona_town", "goto", "goto"+(7+i)); /// НАЗНАЧИТЬ ЛОКАТОРЫ НОВОЙ ЛОКАЦИИ
		}
	}
	sld = characterFromId("Islamona_fort_pirate_1"); // пират 1
	ChangeCharacterAddressGroup(sld, "IslaMona_town", "quest", "QuestChar5"); /// НАЗНАЧИТЬ ЛОКАТОР НОВОЙ ЛОКАЦИИ У ПУШКИ
	LAi_SetActorType(sld);
	if (!CheckAttribute(pchar, "questTemp.IslaMona.Nodublon"))
	{
		sld = characterFromId("Islamona_fort_pirate_2"); // пират 2
		ChangeCharacterAddressGroup(sld, "IslaMona_town", "quest", "QuestChar6"); /// НАЗНАЧИТЬ ЛОКАТОР НОВОЙ ЛОКАЦИИ У ПУШКИ
		LAi_SetActorType(sld);
	}
	if (GetCharacterIndex("Mirabella") != -1) // Мирабель
	{
		sld = characterFromId("Mirabella");
		ChangeCharacterAddressGroup(sld, "IslaMona_town", "quest", "QuestChar4"); /// НАЗНАЧИТЬ ЛОКАТОР НОВОЙ ЛОКАЦИИ У ПУШКИ
		LAi_SetActorType(sld);
	}
	for (i=1; i<=2; i++) // антуражные горожане
	{
		sld = GetCharacter(NPC_GenerateCharacter("IM_Tempcitien_"+i, "citiz_1"+(7+i), "man", "man", 18, PIRATE, -1, true, "quest"));
		FantomMakeCoolFighter(sld, 18, 50, 50, LinkRandPhrase("blade_07","blade_08","blade_11"), "pistol1", "bullet", 100);
		LAi_CharacterDisableDialog(sld);
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, "IslaMona_town", "goto", "goto"+(10+i)); /// НАЗНАЧИТЬ ЛОКАТОРЫ НОВОЙ ЛОКАЦИИ
	}
	// горожан с улицы убрать
	for(i=1; i<=12; i++)
	{
		sld = characterFromId("Himenes_companion_"+i);
		ChangeCharacterAddressGroup(sld, "none", "", "");
	}
	// рабов с фактории убрать
	for(i=1; i<=5; i++)
	{
		sld = characterFromId("Factory_slave_"+i);
		ChangeCharacterAddressGroup(sld, "none", "", "");
	} 
	// остановить производство бакаута, но количество уже готовых партий запомним
	pchar.questTemp.IslaMona.RecordPart = sti(pchar.questTemp.IslaMona.Factory.Part);
	DeleteAttribute(pchar, "questTemp.IslaMona.Factory");
	pchar.quest.islamona_church_frasolders.win_condition.l1 = "location";
	pchar.quest.islamona_church_frasolders.win_condition.l1.location = "shore75";
	pchar.quest.islamona_church_frasolders.function = "IslaMona_Church_frasold";
}

void IslaMona_Church_frasold(string qName)
{
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE;
	int iScl = 20 + 2*sti(pchar.rank);
	pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу
	chrDisableReloadToLocation = true;
	bQuestDisableMapEnter = true;//закрыть карту
	pchar.GenQuest.MapClosedNoBattle = true;
	LAi_LocationFightDisable(&Locations[FindLocation("shore75")], true);
	// в факторию ставим офицера
	sld = GetCharacter(NPC_GenerateCharacter("IM_fraofficer", "off_fra_2", "man", "man", iRank+5, FRANCE, -1, true, "soldier"));
	FantomMakeCoolFighter(sld, iRank+5, iScl+10, iScl+10, "blade_20", "pistol4", "bullet", iScl*3);
	sld.Dialog.Filename = "Quest\IslaMona_NPC.c";
	sld.dialog.currentnode = "FraOfficer";
	sld.greeting = "ImOfficer_01";
	ChangeCharacterAddressGroup(sld, "IslaMona_factoria", "quest", "quest1");
	LAi_SetActorType(sld);
	// создаем группировку французов
	for (i=1; i<=7; i++) 
	{
		sld = GetCharacter(NPC_GenerateCharacter("IM_soldier_"+i, "sold_fra_"+i, "man", "man", iRank, FRANCE, -1, true, "soldier"));
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, LinkRandPhrase("blade_10","blade_13","blade_15"), "pistol1", "bullet", iScl*2);
		if (i == 1)
		{
			sld.Dialog.Filename = "Quest\IslaMona_NPC.c";
			sld.dialog.currentnode = "Capral";
			ChangeCharacterAddressGroup(sld, "Shore75", "goto", "goto2"); 
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		}
	}
	for (i=8; i<=12; i++) // мушкетеры
	{
		sld = GetCharacter(NPC_GenerateCharacter("IM_soldier_"+i, "mush_fra_"+(i-7), "man", "mushketer", iRank, FRANCE, -1, true, "soldier"));
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "cartridge", iScl*2);
	}		
	for (int i=1; i<=7; i++) 
	{
		sld = GetCharacter(NPC_GenerateCharacter("IM_fra_sailor_"+i, "citiz_3"+i, "man", "man", iRank, FRANCE, -1, true, "soldier"));
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, LinkRandPhrase("blade_10","blade_13","blade_15"), "pistol1", "bullet", iScl*2);
	}
}

void IslaMona_DefCapralTalk(string qName) // разговор с капралом
{
	LAi_LocationFightDisable(&Locations[FindLocation("IslaMona_Jungle_01")], true);//запретить драться
	chrDisableReloadToLocation = true;
	sld = characterFromId("IM_soldier_1");
	sld.dialog.currentnode = "Capral_6";
	ChangeCharacterAddressGroup(sld, "IslaMona_Jungle_01", "goto", "goto8");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void IslaMona_DefKillCapral(string qName) // 
{
	LAi_LocationFightDisable(&Locations[FindLocation("Shore75")], false);
	LAi_LocationFightDisable(&Locations[FindLocation("IslaMona_Jungle_01")], false);
	// если не надет пистоль или мушкет, то выдадим строевой -->
	if(!CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE) || !CheckAttribute(pchar,"equip."+MUSKET_ITEM_TYPE))
	{
		GiveItem2Character(pchar, "pistol1");
		EquipCharacterbyItem(pchar, "pistol1");
	}
	LAi_SetActorType(pchar);
	LAi_ActorAnimation(pchar, "Shot", "IslaMona_DefKillCapral", 1.5);
}

void IslaMona_DefGotoMarch() // идем в посёлок
{
	LocatorReloadEnterDisable("IslaMona_jungle_01", "reload1_back", true); // закрыть бухту Губернатора
	pchar.quest.islamona_def_jungle.win_condition.l1 = "locator";
	pchar.quest.islamona_def_jungle.win_condition.l1.location = "IslaMona_jungle_01";
	pchar.quest.islamona_def_jungle.win_condition.l1.locator_group = "encdetector";
	pchar.quest.islamona_def_jungle.win_condition.l1.locator = "enc01";
	pchar.quest.islamona_def_jungle.function = "IslaMona_DefCheckJungle"; // проверка на оплату 600 дублонов
	pchar.quest.islamona_def_town.win_condition.l1 = "locator";
	pchar.quest.islamona_def_town.win_condition.l1.location = "IslaMona_town";
	pchar.quest.islamona_def_town.win_condition.l1.locator_group = "quest";
	pchar.quest.islamona_def_town.win_condition.l1.locator = "detector1"; /// !! ЭТОТ ЛОКАТОР НУЖНО ПЕРЕНЕСТИ В НОВУЮ ЛОКАЦИЮ, он активирует функцию ниже, либо изменить логику на иную
	pchar.quest.islamona_def_town.function = "IslaMona_DefInTown"; // на наших поселенцев
}

void IslaMona_DefCheckJungle(string qName) // проверяем на оплату дублонов
{
	if (!CheckAttribute(pchar, "questTemp.IslaMona.Nodublon")) return;
	chrDisableReloadToLocation = true;
	sld = characterFromId("Islamona_fort_pirate_2"); // пират 2
	ChangeCharacterAddressGroup(sld, "IslaMona_jungle_01", "goto", "goto8");
	LAi_CharacterEnableDialog(sld);
	sld.Dialog.Filename = "Quest\IslaMona_NPC.c";
	sld.dialog.currentnode = "Pirate";
	LAi_SetImmortal(sld, false);
	LAi_SetActorType(sld);
	LAi_ActorDialogDelay(sld, pchar, "", 1.0);
	pchar.questTemp.IslaMona.Defend.Force = "true";
}

void IslaMona_DefCheckJungleFight() // бой при неоплате дублонов - наказание за жадность, чтобы сам с офицерами дрался против всей толпы
{
	PlaySound("interface\abordage_wining.wav");
	LAi_group_Delete("EnemyFight");
	sld = characterFromId("IM_fraofficer");
	ChangeCharacterAddressGroup(sld, "IslaMona_jungle_01", "reload", "reload2_back");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	for (int i=1; i<=12; i++) 
	{
		sld = characterFromId("IM_soldier_"+i);
		ChangeCharacterAddressGroup(sld, "IslaMona_jungle_01", "reload", "reload2_back");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	sld = characterFromId("Islamona_fort_pirate_2");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "IslaMona_DefCheckJungleAfterFight");
	LAi_LocationFightDisable(&Locations[FindLocation("IslaMona_Jungle_01")], false);
	AddDialogExitQuest("MainHeroFightModeOn");	
}
void IslaMona_DefKillSlaves(string qName) 
{
	for (i=1; i<=10; i++) // жертвы нападения
	{
		sld = GetCharacter(NPC_GenerateCharacter("IMdead_slave_"+i, "prizon_"+(rand(7)+1), "man", "man_B", 5, PIRATE, -1, true, "quest"));
		SetFantomParamFromRank(sld, 5, true);
		RemoveAllCharacterItems(sld, true);
		sld.DontClearDead = true;
		LAi_SetStayType(sld);
		ChangeCharacterAddressGroup(sld, "Islamona_town", "quest", "NPCDeadSlaves"+i);
		LAi_KillCharacter(sld);
	}
}
void IslaMona_DefInTown(string qName) // пришли к поселку
{
	sld = characterFromId("Islamona_carpenter");
	sld.dialog.currentnode = "IslaMona_64";
	LAi_SetActorType(sld);
	LAi_ActorDialogDelay(sld, pchar, "", 1.0);
}

void IslaMona_DefSoldiersInJungle(string qName) // разговор с офицером перед атакой поселка
{
	chrDisableReloadToLocation = true;
	sld = characterFromId("IM_fraofficer");
	sld.dialog.currentnode = "FraOfficer_10";
	sld.greeting = "ImOfficer_02";
	ChangeCharacterAddressGroup(sld, "IslaMona_jungle_01", "reload", "reload2_back");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	for (int i=1; i<=12; i++) 
	{
		sld = characterFromId("IM_soldier_"+i);
		ChangeCharacterAddressGroup(sld, "IslaMona_jungle_01", "reload", "reload2_back");
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, characterFromID("IM_fraofficer"), "", -1);
	}
	for(i=1; i<=7; i++)
	{
		sld = characterFromId("IM_fra_sailor_"+i);
		ChangeCharacterAddressGroup(sld, "IslaMona_jungle_01", "reload", "reload2_back");
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, characterFromID("IM_fraofficer"), "", -1);
	}
}

void IslaMona_DefAttackLight() // французы атакуют без нас
{
	sld = characterFromId("IM_fraofficer");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload3_back", "none", "", "", "IslaMona_DefAttackLight", 10.0);
	for (int i=1; i<=12; i++) 
	{
		sld = characterFromId("IM_soldier_"+i);
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, characterFromID("IM_fraofficer"), "", -1);
	}
	for(i=1; i<=7; i++)
	{
		sld = characterFromId("IM_fra_sailor_"+i);
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, characterFromID("IM_fraofficer"), "", -1);
	}
}

void IslaMona_DefBattleLight(string qName) // входим в посёлок в варианте без нас
{
	chrDisableReloadToLocation = true;
	PlaySound("interface\MusketFire1.wav");
	for (int i=6; i<=12; i++) 
	{
		sld = characterFromId("IM_soldier_"+i);
		ChangeCharacterAddressGroup(sld, "IslaMona_town", "quest", "NPCDeadSold"+(i-3)); /// НАДО РАССТАВИТЬ В ЛОКАЦИИ ЭТИ ЛОКАТОРЫ У САМЫХ ВОРОТ
		LAi_KillCharacter(sld);
	}
	
	for(i=1; i<=3; i++)
	{
		sld = characterFromId("IM_fra_sailor_"+i);
		ChangeCharacterAddressGroup(sld, "IslaMona_town", "quest", "NPCDeadSlaves"+(11-i)); 
		LAi_KillCharacter(sld);
	}
	
	for (i=1; i<=5; i++) 
	{
		sld = characterFromId("IM_soldier_"+i);
		ChangeCharacterAddressGroup(sld, "IslaMona_town", "quest", "NPCDeadSlaves"+i); /// НАДО РАССТАВИТЬ В ЛОКАЦИИ ЭТИ ЛОКАТОРЫ У САМЫХ ВОРОТ
		LAi_SetImmortal(sld, true);
		LAi_CharacterDisableDialog(sld);
		LAi_SetgroundSitType(sld);
	}
	
	for(i=4; i<=7; i++)
	{
		sld = characterFromId("IM_fra_sailor_"+i);
		ChangeCharacterAddressGroup(sld, "IslaMona_town", "quest", "NPCDeadSold"+(8-i)); 
		LAi_SetImmortal(sld, true);
		LAi_CharacterDisableDialog(sld);
		LAi_SetgroundSitType(sld);
	}
	sld = characterFromId("IM_fraofficer");
	sld.greeting = "ImOfficer_03";
	LAi_SetImmortal(sld, true);
	LAi_CharacterDisableDialog(sld);
	ChangeCharacterAddressGroup(sld, "IslaMona_town", "quest", "NPCDeadSlaves6"); /// ОПРЕДЕЛИТЬ ЕМУ ЛОКАТОР У ВОРОТ
	LAi_SetgroundSitType(sld);
	pchar.quest.islamona_def_finbattle.win_condition.l1 = "locator";
	pchar.quest.islamona_def_finbattle.win_condition.l1.location = "IslaMona_town";
	pchar.quest.islamona_def_finbattle.win_condition.l1.locator_group = "quest";
	pchar.quest.islamona_def_finbattle.win_condition.l1.locator = "detector1";
	pchar.quest.islamona_def_finbattle.function = "IslaMona_DefBattleLightFin"; // на Родгара
}

void IslaMona_DefBattleLightFin(string qName) // разговор с Родгаром после боя
{
	sld = characterFromId("Islamona_carpenter");
	sld.dialog.currentnode = "IslaMona_70";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void IslaMona_DefBattleLightClear() // приводим посёлок в мирное состояние
{
	/// УСТАНОВИТЬ МИРНЫЙ ВАРИАНТ ПОСЕЛКА - ПАТЧ СО ВХОДОМ ВНУТРЬ, ПУШКУ В СТОРОНУ
	int n = Findlocation("IslaMona_town");
	locations[n].models.always.mortair = "mortair";
	Locations[n].models.always.mortair.locator.group = "quest";
	Locations[n].models.always.mortair.locator.name = "mortair";
	Locations[n].models.day.charactersPatch = "Patch";
	Locations[n].models.night.charactersPatch = "Patch";
	chrDisableReloadToLocation = false;
	LocatorReloadEnterDisable("IslaMona_Jungle_01", "reload1_back", false);
	LocatorReloadEnterDisable("IslaMona_Jungle_01", "reload2_back", false);
	LAi_LocationFightDisable(&Locations[FindLocation("IslaMona_Jungle_01")], false);
	// Родгара и Мирабель в таверну, запустить гулять горожан и пиратов, Родриго спрятать
	sld = characterFromId("Islamona_carpenter");
	sld.dialog.currentnode = "carpenter_17";
	ChangeCharacterAddressGroup(sld, "IslaMona_Town", "barmen", "stay");
	LAi_SetBarmanType(sld);
	LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
	if (GetCharacterIndex("Mirabella") != -1)
	{
		sld = characterFromId("Mirabella");
		sld.dialog.currentnode = "mirabelle_42";
		ChangeCharacterAddressGroup(sld, "IslaMona_Town", "waitress", "barmen");
		LAi_SetWaitressType(sld);
		LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
	}
	sld = characterFromId("Himenes");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	for (int i=1; i<=12; i++)
	{
		sld = characterFromId("Himenes_companion_"+i);
		ChangeCharacterAddressGroup(sld, "IslaMona_town", "goto", "goto"+i);
		LAi_SetCitizenType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	for (i=1; i<=2; i++)
	{
		if (GetCharacterIndex("Islamona_fort_pirate_"+i) != -1)
		{
			sld = characterFromId("Islamona_fort_pirate_"+i);
			LAi_SetWarriorType(sld);
			ChangeCharacterAddressGroup(sld, "IslaMona_town", "goto", "goto1"+i); /// ОПРЕДЕЛИТЬ ЛОКАТОРЫ
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
		if (GetCharacterIndex("IM_sailor_"+i) != -1)
		{
			sld = characterFromId("IM_sailor_"+i);
			LAi_SetImmortal(sld, false);
			sld.lifeDay = 0;
		}
		if (GetCharacterIndex("IM_Tempcitien_"+i) != -1)
		{
			sld = characterFromId("IM_Tempcitien_"+i);
			LAi_SetImmortal(sld, false);
			sld.lifeDay = 0;
		}
	}
	if(!CheckAttribute(pchar, "questTemp.IslaMona.Defend.Force"))
	{
		if(CheckAttribute(pchar,"questTemp.IslaMona.Fraprisoner")) // превратим в рабов todo
		{
			
		}
		else
		{
			for (i=1; i<=5; i++) 
			{
				sld = characterFromId("IM_soldier_"+i);
				LAi_SetImmortal(sld, false);
				sld.lifeDay = 0;
			}
			for(i=5; i<=7; i++)
			{
				sld = characterFromId("IM_fra_sailor_"+i);
				LAi_SetImmortal(sld, false);
				sld.lifeDay = 0;
			}
			sld = characterFromId("IM_fraofficer");
			LAi_SetImmortal(sld, false);
			sld.lifeDay = 0;
		}
	}
	pchar.quest.islamona_def_clear.win_condition.l1 = "Timer";
	pchar.quest.islamona_def_clear.win_condition.l1.date.hour  = 8.00;
	pchar.quest.islamona_def_clear.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
	pchar.quest.islamona_def_clear.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
	pchar.quest.islamona_def_clear.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
	pchar.quest.islamona_def_clear.function = "IslaMona_ChurchPrepareCelebrar";
	AddQuestRecord("IslaMona", "25");
	Achievment_Set("ach_CL_93");
}

void IslaMona_DefAttackCommon() // готовим абордажную роту для совместной атаки
{
	chrDisableReloadToLocation = false;
	LocatorReloadEnterDisable("IslaMona_Jungle_01", "reload1_back", false);
	LocatorReloadEnterDisable("IslaMona_Jungle_01", "reload3_back", true);
	LocatorReloadEnterDisable("IslaMona_Jungle_01", "reload2_back", true);
	pchar.quest.islamona_attack_common.win_condition.l1 = "location";
	pchar.quest.islamona_attack_common.win_condition.l1.location = "shore75";
	pchar.quest.islamona_attack_common.function = "IslaMona_DefAttackCommonArmy";
	pchar.questTemp.IslaMona.Defend.Common = "true";
}

void IslaMona_DefAttackCommonArmy(string qName) // абордажная рота в бухте
{
	chrDisableReloadToLocation = true;
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE;
	int iScl = 20 + 2*sti(pchar.rank);
	sld = GetCharacter(NPC_GenerateCharacter("Alonso", "citiz_36", "man", "man", 35, FRANCE, -1, false, "soldier"));
	FantomMakeCoolFighter(sld, 35, 90, 90, "blade_10", "pistol5", "bullet", 250);
	sld.name = StringFromKey("IslaMona_8");
	sld.lastname = StringFromKey("IslaMona_9");
	sld.Dialog.Filename = "Quest\IslaMona_NPC.c";
	sld.dialog.currentnode = "Alonso";
	LAi_SetCheckMinHP(sld, 10, true, ""); // скрытое бессмертие
	ChangeCharacterAddressGroup(sld, "Shore75", "reload", "sea");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	for (int i=1; i<=5; i++) 
	{
		sld = GetCharacter(NPC_GenerateCharacter("IM_our_soldier_"+i, "citiz_3"+i, "man", "man", iRank, FRANCE, -1, true, "soldier"));
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, LinkRandPhrase("blade_10","blade_13","blade_15"), "pistol1", "bullet", iScl*2);
		ChangeCharacterAddressGroup(sld, "Shore75", "reload", "sea");
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, characterFromID("Alonso"), "", -1);
	}
}

void IslaMona_DefAttackCommonPrepare(string qName) // разговор с офицером перед атакой поселка
{
	chrDisableReloadToLocation = true;
	sld = characterFromId("IM_fraofficer");
	sld.dialog.currentnode = "FraOfficer_20";
	LAi_SetStayType(sld);
}

void IslaMona_DefAttackCommonRun() // бежим в посёлок для совместной атаки
{
	chrDisableReloadToLocation = false;
	LocatorReloadEnterDisable("IslaMona_Jungle_01", "reload1_back", true);
	LocatorReloadEnterDisable("IslaMona_Jungle_01", "reload3_back", false);
	LAi_LocationFightDisable(&Locations[FindLocation("IslaMona_town")], false);
	sld = characterFromId("IM_fraofficer");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload3_back", "none", "", "", "", 10.0);
	for (int i=1; i<=12; i++) 
	{
		sld = characterFromId("IM_soldier_"+i);
		LAi_SetActorType(sld);
		LAi_ActorRunToLocation(sld, "reload", "reload3_back", "none", "", "", "", 10.0);
	}
	pchar.quest.islamona_attack_common2.win_condition.l1 = "location";
	pchar.quest.islamona_attack_common2.win_condition.l1.location = "IslaMona_town";
	pchar.quest.islamona_attack_common2.function = "IslaMona_DefAttackCommonBattle";
}

void IslaMona_DefAttackCommonBattle(string qName) // бой в посёлке - выставим паузу на старт боя в несколько сек, иначе могут быть накладки при загрузке локации
{
	chrDisableReloadToLocation = true;
	/// ВЫСТАВЛЯЕМ РОДРИГО И ДВУХ ЕГО ПИРАТОВ ЗА ВОРОТА, ОПРЕДЕЛИТЬ ИМ ЛОКАТОРЫ 
	///(НАПОМИНАЮ ЧТО В ЛОКАЦИИ В ДАННЫЙ МОМЕНТ СТОИТ ПАТЧ, НЕ ПОЗВОЛЯЮЩИЙ ПРОХОД ВНУТРЬ ПОСЕЛКА)
	sld = characterFromId("Islamona_carpenter");
	ChangeCharacterAddressGroup(sld, "IslaMona_town", "quest", "NPCOur14"); /// ОПРЕДЕЛИТЬ ЕМУ ЛОКАТОР У ВОРОТ
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	for (int i=1; i<=2; i++) // 
	{
		sld = characterFromId("Islamona_fort_pirate_"+i);
		ChangeCharacterAddressGroup(sld, "IslaMona_town", "quest", "NPCOur1"+i); /// ОПРЕДЕЛИТЬ ЕМУ ЛОКАТОР У ВОРОТ
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	sld = characterFromId("Alonso");
	ChangeCharacterAddressGroup(sld, "IslaMona_town", "quest", "NPCOur13");
	
	for (i=1; i<=5; i++) 
	{
		sld = characterFromId("IM_our_soldier_"+i);
		ChangeCharacterAddressGroup(sld, "IslaMona_town", "quest", "NPCOur"+i);
	}
	
	sld = characterFromId("IM_fraofficer");
	ChangeCharacterAddressGroup(sld, "IslaMona_town", "quest", "NPCEnemy1"); /// ОПРЕДЕЛИТЬ ЕМУ ЛОКАТОР МЕЖДУ ВХОДОМ И ВОРОТАМИ
	LAi_SetWarriorType(sld);
	for (i=1; i<=12; i++) 
	{
		sld = characterFromId("IM_soldier_"+i);
		ChangeCharacterAddressGroup(sld, "IslaMona_town", "quest", "NPCEnemy"+i); /// ОПРЕДЕЛИТЬ ЕМУ ЛОКАТОР МЕЖДУ ВХОДОМ И ВОРОТАМИ
		LAi_SetWarriorType(sld);
	}
	for(i=1; i<=3; i++)
	{
		sld = characterFromId("IM_fra_sailor_"+i);
		ChangeCharacterAddressGroup(sld, "IslaMona_town", "quest", "NPCEnemy1"+i);
	}
	for(i=4; i<=7; i++)
	{
		sld = characterFromId("IM_fra_sailor_"+i);
		ChangeCharacterAddressGroup(sld, "IslaMona_town", "quest", "NPCEnemy1"+i);
	}
	DoQuestFunctionDelay("IslaMona_DefAttackCommonBattleGo", 2.5); // время задержки можно корректировать чтобы выглядело лучше (по тестам)
}

void IslaMona_DefAttackCommonBattleGo(string qName) // начинаем бой в посёлке
{
	PlaySound("interface\abordage_wining.wav");
	LAi_group_Delete("EnemyFight");
	sld = characterFromId("Alonso");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	for (int i=1; i<=5; i++) 
	{
		sld = characterFromId("IM_our_soldier_"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	sld = characterFromId("IM_fraofficer");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	for (i=1; i<=12; i++) 
	{
		sld = characterFromId("IM_soldier_"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	for(i=1; i<=7; i++)
	{
		sld = characterFromId("IM_fra_sailor_"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "IslaMona_DefAttackCommonBattleEnd");
}

void IslaMona_DefAttackForce(string qName) // атака фактории своими силами
{
	sld = characterFromId("IM_fraofficer");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	chrDisableReloadToLocation = true;
	DoQuestFunctionDelay("IslaMona_DefAttackForceGo", 2.0); 
}

void IslaMona_DefAttackForceGo(string qName) // атака фактории своими силами
{
	PlaySound("interface\abordage_wining.wav");
	LAi_group_Delete("EnemyFight");
	sld = characterFromId("Alonso");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	for (int i=1; i<=5; i++) 
	{
		sld = characterFromId("IM_our_soldier_"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	sld = characterFromId("IM_fraofficer");
	ChangeCharacterAddressGroup(sld, "IslaMona_factoria", "quest", "NPCEnemy1"); /// ОПРЕДЕЛИТЬ ЛОКАТОР
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	for (i=2; i<=12; i++) 
	{
		sld = characterFromId("IM_soldier_"+i);
		ChangeCharacterAddressGroup(sld, "IslaMona_factoria", "quest", "NPCEnemy"+i); /// ОПРЕДЕЛИТЬ ЛОКАТОР
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "IslaMona_DefAttackForceEnd");
}

void IslaMona_ChurchPrepareCelebrar(string qName) // готовим праздник в церкви
{
	/// РАССТАВИТЬ ПО ЛОКАТОРАМ СЛЕДУЮЩИХ ПЕРСОНАЖЕЙ В ЦЕРКВИ ТАК, ЧТОБЫ ОНИ МОГЛИ ГОВОРИТЬ С ГГ НЕ СХОДЯ С МЕСТА
	sld = characterFromId("Himenes"); // Хименес
	ChangeCharacterAddressGroup(sld, "IslaMona_church", "barmen", "stay"); /// ОПРЕДЕЛИТЬ ЛОКАТОР
	LAi_SetActorType(sld);
	sld = characterFromId("Islamona_carpenter"); // Родгар
	sld.greeting = "Rodgar_03";
	ChangeCharacterAddressGroup(sld, "IslaMona_church", "goto", "tich"); /// ОПРЕДЕЛИТЬ ЛОКАТОР
	LAi_SetActorType(sld);
	if (GetCharacterIndex("Mirabella") != -1)
	{
		sld = characterFromId("Mirabella"); // Мирабель
		ChangeCharacterAddressGroup(sld, "IslaMona_church", "goto", "gladys"); /// ОПРЕДЕЛИТЬ ЛОКАТОР
		LAi_SetActorType(sld);
	}
	sld = characterFromId("Himenes_companion_1"); // колонист
	ChangeCharacterAddressGroup(sld, "IslaMona_church", "goto", "mayor3"); 
	LAi_SetActorType(sld);
	LAi_RemoveLoginTime(sld);
	sld = characterFromId("Himenes_companion_12"); // колонистка
	ChangeCharacterAddressGroup(sld, "IslaMona_church", "goto", "mayor2"); 
	LAi_SetActorType(sld);
	LAi_RemoveLoginTime(sld);
	
	for (int i=5; i<=8; i++) // 
	{
		sld = characterFromId("Himenes_companion_"+i);
		ChangeCharacterAddressGroup(sld, "IslaMona_church", "sit", "sit"+i); 
		LAi_SetActorType(sld);
		LAi_RemoveLoginTime(sld);
	}
	pchar.quest.islamona_church_celebre.win_condition.l1 = "location";
	pchar.quest.islamona_church_celebre.win_condition.l1.location = "IslaMona_church";
	pchar.quest.islamona_church_celebre.function = "IslaMona_ChurchCelebrarGo";
}

void IslaMona_ChurchCelebrarGo(string qName) // запускаем праздник в церкви
{
	if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
	{
		sld = characterFromId("Mary"); // Мэри
		ChangeCharacterAddressGroup(sld, "IslaMona_church", "goto", "girl"); 
		LAi_SetActorType(sld);
	}
	if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
	{
		sld = characterFromId("Helena"); // Элен
		ChangeCharacterAddressGroup(sld, "IslaMona_church", "goto", "girl"); 
		LAi_SetActorType(sld);
	}
	chrDisableReloadToLocation = true;//закрыть локацию
	LAi_SetActorType(pchar);
	LAi_ActorGoToLocator(pchar, "goto", "Charles", "IslaMona_ChurchCelebrarGo", -1); /// ОПРЕДЕЛИТЬ ЛОКАТОР ДЛЯ ГГ ЧТОБЫ ВСТАЛ КРАСИВО ДЛЯ РАЗГОВОРА СО ВСЕМИ
}

void IslaMona_ChurchTavernStandUp() // ГГ встает из-за стола, завершаем попойку в таверне
{
	LAi_Fade("", "");
	ChangeCharacterAddressGroup(pchar, "IslaMona_town", "goto", "goto10"); 
	LAi_SetPlayerType(pchar);
	if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) // есть Мэри
	{
		sld = characterFromId("Mary"); 
		sld.dialog.currentnode = "IslaMona_4";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		if (GetCharacterIndex("Mirabella") != -1)
		{
			sld = characterFromId("Mirabella");
			sld.dialog.currentnode = "mirabelle_52";
		}
		return;
	}
	if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) // есть Элен
	{
		sld = characterFromId("Helena"); 
		sld.dialog.currentnode = "IslaMona_4";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		if (GetCharacterIndex("Mirabella") != -1)
		{
			sld = characterFromId("Mirabella");
			sld.dialog.currentnode = "mirabelle_52";
		}
		return;
	}
	if (GetCharacterIndex("Mirabella") != -1) // есть Мирабель
	{
		sld = characterFromId("Mirabella");
		sld.dialog.currentnode = "mirabelle_48";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		return;
	}
	// никого нет - завершаем
	DoQuestFunctionDelay("IslaMona_ChurchReloadToRoom", 2.0);
}

void IslaMona_ChurchReloadToRoom(string qName) // ГГ в свою комнату
{
	int iTime, iAddTime; // ориентируем на утро
	iTime = sti(environment.time);
	if (iTime >= 21) iAddTime = 24 - iTime + 8;
	if (iTime < 7) iAddTime = 8 - iTime;
	if (iTime >= 7 && iTime < 21) iAddTime = 24  + 8 - iTime;
	StoreDayUpdate();
	WaitDate("",0,0,0,iAddtime,5);
	RecalculateJumpTable();
	RefreshWeather();
	RefreshLandTime();
	DoQuestReloadToLocation("IslaMona_TwoFloorRoom", "goto", "goto2", "IslaMona_ChurchReloadToRoom");
}

void IslaMona_ChurchNextMorning(string qName) // спустились наутро вниз таверны
{
	//chrDisableReloadToLocation = true;
	sld = characterFromId("Islamona_carpenter");
	sld.dialog.currentnode = "carpenter_17";
	ChangeCharacterAddressGroup(sld, "IslaMona_town", "barmen", "stay");
	LAi_SetBarmanType(sld);
	LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
	sld = characterFromId("Himenes");
	sld.dialog.currentnode = "Himenes_81";
	LAi_SetgroundSitType(sld);
	ChangeCharacterAddressGroup(sld, "IslaMona_town", "goto", "goto5"); /// НАЙТИ ЕМУ ЛОКАТОР ЧТОБЫ НА ПОЛУ КРАСИВО СИДЕЛ
	pchar.questTemp.IslaMona.TownStage = 3;
	if(CheckAttribute(pchar,"questTemp.IslaMonaDisableFantom")) DeleteAttribute(pchar,"questTemp.IslaMonaDisableFantom");
}

void IslaMona_ChurchSetHispanos() // ставим испанца в факторию
{
	sld = GetCharacter(NPC_GenerateCharacter("IM_spaofficer", "off_spa_5", "man", "man", 30, SPAIN, -1, true, "soldier"));
	FantomMakeCoolFighter(sld, 30, 90, 0, "", "", "", 50);
	sld.name = StringFromKey("IslaMona_10");
	sld.lastname = StringFromKey("IslaMona_11");
	sld.Dialog.Filename = "Quest\IslaMona_NPC.c";
	sld.dialog.currentnode = "SpaOfficer";
	ChangeCharacterAddressGroup(sld, "IslaMona_factoria", "goto", "goto2");
	LAi_SetStayType(sld);
}

void IslaMona_KillSpanish(string qName) // решил убить испанца
{
	LAi_LocationFightDisable(&Locations[FindLocation("IslaMona_factoria")], false);
	// если не надет пистоль или мушкет, то выдадим строевой -->
	if(!CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE) || !CheckAttribute(pchar,"equip."+MUSKET_ITEM_TYPE))
	{
		GiveItem2Character(pchar, "pistol1");
		EquipCharacterbyItem(pchar, "pistol1");
	}
	LAi_SetActorType(pchar);
	LAi_ActorAnimation(pchar, "Shot", "IslaMona_KillSpanish", 1.5);
}

void IslaMona_FinalPrepare() // 
{
	chrDisableReloadToLocation = false;
	pchar.quest.islamona_final_shore.win_condition.l1 = "location";
	pchar.quest.islamona_final_shore.win_condition.l1.location = "shore75";
	pchar.quest.islamona_final_shore.function = "IslaMona_FinalShore";
}

void IslaMona_FinalShore(string qName) // финальный разговор в бухте
{
    int n = FindLocation("IslaMona_town");
	locations[n].fastreload = "IslaMona";
	n = FindLocation("IslaMona_TwoFloorRoom");
	locations[n].fastreload = "IslaMona";
	n = FindLocation("IslaMona_church");
	locations[n].fastreload = "IslaMona";
	n = FindLocation("IslaMona_Jungle_01");
	locations[n].fastreload = "IslaMona";
	n = FindLocation("IslaMona_Jungle_02");
	locations[n].fastreload = "IslaMona";
	n = FindLocation("Shore75");
	locations[n].fastreload = "IslaMona";
	n = FindLocation("IslaMona_factoria");
	locations[n].fastreload = "IslaMona";
	n = FindLocation("IslaMona_factoria_residence");
	locations[n].fastreload = "IslaMona";
	RecalculateJumpTable();
	
	chrDisableReloadToLocation = true;
	sld = characterFromId("Islamona_carpenter");
	sld.dialog.currentnode = "IslaMona_103";
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, "shore75", "reload", "sea");
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	sld = characterFromId("Himenes");
	sld.dialog.currentnode = "Himenes_85";
	ChangeCharacterAddressGroup(sld, "shore75", "reload", "sea");
	LAi_SetActorType(sld);
	LAi_ActorFollow(sld, characterFromID("Islamona_carpenter"), "", 15.0);
	if (GetCharacterIndex("Mirabella") != -1)
	{
		if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") || CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) pchar.questTemp.IslaMona.MiraRodgar = "true";
	}
}

void IslaMona_FinalMayakSpanish(string qName) // высаживаем испанца на маяке
{
	pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу
	chrDisableReloadToLocation = true;
	sld = characterFromId("IM_spaofficer");
	sld.dialog.currentnode = "SpaOfficer_9";
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, "Mayak9", "goto", "goto2");
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	RemovePassenger(pchar, sld);
}

//=================================================================
//======================кейсы из quests_reaction===================
//=================================================================
bool IslaMona_QuestComplete(string sQuestName, string qname)
{

	ref sld;
	int i, n, iTime;
	
	bool condition = true;
	
	if (sQuestName == "IslaMona_HouseDialog") // в доме с Хименесом и Родгаром
	{
		if (GetCharacterIndex("Mirabella") != -1)
		{
			sld = characterFromId("Mirabella");
			ChangeCharacterAddressGroup(sld, "IslaMona_TwoFloorRoom", "goto", "goto4");
		}
		sld = characterFromId("Islamona_carpenter");
		ChangeCharacterAddressGroup(sld, "IslaMona_TwoFloorHouse", "goto", "goto3");
		LAi_SetActorType(sld);
		LAi_ActorTurnToLocator(sld, "goto", "goto5");
		sld = characterFromId("Himenes");
		sld.dialog.currentnode = "Himenes_44";
		ChangeCharacterAddressGroup(sld, "IslaMona_TwoFloorHouse", "goto", "goto2");
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
	}
	else if (sQuestName == "IslaMona_HarbourClear") // Хименеса и Родгара по местам после сдачи пристани
	{
		sld = characterFromId("Islamona_carpenter");
		if (CheckAttribute(pchar, "questTemp.IslaMona.Tavern") && pchar.questTemp.IslaMona.Tavern == "done") // таверна сдана
		{
			ChangeCharacterAddressGroup(sld, "IslaMona_town", "barmen", "stay");
			LAi_SetBarmanType(sld);
		}
		else
		{
			ChangeCharacterAddressGroup(sld, "IslaMona_town", "goto", "goto1");
			LAi_SetCitizenType(sld);
		}
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		sld = characterFromId("Himenes");
		if (CheckAttribute(pchar, "questTemp.IslaMona.Plantation") && pchar.questTemp.IslaMona.Plantation == "done") // фактория сдана
		{
			ChangeCharacterAddressGroup(sld, "IslaMona_factoria_residence", "sit", "sit1");
			LAi_SetHuberType(sld);
		}
		else
		{
			ChangeCharacterAddressGroup(sld, "IslaMona_town", "goto", "goto4");
			LAi_SetCitizenType(sld);
		}
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	else if (sQuestName == "IslaMona_PlantationHouse") // Хименеса прописываем в доме на фактории, Родгар гуляет, если не построена таверна
	{
		chrDisableReloadToLocation = false;
		sld = characterFromId("Himenes");
		LAi_SetHuberType(sld);
		LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
		sld = characterFromId("Islamona_carpenter");
		sld.dialog.currentnode = "carpenter_17";
		if (CheckAttribute(pchar, "questTemp.IslaMona.Tavern") && pchar.questTemp.IslaMona.Tavern == "done") // таверна сдана
		{
			ChangeCharacterAddressGroup(sld, "IslaMona_Town", "barmen", "stay");
			LAi_SetBarmanType(sld);
		}
		else
		{
			ChangeCharacterAddressGroup(sld, "IslaMona_Town", "reload", "reload5");
			LAi_SetCitizenType(sld);
		}
		LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
	}
	else if (sQuestName == "IslaMona_ReloadTavern") // перед сдачей таверны
	{
		DoQuestReloadToLocation("IslaMona_TwoFloorRoom", "goto", "goto4", "OpenTheDoors");
		//LocatorReloadEnterDisable("IslaMona_Town", "reload1_inside", true);
		//LocatorReloadEnterDisable("IslaMona_Town", "reload3_inside", true);
		sld = characterFromId("Himenes");
		sld.dialog.currentnode = "Himenes_72";
		if (CheckAttribute(pchar, "questTemp.IslaMona.Plantation") && pchar.questTemp.IslaMona.Plantation == "done") // фактория сдана
		{
			ChangeCharacterAddressGroup(sld, "IslaMona_factoria_residence", "sit", "sit1");
			LAi_SetHuberType(sld);
		}
		else
		{
			ChangeCharacterAddressGroup(sld, "IslaMona_town", "reload", "reload6");
			LAi_SetCitizenType(sld);
		}
		LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
		sld = characterFromId("Islamona_carpenter");
		sld.dialog.currentnode = "IslaMona_60";
		sld.greeting = "Rodgar_04";
		ChangeCharacterAddressGroup(sld, "IslaMona_town", "barmen", "stay");
		LAi_SetBarmanType(sld);
		LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
		// атрибуты таверны
		//n = Findlocation("IslaMona_town");
		//locations[n].fastreload = "IslaMona";
		// Мирабель в официантки
		if (GetCharacterIndex("Mirabella") != -1)
		{
			//pchar.quest.mtraxx_mirabella_life.over = "yes"; //снять прерывание на её поведение
			sld = characterFromId("Mirabella");
			ChangeCharacterAddressGroup(sld, "IslaMona_Town", "waitress", "barmen");
			LAi_SetWaitressType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
		}
	}
	else if (sQuestName == "IslaMona_DefReloadFactory") // релоад в захваченную факторию
	{
		LAi_LocationFightDisable(&Locations[FindLocation("Shore75")], false);
		LAi_LocationFightDisable(&Locations[FindLocation("IslaMona_factoria")], true);
		pchar.questTemp.IslaMona.Defend = "start";
		DoQuestReloadToLocation("IslaMona_factoria", "reload", "reload1", "IslaMona_DefInFactory");
	}
	else if (sQuestName == "IslaMona_DefInFactory") // диалог с офицером
	{
		sld = characterFromId("IM_fraofficer");
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 3.0);
	}
	else if (sQuestName == "IslaMona_DefKillCapral") // прибили капрала сразу - воевать самим на фактории, вот именно сюда и поставим Алонсо
	{
		LAi_SetPlayerType(pchar);
		sld = characterFromId("IM_soldier_1");
		LAi_KillCharacter(sld);
		pchar.questTemp.IslaMona.Defend = "start";
		pchar.questTemp.IslaMona.Defend.Force = "true";
		AddComplexSelfExpToScill(300, 300, 300, 300);
		Achievment_SetStat(95, 1);
		DoQuestCheckDelay("IslaMona_DefKillCapralAfter", 5.0);
	}
	else if (sQuestName == "IslaMona_DefKillCapralAfter") // 
	{
		AddQuestRecord("IslaMona", "17");
		DoQuestReloadToLocation("Shore75", "goto", "goto2", "IslaMona_DefForceArmy");
	}
	else if (sQuestName == "IslaMona_DefAttackLight") // французы атакуют без нас
	{
		for (i=1; i<=12; i++) 
		{
			sld = characterFromId("IM_soldier_"+i);
			ChangeCharacterAddressGroup(sld, "none", "", "");
		}
		for(i=1; i<=7; i++)
		{
			sld = characterFromId("IM_fra_sailor_"+i);
			ChangeCharacterAddressGroup(sld, "none", "", "");
		}
		DoQuestCheckDelay("IslaMona_DefAttackLight_1", 5.0);
	}
	else if (sQuestName == "IslaMona_DefAttackLight_1") //
	{
		PlaySound("interface\abordage_wining.wav");
		DoQuestCheckDelay("IslaMona_DefAttackLight_2", 5.0);
	}
	else if (sQuestName == "IslaMona_DefAttackLight_2") //
	{
		PlaySound("interface\boom.wav");
		DoQuestCheckDelay("IslaMona_DefAttackLight_3", 2.0);
	}
	else if (sQuestName == "IslaMona_DefAttackLight_3") //
	{
		PlaySound("Sea Battles\sdavl_kriki_002.wav");
		Log_Info(StringFromKey("IslaMona_12"));
		chrDisableReloadToLocation = false;
		LAi_LocationFightDisable(&Locations[FindLocation("IslaMona_jungle_01")], false);
		LocatorReloadEnterDisable("IslaMona_Jungle_01", "reload1_back", true);
		LocatorReloadEnterDisable("IslaMona_Jungle_01", "reload2_back", true);
		pchar.quest.islamona_def_Lbattle.win_condition.l1 = "location";
		pchar.quest.islamona_def_Lbattle.win_condition.l1.location = "IslaMona_town";
		pchar.quest.islamona_def_Lbattle.function = "IslaMona_DefBattleLight";
	}
	else if (sQuestName == "IslaMona_DefFraPrisoner") // решение по пленному французу на фактории
	{
		sld = characterFromId("Islamona_carpenter");
		sld.dialog.currentnode = "IslaMona_78";
		ChangeCharacterAddressGroup(sld, "IslaMona_factoria", "reload", "reload2"); /// ОПРЕДЕЛИТЬ ЛОКАТОР
		LAi_SetStayType(sld);
		/*for (i=1; i<=2; i++)
		{
			sld = characterFromId("Islamona_fort_pirate_"+i);
			ChangeCharacterAddressGroup(sld, "IslaMona_factoria", "goto", "goto"+i); /// ОПРЕДЕЛИТЬ ЛОКАТОР
			LAi_SetActorType(sld);
		} */
	}
	else if (sQuestName == "IslaMona_DefFraPrisonerFin") //
	{
		if (CheckAttribute(pchar, "questTemp.IslaMona.Fraprisoner")) IslaMona_DefBattleLightClear();
		else DoQuestCheckDelay("IslaMona_DefFraPrisonerShot", 3.0);
	}
	else if (sQuestName == "IslaMona_DefFraPrisonerShot") //
	{
		PlaySound("interface\MusketFire1.wav");
		IslaMona_DefBattleLightClear();
	}
	else if (sQuestName == "IslaMona_DefAttackCommonBattleEnd") // после боя совместного
	{
		LAi_group_Delete("EnemyFight");
		DoQuestCheckDelay("hide_weapon", 1.3);
		sld = characterFromId("Islamona_carpenter");
		sld.dialog.currentnode = "IslaMona_82";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		sld = characterFromId("Himenes");
		ChangeCharacterAddressGroup(sld, "IslaMona_town", "goto", "goto3"); /// ПЕРЕСТАВИТЬ ХИМЕНЕСА ЗА ВОРОТА ЧТОБЫ МОГ ПОДОЙТИ, ОПРЕДЕЛИТЬ ЛОКАТОР
		// роту убираем
		sld = characterFromId("Alonso");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
		sld.lifeday = 0;
		for (i=1; i<=5; i++) 
		{
			sld = characterFromId("IM_our_soldier_"+i);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
			sld.lifeday = 0;
		}
	}
	else if (sQuestName == "IslaMona_DefCheckJungleAfterFight") // после боя при неоплате дублонов
	{
		chrDisableReloadToLocation = false;
		AddQuestRecord("IslaMona", "20");
	}
	else if (sQuestName == "IslaMona_DefForceArmy") // абордажная рота в случае нападения на капрала сразу
	{
		DoQuestFunctionDelay("IslaMona_DefAttackCommonArmy", 2.0);
	}
	else if (sQuestName == "IslaMona_DefAttackForceEnd") // завершили бой на фактории
	{
		LAi_group_Delete("EnemyFight");
		DoQuestCheckDelay("hide_weapon", 1.3);
		chrDisableReloadToLocation = false;
		LAi_LocationFightDisable(&Locations[FindLocation("IslaMona_factoria")], true);
		LocatorReloadEnterDisable("IslaMona_Jungle_01", "reload3_back", false);
		// роту убираем
		sld = characterFromId("Alonso");
		sld.lifeday = 0;
		for (i=1; i<=5; i++) 
		{
			sld = characterFromId("IM_our_soldier_"+i);
			sld.lifeday = 0;
		}
		pchar.quest.islamona_def_town.win_condition.l1 = "locator";
		pchar.quest.islamona_def_town.win_condition.l1.location = "IslaMona_Town";
		pchar.quest.islamona_def_town.win_condition.l1.locator_group = "quest";
		pchar.quest.islamona_def_town.win_condition.l1.locator = "detector1"; 
		pchar.quest.islamona_def_town.function = "IslaMona_DefInTown"; // на наших поселенцев
		AddQuestRecord("IslaMona", "20_1");
	}
	else if (sQuestName == "IslaMona_ChurchCelebrarGo") // запускаем праздник в церкви
	{
		LAi_SetPlayerType(pchar);
		sld = characterFromId("Himenes");
		sld.greeting = "Himenes_04";
		sld.dialog.currentnode = "Himenes_church_29";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
	}
	else if (sQuestName == "IslaMona_ChurchToTavern") // переносим в таверну
	{
		FreeSitLocator("IslaMona_town", "sit_front1");
		LAi_SetSitType(pchar);
		sld = characterFromId("Himenes");
		sld.dialog.currentnode = "Himenes_74";
		FreeSitLocator("IslaMona_town", "sit_front3");
		ChangeCharacterAddressGroup(sld, "IslaMona_Town", "sit", "sit_front3");
		LAi_ActorSetSitMode(sld);
		sld = characterFromId("Islamona_carpenter");
		sld.dialog.currentnode = "IslaMona_88";
		FreeSitLocator("IslaMona_town", "sit_front2");
		ChangeCharacterAddressGroup(sld, "IslaMona_Town", "sit", "sit_front2");
		LAi_ActorSetSitMode(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		// бомонд из церкви переводим
		if (GetCharacterIndex("Mirabella") != -1)
		{
			sld = characterFromId("Mirabella");
			sld.dialog.currentnode = "mirabelle_42";
			ChangeCharacterAddressGroup(sld, "IslaMona_Town", "waitress", "barmen");
			LAi_SetWaitressType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
		}
		for (i=1; i<=12; i++)
		{
			sld = characterFromId("Himenes_companion_"+i);
			ChangeCharacterAddressGroup(sld, "IslaMona_fort", "goto", "goto"+i); /// ОПРЕДЕЛИТЬ ЛОКАТОРЫ
			LAi_SetCitizenType(sld);
			LAi_SetLoginTime(sld, 6.0, 22.0);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
		if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
		{
			sld = characterFromId("Mary"); // Мэри
			ChangeCharacterAddressGroup(sld, "IslaMona_Town", "goto", "goto2"); /// ОПРЕДЕЛИТЬ ЛОКАТОР
			LAi_SetOfficerType(sld);
		}
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
		{
			sld = characterFromId("Helena"); // Элен
			ChangeCharacterAddressGroup(sld, "IslaMona_Town", "goto", "goto2"); /// ОПРЕДЕЛИТЬ ЛОКАТОР
			LAi_SetOfficerType(sld);
		}
	}
	else if (sQuestName == "IslaMona_ChurchTavernExit") // закончили службу
	{
		bDisableCharacterMenu = false;
		InterfaceStates.Buttons.Save.enable = true;
		DeleteAttribute(pchar, "GenQuest.FrameLockEsc");
		locCameraResetState();
		iTime = sti(environment.time);
		WaitDate("", 0, 0, 0, 3, 5); //крутим время
		RecalculateJumpTable();
		StoreDayUpdate();
		RefreshWeather();
		RefreshLandTime();
		LAi_SetPlayerType(pchar);
		DoQuestReloadToLocation("IslaMona_Town", "sit", "sit_base2", "IslaMona_ChurchToTavern"); /// ОПРЕДЕЛИТЬ ЛОКАТОР
	}
	else if (sQuestName == "IslaMona_CardsGameRes") // результаты игры
	{
		sld = characterFromId("Islamona_carpenter");
		sld.dialog.currentnode = "IslaMona_99";
		LAi_ActorSetSitMode(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 0.5);
	}
	else if (sQuestName == "IslaMona_ChurchReloadToRoom") // в комнате наутро
	{
		if (!CheckAttribute(pchar, "questTemp.IslaMona.Doorlock")) chrDisableReloadToLocation = false;
		else DeleteAttribute(pchar, "questTemp.IslaMona.Doorlock");
		if (CheckAttribute(pchar, "questTemp.IslaMona.Mirabelle"))
		{
			sld = characterFromId("Mirabella");
			ChangeCharacterAddressGroup(sld, "IslaMona_TwoFloorRoom", "goto", "goto4");
			DoQuestFunctionDelay("Mtraxx_MirabellaSex", 1.5);
			DeleteAttribute(pchar, "questTemp.IslaMona.Mirabelle");
		}
		pchar.quest.islamona_church_room.win_condition.l1 = "location";
		pchar.quest.islamona_church_room.win_condition.l1.location = "IslaMona_Town";
		pchar.quest.islamona_church_room.function = "IslaMona_ChurchNextMorning";
		AddQuestRecord("IslaMona", "26");
	}
	else if (sQuestName == "IslaMona_KillSpanish") // решил убить испанца
	{
		LAi_SetPlayerType(pchar);
		sld = characterFromId("IM_spaofficer");
		LAi_KillCharacter(sld);
		AddQuestRecord("IslaMona", "27");
		LAi_LocationFightDisable(&Locations[FindLocation("IslaMona_factoria_residence")], true);
		ChangeCharacterComplexReputation(pchar, "nobility", -6);
		Achievment_SetStat(95, 1);
		IslaMona_FinalPrepare();
	}
	else if (sQuestName == "IslaMona_Final") // финал, всех по местам, ГГ выпустить
	{
		sld = characterFromId("Islamona_carpenter");
		sld.dialog.currentnode = "carpenter_17";
		sld.greeting = "Rodgar_04";
		ChangeCharacterAddressGroup(sld, "IslaMona_Town", "barmen", "stay");
		LAi_SetBarmanType(sld);
		LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
		sld = characterFromId("Himenes");
		sld.dialog.currentnode = "Himenes_72";
		sld.greeting = "Himenes_03";
		ChangeCharacterAddressGroup(sld, "IslaMona_factoria_residence", "sit", "sit1");
		LAi_SetHuberType(sld);
		LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
		DeleteAttribute(pchar, "questTemp.IslaMona.MiraRodgar");
		chrDisableReloadToLocation = false;
		bQuestDisableMapEnter = false;//открыть карту
		DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		ref rIsl = GetIslandByIndex(FindIslandBySeaLocation("shore75"));
		rIsl.reload.l2.go = "shore76";
		rIsl.reload.l2.emerge = "sea";
		rIsl.reload.l2.radius = 600.0;
		Island_SetReloadEnableLocal("IslaMona", "reload_2", true);
		Island_SetReloadEnableLocal("IslaMona", "reload_3", true);
		rIsl = &locations[FindLocation("Shore76")];
		rIsl.reload.l2.name = "boat";
		rIsl.reload.l2.go = "IslaMona";
		rIsl.reload.l2.emerge = "reload_2";
		rIsl.reload.l2.autoreload = "0";
		rIsl.reload.l2.label = "Sea";
		rIsl.locators_radius.reload.boat = 12.0;
		if (!CheckAttribute(pchar, "questTemp.IslaMona.Mayak")) CloseQuestHeader("IslaMona");
	}
	else if (sQuestName == "IslaMona_MirabelleKiss") // Sinistra катсцена с поцелуями
	{
		locCameraFromToPos(-1.48, 1.84, -0.86, true, -3.61, -0.20, -2.41);
		//if(CheckAttribute (pchar, "IsMushketer")) SetMainCharacterToMushketer("", false);
		TeleportCharacterToPosAy(pchar, -3.60, 0.00, -2.20, 3.00);
		LAi_SetActorType(pchar);
		LAi_ActorAnimation(pchar, "kiss", "1", 5.5);
		sld = characterFromId("Mirabella");
		ChangeCharacterAddressGroup(sld, "IslaMona_TwoFloorRoom", "goto", "goto4");
		sld.model.animation = "woman";
		Characters_RefreshModel(sld);
		TeleportCharacterToPosAy(sld, -3.60, 0.00, -2.80, 0.00);
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "kiss", "1", 5.5);
		if(CheckAttribute(pchar,"questTemp.Mtraxx.MirabellaFirstTimeKiss")) 
		{
			DoQuestCheckDelay("IslaMona_MirabelleKiss_2", 5.5);
			DeleteAttribute(pchar,"questTemp.Mtraxx.MirabellaFirstTimeKiss");
		}
		else DoQuestFunctionDelay("Mtraxx_MirabellaSex", 5.5);
	}
	else if (sQuestName == "IslaMona_MirabelleKiss_2")
	{
		ChangeCharacterComplexReputation(pchar,"nobility", -1);
		pchar.GenQuest.FrameLockEsc = true;
		ResetSound();
		WaitDate("", 0, 0, 0, 2, 30);
		SetLaunchFrameFormParam("", "", 0, 12);
		SetLaunchFrameFormPic("loading\inside\censored1.tga");
		PlayStereoSound("sex\sex10.wav");
		LaunchFrameForm();
		if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	
		{
			AddCharacterHealth(pchar, 10);
			AddCharacterMaxHealth(pchar, 1.0);
		}
		else AddCharacterHealth(pchar, 5);
		LAi_SetCurHPMax(pchar);
		DoQuestFunctionDelay("Mtraxx_PasqualeMirabellaSex", 12.0);
		ChangeCharacterAddressGroup(pchar, "IslaMona_TwoFloorRoom", "goto", "goto2");
		sld = characterFromId("Mirabella");
		ChangeCharacterAddressGroup(sld, "IslaMona_TwoFloorRoom", "goto", "goto4");
	}
	else
	{
		condition = false;
	}
	
	return condition;
}