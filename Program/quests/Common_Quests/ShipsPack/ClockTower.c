
void ClockTower_TEST_OfficeServices()
{
    ref sld = CreateVanDoorn("ClockTower_VanDoorn", -1);
	ChangeCharacterAddressGroup(sld, "Villemstad_ClockTower", "sit", "sit1");
	LAi_SetHuberType(sld);
	sld.dialog.filename = "Quest\ShipsPack\ClockTower_dialog.c";
	sld.dialog.currentnode = "ClockTower_OfficeServices";
	LAi_CharacterEnableDialog(sld);
}

void ClockTower_Start()
{
	log_testinfo("Квест 'Башня с часами' стартовал");
	pchar.questTemp.ClockTower_Start = true;
	pchar.quest.ClockTower.date = rand(27)+1;
	
	sld = GetCharacter(NPC_GenerateCharacter("ClockTower_Johan", "sold_hol_9", "man", "man", 10, HOLLAND, -1, true, "soldier"));
	ForceAdaptivelevel(sld, 15, GEN_TYPE_ENEMY, GEN_MINIBOSS, GEN_ARCHETYPE_GUNMAN, GEN_ARCHETYPE_RANDOM, GEN_RANDOM_PIRATES, 0.7);
	sld.name = GetCharacterName("Johan");
	sld.lastname = "";
	sld.role = "Naval Registry Guard";
	sld.City = "Villemstad";
	sld.dialog.filename = "Quest\ShipsPack\ClockTower_dialog.c";
	sld.dialog.currentnode = "ClockTower_Johan_1";
	sld.talker = 5;
	ChangeCharacterAddressGroup(sld, "Villemstad_town", "quest", "quest3");
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetImmortal(sld, true);
	AddLandQuestMark(sld, "questmarkmain");
	AddMapQuestMarkCity("Villemstad", false);
	LAi_SetGuardianType(sld);
	LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	AddMoneyToCharacter(sld, 90);
	AddItems(sld, "ArmoryPaper", 2);
	AddItems(sld, "cartridge", 2);
	AddItems(sld, "Mineral18", 1);
	AddItems(sld, "Mineral15", 1);
	locations[FindLocation("Villemstad_town")].models.always.sign_gvik = "Curacao_signs_gvik_a";
}

void ClockTower_Quest_1() // Задание 1: нужна репутация "Восхищение" у Голландии
{
	SetQuestHeader("ClockTower");
	AddQuestRecord("ClockTower", "1");
	DelMapQuestMarkCity("Villemstad");
	
	ref sld = CharacterFromID("ClockTower_Johan");
	sld.dialog.filename = "Quest\ShipsPack\ClockTower_dialog.c";
	sld.dialog.currentnode = "ClockTower_Johan_repeat";
	
	SetFunctionTimerCondition("ClockTower_HollandAdmiresMe", 0, 0, 7, true);
}

void ClockTower_HollandAdmiresMe(string qName)
{
	if(!GetDLCenabled(DLC_APPID_7)) return;
	if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) >= 51)
	{
		DeleteQuestCondition("ClockTower_HollandAdmiresMe");
		AddQuestRecord("ClockTower", "2");
		sld = CharacterFromID("ClockTower_Johan");
		sld.dialog.filename = "Quest\ShipsPack\ClockTower_dialog.c";
		sld.dialog.currentnode = "ClockTower_Johan_21";
		sld.talker = 5;
		AddLandQuestMark(sld, "questmarkmain");
		AddMapQuestMarkCity("Villemstad", false);
	}
}

void ClockTower_InvitationToTheTower()// пригласили в башню на приём
{
	DeleteQuestCondition("ClockTower_HollandAdmiresMe");
	sld = CharacterFromID("ClockTower_Johan");
	LAi_CharacterDisableDialog(sld);
	
	// открыть проход в башню
	LocatorReloadEnterDisable("Villemstad_town", "houseO2", false);
	
	// Маартен Виссер заместитель сидит в башне
	sld = GetCharacter(NPC_GenerateCharacter("ClockTower_Visser", "citiz_6", "man", "man", sti(pchar.rank), HOLLAND, -1, false, "quest"));
	sld.name = GetCharacterName("Maarten");
	sld.lastname = GetCharacterName("Visser");
	sld.role = "Deputy Director";
	sld.City = "Villemstad";
	sld.dialog.filename = "Quest\ShipsPack\ClockTower_dialog.c";
	sld.dialog.currentnode = "ClockTower_Visser_1";
	ChangeCharacterAddressGroup(sld, "Villemstad_ClockTower", "sit", "sit1");
	LAi_SetImmortal(sld, true);
	LAi_SetHuberType(sld);
	LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
	AddLandQuestMark(sld, "questmarkmain");
}

void ClockTower_Quest_2() // Задание 2: нужно раздобывать 5 журналов у пиратских капитанов
{
	AddQuestRecord("ClockTower", "3");
	DelMapQuestMarkCity("Villemstad");
	
	sld = CharacterFromID("ClockTower_Visser");
	LAi_CharacterDisableDialog(sld);
	
	SetFunctionTimerCondition("ClockTower_journal", 0, 0, 1, false);
	
	// закрыть проход в башню
	LocatorReloadEnterDisable("Villemstad_town", "houseO2", true);
	
	// С этого момента у пиратов начинают дропаться судовые журналы
	ClockTower_AddJournals();
	// обновим счетчик ачивки
	if(!GetAchievement("ach_CL_200")) pchar.achievment.piratesJournals = GetStat("stat_CL_200");
}

void ClockTower_journal(string qName)
{
	sld = CharacterFromID("ClockTower_Johan");
	LAi_CharacterEnableDialog(sld);
	sld.dialog.filename = "Quest\ShipsPack\ClockTower_dialog.c";
	sld.dialog.currentnode = "ClockTower_Johan_31";
	
	PChar.quest.ClockTower_FoundJournal_1.win_condition.l1 = "item";
	PChar.quest.ClockTower_FoundJournal_1.win_condition.l1.item = "piratesJournal_1";
	PChar.quest.ClockTower_FoundJournal_1.function = "ClockTower_FoundJournal";
	PChar.Quest.ClockTower_FoundJournal_1.again = true;
	PChar.quest.ClockTower_FoundJournal_2.win_condition.l1 = "item";
	PChar.quest.ClockTower_FoundJournal_2.win_condition.l1.item = "piratesJournal_2";
	PChar.quest.ClockTower_FoundJournal_2.function = "ClockTower_FoundJournal";
	PChar.Quest.ClockTower_FoundJournal_2.again = true;
	PChar.quest.ClockTower_FoundJournal_3.win_condition.l1 = "item";
	PChar.quest.ClockTower_FoundJournal_3.win_condition.l1.item = "piratesJournal_3";
	PChar.quest.ClockTower_FoundJournal_3.function = "ClockTower_FoundJournal";
	PChar.Quest.ClockTower_FoundJournal_3.again = true;
}

void ClockTower_FoundJournal(string qName)
{
	Log_testinfo("Всего журналов найдено " + ClockTower_JournalsQty());
	if (ClockTower_JournalsQty() >= 5)
	{
		AddQuestRecord("ClockTower", "4");
		DeleteQuestCondition("ClockTower_FoundJournal_1");
		DeleteQuestCondition("ClockTower_FoundJournal_2");
		DeleteQuestCondition("ClockTower_FoundJournal_3");
	}
}

int ClockTower_JournalsQty()
{
	return GetCharacterFreeItem(pchar, "piratesJournal_1") +
		   GetCharacterFreeItem(pchar, "piratesJournal_2") +
		   GetCharacterFreeItem(pchar, "piratesJournal_3");
}

int SellJournals()
{
	int i, j;
	int sold = 0;
	int dub = 0;
	int prices[3] = {25, 60, 125};
	string journalNames[3] = {"piratesJournal_1", "piratesJournal_2", "piratesJournal_3"};

	for(j = 0; j < 5; j++)
	{
		for(i = 0; i < 3; i++)
		{
			if(GetCharacterFreeItem(pchar, journalNames[i]) > 0 && sold < 5)
			{
				RemoveItems(pchar, journalNames[i], 1);
				dub += prices[i];
				sold++;
				break;
			}
		}
	}
    
	JournalsAchievment(sold);
	
	Log_TestInfo("Продано журналов: " + sold + " за " + dub + " дублонов");
	AddItems(pchar, "gold_dublon", dub);
	
	return dub;
}

int JournalsCost()
{
	int dub = 0;
	int sold = 0;
	int j1 = GetCharacterFreeItem(pchar, "piratesJournal_1");
	int j2 = GetCharacterFreeItem(pchar, "piratesJournal_2");
	int j3 = GetCharacterFreeItem(pchar, "piratesJournal_3");
	
	if(j1 > 0)
	{
		sold += j1;
		dub += j1 * 25;
		RemoveItems(pchar, "piratesJournal_1", j1);
	}
	if(j2 > 0)
	{
		sold += j2;
		dub += j2 * 60;
		RemoveItems(pchar, "piratesJournal_2", j2);
	}
	if(j3 > 0)
	{
		sold += j3;
		dub += j3 * 125;
		RemoveItems(pchar, "piratesJournal_3", j3);
	}
	
	JournalsAchievment(sold);
	
	AddItems(pchar, "gold_dublon", dub);
	return dub;
}

void JournalsAchievment(int sold)
{
	if(!GetAchievement("ach_CL_200"))
	{
		if(!CheckAttribute(pchar, "achievment.piratesJournals"))
		{
			pchar.achievment.piratesJournals = 0;
		}
		
		int stat = GetStat("stat_CL_200");
		int piratesJournalsQty = sti(pchar.achievment.piratesJournals) + sold;
		pchar.achievment.piratesJournals = piratesJournalsQty;
		
		if(piratesJournalsQty > stat) Achievment_SetStat(200, piratesJournalsQty - stat);
	}
}

void ClockTower_FoundJournal_cheat()
{
	AddQuestRecord("ClockTower", "4");
	DeleteQuestCondition("ClockTower_FoundJournal_1");
	DeleteQuestCondition("ClockTower_FoundJournal_2");
	DeleteQuestCondition("ClockTower_FoundJournal_3");
}

