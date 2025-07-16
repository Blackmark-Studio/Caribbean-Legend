///////////////////////////////////////////////////////////////////////////////////////////////////////
///Jason-----------------------------------Португалец начало-----------------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////////////////
void Portugal_BeginOver(string qName)//не пришли
{
	sld = characterFromId("Avendel");
	sld.lifeday = 0;
	pchar.questTemp.Portugal = "end";
}

void Portugal_DoctorOver(string qName)//не нашли дом
{
	sld = characterFromId("Avendel");
	sld.lifeday = 0;
	pchar.quest.Portugal_Guard.over = "yes";
	AddQuestRecord("Portugal", "2");
	CloseQuestHeader("Portugal");
	pchar.questTemp.Portugal = "end";
	QuestPointerDelLoc("marigo_town", "reload", "houseF1");
}

void CreatePortugalGuard(string qName)//охрана Португальца
{
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
	QuestPointerDelLoc("marigo_town", "reload", "houseF1");
	LAi_group_Delete("EnemyFight");
	for (int i=1; i <=3; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("PortugalGuard_"+i, "citiz_"+(i+42), "man", "man", sti(pchar.rank), PIRATE, -1, true, "quest"));
		FantomMakeCoolFighter(sld, sti(pchar.rank), 20, 20, "blade_10", "pistol1", "bullet", 0);
		LAi_SetHP(sld, 60.0, 60.0);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		sld.dialog.FileName = "Quest\Portugal_dialog.c";
		sld.dialog.currentnode = "Portugal_guard";
		sld.greeting = "town_pirate";		
		GetCharacterPos(pchar, &locx, &locy, &locz);
        ChangeCharacterAddressGroup(sld, "Marigo_houseF1", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
		LAi_SetWarriorType(sld);
		if (i == 1)
		{
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		}
	}
}

void CreatePortugalDoctor(string qName)//создаем доктора и Португальца
{
	chrDisableReloadToLocation = true;
	//Барт Португалец
	sld = GetCharacter(NPC_GenerateCharacter("Portugal", "Port_A", "man", "man", 35, PIRATE, -1, true, "quest"));
	FantomMakeCoolFighter(sld, 35, 65, 65, "", "", "bullet", 150);
	sld.name = StringFromKey("Portugal_1");
	sld.lastname = StringFromKey("Portugal_2");
	sld.dialog.FileName = "Quest\Portugal_dialog.c";
	sld.dialog.currentnode = "Bart_lay";
	LAi_SetLayType(sld);
	ChangeCharacterAddressGroup(sld, "Marigo_RoomHouseF1", "barmen", "bar1");
	//доктор
	sld = GetCharacter(NPC_GenerateCharacter("PortugalDoctor", "VanShtal", "man", "man", 10, HOLLAND, -1, true, "quest"));
	sld.dialog.FileName = "Quest\Portugal_dialog.c";
	sld.dialog.currentnode = "Portugal_doctor";
	sld.greeting = "shtile";
	sld.name = StringFromKey("Portugal_3");
	sld.lastname = StringFromKey("Portugal_4");
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, "Marigo_RoomHouseF1", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_SetActorType(sld);
	LAi_ActorDialogDelay(sld, pchar, "", 2.5);
}

