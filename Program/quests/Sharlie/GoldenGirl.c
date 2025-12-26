/// Jason ----------------------------------------------------------- Дороже золота ------------------------------------------------------------------
void GoldenGirl_Start(string qName) // инициализация
{
	// проверка на наличие Элен или Мэри
	if (!GoldenGirl_CheckGirls())
	{
		if(CheckAttribute(pchar,"quest.GoldenGirl_Start.over"))
			DeleteAttribute(pchar,"quest.GoldenGirl_Start.over");
		SetFunctionTimerCondition("GoldenGirl_Start", 0, 0, 1, false);
		log_Testinfo("Отложен квест Дороже золота");
		return;
	}
	log_Testinfo("Стартовал квест Дороже золота");
	// запускаем слухи
	AddSimpleRumour(StringFromKey("GoldenGirl_1"), FRANCE, 180, 5);
	AddSimpleRumour(StringFromKey("GoldenGirl_2"), FRANCE, 180, 5);
	AddSimpleRumour(StringFromKey("GoldenGirl_3"), FRANCE, 180, 5);
	
	LocatorReloadEnterDisable("FortFrance_town", "reload91", false); // fix 22-03-20 открыть боковой вход если закрыт (Captain Beltrop, 19.02.2021, правка в названии локатора)
	// меняем внутрянку гостиной борделя
	int n = Findlocation("FortFrance_SecBrRoom");
	locations[n].image = "loading\inside\BigHouseBack.tga";
	locations[n].filespath.models = "locations\inside\BigHouseBack";
	locations[n].models.always.house = "BigHouseBack";
	locations[n].models.always.house.level = 65538;
	locations[n].models.always.window = "BigHouseBack_windows";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.always.back = "..\inside_back3";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "BigHouseBack_patch";
	locations[n].models.day.locators = "BigHouseBack_locators";
	//Night
	locations[n].models.night.charactersPatch = "BigHouseBack_patch";
	locations[n].models.night.locators = "BigHouseBack_locators";
	locations[n].box1.QuestClosed = true;
	locations[n].box2.QuestClosed = true;
	locations[n].box3.QuestClosed = true;
	locations[n].DisableOfficers = "1";
	LAi_LocationFightDisable(&locations[n], true);
	// добавляем вход в ещё одну комнату
	locations[n].reload.l3.name = "reload3";
	locations[n].reload.l3.go = "Location_reserve_02";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Brothel";
	LocatorReloadEnterDisable("FortFrance_SecBrRoom", "reload3", true);
	
	// добавляем ещё одну комнату
	n = Findlocation("Location_reserve_02");
	locations[n].image = "loading\inside\BigHouse04.tga";
	//Always
	locations[n].filespath.models = "locations\Inside\BigHouse04";
	locations[n].models.always.room = "BigHouse04";
	locations[n].models.always.room.level = 65538;
	locations[n].models.always.windows = "BigHouse04_windows";
	locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;
	locations[n].models.always.back = "..\inside_back3";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "BigHouse04_patch";
	locations[n].models.day.locators = "BigHouse04_locators";
	//Night
	locations[n].models.night.charactersPatch = "BigHouse04_patch";
	locations[n].models.night.locators = "BigHouse04_Nlocators";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "FortFrance_SecBrRoom";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Room";
	locations[n].DisableOfficers = "1";
	LAi_LocationFightDisable(&locations[n], true);
	
	// создаем маркизу Бото
	sld = GetCharacter(NPC_GenerateCharacter("Julianna", "Marquesa", "woman", "towngirl", 1, FRANCE, -1, false, "quest"));
	sld.name = StringFromKey("GoldenGirl_4");
	sld.lastname = StringFromKey("GoldenGirl_5");
	sld.greeting = "Marquesa_kakayavstrecha";
    sld.Dialog.Filename = "Quest\GoldenGirl.c";
	sld.dialog.currentnode = "Julianna";
	sld.rank = 1;
	LAi_SetHP(sld, 50, 50); 
	SetSelfSkill(sld, 1, 1, 1, 1, 50);
	SetShipSkill(sld, 90, 50, 1, 1, 1, 1, 1, 1, 50);
	SetSPECIAL(sld, 3, 8, 4, 8, 6, 4, 9);
	LAi_SetImmortal(sld, true);
	LAi_SetStayType(sld);
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	// создаем Ангеррана Шиво
	sld = GetCharacter(NPC_GenerateCharacter("Angerran", "Angerran", "man", "man", 1, FRANCE, -1, false, "quest"));
	sld.name = StringFromKey("GoldenGirl_6");
	sld.lastname = StringFromKey("GoldenGirl_7");
	sld.greeting = "Angerran_ne_po_chinu";
    sld.Dialog.Filename = "Quest\GoldenGirl.c";
	sld.dialog.currentnode = "Angerran";
	sld.rank = 35;
	LAi_SetHP(sld, 600, 600); 
	SetSelfSkill(sld, 70, 95, 70, 90, 90);
	SetShipSkill(sld, 20, 70, 80, 80, 80, 70, 70, 70, 70);
	SetSPECIAL(sld, 8, 4, 8, 6, 6, 10, 6);
	SetCharacterPerk(sld, "Energaiser");
	SetCharacterPerk(sld, "BasicDefense");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "Gunman");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "HardHitter");

	SetCharacterPerk(sld, "ShipSpeedUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");

	SetCharacterPerk(sld, "WindCatcher");
	SetCharacterPerk(sld, "SailsMan");
	SetCharacterPerk(sld, "Doctor1");
	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterPerk(sld, "LongRangeGrappling");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "BasicCommerce");
	SetCharacterPerk(sld, "AdvancedCommerce");
	GiveItem2Character(sld, "blade_19");
	sld.equip.blade = "blade_19";
	GiveItem2Character(sld, "pistol6");
	EquipCharacterbyItem(sld, "pistol6");
	LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
    TakeNItems(sld, "bullet", 50);
	AddItems(sld, "gunpowder", 50);
	TakeNItems(sld, "potion2", MOD_SKILL_ENEMY_RATE/2);
	TakeNItems(sld, "potion3", 5);
	sld.cirassId = Items_FindItemIdx("cirass1"); 
	LAi_SetImmortal(sld, true);
	sld.SuperShooter = true;
	sld.MultiFighter = 1.0 + stf(MOD_SKILL_ENEMY_RATE/10);
	sld.MultiShooter = 1.0 + stf(MOD_SKILL_ENEMY_RATE/10);
	LAi_SetStayType(sld);
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	// создаем баронета Кортни
	sld = GetCharacter(NPC_GenerateCharacter("Cortny", "Baronet_1", "man", "man", 1, FRANCE, -1, false, "quest"));
	sld.name = StringFromKey("GoldenGirl_8");
	sld.lastname = StringFromKey("GoldenGirl_9");
	sld.greeting = "";
    sld.Dialog.Filename = "Quest\GoldenGirl.c";
	sld.dialog.currentnode = "Cortny";
	sld.rank = 32;
	LAi_SetHP(sld, 400, 400); 
	SetSelfSkill(sld, 90, 70, 70, 85, 70);
	SetShipSkill(sld, 70, 65, 85, 75, 80, 85, 65, 75, 75);
	SetSPECIAL(sld, 7, 5, 8, 7, 6, 8, 7);
	SetCharacterPerk(sld, "Energaiser");
	SetCharacterPerk(sld, "BasicDefense");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "Gunman");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "HardHitter");

	SetCharacterPerk(sld, "ShipSpeedUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");

	SetCharacterPerk(sld, "WindCatcher");
	SetCharacterPerk(sld, "SailsMan");
	SetCharacterPerk(sld, "Doctor1");
	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterPerk(sld, "LongRangeGrappling");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "BasicCommerce");
	GiveItem2Character(sld, "blade_18");
	sld.equip.blade = "blade_18";
	GiveItem2Character(sld, "pistol5");
	EquipCharacterbyItem(sld, "pistol5");
	LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
    TakeNItems(sld, "bullet", 50);
	AddItems(sld, "gunpowder", 50);
	TakeNItems(sld, "potion2", MOD_SKILL_ENEMY_RATE/2);
	TakeNItems(sld, "potion3", 5);
	sld.cirassId = Items_FindItemIdx("cirass1"); 
	sld.SuperShooter = true;
	sld.MultiFighter = 1.0 + stf(MOD_SKILL_ENEMY_RATE/10);
	sld.MultiShooter = 1.0 + stf(MOD_SKILL_ENEMY_RATE/10);
	LAi_SetStayType(sld);
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	//запуск ативной части
	SetFunctionTimerCondition("GoldenGirl_FortFrance", 0, 0, 30, false); // таймер
	pchar.questTemp.GoldenGirl = "start";
}

void GoldenGirl_FortFrance(string qName) // на Сен-Пьер
{
	pchar.quest.GoldenGirl_go.win_condition.l1 = "location";
	pchar.quest.GoldenGirl_go.win_condition.l1.location = "FortFrance_town";
	pchar.quest.GoldenGirl_go.function = "GoldenGirl_Message";
}