void ClockTower_InvitationToTheTower_2()// пригласили в башню на приём, второй раз
{
	DeleteQuestCondition("ClockTower_FoundJournal_1");
	DeleteQuestCondition("ClockTower_FoundJournal_2");
	DeleteQuestCondition("ClockTower_FoundJournal_3");
	sld = CharacterFromID("ClockTower_Johan");
	LAi_CharacterDisableDialog(sld);
	
	// открыть проход в башню
	LocatorReloadEnterDisable("Villemstad_town", "houseO2", false);
	
	sld = CharacterFromID("ClockTower_Visser");
	LAi_CharacterEnableDialog(sld);
	sld.dialog.filename = "Quest\ShipsPack\ClockTower_dialog.c";
	sld.dialog.currentnode = "ClockTower_Visser_21";
	AddLandQuestMark(sld, "questmarkmain");
}

void ClockTower_AmsterdamInTheHarbor()
{
	chrDisableReloadToLocation = true;

	ref sld = GetCharacter(CreateCharacterClone(CharacterFromID("ClockTower_Johan"), 0));
	sld.id = "ClockTower_Johan_Clone";
	sld.dialog.filename = "Quest\ShipsPack\ClockTower_dialog.c";
	sld.dialog.currentnode = "ClockTower_Visser_31";
	ChangeCharacterAddressGroup(sld, "Villemstad_ClockTower", "reload", "reload1");
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);

	sld = CharacterFromID("ClockTower_Visser");
	LAi_CharacterDisableDialog(sld);

	// PlaySound("Ships\snasti_skrp_006.wav");
    float x = stf(loadedLocation.locators.reload.reload1.x);
    float y = stf(loadedLocation.locators.reload.reload1.y);
    float z = stf(loadedLocation.locators.reload.reload1.z);
	SendMessage(Sound, "lslfff", MSG_SOUND_EVENT_PLAY, "Location/SP4_quest1", 0, x, y, z);
}

void ClockTower_AmsterdamInTheHarbor_2()
{
	sld = CharacterFromID("ClockTower_Visser");
	LAi_CharacterEnableDialog(sld);
}

void ClockTower_AmsterdamInTheHarbor_Kino_1()
{
	sld = CharacterFromID("ClockTower_Johan");
	LAi_LoginInCaptureTown(sld, true);
	
	StopRain();
	PChar.questTemp.NoFast = true;
	SetCurrentTime(11, 59);
	SetLocationCapturedState("Villemstad_town", true);

    // Подменим LoadSceneSound, чтобы не запускать трек
    PChar.systeminfo.stopsound = "";
    SetEventHandler("LoadSceneSound", "ClockTower_AmsterdamInTheHarbor_Kino_Sounds", 0);

	DoFunctionReloadToLocation("Villemstad_town", "goto", "goto1", "ClockTower_AmsterdamInTheHarbor_Kino_2");
}

void ClockTower_AmsterdamInTheHarbor_Kino_2()
{
	StartQuestMovie(true, false, true);
	TeleportCharacterToPos(pchar, -66.00, 9.00, -43.00);
	CreateSky(3);
	LAi_FadeToBlackStartInstantly();
	DoQuestFunctionDelay("ClockTower_AmsterdamInTheHarbor_Kino_3", 2.0);

	ref sld = GetCharacter(NPC_GenerateCharacter("ClockTower_Amsterdam", "off_hol_5", "man", "man", 10, HOLLAND, 0, true, "quest"));
	FantomMakeSmallSailor(sld, SHIP_AMSTERDAM, GetShipName("Amsterdam"), -1, 10+rand(10), 10+rand(10), 10+rand(10), 10+rand(10), 10+rand(10));
	RealShips[sti(sld.Ship.Type)].ship.upgrades.hull = 1;
	ref rShip = GetRealShip(sti(sld.Ship.Type));
	CreateEntity(sld, "ship");
	Ship_SetLightsAndFlares(sld);
	sld.Ship.Pos.x = 89.39;
	sld.Ship.Pos.z = -40.05;
	sld.Ship.Ang.y = GetAngleY(0.0,0.0);
	sld.Ship.stopped = true;
	sld.Ship.Speed.z = 0.0;
	Ship_PrepareShipForLocation(sld);
	SendMessage(sld, "laa", MSG_SHIP_CREATE, sld, rShip);

	ClockTower_AmsterdamInTheHarbor_Citizens();
}

void ClockTower_AmsterdamInTheHarbor_Citizens() // Особое событие в городе. Расставляем жителей:
{
	//Солдаты - Протекторы
	for (i=1; i<=6; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("ClockTower_SoldierProtector_"+i, "sold_hol_"+(rand(7)+1), "man", "man", sti(pchar.rank), HOLLAND, 0, true, "soldier"));
        LAi_LoginInCaptureTown(sld, true);
		LAi_SetGuardianType(sld);
		LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
		ChangeCharacterAddressGroup(sld, "Villemstad_town", "soldiers",  "protector"+i);
		LAi_CharacterDisableDialog(sld);
	}
	
	//Солдаты - Протекторы 2
	for (i=1; i<=3; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("ClockTower_SoldierProtector2_"+i, "sold_hol_"+(rand(7)+1), "man", "man", sti(pchar.rank), HOLLAND, 0, true, "soldier"));
        LAi_LoginInCaptureTown(sld, true);
		LAi_SetGuardianType(sld);
		LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
		ChangeCharacterAddressGroup(sld, "Villemstad_town", "soldiers",  "soldier"+i);
		LAi_CharacterDisableDialog(sld);
	}
	
	//Мирные жители - стоят у пирса
	for (i=1; i<=13; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("ClockTower_CitizenPirs_"+i, "citiz_"+i, "man", "man", sti(pchar.rank), HOLLAND, 0, false, "soldier"));
        LAi_LoginInCaptureTown(sld, true);
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
		ChangeCharacterAddressGroup(sld, "Villemstad_town", "reload",  "reload1");
		LAi_CharacterDisableDialog(sld);
		// 1 ряд
		if (i==1) TeleportCharacterToPosAy(sld, 30.20, 2.00, -43.00, 1.00);
		else if (i==11) TeleportCharacterToPosAy(sld, 29.90, 2.00, -42.00, 1.40);
		else if (i==3) TeleportCharacterToPosAy(sld, 29.70, 2.00, -41.00, 1.50);
		else if (i==4) TeleportCharacterToPosAy(sld, 29.00, 2.00, -40.00, 1.50);
		else if (i==5) TeleportCharacterToPosAy(sld, 29.00, 2.00, -39.00, 1.50);
		else if (i==6) TeleportCharacterToPosAy(sld, 29.70, 2.00, -38.00, 1.50);
		else if (i==7) TeleportCharacterToPosAy(sld, 29.90, 2.00, -37.00, 1.60);
		else if (i==8) TeleportCharacterToPosAy(sld, 30.20, 2.00, -36.00, 1.80);
		// 2 ряд
		else if (i==9) TeleportCharacterToPosAy(sld, 28.60, 2.00, -41.50, 1.30);
		else if (i==10) TeleportCharacterToPosAy(sld, 28.30, 2.00, -40.50, 1.40);
		else if (i==2) TeleportCharacterToPosAy(sld, 28.00, 2.00, -39.50, 1.50);
		else if (i==12) TeleportCharacterToPosAy(sld, 28.00, 2.00, -38.50, 1.40);
		else if (i==13) TeleportCharacterToPosAy(sld, 28.30, 2.00, -37.50, 1.70);
	}
	for (i=4; i<=5; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("ClockTower_CitizenPirsWoman_"+i, "women_"+i, "woman", "woman", sti(pchar.rank), HOLLAND, 0, false, "soldier"));
        LAi_LoginInCaptureTown(sld, true);
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
		ChangeCharacterAddressGroup(sld, "Villemstad_town", "reload",  "reload1");
		LAi_CharacterDisableDialog(sld);
		// 0 ряд
		if (i==4) TeleportCharacterToPosAy(sld, 30.50, 2.00, -40.50, 1.50);
		else TeleportCharacterToPosAy(sld, 30.50, 2.00, -38.50, 1.50);
	}
}

void ClockTower_AmsterdamInTheHarbor_Kino_Sounds()
{
    // Первый вызов: Катсцена
    if (!CheckAttribute(&TEV, "SP4_Static_Sounds"))
    {
        // Поставим только нужное
        ResetSound();
        SetWeatherScheme("town");
        SetStaticSounds(loadedLocation);
        // bChangeScheme вернёт false, так что после перезагрузки запустим LoadSceneSound сами
        DelEventHandler("LoadSceneSound", "ClockTower_AmsterdamInTheHarbor_Kino_Sounds");
        SetEventHandler("FaderEvent_EndFade", "ClockTower_AmsterdamInTheHarbor_Kino_Sounds", 1);
        // Звуки катсцены, чтобы потом выключить
        TEV.SP4_Static_Sounds.s1 = SendMessage(Sound, "lslfff", MSG_SOUND_EVENT_PLAY, "Location/SP4_Piple_Talk", 0, 29.00, 2.00, -39.00);
        return;
    }

    // Второй вызов: После катсцены
    DelEventHandler("FaderEvent_EndFade", "ClockTower_AmsterdamInTheHarbor_Kino_Sounds");
    DeleteAttribute(PChar, "systeminfo.stopsound");
    DeleteAttribute(&TEV, "SP4_Static_Sounds");
    ResetSound();
    PostEvent("LoadSceneSound", 500);
}

void ClockTower_AmsterdamInTheHarbor_Kino_3(string qName)
{
	LAi_FadeToBlackEnd();
	locCameraFlyToPositionLookToPoint(-43.05, 16.20, -36.76, -45.35, 17.55, -36.72, -48.45, 19.37, -36.67, -1, 9000/GetDeltaTime());

    TEV.BigClockCounter = 0;
	Pchar.FuncCameraFly = "CameraSleep";
    DelEventHandler("NextHour", "Villemstad_BigClock");
    SetEventHandler("NextHour", "ClockTower_BigClock_Sound", 0);
    SetEventHandler("ClockTower_BigClock_Sound", "ClockTower_BigClock_Sound", 0);
}