void AvendelInHouse(string qName)//Португалец в доме
{
	sld = characterFromId("Avendel");
	sld.dialog.currentnode = "Avendel_house";
	ChangeCharacterAddressGroup(sld, "Marigo_HouseF1", "goto", "goto2");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void PortugalClovesOver(string qName)//просрочили забрать Португальца из дома - зачищаем всех
{
	sld = characterFromId("Avendel");
	sld.lifeday = 0;
	sld = characterFromId("PortugalDoctor");
	sld.lifeday = 0;
	sld = characterFromId("Portugal");
	sld.lifeday = 0;
	AddQuestRecord("Portugal", "4");
	CloseQuestHeader("Portugal");
	pchar.questTemp.Portugal = "end";
	DelLandQuestMark(characterFromId("Marigo_trader"));
	QuestPointerDelLoc("marigo_town", "reload", "houseF1");
	QuestPointerDelLoc("marigo_town", "reload", "reload6_back");
}

void Portugal_ToAntiguaOver(string qName)//Португалец помер
{
	DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
	sld = characterFromId("Portugal");
	LAi_KillCharacter(sld);
	if (pchar.questTemp.Portugal == "TreatmentStart" || pchar.questTemp.Portugal == "TreatmentCurrent" || pchar.questTemp.Portugal == "TreatmentComplete") pchar.questTemp.Portugal.Die = "true";
	else
	{
		pchar.quest.Remove_Avendel.win_condition.l1 = "Location_Type";
		pchar.quest.Remove_Avendel.win_condition.l1.location_type = "town";
		pchar.quest.Remove_Avendel.function = "RemoveAvendelnDoc";
		AddQuestRecord("Portugal", "6");
		CloseQuestHeader("Portugal");
		pchar.questTemp.Portugal = "end";
	}
	sld = characterFromId("Jino");
	ChangeCharacterAddressGroup(sld, "SentJons_HouseF3_Room", "goto", "goto1"); // patch-9
}

void RemoveAvendelnDoc(string qName)//зачищаем Авендела и доктора
{
	chrDisableReloadToLocation = true;
	bDisableFastReload = true;
	sld = characterFromId("PortugalDoctor");
	RemovePassenger(Pchar, sld);
	sld.lifeday = 0;
	sld = characterFromId("Avendel");
	sld.dialog.currentnode = "Avendel_goodbye";
	RemovePassenger(Pchar, sld);
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void Portugal_DoctorPodhodit(string qName)//доктор подходит
{
	chrDisableReloadToLocation = true;
	pchar.questTemp.Portugal = "Portugal_wait";
	int iShipType = GetCharacterShipType(pchar);
	ref rShip = GetRealShip(iShipType);
	//sTemp = "My_" + rShip.CabinType;
	sld = characterFromId("PortugalDoctor");
	sld.dialog.currentnode = "Portugal_doctor_9";
	ChangeCharacterAddressGroup(sld, "SentJons_HouseF3", "reload", "reload1");
	LAi_SetStayType(sld);
	AddLandQuestMark(sld, "questmarkmain");
}

void Portugal_TreatmentOver(string qName)//лечение окончено
{
	pchar.questTemp.Portugal = "TreatmentFinish";
}

void AvendelSpeach(string qName)//подходилка-говорилка Авендела
{
	chrDisableReloadToLocation = true;
	sld = characterFromId("Avendel");
	if (pchar.questTemp.Portugal == "ToMartinique") sld.dialog.currentnode = "Avendel_Room_2";
	else
	{
		if (pchar.questTemp.Portugal == "MartiniqueGovernor") sld.dialog.currentnode = "Avendel_seapatrol";
		else
		{
			if (pchar.questTemp.Portugal == "MartiniqueGovernorEnd") sld.dialog.currentnode = "Avendel_seapatrol_5";
			else
			{
				if (pchar.questTemp.Portugal == "LeFransuaAfterFight") sld.dialog.currentnode = "Avendel_LeFransua";
			else sld.dialog.currentnode = "Avendel_Room";
		}
	}
	}
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void PortugalOnStreet(string qName)//охотники в Сент-Джонсе
{
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретим драться
	for (int i=1; i <=5; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("PortugalHunter_"+i, "citiz_"+(i+42), "man", "man", sti(pchar.rank)+1, PIRATE, -1, true, "quest"));
		FantomMakeCoolFighter(sld, sti(pchar.rank)+1, 30, 30, "blade_10", "pistol1", "bullet", 0);
		LAi_SetHP(sld, 70.0, 70.0);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		sld.dialog.FileName = "Quest\Portugal_dialog.c";
		sld.dialog.currentnode = "Portugal_hunter";
		sld.greeting = "town_pirate";		
		GetCharacterPos(pchar, &locx, &locy, &locz);
        ChangeCharacterAddressGroup(sld, "SentJons_town", "goto", LAi_FindNearestLocator("goto", locx, locy, locz));
		LAi_SetWarriorType(sld);
		if (i == 1)
		{
		sld.name = StringFromKey("Portugal_5");
		sld.lastname = StringFromKey("Portugal_6");
		}
		if (i != 1) LAi_CharacterDisableDialog(sld);
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
}

void PortugalSeaHunter(string qName)//атака охотников в порту
{
	sld = characterFromId("Portugal");
	LAi_SetGroundSitType(sld);
	ChangeCharacterAddressGroup(sld, "My_Deck", "goto", "goto6");//Португальца в трюм
	Group_DeleteGroup("Hunter_Attack");
	Group_FindOrCreateGroup("Hunter_Attack");
	SelectLevelWarShipParameter();//автолевеллинг
	sld = GetCharacter(NPC_GenerateCharacter("Porthunter", "mercen_"+(rand(27)+1), "man", "man", sti(PChar.rank)+1, ENGLAND, 5, true, "hunter"));
	FantomMakeSmallSailor(sld, iGlobalTemp, "", iTotalTemp, 70+rand(5), 60+rand(5), 60+rand(5), 50+rand(5), 55+rand(5));
	FantomMakeCoolFighter(sld, sti(PChar.rank)+1, 30, 30, sTotalTemp, "pistol3", "grapeshot", 50);
	sld.AlwaysEnemy = true;
	sld.Coastal_Captain = true;
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.Ship.Mode = "pirate";
	Group_AddCharacter("Hunter_Attack", "Porthunter");
	Group_SetGroupCommander("Hunter_Attack", "Porthunter");
	Group_SetTaskAttack("Hunter_Attack", PLAYER_GROUP);
	Group_SetPursuitGroup("Hunter_Attack", PLAYER_GROUP);
	Group_SetAddress("Hunter_Attack", "Antigua", "", "");
	Group_LockTask("Hunter_Attack");
	int i = FindColony("Fortfrance");
	colonies[i].DontSetShipInPort = true;  //не ставить корабли в порту Мартиники
}

void PortugalOnMartinique(string qName)//прибыли на Мартинику - доктор
{
	sld = characterFromId("PortugalDoctor");
	sld.dialog.currentnode = "Portugal_doctor_12";
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void PortugalInTavernRoom(string qName)//доктор и Португалец в комнате таверны
{
	sld = characterFromId("PortugalDoctor");
	sld.dialog.currentnode = "Portugal_doctor_14";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void CreateFrancePatrol(string qName)//посыльный в городе - приглашение к губернатору
{
	chrDisableReloadToLocation = true;//закрыть локацию
	sld = GetCharacter(NPC_GenerateCharacter("PortugalPatrol_"+i, "off_fra_1", "man", "man", 25, FRANCE, 0, true, "quest"));
	FantomMakeCoolFighter(sld, 25, 70, 70, "blade_15", "pistol6", "bullet", 50);
	sld.dialog.FileName = "Quest\Portugal_dialog.c";
	sld.dialog.currentnode = "Portugal_patrol";
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, "Fortfrance_town", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void PortugalSeapatrolGo(string qName)//типо патрулируем Мартинику - просто крутим время
{
	DoQuestFunctionDelay("PortugalSeapatrolEnd", 60.0);//минуту поплаваем
	Island_SetReloadEnableGlobal("Martinique", false);//на остров нельзя			
	bQuestDisableMapEnter = true;//запрет выхода на глобу
}

void PortugalSeapatrolEnd(string qName)//отдежурили
{
	AddQuestRecord("Portugal", "11");
	Island_SetReloadEnableGlobal("Martinique", true); //снять запрет
	LocatorReloadEnterDisable("Fortfrance_town", "reload4_back", false);//открыть таверну
	SetLaunchFrameFormParam(StringFromKey("Portugal_7", NewStr()), "", 0, 4);
	LaunchFrameForm();
	WaitDate("", 0, 0, 2, 4, 10); //крутим время
	RecalculateJumpTable();
	sld = characterFromId("FortFrance_Mayor");
	sld.dialog.currentnode = "Portugal_9";
	pchar.questTemp.Portugal = "MartiniqueGovernorEnd";//новый флаг
	sld = characterFromId("Avendel");
	sld.greeting = "avendel_2";
	sld = characterFromId("Portugal");
	sld.greeting = "portugal";
	SetFunctionTimerCondition("MartiniqueGovernorOver", 0, 0, 5, false);//5 дней на получение награды
	pchar.quest.Portugal_SeapatrolAvendel1.win_condition.l1 = "location";
	pchar.quest.Portugal_SeapatrolAvendel1.win_condition.l1.location = "Fortfrance_town";
	pchar.quest.Portugal_SeapatrolAvendel1.function = "AvendelSpeach";
	int i = FindColony("Fortfrance");
	colonies[i].DontSetShipInPort = false;//ставить корабли в порту Мартиники
		}

void MartiniqueGovernorOver(string qName)//вертаем обычную ноду губеру Мартиники
{
	sld = characterFromId("FortFrance_Mayor");
	sld.dialog.currentnode = "First time";
}

void MartiniquePortugalOver(string qName)//не нашли Португальца за 2 дня - конец квеста
{
	sld = characterFromId("Avendel");
	sld.lifeday = 0;
	RemovePassenger(Pchar, sld);
	AddQuestRecord("Portugal", "16");
	CloseQuestHeader("Portugal");
	pchar.questTemp.Portugal = "end";
}

void Portugal_enterPirates()//пиратусы в таверне Ле Франсуа
{
	LAi_group_Delete("EnemyFight");
	for (int i=1; i<=3; i++)
{
		sld = GetCharacter(NPC_GenerateCharacter("LeFransuaPirate_"+i, "citiz_"+(i+43), "man", "man", sti(pchar.rank)+2, PIRATE, -1, true, "quest"));
		FantomMakeCoolFighter(sld, sti(pchar.rank)+2, 40, 40, "blade_10", "pistol3", "bullet", 0);
		LAi_SetHP(sld, 100.0, 100.0);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		sld.dialog.FileName = "Quest\Portugal_dialog.c";
		sld.dialog.currentnode = "LeFransua_pirate";
		sld.greeting = "town_pirate";		
		GetCharacterPos(pchar, &locx, &locy, &locz);
        ChangeCharacterAddressGroup(sld, "LeFransua_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
		LAi_SetWarriorType(sld);
		if (i == 1)
		{
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		}
	}
}

void CreateFranzGarke(string qName)//создаем Франца Гарке в комнате, туда же - Португальца
{
	LAi_group_Delete("EnemyFight");
	chrDisableReloadToLocation = true;
	sld = characterFromId("Portugal");
	ChangeCharacterAddressGroup(sld, "LeFransua_tavern_upstairs", "goto", "goto2");//ставим Португальца
	sld = GetCharacter(NPC_GenerateCharacter("FranzGarke", "Garke", "man", "man", 30, PIRATE, -1, true, "quest"));
	FantomMakeCoolFighter(sld, 25+MOD_SKILL_ENEMY_RATE, 90, 90, "blade_17", "pistol6", "bullet", 150);
	SetCharacterPerk(sld, "SwordplayProfessional");
	sld.name = StringFromKey("Portugal_8");
	sld.lastname = StringFromKey("Portugal_9");
	GiveItem2Character(sld, "cirass2");
	EquipCharacterbyItem(sld, "cirass2");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	sld.dialog.FileName = "Quest\Portugal_dialog.c";
	sld.dialog.currentnode = "FranzGarke";
	sld.greeting = "town_pirate";
	ChangeCharacterAddressGroup(sld, "LeFransua_tavern_upstairs", "goto", "goto1");
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, pchar, "", -1);
}

void CreateVaskezsPirates(string qName)//драка на улицах Ле Франсуа
{
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретим драться
	for (int i=1; i <=9; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("VaskezsPirate_"+i, "citiz_"+(i+40), "man", "man", sti(pchar.rank)+2, PIRATE, -1, true, "quest"));
		FantomMakeCoolFighter(sld, sti(pchar.rank)+2, 40, 40, "blade_10", "pistol1", "bullet", 0);
		LAi_SetHP(sld, 100.0, 100.0);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		sld.dialog.FileName = "Quest\Portugal_dialog.c";
		sld.dialog.currentnode = "Vaskezs_pirate";
		sld.greeting = "town_pirate";		
		GetCharacterPos(pchar, &locx, &locy, &locz);
        
		LAi_SetWarriorType(sld);
		if (i == 1)
		{
			//ChangeCharacterAddressGroup(sld, "LeFransua_town", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			ChangeCharacterAddressGroup(sld, "LeFransua_town", "goto", "goto11");
		}
		else
		{
			LAi_CharacterDisableDialog(sld);
			ChangeCharacterAddressGroup(sld, "LeFransua_town", "goto", "goto"+i);
		}
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
}

void CreateVaskezsFrigate(string qName)//атака фрегата Васкеза // patch-9
{
	Island_SetReloadEnableGlobal("Martinique", false);
	sld = characterFromId("Portugal");
	LAi_SetStayType(sld);
	LAi_CharacterDisableDialog(sld);//запрет диалога
	RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
	RemoveCharacterEquip(sld, GUN_ITEM_TYPE);
	ChangeCharacterAddressGroup(sld, "My_Deck", "goto", "goto6");//Португальца в трюм
	Group_FindOrCreateGroup("VaskezFrigate");
	sld = GetCharacter(NPC_GenerateCharacter("Vaskezs_helper", "mercen_"+(rand(27)+1), "man", "man", 25+MOD_SKILL_ENEMY_RATE, PIRATE, -1, true, "quest"));
	
	int iClass = sti(RealShips[sti(pchar.ship.type)].Class);
	if(iClass < 2) iClass = 2;
	if(iClass > 4) iClass = 4;
	
	FantomMakeCoolSailor(sld, GetRandomShipType(GetClassFlag(iClass), FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_RAIDER, FLAG_SHIP_NATION_ANY), StringFromKey("Portugal_10"), -1, 90, 90, 90);
	FantomMakeCoolFighter(sld, 25+MOD_SKILL_ENEMY_RATE, 70, 70, "blade_10", "pistol3", "grapeshot", 100);
	sld.AlwaysEnemy = true;
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.WatchFort = true;//видеть форты
	Group_AddCharacter("VaskezFrigate", "Vaskezs_helper");
	Group_SetGroupCommander("VaskezFrigate", "Vaskezs_helper");
	Group_SetTaskAttack("VaskezFrigate", PLAYER_GROUP);
	Group_SetAddress("VaskezFrigate", "Martinique", "quest_ships", "quest_ship_6");
	Group_LockTask("VaskezFrigate");
	pchar.quest.VaskezFrigate_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.VaskezFrigate_AfterBattle.win_condition.l1.group = "VaskezFrigate";
	pchar.quest.VaskezFrigate_AfterBattle.function = "VaskezFrigate_AfterBattle";
	pchar.quest.VaskezFrigate_DieHard.win_condition.l1 = "MapEnter";
	pchar.quest.VaskezFrigate_DieHard.function = "VaskezFrigate_DieHard";
}

void VaskezFrigate_AfterBattle(string qName)//победили
{
	DoQuestCheckDelay("sea_victory", 1.5);
	pchar.quest.VaskezFrigate_DieHard.over = "yes";
	Group_DeleteGroup("VaskezFrigate");
	Island_SetReloadEnableGlobal("Martinique", true);
	AddComplexSeaExpToScill(250, 150, 150, 150, 150, 150, 0);
	ChangeOfficersLoyality("good_all", 1);
	pchar.questTemp.Portugal.Condition2 = "true";
	bQuestDisableMapEnter = true;
	AddQuestRecord("Portugal", "18");
	sld = characterFromId("Portugal");
	sld.dialog.currentnode = "Portugal_treasure";
	LAi_CharacterEnableDialog(sld);//разрешение диалога
}

void VaskezFrigate_DieHard(string qName)//сбежали
{
	pchar.quest.VaskezFrigate_AfterBattle.over = "yes";
	Group_DeleteGroup("VaskezFrigate");
	Island_SetReloadEnableGlobal("Martinique", true);
	ChangeOfficersLoyality("bad_all", 1);
	AddQuestRecord("Portugal", "19");
	sld = characterFromId("Portugal");
	sld.dialog.currentnode = "Portugal_treasure";
	LAi_CharacterEnableDialog(sld);//разрешение диалога
}

void RemovePortugal(string qName)//Португальца - вон
{
	sld = characterFromId("Portugal");
	sld.lifeday = 0;
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "", "", "none", "", "", "", 1.0);
	CloseQuestHeader("Portugal");
	pchar.questTemp.Portugal = "end";
	log_info(StringFromKey("Portugal_11"));
}

void CreateHollIndBattle(string qName)//массовая драка в джунглях с индейцами и голландцами
{
	chrDisableReloadToLocation = true;
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE;
	int iScl = 10 + 2*sti(pchar.rank);
	//ставим голландцев
	for (i=1; i<=10; i++)
	{
		if (i >= 1 && i <= 3)
		{
			sld = GetCharacter(NPC_GenerateCharacter("PortHol_"+i, "mush_hol_"+i, "man", "mushketer", iRank, HOLLAND, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "cartridge", iScl*2);
			sld.MusketerDistance = 0;
			ChangeCharacterAddressGroup(sld, "Terks_Jungle_01", "rld", "aloc"+(4+i));
		}
		else
		{
			if (i == 4)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PortHol_"+i, "off_hol_"+i, "man", "man", iRank, HOLLAND, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, iRank+7, iScl+5, iScl+5, "blade_20", "pistol1", "bullet", iScl*2);
				ChangeCharacterAddressGroup(sld, "Terks_Jungle_01", "rld", "aloc8");
				LAi_SetImmortal(sld, true);
			}
			else
			{
				sld = GetCharacter(NPC_GenerateCharacter("PortHol_"+i, "sold_hol_"+(5+i), "man", "man", iRank, HOLLAND, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_19", "pistol1", "bullet", iScl*2);
				ChangeCharacterAddressGroup(sld, "Terks_Jungle_01", "rld", "aloc9");
			}
		}
		LAi_SetWarriorType(sld);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		LAi_group_Register("PortHoll");
		LAi_group_MoveCharacter(sld, "PortHoll");
	}
	//ставим индеев
	for (i=1; i<=12; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("PortInd_"+i, "canib_"+(rand(5)+1), "man", "man", iRank, PIRATE, -1, false, "soldier"));
		FantomMakeCoolFighter(sld, iRank+5, iScl+5, iScl+5, "blade_02", "", "", iScl*2);
		ChangeCharacterAddressGroup(sld, "Terks_Jungle_01", "goto", "goto4");
		LAi_SetWarriorType(sld);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		LAi_group_Register("PortInd");
		LAi_group_MoveCharacter(sld, "PortInd");
	}
	//стравим все группы
	LAi_group_SetRelation("PortInd", "PortHoll", LAI_GROUP_ENEMY);
	LAi_group_FightGroups("PortInd", "PortHoll", true);
	LAi_group_SetRelation("PortHoll", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("PortHoll", LAI_GROUP_PLAYER, true);
	LAi_group_SetRelation("PortInd", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("PortInd", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("PortInd", "CheckPortHoll");
}

void DigPortugalGems(string qName)//могу копать, могу не копать :)
{
	DoQuestCheckDelay("TalkSelf_Quest", 0.1);
}

void CreatePortugalHollShip(string qName)//голландский фрегат // patch-9
{
	Island_SetReloadEnableGlobal("Terks", false);
	Group_FindOrCreateGroup("PortHolFrigate");
	sld = GetCharacter(NPC_GenerateCharacter("PortHolCap", "off_hol_5", "man", "man", sti(PChar.rank)+MOD_SKILL_ENEMY_RATE, HOLLAND, -1, true, "quest"));
	FantomMakeCoolSailor(sld, SHIP_FRIGATE, "", CANNON_TYPE_CANNON_LBS32, 90, 90, 90);
	FantomMakeCoolFighter(sld, sti(PChar.rank)+MOD_SKILL_ENEMY_RATE, 70, 70, "blade_21", "pistol3", "grapeshot", 100);
	sld.AlwaysEnemy = true;
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	Group_AddCharacter("PortHolFrigate", "PortHolCap");
	Group_SetGroupCommander("PortHolFrigate", "PortHolCap");
	Group_SetTaskAttack("PortHolFrigate", PLAYER_GROUP);
	Group_SetPursuitGroup("PortHolFrigate", PLAYER_GROUP);
	Group_SetAddress("PortHolFrigate", "Terks", "", "");
	Group_LockTask("PortHolFrigate");
	pchar.quest.PortHolFrigate_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.PortHolFrigate_AfterBattle.win_condition.l1.group = "PortHolFrigate";
	pchar.quest.PortHolFrigate_AfterBattle.function = "PortHolFrigate_AfterBattle";
	pchar.quest.PortHolFrigate_DieHard.win_condition.l1 = "MapEnter";
	pchar.quest.PortHolFrigate_DieHard.function = "PortHolFrigate_DieHard";
	pchar.quest.Portugal_Terks2.win_condition.l1 = "location";
	pchar.quest.Portugal_Terks2.win_condition.l1.location = "Marigo_tavern";
	pchar.quest.Portugal_Terks2.function = "SetAvendelMarigo";
	SetFunctionTimerCondition("SetAvendelMarigoOver", 0, 0, 30, false);
}

void PortHolFrigate_AfterBattle(string qName)//победили
{
	DoQuestCheckDelay("sea_victory", 1.5);
	pchar.quest.PortHolFrigate_DieHard.over = "yes";
	Group_DeleteGroup("PortHolFrigate");
	Island_SetReloadEnableGlobal("Terks", true);
	AddComplexSeaExpToScill(150, 100, 100, 100, 100, 100, 0);
	ChangeOfficersLoyality("good_all", 1);
	AddQuestRecord("Portugal", "26");
}

void PortHolFrigate_DieHard(string qName)//сбежали
{
	pchar.quest.PortHolFrigate_AfterBattle.over = "yes";
	Group_DeleteGroup("PortHolFrigate");
	Island_SetReloadEnableGlobal("Terks", true);
	ChangeOfficersLoyality("bad_all", 1);
	AddQuestRecord("Portugal", "27");
}

void SetAvendelMarigoOver(string qName)//счищаем Авендела и Португальца
{
	sld = characterFromId("Avendel");
	sld.lifeday = 0;
	sld = characterFromId("Portugal");
	sld.lifeday = 0;
	AddQuestRecord("Portugal", "28");
	CloseQuestHeader("Portugal");
	pchar.questTemp.Portugal = "end";
}

void SetAvendelMarigo(string qName)//Авендел в таверне Мариго
{
	sld = characterFromId("Avendel");
	sld.dialog.currentnode = "Avendel_Marigo";
	LAi_SetSitType(sld);
	FreeSitLocator("Marigo_tavern", "sit_front1");
	ChangeCharacterAddressGroup(sld, "Marigo_tavern", "sit", "sit_front1");
}

void InMarigoResidence()//в резиденции Мариго
{
	AddQuestRecord("Portugal", "29");
	//SetFunctionTimerCondition("InMarigoResidenceOver", 0, 0, 5, false);
	sld = GetCharacter(NPC_GenerateCharacter("PortServant" , "shipowner_10", "man", "man", 10, HOLLAND, 5, true, "quest"));
	FantomMakeCoolFighter(sld, 10, 10, 10, "", "", "", 10);
	sld.dialog.FileName = "Quest\Portugal_dialog.c";
	sld.dialog.currentnode = "Servant";
	sld.greeting = "worker";
	LAi_SetOwnerType(sld);
	ChangeCharacterAddressGroup(sld, "Marigo_TownhallRoom", "goto", "goto1");
}

/*void InMarigoResidenceOver(string qName)//счищаем Португальца
{
	sld = characterFromId("Portugal");
	sld.lifeday = 0;
	if (pchar.questTemp.Portugal == "SeekPortVillemstad" || pchar.questTemp.Portugal == "PortugalInPrison") AddQuestRecord("Portugal", "33");
	else AddQuestRecord("Portugal", "30");
	CloseQuestHeader("Portugal");
	pchar.questTemp.Portugal = "end";
}*/

void CreateErnandoVaskez()//появился Васкез
{
	sld = GetCharacter(NPC_GenerateCharacter("Vaskez", "Vasces", "man", "man", 35, PIRATE, -1, true, "soldier"));
	FantomMakeCoolFighter(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+15, 100, 100, "blade_10", "pistol6", "bullet", 200);
	sld.name = StringFromKey("Portugal_12");
	sld.lastname = StringFromKey("Portugal_13");
	sld.dialog.FileName = "Quest\Portugal_dialog.c";
	sld.dialog.currentnode = "Vaskez";
	sld.greeting = "vaskez";
	SetCharacterPerk(sld, "SwordplayProfessional");
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, "Villemstad_prison", "reload", "reload9");
	LAi_ActorDialogNow(sld, pchar, "", -1);
}
//<-- Португалец конец

//=================================================================
//======================кейсы из quests_reaction===================
//=================================================================
bool Portugal_QuestComplete(string sQuestName, string qname)
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////		
//Jason-------------------------------------------------Португалец---------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////

	ref sld;
	
	bool condition = true;
	
	if (sQuestName == "PortugalOutResidence")	
	{
		pchar.questTemp.Portugal = "Findcloves";
		LocatorReloadEnterDisable("Marigo_town", "reload1_back", false);
		LocatorReloadEnterDisable("Marigo_town", "reload2_back", false);
		LocatorReloadEnterDisable("Marigo_town", "reload_gate", false);
		sld = characterFromId("Avendel");
		sld.dialog.currentnode = "Avendel_house_2";
		ChangeCharacterAddressGroup(sld, "Marigo_town", "goto", "goto15");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	else if (sQuestName == "Portugal_PerenesliVDom1")	
	{
		DoQuestCheckDelay("Portugal_PerenesliVDom2", 1.5);
	}
	else if (sQuestName == "Portugal_PerenesliVDom2")	
	{
		WaitDate("", 0, 0, 0, 1, 0);
		SetLaunchFrameFormParam(StringFromKey("Portugal_14", NewStr()), "Portugal_PerenesliVDom3", 0, 4.0);
		LaunchFrameForm();
	}
	else if (sQuestName == "Portugal_PerenesliVDom3")	
	{
		chrDisableReloadToLocation = false;
		AddQuestRecord("Portugal", "7");
	}
	else if (sQuestName == "Portugal_JinoNorm")	
	{
		sld = characterFromId("Jino");
		LAi_SetOwnerType(sld);
	}
	else if (sQuestName == "PortugalHunterDied")
	{
		chrDisableReloadToLocation = false;
		DoQuestCheckDelay("hide_weapon", 1.5);
		sld = characterFromId("Avendel");
		sld.dialog.currentnode = "Avendel_street";
		GetCharacterPos(pchar, &locx, &locy, &locz);
		ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		sld = characterFromId("Portugal");
		if (LAi_GetCharacterHP(sld) > 0) LAi_SetImmortal(sld, true);
		AddComplexSelfExpToScill(50, 50, 50, 50);
	}
	else if (sQuestName == "LeFransuaAfterFight")
	{
		DoQuestCheckDelay("hide_weapon", 1.3);
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
		chrDisableReloadToLocation = false;
		LAi_LocationDisableOfficersGen("LeFransua_tavern", false);//офицеров пускать
		LocatorReloadEnterDisable("LeFransua_tavern", "reload2_back", false);
		pchar.quest.Portugal_Franz.win_condition.l1 = "location";
		pchar.quest.Portugal_Franz.win_condition.l1.location = "LeFransua_tavern_upstairs";
		pchar.quest.Portugal_Franz.function = "CreateFranzGarke";
		AddQuestRecord("Portugal", "14");
	}
	else if (sQuestName == "LeFransua_PortugalTalk")
	{
		DoQuestCheckDelay("hide_weapon", 1.3);
		chrDisableReloadToLocation = false;
		sld = characterFromId("Portugal");
		sld.dialog.currentnode = "Portugal_LFTalk";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 2.5);
	}
	else if (sQuestName == "VaskezsPiratesDied")
	{
		LAi_group_Delete("EnemyFight");
		DoQuestCheckDelay("hide_weapon", 1.3);

		sld = characterFromId("Portugal");
		if (LAi_GetCharacterHP(sld) > 0) 
		{
			LAi_SetImmortal(sld, true);
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			AddQuestRecord("Portugal", "17");
		}
		else AddQuestRecord("Portugal", "36");
		sld = characterFromId("Avendel");
		RemovePassenger(Pchar, sld);
		pchar.questTemp.Portugal = "LeFransuaAfterFight";
		AddComplexSelfExpToScill(100, 100, 100, 100);
		
		DoQuestFunctionDelay("AvendelSpeach", 1.0);
	}
	else if (sQuestName == "Portugal_Final")
	{
		sld = characterFromId("Portugal");
		sld.lifeday = 0;
		ChangeCharacterAddressGroup(sld, "none", "", "");
		AddQuestRecord("Portugal", "22");
		CloseQuestHeader("Portugal");
		pchar.questTemp.Portugal = "end";
	}
	else if (sQuestName == "CheckPortHoll")
	{
		sld = characterFromId("PortHol_4");
		LAi_SetImmortal(sld, false);
		LAi_group_SetCheck("PortHoll", "PortugalTerks_AfterFight");
	}
	else if (sQuestName == "PortugalTerks_AfterFight")
	{
		DoQuestCheckDelay("hide_weapon", 1.3);
		LAi_group_Delete("PortHoll");
		LAi_group_Delete("PortInd");
		pchar.quest.Portugal_Terks1.win_condition.l1 = "locator";
		pchar.quest.Portugal_Terks1.win_condition.l1.location = "Terks_Jungle_01";
		pchar.quest.Portugal_Terks1.win_condition.l1.locator_group = "rld";
		pchar.quest.Portugal_Terks1.win_condition.l1.locator = "aloc11";
		pchar.quest.Portugal_Terks1.function = "DigPortugalGems";
		pchar.questTemp.Portugal = "DigGems";
		AddQuestRecord("Portugal", "24");
		AddComplexSelfExpToScill(150, 150, 150, 150);
	}
	else if (sQuestName == "FindPortugalGems")
	{
		SetLaunchFrameFormParam(StringFromKey("Portugal_15"), "GivePortugalGems", 0, 4);
		LaunchFrameForm();
		WaitDate("", 0, 0, 0, 2, 10); //крутим время
		RecalculateJumpTable();
	}
	else if (sQuestName == "GivePortugalGems")
	{
		chrDisableReloadToLocation = false;
		Log_Info(StringFromKey("Portugal_16"));
		PlaySound("interface\important_item.wav");
		TakeNItems(pchar, "jewelry2", 510+hrand(30));
		TakeNItems(pchar, "jewelry3", 530+hrand(50));
		AddQuestRecord("Portugal", "25");
		pchar.quest.Portugal_Terks.win_condition.l1 = "location";
		pchar.quest.Portugal_Terks.win_condition.l1.location = "Terks";
		pchar.quest.Portugal_Terks.function = "CreatePortugalHollShip";
		pchar.questTemp.Portugal = "GiveGems"; // 021012
		AddCharacterExpToSkill(pchar, "Fortune", 500);//везение
	}
	else if (sQuestName == "VaskezFight")
	{
		Pchar.chr_ai.hp = stf(Pchar.chr_ai.hp)/2;
		sld = characterFromId("Vaskez");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "VaskezDied");
		LAi_SetFightMode(pchar, true);
	}
	else if (sQuestName == "VaskezDied")
	{
		//LAi_group_Delete("EnemyFight");
		DoQuestCheckDelay("hide_weapon", 1.3);
		sld = characterFromId("Portugal");
		sld.dialog.currentnode = "Portugal_free_2";
	}
	else if (sQuestName == "PortugalFree")
	{
		sld = characterFromId("Portugal");
		sld.dialog.currentnode = "Portugal_free_5";
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, "Villemstad_Exittown", "rld", "loc16");
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	else
	{
		condition = false;
	}
	
	return condition;
}