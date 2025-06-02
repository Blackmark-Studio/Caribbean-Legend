void LadyBeth_init()
{
	pchar.questTemp.LadyBeth = true;
	log_testinfo("Инициализация ШНЯВЫ");
	pchar.questTemp.LadyBeth.stage = 1; // стадии меняем при выходе на карту
	pchar.questTemp.LadyBeth.colony = LadyBeth_findColony(sti(pchar.questTemp.LadyBeth.stage)); // колонии меняем при заходе в порт
    ref sld, itm;
	
	// характеристики запишем после ТЗ
	sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_cap", "quest_off_eng", "man", "man", 30, ENGLAND, -1, false, "governor"));
	FantomMakeCoolSailor(sld, SHIP_LADYBETH, GetConvertStr("LadyBeth_Ship_Name", "LadyBeth.txt"), CANNON_TYPE_CANNON_LBS24, 105, 105, 105);
	FantomMakeCoolFighter(sld, 30, 70, 70, "blade_15", "pistol6", "bullet", 200);
	SetCaptanModelByEncType(sld, "war");
	sld.ship.Crew.Morale = 100;
	ChangeCrewExp(sld, "Sailors",   100);
	ChangeCrewExp(sld, "Cannoners", 100);
	ChangeCrewExp(sld, "Soldiers",  100); 
	LAi_SetHP(sld, 200 + makeint(pchar.rank) * 2, 200 + makeint(pchar.rank) * 2);
	SetAllPerksToChar(sld, true);
	sld.name = GetConvertStr("LadyBeth_Cap_Name", "LadyBeth.txt");
	sld.lastname = GetConvertStr("LadyBeth_Cap_lastname", "LadyBeth.txt");
	UpgradeShipParameter(sld, "SpeedRate");	//апгрейдить скорость
	UpgradeShipParameter(sld, "TurnRate");	//манёвренность 
	sld.DontRansackCaptain = true; //квестовые не сдаются
	SetSPECIAL(sld, 10, 10, 10, 10, 10, 10, 10);
	SetSelfSkill(sld, 100, 100, 100, 100, 100);
	SetShipSkill(sld, 100, 100, 100, 100, 100, 100, 100, 100, 100);
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	sld.DontHitInStorm = true;
	//Предметы
	AddItems(sld, "harpoon", 20);
	AddItems(sld, "potion4", 5);
	GiveItem2Character(sld, "cirass1");
	EquipCharacterByItem(sld, "cirass1");
	GiveItem2Character(sld, "amulet_8");
	GiveItem2Character(sld, "amulet_10");
	GiveItem2Character(sld, "obereg_11");
	//Товары в трюме
	SetCharacterGoods(sld, GOOD_POWDER, 3000);
	SetCharacterGoods(sld, GOOD_BALLS, 1000);
	SetCharacterGoods(sld, GOOD_GRAPES, 1000);
	SetCharacterGoods(sld, GOOD_KNIPPELS, 1000);
	SetCharacterGoods(sld, GOOD_BOMBS, 1000);
	
	string sGroup = "Sea_"+sld.id
	Group_FindOrCreateGroup(sGroup);
	Group_SetType(sGroup,"trade");
    Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
    Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation));
	
	sld.quest = "InMap";
	sld.city = LadyBeth_findColony(sti(pchar.questTemp.LadyBeth.stage));
	sld.quest.targetCity = LadyBeth_findColony(sti(pchar.questTemp.LadyBeth.stage)+1);
	sld.mapEnc.type = "trade";
	sld.mapEnc.worldMapShip = "shnyava_sp2";
	sld.mapEnc.Name = GetConvertStr("LadyBeth_Ship_Name", "LadyBeth.txt");
	Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, 30);
	
	//общий слух
	AddSimpleRumourAllNations(GetConvertStr("LadyBeth_Rum1", "LadyBeth.txt"), 30, 1);
}

string LadyBeth_findColony(int stage)
{
	switch(stage)
	{
		case 1: return "BasTer"; break;
		case 2: return "FortFrance"; break;
		case 3: return "Charles"; break;
		case 4: return "Tortuga"; break;
		case 5: return "BasTer"; break;
		case 6: return "Shore16"; break;
	}
}

void LadyBeth_ToCity(string sChar)
{
	if(!GetDLCenabled(DLC_APPID_5)) return;
	if(!CharacterIsAlive(sChar)) {Log_testinfo("Капитан ШНЯВЫ умер"); return;}
	pchar.questTemp.LadyBeth.colony = LadyBeth_findColony(sti(pchar.questTemp.LadyBeth.stage)+1);
	Log_testinfo("капитан шнявы сошёл в порту "+ pchar.questTemp.LadyBeth.colony);
	
	DeleteQuestCheck("LadyBeth_MapRelease");
	
	//таймер через сколько опять выйти на карту
	int Qty = 3; //через сколько дней выйдем на карту
	if(pchar.questTemp.LadyBeth.colony == "Shore16") Qty = 14;
	PChar.quest.LadyBeth_toMap.win_condition.l1            = "Timer";
    PChar.quest.LadyBeth_toMap.win_condition.l1.date.day   = GetAddingDataDay(0, 0, Qty);
    PChar.quest.LadyBeth_toMap.win_condition.l1.date.month = GetAddingDataMonth(0, 0, Qty);
    PChar.quest.LadyBeth_toMap.win_condition.l1.date.year  = GetAddingDataYear(0, 0, Qty);
    PChar.quest.LadyBeth_toMap.function					   = "LadyBeth_toMap";
	
	ref sld = &characters[GetCharacterIndex(sChar)];
	sld.quest = "InCity"; //флаг кэпа ходит по городу или острову
	sld.City = sld.quest.targetCity; //аттрибут текущего города пропишем
	sld.DontDeskTalk = true; //нельзя выслать шлюпку
	if(CheckAttribute(sld, "SinkTenPercent")) DeleteAttribute(sld, "SinkTenPercent");
	
	// отдельное условие для замеса на каймане
	if(pchar.questTemp.LadyBeth.colony == "Shore16")
	{
		SetQMtoCaiman();
		SetFunctionLocationCondition("LadyBeth_CaimanSea", "Caiman", false);
		return;
	}
	
	int iColony = FindColony(sld.City);
	//стоит на рейде в порту
	string sGroup = "Sea_" + sld.id;
	Group_FindOrCreateGroup(sGroup);
	Group_AddCharacter(sGroup, sld.id);			
	Group_SetGroupCommander(sGroup, sld.id);
	Group_SetType(sGroup, "war");
	Group_SetAddress(sGroup, colonies[iColony].island, "quest_ships", "Quest_ship_"+(rand(2)+1));
	Group_SetTaskNone(sGroup);
	
	//ставим ограничения в колонии, где находится капитан
	pchar.questTemp.LadyBeth.CaptainInColony = pchar.questTemp.LadyBeth.colony;
	//тавернщик не даёт комнату
	sld = CharacterFromID(pchar.questTemp.LadyBeth.colony + "_tavernkeeper");
	sld.quest.LadyBeth = true;
	//ростовщик даёт больше дублонов
	if(CheckAttribute(pchar, "questTemp.LadyBeth_Usurer")) DeleteAttribute(pchar, "questTemp.LadyBeth_Usurer");
	//можно зайти в комнату в таверне
	LocatorReloadEnterDisable(pchar.questTemp.LadyBeth.colony + "_tavern", "reload2_back", false);
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.questTemp.LadyBeth.colony + "_tavern_upstairs")], true);
	//сидит в своей комнате таверны
	sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_clone_tavern", "quest_off_eng", "man", "man", 30, ENGLAND, -1, false, "governor"));
	sld.name = GetConvertStr("LadyBeth_Cap_Name", "LadyBeth.txt");
	sld.lastname = GetConvertStr("LadyBeth_Cap_lastname", "LadyBeth.txt");
	FantomMakeCoolFighter(sld, 30, 70, 70, "blade_15", "pistol6", "bullet", 200);
	sld.dialog.filename = "Quest\LadyBeth_dialog.c";
	sld.dialog.currentnode = "LadyBeth_DialogInCity";
	sld.City = pchar.questTemp.LadyBeth.colony;
	ChangeCharacterAddressGroup(sld, pchar.questTemp.LadyBeth.colony + "_tavern_upstairs", "goto", "goto1");
	LAi_SetStayType(sld);
	LAi_SetImmortal(sld, true);
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	
	AddSimpleRumourCity(GetConvertStr("LadyBeth_Rum3", "LadyBeth.txt"), pchar.questTemp.LadyBeth.colony, 3, 1, "");
	AddSimpleRumourCity(GetConvertStr("LadyBeth_Rum4", "LadyBeth.txt"), pchar.questTemp.LadyBeth.colony, 3, 1, "");
	AddSimpleRumourCity(GetConvertStr("LadyBeth_Rum5", "LadyBeth.txt"), pchar.questTemp.LadyBeth.colony, 3, 1, "");
	AddSimpleRumourCity(GetConvertStr("LadyBeth_Rum6", "LadyBeth.txt"), pchar.questTemp.LadyBeth.colony, 3, 1, "");
	AddSimpleRumourCity(GetConvertStr("LadyBeth_Rum7", "LadyBeth.txt"), pchar.questTemp.LadyBeth.colony, 3, 1, "");
	AddSimpleRumourCity(GetConvertStr("LadyBeth_Rum8", "LadyBeth.txt"), pchar.questTemp.LadyBeth.colony, 3, 1, "");
	AddSimpleRumourCity(GetConvertStr("LadyBeth_Rum9", "LadyBeth.txt"), pchar.questTemp.LadyBeth.colony, 3, 1, "");
	AddSimpleRumourCity(GetConvertStr("LadyBeth_Rum10", "LadyBeth.txt"), pchar.questTemp.LadyBeth.colony, 3, 1, "");
	AddSimpleRumourCity(GetConvertStr("LadyBeth_Rum11", "LadyBeth.txt"), pchar.questTemp.LadyBeth.colony, 3, 1, "");
}

void LadyBeth_ToMap(string sQuest)
{
	if(!CharacterIsAlive("LadyBeth_cap")) {Log_testinfo("Капитан ШНЯВЫ умер"); return;}
	ref sld = characterFromId("LadyBeth_cap");
	sld.quest = "InMap";
	
	
	pchar.questTemp.LadyBeth.stage = sti(pchar.questTemp.LadyBeth.stage) + 1;
	if(sti(pchar.questTemp.LadyBeth.stage) >= 6)
	{		
		pchar.questTemp.LadyBeth.stage = 0;
		sld.city = LadyBeth_findColony(6);
	}
	else
	{
		sld.city = LadyBeth_findColony(sti(pchar.questTemp.LadyBeth.stage));
	}
	// При Супе из Черепахи не заходим на Тортугу
	if (CheckAttribute(pchar, "questTemp.Terrapin"))
	{
		if (pchar.questTemp.Terrapin != "done")
		{
			if(LadyBeth_findColony(sti(pchar.questTemp.LadyBeth.stage)+1) == "Tortuga")
			{
				pchar.questTemp.LadyBeth.stage = sti(pchar.questTemp.LadyBeth.stage) + 1;
				Log_testInfo("Капитан ШНЯВЫ ПРОПУСТИЛ ТОРТУГУ и направился в колонию: "+LadyBeth_findColony(sti(pchar.questTemp.LadyBeth.stage)+1));
			}
		}
	}
	
	sld.quest.targetCity = LadyBeth_findColony(sti(pchar.questTemp.LadyBeth.stage)+1);
	Log_testInfo("Капитан ШНЯВЫ направился в колонию: "+sld.quest.targetCity + " из колонии : "+sld.city);
	sld.mapEnc.type = "trade";
	sld.mapEnc.worldMapShip = "shnyava_sp2";
	sld.mapEnc.Name = GetConvertStr("LadyBeth_Ship_Name", "LadyBeth.txt");
	Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, 30);
	
	//если шнява вышла из Каймана, то чистим
	if(sld.city == "Shore16")
	{
		DelQMfromCaiman();
		DeleteQuestCondition("LadyBeth_CaimanSea");
		return;
	}
	//убираем ограничения в колонии, где находился ревизор
	pchar.questTemp.LadyBeth.CaptainInColony = "";
	//капитан клон исчезает
	sld = CharacterFromID("LadyBeth_clone_tavern");
	sld.lifeday = 0;
	//тавернщик теперь даёт комнату
	sld = CharacterFromID(pchar.questTemp.LadyBeth.colony + "_tavernkeeper");
	DeleteAttribute(sld, "quest.LadyBeth");
	//нельзя зайти в комнату в таверне
	LocatorReloadEnterDisable(pchar.questTemp.LadyBeth.colony + "_tavern", "reload2_back", true);
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.questTemp.LadyBeth.colony + "_tavern_upstairs")], false);
}

string findLedyBethRumour(ref chr)
{
	string Rumors[11];
	
	Rumors[0] = GetConvertStr("LadyBeth_Rum3", "LadyBeth.txt");
	Rumors[1] = GetConvertStr("LadyBeth_Rum4", "LadyBeth.txt");
	Rumors[2] = GetConvertStr("LadyBeth_Rum5", "LadyBeth.txt");
	Rumors[3] = GetConvertStr("LadyBeth_Rum6", "LadyBeth.txt");
	Rumors[4] = GetConvertStr("LadyBeth_Rum7", "LadyBeth.txt");
	Rumors[5] = GetConvertStr("LadyBeth_Rum8", "LadyBeth.txt");
	Rumors[6] = GetConvertStr("LadyBeth_Rum9", "LadyBeth.txt");
	Rumors[7] = GetConvertStr("LadyBeth_Rum10", "LadyBeth.txt");
	Rumors[8] = GetConvertStr("LadyBeth_Rum11", "LadyBeth.txt");
	Rumors[9] = GetConvertStr("LadyBeth_Rum12", "LadyBeth.txt");
	
	if(chr.sex == "man") return Rumors[rand(8)];
	else return Rumors[rand(9)];
}

void CheckLadyBeth()
{
	if(CharacterIsAlive("LadyBeth_cap"))
	{
		ref sld = CharacterFromID("LadyBeth_cap")
		if(CheckAttribute(sld,"quest") && sld.quest == "InMap")
		{
			//проверяем на карте
			bool bAtMap = false;
			aref encs;

			makearef(encs, worldMap.encounters);

			int num = GetAttributesNum(encs);
			aref enc;
			
			for (int i = 0; i < num; i++)
			{
				enc = GetAttributeN(encs, i);
				if(CheckAttribute(enc, "quest.chrID") && enc.quest.chrID == "LadyBeth_cap")
				{
					bAtMap = true;
				}
			}
			// на карте нет, но и атрибут "в порту" отсутствует
			if(!bAtMap)
			{
				LadyBeth_ToCity("LadyBeth_cap");
			}
			else
			{
				if(CheckQuestCondition("LadyBeth_MapRelease"))
				{
					Map_ReleaseQuestEncounter("LadyBeth_cap");
				}
				else
				{
					SetFunctionTimerCondition("LadyBeth_MapRelease", 0, 0, 31, false);
				}
			}
		}
	}
}

