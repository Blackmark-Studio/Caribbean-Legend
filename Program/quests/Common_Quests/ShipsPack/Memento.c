void Memento_init()
{
	pchar.questTemp.Memento = true;
	log_testinfo("Инициализация БРИГА");
	pchar.questTemp.Memento.stage = 1; // стадии меняем при выходе на карту
	pchar.questTemp.Memento.colony = Memento_findColony(sti(pchar.questTemp.Memento.stage)); // колонии меняем при заходе в порт
    ref sld, itm;
	
	// характеристики запишем после ТЗ
	sld = GetCharacter(NPC_GenerateCharacter("Memento_cap", "mercen_19", "man", "man", 30, PIRATE, -1, false, "governor"));
	FantomMakeCoolSailor(sld, SHIP_MEMENTO, StringFromKey("Memento_1"), CANNON_TYPE_CANNON_LBS18, 105, 105, 105);
	FantomMakeCoolFighter(sld, 30, 70, 70, "blade_SP_3low", "pistol4", "bullet", 200);
	// SetSailsColor(sld, 8);
	sld.ship.Crew.Morale = 100;
	ChangeCrewExp(sld, "Sailors",   100);
	ChangeCrewExp(sld, "Cannoners", 100);
	ChangeCrewExp(sld, "Soldiers",  100); 
	LAi_SetHP(sld, 470.0, 470.0);
	SetAllPerksToChar(sld, true);
	sld.name = StringFromKey("Memento_2");
	sld.lastname = StringFromKey("Memento_3");
	RealShips[sti(sld.Ship.Type)].ship.upgrades.hull  = "q";
	RealShips[sti(sld.Ship.Type)].EmblemedSails.normalTex = "ships/parus_black0.tga";
	RealShips[sti(sld.Ship.Type)].ShipSails.Gerald_Name = "pir6.tga.tx";
	sld.DontRansackCaptain = true; //квестовые не сдаются
	SetSPECIAL(sld, 10, 10, 10, 10, 10, 10, 10);
	SetSelfSkill(sld, 100, 100, 100, 100, 100);
	SetShipSkill(sld, 75, 75, 75, 75, 75, 75, 75, 75, 75);
	AddBonusEnergyToCharacter(sld, 50000);
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	sld.GenQuest.CrewMementoMode = true;
	sld.DontHitInStorm = true;
	sld.AlwaysFriend = true;
	sld.viper = true;
	//sld.MultiFighter = 2.5;
	//Предметы
	//AddItems(sld, "harpoon", 20);
	//AddItems(sld, "potion4", 5);
	//GiveItem2Character(sld, "cirass1");
	//EquipCharacterByItem(sld, "cirass1");
	GiveItem2Character(sld, "indian_4");
	GiveItem2Character(sld, "indian_5");
	GiveItem2Character(sld, "indian_6");
	//Товары в трюме
	SetCharacterGoods(sld, GOOD_POWDER, 3000);
	SetCharacterGoods(sld, GOOD_BALLS, 1000);
	SetCharacterGoods(sld, GOOD_GRAPES, 1000);
	SetCharacterGoods(sld, GOOD_KNIPPELS, 1000);
	SetCharacterGoods(sld, GOOD_SANDAL, 50);
	SetCharacterGoods(sld, GOOD_OIL, 50);
	SetCharacterGoods(sld, GOOD_SHIPSILK, 50);
	SetCharacterGoods(sld, GOOD_ROPES, 50);
	
	string sGroup = "Sea_"+sld.id
	Group_FindOrCreateGroup(sGroup);
	Group_SetType(sGroup,"trade");
    Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
    Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	// SetRandGeraldSail(sld, sti(sld.Nation));
	
	sld.quest = "InMap";
	sld.city = Memento_findColony(sti(pchar.questTemp.Memento.stage));
	sld.quest.targetCity = Memento_findColony(sti(pchar.questTemp.Memento.stage)+1);
	sld.mapEnc.type = "trade";
	sld.mapEnc.worldMapShip = "memento";
	sld.mapEnc.Name = StringFromKey("Memento_1");
	Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, 30);
	
	PChar.quest.Memento_Book.win_condition.l1 = "item";
	PChar.quest.Memento_Book.win_condition.l1.item = "Memento_Book";
	PChar.quest.Memento_Book.function = "Memento_Book";
}

string Memento_findColony(int stage)
{
	switch(stage)
	{
		case 1: return "Shore36"; break;
		case 2: return "PuertoPrincipe"; break;
		case 3: return "LaVega"; break;
		case 4: return "Shoreship1"; break;
		case 5: return "LeFransua"; break;
	}
}

void Memento_ToCity(string sChar)
{
	if(!GetDLCenabled(DLC_APPID_6)) return;
	if(!CharacterIsAlive(sChar)) {Log_testinfo("Капитан БРИГА умер"); return;}
	pchar.questTemp.Memento.colony = Memento_findColony(sti(pchar.questTemp.Memento.stage)+1);
	Log_testinfo("капитан брига сошёл в порту "+ pchar.questTemp.Memento.colony);
	
	DeleteQuestCheck("Memento_MapRelease");
	
	//таймер через сколько опять выйти на карту
	PChar.quest.Memento_toMap.win_condition.l1            = "Timer";
    PChar.quest.Memento_toMap.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
    PChar.quest.Memento_toMap.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
    PChar.quest.Memento_toMap.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
    PChar.quest.Memento_toMap.function					   = "Memento_toMap";
	
	ref sld = &characters[GetCharacterIndex(sChar)];
	sld.quest = "InCity"; //флаг кэпа ходит по городу или острову
	sld.City = sld.quest.targetCity; //аттрибут текущего города пропишем
}