void ClockTower_BigClock_Sound()
{
    ref sld;
    int iCurQty = sti(TEV.BigClockCounter) + 1;
    if (iCurQty != 1)
    {
        locCameraResetState();
        locCameraSleep(false);
    }
    TEV.BigClockCounter = iCurQty; 
    Villemstad_BigClock_Sound();
    switch (iCurQty)
    {
        case 1: SetEventHandler("NextHour", "Villemstad_BigClock", 0);
                DelEventHandler("NextHour", "ClockTower_BigClock_Sound");
                break;
		case 2: locCameraFlyToPositionLookToPoint(-62.46, 8.00, -44.67, -62.39, 7.99, -44.29, -61.80, 7.92, -41.41,
				-1.0, 5000/GetDeltaTime());
				break;
		case 3: locCameraFlyToPositionLookToPoint(-36.83, 5.69, 7.69, -36.23, 5.67, 8.20, -34.84, 5.62, 9.37,
				-1.0, 4000/GetDeltaTime()); break;
		case 4: locCameraFlyToPositionLookToPoint(-5.04, 4.23, -3.98, -5.05, 4.23, -4.50, -5.08, 4.23, -5.83,
				-1.0, 4000/GetDeltaTime()); break;
		case 5: locCameraFlyToPositionLookToPoint(-22.58, 3.82, -23.69, -22.75, 3.83, -24.32, -23.01, 3.84, -25.26,
				-1.0, 4000/GetDeltaTime());
				sld = GetCharacter(NPC_GenerateCharacter("ClockTower_GirlRun", "whore_4", "woman", "woman_B", 5, HOLLAND, 0, false, "quest"));
				LAi_LoginInCaptureTown(sld, true);
				ChangeCharacterAddressGroup(sld, "Villemstad_town", "goto", "goto15");
				TeleportCharacterToPosAy(sld, -33.98, 2.80, -48.16, 1.50);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "goto", "goto22", "none", "", "", "", 8);
				sld = GetCharacter(NPC_GenerateCharacter("ClockTower_PoorSit", "panhandler_3", "man", "man", 5, HOLLAND, 0, false, "quest"));
				LAi_LoginInCaptureTown(sld, true);
				ChangeCharacterAddressGroup(sld, "Villemstad_town", "goto", "goto10");
				TeleportCharacterToPosAy(sld, -29.20, 3.10, -56.65, -1.00);
				LAi_SetGroundSitType(sld);
				break;
		case 6: locCameraFlyToPositionLookToPoint(-31.71, 3.69, -54.04, -31.41, 3.72, -54.54, -30.84, 3.77, -55.48,
				-1.0, 4000/GetDeltaTime()); break;
		case 7: locCameraFlyToPositionLookToPoint(-32.66, 8.32, -88.24, -32.14, 8.30, -88.30, -30.40, 8.21, -88.48,
				-1.0, 4000/GetDeltaTime()); break;
				// ракурс фронтально на весь корабль:
		case 8: locCameraFlyToPositionLookToPoint(128.15, 1.76, -39.00, 126.68, 2.04, -39.01, 123.27, 2.71, -39.02, 
				-1.0, 4000/GetDeltaTime()); break;
				// нос корабля:
		case 9: locCameraFlyToPositionLookToPoint(87.65, 5.95, -14.80, 87.80, 5.98, -15.27, 88.12, 6.06, -16.36,
				-1.0, 4000/GetDeltaTime()); break;
				// палуба 1:
		case 10: locCameraFlyToPositionLookToPoint(91.49, 7.25, -25.00, 91.45, 7.19, -25.53, 91.33, 7.01, -27.07,
				-1.0, 4000/GetDeltaTime()); break;
				// палуба 2:
		case 11: locCameraFlyToPositionLookToPoint(90.97, 4.37, -37.29, 90.96, 4.34, -37.66, 90.90, 4.27, -38.89,
				-1.0, 4000/GetDeltaTime()); break;
				// задник с названием корабля:
		case 12: locCameraFlyToPositionLookToPoint(89.51, 6.92, -66.88, 89.46, 6.78, -65.73, 89.40, 6.63, -60.22, 
				-1.0, 5000/GetDeltaTime()); break;
				// народ встречает ван Дорна на пирсе
		case 13: locCameraFlyToPositionLookToPoint(25.72, 4.40, -39.00, 26.24, 4.35, -39.01, 27.28, 4.25, -39.04,
				-1.0, 9000/GetDeltaTime());
				sld = CreateVanDoorn("ClockTower_VanDoorn", -1);
				LAi_LoginInCaptureTown(sld, true);
				FantomMakeSmallSailor(sld, SHIP_AMSTERDAM, GetShipName("Amsterdam"), CANNON_TYPE_CANNON_LBS32, 10+rand(10), 10+rand(10), 10+rand(10), 10+rand(10), 10+rand(10));
				ChangeCharacterAddressGroup(sld, "Villemstad_town", "goto", "goto31");
				TeleportCharacterToPosAy(sld, 60.50, 2.20, -40.00, -1.50);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocator(sld, "reload", "houseO2", "", -1);
				for (i=4; i<=5; i++)
				{
					sld = GetCharacter(NPC_GenerateCharacter("ClockTower_mushket_"+i, "mush_hol_"+i, "man", "mushketer", 5, HOLLAND, 0, false, "soldier"));
					LAi_LoginInCaptureTown(sld, true);
					FantomMakeCoolFighter(sld, sti(pchar.rank), 50, 50, "", "mushket1", "bullet", 0);
					ChangeCharacterAddressGroup(sld, "Villemstad_town", "goto", "goto31");
					if (i==4) TeleportCharacterToPosAy(sld, 61.50, 2.20, -39.00, -1.50);
					if (i==5) TeleportCharacterToPosAy(sld, 61.50, 2.20, -41.20, -1.50);
					LAi_SetActorType(sld);
					LAi_ActorGoToLocator(sld, "reload", "houseO2", "", -1);
				}
				Pchar.FuncCameraFly = "CameraSleep";
				DeleteAttribute(&TEV, "BigClockCounter");
                DelEventHandler("ClockTower_BigClock_Sound", "ClockTower_BigClock_Sound");
				DoQuestFunctionDelay("ClockTower_AmsterdamInTheHarbor_Kino_6", 3.0);
				return; break;
	}

	if (iCurQty == 2 || iCurQty == 12) PostEvent("ClockTower_BigClock_Sound", 4500);
	else PostEvent("ClockTower_BigClock_Sound", 3500);
}

/*void ClockTower_AmsterdamInTheHarbor_Kino_5() // ван Дорн идёт в сторону башни
{
    Pchar.FuncCameraFly = "";
	locCameraFromToPos(-39.29, 5.71, -47.95, true, -42.86, 4.18, -46.90);
	DoQuestFunctionDelay("ClockTower_AmsterdamInTheHarbor_Kino_6", 6.0);

    ref sld = CharacterFromID("ClockTower_VanDoorn");
	TeleportCharacterToPosAy(sld, -37.50, 4.00, -48.20, -1.50);
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "reload", "houseO2", "", -1);
	for (i=4; i<=5; i++)
	{
		sld = CharacterFromID("ClockTower_mushket_"+i);
		if (i==4) TeleportCharacterToPosAy(sld, -37.00, 4.00, -47.20, -1.50);
		else TeleportCharacterToPosAy(sld, -37.00, 4.00, -49.20, -1.50);
		LAi_SetActorType(sld);
		LAi_ActorGoToLocator(sld, "reload", "houseO2", "", -1);
	}
}*/

void ClockTower_AmsterdamInTheHarbor_Kino_6(string qName)
{
	LAi_FadeLong("", "");
	DoQuestFunctionDelay("ClockTower_AmsterdamInTheHarbor_Kino_7", 1.0);
}

void ClockTower_AmsterdamInTheHarbor_Kino_7(string qName)
{
	//Чистим город от квестовых жителей
	for (i=4; i<=5; i++)
	{
		sld = CharacterFromID("ClockTower_mushket_"+i);
		ChangeCharacterAddressGroup(sld, "none", "", "");
	}
	for (i=1; i<=6; i++)
	{
		sld = CharacterFromID("ClockTower_SoldierProtector_"+i);
		ChangeCharacterAddressGroup(sld, "none", "", "");
	}
	for (i=1; i<=3; i++)
	{
		sld = CharacterFromID("ClockTower_SoldierProtector2_"+i);
		ChangeCharacterAddressGroup(sld, "none", "", "");
	}
	for (i=1; i<=13; i++)
	{
		sld = CharacterFromID("ClockTower_CitizenPirs_"+i);
		ChangeCharacterAddressGroup(sld, "none", "", "");
	}
	for (i=4; i<=5; i++)
	{
		sld = CharacterFromID("ClockTower_CitizenPirsWoman_"+i);
		ChangeCharacterAddressGroup(sld, "none", "", "");
	}
	sld = CharacterFromID("ClockTower_GirlRun");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	
	sld = CharacterFromID("ClockTower_PoorSit");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	
	sld = CharacterFromID("ClockTower_VanDoorn");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	LAi_LoginInCaptureTown(sld, false);
	
	sld = CharacterFromID("ClockTower_Johan");
	LAi_LoginInCaptureTown(sld, false);

	EndQuestMovie();

    SendMessage(Sound, "lll", MSG_SOUND_EVENT_STOP, sti(TEV.SP4_Static_Sounds.s1), 0);

    DeleteAttribute(PChar, "questTemp.NoFast");
	SetLocationCapturedState("Villemstad_town", false);
	DoFunctionReloadToLocation("Villemstad_town", "reload", "houseO2", "ClockTower_AmsterdamInTheHarbor_DialogWithJohan");
}

void ClockTower_AmsterdamInTheHarbor_DialogWithJohan() // Диалог с Йоханом
{
	chrDisableReloadToLocation = true;
	PChar.GenQuest.CannotWait = true;
	locCameraResetState();
	locCameraSleep(false);
	locCameraFollowEx(true);
	
	sld = CharacterFromID("ClockTower_Johan");
	sld.dialog.filename = "Quest\ShipsPack\ClockTower_dialog.c";
	sld.dialog.currentnode = "ClockTower_Johan_41";
	LAi_CharacterEnableDialog(sld);
	AddLandQuestMark(sld, "questmarkmain");
}