void LadyBeth_MapRelease(string qName)
{
	
}


//==============Ловушка в каюте================
void LadyBeth_Lovushka(string qName)
{
	LAi_SetActorType(pchar);
	LAi_FadeToBlackStart();
	DoQuestFunctionDelay("LadyBeth_Lovushka_2", 2.0);
}

void LadyBeth_Lovushka_2(string qName)
{
	PlaySound("interface\boom.wav");
	DoQuestFunctionDelay("LadyBeth_Lovushka_3", 2.0);
}

void LadyBeth_Lovushka_3(string qName)
{
	GameOver("sea");
}

//===============Битва на Каймане==============
void LadyBeth_CaimanSea(string qName)
{
	pchar.GenQuest.CabinLock = true;
	Island_SetReloadEnableGlobal("Caiman", false);
	bQuestDisableMapEnter = true;
		
	DoQuestFunctionDelay("LadyBeth_CaimanSea_2", 3.0);
}

void LadyBeth_CaimanSea_2(string qName)
{
	DeleteAttribute(pchar, "GenQuest.CabinLock");
	chrDisableReloadToLocation = true;
	
	pchar.questTemp.LadyBeth_CaimanSea_Paluba.ShipPos.x = pchar.ship.pos.x;
	pchar.questTemp.LadyBeth_CaimanSea_Paluba.ShipPos.z = pchar.ship.pos.z;
	pchar.questTemp.LadyBeth_CaimanSea_Paluba.ShipPos.Island = AISea.Island;
	
	CloneLocation("Ship_deck_Big", "Clone_location");
	DeleteAttribute(&locations[FindLocation("Clone_location")], "boarding");
	DoFunctionReloadToLocation("Clone_location", "goto", "goto7", "LadyBeth_CaimanSea_3");
}

void LadyBeth_CaimanSea_3(string qName)
{
	StartQuestMovie(true, false, true);
	TeleportCharacterToPosAy(pchar, -7.70, 8.01, -22.31, 1.50);
	
	sld = GetCharacter(NPC_GenerateCharacter("Alonso", "citiz_36", "man", "man", 25, pchar.nation, -1, true, "soldier"));
	sld.name 	= StringFromKey("SharlieTrial_29");
	sld.lastname = StringFromKey("SharlieTrial_30");
	sld.Dialog.Filename = "Quest\LadyBeth_dialog.c";
	sld.dialog.currentnode = "AlonsoNaPalube";
	LAi_SetImmortal(sld, true);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto9");
	LAi_SetActorType(sld);
	
	locCameraFromToPos(-4.01, 8.92, -20.43, true, -8.43, 7.52, -22.04);
	DoQuestFunctionDelay("LadyBeth_CaimanSea_6", 2.0);
}