void GoldenGirl_Message(string qName) // вестовой в Сен-Пьере
{
	// проверка на наличие Элен или Мэри
	if (CheckAttribute(pchar, "questTemp.GoldenGirl_Ready") && !CheckAttribute(pchar, "questTemp.GoldenGirl_Block"))
	{
		chrDisableReloadToLocation = true;//закрыть локацию
		DeleteQuestCondition("GoldenGirl_FortFrance");
		DeleteQuestCondition("GoldenGirl_go");
		sld = GetCharacter(NPC_GenerateCharacter("GoldenGirl_FraOfficer", "off_fra_1", "man", "man", 25, FRANCE, -1, true, "quest"));
		FantomMakeCoolFighter(sld, 25, 60, 60, "blade_10", "pistol5", "bullet", 100);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		sld.Dialog.Filename = "Quest\GoldenGirl.c";
		sld.dialog.currentnode = "fraofficer";
		ChangeCharacterAddressGroup(sld, "FortFrance_town", "quest", "quest1");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	else
	{
		SetFunctionTimerCondition("GoldenGirl_FortFrance", 0, 0, 7, true); // таймер
	}
}

void GoldenGirl_GirlAngry(string qName) // ссора с подругой
{
	chrDisableReloadToLocation = true;//закрыть локацию
	if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
	else sld = characterFromId("Mary");
	sld.dialog.currentnode = "GoldenGirl";
	LAi_SetActorType(sld);
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void GoldenGirl_BrothelDoor(string qName) // закрываем центральный вход в бордель и убираем Аврору
{
	LocatorReloadEnterDisable("FortFrance_town", "reload91", false); // fix 22-03-20 открыть боковой вход если закрыт (Captain Beltrop, 19.02.2021, правка в названии локатора)
	sld = characterFromId("FortFrance_Hostess");
	ChangeCharacterAddressGroup(sld, "none", "", "");
}

void GoldenGirl_TimeOver(string qName) // не пришли на встречу с мадам Бото
{
	pchar.quest.GoldenGirl_bronca.over = "yes"; //снять прерывание
	pchar.quest.GoldenGirl_eventstart.over = "yes"; //снять прерывание
	LAi_LocationDisableOfficersGen("FortFrance_townhall", false);//офицеров пускать
	DoQuestFunctionDelay("GoldenGirl_BrothelNorm", 0.5);
	LocatorReloadEnterDisable("FortFrance_town", "reload1_back", false);
	LocatorReloadEnterDisable("FortFrance_town", "reload2_back", false);
	LocatorReloadEnterDisable("FortFrance_town", "gate_back", false);//открыть выходы из города
	pchar.questTemp.GoldenGirl = "start_fail"; // fix 22-03-20
	AddQuestRecord("GoldenGirl", "3");
	CloseQuestHeader("GoldenGirl");
}

void GoldenGirl_BrothelNorm(string qName) // 
{
	LocatorReloadEnterDisable("FortFrance_town", "reload9_back", false); // бордель - открыть, Аврору на место
	LocatorReloadEnterDisable("FortFrance_town", "reload91", false); // Captain Beltrop, 19.02.2021, правка в названии локатора
	sld = characterFromId("FortFrance_Hostess");
	ChangeCharacterAddressGroup(sld, "FortFrance_SecBrRoom", "barmen", "stay");
	if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena"))
	{
		sld = characterFromId("Helena");
		sld.dialog.currentnode = "Helena_officer";
		DeleteAttribute(pchar, "questTemp.GoldenGirl.Helena");
	}
	else 
	{
		sld = characterFromId("Mary");
		sld.dialog.currentnode = "Mary_officer";
		DeleteAttribute(pchar, "questTemp.GoldenGirl.Mary");
	}
}

void GoldenGirl_Party(string qName) // на приеме у мадам Бото
{
	pchar.quest.GoldenGirl_TimeOver.over = "yes"; //снять прерывание
	// запереть локаторы выхода из комнаты борделя
	LocatorReloadEnterDisable("FortFrance_SecBrRoom", "reload1", true);
	LocatorReloadEnterDisable("FortFrance_SecBrRoom", "reload2", true);
	LocatorReloadEnterDisable("FortFrance_SecBrRoom", "reload3", true);
	bDisableFastReload = true;//закрыть переход
	pchar.GenQuest.CannotWait = true;//запрет ожидания
	// ставим Бото, Шиво и губернатора, определить локаторы 
	sld = characterFromId("Julianna");
	ChangeCharacterAddressGroup(sld, "FortFrance_SecBrRoom", "barmen", "bar1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	sld = characterFromId("Angerran");
	ChangeCharacterAddressGroup(sld, "FortFrance_SecBrRoom", "quest", "quest2");
	sld = characterFromId("FortFrance_Mayor");
	sld.Dialog.Filename = "Quest\GoldenGirl.c";
	sld.Dialog.currentnode = "governor";
	ChangeCharacterAddressGroup(sld, "FortFrance_SecBrRoom", "quest", "quest3");
	LAi_SetStayType(sld);
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	// добавить 5 статистов
	// 1
	sld = GetCharacter(NPC_GenerateCharacter("GG_statist1", "banker_9", "man", "man", 10, FRANCE, -1, true, "quest"));
	FantomMakeCoolFighter(sld, 10, 60, 60, "blade_10", "pistol5", "bullet", 100);
	sld.Dialog.Filename = "Quest\GoldenGirl.c";
	sld.dialog.currentnode = "statist_1";
    ChangeCharacterAddressGroup(sld, "FortFrance_SecBrRoom", "goto", "goto1");
	LAi_SetOwnerType(sld);
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	// 2
	sld = GetCharacter(NPC_GenerateCharacter("GG_statist2", "huber_13", "man", "man", 10, FRANCE, -1, true, "quest"));
	FantomMakeCoolFighter(sld, 10, 60, 60, "blade_15", "pistol5", "bullet", 100);
	sld.Dialog.Filename = "Quest\GoldenGirl.c";
	sld.dialog.currentnode = "statist_2";
    ChangeCharacterAddressGroup(sld, "FortFrance_SecBrRoom", "goto", "goto4");
	LAi_SetStayType(sld);
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	// 3
	sld = GetCharacter(NPC_GenerateCharacter("GG_statist3", "mercen_21", "man", "man", 10, FRANCE, -1, true, "quest"));
	FantomMakeCoolFighter(sld, 10, 60, 60, "blade_16", "pistol6", "bullet", 100);
	sld.Dialog.Filename = "Quest\GoldenGirl.c";
	sld.dialog.currentnode = "statist_3";
    ChangeCharacterAddressGroup(sld, "FortFrance_SecBrRoom", "goto", "goto7");
	LAi_SetStayType(sld);
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	// 4
	sld = GetCharacter(NPC_GenerateCharacter("GG_statist4", "banker_8_1", "man", "man", 10, FRANCE, -1, true, "quest"));
	FantomMakeCoolFighter(sld, 10, 60, 60, "blade_20", "pistol5", "bullet", 100);
	sld.Dialog.Filename = "Quest\GoldenGirl.c";
	sld.dialog.currentnode = "statist_4";
    ChangeCharacterAddressGroup(sld, "FortFrance_SecBrRoom", "goto", "goto6");
	LAi_SetStayType(sld);
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	// 5
	sld = GetCharacter(NPC_GenerateCharacter("GG_statist5", "citiz_1", "man", "man", 10, FRANCE, -1, true, "quest"));
	FantomMakeCoolFighter(sld, 10, 60, 60, "blade_19", "pistol5", "bullet", 100);
	sld.Dialog.Filename = "Quest\GoldenGirl.c";
	sld.dialog.currentnode = "statist_5";
    ChangeCharacterAddressGroup(sld, "FortFrance_SecBrRoom", "sit", "sit1");
	LAi_SetHuberType(sld);
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
}

void GoldenGirl_CardsFail() // проигрыш в карты
{
	sld = characterFromId("FortFrance_Mayor");
	sld.Dialog.Filename = "Common_Mayor.c";
	sld.Dialog.currentnode = "First time";
	ChangeCharacterAddressGroup(sld, "FortFrance_townhall", "sit", "sit1");
	LAi_SetHuberType(sld);
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	sld = characterFromId("Julianna");
	sld.lifeday = 0;
	sld = characterFromId("Angerran");
	sld.lifeday = 0;
	// тут же убрать всех статистов
	for (int i=1; i<=5; i++)
	{
		sld = characterFromId("GG_statist"+i);
		sld.lifeday = 0;
	}
	LocatorReloadEnterDisable("FortFrance_town", "reload9_back", true);
	LocatorReloadEnterDisable("FortFrance_town", "reload91", true); // Captain Beltrop, 19.02.2021, правка в названии локатора
	DoQuestReloadToLocation("FortFrance_town", "reload", "reload1", "");
	SetFunctionTimerCondition("GoldenGirl_BrothelNorm", 0, 0, 1, false); // таймер
	DeleteAttribute(pchar, "questTemp.GoldenGirl.Game");
	if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena"))
	{
		sld = characterFromId("Helena");
		sld.dialog.currentnode = "Helena_officer";
		DeleteAttribute(pchar, "questTemp.GoldenGirl.Helena");
	}
	else 
	{
		sld = characterFromId("Mary");
		sld.dialog.currentnode = "Mary_officer";
		DeleteAttribute(pchar, "questTemp.GoldenGirl.Mary");
	}
	LocatorReloadEnterDisable("FortFrance_town", "reload1_back", false);
	LocatorReloadEnterDisable("FortFrance_town", "reload2_back", false);
	LocatorReloadEnterDisable("FortFrance_town", "gate_back", false);//открыть выходы из города
	LocatorReloadEnterDisable("FortFrance_SecBrRoom", "reload1", false);
	LocatorReloadEnterDisable("FortFrance_SecBrRoom", "reload2", false);
	LocatorReloadEnterDisable("FortFrance_SecBrRoom", "reload3", false);
	bDisableFastReload = false; // все открыть
	DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
	LAi_LocationDisableOfficersGen("FortFrance_townhall", false);//офицеров пускать
	AddQuestRecord("GoldenGirl", "5");
	CloseQuestHeader("GoldenGirl");
	pchar.questTemp.GoldenGirl = "cards_fail";
}

void GoldenGirl_CreateCaptainMoreno() // ставим "капитана Морено"
{
	DeleteAttribute(pchar, "questTemp.GoldenGirl.Game");
	int ch;
	if (CheckAttribute(pchar, "questTemp.Portugal")) // был квест
	{
		if (CheckAttribute(pchar, "questTemp.Portugal.GG1")) ch = 1;
		else ch = 2;
	}
	else ch = 2;
	
	if (ch == 1)
	{
		sld = GetCharacter(NPC_GenerateCharacter("GG_Moreno", "Port_B", "man", "man", 35, FRANCE, -1, true, "quest"));
		sld.name = StringFromKey("GoldenGirl_10");
		sld.lastname = StringFromKey("GoldenGirl_11");
	}
	else
	{
		sld = GetCharacter(NPC_GenerateCharacter("GG_Moreno", "Vasces", "man", "man", 35, FRANCE, -1, true, "quest"));
		sld.name = StringFromKey("GoldenGirl_12");
		sld.lastname = StringFromKey("GoldenGirl_13");
	}
	FantomMakeCoolFighter(sld, 35, 100, 100, "blade_20", "pistol5", "bullet", 200);
	ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload2");
	sld.Dialog.Filename = "Quest\GoldenGirl.c";
	sld.dialog.currentnode = "moreno";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void GoldenGirl_SleepInBrothel() // 
{
	DeleteAttribute(pchar, "questTemp.GoldenGirl.Game");
	bDisableFastReload = false; // все открыть
	DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
	// тут же убрать всех статистов
	for (int i=1; i<=5; i++)
	{
		sld = characterFromId("GG_statist"+i);
		sld.lifeday = 0;
	}
	// губера к себе в резиденцию
	sld = characterFromId("FortFrance_Mayor");
	sld.Dialog.currentnode = "governor_14";
	ChangeCharacterAddressGroup(sld, "FortFrance_townhall", "sit", "sit1");
	LAi_SetHuberType(sld);
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	// ориентируем на день
	int iTime, iAddTime;
	iTime = sti(environment.time);
	if (iTime >= 21) iAddTime = 24 - iTime + 12;
	if (iTime < 7) iAddTime = 12 - iTime;
	if (iTime >= 7 && iTime < 21) iAddTime = 24  + 12 - iTime;
	StoreDayUpdate();
	WaitDate("",0,0,0,iAddtime,5);
	RecalculateJumpTable();
	RefreshWeather();
	RefreshLandTime();
	DoQuestReloadToLocation("FortFrance_Brothel_room", "goto", "goto1", "GoldenGirl_AfterCardsGames");
	LocatorReloadEnterDisable("FortFrance_Brothel", "reload1_back", true); // закрыть выход на улицу
	AddQuestRecord("GoldenGirl", "6");
	pchar.questTemp.GoldenGirl = "cards_win";
}

void GoldenGirl_ToGovernor() // 
{
	sld = characterFromId("Julianna");
	sld.dialog.currentnode = "Julianna_46";
	LocatorReloadEnterDisable("FortFrance_town", "reload91", true); // закрыть вход в бордель сбоку
	LocatorReloadEnterDisable("FortFrance_town", "reload9", true); // закрыть основной вход в бордель fix 08-04-20
	DoQuestReloadToLocation("FortFrance_townhall", "reload", "reload1", "");
	chrDisableReloadToLocation = true;//закрыть локацию
}

void GoldenGirl_GovernorOut() // 
{
	sld = characterFromId("FortFrance_Mayor");
	sld.Dialog.Filename = "Common_Mayor.c";
	sld.Dialog.currentnode = "First time";
	LocatorReloadEnterDisable("FortFrance_town", "reload3_back", true); // закрыть вход в резиденцию
	DoQuestReloadToLocation("FortFrance_town", "reload", "reload3", "GoldenGirl_GirlShip");
	chrDisableReloadToLocation = false; //открыть локацию
}

void GoldenGirl_DuelPrepare(string qName) // подготовка к дуэли
{
	LocatorReloadEnterDisable("FortFrance_town", "reload9", false); // открыть основной вход в бордель fix 08-04-20
	LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_ExitTown")], true);//запретить драться
	LAi_LocationDisableOfficersGen("FortFrance_ExitTown", true);//офицеров не пускать
	locations[FindLocation("FortFrance_ExitTown")].DisableEncounters = true; //энкаутеры закрыть
	// создаем двух секундантов ГГ
	for (int i=1; i<=2; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("GG_SecundantGG_"+i, "off_fra_"+i, "man", "man", 30, FRANCE, -1, true, "quest"));
		FantomMakeCoolFighter(sld, 35, 70, 70, "blade_15", "pistol5", "bullet", 180);
		if (i==1)
		{
			sld.Dialog.Filename = "Quest\GoldenGirl.c";
			sld.dialog.currentnode = "secundant";
		}
		ChangeCharacterAddressGroup(sld, "FortFrance_ExitTown", "goto", "goto"+(7+i));
		LAi_SetActorType(sld);
		sld.LSC_clan = true;
	}
	// создаем двух секундантов Шиво
	for (i=1; i<=2; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("GG_SecundantAG_"+i, "mercen_2"+i, "man", "man", 25, PIRATE, -1, true, "quest"));
		FantomMakeCoolFighter(sld, 32, 70, 70, "blade_10", "pistol5", "bullet", 150);
		ChangeCharacterAddressGroup(sld, "FortFrance_ExitTown", "goto", "goto1"+(7+i)); // найти нужные локаторы
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
		sld.LSC_clan = true;
	}
	// ставим Шиво
	sld = characterFromId("Angerran");
	sld.dialog.currentnode = "Angerran_29";
	ChangeCharacterAddressGroup(sld, "FortFrance_ExitTown", "goto", "goto7"); // найти нужные локаторы
	LAi_SetActorType(sld);
	sld.LSC_clan = true;
	chrDisableReloadToLocation = true;//закрыть локацию
	DoQuestReloadToLocation("FortFrance_ExitTown", "reload", "reload3", "GoldenGirl_DuelPrepare");
}

void GoldenGirl_DuelNext() // 
{
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
	// создаем ещё 3 клевретов Шиво
	for (int i=3; i<=5; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("GG_SecundantAG_"+i, "mush_ctz_"+(7+i), "man", "mushketer", 25, PIRATE, -1, false, "soldier"));
		FantomMakeCoolFighter(sld, 30, 70, 70, "", "mushket1", "bullet", 150);
		ChangeCharacterAddressGroup(sld, "FortFrance_ExitTown", "rld", "loc"+(i-3)); // найти нужные локаторы
	}
	for (i=1; i<=5; i++)
	{
		sld = characterFromId("GG_SecundantAG_"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	for (i=1; i<=2; i++)
	{
		sld = characterFromId("GG_SecundantGG_"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "GoldenGirl_AfterDuel");
	LAi_SetFightMode(pchar, true);
}

void GoldenGirl_ToJulianna() // 
{
	sld = characterFromId("FortFrance_Mayor");
	sld.Dialog.Filename = "Common_Mayor.c";
	sld.Dialog.currentnode = "First time";
	DoQuestReloadToLocation("FortFrance_SecBrRoom", "reload", "reload2", "GoldenGirl_ToJulianna");
}

void GoldenGirl_GirlPrisoner() // 
{
	// открываем все, кроме двух наружних дверей борделя
	chrDisableReloadToLocation = false;
	bDisableFastReload = false;
	LocatorReloadEnterDisable("FortFrance_town", "reload1_back", false);
	LocatorReloadEnterDisable("FortFrance_town", "reload2_back", false);
	LocatorReloadEnterDisable("FortFrance_town", "gate_back", false);//открыть выходы из города
	LocatorReloadEnterDisable("FortFrance_SecBrRoom", "reload1", false);
	LocatorReloadEnterDisable("FortFrance_SecBrRoom", "reload2", false);
	LocatorReloadEnterDisable("FortFrance_SecBrRoom", "reload3", false);
	LocatorReloadEnterDisable("FortFrance_Brothel", "reload1_back", false);
	LAi_LocationDisableOfficersGen("FortFrance_townhall", false);//офицеров пускать
	if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
	else sld = characterFromId("Mary");
	string sTemp = sld.name;
	AddQuestRecord("GoldenGirl", "9");
	AddQuestUserData("GoldenGirl", "sName", sTemp);
	pchar.questTemp.GoldenGirl = "girl_prisoner";
	//на таймер
	pchar.quest.goldengirl_timerSP.win_condition.l1 = "Timer";
	pchar.quest.goldengirl_timerSP.win_condition.l1.date.hour  = sti(GetTime());
	pchar.quest.goldengirl_timerSP.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
	pchar.quest.goldengirl_timerSP.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
	pchar.quest.goldengirl_timerSP.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
	pchar.quest.goldengirl_timerSP.function = "GoldenGirl_GirlPrisonerFail";
	if(bImCasual) NewGameTip(StringFromKey("GoldenGirl_14"));
}

void GoldenGirl_GirlPrisonerFail(string qName) // просрочили
{
	pchar.quest.goldengirl_baster.over = "yes";
	LocatorReloadEnterDisable("FortFrance_town", "reload9_back", false); // бордель - открыть, Аврору на место
	LocatorReloadEnterDisable("FortFrance_town", "reload91", false);
	sld = characterFromId("FortFrance_Hostess");
	ChangeCharacterAddressGroup(sld, "FortFrance_SecBrRoom", "barmen", "stay");
	sld = characterFromId("Julianna");
	sld.lifeday = 0;
	sld = characterFromId("Angerran");
	sld.lifeday = 0;
	if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
	else sld = characterFromId("Mary");
	string sTemp = sld.name;
	AddQuestRecord("GoldenGirl", "10");
	AddQuestUserData("GoldenGirl", "sName", sTemp);
	CloseQuestHeader("GoldenGirl");
	pchar.questTemp.GoldenGirl = "fail";
}

void GoldenGirl_ToBaster() // 
{
	if (CheckAttribute(pchar, "questTemp.GoldenGirl.Vaskez")) // васкез враждебный fix 08-04-20
	{
		pchar.quest.goldengirl_vaskez_attack.win_condition.l1 = "location";
		pchar.quest.goldengirl_vaskez_attack.win_condition.l1.location = "Martinique";
		pchar.quest.goldengirl_vaskez_attack.function = "GoldenGirl_VaskezAttack";
	}
	pchar.quest.goldengirl_baster.win_condition.l1 = "location";
	pchar.quest.goldengirl_baster.win_condition.l1.location = "Guadeloupe";
	pchar.quest.goldengirl_baster.function = "GoldenGirl_BasterSetFrigate";
	pchar.quest.goldengirl_timerSP.over = "yes"; //снять таймер
	SetFunctionTimerCondition("GoldenGirl_GirlPrisonerFail", 0, 0, 10, false); // новый таймер
	if(bImCasual) NewGameTip(StringFromKey("GoldenGirl_14"));
	if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
	else sld = characterFromId("Mary");
	string sTemp = sld.name;
	AddQuestRecord("GoldenGirl", "11");
	AddQuestUserData("GoldenGirl", "sName", sTemp);
	pchar.questTemp.GoldenGirl = "baster";
}

void GoldenGirl_VaskezAttack(string qName) // 
{
	bQuestDisableMapEnter = true;//закрыть карту
	Island_SetReloadEnableGlobal("Martinique", false);
	Group_DeleteGroup("GG_MorenoGroup");
	Group_FindOrCreateGroup("GG_MorenoGroup");
	sld = characterFromId("GG_Moreno");
	FantomMakeCoolSailor(sld, SHIP_FRIGATE_H, "", CANNON_TYPE_CANNON_LBS24, 70, 70, 70);
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.AlwaysEnemy = true;
	sld.Coastal_Captain = true;
	sld.Ship.Mode = "pirate";
	sld.ship.Crew.Morale = 40+MOD_SKILL_ENEMY_RATE*6;
	sld.Ship.Crew.Exp.Sailors = 40+MOD_SKILL_ENEMY_RATE*6;
	sld.Ship.Crew.Exp.Cannoners = 40+MOD_SKILL_ENEMY_RATE*6;
	sld.Ship.Crew.Exp.Soldiers = 40+MOD_SKILL_ENEMY_RATE*6;
	if (MOD_SKILL_ENEMY_RATE > 2) SetCharacterPerk(sld, "MusketsShoot");
	sld.WatchFort = true;
	Group_AddCharacter("GG_MorenoGroup", "GG_Moreno");
	Group_SetGroupCommander("GG_MorenoGroup", "GG_Moreno");
	Group_SetAddress("GG_MorenoGroup", "Martinique", "quest_ships", "quest_ship_1");
	Group_SetTaskAttack("GG_MorenoGroup", PLAYER_GROUP);
	Group_LockTask("GG_MorenoGroup");
	pchar.quest.goldengirl_vaskez_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.goldengirl_vaskez_AfterBattle.win_condition.l1.group = "GG_MorenoGroup";
	pchar.quest.goldengirl_vaskez_AfterBattle.function = "GoldenGirl_VaskezAfterBattle";
}

void GoldenGirl_VaskezAfterBattle(string qName) // 
{
	Island_SetReloadEnableGlobal("Martinique", true);
	bQuestDisableMapEnter = false;
	DoQuestCheckDelay("sea_victory", 1.5);
}

void GoldenGirl_BasterSetFrigate(string qName) // 
{
	if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
	else sld = characterFromId("Mary");
	string sTemp = sld.name;
	AddQuestRecord("GoldenGirl", "12");
	AddQuestUserData("GoldenGirl", "sName", sTemp);
	Group_DeleteGroup("GG_AngerranGroup");
	Group_FindOrCreateGroup("GG_AngerranGroup");
	sld = GetCharacter(NPC_GenerateCharacter("GG_AngerranCap", "off_fra_3", "man", "man", 35, FRANCE, -1, true, "quest"));
	FantomMakeCoolFighter(sld, 35, 70, 70, "blade_20", "pistol5", "bullet", 250);
	sld.Ship.Type = GenerateShipHand(sld, SHIP_FRIGATE, 24, 4500, 350, 5200, 70000, 15.5, 39.0, 0.4);
	sld.Ship.name = StringFromKey("GoldenGirl_15");
	SetBaseShipData(sld);
	sld.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS24;
	RealShips[sti(sld.Ship.Type)].ship.upgrades.hull = 3;
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.Coastal_Captain = true;
	sld.Ship.Mode = "war";
	sld.ship.Crew.Morale = 40+MOD_SKILL_ENEMY_RATE*6;
	sld.Ship.Crew.Exp.Sailors = 40+MOD_SKILL_ENEMY_RATE*6;
	sld.Ship.Crew.Exp.Cannoners = 40+MOD_SKILL_ENEMY_RATE*6;
	sld.Ship.Crew.Exp.Soldiers = 40+MOD_SKILL_ENEMY_RATE*6;
	if (MOD_SKILL_ENEMY_RATE > 2) SetCharacterPerk(sld, "MusketsShoot");
	sld.WatchFort = true;
	Group_AddCharacter("GG_AngerranGroup", "GG_AngerranCap");
	Group_SetGroupCommander("GG_AngerranGroup", "GG_AngerranCap");
	Group_SetAddress("GG_AngerranGroup", "Guadeloupe", "quest_ships", "quest_ship_1");
	Group_SetTaskNone("GG_AngerranGroup");
	Group_LockTask("GG_AngerranGroup");
	pchar.quest.goldengirl_AngerranCap_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.goldengirl_AngerranCap_AfterBattle.win_condition.l1.group = "GG_AngerranGroup";
	pchar.quest.goldengirl_AngerranCap_AfterBattle.function = "GoldenGirl_AngerranCapAfterBattle";
}

void GoldenGirl_AngerranCapAfterBattle(string qName) // 
{
	pchar.quest.GoldenGirl_GirlPrisonerFail.over = "yes"; //снять таймер
	DoQuestFunctionDelay("GoldenGirl_GirlPrisonerFail", 0.1);
}

void GoldenGirl_GirlDominicaFail(string qName) // опоздание к Доминике
{
	pchar.quest.goldengirl_dominica_cortny.over = "yes";
	pchar.quest.goldengirl_dominica_alarm.over = "yes";
	Group_DeleteGroup("GG_AngerranGroup");
	sld = characterFromId("GG_AngerranCap");
	sld.lifeday = 0;
	sld = characterFromId("Julianna");
	RemovePassenger(pchar, sld);
	sld.lifeday = 0;
	sld = characterFromId("Angerran");
	sld.lifeday = 0;
	if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
	else sld = characterFromId("Mary");
	string sTemp = sld.name;
	AddQuestRecord("GoldenGirl", "10");
	AddQuestUserData("GoldenGirl", "sName", sTemp);
	CloseQuestHeader("GoldenGirl");
	pchar.questTemp.GoldenGirl = "fail";
}

void GoldenGirl_PatrolInBrothel() // 
{
	string sModel;
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
	for (int i=1; i<=4; i++)
	{
		if (i == 1) sModel = "off_fra_2";
		else sModel = "sold_fra_"+i;
		sld = GetCharacter(NPC_GenerateCharacter("GG_PatrolBrl_"+i, sModel, "man", "man", 30, FRANCE, -1, true, "quest"));
		FantomMakeCoolFighter(sld, 30, 70, 70, "blade_15", "pistol1", "bullet", 150);
		if (i==1)
		{
			sld.Dialog.Filename = "Quest\GoldenGirl.c";
			sld.dialog.currentnode = "off_brothel";
		}
		else LAi_CharacterDisableDialog(sld);
		ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1"); 
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
}

void GoldenGirl_AlarmSP(string qName) // 
{
	sld = characterFromId("FortFrance_Hostess");
	ChangeCharacterAddressGroup(sld, "FortFrance_SecBrRoom", "barmen", "stay");
	sld = characterFromId("FortFrance_Mayor");
	LAi_group_Attack(sld, Pchar);
	Map_NationQuestHunter(FRANCE);
	// перемещаем корабль Шиво на Доминику и даем ноду его кэпу
	Group_SetAddress("GG_AngerranGroup", "Dominica", "quest_ships", "quest_ship_1");
	sld = characterFromId("GG_AngerranCap");
	sld.Dialog.Filename = "Quest\GoldenGirl.c";
	sld.dialog.currentnode = "Cap_Nayad";
	sld.DeckDialogNode = "Cap_Nayad";
	LAi_SetImmortal(sld, true);
	sld.AlwaysFriend = true;
	sld.ShipEnemyDisable  = true;
}

void GoldenGirl_JuliannaOneDay(string qName) // 
{
	pchar.quest.goldengirl_evening.win_condition.l1 = "HardHour";
	pchar.quest.goldengirl_evening.win_condition.l1.hour = 21.00;
	pchar.quest.goldengirl_evening.function = "GoldenGirl_JuliannaEvening";
	if(bImCasual) NewGameTip(StringFromKey("GoldenGirl_14"));
	SetFunctionTimerCondition("GoldenGirl_JuliannaOneDayFail", 0, 0, 1, false);
}

void GoldenGirl_JuliannaEvening(string qName) // 
{
	sld = characterFromId("Julianna");
	sld.dialog.currentnode = "Julianna_88";
}

void GoldenGirl_JuliannaOneDayFail(string qName) // 
{
	sld = characterFromId("Julianna");
	sld.dialog.currentnode = "Julianna_109";
	LAi_SetOwnerType(sld);
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
	else sld = characterFromId("Mary");
	string sTemp = sld.name;
	AddQuestRecord("GoldenGirl", "18_1");
	AddQuestUserData("GoldenGirl", "sName", sTemp);
}

void GoldenGirl_DominicaAlarm(string qName) // на Доминике, маркиза пленница
{
	pchar.quest.GoldenGirl_GirlDominicaFail.over = "yes"; //снять прерывание
	bQuestDisableMapEnter = true;//закрыть карту
	pchar.GenQuest.MapClosedNoBattle = true;
	AddQuestRecord("GoldenGirl", "15");
}

void GoldenGirl_GirlReturn() // 
{
	if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
	else sld = characterFromId("Mary");
	sld.quest.OfficerPrice = sti(pchar.rank)*500;
	sld.OfficerWantToGo.DontGo = true; //не пытаться уйти
	sld.loyality = MAX_LOYALITY;
	AddPassenger(pchar, sld, false);
	SetCharacterRemovable(sld, true);
	sld.Payment = true;
	LAi_SetOfficerType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	SaveCurrentNpcQuestDateParam(sld, "HiredDate");
	if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld.CompanionDisable = true; // fix 22-03-20 блок компаньона у Мэри
}

void GoldenGirl_TimeCortnyFail(string qName) // фин 2, не пришли на встречу с Кортни
{
	sld = characterFromId("Cortny");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	sld = characterFromId("Julianna");
	sld.dialog.currentnode = "Julianna_109";
	LAi_SetOwnerType(sld);
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
	else sld = characterFromId("Mary");
	string sTemp = sld.name;
	AddQuestRecord("GoldenGirl", "18");
	AddQuestUserData("GoldenGirl", "sName", sTemp);
}

void GoldenGirl_TimeCortny(string qName) // фин 2 пришли на встречу с Кортни
{
	sld = characterFromId("Cortny");
	sld.dialog.currentnode = "Cortny_";
	ChangeCharacterAddressGroup(sld, "FortFrance_SecBrRoom", "goto", "goto4");
	sld = characterFromId("Julianna");
	sld.dialog.currentnode = "Julianna_110";
	LAi_SetStayType(sld);
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
}

void GoldenGirl_CortnyBandosFight() // 
{
	chrDisableReloadToLocation = true;//закрыть локацию
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
	sld = characterFromId("Julianna");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocator(sld, "quest", "quest1", "", -1);
	sld = characterFromId("Cortny");
	ForceAutolevel(sld, GEN_TYPE_ENEMY, GEN_BOSS, GEN_ARCHETYPE_RANDOM, GEN_ARCHETYPE_RANDOM, GEN_RANDOM_PIRATES, 0.6);
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	LAi_SetFightMode(sld, true);
	LAi_group_Delete("EnemyFight");
	for (int i=1; i<=5; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("GG_Bandos_"+i, "citiz_4"+i, "man", "man", 25, PIRATE, -1, true, "quest"));
		FantomMakeCoolFighter(sld, 25, 50, 50, "blade_10", "pistol1", "bullet", 150);
		if (i < 4) ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
		else ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload2");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "GoldenGirl_BandosAfterFight");
	LAi_SetFightMode(pchar, true);
}

void GoldenGirl_CortnyMercenFight() // 
{
	sld = characterFromId("Cortny");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	LAi_SetFightMode(sld, true);
	LAi_group_Delete("EnemyFight");
	for (int i=1; i<=3; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("GG_Mercen_"+i, "killer_"+i, "man", "man", 35, PIRATE, -1, true, "quest"));
		FantomMakeCoolFighter(sld, 35, 70, 70, "blade_19", "pistol4", "bullet", 250);
		ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "GoldenGirl_MercenAfterFight");
	LAi_SetFightMode(pchar, true);
}

void GoldenGirl_DominicaCortny(string qName) // на Доминике с Кортни
{
	pchar.quest.GoldenGirl_GirlDominicaFail.over = "yes"; //снять прерывание
	bQuestDisableMapEnter = true;//закрыть карту
	pchar.GenQuest.MapClosedNoBattle = true;
}

void GoldenGirl_CortnySetOnDeck() // 
{
	sld = characterFromId("Cortny");
	sld.dialog.currentnode = "Cortny_35";
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void GoldenGirl_CortnySPFinal(string qName) // финал без посещения маркизы
{
	pchar.quest.goldengirl_cortny_sp.over = "yes"; //снять прерывание
	sld = characterFromId("FortFrance_Hostess");
	ChangeCharacterAddressGroup(sld, "FortFrance_SecBrRoom", "barmen", "stay");
	sld = characterFromId("Cortny");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	CloseQuestHeader("GoldenGirl");
	pchar.questTemp.GoldenGirl = "end";
	AddSimpleRumour(StringFromKey("GoldenGirl_16"), FRANCE, 90, 5);
}

void GoldenGirl_CortnySPFinalAdd(string qName) // финал с посещением маркизы
{
	pchar.quest.GoldenGirl_CortnySPFinal.over = "yes"; //снять прерывание
	chrDisableReloadToLocation = true;
	sld = characterFromId("Cortny");
	sld.dialog.currentnode = "Cortny_38";
	ChangeCharacterAddressGroup(sld, "FortFrance_SecBrRoom", "goto", "goto1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void GoldenGirl_AntiguaArest()//арестовывающие солдаты на Антигуа
{
	chrDisableReloadToLocation = true;//закрыть локацию
	for (int i=1; i<=3; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter("GASold"+i, "sold_eng_"+i, "man", "man", 20, ENGLAND, 0, true, "soldier"));
		SetFantomParamFromRank(sld, 20, true);         
		LAi_SetWarriorType(sld); 
		LAi_warrior_DialogEnable(sld, false);
        ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
    }
    sld = GetCharacter(NPC_GenerateCharacter("GAOfficer", "off_eng_3", "man", "man", 30, ENGLAND, 0, true, "soldier"));
	SetFantomParamFromRank(sld, 30, true);
	sld.Dialog.Filename = "Quest\GoldenGirl.c";
	sld.dialog.currentnode = "antigua_officer";
	sld.greeting = "soldier_arest";
    LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
	LAi_ActorDialog(sld, pchar, "", 1.0, 0);
	pchar.questTemp.GoldenGirl = "arest";
}

void GoldenGirl_CortnyInJail(string qName)//Кортни в тюрьме
{
    sld = characterFromID("Cortny");
	LAi_SetActorType(sld);
    LAi_ActorGoToLocator(sld, "goto", "goto23", "", -1);
	DoQuestFunctionDelay("GoldenGirl_CortnyInJailGo", 3.0);
}

void GoldenGirl_CortnyInJailGo(string qName)//Кортни в тюрьме
{
    sld = characterFromID("Cortny");
	LAi_SetActorType(sld);
    LAi_ActorDialog(sld, pchar, "", 0, 0);
}

void GoldenGirl_BasterArest()//арестовывающие солдаты на Гваделупе
{
	for (int i=1; i<=3; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter("GBSold"+i, "sold_fra_"+i, "man", "man", 20, FRANCE, 0, true, "soldier"));
		SetFantomParamFromRank(sld, 20, true);         
		LAi_SetWarriorType(sld); 
		LAi_warrior_DialogEnable(sld, false);
        ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
    }
    sld = GetCharacter(NPC_GenerateCharacter("GBOfficer", "off_fra_3", "man", "man", 30, FRANCE, 0, true, "soldier"));
	SetFantomParamFromRank(sld, 30, true);
	sld.Dialog.Filename = "Quest\GoldenGirl.c";
	sld.dialog.currentnode = "baster_officer";
	sld.greeting = "soldier_arest";
    LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
	LAi_ActorDialog(sld, pchar, "", 1.0, 0);
}

void GoldenGirl_JuliannaInJail(string qName)//Джулиана в тюрьме
{
    sld = characterFromID("Julianna");
	LAi_SetActorType(sld);
    LAi_ActorGoToLocator(sld, "goto", "goto23", "", -1);
	DoQuestFunctionDelay("GoldenGirl_JuliannaInJailGo", 3.0);
}

void GoldenGirl_JuliannaInJailGo(string qName)//Джулиана в тюрьме
{
    sld = characterFromID("Julianna");
	LAi_SetActorType(sld);
    LAi_ActorDialog(sld, pchar, "", 0, 0);
}

void GoldenGirl_OnMartinique(string qName)// на Мартинике
{
	pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу
    if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Helper")) // belamour теперь Бото в резиденции 
	{
		sld = characterFromID("Julianna");
		RemovePassenger(pchar, sld);
		sld.dialog.currentnode = "Julianna_144";
		ChangeCharacterAddressGroup(sld, "FortFrance_SecBrRoom", "goto", "goto4");
		LAi_SetStayType(sld);
		LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	}
	chrDisableReloadToLocation = true;//закрыть локацию
	if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
	else sld = characterFromId("Mary");
	sld.dialog.currentnode = "GoldenGirl_32";
	ChangeCharacterAddressGroup(sld, "FortFrance_town", "quest", "quest1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void GoldenGirl_MaryBlockDelete() // fix 22-03-20 возвращаем Мэри её поведение
{
    DeleteAttribute(pchar, "questTemp.MarySexBlock");
	pchar.quest.Mary_giveme_sex.win_condition.l1 = "Timer";
	pchar.quest.Mary_giveme_sex.win_condition.l1.date.hour  = sti(GetTime());
	pchar.quest.Mary_giveme_sex.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 14);
	pchar.quest.Mary_giveme_sex.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 14);
	pchar.quest.Mary_giveme_sex.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 14);
	pchar.quest.Mary_giveme_sex.function = "Mary_GiveMeSex";
}

//=================================================================
//======================кейсы из quests_reaction===================
//=================================================================
bool GoldenGirl_QuestComplete(string sQuestName, string qname)
{

	ref sld;
	int     iTemp, i, n;
    float locx, locy, locz;
	string sTemp;
	
	bool condition = true;
	
	if (sQuestName == "GoldenGirl_GirlExit") // подруга убегает
	{
		chrDisableReloadToLocation = false;//открыть локацию
		bDisableFastReload = false;//открыть переход
		if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
		else sld = characterFromId("Mary");
		sld.dialog.currentnode = "GoldenGirl_10";
		LAi_SetOfficerType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	} 
	else if (sQuestName == "GoldenGirl_PartyTalk") 
	{
		sld = characterFromId("Julianna");
		ChangeCharacterAddressGroup(sld, "FortFrance_SecBrRoom", "goto", "goto5");
		LAi_SetPlayerType(pchar);
		sld = characterFromId("Julianna");
		sld.dialog.currentnode = "Julianna_9";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	} 
	else if (sQuestName == "GoldenGirl_JulianaPause") 
	{
		sld = characterFromId("Julianna");
		sld.dialog.currentnode = "Julianna_15";
		LAi_SetOwnerType(sld);
		LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	} 
	else if (sQuestName == "GoldenGirl_JulianaAfterPause") 
	{
		sld = characterFromId("Julianna");
		LAi_CharacterEnableDialog(sld);
	} 
	else if (sQuestName == "GoldenGirl_CreateColonel") 
	{
		sld = GetCharacter(NPC_GenerateCharacter("GG_Colonel", "off_fra_5", "man", "man", 35, FRANCE, -1, false, "quest"));
		FantomMakeCoolFighter(sld, 35, 80, 80, "blade_20", "pistol5", "bullet", 150);
		ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
		sld.Dialog.Filename = "Quest\GoldenGirl.c";
		sld.dialog.currentnode = "comendant";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	} 
	else if (sQuestName == "GoldenGirl_Game1Res") // результаты 1 игры
	{
		sld = characterFromId("GG_Colonel");
		sld.dialog.currentnode = "comendant_3";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	} 
	else if (sQuestName == "GoldenGirl_Game2Res") // результаты 2 игры
	{
		sld = characterFromId("GG_Moreno");
		sld.dialog.currentnode = "moreno_7";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	} 
	else if (sQuestName == "GoldenGirl_Talking") // 
	{
		LAi_SetPlayerType(pchar);
		sld = characterFromId("Julianna");
		sld.dialog.currentnode = "Julianna_23";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	} 
	else if (sQuestName == "GoldenGirl_AngerranCards") 
	{
		sld = characterFromId("Angerran");
		sld.dialog.currentnode = "Angerran_9";
		sld.greeting = "Angerran_ne_po_chinu";
		LAi_SetStayType(sld);
		LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
		sld = characterFromId("GG_statist1");
		ChangeCharacterAddressGroup(sld, "Location_reserve_02", "goto", "goto8");
		LAi_SetActorType(sld);
	} 
	else if (sQuestName == "GoldenGirl_Game3Res") // результаты 3 игры
	{
		sld = characterFromId("Angerran");
		sld.dialog.currentnode = "Angerran_13";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	} 
	else if (sQuestName == "GoldenGirl_Game4Res") // результаты 4 игры
	{
		sld = characterFromId("Angerran");
		sld.dialog.currentnode = "Angerran_19";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	} 
	else if (sQuestName == "GoldenGirl_AfterCardsGames") 
	{
		sld = characterFromId("Julianna");
		sld.dialog.currentnode = "Julianna_39";
		sld.greeting = "Marquesa_again";
		ChangeCharacterAddressGroup(sld, "FortFrance_SecBrRoom", "barmen", "bar1");
		LAi_SetOwnerType(sld);
		LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	} 
	else if (sQuestName == "GoldenGirl_GirlShip") 
	{
		chrDisableReloadToLocation = true;//закрыть локацию
		if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
		else sld = characterFromId("Mary");
		sld.dialog.currentnode = "GoldenGirl_12";
		LAi_SetActorType(sld);
		GetCharacterPos(pchar, &locx, &locy, &locz);
		ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	} 
	else if (sQuestName == "GoldenGirl_GirlToFregat") 
	{
		chrDisableReloadToLocation = false;
		if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
		else sld = characterFromId("Mary");
		DeleteAttribute(sld, "CompanionDisable");
		RemovePassenger(Pchar, sld);
		RemoveCharacterCompanion(pchar, sld);
		sld.Ship.Type = GenerateShipHand(sld, SHIP_FRIGATE, 24, 4500, 350, 5200, 70000, 15.5, 39.0, 0.4);
		sld.Ship.name = StringFromKey("GoldenGirl_15");
		SetBaseShipData(sld);
		sld.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS24;
		RealShips[sti(sld.Ship.Type)].ship.upgrades.hull = 3;
		SetCrewQuantityOverMax(sld, 10);
		SetCharacterRemovable(sld, false);
		sld.CompanionEnemyEnable = false; //всегда друзья
		SetCompanionIndex(sld, -1, sti(sld.index));
		sld.loyality = MAX_LOYALITY;
		pchar.questTemp.GoldenGirl = "duel";
		sTemp = sld.name;
		AddQuestRecord("GoldenGirl", "7");
		AddQuestUserData("GoldenGirl", "sName", sTemp);
		pchar.quest.goldengirl_duel.win_condition.l1 = "Timer";
		pchar.quest.goldengirl_duel.win_condition.l1.date.hour  = sti(GetTime() + 8);
		pchar.quest.goldengirl_duel.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
		pchar.quest.goldengirl_duel.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
		pchar.quest.goldengirl_duel.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
		pchar.quest.goldengirl_duel.function = "GoldenGirl_DuelPrepare";
	} 
	else if (sQuestName == "GoldenGirl_DuelPrepare") 
	{
		sld = characterFromId("GG_SecundantGG_1");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	else if (sQuestName == "GoldenGirl_Duel") 
	{
		DoQuestCheckDelay("hide_weapon", 1.0);
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
		sld = characterFromId("Angerran");
		sld.dialog.currentnode = "Angerran_31";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	} 
	else if (sQuestName == "GoldenGirl_AfterDuel") 
	{
		LAi_group_Delete("EnemyFight");
		LAi_LocationDisableOfficersGen("FortFrance_ExitTown", false);
		locations[FindLocation("FortFrance_ExitTown")].DisableEncounters = false;
		n = 0;
		for (i=1; i<=2; i++)
		{
			sld = characterFromId("GG_SecundantGG_"+i);
			sld.lifeday = 0;
			if (LAi_GetCharacterHP(sld) > 0) n++;
		}
		pchar.questTemp.GoldenGirl.Officer = n;
		DoQuestCheckDelay("hide_weapon", 1.0);
		DoQuestCheckDelay("GoldenGirl_AfterDuelToGovernor", 4.0);
	} 
	else if (sQuestName == "GoldenGirl_AfterDuelToGovernor") 
	{
		sld = characterFromId("FortFrance_Mayor");
		sld.Dialog.Filename = "Quest\GoldenGirl.c";
		sld.dialog.currentnode = "governor_25";
		DoQuestReloadToLocation("FortFrance_Townhall", "reload", "reload1", "");
		AddQuestRecord("GoldenGirl", "8");
	} 
	else if (sQuestName == "GoldenGirl_ToJulianna") 
	{
		sld = characterFromId("Julianna");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	} 
	else if (sQuestName == "GoldenGirl_WithoutJulianna") 
	{
		DoQuestCheckDelay("GoldenGirl_SleepInRoom", 1.8);
	} 
	// Sinistra катсцена с поцелуями
	else if (sQuestName == "GoldenGirl_KissJulianna") 
	{
		DialogExit();
		StartQuestMovie(true, false, true);
		//if(CheckAttribute (pchar, "IsMushketer")) SetMainCharacterToMushketer("", false);
		TeleportCharacterToPosAy(pchar, 1.50, 0.00, -1.89, 3.00);
		LAi_SetActorType(pchar);
		LAi_ActorAnimation(pchar, "kiss", "1", 7.5);
		sld = CharacterFromID("Julianna");
		sld.model.animation = "woman";
		Characters_RefreshModel(sld);
		TeleportCharacterToPosAy(sld, 1.50, 0.00, -2.49, 0.00);
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "kiss", "1", 7.5);
		locCameraFromToPos(2.37, 1.48, -1.02, true, -0.29, -0.14, -3.85);
		DoQuestCheckDelay("GoldenGirl_SexJulianna", 7.5);
	} 
	else if (sQuestName == "GoldenGirl_SexJulianna") 
	{
		EndQuestMovie();
		bDisableCharacterMenu = false;
		locCameraTarget(PChar);
		locCameraFollow();
		
		pchar.GenQuest.FrameLockEsc = true;
		ResetSound();
		SetLaunchFrameFormParam("", "", 0, 14);
		SetLaunchFrameFormPic("loading\inside\censored1.tga");
		if(bSFW) PlayStereoSound("sex\sex_sfw.wav");
		else PlayStereoSound("sex\sex6.wav");
		LaunchFrameForm();
		DoQuestCheckDelay("GoldenGirl_AfterSexJulianna", 14.0);
		if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	
		{
			AddCharacterHealth(pchar, 12);
			AddCharacterMaxHealth(pchar, 1.0);
		}
		else AddCharacterHealth(pchar, 6);
		pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1; //счетчик
	} 
	else if (sQuestName == "GoldenGirl_AfterSexJulianna") 
	{
		LAi_SetPlayerType(pchar);
		TeleportCharacterToPosAy(pchar, 1.97, 0.00, -2.61, 0.00);
		DeleteAttribute(pchar, "GenQuest.FrameLockEsc");
		sld = characterFromId("Julianna");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "GoldenGirl_SleepInRoom", 5.0);
	} 
	else if (sQuestName == "GoldenGirl_SleepInRoom") 
	{
		LSC_MaryLoveWaitTime();
		SetLaunchFrameFormParam(StringFromKey("GoldenGirl_17"), "", 0, 4);
		LaunchFrameForm();
		DoQuestCheckDelay("GoldenGirl_SleepInRoomMorning", 4.0);
		LAi_SetCurHPMax(pchar);
		AddCharacterHealth(pchar, 6);
		// убираем фрегат
		if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
		else sld = characterFromId("Mary");
		RemovePassenger(pchar, sld);
		RemoveCharacterCompanion(pchar, sld);
	} 
	else if (sQuestName == "GoldenGirl_SleepInRoomMorning") 
	{
		sld = characterFromId("Julianna");
		sld.model.animation = "towngirl";
		Characters_RefreshModel(sld);
		sld.dialog.currentnode = "Julianna_54";
		ChangeCharacterAddressGroup(sld, "FortFrance_Brothel_room", "reload", "reload1");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	} 
	else if (sQuestName == "GoldenGirl_BadNews") 
	{
		LocatorReloadEnterDisable("FortFrance_town", "reload3_back", false);
		sld = characterFromId("Julianna");
		sld.dialog.currentnode = "Julianna_58";
		ChangeCharacterAddressGroup(sld, "FortFrance_SecBrRoom", "barmen", "stay");
		LAi_SetOwnerType(sld);
		LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
		sld = GetCharacter(NPC_GenerateCharacter("GG_sailor", "Alonso", "man", "man", 10, FRANCE, 1, true, "soldier"));
		sld.name = GetCharacterName("Alonso");
		sld.lastname = "";
		SetFantomParamFromRank(sld, 10, true);
		sld.Dialog.Filename = "Quest\GoldenGirl.c";
		sld.dialog.currentnode = "sailor";
		ChangeCharacterAddressGroup(sld, "FortFrance_town", "reload", "reload9");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	} 
	else if (sQuestName == "GoldenGirl_AngerranInResidence") 
	{
		chrDisableReloadToLocation = true;
		sld = characterFromId("Angerran");
		sld.dialog.currentnode = "Angerran_34";
		sld.greeting = "Angerran_poluybovno";
		ChangeCharacterAddressGroup(sld, "CommonResidence_3", "reload", "reload2");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	} 
	else if (sQuestName == "GoldenGirl_AfterBaster") 
	{
		chrDisableReloadToLocation = false;
		sld = characterFromId("Angerran");
		ChangeCharacterAddressGroup(sld, "none", "", "");
		pchar.quest.goldengirl_AngerranCap_AfterBattle.over = "yes"; //снять прерывание
		pchar.quest.GoldenGirl_GirlPrisonerFail.over = "yes"; //снять таймер
		SetFunctionTimerCondition("GoldenGirl_GirlDominicaFail", 0, 0, 15, false); // новый таймер
		sld = characterFromId("Julianna");
		sld.dialog.currentnode = "Julianna_72";
		if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
		else sld = characterFromId("Mary");
		sTemp = sld.name;
		AddQuestRecord("GoldenGirl", "13");
		AddQuestUserData("GoldenGirl", "sName", sTemp);
		pchar.questTemp.GoldenGirl = "dominica";
	} 
	else if (sQuestName == "GoldenGirl_BrothelAfterFight") 
	{
		LAi_group_Delete("EnemyFight");
		sld = characterFromId("Julianna");
		sld.dialog.currentnode = "Julianna_78";
		sld.greeting = "Marquesa_kashmar";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	else if (sQuestName == "GoldenGirl_DominicaAlarmFinal") // завершение силового варианта
	{
		pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу
		chrDisableReloadToLocation = true;//закрыть локацию
		bQuestDisableMapEnter = false;//открыть карту
		DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		pchar.quest.goldengirl_AngerranCap_AfterBattle.over = "yes";
		Group_DeleteGroup("GG_AngerranGroup");
		sld = characterFromId("GG_AngerranCap");
		sld.lifeday = 0;
		sld = characterFromId("Julianna");
		RemovePassenger(pchar, sld);
		sld.lifeday = 0;
		setCharacterShipLocation(pchar, "shore27");
		setWDMPointXZ("shore27"); // корабль на рейд
		if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
		else sld = characterFromId("Mary");
		sld.dialog.currentnode = "GoldenGirl_24";
		ChangeCharacterAddressGroup(sld, "shore27", "goto", "goto14");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		pchar.questTemp.GoldenGirl = "alarm_fin";
		pchar.questTemp.GoldenGirl.Angerran = "true"; // Шиво ещё вернётся fix 02-04-20
	} 
	else if (sQuestName == "GoldenGirl_GirlGoOnBoard") 
	{
		GoldenGirl_GirlReturn();
		chrDisableReloadToLocation = false;//открыть локацию
		if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
		else sld = characterFromId("Mary");
		if (pchar.questTemp.GoldenGirl == "alarm_fin")
		{
			AddQuestRecord("GoldenGirl", "16");
			AddQuestUserData("GoldenGirl", "sName", sld.name);
			CloseQuestHeader("GoldenGirl");
			pchar.questTemp.GoldenGirl = "end";
		}
		else 
		{
			AddQuestRecord("GoldenGirl", "21");
			AddQuestUserData("GoldenGirl", "sName", sld.name);
			SetFunctionTimerCondition("GoldenGirl_CortnySPFinal", 0, 0, 8, false);
			pchar.quest.goldengirl_cortny_sp.win_condition.l1 = "location";
			pchar.quest.goldengirl_cortny_sp.win_condition.l1.location = "FortFrance_SecBrRoom";
			pchar.quest.goldengirl_cortny_sp.function = "GoldenGirl_CortnySPFinalAdd";
		}
	} 
	else if (sQuestName == "GoldenGirl_BandosAfterFight") 
	{
		sld = characterFromId("Cortny");
		if (LAi_GetCharacterHP(sld) < 1)
		{
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_78";
			LAi_CharacterEnableDialog(sld);
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestRecord("GoldenGirl", "19");
			AddQuestUserData("GoldenGirl", "sName", sTemp);
		}
		else
		{
			sld.dialog.currentnode = "Cortny_19";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		}
	} 
	else if (sQuestName == "GoldenGirl_MercenAfterFight") 
	{
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
		LAi_group_Delete("EnemyFight");
		sld = characterFromId("Cortny");
		if (LAi_GetCharacterHP(sld) < 1)
		{
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_78";
			LAi_CharacterEnableDialog(sld);
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestRecord("GoldenGirl", "19");
			AddQuestUserData("GoldenGirl", "sName", sTemp);
		}
		else
		{
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_115";
			LAi_CharacterEnableDialog(sld);
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		}
	} 
	else if (sQuestName == "GoldenGirl_CortnyPassenger") 
	{
		sld = characterFromId("Cortny");
		AddPassenger(pchar, sld, false);//добавить пассажира
		SetCharacterRemovable(sld, false);
		chrDisableReloadToLocation = false;
		// перемещаем корабль Шиво на Доминику и даем ноду его кэпу
		Group_SetAddress("GG_AngerranGroup", "Dominica", "quest_ships", "quest_ship_1");
		sld = characterFromId("GG_AngerranCap");
		sld.Dialog.Filename = "Quest\GoldenGirl.c";
		sld.dialog.currentnode = "Cap_Nayad";
		sld.DeckDialogNode = "Cap_Nayad_3";
		LAi_SetImmortal(sld, true);
		sld.AlwaysFriend = true;
		sld.ShipEnemyDisable  = true;
		pchar.quest.goldengirl_dominica_cortny.win_condition.l1 = "location";
		pchar.quest.goldengirl_dominica_cortny.win_condition.l1.location = "Dominica";
		pchar.quest.goldengirl_dominica_cortny.function = "GoldenGirl_DominicaCortny";
		if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
		else sld = characterFromId("Mary");
		sTemp = sld.name;
		AddQuestRecord("GoldenGirl", "20");
		AddQuestUserData("GoldenGirl", "sName", sTemp);
	}
	else if (sQuestName == "GoldenGirl_DominicaCortnyFinal") // завершение варианта Кортни на Доминике
	{
		pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу
		chrDisableReloadToLocation = true;//закрыть локацию
		bQuestDisableMapEnter = false;//открыть карту
		DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		Group_DeleteGroup("GG_AngerranGroup");
		sld = characterFromId("GG_AngerranCap");
		sld.lifeday = 0;
		sld = characterFromId("Cortny");
		RemovePassenger(pchar, sld);
		int iCrew = makeint(sti(pchar.Ship.Crew.Quantity)*0.67); 
		SetCrewQuantityOverMax(pchar, iCrew); // сносим треть команды
		setCharacterShipLocation(pchar, "shore27");
		setWDMPointXZ("shore27"); // корабль на рейд
		if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
		else sld = characterFromId("Mary");
		sld.dialog.currentnode = "GoldenGirl_24";
		ChangeCharacterAddressGroup(sld, "shore27", "goto", "goto14");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		pchar.questTemp.GoldenGirl = "cortny_fin";
	} 
	else if (sQuestName == "GoldenGirl_SPFinal") // завершение варианта Кортни в Сен-Пьер
	{
		chrDisableReloadToLocation = false;
		sld = characterFromId("FortFrance_Hostess");
		ChangeCharacterAddressGroup(sld, "FortFrance_SecBrRoom", "barmen", "stay");
		sld = characterFromId("Cortny");
		ChangeCharacterAddressGroup(sld, "none", "", "");
		CloseQuestHeader("GoldenGirl");
		pchar.questTemp.GoldenGirl = "end";
		GiveItem2Character(pchar, "blackpearl"); // черная жемчужина 
	} 
	else if (sQuestName == "GoldenGirl_ReloadToBaster") 
	{
		pchar.quest.GoldenGirl_GirlDominicaFail.over = "yes"; //снять прерывание
		SetLaunchFrameFormParam(StringFromKey("GoldenGirl_18", NewStr()), "", 0, 5);
		WaitDate("", 0, 0, 3, 2, 10); 
		LaunchFrameForm();
		RefreshLandTime();
		RecalculateJumpTable();
		Whr_UpdateWeather();
		DoQuestCheckDelay("GoldenGirl_ReloadToBasterGo", 5.0);
	} 
	else if (sQuestName == "GoldenGirl_ReloadToBasterGo") 
	{
		DoQuestReloadToLocation("Baster_Townhall", "goto", "goto1", "GoldenGirl_CortnyBaster");
	} 
	else if (sQuestName == "GoldenGirl_CortnyBaster") 
	{
		setCharacterShipLocation(pchar, "Baster_town");
		setWDMPointXZ("Baster_town"); // корабль на рейд
		sld = characterFromId("Cortny");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	} 
	else if (sQuestName == "GoldenGirl_BasterReloadJail") 
	{
		pchar.questTemp.jailCanMove = true; //разрешить пройти мимо стражи
		DoQuestReloadToLocation(pchar.location, "goto", "goto23", "GoldenGirl_BasterFinal");
	} 
	else if (sQuestName == "GoldenGirl_BasterFinal") 
	{
		bDisableCharacterMenu = false;
		chrDisableReloadToLocation = false;
		sld = characterFromId("FortFrance_Hostess");
		ChangeCharacterAddressGroup(sld, "FortFrance_SecBrRoom", "barmen", "stay");
		if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Helper")) // belamour целый час бился, какого ... не видит условие
		{
			sld = characterFromID("Julianna");
			AddPassenger(pchar, sld, false);//добавить пассажира
			SetCharacterRemovable(sld, false);
		}
		pchar.quest.goldengirl_martinique.win_condition.l1 = "location";
		pchar.quest.goldengirl_martinique.win_condition.l1.location = "FortFrance_town";
		pchar.quest.goldengirl_martinique.function = "GoldenGirl_OnMartinique";
		pchar.questTemp.GoldenGirl = "martinique";
	} 
	else if (sQuestName == "GoldenGirl_SPGirlReturn") 
	{
		GoldenGirl_GirlReturn();
		chrDisableReloadToLocation = false;//открыть локацию
		AddQuestRecord("GoldenGirl", "25");
		if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
		else sld = characterFromId("Mary");
		sTemp = sld.name;
		AddQuestUserData("GoldenGirl", "sName", sTemp);
		CloseQuestHeader("GoldenGirl");
		AddQuestRecordInfo("Letter_Portugal", "1");
		pchar.questTemp.GoldenGirl = "end";
		pchar.questTemp.GoldenGirl.Angerran = "true"; // Шиво ещё вернётся fix 02-04-20
	}
	else
	{
		condition = false;
	}
	
	return condition;
}