void Memento_ToMap(string sQuest)
{
	if(!CharacterIsAlive("Memento_cap")) {Log_testinfo("Капитан БРИГА умер"); return;}
	ref sld = characterFromId("Memento_cap");
	sld.quest = "InMap";
	
	pchar.questTemp.Memento.stage = sti(pchar.questTemp.Memento.stage) + 1;
	if(sti(pchar.questTemp.Memento.stage) >= 5)
	{		
		pchar.questTemp.Memento.stage = 0;
		sld.city = Memento_findColony(5);
	}
	else
	{
		sld.city = Memento_findColony(sti(pchar.questTemp.Memento.stage));
	}
	
	if(CheckAttribute(pchar, "questTemp.BM_StartQuest") && !CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
	{
		if(Memento_findColony(sti(pchar.questTemp.Memento.stage)+1) == "Shore36")
		{
			pchar.questTemp.Memento.stage = sti(pchar.questTemp.Memento.stage) + 1;
			Log_testInfo("Капитан БРИГА ПРОПУСТИЛ ЯМАЙКУ и направился в колонию: "+Memento_findColony(sti(pchar.questTemp.Memento.stage)+1));
		}
	}
	if(CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "islatesoro")
	{
		if(Memento_findColony(sti(pchar.questTemp.Memento.stage)+1) == "Shoreship1")
		{
			pchar.questTemp.Memento.stage = sti(pchar.questTemp.Memento.stage) + 1;
			Log_testInfo("Капитан БРИГА ПРОПУСТИЛ ИСЛА-ТЕСОРО и направился в колонию: "+Memento_findColony(sti(pchar.questTemp.Memento.stage)+1));
		}
	}
	
	sld.quest.targetCity = Memento_findColony(sti(pchar.questTemp.Memento.stage)+1);
	Log_testInfo("Капитан БРИГА направился в колонию: "+sld.quest.targetCity + " из колонии : "+sld.city);
	sld.mapEnc.type = "trade";
	sld.mapEnc.worldMapShip = "memento";
	sld.mapEnc.Name = StringFromKey("Memento_1");
	Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, 30);
}

void CheckMemento()
{
	if(CharacterIsAlive("Memento_cap"))
	{
		ref sld = CharacterFromID("Memento_cap")
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
				if(CheckAttribute(enc, "quest.chrID") && enc.quest.chrID == "Memento_cap")
				{
					bAtMap = true;
				}
			}
			// на карте нет, но и атрибут "в порту" отсутствует
			if(!bAtMap)
			{
				Memento_ToCity("Memento_cap");
			}
			else
			{
				if(CheckQuestCondition("Memento_MapRelease"))
				{
					Map_ReleaseQuestEncounter("Memento_cap");
				}
				else
				{
					SetFunctionTimerCondition("Memento_MapRelease", 0, 0, 31, false);
				}
			}
		}
	}
}

void Memento_MapRelease(string qName)
{
	
}

void Memento_PlayerAttack()
{
	bQuestDisableMapEnter = true;
	sld = characterFromId("Memento_cap");
	sld.PlayerAttack = true;
	DeleteAttribute(sld, "AlwaysFriend");
	sld.AlwaysEnemy = true;
	pchar.questTemp.Memento.AttackFromMap = true;
	SetCharacterRelationBoth(sti(GetCharacterIndex("Memento_cap")), GetMainCharacterIndex(), RELATION_ENEMY);
	Group_SetTaskAttack("Sea_Memento_cap", PLAYER_GROUP);
	Group_LockTask("Sea_Memento_cap");
	UpdateRelations();
	RefreshBattleInterface();
	
	pchar.quest.Memento_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.Memento_AfterBattle.win_condition.l1.group = "Sea_Memento_cap";
	pchar.quest.Memento_AfterBattle.function = "Memento_AfterBattle";
	
	if(CheckAttribute(pchar, "questTemp.Memento_InfoPU"))
	{
		NewGameTip(StringFromKey("Memento_6"));
	}
}

void Memento_AfterBattle(string qName)
{
	bQuestDisableMapEnter = false;
	DeleteAttribute(pchar, "questTemp.Memento.AttackFromMap");
}

void Memento_Book(string qName)
{
	AddQuestRecordInfo("Memento_Book", "1");
}

//===============Абордаж Мементо, в каюте==============
void Memento_MortimerGrimDead_Alonso(string qName)
{
	DoQuestCheckDelay("hide_weapon", 1.2);
	
	sld = GetCharacter(NPC_GenerateCharacter("Memento_Alonso", "Alonso", "man", "man", sti(pchar.rank), pchar.nation, 0, false, "soldier"));
	sld.name 	= StringFromKey("SharlieTrial_29");
	sld.lastname = StringFromKey("SharlieTrial_30");
	sld.Dialog.Filename = "Quest\ShipsPack\Memento_dialog.c";
	sld.dialog.currentnode = "Memento_MortimerGrimDead_Alonso_1";
	GiveItem2Character(sld, "blade_10");
	EquipCharacterByItem(sld, "blade_10");
	ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 1.2, 0);
	
	// Активируется этап: Дичь
	pchar.questTemp.Memento_Dich = true;
	SetTimerFunction("Memento_Dich", 0, 0, 1);
}

