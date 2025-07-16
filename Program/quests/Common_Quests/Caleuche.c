//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------ Калеуче ---------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Caleuche_StartTotal(string qName) // этот долбоебизм вызван необходимостью типа не начинать новую игру... 
{
	log_testinfo("Квест Калеуче стартовал!!!");
	pchar.questTemp.Caleuche = "Go";
	pchar.questTemp.Caleuche.SeekAmulet = "true"; 
	if (pchar.questTemp.HWIC.Detector == "self_win" || pchar.questTemp.HWIC.Detector == "holl_win") pchar.questTemp.Caleuche.Skul = "true";
	if (GetCharacterIndex("Landlady") != -1)
	{
		sld = characterFromId("Landlady");
		sld.lifeday = 0;
	}
	// находим
	pchar.quest.Caleuche_find_amulet.win_condition.l1 = "item";
	pchar.quest.Caleuche_find_amulet.win_condition.l1.item = "kaleuche_amulet1";
	pchar.quest.Caleuche_find_amulet.function = "Caleuche_FindFirstAmulet";
	// бухта Хаэль Роа
	int n = Findlocation("KhaelRoa_port");
	locations[n].image = "loading\haelroa.tga";
	locations[n].type = "questisland";
	locations[n].locators_radius.reload.reload2 = 2;
	SetItemInLocation("cannabis7", locations[n].id, "qflower1");
	// сюда ставим переменные для храма чавинцев
	// механизм 9 каменных плиток - определим маршрут
	pchar.questTemp.Caleuche.Tile = rand(4);
	switch (sti(pchar.questTemp.Caleuche.Tile))
	{
		case 0: pchar.questTemp.Caleuche.NextTile = "step1"; break;
		case 1: pchar.questTemp.Caleuche.NextTile = "step4"; break;
		case 2: pchar.questTemp.Caleuche.NextTile = "step7"; break;
		case 3: pchar.questTemp.Caleuche.NextTile = "step7"; break;
		case 4: pchar.questTemp.Caleuche.NextTile = "step1"; break;
	}
	// механизм 6 рычагов - определим последовательность
	pchar.questTemp.Caleuche.LeftLevers = rand(4);
	pchar.questTemp.Caleuche.RightLevers = rand(4);
	// ящик Мерримана
	sld = ItemsFromID("MerrimanBook");
	sld.picTexture = "ITEMS_18";
	sld.picIndex = 14;
	sld.model = "BrassBox";
	sld.shown = true; 
	sld.Weight = 8.0;
	sld.startLocation = "Havana_CryptDungeon";
	sld.startLocator = "item"+(rand(4)+1);
}

void Caleuche_FindFirstAmulet(string qName) // нашли первый амулет
{
	DeleteAttribute(pchar, "questTemp.Caleuche.SeekAmulet");
	AddQuestRecord("Caleuche", "1");
	pchar.questTemp.Caleuche = "amulet"; 
	// определяем знатока амулетов из двух смотрителей
	if (rand(1) == 0)
	{
		pchar.questTemp.Caleuche.Amuletmaster = "BasTer_Lightman";
		AddMapQuestMarkShore("Mayak4", false);
		AddLandQuestMark(characterFromId("BasTer_Lightman"), "questmarkmain");
	}
	else
	{
		pchar.questTemp.Caleuche.Amuletmaster = "Santiago_Lightman";
		AddMapQuestMarkShore("Mayak9", false);
		AddLandQuestMark(characterFromId("Santiago_Lightman"), "questmarkmain");
	}
}

void Caleuche_CreateShamane()// создаем Туттуатхапака - шамана
{
	sld = GetCharacter(NPC_GenerateCharacter("Tuttuat", "Tuttuathapack", "man", "man_A1", 30, PIRATE, -1, true, "native"));
	SetFantomParamFromRank(sld, 30, true);
	RemoveAllCharacterItems(sld, true);
	sld.name = StringFromKey("Caleuche_1");
	sld.lastname = StringFromKey("Caleuche_2");
	sld.dialog.FileName = "Quest\Caleuche_dialog.c";
	sld.dialog.currentnode = "Tuttuat";
	sld.greeting = "Tuttuat_1";
	LAi_SetStayTypeNoGroup(sld);
	LAi_SetImmortal(sld, true);
	AddLandQuestMark(sld, "questmarkmain");
	AddMapQuestMarkIsland("Dominica", false);
	ChangeCharacterAddressGroup(sld, "Dominica_shack2", "quest", "quest1");
}

void Caleuche_PrepareGhostship(string qName) // готовим первую атаку Калеуче
{
	for (int i=0;i<MAX_ISLANDS;i++)
	{				
		if (Islands[i].id == "Dominica")
		{
			Islands[i].alwaysStorm = true; 
			Islands[i].storm = true;
		}
	}
	Island_SetReloadEnableGlobal("Dominica", false);//на остров нельзя			
	bQuestDisableMapEnter = true;
	DoQuestFunctionDelay("Caleuche_CreateGhostship", 25.0);
}

void Caleuche_CreateGhostship(string qName)//подгружаем в море Калеуче
{
	int iRank = 20+MOD_SKILL_ENEMY_RATE*2;
	Group_FindOrCreateGroup("Caleuche_Attack");
	sld = GetCharacter(NPC_GenerateCharacter("Caleuche_seacap", "skeletcap", "man", "man", iRank, PIRATE, -1, true, "quest"));
	sld.name = StringFromKey("Caleuche_3");
	sld.lastname = StringFromKey("Caleuche_4");
	sld.dialog.FileName = "Quest\Caleuche_dialog.c";
	sld.dialog.currentnode = "CaleucheCap";
	FantomMakeCoolSailor(sld, SHIP_CURSED_FDM, StringFromKey("Caleuche_5"), CANNON_TYPE_CANNON_LBS32, 90, 90, 90);
	FantomMakeCoolFighter(sld, iRank, 90, 90, "blade_21", "pistol5", "bullet", 200);
	NullCharacterGoods(sld); // удаляем все товары, чтобы не стрелял
	LAi_SetImmortal(sld, true);
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.PoisonResistent = true; // Captain Beltrop, 06.10.2020, нет отравлению ядом Таино
	sld.DontHitInStorm = true; // не ломается в шторм
	sld.Abordage.Enable = false; // запрет абордажа
	SetShipSailsFromFile(sld, "ships/parus_common.tga");
	SetSailsColor(sld, 8);//черный рваный парус
	ref shTo = &RealShips[sti(sld.Ship.Type)];
	shTo.SpeedRate = 30.0;
	shTo.TurnRate = 70.0;
	SetCrewQuantityOverMax(sld, 666);
	Group_AddCharacter("Caleuche_Attack", "Caleuche_seacap");
    Group_SetGroupCommander("Caleuche_Attack", "Caleuche_seacap");
	Group_SetTaskAttack("Caleuche_Attack", PLAYER_GROUP);
    Group_LockTask("Caleuche_Attack");
	SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);
	Sea_LoginGroupCurrentSea("Caleuche_Attack");
	Group_SetTaskAttack("Caleuche_Attack", PLAYER_GROUP);
	Ship_SetTaskAttack(SECONDARY_TASK, sti(sld.index), GetMainCharacterIndex());
	DoQuestCheckDelay("Caleuche_Video", 1.5);
}