void LadyBeth_CaimanSea_6(string qName)
{
	sld = CharacterFromID("Alonso");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void LadyBeth_AlonsoNaPalube_Vpered(string qName)
{
	EndQuestMovie();
	chrDisableReloadToLocation = false;
	bQuestDisableMapEnter = true;
	//Island_SetReloadEnableGlobal("Caiman", true);
	//Island_SetGotoEnableLocal("Caiman", "reload_2", false);
	//Island_SetReloadEnableLocal("Caiman", "reload_2", false);
	
	//SetFunctionLocationCondition("LadyBeth_CaimanBuhta", "Shore17", false);
	SetCurrentTime(12, 00);
	RecalculateJumpTable();
	RefreshWeather();
	RefreshLandTime();
	pchar.questTemp.TimeLock = true;
	pchar.GenQuest.CannotWait = true;
	
	SetFunctionLocationCondition("LadyBeth_CaimanBuhta", "Caiman", false);
	
	aref arTmp;
	makearef(arTmp, pchar.questTemp.LadyBeth_CaimanSea_Paluba.ShipPos);
	QuestToSeaLogin_Prepare(stf(arTmp.x), stf(arTmp.z), arTmp.Island);
	DeleteAttribute(pchar, "questTemp.LadyBeth_CaimanSea_Paluba.ShipPos");
	QuestToSeaLogin_Launch();
}

void LadyBeth_CaimanBuhta(string qName)
{
	DoQuestFunctionDelay("LadyBeth_CaimanBuhta_2", 3.0);
}

void LadyBeth_CaimanBuhta_2(string qName)
{
	if(GetArraySize(&Dead_Characters) != MAX_CHARS_IN_LOC)
	{
		SetArraySize(&Dead_Characters, MAX_CHARS_IN_LOC);
	}
	locations[FindLocation("Caiman_Jungle_01")].DisableEncounters = true;
	locations[FindLocation("Shore16")].DisableEncounters = true;
	locations[FindLocation("Shore17")].DisableEncounters = true;
	locations[FindLocation("Caiman_Grot")].DisableEncounters = true;
	locations[FindLocation("Caiman_CaveEntrance")].DisableEncounters = true;
	pchar.GenQuest.HunterLongPause = true;
	pchar.questTemp.BlackMark.IronsBlock = true;
	setCharacterShipLocation(pchar, "Shore17");
	DoFunctionReloadToLocation("Shore17", "reload", "sea", "LadyBeth_CaimanBuhta_3");
}

void LadyBeth_CaimanBuhta_3(string qName)
{
	//pchar.Ship.Crew.Quantity = sti(pchar.ship.Crew.Quantity) / 2;
	// Холм в джунглях
	sld = &Locations[FindLocation("Caiman_Jungle_01")];
	sld.filespath.models = "locations\Outside\Jungles\Jungle_SP2";
	sld.models.always.jungle = "Jungle_SP2";
	sld.models.always.locators = "Jungle_SP2_locators";
	sld.models.always.parts = "Jungle_SP2_parts";
	sld.models.always.decals = "Jungle_SP2_decals";
	sld.models.always.decals.tech = "Blood";
	sld.models.always.grassPatch = "Jungle_SP2_grass";
	sld.models.always.grassPatch.texture = "grass\grassshore.tga.tx";
	sld.models.day.charactersPatch = "Jungle_SP2_patch";
	sld.models.night.charactersPatch = "Jungle_SP2_patch";
	sld.locators_radius.quest.cannonarea1_1 = 3.5;
	sld.locators_radius.quest.cannonarea1_2 = 4.5;
	sld.locators_radius.quest.cannonarea1_3 = 4.5;
	sld.locators_radius.quest.cannonarea2_1 = 3.5;
	sld.locators_radius.quest.cannonarea2_2 = 7.0;
	sld.locators_radius.quest.cannonarea2_3 = 7.0;
	sld.locators_radius.quest.cannoneer1_1 = 5.0;
	sld.locators_radius.quest.cannoneer2_1 = 5.0;
	pchar.wind.angle = 900.0;
	
	sld.reload.l1.name = "reload1_back";
	sld.reload.l1.go = "Shore17";
	sld.reload.l1.emerge = "reload1";
	sld.reload.l1.autoreload = "1";
	sld.reload.l1.label = "Shore17";
	sld.locators_radius.reload.reload1_back = 2;
	
	sld.reload.l2.name = "reload2_back";
	sld.reload.l2.go = "Caiman_CaveEntrance";
	sld.reload.l2.emerge = "reload2";
	sld.reload.l2.autoreload = "1";
	sld.reload.l2.label = "Jungle";
	sld.locators_radius.reload.reload3_back = 2;
	
	sld.reload.l3.name = "reload3_back";
	sld.reload.l3.go = "Shore16";
	sld.reload.l3.emerge = "reload1";
	sld.reload.l3.autoreload = "1";
	sld.reload.l3.label = "Shore16";
	// Пустынный пляж
	sld = &Locations[FindLocation("Shore16")];
	sld.filespath.models = "locations\Outside\Shores\bay_sp2";
	sld.models.always.shore07 = "bay_sp2";
	sld.models.always.shore07seabed = "bay_sp2_sb";
	sld.models.always.locators = "bay_sp2_locators";
	sld.models.always.grassPatch = "bay_sp2_grass";
	
	sld.models.always.parts = "bay_sp2_parts";
	//sld.models.always.sb = "bay_sp2_sb";
	sld.models.always.jump = "bay_sp2_jump";
	sld.models.always.decals = "bay_sp2_decals";
	sld.models.always.decals.tech = "Blood"
	sld.models.always.watermask = "bay_sp2_watermask";
	sld.models.always.watermask.tech = "WaterMask";
	sld.models.always.watermask.level = 65500;
	
	sld.models.always.windows = "bay_sp2_windows";
	sld.models.always.windows.level = 65539;
	
	sld.models.day.charactersPatch = "bay_sp2_patch";
	sld.models.night.charactersPatch = "bay_sp2_patch";
	
	sld.reload.l1.name = "reload1_back";
	sld.reload.l1.go = "Caiman_Jungle_01";
	sld.reload.l1.emerge = "reload3";
	sld.reload.l1.autoreload = "1";
	sld.reload.l1.label = "Jungle";
	sld.locators_radius.reload.reload1_back = 2;
	// Вход в грот
	sld = &Locations[FindLocation("Caiman_CaveEntrance")];
	
	sld.reload.l2.name = "reload2_back";
	sld.reload.l2.go = "Caiman_Jungle_01";
	sld.reload.l2.emerge = "reload2";
	sld.reload.l2.autoreload = "1";
	sld.reload.l2.label = "Jungle";
	//
	QuestCloseSeaExit();
	SetFunctionLocationCondition("LadyBeth_CaimanBitva_1", "Caiman_Jungle_01", false);
	
	if (CheckAttribute(pchar, "questTemp.LadyBeth_LiteGroup"))
	{
		//ставим наших бойцов
		for (i=1; i<=14; i++)
		{
			if (i > 11)
			{
				if (i == 12)
				{
					sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_Our_crew_"+i, "mush_ctz_4", "man", "mushketer", 6, sti(pchar.nation), 0, false, "soldier"));
					FantomMakeCoolFighter(sld, 6, 30, 30, "", "mushket3", "grapeshot", 30);
				}
				if (i == 13)
				{
					sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_Our_crew_"+i, "mush_ctz_6", "man", "mushketer", 6, sti(pchar.nation), 0, false, "soldier"));
					FantomMakeCoolFighter(sld, 12, 50, 50, "", "grape_mushket", "grenade", 0);
				}
				if (i == 14)
				{
					sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_Our_crew_"+i, "mush_ctz_5", "man", "mushketer", 6, sti(pchar.nation), 0, false, "soldier"));
					FantomMakeCoolFighter(sld, 6, 30, 30, "", "mushket1", "cartridge", 30);
				}
			}
			else
			{
				sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_Our_crew_"+i, "citiz_3"+(rand(8)+1), "man", "man", 6, sti(pchar.nation), 0, false, "soldier"));
				FantomMakeCoolFighter(sld, 6, 30, 30, "blade_10", "pistol1", "bullet", 30);
			}
			ChangeCharacterAddressGroup(sld, "Shore17", "goto", "goto6");
			LAi_CharacterDisableDialog(sld);
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
	}
	if (CheckAttribute(pchar, "questTemp.LadyBeth_StrongGroup"))
	{
		//ставим наших бойцов
		for (i=1; i<=20; i++)
		{
			if (i > 15)
			{
				if (i == 16)
				{
					sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_Our_crew_"+i, "mush_ctz_4", "man", "mushketer", 6, sti(pchar.nation), 0, false, "soldier"));
					FantomMakeCoolFighter(sld, 12, 50, 50, "", "grape_mushket", "grenade", 0);
				}
				if (i >= 17 && i <= 18)
				{
					sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_Our_crew_"+i, "mush_ctz_4", "man", "mushketer", 5, sti(pchar.nation), 0, false, "soldier"));
					FantomMakeCoolFighter(sld, 12, 50, 50, "", "mushket3", "grapeshot", 0);
				}
				if (i >= 19 && i <= 20)
				{
					sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_Our_crew_"+i, "mush_ctz_5", "man", "mushketer", 5, sti(pchar.nation), 0, false, "soldier"));
					FantomMakeCoolFighter(sld, 12, 50, 50, "", "mushket1", "cartridge", 0);
				}
			}
			else
			{
				sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_Our_crew_"+i, "citiz_3"+(rand(8)+1), "man", "man", 6, sti(pchar.nation), 0, false, "soldier"));
				FantomMakeCoolFighter(sld, 6, 30, 30, "blade_10", "pistol1", "bullet", 30);
			}
			ChangeCharacterAddressGroup(sld, "Shore17", "goto", "goto6");
			LAi_CharacterDisableDialog(sld);
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
		// Наёмник
		sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_Our_Golovorez", "citiz_60", "man", "man", 15, pchar.nation, 0, false, "pirate"));
		FantomMakeCoolFighter(sld, 15, 70, 70, "blade_13", "pistol1", "bullet", 150);
		ChangeCharacterAddressGroup(sld, "Shore17", "goto", "goto6");
		LAi_CharacterDisableDialog(sld);
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, pchar, "", -1);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	// Алонсо
	sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_Alonso", "citiz_36", "man", "man", 15, pchar.nation, 0, false, "pirate"));
	FantomMakeCoolFighter(sld, 15, 70, 70, "blade_13", "pistol6", "bullet", 300);
	sld.name 	= StringFromKey("SharlieTrial_29");
	sld.lastname = StringFromKey("SharlieTrial_30");
	ChangeCharacterAddressGroup(sld, "Shore17", "goto", "goto6");
	LAi_CharacterDisableDialog(sld);
	LAi_SetActorType(sld);
	LAi_ActorFollow(sld, pchar, "", -1);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
}

void LadyBeth_CaimanBitva_1(string qName)
{
	chrDisableReloadToLocation = true;
	LAi_SetStayType(pchar);
	SetFunctionNPCDeathCondition("LadyBeth_HeadShotBoos", "LadyBeth_Blackwood", false);
	// прячем в сундук лут Блеквуда
	pchar.GenQuestBox.Caiman_Jungle_01.box4.items.LadyBeth_Map = 1;
	pchar.GenQuestBox.Caiman_Jungle_01.box4.items.mushket9 = 1;
	pchar.GenQuestBox.Caiman_Jungle_01.box4.items.grapeshot = 29;
	pchar.GenQuestBox.Caiman_Jungle_01.box4.items.GunPowder = 29;
	// остальные сундуки
	pchar.GenQuestBox.Caiman_Jungle_01.box1.items.mushket1 = 1;
	pchar.GenQuestBox.Caiman_Jungle_01.box1.items.GunPowder = 17;
	pchar.GenQuestBox.Caiman_Jungle_01.box1.items.bullet = 17;
	pchar.GenQuestBox.Caiman_Jungle_01.box2.items.potion1 = 3;
	pchar.GenQuestBox.Caiman_Jungle_01.box2.items.potion4 = 1;
	pchar.GenQuestBox.Caiman_Jungle_01.box2.items.indian_2 = 1;
	pchar.GenQuestBox.Caiman_Jungle_01.box3.items.talisman11 = 5;
	pchar.GenQuestBox.Caiman_Jungle_01.box5.items.jewelry6 = 20;
	pchar.GenQuestBox.Caiman_Jungle_01.box5.items.jewelry3 = 5;
	// Меняем статы Аркебузы
	ref itm;
	makeref(itm, items[FindItem("mushket9")]);
	itm.UpgradeStage = 1;
    TreasureTiers[0].QuestSlot.LadyBeth = "LadyBeth_Treasure"; // Части будут рандомиться в сокровища
	// Наш обычный отряд
	if (CheckAttribute(pchar, "questTemp.LadyBeth_LiteGroup"))
	{
		//ставим наших бойцов
		for (i=1; i<=14; i++)
		{
			if (i > 11)
			{
				if (i == 12)
				{
					sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_Our_crew_"+i, "mush_ctz_4", "man", "mushketer", 6, sti(pchar.nation), 0, false, "soldier"));
					FantomMakeCoolFighter(sld, 12, 50, 50, "", "mushket3", "grapeshot", 0);
					ChangeCharacterAddressGroup(sld, "Caiman_Jungle_01", "quest", "ourmush_1");
				}
				if (i == 13)
				{
					sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_Our_crew_"+i, "mush_ctz_6", "man", "mushketer", 6, sti(pchar.nation), 0, false, "soldier"));
					FantomMakeCoolFighter(sld, 12, 50, 50, "", "grape_mushket", "grenade", 0);
					ChangeCharacterAddressGroup(sld, "Caiman_Jungle_01", "quest", "ourmush_1");
					TeleportCharacterToPos(sld, 48.21, 9.5, -154.17);
				}
				if (i == 14)
				{
					sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_Our_crew_"+i, "mush_ctz_5", "man", "mushketer", 6, sti(pchar.nation), 0, false, "soldier"));
					FantomMakeCoolFighter(sld, 12, 50, 50, "", "mushket1", "cartridge", 0);
					ChangeCharacterAddressGroup(sld, "Caiman_Jungle_01", "quest", "ourmush_1");
				}
			}
			else
			{
				sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_Our_crew_"+i, "citiz_3"+(rand(8)+1), "man", "man", 6, sti(pchar.nation), 0, false, "soldier"));
				FantomMakeCoolFighter(sld, 6, 30, 30, "blade_10", "pistol1", "bullet", 30);
				if (i >= 1 && i <= 4) ChangeCharacterAddressGroup(sld, "Caiman_Jungle_01", "quest", "our_1");
				if (i >= 5 && i <= 8) ChangeCharacterAddressGroup(sld, "Caiman_Jungle_01", "quest", "our_2");
				if (i >= 9 && i <= 12) ChangeCharacterAddressGroup(sld, "Caiman_Jungle_01", "quest", "our_3");
				if (i >= 13 && i <= 14) ChangeCharacterAddressGroup(sld, "Caiman_Jungle_01", "quest", "our_4");
			}
			LAi_CharacterDisableDialog(sld);
			//LAi_SetActorType(sld);
			//LAi_SetOfficerType(sld);
			LAi_SetWarriorType(sld);
			LAi_warrior_SetStay(sld, true);
			RemoveItems(sld, "potion1", 10);
			//LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
		// Алонсо
		sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_Alonso", "citiz_36", "man", "man", 15, pchar.nation, 0, false, "pirate"));
		FantomMakeCoolFighter(sld, 15, 50, 50, "blade_13", "pistol6", "bullet", 300);
		sld.name 	= StringFromKey("SharlieTrial_29");
		sld.lastname = StringFromKey("SharlieTrial_30");
		ChangeCharacterAddressGroup(sld, "Caiman_Jungle_01", "quest", "our_1");
		sld.MultiFighter = 2.5;
		AddItems(sld, "potion4", 1);
		LAi_CharacterDisableDialog(sld);
		//LAi_SetActorType(sld);
		//LAi_SetOfficerType(sld);
		LAi_SetWarriorType(sld);
		LAi_warrior_SetStay(sld, true);
		//LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	// Наш усиленный отряд
	if (CheckAttribute(pchar, "questTemp.LadyBeth_StrongGroup"))
	{
		//ставим наших бойцов
		for (i=1; i<=20; i++)
		{
			if (i > 15)
			{
				if (i == 16)
				{
					sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_Our_crew_"+i, "mush_ctz_6", "man", "mushketer", 6, sti(pchar.nation), 0, false, "soldier"));
					FantomMakeCoolFighter(sld, 12, 50, 50, "", "grape_mushket", "grenade", 0);
					ChangeCharacterAddressGroup(sld, "Caiman_Jungle_01", "quest", "ourmush_1");
					TeleportCharacterToPos(sld, 48.21, 9.5, -154.17);
				}
				if (i >= 17 && i <= 18)
				{
					sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_Our_crew_"+i, "mush_ctz_4", "man", "mushketer", 6, sti(pchar.nation), 0, false, "soldier"));
					FantomMakeCoolFighter(sld, 12, 50, 50, "", "mushket3", "grapeshot", 0);
					ChangeCharacterAddressGroup(sld, "Caiman_Jungle_01", "quest", "ourmush_1");
				}
				if (i >= 19 && i <= 20)
				{
					sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_Our_crew_"+i, "mush_ctz_5", "man", "mushketer", 6, sti(pchar.nation), 0, false, "soldier"));
					FantomMakeCoolFighter(sld, 12, 50, 50, "", "mushket1", "cartridge", 0);
					ChangeCharacterAddressGroup(sld, "Caiman_Jungle_01", "quest", "ourmush_1");
				}
			}
			else
			{
				sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_Our_crew_"+i, "citiz_3"+(rand(8)+1), "man", "man", 6, sti(pchar.nation), 0, false, "soldier"));
				FantomMakeCoolFighter(sld, 6, 30, 30, "blade_10", "pistol1", "bullet", 30);
				if (i >= 1 && i <= 4) ChangeCharacterAddressGroup(sld, "Caiman_Jungle_01", "quest", "our_1");
				if (i >= 5 && i <= 8) ChangeCharacterAddressGroup(sld, "Caiman_Jungle_01", "quest", "our_2");
				if (i >= 9 && i <= 12) ChangeCharacterAddressGroup(sld, "Caiman_Jungle_01", "quest", "our_3");
				if (i >= 13 && i <= 15) ChangeCharacterAddressGroup(sld, "Caiman_Jungle_01", "quest", "our_4");
			}
			LAi_CharacterDisableDialog(sld);
			//LAi_SetOfficerType(sld);
			LAi_SetWarriorType(sld);
			LAi_warrior_SetStay(sld, true);
			RemoveItems(sld, "potion1", 10);
			//LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
		// Алонсо
		sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_Alonso", "citiz_36", "man", "man", 15, pchar.nation, -1, false, "pirate"));
		FantomMakeCoolFighter(sld, 15, 70, 70, "blade_13", "pistol6", "bullet", 300);
		sld.name 	= StringFromKey("SharlieTrial_29");
		sld.lastname = StringFromKey("SharlieTrial_30");
		ChangeCharacterAddressGroup(sld, "Caiman_Jungle_01", "quest", "our_1");
		sld.MultiFighter = 2.5;
		AddItems(sld, "potion4", 1);
		LAi_CharacterDisableDialog(sld);
		//LAi_SetOfficerType(sld);
		LAi_SetWarriorType(sld);
		LAi_warrior_SetStay(sld, true);
		//LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		// Наёмник
		sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_Our_Golovorez", "citiz_60", "man", "man", 15, pchar.nation, 0, false, "pirate"));
		FantomMakeCoolFighter(sld, 15, 70, 70, "topor_04", "pistol3", "grapeshot", 150);
		ChangeCharacterAddressGroup(sld, "Caiman_Jungle_01", "quest", "our_1");
		sld.MultiFighter = 2.5;
		AddItems(sld, "potion4", 1);
		LAi_CharacterDisableDialog(sld);
		//LAi_SetOfficerType(sld);
		LAi_SetWarriorType(sld);
		LAi_warrior_SetStay(sld, true);
		//LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	// наши потери будут учитываться
	int iSailors;
	iSailors = (GetCrewQuantity(pchar) / 40);
	if (iSailors < 1) iSailors = 1;
	pchar.SailorDiedInBattle = iSailors;
	
	for (i=1; i<=60; i++)
	{
		if (CharacterIsAlive("LadyBeth_Our_crew_"+i))
		{
			sld = CharacterFromID("LadyBeth_Our_crew_"+i);
			string cnd = "LadyBeth_Our_crew_"+i;
			pchar.quest.(cnd).win_condition.(cnd) = "NPC_Death";
			pchar.quest.(cnd).win_condition.(cnd).character = sld.id;
			pchar.quest.(cnd).function = "LadyBeth_SailorDead";
		}
	}
	// усиление армий
	int LadyBeth_SilaEnemy;
	LadyBeth_SilaEnemy = 1;
	if (GetCrewQuantity(pchar) <= 8+4*MOD_SKILL_ENEMY_RATE) LadyBeth_SilaEnemy = 10.00;
	if (GetCrewQuantity(pchar) >= 9+4*MOD_SKILL_ENEMY_RATE) LadyBeth_SilaEnemy = 1.40;
	if (GetCrewQuantity(pchar) >= 26+4*MOD_SKILL_ENEMY_RATE) LadyBeth_SilaEnemy = 1.25;
	if (GetCrewQuantity(pchar) >= 35+4*MOD_SKILL_ENEMY_RATE) LadyBeth_SilaEnemy = 1.00;
	if (GetCrewQuantity(pchar) >= 42+4*MOD_SKILL_ENEMY_RATE) LadyBeth_SilaEnemy = 0.90;
	if (GetCrewQuantity(pchar) >= 63+4*MOD_SKILL_ENEMY_RATE) LadyBeth_SilaEnemy = 0.80;
	if (GetCrewQuantity(pchar) >= 78+4*MOD_SKILL_ENEMY_RATE) LadyBeth_SilaEnemy = 0.70;
	if (GetCrewQuantity(pchar) >= 107+4*MOD_SKILL_ENEMY_RATE) LadyBeth_SilaEnemy = 0.60;
	//===СОЛДАТЫ БЛЕКВУДА===
	// Блеквуд (БОСС)
	sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_Blackwood", "quest_off_eng", "man", "man", 30, ENGLAND, -1, false, "soldier"));
	sld.name = GetConvertStr("LadyBeth_Cap_Name", "LadyBeth.txt");
	sld.lastname = GetConvertStr("LadyBeth_Cap_lastname", "LadyBeth.txt");
	FantomMakeCoolFighter(sld, 30, 70, 70, "blade_15", "pistol6", "bullet", 200);
	GiveItem2Character(sld, "cirass1");
	EquipCharacterByItem(sld, "cirass1");
	AddItems(sld, "cartridge", 30);
	AddItems(sld, "GunPowder", 30);
	//ChangeCharacterAddressGroup(sld, "Caiman_Jungle_01", "quest", "boss");
	//LAi_CharacterDisableDialog(sld);
	//LAi_SetWarriorType(sld);
	LAi_SetActorType(sld);
	//CharacterTurnToLoc(sld, "quest", "our_1");
	LAi_warrior_SetStay(sld, true);
	sld.CantLoot = true;
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	//LAi_SetImmortal(sld, true);
	LAi_group_MoveCharacter(sld, "LadyBeth_Enemy");
	LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LadyBeth_VistrelSnizu");
	// Блеквуд Мушкетёр клон
	sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_Blackwood_clone", "quest_off_eng_mush", "man", "mushketer", 30, ENGLAND, 0, false, "soldier"));
	sld.name = GetConvertStr("LadyBeth_Cap_Name", "LadyBeth.txt");
	sld.lastname = GetConvertStr("LadyBeth_Cap_lastname", "LadyBeth.txt");
	FantomMakeCoolFighter(sld, 12, 50, 50, "", "mushket9", "bullet", 0);
	ChangeCharacterAddressGroup(sld, "Caiman_Jungle_01", "quest", "boss");
	//LAi_CharacterDisableDialog(sld);
	//LAi_SetWarriorType(sld);
	LAi_SetActorType(sld);
	// Отряд 1
	for (i=1; i<=13; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_EnemyGroup1_"+i, "citiz_4"+(rand(8)+1), "man", "man", 3, ENGLAND, 0, false, "soldier"));
		FantomMakeCoolFighter(sld, 3, 30, 30, "blade_10", "pistol1", "bullet", 0);
		if (i >= 1 && i <= 4) ChangeCharacterAddressGroup(sld, "Caiman_Jungle_01", "quest", "enc1_1");
		if (i >= 5 && i <= 8) ChangeCharacterAddressGroup(sld, "Caiman_Jungle_01", "quest", "enc1_2");
		if (i >= 9 && i <= 13) ChangeCharacterAddressGroup(sld, "Caiman_Jungle_01", "quest", "enc1_3");
		LAi_CharacterDisableDialog(sld);
		LAi_SetWarriorType(sld);
		LAi_warrior_SetStay(sld, true);
		LAi_SetHP(sld, 40.0, 40.0);
		RemoveItems(sld, "potion1", 10);
		LAi_group_MoveCharacter(sld, "LadyBeth_Enemy");
	}
	// Отряд 2
	for (i=1; i<=13; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_EnemyGroup2_"+i, "citiz_4"+(rand(8)+1), "man", "man", 3, ENGLAND, 0, false, "soldier"));
		FantomMakeCoolFighter(sld, 3, 30, 30, "blade_10", "pistol1", "bullet", 0);
		if (i >= 1 && i <= 4) ChangeCharacterAddressGroup(sld, "Caiman_Jungle_01", "quest", "enc2_1");
		if (i >= 5 && i <= 8) ChangeCharacterAddressGroup(sld, "Caiman_Jungle_01", "quest", "enc2_2");
		if (i >= 9 && i <= 13) ChangeCharacterAddressGroup(sld, "Caiman_Jungle_01", "quest", "enc2_3");
		LAi_SetWarriorType(sld);
		LAi_warrior_SetStay(sld, true);
		LAi_SetHP(sld, 40.0, 40.0);
		RemoveItems(sld, "potion1", 10);
		LAi_group_MoveCharacter(sld, "LadyBeth_Enemy");
	}
	// Отряд 3
	for (i=1; i<=13; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_EnemyGroup3_"+i, "citiz_4"+(rand(8)+1), "man", "man", 3, ENGLAND, 0, false, "soldier"));
		FantomMakeCoolFighter(sld, 3, 30, 30, "blade_10", "pistol1", "bullet", 0);
		if (i >= 1 && i <= 4) ChangeCharacterAddressGroup(sld, "Caiman_Jungle_01", "quest", "enc3_1");
		if (i >= 5 && i <= 8) ChangeCharacterAddressGroup(sld, "Caiman_Jungle_01", "quest", "enc3_2");
		if (i >= 9 && i <= 13) ChangeCharacterAddressGroup(sld, "Caiman_Jungle_01", "quest", "enc3_3");
		LAi_CharacterDisableDialog(sld);
		LAi_SetWarriorType(sld);
		LAi_warrior_SetStay(sld, true);
		LAi_SetHP(sld, 40.0, 40.0);
		RemoveItems(sld, "potion1", 10);
		LAi_group_MoveCharacter(sld, "LadyBeth_Enemy");
	}
	// Отряд 4
	for (i=1; i<=13; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_EnemyGroup4_"+i, "citiz_4"+(rand(8)+1), "man", "man", 3, ENGLAND, 0, false, "soldier"));
		FantomMakeCoolFighter(sld, 3, 30, 30, "blade_10", "pistol1", "bullet", 0);
		if (i >= 1 && i <= 4) ChangeCharacterAddressGroup(sld, "Caiman_Jungle_01", "quest", "enc4_1");
		if (i >= 5 && i <= 8) ChangeCharacterAddressGroup(sld, "Caiman_Jungle_01", "quest", "enc4_2");
		if (i >= 9 && i <= 13) ChangeCharacterAddressGroup(sld, "Caiman_Jungle_01", "quest", "enc4_3");
		LAi_CharacterDisableDialog(sld);
		LAi_SetWarriorType(sld);
		LAi_warrior_SetStay(sld, true);
		LAi_SetHP(sld, 40.0, 40.0);
		RemoveItems(sld, "potion1", 10);
		LAi_group_MoveCharacter(sld, "LadyBeth_Enemy");
	}
	// Отряд 5
	/*for (i=1; i<=13; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_EnemyGroup5_"+i, "citiz_4"+(rand(8)+1), "man", "man", 3, ENGLAND, 0, false, "soldier"));
		FantomMakeCoolFighter(sld, 3, 30, 30, "blade_10", "pistol1", "bullet", 0);
		if (i >= 1 && i <= 4) ChangeCharacterAddressGroup(sld, "Caiman_Jungle_01", "quest", "enc5_1");
		if (i >= 5 && i <= 8) ChangeCharacterAddressGroup(sld, "Caiman_Jungle_01", "quest", "enc5_2");
		if (i >= 9 && i <= 13) ChangeCharacterAddressGroup(sld, "Caiman_Jungle_01", "quest", "enc5_3");
		LAi_CharacterDisableDialog(sld);
		LAi_SetWarriorType(sld);
		LAi_warrior_SetStay(sld, true);
		LAi_SetHP(sld, 40.0, 40.0);
		RemoveItems(sld, "potion1", 10);
		LAi_group_MoveCharacter(sld, "LadyBeth_Enemy");
	}*/
	// Головорезы
	for (i=1; i<=4; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_EnemyGolovorez_"+i, "sold_eng_"+i, "man", "man", 15, ENGLAND, 0, false, "soldier"));
		FantomMakeCoolFighter(sld, 15*LadyBeth_SilaEnemy, 70*LadyBeth_SilaEnemy, 70*LadyBeth_SilaEnemy, "blade_13", "pistol3", "grapeshot", 150*LadyBeth_SilaEnemy);
		ChangeCharacterAddressGroup(sld, "Caiman_Jungle_01", "encdetector", "enc"+i);
		LAi_SetCheckMinHP(sld, 1, false, "LadyBeth_IronWill");
		sld.MultiFighter = 1.0+LadyBeth_SilaEnemy;
		AddItems(sld, "potion4", 1);
		LAi_CharacterDisableDialog(sld);
		LAi_SetWarriorType(sld);
		LAi_warrior_SetStay(sld, true);
		LAi_group_MoveCharacter(sld, "LadyBeth_Enemy");
	}
	// Мушкетёры
	for (i=1; i<=3; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_EnemyMushket_"+i, "mush_eng_"+(rand(2)+1), "man", "mushketer", 12, ENGLAND, 0, false, "soldier"));
		FantomMakeCoolFighter(sld, 12*LadyBeth_SilaEnemy, 50*LadyBeth_SilaEnemy, 50*LadyBeth_SilaEnemy, "", "mushket2", "bullet", 30*LadyBeth_SilaEnemy);
		ChangeCharacterAddressGroup(sld, "Caiman_Jungle_01", "quest", "mushket"+i);
		sld.MultiFighter = 1.0+LadyBeth_SilaEnemy;
		LAi_CharacterDisableDialog(sld);
		SetCharacterPerk(sld, "Gunman");
		SetCharacterPerk(sld, "GunProfessional");
		LAi_SetWarriorType(sld);
		LAi_warrior_SetStay(sld, true);
		sld.MusketerDistance = 0;
		LAi_group_MoveCharacter(sld, "LadyBeth_Enemy");
	}
	for (i=6; i<=11; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_EnemyMushket_"+i, "mush_eng_"+(rand(2)+1), "man", "mushketer", 12, ENGLAND, 0, false, "soldier"));
		FantomMakeCoolFighter(sld, 12*LadyBeth_SilaEnemy, 50*LadyBeth_SilaEnemy, 50*LadyBeth_SilaEnemy, "", "mushket2", "bullet", 30*LadyBeth_SilaEnemy);
		ChangeCharacterAddressGroup(sld, "Caiman_Jungle_01", "quest", "mushket"+i);
		sld.MultiFighter = 1.0+LadyBeth_SilaEnemy;
		LAi_CharacterDisableDialog(sld);
		SetCharacterPerk(sld, "Gunman");
		SetCharacterPerk(sld, "GunProfessional");
		LAi_SetWarriorType(sld);
		LAi_warrior_SetStay(sld, true);
		sld.MusketerDistance = 0;
		LAi_group_MoveCharacter(sld, "LadyBeth_Enemy");
	}
	// Одинокий мушкетёр
	/*sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_EnemyMushket_13", "mush_ctz_9", "man", "mushketer", 12, ENGLAND, 0, false, "soldier"));
	FantomMakeCoolFighter(sld, 12, 50, 50, "", "mushket3", "grapeshot", 0);
	ChangeCharacterAddressGroup(sld, "Caiman_Jungle_01", "quest", "mushket13");
	LAi_CharacterDisableDialog(sld);
	LAi_SetWarriorType(sld);
	sld.MusketerDistance = 10;
	LAi_group_MoveCharacter(sld, "LadyBeth_Enemy");*/
	// Пушка 1
	sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_EnemyPushkar_1", "sold_eng_"+(rand(7)+1), "man", "man", 10, ENGLAND, 0, true, "soldier"));
	ChangeCharacterAddressGroup(sld, "Caiman_Jungle_01", "quest", "cannoneer1_1");
	LAi_SetHP(sld, 1.0, 1.0);
	LAi_CharacterDisableDialog(sld);
	LAi_SetStayType(sld);
	//LAi_SetWarriorType(sld);
	//LAi_warrior_SetStay(sld, true);
	LAi_group_MoveCharacter(sld, "LadyBeth_Enemy");
	SetFunctionLocatorCondition("LadyBeth_Pushka1", "Caiman_Jungle_01", "quest", "cannonarea1_1", false)
	SetFunctionLocatorCondition("LadyBeth_Pushka1", "Caiman_Jungle_01", "quest", "cannonarea1_2", false)
	SetFunctionLocatorCondition("LadyBeth_Pushka1", "Caiman_Jungle_01", "quest", "cannonarea1_3", false)
	// Пушка 2
	sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_EnemyPushkar_2", "sold_eng_"+(rand(7)+1), "man", "man", 10, ENGLAND, 0, true, "soldier"));
	ChangeCharacterAddressGroup(sld, "Caiman_Jungle_01", "quest", "cannoneer2_1");
	LAi_SetHP(sld, 1.0, 1.0);
	LAi_CharacterDisableDialog(sld);
	LAi_SetStayType(sld);
	//LAi_SetWarriorType(sld);
	//LAi_warrior_SetStay(sld, true);
	LAi_group_MoveCharacter(sld, "LadyBeth_Enemy");
	SetFunctionLocatorCondition("LadyBeth_Pushka2", "Caiman_Jungle_01", "quest", "cannonarea2_1", false)
	SetFunctionLocatorCondition("LadyBeth_Pushka2", "Caiman_Jungle_01", "quest", "cannonarea2_2", false)
	SetFunctionLocatorCondition("LadyBeth_Pushka2", "Caiman_Jungle_01", "quest", "cannonarea2_3", false)
	// Установки поведения армии
	LAi_group_SetRelation("LadyBeth_Enemy", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("LadyBeth_Enemy", LAI_GROUP_PLAYER, false);
	LAi_group_SetCheckFunction("LadyBeth_Enemy", "LadyBeth_PobedaInJungles");
	LAi_group_SetLookRadius("LadyBeth_Enemy", 20.0);
	LAi_group_SetHearRadius("LadyBeth_Enemy", 15.0);
	LAi_group_SetSayRadius("LadyBeth_Enemy", 30.0);
	//Другое
	SetFunctionLocatorCondition("LadyBeth_CannonerFight1", "Caiman_Jungle_01", "quest", "cannoneer1_1", false)
	SetFunctionLocatorCondition("LadyBeth_CannonerFight2", "Caiman_Jungle_01", "quest", "cannoneer2_1", false)
	SetFunctionLocatorCondition("LadyBeth_BossEtap", "Caiman_Jungle_01", "quest", "quest1", false)
	DoQuestFunctionDelay("LadyBeth_CaimanKino_0", 0.1);
	TeleportCharacterToPosAy(pchar, 51.88, 9.50, -153.71, -0.50);
	for(int i=1; i<=3; i++)
	{
		int idx = GetOfficersIndex(pchar, i);
		if(idx < 0) continue;
		sld = &Characters[idx];
		LAi_group_MoveCharacter(sld, "");
	}
}

void LadyBeth_CaimanKino_0(string qName)
{
	ClearAllLogStrings();
	StartQuestMovie(true, false, true);
	pchar.questTemp.NoFast = true;
	locCameraFromToPos(50.97, 11.66, -157.50, true, 49.86, 9.70, -152.36);
	DoQuestFunctionDelay("LadyBeth_CaimanKino_1", 3.5);
}

void LadyBeth_CaimanKino_1(string qName)
{
	locCameraFlyToPositionLookToPoint(44.03, 11.38, -102.28, 44.74, 10.98, -105.80, 48.30, 6.68, -122.86, -1, 6500/GetDeltaTime());
	Pchar.FuncCameraFly = "LadyBeth_CaimanKino_2";
}

void LadyBeth_CaimanKino_2(string qName)
{
	locCameraFlyToPositionLookToPoint(59.58, 12.93, -101.36, 57.41, 13.78, -112.58, 39.30, 8.68, -154.86, -1, 6000/GetDeltaTime());
	Pchar.FuncCameraFly = "LadyBeth_CaimanKino_3";
}

void LadyBeth_CaimanKino_3(string qName)
{
	sld = CharacterFromID("LadyBeth_Blackwood_clone");
	LAi_SetActorType(sld);
	LAi_ActorAnimation(sld, "blackwood_idle", "", 5.5);
	
	locCameraFlyToPositionLookToPoint(22.88, 11.14, -148.09, 21.98, 10.78, -140.74, 15.73, 6.38, -129.61, -1, 5300/GetDeltaTime());
	Pchar.FuncCameraFly = "LadyBeth_CaimanKino_4";
}

void LadyBeth_CaimanKino_4(string qName)
{
	locCameraFlyToPositionLookToPoint(12.53, 11.65, -85.90, 26.77, 17.72, -102.27, 22.87, 19.86, -119.00, -1, 10000/GetDeltaTime());
	Pchar.FuncCameraFly = "LadyBeth_CaimanKino_5";
}

void LadyBeth_CaimanKino_5(string qName)
{
	locCameraFlyToPositionLookToPoint(41.95, 13.86, -128.97, 34.01, 19.02, -123.49, 18.47, 22.52, -115.55, -1, 5200/GetDeltaTime());
	Pchar.FuncCameraFly = "LadyBeth_CaimanKino_6";
}

void LadyBeth_CaimanKino_6(string qName)
{
	locCameraFlyToPositionLookToPoint(34.01, 19.02, -123.49, 33.41, 19.28, -122.89, 18.47, 22.52, -115.55, -1, 2600/GetDeltaTime());
	Pchar.FuncCameraFly = "LadyBeth_CaimanKino_7";
}

void LadyBeth_CaimanKino_7(string qName)
{
	locCameraFromToPos(29.59, 19.46, -123.89, true, 28.27, 18.46, -117.30);
	DoQuestFunctionDelay("LadyBeth_CaimanKino_8", 3.2);
}

void LadyBeth_CaimanKino_8(string qName)
{
	locCameraFromToPos(27.32, 20.75, -119.93, true, 33.53, 16.73, -126.34);
	DoQuestFunctionDelay("LadyBeth_CaimanKino_9", 2.0);
}

void LadyBeth_CaimanKino_9(string qName)
{
	locCameraFromToPos(53.53, 10.90, -154.39, true, 48.14, 10.24, -148.57);
	DoQuestFunctionDelay("LadyBeth_CaimanKino_10", 2.0);
}

void LadyBeth_CaimanKino_10(string qName)
{
	sld = CharacterFromID("LadyBeth_Blackwood_clone");
	sld.dialog.filename = "Quest\LadyBeth_dialog.c";
	sld.dialog.currentnode = "LadyBeth_BlackWood_Boss";
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, Pchar, "", -1);
	LAi_ActorAnimation(sld, "blackwood_idle", "", 5.5);
}

void LadyBeth_CaimanKino_11(string qName)
{
	locCameraFromToPos(27.32, 20.75, -119.93, true, 33.53, 16.73, -126.34);
	DoQuestFunctionDelay("LadyBeth_CaimanKino_12", 1.2);
}

void LadyBeth_CaimanKino_12(string qName)
{
	sld = CharacterFromID("LadyBeth_Blackwood_clone");
	LAi_SetActorType(sld);
	LAi_ActorAnimation(sld, "blackwood_shot", "1", 3.0);
	DoQuestFunctionDelay("LadyBeth_CaimanKino_13", 1.43);
}

void LadyBeth_CaimanKino_13(string qName)
{
	//locCameraSleep(false);
	//locCameraFromToPos(50.78, 11.49, -150.20, true, 50.48, 9.00, -155.15);
	locCameraFromToPos(49.47, 11.50, -149.98, true, 49.85, 9.00, -154.90);
	DoQuestFunctionDelay("LadyBeth_CaimanKino_14", 0.8);
}

void LadyBeth_CaimanKino_14(string qName)
{
	sld = CharacterFromID("LadyBeth_Blackwood_clone");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	sld = CharacterFromID("LadyBeth_Our_crew_3");
	LAi_SetActorType(sld);
	LAi_ActorAnimation(sld, "death_8", "1", 4.5);
	LaunchBlood(sld, 1.0, true, "fight");
	LaunchBlood(sld, 1.0, true, "fight");
	//LAi_KillCharacter(sld);
	sld = CharacterFromID("LadyBeth_Our_crew_4");
	LAi_SetActorType(sld);
	LAi_ActorAnimation(sld, "death_5", "1", 5.3);
	LaunchBlood(sld, 1.0, true, "fight");
	LaunchBlood(sld, 1.0, true, "fight");
	//LAi_KillCharacter(sld);
	PlaySound("People Fight\Death_NPC_03.wav");
	//LAi_SetActorType(pchar);
	//LAi_ActorAnimation(pchar, "hit_fire", "1", 1.8);
	//LaunchBlood(pchar, 1.0, true, "fight");
	//LaunchBlood(pchar, 1.0, true, "fight");
	//Pchar.chr_ai.hp = stf(Pchar.chr_ai.hp) - stf(Pchar.chr_ai.hp)/10;
	DoQuestFunctionDelay("LadyBeth_CaimanKino_15", 2.0);
	DoQuestFunctionDelay("LadyBeth_CaimanBitva_2", 2.5);
}

void LadyBeth_CaimanKino_15(string qName)
{
	locCameraFromToPos(50.21, 11.67, -166.00, true, 47.52, 8.41, -140.27);
}

void LadyBeth_CaimanBitva_2(string qName)
{
	EndQuestMovie();
	locCameraTarget(PChar);
	locCameraFollow();
	LAi_SetPlayerType(pchar);
	LAi_SetFightMode(pchar, true);
	DeleteAttribute(pchar, "questTemp.NoFast");
	PlaySound("interface\abordage_wining.wav");
	PlaySound("interface\abordage_wining.wav");
	DoQuestFunctionDelay("LadyBeth_Souzniki_1", 90.0);
	
	sld = CharacterFromID("LadyBeth_Blackwood");
	ChangeCharacterAddressGroup(sld, "Caiman_Jungle_01", "quest", "boss");
	
	if (CheckAttribute(pchar, "questTemp.LadyBeth_LiteGroup"))
	{
		for (i=1; i<=14; i++)
		{
			sld = CharacterFromID("LadyBeth_Our_crew_"+i);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
		sld = CharacterFromID("LadyBeth_Alonso");
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	if (CheckAttribute(pchar, "questTemp.LadyBeth_StrongGroup"))
	{
		for (i=1; i<=20; i++)
		{
			sld = CharacterFromID("LadyBeth_Our_crew_"+i);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
		sld = CharacterFromID("LadyBeth_Alonso");
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		sld = CharacterFromID("LadyBeth_Our_Golovorez");
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	for(int i=1; i<=3; i++)
	{
		int idx = GetOfficersIndex(pchar, i);
		if(idx < 0) continue;
		sld = &Characters[idx];
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	//трупы убитых
	sld = CharacterFromID("LadyBeth_Our_crew_3");
	sld.model.animation = "man_dead";
	Characters_RefreshModel(sld);
	LAi_KillCharacter(sld);
	sld = CharacterFromID("LadyBeth_Our_crew_4");
	sld.model.animation = "man_dead";
	Characters_RefreshModel(sld);
	LAi_KillCharacter(sld);
	
	AutoSave();
}

void LadyBeth_Souzniki_1(string qName)
{
	//союзное подкрепление
	for (i=31; i<=42; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_Our_crew_"+i, "citiz_3"+(rand(8)+1), "man", "man", 6, sti(pchar.nation), 0, false, "soldier"));
		FantomMakeCoolFighter(sld, 6, 30, 30, "blade_10", "pistol1", "bullet", 30);
		if (i >= 31 && i <= 34) ChangeCharacterAddressGroup(sld, "Caiman_Jungle_01", "quest", "our_1");
		if (i >= 35 && i <= 38) ChangeCharacterAddressGroup(sld, "Caiman_Jungle_01", "quest", "our_2");
		if (i >= 39 && i <= 42) ChangeCharacterAddressGroup(sld, "Caiman_Jungle_01", "quest", "our_3");
		LAi_CharacterDisableDialog(sld);
		LAi_SetWarriorType(sld);
		RemoveItems(sld, "potion1", 10);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	PlaySound("interface\abordage_wining.wav");
	PlaySound("interface\abordage_wining.wav");
}

/*void LadyBeth_Souzniki_2(string qName)
{
	//союзное подкрепление
	for (i=51; i<=58; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_Our_crew_"+i, "citiz_3"+(rand(8)+1), "man", "man", 6, sti(pchar.nation), 0, false, "soldier"));
		FantomMakeCoolFighter(sld, 6, 30, 30, "blade_10", "pistol1", "bullet", 30);
		if (i >= 51 && i <= 54) ChangeCharacterAddressGroup(sld, "Caiman_Jungle_01", "quest", "our_1");
		if (i >= 55 && i <= 58) ChangeCharacterAddressGroup(sld, "Caiman_Jungle_01", "quest", "our_2");
		LAi_CharacterDisableDialog(sld);
		LAi_SetWarriorType(sld);
		RemoveItems(sld, "potion1", 10);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	PlaySound("interface\abordage_wining.wav");
	PlaySound("interface\abordage_wining.wav");
}*/

void LadyBeth_Pushka1(string qName)
{
	if (CharacterIsAlive("LadyBeth_EnemyPushkar_1"))
	{
		DoQuestFunctionDelay("LadyBeth_Pushka1_2", 1.7);
	}
}

void LadyBeth_Pushka1_2(string qName)
{
	if (CharacterIsAlive("LadyBeth_EnemyPushkar_1"))
	{
		CreateLocationParticles("Ship_cannon_fire", "quest", "cannon1", 0, -48, 0, "cannon_fire_3");
		DoQuestFunctionDelay("LadyBeth_Pushka1_fire", 0.25);
	}
}

void LadyBeth_Pushka1_fire(string qName)
{
	CreateLocationParticles("ShipExplode", "quest", "cannonarea1_3", -1.0, 0, 0, "boom");
	CreateLocationParticles("blast_dirt", "quest", "cannonarea1_3", -1.0, 0, 0, "");
	CreateLocationParticles("blast_inv", "quest", "cannonarea1_3", -1.0, 0, 0, "");
	
	for (i=1; i<=6; i++)
	{
		sld = CharacterFromID("LadyBeth_Our_crew_"+i);
		LAi_KillCharacter(sld);
	}
	
	LAi_group_SetLookRadius("LadyBeth_Enemy", 25.0);
	
	AddCharacterHealth(pchar, -25);
	if (CheckAttribute(pchar, "questTemp.LadyBeth_PushkaZalp"))
	{
		LAi_KillImmortalCharacter(pchar);
		return;
	}
	if (IsEquipCharacterByItem(pchar, "cirass1") || IsEquipCharacterByItem(pchar, "cirass2") || IsEquipCharacterByItem(pchar, "cirass4") || IsEquipCharacterByItem(pchar, "cirass9"))
	{
		Pchar.chr_ai.hp = stf(Pchar.chr_ai.hp)/5;
		pchar.questTemp.LadyBeth_PushkaZalp = true;
	}
	else
	{
		LAi_KillCharacter(pchar);
	}
}

void LadyBeth_Pushka2(string qName)
{
	if (CharacterIsAlive("LadyBeth_EnemyPushkar_2"))
	{
		DoQuestFunctionDelay("LadyBeth_Pushka2_2", 1.7);
	}
}

void LadyBeth_Pushka2_2(string qName)
{
	if (CharacterIsAlive("LadyBeth_EnemyPushkar_2"))
	{
		CreateLocationParticles("Ship_cannon_fire", "quest", "cannon2", 0, 0, 138, "cannon_fire_3");
		DoQuestFunctionDelay("LadyBeth_Pushka2_fire", 0.25);
	}
}

void LadyBeth_Pushka2_fire(string qName)
{
	CreateLocationParticles("ShipExplode", "quest", "cannonarea2_3", -1.0, 0, 0, "boom");
	CreateLocationParticles("blast_dirt", "quest", "cannonarea2_3", -1.0, 0, 0, "");
	CreateLocationParticles("blast_inv", "quest", "cannonarea2_3", -1.0, 0, 0, "");
	
	for (i=7; i<=12; i++)
	{
		sld = CharacterFromID("LadyBeth_Our_crew_"+i);
		LAi_KillCharacter(sld);
	}
	
	LAi_group_SetLookRadius("LadyBeth_Enemy", 25.0);
	
	AddCharacterHealth(pchar, -25);
	if (CheckAttribute(pchar, "questTemp.LadyBeth_PushkaZalp"))
	{
		LAi_KillImmortalCharacter(pchar);
		return;
	}
	if (IsEquipCharacterByItem(pchar, "cirass1") || IsEquipCharacterByItem(pchar, "cirass2") || IsEquipCharacterByItem(pchar, "cirass4") || IsEquipCharacterByItem(pchar, "cirass9"))
	{
		Pchar.chr_ai.hp = stf(Pchar.chr_ai.hp)/5;
		pchar.questTemp.LadyBeth_PushkaZalp = true;
	}
	else
	{
		LAi_KillCharacter(pchar);
	}
}

void LadyBeth_CannonerFight1(string qName)
{
	sld = CharacterFromID("LadyBeth_EnemyPushkar_1");
	LAi_SetWarriorType(sld);
	LAi_warrior_SetStay(sld, true);
	LAi_group_MoveCharacter(sld, "LadyBeth_Enemy");
}

void LadyBeth_CannonerFight2(string qName)
{
	sld = CharacterFromID("LadyBeth_EnemyPushkar_2");
	LAi_SetWarriorType(sld);
	LAi_warrior_SetStay(sld, true);
	LAi_group_MoveCharacter(sld, "LadyBeth_Enemy");
}

/*void LadyBeth_MoraleEnemy(string qName)
{
	notification("Вражеский отряд бежит", "X");
	// Низкая мораль, враги отступают
	for (i=1; i<=16; i++)
	{
		if (!CharacterIsAlive("LadyBeth_EnemyGolovorez_1") && CharacterIsAlive("LadyBeth_EnemyGroup1_"+i))
		{
			sld = CharacterFromID("LadyBeth_EnemyGroup1_"+i);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload2", "none", "", "", "", 15);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
		}
	}
	for (i=1; i<=16; i++)
	{
		if (!CharacterIsAlive("LadyBeth_EnemyGolovorez_2") && CharacterIsAlive("LadyBeth_EnemyGroup2_"+i))
		{
			sld = CharacterFromID("LadyBeth_EnemyGroup2_"+i);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload2", "none", "", "", "", 15);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
		}
	}
	for (i=1; i<=16; i++)
	{
		if (!CharacterIsAlive("LadyBeth_EnemyGolovorez_3") && CharacterIsAlive("LadyBeth_EnemyGroup3_"+i))
		{
			sld = CharacterFromID("LadyBeth_EnemyGroup3_"+i);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload2", "none", "", "", "", 15);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
		}
	}
	for (i=1; i<=16; i++)
	{
		if (!CharacterIsAlive("LadyBeth_EnemyGolovorez_4") && CharacterIsAlive("LadyBeth_EnemyGroup4_"+i))
		{
			sld = CharacterFromID("LadyBeth_EnemyGroup4_"+i);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload2", "none", "", "", "", 15);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
		}
	}
	for (i=1; i<=16; i++)
	{
		if (!CharacterIsAlive("LadyBeth_EnemyGolovorez_5") && CharacterIsAlive("LadyBeth_EnemyGroup5_"+i))
		{
			sld = CharacterFromID("LadyBeth_EnemyGroup5_"+i);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload2", "none", "", "", "", 15);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
		}
	}
}*/

void LadyBeth_BossEtap(string qName)
{
	if (CharacterIsAlive("LadyBeth_Blackwood"))
	{
		// Отряд 6 (подкрепление с тыла)
		for (i=1; i<=12; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_EnemyGroup6_"+i, "citiz_4"+(rand(8)+1), "man", "man", 3, ENGLAND, 0, false, "soldier"));
			FantomMakeCoolFighter(sld, 3, 30, 30, "blade_10", "pistol1", "bullet", 0);
			if (i >= 1 && i <= 4) ChangeCharacterAddressGroup(sld, "Caiman_Jungle_01", "quest", "enc5_1");
			if (i >= 5 && i <= 8) ChangeCharacterAddressGroup(sld, "Caiman_Jungle_01", "quest", "enc5_2");
			if (i >= 9 && i <= 12) ChangeCharacterAddressGroup(sld, "Caiman_Jungle_01", "quest", "enc5_3");
			LAi_CharacterDisableDialog(sld);
			LAi_SetWarriorType(sld);
			LAi_warrior_SetStay(sld, true);
			LAi_SetHP(sld, 40.0, 40.0);
			RemoveItems(sld, "potion1", 10);
			LAi_group_MoveCharacter(sld, "LadyBeth_Enemy");
		}
		// Босс активируется
		sld = CharacterFromID("LadyBeth_Blackwood");
		LAi_RemoveCheckMinHP(sld);
		LAi_SetImmortal(sld, false);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "LadyBeth_Enemy");
		//LAi_SetCheckMinHP(sld, 1, true, "LadyBeth_BossEtap_2");
		
		LAi_group_SetLookRadius("LadyBeth_Enemy", 1000.0);
		LAi_group_SetHearRadius("LadyBeth_Enemy", 1000.0);
		LAi_group_SetSayRadius("LadyBeth_Enemy", 1000.0);
		LAi_group_SetRelation("LadyBeth_Enemy", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("LadyBeth_Enemy", LAI_GROUP_PLAYER, false);
		LAi_group_SetCheckFunction("LadyBeth_Enemy", "LadyBeth_PobedaInJungles");
		
		DeleteQuestCondition("LadyBeth_HeadShotBoos");
	}
}

void LadyBeth_HeadShotBoos(string qName)
{
	Achievment_Set("ach_CL_148");
}

void LadyBeth_SailorDead(string qName)
{
	SetCrewQuantity(pchar, GetCrewQuantity(pchar) - sti(pchar.SailorDiedInBattle));
	pchar.SailorDiedInBattleInfo = sti(pchar.SailorDiedInBattleInfo) + sti(pchar.SailorDiedInBattle);
}

void LadyBeth_PobedaInJungles(string qName)
{
	if (CharacterIsAlive("LadyBeth_Blackwood"))
	{
		DeleteQuestCondition("LadyBeth_BossEtap");
		DoQuestFunctionDelay("LadyBeth_BossEtap", 0.5);
	}
	else
	{
		Event("QuestDelayExit","sl", "", 0);
		DoQuestFunctionDelay("LadyBeth_PobedaInJungles_2", 1.5);
	}
}

void LadyBeth_PobedaInJungles_2(string qName)
{
	DoFunctionReloadToLocation("Caiman_Jungle_01", "quest", "boss2", "LadyBeth_PobedaInJungles_3");
}

void LadyBeth_PobedaInJungles_3(string qName)
{
	LAi_group_Delete("LadyBeth_Enemy");
	chrDisableReloadToLocation = false; //временно откроем проход в бухту к Леди Бет
	LocatorReloadEnterDisable("Caiman_Jungle_01", "reload1_back", true);
	// остальное
	SetFunctionLocationCondition("LadyBeth_ShipInShore_1", "Shore16", false);
	SetFunctionLocationCondition("LadyBeth_Grot_MatrosySdautsya", "Caiman_Grot", false);
	// Мёртвого капитана убираем с глобаки и даём слух
	sld = CharacterFromID("LadyBeth_cap");
	LAi_KillCharacter(sld);
	AddSimpleRumourAllNations(GetConvertStr("LadyBeth_Rum2", "LadyBeth.txt"), 30, 1);
	// офицеры хотят поговорить
	if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && CharacterIsAlive("Helena"))
	{
		sld = CharacterFromID("Helena");
		AddLandQuestMark(sld, "questmarkmain");
		sld.dialog.filename = "Quest\LadyBeth_dialog.c";
		sld.dialog.currentnode = "LadyBeth_Helena_1";
	}
	if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && CharacterIsAlive("Mary"))
	{
		sld = CharacterFromID("Mary");
		AddLandQuestMark(sld, "questmarkmain");
		sld.dialog.filename = "Quest\LadyBeth_dialog.c";
		sld.dialog.currentnode = "LadyBeth_Mary_1";
	}
	if (CharacterIsAlive("Tichingitu") && CheckPassengerInCharacter(pchar, "Tichingitu"))
	{
		sld = CharacterFromID("Tichingitu");
		AddLandQuestMark(sld, "questmarkmain");
		sld.dialog.filename = "Quest\LadyBeth_dialog.c";
		sld.dialog.currentnode = "LadyBeth_Tichingitu_1";
	}
	if (CharacterIsAlive("Irons") && CheckPassengerInCharacter(pchar, "Irons"))
	{
		sld = CharacterFromID("Irons");
		AddLandQuestMark(sld, "questmarkmain");
		sld.dialog.filename = "Quest\LadyBeth_dialog.c";
		sld.dialog.currentnode = "LadyBeth_Irons_1";
	}
	if (CharacterIsAlive("Knippel") && CheckPassengerInCharacter(pchar, "Knippel"))
	{
		sld = CharacterFromID("Knippel");
		AddLandQuestMark(sld, "questmarkmain");
		sld.dialog.filename = "Quest\LadyBeth_dialog.c";
		sld.dialog.currentnode = "LadyBeth_Knippel_1";
	}
	for(int i=1; i<=3; i++)
	{
		int idx = GetOfficersIndex(pchar, i);
		if(idx < 0) continue;
		sld = &Characters[idx];
		ChangeCharacterAddressGroup(sld, pchar.location, "quest", "boss2");
		LAi_SetOfficerType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	DoQuestFunctionDelay("LadyBeth_PobedaInJungles_4", 2.5);
	// ставим Алонсо
	if (CharacterIsAlive("LadyBeth_Alonso"))
	{
		sld = CharacterFromID("LadyBeth_Alonso");
		ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload2");
		TeleportCharacterToPosAy(sld, 20.23, 17.00, -110.28, 2.50);
		LAi_CharacterEnableDialog(sld);
		LAi_SetStayType(sld);
		AddLandQuestMark(sld, "questmarkmain");
		sld.dialog.filename = "Quest\LadyBeth_dialog.c";
		sld.dialog.currentnode = "LadyBeth_Alonso_1";
	}
	else
	{
		sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_Alonso", "citiz_36", "man", "man", 15, pchar.nation, 0, false, "pirate"));
		FantomMakeCoolFighter(sld, 15, 70, 70, "blade_13", "pistol6", "bullet", 300);
		sld.name 	= StringFromKey("SharlieTrial_29");
		sld.lastname = StringFromKey("SharlieTrial_30");
		ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload2");
		TeleportCharacterToPosAy(sld, 20.23, 17.00, -110.28, 2.50);
		LAi_CharacterEnableDialog(sld);
		LAi_SetStayType(sld);
		AddLandQuestMark(sld, "questmarkmain");
		sld.dialog.filename = "Quest\LadyBeth_dialog.c";
		sld.dialog.currentnode = "LadyBeth_Alonso_1";
	}
	// труп Блеквуда
	sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_Blackwood_death", "quest_off_eng", "man", "man_dead", 30, ENGLAND, 0, false, "soldier"));
	FantomMakeCoolFighter(sld, 30, 70, 70, "blade_15", "pistol6", "bullet", 200);
	GiveItem2Character(sld, "cirass1");
	EquipCharacterByItem(sld, "cirass1");
	AddItems(sld, "cartridge", 30);
	AddItems(sld, "GunPowder", 30);
	ChangeCharacterAddressGroup(sld, "Caiman_Jungle_01", "quest", "boss");
	TeleportCharacterToPosAy(sld, 27.63, 18.81, -119.35, 2.0);
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	//sld.CantLoot = true;
	sld.DeadWithBlade = true;
	LAi_SetFightMode(sld, true);
	LAi_KillCharacter(sld);
	for (i=1; i<=60; i++)
	{
		if (CharacterIsAlive("LadyBeth_Our_crew_"+i))
		{
			sld = CharacterFromID("LadyBeth_Our_crew_"+i);
			sld.lifeday = 0;
			ChangeCharacterAddressGroup(sld, "none", "", "");
		}
	}
}

void LadyBeth_PobedaInJungles_4(string qName)
{
	OfficersFollow();
}

void LadyBeth_Grot_MatrosySdautsya(string qName)
{
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(loadedLocation, true);
	pchar.GenQuestBox.Caiman_Grot.box1.items.jewelry5 = 100;
	pchar.GenQuestBox.Caiman_Grot.box1.items.jewelry6 = 200;
	
	for (i=1; i<=8; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_MatrosyPryachutsya_"+i, "citiz_3"+(rand(8)+1), "man", "man", 3, ENGLAND, 0, false, "soldier"));
		FantomMakeCoolFighter(sld, 3, 30, 30, "blade_10", "pistol1", "bullet", 0);
		sld.dialog.filename = "Quest\LadyBeth_dialog.c";
		sld.dialog.currentnode = "LadyBeth_MatrosyInGrot";
		ChangeCharacterAddressGroup(sld, "Caiman_Grot", "goto", "goto4");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
}

void LadyBeth_Grot_MatrosySdautsya_2(string qName)
{
	for (i=1; i<=8; i++)
	{
		sld = CharacterFromID("LadyBeth_MatrosyPryachutsya_"+i);
		LAi_SetActorType(sld);
		LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", 5);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	LAi_LocationFightDisable(loadedLocation, false);
}

void LadyBeth_ShipInShore_1(string qName)
{
	//chrDisableReloadToLocation = true;
	SetFunctionLocatorCondition("LadyBeth_ShipInShore_2", "Shore16", "encdetector", "enc01", false)
	//ставим наших бойцов
	for (i=1; i<=14; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_Our_crew_"+i, "citiz_3"+(rand(8)+1), "man", "man", 6, sti(pchar.nation), -1, false, "soldier"));
		FantomMakeCoolFighter(sld, 6, 30, 30, "blade_10", "pistol1", "bullet", 30);
		ChangeCharacterAddressGroup(sld, "Shore16", "encdetector", "enc02");
		LAi_CharacterDisableDialog(sld);
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, pchar, "", -1);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	// труп на берегу
	/*sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_DeadCrew_1", "citiz_3"+(rand(8)+1), "man", "man_dead", 1, sti(pchar.nation), -1, false, "soldier"));
	ChangeCharacterAddressGroup(sld, "Shore16", "reload", "reload2");
	GiveItem2Character(sld, "slave_02");
	EquipCharacterByItem(sld, "slave_02");
	sld.DontClearDead = true;
	sld.CantLoot = true;
	sld.DeadWithBlade = true;
	LAi_SetFightMode(sld, true);
	LAi_KillCharacter(sld);*/
	
	sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_enemyMushket", "mush_eng_"+(rand(2)+1), "man", "mushketer", 12, ENGLAND, -1, false, "soldier"));
	FantomMakeCoolFighter(sld, 12, 50, 50, "", "mushket2", "bullet", 0);
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, "Shore16", "quest", "quest1");
	LAi_SetActorType(sld);
	
	for (i=1; i<=8; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_CrewOfShip_"+i, "citiz_3"+(rand(8)+1), "man", "man", 10, ENGLAND, -1, false, "soldier"));
		FantomMakeCoolFighter(sld, 6, 30, 30, "blade_10", "pistol1", "bullet", 30);
		ChangeCharacterAddressGroup(sld, "Shore16", "goto", "goto"+i);
		LAi_SetWarriorType(sld);
	}
}

void LadyBeth_ShipInShore_2(string qName)
{
	ResetTimeScale();
	pchar.questTemp.NoFast = true;
	LAi_SetActorType(pchar);
	LAi_FadeLong("", "");
	DoQuestFunctionDelay("LadyBeth_ShipInShore_2_1", 1.0);
}

void LadyBeth_ShipInShore_2_1(string qName)
{
	StartQuestMovie(true, false, true);
	SetMusic("music_LadyBeth");
	locCameraFlyToPositionLookToPoint(-7.50, 1.61, -5.84, -3.11, 3.44, 3.53, 4.93, 9.67, 41.97, -1, 7800/GetDeltaTime());
	Pchar.FuncCameraFly = "LadyBeth_ShipInShore_3";
}

void LadyBeth_ShipInShore_3(string qName)
{
	locCameraFlyToPositionLookToPoint(-3.72, 1.22, 62.77, -5.72, 3.73, 59.48, -3.23, 4.65, 55.50,  -1, 10200/GetDeltaTime());
	Pchar.FuncCameraFly = "LadyBeth_ShipInShore_4";
}

void LadyBeth_ShipInShore_4(string qName)
{
	locCameraFlyToPositionLookToPoint(7.11, 2.22, 25.36, -3.48, 1.30, 44.54, -3.23, 3.95, 55.50, -1, 5300/GetDeltaTime());
	Pchar.FuncCameraFly = "LadyBeth_ShipInShore_5";
}

void LadyBeth_ShipInShore_5(string qName)
{
	locCameraFlyToPositionLookToPoint(25.59, 11.11, 27.32, 16.80, 5.16, 25.45, -3.23, 4.65, 55.50, -1, 11000/GetDeltaTime());
	Pchar.FuncCameraFly = "LadyBeth_ShipInShore_6";
}

void LadyBeth_ShipInShore_6(string qName)
{
	locCameraFlyToPositionLookToPoint(16.80, 5.16, 25.45, 15.32, 4.16, 25.13, -3.23, 4.65, 55.50, -1, 6000/GetDeltaTime());
	Pchar.FuncCameraFly = "LadyBeth_ShipInShore_7";
}

void LadyBeth_ShipInShore_7(string qName)
{
	SetMusic("");
	locCameraFromToPos(-6.07, 5.25, 51.89, true, -1.06, 3.12, 51.55);
	DoQuestFunctionDelay("LadyBeth_ShipInShore_8", 2.5);
}

void LadyBeth_ShipInShore_8(string qName)
{
	sld = CharacterFromID("LadyBeth_enemyMushket");
	CharacterTurnToLoc(sld, "reload", "reload2");
	DoQuestFunctionDelay("LadyBeth_ShipInShore_9", 1.0);
}

void LadyBeth_ShipInShore_9(string qName)
{
	PlaySound("PEOPLE\whistling.wav");
	PlaySound("PEOPLE\whistling.wav");
	DoQuestFunctionDelay("LadyBeth_ShipInShore_10", 1.5);
}

void LadyBeth_ShipInShore_10(string qName)
{
	locCameraFromToPos(-3.18, 5.45, 55.50, true, -3.94, 3.72, 48.90);
	DoQuestFunctionDelay("LadyBeth_ShipInShore_11", 2.5);
}

void LadyBeth_ShipInShore_11(string qName)
{
	sld = CharacterFromID("LadyBeth_enemyMushket");
	LAi_SetActorType(sld);
	LAi_ActorAnimation(sld, "Shot", "1", 1.5);
	DoQuestFunctionDelay("LadyBeth_ShipInShore_12", 2.5);
}

void LadyBeth_ShipInShore_12(string qName)
{
	PlaySound("interface\abordage_wining.wav");
	PlaySound("interface\abordage_wining.wav");
	for (i=1; i<=14; i++)
	{
		sld = CharacterFromID("LadyBeth_Our_crew_"+i);
		LAi_SetActorType(sld);
		LAi_ActorRunToLocator(sld, "reload", "reload2", "", -1);
	}
	/*sld = CharacterFromID("LadyBeth_Alonso");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocator(sld, "reload", "reload2", "", -1);*/
	LAi_SetActorType(pchar);
	LAi_ActorRunToLocator(pchar, "reload", "reload2", "", -1);
	DoQuestFunctionDelay("LadyBeth_ShipInShore_13", 1.5);
}

void LadyBeth_ShipInShore_13(string qName)
{
	LAi_FadeToBlackStart();
	DoQuestFunctionDelay("LadyBeth_ShipInShore_14", 1.5);
}

void LadyBeth_ShipInShore_14(string qName)
{
	DoQuestFunctionDelay("LadyBeth_ShipInShore_15", 3.5);
	sld = CharacterFromID("LadyBeth_enemyMushket");
	LAi_SetImmortal(sld, false);
	LAi_KillCharacter(sld);
	for (i=1; i<=14; i++)
	{
		sld = CharacterFromID("LadyBeth_Our_crew_"+i);
		sld.lifeday = 0;
		ChangeCharacterAddressGroup(sld, "none", "", "");
	}
	if (CharacterIsAlive("LadyBeth_Alonso"))
	{
		sld = CharacterFromID("LadyBeth_Alonso");
		ChangeCharacterAddressGroup(sld, "none", "", "");
	}
	for(int i=1; i<=3; i++)
	{
		int idx = GetOfficersIndex(pchar, i);
		if(idx < 0) continue;
		sld = &Characters[idx];
		ChangeCharacterAddressGroup(sld, pchar.location, "officers", "reload3_"+i);
	}
	ChangeCharacterAddressGroup(pchar, "Shore16", "quest", "quest1");
	LAi_SetActorType(pchar);
	PlaySound("Interface\MusketFire1.wav");
	PlaySound("Interface\MusketFire1.wav");
	PlaySound("Interface\MusketFire1.wav");
}

void LadyBeth_ShipInShore_15(string qName)
{
	LAi_FadeToBlackEnd();
	//ResetSound();
	DoQuestFunctionDelay("LadyBeth_ShipInShore_16", 4.0);
}

void LadyBeth_ShipInShore_16(string qName)
{
	// прописываем каюту внутри корабля -->
	sld = &Locations[FindLocation("Shore16")];
	sld.models.always.locators = "bay_sp2_locators_ship";
	sld.reload.l41.name = "reload4";
	sld.reload.l41.go = "Location_reserve_05";
	sld.reload.l41.emerge = "reload1";
	sld.reload.l41.autoreload = "0";
	sld.reload.l41.label = "cabine";
	sld.reload.l41.disable = false;
	
	//sld = Findlocation("Location_reserve_05");
	sld = &Locations[FindLocation("Location_reserve_05")];
	DeleteAttribute(sld, "IslandId");
	DeleteAttribute(sld, "type");
	DeleteAttribute(sld, "models");
	DeleteAttribute(sld, "environment");
	DeleteAttribute(sld, "Box1");
	DeleteAttribute(sld, "Box2");
	DeleteAttribute(sld, "Box3");
	sld.id.label = "cabine";
	sld.filespath.models = "locations\decks\capmd";
	sld.image = "loading\Capdeck_" + rand(4) + ".tga";
	//Sound
	sld.type = "boarding_cabine";
	//Models
	//Always
	sld.models.always.l1 = "capmd";
	sld.models.always.l1.level = 65538;

	sld.models.always.window = "capmd_bdw";
	sld.models.always.window.tech = "LocationWindows";
	sld.models.always.window.level = 65539;

	//Day
	sld.models.day.l2 = "capmd_bd"; //пушки с кормы, старые портреты и сундуки
	sld.models.day.l2.level = 65538;
	sld.models.day.locators = "capmd_lbd"; //боевые локаторы, смещаем loc0 к центру
	sld.models.day.charactersPatch = "capmd_pbd"; //дерево, без стола и ковра
	sld.models.day.fonar = "capmd_fd"; //фонарь общий, днём дополнительное освещение не работает

	//Night
	sld.models.night.l3 = "capmd_bn"; //пушки по бортам, старые портреты и сундуки
    sld.models.night.l3.level = 65538;
    sld.models.night.locators = "capmd_lbn";  //боевые локаторы, смещаем loc0 к торцу стола
    sld.models.night.charactersPatch = "capmd_pbn"; //дерево, без ковра
    sld.models.night.fonar = "capmd_fn"; //фонарь общий, добавляет локаторы каретной и настольной свечей

	//Environment
	sld.environment.sea = "true";
	sld.environment.weather = "true";

    sld.locators_radius.randitem.randitem1 = 1;
    sld.locators_radius.randitem.randitem2 = 1;

    sld.locators_radius.rld.loc0 = 0.5;
    sld.locators_radius.rld.loc1 = 0.5;
    sld.locators_radius.rld.loc2 = 0.5;
    sld.locators_radius.rld.aloc0 = 0.5;
    sld.locators_radius.rld.aloc1 = 0.5;
    sld.locators_radius.rld.aloc2 = 0.5;

	sld.boarding = "true";
	sld.boarding.nextdeck = "";
	sld.camshuttle = 1;
	sld.boarding.locatorNum = 1;
	sld.CabinType = true;
	sld.environment.weather.rain = false;
	sld.boarding.Loc.Hero = "loc2";
    sld.boarding.Loc.Capt = "loc0";
	
	sld.reload.l1.name = "reload1";
	sld.reload.l1.go = "Shore16";
	sld.reload.l1.emerge = "reload3";
	sld.reload.l1.autoreload = "0";
	sld.reload.l1.label = "Shore16";
	sld.reload.l1.disable = false;
	// прописываем каюту внутри корабля <--
	//
	//EndQuestMovie();
	//DeleteAttribute(pchar, "questTemp.NoFast");
	setCharacterShipLocation(pchar, "Shore16");
	DoFunctionReloadToLocation("Shore16", "reload", "reload3", "LadyBeth_ShipInShore_17");
}

void LadyBeth_ShipInShore_17(string qName)
{
	chrDisableReloadToLocation = true;
	//LAi_LocationFightDisable(loadedLocation, true);
	locCameraFromToPos(-15.48, 1.21, 60.26, true, -11.17, 0.33, 53.97);
	
	sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_enemyMushket", "sold_eng_3", "man", "man_dead", 12, ENGLAND, 0, false, "soldier"));
	ChangeCharacterAddressGroup(sld, "Shore16", "quest", "quest1");
	TeleportCharacterToPosAy(sld, 10.31, 2.87, 34.36, 1.50);
	sld.DontClearDead = true;
	sld.CantLoot = true;
	LAi_KillCharacter(sld);
	
	sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_DeadMatrosNaPalube", "citiz_3"+(rand(8)+1), "man", "man_dead", 3, ENGLAND, 0, false, "soldier"));
	ChangeCharacterAddressGroup(sld, "Shore16", "quest", "quest1");
	TeleportCharacterToPosAy(sld, 10.73, 2.87, 34.50, 0.00);
	sld.DontClearDead = true;
	sld.CantLoot = true;
	LAi_KillCharacter(sld);
	
	//наши солдаты
	if (GetOfficersQuantity(pchar) == 0)
	{
		for (i=1; i<=3; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_Our_crew_"+i, "citiz_3"+(rand(8)+1), "man", "man", 6, sti(pchar.nation), -1, false, "soldier"));
			FantomMakeCoolFighter(sld, 6, 30, 30, "blade_10", "pistol1", "bullet", 30);
			ChangeCharacterAddressGroup(sld, pchar.location, "officers", "reload3_"+i);
			LAi_CharacterDisableDialog(sld);
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
	}
	if (GetOfficersQuantity(pchar) == 1)
	{
		for (i=1; i<=2; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_Our_crew_"+i, "citiz_3"+(rand(8)+1), "man", "man", 6, sti(pchar.nation), -1, false, "soldier"));
			FantomMakeCoolFighter(sld, 6, 30, 30, "blade_10", "pistol1", "bullet", 30);
			ChangeCharacterAddressGroup(sld, pchar.location, "officers", "reload3_"+i);
			LAi_CharacterDisableDialog(sld);
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
	}
	if (GetOfficersQuantity(pchar) == 2)
	{
		sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_Our_crew_1", "citiz_3"+(rand(8)+1), "man", "man", 6, sti(pchar.nation), -1, false, "soldier"));
		FantomMakeCoolFighter(sld, 6, 30, 30, "blade_10", "pistol1", "bullet", 30);
		ChangeCharacterAddressGroup(sld, pchar.location, "officers", "reload3_1");
		LAi_CharacterDisableDialog(sld);
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, pchar, "", -1);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	// Алонсо
	if (CharacterIsAlive("LadyBeth_Alonso"))
	{
		sld = CharacterFromID("LadyBeth_Alonso");
		ChangeCharacterAddressGroup(sld, pchar.location, "officers", "reload3_1");
		LAi_CharacterDisableDialog(sld);
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, pchar, "", -1);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	else
	{
		sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_Alonso", "citiz_36", "man", "man", 15, pchar.nation, -1, false, "pirate"));
		FantomMakeCoolFighter(sld, 15, 70, 70, "blade_13", "pistol6", "bullet", 300);
		sld.name 	= StringFromKey("SharlieTrial_29");
		sld.lastname = StringFromKey("SharlieTrial_30");
		ChangeCharacterAddressGroup(sld, pchar.location, "officers", "reload3_1");
		LAi_CharacterDisableDialog(sld);
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, pchar, "", -1);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	
	DoQuestFunctionDelay("LadyBeth_ShipInShore_18", 3.5);
}

void LadyBeth_ShipInShore_18(string qName)
{
	locCameraFromToPos(10.29, 6.35, 33.61, true, 10.87, 1.19, 35.19);
	DoQuestFunctionDelay("LadyBeth_ShipInShore_19", 2.5);
}

void LadyBeth_ShipInShore_19(string qName)
{
	locCameraFromToPos(11.87, 5.08, 32.35, true, 8.79, 1.74, 37.24);
	
	LAi_SetStayType(pchar);
	for (i=1; i<=8; i++)
	{
		sld = CharacterFromID("LadyBeth_CrewOfShip_"+i);
		//sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_CrewOfShip_"+i, "citiz_3"+(rand(8)+1), "man", "man", 8, ENGLAND, 0, false, "soldier"));
		//FantomMakeCoolFighter(sld, 8, 40, 40, "blade_10", "pistol1", "bullet", 30);
		//ChangeCharacterAddressGroup(sld, "Shore16", "goto", "goto"+i);
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, CharacterFromID("LadyBeth_CrewOfShip_7"), "", -1);
		if (i==7)
		{
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto7");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.filename = "Quest\LadyBeth_dialog.c";
			sld.dialog.currentnode = "LadyBeth_EnemyMatros_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		}
	}
}

void LadyBeth_ShipInShore_Bitva(string qName)
{
	EndQuestMovie();
	DeleteAttribute(pchar, "questTemp.NoFast");
	LAi_SetPlayerType(pchar);
	pchar.questTemp.LadyBeth_BitvaNaKorable = true;
	LAi_LocationFightDisable(loadedLocation, false);
	if (CharacterIsHere("Helena")) Return_HelenaOfficer();
	if (CharacterIsHere("Knippel")) Return_KnippelOfficer();
	if (CharacterIsHere("Irons")) Return_IronsOfficer();
	LAi_SetFightMode(pchar, true);
	for (i=1; i<=3; i++)
	{
		if (CharacterIsAlive("LadyBeth_Our_crew_"+i))
		{
			sld = CharacterFromID("LadyBeth_Our_crew_"+i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
	}
	sld = CharacterFromID("LadyBeth_Alonso");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	for (i=1; i<=8; i++)
	{
		sld = CharacterFromID("LadyBeth_CrewOfShip_"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
	LAi_group_SetCheckFunction("EnemyFight", "LadyBeth_ShipInShore_Vnutri_1");
}

void LadyBeth_ShipInShore_Vnutri_1(string qName)
{
	EndQuestMovie();
	LAi_SetPlayerType(pchar);
	DeleteAttribute(pchar, "questTemp.NoFast");
	chrDisableReloadToLocation = false;
	SetFunctionLocationCondition("LadyBeth_ShipInShore_Vnutri_2", "Location_reserve_05", false);
	
	for (i=1; i<=8; i++)
	{
		if (CharacterIsAlive("LadyBeth_CrewOfShip_"+i))
		{
			sld = CharacterFromID("LadyBeth_CrewOfShip_"+i);
			LAi_SetWarriorType(sld);
			LAi_CharacterDisableDialog(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
	}
	if (CharacterIsHere("Helena")) Return_HelenaOfficer();
	if (CharacterIsHere("Knippel")) Return_KnippelOfficer();
	if (CharacterIsHere("Irons")) Return_IronsOfficer();
}

void LadyBeth_ShipInShore_Vnutri_2(string qName)
{
	CreateSea(EXECUTE, REALIZE);
	CreateWeather(EXECUTE,REALIZE);
	
	Locations[FindLocation(pchar.location)].box1.items.gold = 25000;
	Locations[FindLocation(pchar.location)].box1.items.spyglass3 = 1;
	Locations[FindLocation(pchar.location)].box1.items.icollection = 1;
	Locations[FindLocation(pchar.location)].box1.items.map_normal = 1;
	Locations[FindLocation(pchar.location)].box1.items.LadyBeth_Book = 1;
	
	PChar.quest.LadyBeth_Book.win_condition.l1 = "item";
	PChar.quest.LadyBeth_Book.win_condition.l1.item = "LadyBeth_Book";
	PChar.quest.LadyBeth_Book.function = "LadyBeth_Book";
	
	SetFunctionLocationCondition("LadyBeth_ShipInShore_Vnutri_3", "Shore16", false);
}

void LadyBeth_Book(string qName)
{
	TakeItemFromCharacter(pchar, "LadyBeth_Book");
	AddQuestRecordInfo("LadyBeth_Book", "1");
}

void LadyBeth_ShipInShore_Vnutri_3(string qName)
{
	// Леди Бет входит в нашу эскадру
	sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_Companion", "mercen_15", "man", "man", 1, ENGLAND, -1, false, "quest"));
	FantomMakeCoolSailor(sld, SHIP_LADYBETH, GetConvertStr("LadyBeth_Ship_Name", "LadyBeth.txt"), CANNON_TYPE_CANNON_LBS24, 70, 70, 70);
	sld.Ship.Crew.Quantity = sti(sld.ship.Crew.Quantity) / 4;
	sld.ship.Crew.Morale = 100;
	SetSPECIAL(sld, 4, 2, 3, 4, 4, 2, 1);
	InitStartParam(sld);
	sld.rank = 1;
	SetCharacterPerk(sld, "HPPlus");
	SetCharacterPerk(sld, "EnergyPlus");
	SetCharacterPerk(sld, "Brander");
	SetCharacterPerk(sld, "Troopers");
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
	SetCompanionIndex(pchar, -1, sti(sld.index));
	//трюм корабля
	SetCharacterGoods(sld, GOOD_FOOD, 1000);
	SetCharacterGoods(sld, GOOD_MEDICAMENT, 500);
	SetCharacterGoods(sld, GOOD_RUM, 300);
	SetCharacterGoods(sld, GOOD_GOLD, 100);
	SetCharacterGoods(sld, GOOD_ROPES, 50);
	SetCharacterGoods(sld, GOOD_SHIPSILK, 50);
	SetCharacterGoods(sld, GOOD_CINNAMON, 50);
	SetCharacterGoods(sld, GOOD_SANDAL, 50);
	AddCharacterGoodsSimple(sld, GOOD_BOMBS, 500);
	AddCharacterGoodsSimple(sld, GOOD_GRAPES, 500);
	AddCharacterGoodsSimple(sld, GOOD_POWDER, 750);
	
	//
	if (!CheckAttribute(pchar, "questTemp.LadyBeth_BitvaNaKorable"))
	{
		for (i=1; i<=8; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("LadyBeth_CrewOfShip_"+i, "citiz_3"+(rand(8)+1), "man", "man", 8, ENGLAND, 0, false, "soldier"));
			FantomMakeCoolFighter(sld, 8, 40, 40, "blade_10", "pistol1", "bullet", 30);
			ChangeCharacterAddressGroup(sld, "Shore16", "goto", "goto"+i);
			LAi_SetWarriorType(sld);
			LAi_CharacterDisableDialog(sld);
		}
	}
	for (i=1; i<=3; i++)
	{
		if (CharacterIsAlive("LadyBeth_Our_crew_"+i))
		{
			sld = CharacterFromID("LadyBeth_Our_crew_"+i);
			sld.lifeday = 0;
		}
	}
	if (CharacterIsAlive("LadyBeth_Alonso"))
	{
		sld = CharacterFromID("LadyBeth_Alonso");
		sld.lifeday = 0;
	}
	chrDisableReloadToLocation = true;
	DoQuestFunctionDelay("LadyBeth_KorablNash", 3.0);
}

void LadyBeth_KorablNash(string qName)
{
	QuestToSeaLogin_Launch();
	QuestToSeaLogin_PrepareLoc("Caiman", "Quest_Ships", "Quest_ship_1", true);
	//убираем запреты
	bQuestDisableMapEnter = false;
	chrDisableReloadToLocation = false;
	QuestOpenSeaExit();
	LocatorReloadEnterDisable("Shore16", "boat", false);
	LocatorReloadEnterDisable("Shore17", "boat", false);
	DeleteAttribute(pchar,"questTemp.TimeLock");
	DeleteAttribute(pchar, "GenQuest.CannotWait");
	DeleteAttribute(pchar, "GenQuest.HunterLongPause");
	if(CheckAttribute(pchar,"questTemp.BlackMark.IronsBlock")) DeleteAttribute(pchar,"questTemp.BlackMark.IronsBlock");
	//через день приводим Кайман в порядок
	DelQMfromCaiman();
	SetTimerFunction("LadyBeth_CaimanReset", 0, 0, 1);
	//ачивки
	Achievment_Set("ach_CL_147");
	if (sti(pchar.rank) <= 10) Achievment_Set("ach_CL_150");
	//офицеры в норму
	if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && CharacterIsAlive("Mary"))
	{
		Return_MaryOfficer();
		DelLandQuestMark(CharacterFromID("Mary"));
	}
	if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && CharacterIsAlive("Helena"))
	{
		Return_HelenaOfficer();
		DelLandQuestMark(CharacterFromID("Helena"));
	}
	if (CharacterIsAlive("Tichingitu") && CheckPassengerInCharacter(pchar, "Tichingitu"))
	{
		Return_TichingituOfficer();
		DelLandQuestMark(CharacterFromID("Tichingitu"));
	}
	if (CharacterIsAlive("Irons") && CheckPassengerInCharacter(pchar, "Irons"))
	{
		Return_IronsOfficer();
		DelLandQuestMark(CharacterFromID("Irons"));
	}
	if (CharacterIsAlive("Knippel") && CheckPassengerInCharacter(pchar, "Knippel"))
	{
		Return_KnippelOfficer();
		DelLandQuestMark(CharacterFromID("Knippel"));
	}
}

void LadyBeth_CaimanReset(string qName)
{
	//разрешаем высаживаться
	Island_SetReloadEnableGlobal("Caiman", true);
	//джунгли в порядок
	DeleteAttribute(&locations[FindLocation("Caiman_Jungle_01")], "models.always.parts");
	DeleteAttribute(&locations[FindLocation("Caiman_Jungle_01")], "models.always.decals");
	
	sld = &Locations[FindLocation("Caiman_Jungle_01")];
	sld.filespath.models = "locations\Outside\Jungles\jungle13";
	sld.models.always.jungle = "jungle13";	
	sld.models.always.locators = "jungle13_locators";
	sld.models.always.grassPatch = "jungle13_grass";
	sld.models.always.grassPatch.texture = "grass\grassshore.tga.tx";
	sld.models.day.charactersPatch = "jungle13_patch";
	sld.models.night.charactersPatch = "jungle13_patch";
	//Пустынный пляж в порядок
	DeleteAttribute(&locations[FindLocation("Shore16")], "models.always.parts");
	DeleteAttribute(&locations[FindLocation("Shore16")], "models.always.sb");
	DeleteAttribute(&locations[FindLocation("Shore16")], "models.always.watermask");
	DeleteAttribute(&locations[FindLocation("Shore16")], "models.always.windows");
	DeleteAttribute(&locations[FindLocation("Shore16")], "models.always.jump");
	DeleteAttribute(&locations[FindLocation("Shore16")], "models.always.decals");
	
	sld = &Locations[FindLocation("Shore16")];
	sld.filespath.models = "locations\Outside\Shores\Shore07";
	sld.models.always.shore07 = "shore07";
	sld.models.always.shore07seabed = "shore07_sb";
	sld.models.always.locators = "shore07_locators";
	sld.models.always.grassPatch = "shore07_grass";
	sld.models.day.charactersPatch = "shore07_patch";
	sld.models.night.charactersPatch = "shore07_patch";
	//остальное
	LocatorReloadEnterDisable("Caiman_Jungle_01", "reload1_back", false);
	locations[FindLocation("Caiman_Jungle_01")].DisableEncounters = false;
	locations[FindLocation("Shore16")].DisableEncounters = false;
	locations[FindLocation("Shore17")].DisableEncounters = false;
	locations[FindLocation("Caiman_Grot")].DisableEncounters = false;
	locations[FindLocation("Caiman_CaveEntrance")].DisableEncounters = false;
	DeleteQuestCondition("LadyBeth_Grot_MatrosySdautsya");
}

//===============Квестовая марка на Каймане==============
void SetQMtoCaiman()
{
	if(!IsEntity(&worldMap))
	{
		worldMap.labels.caiman.icon1 = 9;
		worldMap.labels.caiman.majorQM = true;
	}
	else
	{
		pchar.quest.caiman.win_condition.l1			= "EnterToSea";           	
        pchar.quest.caiman.function    				= "DelaySetQMtoCaiman";
	}
}

void DelaySetQMtoCaiman(string qName)
{
	worldMap.labels.caiman.icon1 = 9;
	worldMap.labels.caiman.majorQM = true;
}

void DelQMfromCaiman()
{
	if(!IsEntity(&worldMap))
	{
		if(CheckAttribute(worldMap,"labels.caiman.icon1"))
			DeleteAttribute(&worldMap,"labels.caiman.icon1");
		if(CheckAttribute(worldMap,"labels.caiman.majorQM"))
			DeleteAttribute(&worldMap,"labels.caiman.majorQM");
	}
	else
	{
		pchar.quest.caiman.win_condition.l1			= "EnterToSea";           	
        pchar.quest.caiman.function    				= "DelayDelQMfromCaiman";
	}
}

void DelayDelQMfromCaiman(string qName)
{
	if(CheckAttribute(worldMap,"labels.caiman.icon1"))
			DeleteAttribute(&worldMap,"labels.caiman.icon1");
	if(CheckAttribute(worldMap,"labels.caiman.majorQM"))
		DeleteAttribute(&worldMap,"labels.caiman.majorQM");
}

//=================События на Бриджтауне=================
void LadyBeth_Barbados_Elizabeth_1(string qName)
{
	notification(XI_ConvertString("TreasuresNear"), "Icollection");
	PlaySound("interface\notebook.wav");
	TakeNItems(Pchar, "LadyBeth_Map", -1);
	sld = GetCharacter(NPC_GenerateCharacter("LadyVeth_Elizabeth", "girl_11", "woman", "woman", 5, ENGLAND, -1, false, "quest"));
	sld.name 	= GetConvertStr("LadyBeth_Elizabeth_Name", "LadyBeth.txt");
	sld.lastname = GetConvertStr("LadyBeth_Elizabeth_lastname", "LadyBeth.txt");
	ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation_Sp1", "goto", "goto1");
	sld.dialog.filename = "Quest\LadyBeth_dialog.c";
	sld.dialog.currentnode = "LadyBeth_Elizabeth_1";
	LAi_SetStayType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	LAi_SetImmortal(sld, true);
	AddLandQuestMark(sld, "questmarkmain");
}

void LadyBeth_Barbados_Elizabeth_2(string qName)
{
	Achievment_Set("ach_CL_149"); // нашли устав Блеквуда
	sld = CharacterFromID("LadyVeth_Elizabeth");
	LAi_SetActorType(sld);
	sld.lifeday = 0;
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	SetFunctionLocationCondition("LadyBeth_Barbados_Diego_1", "Bridgetown_Plantation", false);
}

void LadyBeth_Barbados_Diego_1(string qName)
{
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(loadedLocation, true);
	sld = GetCharacter(NPC_GenerateCharacter("LadyVeth_DiegoPop", "priest_sp1", "man", "man2", 100, SPAIN, -1, false, "quest"));
	LAi_SetHP(sld, 999.0, 999.0);
	LAi_SetImmortal(sld, true);
	AddItems(sld, "Mineral3", 10);
	sld.name = GetConvertStr("LadyBeth_Pop_Name", "LadyBeth.txt");
	sld.lastname = GetConvertStr("LadyBeth_Pop_lastname", "LadyBeth.txt");
	ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation", "goto", "goto9");
	sld.dialog.filename = "Quest\LadyBeth_dialog.c";
	sld.dialog.currentnode = "LadyBeth_DiegoDeLanda_1";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	pchar.questTemp.ISawDiegoDeLanda = sti(pchar.questTemp.ISawDiegoDeLanda) + 1; // встретил Диего де Ланда
}

void LadyBeth_Barbados_Diego_2(string qName)
{
	LAi_SetActorType(pchar);
	LAi_FadeLong("", "");
	DoQuestFunctionDelay("LadyBeth_Barbados_Diego_3", 0.4);
	DoQuestFunctionDelay("LadyBeth_Barbados_Diego_4", 1.0);
}

void LadyBeth_Barbados_Diego_3(string qName)
{
	sld = CharacterFromID("LadyVeth_DiegoPop");
	sld.lifeday = 0;
	ChangeCharacterAddressGroup(sld, "none", "", "");
}

void LadyBeth_Barbados_Diego_4(string qName)
{
	LAi_SetPlayerType(pchar);
	chrDisableReloadToLocation = false;
	if (sti(pchar.questTemp.ISawDiegoDeLanda) == 2)
	{
		SetQuestHeader("SixCaptains");
		AddQuestRecord("SixCaptains", "1");
		AddQuestUserData("SixCaptains", "sSex", GetSexPhrase("","а")); 
		CloseQuestHeader("SixCaptains");
	}
}

//=======================================================
bool LadyBeth_QuestComplete(string sQuestName, string qname)
{

	ref sld;
	int i, n; 
	
	bool condition = true;
	
	/*if (sQuestName == "LadyBeth_BossEtap_2")	
	{
		// Босс убегает для восстановления
		sld = CharacterFromID("LadyBeth_Blackwood");
		LAi_SetActorType(sld);
		LAi_ActorRunToLocator(sld, "quest", "boss", "LadyBeth_BossEtap_3", -1);
	}
	else if (sQuestName == "LadyBeth_BossEtap_3")	
	{
		sld = CharacterFromID("LadyBeth_Blackwood");
		LAi_SetCurHPMax(sld);
		LAi_GetCharacterMaxEnergy(sld);
		LAi_SetImmortal(sld, false);
		LAi_SetActorType(sld);
		LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, true, "LadyBeth_BossEtap_4");
	}
	else if (sQuestName == "LadyBeth_BossEtap_4")	
	{
		sld = CharacterFromID("LadyBeth_Blackwood");
		LAi_SetImmortal(sld, false);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "LadyBeth_Enemy");
		
		LAi_group_SetRelation("LadyBeth_Enemy", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("LadyBeth_Enemy", LAI_GROUP_PLAYER, false);
		LAi_group_SetCheckFunction("LadyBeth_Enemy", "LadyBeth_PobedaInJungles");
	}*/
	/*if (sQuestName == "LadyBeth_IronWill")
	{
		for (i=1; i<=5; i++)
		{
			sld = CharacterFromID("LadyBeth_EnemyGolovorez_"+i);
			if (LAi_GetCharacterHP(sld) >= 1 && LAi_GetCharacterHP(sld) <= 50)
			{
				LAi_SetImmortal(sld, false);
				LAi_RemoveCheckMinHP(sld); 
				LAi_SetCurHP(sld, 100.0);
			}
		}
		pchar.questTemp.LadyBeth_MoraleEnemy = sti(pchar.questTemp.LadyBeth_MoraleEnemy) + 1;
		if (sti(pchar.questTemp.LadyBeth_MoraleEnemy) >= 3)
		{
			DoQuestFunctionDelay("LadyBeth_MoraleEnemy", 1.0);
		}
	}*/
	else if (sQuestName == "LadyBeth_VistrelSnizu")
	{
		sld = CharacterFromID("LadyBeth_Blackwood");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocator(sld, "quest", "boss2", "LadyBeth_VistrelSnizu2", -1);
		LAi_SetImmortal(sld, true);
	}
	else if (sQuestName == "LadyBeth_VistrelSnizu2")
	{
		sld = CharacterFromID("LadyBeth_Blackwood");
		LAi_SetActorType(sld);
		LAi_ActorSetGroundSitMode(sld);
		LAi_SetCurHPMax(sld);
	}
	else
	{
		condition = false;
	}
	
	return condition;
}

// Предметы для сокровищ
void LadyBeth_Treasure(int iTier, int iBonus, ref item)
{
    /*
    if(FindRealItem("mushket9", "") == 0)
    {
        DeleteAttribute(PChar, "Items.FirearmStockPart_1");
        DeleteAttribute(PChar, "Items.FirearmStockPart_2");
        DeleteAttribute(PChar, "Items.FirearmStockPart_3");
        DeleteAttribute(&TreasureTiers[0], "QuestSlot.LadyBeth");
        return;
    }
    */
    if(rand(1)) return; // 50% скип
    
    int iStage = sti(items[FindItem("mushket9")].UpgradeStage);
    if(!CheckCharacterItem(pchar, "FirearmStockPart_1") && iStage == 1)
    {
        if(iTier < 3) return;
        item.BoxTreasure.FirearmStockPart_1 = 1;
    }
    else if(!CheckCharacterItem(pchar, "FirearmStockPart_2") && iStage < 3)
    {
        if(iTier < 6) return;
        item.BoxTreasure.FirearmStockPart_2 = 1;
    }
    else if(!CheckCharacterItem(pchar, "FirearmStockPart_3") && iStage < 4)
    {
        if(iTier < 9) return;
        item.BoxTreasure.FirearmStockPart_3 = 1;
        DeleteAttribute(&TreasureTiers[0], "QuestSlot.LadyBeth"); // Положили последнюю часть, больше не генерим
    }
}

string GetLadyBethCity()
{
	if(!CharacterIsAlive("LadyBeth_cap")) return "";
	ref chr = characterFromId("LadyBeth_cap");
	if(CheckAttribute(chr, "quest") && CheckAttribute(chr, "City"))
	{
		if(chr.quest == "InCity") return chr.City;
		
	}
	
	return "";
}