void Memento_MortimerGrimDead_Alonso_2()
{
	AddCrewMorale(Pchar, -10);
	sld = characterFromId("Memento_Alonso");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", 3);
}

//===============Мементо, Этап Дичь==============
void Memento_Dich(string qName)
{
	if (sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_MEMENTO)
	{
		if (IsEntity(worldMap))
		{
			if (CheckAttribute(pchar, "questTemp.Memento_Dich_EtapThree"))
			{
				Memento_Dich_Start_EtapThree();
				return;
			}
			if (CheckAttribute(pchar, "questTemp.Memento_Dich_EtapTwo"))
			{
				Memento_Dich_Start_EtapTwo();
				return;
			}
			Memento_Dich_Start_EtapOne();
		}
		else
		{
			PChar.quest.Memento_Dich_EtapOne_Paluba_Wait.win_condition.l1 = "MapEnter";
			PChar.quest.Memento_Dich_EtapOne_Paluba_Wait.function = "Memento_Dich";
		}
	}
}

void Memento_Dich_Start_EtapOne() // Этап первый
{
	SetFunctionLocationCondition("Memento_Dich_EtapOne_Paluba_2", "My_Campus", false);
	aref arOldMapPos;
	makearef(arOldMapPos, worldMap.old);
	WdmPrepareMapForAbordage(arOldMapPos);
	LAi_LocationFightDisable(&Locations[FindLocation("My_Campus")], true);
	DoReloadFromWorldMapToLocation("My_Campus", "goto", "goto1");
}

void Memento_Dich_EtapOne_Paluba_2(string qName)
{
	QuestToSeaLogin_Launch();
	pchar.GenQuest.CabinLock = true;
	bQuestDisableMapEnter = true;
			
	DoQuestFunctionDelay("Memento_Dich_EtapOne_Paluba_3", 5.0);
}

void Memento_Dich_EtapOne_Paluba_3(string qName)
{
	DeleteAttribute(pchar, "GenQuest.CabinLock");
	pchar.GenQuest.DontSetCabinOfficer = true;
	chrDisableReloadToLocation = true;
	Sea_CabinStartNow();
	
	DoQuestFunctionDelay("Memento_Dich_EtapOne_Paluba_4", 3.0);
}