void ClockTower_VisserComingTowardsUs()
{
	sld = CharacterFromID("ClockTower_Visser");
	ChangeCharacterAddressGroup(sld, "Villemstad_town", "reload", "houseO2");
	LAi_CharacterEnableDialog(sld);
	sld.dialog.filename = "Quest\ShipsPack\ClockTower_dialog.c";
	sld.dialog.currentnode = "ClockTower_Visser_37";
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "", 7, 0);
	AddLandQuestMark(sld, "questmarkmain");
	
	sld = CharacterFromID("ClockTower_Johan");
	LAi_CharacterDisableDialog(sld);
}

void ClockTower_VisserComingTowardsUs_2()
{
	LAi_SetPlayerType(pchar);
	sld = CharacterFromID("ClockTower_Visser");
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorGoToLocator(sld, "officers", "houseO2_1", "ClockTower_VisserComingTowardsUs_2_1", -1);
	
	// открыть проход в башню
	// LocatorReloadEnterDisable("Villemstad_town", "houseO2", false);
	
	SetFunctionLocatorCondition("ClockTower_VanDoornInCabinet_1", "Villemstad_town", "reload", "houseO2", false);
}

void ClockTower_VisserComingTowardsUs_3()
{
	sld = CharacterFromID("ClockTower_Visser");
	CharacterTurnAy(sld, 4.50);
}

void ClockTower_VanDoornInCabinet_1(string qName)
{
	DoFunctionReloadToLocation("Villemstad_ClockTower", "reload", "reload1", "ClockTower_VanDoornInCabinet_2");
}

void ClockTower_VanDoornInCabinet_2()
{	// ван Дорн садится в кресло
	sld = CharacterFromID("ClockTower_VanDoorn");
	sld.dialog.filename = "Quest\ShipsPack\ClockTower_dialog.c";
	sld.dialog.currentnode = "ClockTower_VanDoorn_1";
	ChangeCharacterAddressGroup(sld, "Villemstad_ClockTower", "sit", "sit1");
	LAi_SetHuberType(sld);
	LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
	AddLandQuestMark(sld, "questmarkmain");
}

void ClockTower_VanDoornInCabinet_3()
{
	chrDisableReloadToLocation = false;
	bDisableFastReload = true;
	
	ref sld = CharacterFromID("ClockTower_VanDoorn");
	LAi_CharacterDisableDialog(sld);
	
	sld = CharacterFromID("ClockTower_Visser");
	LAi_CharacterEnableDialog(sld);
	sld.dialog.filename = "Quest\ShipsPack\ClockTower_dialog.c";
	sld.dialog.currentnode = "ClockTower_Visser_41";
	LAi_SetStayTypeNoGroup(sld);
	sld.talker = 5;
}

void ClockTower_Quest_3() // Задание 3: нужно заполучить оригинал контракта
{
	AddQuestRecord("ClockTower", "5");
	DeleteAttribute(pchar, "GenQuest.CannotWait");
	bDisableFastReload = false;
	
	sld = CharacterFromID("ClockTower_Visser");
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorGoToLocation(sld, "reload", "houseO1", "", "", "", "", 20);
	sld.location = "None";
	
	sld = CharacterFromID("ClockTower_Johan");
	sld.dialog.filename = "Quest\ShipsPack\ClockTower_dialog.c";
	sld.dialog.currentnode = "ClockTower_Johan_51";
	LAi_CharacterEnableDialog(sld);
	LAi_RemoveLoginTime(sld);
	
	// в сегодняшний день нельзя прийти
	SetFunctionTimerCondition("ClockTower_NeedToComeRightDay", 0, 0, 1, false);
	
	// закрыть проход в башню
	LocatorReloadEnterDisable("Villemstad_town", "houseO2", true);
}

void ClockTower_NeedToComeRightDay(string qName)
{
	pchar.questTemp.ClockTower_NoToday = true;
	
	sld = CharacterFromID("ClockTower_Visser");
	LAi_SetLoginTime(sld, 6.0, 23.99);
	ChangeCharacterAddressGroup(sld, "GVIK", "sit", "sit5");
	LAi_SetHuberTypeNoGroup(sld);
	sld.dialog.filename = "Quest\ShipsPack\ClockTower_dialog.c";
	sld.dialog.currentnode = "ClockTower_Visser_64";
	
	sld = CharacterFromID("ClockTower_VanDoorn");
	LAi_SetLoginTime(sld, 6.0, 23.99);
	sld.dialog.filename = "Quest\ShipsPack\ClockTower_dialog.c";
	sld.dialog.currentnode = "ClockTower_OfficeServices";
	LAi_CharacterEnableDialog(sld);
}

void ClockTower_GuardianNewDay(string qName)
{
	if (CharacterIsAlive("ClockTower_Johan"))
	{
		sld = CharacterFromID("ClockTower_Johan");
		DeleteAttribute(sld, "ClockTower_repeat");
	}
	if (CharacterIsAlive("ClockTower_Peter"))
	{
		sld = CharacterFromID("ClockTower_Peter");
		DeleteAttribute(sld, "ClockTower_repeat");
	}
}

void ClockTower_RightDay()
{
	// открыть проход в башню
	LocatorReloadEnterDisable("Villemstad_town", "houseO2", false);
	
	SetFunctionTimerCondition("ClockTower_CloseTower", 0, 0, 1, false);
	
	if (CheckAttribute(pchar, "questTemp.ClockTower_NightFree"))
	{
		sld = &Locations[FindLocation("Villemstad_town")];
		sld.reload.l12.open_for_night = 0;
	}
}

void ClockTower_CloseTower(string qName)
{
	if (CheckAttribute(pchar, "questTemp.ClockTower_NightFree"))
	{
		sld = &Locations[FindLocation("Villemstad_town")];
		sld.reload.l12.open_for_night = 1;
	}
	else
	{
		// закрыть проход в башню
		LocatorReloadEnterDisable("Villemstad_town", "houseO2", true);
	}
}

void ClockTower_NightFree()
{
	// ночной доступ в башню
	LocatorReloadEnterDisable("Villemstad_town", "houseO2", false);
	pchar.questTemp.ClockTower_NightFree = true;
	sld = &Locations[FindLocation("Villemstad_town")];
	sld.reload.l12.open_for_night = 1;
	ClockTower_AddItems();
}

void ClockTower_KillToJohan()// ночное убийство Йохана
{
	StartQuestMovie(true, false, true);
	locCameraFromToPos(-53.72, 5.38, -42.69, true, -55.40, 3.61, -44.92);
	sld = CharacterFromID("ClockTower_Johan");
	SyncPlaybackDlt(PChar, sld);
	TeleportCharacterToPosAy(sld, -55.54, 3.80, -44.62, 1.50);
	LAi_SetActorTypeNoGroup(sld);
	SetCharacterActionAnimation(sld, "dead", "hit_stab");
	LAi_KillCharacter(sld);
	TeleportCharacterToPosAy(pchar, -54.64, 3.80, -44.62, -1.50);
	LAi_SetActorType(pchar);
	LAi_ActorAnimation(pchar, "stab", "", 12.0);
	SendMessage(pchar, "lslssl", MSG_CHARACTER_EX_MSG, "TieItem", FindItem("knife_01"), "knife_01", "Saber_hand", 1);
	DoQuestFunctionDelay("ClockTower_KillToJohan_kino_2", 1.6);
}

void ClockTower_KillToJohan_kino_2(string qName)
{
	locCameraFromToPos(-56.19, 6.74, -42.89, true, -55.40, 3.95, -44.26);
	DoQuestFunctionDelay("ClockTower_KillToJohan_kino_3", 2.3);
}

void ClockTower_KillToJohan_kino_3(string qName)
{
	EndQuestMovie();
	LAi_SetPlayerType(pchar);
	locCameraFollowEx(true);
	SendMessage(pchar, "lsl", MSG_CHARACTER_EX_MSG, "UntieItem", FindItem("knife_01"));
	ClockTower_NightFree();
	
	SetFunctionTimerCondition("ClockTower_SpawnPeter", 0, 0, 1, false);
}

void ClockTower_AddItems()
{
	ref itm;
	
	SetItemInLocation("purse3", "Villemstad_ClockTower", "item1");
	locations[FindLocation("Villemstad_ClockTower")].locators_radius.item.item1 = 1.0;
	
	SetItemInLocation("pistol9", "Villemstad_ClockTower", "item2");
	locations[FindLocation("Villemstad_ClockTower")].locators_radius.item.item2 = 1.0;
	
	SetItemInLocation("potionwine", "Villemstad_ClockTower", "item3");
	locations[FindLocation("Villemstad_ClockTower")].locators_radius.item.item3 = 1.0;
	
	makeref(itm,Items[FindItem("Reserve_item_13")]); //резервный предмет №13 Контракт ван Дорна
	itm.id = "VD_Contract";
	itm.name = "itmname_VD_Contract";
	itm.describe = "itmdescr_VD_Contract";
	itm.model = "letter_sp4";
	itm.picIndex = 14;
	itm.picTexture = "ITEMS_32";
	itm.Weight = 0.3;
	itm.price = 0;
	itm.ItemType = "QUESTITEMS";
	
	SetItemInLocation("VD_Contract", "Villemstad_ClockTower", "item6");
	locations[FindLocation("Villemstad_ClockTower")].locators_radius.item.item6 = 1.0;
	
	PChar.quest.ClockTower_FoundContract.win_condition.l1 = "item";
	PChar.quest.ClockTower_FoundContract.win_condition.l1.item = "VD_Contract";
	PChar.quest.ClockTower_FoundContract.function = "ClockTower_FoundContract";
	
	makeref(itm,Items[FindItem("Reserve_item_15")]); //резервный предмет №15 SP4 Документ 1
	itm.id = "Doc1Sp4";
	itm.name = "itmname_Doc1Sp4";
	itm.describe = "itmdescr_Doc1Sp4";
	itm.model = "Letter_sp2";
	itm.picIndex = 16;
	itm.picTexture = "ITEMS_34";
	itm.Weight = 0.3;
	itm.price = 0;
	itm.ItemType = "QUESTITEMS";
	
	SetItemInLocation("Doc1Sp4", "Villemstad_ClockTower", "item4");
	locations[FindLocation("Villemstad_ClockTower")].locators_radius.item.item4 = 1.0;
	
	PChar.quest.Find_Doc1Sp4.win_condition.l1 = "item";
	PChar.quest.Find_Doc1Sp4.win_condition.l1.item = "Doc1Sp4";
	PChar.quest.Find_Doc1Sp4.function = "Find_Doc1Sp4";
	
	makeref(itm,Items[FindItem("Reserve_item_16")]); //резервный предмет №16 SP4 Документ 2
	itm.id = "Doc2Sp4";
	itm.name = "itmname_Doc2Sp4";
	itm.describe = "itmdescr_Doc2Sp4";
	itm.model = "Letter_sp2";
	itm.picIndex = 16;
	itm.picTexture = "ITEMS_34";
	itm.Weight = 0.3;
	itm.price = 0;
	itm.ItemType = "QUESTITEMS";
	
	SetItemInLocation("Doc2Sp4", "Villemstad_ClockTower", "item5");
	locations[FindLocation("Villemstad_ClockTower")].locators_radius.item.item5 = 1.0;
	
	PChar.quest.Find_Doc2Sp4.win_condition.l1 = "item";
	PChar.quest.Find_Doc2Sp4.win_condition.l1.item = "Doc2Sp4";
	PChar.quest.Find_Doc2Sp4.function = "Find_Doc2Sp4";
}