void Caleuche_GhostshipBoarding() // калеуче готовит абордаж
{
	PlaySound("interface\" + LanguageGetLanguage() + "\_GTBoard0.wav");
	SetLaunchFrameFormParam("", "", 0, 4);
	SetLaunchFrameFormPic("loading\boarding_b3.tga");
	LaunchFrameForm();
	DoQuestFunctionDelay("Caleuche_GhostshipBoardingGo", 4.0);
}

void Caleuche_GhostshipBoardingGo(string qName) // калеуче идёт на абордаж
{
	for (int i=0;i<MAX_LOCATIONS;i++)
	{				
		if (Locations[i].id == "Deck_Galeon_Ship")
		{
			Locations[i].alwaysStorm = true; 
			Locations[i].storm = true;
		}
	}
	LAi_LocationFightDisable(&Locations[FindLocation("Deck_Galeon_Ship")], false);//разрешить драться
	DoQuestReloadToLocation("Deck_Galeon_Ship", "reload", "reload2", "Caleuche_GhostshipBoardingDeck");
}

void Caleuche_PrepareBeliz(string qName) // готовим локации Белиза
{
	locations[FindLocation("Beliz_ExitTown")].DisableEncounters = true; 
	locations[FindLocation("Beliz_Jungle_01")].DisableEncounters = true; 
	locations[FindLocation("Beliz_CaveEntrance_1")].DisableEncounters = true; 
	locations[FindLocation("Beliz_Cave")].DisableEncounters = true; 
	locations[FindLocation("Beliz_CaveEntrance_2")].DisableEncounters = true; 
	locations[FindLocation("Beliz_Cave_2")].DisableEncounters = true; 
	locations[FindLocation("Beliz_CaveEntrance_3")].DisableEncounters = true; 
	locations[FindLocation("Beliz_jungle_03")].DisableEncounters = true; 
}

void Caleuche_FergusCome(string qName) // Фергус в таверне Белиза
{
	sld = GetCharacter(NPC_GenerateCharacter("Fergus", "mercen_16", "man", "man", 20, ENGLAND, -1, true, "quest"));
	FantomMakeCoolFighter(sld, 20, 50, 50, "blade_12", "pistol1", "bullet", 50);
	sld.name = StringFromKey("Caleuche_6");
	sld.lastname = StringFromKey("Caleuche_7");
	sld.dialog.FileName = "Quest\Caleuche_dialog.c";
	sld.dialog.currentnode = "fergus";
	sld.greeting = "marginal";
	LAi_SetSitType(sld);
	LAi_SetImmortal(sld, true);
	FreeSitLocator("Beliz_tavern", "sit_front1");
	ChangeCharacterAddressGroup(sld, "Beliz_tavern", "sit", "sit3");
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	LAi_SetLoginTime(sld, 18.0, 22.0);
}

void Caleuche_FindLetter(string qName) // 
{
	chrDisableReloadToLocation = false;//открыть локацию
	AddQuestRecord("Caleuche", "12");
	pchar.quest.Caleuche_junglebandos.win_condition.l1 = "location";
	pchar.quest.Caleuche_junglebandos.win_condition.l1.location = "Beliz_Jungle_01";
	pchar.quest.Caleuche_junglebandos.win_condition.l2 = "Hour";
	pchar.quest.Caleuche_junglebandos.win_condition.l2.start.hour = 0.00;
	pchar.quest.Caleuche_junglebandos.win_condition.l2.finish.hour = 3.00;
	pchar.quest.Caleuche_junglebandos.function = "Caleuche_LoginJungleBandos";
}

void Caleuche_LoginJungleBandos(string qName) // бандосы в лесу
{
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
	chrDisableReloadToLocation = true;//закрыть локацию
	int iRank = 20+MOD_SKILL_ENEMY_RATE*2;
	int iScl = 60;
	for (int i=1; i<=6; i++)
	{
		if (i == 1)
		{
			sld = GetCharacter(NPC_GenerateCharacter("Beliz_forestbandos_"+i, "mercen_20", "man", "man", iRank+5, PIRATE, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank+5, iScl, iScl, "blade_13", "pistol4", "bullet", iScl*2+100);
			sld.dialog.FileName = "Quest\Caleuche_dialog.c";
			sld.dialog.currentnode = "Beliz_forestbandos";	
			sld.greeting = "banditos"; 
			LAi_SetCheckMinHP(sld, 10, true, "Caleuche_HeadBandosEscape");
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto3");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		}
		else
		{
			if (i == 2)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Beliz_forestbandos_"+i, "mush_ctz_9", "man", "mushketer", iRank, PIRATE, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "bullet", iScl*2);
				LAi_CharacterDisableDialog(sld);
				ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto3");
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else
			{
				sld = GetCharacter(NPC_GenerateCharacter("Beliz_forestbandos_"+i, "citiz_4"+i, "man", "man", iRank, PIRATE, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_10", "pistol1", "bullet", iScl*2);
				LAi_CharacterDisableDialog(sld);
				ChangeCharacterAddressGroup(sld, pchar.location, "goto", "ass"+(i+2));
				LAi_SetSitType(sld);
			}
		}
		LAi_group_MoveCharacter(sld, "TMP_FRIEND");
	}
	// костер
	ref location = &Locations[FindLocation(pchar.location)];
	ref rItm = ItemsFromID("fire");
	rItm.shown = true;
	rItm.startLocation = location.id;
	rItm.startLocator = "fire";
	location.fire = true;
}

void Caleuche_JungleBandosRobbery(string qName) // 
{
	// купец с конвоем
	LAi_group_Delete("EnemyFight");
	chrDisableReloadToLocation = true;//закрыть локацию
	int iRank = 22+MOD_SKILL_ENEMY_RATE*2;
	int iScl = 65;
	for (int i=1; i<=7; i++)
	{
		if (i == 1)
		{
			sld = GetCharacter(NPC_GenerateCharacter("Beliz_forestmerchant_"+i, "trader_1", "man", "man", iRank, PIRATE, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_13", "pistol6", "bullet", iScl*2);
			ChangeCharacterAddressGroup(sld, pchar.location, "rld", "loc1");
			LAi_SetWarriorType(sld);
		}
		else
		{
			if (i > 1 && i < 4)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Beliz_forestmerchant_"+i, "mush_ctz_"+i, "man", "mushketer", iRank, PIRATE, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, iRank+5, iScl+5, iScl+5, "", "mushket2", "cartridge", iScl*2+70);
				ChangeCharacterAddressGroup(sld, pchar.location, "rld", "loc1");
				LAi_SetWarriorType(sld);
			}
			else
			{
				sld = GetCharacter(NPC_GenerateCharacter("Beliz_forestmerchant_"+i, "citiz_2"+i, "man", "man", iRank, PIRATE, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_11", "pistol5", "bullet", iScl*2+70);
				ChangeCharacterAddressGroup(sld, pchar.location, "rld", "loc1");
				LAi_SetWarriorType(sld);
			}
		}
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	for (i=1; i<=6; i++)
	{
		sld = characterFromId("Beliz_forestbandos_"+i);	
		sld.LSC_clan = true;
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "Caleuche_ForestMerchantDie");
	LAi_SetFightMode(pchar, true);
}

void Caleuche_CaveOpen(string qName) // 
{
	LocatorReloadEnterDisable("Beliz_CaveEntrance_2", "reload1_back", false); // открываем пещеру
	pchar.quest.Caleuche_amulet2.win_condition.l1 = "item";
	pchar.quest.Caleuche_amulet2.win_condition.l1.item = "kaleuche_amulet2";
	pchar.quest.Caleuche_amulet2.function = "Caleuche_SecondAmuletFind";
}

void Caleuche_SecondAmuletFind(string qName) // 
{
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
	chrDisableReloadToLocation = true;//закрыть локацию
	int iRank = 20+MOD_SKILL_ENEMY_RATE*2;
	int iScl = 70;
	for (int i=1; i<=2; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Beliz_cavebandos_"+i, "citiz_2"+i, "man", "man", iRank, PIRATE, -1, false, "soldier"));
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_06", "pistol6", "bullet", 250);
		sld.dialog.FileName = "Quest\Caleuche_dialog.c";
		sld.dialog.currentnode = "Beliz_cavebandos";	
		sld.greeting = "banditos"; 
		if (i == 2) LAi_CharacterDisableDialog(sld);
		ChangeCharacterAddressGroup(sld, pchar.location, "monsters", "monster"+(33+i));
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	// Калеуче почуял амулет
	pchar.quest.Caleuche_Prepare_MapAttack.win_condition.l1 = "MapEnter";
	pchar.quest.Caleuche_Prepare_MapAttack.function = "Caleuche_PrepareMapAttack";
	AddMapQuestMarkIsland("Dominica", false);
	AddLandQuestMark(characterFromId("Tuttuat"), "questmarkmain");
}

void Caleuche_BelizbandosClear(string qName) // чистим все по квесту
{
	locations[FindLocation("Beliz_ExitTown")].DisableEncounters = false; 
	locations[FindLocation("Beliz_Jungle_01")].DisableEncounters = false; 
	locations[FindLocation("Beliz_CaveEntrance_1")].DisableEncounters = false; 
	locations[FindLocation("Beliz_Cave")].DisableEncounters = false; 
	locations[FindLocation("Beliz_CaveEntrance_2")].DisableEncounters = false; 
	locations[FindLocation("Beliz_Cave_2")].DisableEncounters = false; 
	locations[FindLocation("Beliz_CaveEntrance_3")].DisableEncounters = false; 
	locations[FindLocation("Beliz_jungle_03")].DisableEncounters = false;
	LAi_LocationDisableOfficersGen("Beliz_ExitTown", false);
	LAi_LocationDisableOfficersGen("Beliz_Jungle_01", false);
	LAi_LocationDisableOfficersGen("Beliz_CaveEntrance_1", false);
	LAi_LocationDisableOfficersGen("Beliz_Cave", false);
	LAi_LocationDisableOfficersGen("Beliz_CaveEntrance_2", false);
	LAi_LocationDisableOfficersGen("Beliz_Cave_2", false);
	LAi_LocationDisableOfficersGen("Beliz_CaveEntrance_3", false);
	LAi_LocationDisableOfficersGen("Beliz_jungle_03", false);
	DeleteAttribute(pchar, "questTemp.Caleuche.Bandos");
	DeleteAttribute(pchar, "questTemp.Caleuche.belizbandos");
}

void Caleuche_BelizRegard(string qName) // 
{
	pchar.questTemp.Caleuche.BelizRegard = "true";
}

void Caleuche_PrepareMapAttack(string qName) // 
{
	SetFunctionTimerCondition("Caleuche_MapAttack", 0, 0, 3, false); // таймер
}

void Caleuche_MapAttack(string qName) // корабль-призрак ищет ГГ
{
	if (!Caleuche_CheckAmulet()) return;
	string sCapId = "Map_Caleuche";
    string sGroup = "Sea_" + sCapId + "1";
	Group_DeleteGroup(sGroup);
	Group_FindOrCreateGroup(sGroup);
	
	sld = GetCharacter(NPC_GenerateCharacter(sCapId, "skeletcap", "man", "man", 45, PIRATE, -1, true, "quest"));
	sld.name = StringFromKey("Caleuche_3")
	sld.lastname = "";
	FantomMakeCoolSailor(sld, SHIP_CURSED_FDM, StringFromKey("Caleuche_5"), CANNON_TYPE_CANNON_LBS32, 105, 105, 105);
	FantomMakeCoolFighter(sld, 45, 100, 100, "blade_21", "pistol5", "bullet", 300);
	LAi_SetImmortal(sld, true);
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.DontHitInStorm = true; // не ломается в шторм
	sld.Abordage.Enable = false; // запрет абордажа
	SetShipSailsFromFile(sld, "ships/parus_common.tga");
	SetSailsColor(sld, 8);//черный рваный парус
	ref shTo = &RealShips[sti(sld.Ship.Type)];
	shTo.SpeedRate = 30.0;
	shTo.TurnRate = 70.0;
	SetCrewQuantityOverMax(sld, 666);
	sld.mapEnc.type = "war";
    sld.mapEnc.Name = StringFromKey("Caleuche_5")
	sld.mapEnc.worldMapShip = "pirates_manowar";
	
	Group_AddCharacter(sGroup, sCapId);
	Group_SetGroupCommander(sGroup, sCapId);
    Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
    Group_LockTask(sGroup);
    Map_CreateCoolWarrior("", sCapId, 5);
}

void Caleuche_ClearFromMap(string qName) // стираем энкаунтер Калеуче и ставим новый таймер
{
	log_info(StringFromKey("Caleuche_8"));
	PlaySound("MUSIC\Victory.mp3");
	Group_DeleteGroup("Sea_Map_Caleuche1");
	SetFunctionTimerCondition("Caleuche_MapAttack", 0, 0, 4, false); // таймер
	AddCharacterExpToSkill(pchar, "Sailing", 50);
}

void Caleuche_MapGhostshipBoarding() // подпустили слишком близко - пипец котенку
{
	pchar.GenQuest.FrameLockEsc = true;
	SetMusicAlarm("");
	PlaySound("interface\" + LanguageGetLanguage() + "\_GTBoard2.wav");
	PlaySound("interface\abordage2.wav");
	SetLaunchFrameFormParam("", "", 0, 15);
	SetLaunchFrameFormPic("loading\boarding_b3.tga");
	LaunchFrameForm();
	DoQuestCheckDelay("Caleuche_GhostshipGameOver", 15.0);
}

void Caleuche_CreateGarpiyaInWorld(string qName) // щебека Гарпия на карте
{
	if (!CheckAttribute(pchar, "questTemp.Caleuche.Garpiya")) return;
	
	string sStartCity, sTargetCity;
	if (pchar.questTemp.Garpiya == "to_portroyal")
	{
		sStartCity = "Marigo";
		sTargetCity = "PortRoyal";
	}
	else
	{
		sStartCity = "PortRoyal";
		sTargetCity = "Marigo";
	}
	
	string sCapId = "Map_Garpiya";
    string sGroup = "Sea_" + sCapId + "1";
	Group_DeleteGroup(sGroup);
	Group_FindOrCreateGroup(sGroup);
	
	sld = GetCharacter(NPC_GenerateCharacter(sCapId, "mercen_20", "man", "man", 30, FRANCE, 13, true, "quest"));
	sld.name = StringFromKey("Caleuche_9");
	sld.lastname = StringFromKey("Caleuche_10");
	sld.greeting = "captain";
	sld.Dialog.Filename = "Quest\Caleuche_dialog.c";
	sld.DeckDialogNode = "reginald";
	FantomMakeCoolSailor(sld, SHIP_XebekVML, StringFromKey("Caleuche_11"), CANNON_TYPE_CULVERINE_LBS18, 70, 70, 70);
	FantomMakeCoolFighter(sld, 30, 70, 70, "blade_20", "pistol4", "bullet", 200);
	LAi_SetImmortal(sld, true);
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.DontHitInStorm = true; // не ломается в шторм
	sld.Abordage.Enable = false; // запрет абордажа
	sld.AlwaysFriend = true;
	sld.ShipEnemyDisable  = true;
	sld.Ship.Mode = "trade";
	RealShips[sti(sld.Ship.Type)].ship.upgrades.hull = 1;
	SetCharacterPerk(sld, "MusketsShoot");
	
	sld.mapEnc.type = "trade";
    sld.mapEnc.Name = StringFromKey("Caleuche_12");
	sld.mapEnc.worldMapShip = "ranger";
	
	Group_AddCharacter(sGroup, sCapId);
	Group_SetGroupCommander(sGroup, sCapId);
    //Group_LockTask(sGroup);
    Map_CreateTrader(sStartCity, sTargetCity, sCapId, 12);
	
	pchar.quest.Caleuche_garpiya_sea.win_condition.l1 = "Group_Death";
	pchar.quest.Caleuche_garpiya_sea.win_condition.l1.group = sGroup;
	pchar.quest.Caleuche_garpiya_sea.function = "Caleuche_CreateGarpiyaInSea";
	
	// Captain Beltrop, 12.09.21, отключаем морских ОЗГов на время
    pchar.GenQuest.SeaHunter2Pause = true;
    SeaHunter_Delete();
}

void Caleuche_CreateGarpiyaInSea(string qName) // щебека Гарпия в порту
{
	log_testinfo("Гарпия в порту");
	if (!CheckAttribute(pchar, "questTemp.Caleuche.Garpiya")) return;
	
	int iNation;
	string sTargetIsland;
	if (pchar.questTemp.Garpiya == "to_portroyal")
	{
		sTargetIsland = "Jamaica";
		iNation = ENGLAND;
	}
	else 
	{
		sTargetIsland = "SentMartin";
		iNation = HOLLAND;
	}
	
	string sCapId = "Sea_Garpiya";
    string sGroup = "XebecGarpiya";
	Group_DeleteGroup(sGroup);
	Group_FindOrCreateGroup(sGroup);
	
	sld = GetCharacter(NPC_GenerateCharacter(sCapId, "mercen_20", "man", "man", 30, iNation, 2, true, "quest"));
	sld.name = StringFromKey("Caleuche_9");
	sld.lastname = StringFromKey("Caleuche_10");
	sld.Dialog.Filename = "Quest\Caleuche_dialog.c";
	sld.DeckDialogNode = "reginald";
	sld.greeting = "captain";
	FantomMakeCoolSailor(sld, SHIP_XebekVML, StringFromKey("Caleuche_11"), CANNON_TYPE_CULVERINE_LBS18, 70, 70, 70);
	FantomMakeCoolFighter(sld, 30, 70, 70, "blade_20", "pistol4", "bullet", 200);
	LAi_SetImmortal(sld, true);
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.DontHitInStorm = true; // не ломается в шторм
	sld.Abordage.Enable = false; // запрет абордажа
	sld.AlwaysFriend = true;
	sld.ShipEnemyDisable  = true;
	sld.Ship.Mode = "trade";
	RealShips[sti(sld.Ship.Type)].ship.upgrades.hull = 1;
	SetCharacterPerk(sld, "MusketsShoot");
	
	Group_AddCharacter(sGroup, sCapId);
	Group_SetGroupCommander(sGroup, sCapId);
	Group_SetTaskNone(sGroup);//нет задачи
	Group_SetAddress(sGroup, sTargetIsland, "quest_ships", "Quest_ship_1");
	
	pchar.quest.Caleuche_garpiya_map.win_condition.l1 = "Group_Death";
	pchar.quest.Caleuche_garpiya_map.win_condition.l1.group = sGroup;
	pchar.quest.Caleuche_garpiya_map.function = "Caleuche_PrepareGarpiyaInWorld";
}

void Caleuche_PrepareGarpiyaInWorld(string qName) // подготовка к выходу на карту
{
	if (!CheckAttribute(pchar, "questTemp.Caleuche.Garpiya")) return;

	if (pchar.questTemp.Garpiya == "to_portroyal") pchar.questTemp.Garpiya = "to_marigo";
	else pchar.questTemp.Garpiya = "to_portroyal";
	DoQuestFunctionDelay("Caleuche_CreateGarpiyaInWorld", 1.0);
}

void Caleuche_ThirdAmuletFind(string qName) // нашли третий амулет
{
	BackItemDescribe("kaleuche_key");
	AddQuestRecord("Caleuche", "21");
	SetFunctionTimerCondition("Caleuche_MapAttack", 0, 0, 1, false); // таймер
	AddMapQuestMarkIsland("Dominica", false);
	AddLandQuestMark(characterFromId("Tuttuat"), "questmarkmain");
}

void Caleuche_CreateMonk(string qName) // ставим монаха в Виллемстад
{
	sld = GetCharacter(NPC_GenerateCharacter("monk_caleuche", "monk_5", "man", "man_B", 5, HOLLAND, -1, false, "soldier"));
	FantomMakeCoolFighter(sld, 5, 10, 10, "", "", "", 20);
	sld.Dialog.Filename = "Quest\Caleuche_dialog.c";
	sld.Dialog.currentnode = "monk_caleuche";
	sld.greeting = "monk";
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, "villemstad_town", "quest", "quest1");
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
	AddLandQuestMark(sld, "questmarkmain");
}

void Caleuche_CreateJoakimSkel(string qName) // в комнате ночью
{
	LAi_group_Delete("EnemyFight");
	chrDisableReloadToLocation = true;//закрыть локацию
	LAi_SetActorType(pchar);
	LAi_ActorTurnToLocator(pchar, "goto", "goto2");
	CreateLocationParticles("large_smoke", "goto", "goto2", 0.5, 0, 0, "");
	DoQuestFunctionDelay("Caleuche_SetLandLedySkel", 5.0);
	DoQuestFunctionDelay("Terrapin_SetMusic", 1.2);
}

void Caleuche_SetLandLedySkel(string qName) // скелет хозяйки дома
{
	PlaySound("Types\skel.wav");
	int iRank = 20+MOD_SKILL_ENEMY_RATE*3;
	int iHp = 200+MOD_SKILL_ENEMY_RATE*80;
	sld = GetCharacter(NPC_GenerateCharacter("skel_landlady", "skelt", "skeleton", "skeleton_b", iRank, PIRATE, -1, true, "quest"));
	FantomMakeCoolFighter(sld, iRank, 90, 90, "topor_02", "", "", 50);
	SetSPECIAL(sld, 10, 10, 10, 3, 3, 10, 10);
	LAi_SetHP(sld, iHp, iHp);
	if (MOD_SKILL_ENEMY_RATE > 4)
	{
		sld.cirassId = Items_FindItemIdx("cirass1");
		SetCharacterPerk(sld, "Energaiser");
		SetCharacterPerk(sld, "SwordplayProfessional");
		SetCharacterPerk(sld, "HardHitter");
	}
	float fMft = MOD_SKILL_ENEMY_RATE/10;
	sld.MultiFighter = 1.0+fMft; // мультифайтер
	sld.name = StringFromKey("Caleuche_13");
	sld.lastname = StringFromKey("Caleuche_14");
	sld.monster = true;
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	GiveItem2Character(sld, "jewelry42");
	GiveItem2Character(sld, "jewelry45");
	GiveItem2Character(sld, "jewelry46");
	GiveItem2Character(sld, "jewelry43");
	GiveItem2Character(sld, "Mineral6");
	GiveItem2Character(sld, "purse1"); // Addon-2016 Jason
	LAi_SetActorType(sld);
	LAi_ActorTurnToCharacter(sld, pchar);
	ChangeCharacterAddressGroup(sld, "Villemstad_houseSp1_room", "goto", "goto2");
	CreateLocationParticles("fire_incas_Simple", "goto", "goto2", 0.5, 0, 0, "");
	DoQuestFunctionDelay("Caleuche_LandLedySkelAttack", 5.0);
}

void Caleuche_LandLedySkelAttack(string qName) // скелет хозяйки дома атакует
{
	PlaySound("Reef\reef_01.wav");
	LAi_SetPlayerType(pchar);
	sld = characterFromId("skel_landlady");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "Caleuche_LandLedySkelDie");
	LAi_SetFightMode(pchar, true);
	DoQuestFunctionDelay("Terrapin_SetMusic", 0.5);
}

void Caleuche_PrepareCubaGrot() // готовим пещеру Кубы
{
	locations[FindLocation("Cuba_Jungle_07")].DisableEncounters = true; 
	locations[FindLocation("Cuba_CaveEntrance")].DisableEncounters = true; 
	locations[FindLocation("Cuba_Grot")].DisableEncounters = true;
	LocatorReloadEnterDisable("Cuba_Jungle_07", "reload2_back", true);
	// ставим охотника
	sld = GetCharacter(NPC_GenerateCharacter("cavehunter", "mush_ctz_2", "man", "mushketer", 25, SPAIN, -1, true, "soldier"));
	FantomMakeCoolFighter(sld, 25, 70, 100, "", "mushket1", "cartridge", 150);
	sld.Dialog.Filename = "Quest\Caleuche_dialog.c";
	sld.dialog.currentnode = "cavehunter";
	sld.greeting = "town_pirate";
	sld.MusketerDistance = 5;
	LAi_SetGuardianType(sld);
	sld.protector = true;
	ChangeCharacterAddressGroup(sld, "Cuba_Jungle_07", "officers", "reload2_2");
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
}

void Caleuche_CubaCaveEntrance(string qName) // бой перед пещерой
{
	LAi_group_Delete("EnemyFight");
	chrDisableReloadToLocation = true;//закрыть локацию
	// нечисть
	int iRank = 16+MOD_SKILL_ENEMY_RATE*2;
	for (int i=1; i<=6; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("cubacaveent_skel_"+i, "skel"+(rand(3)+1), "skeleton", "skeleton", iRank, PIRATE, -1, true, "soldier"));
		FantomMakeCoolFighter(sld, iRank, 50, 50, LinkRandPhrase("blade_03","blade_05","blade_07"), "pistol1", "bullet", 120);
		sld.monster = true; 
		LAi_SetWarriorType(sld);
		if (i < 4) ChangeCharacterAddressGroup(sld, "Cuba_CaveEntrance", "officers", "reload1_"+i);
		else ChangeCharacterAddressGroup(sld, "Cuba_CaveEntrance", "monsters", "monster"+(i-3));
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	// помощник, если есть
	if (GetCharacterIndex("cavehunter") != -1)
	{
		sld = characterFromId("cavehunter");
		if (CheckAttribute(sld, "quest.caleuche"))
		{
			sld.MusketerDistance = 0;
			sld.MushketBulletType = "cartridge";
			ChangeCharacterAddressGroup(sld, "Cuba_CaveEntrance", "officers", "reload2_1");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
		else sld.lifeday = 0;
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "Caleuche_CubaCaveEntSkelDie");
	LAi_SetFightMode(pchar, true);
}

void Caleuche_CubaGrot(string qName) // нечисть в гроте
{
	chrDisableReloadToLocation = true;//закрыть локацию
	// нечисть
	int iRank = 18+MOD_SKILL_ENEMY_RATE*2;
	for (int i=1; i<=6; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("cubagrot_skel1_"+i, "skel"+(rand(3)+1), "skeleton", "skeleton", iRank, PIRATE, -1, true, "soldier"));
		FantomMakeCoolFighter(sld, iRank, 60, 60, LinkRandPhrase("blade_15","blade_04","blade_06"), "pistol1", "bullet", 150);
		sld.monster = true; 
		LAi_SetWarriorType(sld);
		if (i < 4) ChangeCharacterAddressGroup(sld, "Cuba_Grot", "monsters", "monster3");
		else ChangeCharacterAddressGroup(sld, "Cuba_Grot", "monsters", "monster4");
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	// помощник, если есть
	if (GetCharacterIndex("cavehunter") != -1)
	{
		sld = characterFromId("cavehunter");
		if (CheckAttribute(sld, "quest.caleuche"))
		{
			sld.MusketerDistance = 5;
			sld.MushketBulletType = "cartridge";
			ChangeCharacterAddressGroup(sld, "Cuba_Grot", "officers", "reload1_2");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_SetCheck("EnemyFight", "Caleuche_CubaGrotSkel1Die");
	LAi_SetFightMode(pchar, true);
}

void Caleuche_CubaGrotChavinavy(string qName)//драка с монстром
{
	LAi_group_Delete("EnemyFight");
	PlaySound("ambient\horror\horror2.wav");
	sld = GetCharacter(NPC_GenerateCharacter("CubaChavinavi", "Chavinavi_1", "skeleton", "skeleton", 20+MOD_SKILL_ENEMY_RATE*3, PIRATE, -1, false, "quest"));
	FantomMakeCoolFighter(sld, 20+MOD_SKILL_ENEMY_RATE*3, 80, 80, "topor_01", "pistol6", "bullet", MOD_SKILL_ENEMY_RATE*80);
	sld.name = StringFromKey("Caleuche_15");
	sld.lastname = StringFromKey("Caleuche_16");
	sld.monster = true; // признак нежити
	sld.MultiFighter = 1.0+MOD_SKILL_ENEMY_RATE/10; // мультифайтер
	ChangeCharacterAddressGroup(sld, "Cuba_Grot", "item", "item2");
	LAi_SetActorType(sld);
	LAi_ActorAnimation(sld, "Ground_sitting", "Caleuche_MonsterStandUp", 1.0);
}

void Caleuche_MerrimanCaveOver(string qName) // провалили по времени
{
	pchar.quest.caleuche_merriman_cave.over = "yes"; //снять прерывание
	pchar.quest.caleuche_merriman_cave1.over = "yes"; //снять прерывание
	LocatorReloadEnterDisable("Havana_CryptBig2", "reload2", true);
	RemoveItems(pchar, "kaleuche_key", 1);
	sld = characterFromId("Havana_Cemeteryman");
	sld.model = "keeper_5";
	Characters_RefreshModel(sld);
	sld.name = StringFromKey("Caleuche_17");
	sld.lastname = StringFromKey("Caleuche_18");
	sld = characterFromId("Tuttuat");
	sld.dialog.currentnode = "Tuttuat_41";
	sld = GetCharacter(NPC_GenerateCharacter("cryptguard", "off_spa_2", "man", "man", 40, SPAIN, -1, true, "quest"));
	FantomMakeCoolFighter(sld, 40, 100, 100, "blade_19", "pistol4", "bullet", 100);
	sld.dialog.FileName = "Quest\Caleuche_dialog.c";
	sld.dialog.currentnode = "cryptguard";
	sld.greeting = "";
	LAi_SetImmortal(sld, true);
	LAi_SetGuardianType(sld);
	sld.protector = true;
	ChangeCharacterAddressGroup(sld, "Havana_CryptBig2", "reload", "reload2");
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
}

void Caleuche_OpenMerrimanCave(string qName) // открываем логово Мерримана
{
	PlaySound("interface\key.wav");
	LocatorReloadEnterDisable("Havana_CryptBig2", "reload2", false);
}

void Caleuche_InMerrimanCave(string qName) // заполняем логово Мерримана
{
	pchar.quest.Caleuche_MerrimanCaveOver.over = "yes"; //снять прерывание
	RemoveItems(pchar, "kaleuche_key", 1);
	chrDisableReloadToLocation = true;//закрыть локацию
	int iRank = 16+MOD_SKILL_ENEMY_RATE*2;
	int iHp = 200+MOD_SKILL_ENEMY_RATE*80;
	string sTemp = "pistol1";
	if (MOD_SKILL_ENEMY_RATE > 4) sTemp = "pistol5";
	if (MOD_SKILL_ENEMY_RATE > 6) sTemp = "pistol6";
	if (MOD_SKILL_ENEMY_RATE > 8) sTemp = "pistol4";
	// скелеты - черные стражи
	for (int i=1; i<=2; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("merriman_skel_"+i, "skelt", "skeleton", "skeleton_B", iRank+2, PIRATE, -1, true, "soldier"));
		FantomMakeCoolFighter(sld, iRank+2, 60, 60, LinkRandPhrase("blade_15","blade_04","blade_06"), "pistol3", "grapeshot", 150);
		sld.monster = true;
		sld.LSC_clan = true;
		LAi_CharacterDisableDialog(sld);
		LAi_SetGuardianType(sld);
		ChangeCharacterAddressGroup(sld, "Havana_CryptDungeon", "goto", "goto"+(15+i));
		LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
	}
	// скелеты - простые
	for (i=3; i<=8; i++)
	{
		if (i > 6) sld = GetCharacter(NPC_GenerateCharacter("merriman_skel_"+i, "skelt", "skeleton", "skeleton_B", iRank+2, PIRATE, -1, true, "soldier"));
		else sld = GetCharacter(NPC_GenerateCharacter("merriman_skel_"+i, "skel"+(rand(3)+1), "skeleton", "skeleton", iRank, PIRATE, -1, true, "soldier"));
		FantomMakeCoolFighter(sld, iRank, 50, 50, LinkRandPhrase("blade_03","blade_05","blade_07"), "pistol1", "bullet", 120);
		sld.monster = true; 
		sld.LSC_clan = true;
		LAi_CharacterDisableDialog(sld);
		LAi_SetGuardianType(sld);
		if (i < 7) ChangeCharacterAddressGroup(sld, "Havana_CryptDungeon", "goto", "goto"+(3+i));
		else ChangeCharacterAddressGroup(sld, "Havana_CryptDungeon", "goto", "goto"+(11+i));
		LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
	}
	// скелеты - крутые
	for (i=9; i<=11; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("merriman_skel_"+i, "skel"+(rand(3)+1), "skeleton", "skeleton", iRank+4, PIRATE, -1, true, "soldier"));
		FantomMakeCoolFighter(sld, iRank+4, 70, 70, LinkRandPhrase("blade_18","blade_19","blade_21"), sTemp, "bullet", 170);
		sld.monster = true; 
		sld.LSC_clan = true;
		LAi_CharacterDisableDialog(sld);
		LAi_SetGuardianType(sld);
		ChangeCharacterAddressGroup(sld, "Havana_CryptDungeon", "goto", "goto"+(2+i));
		LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
	}
	// скелеты - за решеткой, антураж
	for (i=12; i<=15; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("merriman_skel_"+i, "skel"+(rand(3)+1), "skeleton", "skeleton", 10, PIRATE, -1, true, "soldier"));
		FantomMakeCoolFighter(sld, 10, 20, 20, "", "", "", 30);
		sld.monster = true; 
		sld.LSC_clan = true;
		LAi_CharacterDisableDialog(sld);
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, "Havana_CryptDungeon", "goto", "goto"+(8+i));
	}
	// скелеты - за столом, антураж
	for (i=16; i<=21; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("merriman_skel_"+i, "skel"+(rand(3)+1), "skeleton", "skeleton", 10, PIRATE, -1, true, "soldier"));
		FantomMakeCoolFighter(sld, 10, 10, 10, "", "", "", 20);
		sld.monster = true; 
		sld.LSC_clan = true;
		LAi_CharacterDisableDialog(sld);
		LAi_SetSitType(sld);
		ChangeCharacterAddressGroup(sld, "Havana_CryptDungeon", "goto", "goto"+(13+i));
	}
	// Жоаким Мерриман, с обычной бошкой
	sld = characterFromId("Joakim");
	sld.dialog.currentnode = "caleuche";
	FantomMakeCoolFighter(sld, iRank+4, 80, 80, "topor_04", "pistol4", "bullet", 20);
	SetSPECIAL(sld, 8, 6, 8, 5, 5, 10, 6);
	LAi_SetHP(sld, iHp, iHp);
	if (MOD_SKILL_ENEMY_RATE > 4)
	{
		sld.cirassId = Items_FindItemIdx("cirass1");
		SetCharacterPerk(sld, "Energaiser");
		SetCharacterPerk(sld, "SwordplayProfessional");
		SetCharacterPerk(sld, "HardHitter");
		TakeNItems(pchar, "potion2", MOD_SKILL_ENEMY_RATE-5);
	}
	float fMft = MOD_SKILL_ENEMY_RATE/10;
	sld.MultiFighter = 1.0+fMft; // мультифайтер
	sld.LSC_clan = true;
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	GiveItem2Character(sld, "SkullAztec");
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, "Havana_CryptDungeon", "quest", "quest1");
	// прерывание на локатор-детектор
	pchar.quest.caleuche_mdetector.win_condition.l1 = "locator";
	pchar.quest.caleuche_mdetector.win_condition.l1.location = "Havana_CryptDungeon";
	pchar.quest.caleuche_mdetector.win_condition.l1.locator_group = "quest";
	pchar.quest.caleuche_mdetector.win_condition.l1.locator = "detector";
	pchar.quest.caleuche_mdetector.function = "Caleuche_MerrimanTalk";
}

void Caleuche_MerrimanTalk(string qName) // активируем разговор с Мерриманом
{
	DoQuestFunctionDelay("Terrapin_SetMusic", 0.5);
	// останавливаем скелетов и офицеров
	for (i=1; i<=11; i++)
	{
		if (GetCharacterIndex("merriman_skel_"+i) != -1)
		{
			sld = characterFromId("merriman_skel_"+i);
			if (LAi_GetCharacterHP(sld) > 0) LAi_SetActorType(sld);
		}
	}
	if(GetOfficersQuantity(pchar) > 0)
	{
		pchar.OfficerAttRange = 7.0;
		OfficersHold();
	}
	sld = characterFromId("Joakim");
	LAi_SetActorType(sld);
	LAi_SetActorType(pchar);
	LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
	LAi_ActorTurnToCharacter(sld, pchar);
	SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
	iGlobalTemp = 0;
}

void Caleuche_MerrimanCallMonster(string qName) // вызов Мерриманом Чавинави
{
	sld = characterFromId("Joakim");
	if (LAi_GetCharacterHP(sld) < 1) return;
	PlaySound("VOICE\Russian\hambit\Joakim Merriman-03.wav");
	sld = GetCharacter(NPC_GenerateCharacter("MerrimanChavinavi"+iGlobalTemp, "Chavinavi_1", "man", "skeleton", 20+MOD_SKILL_ENEMY_RATE*3, PIRATE, -1, false, "quest"));
	FantomMakeCoolFighter(sld, 20+MOD_SKILL_ENEMY_RATE*3, 70, 70, "topor_01", "pistol6", "bullet", MOD_SKILL_ENEMY_RATE*60);
	sld.name = StringFromKey("Caleuche_15");
	sld.lastname = StringFromKey("Caleuche_16");
	sld.monster = true; // признак нежити
	sld.LSC_clan = true;
	sld.MultiFighter = 1.0+MOD_SKILL_ENEMY_RATE/20; // мультифайтер
	GetCharacterPos(pchar, &locx, &locy, &locz);
	string sTemp = LAi_FindNearestLocator("goto", locx, locy, locz);
	ChangeCharacterAddressGroup(sld, "Havana_CryptDungeon", "goto", sTemp);
	CreateLocationParticles("fire_incas_Simple", "goto", sTemp, 0.5, 0, 0, "");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	LAi_group_SetRelation("TmpEnemy", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("TmpEnemy", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("TmpEnemy", "Caleuche_MerrimanRecallMonster");
}

void Caleuche_FindSkull(string qName) // нашли нефритовый череп
{
	chrDisableReloadToLocation = false;//открыть локацию
	InterfaceStates.Buttons.Save.enable = true;
	DeleteAttribute(pchar, "GenQuest.CannotWait");
	DeleteAttribute(pchar, "GenQuest.NoDelBody");
	AddQuestRecord("Caleuche", "33");
	sld = characterFromId("Joakim");
	sld.model = "Meriman_1";
	Characters_RefreshModel(sld);
	pchar.questTemp.Caleuche = "island";
	sld = ItemsFromID("SkullAztec");
	sld.shown = true; // деактивация для локатора итем
	sld.price = 0;
	sld.ItemType = "QUESTITEMS";
}

void Caleuche_MerrimanBoxOpen() // открыли ящик Мерримана
{
	RemoveItems(pchar, "MerrimanBook", 1);
	PlaySound("interface\important_item.wav");
	//Log_Info("Вы получили склянку этилового спирта");
	//Log_Info("Вы получили склянку азотной кислоты");
	//Log_Info("Вы получили тигель");
	//Log_Info("Вы получили ступку с пестиком");
	//Log_Info("Вы получили стеклянные флаконы");
	//Log_Info("Вы получили мангаросу");
	//Log_Info("Вы получили рецепт эликсира");
	TakeNItems(pchar, "mineral28", 1);
	TakeNItems(pchar, "mineral29", 1);
	TakeNItems(pchar, "tigel", 1);
	TakeNItems(pchar, "mineral27", 1);
	TakeNItems(pchar, "mineral17", 10);
	TakeNItems(pchar, "cannabis7", 1);
	TakeNItems(pchar, "recipe_potion2", 1);
}

void Caleuche_TuttuatAmuletOver(string qName) // действие амулетов истекло
{
	Log_Info(StringFromKey("Caleuche_19"));
	PlaySound("interface\notebook.wav");
	if(IsEquipCharacterByArtefact(pchar, "kaleuche_amulet2")) RemoveCharacterEquip(pchar, TALISMAN_ITEM_TYPE);
	if(IsEquipCharacterByArtefact(pchar, "kaleuche_amulet3")) RemoveCharacterEquip(pchar, TALISMAN_ITEM_TYPE);
	// преобразуем амулеты
	ChangeItemDescribe("kaleuche_amulet2", "itmdescr_kaleuche_amulet2");
	ChangeItemDescribe("kaleuche_amulet3", "itmdescr_kaleuche_amulet3");
	sld = ItemsFromID("kaleuche_amulet2");
	sld.picIndex = 10;
	sld.picTexture = "ITEMS_36";
	DeleteAttribute(sld, "groupID");
	DeleteAttribute(sld, "unique");
	DeleteAttribute(sld, "kind");
	sld.ItemType = "QUESTITEMS";
	sld = ItemsFromID("kaleuche_amulet3");
	sld.picIndex = 11;
	sld.picTexture = "ITEMS_36";
	DeleteAttribute(sld, "groupID");
	DeleteAttribute(sld, "unique");
	DeleteAttribute(sld, "kind");
	sld.ItemType = "QUESTITEMS";
	pchar.questTemp.Caleuche.AmuletOver = "true";
}

void Caleuche_KhaelRoaArrive(string qName) // прибыли на Хаэль Роа
{
	AddQuestRecord("Caleuche", "36");
	int i, n;
	string sTemp;
	// сюда ставим все изменения в локациях храма, лабиринтов и алькова - без НИ
	// джунгли вход в храм
	n = Findlocation("KhaelRoa_Temple_h");
	locations[n].type = "questisland";
	locations[n].DisableEncounters = true;
	locations[n].islandId = "KhaelRoa";
	SetItemInLocation("cannabis7", locations[n].id, "qflower1");
	// лабиринт-1
	n = Findlocation("KhaelRoa_Labirint_1");
	locations[n].type = "teno_inside";
	Locations[n].environment.weather = "true";
	Locations[n].environment.sea = "false";
	Locations[n].lockWeather = "Inside";
	locations[n].environment.weather.rain = false;
	locations[n].islandId = "KhaelRoa";
	Locations[n].reload.l1.name = "reload27";
	Locations[n].reload.l1.go = "KhaelRoa_Temple_h";
	Locations[n].reload.l1.emerge = "reload2";
	Locations[n].reload.l1.autoreload = "1";
	locations[n].DisableOfficers = "1";
	// лабиринт-2
	n = Findlocation("KhaelRoa_Labirint_2");
	locations[n].type = "teno_inside";
	Locations[n].environment.weather = "true";
	Locations[n].environment.sea = "false";
	Locations[n].lockWeather = "Inside";
	locations[n].environment.weather.rain = false;
	locations[n].islandId = "KhaelRoa";
	locations[n].DisableOfficers = "1";
	// лабиринт-3
	n = Findlocation("KhaelRoa_Labirint_3");
	locations[n].type = "teno_inside";
	Locations[n].environment.weather = "true";
	Locations[n].environment.sea = "false";
	Locations[n].lockWeather = "Inside";
	locations[n].environment.weather.rain = false;
	locations[n].islandId = "KhaelRoa";
	DeleteAttribute(&locations[n], "reload.l28");
	Locations[n].models.always.l2 = "lab3_blocks";
	locations[n].models.always.door = "door";
	locations[n].models.always.door.locator.group = "door";
	locations[n].models.always.door.locator.name = "door1";
	locations[n].DisableOfficers = "1";
	// альков
	n = Findlocation("KhaelRoa_Treasure_Alcove");
	locations[n].type = "Alcove";
	Locations[n].environment.weather = "true";
	Locations[n].environment.sea = "false";
	Locations[n].lockWeather = "Inside";
	locations[n].environment.weather.rain = false;
	locations[n].islandId = "KhaelRoa";
	locations[n].locators_radius.item.button01 = 1.2;
	DeleteAttribute(&locations[n], "models.always.l3"); // артефакт
	locations[n].DisableOfficers = "1";
	// прерывание
	pchar.quest.Caleuche_alcove.win_condition.l1 = "locator";
	pchar.quest.Caleuche_alcove.win_condition.l1.location = "KhaelRoa_Treasure_Alcove";
	pchar.quest.Caleuche_alcove.win_condition.l1.locator_group = "teleport";
	pchar.quest.Caleuche_alcove.win_condition.l1.locator = "teleport6";
	pchar.quest.Caleuche_alcove.function = "Caleuche_InAlcoveTop";
	// подсказки
	pchar.quest.Caleuche_support1.win_condition.l1 = "locator";
	pchar.quest.Caleuche_support1.win_condition.l1.location = "KhaelRoa_Treasure_Alcove";
	pchar.quest.Caleuche_support1.win_condition.l1.locator_group = "teleport";
	pchar.quest.Caleuche_support1.win_condition.l1.locator = "teleport0";
	pchar.quest.Caleuche_support1.function = "Caleuche_TeleportSupport";
	pchar.quest.Caleuche_support2.win_condition.l1 = "locator";
	pchar.quest.Caleuche_support2.win_condition.l1.location = "KhaelRoa_Treasure_Alcove";
	pchar.quest.Caleuche_support2.win_condition.l1.locator_group = "teleport";
	pchar.quest.Caleuche_support2.win_condition.l1.locator = "teleport1";
	pchar.quest.Caleuche_support2.function = "Caleuche_TeleportSupport";
	pchar.quest.Caleuche_support3.win_condition.l1 = "locator";
	pchar.quest.Caleuche_support3.win_condition.l1.location = "KhaelRoa_Labirint_3";
	pchar.quest.Caleuche_support3.win_condition.l1.locator_group = "quest";
	pchar.quest.Caleuche_support3.win_condition.l1.locator = "detector";
	pchar.quest.Caleuche_support3.function = "Caleuche_TileSupport";
}

void Caleuche_TileSupport(string qName) // 
{
	AddQuestRecord("Caleuche", "44");
}

void Caleuche_NineStoneTiles() // ступили на правильную плитку
{
	PlaySound("interface\key.wav");
	switch (sti(pchar.questTemp.Caleuche.Tile))
	{
		case 0:
			switch (pchar.questTemp.Caleuche.NextTile)
			{
				case "step1": pchar.questTemp.Caleuche.NextTile = "step4"; break;
				case "step4": pchar.questTemp.Caleuche.NextTile = "step5"; break;
				case "step5": pchar.questTemp.Caleuche.NextTile = "step2"; break;
				case "step2": pchar.questTemp.Caleuche.NextTile = "step3"; break;
				case "step3": pchar.questTemp.Caleuche.NextTile = "step6"; break;
				case "step6": pchar.questTemp.Caleuche.NextTile = "step9"; break;
				case "step9": Caleuche_NineStoneTilesOpen(); break;
				break;
			}
		break;
		case 1:
			switch (pchar.questTemp.Caleuche.NextTile)
			{
				case "step4": pchar.questTemp.Caleuche.NextTile = "step1"; break;
				case "step1": pchar.questTemp.Caleuche.NextTile = "step2"; break;
				case "step2": pchar.questTemp.Caleuche.NextTile = "step5"; break;
				case "step5": pchar.questTemp.Caleuche.NextTile = "step8"; break;
				case "step8": pchar.questTemp.Caleuche.NextTile = "step9"; break;
				case "step9": pchar.questTemp.Caleuche.NextTile = "step6"; break;
				case "step6": Caleuche_NineStoneTilesOpen(); break;
				break;
			}
		break;
		case 2:
			switch (pchar.questTemp.Caleuche.NextTile)
			{
				case "step7": pchar.questTemp.Caleuche.NextTile = "step4"; break;
				case "step4": pchar.questTemp.Caleuche.NextTile = "step5"; break;
				case "step5": pchar.questTemp.Caleuche.NextTile = "step8"; break;
				case "step8": pchar.questTemp.Caleuche.NextTile = "step9"; break;
				case "step9": pchar.questTemp.Caleuche.NextTile = "step6"; break;
				case "step6": pchar.questTemp.Caleuche.NextTile = "step3"; break;
				case "step3": Caleuche_NineStoneTilesOpen(); break;
				break;
			}
		break;
		case 3:
			switch (pchar.questTemp.Caleuche.NextTile)
			{
				case "step7": pchar.questTemp.Caleuche.NextTile = "step8"; break;
				case "step8": pchar.questTemp.Caleuche.NextTile = "step5"; break;
				case "step5": pchar.questTemp.Caleuche.NextTile = "step2"; break;
				case "step2": pchar.questTemp.Caleuche.NextTile = "step3"; break;
				case "step3": pchar.questTemp.Caleuche.NextTile = "step6"; break;
				case "step6": pchar.questTemp.Caleuche.NextTile = "step9"; break;
				case "step9": Caleuche_NineStoneTilesOpen(); break;
			}
		break;
		case 4:
			switch (pchar.questTemp.Caleuche.NextTile)
			{
				case "step1": pchar.questTemp.Caleuche.NextTile = "step4"; break;
				case "step4": pchar.questTemp.Caleuche.NextTile = "step7"; break;
				case "step7": pchar.questTemp.Caleuche.NextTile = "step8"; break;
				case "step8": pchar.questTemp.Caleuche.NextTile = "step9"; break;
				case "step9": pchar.questTemp.Caleuche.NextTile = "step6"; break;
				case "step6": pchar.questTemp.Caleuche.NextTile = "step3"; break;
				case "step3": Caleuche_NineStoneTilesOpen(); break;
			}
		break;
	}
}

void Caleuche_NineStoneTilesOpen() // прошли 9 плиток правильно
{
	DeleteAttribute(pchar, "questTemp.Caleuche.NextTile");
	DeleteAttribute(pchar, "questTemp.Caleuche.Tile");
	PlaySound("Ambient\Teno_inside\door_1.wav");
	LAi_SetActorType(pchar);
	LAi_ActorTurnToLocator(pchar, "reload", "reload30");
	DoQuestFunctionDelay("Caleuche_ShowLeftLevers", 4.5);
	AddCharacterExpToSkill(pchar, "Sneak", 200);
}

void Caleuche_NineStoneDelete() // ступили на ложную плитку - начинай сначала
{
	PlaySound("interface\box_locked.wav");
	switch (sti(pchar.questTemp.Caleuche.Tile))
	{
		case 0: pchar.questTemp.Caleuche.NextTile = "step1"; break;
		case 1: pchar.questTemp.Caleuche.NextTile = "step4"; break;
		case 2: pchar.questTemp.Caleuche.NextTile = "step7"; break;
		case 3: pchar.questTemp.Caleuche.NextTile = "step7"; break;
		case 4: pchar.questTemp.Caleuche.NextTile = "step1"; break;
	}
}

void Caleuche_ShowLeftLevers(string qName) // показываем левые рычаги
{
	LAi_SetActorType(pchar);
	LAi_ActorTurnToLocator(pchar, "item", "knife1");
	DoQuestFunctionDelay("Caleuche_ShowLeftLeversFire", 2.5);
}

void Caleuche_ShowLeftLeversFire(string qName) // показываем левые рычаги
{
	LAi_SetActorType(pchar);
	LAi_ActorTurnToLocator(pchar, "item", "knife3");
	pchar.questTemp.Caleuche.Lever.Count = 0;
	pchar.questTemp.Caleuche.LeverL = "true";
	DoQuestCheckDelay("pchar_back_to_player", 2.5);
	iGlobalTemp = 0;
}

void Caleuche_ThreeLeverAim() // наводим ГГ на цель
{
	string sTemp;
	switch (pchar.questTemp.Caleuche.Lever.Locator)
	{
		case "column11": sTemp = "knife1"; break;
		case "column12": sTemp = "knife2"; break;
		case "column13": sTemp = "knife3"; break;
	}
	LAi_SetActorType(pchar);
	LAi_ActorTurnToLocator(pchar, "item", sTemp);
	DoQuestCheckDelay("Caleuche_ThreeLeverAim", 1.0);
}

void Caleuche_ThreeLeverTurn(string qName) // поворачиваем рычаг
{
	PlaySound("interface\key.wav");
	switch (sti(pchar.questTemp.Caleuche.Lever.Count))
	{
		case 0: return; break;
		case 1: pchar.questTemp.Caleuche.Lever.Locator1 = pchar.questTemp.Caleuche.Lever.Locator; break;
		case 2: pchar.questTemp.Caleuche.Lever.Locator2 = pchar.questTemp.Caleuche.Lever.Locator; break;
		case 3: 
			pchar.questTemp.Caleuche.Lever.Locator3 = pchar.questTemp.Caleuche.Lever.Locator;
			Caleuche_CheckThreeLeverTurn();
		break;
	}
}

void Caleuche_CheckThreeLeverTurn() // проверям правильность поворота левых рычагов
{
	bool bOk = false;
	pchar.questTemp.Caleuche.Lever.Count = 0;
	switch (sti(pchar.questTemp.Caleuche.LeftLevers))
	{
		case 0: 
			if (pchar.questTemp.Caleuche.Lever.Locator1 == "column13" && pchar.questTemp.Caleuche.Lever.Locator2 == "column11" && pchar.questTemp.Caleuche.Lever.Locator3 == "column12") bOk = true;
		break;
		
		case 1: 
			if (pchar.questTemp.Caleuche.Lever.Locator1 == "column11" && pchar.questTemp.Caleuche.Lever.Locator2 == "column13" && pchar.questTemp.Caleuche.Lever.Locator3 == "column12") bOk = true;
		break;
		
		case 2: 
			if (pchar.questTemp.Caleuche.Lever.Locator1 == "column12" && pchar.questTemp.Caleuche.Lever.Locator2 == "column13" && pchar.questTemp.Caleuche.Lever.Locator3 == "column11") bOk = true;
		break;
		
		case 3: 
			if (pchar.questTemp.Caleuche.Lever.Locator1 == "column12" && pchar.questTemp.Caleuche.Lever.Locator2 == "column11" && pchar.questTemp.Caleuche.Lever.Locator3 == "column13") bOk = true;
		break;
		
		case 4: 
			if (pchar.questTemp.Caleuche.Lever.Locator1 == "column11" && pchar.questTemp.Caleuche.Lever.Locator2 == "column12" && pchar.questTemp.Caleuche.Lever.Locator3 == "column13") bOk = true;
		break;
	}
	if (bOk)
	{
		PlaySound("Ambient\Teno_inside\door_2.wav");
		LAi_SetActorType(pchar);
		LAi_ActorTurnToLocator(pchar, "reload", "reload30");
		DeleteAttribute(pchar, "questTemp.Caleuche.LeverL");
		DeleteAttribute(pchar, "questTemp.Caleuche.LeftLevers");
		DoQuestFunctionDelay("Caleuche_ShowRightLevers", 5.5);
		AddCharacterExpToSkill(pchar, "Fortune", 150);
	}
	else
	{
		DeleteAttribute(pchar, "questTemp.Caleuche.LeverL");
		pchar.questTemp.Caleuche.LeverType = 0;
		LAi_SetActorType(pchar);
		LAi_ActorTurnToLocator(pchar, "item", "knife4");
		DoQuestFunctionDelay("Caleuche_LeverAttack", 2.0);
	}
}

void Caleuche_ShowRightLevers(string qName) // показываем правые рычаги
{
	LAi_SetActorType(pchar);
	LAi_ActorTurnToLocator(pchar, "item", "knife4");
	DoQuestFunctionDelay("Caleuche_ShowRightLeversFire", 2.5);
	
}

void Caleuche_ShowRightLeversFire(string qName) // показываем правые рычаги
{
	LAi_SetActorType(pchar);
	LAi_ActorTurnToLocator(pchar, "item", "knife6");
	pchar.questTemp.Caleuche.Lever.Count = 0;
	pchar.questTemp.Caleuche.LeverR = "true";
	DoQuestCheckDelay("pchar_back_to_player", 2.5);
}

void Caleuche_SixLeverAim() // наводим ГГ на цель
{
	string sTemp;
	switch (pchar.questTemp.Caleuche.Lever.Locator)
	{
		case "column21": sTemp = "knife4"; break;
		case "column22": sTemp = "knife5"; break;
		case "column23": sTemp = "knife6"; break;
	}
	LAi_SetActorType(pchar);
	LAi_ActorTurnToLocator(pchar, "item", sTemp);
	DoQuestCheckDelay("Caleuche_SixLeverAim", 1.0);
}

void Caleuche_SixLeverTurn(string qName) // поворачиваем рычаг
{
	PlaySound("interface\key.wav");
	switch (sti(pchar.questTemp.Caleuche.Lever.Count))
	{
		case 0: return; break;
		case 1: pchar.questTemp.Caleuche.Lever.Locator1 = pchar.questTemp.Caleuche.Lever.Locator; break;
		case 2: pchar.questTemp.Caleuche.Lever.Locator2 = pchar.questTemp.Caleuche.Lever.Locator; break;
		case 3: 
			pchar.questTemp.Caleuche.Lever.Locator3 = pchar.questTemp.Caleuche.Lever.Locator;
			Caleuche_CheckSixLeverTurn();
		break;
	}
}

void Caleuche_CheckSixLeverTurn() // проверям правильность поворота правых рычагов
{
	bool bOk = false;
	pchar.questTemp.Caleuche.Lever.Count = 0;
	switch (sti(pchar.questTemp.Caleuche.RightLevers))
	{
		case 0: 
			if (pchar.questTemp.Caleuche.Lever.Locator1 == "column23" && pchar.questTemp.Caleuche.Lever.Locator2 == "column22" && pchar.questTemp.Caleuche.Lever.Locator3 == "column21") bOk = true;
		break;
		
		case 1: 
			if (pchar.questTemp.Caleuche.Lever.Locator1 == "column22" && pchar.questTemp.Caleuche.Lever.Locator2 == "column21" && pchar.questTemp.Caleuche.Lever.Locator3 == "column23") bOk = true;
		break;
		
		case 2: 
			if (pchar.questTemp.Caleuche.Lever.Locator1 == "column21" && pchar.questTemp.Caleuche.Lever.Locator2 == "column23" && pchar.questTemp.Caleuche.Lever.Locator3 == "column22") bOk = true;
		break;
		
		case 3: 
			if (pchar.questTemp.Caleuche.Lever.Locator1 == "column22" && pchar.questTemp.Caleuche.Lever.Locator2 == "column23" && pchar.questTemp.Caleuche.Lever.Locator3 == "column21") bOk = true;
		break;
		
		case 4: 
			if (pchar.questTemp.Caleuche.Lever.Locator1 == "column23" && pchar.questTemp.Caleuche.Lever.Locator2 == "column22" && pchar.questTemp.Caleuche.Lever.Locator3 == "column21") bOk = true;
		break;
	}
	if (bOk)
	{
		PlaySound("Ambient\Teno_inside\door_3.wav");
		LAi_SetActorType(pchar);
		LAi_ActorTurnToLocator(pchar, "reload", "reload30");
		DeleteAttribute(pchar, "questTemp.Caleuche.LeverR");
		DeleteAttribute(pchar, "questTemp.Caleuche.RightLevers");
		DoQuestCheckDelay("pchar_back_to_player", 6.0);
		DoQuestCheckDelay("Video_Door", 6.0);
		AddCharacterExpToSkill(pchar, "Fortune", 150);
	}
	else
	{
		DeleteAttribute(pchar, "questTemp.Caleuche.LeverR");
		pchar.questTemp.Caleuche.LeverType = 1;
		LAi_SetActorType(pchar);
		LAi_ActorTurnToLocator(pchar, "item", "knife2");
		DoQuestFunctionDelay("Caleuche_LeverAttack", 2.0);
	}
}

void Caleuche_LeverAttack(string qName) // ставим чавинави при неправильной последовательности
{
	PlaySound("ambient\horror\horror2.wav");
	for (int i=1; i<=2; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("LeverChavinavi_"+i+iGlobalTemp, "Chavinavi_1", "man", "skeleton", 20+MOD_SKILL_ENEMY_RATE*2, PIRATE, -1, false, "quest"));
		FantomMakeCoolFighter(sld, 20+MOD_SKILL_ENEMY_RATE*3, 70, 70, "topor_01", "pistol6", "bullet", MOD_SKILL_ENEMY_RATE*60);
		sld.name = StringFromKey("Caleuche_15");
		sld.lastname = StringFromKey("Caleuche_16");
		sld.monster = true; // признак нежити
		sld.LSC_clan = true;
		sld.KhaelRoaMonster = true;
		sld.MultiFighter = 1.0+MOD_SKILL_ENEMY_RATE/20; // мультифайтер
		LAi_SetActorType(sld);
		if (sti(pchar.questTemp.Caleuche.LeverType) == 0) 
		{
			ChangeCharacterAddressGroup(sld, "KhaelRoa_Labirint_3", "goto", "monster1"+i);
			CreateLocationParticles("fire_incas_Simple", "goto", "monster1"+i, 0.5, 0, 0, "");
		}
		else 
		{
			ChangeCharacterAddressGroup(sld, "KhaelRoa_Labirint_3", "goto", "monster2"+i);
			CreateLocationParticles("fire_incas_Simple", "goto", "monster2"+i, 0.5, 0, 0, "");
		}
	}
	DoQuestFunctionDelay("Caleuche_LeverFight", 2.0);
}

void Caleuche_LeverFight(string qName) // атака чавинави
{
	LAi_SetPlayerType(pchar);
	LAi_group_Delete("EnemyFight");
	chrDisableReloadToLocation = true;//закрыть локацию
	for (int i=1; i<=2; i++)
	{
		sld = characterFromId("LeverChavinavi_"+i+iGlobalTemp);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "Caleuche_LeverFightOver");
	LAi_SetFightMode(pchar, true);
}

void Caleuche_TeleportSupport(string qName)
{
	log_info(StringFromKey("Caleuche_20"));
}

void Caleuche_TeleportStart() // телепортация по алькову
{
	if (CheckAttribute(pchar, "questTemp.Caleuche.LockTeleport"))
	{
		log_info(StringFromKey("Caleuche_21"));
		return;
	}
	PlaySound("Ambient\Teno_inside\teleporter.wav");
	switch (sGlobalTemp)
	{
		case "teleport0": 
			ChangeCharacterAddressGroup(pchar, "KhaelRoa_Treasure_Alcove", "quest", "teleport");
			Caleuche_TeleportTrap();
		break;
		case "teleport1": ChangeCharacterAddressGroup(pchar, "KhaelRoa_Treasure_Alcove", "teleport", "teleport2"); break;
		case "teleport2": ChangeCharacterAddressGroup(pchar, "KhaelRoa_Treasure_Alcove", "teleport", "teleport1"); break;
		case "teleport3": ChangeCharacterAddressGroup(pchar, "KhaelRoa_Treasure_Alcove", "teleport", "teleport4"); break;
		case "teleport4": ChangeCharacterAddressGroup(pchar, "KhaelRoa_Treasure_Alcove", "teleport", "teleport3"); break;
		case "teleport5": ChangeCharacterAddressGroup(pchar, "KhaelRoa_Treasure_Alcove", "teleport", "teleport6"); break;
		case "teleport6": ChangeCharacterAddressGroup(pchar, "KhaelRoa_Treasure_Alcove", "teleport", "teleport5"); break;
	}
}

void Caleuche_TeleportTrap() // телепорт-ловушка
{
	if (CheckAttribute(pchar, "questTemp.Caleuche.Friend")) return;
	LAi_SetActorType(pchar);
	PlaySound("ambient\horror\horror2.wav");
	for (int i=1; i<=6; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("AlkovChavinavi_"+i+iGlobalTemp, "Chavinavi_1", "skeleton", "skeleton", 20+MOD_SKILL_ENEMY_RATE*2, PIRATE, -1, false, "quest"));
		FantomMakeCoolFighter(sld, 20+MOD_SKILL_ENEMY_RATE*3, 70, 70, "topor_01", "", "", MOD_SKILL_ENEMY_RATE*60);
		sld.name = StringFromKey("Caleuche_15");
		sld.lastname = StringFromKey("Caleuche_16");
		sld.monster = true; // признак нежити
		sld.LSC_clan = true;
		sld.KhaelRoaMonster = true;
		sld.MultiFighter = 1.0+MOD_SKILL_ENEMY_RATE/20; // мультифайтер
		if (i < 4) ChangeCharacterAddressGroup(sld, "KhaelRoa_Treasure_Alcove", "quest", "quest1");
		else ChangeCharacterAddressGroup(sld, "KhaelRoa_Treasure_Alcove", "quest", "quest2");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "Caleuche_TeleportTrapOver");
	pchar.questTemp.Caleuche.LockTeleport = "true";
	DoQuestCheckDelay("pchar_back_to_player", 3.0);
}

void Caleuche_InAlcoveTop(string qName) // в святилище
{
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
	pchar.questTemp.Caleuche.LockTeleport = "true";
	int iRank = 20+MOD_SKILL_ENEMY_RATE*3;
	int iHp = 400+MOD_SKILL_ENEMY_RATE*160;
	int iHpt = 200+MOD_SKILL_ENEMY_RATE*100;
	string sPistol = "pistol6";
	if (MOD_SKILL_ENEMY_RATE > 4) sPistol = "pistol4";
	sld = GetCharacter(NPC_GenerateCharacter("TopChavinavi_1", "mictlantecuhtli", "skeleton", "skeleton", iRank+10, PIRATE, -1, false, "quest"));
	FantomMakeCoolFighter(sld, iRank+10, 90, 90, "topor_01", sPistol, "bullet", 50);
	sld.name = StringFromKey("Caleuche_22");
	sld.lastname = StringFromKey("Caleuche_23");
	sld.Dialog.Filename = "Quest\Caleuche_dialog.c";
	sld.dialog.currentnode = "Chavinavi";
	LAi_SetHP(sld, iHp, iHp);
	sld.KhaelRoaMonster = true;
	sld.monster = true; // признак нежити
	sld.MultiFighter = 1.0+MOD_SKILL_ENEMY_RATE/10; // мультифайтер
	ChangeCharacterAddressGroup(sld, "KhaelRoa_Treasure_Alcove", "goto", "monster1");
	TakeNItems(sld, "potion2", MOD_SKILL_ENEMY_RATE/2+1);
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	if (MOD_SKILL_ENEMY_RATE > 2)
	{
		for (int i=2; i<=3; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("TopChavinavi_"+i, "Chavinavi_1", "skeleton", "skeleton", iRank, PIRATE, -1, false, "quest"));
			FantomMakeCoolFighter(sld, iRank, 70, 70, "topor_01", "", "", 50);
			sld.name = StringFromKey("Caleuche_15");
			sld.lastname = StringFromKey("Caleuche_16");
			LAi_SetHP(sld, iHpt, iHpt);
			sld.KhaelRoaMonster = true;
			sld.monster = true; // признак нежити
			sld.MultiFighter = 1.0+MOD_SKILL_ENEMY_RATE/20; // мультифайтер
			TakeNItems(sld, "potion2", MOD_SKILL_ENEMY_RATE/2);
			ChangeCharacterAddressGroup(sld, "KhaelRoa_Treasure_Alcove", "goto", "monster"+i);
			LAi_SetActorType(sld);
		}
	}
	if (MOD_SKILL_ENEMY_RATE == 6)
	{
		for (i=4; i<=5; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("TopChavinavi_"+i, "skel"+(rand(3)+1), "skeleton", "skeleton", iRank, PIRATE, -1, false, "quest"));
			FantomMakeCoolFighter(sld, iRank-10, 60, 60, LinkRandPhrase("blade_10","blade_06","blade_04"), "pistol5", "bullet", 50);
			sld.name = StringFromKey("Caleuche_24");
			sld.lastname = StringFromKey("Caleuche_25");
			LAi_SetHP(sld, iHpt-400, iHpt-400);
			sld.monster = true; // признак нежити
			TakeNItems(sld, "potion2", 2);
			ChangeCharacterAddressGroup(sld, "KhaelRoa_Treasure_Alcove", "goto", "monster"+i);
			LAi_SetActorType(sld);
		}
	}
	if (MOD_SKILL_ENEMY_RATE > 7)
	{
		for (i=4; i<=5; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("TopChavinavi_"+i, "Chavinavi_1", "skeleton", "skeleton", iRank, PIRATE, -1, false, "quest"));
			FantomMakeCoolFighter(sld, iRank, 70, 70, "topor_01", "", "", 50);
			sld.name = StringFromKey("Caleuche_15");
			sld.lastname = StringFromKey("Caleuche_16");
			LAi_SetHP(sld, iHpt, iHpt);
			sld.KhaelRoaMonster = true;
			sld.monster = true; // признак нежити
			sld.MultiFighter = 1.0+MOD_SKILL_ENEMY_RATE/20; // мультифайтер
			TakeNItems(sld, "potion2", MOD_SKILL_ENEMY_RATE/2);
			ChangeCharacterAddressGroup(sld, "KhaelRoa_Treasure_Alcove", "goto", "monster"+i);
			LAi_SetActorType(sld);
		}
	}
	LAi_SetActorType(pchar);
	DoQuestCheckDelay("pchar_back_to_player", 2.5);
}

void Caleuche_PutSkull() // положили череп
{
	if (CheckAttribute(pchar, "questTemp.Caleuche.QuestionFail"))
	{
		DeleteAttribute(pchar, "questTemp.Caleuche.QuestionFail");
		AddQuestRecord("Caleuche", "37");
	}
	int n = Findlocation("KhaelRoa_Treasure_Alcove");
	locations[n].type = "Alcove_1";
	Locations[n].models.always.totem.rotate.x = 0.0;
	Locations[n].models.always.totem.rotate.y = 0.5;
	Locations[n].models.always.totem.rotate.z = 0.0;
	SetMusic("music_alcove_1");
	DeleteAttribute(pchar, "questTemp.Caleuche.LockTeleport");
	setCharacterShipLocation(pchar, "KhaelRoa_port");
	setWDMPointXZ("KhaelRoa_port");
	// ставим прерывание на выход в локацию острова - бой с Калеуче
	pchar.quest.Caleuche_final_battle.win_condition.l1 = "location";
	pchar.quest.Caleuche_final_battle.win_condition.l1.location = "KhaelRoa";
	pchar.quest.Caleuche_final_battle.function = "Caleuche_FinalBattle";
}

void Caleuche_GiveGrant() // получение шкуры ягуара
{
	pchar.questTemp.Caleuche.Friend = "true";
	SetMusic("music_alcove_1");
	sld = characterFromId("TopChavinavi_1");
	sld.dialog.currentnode = "Chavinavi_5";
	LAi_SetActorType(pchar);
	bDisableCharacterMenu = true;//лоченые интерфейсы
	InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться
	DoQuestCheckDelay("Caleuche_RotatePause", 5.0);
}

void Caleuche_FinalBattle(string qName) // последний бой калеуче
{
	if (GetCharacterIndex("Caleuche_seacap") != -1)
	{
		sld = characterFromId("Caleuche_seacap");
		sld.lifeday = 0; // убираем ненужного НПС
		ChangeCharacterAddressGroup(sld, "none", "", "");
	} // это лучше потом убрать
	bQuestDisableMapEnter = true;
	Island_SetReloadEnableGlobal("KhaelRoa", false);
	DoQuestFunctionDelay("Caleuche_CreateGhostshipKhalRoa", 30.0);
	LAi_group_SetRelation(LAI_GROUP_MONSTERS, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	DeleteAttribute(pchar, "questTemp.Caleuche.Friend");
	LAi_LocationFightDisable(&Locations[FindLocation("KhaelRoa_Treasure_Alcove")], false);
}

void Caleuche_CreateGhostshipKhalRoa(string qName)//подгружаем в море Калеуче
{
	log_info(StringFromKey("Caleuche_26"));
	PlaySound("interface\" + LanguageGetLanguage() + "\_EvEnemy1.wav");
	SetMusicAlarm("music_storm");
	int iRank = 20+MOD_SKILL_ENEMY_RATE*3;
	Group_FindOrCreateGroup("Caleuche_Attack");
	sld = GetCharacter(NPC_GenerateCharacter("Kaleuche_khaelroacap", "skeletcap", "man", "man", iRank, PIRATE, -1, true, "quest"));
	sld.name = StringFromKey("Caleuche_27");
	sld.lastname = StringFromKey("Caleuche_28");
	FantomMakeCoolSailor(sld, SHIP_CURSED_FDM, StringFromKey("Caleuche_29"), CANNON_TYPE_CANNON_LBS36, 80, 80, 80);
	FantomMakeCoolFighter(sld, iRank, 100, 100, "blade_21", "pistol5", "bullet", 400);
	sld.MultiFighter = 1.0+MOD_SKILL_ENEMY_RATE/10;
	GiveItem2Character(sld, "kaleuche_amulet1");
	GiveItem2Character(sld, "spyglass3");
	sld.cirassId = Items_FindItemIdx("cirass1");
	TakeNItems(sld, "potion2", MOD_SKILL_ENEMY_RATE/2);
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	sld.GenQuest.CrewSkelMode = true;
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.PoisonResistent = true; // Captain Beltrop, 06.10.2020, нет отравлению ядом Таино
	sld.DontHitInStorm = true; // не ломается в шторм
	sld.AlwaysSandbankManeuver = true;
	sld.SinkTenPercent = false;
	SetShipSailsFromFile(sld, "ships/parus_common.tga");
	SetSailsColor(sld, 8);//черный рваный парус
	ref shTo = &RealShips[sti(sld.Ship.Type)];
	shTo.SpeedRate = 30.0;
	shTo.TurnRate = 70.0;
	if (MOD_SKILL_ENEMY_RATE == 10) SetCrewQuantityOverMax(sld, 666);
	else SetCrewQuantityOverMax(sld, 466);
	sld.ship.Crew.Morale = 40+MOD_SKILL_ENEMY_RATE*6;
	sld.Ship.Crew.Exp.Sailors = 40+MOD_SKILL_ENEMY_RATE*6;
	sld.Ship.Crew.Exp.Cannoners = 40+MOD_SKILL_ENEMY_RATE*6;
	sld.Ship.Crew.Exp.Soldiers = 40+MOD_SKILL_ENEMY_RATE*6;
	AddCharacterGoods(sld, GOOD_BALLS, 3300);
	AddCharacterGoods(sld, GOOD_GRAPES, 500);
	AddCharacterGoods(sld, GOOD_KNIPPELS, 700);
	AddCharacterGoods(sld, GOOD_BOMBS, 1500);
	AddCharacterGoods(sld, GOOD_POWDER, 6000);
	Group_AddCharacter("Caleuche_Attack", "Kaleuche_khaelroacap");
    Group_SetGroupCommander("Caleuche_Attack", "Kaleuche_khaelroacap");
	Group_SetTaskAttack("Caleuche_Attack", PLAYER_GROUP);
    Group_LockTask("Caleuche_Attack");
	SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);
	Sea_LoginGroupCurrentSea("Caleuche_Attack");
	Group_SetTaskAttack("Caleuche_Attack", PLAYER_GROUP);
	Ship_SetTaskAttack(SECONDARY_TASK, sti(sld.index), GetMainCharacterIndex());
	
	pchar.quest.Caleuche_Khaelroa_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.Caleuche_Khaelroa_AfterBattle.win_condition.l1.group = "Caleuche_Attack";
	pchar.quest.Caleuche_Khaelroa_AfterBattle.function = "Caleuche_KhaelRoaAfterBattle";
	// для ачивки
	pchar.quest.Caleuche_Khaelroa_Abordage.win_condition.l1 = "Character_Capture";
	pchar.quest.Caleuche_Khaelroa_Abordage.win_condition.l1.character = "Kaleuche_khaelroacap";
	pchar.quest.Caleuche_Khaelroa_Abordage.function = "Caleuche_KhaelroaAbordage";//взяли на абордаж
}

void Caleuche_KhaelRoaAfterBattle(string qName) // победили калеуче
{
	DoQuestCheckDelay("sea_victory", 1.5);
	Group_DeleteGroup("Caleuche_Attack");
	bQuestDisableMapEnter = false;//открыть карту
	Island_SetReloadEnableGlobal("KhaelRoa", true);
	LocatorReloadEnterDisable("KhaelRoa_Temple_h", "reload2", true); // в храм больше не пускаем
	if (CheckCharacterItem(pchar, "kaleuche_amulet1"))
	{
		AddQuestRecord("Caleuche", "39");
		pchar.questTemp.Caleuche = "regard";
		AddCharacterExpToSkill(pchar, "Grappling", 500);
		AddCharacterExpToSkill(pchar, "Defence", 200);
		Achievment_Set("ach_49");
	}
	else
	{
		AddQuestRecord("Caleuche", "40");
		pchar.questTemp.Caleuche = "end";
		CloseQuestHeader("Caleuche");
		sld = characterFromId("Tuttuat");
		sld.lifeday = 0;
		sld = ItemsFromID("kaleuche_amulet1");
		sld.price = 1000;
		sld = ItemsFromID("kaleuche_amulet2");
		sld.price = 1000;
		sld = ItemsFromID("kaleuche_amulet3");
		sld.price = 1000;
	}
	AddComplexSeaExpToScill(600, 500, 500, 0, 300, 500, 0);
	ChangeCharacterComplexReputation(pchar, "fame", 10);
	ChangeCharacterComplexReputation(pchar, "authority", 20);
	pchar.questTemp.KhaelRoa = "true"; // атрибут для Натаниэля на LSC
	if(rand(9) == 5) GiveItem2Character(pchar, "hat7");
}

void Caleuche_KhaelroaAbordage(string qName) // 
{
	pchar.questTemp.Caleuche.Abordage = "true";
	Achievment_Set("ach_49");
}

void Caleuche_MangarosaPotion(string qName) // 
{
	pchar.questTemp.Caleuche.Potion = "true";
}

void Caleuche_MangarosaPotionEffect(string sEff) // 
{
	switch (sEff)
	{
		case "kaleuche_amulet1":
			if (AddSPECIALValue(pchar, SPECIAL_A, 0) != SPECIAL_MAX)
			{
				notification(StringFromKey("Caleuche_30"), "None");
				AddSPECIALValue(pchar, SPECIAL_A, 1);
			}
			AddCharacterSkill(pchar, SKILL_F_LIGHT, 5);
		break;
		
		case "kaleuche_amulet2":
			if (AddSPECIALValue(pchar, SPECIAL_E, 0) != SPECIAL_MAX)
			{
				notification(StringFromKey("Caleuche_31"), "None");
				AddSPECIALValue(pchar, SPECIAL_E, 1);
			}
			AddCharacterSkill(pchar, SKILL_FENCING, 5);
		break;
		
		case "kaleuche_amulet3":
			sld = ItemsFromID("kaleuche_amulet3");
			int i = sti(sld.reaction);
			switch (i)
			{
				case 31:
					if (AddSPECIALValue(pchar, SPECIAL_S, 0) != SPECIAL_MAX)
					{
						notification(StringFromKey("Caleuche_32"), "None");
						AddSPECIALValue(pchar, SPECIAL_S, 1);
					}
					AddCharacterSkill(pchar, SKILL_F_HEAVY, 5);
				break;
				
				case 32:
					if (AddSPECIALValue(pchar, SPECIAL_P, 0) != SPECIAL_MAX)
					{
						notification(StringFromKey("Caleuche_33"), "None");
						AddSPECIALValue(pchar, SPECIAL_P, 1);
					}
					AddCharacterSkill(pchar, SKILL_PISTOL, 5);
				break;
				
				case 33:
					if (AddSPECIALValue(pchar, SPECIAL_I, 0) != SPECIAL_MAX)
					{
						notification(StringFromKey("Caleuche_34"), "None");
						AddSPECIALValue(pchar, SPECIAL_I, 1);
					}
					AddCharacterSkill(pchar, SKILL_SNEAK, 5);
				break;
				
				case 34:
					if (AddSPECIALValue(pchar, SPECIAL_C, 0) != SPECIAL_MAX)
					{
						notification(StringFromKey("Caleuche_35"), "None");
						AddSPECIALValue(pchar, SPECIAL_C, 1);
					}
					AddCharacterSkill(pchar, SKILL_LEADERSHIP, 5);
				break;
				
				case 35:
					if (AddSPECIALValue(pchar, SPECIAL_L, 0) != SPECIAL_MAX)
					{
						notification(StringFromKey("Caleuche_36"), "None");
						AddSPECIALValue(pchar, SPECIAL_L, 1);
					}
					AddCharacterSkill(pchar, SKILL_FORTUNE, 5);
				break;
			}
		break;
	}
}
// <-- Калеуче

//=================================================================
//======================кейсы из quests_reaction===================
//=================================================================
bool Caleuche_QuestComplete(string sQuestName, string qname)
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------ Калеуче ---------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	ref sld, shTo;
	
	int   i, n, Rank, idx, iRank;
    float locx, locy, locz;
	string sTemp;
	
	bool condition = true;
	
	if (sQuestName == "Caleuche_Video") // ролик
	{
		PChar.GenQuest.VideoAVI = "BlackPearl";
		PChar.GenQuest.VideoAfterQuest = "Caleuche_GhostAttack";
		DoQuestCheckDelay("PostVideo_Start", 0.2);
	}
	else if (sQuestName == "Caleuche_GhostAttack") // 
	{
		log_info(StringFromKey("Caleuche_37"));
		PlaySound("interface\" + LanguageGetLanguage() + "\_EvEnemy1.wav");
		SetMusicAlarm("music_storm");
	}
	else if (sQuestName == "Caleuche_GhostshipBoardingDeck") // расстановка абордажных групп
	{
		PlaySound("interface\" + LanguageGetLanguage() + "\_GTBoard2.wav");
		PlaySound("interface\abordage_wining.wav");
		DoQuestFunctionDelay("Terrapin_SetMusic", 1.2);
		LAi_group_Delete("EnemyFight");
		bDisableCharacterMenu = true;//лочим F2
		InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться
		// делаем расчёт сил
		int pCrew = sti(pchar.Ship.Crew.Quantity); 
		int eRank = 20+MOD_SKILL_ENEMY_RATE;
		int pRank = makeint(pCrew*30/666);
		if (pRank < 1) pRank = 1;
		int pScl = makeint(pCrew*70/666)+(20-MOD_SKILL_ENEMY_RATE*2);
		if (pScl < 10) pScl = 10;
		n = 20;
		if (pCrew < 20) n = pCrew;
		// наши 
		for (i=1; i<=n; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("caleuche_pcrew_"+i, "citiz_"+(rand(9)+31), "man", "man", pRank, FRANCE, 2, true, "soldier"));
			FantomMakeCoolFighter(sld, pRank, 20, 20, RandPhraseSimple("blade_10","blade_11"), "pistol1", "bullet", 120);
			SetSelfSkill(sld, pScl, pScl, pScl, pScl, pScl);
			LAi_SetWarriorType(sld);
			if (i < 8) ChangeCharacterAddressGroup(sld, "Deck_Galeon_Ship", "quest", "quest1");
			else ChangeCharacterAddressGroup(sld, "Deck_Galeon_Ship", "quest", "quest2");
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
		// враги
		for (i=1; i<=20; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("caleuche_ecrew_"+i, "skel"+(rand(3)+1), "man", "man", eRank, PIRATE, -1, true, "soldier"));
			FantomMakeCoolFighter(sld, eRank, 20, 20, RandPhraseSimple("blade_10","blade_11"), "pistol1", "bullet", 120);
			SetSelfSkill(sld, 70, 70, 70, 70, 70);
			LAi_SetWarriorType(sld);
			if (i < 8) ChangeCharacterAddressGroup(sld, "Deck_Galeon_Ship", "quest", "quest3");
			else ChangeCharacterAddressGroup(sld, "Deck_Galeon_Ship", "quest", "quest4");
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "Caleuche_GhostshipSkelDie");
		LAi_SetFightMode(pchar, true);
		for(i=1; i<=3; i++)
		{
			idx = GetOfficersIndex(pchar, i);
			if(idx < 0) continue;
			sld = &Characters[idx];
			ChangeCharacterAddressGroup(sld, "Deck_Galeon_Ship", "reload", "reload2");
		}
	}
	else if (sQuestName == "Caleuche_GhostshipSkelDie") // перебили скелетов на палубе
	{
		DoQuestCheckDelay("Caleuche_GhostshipCabinReload", 5.0);
		LAi_SetFightMode(pchar, false);
		AddComplexSelfExpToScill(100, 100, 100, 100);
	}
	else if (sQuestName == "Caleuche_GhostshipCabinReload") // в каюту
	{
		SetLaunchFrameFormParam("", "", 0, 4);
		SetLaunchFrameFormPic("loading\Capdeck_1.tga");
		LaunchFrameForm();
		DoQuestCheckDelay("Caleuche_GhostshipCabinReloadGo", 4.0);
	}
	else if (sQuestName == "Caleuche_GhostshipCabinReloadGo") // в каюту
	{
		DoQuestReloadToLocation("CabineFDM", "rld", "loc0", "Caleuche_GhostshipBoardingCabin");
	}
	else if (sQuestName == "Caleuche_GhostshipBoardingCabin") // в каюте
	{
		LAi_group_Delete("EnemyFight");
		sld = characterFromId("Caleuche_seacap");
		ChangeCharacterAddressGroup(sld, "CabineFDM", "rld", "aloc2");
		LAi_group_MoveCharacter(sld, "EnemyFight");
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_SetFightMode(pchar, true);
		DoQuestCheckDelay("Caleuche_GhostshipCapitan", 15.0);
	}
	else if (sQuestName == "Caleuche_GhostshipCapitan") // разговор
	{
		LAi_SetFightMode(pchar, false);
		sld = characterFromId("Caleuche_seacap");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	else if (sQuestName == "Caleuche_GhostshipGetOut") // вырубили ГГ
	{
		PlaySound("People Fight\Death_NPC_05.wav");
		SetLaunchFrameFormParam(StringFromKey("Caleuche_38"), "", 0, 5);
		LaunchFrameForm();
		WaitDate("", 0, 0, 1, 5, 10); //крутим время
		RecalculateJumpTable();
		DoQuestCheckDelay("Caleuche_ReloadCoast", 5.0);
		RemoveItems(pchar, "kaleuche_amulet1", 1);
		locations[FindLocation("shore27")].DisableEncounters = true; //энкаутеры закрыть
	}
	else if (sQuestName == "Caleuche_ReloadCoast") // на берег
	{
		Group_DeleteGroup("Caleuche_Attack");
		// вычищаем все шторма и прочее
		for (i=0; i<MAX_ISLANDS;i++)
		{				
			if (Islands[i].id == "Dominica")
			{
				DeleteAttribute(&Islands[i], "alwaysStorm");
				DeleteAttribute(&Islands[i], "storm");
				DeleteAttribute(&Islands[i], "QuestlockWeather");
			}
		}
		for (i=0; i<MAX_LOCATIONS;i++)
		{				
			if (Locations[i].id == "Deck_Galeon_Ship")
			{
				DeleteAttribute(&locations[i], "alwaysStorm");
				DeleteAttribute(&locations[i], "storm");
				DeleteAttribute(&locations[i], "QuestlockWeather");
			}
		}
		sld = characterFromId("Caleuche_seacap");
		sld.lifeday = 0; // убираем ненужного НПС
		LAi_LocationFightDisable(&Locations[FindLocation("Deck_Galeon_Ship")], true);//запретить драться
		LAi_SetImmortal(pchar, false);
		Island_SetReloadEnableGlobal("Dominica", true);//на остров можно			
		bQuestDisableMapEnter = false;
		bDisableCharacterMenu = false;//разлочим F2
		InterfaceStates.Buttons.Save.enable = true;//разрешим сохраняться
		setCharacterShipLocation(pchar, "Shore27");
		setWDMPointXZ("Shore27"); // корабль в бухту
		//pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
		//pchar.Ship.name = "Лодка";
		//SetBaseShipData(pchar); // на баркас
		//NullCharacterGoods(pchar);
		//SetCrewQuantityFull(pchar);
		//SetCharacterGoods(pchar, GOOD_FOOD, 20);
		//AddCharacterGoods(pchar, GOOD_MEDICAMENT, 5);
		//AddCharacterGoods(pchar, GOOD_RUM, 3);
		pchar.ship.HP = sti(pchar.ship.HP) / 5;
		pchar.Ship.Crew.Quantity = sti(pchar.ship.Crew.Quantity) / 5;
		pchar.ship.masts.mast1 = 1;
		pchar.ship.masts.mast2 = 1;
		pchar.ship.masts.mast3 = 1;
		DoQuestReloadToLocation("Shore27", "goto", "goto1", "");
		LocatorReloadEnterDisable("Shore27", "boat", true); // в море не пускаем
		chrDisableReloadToLocation = true;//закрыть локацию
		sld = characterFromId("Tuttuat");
		sld.dialog.currentnode = "Tuttuat_11"; // ноду шаману
		AddLandQuestMark(sld, "questmarkmain");
		if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = characterFromId("Mary");
		else
		{
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sld = characterFromId("Helena");
			else
			{
				sld = GetCharacter(NPC_GenerateCharacter("caleuche_oursailor", "Alonso", "man", "man", 25, FRANCE, 1, false, "soldier"));
				sld.name = StringFromKey("Caleuche_39");
				sld.lastname = StringFromKey("Caleuche_40");
				sld.dialog.FileName = "Quest\Caleuche_dialog.c";
			}
		}
		sld.Dialog.currentnode = "on_coast";
		ChangeCharacterAddressGroup(sld, "shore27", "goto", "goto2");
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.5);
		LAi_SetCurHPMax(pchar);
		AddCharacterHealth(pchar, -30);
		AddQuestRecord("Caleuche", "4");
	}
	else if (sQuestName == "Caleuche_BelizTownbandosDie") // прибили бандюка в доме
	{
		AddQuestRecord("Caleuche", "11");
		LAi_LocationDisableOfficersGen("Beliz_ExitTown", true);
		LAi_LocationDisableOfficersGen("Beliz_Jungle_01", true);
		LAi_LocationDisableOfficersGen("Beliz_CaveEntrance_1", true);
		LAi_LocationDisableOfficersGen("Beliz_Cave", true);
		LAi_LocationDisableOfficersGen("Beliz_CaveEntrance_2", true);
		LAi_LocationDisableOfficersGen("Beliz_Cave_2", true);
		LAi_LocationDisableOfficersGen("Beliz_CaveEntrance_3", true);
		LAi_LocationDisableOfficersGen("Beliz_jungle_03", true);
		AddComplexSelfExpToScill(50, 50, 50, 50);
	}
	else if (sQuestName == "Caleuche_ForestMerchantDie") // перебили конвой купца
	{
		// собираем бандюков
		for (i=2; i<=6; i++)
		{
			if (GetCharacterIndex("Beliz_forestbandos_"+i) != -1)
			{
				sld = characterFromId("Beliz_forestbandos_"+i);	
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				sld.lifeday = 0;
			}
		}
		sld = characterFromId("Beliz_forestbandos_1");
		sld.lifeday = 0; // если будет дополнение - то это убрать
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		sld.dialog.currentnode = "Beliz_forestbandos_7";
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		AddComplexSelfExpToScill(80, 80, 80, 80);
	}
	else if (sQuestName == "Caleuche_HeadBandosEscape") // главнюк почти прибит
	{
		sld = characterFromId("Beliz_forestbandos_1");
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		LAi_ActorRunToLocation(sld, "reload", "reload1_back", "Beliz_ExitTown", "rld", "aloc10", "", -1);
	}
	else if (sQuestName == "Caleuche_CaveBandosDie") // перебили бандюков в пещере
	{
		chrDisableReloadToLocation = false;
		AddQuestRecord("Caleuche", "14");
		AddComplexSelfExpToScill(70, 70, 70, 70);
	}
	else if (sQuestName == "Caleuche_GhostshipGameOver") // калеуче настиг ГГ - геймовер
	{
		GameOver("sea");
	}
	else if (sQuestName == "Caleuche_LandLedySkelDie") // прибили скелет хозяйки дома
	{
		LAi_group_Delete("EnemyFight");
		SetMusicAlarm("");
		chrDisableReloadToLocation = false;
		PlaySound("People Fight\Peace_woman_death_07.wav");
		AddQuestRecord("Caleuche", "25");
		pchar.questTemp.Caleuche = "priest";
		AddComplexSelfExpToScill(100, 100, 100, 100);
	}
	else if (sQuestName == "Caleuche_CubaCaveEntSkelDie") // прибили скелетов у пещеры
	{
		LAi_group_Delete("EnemyFight");
		chrDisableReloadToLocation = false;
		LocatorReloadEnterDisable("Cuba_CaveEntrance", "reload2_back", true);
		pchar.quest.Caleuche_cuba_grot.win_condition.l1 = "location";
		pchar.quest.Caleuche_cuba_grot.win_condition.l1.location = "Cuba_Grot";
		pchar.quest.Caleuche_cuba_grot.function = "Caleuche_CubaGrot";
		AddComplexSelfExpToScill(50, 50, 50, 50);
	}
	else if (sQuestName == "Caleuche_CubaGrotSkel1Die") // прибили 1 партию
	{
		iRank = 20+MOD_SKILL_ENEMY_RATE*2;
		sTemp = "pistol1";
		if (MOD_SKILL_ENEMY_RATE > 4) sTemp = "pistol5";
		if (MOD_SKILL_ENEMY_RATE > 6) sTemp = "pistol6";
		if (MOD_SKILL_ENEMY_RATE > 8) sTemp = "pistol4";
		for (i=1; i<=4; i++)
		{
			PlaySound("Types\skel.wav");
			CreateLocationParticles("fire_incas_Simple", "goto", "ass"+i, 0.5, 0, 0, "");
			sld = GetCharacter(NPC_GenerateCharacter("cubagrot_skel2_"+i, "skel"+(rand(3)+1), "skeleton", "skeleton", iRank, PIRATE, -1, true, "soldier"));
			FantomMakeCoolFighter(sld, iRank, 70, 70, LinkRandPhrase("blade_18","blade_19","blade_21"), sTemp, "bullet", 150);
			sld.monster = true; 
			LAi_SetWarriorType(sld);
			ChangeCharacterAddressGroup(sld, "Cuba_Grot", "goto", "ass"+i);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "Caleuche_CubaGrotSkel2Die");
	}
	else if (sQuestName == "Caleuche_CubaGrotSkel2Die") // прибили 2 партию
	{
		LAi_group_Delete("EnemyFight");
		LAi_SetActorType(pchar);
		LAi_ActorGoToLocator(pchar, "goto", "goto2", "Caleuche_CubaGrotLook", -1);
		CreateLocationParticles("large_smoke", "item", "item2", 0.5, 0, 0, "");
	}
	else if (sQuestName == "Caleuche_CubaGrotLook") // смотрим на дым
	{
		LAi_SetActorType(pchar);
		LAi_ActorTurnToLocator(pchar, "randitem", "randitem1");
		DoQuestFunctionDelay("Caleuche_CubaGrotChavinavy", 3.0);
	}
	else if (sQuestName == "Caleuche_MonsterStandUp") // чавинави
	{
		sld = characterFromId("CubaChavinavi");
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "Ground_StandUp", "Caleuche_MonsterFight", 3.5);
		PlaySound("VOICE\Russian\hambit\Chavinavy.wav");
	}
	else if (sQuestName == "Caleuche_MonsterFight") // чавинави атакует
	{
		PlaySound("ambient\horror\horror2.wav");
		PlaySound("types\skel.wav");
		LAi_SetPlayerType(Pchar);
		sld = characterFromId("CubaChavinavi");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "Caleuche_CubaGrotAfterBattle");
		LAi_SetFightMode(pchar, true);
	}
	else if (sQuestName == "Caleuche_CubaGrotAfterBattle") // прибили чавинави
	{
		chrDisableReloadToLocation = false;
		if (GetCharacterIndex("cavehunter") != -1)
		{
			sld = characterFromId("cavehunter");
			sld.lifeday = 0;
			sld.dialog.currentnode = "cavehunter_11";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		}
		LocatorReloadEnterDisable("Cuba_Jungle_07", "reload1_back", false);
		LocatorReloadEnterDisable("Cuba_Jungle_07", "reload3_back", false);
		LocatorReloadEnterDisable("Cuba_CaveEntrance", "reload2_back", false);
		AddQuestRecord("Caleuche", "28");
		pchar.questTemp.Caleuche = "havana1";
		AddComplexSelfExpToScill(150, 150, 150, 150);
		ChangeCharacterComplexReputation(pchar, "authority", 1);
		ChangeCharacterComplexReputation(pchar, "fame", 1);
	}
	else if (sQuestName == "Caleuche_MerrimanTeleport") // телепортируем Мерримана
	{
		sld = characterFromId("Joakim");
		ChangeCharacterAddressGroup(sld, "Havana_CryptDungeon", "goto", "goto3");
		LAi_SetImmortal(sld, false);
		DoQuestFunctionDelay("Caleuche_MerrimanCallMonster", 1.0);
		LAi_SetPlayerType(pchar);
		LAi_SetFightMode(pchar, true);
		if(GetOfficersQuantity(pchar) > 0)
		{
			pchar.OfficerAttRange = 7.0;
			OfficersFollow();
		}
		for (i=1; i<=11; i++)
		{
			if (GetCharacterIndex("merriman_skel_"+i) != -1)
			{
				sld = characterFromId("merriman_skel_"+i);
				if (LAi_GetCharacterHP(sld) > 0)
				{
					LAi_SetWarriorType(sld);
					LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
				}
			}
		}
		DoQuestFunctionDelay("Terrapin_SetMusic", 0.5);
	}
	else if (sQuestName == "Caleuche_MerrimanRecallMonster") // повторные вызовы чавинави
	{
		if (CheckAttribute(pchar, "questTemp.Caleuche.Merriman_hide"))
		{
			DeleteAttribute(pchar, "questTemp.Caleuche.Merriman_hide");
			sld = characterFromId("Joakim");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, "Havana_CryptDungeon", "goto", LAi_FindFarLocator("goto", locx, locy, locz));
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Caleuche_MerrimanDie");
		}
		iGlobalTemp++;
		DoQuestFunctionDelay("Caleuche_MerrimanCallMonster", 5.0);
	}
	else if (sQuestName == "Caleuche_MerrimanDie") // прибили Мерримана
	{
		InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться
		pchar.GenQuest.CannotWait = true;//запрет ожидания
		for (i=1; i<=11; i++)
		{
			if (GetCharacterIndex("merriman_skel_"+i) != -1)
			{
				sld = characterFromId("merriman_skel_"+i);
				if (LAi_GetCharacterHP(sld) > 0) LAi_KillCharacter(sld); // прибьем скелетов
			}
		}
		sld = characterFromId("MerrimanChavinavi"+iGlobalTemp);
		if (LAi_GetCharacterHP(sld) > 0) LAi_KillCharacter(sld); // прибьем чавинави
		// на нефритовый череп
		pchar.GenQuest.NoDelBody = true;
		pchar.quest.Caleuche_find_skull.win_condition.l1 = "item";
		pchar.quest.Caleuche_find_skull.win_condition.l1.item = "SkullAztec";
		pchar.quest.Caleuche_find_skull.function = "Caleuche_FindSkull";
		AddQuestRecord("Caleuche", "32");
		AddComplexSelfExpToScill(200, 200, 200, 200);
		AddCharacterExpToSkill(pchar, "Leadership", 400);
		ChangeCharacterComplexReputation(pchar, "authority", 5);
		ChangeCharacterComplexReputation(pchar, "fame", 5);
	}
	else if (sQuestName == "Caleuche_ThreeLeverAim") // 
	{
		LAi_SetActorType(pchar);
		LAi_ActorAnimation(pchar, "Barman_idle", "pchar_back_to_player", 2.0);
		DoQuestFunctionDelay("Caleuche_ThreeLeverTurn", 2.0);
	}
	else if (sQuestName == "Caleuche_SixLeverAim") // 
	{
		LAi_SetActorType(pchar);
		LAi_ActorAnimation(pchar, "Barman_idle", "pchar_back_to_player", 2.0);
		DoQuestFunctionDelay("Caleuche_SixLeverTurn", 2.0);
	}
	else if (sQuestName == "Video_Door") // открывается дверь в альков
	{
		PChar.GenQuest.VideoAVI = "Door";
		PChar.GenQuest.VideoAfterQuest = "Caleuche_LabirintReload";
		DoQuestCheckDelay("PostVideo_Start", 0.2);
	}
	else if (sQuestName == "Caleuche_LabirintReload") // перегрузка локации
	{
		n = Findlocation("KhaelRoa_Labirint_3");
		DeleteAttribute(&locations[n], "models.always.door");
		Locations[n].reload.l28.name = "reload30_back";
		Locations[n].reload.l28.go = "KhaelRoa_Treasure_Alcove";
		Locations[n].reload.l28.emerge = "Reload1";
		Locations[n].reload.l28.autoreload = "1";
		DoQuestReloadToLocation("KhaelRoa_Labirint_3", "item", "step5", "");
		iGlobalTemp = 0;
	}
	else if (sQuestName == "Caleuche_LeverFightOver") // прибили чавинави у рычагов
	{
		LAi_group_Delete("EnemyFight");
		chrDisableReloadToLocation = false;
		if (sti(pchar.questTemp.Caleuche.LeverType) == 0) pchar.questTemp.Caleuche.LeverL = "true";
		if (sti(pchar.questTemp.Caleuche.LeverType) == 1) pchar.questTemp.Caleuche.LeverR = "true";
		DeleteAttribute(pchar, "questTemp.Caleuche.LeverType");
		iGlobalTemp++;
	}
	else if (sQuestName == "Caleuche_TeleportTrapOver") // прибили чавинави у телепорта-ловушки
	{
		LAi_group_Delete("EnemyFight");
		DeleteAttribute(pchar, "questTemp.Caleuche.LockTeleport");
		iGlobalTemp++;
	}
	else if (sQuestName == "Caleuche_TopChavinaviDie") // прибили чавинави в святилище
	{
		LAi_group_Delete("EnemyFight");
		sld = ItemsFromID("SkullAztec");
		sld.shown = "0";
		sld.useLocation = "KhaelRoa_Treasure_Alcove";
		sld.useLocator = "button01";
	}
	else if (sQuestName == "Caleuche_RotatePause") // крутим камеру
	{
		locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.005, 0.0, 2.0, 0.0, 1700);
		Pchar.FuncCameraFly = "";
		DoQuestCheckDelay("Caleuche_RotatePauseOver", 25.0);
	}
	else if (sQuestName == "Caleuche_RotatePauseOver") // идем к вождю чавинави
	{
		locCameraResetState();
		bDisableCharacterMenu = false;
		InterfaceStates.Buttons.Save.enable = true;
		Caleuche_PutSkull();
		if (CharacterIsAlive("TopChavinavi_1"))
		{
			sld = characterFromId("TopChavinavi_1");
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
			LAi_ActorTurnToCharacter(sld, pchar);
			SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
		}
		else LAi_SetPlayerType(pchar);
	}
	else if (sQuestName == "Caleuche_ChangeShip") // меняем харки калеуче
	{
		sld = characterFromId("Kaleuche_khaelroacap");
		shTo = &RealShips[sti(sld.Ship.Type)];
		shTo.SpeedRate = 15.2;
		shTo.TurnRate = 32.0;
	}
	else
	{
		condition = false;
	}
	
	return condition;
}