void Memento_Dich_EtapOne_Paluba_4(string qName)
{
	sld = GetCharacter(NPC_GenerateCharacter("Memento_Alonso", "Alonso", "man", "man", sti(pchar.rank), pchar.nation, 0, false, "soldier"));
	sld.name 	= StringFromKey("SharlieTrial_29");
	sld.lastname = StringFromKey("SharlieTrial_30");
	sld.Dialog.Filename = "Quest\ShipsPack\Memento_dialog.c";
	sld.dialog.currentnode = "Memento_Dich_EtapOne_Alonso_1";
	GiveItem2Character(sld, "blade_10");
	EquipCharacterByItem(sld, "blade_10");
	ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void Memento_Dich_EtapOne_End()
{
	SetCrewQuantity(pchar, GetCrewQuantity(pchar) - 1);
	AddCrewMorale(Pchar, -10);
	SetTimerFunction("Memento_Dich", 0, 0, 3);
	pchar.questTemp.Memento_Dich_EtapTwo = true;
	
	DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
	bQuestDisableMapEnter = false;
	
	sld = characterFromId("Memento_Alonso");
	LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", 3);
}

void Memento_Dich_Start_EtapTwo() // Этап второй
{
	SetFunctionLocationCondition("Memento_Dich_EtapTwo_Paluba_2", "My_Campus", false);
	aref arOldMapPos;
	makearef(arOldMapPos, worldMap.old);
	WdmPrepareMapForAbordage(arOldMapPos);
	LAi_LocationFightDisable(&Locations[FindLocation("My_Campus")], true);
	DoReloadFromWorldMapToLocation("My_Campus", "quest", "quest2");
}

void Memento_Dich_EtapTwo_Paluba_2(string qName)
{
	CreateSea(EXECUTE, REALIZE);
	CreateWeather(EXECUTE,REALIZE);
	chrDisableReloadToLocation = true;
	SetMusic("classic_music_sea_night");
	//StartQuestMovie(true, false, true);
	//locCameraFromToPos(-3.07, 8.30, 19.91, true, -0.20, 6.59, 17.00);
	//TeleportCharacterToPosAy(pchar, -2.28, 6.82, 18.68, 3.00);
	//LAi_SetStayType(pchar);
	DoQuestFunctionDelay("Memento_Dich_EtapTwo_Paluba_3", 0.5);
}

void Memento_Dich_EtapTwo_Paluba_3(string qName)
{
	sld = GetCharacter(NPC_GenerateCharacter("Memento_Alonso", "Alonso", "man", "man", sti(pchar.rank), pchar.nation, 0, false, "soldier"));
	sld.name 	= StringFromKey("SharlieTrial_29");
	sld.lastname = StringFromKey("SharlieTrial_30");
	GiveItem2Character(sld, "blade_10");
	EquipCharacterByItem(sld, "blade_10");
	ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
	//LAi_ActorGoToLocator(sld, "rld", "aloc2", "Memento_Dich_EtapTwo_Paluba_4", -1);
	sld.Dialog.Filename = "Quest\ShipsPack\Memento_dialog.c";
	sld.dialog.currentnode = "Memento_Dich_EtapOne_Alonso_1";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void Memento_Dich_EtapTwo_End()
{
	if(UnloadLocation(loadedLocation) == true)
	{
		//EndQuestMovie();
		chrDisableReloadToLocation = false;
		DeleteSea();
		DeleteWeather();
		LAi_SetPlayerType(pchar);
		SetCrewQuantity(pchar, GetCrewQuantity(pchar) - 13);
		AddCrewMorale(Pchar, -20);
		Land_MapLoad();
		pchar.location = "";
		SetTimerFunction("Memento_Dich", 0, 0, 3);
		pchar.questTemp.Memento_Dich_EtapThree = true;
	}
}

void Memento_Dich_Start_EtapThree() // Этап третий
{
	SetFunctionLocationCondition("Memento_Dich_EtapThree_Paluba_2", "My_Campus", false);
	if (CheckAttribute(pchar,"equip."+HAT_ITEM_TYPE)) RemoveCharacterEquip(pchar, HAT_ITEM_TYPE);
	if (CheckAttribute(pchar,"equip."+CIRASS_ITEM_TYPE)) RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
	aref arOldMapPos;
	makearef(arOldMapPos, worldMap.old);
	WdmPrepareMapForAbordage(arOldMapPos);
	LAi_LocationFightDisable(&Locations[FindLocation("My_Campus")], true);
	LAi_FadeToBlackStartInstantly();
	DoReloadFromWorldMapToLocation("My_Campus", "sit", "sit6");
}

void Memento_Dich_EtapThree_Paluba_2(string qName)
{
	CreateSea(EXECUTE, REALIZE);
	CreateWeather(EXECUTE,REALIZE);
	bDisableCharacterMenu = true;
	SetMusic("classic_music_sea_night");
	StartQuestMovie(true, false, true);
	locCameraFromToPos(-2.30, 8.65, 18.66, true, -2.49, 5.67, 17.20);
	//TeleportCharacterToPosAy(pchar, -2.28, 6.82, 18.68, 3.00);
	LAi_SetActorType(pchar);
	LAi_ActorAnimation(pchar, "tablesleep_2", "1", -1);
	
	sld = GetCharacter(NPC_GenerateCharacter("Memento_Alonso", "Alonso", "man", "man", sti(pchar.rank), pchar.nation, 0, false, "soldier"));
	sld.name 	= StringFromKey("SharlieTrial_29");
	sld.lastname = StringFromKey("SharlieTrial_30");
	GiveItem2Character(sld, "blade_10");
	EquipCharacterByItem(sld, "blade_10");
	ChangeCharacterAddressGroup(sld, PChar.location, "quest", "quest3");
	sld.Dialog.Filename = "Quest\ShipsPack\Memento_dialog.c";
	sld.dialog.currentnode = "Memento_Dich_EtapThree_AlonsoPrizrak_1";
	CharacterTurnByChr(sld, pchar);
	
	DoQuestFunctionDelay("Memento_Dich_EtapThree_Paluba_2_1", 2.0);
	DoQuestFunctionDelay("Memento_Dich_EtapThree_Paluba_3", 6.5);
}

void Memento_Dich_EtapThree_Paluba_2_1(string qName)
{
	LAi_FadeToBlackEnd();
}

void Memento_Dich_EtapThree_Paluba_3(string qName)
{
	LAi_ActorAnimation(pchar, "tablesleep_3", "1", -1);
	
	DoQuestFunctionDelay("Memento_Dich_EtapThree_Paluba_4", 3.5);
}

void Memento_Dich_EtapThree_Paluba_4(string qName)
{
	LAi_SetStayType(pchar);
	sld = characterFromId("Memento_Alonso");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 0, 0);
	locCameraFromToPos(-2.45, 8.31, 18.23, true, -0.05, 6.60, 19.57);
}

void Memento_Dich_EtapThree_Paluba_4_1()
{
	EndQuestMovie();
	LAi_SetPlayerType(pchar);
	ChangeCharacterAddressGroup(pchar, PChar.location, "rld", "loc2");
	//locCameraSleep(false);
	chrDisableReloadToLocation = true;
	locCameraFollowEx(false);
	InterfaceStates.Buttons.Save.enable = false;
	SetFunctionLocationCondition("Memento_Dich_EtapThree_Paluba_5", "My_Deck_Medium", false);
	
	sld = &Locations[FindLocation("My_Deck_Medium")];
	sld.locators_radius.box.private1 = 0.0;
	sld.locators_radius.box.private2 = 0.0;
	sld.locators_radius.box.private3 = 0.0;
	sld.locators_radius.box.private4 = 0.0;
	// меняем модель квестовой каюты
	sld = &Locations[FindLocation("Quest_Cabin_Medium")];
	//убираем сначала лишнее
	DeleteAttribute(&locations[FindLocation("Quest_Cabin_Medium")], "models");
	//Models
	sld.filespath.models = "locations\decks\inside_cabin_4"; // каюта брига/"Мементо"
	//Always
	sld.models.always.main = "inside_cabin_4";
	sld.models.always.parts = "inside_cabin_4_parts";
	sld.models.always.partsQ = "inside_cabin_4_partsMemento"; // декор "Мементо"
	sld.models.always.locators = "inside_cabin_4_locators";
	sld.models.always.camcollider = "inside_cabin_4_camcollider";
	sld.models.always.windows = "inside_cabin_4_windows";
	sld.models.always.windows.tech = "LocationWindows";
	sld.models.always.windows.level = 65539;
	sld.models.always.rays = "inside_cabin_4_rays"; // лучи
	sld.models.always.rays.uvslide.v0 = 0.08;
	sld.models.always.rays.uvslide.v1 = 0.0;
	sld.models.always.rays.tech = "LocationWaterFall";
	sld.models.always.rays.level = 99950;
	//Day
	sld.models.day.charactersPatch = "inside_cabin_4_patch";
	sld.models.day.fonar = "inside_cabin_4_fd";
	//Night
	sld.models.night.charactersPatch = "inside_cabin_4_patch";
	sld.models.night.fonar = "inside_cabin_4_fn";
	
	sld.locators_radius.box.private1 = 0.0;
	sld.locators_radius.box.private2 = 0.0;
	sld.locators_radius.box.private3 = 0.0;
	sld.locators_radius.item.item1 = 0.0;
	sld.locators_radius.item.item2 = 0.0;
	
	sld = characterFromId("Memento_Alonso");
	LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "OpenTheDoors", 4);
}