void ClockTower_AddBook()
{
	pchar.questTemp.ClockTower_GotHint = true;
	ref itm;
	
	makeref(itm,Items[FindItem("Reserve_item_14")]); //резервный предмет №14 Странная книга
	itm.id = "BookSp4";
	itm.name = "itmname_BookSp4";
	itm.describe = "itmdescr_BookSp4";
	itm.model = "book_sp4";
	itm.picIndex = 14;
	itm.picTexture = "ITEMS_26";
	itm.Weight = 0.3;
	itm.price = 0;
	itm.groupID = SPECIAL_ITEM_TYPE;
	itm.ItemType = "QUESTITEMS";
	
	SetItemInLocation("BookSp4", "Villemstad_ClockTower", "item7");
	locations[FindLocation("Villemstad_ClockTower")].locators_radius.item.item7 = 1.8;
	
	makeref(itm,Items[FindItem("Reserve_item_17")]); //резервный предмет №17 Ключ к ван Дорну
	itm.id = "VD_key";
	itm.name = "itmname_VD_key";
	itm.describe = "itmdescr_VD_key";
	itm.model = "keymiddle";
	itm.picIndex = 8;
	itm.picTexture = "ITEMS_36";
	itm.Weight = 0.1;
	itm.price = 0;
	itm.useLocation = "Villemstad_ClockCellar";
	itm.useLocator = "button01";
	itm.ItemType = "QUESTITEMS";
	
	ExpandItemsArray();
	
	makeref(itm,Items[TOTAL_ITEMS - 1]); // Письмо Катарины
	itm.id = "CatharinaLetter";
	itm.name = "itmname_CatharinaLetter";
	itm.describe = "itmdescr_CatharinaLetter";
	itm.model = "";
	itm.picIndex = 6;
	itm.picTexture = "ITEMS_26";
	itm.Weight = 0.1;
	itm.price = 0;
	itm.ItemType = "QUESTITEMS";
}

void ClockTower_AddBook_FromDiegoDeLanda()
{
	ref itm;
	
	makeref(itm,Items[FindItem("Reserve_item_14")]);
	itm.id = "BookSp4";
	itm.name = "itmname_BookSp4";
	itm.describe = "itmdescr_BookSp4";
	itm.model = "book_sp4";
	itm.picIndex = 14;
	itm.picTexture = "ITEMS_26";
	itm.Weight = 0.3;
	itm.price = 0;
	itm.groupID = SPECIAL_ITEM_TYPE;
	itm.ItemType = "QUESTITEMS";
	
	makeref(itm,Items[FindItem("Reserve_item_17")]); //резервный предмет №17 Ключ к ван Дорну
	itm.id = "VD_key";
	itm.name = "itmname_VD_key";
	itm.describe = "itmdescr_VD_key";
	itm.model = "keymiddle";
	itm.picIndex = 8;
	itm.picTexture = "ITEMS_36";
	itm.Weight = 0.1;
	itm.price = 0;
	itm.useLocation = "Villemstad_ClockCellar";
	itm.useLocator = "button01";
	itm.ItemType = "QUESTITEMS";
	
	GiveItem2Character(PChar, "BookSp4");
}

void ClockTower_AddVisserKey()
{
	ref itm;
	ExpandItemsArray();
	
	makeref(itm,Items[TOTAL_ITEMS - 1]); // Ключ к Маартену Виссеру
	itm.id = "Visser_Key";
	itm.name = "itmname_Visser_Key";
	itm.describe = "itmdescr_Visser_Key";
	itm.model = "";
	itm.picIndex = 13;
	itm.picTexture = "ITEMS_32";
	itm.Weight = 0.1;
	itm.price = 0;
	itm.ItemType = "QUESTITEMS";
	
	GiveItem2Character(PChar, "Visser_Key");
}

void Find_Doc1Sp4(string qName)
{
	TakeItemFromCharacter(pchar, "Doc1Sp4");
	AddQuestRecordInfo("Doc1Sp4", "1");
}

void Find_Doc2Sp4(string qName)
{
	TakeItemFromCharacter(pchar, "Doc2Sp4");
	AddQuestRecordInfo("Doc2Sp4", "1");
}

void Open_BookSp4()
{
	LocatorReloadEnterDisable("Villemstad_ClockTower", "reload2", false);
	AddItems(pchar, "VD_key", 1);
}

void Open_Villemstad_ClockCellar()
{
	DeleteAttribute(&locations[FindLocation("Villemstad_ClockCellar")], "models.always.WineCellar_Room");
	ref loc = &Locations[FindLocation("Villemstad_ClockCellar")];
	loc.models.always.WineCellar_Room = "WineCellar_RoomOpened";
	loc.models.day.charactersPatch = "WineCellar_RoomOpened_patch";
	loc.models.night.charactersPatch = "WineCellar_RoomOpened_patch";
	
	LAi_SetActorType(pchar);
	DoQuestFunctionDelay("OpenWardrobe_Sound", 0.85);
	DoQuestFunctionDelay("Open_Villemstad_ClockCellar_2", 2.0);
}

void Open_Villemstad_ClockCellar_2(string qName)
{
	LAi_SetPlayerType(pchar);
	pchar.GenQuestBox.Villemstad_ClockCellar.box3.items.gold_dublon = 1000;
	pchar.GenQuestBox.Villemstad_ClockCellar.box3.items.spyglass5 = 1;
	pchar.GenQuestBox.Villemstad_ClockCellar.box3.items.hat6 = 1;
	if (CheckAttribute(pchar, "questTemp.ClockTower_GotHint")) pchar.GenQuestBox.Villemstad_ClockCellar.box3.items.CatharinaLetter = 1;
	
	DoFunctionReloadToLocation("Villemstad_ClockCellar", "item", "button01", "");
}

void ClockTower_SpawnPeter(string qName)
{
	sld = GetCharacter(NPC_GenerateCharacter("ClockTower_Peter", "sold_hol_14", "man", "man", 10, HOLLAND, -1, true, "soldier"));
	ForceAdaptivelevel(sld, 15, GEN_TYPE_ENEMY, GEN_MINIBOSS, GEN_ARCHETYPE_GUNMAN, GEN_ARCHETYPE_RANDOM, GEN_RANDOM_PIRATES, 0.7);
	sld.name = GetCharacterName("Peter");
	sld.lastname = "";
	sld.role = "Naval Registry Guard";
	sld.City = "Villemstad";
	sld.dialog.filename = "Quest\ShipsPack\ClockTower_dialog.c";
	sld.dialog.currentnode = "ClockTower_Peter_50";
	sld.talker = 5;
	ChangeCharacterAddressGroup(sld, "Villemstad_town", "quest", "quest3");
	LAi_SetImmortal(sld, true);
	LAi_SetGuardianType(sld);
	LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
}

void ClockTower_FoundContract(string qName)
{
	AddQuestRecord("ClockTower", "6");
	sld = CharacterFromID("ClockTower_Visser");
	sld.dialog.filename = "Quest\ShipsPack\ClockTower_dialog.c";
	sld.dialog.currentnode = "ClockTower_Visser_71";
	LAi_CharacterEnableDialog(sld);
	AddLandQuestMark(sld, "questmarkmain");
}

void ClockTower_WaitFewMonths()
{
	AddQuestRecord("ClockTower", "7");
	TakeItemFromCharacter(pchar, "VD_Contract");
	SetFunctionTimerCondition("ClockTower_NewDirector", 0, 0, 60, false);
	
	sld = CharacterFromID("ClockTower_Visser");
	sld.dialog.filename = "Quest\ShipsPack\ClockTower_dialog.c";
	sld.dialog.currentnode = "ClockTower_Visser_79";
}

void ClockTower_NewDirector(string qName)
{
	AddQuestRecord("ClockTower", "8");
	sld = CharacterFromID("ClockTower_VanDoorn");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	
	// новый директор
	locations[FindLocation("Villemstad_town")].models.always.sign_gvik = "Curacao_signs_gvik_b";
	sld = CharacterFromID("ClockTower_Visser");
	ChangeCharacterAddressGroup(sld, "Villemstad_ClockTower", "sit", "sit1");
	sld.dialog.filename = "Quest\ShipsPack\ClockTower_dialog.c";
	sld.dialog.currentnode = "ClockTower_Visser_81";
	AddLandQuestMark(sld, "questmarkmain");
	ClockTower_FreeAccess("");
}