void Memento_Dich_EtapThree_Paluba_5(string qName)
{
	chrDisableReloadToLocation = true;
	for (i=1; i<=6; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Memento_Skelet_"+i, "skel"+(rand(3)+1), "skeleton", "skeleton", sti(pchar.rank), PIRATE, -1, true, "soldier"));
		ChangeCharacterAddressGroup(sld, pchar.location, "rld", "loc"+i);
		LAi_SetLayType(sld);
		LAi_CharacterEnableDialog(sld);
		sld.CantLoot = true;
		LAi_CharacterDisableDialog(sld);
		sld.BlockSnore = true;
	}
	sld = GetCharacter(NPC_GenerateCharacter("Memento_Alonso", "Alonso", "man", "man", sti(pchar.rank), pchar.nation, 0, false, "soldier"));
	sld.name 	= StringFromKey("SharlieTrial_29");
	sld.lastname = StringFromKey("SharlieTrial_30");
	GiveItem2Character(sld, "blade_10");
	EquipCharacterByItem(sld, "blade_10");
	sld.Dialog.Filename = "Quest\ShipsPack\Memento_dialog.c";
	sld.dialog.currentnode = "Memento_Alonso_phantom_11";
	ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload_cabin");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	sld.CantLoot = true;
}

void Memento_Dich_EtapThree_Paluba_6()
{
	pchar.questTemp.Memento_BitvaSkeletMusic = true;
	LAi_SetCheckMinHP(pchar, 1, true, "");
	for (i=1; i<=6; i++)
	{
		sld = CharacterFromID("Memento_Skelet_"+i);
		LAi_SetActorType(sld);
		LAi_ActorSetGroundSitMode(sld);
		LAi_ActorAnimation(sld, "ground_standup", "Memento_Dich_EtapThree_Paluba_7", 7);
	}
}

void Memento_Dich_EtapThree_Paluba_8(string qName)
{
	LAi_LocationFightDisable(loadedLocation, true);
	DoQuestCheckDelay("hide_weapon", 1.2);
	SetFunctionLocatorCondition("Memento_Dich_EtapThree_Paluba_9", "My_Deck_Medium", "reload", "reload_cabin", false)
	QuestPointerToLoc("My_Deck_Medium", "reload", "reload_cabin");
}

void Memento_Dich_EtapThree_Paluba_9(string qName)
{
	QuestPointerDelLoc("My_Deck_Medium", "reload", "reload_cabin");
	DoFunctionReloadToLocation("Quest_Cabin_Medium", "reload", "reload1", "Memento_Dich_EtapThree_Paluba_10");
}

void Memento_Dich_EtapThree_Paluba_10()
{
	sld = GetCharacter(NPC_GenerateCharacter("Memento_Cap_phantom", "mercen_19", "man", "man", sti(pchar.rank), PIRATE, -1, true, "soldier"));
	FantomMakeCoolFighter(sld, 30, 70, 70, "blade_SP_3low", "pistol4", "bullet", 0);
	sld.name = StringFromKey("Memento_2");
	sld.lastname = StringFromKey("Memento_3");
	sld.Dialog.Filename = "Quest\ShipsPack\Memento_dialog.c";
	sld.dialog.currentnode = "Memento_MortimerGrim_phantom_11";
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, pchar.location, "rld", "aloc0");
	LAi_SetActorType(sld);
	//LAi_ActorDialog(sld, pchar, "", -1, 0);
	LAi_SetActorType(pchar);
	SetActorDialogAny2Pchar(sld.id, "", -1, 0.0);
	//LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 2.0);
	LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 2.0);
	
	
	LAi_SetHP(sld, 300.0, 300.0);
	SetAllPerksToChar(sld, true);
	SetSPECIAL(sld, 10, 10, 10, 10, 10, 10, 10);
	SetSelfSkill(sld, 100, 100, 100, 100, 100);
	AddBonusEnergyToCharacter(sld, 50000);
	LAi_SetCurHPMax(sld);
	sld.viper = true;
}

void Memento_Dich_EtapThree_Paluba_11()
{
	LAi_LocationFightDisable(loadedLocation, false);
	LAi_SetPlayerType(pchar);
	LAi_SetFightMode(pchar, true);
	
	sld = CharacterFromID("Memento_Cap_phantom");
	LAi_SetImmortal(sld, false);
	LAi_SetWarriorType(sld);
    LAi_group_MoveCharacter(sld, "EnemyFight");
	LAi_SetCheckMinHP(sld, 1, true, "Memento_Dich_EtapThree_Paluba_12");
	sld.lifeday = 0;
}

void Memento_Dich_EtapThree_Paluba_13()
{
	sld = &Locations[FindLocation("My_Deck_Medium")];
	sld.locators_radius.box.private1 = 1.0;
	sld.locators_radius.box.private2 = 1.0;
	sld.locators_radius.box.private3 = 1.0;
	sld.locators_radius.box.private4 = 1.0;
	sld = &Locations[FindLocation("Quest_Cabin_Medium")];
	sld.locators_radius.box.private1 = 1.0;
	sld.locators_radius.box.private2 = 1.0;
	sld.locators_radius.box.private3 = 1.0;
	sld.locators_radius.item.item1 = 1.0;
	sld.locators_radius.item.item2 = 1.0;
	DoFunctionReloadToLocation("Deck_Near_Ship_Memento", "goto", "goto2", "Memento_Dich_EtapThree_Paluba_14");
}

void Memento_Dich_EtapThree_Paluba_14()
{
	//CreateSea(EXECUTE, REALIZE);
	//CreateWeather(EXECUTE,REALIZE);
	DeleteAttribute(pchar, "questTemp.Memento_BitvaSkeletMusic");
	SetCurrentTime(8, 00);
	CreateWeatherEnvironment();
	StartQuestMovie(true, false, true);
	LAi_SetActorType(pchar);
	LAi_ActorSetLayMode(pchar);
	DoQuestFunctionDelay("Memento_Dich_EtapThree_Paluba_14_1", 0.1);
	DoQuestFunctionDelay("Memento_Dich_EtapThree_Paluba_14_2", 2.0);
	LAi_FadeToBlackStartInstantly();
	pchar.questTemp.NoFast = true;
}

void Memento_Dich_EtapThree_Paluba_14_1(string qName)
{
	SetMusic("music_alcove_1");
}

void Memento_Dich_EtapThree_Paluba_14_2(string qName)
{
	LAi_FadeToBlackEnd();
	locCameraFlyToPositionLookToPoint(-54.43, 1.45, -36.94, -33.53, 2.08, -27.39, 0.42, 5.49, 2.76, -1, 11200/GetDeltaTime());
	Pchar.FuncCameraFly = "Memento_Dich_EtapThree_Paluba_15";
}

void Memento_Dich_EtapThree_Paluba_15()
{
	//locCameraFlyToPositionLookToPoint(1.60, 2.55, 20.12, -0.91, 4.09, 19.01, -0.05, 3.59, 17.23, -1, 10000/GetDeltaTime());
	locCameraFlyToPositionLookToPoint(2.04, 2.35, 19.95, -1.29, 3.92, 18.58, -0.05, 3.73, 17.23, -1, 10000/GetDeltaTime());
	Pchar.FuncCameraFly = "Memento_Dich_EtapThree_Paluba_16";
}

void Memento_Dich_EtapThree_Paluba_16()
{
	locCameraFlyToPositionLookToPoint(5.04, 3.03, -7.78, 2.81, 4.32, -22.05, 2.07, 3.67, -12.75, -1, 10500/GetDeltaTime());
	Pchar.FuncCameraFly = "Memento_Dich_EtapThree_Paluba_17";
}

void Memento_Dich_EtapThree_Paluba_17()
{
	//locCameraFlyToPositionLookToPoint(0.22, 5.85, -23.17, -0.00, 6.17, -18.13, 0.01, 6.13, -16.23, -1, 6000/GetDeltaTime());
	locCameraFlyToPositionLookToPoint(-0.01, 5.85, -23.17, -0.00, 6.17, -18.13, 0.01, 6.13, -16.23, -1, 6000/GetDeltaTime());
	Pchar.FuncCameraFly = "Memento_Dich_EtapThree_Paluba_18";
	LAi_SetActorType(pchar);
	LAi_ActorAnimation(pchar, "idle_1", "", 12.0);
	ChangeCharacterAddressGroup(pchar, PChar.location, "quest", "quest3");
	//LAi_ActorGoToLocator(pchar, "quest", "quest3", "Memento_Dich_EtapThree_Paluba_19", -1);
}

void Memento_Dich_EtapThree_Paluba_18()
{
	locCameraSleep(true);
	DoQuestFunctionDelay("Memento_Dich_EtapThree_Paluba_21", 3.0);
}

void Memento_Dich_EtapThree_Paluba_21(string qName)
{
	//EndQuestMovie();
	RealShips[sti(pchar.Ship.Type)].ship.upgrades.hull  = "1";	// с корабля исчезает шляпа
	DeleteAttribute(pchar, "questTemp.NoFast");
	DoFunctionReloadToLocation("My_Campus", "sit", "sit6", "Memento_Dich_EtapThree_Paluba_22");
}

void Memento_Dich_EtapThree_Paluba_22()
{
	//StartQuestMovie(true, false, true);
	EndBattleLandInterface();
	GiveItem2Character(PChar, "hat9");
	EquipCharacterByItem(PChar, "hat9");
	locCameraFromToPos(-2.30, 8.65, 18.66, true, -2.49, 5.67, 17.20);
	LAi_SetActorType(pchar);
	LAi_ActorAnimation(pchar, "tablesleep_2", "1", -1);
	
	sld = GetCharacter(NPC_GenerateCharacter("Memento_Alonso", "Alonso", "man", "man", sti(pchar.rank), pchar.nation, 0, false, "soldier"));
	sld.name 	= StringFromKey("SharlieTrial_29");
	sld.lastname = StringFromKey("SharlieTrial_30");
	GiveItem2Character(sld, "blade_10");
	EquipCharacterByItem(sld, "blade_10");
	ChangeCharacterAddressGroup(sld, PChar.location, "quest", "quest3");
	sld.Dialog.Filename = "Quest\ShipsPack\Memento_dialog.c";
	sld.dialog.currentnode = "Memento_Dich_EtapThree_Alonso_1";
	CharacterTurnByChr(sld, pchar);
	
	DoQuestFunctionDelay("Memento_Dich_EtapThree_Paluba_3", 4.5);
}