void ClockTower_VillemstadStreet()
{
	AddQuestRecord("ClockTower", "9");
	
	sld = CharacterFromID("ClockTower_Visser");
	sld.dialog.filename = "Quest\ShipsPack\ClockTower_dialog.c";
	sld.dialog.currentnode = "ClockTower_OfficeServices";
	
	if (GetAttributeInt(pchar, "questTemp.ISawDiegoDeLanda") >= 2)
	{
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
		{
			PChar.quest.ClockTower_GirlMeets.win_condition.l1 = "location";
			PChar.quest.ClockTower_GirlMeets.win_condition.l1.location = "Villemstad_town";
			PChar.quest.ClockTower_GirlMeets.function = "ClockTower_GirlMeets";
			bDisableFastReload = true;
		}
		else
		{
			ClockTower_ExitToSea();
		}
	}
	else
	{
		ClockTower_ExitToSea();
	}
	
	//SetFunctionTimerCondition("ClockTower_FreeAccess", 0, 0, 1, false);
}

void ClockTower_FreeAccess(string qName)
{
	if (CharacterIsAlive("ClockTower_Johan"))
	{
		sld = CharacterFromID("ClockTower_Johan");
		sld.dialog.filename = "Quest\ShipsPack\ClockTower_dialog.c";
		sld.dialog.currentnode = "ClockTower_Johan_61";
		AddLandQuestMark(sld, "questmarkmain");
	}
	if (CharacterIsAlive("ClockTower_Peter"))
	{
		sld = CharacterFromID("ClockTower_Peter");
		sld.dialog.filename = "Quest\ShipsPack\ClockTower_dialog.c";
		sld.dialog.currentnode = "ClockTower_Peter_61";
		AddLandQuestMark(sld, "questmarkmain");
	}
}

void ClockTower_FreeAccess_2()
{
	if (CharacterIsAlive("ClockTower_Johan"))
	{
		sld = CharacterFromID("ClockTower_Johan");
		LAi_CharacterDisableDialog(sld);
	}
	if (CharacterIsAlive("ClockTower_Peter"))
	{
		sld = CharacterFromID("ClockTower_Peter");
		LAi_CharacterDisableDialog(sld);
	}
	DeleteQuestCondition("ClockTower_CloseTower");
	LocatorReloadEnterDisable("Villemstad_town", "houseO2", false);
	sld = &Locations[FindLocation("Villemstad_town")];
	sld.reload.l12.open_for_night = 0;
	
	sld = CharacterFromID("ClockTower_Visser");
	sld.role = "Director";
	sld = CharacterFromID("ClockTower_VanDoorn");
	sld.role = "legend";
}

void ClockTower_GirlMeets(string qName)
{
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(loadedLocation, true);
	
	if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && CharacterIsAlive("Helena"))
	{
		sld = CharacterFromID("Helena");
		sld.dialog.filename = "Quest\ShipsPack\ClockTower_dialog.c";
		sld.dialog.currentnode = "ClockTower_Helena_1";
	}
	if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && CharacterIsAlive("Mary"))
	{
		sld = CharacterFromID("Mary");
		sld.dialog.filename = "Quest\ShipsPack\ClockTower_dialog.c";
		sld.dialog.currentnode = "ClockTower_Mary_1";
	}
	ChangeCharacterAddressGroup(sld, "Villemstad_town", "goto", "goto15");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void ClockTower_Girl_DlgExit()
{
	chrDisableReloadToLocation = false;
	bDisableFastReload = false;
	LAi_LocationFightDisable(loadedLocation, false);
	
	if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && CharacterIsAlive("Helena")) ReturnOfficer_Helena();
	if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && CharacterIsAlive("Mary")) ReturnOfficer_Mary();
	
	ClockTower_ExitToSea();
}

void ClockTower_ExitToSea()
{
	PChar.quest.ClockTower_CuracaoSea.win_condition.l1 = "location";
	PChar.quest.ClockTower_CuracaoSea.win_condition.l1.location = "Curacao";
	PChar.quest.ClockTower_CuracaoSea.function = "ClockTower_CuracaoInCabin_1";
}

void ClockTower_CuracaoInCabin_1(string qName)
{
	pchar.GenQuest.CabinLock = true;
	Island_SetReloadEnableGlobal("Curacao", false);
	bQuestDisableMapEnter = true;
	
	DoQuestFunctionDelay("ClockTower_CuracaoInCabin_2", 2.5);
}

void ClockTower_CuracaoInCabin_2(string qName)
{
	DeleteAttribute(pchar, "GenQuest.CabinLock");
	pchar.GenQuest.DontSetCabinOfficer = true;
	chrDisableReloadToLocation = true;
	Sea_CabinStartNow();
	
	sld = GetCharacter(NPC_GenerateCharacter("ClockTower_Alonso", "Alonso", "man", "man", sti(pchar.rank), pchar.nation, 0, false, "soldier"));
	sld.name = GetCharacterName("Alonso");
	sld.lastname = "";
	GiveItem2Character(sld, "blade_10");
	EquipCharacterByItem(sld, "blade_10");
	ChangeCharacterAddressGroup(sld, Get_My_Cabin(), "rld", "loc1");
	DoQuestFunctionDelay("ClockTower_CuracaoInCabin_3", 1.8);
}

void ClockTower_CuracaoInCabin_3(string qName)
{
	sld = CharacterFromID("ClockTower_Alonso");
	sld.dialog.filename = "Quest\ShipsPack\ClockTower_dialog.c";
	sld.dialog.currentnode = "ClockTower_Alonso_1";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void ClockTower_CuracaoInCabin_4_DlgExit()
{
	if (CheckPassengerInCharacter(pchar, "Irons")) // Томми
	{
		sld = CharacterFromID("Irons");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "ClockTower_CuracaoInCabin_4_1", 10);
	}
	else
	{
		ClockTower_CuracaoInCabin_5();
	}
	sld = CharacterFromID("ClockTower_Alonso");
	LAi_CharacterDisableDialog(sld);
	
}

void ClockTower_TommyInCabin()
{
	sld = CharacterFromID("ClockTower_Alonso");
	LAi_CharacterDisableDialog(sld);
	
	sld = CharacterFromID("Irons");
	ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
	sld.dialog.filename = "Quest\ShipsPack\ClockTower_dialog.c";
	sld.dialog.currentnode = "ClockTower_Alonso_4_2";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	
	PlaySound("Ships\snasti_skrp_006.wav");
}

void ClockTower_TommyInCabin_2()
{
	sld = CharacterFromID("ClockTower_Alonso");
	LAi_CharacterEnableDialog(sld);
	StartInstantDialogTurnToNPC("ClockTower_Alonso", "ClockTower_Alonso_4_4", "Quest\ShipsPack\ClockTower_dialog.c", "Irons");
}

void ClockTower_CuracaoInCabin_5()
{
	if (CheckPassengerInCharacter(pchar, "Irons")) ReturnOfficer_Irons();
	DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
	Island_SetReloadEnableGlobal("Curacao", true);
	bQuestDisableMapEnter = false;
	chrDisableReloadToLocation = false;
	
    ref sld = CharacterFromId("ClockTower_VanDoorn");
    sld.lifeday = 0;
	//Запускается пожарная бригада
	SetFunctionTimerCondition("ClockTower_FireBrigadeExt_hol", 0, 0, 5, true);
}

void ClockTower_AfterBoarding()
{
	if (CharacterIsAlive("DiegoDeLanda")) ClockTower_DiegoDeLandaInTower(); // если живой Диего де Ланда, то появится в башне
	else ClockTower_VisserWait(); // в противном случае Диего не будет, и в башне нас ждёт Виссер
}

void ClockTower_DiegoDeLandaInTower()
{
	sld = CharacterFromID("ClockTower_Visser");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	
	sld = CharacterFromID("DiegoDeLanda");
	sld.dialog.filename = "Quest\ShipsPack\DiegoDeLanda_dialog.c";
	sld.dialog.currentnode = "DiegoDeLanda_Meeting";
	LAi_SetHuberType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
	ChangeCharacterAddressGroup(sld, "Villemstad_ClockTower", "sit", "sit1");
	AddLandQuestMark(sld, "questmarkmain");
	
	ref sld = &Locations[FindLocation("Villemstad_ClockTower")];
	sld.QuestlockWeather.hours = 23;
	sld.QuestlockWeather.minutes = 00;
	SetFunctionLocationCondition("ClockTower_DiegoDeLandaInTower_ISawDiego", "Villemstad_ClockTower", false);
}

void ClockTower_DiegoDeLandaInTower_ISawDiego(string qName)
{
	chrDisableReloadToLocation = true;
	pchar.questTemp.ISawDiegoDeLanda = sti(pchar.questTemp.ISawDiegoDeLanda) + 1; // встретил Диего де Ланда
	pchar.questTemp.DiegoDeLanda_ClockTower = true;
	// ref sld = &Locations[FindLocation("Villemstad_ClockTower")];
	// DeleteAttribute(sld, "QuestlockWeather");
	SetFunctionTimerCondition("ClockTower_VisserBack", 0, 0, 1, false);
}

void ClockTower_VisserBack(string qName)
{
	ClockTower_VisserWait();
}

void ClockTower_VisserWait()
{
	sld = CharacterFromID("ClockTower_Visser");
	sld.dialog.filename = "Quest\ShipsPack\ClockTower_dialog.c";
	sld.dialog.currentnode = "ClockTower_Visser_101";
	ChangeCharacterAddressGroup(sld, "Villemstad_ClockTower", "sit", "sit1");
	LAi_SetHuberTypeNoGroup(sld);
	AddLandQuestMark(sld, "questmarkmain");
}

void ClockTower_Visser_pausa_1()
{
	EndBattleLandInterface();
	LAi_SetStayType(pchar);
	DoQuestFunctionDelay("ClockTower_Visser_pausa_2", 2.0);
}

void ClockTower_Visser_pausa_2(string qName)
{
	sld = CharacterFromID("ClockTower_Visser");
	LAi_SetActorType(sld);
	LAi_ActorSetHuberMode(sld);
	sld.dialog.filename = "Quest\ShipsPack\ClockTower_dialog.c";
	sld.dialog.currentnode = "ClockTower_Visser_121";
	LAi_ActorDialogNow(sld, Pchar, "", -1);
}