void Memento_Dich_EtapThree_End()
{
	EndQuestMovie();
	DeleteSea();
	DeleteWeather();
	bDisableCharacterMenu = false;
	chrDisableReloadToLocation = false;
	LAi_SetPlayerType(pchar);
	InterfaceStates.Buttons.Save.enable = true;
	LAi_RemoveCheckMinHP(pchar);
	LAi_SetImmortal(pchar, false);
	pchar.questTemp.Memento_Dich_EtapDominika = true;
	Memento_Dominica_SpawnObereg();
	QuestToSeaLogin_Launch();
}

//===============Доминика==============

void Memento_Dominica_SpawnObereg()
{
	//pchar.questTemp.Memento_Dominica = true; // НЕ ЗАБЫТЬ вставить в нужный момент
	//DeleteAttribute(pchar, "questTemp.Memento_Dominica");
	// в бухте Скотс Хед острова Доминика прячем Череп-оберег в сундуке
	pchar.GenQuestBox.Shore27.box1.items.talisman19 = 1;
	SetFunctionLocatorCondition("Memento_Dominica_DeLanda", "Shore27", "box", "box1", false)
	// Если вышел на глобалку, не забрав череп
	//PChar.quest.Memento_Dominica_Proval.win_condition.l1 = "MapEnter";
	//PChar.quest.Memento_Dominica_Proval.function = "Memento_Dominica_Proval";
}

void Memento_Dominica_DeLanda(string qName)
{
	if (CharacterIsAlive("DiegoDeLanda"))
	{
		chrDisableReloadToLocation = true;
		LAi_LocationFightDisable(loadedLocation, true);
		sld = CharacterFromID("DiegoDeLanda");
		ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto14");
		LAi_SetStayType(sld);
		LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
		AddLandQuestMark(sld, "questmarkmain");
		pchar.questTemp.ISawDiegoDeLanda = sti(pchar.questTemp.ISawDiegoDeLanda) + 1; // встретил Диего де Ланда
		pchar.questTemp.DiegoDeLanda_Memento = true;
	}
	Achievment_Set("ach_CL_155");
	if (sti(pchar.rank) <= 13) Achievment_Set("ach_CL_156");
}

//===============Высылаем шлюпку на Мементо==============
void Memento_OnUpdeck()
{
	if (!CheckAttribute(pchar, "questTemp.Memento_OnUpdeck"))
	{
		Log_TestInfo("Логинем нужных персонажей");
		pchar.questTemp.Memento_OnUpdeck = true;
		// Капитан
		sld = GetCharacter(NPC_GenerateCharacter("Memento_Cap_clone", "mercen_19", "man", "man", 30, PIRATE, -1, false, "governor"));
		FantomMakeCoolFighter(sld, 30, 70, 70, "blade_SP_3low", "pistol4", "bullet", 0);
		sld.name = StringFromKey("Memento_2");
		sld.lastname = StringFromKey("Memento_3");
		sld.Dialog.Filename = "Quest\ShipsPack\Memento_dialog.c";
		sld.dialog.currentnode = "Memento_MortimerGrim_1";
		FantomMakeCoolFighter(sld, 30, 70, 70, "blade_05", "pistol4", "bullet", 200);
		sld.SpyglassWithSkull = true;
		ChangeCharacterAddressGroup(sld, "Deck_Near_Ship", "quest", "quest1");
		LAi_SetStayType(sld);
		// Матросы
		sld = GetCharacter(NPC_GenerateCharacter("Memento_Sailor_1", "citiz_33", "man", "man", 5, PIRATE, -1, true, "pirate"));
		sld.name = StringFromKey("Memento_5");
		sld.lastname = "";
		sld.Dialog.Filename = "Quest\ShipsPack\Memento_dialog.c";
		sld.dialog.currentnode = "Memento_Sailor_1";
		ChangeCharacterAddressGroup(sld, "Deck_Near_Ship", "goto", "goto1");
		LAi_SetCitizenType(sld);
		
		sld = GetCharacter(NPC_GenerateCharacter("Memento_Sailor_2", "citiz_43", "man", "man", 5, PIRATE, -1, true, "pirate"));
		sld.name = StringFromKey("Memento_5");
		sld.lastname = "";
		sld.Dialog.Filename = "Quest\ShipsPack\Memento_dialog.c";
		sld.dialog.currentnode = "Memento_Sailor_2";
		ChangeCharacterAddressGroup(sld, "Deck_Near_Ship", "goto", "goto2");
		LAi_SetCitizenType(sld);
		
		sld = GetCharacter(NPC_GenerateCharacter("Memento_Sailor_3", "rivados_2", "man", "man", 5, PIRATE, -1, true, "pirate"));
		sld.name = StringFromKey("Memento_5");
		sld.lastname = "";
		sld.Dialog.Filename = "Quest\ShipsPack\Memento_dialog.c";
		sld.dialog.currentnode = "Memento_Sailor_3";
		ChangeCharacterAddressGroup(sld, "Deck_Near_Ship", "goto", "goto4");
		LAi_SetCitizenType(sld);
		
		sld = GetCharacter(NPC_GenerateCharacter("Memento_Sailor_4", "sold_spa_3", "man", "man", 5, PIRATE, -1, true, "soldier"));
		sld.name = StringFromKey("Memento_5");
		sld.lastname = "";
		sld.Dialog.Filename = "Quest\ShipsPack\Memento_dialog.c";
		sld.dialog.currentnode = "Memento_Sailor_4";
		ChangeCharacterAddressGroup(sld, "Deck_Near_Ship", "goto", "goto6");
		LAi_SetCitizenType(sld);
		
		/*sld = GetCharacter(NPC_GenerateCharacter("Memento_Sailor_5", "prizon_7", "man", "man_B", 5, PIRATE, -1, true, "pirate"));
		sld.Dialog.Filename = "Quest\ShipsPack\Memento_dialog.c";
		sld.dialog.currentnode = "Memento_Sailor_5";
		ChangeCharacterAddressGroup(sld, "Deck_Near_Ship", "goto", "goto7");
		LAi_SetCitizenType(sld);*/
		
		sld = GetCharacter(NPC_GenerateCharacter("Memento_Sailor_6", "citiz_12", "man", "man", 5, PIRATE, -1, false, "pirate"));
		sld.name = StringFromKey("Memento_5");
		sld.lastname = "";
		sld.Unpushable = "";
		ChangeCharacterAddressGroup(sld, "Deck_Near_Ship", "quest", "quest2");
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "tutorial_4", "", -1.0);
	}
	else
	{
		sld = CharacterFromID("Memento_Cap_clone");
		ChangeCharacterAddressGroup(sld, "Deck_Near_Ship", "quest", "quest1");
		
		sld = CharacterFromID("Memento_Sailor_1");
		ChangeCharacterAddressGroup(sld, "Deck_Near_Ship", "goto", "goto1");
		
		sld = CharacterFromID("Memento_Sailor_2");
		ChangeCharacterAddressGroup(sld, "Deck_Near_Ship", "goto", "goto2");
		
		sld = CharacterFromID("Memento_Sailor_3");
		ChangeCharacterAddressGroup(sld, "Deck_Near_Ship", "goto", "goto4");
		
		sld = CharacterFromID("Memento_Sailor_4");
		ChangeCharacterAddressGroup(sld, "Deck_Near_Ship", "goto", "goto6");
		
		// sld = CharacterFromID("Memento_Sailor_5");
		// ChangeCharacterAddressGroup(sld, "Deck_Near_Ship", "goto", "goto7");
		
		sld = CharacterFromID("Memento_Sailor_6");
		ChangeCharacterAddressGroup(sld, "Deck_Near_Ship", "quest", "quest2");
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "tutorial_4", "", -1.0);
	}
	DoQuestFunctionDelay("Memento_BrushProps", 2.0);
}

void Memento_BrushProps(string qName)
{
	sld = CharacterFromID("Memento_Sailor_6");
	SendMessage(sld, "lslssl", MSG_CHARACTER_EX_MSG, "TieItem", FindItem("Brush_Props"), "Brush_Props", "Saber_hand", 1);
}

//=======================================================
bool Memento_QuestComplete(string sQuestName, string qname)
{

	ref sld;
	int i, n; 
	
	bool condition = true;
	
	if (sQuestName == "Memento_MortimerGrimDead")
	{
		if (CharacterIsAlive(&Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)]))
		{
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			LAi_KillCharacter(sld);
		}
		DoQuestFunctionDelay("Memento_MortimerGrimDead_Alonso", 0.5);
	}
	else if (sQuestName == "Memento_Dich_EtapTwo_Paluba_4")
	{
		sld = CharacterFromID("Memento_Alonso");
		sld.Dialog.Filename = "Quest\ShipsPack\Memento_dialog.c";
		sld.dialog.currentnode = "Memento_Dich_EtapOne_Alonso_1";
		//LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
	}
	else if (sQuestName == "Memento_Dich_EtapThree_Paluba_7")
	{
		LAi_LocationFightDisable(loadedLocation, false);
		LAi_SetFightMode(pchar, true);
		sld = CharacterFromID("Memento_Alonso");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		for (i=1; i<=6; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("Memento_Skelet_"+i, "skel"+(rand(3)+1), "skeleton", "skeleton", sti(pchar.rank), PIRATE, -1, true, "soldier"));
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		LAi_group_SetCheckFunction("EnemyFight", "Memento_Dich_EtapThree_Paluba_8");
	}
	else if (sQuestName == "Memento_Dich_EtapThree_Paluba_12")
	{
		LAi_LocationFightDisable(loadedLocation, true);
		DoQuestCheckDelay("hide_weapon", 1.2);
		
		sld = CharacterFromID("Memento_Cap_phantom");
		sld.Dialog.Filename = "Quest\ShipsPack\Memento_dialog.c";
		sld.dialog.currentnode = "Memento_MortimerGrim_phantom_21";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	/*else if (sQuestName == "Memento_Dich_EtapThree_Paluba_19")
	{
		CharacterTurnByLoc(pchar, "quest", "quest3");
	}*/
	else
	{
		condition = false;
	}
	
	return condition;
}