void ClockTower_FINAL()
{
	CloseQuestHeader("ClockTower");
	StartBattleLandInterface();
	LAi_SetPlayerType(pchar);
	sld = CharacterFromID("ClockTower_Visser");
	LAi_SetHuberTypeNoGroup(sld);
	sld.dialog.filename = "Quest\ShipsPack\ClockTower_dialog.c";
	sld.dialog.currentnode = "ClockTower_OfficeServices";
	
	// Фрегат Амстердам больше не триггерит голландские города
	DeleteAttribute(pchar, "questTemp.ClockTower_AmsterdamCheck");
}

//=======================================================
bool ClockTower_QuestComplete(string sQuestName, string qname)
{

	ref sld;
	int i, n; 
	
	bool condition = true;
	
	if (sQuestName == "ClockTower_VisserComingTowardsUs_2_1")
	{
		ClockTower_VisserComingTowardsUs_3();
	}
	else if (sQuestName == "ClockTower_CuracaoInCabin_4_1")
	{
		ClockTower_CuracaoInCabin_5();
	}
	else if (sQuestName == "ClockTower_3")
	{
		
	}
	else
	{
		condition = false;
	}
	
	return condition;
}

void ClockTower_FireBrigadeExt_hol(string qName) // Temp-SP4-Joker
{
	if (wdmGetNationThreat(HOLLAND) > 3 && !CharacterIsAlive("ClockTower_HWIC_Cap01"))
	{
		ref sld;
		string sCapId = "ClockTower_HWIC_Cap0";
		string sGroup = "Sea_" + sCapId + "1";
		Group_DeleteGroup(sGroup);
		Group_FindOrCreateGroup(sGroup);

		int iClass;
		int iDays = 6 + rand(6);
		for (int i = 1; i <= 6; i++)
		{
			if(i == 1)
			{
				sld = CreateVanDoorn("ClockTower_HWIC_Cap01", iDays + 1);
				sld.role = "legend";
				sld.Ship.Type = GenerateShipExt(SHIP_AMSTERDAM, true, sld);
				sld.Ship.Name = GetShipName("Amsterdam");
				sld.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS32;
				RealShips[sti(sld.Ship.Type)].ship.upgrades.hull = 1;
				sld.QuestHandler = "ClockTower_HolBrigadeInterruption";
				sld.DontClearDead = true;
				sld.SaveItemsForDead = true;
				pchar.questTemp.ClockTower_AmsterdamCheck = true;
				FaceMaker(sld);
				CirassMaker(sld);
				SetBaseShipData(sld);
				DeleteAttribute(sld,"ship.sails");
				DeleteAttribute(sld,"ship.masts");
				DeleteAttribute(sld,"ship.blots");
				DeleteAttribute(sld,"ship.hulls");
				Fantom_SetBalls(sld, "war");
				SetCrewQuantityFull(sld);
				AddCrewMorale(sld, 100);
				ChangeCrewExp(sld, "Sailors", 100);
				ChangeCrewExp(sld, "Cannoners", 100);
				ChangeCrewExp(sld, "Soldiers", 100);
			}
			else
			{
				sld = GetCharacter(NPC_GenerateCharacter(sCapId + i, "off_hol_2", "man", "man", 5, HOLLAND, iDays + 1, true, "hunter"));
				switch (i)
				{
					case 2: iClass = 3; sld.GenShip.Spec = SHIP_SPEC_RAIDER; sld.model = "citiz_60";     break;
					case 3: iClass = 3; sld.GenShip.Spec = SHIP_SPEC_RAIDER; sld.model = "off_hol_5";    break;
					case 4: iClass = 2; sld.GenShip.Spec = SHIP_SPEC_UNIVERSAL; sld.model = "mercen_14"; break;
					case 5: iClass = 2; sld.GenShip.Spec = SHIP_SPEC_WAR; sld.model = "off_hol_6";       break;
					case 6: iClass = 3; sld.GenShip.Spec = SHIP_SPEC_WAR; sld.model = "mercen_22";       break;
				}

				if(i == 2)
				{
					sld.name = GetCharacterName("Jan");
					sld.lastname = GetCharacterName("Brouwer");
				}
				if(i == 3)
				{
					sld.name = GetCharacterName("Bartel");
					sld.lastname = GetCharacterName("van der Waerden");
				}
				if(i == 4)
				{
					sld.name = GetCharacterName("Niels");
					sld.lastname = GetCharacterName("Ferguson");
				}
				if(i == 5)
				{
					sld.name = GetCharacterName("Willebrord");
					sld.lastname = GetCharacterName("Snellius");
				}
				if(i == 6)
				{
					sld.name = GetCharacterName("Thomas");
					sld.lastname = GetCharacterName("Stieltjes");
				}
				
				sld.PhantomType = "officer";
				FaceMaker(sld);
				CirassMaker(sld);

				sld.GenShip.Class = iClass;
				SetShipHunter(sld);
			}
			//Fantom_SetPrize(sld);
			SetFantomParamHunter(sld);
			sld.WatchFort = true;
			sld.AlwaysEnemy = true;
			sld.DontRansackCaptain = true;
			sld.AlwaysSandbankManeuver = true;
			sld.mapEnc.type = "war";
			sld.mapEnc.Name = XI_ConvertString("Punitive expedition");
			sld.mapEnc.worldMapShip = "amsterdam_sp4";
			sld.mapEnc.NoSkip = "";
			sld.mapEnc.Marker = "BigBrigadier";
			sld.hunter = "hunter";
			Group_AddCharacter(sGroup, sCapId + i);
			if (i == 1) RealShips[sti(sld.Ship.Type)].ShipSails.Gerald_Name = "hol_4.tga.tx";
			else if (i == 4 || i == 5) RealShips[sti(sld.Ship.Type)].ShipSails.Gerald_Name = "hol_1.tga.tx";

            if(i == 1)
            {
                DeleteAttribute(sld, "items");
                sld.items = "";
                ForceAdaptiveLevel(sld, 20, GEN_TYPE_ENEMY, GEN_BOSS, GEN_ARCHETYPE_PEASANT, GEN_ARCHETYPE_TREASURER, GEN_RANDOM_PIRATES, 0.6);
                GiveCaptainOfficers(sld, true);
                GiveItem2Character(sld, "blade_27");
                EquipCharacterByItem(sld, "blade_27");
                GiveItem2Character(sld, "cirass4");
                EquipCharacterByItem(sld, "cirass4");
                GiveItem2Character(sld, "pistol15");
                EquipCharacterByItem(sld, "pistol15");
                TakeNItems(sld, "cartridge", 30);
                LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "cartridge");
                TakeNItems(sld, "potion4", 5);
                sld.SaveItemsForDead = true;
                sld.DontClearDead = true;
            }
        }

		Group_SetGroupCommander(sGroup, sCapId + "1");
		Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
		Group_LockTask(sGroup);

		UpdatePlayerSquadronPower(); // Актуализируем
		if(wdmCompareEncPower(HOLLAND)) Map_CreateTrader("", "", sCapId + "1", iDays);
		else Map_CreateWarrior("", sCapId + "1", iDays);
	}

	SetFunctionTimerCondition("ClockTower_FireBrigadeExt_hol", 0, 0, 5 + rand(4), true);
}

ref CreateVanDoorn(string id, int lifeday)
{
	ref sld = GetCharacter(NPC_GenerateCharacter(id, "off_hol_5", "man", "man", sti(pchar.rank), HOLLAND, lifeday, false, "quest"));
	sld.name = GetCharacterName("Hendrik");
	sld.lastname = GetCharacterName("van Doorn");
	//sld.greeting = ""; // to_do
	sld.role = "Director";
	sld.City = "Villemstad";
	FantomMakeCoolFighter(sld, 15, 100, 100, "blade_20", "pistol5", "cartridge", 0);
	ForceAdaptivelevel(sld, 15, GEN_TYPE_ENEMY, GEN_BOSS, GEN_ARCHETYPE_PIRATE, GEN_ARCHETYPE_NAVIGATOR, GEN_RANDOM_PIRATES, 0.7);
	AddItems(sld, "gold_dublon", 200);
	AddItems(sld, "cartridge", 10);
	return sld;
}

void ClockTower_BrigadeRefresh(ref rCaptain)
{
    if(CheckAttribute(&TEV, "HWIC_FreezeRefresh"))
    {
        DeleteAttribute(&TEV, "HWIC_FreezeRefresh");
        return;
    }
    rCaptain.lifeday = 0;
    SetFunctionTimerCondition("ClockTower_FireBrigadeExt_hol", 0, 0, 3 + rand(3), true);
}

void ClockTower_HolBrigadeInterruption(ref rCaptain)
{
	// Убежать
	PChar.quest.ClockTower_HolBrigadeEscape.win_condition.l1 = "ExitFromSea";
	PChar.quest.ClockTower_HolBrigadeEscape.function = "ClockTower_HolBrigadeEscape";
	// Потопить
	PChar.quest.ClockTower_HolBrigadeSink.win_condition.l1 = "Character_sink";
	PChar.quest.ClockTower_HolBrigadeSink.win_condition.l1.character = rCaptain.id;
	PChar.quest.ClockTower_HolBrigadeSink.function = "ClockTower_HolBrigadeSink";
	// Захватить
	PChar.quest.ClockTower_HolBrigadeCapture.win_condition.l1 = "Character_Capture";
	PChar.quest.ClockTower_HolBrigadeCapture.win_condition.l1.character = rCaptain.id;
	PChar.quest.ClockTower_HolBrigadeCapture.function = "ClockTower_HolBrigadeCapture";
}

void ClockTower_HolBrigadeEscape(string qName)
{
	DeleteQuestCondition("ClockTower_HolBrigadeSink");
	DeleteQuestCondition("ClockTower_HolBrigadeCapture");
	TEV.HWIC_FreezeRefresh = "";
	Map_ReleaseQuestEncounter("ClockTower_HWIC_Cap01");
	ref sld = CharacterFromID("ClockTower_HWIC_Cap01");
	sld.lifeday = 0;
	Group_DeleteGroup("Sea_ClockTower_HWIC_Cap01");
	SetFunctionTimerCondition("ClockTower_FireBrigadeExt_hol", 0, 0, 5 + rand(4), true);
}

void ClockTower_HolBrigadeSink(string qName)
{
	DeleteQuestCondition("ClockTower_HolBrigadeEscape");
	DeleteQuestCondition("ClockTower_HolBrigadeCapture");
	DeleteQuestCondition("ClockTower_FireBrigadeExt_hol");
	TEV.HWIC_FreezeRefresh = "";

	// Нулим отношения по выходу
	sTemp = "NationIntimidated" + NationShortName(HOLLAND);
	PChar.quest.(sTemp).win_condition.l1 = "ExitFromSea";
	PChar.quest.(sTemp).function = "NationIntimidated";
	PChar.quest.(sTemp).Nation = HOLLAND;

	ref rItem = ItemsFromID("CatharinaLetter"); // ??
	rItem.price = 100;

	// Провал квеста
	CloseQuestHeader("ClockTower");
}

void ClockTower_HolBrigadeCapture(string qName)
{
	DeleteQuestCondition("ClockTower_HolBrigadeEscape");
	DeleteQuestCondition("ClockTower_HolBrigadeSink");
	DeleteQuestCondition("ClockTower_FireBrigadeExt_hol");
	TEV.HWIC_FreezeRefresh = "";

	// Нулим отношения по выходу
	sTemp = "NationIntimidated" + NationShortName(HOLLAND);
	PChar.quest.(sTemp).win_condition.l1 = "ExitFromSea";
	PChar.quest.(sTemp).function = "NationIntimidated";
	PChar.quest.(sTemp).Nation = HOLLAND;

	ref rItem = ItemsFromID("CatharinaLetter");
	rItem.price = 100;

	//Ачивки
	Achievment_Set("ach_CL_196");
	if (sti(PChar.rank) <= 19) Achievment_Set("ach_CL_195");
	if (CheckAttribute(PChar, "questTemp.ClockTower_KillVanDornAnyway")) Achievment_Set("ach_CL_198");

	// Продолжение квеста
	ClockTower_AfterBoarding();
}

void ClockTower_CabinFight(ref _boarding_enemy, ref _callback)
{
	LAi_SetFightMode(pchar, false);
	LAi_LockFightMode(pchar, true);
	LAi_group_SetCheckEvent(LAI_GROUP_BRDENEMY);

	ref chr = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
	chr.Dialog.FileName = "Quest\ShipsPack\ClockTower_dialog.c";
	chr.Dialog.CurrentNode = "ClockTower_VanDoorn_21";
	LAi_SetActorType(chr);
	LAi_ActorDialog(chr, pchar, "", -1, 0);
}

void ClockTower_InitOfficersInCabin()
{
	// Первый офицер
	ref chr = GetCharacter(NPC_GenerateCharacter("ClockTower_VanDorn_officer_1", "quest_off_holl", "man", "man", 15, pchar.nation, 0, false, "quest"));
	GiveItem2Character(chr, "blade_26");
	EquipCharacterByItem(chr, "blade_26");
	GiveItem2Character(chr, "cirass6");
	EquipCharacterByItem(chr, "cirass6");
	TakeNItems(chr, "potionwine", 4);
	TakeNItems(chr, "potion2", 3);
	ForceAdaptivelevel(chr, 27, GEN_TYPE_ENEMY, GEN_ELITE, GEN_ARCHETYPE_DUELIST, GEN_ARCHETYPE_FREE, GEN_RANDOM_PIRATES, 0.65);
	ChangeCharacterAddressGroup(chr, pchar.location, "officers", "stay1");
	LAi_SetWarriorType(chr);
	LAi_group_MoveCharacter(chr, LAI_GROUP_PEACE);
	chr.SaveItemsForDead = true;
	chr.DontClearDead = true;

	// Второй офицер
	chr = GetCharacter(NPC_GenerateCharacter("ClockTower_VanDorn_officer_2", "off_hol_2", "man", "man", 15, pchar.nation, 0, false, "quest"));
	GiveItem2Character(chr, "blade_29");
	EquipCharacterByItem(chr, "blade_29");
	GiveItem2Character(chr, "cirass8");
	EquipCharacterByItem(chr, "cirass8");
	TakeNItems(chr, "potion2", 4);
	ForceAdaptivelevel(chr, 27, GEN_TYPE_ENEMY, GEN_ELITE, GEN_ARCHETYPE_PIRATE, GEN_ARCHETYPE_FREE, GEN_RANDOM_PIRATES, 0.65);
	LAi_SetWarriorType(chr);
	ChangeCharacterAddressGroup(chr, pchar.location, "officers", "stay2");
	LAi_group_MoveCharacter(chr, LAI_GROUP_PEACE);
	chr.SaveItemsForDead = true;
	chr.DontClearDead = true;

	// Третий офицер
	chr = GetCharacter(NPC_GenerateCharacter("ClockTower_VanDorn_officer_3", "ozg_martin", "man", "man", 15, pchar.nation, 0, false, "quest"));
	GiveItem2Character(chr, "topor_04");
	EquipCharacterByItem(chr, "topor_04");
	GiveItem2Character(chr, "cirass2");
	EquipCharacterByItem(chr, "cirass2");
	TakeNItems(chr, "potion2", 2);
	TakeNItems(chr, "berserker_potion", 1);
	ForceAdaptivelevel(chr, 27, GEN_TYPE_ENEMY, GEN_ELITE, GEN_ARCHETYPE_SOLDIER, GEN_ARCHETYPE_FREE, GEN_RANDOM_PIRATES, 0.65);
	LAi_SetCheckMinHPCallback(chr, LAi_GetCharacterMaxHP(chr)*0.5, false, "LAi_UseBerserkPotion"); // тинктура
	LAi_SetWarriorType(chr);
	ChangeCharacterAddressGroup(chr, pchar.location, "rld", "loc2");
	LAi_group_MoveCharacter(chr, LAI_GROUP_PEACE);
	chr.SaveItemsForDead = true;
	chr.DontClearDead = true;
}

void ClockTower_CabinFight2()
{
	if (CheckAttribute(pchar, "questTemp.ClockTower_GaveCatharinaLetter"))
	{	
		ChangeCharacterComplexReputation(pchar, "nobility", -12);
		pchar.questTemp.ClockTower_KillVanDornAnyway = true;
	}
	LAi_SetFightMode(pchar, true);

    ref chr;
	for (i=1; i<=3; i++)
	{
		chr = CharacterFromID("ClockTower_VanDorn_officer_"+i);
		LAi_SetWarriorType(chr);
		LAi_group_MoveCharacter(chr, LAI_GROUP_BRDENEMY);
	}

	chr = GetCharacter(NPC_GenerateCharacter("ClockTower_Alonso", "Alonso", "man", "man", 25, pchar.nation, 0, true, "soldier"));
	chr.name = GetCharacterName("Alonso");
	chr.lastname = "";
	FantomMakeCoolFighter(chr, 15, 50, 50, "blade_13", "pistol6", "bullet", 300);
	ForceAdaptivelevel(chr, 27, GEN_TYPE_ENEMY, GEN_ELITE, GEN_ARCHETYPE_RANDOM, GEN_ARCHETYPE_FREE, GEN_RANDOM_PIRATES, 0.65);
	ChangeCharacterAddressGroup(chr, PChar.location, "reload", "reload1");
	LAi_SetWarriorType(chr);
	LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER);

	if (GetCharacterIndex("Irons") != -1 && CheckPassengerInCharacter(pchar, "Irons"))
	{
		chr = CharacterFromID("Irons");
	}

	ChangeCharacterAddressGroup(chr, PChar.location, "reload", "reload1");
	LAi_SetWarriorType(chr);
	LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER);

	if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && CheckPassengerInCharacter(pchar, "Mary"))
	{
		chr = CharacterFromID("Mary");
	}
	else if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena"))
	{
		chr = CharacterFromID("Helena");
	}
	else return;

	ChangeCharacterAddressGroup(chr, PChar.location, "reload", "reload1");
	LAi_SetWarriorType(chr);
	LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER);
}

void ClockTower_cabinPeace()
{
	ChangeCharacterComplexReputation(pchar, "nobility", 6);
	
	ref chr = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
	LAi_SetActorType(chr);
	LAi_group_MoveCharacter(chr, LAI_GROUP_PEACE);
	sld.lifeday = 0;
	
	for (i=1; i<=3; i++)
	{
		chr = CharacterFromID("ClockTower_VanDorn_officer_"+i);
		LAi_SetActorType(chr);
		LAi_group_MoveCharacter(chr, LAI_GROUP_PEACE);
	}
	
	PostEvent("LAi_event_boarding_EnableReload", 5000);
}

void ClockTower_AddJournals()
{
	if (CheckAttribute(pchar, "questTemp.SP4_PiratesJournals")) return;

	pchar.questTemp.SP4_PiratesJournals = true;
	object newItem;
	ref item;
	newItem.id = "piratesJournal_1";
	newItem.name = "itmname_piratesJournal_1";
	newItem.describe = "itmdescr_piratesJournal_1";
	newItem.model = "";
	newItem.picIndex = 1;
	newItem.picTexture = "ITEMS_42";
	newItem.Weight = 0.3;
	newItem.price = 0;
	newItem.ItemType = "SUPPORT";
	newItem.TradeType = ITEM_TRADE_NORMAL;
	newItem.groupID	= TOOL_ITEM_TYPE;
	newItem.kind = JOB_NAVIGATOR;
	item = InitNewItem(&newItem);
	AddDescriptor(item, item.kind, -1);
	AddSpecialDescriptor(item, "piratesJournal");

	newItem.id = "piratesJournal_2";
	newItem.name = "itmname_piratesJournal_2";
	newItem.describe = "itmdescr_piratesJournal_2";
	newItem.picIndex = 2;
	newItem.picTexture = "ITEMS_42";
	newItem.kind = JOB_TREASURER;
	item = InitNewItem(&newItem);
	AddDescriptor(item, item.kind, -1);
	AddSpecialDescriptor(item, "piratesJournal");
	
	newItem.id = "piratesJournal_3";
	newItem.name = "itmname_piratesJournal_3";
	newItem.describe = "itmdescr_piratesJournal_3";
	newItem.picIndex = 3;
	newItem.picTexture = "ITEMS_42";
	newItem.kind = JOB_CARPENTER;
	item = InitNewItem(&newItem);
	AddDescriptor(item, item.kind, -1);
	AddSpecialDescriptor(item, "piratesJournal");
}
