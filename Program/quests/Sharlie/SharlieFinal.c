/////////////////////////////////////////////////////////////////////////////////////////////////////////
// ---------------------------------------- Суп из черепахи --------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void Terrapin_SetEnvoy(string qName) // посланник в таверне
{
	chrDisableReloadToLocation = true;//закрыть локацию
	sld = GetCharacter(NPC_GenerateCharacter("TerrapinEnvoy", "citiz_44", "man", "man", 20, FRANCE, 0, true, "quest"));
	FantomMakeCoolFighter(sld, 20, 50, 50, "blade_10", "pistol3", "bullet", 100);
	sld.dialog.FileName = "Quest\Sharlie\Terrapin.c";
	sld.dialog.currentnode = "envoy";
	sld.greeting = "town_pirate";
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void Terrapin_LevasserInCave(string qName) // ставим Левассера и свиту
{
	chrDisableReloadToLocation = true;//закрыть локацию
	LAi_LocationFightDisable(&Locations[FindLocation("Tortuga_cave")], true);//запретить драться
	int iRank = 22+MOD_SKILL_ENEMY_RATE*2;
	int iScl = 70;
	// сам Левассер
	sld = characterFromId("Tortuga_Mayor");
	sld.dialog.FileName = "Quest\Sharlie\Terrapin.c";
	sld.dialog.currentnode = "levasser_cave";
	sld.greeting = "Levasser";
	LAi_SetWarriorType(sld);
	LAi_warrior_SetStay(sld, true);
	LAi_warrior_DialogEnable(sld, true);
	ChangeCharacterAddressGroup(sld, "Tortuga_cave", "goto", "goto1");
	LAi_SetImmortal(sld, false);
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	// гарды
	for (int i=2; i<=4; i++)
	{		
		sld = GetCharacter(NPC_GenerateCharacter("TerrapinGuard"+i, "citiz_5"+i, "man", "man", iRank, PIRATE, -1, true, "quest"));
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_21", RandPhraseSimple("pistol6","pistol4"), "bullet", iScl*2);
		ChangeCharacterAddressGroup(sld, "Tortuga_cave", "goto", "goto"+i);
		LAi_SetWarriorType(sld);
		LAi_warrior_SetStay(sld, true);
		LAi_warrior_DialogEnable(sld, false);
	}
}

void Terrapin_GotoWindow(string qName) // телепортируем через окошко на крыши
{
	LAi_group_Delete("EnemyFight");
	DoQuestReloadToLocation("Tortuga_Town", "reload", "tavernWindow", "");
	DoQuestFunctionDelay("Terrapin_TownAttack", 1.2);
	chrDisableReloadToLocation = true; // закрыть локацию
	InterfaceStates.Buttons.Save.enable = false; //запретить сохраняться
	LocatorReloadEnterDisable("Tortuga_tavern_upstairs", "reload1_back", false);//открыть комнату таверны patch-8
	setCharacterShipLocation(pchar, "Tortuga_town"));
	setWDMPointXZ("Tortuga_town"); // корабль на рейд
	// ставим горожанку
	sld = GetCharacter(NPC_GenerateCharacter("TerrapinRoofGirl", "women_15", "woman", "towngirl", 10, FRANCE, -1, true, "quest"));
	sld.dialog.FileName = "Quest\Sharlie\Terrapin.c";
	sld.dialog.currentnode = "roof_girl";
	sld.greeting = "rapers_girl_1";
	LAi_SetStayType(sld);
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, "Tortuga_town", "quest", "roof");
	// прерывание на локатор с горожанкой
	pchar.quest.Terrapin_roof.win_condition.l1 = "locator";
	pchar.quest.Terrapin_roof.win_condition.l1.location = "Tortuga_town";
	pchar.quest.Terrapin_roof.win_condition.l1.locator_group = "quest";
	pchar.quest.Terrapin_roof.win_condition.l1.locator = "roof";
	pchar.quest.Terrapin_roof.function = "Terrapin_RoofGirl";
	// ставим Тибо в грот
	sld = characterFromId("Tibo");
	LAi_SetWarriorType(sld);
	LAi_warrior_SetStay(sld, true);
	LAi_warrior_DialogEnable(sld, true);
	ChangeCharacterAddressGroup(sld, "Tortuga_town", "quest", "grot1");
	pchar.questTemp.Terrapin.Attack = "true"; // обработка в АИ
	// создаем и ставим Кати в грот
	sld = GetCharacter(NPC_GenerateCharacter("Kathy", "Catherine", "woman", "woman", 10, ENGLAND, -1, true, "quest"));
	sld.dialog.FileName = "Quest\Sharlie\Terrapin.c";
	sld.dialog.currentnode = "kathy";
	sld.name = StringFromKey("SharlieFinal_1");
	sld.lastname = StringFromKey("SharlieFinal_2");
	LAi_CharacterDisableDialog(sld);
	LAi_SetStayType(sld);
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, "Tortuga_town", "quest", "grot2");
	// ставим трёх квестовых мушкетеров
	for (int i=1; i<=3; i++)
	{		
		sld = GetCharacter(NPC_GenerateCharacter("TerrapinMush"+i, "mush_fra_"+i, "man", "mushketer", 30, FRANCE, 1, true, "quest"));
		FantomMakeCoolFighter(sld, 30, 100, 100, "", "mushket1", "bullet", 200);
		ChangeCharacterAddressGroup(sld, "Tortuga_town", "quest", "mushketer"+i);
		LAi_SetWarriorType(sld);
		LAi_warrior_SetStay(sld, true);
		LAi_warrior_DialogEnable(sld, false);
		LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	}
	pchar.quest.Terrapin_roof1.win_condition.l1 = "locator";
	pchar.quest.Terrapin_roof1.win_condition.l1.location = "Tortuga_town";
	pchar.quest.Terrapin_roof1.win_condition.l1.locator_group = "quest";
	pchar.quest.Terrapin_roof1.win_condition.l1.locator = "shot1";
	pchar.quest.Terrapin_roof1.win_condition = "Terrapin_FirstShot";
	pchar.quest.Terrapin_roof2.win_condition.l1 = "locator";
	pchar.quest.Terrapin_roof2.win_condition.l1.location = "Tortuga_town";
	pchar.quest.Terrapin_roof2.win_condition.l1.locator_group = "quest";
	pchar.quest.Terrapin_roof2.win_condition.l1.locator = "shot3";
	pchar.quest.Terrapin_roof2.win_condition = "Terrapin_FirstShot";
	sTotalTemp = "1";
}

void Terrapin_TownAttack(string qName) // 
{
	sld = CharacterFromID("TerrapinMush1");
	LAi_group_Attack(sld, Pchar);
	SetNationRelation2MainCharacter(FRANCE, RELATION_ENEMY);
	DoQuestFunctionDelay("Terrapin_SetMusic", 0.2);
}

void Terrapin_SetMusic(string qName) // 
{
	SetMusic("music_q_battle");
}

void Terrapin_RoofGirl(string qName) // разговор с девушкой на балконе
{
	DoQuestCheckDelay("hide_weapon", 0.5);
	sld = characterFromId("TerrapinRoofGirl");
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, pchar, "", -1);
	LAi_SetImmortal(sld, false);
}

void Terrapin_CheckEnemyDistance() // расчет дистанции до Тибо
{
	float fdist;
	if (pchar.location == "Tortuga_town")
	{
		if (GetCharacterDistByLoc(pchar, "quest", "grot1", &fdist))
		{
			if (fdist < 13.0) Terrapin_TiboAttack();
		}
	}
}

void Terrapin_TiboAttack() // Тибо атакует
{
	DeleteAttribute(pchar, "questTemp.Terrapin.Attack");
	sld = characterFromId("Tibo");
	LAi_group_MoveCharacter(sld, "EnemyFight");
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "Terrapin_TiboDied");
}

void Terrapin_OwrInGrot() // пришли свои
{
	LAi_SetPlayerType(pchar);
	sld = characterFromId("Kathy");
	LAi_SetActorType(sld);
	LAi_ActorFollow(sld, pchar, "", -1);
	if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = characterFromId("Mary");
	else 
	{
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sld = characterFromId("Helena");
		else
		{
			sld = GetCharacter(NPC_GenerateCharacter("TerrapinOurChar", "Alonso", "man", "man", 20, FRANCE, 0, true, "quest"));
			sld.name = StringFromKey("SharlieFinal_85");
			sld.lastname = "";
			FantomMakeCoolFighter(sld, 20, 50, 50, "blade_10", "pistol1", "bullet", 100);
			sld.dialog.FileName = "Quest\Sharlie\Terrapin.c";
		}
	}
	sld.dialog.currentnode = "terrapin_grot";
	ChangeCharacterAddressGroup(sld, "Tortuga_town", "reload", "reload_grot");
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, pchar, "", -1);
}

void Terrapin_GotoShip()
{
	sld = characterFromId("Kathy");
	sld.dialog.currentnode = "kathy_5";
	AddPassenger(pchar, sld, false);
	SetCharacterRemovable(sld, false);
	// снимаем часть запретов
	chrDisableReloadToLocation = false;//открыть локацию
	InterfaceStates.Buttons.Save.enable = true; //разрешить сохраняться
	SetNationRelation2MainCharacter(FRANCE, RELATION_FRIEND); // мирим
	LAi_LocationDisableOfficersGen("Tortuga_Town", false);//офицеров пускать
	DeleteAttribute(pchar, "GenQuest.Notsearchbody"); // снять запрет обыска
	DeleteAttribute(pchar, "questTemp.Terrapin.Room_close"); // пускать в комнату таверны
	// ставим прерывание на 'Вольтижёр'
	pchar.quest.Terrapin_Rober_attack.win_condition.l1 = "location";
	pchar.quest.Terrapin_Rober_attack.win_condition.l1.location = "Tortuga";
	pchar.quest.Terrapin_Rober_attack.function = "Terrapin_RoberAttack";
	// прерывания на Кати
	pchar.quest.Terrapin_Kathy.win_condition.l1 = "location";
	pchar.quest.Terrapin_Kathy.win_condition.l1.location = "SentJons_town";
	pchar.quest.Terrapin_Kathy.function = "Terrapin_KathyGoHome";
	SetFunctionTimerCondition("Terrapin_KathyDie", 0, 0, 30, false); // таймер
	AddQuestRecord("Terrapin", "11");
	// Пуанси будет не доволен, что устроили беготню с солдатами
	pchar.questTemp.Terrapin_KathyFox = true;
}

void Terrapin_RoberAttack(string qName) // Мартэн атакуэ
{
	int n = Findlocation("Tortuga_town");
	locations[n].models.always.roof_details = "";  //Экку Korsar - удаляем детали для бега на крыше
	locations[n].models.day.charactersPatch = "Margarita_GPK_patch_day"; 
	locations[n].models.night.charactersPatch = "Margarita_GPK_patch_night"; // подменяем патч для персонажа  //Экку Korsar - На новый патч от новой Маргариты
	DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
	int iRate = 40+MOD_SKILL_ENEMY_RATE*5;
	Island_SetReloadEnableGlobal("Tortuga", false);//на остров нельзя
	Group_FindOrCreateGroup("Rober_Group");
	Group_SetType("Rober_Group", "war");//тип группы
	sld = characterFromId("Rober");
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.Coastal_Captain = true;
	sld.Ship.Mode = "pirate";
	sld.alwaysenemy = true;
	sld.ship.Crew.Morale = iRate;
	sld.Ship.Crew.Exp.Sailors = iRate;
	sld.Ship.Crew.Exp.Cannoners = iRate;
	sld.Ship.Crew.Exp.Soldiers = iRate;
	Group_AddCharacter("Rober_Group", "Rober");
	Group_SetGroupCommander("Rober_Group", "Rober");
	Group_SetTaskAttack("Rober_Group", PLAYER_GROUP);
	Group_SetAddress("Rober_Group", "Tortuga", "IslandShips1", "ship_2");
	Group_LockTask("Rober_Group");
	
	pchar.quest.Terrapin_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.Terrapin_AfterBattle.win_condition.l1.group = "Rober_Group";
	pchar.quest.Terrapin_AfterBattle.function = "Terrapin_RoberAfterBattle";
	pchar.quest.Terrapin_DieHard.win_condition.l1 = "MapEnter";
	pchar.quest.Terrapin_DieHard.function = "Terrapin_RoberDieHard";
}

void Terrapin_RoberAfterBattle(string qName) // победили Мартэна
{
	DoQuestCheckDelay("sea_victory", 1.5);
	pchar.quest.Terrapin_DieHard.over = "yes"; //снять прерывание
	Group_DeleteGroup("Rober_Group");
	if (CheckCharacterItem(pchar, "Cromvel_depeshe"))
	{
		AddQuestRecord("Terrapin", "13");
		// прерывание на эскадру Кромвеля
		pchar.quest.Terrapin_CromvelScuadron.win_condition.l1 = "Timer";
		pchar.quest.Terrapin_CromvelScuadron.win_condition.l1.date.hour  = sti(GetTime());
		pchar.quest.Terrapin_CromvelScuadron.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 429);
		pchar.quest.Terrapin_CromvelScuadron.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 429);
		pchar.quest.Terrapin_CromvelScuadron.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 429);
		pchar.quest.Terrapin_CromvelScuadron.function = "Terrapin_SetCromvelScuadron";
		AddCharacterExpToSkill(pchar, "Grappling", 350);
		AddComplexSelfExpToScill(250, 150, 150, 150);
	}
	else AddQuestRecord("Terrapin", "14");
	pchar.questTemp.Terrapin = "done";
	AddComplexSeaExpToScill(100, 150, 150, 0, 100, 100, 0);
	ChangeCharacterComplexReputation(pchar, "authority", 1);
	ChangeOfficersLoyality("good_all", 1);
}

void Terrapin_RoberDieHard(string qName) // ушли на карту
{
	pchar.quest.Terrapin_AfterBattle.over = "yes"; //снять прерывание
	Group_DeleteGroup("Rober_Group");
	AddQuestRecord("Terrapin", "12");
	pchar.questTemp.Terrapin = "done";
	ChangeCharacterComplexReputation(pchar, "authority", -3);
	ChangeOfficersLoyality("bad_all", 1);
}

void Terrapin_KathyDie(string qName) // не довезли Кати
{
	if(bImCasual)
	{
		if(CheckAttribute(pchar,"quest.Terrapin_KathyDie.over"))
			DeleteAttribute(pchar,"quest.Terrapin_KathyDie.over");
		NewGameTip(StringFromKey("SharlieFinal_3"));
		SetFunctionTimerCondition("Terrapin_KathyDie", 0, 0, 30, false);
		return;
	}
	pchar.quest.Terrapin_Kathy.over = "yes"; //снять прерывание
	sld = characterFromId("Kathy");
	RemovePassenger(pchar, sld);
	sld.lifeday = 0;
	SetFunctionTimerCondition("Terrapin_ReturnFox", 0, 0, 3, false); // Фокса на место
	Log_Info(StringFromKey("SharlieFinal_4"));
	AddQuestRecord("Terrapin", "15");
}

void Terrapin_KathyGoHome(string qName) // отвезли Кати
{
	chrDisableReloadToLocation = true;//закрыть локацию
	pchar.quest.Terrapin_KathyDie.over = "yes"; //снять прерывание
	sld = characterFromId("Kathy");
	RemovePassenger(pchar, sld);
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, "SentJons_town", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void Terrapin_ReturnFox(string qName) // Фокса на место
{
	sld = characterFromId("Fox");
	ChangeCharacterAddressGroup(sld, "SentJons_Roomtownhall", "sit", "sit1");
}

void Terrapin_SetFontene(string qName) // Фонтене на место
{
	sld = GetCharacter(NPC_GenerateCharacter("Tortuga_Mayor", "off_fra_5", "man", "man", 40, FRANCE, -1, true, "soldier"));
	sld.name = StringFromKey("SharlieFinal_5");
    sld.lastname = StringFromKey("SharlieFinal_6");
	sld.Dialog.Filename = "Common_Mayor.c";
	sld.dialog.currentnode = "First time";
	sld.greeting = "fra_gov_common";
	sld.quest.type = "hovernor";
	ChangeCharacterAddressGroup(sld, "Tortuga_townhall", "sit", "sit1");
	GiveItem2character(sld, "blade_17");
	EquipcharacterbyItem(sld, "blade_17");
	GiveItem2character(sld, "pistol5"); 
	EquipcharacterbyItem(sld, "pistol5");
	SetRandSPECIAL(sld);
    SetSelfSkill(sld, 100, 100, 100, 100, 100);
	SetShipSkill(sld, 80, 90, 90, 80, 90, 70, 60, 70, 50);
	sld.standUp = true;
	LAi_SetHuberType(sld);
	LAi_RemoveLoginTime(sld);
	LAi_group_Movecharacter(sld, "FRANCE_CITIZENS");
	LAi_SetImmortal(sld, true);
	LAi_LoginInCaptureTown(sld, false);
	LAi_NoRebirthDisable(sld);
}

void CreateGriffondor() // малый фрегат Гриффондор
{
	sld = GetCharacter(NPC_GenerateCharacter("GriffOfficer", "off_fra_2", "man", "man", 10, FRANCE, -1, true, "soldier"));
	SetFantomParamFromRank(sld, 10, true);
	FantomMakeSmallSailor(sld, SHIP_CORVETTE_QUEST, StringFromKey("SharlieFinal_7"), CANNON_TYPE_CANNON_LBS32, 30, 30, 30, 30, 30);
	SetShipSkill(sld, 30, 40, 50, 50, 65, 40, 45, 48, 20);
	SetSelfSkill(sld, 20, 22, 18, 25, 30);
	sld.dialog.FileName = "Quest\Sharlie\OtherNPC.c";
	sld.dialog.currentnode = "griffondor_officer";
	sld.greeting = "patrol";
	SetCharacterPerk(sld, "BasicDefense");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "Gunman");
	SetCharacterPerk(sld, "LongRangeGrappling");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "BasicBattleState");
	SetCharacterPerk(sld, "ShipSpeedUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "Doctor1");
	sld.ship.Crew.Morale = 100;
	sld.Ship.Crew.Exp.Sailors = 100;
	sld.Ship.Crew.Exp.Cannoners = 100;
	sld.Ship.Crew.Exp.Soldiers = 100;
	NullCharacterGoods(sld);
	AddCharacterGoods(sld, GOOD_BALLS, 700);
	AddCharacterGoods(sld, GOOD_GRAPES, 700);
	AddCharacterGoods(sld, GOOD_KNIPPELS, 700);
	AddCharacterGoods(sld, GOOD_BOMBS, 700);
	AddCharacterGoods(sld, GOOD_POWDER, 1000);
	AddCharacterGoods(sld, GOOD_FOOD, 1000);
	AddCharacterGoods(sld, GOOD_MEDICAMENT, 300);
	AddCharacterGoods(sld, GOOD_RUM, 200);
	AddCharacterGoods(sld, GOOD_PLANKS, 50);
	AddCharacterGoods(sld, GOOD_SAILCLOTH, 50);
}

void Terrapin_ReturnTibo(string qName) // Тибо на место
{
	sld = characterFromId("Tibo");
	sld.dialog.currentnode = "tibo_22";
	ChangeCharacterAddressGroup(sld, "Tortuga_houseS2", "barmen", "stay");
	LAi_SetOwnerType(sld);
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	pchar.quest.Terrapin_tibo_call.win_condition.l1 = "Location_Type";
	pchar.quest.Terrapin_tibo_call.win_condition.l1.location_type = "seashore";
	pchar.quest.Terrapin_tibo_call.function = "Terrapin_TiboCall";
	sld = characterFromId("Rober");
	sld.lifeday = 0; // чистим Мартэна
}

void Terrapin_TiboCall(string qName) // засланец от Тибо
{
	chrDisableReloadToLocation = true;//закрыть локацию
	sld = GetCharacter(NPC_GenerateCharacter("Tibo_sailor", "citiz_34", "man", "man", 10, FRANCE, 0, true, "quest"));
	SetFantomParamFromRank(sld, 10, true);
	sld.dialog.FileName = "Quest\Sharlie\Terrapin.c";
	sld.dialog.currentnode = "tibo_sailor";
	sld.greeting = "town_pirate";
	LAi_SetImmortal(sld, true);
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void Terrapin_TiboCallOver(string qName) // опоздали к Тибо
{
	sld = characterFromId("Tibo");
	sld.dialog.currentnode = "tibo_late";
}

void Terrapin_CreateRoberConvoy()//создаем испанский конвой
{
	int iRate = 20+MOD_SKILL_ENEMY_RATE*7;
	int iRank = 25+MOD_SKILL_ENEMY_RATE;
	float fMft = MOD_SKILL_ENEMY_RATE/10;
	string sCapId = "RoberCap";
    string sGroup = "Sea_" + sCapId + "1";
	Group_DeleteGroup(sGroup);
	Group_FindOrCreateGroup(sGroup);
	for (int i = 1; i <= 3; i++)
    {
		sld = GetCharacter(NPC_GenerateCharacter(sCapId + i, "citiz_41", "man", "man", iRank, SPAIN, 22, true, "quest"));
		SetRandomNameToCharacter(sld);
		SetRandomNameToShip(sld);
		switch (i)
		{
			case 1: iTemp = SHIP_GALEON_H; break;
			case 2: iTemp = SHIP_FRIGATE_H; break;
			case 3: iTemp = SHIP_CORVETTE; break;
		}
		sld.Ship.Type = GenerateShipExt(iTemp, 1, sld);
		SetBaseShipData(sld);
		SetCaptanModelByEncType(sld, "war");
		sld.Ship.Mode = "war";
		if (i == 2)
		{
			sld.model = "Marten";
			sld.name = StringFromKey("SharlieFinal_8");
			sld.lastname = StringFromKey("SharlieFinal_9");
			sld.Ship.Mode = "pirate";
			sld.Ship.Name = StringFromKey("SharlieFinal_10");
			FantomMakeCoolFighter(sld, 30, 70, 70, "blade_19", "pistol5", "bullet", 150);
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			GiveItem2Character(sld, "Finger");
			ChangeItemDescribe("Finger", "itmdescr_finger_rober");
		}
		int hcrew = GetMaxCrewQuantity(sld);
		SetCrewQuantity(sld, hcrew);
		SetCrewQuantityFull(sld);
		sld.AlwaysEnemy = true;
		sld.DontRansackCaptain = true;
		sld.AnalizeShips = true;
		sld.skill.Sailing = iRate;
		sld.skill.Defence = iRate;
		sld.skill.Accuracy = iRate;
		sld.skill.Cannons = iRate;
		sld.Ship.Crew.Morale = iRate;
		sld.Ship.Crew.Exp.Sailors = iRate;
		sld.Ship.Crew.Exp.Cannoners = iRate;
		sld.Ship.Crew.Exp.Soldiers = iRate;
		TakeNItems(sld, "potion2", 1);
		TakeNItems(sld, "potion3", 2);
		SetCharacterPerk(sld, "Energaiser");
		SetCharacterPerk(sld, "BasicDefense");
		SetCharacterPerk(sld, "AdvancedDefense");
		SetCharacterPerk(sld, "CriticalHit");
		SetCharacterPerk(sld, "Tireless");
		SetCharacterPerk(sld, "HardHitter");
		SetCharacterPerk(sld, "Sliding");
		SetCharacterPerk(sld, "BladeDancer");
		SetCharacterPerk(sld, "SwordplayProfessional");
		SetCharacterPerk(sld, "Gunman");
		SetCharacterPerk(sld, "GunProfessional");
		SetCharacterPerk(sld, "MusketsShoot");
		SetCharacterPerk(sld, "LongRangeGrappling");
		SetCharacterPerk(sld, "GrapplingProfessional");
		SetCharacterPerk(sld, "HullDamageUp");
		SetCharacterPerk(sld, "SailsDamageUp");
		SetCharacterPerk(sld, "CrewDamageUp");
		SetCharacterPerk(sld, "CriticalShoot");
		SetCharacterPerk(sld, "LongRangeShoot");
		SetCharacterPerk(sld, "BasicBattleState");
		SetCharacterPerk(sld, "AdvancedBattleState");
		SetCharacterPerk(sld, "ShipDefenseProfessional");
		SetCharacterPerk(sld, "ShipSpeedUp");
		SetCharacterPerk(sld, "ShipTurnRateUp");
		SetCharacterPerk(sld, "WindCatcher");
		SetCharacterPerk(sld, "SailsMan");
		SetCharacterPerk(sld, "Doctor1");
		SetCharacterPerk(sld, "Doctor2");
		DeleteAttribute(sld, "SinkTenPercent");
		if (i == 2) SetCharacterGoods(sld, GOOD_ROPES, 50);//бонус
		sld.mapEnc.type = "war";
		sld.mapEnc.worldMapShip = "quest_ship";
        sld.mapEnc.Name = StringFromKey("SharlieFinal_11");
        Group_AddCharacter(sGroup, sCapId + i);
	}
	Group_SetGroupCommander(sGroup, sCapId+ "1");
    Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
    Group_LockTask(sGroup);
	Map_CreateTrader("Caracas", "SantoDomingo", sCapId + "1", 22);//запуск энкаунтера
	
	pchar.quest.Terrapinconvoy_Abordage.win_condition.l1 = "Character_Capture";
	pchar.quest.Terrapinconvoy_Abordage.win_condition.l1.character = "RoberCap2";
	pchar.quest.Terrapinconvoy_Abordage.function = "Terrapinconvoy_AfterBattle";//взяли на абордаж
	pchar.quest.Terrapinconvoy_Sink.win_condition.l1 = "Character_sink";
	pchar.quest.Terrapinconvoy_Sink.win_condition.l1.character = "RoberCap2";
	pchar.quest.Terrapinconvoy_Sink.function = "Terrapinconvoy_AfterBattle";//потопили
	SetFunctionTimerCondition("Terrapinconvoy_failed", 0, 0, 23, false); // упустили
}

void Terrapinconvoy_AfterBattle(string qName)//после боя
{
	DoQuestCheckDelay("sea_victory", 1.5);
	pchar.quest.Terrapinconvoy_failed.over = "yes";
	sld = characterFromId("Tibo");
	if (CheckCharacterItem(pchar, "Finger"))
	{
		sld.dialog.currentnode = "tibo_38";
		AddQuestRecord("Sharlie", "28");
		AddCharacterExpToSkill(pchar, "Grappling", 350);
		AddComplexSelfExpToScill(150, 150, 150, 150);
	}
	else
	{
		sld.dialog.currentnode = "tibo_over";
		AddQuestRecord("Sharlie", "29");
	}
	if (CheckCharacterItem(pchar, "Cromvel_depeshe"))
	{
		// прерывание на эскадру Кромвеля
		pchar.quest.Terrapin_CromvelScuadron.win_condition.l1 = "Timer";
		pchar.quest.Terrapin_CromvelScuadron.win_condition.l1.date.hour  = sti(GetTime());
		pchar.quest.Terrapin_CromvelScuadron.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 397);
		pchar.quest.Terrapin_CromvelScuadron.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 397);
		pchar.quest.Terrapin_CromvelScuadron.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 397);
		pchar.quest.Terrapin_CromvelScuadron.function = "Terrapin_SetCromvelScuadron";
	}
	AddComplexSeaExpToScill(200, 250, 250, 0, 200, 200, 0);
}

void Terrapinconvoy_failed(string qName)//опоздали или не нашли конвой
{
	pchar.quest.Terrapinconvoy_Abordage.over = "yes";
	pchar.quest.Terrapinconvoy_Sink.over = "yes";
	sld = characterFromId("Tibo");
	sld.dialog.currentnode = "tibo_over";
	AddQuestRecord("Sharlie", "30");
}

void Terrapin_LateBaster(string qName)//опоздали к Мартэну в Бас-тер
{
	AddQuestRecord("Terrapin", "16");
	Terrapin_LateDelete();
}

void Terrapin_LateTortuga(string qName)//опоздали на Тортугу
{
	sld = characterFromId("Tibo");
	sld.lifeday = 0;
	AddQuestRecord("Terrapin", "17");
	Terrapin_LateDelete();
}

void Terrapin_LateDungeon(string qName)//опоздали в подземелье
{
	pchar.quest.Terrapin_wait.over = "yes"; //снять прерывание
	pchar.quest.Terrapin_cave.over = "yes"; //снять прерывание
	pchar.quest.Terrapin_ReturnTibo.over = "yes"; //снять прерывание
	sld = characterFromId("Tibo");
	sld.lifeday = 0;
	AddQuestRecord("Terrapin", "18");
	Terrapin_LateDelete();
}

void Terrapin_LateDelete() //общее на все опоздания
{
	sld = characterFromId("Rober");
	sld.lifeday = 0;
	DeleteAttribute(pchar, "questTemp.Terrapin");
	CloseQuestHeader("Terrapin");
	// Левассера - к барьеру!
	sld = characterFromId("Tortuga_Mayor");
	LAi_LoginInCaptureTown(sld, true);
	pchar.questTemp.Sharlie.Hardcore_Tortuga = "true";
}

void Terrapin_SetCromvelScuadron(string qName) //эскадра Кромвеля прибыла
{
	if (CheckCharacterItem(pchar, "Cromvel_depeshe")) RemoveItems(pchar, "Cromvel_depeshe", 1);
	// создаем эскадру
	Group_FindOrCreateGroup("CromvelGroup");
	Group_SetType("CromvelGroup", "war");
	int iRank, iShip, iCannon;
	string sName;
	for (int i=1; i<=5; i++)
	{
		switch (i)
		{
			case 1:
				iShip = SHIP_LSHIP_ENG;
				iCannon = CANNON_TYPE_CULVERINE_LBS36;
				sName = StringFromKey("SharlieFinal_12");
			break;
			
			case 2:
				iShip = SHIP_LINESHIP;
				iCannon = CANNON_TYPE_CANNON_LBS36;
				sName = StringFromKey("SharlieFinal_13");
			break;
			
			case 3:
				iShip = SHIP_FRIGATE_H;
				iCannon = CANNON_TYPE_CANNON_LBS32;
				sName = StringFromKey("SharlieFinal_14");
			break;
			
			case 4:
				iShip = SHIP_FRIGATE;
				iCannon = CANNON_TYPE_CANNON_LBS24;
				sName = StringFromKey("SharlieFinal_15");
			break;
			
			case 5:
				iShip = SHIP_POLACRE;
				iCannon = CANNON_TYPE_CULVERINE_LBS18;
				sName =StringFromKey("SharlieFinal_16");
			break;
		}
		iRank = 20+MOD_SKILL_ENEMY_RATE+(15-i*3);
		sld = GetCharacter(NPC_GenerateCharacter("Cromvel_cap_"+i, "off_eng_"+(7-i), "man", "man", iRank, ENGLAND, 3, true, "quest"));
		FantomMakeCoolSailor(sld, iShip, sName, iCannon, 55+(60-i*12), 55+(60-i*12), 55+(60-i*12));
		FantomMakeCoolFighter(sld, iRank, 52+(60-i*12), 52+(60-i*12), "blade_19", "pistol5", "bullet", 170+(100-i*20));
		sld.DontRansackCaptain = true;
		sld.AnalizeShips = true;
		sld.Ship.Mode = "war";
		sld.AlwaysEnemy = true;
		sld.ship.Crew.Morale = 50+(60-i*12);
		sld.Ship.Crew.Exp.Sailors = 50+(60-i*12);
		sld.Ship.Crew.Exp.Cannoners = 50+(60-i*12);
		sld.Ship.Crew.Exp.Soldiers = 50+(60-i*12);
		if (i < 4) SetCharacterPerk(sld, "MusketsShoot");
		if (i < 5) SetRandGeraldSail(sld, ENGLAND);
		Group_AddCharacter("CromvelGroup", "Cromvel_cap_"+i);
	}
	Group_SetGroupCommander("CromvelGroup", "Cromvel_cap_1");
	Group_SetAddress("CromvelGroup", "IslaMona", "quest_ships", "quest_ship_1");
	Group_SetTaskNone("CromvelGroup"); // 280313
	
	pchar.quest.Ach_TrafalgarA.win_condition.l1 = "Character_Capture";
	pchar.quest.Ach_TrafalgarA.win_condition.l1.character = "Cromvel_cap_1";
	pchar.quest.Ach_TrafalgarA.function = "Ach_TrafalgarA";
	//прерывание на потопление без абордажа
	pchar.quest.Ach_TrafalgarB.win_condition.l1 = "Character_sink";
	pchar.quest.Ach_TrafalgarB.win_condition.l1.character = "Cromvel_cap_1";
	pchar.quest.Ach_TrafalgarB.function = "Ach_TrafalgarB";
	//если не стали связываться
	pchar.quest.Ach_TrafalgarC.win_condition.l1 = "Timer";
	pchar.quest.Ach_TrafalgarC.win_condition.l1.date.hour  = 22;
	pchar.quest.Ach_TrafalgarC.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 5);
	pchar.quest.Ach_TrafalgarC.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 5);
	pchar.quest.Ach_TrafalgarC.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 5);
	pchar.quest.Ach_TrafalgarC.function = "Ach_TrafalgarC";
	
	if(CheckAttribute(pchar,"questTemp.IslaMona.TownStage") && sti(pchar.questTemp.IslaMona.TownStage) > 0)
	{
		pchar.quest.Cromvel_CheckIslaMona.win_condition.l1 = "location";
		pchar.quest.Cromvel_CheckIslaMona.win_condition.l1.location = "IslaMona";
		pchar.quest.Cromvel_CheckIslaMona.function = "CromvelCheckIslaMona";
	}
}

void Ach_TrafalgarA(string qName)
{
	pchar.quest.Ach_TrafalgarB.over = "yes";
	pchar.quest.Ach_TrafalgarC.over = "yes";
	Achievment_Set("ach_CL_109");
}

void Ach_TrafalgarB(string qName)
{
	pchar.quest.Ach_TrafalgarA.over = "yes";
	pchar.quest.Ach_TrafalgarC.over = "yes";
	Achievment_Set("ach_CL_109");
}

void Ach_TrafalgarC(string qName)
{
	pchar.quest.Ach_TrafalgarA.over = "yes";
	pchar.quest.Ach_TrafalgarB.over = "yes";
}

void CromvelCheckIslaMona(string qName) // прерывание на остров
{
	if(Group_isDead("CromvelGroup")) return;
	pchar.quest.Cromvel_CheckW.win_condition.l1 = "Group_Death";
	pchar.quest.Cromvel_CheckW.win_condition.l1.group = "CromvelGroup";
	pchar.quest.Cromvel_CheckW.function = "CromvelDepesha_CheckWin";
	
	pchar.quest.Cromvel_CheckM.win_condition.l1 = "ExitFromSea";
	pchar.quest.Cromvel_CheckM.function = "CromvelDepesha_CheckExit";
}

void CromvelDepesha_CheckWin(string qName) // прибили конвой
{
	pchar.questTemp.RodgarCromvelWin = true;
}

void CromvelDepesha_CheckExit(string qName) // вышли на карту или берег
{
	pchar.quest.Cromvel_CheckW.over = "yes";
}

//----------------------------------------- защита Сен-Пьера --------------------------------------------
void DefendSP_PrepareMartinique(string qName) // готовим Мартинику
{
	int n = FindColony("Fortfrance");
	colonies[n].DontSetShipInPort = true;
	Island_SetReloadEnableGlobal("Martinique", false);//на остров нельзя
	bQuestDisableMapEnter = true;//на карту тоже
	// подменяем файл локаторов на выходе из города
	locations[FindLocation("FortFrance_ExitTown")].models.always.locators = "townExitYQuest_locators";
	// создаем испанскую эскадру
	Group_FindOrCreateGroup("MartiniqueQuestSiege");
	Group_SetType("MartiniqueQuestSiege", "war");
	int iRank, iShip, iCannon, hcrew;
	float fSpace, fDamage;
	string sName;
	for (int i=1; i<=5; i++)
	{
		switch (i)
		{
			case 1:
				iShip = SHIP_LSHIP_SPA;
				iCannon = CANNON_TYPE_CULVERINE_LBS36;
				sName = StringFromKey("SharlieFinal_17");
				fSpace = 1.5;
				fDamage = 1.0;
			break;
			
			case 2:
				iShip = SHIP_CORVETTE;
				iCannon = CANNON_TYPE_CULVERINE_LBS18;
				sName = StringFromKey("SharlieFinal_18");
				fSpace = 2.3;
				fDamage = 1.2;
			break;
			
			case 3:
				iShip = SHIP_GALEON_H;
				iCannon = CANNON_TYPE_CANNON_LBS32;
				sName = StringFromKey("SharlieFinal_19");
				fSpace = 2.0;
				fDamage = 1.3;
			break;
			
			case 4:
				iShip = SHIP_GALEON_L;
				iCannon = CANNON_TYPE_CANNON_LBS20;
				sName = StringFromKey("SharlieFinal_20");
				fSpace = 1.7;
				fDamage = 1.2;
			break;
			
			case 5:
				iShip = SHIP_POLACRE;
				iCannon = CANNON_TYPE_CULVERINE_LBS18;
				sName = StringFromKey("SharlieFinal_21");
				fSpace = 2.1;
				fDamage = 1.3;
			break;
		}
		iRank = 10+2*MOD_SKILL_ENEMY_RATE+(15-i*3);
		sld = GetCharacter(NPC_GenerateCharacter("SPsiege_cap_"+i, "off_spa_"+(7-i), "man", "man", iRank, SPAIN, -1, true, "quest"));
		FantomMakeCoolSailor(sld, iShip, sName, iCannon, 40+(60-i*12), 40+(60-i*12), 40+(60-i*12));
		FantomMakeCoolFighter(sld, iRank, 40+(60-i*12), 40+(60-i*12), "blade_19", "pistol5", "bullet", 70+(100-i*20));
		sld.DontRansackCaptain = true;
		sld.AnalizeShips = true;
		sld.AlwaysEnemy = true;
		sld.Coastal_Captain = true;
		sld.Ship.Mode = "war";
		hcrew = GetMaxCrewQuantity(sld);
		SetCrewQuantityOverMax(sld, sti(hcrew/fSpace));
		sld.ship.HP = makeint(sti(sld.ship.HP)/fDamage);
		sld.ship.Crew.Morale = MOD_SKILL_ENEMY_RATE*5+(60-i*12);
		sld.Ship.Crew.Exp.Sailors = MOD_SKILL_ENEMY_RATE*5+(60-i*12);
		sld.Ship.Crew.Exp.Cannoners = MOD_SKILL_ENEMY_RATE*5+(60-i*12);
		sld.Ship.Crew.Exp.Soldiers = MOD_SKILL_ENEMY_RATE*5+(60-i*12);
		if (i < 4 && MOD_SKILL_ENEMY_RATE > 2) SetCharacterPerk(sld, "MusketsShoot");
		if (i < 5) SetRandGeraldSail(sld, SPAIN);
		Group_AddCharacter("MartiniqueQuestSiege", "SPsiege_cap_"+i);
		Group_SetGroupCommander("MartiniqueQuestSiege", "SPsiege_cap_1");
		Group_SetAddress("MartiniqueQuestSiege", "Martinique", "quest_ships", "quest_ship_1");
		Group_SetTaskNone("MartiniqueQuestSiege");
		//Group_LockTask("MartiniqueQuestSiege");
	}
	DoQuestCheckDelay("DefendSP_VideoSiege", 1.5);
}

void DefendSP_CatchOurSoldiers()
{
	for (int i=0; i<=12; i++)
	{
		if (GetCharacterIndex("DefendSP_soldier_"+i) != -1)
		{
			sld = CharacterFromID("DefendSP_soldier_"+i);
			if (LAi_GetCharacterHP(sld) > 0)
			{
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
		}
	}
}

void DefendSP_OurSoldiersFight()
{
	for (int i=0; i<=12; i++)
	{
		if (GetCharacterIndex("DefendSP_soldier_"+i) != -1)
		{
			sld = CharacterFromID("DefendSP_soldier_"+i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
	}
}

void DefendSP_SpainPatrol(string qName) // ставим испанский патруль в джунглях
{
	// устанавливаем патруль, 4 рыл+офицер+убегающий
	chrDisableReloadToLocation = true;//закрыть локацию
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
	int iRank = 20+MOD_SKILL_ENEMY_RATE*2;
	int iScl = 60;
	for (int i=1; i<=5; i++)
	{
		if (i == 1)
		{
			sld = GetCharacter(NPC_GenerateCharacter("DefendSP_spapatrol_"+i, "off_spa_1", "man", "man", iRank+5, SPAIN, -1, true, "soldier"));
			FantomMakeCoolFighter(sld, iRank+5, iScl+5, iScl+5, "blade_15", "pistol6", "bullet", iScl*2+50);
			sld.dialog.FileName = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "spain_patrol";
			sld.greeting = "patrol";
		}
		else
		{
			if (i == 2)
			{
				sld = GetCharacter(NPC_GenerateCharacter("DefendSP_spapatrol_"+i, "mush_spa_"+i, "man", "mushketer", iRank, SPAIN, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "cartridge", iScl*2);
			}
			else
			{
				sld = GetCharacter(NPC_GenerateCharacter("DefendSP_spapatrol_"+i, "sold_spa_"+i, "man", "man", iRank, SPAIN, -1, true, "soldier"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, RandPhraseSimple("blade_12","blade_14"), "pistol1", "bullet", iScl*2);
			}
			LAi_CharacterDisableDialog(sld);
			if (i == 5) LAi_SetHP(sld, 150, 150); // убегающий
		}
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, "Martinique_jungle_01", "rld", "loc"+i);
		LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
		if (i == 1) LAi_ActorDialogDelay(sld, pchar, "", 1.5);
	}
}

void DefendSP_SpainAvanpost(string qName) // ставим испанцев у ворот
{
	// устанавливаем аванпост испанцев за городскими воротами, 6 солдат, 3 мушкетера, 1 офицер
	chrDisableReloadToLocation = true;//закрыть локацию
	int iRank = 22+MOD_SKILL_ENEMY_RATE*2;
	int iScl = 60;
	int dist = 20;
	float hpm = 1.5;
	string locator = "aloc";
	if (CheckAttribute(pchar, "questTemp.Sharlie.DefendSP.GateAlarm"))
	{
		dist = 0;
		hpm = 1.0;
		locator = "loc";
	}
	for (int i=1; i<=10; i++)
	{
		if (i == 1)
		{
			sld = GetCharacter(NPC_GenerateCharacter("DefendSP_spaavanpost_"+i, "off_spa_1", "man", "man", iRank+5, SPAIN, -1, true, "soldier"));
			FantomMakeCoolFighter(sld, iRank+5, iScl+5, iScl+5, "blade_16", "pistol4", "bullet", iScl*2+50);
		}
		else
		{
			if (i > 1 && i < 5)
			{
				sld = GetCharacter(NPC_GenerateCharacter("DefendSP_spaavanpost_"+i, "mush_spa_"+i, "man", "mushketer", iRank, SPAIN, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket2", "cartridge", iScl*2);
				sld.MusketerDistance = dist;
			}
			else
			{
				sld = GetCharacter(NPC_GenerateCharacter("DefendSP_spaavanpost_"+i, "sold_spa_"+i, "man", "man", iRank+5, SPAIN, -1, true, "soldier"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, RandPhraseSimple("blade_12","blade_14"), "pistol1", "bullet", iScl*2);
			}
		}
		LAi_CharacterDisableDialog(sld);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		ChangeCharacterAddressGroup(sld, "FortFrance_ExitTown", "rld", locator+i);
		int hpl = LAi_GetCharacterHP(sld)/hpm;
		LAi_SetHP(sld, hpl, hpl);
	}
	DefendSP_OurSoldiersFight();
	if (CheckAttribute(pchar, "questTemp.Sharlie.DefendSP.GateAlarm"))
	{
		LAi_SetFightMode(pchar, true);
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "DefendSP_SpaAvanpostDie");
	}
	else DoQuestCheckDelay("DefendSP_SpaAvanpostAttack", 2.0); // застали врасплох
}

void DefendSP_TownBattle(string qName) // городская боевка
{
	for (int i=6; i<=13; i++)
	{
		CreateLocationParticles("smoke", "goto", "goto"+i, 0, 0, 0, "");
	}
	ref chr;
	for(int n = 0; n < MAX_CHARACTERS; n++)
	{
		makeref(chr, Characters[n]);
		if (CheckAttribute(chr, "Merchant") && chr.city == "fortfrance")
		{
			chr.lifeday = 0;
			ChangeCharacterAddressGroup(chr, "none", "", "");
		}
	}
	chr = characterFromId("Fortfrance_Poorman");
	ChangeCharacterAddressGroup(chr, "none", "", "");
	chrDisableReloadToLocation = true;//закрыть локацию
	int iRank = 24+MOD_SKILL_ENEMY_RATE+5;
	int iScl = 60;
	// ставим французов
	for (i=1; i<=8; i++)
	{
		if (i == 1)
		{
			sld = GetCharacter(NPC_GenerateCharacter("DefendSP_fratown_"+i, "off_fra_"+i, "man", "man", iRank+5, FRANCE, 1, true, "soldier"));
			FantomMakeCoolFighter(sld, iRank+5, iScl+5, iScl+5, "blade_15", "pistol6", "bullet", iScl*2+50);
		}
		else
		{
			if (i >= 2 && i < 4)
			{
				sld = GetCharacter(NPC_GenerateCharacter("DefendSP_fratown_"+i, "mush_fra_"+i, "man", "mushketer", iRank, FRANCE, 1, false, "soldier"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "cartridge", iScl*2);
			}
			else
			{
				sld = GetCharacter(NPC_GenerateCharacter("DefendSP_fratown_"+i, "sold_fra_"+i, "man", "man", iRank, FRANCE, 1, true, "soldier"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, RandPhraseSimple("blade_12","blade_14"), "pistol1", "bullet", iScl*2);
			}
		}
		LAi_CharacterDisableDialog(sld);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		ChangeCharacterAddressGroup(sld, "FortFrance_Town", "patrol", "patrol"+i);
	}
	// ставим испанцев
	for (i=1; i<=13+MOD_SKILL_ENEMY_RATE; i++)
	{
		if (i < 3)
		{
			sld = GetCharacter(NPC_GenerateCharacter("DefendSP_spatown_"+i, "off_spa_"+i, "man", "man", iRank+5, SPAIN, -1, true, "soldier"));
			FantomMakeCoolFighter(sld, iRank+5, iScl+5, iScl+5, "blade_16", "pistol4", "bullet", iScl*2+50);
		}
		else
		{
			if (i >= 3 && i < 6)
			{
				sld = GetCharacter(NPC_GenerateCharacter("DefendSP_spatown_"+i, "mush_spa_"+i, "man", "mushketer", iRank, SPAIN, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "cartridge", iScl*2);
			}
			else
			{
				sld = GetCharacter(NPC_GenerateCharacter("DefendSP_spatown_"+i, "sold_spa_"+(rand(15)+1), "man", "man", iRank, SPAIN, -1, true, "soldier"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, RandPhraseSimple("blade_12","blade_14"), "pistol1", "bullet", iScl*2);
			}
		}
		LAi_CharacterDisableDialog(sld);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		ChangeCharacterAddressGroup(sld, "FortFrance_Town", "goto", "goto"+i);
	}
	DefendSP_OurSoldiersFight();
	LAi_SetFightMode(pchar, true);
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "DefendSP_SpaTownDie");
	
	if (CheckAttribute(pchar, "questTemp.Del_DeluckSiditTurma"))	//Фулька убили в тюрьме
	{
		sld = CharacterFromID("Folke");
		LAi_SetActorType(sld);
		LAi_ActorSetLayMode(sld);
		sld.lifeday = 14;
		SaveCurrentNpcQuestDateParam(sld, "LifeTimeCreate");
	}
}

void DefendSP_GotoMatieBase(string qName) // телепорт в базу
{
	DoQuestReloadToLocation("FortFrance_Dungeon", "reload", "reload1", "");
}

void DefendSP_BaseBattle(string qName) // боевка на базе мальтийцев
{
	sld = characterFromId("Mishelle");
	sld.dialog.currentnode = "Base_fight";
	int iRank = 24+MOD_SKILL_ENEMY_RATE*2;
	int iScl = 70;
	// ставим французов
	for (int i=1; i<=7; i++)
	{
		if (i == 1)
		{
			sld = GetCharacter(NPC_GenerateCharacter("DefendSP_frabase_"+i, "off_Malt_1", "man", "man", iRank+5, FRANCE, 1, true, "soldier"));
			FantomMakeCoolFighter(sld, iRank+5, iScl+5, iScl+5, "blade_07", "pistol5", "bullet", iScl*2+50);
		}
		else
		{
			sld = GetCharacter(NPC_GenerateCharacter("DefendSP_frabase_"+i, "sold_fra_"+(rand(7)+9), "man", "man", iRank, FRANCE, 1, true, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, RandPhraseSimple("blade_12","blade_14"), "pistol1", "bullet", iScl*2);
		}
		LAi_CharacterDisableDialog(sld);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		ChangeCharacterAddressGroup(sld, "FortFrance_Dungeon", "goto", "goto"+i);
	}
	// ставим испанцев
	for (i=1; i<=8+MOD_SKILL_ENEMY_RATE/2; i++)
	{
		if (i < 3)
		{
			sld = GetCharacter(NPC_GenerateCharacter("DefendSP_spabase_"+i, "off_spa_"+i, "man", "man", iRank+10, SPAIN, -1, true, "soldier"));
			FantomMakeCoolFighter(sld, iRank+5, iScl+5, iScl+5, "blade_16", "pistol5", "bullet", iScl*2+50);
		}
		else
		{
			sld = GetCharacter(NPC_GenerateCharacter("DefendSP_spabase_"+i, "sold_spa_"+i, "man", "man", iRank, SPAIN, -1, true, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, RandPhraseSimple("blade_12","blade_14"), "pistol1", "bullet", iScl*2);
		}
		LAi_CharacterDisableDialog(sld);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		ChangeCharacterAddressGroup(sld, "FortFrance_Dungeon", "soldiers", "soldier"+i);
	}
	DefendSP_OurSoldiersFight();
	LAi_SetFightMode(pchar, true);
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "DefendSP_SpaBaseDie");
}

void DefendSP_OpenMishelleCasemate()
{	
	if (CheckCharacterItem(pchar, "MaltieBase_keys"))
	{
		PlaySound("interface\key.wav");
		RemoveItems(pchar, "MaltieBase_keys", 1);
		DeleteAttribute(pchar, "questTemp.Sharlie.DefendSP.SeekKey");
		Log_info(StringFromKey("SharlieFinal_22"));
		DoQuestFunctionDelay("DefendSP_MishelleFreedom", 2.0);
	}
	else
	{
		Log_SetStringToLog(XI_ConvertString("Box is closed"));
		PlaySound("interface\door_locked.wav");
	}
}

void DefendSP_MishelleFreedom(string qName)
{
	sld = characterFromId("Mishelle");
	LAi_CharacterEnableDialog(sld);
	sld.dialog.currentnode = "Base_afterfight_6";
	ChangeCharacterAddressGroup(sld, "FortFrance_Dungeon", "quest", "quest5");
	LAi_SetActorType(sld);
	LAi_ActorDialogDelay(sld, pchar, "", 1.0);
}

void DefendSP_CloseTown(string qName) // закрываем входы
{
	chrDisableReloadToLocation = true;//закрыть локацию
	pchar.quest.DefendSP_fort1.win_condition.l1 = "locator";
	pchar.quest.DefendSP_fort1.win_condition.l1.location = "FortFrance_Town";
	pchar.quest.DefendSP_fort1.win_condition.l1.locator_group = "reload";
	pchar.quest.DefendSP_fort1.win_condition.l1.locator = "gate_back";
	pchar.quest.DefendSP_fort1.function = "DefendSP_gotoExittown";
}

void DefendSP_gotoExittown(string qName) // телепорт за ворота
{
	DoQuestReloadToLocation("FortFrance_Exittown", "reload", "reload3", "DefendSP_PrepareFortAttack");
}

void DefendSP_FortBattle(string qName) // входим в фортовую локацию
{
	int iRank = 25+MOD_SKILL_ENEMY_RATE*2;
	int iScl = 70;
	for (int i=1; i<=7; i++)
	{
		sld = characterFromId("Mishelle");
		ChangeCharacterAddressGroup(sld, "FortFrance_fort", "rld", "loc0");
		sld = CharacterFromID("DefendSP_frafort_"+i);
		ChangeCharacterAddressGroup(sld, "FortFrance_fort", "rld", "loc0");
		LAi_SetActorType(sld);
		LAi_ActorFollowEverywhere(sld, "", -1);
	}
	for (i=1; i<=16; i++)
	{
		if (i > 13)
		{
			sld = GetCharacter(NPC_GenerateCharacter("DefendSP_spafort_"+i, "off_spa_"+i, "man", "man", iRank+10, SPAIN, -1, true, "soldier"));
			FantomMakeCoolFighter(sld, iRank+10, iScl+5, iScl+5, "blade_16", "pistol5", "bullet", iScl*2+100);
		}
		else
		{
			if (i >= 3 && i < 7)
			{
				sld = GetCharacter(NPC_GenerateCharacter("DefendSP_spafort_"+i, "mush_spa_"+i, "man", "mushketer", iRank, SPAIN, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "cartridge", iScl*2+20);
				sld.MusketerDistance = 0;
			}
			else
			{
				sld = GetCharacter(NPC_GenerateCharacter("DefendSP_spafort_"+i, "sold_spa_"+i, "man", "man", iRank, SPAIN, -1, true, "soldier"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, RandPhraseSimple("blade_12","blade_14"), "pistol1", "bullet", iScl*2+30);
			}
		}
		LAi_CharacterDisableDialog(sld);
		LAi_SetStayType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		if (i > 13) ChangeCharacterAddressGroup(sld, "FortFrance_fort", "patrol", "patrol0"+(16-i));
		else ChangeCharacterAddressGroup(sld, "FortFrance_fort", "soldiers", "soldier"+i);
	}
	pchar.quest.DefendSP_fort3.win_condition.l1 = "locator";
	pchar.quest.DefendSP_fort3.win_condition.l1.location = "FortFrance_fort";
	pchar.quest.DefendSP_fort3.win_condition.l1.locator_group = "quest";
	pchar.quest.DefendSP_fort3.win_condition.l1.locator = "detector";
	pchar.quest.DefendSP_fort3.function = "DefendSP_FortAttack";
}

void DefendSP_FortAttack(string qName) //атака форта
{
	PlaySound("interface\abordage_wining.wav");
	PlaySound("interface\abordage_wining.wav");
	chrDisableReloadToLocation = true;//закрыть локацию
	sld = characterFromId("Mishelle");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	for (int i=1; i<=7; i++)
	{
		sld = CharacterFromID("DefendSP_frafort_"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	for (i=1; i<=16; i++)
	{
		sld = CharacterFromID("DefendSP_spafort_"+i);
		LAi_SetWarriorTypeNoGroup(sld);
	}
	LAi_SetFightMode(pchar, true);
	DefendSP_OurSoldiersFight();
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "DefendSP_SpaFortDie");
}

void DefendSP_BeforeSeaBattle(string qName) // убираем солдат наших, если остались
{
	for (int i=0; i<=12; i++)
	{
		if (GetCharacterIndex("DefendSP_soldier_"+i) != -1)
		{
			sld = CharacterFromID("DefendSP_soldier_"+i);
			sld.lifeday = 0;
		}
	}
	// переделываем коммандера и форт
	sld = CharacterFromID("FortFrance Fort Commander");
	sld.FaceId = 204;
	sld.name = StringFromKey("SharlieFinal_23");
	sld.lastname = StringFromKey("SharlieFinal_24"); 
	sld.ShipEnemyDisable  = true;
	i = FindIsland("Martinique");
	Islands[i].reload.l2.fort.locators = "Martinique_fort1quest_locators";
}

void DefendSP_SeaBattle(string qName) //бой с испанской эскадрой
{
	Island_SetReloadEnableGlobal("Martinique", true);
	Group_SetAddress("MartiniqueQuestSiege", "Martinique", "quest_ships", "quest_ship_1");
	pchar.quest.DefendSP_sea2.win_condition.l1 = "Group_Death";
	pchar.quest.DefendSP_sea2.win_condition.l1.group = "MartiniqueQuestSiege";
	pchar.quest.DefendSP_sea2.function = "DefendSP_SeaAfterBattle";
}

void DefendSP_SeaAfterBattle(string qName) // уничтожили эскадру
{
	DoQuestCheckDelay("sea_victory", 1.5);
	Group_DeleteGroup("MartiniqueQuestSiege");
	pchar.GenQuest.MapClosedNoBattle = true; // patch
	pchar.quest.DefendSP_sea3.win_condition.l1 = "location";
	pchar.quest.DefendSP_sea3.win_condition.l1.location = "FortFrance_town";
	pchar.quest.DefendSP_sea3.function = "DefendSP_Victory";
	AddQuestRecord("Sharlie", "38");
	AddComplexSeaExpToScill(1000, 1000, 1000, 1000, 1000, 1000, 0);
	ChangeCharacterNationReputation(pchar, SPAIN, -5);
}

void DefendSP_Victory(string qName) // в городе
{
	DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle"); // patch
	LocatorReloadEnterDisable("FortFrance_town", "reload1_back", true);
	LocatorReloadEnterDisable("FortFrance_town", "reload2_back", true);
	LocatorReloadEnterDisable("FortFrance_town", "reload_gate", true);
	sld = characterFromId("Mishelle");
	sld.dialog.currentnode = "Victory";
	ChangeCharacterAddressGroup(sld, "FortFrance_town", "quest", "quest1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void DefendSP_AllClear(string qName) // чистим все по квесту
{
	ref loc;
	for (i=3; i<=10; i++) // открываем заведения
	{
		LocatorReloadEnterDisable("FortFrance_town", "reload"+i+"_back", false);
	}
	sld = characterFromId("FortFrance_usurer");
	ChangeCharacterAddressGroup(sld, "FortFrance_Bank", "barmen", "stay");
	LAi_SetOwnerType(sld);
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS"); // patch-9
	int n = FindColony("Fortfrance");
	DeleteAttribute(colonies[n], "DontSetShipInPort");//ставить корабли
	// переделываем коммандера и форт
	sld = CharacterFromID("FortFrance Fort Commander");
	sld.FaceId = 5;
	sld.name = StringFromKey("SharlieFinal_25");
	sld.lastname = StringFromKey("SharlieFinal_26"); 
	DeleteAttribute(sld, "ShipEnemyDisable");
	n = FindIsland("Martinique");
	Islands[n].reload.l2.fort.locators = "Martinique_fort1_locators";
	// подменяем файл локаторов на выходе из города
	locations[FindLocation("FortFrance_ExitTown")].models.always.locators = "townExitY_locators";
	DeleteAttribute(&locations[FindLocation("FortFrance_Town")], "QuestCapture");
	DeleteAttribute(&locations[FindLocation("FortFrance_Fort")], "QuestCapture");
	DeleteAttribute(&locations[FindLocation("FortFrance_Dungeon")], "QuestCapture");
	sld = characterFromId("Fortfrance_Poorman");
	ChangeCharacterAddressGroup(sld, "FortFrance_Town", "goto", "goto4");
	DeleteAttribute(&locations[FindLocation("FortFrance_Town")], "hidden_fire");
	DeleteAttribute(&locations[FindLocation("FortFrance_Town")], "hidden_sound");
	DeleteAttribute(pchar, "questTemp.Sharlie.DefendSP");
}

void DefendSP_finaltalk(string qName) // разговор с аббатом
{
	pchar.questTemp.Sharlie = "benua_final";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////	
// --------------------------------------- В поисках Стража Истины ------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GuardOT_ExitFrombase(string qName) // вышли из базы
{
	bQuestDisableMapEnter = false;//открыть карту
	sld = characterFromId("spa_baseprisoner");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	AddPassenger(pchar, sld, false);
	SetCharacterRemovable(sld, false);
	pchar.quest.GuardOT_cuba.win_condition.l1 = "location";
	pchar.quest.GuardOT_cuba.win_condition.l1.location = "shore12";
	pchar.quest.GuardOT_cuba.function = "GuardOT_ArriveCuba";
}

void GuardOT_ArriveCuba(string qName) // прибыли в бухту
{
	chrDisableReloadToLocation = true;//закрыть локацию
	sld = characterFromId("spa_baseprisoner");
	sld.dialog.currentnode = "spa_prisoner_32";
	LAi_CharacterEnableDialog(sld);//разрешение диалога
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, "shore12", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void GuardOT_CreateVinsentoAgent(string qName) // пришёл посланец Винсенто
{
	chrDisableReloadToLocation = true;//закрыть локацию
	sld = GetCharacter(NPC_GenerateCharacter("vinsentoagent", "citiz_22", "man", "man", 10, SPAIN, -1, true, "marginal"));
	SetFantomParamFromRank(sld, 10, true);
	sld.dialog.FileName = "Quest\Sharlie\Guardoftruth.c";
	sld.dialog.currentnode = "vinsentoagent";
	RemoveAllCharacterItems(sld, true);
	LAi_SetStayType(sld);
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, "mayak9", "goto", LAi_FindFarFreeLocator("goto", locx, locy, locz));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void GuardOT_VinsentoLetterRead() // прочли письмо Винсенто
{
	AddQuestRecord("Guardoftruth", "6");
	pchar.questTemp.Guardoftruth = "portprince";
	sld = characterFromId("Santiago_Lightman");
	pchar.questTemp.Guardoftruth.LMname = GetFullName(sld); // имя смотрителя
}

void GuardOT_CreateTwoShips(string qName) // создаем галеон Гая и каракку торговца
{
	// галеон Гая Марше
	Group_FindOrCreateGroup("Marshe_group");
	Group_SetType("Marshe_group", "trade");//тип группы
	sld = GetCharacter(NPC_GenerateCharacter("GOT_boatsvanDega", "mercen_3", "man", "man", 15, FRANCE, -1, true, "soldier"));
	FantomMakeCoolSailor(sld, SHIP_GALEON_L, StringFromKey("SharlieFinal_27"), CANNON_TYPE_CANNON_LBS16, 50, 50, 50);
	SetFantomParamFromRank(sld, 15, true);
	sld.name = StringFromKey("SharlieFinal_28");
	sld.lastname = StringFromKey("SharlieFinal_29");
	sld.greeting = "captain";
	sld.Dialog.Filename = "Quest\Sharlie\Guardoftruth.c";
	sld.DeckDialogNode = "boatsvandega";
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.Ship.Mode = "trade";
	RealShips[sti(sld.Ship.Type)].ship.upgrades.sails = 9;
	// грузим ваниль
	int iSpace = GetCharacterFreeSpace(sld, GOOD_CINNAMON);
	Fantom_SetCharacterGoods(sld, GOOD_CINNAMON, iSpace, 1);
	pchar.questTemp.Guardoftruth.VanilleQty = iSpace; // запомним
	// защита от дурака
	sld.AlwaysFriend = true;
	sld.ShipEnemyDisable  = true; //не обижаться на выстрелы
	LAi_SetImmortal(sld, true);
	Group_AddCharacter("Marshe_group", "GOT_boatsvanDega");
	Group_SetGroupCommander("Marshe_group", "GOT_boatsvanDega");
	Group_SetTaskNone("Marshe_group");
	Group_SetAddress("Marshe_group", "Guadeloupe", "quest_ships", "quest_ship_1");
	Group_LockTask("Marshe_group");
	
	// бригантина испанского торговца под голландским флагом
	Group_FindOrCreateGroup("Gevarra_group");
	Group_SetType("Gevarra_group", "trade");//тип группы
	sld = GetCharacter(NPC_GenerateCharacter("GOT_Gevarra", "trader_5", "man", "man", 15, HOLLAND, -1, true, "soldier"));
	FantomMakeCoolSailor(sld, SHIP_BRIGANTINE, StringFromKey("SharlieFinal_30"), CANNON_TYPE_CANNON_LBS12, 50, 50, 50);
	SetFantomParamFromRank(sld, 15, true);
	sld.name = StringFromKey("SharlieFinal_31");
	sld.lastname = StringFromKey("SharlieFinal_32");
	sld.greeting = "captain";
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.Ship.Mode = "trade";
	// защита от дурака
	sld.AlwaysFriend = true;
	sld.ShipEnemyDisable  = true; //не обижаться на выстрелы
	LAi_SetImmortal(sld, true);
	Group_AddCharacter("Gevarra_group", "GOT_Gevarra");
	Group_SetGroupCommander("Gevarra_group", "GOT_Gevarra");
	Group_SetTaskNone("Gevarra_group");
	Group_SetAddress("Gevarra_group", "Guadeloupe", "quest_ships", "quest_ship_2");
	Group_LockTask("Gevarra_group");
	// сажаем Марше в таверну
	sld = GetCharacter(NPC_GenerateCharacter("GOT_Marshe", "GayMarshe", "man", "man", 30, FRANCE, -1, true, "soldier"));
	SetFantomParamFromRank(sld, 30, true);
	sld.name = StringFromKey("SharlieFinal_33");
	sld.lastname = StringFromKey("SharlieFinal_34");
	sld.dialog.FileName = "Quest\Sharlie\Guardoftruth.c";
	sld.dialog.currentnode = "marshe_tavern";
	LAi_SetLoginTime(sld, 7.0, 21.0);
	LAi_SetSitType(sld);
	LAi_SetImmortal(sld, true);
	FreeSitLocator("baster_tavern", "sit2");
	ChangeCharacterAddressGroup(sld, "baster_tavern", "sit", "sit2");
	// ваниль в магазине
	pchar.GenQuest.StoreGoods.StoreIdx = Baster_STORE;
	pchar.GenQuest.StoreGoods.Guardoftruth = true;
	// даем подсказку
	AddQuestRecord("Guardoftruth", "15");
}

void GuardOT_PrepareTrade(string qName) //
{
	sld = characterFromId("GOT_Gevarra");
	sld.DeckDialogNode = "gevarra_16";
}

void GuardOT_TradeComplete(string qName) // типо поторговали - насильно телепортируем ГГ на пляж Капстер
{
	DoQuestFunctionDelay("GuardOT_TradeCompleteNext", 2.0);
}

void GuardOT_TradeCompleteNext(string qName) // типо поторговали - насильно телепортируем ГГ на пляж Капстер
{
	pchar.quest.GuardOT_gotoshore.over = "yes"; //снять прерывание
	pchar.quest.GuardOT_gotoshore1.over = "yes"; //снять прерывание
	// ориентируем на вечер
	int iTime, iAddTime;
	iTime = sti(environment.time);
	if (iTime >= 21) iAddTime = 24 - iTime + 21;
	if (iTime < 7) iAddTime = 21 - iTime;
	if (iTime >= 7 && iTime < 21) iAddTime = 24  + 21 - iTime;
	SetLaunchFrameFormParam(StringFromKey("SharlieFinal_35", NewStr()), "", 0, 5);
	LaunchFrameForm();
	StoreDayUpdate();
	WaitDate("",0,0,1,iAddtime,5);
	RecalculateJumpTable();
	RefreshWeather();
	RefreshLandTime();
	DoQuestFunctionDelay("GuardOT_GotoBeach", 5.0);
	// совершаем перестановки
	sld = characterFromId("GOT_Marshe");
	LAi_RemoveLoginTime(sld);
	ChangeCharacterAddressGroup(sld, "none", "", "");
	sld = characterFromId("GOT_boatsvanDega");
	sld.DontDeskTalk = true;
	sld.name = StringFromKey("SharlieFinal_33");
	sld.lastname = StringFromKey("SharlieFinal_34");
	sld.FaceId = 44;
	SetCrewQuantityOverMax(sld, 30);
	RemoveCharacterGoods(pchar, GOOD_CINNAMON, sti(pchar.questTemp.Guardoftruth.VanilleQty));
	sld = characterFromId("GOT_Gevarra");
	sld.lifeday = 0;
	Group_DeleteGroup("Gevarra_group");
}

void GuardOT_GotoBeach(string qName) // телепорт
{
	LocatorReloadEnterDisable("Shore29", "boat", true);
	DoQuestReloadToLocation("Shore29", "reload", "sea", "GuardOT_ArriveBeach");
	setCharacterShipLocation(pchar, "Shore29"));
	setWDMPointXZ("Shore29");
	pchar.questTemp.Guardoftruth = "shore";
}

void GuardOT_EnterInTown(string qName) // пришли в город
{
	chrDisableReloadToLocation = true;//закрыть локацию
	// запустим матросиков гулять
	for (int i=1; i<=15; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("marshe_sailor_"+i, "citiz_"+(rand(9)+31), "man", "man", 10, FRANCE, 1, true, "soldier"));
		SetFantomParamFromRank(sld, 10, true);
		sld.dialog.FileName = "Quest\Sharlie\Guardoftruth.c";
		sld.dialog.currentnode = "marshe_sailor";
		sld.greeting = "habitue";
		LAi_SetWarriorType(sld);
		LAi_warrior_DialogEnable(sld, true);
		ChangeCharacterAddressGroup(sld, "Baster_town", "goto", "goto"+i);
		LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	}
	DoQuestFunctionDelay("GuardOT_ManyDrunkSailors", 5.0);
}

void GuardOT_ManyDrunkSailors(string qName) // увидели все это безобразие
{
	chrDisableReloadToLocation = false;
	DeleteAttribute(&locations[FindLocation("Deck_Galeon_Ship")], "boarding");
	AddQuestRecord("Guardoftruth", "19");
	pchar.quest.GuardOT_marchtogaleon.win_condition.l1 = "locator";
	pchar.quest.GuardOT_marchtogaleon.win_condition.l1.location = "shore29";
	pchar.quest.GuardOT_marchtogaleon.win_condition.l1.locator_group = "reload";
	pchar.quest.GuardOT_marchtogaleon.win_condition.l1.locator = "boat";
	pchar.quest.GuardOT_marchtogaleon.function = "GuardOT_GotoGaleon";
	// заполним сундуки
	pchar.GenQuestBox.Deck_Galeon_Ship = true;
	pchar.GenQuestBox.Deck_Galeon_Ship.box1.money = 5221;
	pchar.GenQuestBox.Deck_Galeon_Ship.box1.items.gold_dublon = 28;
	pchar.GenQuestBox.Deck_Galeon_Ship.box1.items.chest_open = 6;
	pchar.GenQuestBox.Deck_Galeon_Ship.box1.items.chest = 1;
	pchar.GenQuestBox.Deck_Galeon_Ship.box2.items.totem_02 = 1;
	pchar.GenQuestBox.Deck_Galeon_Ship.box2.items.purse3 = 1;
	pchar.GenQuestBox.Deck_Galeon_Ship.box2.items.jewelry52 = 20;
	pchar.GenQuestBox.Deck_Galeon_Ship.box2.items.map_hisp = 1;
	pchar.GenQuestBox.Deck_Galeon_Ship.box3.money = 100000;
	pchar.GenQuestBox.Deck_Galeon_Ship.box3.items.obereg_8 = 1;
	pchar.GenQuestBox.Deck_Galeon_Ship.box3.items.jewelry14 = 2;
	pchar.GenQuestBox.Deck_Galeon_Ship.box3.items.jewelry21 = 3;
	pchar.GenQuestBox.Deck_Galeon_Ship.box3.items.potion7 = 1;
}

void GuardOT_GotoGaleon(string qName) // телепортируем на галеон
{
	for (int i=1; i<=20; i++)
	{
		if (GetCharacterIndex("caleuche_pcrew_"+i) != -1)
		{
			sld = characterFromId("caleuche_pcrew_"+i);
			sld.lifeday = 0;
		}
	} // предохранительный клапан
	LAi_LocationDisableOfficersGen("Deck_Galeon_Ship", false);
	DoQuestReloadToLocation("Deck_Galeon_Ship", "reload", "reload2", "GuardOT_ArriveGaleon");
}

void GuardOT_KickGuard(string qName) // тюк!
{
	int num = sti(pchar.questTemp.Guardoftruth.num);
	LAi_SetPlayerType(pchar);
	CreateLocationParticles("blood_big", "item", "kick"+num, 2.0, 0, 0, "");
	PlaySound("People\jump.wav");
	PlaySound("People Fight\Damage_NPC_0"+(rand(2)+4)+".wav");
	sld = characterFromId("GuardOT_galeonguard_"+num);
	LAi_RemoveCheckMinHP(sld);
	LAi_KillCharacter(sld);
	AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
	AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
}

void GuardOT_GaleonGuardFightAdd() // выбежала подмога
{
	PlaySound("interface\abordage_wining.wav");
	PlaySound("interface\abordage_wining.wav");
	int iRank = 25+MOD_SKILL_ENEMY_RATE*2;
	int iScl = 65;
	for (int i=1; i<=8; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("GuardOT_galeonguardadd_"+i, "citiz_"+(rand(9)+31), "man", "man", iRank, PIRATE, -1, true, "soldier"));
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_12", "pistol1", "bullet", iScl*2+50);
		ChangeCharacterAddressGroup(sld, "Deck_Galeon_Ship", "reload", "reload1");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "GaleonFight");
	}
	sld = GetCharacter(NPC_GenerateCharacter("GuardOT_galeonguardaddmush", "mush_ctz_"+(4+rand(2)), "man", "mushketer", iRank, PIRATE, -1, false, "soldier"));
	FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "cartridge", iScl*2+50);
	sld.MusketerDistance = 0;
	ChangeCharacterAddressGroup(sld, "Deck_Galeon_Ship", "goto", "mush");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "GaleonFight");
}

void GuardOT_ExitGaleon(string qName) // вышли с галеона
{
	Island_SetReloadEnableGlobal("Guadeloupe", false);
	SetFunctionTimerCondition("GuardOT_GuadeloupeOpen", 0, 0, 2, false); // таймер
	LocatorReloadEnterDisable("Shore29", "boat", false);
	DoQuestReloadToLocation("shore29", "reload", "sea", "OpenTheDoors");
	DeleteAttribute(pchar, "GenQuest.Notsearchbody");
	DeleteAttribute(pchar, "GenQuest.CannotWait");
	InterfaceStates.Buttons.Save.enable = true;
	bQuestDisableMapEnter = false;
	DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
	sld = characterFromId("GOT_Marshe");
	DeleteAttribute(sld, "LifeDay");
	AddPassenger(pchar, sld, false);
	SetCharacterRemovable(sld, false);
	pchar.questTemp.Guardoftruth = "gotomayak";
	sld = characterFromId("GOT_boatsvanDega");
	sld.name = "";
	sld.lastname = "";
	sld.FaceId = 333;
	sld.lifeday = 1;
	AddQuestRecord("Guardoftruth", "20");
	pchar.quest.GuardOT_arrive_tomayak.win_condition.l1 = "Ship_location";
	pchar.quest.GuardOT_arrive_tomayak.win_condition.l1.location = "mayak9";
	pchar.quest.GuardOT_arrive_tomayak.function = "GuardOT_ArriveToMayak";
}

void GuardOT_GuadeloupeOpen(string qName) // открываем остров
{
	Island_SetReloadEnableGlobal("Guadeloupe", true);
}

void GuardOT_ArriveToMayak(string qName) // прибыли на маяк
{
	Group_DeleteGroup("Marshe_group"); // patch
	LocatorReloadEnterDisable("mayak9", "boat", true);
	sld = characterFromId("GOT_Marshe");
	RemovePassenger(pchar, sld);
	LAi_SetActorType(sld);
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, "mayak9", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_ActorFollowEverywhere(sld, "", -1);
	pchar.questTemp.Guardoftruth = "mayak";
}

void GuardOT_MayakNextStage(string qName) // идем за письмом
{
	pchar.questTemp.Guardoftruth = "mayak_next";
}

void GuardOT_VinsentoNextLetterRead() // прочли письмо Винсенто
{
	pchar.questTemp.Guardoftruth = "utensil";
	AddQuestRecord("Guardoftruth", "22");
}

void GuardOT_DominicaChest(string qName) // нашли сундук в бухте
{
	chrDisableReloadToLocation = true;//закрыть локацию
	string sTemp;
	if (pchar.location.from_sea == "shore27") sTemp = "boat";
	else sTemp = "reload2_back";
	pchar.quest.GuardOT_createhunters.win_condition.l1 = "locator";
	pchar.quest.GuardOT_createhunters.win_condition.l1.location = "shore27";
	pchar.quest.GuardOT_createhunters.win_condition.l1.locator_group = "reload";
	pchar.quest.GuardOT_createhunters.win_condition.l1.locator = sTemp;
	pchar.quest.GuardOT_createhunters.function = "GuardOT_CreateDominicaHunters";
	AddQuestRecord("Guardoftruth", "25");
	AddCharacterExpToSkill(pchar, "Fortune", 300);
}

void GuardOT_CreateDominicaHunters(string qName) // 
{
	DoQuestCheckDelay("hide_weapon", 1.0); // patch-9
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
	int iRank = 20+MOD_SKILL_ENEMY_RATE*2;
	int iScl = 50;
	for (i=1; i<=8; i++)
	{
		if (i == 1)
		{
			sld = GetCharacter(NPC_GenerateCharacter("GuardOT_DH_"+i, "off_eng_"+i, "man", "man", iRank+5, ENGLAND, -1, true, "soldier"));
			FantomMakeCoolFighter(sld, iRank+5, iScl+5, iScl+5, "blade_13", "pistol4", "bullet", iScl*2);
			sld.Dialog.Filename = "Quest\Sharlie\Guardoftruth.c";
			sld.dialog.currentnode = "dominica_hunter";
		}
		else
		{
			if (i >= 2 && i < 4)
			{
				sld = GetCharacter(NPC_GenerateCharacter("GuardOT_DH_"+i, "mush_eng_"+i, "man", "mushketer", iRank, ENGLAND, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "bullet", iScl*2);
			}
			else
			{
				sld = GetCharacter(NPC_GenerateCharacter("GuardOT_DH_"+i, "sold_eng_"+i, "man", "man", iRank, ENGLAND, -1, true, "soldier"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, RandPhraseSimple("blade_12","blade_14"), "pistol1", "bullet", iScl*2);
			}
			LAi_CharacterDisableDialog(sld);
		}
		LAi_SetWarriorType(sld);
		ChangeCharacterAddressGroup(sld, "shore27", "quest", "LLquest1");
	}
	sld = characterFromId("GuardOT_DH_1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void GuardOT_FadeyTimer(string qName) // 
{
	pchar.questTemp.Guardoftruth.Baster_church = "find";
}

void GuardOT_InCaveEntrance(string qName) // ставим встречающего
{
	chrDisableReloadToLocation = true;//закрыть локацию
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
	locations[FindLocation("Cumana_Cave")].DisableEncounters = true; // patch
	int iRank = 25+MOD_SKILL_ENEMY_RATE*2;
	int iScl = 65;
	sld = GetCharacter(NPC_GenerateCharacter("GOT_bandos_0", "mush_ctz_9", "man", "mushketer", iRank, PIRATE, -1, true, "marginal"));
	FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "cartridge", iScl*2);
	sld.dialog.FileName = "Quest\Sharlie\Guardoftruth.c";
	sld.dialog.currentnode = "bandos_mush";
	ChangeCharacterAddressGroup(sld, "Cumana_CaveEntrance", "monsters", "monster1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void GuardOT_InCumanaCave(string qName) // 
{
	WaitDate("", 0, 0, 0, 1, 10); //fix 080812
	chrDisableReloadToLocation = true;//закрыть локацию
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
	int iRank = 20+MOD_SKILL_ENEMY_RATE*2;
	int iScl = 50;
	sld = GetCharacter(NPC_GenerateCharacter("GOT_Bart", "mercen_21", "man", "man", iRank, PIRATE, -1, true, "marginal"));
	FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_07", "pistol1", "bullet", iScl*2);
	sld.dialog.FileName = "Quest\Sharlie\Guardoftruth.c";
	sld.dialog.currentnode = "barty";
	sld.name = StringFromKey("SharlieFinal_36");
	sld.lastname = StringFromKey("SharlieFinal_37");
	sld.LSC_clan = true;
	LAi_SetCheckMinHP(sld, 10, true, "GuardOT_BartyEscape");
	LAi_SetStayType(sld);
	ChangeCharacterAddressGroup(sld, "Cumana_Cave", "quest", "quest0");
	for (i=1; i<=2; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("GOT_bandos_"+i, "citiz_4"+i, "man", "man", iRank, PIRATE, -1, true, "marginal"));
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_07", "pistol1", "bullet", iScl*2);
		sld.LSC_clan = true;
		LAi_CharacterDisableDialog(sld);
		LAi_SetStayType(sld);
		ChangeCharacterAddressGroup(sld, "Cumana_Cave", "quest", "quest"+i);
	}
}

void GuardOT_InCumanaCaveEnemyAdd() // добавляем противников
{
	int iRank = 20+MOD_SKILL_ENEMY_RATE*2;
	int iScl = 50;
	for (int i=3; i<=4; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("GOT_bandos_"+i, "citiz_4"+i, "man", "man", iRank, PIRATE, -1, true, "marginal"));
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_07", "pistol1", "bullet", iScl*2);
		sld.LSC_clan = true;
		LAi_CharacterDisableDialog(sld);
		LAi_SetWarriorType(sld);
		ChangeCharacterAddressGroup(sld, "Cumana_Cave", "monsters", "monster"+(i+3));
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	sld = characterFromId("GOT_bandos_0");
	sld.MusketerDistance = 0;
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	ChangeCharacterAddressGroup(sld, "Cumana_Cave", "monsters", "monster1");
}

void GuardOT_SetOfficerCumanaCave(string qName) //
{
	for(int i=1; i<=3; i++)
	{
		int idx = GetOfficersIndex(pchar, i);
		if(idx < 0) continue;
		sld = &Characters[idx];
		ChangeCharacterAddressGroup(sld, "Cumana_Cave", "reload", "reload2");
	}
}

void GuardOT_MayakLastStage(string qName) // 
{
	pchar.questTemp.Guardoftruth = "inquisition";
}

void GuardOT_SetPadreVincento() // ставим отца Винсенто
{
	LAi_LocationFightDisable(&Locations[FindLocation("Santiago_Incquisitio")], true);//запретим шалить
	sld = GetCharacter(NPC_GenerateCharacter("Vincento", "vincento", "man", "man_B", 35, SPAIN, -1, true, "quest"));
	SetFantomParamFromRank(sld, 35, true);
	sld.name = StringFromKey("SharlieFinal_38");
	sld.lastname = StringFromKey("SharlieFinal_39");
	sld.dialog.FileName = "Quest\Sharlie\Vincento.c";
	sld.dialog.currentnode = "First time";
	sld.greeting = "vincento_1";
	RemoveAllCharacterItems(sld, true);
	LAi_SetHuberType(sld);
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, "Santiago_Incquisitio", "sit", "armchair1");
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
}

void GuardOT_SetDiegoOnMayak(string qName) // ставим Диего
{
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
	chrDisableReloadToLocation = true;//закрыть локацию
	// Диего, косит под офицера патруля
	sld = characterFromId("Diego");
	sld.name = StringFromKey("SharlieFinal_40");
	sld.lastname = StringFromKey("SharlieFinal_41");
	sld.dialog.FileName = "Quest\Sharlie\Diego.c";
	sld.dialog.currentnode = "patrol";
	sld.greeting = "patrol";
	LAi_SetImmortal(sld, true);
	LAi_SetActorType(sld);
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, "mayak1", "goto", LAi_FindFarFreeLocator("goto", locx, locy, locz));
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	// сопровождение
	for(int i=1; i<=3; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("GOT_spamayaksold_"+i, "sold_spa_"+i, "man", "man", 35, SPAIN, -1, true, "soldier"));
		FantomMakeCoolFighter(sld, 35, 100, 100, "blade_13", "pistol1", "bullet", 100);
		LAi_CharacterDisableDialog(sld);
		LAi_SetActorType(sld);
		GetCharacterPos(pchar, &locx, &locy, &locz);
		ChangeCharacterAddressGroup(sld, "mayak1", "goto", LAi_FindFarFreeLocator("goto", locx, locy, locz));
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
}

void GuardOT_SetSpaOfficerInTown(string qName) // ставим знакомца-офицера
{
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
	chrDisableReloadToLocation = true;//закрыть локацию
	sld = characterFromId("spa_baseprisoner");
	sld.model = "q_spa_off_2";
	Characters_RefreshModel(sld);
	sld.dialog.currentnode = "spa_prisoner_39";
	GiveItem2Character(sld, "blade_13");
	sld.equip.blade = "blade_13";
	GiveItem2Character(sld, "pistol4");
	EquipCharacterbyItem(sld, "pistol4");
	TakeNItems(sld, "bullet", 50);
	TakeNItems(sld, "gunpowder", 50);
	TakeNItems(sld, "potion2", 10);
	LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
	LAi_SetActorType(sld);
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, "Santiago_town", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void GuardOT_SetBandosInTown(string qName) // напали бандосы
{
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
	chrDisableReloadToLocation = true;//закрыть локацию
	int iRank = 25+MOD_SKILL_ENEMY_RATE*2;
	int iScl = 55;
	for(int i=1; i<=5; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("GOT_santiagoband_"+i, "citiz_58", "man", "man", iRank, SPAIN, -1, true, "soldier"));
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_06", "pistol5", "bullet", iScl*2);
		sld.Dialog.Filename = "Quest\Sharlie\guardoftruth.c";
		sld.Dialog.currentnode = "spa_hunter";
		sld.greeting = "hunter";
		if (i != 1) LAi_CharacterDisableDialog(sld);
		LAi_SetActorType(sld);
		GetCharacterPos(pchar, &locx, &locy, &locz);
		ChangeCharacterAddressGroup(sld, "Santiago_town", "goto", LAi_FindFarFreeLocator("goto", locx, locy, locz));
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
}

void GuardOT_Cuba2Arrive(string qName) // вышли у Гаваны
{
	bQuestDisableMapEnter = true;//закрыть карту
	pchar.GenQuest.MapClosedNoBattle = true;
	AddQuestRecord("Guardoftruth", "46");
	pchar.quest.GuardOT_Batabano.win_condition.l1 = "location";
	pchar.quest.GuardOT_Batabano.win_condition.l1.location = "Shore13";
	pchar.quest.GuardOT_Batabano.function = "GuardOT_BatabanoArrive";
}

void GuardOT_BatabanoArrive(string qName) // в заливе Батабано
{
	LocatorReloadEnterDisable("Shore13", "boat", true);
	sld = CharacterFromID("Havana_tavernkeeper");
	sld.quest.batabano = true;
}

void GuardOT_SanAntonioPrepare(string qName) // ставим абордажную роту
{
	chrDisableReloadToLocation = true;//закрыть локацию
	pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу
	// устанавливаем солдат ГГ, 9 рыл+офицер
	int iRank = 25+MOD_SKILL_ENEMY_RATE+5;
	int iScl = 60;
	for (int i=1; i<=10; i++)
	{
		if (i == 1)
		{
			sld = GetCharacter(NPC_GenerateCharacter("GuardOT_Oursoldier_"+i, "mercen_25", "man", "man", iRank+5, FRANCE, -1, true, "soldier"));
			FantomMakeCoolFighter(sld, iRank+5, iScl+5, iScl+5, "blade_13", "pistol4", "bullet", iScl*2+50);
			sld.dialog.FileName = "Quest\Sharlie\guardoftruth.c";
			sld.dialog.currentnode = "batabano_officer";
		}
		else
		{
			if (i == 2 || i == 3)
			{
				sld = GetCharacter(NPC_GenerateCharacter("GuardOT_Oursoldier_"+i, "mush_ctz_"+(4+rand(2)), "man", "mushketer", iRank, FRANCE, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "cartridge", iScl*2);
			}
			else
			{
				sld = GetCharacter(NPC_GenerateCharacter("GuardOT_Oursoldier_"+i, "citiz_"+(31+rand(9)), "man", "man", iRank, FRANCE, -1, true, "soldier"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, RandPhraseSimple("blade_10","blade_11"), "pistol1", "bullet", iScl*2);
			}
			LAi_CharacterDisableDialog(sld);
		}
		ChangeCharacterAddressGroup(sld, "Shore13", "reload", "sea");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
}

void GuardOT_SanAntonio_Timer(string qName) // метка на время
{
	pchar.questTemp.Guardoftruth.SanAntonio = "true";
}

void GuardOT_SanantonioArrive(string qName) // высадка на мыс
{
	DoQuestFunctionDelay("GuardOT_CreateDiegoShoreGuard", 2.0);
}

void GuardOT_CreateDiegoShoreGuard(string qName) // гишпанцы вылезли из кустов
{
	LAi_SetActorType(pchar);
	LAi_ActorTurnToLocator(pchar, "rld", "loc3");
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
	chrDisableReloadToLocation = true;//закрыть локацию
	// ставим испанцев
	int iRank = 25+MOD_SKILL_ENEMY_RATE*2;
	int iScl = 60;
	for (int i=1; i<=13; i++)
	{
		if (i == 1)
		{
			sld = GetCharacter(NPC_GenerateCharacter("GOT_spashore_"+i, "off_spa_"+i, "man", "man", iRank+5, SPAIN, -1, true, "soldier"));
			FantomMakeCoolFighter(sld, iRank+5, iScl+5, iScl+5, "blade_16", "pistol4", "bullet", iScl*2+50);
			ChangeCharacterAddressGroup(sld, "Shore15", "quest", "quest2");
		}
		else
		{
			if (i >= 2 && i < 6)
			{
				sld = GetCharacter(NPC_GenerateCharacter("GOT_spashore_"+i, "mush_spa_"+i, "man", "mushketer", iRank, SPAIN, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "cartridge", iScl*2);
				ChangeCharacterAddressGroup(sld, "Shore15", "quest", "quest1");
			}
			else
			{
				sld = GetCharacter(NPC_GenerateCharacter("GOT_spashore_"+i, "sold_spa_"+i, "man", "man", iRank, SPAIN, -1, true, "soldier"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, RandPhraseSimple("blade_12","blade_14"), "pistol1", "bullet", iScl*2);
				ChangeCharacterAddressGroup(sld, "Shore15", "reload", "reload1");
			}
		}
		LAi_SetActorType(sld);
		LAi_ActorRunToLocator(sld, "rld", "loc"+i, "", -1);
		DoQuestCheckDelay("GuardOT_DiegoShoreGuardReady", 5.0);
	}
	pchar.GenQuest.SeaHunter2Pause = true;
    SeaHunter_Delete();
}

void GuardOT_CreateDiegoShips(string qName) //
{
	// убираем за собой
	for (i=1; i<=10; i++)
	{
		if (GetCharacterIndex("GuardOT_Oursoldier_"+i) != -1)
		{
			sld = CharacterFromID("GuardOT_Oursoldier_"+i);
			sld.lifeday = 0;
		}
	}
	LocatorReloadEnterDisable("shore15", "reload1_back", false);
	Island_SetReloadEnableGlobal("Cuba2", false);//на остров нельзя
	Group_FindOrCreateGroup("Diegohaleon_group");
	Group_SetType("Diegohaleon_group", "war");//тип группы
	sld = GetCharacter(NPC_GenerateCharacter("Diegohaleon_cap", "off_spa_2", "man", "man", 35, SPAIN, -1, true, "quest"));
	FantomMakeCoolSailor(sld, SHIP_GALEON_H, StringFromKey("SharlieFinal_42"), CANNON_TYPE_CANNON_LBS36, 80, 80, 80);
	FantomMakeCoolFighter(sld, 35, 80, 80, "blade_15", "pistol5", "bullet", 150);
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.Ship.Mode = "war";
	sld.alwaysEnemy = true;
	sld.Coastal_Captain = true;
	sld.ship.Crew.Morale = MOD_SKILL_ENEMY_RATE*10;
	sld.Ship.Crew.Exp.Sailors = MOD_SKILL_ENEMY_RATE*10;
	sld.Ship.Crew.Exp.Cannoners = MOD_SKILL_ENEMY_RATE*10;
	sld.Ship.Crew.Exp.Soldiers = MOD_SKILL_ENEMY_RATE*10;
	if (MOD_SKILL_ENEMY_RATE > 4) SetCharacterPerk(sld, "MusketsShoot");
	Group_AddCharacter("Diegohaleon_group", "Diegohaleon_cap");
	Group_SetGroupCommander("Diegohaleon_group", "Diegohaleon_cap");
	Group_SetTaskAttack("Diegohaleon_group", PLAYER_GROUP);
	Group_SetAddress("Diegohaleon_group", "Cuba2", "quest_ships", "quest_ship_5");
	Group_LockTask("Diegohaleon_group");
	
	pchar.quest.GuardOT_diegoGaleondie.win_condition.l1 = "Group_Death";
	pchar.quest.GuardOT_diegoGaleondie.win_condition.l1.group = "Diegohaleon_group";
	pchar.quest.GuardOT_diegoGaleondie.function = "GuardOT_DiegoGaleonAfterBattle";
}

void GuardOT_DiegoGaleonAfterBattle(string qName)
{
	DoQuestCheckDelay("sea_victory", 1.5);
	Group_DeleteGroup("Diegohaleon_group");
	bQuestDisableMapEnter = false;
	DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
	AddQuestRecord("Guardoftruth", "50");
	GuardOT_CreateDiegoLuggerInWorld();
	pchar.quest.GuardOT_diegoluggerstart.win_condition.l1 = "MapEnter";
	pchar.quest.GuardOT_diegoluggerstart.function = "GuardOT_LuggerClear";
	AddComplexSeaExpToScill(150, 150, 150, 150, 150, 150, 0);
	pchar.quest.Map_SetNationCoolHanters.over = "yes";
}

void GuardOT_LuggerClear(string qName)
{
	pchar.nation = FRANCE; // принудительно
	Island_SetReloadEnableGlobal("Cuba2", true);
	questwdmLockReload = true;
	pchar.worldmapencountersoff = "1";
	pchar.quest.GuardOT_diegoGaleondie.win_condition.l1 = "Group_Death";
	pchar.quest.GuardOT_diegoGaleondie.win_condition.l1.group = "Diego_group";
	pchar.quest.GuardOT_diegoGaleondie.function = "GuardOT_CatocheEnter";
}

void GuardOT_CreateDiegoLuggerInWorld()
{
	sld = GetCharacter(NPC_GenerateCharacter("Diego_clone", "diego_1", "man", "man", 35, SPAIN, 3, true, "soldier"));
	FantomMakeCoolSailor(sld, SHIP_CAREERLUGGER, StringFromKey("SharlieFinal_43"), CANNON_TYPE_CANNON_LBS6, 100, 100, 100);
	FantomMakeCoolFighter(sld, 35, 100, 100, "blade_15", "pistol5", "bullet", 250);
	sld.FaceId = 203;
	sld.name = StringFromKey("SharlieFinal_44");
	sld.lastname = StringFromKey("SharlieFinal_45");
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.Ship.Mode = "war";
	SetSailsColor(sld, 8);//черный парус
	// защита от дурака
	sld.Abordage.Enable = true;
	sld.AlwaysFriend = true;
	sld.ShipEnemyDisable  = true; //не обижаться на выстрелы
	LAi_SetImmortal(sld, true);
	// чит
	ref shTo = &RealShips[sti(sld.Ship.Type)];
	shTo.SpeedRate = 25.0;
	shTo.TurnRate = 80.0;
	//в морскую группу
	string sGroup = "Diego_group";
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	sld.mapEnc.type = "trade";
	sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.Name = StringFromKey("SharlieFinal_46");
	Map_CreateCoolTrader("shore15", "shore6", sld.id, 2, 1.7);
}	

void GuardOT_CatocheEnter(string qName)
{
	Group_DeleteGroup("Diego_group");
	questwdmLockReload = false;
	pchar.worldmapencountersoff = "0";
	pchar.quest.GuardOT_CatocheArrive1.win_condition.l1 = "location";
	pchar.quest.GuardOT_CatocheArrive1.win_condition.l1.location = "Beliz";
	pchar.quest.GuardOT_CatocheArrive1.function = "GuardOT_CreateCatocheSquadron";
}

void GuardOT_CreateCatocheSquadron(string qName) // эскадра Диего
{
	AddQuestRecord("Guardoftruth", "51");
	Island_SetReloadEnableGlobal("Beliz", false); // закрыть остров
	bQuestDisableMapEnter = true; // закрыть карту
	pchar.nation = FRANCE; // принудительно
	pchar.DisableChangeFlagMode = true; // запретить менять флаг
	SetNationRelation2MainCharacter(SPAIN, RELATION_FRIEND);
	SetNationRelation2MainCharacter(FRANCE, RELATION_FRIEND);
	SetNationRelation2MainCharacter(ENGLAND, RELATION_NEUTRAL);
	// ставим люггер Диего
	Group_FindOrCreateGroup("camicadze_group");
	sld = GetCharacter(NPC_GenerateCharacter("GOT_camicadze", "off_spa_1", "man", "man", 35, SPAIN, 2, true, "soldier"));
	FantomMakeCoolSailor(sld, SHIP_CAREERLUGGER, StringFromKey("SharlieFinal_43"), CANNON_TYPE_CANNON_LBS6, 100, 100, 100);
	sld.FaceId = 333;
	sld.name = "";
	sld.lastname = "";
	ref realShip = GetRealShip(GetCharacterShipType(sld));
	realShip.lowpolycrew = 0; // убрать матросиков с палубы корабля
	SetCrewQuantityOverMax(sld, 0);
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.Ship.Mode = "war";
	sld.DontDeskTalk = true;
	SetSailsColor(sld, 8);//черный парус
	sld.Abordage.Enable = true;
	sld.ShipEnemyDisable  = true; //не обижаться на выстрелы
	AddCharacterGoods(sld, GOOD_POWDER, 1000);
	Group_AddCharacter("camicadze_group", "GOT_camicadze");
	Group_SetGroupCommander("camicadze_group", "GOT_camicadze");
	Group_SetTaskNone("camicadze_group");
	Group_SetAddress("camicadze_group", "Beliz", "quest_ships", "quest_ship_9");
	Group_LockTask("camicadze_group");
	// ставим эскадру Диего - ВК, 2 ТГ, шебека
	int iRank = 20+MOD_SKILL_ENEMY_RATE*2;
	int iScl = 60;
	int iShip, iCannon;
	Group_FindOrCreateGroup("Catoche_group");
	Group_SetType("Catoche_group", "war");//тип группы
	for (int i=1; i<=4; i++)
	{
		switch (i)
		{
			case 1:
				iShip = SHIP_LINESHIP;
				iCannon = CANNON_TYPE_CANNON_LBS36;
			break;
			
			case 2:
				iShip = SHIP_GALEON_H;
				iCannon = CANNON_TYPE_CANNON_LBS36;
			break;
			
			case 3:
				iShip = SHIP_GALEON_H;
				iCannon = CANNON_TYPE_CANNON_LBS24;
			break;
			
			case 4:
				iShip = SHIP_CORVETTE;
				iCannon = CANNON_TYPE_CULVERINE_LBS18;
			break;
		}
		sld = GetCharacter(NPC_GenerateCharacter("GOT_catochecap_"+i, "off_spa_"+i, "man", "man", iRank, SPAIN, -1, true, "quest"));
		FantomMakeCoolSailor(sld, iShip, "", iCannon, iScl, iScl, iScl);
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_13", "pistol5", "bullet", iScl*2+50);
		sld.DontRansackCaptain = true;
		sld.AnalizeShips = true;
		sld.watchfort = true;
		sld.Ship.Mode = "war";
		sld.alwaysEnemy = true;
		sld.Coastal_Captain = true;
		sld.ship.Crew.Morale = MOD_SKILL_ENEMY_RATE*7+30;
		sld.Ship.Crew.Exp.Sailors = MOD_SKILL_ENEMY_RATE*7+30;
		sld.Ship.Crew.Exp.Cannoners = MOD_SKILL_ENEMY_RATE*7+30;
		sld.Ship.Crew.Exp.Soldiers = MOD_SKILL_ENEMY_RATE*7+30;
		if (MOD_SKILL_ENEMY_RATE > 4 && i < 3) SetCharacterPerk(sld, "MusketsShoot");
		Group_AddCharacter("Catoche_group", "GOT_catochecap_"+i);
	}
	Group_SetGroupCommander("Catoche_group", "GOT_catochecap_1");
	Group_SetTaskAttack("Catoche_group", PLAYER_GROUP);
	Group_SetAddress("Catoche_group", "Beliz", "quest_ships", "quest_ship_8");
	Group_LockTask("Catoche_group");
	
	pchar.quest.GuardOT_catocheshipsdie.win_condition.l1 = "Group_Death";
	pchar.quest.GuardOT_catocheshipsdie.win_condition.l1.group = "Catoche_group";
	pchar.quest.GuardOT_catocheshipsdie.function = "GuardOT_CatocheSquadronDie";
}

void GuardOT_CamicadzeBoom()
{
	log_info(StringFromKey("SharlieFinal_47"))
	sld = characterFromId("GOT_camicadze");
	PostEvent(SHIP_BRANDER_DETONATE, 800, "l", sti(sld.index));
    PlaySound("Sea Battles\Vzriv_fort_001.wav");
	Ship_SetTaskNone(SECONDARY_TASK, sti(sld.index));
}

void GuardOT_CatocheSquadronDie(string qName) // прибили эскадру Диего
{
	DoQuestCheckDelay("sea_victory", 1.5);
	pchar.GenQuest.MapClosedNoBattle = true;
	Group_DeleteGroup("Catoche_group");
	AddQuestRecord("Guardoftruth", "52");
	Island_SetReloadEnableGlobal("Beliz", true);
	pchar.quest.GuardOT_catochecoast.win_condition.l1 = "location";
	pchar.quest.GuardOT_catochecoast.win_condition.l1.location = "shore6";
	pchar.quest.GuardOT_catochecoast.function = "GuardOT_CatocheCoastBattle";
	AddComplexSeaExpToScill(250, 250, 250, 250, 250, 250, 0);
}

void GuardOT_CatocheCoastBattle(string qName) // бой на берегу
{
	Group_DeleteGroup("camicadze_group");
	chrDisableReloadToLocation = true;
	int iRank = 25+MOD_SKILL_ENEMY_RATE*2;
	int iScl = 55;
	// наши
	for (int i=1; i<=15; i++)
	{
		if (i == 1 || i == 12)
		{
			sld = GetCharacter(NPC_GenerateCharacter("GuardOT_soldier_"+i, "mush_ctz_"+(4+rand(2)), "man", "mushketer", iRank, FRANCE, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "cartridge", iScl*2);
		}
		else
		{
			sld = GetCharacter(NPC_GenerateCharacter("GuardOT_soldier_"+i, "citiz_"+(31+rand(9)), "man", "man", iRank, FRANCE, -1, true, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, RandPhraseSimple("blade_10","blade_11"), "pistol1", "bullet", iScl*2);
		}
		LAi_CharacterDisableDialog(sld);
		LAi_SetWarriorType(sld);
		if (i < 8) ChangeCharacterAddressGroup(sld, "Shore6", "rld", "aloc1");
		else ChangeCharacterAddressGroup(sld, "Shore6", "rld", "aloc0");
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	// испанцы
	for (i=1; i<=10; i++)
	{
		if (i > 7)
		{
			sld = GetCharacter(NPC_GenerateCharacter("GuardOT_coastsoldier_"+i, "mush_spa_"+(1+rand(2)), "man", "mushketer", iRank, SPAIN, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "cartridge", iScl*2);
		}
		else
		{
			if (i == 1)
			{
				sld = GetCharacter(NPC_GenerateCharacter("GuardOT_coastsoldier_"+i, "off_spa_3", "man", "man", iRank+5, SPAIN, -1, true, "soldier"));
				FantomMakeCoolFighter(sld, iRank+5, iScl+5, iScl+5, "blade_13", "pistol4", "bullet", iScl*2+50);
			}
			else
			{
				sld = GetCharacter(NPC_GenerateCharacter("GuardOT_coastsoldier_"+i, "sold_spa_"+i, "man", "man", iRank, SPAIN, -1, true, "soldier"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, RandPhraseSimple("blade_10","blade_11"), "pistol1", "bullet", iScl*2);
			}
		}
		LAi_CharacterDisableDialog(sld);
		LAi_SetWarriorType(sld);
		if (i > 7)
		{
			ChangeCharacterAddressGroup(sld, "Shore6", "rld", "loc"+i);
			sld.MusketerDistance = 0;
		}
		else ChangeCharacterAddressGroup(sld, "Shore6", "rld", "loc1");
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "GuardOT_CoastalGuardDie");
	LAi_SetFightMode(pchar, true);
	DeleteAttribute(pchar, "GenQuest.SeaHunter2Pause");
}

void GuardOT_CatchOurSoldiers() // собрать солдат
{
	for (int i=1; i<=15; i++)
	{
		if (GetCharacterIndex("GuardOT_soldier_"+i) != -1)
		{
			sld = CharacterFromID("GuardOT_soldier_"+i);
			if (LAi_GetCharacterHP(sld) > 0)
			{
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
		}
	}
}

void GuardOT_OurSoldiersFight() // приказ солдатам атаковать
{
	for (int i=1; i<=15; i++)
	{
		if (GetCharacterIndex("GuardOT_soldier_"+i) != -1)
		{
			sld = CharacterFromID("GuardOT_soldier_"+i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
	}
}

void GuardOT_CreateExitFortGuard(string qName) // бой на выходе из форта
{
	chrDisableReloadToLocation = true;
	GuardOT_OurSoldiersFight();
	int iRank = 20+MOD_SKILL_ENEMY_RATE*2;
	int iScl = 50;
	// испанцы
	for (i=1; i<=10; i++)
	{
		if (i > 8)
		{
			sld = GetCharacter(NPC_GenerateCharacter("GuardOT_exitsoldier_"+i, "mush_spa_"+(1+rand(2)), "man", "mushketer", iRank, SPAIN, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "cartridge", iScl*2);
		}
		else
		{
			if (i == 1)
			{
				sld = GetCharacter(NPC_GenerateCharacter("GuardOT_exitsoldier_"+i, "off_spa_3", "man", "man", iRank+5, SPAIN, -1, true, "soldier"));
				FantomMakeCoolFighter(sld, iRank+5, iScl+5, iScl+5, "blade_13", "pistol4", "bullet", iScl*2+50);
			}
			else
			{
				sld = GetCharacter(NPC_GenerateCharacter("GuardOT_exitsoldier_"+i, "sold_spa_"+i, "man", "man", iRank, SPAIN, -1, true, "soldier"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, RandPhraseSimple("blade_10","blade_11"), "pistol1", "bullet", iScl*2);
			}
		}
		LAi_CharacterDisableDialog(sld);
		LAi_SetWarriorType(sld);
		if (i > 8) sld.MusketerDistance = 0;
		ChangeCharacterAddressGroup(sld, "Jungle_fort_exit", "rld", "loc"+i);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "GuardOT_ExitfortGuardDie");
	LAi_SetFightMode(pchar, true);
}

void GuardOT_CreateFortGuard(string qName) // бой внутри форта
{
	chrDisableReloadToLocation = true;
	GuardOT_OurSoldiersFight();
	int iRank = 20+MOD_SKILL_ENEMY_RATE*2;
	int iScl = 50;
	// испанцы
	for (i=1; i<=12; i++)
	{
		if (i > 8)
		{
			sld = GetCharacter(NPC_GenerateCharacter("GuardOT_fortsoldier_"+i, "mush_spa_"+(1+rand(2)), "man", "mushketer", iRank, SPAIN, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "cartridge", iScl*2);
		}
		else
		{
			if (i < 3)
			{
				sld = GetCharacter(NPC_GenerateCharacter("GuardOT_fortsoldier_"+i, "off_spa_3", "man", "man", iRank+5, SPAIN, -1, true, "soldier"));
				FantomMakeCoolFighter(sld, iRank+5, iScl+10, iScl+10, "blade_13", "pistol4", "bullet", iScl*2);
			}
			else
			{
				sld = GetCharacter(NPC_GenerateCharacter("GuardOT_fortsoldier_"+i, "sold_spa_"+i, "man", "man", iRank, SPAIN, -1, true, "soldier"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, RandPhraseSimple("blade_10","blade_11"), "pistol1", "bullet", iScl*2);
			}
		}
		LAi_CharacterDisableDialog(sld);
		LAi_SetWarriorType(sld);
		if (i > 8) sld.MusketerDistance = 0;
		ChangeCharacterAddressGroup(sld, "Jungle_fort", "rld", "loc"+i);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "GuardOT_FortGuardDie");
	LAi_SetFightMode(pchar, true);
}

void GuardOT_SetDiegoFortInside(string qName) // бой в резиденции
{
	chrDisableReloadToLocation = true;
	InterfaceStates.Buttons.Save.enable = false;
	pchar.GenQuest.NoDelBody = true;
	int iRank = 25+MOD_SKILL_ENEMY_RATE*2;
	int iScl = 70;
	// испанцы
	int n = MOD_SKILL_ENEMY_RATE/2;
	for (int i=2; i<=n; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("GuardOT_ressoldier_"+i, "sold_spa_"+i, "man", "man", iRank, SPAIN, -1, true, "soldier"));
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, RandPhraseSimple("blade_13","blade_10"), "pistol5", "bullet", iScl*2+50);
		LAi_CharacterDisableDialog(sld);
		LAi_SetWarriorType(sld);
		ChangeCharacterAddressGroup(sld, "Jungle_fort_ammo", "rld", "loc"+i);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	if(GetOfficersQuantity(pchar) > 0)
	{
		int idx;
		for(i=1; i<4; i++)
		{
			idx = GetOfficersIndex(PChar,i);
			if (idx != -1) 
			{
				sld = GetCharacter(idx)
				ChangeCharacterAddressGroup(sld, "Jungle_fort_ammo", "rld", "loc"+sti(i+2));
			}
		}
	}
	// мушкетер
	sld = GetCharacter(NPC_GenerateCharacter("GuardOT_resmushketer", "mush_spa_2", "man", "mushketer", 35, SPAIN, -1, false, "soldier"));
	FantomMakeCoolFighter(sld, 35, 95, 95, "", "mushket2", "cartridge", 100);
	sld.SaveItemsForDead = true; // сохранять на трупе вещи
	sld.DontClearDead = true; // не убирать труп через 200с
	sld.MusketerDistance = 0;
	LAi_SetWarriorType(sld);
	ChangeCharacterAddressGroup(sld, "Jungle_fort_ammo", "rld", "loc0");
	LAi_group_MoveCharacter(sld, "EnemyFight");
	// Диего
	sld = characterFromId("Diego");
	GiveItem2Character(sld, "skinmap");
	GiveItem2Character(sld, "knife_02");
	GiveItem2Character(sld, "recipe_totem_05");
	GiveItem2Character(sld, "totem_05");
	LAi_SetImmortal(sld, false);
	TargetAdmiralMapToCharacter(sld, "A_map_beliz"); // 260912
	sld.SaveItemsForDead = true; // сохранять на трупе вещи
	sld.DontClearDead = true; // не убирать труп через 200с
	LAi_SetWarriorType(sld);
	ChangeCharacterAddressGroup(sld, "Jungle_fort_ammo", "rld", "loc1");
	LAi_group_MoveCharacter(sld, "EnemyFight");
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "GuardOT_ResidenceGuardDie");
	LAi_SetFightMode(pchar, true);
}

void GuardOT_FindSkinmap(string qName) // нашли карту двух появлений
{
	chrDisableReloadToLocation = false;
	AddQuestRecord("Guardoftruth", "56");
	Island_SetReloadEnableGlobal("Beliz", true); // открыть остров
	bQuestDisableMapEnter = false; // открыть карту
	DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
	InterfaceStates.Buttons.Save.enable = true; // разрешить сохраняться
	DeleteAttribute(pchar, "GenQuest.NoDelBody");
	DeleteAttribute(pchar, "DisableChangeFlagMode");
	pchar.quest.GuardOT_meetingwilly.win_condition.l1 = "location";
	pchar.quest.GuardOT_meetingwilly.win_condition.l1.location = "shore6";
	pchar.quest.GuardOT_meetingwilly.function = "GuardOT_SetWillynArchy";
	pchar.quest.GuardOT_meetingwilly1.win_condition.l1 = "location";
	pchar.quest.GuardOT_meetingwilly1.win_condition.l1.location = "Beliz";
	pchar.quest.GuardOT_meetingwilly1.function = "GuardOT_SetWillySquadron";
	sld = CharacterFromID("Vincento");
	sld.dialog.currentnode = "First time";
	pchar.questTemp.Guardoftruth.Archy = "begin";
	AddCharacterExpToSkill(pchar, "Fortune", 300);
}

void GuardOT_SetWillynArchy(string qName) // на берегу нас встречают Вилли и Арчи
{
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
	sld = CharacterFromID("Archy");
	LAi_CharacterDisableDialog(sld);
	ChangeCharacterAddressGroup(sld, "shore6", "reload", "sea");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	sld = CharacterFromID("Willy");
	sld.model = "willy_6";
	sld.dialog.currentnode = "catoche";
	ChangeCharacterAddressGroup(sld, "shore6", "rld", "aloc0");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void GuardOT_SetWillySquadron(string qName) // ставим эскадру Патерсона
{
	SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
	SetNationRelation2MainCharacter(FRANCE, RELATION_FRIEND);
	SetNationRelation2MainCharacter(ENGLAND, RELATION_NEUTRAL);
	AddQuestRecord("Guardoftruth", "58");
	Group_FindOrCreateGroup("Willy_group");
	Group_SetType("Willy_group", "war");//тип группы
	sld = CharacterFromID("Willy");
	FantomMakeCoolSailor(sld, SHIP_FRIGATE_L, StringFromKey("SharlieFinal_48"), CANNON_TYPE_CANNON_LBS24, 90, 90, 90);
	sld.DontRansackCaptain = true;
	sld.watchfort = true;
	sld.DontDeskTalk = true;
	sld.Ship.Mode = "mercenary";
	// защита от дурака, временно
	sld.Abordage.Enable = true;
	sld.AlwaysFriend = true;
	sld.ShipEnemyDisable  = true; //не обижаться на выстрелы
	LAi_SetImmortal(sld, true);
	sld.ship.Crew.Morale = 50+MOD_SKILL_ENEMY_RATE*5;
	sld.Ship.Crew.Exp.Sailors = 50+MOD_SKILL_ENEMY_RATE*5;
	sld.Ship.Crew.Exp.Cannoners = 50+MOD_SKILL_ENEMY_RATE*5;
	sld.Ship.Crew.Exp.Soldiers = 50+MOD_SKILL_ENEMY_RATE*5;
	if (MOD_SKILL_ENEMY_RATE > 2) SetCharacterPerk(sld, "MusketsShoot");
	Group_AddCharacter("Willy_group", "Willy");
	int iShip, iCannon;
	for (int i=1; i<=4; i++)
	{
		switch (i)
		{
			case 1:
				iShip = SHIP_LINESHIP;
				iCannon = CANNON_TYPE_CANNON_LBS36;
			break;
			
			case 2:
				iShip = SHIP_FRIGATE_H;
				iCannon = CANNON_TYPE_CANNON_LBS32;
			break;
			
			case 3:
				iShip = SHIP_CORVETTE;
				iCannon = CANNON_TYPE_CANNON_LBS20;
			break;
			
			case 4:
				iShip = SHIP_POLACRE;
				iCannon = CANNON_TYPE_CULVERINE_LBS18;
			break;
		}
		sld = GetCharacter(NPC_GenerateCharacter("Willy_cap_"+i, "mercen_"+(21+i), "man", "man", 46-(i*4), ENGLAND, -1, true, "quest"));
		FantomMakeCoolSailor(sld, iShip, "", iCannon, 80, 80, 80);
		FantomMakeCoolFighter(sld, 30, 80, 80, "blade_21", "pistol5", "bullet", 150);
		sld.DontRansackCaptain = true;
		sld.watchfort = true;
		sld.Ship.Mode = "mercenary";
		sld.Coastal_Captain = true; // 7-add
		// защита от дурака, временно
		sld.Abordage.Enable = true;
		sld.AlwaysFriend = true;
		sld.ShipEnemyDisable  = true; //не обижаться на выстрелы
		LAi_SetImmortal(sld, true);
		sld.ship.Crew.Morale = MOD_SKILL_ENEMY_RATE*7+30;
		sld.Ship.Crew.Exp.Sailors = MOD_SKILL_ENEMY_RATE*7+30;
		sld.Ship.Crew.Exp.Cannoners = MOD_SKILL_ENEMY_RATE*7+30;
		sld.Ship.Crew.Exp.Soldiers = MOD_SKILL_ENEMY_RATE*7+30;
		if (MOD_SKILL_ENEMY_RATE > 4) SetCharacterPerk(sld, "MusketsShoot");
		Group_AddCharacter("Willy_group", "Willy_cap_"+i);
	}
	Group_SetGroupCommander("Willy_group", "Willy");
	Group_SetTaskNone("Willy_group");
	Group_SetAddress("Willy_group", "Beliz", "quest_ships", "quest_ship_8");
	Group_LockTask("Willy_group");
}

void GuardOT_PrepareCreateBandosInCabin(string qName) // негодяи залезли в каюту
{
	bQuestDisableMapEnter = true;//закрыть карту
	Island_SetReloadEnableGlobal("Bermudes", false);//закрыть остров
	DoQuestFunctionDelay("GuardOT_CreateBandosInCabin", 2.5);
}

void GuardOT_CreateBandosInCabin(string qName) // негодяи засели в каюте
{
	pchar.GenQuest.DontSetCabinOfficer = true;
	int iShipType = GetCharacterShipType(pchar);
	ref rShip = GetRealShip(iShipType);
	string sTemp = "My_" + rShip.CabinType;
	int iRank = 25+MOD_SKILL_ENEMY_RATE*2;
	int iScl = 70;
	for(int i=1; i<=2; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("GOT_cabinband_"+i, "citiz_58", "man", "man", iRank, PIRATE, 1, true, "soldier"));
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_06", "pistol4", "bullet", iScl*2+50);
		sld.Dialog.Filename = "Quest\Sharlie\guardoftruth.c";
		sld.Dialog.currentnode = "cabin_hunter";
		sld.greeting = "hunter";
		LAi_SetActorType(sld);
		if (i == 2) LAi_CharacterDisableDialog(sld);
		ChangeCharacterAddressGroup(sld, sTemp, "rld", "loc"+i);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	chrDisableReloadToLocation = true;//закрыть локацию
	Sea_CabinStartNow();
}

void GuardOT_PortRoyalArrive(string qName)
{
	bQuestDisableMapEnter = true;//закрыть карту
	pchar.GenQuest.MapClosedNoBattle = true;
	AddQuestRecord("Guardoftruth", "63");
	pchar.quest.GuardOT_setarchy.win_condition.l1 = "location";
	pchar.quest.GuardOT_setarchy.win_condition.l1.location = "Portroyal_town";
	pchar.quest.GuardOT_setarchy.function = "GuardOT_SetArchyStreet";
}

void GuardOT_SetArchyStreet(string qName)
{
	pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
	chrDisableReloadToLocation = true;//закрыть локацию
	pchar.GenQuest.CannotWait = true;//запрет ожидания
	// ориентируем на день в обязательном порядке
	int iTime, iAddTime;
	iTime = sti(environment.time);
	if (iTime >= 21) iAddTime = 24-iTime+12;
	if (iTime < 7) iAddTime = 12-iTime;
	if (iTime >= 7 && iTime < 21) iAddTime = 24+12-iTime;
	StoreDayUpdate();
	WaitDate("",0,0,0,iAddtime,5);
	RecalculateJumpTable();
	RefreshWeather();
	RefreshLandTime();
	sld = characterFromId("Archy");	
	sld.Dialog.currentnode = "portroyal";
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, "PortRoyal_town", "goto", LAi_FindFarFreeLocator("goto", locx, locy, locz));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void GuardOT_WillySquadronGo(string qName)
{
	// эскадру Патерсона - на Антигуа
	Group_SetAddress("Willy_group", "Antigua", "quest_ships", "quest_ship_1");
	pchar.questTemp.Guardoftruth.Archy = "room";
	pchar.quest.GuardOT_waitsquadron.win_condition.l1 = "location";
	pchar.quest.GuardOT_waitsquadron.win_condition.l1.location = "Jamaica";
	pchar.quest.GuardOT_waitsquadron.function = "GuardOT_CheckWillySquadron";
	// время логина торговцу
	sld = characterFromId("PortRoyal_trader");
	LAi_SetLoginTime(sld, 6.0, 21.0);
}

void GuardOT_CheckWillySquadron(string qName)
{
	AddQuestRecord("Guardoftruth", "65");
	pchar.quest.GuardOT_seekenterroom.win_condition.l1 = "location";
	pchar.quest.GuardOT_seekenterroom.win_condition.l1.location = "PortRoyal_houseSp1Room";
	pchar.quest.GuardOT_seekenterroom.function = "GuardOT_SeekEnterToRoom";
	pchar.questTemp.Guardoftruth_room = "true";
}

void GuardOT_SeekEnterToRoom(string qName)
{
	chrDisableReloadToLocation = true;//закрыть локацию
	DoQuestCheckDelay("TalkSelf_Quest", 2.0);
	AddCharacterExpToSkill(pchar, "Fortune", 300);
}

void GuardOT_ReloadToRoof(string qName) // выходим на крышу
{
	// подменяем патч и локаторы
	int n = Findlocation("PortRoyal_town");
	locations[n].locators_radius.reload.reload_quest2 = 0.2;
	DoQuestReloadToLocation("PortRoyal_town", "reload", "reload_quest1", "");
	pchar.GenQuest.CantRun = true;
	CheckAndSetOverloadMode(GetMainCharacter()); // бег запрещаем
	pchar.quest.GuardOT_onroof.win_condition.l1 = "locator";
	pchar.quest.GuardOT_onroof.win_condition.l1.location = "PortRoyal_town";
	pchar.quest.GuardOT_onroof.win_condition.l1.locator_group = "reload";
	pchar.quest.GuardOT_onroof.win_condition.l1.locator = "reload_quest2";
	pchar.quest.GuardOT_onroof.function = "GuardOT_ReloadToArchyRoom";
}

void GuardOT_ReloadToArchyRoom(string qName)
{
	DoQuestReloadToLocation("PortRoyal_storeRoom", "reload", "reload1_quest", "");
	// кладем дневник
	sld = ItemsFromID("ArchyBook");
    sld.shown = true;
	sld.startLocation = "PortRoyal_storeRoom";
	sld.startLocator = "item"+(rand(2)+1); // 3 места
	chrDisableReloadToLocation = true;//закрыть локацию
}

void GuardOT_ReadArchyBook() // прочли дневник
{
	pchar.quest.GuardOT_toroof.over = "yes"; //снять прерывание
	chrDisableReloadToLocation = false;
	// подменяем патч и локаторы
	int n = Findlocation("PortRoyal_town");
	AddQuestRecordInfo("ArchyBook", "1");
	AddQuestRecord("Guardoftruth", "66");
	bQuestDisableMapEnter = false;//открыть карту
	DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
	pchar.quest.GuardOT_exitfromstore.win_condition.l1 = "location";
	pchar.quest.GuardOT_exitfromstore.win_condition.l1.location = "PortRoyal_town";
	pchar.quest.GuardOT_exitfromstore.function = "GuardOT_ExitFromstore";
	// доступ на остров
	int i = FindIsland("IslaDeVieques");
	Islands[i].visible = true;
	Islands[i].reload_enable = true;
	pchar.quest.GuardOT_findisland.win_condition.l1 = "location";
	pchar.quest.GuardOT_findisland.win_condition.l1.location = "IslaDeVieques";
	pchar.quest.GuardOT_findisland.function = "GuardOT_FindIslaDeVieques";
	pchar.questTemp.Guardoftruth.ArchyBoom = "true";
}

void GuardOT_ExitFromstore(string qName) // вышли на улицу
{
	DeleteAttribute(pchar, "GenQuest.CantRun");
	CheckAndSetOverloadMode(GetMainCharacter()); // бег разрешаем
	DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
}

void GuardOT_FindIslaDeVieques(string qName) // вышли у острова
{
	AddQuestRecord("Guardoftruth", "67");
	// на вход в дом Арчи
	pchar.quest.GuardOT_findisland1.win_condition.l1 = "location";
	pchar.quest.GuardOT_findisland1.win_condition.l1.location = "IslaDeVieques_HouseEntrance";
	pchar.quest.GuardOT_findisland1.function = "GuardOT_NearArchyHouse";
	// прерывание на дом Арчи
	pchar.quest.GuardOT_Onisland.win_condition.l1 = "location";
	pchar.quest.GuardOT_Onisland.win_condition.l1.location = "IslaDeVieques_House";
	pchar.quest.GuardOT_Onisland.function = "GuardOT_InArchyHouse";
}

void GuardOT_NearArchyHouse(string qName) // у дома Арчи
{
	AddQuestRecord("Guardoftruth", "68");
	pchar.GenQuest.CannotWait = true;//запрет ожидания
}

void GuardOT_InArchyHouse(string qName) // в доме Арчи
{
	chrDisableReloadToLocation = true;
	bDisableCharacterMenu = true;//лочим F2
	//if(CheckAttribute(pchar, "IsMushketer")) SetMainCharacterToMushketer("", false);
}

void GuardOT_ArchyChestBoom() // ба-бах!!
{
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
	pchar.GenQuest.CantRun = true;
	CheckAndSetOverloadMode(GetMainCharacter()); // бег запрещаем
	CreateLocationParticles("ShipExplode", "box", "box1", 1.0, 0, 0, "boom");
	CreateLocationParticles("ShipExplode", "box", "box1", 1.5, 0, 0, "");
	CreateLocationParticles("blast_inv", "box", "box1", 1.0, 0, 0, "");
	CreateLocationParticles("blast_inv", "box", "box1", 1.5, 0, 0, "");
	CreateLocationParticles("blast_dirt", "box", "box1", 1.0, 0, 0, "");
	CreateLocationParticles("smoke", "box", "box1", 1.0, 0, 0, "");
	CreateLocationParticles("blood_big", "box", "box1", 1.3, 0, 0, "");
	LAi_SetActorType(Pchar);
	LAi_ActorAnimation(Pchar, "jump", "GuardOT_SitInHouse", 0.5);
	ChangeCharacterAddressGroup(Pchar, "IslaDeVieques_House", "goto", "goto5");
	Pchar.chr_ai.hp = stf(Pchar.chr_ai.hp)/4;
	PlaySound("People fight\Death_NPC_08.wav");
	DeleteAttribute(pchar, "questTemp.Guardoftruth.ArchyBoom");
	AddCharacterExpToSkill(pchar, "Defence", 100);
}

void GuardOT_StandUpInHouse(string qName)//поднимаемся на ноги
{
	LAi_SetActorType(Pchar);
	LAi_ActorAnimation(Pchar, "Ground_StandUp", "", 3.5);
	DoQuestFunctionDelay("GuardOT_CreateMercenInHouse", 3.5);
}

void GuardOT_CreateMercenInHouse(string qName)// вошел бандос
{
	PlaySound("Ambient\LAND\door_001.wav");
	LAi_SetPlayerType(Pchar);
	int iRank = 25+MOD_SKILL_ENEMY_RATE*2;
	int iScl = 70;
	string sGun = "pistol6";
	if (MOD_SKILL_ENEMY_RATE < 4) sGun = "pistol1";
	if (MOD_SKILL_ENEMY_RATE > 6) sGun = "pistol4";
	sld = GetCharacter(NPC_GenerateCharacter("GOT_housemercen_1", "mercen_30", "man", "man", iRank, ENGLAND, -1, true, "quest"));
	FantomMakeCoolFighter(sld, iRank, iScl, iScl, "topor_04", sGun, "bullet", iScl*2);
	sld.dialog.FileName = "Quest\Sharlie\Guardoftruth.c";
	sld.dialog.currentnode = "housemercen";
	sld.greeting = "hunter";
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	GiveItem2Character(sld, "mushket2");
	GiveItem2Character(sld, "amulet_1");
	GiveItem2Character(sld, "amulet_7");
	GiveItem2Character(sld, "totem_05");
	TakeNItems(sld, "cartridge", 20);
	TakeNItems(sld, "bullet", 30);
	TakeNItems(sld, "gunpowder", 30);
	if (MOD_SKILL_ENEMY_RATE > 4) LAi_SetCheckMinHP(sld, sti((LAi_GetCharacterHP(sld))/2), false, "GuardOT_CreateAddMercenInHouse");
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, "IslaDeVieques_House", "reload", "reload1");
	LAi_ActorDialogDelay(sld, pchar, "", 1.0);
}

void GuardOT_KillMCOfficerInJungle() // убиваем офицеров ГГ
{
	int n = 0;
	for(int i=1; i<=3; i++)
	{
		int idx = GetOfficersIndex(pchar, i);
		if(idx < 0) continue;
		sld = &Characters[idx];
		ChangeCharacterAddressGroup(sld, "IslaDeVieques_HouseEntrance", "quest", "officers"+i);
		if(CheckCharacterPerk(sld, "IronWill"))
		{
			LAi_ApplyCharacterDamage(sld, 1000, "fire");
			LAi_CheckKillCharacter(sld);
		}
		if(CheckAttribute(sld, "OfficerImmortal"))
		{
			sld.Health.HP = makefloat(sld.Health.HP)/2.0;
			sld.Health.maxHP = makefloat(sld.Health.maxHP)/2.0;
			
			LAi_ApplyCharacterDamage(sld, 1000, "fire");
			LAi_CheckKillCharacter(sld);
		}
		else LAi_KillCharacter(sld);
		n++;
		if (sld.id == "mary" || sld.id == "helena") pchar.questTemp.Guardoftruth.GirlKill = "true";
	}
	if (n > 0) pchar.questTemp.Guardoftruth.OfficerKill = "true";
	// запрещаем генерацию офицеров по всему острову
	for (i=0; i<MAX_LOCATIONS; i++)
	{	
		if (findsubstr(locations[i].id, "IslaDeVieques" , 0) != -1)
		{
			LAi_LocationDisableOfficersGen(locations[i].id, true);//офицеров не пускать
		}
	}
	LAi_LocationDisableOfficersGen("Shore74", true);//офицеров не пускать
}

void GuardOT_SetWillyOutHouse(string qName) //ставим Патерсона и его отряд
{
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться patch-8
	GuardOT_KillMCOfficerInJungle(); // убиваем офицеров ГГ
	if(MOD_SKILL_ENEMY_RATE < 9) pchar.ReducedDamage = 0.5; // belamour LE уменьшим урон по ГГ
	chrDisableReloadToLocation = true;
	int iRank = 20+MOD_SKILL_ENEMY_RATE*2;
	int iScl = 65;
	// англичане
	for (i=1; i<=5; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("GuardOT_willymushketer_"+i, "mush_ctz_"+(rand(3)+9), "man", "mushketer", iRank, ENGLAND, -1, false, "soldier"));
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket2", "cartridge", iScl*2);
		LAi_CharacterDisableDialog(sld);
		LAi_SetWarriorType(sld);
		LAi_warrior_SetStay(sld, true);
		sld.MusketerDistance = 0;
		ChangeCharacterAddressGroup(sld, "IslaDeVieques_HouseEntrance", "rld", "loc"+i);
	}
	// Патерсон
	sld = characterFromId("Willy");
	sld.model = "Willy_6_mush";
	sld.model.animation = "mushketer";
	sld.dialog.currentnode = "isladevieques";
	GiveItem2Character(sld, "mushket2x2");
	EquipCharacterbyItem(sld, "mushket2x2");
	sld.MushketType = "mushket2x2";
	sld.MushketBulletType = "cartridge";
	if (MOD_SKILL_ENEMY_RATE > 6) TakeNItems(sld, "potion2", 3);
	ChangeCharacterAddressGroup(sld, "IslaDeVieques_HouseEntrance", "rld", "loc0");
	LAi_SetActorType(sld);
	LAi_ActorDialogDelay(sld, pchar, "", 1.3);
	DoQuestFunctionDelay("Terrapin_SetMusic", 1.2);
}

void GuardOT_WillyMushketerFree(string qName) // меняем поведение мушкетеров
{
	for(int i=1; i<=5; i++)
	{
		sld = CharacterFromID("GuardOT_willymushketer_"+i);
		if(i == 1 || i == 4) continue;
		DeleteAttribute(sld, "MusketerDistance");
		sld.MusketerDistance = 10;
	}
}

void GuardOT_WillyShootInJungle(string qName) // Патерсон отстреливается
{
	if(CheckAttribute(pchar,"ReducedDamage")) DeleteAttribute(pchar,"ReducedDamage");
	chrDisableReloadToLocation = true;
	sld = characterFromId("Willy");
	LAi_SetWarriorType(sld);
	LAi_SetCurHPMax(sld);
	TakeNItems(sld, "potion2", MOD_SKILL_ENEMY_RATE/2);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	DoQuestFunctionDelay("GuardOT_WillyRunInJungle", 2.5);
}

void GuardOT_WillyRunInJungle(string qName) // Патерсон убегает
{
	sld = characterFromId("Willy");
	LAi_SetActorType(sld);
	LAi_LockFightMode(sld, true);
	LAi_ActorRunToLocation(sld, "quest", "teleport", "IslaDeVieques_Jungle_01", "quest", "mushketer", "GuardOT_WillyReadyInJungle", -1);
}

void GuardOT_ArchyInCrabShore(string qName) // в бухте
{
	// Патерсон - на корабль
	sld = characterFromId("Willy");
	sld.model = "Willy_6";
	sld.model.animation = "man";
	RemoveItems(sld, "mushket2x2", 1);
	TakeNItems(sld, "potion2", MOD_SKILL_ENEMY_RATE/2);
	DeleteAttribute(sld, "Abordage.Enable");
	DeleteAttribute(sld, "AlwaysFriend");
	DeleteAttribute(sld, "ShipEnemyDisable");
	LAi_SetImmortal(sld, false);
	sld.AlwaysEnemy = true;
	sld.Coastal_Captain = true;
	DeleteAttribute(sld, "ship.sails");
    DeleteAttribute(sld, "ship.blots");
    DeleteAttribute(sld, "ship.masts");
	DeleteAttribute(sld, "ship.hulls");
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	TargetAdmiralMapToCharacter(sld, "A_map_jam"); // 260912
	string sBlade = GetBestGeneratedItem("blade_21");
	GiveItem2Character(sld, sBlade);
	sld.equip.blade = sBlade; // 260912
	GiveItem2Character(sld, "pistol5");
	EquipCharacterbyItem(sld, "pistol5");
	TakeNItems(sld,"potion2", 5);
	chrDisableReloadToLocation = true;
	InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться
	pchar.GenQuest.NoDelBody = true;
	pchar.GenQuest.Notsearchbody = true;
	int iRank = 20+MOD_SKILL_ENEMY_RATE*2;
	int iScl = 60;
	int n = 4+MOD_SKILL_ENEMY_RATE;
	for (i=1; i<=n; i++)
	{
		if (i < 3)
		{
			sld = GetCharacter(NPC_GenerateCharacter("GuardOT_archysoldier_"+i, "mush_ctz_"+(rand(3)+9), "man", "mushketer", iRank, ENGLAND, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket2", "cartridge", iScl*2);
		}
		else
		{
			sld = GetCharacter(NPC_GenerateCharacter("GuardOT_archysoldier_"+i, "mercen_"+(rand(7)+23), "man", "man", iRank, ENGLAND, -1, true, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, RandPhraseSimple("blade_19","blade_21"), "pistol5", "bullet", iScl*2);
		}
		LAi_CharacterDisableDialog(sld);
		LAi_SetWarriorType(sld);
		if (i < 7) ChangeCharacterAddressGroup(sld, "Shore74", "rld", "loc1");
		else ChangeCharacterAddressGroup(sld, "Shore74", "rld", "loc2");
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	// Арчи Колхаун
	sld = characterFromId("Archy");
	sld.model = "Archy_mush";
	sld.model.animation = "mushketer";
	GiveItem2Character(sld, "mushket2x2");
	EquipCharacterbyItem(sld, "mushket2x2");
	sld.MushketType = "mushket2x2";
	sld.MushketBulletType = "cartridge";
	GiveItem2Character(sld, "key_archy"); // ключ Арчи
	GiveAdmiralMapToCharacter(sld, 5);
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	LAi_CharacterDisableDialog(sld);
	LAi_SetWarriorType(sld);
	ChangeCharacterAddressGroup(sld, "Shore74", "rld", "loc0");
	LAi_group_MoveCharacter(sld, "EnemyFight");
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "GuardOT_CrabShoreGuardDie");
	LAi_SetFightMode(pchar, true);
	// нужно продержаться 1.5 минут
	DoQuestFunctionDelay("GuardOT_OurSailorInCrabShore", 90.0);
}

void GuardOT_OurSailorInCrabShore(string qName) // подмога - наши пришли!
{
	if (LAi_grp_playeralarm <= 0)
	{
		log_testinfo("Подмога не понадобилась - сами крутые!");
		return;
	}
	PlaySound("interface\abordage_wining.wav");
	PlaySound("interface\abordage_wining.wav");
	int iRank = 20+MOD_SKILL_ENEMY_RATE+5;
	int iScl = 60;
	int n = 4+MOD_SKILL_ENEMY_RATE;
	// наши
	for (int i=1; i<=n; i++)
	{
		if (i < 3)
		{
			sld = GetCharacter(NPC_GenerateCharacter("GuardOT_soldier_"+i, "mush_ctz_"+(4+rand(2)), "man", "mushketer", iRank, FRANCE, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "cartridge", iScl*2);
		}
		else
		{
			sld = GetCharacter(NPC_GenerateCharacter("GuardOT_soldier_"+i, "citiz_"+(31+rand(9)), "man", "man", iRank, FRANCE, 1, true, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, RandPhraseSimple("blade_10","blade_11"), "pistol1", "bullet", iScl*2);
		}
		LAi_CharacterDisableDialog(sld);
		LAi_SetWarriorType(sld);
		if (i < 6) ChangeCharacterAddressGroup(sld, "Shore74", "rld", "loc1");
		else ChangeCharacterAddressGroup(sld, "Shore74", "rld", "loc2");
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
}

void GuardOT_FindArchyKey(string qName) // нашли ключ Арчи
{
	chrDisableReloadToLocation = false; //открыть локацию
	InterfaceStates.Buttons.Save.enable = true; //разрешить сохраняться
	AddQuestRecord("Guardoftruth", "72");
	DeleteAttribute(pchar, "GenQuest.NoDelBody");
	pchar.quest.GuardOT_crabseabattle.win_condition.l1 = "location";
	pchar.quest.GuardOT_crabseabattle.win_condition.l1.location = "IslaDeVieques";
	pchar.quest.GuardOT_crabseabattle.function = "GuardOT_WillySquadronSeaBattle";
	AddCharacterExpToSkill(pchar, "Fortune", 100);
	for (i=1; i<=4+MOD_SKILL_ENEMY_RATE; i++) // Captain Beltrop, 21.01.2021, убираем выживших матросов
	{
			sld = characterFromID("GuardOT_soldier_"+i);
			if (!LAi_IsDead(sld))
			{
			    sld.lifeday = 0; 
			}
	}
}

void GuardOT_WillySquadronSeaBattle(string qName) // эскадра Патерсона
{ 
	bQuestDisableMapEnter = true;//закрыть карту
	for (int i=1; i<=4; i++)
	{
		sld = characterFromId("Willy_cap_"+i);
		DeleteAttribute(sld, "Abordage.Enable");
		DeleteAttribute(sld, "AlwaysFriend");
		DeleteAttribute(sld, "ShipEnemyDisable");
		LAi_SetImmortal(sld, false);
		sld.AlwaysEnemy = true;
		sld.Coastal_Captain = true;
		DeleteAttribute(sld, "ship.sails");
		DeleteAttribute(sld, "ship.blots");
		DeleteAttribute(sld, "ship.masts");
		DeleteAttribute(sld, "ship.hulls");
	}
	Group_SetTaskAttack("Willy_group", PLAYER_GROUP);
	Group_SetPursuitGroup("Willy_group", PLAYER_GROUP);
	Group_LockTask("Willy_group");
	
	pchar.quest.GuardOT_crabseabattle_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.GuardOT_crabseabattle_AfterBattle.win_condition.l1.group = "Willy_group";
	pchar.quest.GuardOT_crabseabattle_AfterBattle.function = "GuardOT_WillySquadronAfterBattle";
}

void GuardOT_WillySquadronAfterBattle(string qName) // победа!
{
	DoQuestCheckDelay("sea_victory", 1.5);
	Group_DeleteGroup("Willy_group");
	bQuestDisableMapEnter = false;
	DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
	// разрешаем генерацию офицеров по всему острову
	for (i=0; i<MAX_LOCATIONS; i++)
	{	
		if (findsubstr(locations[i].id, "IslaDeVieques" , 0) != -1)
		{
			LAi_LocationDisableOfficersGen(locations[i].id, false);//офицеров пускать
		}
	}
	LAi_LocationDisableOfficersGen("Shore74", false);//офицеров пускать
	if(CheckShipTypeInSquadron(SHIP_FRIGATE_L) > 0) AddQuestRecord("Guardoftruth", "75");
	else AddQuestRecord("Guardoftruth", "73");
	// на компас Стрела пути
	pchar.quest.GuardOT_findarrowway.win_condition.l1 = "item";
	pchar.quest.GuardOT_findarrowway.win_condition.l1.item = "arrowway";
	pchar.quest.GuardOT_findarrowway.function = "GuardOT_FindArrowWayCompas";
	AddComplexSeaExpToScill(250, 250, 250, 250, 250, 250, 0);
}

void GuardOT_FindArrowWayCompas(string qName) // нашли компас
{
	AddQuestRecord("Guardoftruth", "74");
	pchar.questTemp.Guardoftruth = "threeitems"; // флаг для Джино
	AddCharacterExpToSkill(pchar, "Fortune", 500);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////	
//Jason----------------------------------- Коварный остров Ксочитэм ---------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Ksochitam_StartSearchIsland(string qName) // активация
{
	pchar.questTemp.Ksochitam = "begin";
}

void Ksochitam_LookSkinmapFirstTime() // просмотрели карту первый раз
{
	sld = characterFromId("Jino");
	sld.dialog.currentnode = "ksochitam_5";
	pchar.questTemp.Ksochitam = "talk";
}

void Ksochitam_LookSkinmapSecondTime() // просмотрели карту второй раз
{
	sld = characterFromId("Jino");
	sld.dialog.currentnode = "ksochitam_8";
	pchar.questTemp.Ksochitam = "talk";
}

void Ksochitam_JinoPassenger(string qName) // Джино в пассажиры
{
	sld = characterFromId("Jino");
	AddPassenger(pchar, sld, false);
	SetCharacterRemovable(sld, false);
	ChangeCharacterAddressGroup(sld, "none", "", "");
	// устанавливаем прерывания на локаторы со статуями:
	// у деревни мискито
	pchar.quest.Ksochitam_dolly1.win_condition.l1 = "locator";
	pchar.quest.Ksochitam_dolly1.win_condition.l1.location = "Pearl_Jungle_03";
	pchar.quest.Ksochitam_dolly1.win_condition.l1.locator_group = "item";
	pchar.quest.Ksochitam_dolly1.win_condition.l1.locator = "dolly1";
	pchar.quest.Ksochitam_dolly1.function = "Ksochitam_FindPearlShow";
	// на Доминике
	pchar.quest.Ksochitam_dolly3.win_condition.l1 = "locator";
	pchar.quest.Ksochitam_dolly3.win_condition.l1.location = "Dominica_Jungle_02";
	pchar.quest.Ksochitam_dolly3.win_condition.l1.locator_group = "item";
	pchar.quest.Ksochitam_dolly3.win_condition.l1.locator = "dolly3";
	pchar.quest.Ksochitam_dolly3.function = "Ksochitam_FindDominicaShow";
}

void Ksochitam_FindPearlShow(string qName) // нашли статую у мискито
{
	pchar.questTemp.Ksochitam.PearlShow = "true"; // атрибут статуи №1
	DoQuestFunctionDelay("Ksochitam_FindShowScene", 0.5);
}

void Ksochitam_FindDominicaShow(string qName) // нашли статую на Доминике
{
	pchar.questTemp.Ksochitam.DominicaShow = "true"; // атрибут статуи №3
	DoQuestFunctionDelay("Ksochitam_FindShowScene", 0.5);
}

void Ksochitam_FindShowScene(string qName) // сценка
{
	LAi_SetBarmanType(pchar);
	StartQuestMovie(true, false, true);
	locCameraLockNearHero(-5.0, 2.0, -5.0, 600, true);
	DoQuestFunctionDelay("Ksochitam_FindShowSceneEnd", 7.0);
	AddCharacterExpToSkill(pchar, "Fortune", 200);
}

void Ksochitam_FindShowSceneEnd(string qName) // 
{
	locCameraResetState();
	EndQuestMovie();
	InterfaceStates.Buttons.Save.enable = true;
	bDisableCharacterMenu = false;
	DeleteAttribute(pchar, "questTemp.Ksochitam_Dolly");
	if (CheckAttribute(pchar, "questTemp.Ksochitam.PearlShow"))
	{
		if (CheckAttribute(pchar, "questTemp.Ksochitam.DominicaShow")) pchar.questTemp.Ksochitam_Dolly = "full";
		else pchar.questTemp.Ksochitam_Dolly = "half_pearl";
	}
	else pchar.questTemp.Ksochitam_Dolly = "half_dominica";
	DoQuestCheckDelay("TalkSelf_Quest", 0.1);
}

void Ksochitam_JinoDollyTalk(string qName) // говорилка Джино
{
	pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу
	chrDisableReloadToLocation = true;//закрыть локацию
	sld = characterFromId("Jino");
	GetCharacterPos(sld, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void Ksochitam_ArriveIsland(string qName) // вошли в локацию Ксочитэма
{
	AddQuestRecord("Ksochitam", "17");
}

void Ksochitam_ArriveRockshore(string qName) // 
{
	bQuestDisableMapEnter = true;//закрыть карту
	pchar.GenQuest.MapClosedNoBattle = true;
	sld = characterFromId("Jino");
	sld.dialog.currentnode = "ksochitam_35";
	DoQuestFunctionDelay("Ksochitam_JinoDollyTalk", 0.5);
	pchar.questTemp.Ksochitam = "onisland";
	pchar.GenQuest.CannotWait = true;//запрет ожидания
	AddCharacterExpToSkill(pchar, "Sailing", 500);
	LAi_group_SetCheck("KSOCHITAM_MONSTERS", "OpenTheDoors");
}

void Ksochitam_Shoreship(string qName) // 
{
	int iRank = 25+MOD_SKILL_ENEMY_RATE*2;
	int iScl = 80;
	float fMft = MOD_SKILL_ENEMY_RATE/10;
	sld = GetCharacter(NPC_GenerateCharacter("ShoreShip4_skeletcap", "skeletcap", "man", "skeleton", iRank, PIRATE, -1, false, "soldier"));
	FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_21", "pistol4", "bullet", iScl*2+50);
	sld.MultiFighter = 0.8+fMft; // мультифайтер
	ChangeCharacterAddressGroup(sld, "Shore_ship4", "monsters", "monster0");
	LAi_SetWarriorType(sld);
	LAi_warrior_SetStay(sld, true);
	LAi_group_MoveCharacter(sld, "KSOCHITAM_MONSTERS");
	pchar.questTemp.Ksochitam.ShoreShip = "true";
}

void Ksochitam_ShoreshipOpenBox() // открыли сундуки в локации с кораблём
{
	AddQuestRecord("Ksochitam", "7");
	DeleteAttribute(pchar, "questTemp.Ksochitam.ShoreShip");
	AddCharacterExpToSkill(pchar, "Fortune", 400);
}

void Ksochitam_SQOutside(string qName) // вошли в локацию с Санта-Квитерией
{
	chrDisableReloadToLocation = true;//закрыть локацию
	LAi_group_SetCheck("KSOCHITAM_MONSTERS", "Ksochitam_SQMonstersDie");
	DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L2");
	DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L3");
}

void Ksochitam_SQInside(string qName) // внутри Санта-Квитерии
{
	chrDisableReloadToLocation = true;//закрыть локацию
	int iRank = 28+MOD_SKILL_ENEMY_RATE;
	int iScl = 80;
	float fMft = MOD_SKILL_ENEMY_RATE/10;
	for(int i=2; i<=3; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("SQI_skelet_"+i, "skel"+i, "man", "skeleton", iRank, PIRATE, -1, false, "soldier"));
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_07", "pistol5", "bullet", iScl*2+50);
		sld.MultiFighter = 0.8+fMft; // мультифайтер
		sld.monster = true;
		ChangeCharacterAddressGroup(sld, "SantaQuiteriaInside", "goto", "goto"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "KSOCHITAM_MONSTERS");
	}
	sld = GetCharacter(NPC_GenerateCharacter("SQC_skeletcap", "skeletcap", "man", "skeleton", iRank+5, PIRATE, -1, false, "soldier"));
	FantomMakeCoolFighter(sld, iRank+5, iScl+10, iScl+10, "blade_21", "pistol4", "bullet", iScl*2+100);
	sld.dialog.FileName = "Quest\Sharlie\Ksochitam.c";
	sld.dialog.currentnode = "SQC_skeletcap";
	sld.name = StringFromKey("SharlieFinal_49");
	sld.lastname = StringFromKey("SharlieFinal_50");
	sld.MultiFighter = 1.0+fMft; // мультифайтер
	GiveItem2Character(sld, "key_archy");
	sld.SaveItemsForDead = true; // сохранять на трупе вещи
	sld.DontClearDead = true; 
	sld.cirassId = Items_FindItemIdx("cirass1");
	sld.monster = true;
	ChangeCharacterAddressGroup(sld, "SantaQuiteriaInside", "goto", "goto1");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "KSOCHITAM_MONSTERS");
	LAi_SetCheckMinHP(sld, 10, true, "Ksochitam_SQCskeletcaptalk");
}

void Ksochitam_CreateDeMaldonado(string qName) // в скалистой бухте
{
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
	int iRank = 27+MOD_SKILL_ENEMY_RATE*2;
	int iScl = 75;
	// Алонсо де Мальдонадо
	sld = characterFromId("Maldonado");
	sld.SaveItemsForDead = true; // сохранять на трупе вещи
	sld.DontClearDead = true; // не убирать труп через 200с
	LAi_SetGuardianType(sld);
	sld.protector = true;
	sld.dialog.currentnode = "ksochitam";
	sld.cirassId = Items_FindItemIdx("cirass1");
	ChangeCharacterAddressGroup(sld, "shore65", "quest", "maldonado");
	// солдаты
	for (int i=1; i<=2; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Maldonado_soldier_"+i, "sold_spa_"+i, "man", "man", iRank, SPAIN, -1, true, "soldier"));
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, RandPhraseSimple("blade_13","blade_10"), "pistol5", "bullet", iScl*2+50);
		LAi_CharacterDisableDialog(sld);
		LAi_SetStayType(sld);
		ChangeCharacterAddressGroup(sld, "shore65", "quest", "soldier"+i);
	}
	// мушкетеры
	for (i=1; i<=2; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Maldonado_mushketer_"+i, "mush_spa_"+i, "man", "mushketer", 35, SPAIN, -1, false, "soldier"));
		FantomMakeCoolFighter(sld, 35, 105, 105, "", "mushket2", "cartridge", iScl*2+50);
		sld.MusketerDistance = 0;
		LAi_SetStayType(sld);
		LAi_CharacterDisableDialog(sld);
		ChangeCharacterAddressGroup(sld, "shore65", "quest", "mushketer"+i);
	}
}

void Ksochitam_CreateMaldonadoHelpers()
{
	int iRank = 25+MOD_SKILL_ENEMY_RATE*2;
	int iScl = 70;
	int n = MOD_SKILL_ENEMY_RATE/2;
	// солдаты
	for (int i=3; i<=n; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Maldonado_soldier_"+i, "sold_spa_"+i, "man", "man", iRank, SPAIN, -1, true, "soldier"));
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, RandPhraseSimple("blade_13","blade_10"), "pistol5", "bullet", iScl*2+50);
		LAi_CharacterDisableDialog(sld);
		LAi_SetStayType(sld);
		ChangeCharacterAddressGroup(sld, "shore65", "quest", "add");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	// мушкетеры
	for (i=3; i<=n; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Maldonado_mushketer_"+i, "mush_spa_"+i, "man", "mushketer", 35, SPAIN, -1, false, "soldier"));
		FantomMakeCoolFighter(sld, 35, 105, 105, "", "mushket2", "cartridge", iScl*2+50);
		sld.MusketerDistance = 0;
		LAi_SetStayType(sld);
		LAi_CharacterDisableDialog(sld);
		ChangeCharacterAddressGroup(sld, "shore65", "quest", "mushketer"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
}

void Ksochitam_CreateMaldonadoSquadron(string qName)
{
	Island_SetReloadEnableGlobal("Ksochitam", false);
	// ставим эскадру Мальдонадо
	int iRank = 25+MOD_SKILL_ENEMY_RATE*2;
	int iScl = 90;
	int iShip, iCannon;
	Group_FindOrCreateGroup("Maldonado_group");
	Group_SetType("Maldonado_group", "war");//тип группы
	for (int i=1; i<=4; i++)
	{
		switch (i)
		{
			case 1:
				iShip = SHIP_LINESHIP;
				iCannon = CANNON_TYPE_CANNON_LBS36;
			break;
			
			case 2:
				if (MOD_SKILL_ENEMY_RATE > 4) iShip = SHIP_LINESHIP;
				else iShip = SHIP_GALEON_H;
				iCannon = CANNON_TYPE_CANNON_LBS32;
			break;
			
			case 3:
				iShip = SHIP_GALEON_H;
				iCannon = CANNON_TYPE_CANNON_LBS24;
			break;
			
			case 4:
				iShip = SHIP_CORVETTE;
				iCannon = CANNON_TYPE_CULVERINE_LBS18;
			break;
		}
		sld = GetCharacter(NPC_GenerateCharacter("Maldonadocap_"+i, "off_spa_"+i, "man", "man", iRank, SPAIN, -1, true, "quest"));
		FantomMakeCoolSailor(sld, iShip, "", iCannon, iScl, iScl, iScl);
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_13", "pistol5", "bullet", iScl*2+100);
		sld.DontRansackCaptain = true;
		sld.AnalizeShips = true;
		sld.watchfort = true;
		sld.Ship.Mode = "war";
		sld.alwaysEnemy = true;
		sld.Coastal_Captain = true;
		sld.ship.Crew.Morale = MOD_SKILL_ENEMY_RATE*5+50;
		sld.Ship.Crew.Exp.Sailors = MOD_SKILL_ENEMY_RATE*5+50;
		sld.Ship.Crew.Exp.Cannoners = MOD_SKILL_ENEMY_RATE*5+50;
		sld.Ship.Crew.Exp.Soldiers = MOD_SKILL_ENEMY_RATE*5+50;
		if (MOD_SKILL_ENEMY_RATE > 4 && i < 3) SetCharacterPerk(sld, "MusketsShoot");
		Group_AddCharacter("Maldonado_group", "Maldonadocap_"+i);
	}
	Group_SetGroupCommander("Maldonado_group", "Maldonadocap_1");
	Group_SetTaskAttack("Maldonado_group", PLAYER_GROUP);
	Group_SetAddress("Maldonado_group", "Ksochitam", "quest_ships", "quest_ship_10");
	Group_LockTask("Maldonado_group");
	
	pchar.quest.Ksochitam_Maldonadoshipsdie.win_condition.l1 = "Group_Death";
	pchar.quest.Ksochitam_Maldonadoshipsdie.win_condition.l1.group = "Maldonado_group";
	pchar.quest.Ksochitam_Maldonadoshipsdie.function = "Ksochitam_MaldonadoSquadronDie";
}

void Ksochitam_MaldonadoSquadronDie(string qName) // победили эскадру Мальдонадо
{
	DoQuestCheckDelay("sea_victory", 1.5);
	Island_SetReloadEnableGlobal("Ksochitam", true);
	LocatorReloadEnterDisable("Shore65", "reload2_back", false);
	Group_DeleteGroup("Maldonado_group");
	sld = characterFromId("Jino");
	sld.dialog.currentnode = "ksochitam_43";
	AddQuestRecord("Ksochitam", "15");
	RemoveItems(pchar, "VerifyPaper", 1);
	sld = characterFromId("Vincento");
	ChangeCharacterAddressGroup(sld, "none", "", ""); // прячем отца Винсенто
	AddComplexSeaExpToScill(300, 300, 300, 300, 300, 300, 0);
}

void Ksochitam_MaskGuard(string qName) // вошли в грот Стража
{
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
	pchar.quest.Ksochitam_guard_crypt.win_condition.l1 = "locator";
	pchar.quest.Ksochitam_guard_crypt.win_condition.l1.location = "Shore_mask";
	pchar.quest.Ksochitam_guard_crypt.win_condition.l1.locator_group = "quest";
	pchar.quest.Ksochitam_guard_crypt.win_condition.l1.locator = "detector";
	pchar.quest.Ksochitam_guard_crypt.function = "Ksochitam_EnterGuardCrypt";
}

void Ksochitam_EnterGuardCrypt(string qName)
{
	LAi_SetActorType(pchar);
	StartQuestMovie(true, false, true);
	LAi_ActorGoToLocator(pchar, "goto", "rotate", "Ksochitam_GuardCryptRotate", -1);
}

void Ksochitam_GuardMaskFlash(string qName)
{
	if (CheckAttribute(pchar, "questTemp.Ksochitam.GuardMaskBeat")) return; // останавливаем цикл
	int n = rand(18)+1;
	int m = rand(18)+20;
	int k = rand(18)+39;
	int l = rand(18)+58;
	int p = rand(18)+77;
	string locator1 = "fire"+n;
	string locator2 = "fire"+m;
	string locator3 = "fire"+k;
	string locator4 = "fire"+l;
	string locator5 = "fire"+p;
	pchar.questTemp.Ksochitam.GuardMaskFire.l1 = n;
	pchar.questTemp.Ksochitam.GuardMaskFire.l2 = m;
	pchar.questTemp.Ksochitam.GuardMaskFire.l3 = k;
	pchar.questTemp.Ksochitam.GuardMaskFire.l4 = l;
	pchar.questTemp.Ksochitam.GuardMaskFire.l5 = p;
	CreateLocationParticles("fire_incas_Simple", "item", locator1, -0.5, 0, 0, "fortfire");
	CreateLocationParticles("fire_incas_Simple", "item", locator2, -0.5, 0, 0, "fortfire");
	CreateLocationParticles("fire_incas_Simple", "item", locator3, -0.5, 0, 0, "fortfire");
	CreateLocationParticles("fire_incas_Simple", "item", locator4, -0.5, 0, 0, "fortfire");
	CreateLocationParticles("fire_incas_Simple", "item", locator5, -0.5, 0, 0, "fortfire");
	DoQuestFunctionDelay("Ksochitam_GuardMaskFlashPause", 2.5);
}

void Ksochitam_GuardMaskFlashPause(string qName)
{
	DeleteAttribute(pchar, "questTemp.Ksochitam.GuardMaskFire");
	DoQuestFunctionDelay("Ksochitam_GuardMaskFlash", 0.5);
}

void Ksochitam_SetMusic(string qName)
{
	SetMusic("music_teno");
}

void Ksochitam_ArriveHome(string qName)
{
	sld = characterFromId("Jino");
	RemovePassenger(pchar, sld);
	sld.dialog.currentnode = "ksochitam_53";
	DoQuestFunctionDelay("Ksochitam_JinoDollyTalk", 0.5);
}

void Ksochitam_TripComplete(string qName)
{
	CloseQuestHeader("Ksochitam");
	sld = characterFromId("Jino");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "houseF3", "SentJons_HouseF3_Room", "goto", "goto1", "Ksochitam_JinoNormal", 20.0); // patch-7
	// убираем Ксочитэм
	int i = FindIsland("Ksochitam");
	Islands[i].visible = false;
	Islands[i].reload_enable = false;
	DeleteAttribute(&Islands[i], "alwaysStorm");
	DeleteAttribute(&Islands[i], "storm");
	DeleteAttribute(&Islands[i], "tornado");
	DeleteAttribute(&Islands[i], "QuestlockWeather");
	sld = ItemsFromID("arrowway");
	sld.price = 100; // компас можно выкладывать 270912
	sld = ItemsFromID("knife_01");
	sld.price = 1000; // дагу можно выкладывать 270912
	sld = ItemsFromID("mark_map");
	sld.price = 100;
	// создаем монаха
	sld = GetCharacter(NPC_GenerateCharacter("monk_vinsento", "monk_6", "man", "man_B", 5, ENGLAND, 1, false, "soldier"));
	FantomMakeCoolFighter(sld, 5, 10, 10, "", "", "", 20);
	sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
	sld.Dialog.currentnode = "monk_vinsento";
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, "sentjons_town", "goto", LAi_FindFarFreeLocator("goto", locx, locy, locz));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void Ksochitam_VinsentoLastLetterRead() // прочли письмо
{
	chrDisableReloadToLocation = false;//открыть локацию
	pchar.quest.Ksochitam_chapel.win_condition.l1 = "location";
	pchar.quest.Ksochitam_chapel.win_condition.l1.location = "Villemstad_Chapel";
	pchar.quest.Ksochitam_chapel.function = "Tieyasal_VinsentoChapel";
	LocatorReloadEnterDisable("Villemstad_Graveyard", "reload6", false);
	AddQuestRecord("Sharlie", "41");
	SetFunctionTimerCondition("Tieyasal_VinsentoChapelOver", 0, 0, 15, false); // таймер
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////	
//Jason----------------------------------- Древний город майя --------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Tieyasal_VinsentoChapelOver(string qName) // отказались проходить квест
{
	AddQuestRecord("Sharlie", "42");
	CloseQuestHeader("Sharlie"); // patch-8
	LocatorReloadEnterDisable("Villemstad_Graveyard", "reload6", true);
	pchar.quest.Ksochitam_chapel.over = "yes"; //снять прерывание
}

// --> провал по времени
void Tieyasal_TotalOver(string qName)
{
	if(IsEntity(&worldMap) || bSeaActive)
	{
		pchar.quest.Tieyasal_TimeOver.win_condition.l1 = "Location_Type";
		pchar.quest.Tieyasal_TimeOver.win_condition.l1.location_type = "town";
		pchar.quest.Tieyasal_TimeOver.function = "Tieyasal_TimeOver";
		pchar.quest.Tieyasal_TimeOver1.win_condition.l1 = "Location_Type";
		pchar.quest.Tieyasal_TimeOver1.win_condition.l1.location_type = "seashore";
		pchar.quest.Tieyasal_TimeOver1.function = "Tieyasal_TimeOver";
	}
	else DoQuestFunctionDelay("Tieyasal_TimeOver", 1.0);
}

void Tieyasal_TimeOver(string qName) // 
{
	GetCharacterPos(pchar, &locx, &locy, &locz);
	sTotalTemp = LAi_FindNearestLocator("reload", locx, locy, locz);
	LAi_SetActorType(pchar);
	LAi_ActorTurnToLocator(pchar, "reload", sTotalTemp);
	PlaySound("interface\notebook.wav");
	CreateLocationParticles("shadowstar", "reload", sTotalTemp, 1.0, 0, 0, "");
	DoQuestFunctionDelay("Tieyasal_TimeOverContinue_1", 7.0);
	DoQuestFunctionDelay("Tieyasal_TimeOverMusic", 1.5);
}

void Tieyasal_TimeOverMusic(string qName) // 
{
	SetMusic("music_teleport");
}

void Tieyasal_TimeOverContinue_1(string qName) // 
{
	PlaySound("Weather\Thunder_Q.wav");
	CreateLocationParticles("fire_incas", "reload", sTotalTemp, 0.5, 0, 0, "");
	DoQuestFunctionDelay("Tieyasal_TimeOverContinue_2", 7.0);
}

void Tieyasal_TimeOverContinue_2(string qName) // 
{
	PlaySound("Weather\Thunder_Q.wav");
	PlaySound("Ambient\Teno_inside\big_ring.wav");
	PlaySound("Weather\koster_001.wav");
	CreateLocationParticles("shipfire", "reload", sTotalTemp, 0.5, 0, 0, "");
	CreateLocationParticles("shadowstar_Big", "reload", sTotalTemp, 1.5, 0, 0, "");
	DoQuestFunctionDelay("Tieyasal_TimeOverContinue_3", 7.0);
}

void Tieyasal_TimeOverContinue_3(string qName) // 
{
	RemoveAllCharacterItems(pchar, true);
	GiveItem2Character(pchar, "blade_13");
	EquipCharacterbyItem(pchar, "blade_13");
	GiveItem2Character(pchar, "pistol5");
	EquipCharacterbyItem(pchar, "pistol5");
	TakeNItems(pchar, "grapeshot", 50);
	AddItems(pchar, "bullet", 50);
	TakeNItems(pchar, "potion2", 3);
	LAi_SetCharacterUseBullet(pchar, GUN_ITEM_TYPE, "bullet");
	ChangeCharacterAddressGroup(pchar, "none", "", "");
	DoQuestCheckDelay("Tieyasal_Fail_TeleportContinue_6", 3.0);
}
// <-- провал по времени

void Tieyasal_VinsentoChapel(string qName) // ставим отца Винсенто в часовню
{
	pchar.quest.Tieyasal_VinsentoChapelOver.over = "yes"; //снять прерывание
	chrDisableReloadToLocation = true;
	sld = characterFromId("Vincento");
	sld.dialog.currentnode = "tieyasal";
	ChangeCharacterAddressGroup(sld, "Villemstad_Chapel", "barmen", "stay");
	LAi_SetPriestType(sld);
	for(int i=1; i<=3; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("V_guard_"+i, "sold_spa_"+i, "man", "man", 35, SPAIN, -1, true, "soldier"));
		FantomMakeCoolFighter(sld, 35, 100, 100, "blade_13", "pistol5", "bullet", 200);
		LAi_CharacterDisableDialog(sld);
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, "Villemstad_Chapel", "goto", "goto"+i);
		LAi_SetWarriorType(sld);
		LAi_warrior_SetStay(sld, true);
		LAi_warrior_DialogEnable(sld, true);
	}
}

void Tieyasal_SetAdrianInChapel(string qName) // ставим падре Адриана
{
	sld = GetCharacter(NPC_GenerateCharacter("Adrian", "priest_sp1", "man", "man2", 25, SPAIN, -1, true, "quest"));
	SetFantomParamFromRank(sld, 25, true);
	sld.name = StringFromKey("SharlieFinal_51");
	sld.lastname = StringFromKey("SharlieFinal_52");
	sld.dialog.FileName = "Quest\Sharlie\OtherNPC.c";
	sld.dialog.currentnode = "adrian";
	sld.greeting = "padre_1";
	RemoveAllCharacterItems(sld, true);
	LAi_SetPriestType(sld);
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, "Villemstad_Chapel", "barmen", "stay");
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
}

void Tieyasal_CreateITShips(string qName) // ставим корабли у Исла Тесоро
{
	pchar.questTemp.Tieyasal = "islatesoro";
	bQuestDisableMapEnter = true;//закрыть карту
	Island_SetReloadEnableGlobal("Bermudes", false);
	// ставим эскадру
	int iRank = 25+MOD_SKILL_ENEMY_RATE*2;
	int iShip, iCannon;
	Group_FindOrCreateGroup("ITDichoso_group");
	Group_SetType("ITDichoso_group", "war");//тип группы
	for (int i=1; i<=4; i++)
	{
		switch (i)
		{
			case 1:
				iShip = SHIP_LINESHIP;
				iCannon = CANNON_TYPE_CANNON_LBS32;
			break;
			
			case 2:
				iShip = SHIP_FRIGATE;
				iCannon = CANNON_TYPE_CANNON_LBS24;
			break;
			
			case 3:
				iShip = SHIP_BRIG;
				iCannon = CANNON_TYPE_CANNON_LBS16;
			break;
			
			case 4:
				iShip = SHIP_SHNYAVA;
				iCannon = CANNON_TYPE_CANNON_LBS16;
			break;
		}
		sld = GetCharacter(NPC_GenerateCharacter("ITDichosocap_"+i, "mercen_1"+i, "man", "man", iRank, PIRATE, -1, true, "quest"));
		FantomMakeCoolSailor(sld, iShip, "", iCannon, 100, 100, 100);
		FantomMakeCoolFighter(sld, iRank, 100, 100, "blade_21", "pistol5", "bullet", 200);
		sld.Ship.Mode = "mercenary";
		sld.DontRansackCaptain = true;
		sld.AnalizeShips = true;
		sld.alwaysEnemy = true;
		sld.AlwaysSandbankManeuver = true;
		sld.ship.Crew.Morale = MOD_SKILL_ENEMY_RATE*3+70;
		sld.Ship.Crew.Exp.Sailors = MOD_SKILL_ENEMY_RATE*3+70;
		sld.Ship.Crew.Exp.Cannoners = MOD_SKILL_ENEMY_RATE*3+70;
		sld.Ship.Crew.Exp.Soldiers = MOD_SKILL_ENEMY_RATE*3+70;
		SetCharacterPerk(sld, "MusketsShoot");
		SetCharacterPerk(sld, "LongRangeGrappling");
		SetCharacterPerk(sld, "GrapplingProfessional");
		int hcrew = GetMaxCrewQuantity(sld);
		if (i < 3) SetCrewQuantityOverMax(sld, 1.5*hcrew);
		else SetCrewQuantityOverMax(sld, 2*hcrew);
		Group_AddCharacter("ITDichoso_group", "ITDichosocap_"+i);
	}
	Group_SetGroupCommander("ITDichoso_group", "ITDichosocap_1");
	Group_SetTaskAttack("ITDichoso_group", PLAYER_GROUP);
	Group_SetAddress("ITDichoso_group", "Bermudes", "quest_ships", "quest_ship_6");
	Group_LockTask("ITDichoso_group");
	
	pchar.quest.Tieyasal_ITShipsDie.win_condition.l1 = "Group_Death";
	pchar.quest.Tieyasal_ITShipsDie.win_condition.l1.group = "ITDichoso_group";
	pchar.quest.Tieyasal_ITShipsDie.function = "Tieyasal_ITShipsDie";
}

void Tieyasal_ITShipsDie(string qName) // победили эскадру
{
	DoQuestCheckDelay("sea_victory", 1.5);
	Island_SetReloadEnableGlobal("Bermudes", true);
	bQuestDisableMapEnter = false;
	Group_DeleteGroup("ITDichoso_group");
	if (CheckAttribute(pchar, "questTemp.Tieyasal.MigelKnow")) AddQuestRecord("Tieyasal", "6");
	else AddQuestRecord("Tieyasal", "5");
	AddComplexSeaExpToScill(400, 400, 400, 400, 400, 400, 0);
	pchar.quest.Tieyasal_Dichosocall.win_condition.l1 = "location";
	pchar.quest.Tieyasal_Dichosocall.win_condition.l1.location = "Santacatalina_town";
	pchar.quest.Tieyasal_Dichosocall.function = "Tieyasal_CreateDichosoMan";
	pchar.questTemp.Tieyasal = "blueveld";
}

void Tieyasal_CreateDichosoMan(string qName) // посланец Дичозо
{
	pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу
	chrDisableReloadToLocation = true;//закрыть локацию
	sld = GetCharacter(NPC_GenerateCharacter("Dichoso_agent", "mercen_15", "man", "man", 25, ENGLAND, 0, false, "soldier"));
	FantomMakeCoolFighter(sld, 25, 80, 80, "blade_10", "pistol6", "bullet", 120);
	sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
	sld.Dialog.currentnode = "Dichoso_agent";
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, "Santacatalina_town", "goto", LAi_FindFarFreeLocator("goto", locx, locy, locz));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void Tieyasal_ArriveToNevis(string qName) // прибыли на Сент-Кристофер
{
	pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу
	chrDisableReloadToLocation = true;//закрыть локацию
	pchar.GenQuest.CannotWait = true;//запрет ожидания
	// устанавливаем солдат+офицер
	int iRank = 25+MOD_SKILL_ENEMY_RATE+5;
	int iScl = 70;
	iTotalTemp = 6;
	if (CheckAttribute(pchar, "questTemp.Tieyasal.MigelKnow")) iTotalTemp = 14;
	for (int i=1; i<=iTotalTemp; i++)
	{
		if (i == 1)
		{
			sld = GetCharacter(NPC_GenerateCharacter("Tieyasal_Oursoldier_"+i, "mercen_24", "man", "man", iRank+5, FRANCE, -1, true, "soldier"));
			FantomMakeCoolFighter(sld, iRank+5, iScl+5, iScl+5, "blade_21", "pistol4", "bullet", iScl*2+100);
			sld.dialog.FileName = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "newcastle_officer";
			if (CheckAttribute(pchar, "questTemp.Tieyasal.MigelKnow")) sld.dialog.currentnode = "newcastle_officer_0";
		}
		else
		{
			if (i == 2 || i == 3)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Tieyasal_Oursoldier_"+i, "mush_ctz_"+(4+rand(2)), "man", "mushketer", iRank, FRANCE, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "cartridge", iScl*2+50);
			}
			else
			{
				sld = GetCharacter(NPC_GenerateCharacter("Tieyasal_Oursoldier_"+i, "citiz_"+(31+rand(9)), "man", "man", iRank, FRANCE, -1, true, "soldier"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, RandPhraseSimple("blade_10","blade_11"), "pistol1", "bullet", iScl*2+50);
			}
			LAi_CharacterDisableDialog(sld);
		}
		ChangeCharacterAddressGroup(sld, "Shore42", "reload", "reload1");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
}

void Tieyasal_NewcastleGoJungle(string qName) // джунгли перед кладбищем
{
	chrDisableReloadToLocation = true;
	for(int i=1; i<=iTotalTemp; i++)
	{
		if (GetCharacterIndex("Tieyasal_Oursoldier_"+i) != -1)
		{
			sld = characterFromID("Tieyasal_Oursoldier_"+i);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 7); // 160912
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
	}
	DoQuestCheckDelay("Tieyasal_MCSoldiersReset", 8.0); // 160912
}

void Tieyasal_InGraveyardCrypt(string qName) // внутри крипты
{
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
	int iRank = 28+MOD_SKILL_ENEMY_RATE*2;
	int iScl = 90;
	sld = GetCharacter(NPC_GenerateCharacter("Dichoso_crypt_agent", "mercen_22", "man", "man", iRank, SPAIN, -1, false, "soldier"));
	FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_20", "pistol4", "bullet", iScl*2);
	sld.name = StringFromKey("SharlieFinal_53");
	sld.lastname = StringFromKey("SharlieFinal_54");
	sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
	sld.Dialog.currentnode = "Dichoso_crypt_agent";
	sld.MultiFighter = 1.0+MOD_SKILL_ENEMY_RATE/20; // мультифайтер
	ChangeCharacterAddressGroup(sld, "Charles_CryptBig2", "quest", "quest1");
	LAi_SetStayType(sld);
	sld.SaveItemsForDead = true; // сохранять на трупе вещи
	sld.DontClearDead = true;
	GiveItem2Character(sld, "specialletter");
	ChangeItemDescribe("specialletter", "itmdescr_specialletter_dichoso");
	sld = ItemsFromID("specialletter");
	sld.text = "Letter_Dichoso";
}

void Tieyasal_StartCryptBattle() // драка в крипте
{
	pchar.GenQuest.Notsearchbody = true;
	for(int i=1; i<=4; i++)
	{
		PlaySound("Ambient\LAND\door_00"+i+".wav");
	}
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
	// ранг и скиллы нападающих будут зависеть от степени осведомленности героя
	int iRank = 25+MOD_SKILL_ENEMY_RATE*2;
	if (CheckAttribute(pchar, "questTemp.Ksochitam.SQCapBookRead")) iRank = iRank-15;
	if (CheckAttribute(pchar, "questTemp.Tieyasal.MigelKnow")) iRank = iRank-15;
	if (iRank < 20) iRank = 20;
	int iScl = 90;
	if (CheckAttribute(pchar, "questTemp.Ksochitam.SQCapBookRead")) iScl = iScl-20;
	if (CheckAttribute(pchar, "questTemp.Tieyasal.MigelKnow")) iScl = iScl-20;
	if (iScl < 20) iScl = 20;
	int n = 2;
	if (MOD_SKILL_ENEMY_RATE > 5) n++;
	if (MOD_SKILL_ENEMY_RATE > 7) n++;
	if (MOD_SKILL_ENEMY_RATE > 9) n++;
	log_info(StringFromKey("SharlieFinal_55", n));
	for(i=1; i<=n; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Dichoso_crypt_soldier_"+i, "citiz_58", "man", "man", iRank, PIRATE, -1, false, "soldier"));
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, RandPhraseSimple("blade_19","blade_21"), RandPhraseSimple("pistol4","pistol6"), "bullet", iScl*2);
		ChangeCharacterAddressGroup(sld, "Charles_CryptBig2", "monsters", "monster"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	for(i=1; i<=4; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Dichoso_crypt_mushketer_"+i, "mush_ctz_"+(rand(2)+10), "man", "mushketer", iRank, PIRATE, -1, false, "soldier"));
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "cartridge", iScl*2+100);
		ChangeCharacterAddressGroup(sld, "Charles_CryptBig2", "quest", "mushketer"+i);
		sld.MusketerDistance = 0;
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	sld = characterFromId("Dichoso_crypt_agent");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "Tieyasal_CryptBattleComplete");
	LAi_SetFightMode(pchar, true);
	//запускаем офицеров
	for(i=1; i<=3; i++)
	{
		int idx = GetOfficersIndex(pchar, i);
		if(idx < 0) continue;
		sld = &Characters[idx];
		ChangeCharacterAddressGroup(sld, "Charles_CryptBig2", "reload", "reload1");
	}
}

void Tieyasal_DichosoLetterRead() // прочли письмо
{
	chrDisableReloadToLocation = false;//открыть локацию
	DeleteAttribute(pchar, "GenQuest.NoDelBody");
	if (CheckAttribute(pchar, "questTemp.Tieyasal.MigelKnow")) AddQuestRecord("Tieyasal", "13");
	else AddQuestRecord("Tieyasal", "12");
	pchar.quest.Tieyasal_GraveyardBattle.win_condition.l1 = "location";
	pchar.quest.Tieyasal_GraveyardBattle.win_condition.l1.location = "Charles_Graveyard";
	pchar.quest.Tieyasal_GraveyardBattle.function = "Tieyasal_GraveyardBattle";
}

void Tieyasal_GraveyardBattle(string qName) // бой на кладбище
{
	pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу
	chrDisableReloadToLocation = true;//закрыть локацию
	// устанавливаем врагов
	int iRank = 25+MOD_SKILL_ENEMY_RATE*2;
	if (CheckAttribute(pchar, "questTemp.Ksochitam.SQCapBookRead")) iRank = iRank-5;
	if (CheckAttribute(pchar, "questTemp.Tieyasal.MigelKnow")) iRank = iRank-5;
	int iScl = 70;
	if (CheckAttribute(pchar, "questTemp.Ksochitam.SQCapBookRead")) iScl = iScl-5;
	if (CheckAttribute(pchar, "questTemp.Tieyasal.MigelKnow")) iScl = iScl-5;
	for (int i=1; i<=18; i++)
	{
		if (i == 1)
		{
			sld = GetCharacter(NPC_GenerateCharacter("Graveyardsoldier_"+i, "citiz_"+(rand(9)+51), "man", "man", iRank+5, PIRATE, -1, true, "soldier"));
			FantomMakeCoolFighter(sld, iRank+5, iScl+5, iScl+5, "blade_21", "pistol4", "bullet", iScl*2+100);
		}
		else
		{
			if (i > 1 && i < 7)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Graveyardsoldier_"+i, "mush_ctz_"+(rand(2)+10), "man", "mushketer", iRank, PIRATE, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "cartridge", iScl*2+50);
			}
			else
			{
				sld = GetCharacter(NPC_GenerateCharacter("Graveyardsoldier_"+i, "citiz_"+(rand(9)+51), "man", "man", iRank, PIRATE, -1, true, "soldier"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, RandPhraseSimple("blade_10","blade_11"), "pistol1", "bullet", iScl*2+50);
			}
		}
		ChangeCharacterAddressGroup(sld, "Charles_Graveyard", "rld", "loc"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	// наши из засады
	for(i=1; i<=iTotalTemp; i++)
	{
		if (GetCharacterIndex("Tieyasal_Oursoldier_"+i) != -1)
		{
			sld = characterFromID("Tieyasal_Oursoldier_"+i);
			if (CheckAttribute(pchar, "questTemp.Tieyasal.MigelKnow"))
			{
				if (i < 8) ChangeCharacterAddressGroup(sld, "Charles_Graveyard", "reload", "reload1");
				else ChangeCharacterAddressGroup(sld, "Charles_Graveyard", "reload", "reload2");
			}
			else ChangeCharacterAddressGroup(sld, "Charles_Graveyard", "reload", "reload1");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "Tieyasal_GraveyardBattleComplete");
	LAi_SetFightMode(pchar, true);
}

void Tieyasal_TalkSelfInCabin(string qName) // идем в каюту
{
	log_info(StringFromKey("SharlieFinal_56"));
	PlaySound("interface\notebook.wav");
	Island_SetReloadEnableGlobal("Nevis", false);
	bQuestDisableMapEnter = true;//закрыть карту
	pchar.GenQuest.MapClosedNoBattle = true;
	bDisableCharacterMenu = true;//лочим F2
	int iShipType = GetCharacterShipType(pchar);
	ref rShip = GetRealShip(iShipType);
	string sTemp = "My_" + rShip.CabinType;
	pchar.quest.Tieyasal_Cabintalk.win_condition.l1 = "location";
	pchar.quest.Tieyasal_Cabintalk.win_condition.l1.location = sTemp;
	pchar.quest.Tieyasal_Cabintalk.win_condition = "Tieyasal_PrepareCabinTalk";
	if (CheckCharacterItem(pchar, "splinter_js")) pchar.questTemp.Tieyasal_CabinTalk = "calendar";
	else pchar.questTemp.Tieyasal_CabinTalk = "trip";
}

void Tieyasal_CalendarThink(string qName) // Чапай думает
{
	sld = characterFromId("SnakeEye");
	sld.dialog.currentnode = "calendar_12";
}

void Tieyasal_CalendarDone(string qName) // календарь готов
{
	sld = characterFromId("SnakeEye");
	sld.dialog.currentnode = "calendar_28";
}

void Tieyasal_SetUrakanItzaWarrior(string qName) 
{
	LAi_group_Delete("TMP_FRIEND");
	pchar.GenQuest.CannotWait = true;//запрет ожидания
	LocatorReloadEnterDisable("Tenochtitlan", "reload1_back", true); // закрыть выход
	pchar.GenQuest.Notsearchbody = true;
	pchar.quest.Tieyasal_TripStart.over = "yes"; //снять прерывание
	pchar.quest.Tieyasal_TotalOver.over = "yes"; //снять общий таймер
	// ставим Уракана и мушкетеров ица
	sld = GetCharacter(NPC_GenerateCharacter("Urakan", "itza_Urakan", "man", "man", 40, PIRATE, -1, false, "quest"));
	FantomMakeCoolFighter(sld, 40, 110, 110, "topor_01", "", "", 250);
	sld.name = StringFromKey("SharlieFinal_57");
	sld.lastname = StringFromKey("SharlieFinal_58");
	sld.dialog.FileName = "Quest\Sharlie\Itza.c";
	sld.dialog.currentnode = "urakan";
	sld.greeting = "urakan";
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, "Tenochtitlan", "quest", "urakanstay");
	LAi_SetWarriorType(sld);
	LAi_warrior_SetStay(sld, true);
	LAi_group_MoveCharacter(sld, "TMP_FRIEND");
	for(int i=1; i<=2; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Bridge_itza_"+i, "mush_itza_"+i, "man", "mushketer", 35, PIRATE, -1, false, "quest"));
		FantomMakeCoolFighter(sld, 35, 110, 110, "", "mushket1", "bullet", 200);
		ChangeCharacterAddressGroup(sld, "Tenochtitlan", "quest", "mushketer"+i);
		LAi_SetImmortal(sld, true);
		LAi_SetWarriorType(sld);
		LAi_warrior_SetStay(sld, true);
		LAi_warrior_DialogEnable(sld, false);
		LAi_group_MoveCharacter(sld, "TMP_FRIEND");
	}
	// прерывание на вход в локатор fire
	pchar.quest.Tieyasal_mushketfire.win_condition.l1 = "locator";
	pchar.quest.Tieyasal_mushketfire.win_condition.l1.location = "Tenochtitlan";
	pchar.quest.Tieyasal_mushketfire.win_condition.l1.locator_group = "teleport";
	pchar.quest.Tieyasal_mushketfire.win_condition.l1.locator = "fire1";
	pchar.quest.Tieyasal_mushketfire.function = "Tieyasal_MushketShoot";
	// ставим воинов ица через 7 сек
	DoQuestFunctionDelay("Tieyasal_CreateItzaWarriorFirstGroup", 7.0);
	pchar.questTemp.Tieyasal.ItzaWarrior = "1";
	// грузить квестовых офицеров
	i = Findlocation("Tenochtitlan");
	locations[i].setquestofficers = true;
	// деактивируем маску Кукулькана, если она у нас есть
	sld = ItemsFromID("mask_true");
	sld.shown = true;
}

void Tieyasal_MushketShoot(string qName) // ГГ сунулся на мост
{
	for(int i=1; i<=2; i++)
	{
		sld = characterFromId("Bridge_itza_"+i);
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "shot", "Saga_MineBanditsxFire_1", 1.0);
	}
}

void Tieyasal_CreateItzaWarriorFirstGroup(string qName) // первая группа вояк ица
{
	LAi_group_Delete("ITZA");
	PlaySound("interface\abordage_wining.wav");
	PlaySound("interface\abordage_wining.wav");
	int iRank = 25+MOD_SKILL_ENEMY_RATE*2;
	iTotalTemp = 5+makeint(MOD_SKILL_ENEMY_RATE/5);
	for(int i=1; i<=iTotalTemp; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Itza_1Group_"+i, "itza_"+(rand(7)+1), "man", "man", iRank, PIRATE, -1, false, "native"));
		FantomMakeCoolFighter(sld, iRank, 100, 100, RandPhraseSimple("blade_01","blade_02"), "", "", 100);
		ChangeCharacterAddressGroup(sld, "Tenochtitlan", "quest", "itza");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "ITZA");
	}
	LAi_group_SetRelation("ITZA", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("ITZA", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("ITZA", "Tieyasal_ItzaWarriorPause");
}

void Tieyasal_InGreatTemple(string qName) // внутри большого храма
{
	LAi_group_Delete("ITZA");
	// ставим Мишеля. Он же Кукулькан
	int iTemp = MOD_SKILL_ENEMY_RATE;
	sld = characterFromId("Mishelle");
	sld.model = "migel_2":
	sld.dialog.currentnode = "kukulkan";
	LAi_SetHP(sld, 1000+MOD_SKILL_ENEMY_RATE*200, 1000+MOD_SKILL_ENEMY_RATE*200);
	LAi_SetImmortal(sld, true);
	sld.LSC_clan = true;
	RemoveAllCharacterItems(sld, true);
	sld.cirassId = Items_FindItemIdx("cirass1");
	sld.MultiFighter = 1.2+MOD_SKILL_ENEMY_RATE/10; // мультифайтер
	GiveItem2Character(sld, "blade_26");
	sld.equip.blade = "blade_26";
	GiveItem2Character(sld, "pistol8");
	EquipCharacterbyItem(sld, "pistol8");
	TakeNItems(sld, "harpoon", 20);
	AddItems(sld, "gunpowder", 20);
	TakeNItems(sld, "potion2", iTemp);
	TakeNItems(sld, "potion3", 5);
	LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "harpoon");
	ChangeCharacterAddressGroup(sld, "Temple_great", "quest", "kukulkan");
	LAi_SetActorType(sld);
	// ставим Канека
	sld = GetCharacter(NPC_GenerateCharacter("Kanek", "itza_Kanek", "man", "man", 40, PIRATE, -1, false, "quest"));
	FantomMakeCoolFighter(sld, 40, 90, 90, "topor_01", "", "", 200);
	sld.name = StringFromKey("SharlieFinal_59");
	sld.lastname = StringFromKey("SharlieFinal_60");
	sld.dialog.FileName = "Quest\Sharlie\Itza.c";
	sld.dialog.currentnode = "kanek";
	sld.greeting = "kanek";
	sld.LSC_clan = true;
	LAi_SetImmortal(sld, true);
	GiveItem2Character(sld, "stonekey");
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	ChangeCharacterAddressGroup(sld, "Temple_great", "quest", "kanek");
	LAi_SetWarriorType(sld);
	LAi_warrior_SetStay(sld, true);
	// ставим охрану ица
	int iRank = 25+MOD_SKILL_ENEMY_RATE*2;
	for(int i=1; i<=4; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Guard_itza_mush_"+i, "mush_itza_"+(rand(2)+1), "man", "mushketer", iRank, PIRATE, -1, false, "quest"));
		FantomMakeCoolFighter(sld, iRank, 90, 90, "", "mushket1", "cartridge", 100);
		ChangeCharacterAddressGroup(sld, "Temple_great", "monsters", "mushketer"+i);
		sld.MusketerDistance = 0;
		sld.LSC_clan = true;
		if (i == 2)
		{
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
		}
		LAi_SetWarriorType(sld);
		LAi_warrior_SetStay(sld, true);
		LAi_warrior_DialogEnable(sld, false);
		LAi_group_MoveCharacter(sld, "ITZA");
	}
	for(i=1; i<=7; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Guard_itza_"+i, "itza_"+i, "man", "man", iRank, PIRATE, -1, false, "native"));
		FantomMakeCoolFighter(sld, iRank, 90, 90, "topor_01", "", "", 100);
		ChangeCharacterAddressGroup(sld, "Temple_great", "monsters", "guard"+i);
		sld.LSC_clan = true;
		LAi_SetWarriorType(sld);
		LAi_warrior_SetStay(sld, true);
		LAi_warrior_DialogEnable(sld, false);
		LAi_group_MoveCharacter(sld, "ITZA");
	}
	// идем к Мишелю принудительно
	LAi_SetActorType(pchar);
	LAi_ActorGoToLocator(pchar, "goto", "goto1", "Tieyasal_MishelleTalkActivation", -1);
	// прерывания на ключ и скрижали
	if (CheckCharacterItem(pchar, "mask_true"))
	{
		pchar.quest.Tieyasal_stonekey.win_condition.l1 = "item";
		pchar.quest.Tieyasal_stonekey.win_condition.l1.item = "stonekey";
		pchar.quest.Tieyasal_stonekey.function = "Tieyasal_FindStoneKey";
		pchar.quest.Tieyasal_tablet1.win_condition.l1 = "item";
		pchar.quest.Tieyasal_tablet1.win_condition.l1.item = "Tablet_1";
		pchar.quest.Tieyasal_tablet1.function = "Tieyasal_FindTabletItzamna";
		pchar.quest.Tieyasal_tablet2.win_condition.l1 = "item";
		pchar.quest.Tieyasal_tablet2.win_condition.l1.item = "Tablet_3";
		pchar.quest.Tieyasal_tablet2.function = "Tieyasal_FindTabletChak";
	}
}

void Tieyasal_TempleFightGuard(string qName) // драка с гардами ица
{
	chrDisableReloadToLocation = true;//закрыть локацию
	LAi_SetPlayerType(pchar);
	sld = characterFromId("Mishelle");
	LAi_group_MoveCharacter(sld, "TMP_FRIEND");
	sld = characterFromId("Kanek");
	LAi_group_MoveCharacter(sld, "TMP_FRIEND");
	for(int i=1; i<=4; i++)
	{
		sld = characterFromId("Guard_itza_mush_"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "ITZA");
	}
	for(i=1; i<=7; i++)
	{
		sld = characterFromId("Guard_itza_"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "ITZA");
	}
	LAi_group_SetRelation("ITZA", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("ITZA", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("ITZA", "Tieyasal_TempleGuardDie");
	LAi_SetFightMode(pchar, true);
	pchar.questTemp.Tieyasal.Defend = "true"; // устанавливаем защиту Мишелю и Канеку
	pchar.questTemp.Tieyasal.LockLadder = "true"; // закрываем лестницу
}

void Tieyasal_TempleDefendActivation() // защита
{
	LAi_ApplyCharacterDamage(pchar, 100, "other");
	LAi_CheckKillCharacter(pchar);			
	GetCharacterPos(pchar, &locx, &locy, &locz);
	string locator = LAi_FindNearestLocator("rld", locx, locy, locz);
	ChangeCharacterAddressGroup(pchar, "Temple_great", "rld", locator);
	PlaySound("PEOPLE\jump.wav");
	CreateLocationParticles("fire_incas_Simple", "rld", locator, 0.5, 0, 0, "");
}

void Tieyasal_SecondFloorActivate(string qName) // активация боя на 2 этаже
{
	PlaySound("Ambient\Teno_inside\big_ring.wav");
	pchar.questTemp.Tieyasal.LockLadder = "true"; // закрываем лестницу
	pchar.questTemp.Tieyasal.LockGate = "true"; // закрываем проход на 3 этаж
	sld = characterFromId("Mishelle_mushketer");
	LAi_group_MoveCharacter(sld, "ITZA");
	for(int i=5; i<=6; i++)
	{
		sld = characterFromId("Warrior_itza_mush_"+i);
		LAi_group_MoveCharacter(sld, "ITZA");
	}
	for(i=1; i<=iTotalTemp; i++)
	{
		sld = characterFromId("Warrior_itza_"+i);
		LAi_group_MoveCharacter(sld, "ITZA");
	}
	LAi_group_SetRelation("ITZA", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("ITZA", LAI_GROUP_PLAYER, true);
	// прерывание на локатор
	pchar.quest.Tieyasal_2floor_add.win_condition.l1 = "locator";
	pchar.quest.Tieyasal_2floor_add.win_condition.l1.location = "Temple_great";
	pchar.quest.Tieyasal_2floor_add.win_condition.l1.locator_group = "quest";
	pchar.quest.Tieyasal_2floor_add.win_condition.l1.locator = "detector2";
	pchar.quest.Tieyasal_2floor_add.function = "Tieyasal_AddingGroupActivate";
}

void Tieyasal_AddingGroupActivate(string qName) // активация добавочной группы
{
	for(int i=11; i<=14; i++)
	{
		sld = characterFromId("Warrior_itza_"+i);
		LAi_RemoveCheckMinHP(sld);
		LAi_group_MoveCharacter(sld, "ITZA");
	}
	LAi_group_SetRelation("ITZA", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("ITZA", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("ITZA", "Tieyasal_FloorWarriorDie");
}

void Tieyasal_ThirdFloorActivate(string qName) // активация боя на 3 этаже
{
	PlaySound("Ambient\Teno_inside\big_ring.wav");
	pchar.questTemp.Tieyasal.LockGate = "true"; // закрываем проход на 3 этаж
	sld = characterFromId("Mishelle");
	LAi_group_MoveCharacter(sld, "ITZA");
	for(int i=1; i<=5; i++)
	{
		sld = characterFromId("Top_itza_"+i);
		LAi_group_MoveCharacter(sld, "ITZA");
	}
	LAi_group_SetRelation("ITZA", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("ITZA", LAI_GROUP_PLAYER, true);	
	//LAi_group_SetCheck("EnemyFight", "Tieyasal_FloorWarriorDie");
}

void Tieyasal_StandUpInTemple(string qName)//поднимаемся на ноги
{
	// ставим воинов ица - антураж
	for(int i=1; i<=3; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Gate_itza_"+i, "itza_"+i, "man", "man", 30, PIRATE, -1, false, "native"));
		FantomMakeCoolFighter(sld, 30, 100, 100, "topor_01", "", "", 200);
		ChangeCharacterAddressGroup(sld, "Temple_great", "reload", "reload"+i);
		LAi_SetActorType(sld);
		sld.LSC_clan = true;
		LAi_group_MoveCharacter(sld, "TMP_FRIEND");
	}
	LAi_SetActorType(pchar);
	LAi_ActorAnimation(pchar, "Ground_StandUp", "", 3.5);
	DoQuestFunctionDelay("Tieyasal_FinalfailTalkContinue", 3.5);
}

void Tieyasal_FinalfailTalkContinue(string qName)
{
	LAi_SetPlayerType(pchar);
	sld = characterFromId("Mishelle");
	sld.dialog.currentnode = "kukulkan_fail_1";
	LAi_SetActorType(sld);
	LAi_ActorDialogDelay(sld, pchar, "", 1.0);
}

void Tieyasal_PrepareToWinBattle()
{
	LAi_SetActorType(pchar);
	LAi_ActorTurnToLocator(pchar, "reload", "reload1");
	int iRank = 30+MOD_SKILL_ENEMY_RATE*2;
	// входит Уракан и 4 воина
	sld = characterFromId("Urakan");
	LAi_SetActorType(sld);
	sld.LSC_clan = true;
	ChangeCharacterAddressGroup(sld, "Temple_great", "reload", "reload1");
	LAi_ActorGoToLocator(sld, "goto", "stay2", "", -1);
	for(int i=1; i<=8; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Itza_actorwarrior_"+i, "itza_"+(rand(7)+1), "man", "man", iRank, PIRATE, 0, false, "native"));
		FantomMakeCoolFighter(sld, iRank, 100, 100, RandPhraseSimple("topor_01","blade_02"), "", "", 100);
		ChangeCharacterAddressGroup(sld, "Temple_great", "reload", "reload"+(rand(1)+2));
		sld.LSC_clan = true;
		LAi_SetActorType(sld);
		LAi_ActorGoToLocator(sld, "goto", "warrior"+i, "", -1);
		LAi_SetImmortal(sld, true);
		LAi_group_MoveCharacter(sld, "TMP_FRIEND");
	}
	
	// входит Канек
	sld = characterFromId("Kanek");
	ChangeCharacterAddressGroup(sld, "Temple_great", "quest", "detector3");
	LAi_ActorRunToLocator(sld, "goto", "stay3", "", -1);
	DoQuestFunctionDelay("Tieyasal_WinBattleTalk", 10.0);
}

void Tieyasal_WinBattleTalk(string qName) //
{
	if (CheckAttribute(pchar, "questTemp.Tieyasal.Wintalk")) return; // fix
	// запрещаем сохранение и интерфейсы
	bDisableCharacterMenu = true;
	InterfaceStates.Buttons.Save.enable = false;
	ChangeShowIntarface();
	// поворачиваем вояк ица
	for(int i=1; i<=8; i++)
	{
		sld = characterFromId("Itza_actorwarrior_"+i);
		LAi_SetActorType(sld);
		LAi_ActorTurnToCharacter(sld, characterFromID("Blaze"));
	}
	SetMainCharacterIndex(GetCharacterIndex("Urakan"));
	PChar = GetMainCharacter();
	LAi_SetPlayerType(PChar);
	sld = characterFromId("Mishelle");
	sld.dialog.currentnode = "kukulkan_win_1";
	LAi_SetActorType(sld);
	LAi_ActorDialogDelay(sld, pchar, "", 2.0);
}

void Tieyasal_WinBattleStart()
{
	pchar.questTemp.Tieyasal.Wintalk = "true"; // fix
	bDisableCharacterMenu = false;
	ChangeShowIntarface();
	pchar.GenQuest.Notsearchbody = true;
	pchar.GenQuest.NoDelBody = true;
	sld = characterFromId("Urakan");
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, "TMP_FRIEND");
	sld = characterFromId("Kanek");
	LAi_SetImmortal(sld, false);
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "ITZA"); // patch-7
	sld = characterFromId("Mishelle");
	LAi_SetImmortal(sld, false);
	LAi_SetCurHPMax(sld);
	LAi_GetCharacterMaxEnergy(sld);
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "ITZA"); // patch-7
	LAi_group_SetRelation("ITZA", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY); // patch-7
	LAi_group_FightGroups("ITZA", LAI_GROUP_PLAYER, true); // patch-7
	LAi_SetFightMode(pchar, true);
	LAi_SetCheckMinHP(sld, 1, true, "Tieyasal_MishelleDie");
}

void Tieyasal_MishelleDie(string qName) //
{
	LAi_SetActorType(pchar);
	LAi_ActorTurnToCharacter(pchar, characterFromID("Mishelle"));
	PlaySound("Weather\Thunder_Q.wav");
	DoQuestFunctionDelay("Tieyasal_MishelleDie1", 6.0);
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
}

void Tieyasal_MishelleDie1(string qName) //
{
	PlaySound("Weather\Thunder_Q.wav");
	for (i=1; i<=5; i++)
	{
		CreateLocationParticles("fire_incas_Simple", "monsters", "top"+i, 0.5, 0, 0, "");
		CreateLocationParticles("fire_incas_Simple", "monsters", "top"+i, 1.0, 0, 0, "");
		CreateLocationParticles("fire_incas_Simple", "monsters", "top"+i, 1.5, 0, 0, "");
	}
	for (i=1; i<=3; i++)
	{
		CreateLocationParticles("fire_incas_Simple", "sit", "sit"+i, 0.5, 0, 0, "");
		CreateLocationParticles("fire_incas_Simple", "sit", "sit"+i, 1.0, 0, 0, "");
		CreateLocationParticles("fire_incas_Simple", "sit", "sit"+i, 1.5, 0, 0, "");
	}
	for (i=1; i<=3; i++)
	{
		CreateLocationParticles("fire_incas_Simple", "reload", "reload"+i, 0.5, 0, 0, "");
		CreateLocationParticles("fire_incas_Simple", "reload", "reload"+i, 1.0, 0, 0, "");
		CreateLocationParticles("fire_incas_Simple", "reload", "reload"+i, 1.5, 0, 0, "");
	}
	CreateLocationParticles("fire_incas_Simple", "quest", "top", 0.5, 0, 0, "");
	CreateLocationParticles("fire_incas_Simple", "quest", "top", 1.0, 0, 0, "");
	CreateLocationParticles("fire_incas_Simple", "quest", "top", 1.5, 0, 0, "");
	DoQuestFunctionDelay("Tieyasal_MishelleDie2", 6.0);
}

void Tieyasal_MishelleDie2(string qName) //
{
	PlaySound("VOICE\Russian\DeadmansGod.wav");
	for (i=1; i<=5; i++)
	{
		CreateLocationParticles("fire_incas_Simple", "monsters", "top"+i, 0.5, 0, 0, "");
		CreateLocationParticles("fire_incas_Simple", "monsters", "top"+i, 1.0, 0, 0, "");
		CreateLocationParticles("fire_incas_Simple", "monsters", "top"+i, 1.5, 0, 0, "");
	}
	for (i=1; i<=3; i++)
	{
		CreateLocationParticles("fire_incas_Simple", "sit", "sit"+i, 0.5, 0, 0, "");
		CreateLocationParticles("fire_incas_Simple", "sit", "sit"+i, 1.0, 0, 0, "");
		CreateLocationParticles("fire_incas_Simple", "sit", "sit"+i, 1.5, 0, 0, "");
	}
	for (i=1; i<=3; i++)
	{
		CreateLocationParticles("fire_incas_Simple", "reload", "reload"+i, 0.5, 0, 0, "");
		CreateLocationParticles("fire_incas_Simple", "reload", "reload"+i, 1.0, 0, 0, "");
		CreateLocationParticles("fire_incas_Simple", "reload", "reload"+i, 1.5, 0, 0, "");
	}
	CreateLocationParticles("fire_incas_Simple", "quest", "top", 0.5, 0, 0, "");
	CreateLocationParticles("fire_incas_Simple", "quest", "top", 1.0, 0, 0, "");
	CreateLocationParticles("fire_incas_Simple", "quest", "top", 1.5, 0, 0, "");
	DoQuestFunctionDelay("Tieyasal_MishelleDie3", 6.0);
}

void Tieyasal_MishelleDie3(string qName) //
{
	for (i=1; i<=5; i++)
	{
		CreateLocationParticles("blast_inv", "monsters", "top"+i, 1.0, 0, 0, "");
	}
	for (i=1; i<=3; i++)
	{
		CreateLocationParticles("blast_inv", "sit", "sit"+i, 1.0, 0, 0, "");
	}
	for (i=1; i<=3; i++)
	{
		CreateLocationParticles("blast_inv", "reload", "reload"+i, 1.0, 0, 0, "");
	}
	CreateLocationParticles("blast_inv", "quest", "top", 1.0, 0, 0, "");
	sld = characterFromId("Mishelle");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	PlaySound("Ambient\Teno_inside\teleporter.wav");
	DoQuestFunctionDelay("Tieyasal_MishelleDisappear", 6.0);
}

void Tieyasal_MishelleDisappear(string qName) //
{
	SetMusic("music_teno");
	LAi_SetPlayerType(pchar);
	InterfaceStates.Buttons.Save.enable = true;
	// снимаем все защиты
	DeleteAttribute(pchar, "questTemp.Tieyasal.Defend");
	DeleteAttribute(pchar, "questTemp.Tieyasal.LockLadder");
	DeleteAttribute(pchar, "questTemp.Tieyasal.LockGate");
	// открываем все храмовые локаторы, кроме сокровищницы и храма Кукулькана
	for(int i=1; i<=34; i++)
	{
		if (i == 31) continue;
		LocatorReloadEnterDisable("Tenochtitlan", "reloadTemple"+i, false);
	}
	LocatorReloadEnterDisable("Tenochtitlan", "reloadU1_back", false);
	LocatorReloadEnterDisable("Tenochtitlan", "reloadU2_back", false);
	sld = characterFromId("Urakan");
	sld.greeting = "";
	sld.dialog.currentnode = "urakan_10";
	LAi_CharacterEnableDialog(sld);
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void Tieyasal_FindStoneKey(string qName) // нашли каменный ключ
{
	chrDisableReloadToLocation = false;//открыть локацию
	DeleteAttribute(pchar, "GenQuest.NoDelBody");
	AddQuestRecord("Tieyasal", "27");
}

void Tieyasal_FindTabletItzamna(string qName) // нашли скрижаль Ицамны
{
	sld = ItemsFromID("Tablet_1");
	sld.shown = "0";
}

void Tieyasal_FindTabletChak(string qName) // нашли скрижаль Чака
{
	sld = ItemsFromID("Tablet_3");
	sld.shown = "0";
}

void Tieyasal_UrakanInTemple(string qName) // 
{
	for(int i=1; i<=12; i++)
	{
		sld = characterFromId("Itza_ctz_"+i);
		sld.dialog.currentnode = "itza_ctz_1";
	}
	for(i=2; i<=4; i++)
	{
		LocatorReloadEnterDisable("Tenochtitlan", "reloadTemple3"+i, false);
	}
	pchar.quest.Tieyasal_Treasurereload.win_condition.l1 = "locator";
	pchar.quest.Tieyasal_Treasurereload.win_condition.l1.location = "Tenochtitlan";
	pchar.quest.Tieyasal_Treasurereload.win_condition.l1.locator_group = "reload";
	pchar.quest.Tieyasal_Treasurereload.win_condition.l1.locator = "reloadTemple36";
	pchar.quest.Tieyasal_Treasurereload.function = "Tieyasal_FindTreasureEntrance";
	sld = characterFromId("Urakan");
	sld.greeting = "Urakan";
	LAi_SetWarriorType(sld);
	LAi_warrior_SetStay(sld, true);
	ChangeCharacterAddressGroup(sld, "Temple_great", "quest", "urakan");
}

void Tieyasal_FindTreasureEntrance(string qName) // 
{
	sld = characterFromId("Urakan");
	sld.quest.treasureentrance = "true";
}

void Tieyasal_CheckThreeTablets() // проверяем установку 3 скрижалей в большом храме
{
	ref location = &Locations[FindLocation("Temple_great")];
	if (CheckAttribute(location, "sun") && CheckAttribute(location, "rain") && CheckAttribute(location, "fire"))
	{
		ref sld = ItemsFromID("mask_true");
		sld.shown = "0";
		AddQuestRecord("Tieyasal", "28");
	}
}

void Tieyasal_CheckTwoTablets() // проверяем установку 2 скрижалей для сокровищницы
{
	if (CheckAttribute(pchar, "questTemp.Tieyasal.wartotem") && CheckAttribute(pchar, "questTemp.Tieyasal.tradetotem"))
	{
		DeleteAttribute(pchar, "questTemp.Tieyasal.wartotem");
		DeleteAttribute(pchar, "questTemp.Tieyasal.tradetotem");
		for(int i=5; i<=7; i++)
		{
			LocatorReloadEnterDisable("Tenochtitlan", "reloadTemple3"+i, false);
		}
		PlaySound("Ambient\Teno_inside\big_ring.wav");
		Log_Info(StringFromKey("SharlieFinal_61"));
	}
}

void Tieyasal_MaskTerminationStart() // уничтожение маски
{
	InterfaceStates.Buttons.Save.enable = false;
	bDisableCharacterMenu = true;
	LAi_SetActorType(pchar);
	LAi_ActorGoToLocator(pchar, "goto", "goto1", "Tieyasal_MaskTerminationTurn", -1);
}

void Tieyasal_MaskTerminationGo(string qName)
{
	SetMusic("music_teleport");
	PlaySound("interface\notebook.wav");
	CreateLocationParticles("item", "item", "button04", 0.2, 0, 0, "");
	DoQuestFunctionDelay("Tieyasal_MaskTerminationContinue_1", 7.0);
}

void Tieyasal_MaskTerminationContinue_1(string qName)
{
	PlaySound("Weather\Thunder_Q.wav");
	CreateLocationParticles("fire_incas", "item", "button04", 0.5, 0, 0, "");
	DoQuestFunctionDelay("Tieyasal_MaskTerminationContinue_2", 7.0);
}

void Tieyasal_MaskTerminationContinue_2(string qName)
{
	PlaySound("Weather\koster_001.wav");
	CreateLocationParticles("fire_incas", "item", "button04", 0.4, 0, 0, "");
	CreateLocationParticles("fire", "item", "button04", 0.1, 0, 0, "");
	DoQuestFunctionDelay("Tieyasal_MaskTerminationContinue_3", 7.0);
}

void Tieyasal_MaskTerminationContinue_3(string qName)
{
	PlaySound("Ambient\Teno_inside\big_ring.wav");
	CreateLocationParticles("fire_incas", "item", "button04", 0.3, 0, 0, "");
	CreateLocationParticles("smoke", "item", "button04", 0.1, 0, 0, "");
	DoQuestFunctionDelay("Tieyasal_MaskTerminationContinue_4", 7.0);
}

void Tieyasal_MaskTerminationContinue_4(string qName)
{
	PlaySound("Ambient\Teno_inside\big_ring.wav");
	CreateLocationParticles("blast_inv", "item", "button04", 0.2, 0, 0, "Boom");
	CreateLocationParticles("blast_inv", "item", "button04", 0.2, 0, 0, "Boom");
	CreateLocationParticles("large_smoke", "item", "button04", 0.1, 0, 0, "Boom");
	DoQuestFunctionDelay("Tieyasal_MaskTerminationEnd", 3.5);
}

void Tieyasal_MaskTerminationEnd(string qName)
{
	SetLaunchFrameFormParam(StringFromKey("SharlieFinal_62", NewStr()), "", 0, 4);
	LaunchFrameForm();
	DoQuestFunctionDelay("Tieyasal_MaskTerminationReload", 4);
	// убираем партиклы
	int n = Findlocation("Temple_great");
	DeleteAttribute(&locations[n], "sun");
	DeleteAttribute(&locations[n], "rain");
	DeleteAttribute(&locations[n], "fire");
	// разрушаем порталы
	ref rItm = ItemsFromID("dolly0");
	rItm.shown = false;
	ref rItem = ItemsFromID("dolly5");
	rItem.shown = false;
	// Круглый храм
	n = Findlocation("Temple_round");
	locations[n].models.always.dolly = "dolly_F";
	locations[n].models.always.locators = "TempleRoundInside_F_locators";
	// Мэйн
	n = Findlocation("Pearl_Jungle_03");
	DeleteAttribute(&locations[n], "dolly");
	DeleteAttribute(&locations[n], "canteleport");
	DeleteAttribute(&locations[n], "models.always.bracing");
	locations[n].models.always.dolly = "dolly_F";
	locations[n].models.always.dolly.locator.group = "item";
	locations[n].models.always.dolly.locator.name = "dolly1";
	// LSC
	n = Findlocation("UnderWater");
	DeleteAttribute(&locations[n], "dolly");
	DeleteAttribute(&locations[n], "canteleport");
	locations[n].models.always.dolly = "dolly_F";
	locations[n].models.always.dolly.locator.group = "item";
	locations[n].models.always.dolly.locator.name = "dolly2";
	// Доминика
	n = Findlocation("Dominica_Jungle_02");
	DeleteAttribute(&locations[n], "dolly");
	DeleteAttribute(&locations[n], "canteleport");
	locations[n].models.always.dolly = "dolly_F";
	locations[n].models.always.dolly.locator.group = "item";
	locations[n].models.always.dolly.locator.name = "dolly3";
	sld = ItemsFromID("mask_false");
	sld.price = 10000;
}

void Tieyasal_MaskTerminationReload(string qName)
{
	sld = characterFromId("Urakan");
	sld.greeting = "";
	for(int i=1; i<=8; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Itza_actor_"+i, "itza_"+(rand(7)+1), "man", "man", 30, PIRATE, -1, false, "native"));
		FantomMakeCoolFighter(sld, 30, 100, 100, RandPhraseSimple("topor_01","blade_02"), "", "", 100);
		ChangeCharacterAddressGroup(sld, "Temple_great", "monsters", "guard"+i);
		LAi_CharacterDisableDialog(sld);
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		LAi_SetImmortal(sld, true);
		LAi_group_MoveCharacter(sld, "TMP_FRIEND");
	}
	InterfaceStates.Buttons.Save.enable = true;
	bDisableCharacterMenu = false;
	DoQuestReloadToLocation("Temple_great", "goto", "goto1", "Tieyasal_UrakanLastTalk");
}

void Tieyasal_Win_IndianBead()
{
	LAi_SetActorType(pchar);
	sld = characterFromId("Urakan");
	LAi_CharacterDisableDialog(sld);
	LAi_SetActorType(sld);
	LAi_ActorAnimation(sld, "Bead", "", 5.0);
	for(int i=1; i<=8; i++)
	{
		sld = characterFromId("Itza_actor_"+i);
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "Bead", "", 5.0);
	}
	PlaySound("interface\abordage_wining.wav");
	PlaySound("interface\abordage_wining.wav");
	DoQuestFunctionDelay("Tieyasal_Win_TempleFinal", 5.0);
}

void Tieyasal_Win_TempleFinal(string qName)
{
	LAi_SetPlayerType(pchar);
	sld = characterFromId("Urakan");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "TMP_FRIEND");
	for(int i=1; i<=8; i++)
	{
		sld = characterFromId("Itza_actor_"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "TMP_FRIEND");
	}
	AddQuestRecord("Tieyasal", "29");
	// очищаем джунгли от засад ица
	for (i=0; i<MAX_LOCATIONS; i++)
	{				
		if (CheckAttribute(&locations[i], "ItzaLand"))
		{
			DeleteAttribute(&locations[i], "ItzaLand");
		}
	}
	LocatorReloadEnterDisable("Tenochtitlan", "reload1_back", false); // открываем выход
	LocatorReloadEnterDisable("Tayasal_jungle_11", "reload3_back", false); // закрываем Тайясаль со стороны джунглей
	DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
	setCharacterShipLocation(pchar, "Shore_ship2"));
	setWDMPointXZ("Shore_ship2"); // ставим корабль
	pchar.quest.Tieyasal_Returnshore.win_condition.l1 = "location";
	pchar.quest.Tieyasal_Returnshore.win_condition.l1.location = "Shore_ship2";
	pchar.quest.Tieyasal_Returnshore.function = "Tieyasal_InSeaShore";
	pchar.questTemp.Tieyasal = "home";
	pchar.GenQuest.Hunter2Pause = true; 
}

void Tieyasal_InSeaShore(string qName) // победный финал
{
	pchar.GenQuest.Hunter2Pause = true;
	LocatorReloadEnterDisable("Tayasal_jungle_09", "reload3_back", true); // закрываем джунгли у Тайясаля
	LocatorReloadEnterDisable("Tayasal_jungle_07", "reload2_back", true); // patch-5
	RemoveItems(pchar, "stonekey", 1);
	pchar.questTemp.Tieyasal_final = "true";
	if (CheckAttribute(pchar, "questTemp.Tieyasal.Teleport")) DoQuestFunctionDelay("Tieyasal_InSeaShoreTime", 1.2);
	else DoQuestFunctionDelay("Tieyasal_InSeaShore_Continue", 0.5);
}

void Tieyasal_InSeaShoreTime(string qName)
{
	SetLaunchFrameFormParam(StringFromKey("SharlieFinal_63", NewStr()), "", 0, 5);
	WaitDate("", 0, 0, 7, 3, 10); 
	LaunchFrameForm();
	RefreshLandTime();
	RecalculateJumpTable();
	Whr_UpdateWeather();
	DoQuestFunctionDelay("Tieyasal_InSeaShore_Continue", 5.5);
}

void Tieyasal_InSeaShore_Continue(string qName) // победный финал 
{
	StartQuestMovie(true, false, true);
	LAi_SetActorType(pchar);
	LAi_ActorGoToLocator(pchar, "quest", "hero", "Tieyasal_FinalChoise", -1);
}

//=================================================================
//======================кейсы из quests_reaction===================
//=================================================================
bool SharlieFinal_QuestComplete(string sQuestName, string qname)
{
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//Jason------------------------------------ Суп из черепахи --------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////////////

	ref sld, chr;
	int iTemp, i, n, idx, iRank, iScl, iAddTime;
    float locx, locy, locz, fMft;
	string sTemp;
	
	bool condition = true;
	
	if (sQuestName == "Terrapin_LevasserCaveDied")
	{
		LAi_group_Delete("EnemyFight");
		chrDisableReloadToLocation = false;//открыть локацию
		AddQuestRecord("Terrapin", "10");
		pchar.questTemp.Terrapin = "done";
		sld = characterFromId("Tortuga_Mayor");
		LAi_NoRebirthEnable(sld); // респавнился, гад 
		pchar.questTemp.Sharlie.DelTerGuard = "true"; // убираем пиратскую эскадру
		ChangeCharacterComplexReputation(pchar, "authority", 10);
		ChangeOfficersLoyality("good_all", 2);
		AddCrewMorale(pchar, 10);
		AddComplexSelfExpToScill(200, 200, 200, 200);
		AddCharacterExpToSkill(pchar, "Fortune", 400);//везение
		AddCharacterExpToSkill(pchar, "Sneak", 500);//скрытность
		SetFunctionTimerCondition("Terrapin_ReturnFox", 0, 0, 3, false); // Фокса на место fix 160912
	}
	else if (sQuestName == "Terrapin_LevasserRoomEnter")
	{
		LAi_SetPlayerType(pchar);
		PlaySound("Ambient\LAND\door_001.wav");
		PlaySound("Ambient\LAND\door_004.wav");
		iRank = 25+MOD_SKILL_ENEMY_RATE*2;
		iScl = 65;
		// сам Левассер
		sld = characterFromId("Tortuga_Mayor");
		sld.dialog.FileName = "Quest\Sharlie\Terrapin.c";
		sld.dialog.currentnode = "levasser_room";
		sld.greeting = "Levasser";
		ChangeCharacterAddressGroup(sld, "Tortuga_tavern_upstairs", "reload", "reload1_back");
		LAi_SetImmortal(sld, false);
		sld.SaveItemsForDead = true;
		sld.DontClearDead = true;
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		// гарды
		for (i=1; i<=2; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("TerrapinGuard"+i, "sold_fra_"+i, "man", "man", iRank, FRANCE, -1, true, "quest"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_21", "pistol6", "bullet", iScl*2);
			ChangeCharacterAddressGroup(sld, "Tortuga_tavern_upstairs", "quest", "quest"+i);
			LAi_SetWarriorType(sld);
			LAi_warrior_SetStay(sld, true);
			LAi_warrior_DialogEnable(sld, false);
		}
		// заполним сундук в гроте
		pchar.GenQuestBox.Tortuga_town = true;
		pchar.GenQuestBox.Tortuga_town.box1.items.totem_03 = 1;
		pchar.GenQuestBox.Tortuga_town.box1.items.cannabis7 = 1;
		pchar.GenQuestBox.Tortuga_town.box1.items.purse2 = 5; // Addon-2016 Jason
		pchar.GenQuestBox.Tortuga_town.box1.items.map_tortuga = 1;
		pchar.GenQuestBox.Tortuga_town.box1.items.indian_11 = 1;
		pchar.GenQuestBox.Tortuga_town.box1.items.potion2 = 20;
		pchar.GenQuestBox.Tortuga_town.box1.items.potion7 = 1;
		pchar.GenQuestBox.Tortuga_town.box1.items.potionwine = 10;
		pchar.GenQuestBox.Tortuga_town.box1.items.mineral2 = 1;
		pchar.GenQuestBox.Tortuga_town.box1.items.mineral3 = 20;
		pchar.GenQuestBox.Tortuga_town.box1.items.mineral5 = 1;
		pchar.GenQuestBox.Tortuga_town.box1.items.mineral6 = 1;
		pchar.GenQuestBox.Tortuga_town.box1.items.mineral9 = 1;
		pchar.GenQuestBox.Tortuga_town.box1.items.mineral11 = 1;
		pchar.GenQuestBox.Tortuga_town.box1.items.mineral17 = 10;
		pchar.GenQuestBox.Tortuga_town.box1.items.mineral19 = 1;
		pchar.GenQuestBox.Tortuga_town.box1.items.mineral35 = 1;
	}
	else if (sQuestName == "Terrapin_LevasserRoomDied")
	{
		chrDisableReloadToLocation = false;//открыть локацию
		LocatorReloadEnterDisable("Tortuga_tavern", "reload2_back", true); // закроем комнату снаружи
		LocatorReloadEnterDisable("Tortuga_tavern_upstairs", "reload1_back", true);//закрыть выход
		pchar.GenQuest.CannotWait = true;//запрет ожидания
		n = Findlocation("Tortuga_town");
		locations[n].models.always.roof_details = "Margarita_GPK_roof_details";  //Экку Korsar - выставляем детали для бега по крыше от новой Маргариты
		locations[n].models.day.charactersPatch = "Margarita_patch_roof"; 
		locations[n].models.night.charactersPatch = "Margarita_patch_roof"; // подменяем патч для персонажа
		LAi_LocationDisableOfficersGen("Tortuga_Town", true);//офицеров не пускать
		pchar.questTemp.Terrapin = "roof";
		DoQuestCheckDelay("hide_weapon", 1.0);//убрать оружие
		DoQuestCheckDelay("TalkSelf_Quest", 1.0);
		sld = characterFromId("Tortuga_Mayor");
		LAi_NoRebirthEnable(sld); // респавнился, гад 
		pchar.questTemp.Sharlie.DelTerGuard = "true"; // убираем пиратскую эскадру
		ChangeCharacterComplexReputation(pchar, "authority", 10);
		ChangeOfficersLoyality("good_all", 2);
		AddCrewMorale(pchar, 10);
		AddComplexSelfExpToScill(250, 250, 250, 250);
		AddCharacterExpToSkill(pchar, "Fortune", 500);//везение
		AddCharacterExpToSkill(pchar, "Sneak", 400);//скрытность
	}
	else if (sQuestName == "Terrapin_GoWindow")
	{
		pchar.quest.Terrapin_window.win_condition.l1 = "locator";
		pchar.quest.Terrapin_window.win_condition.l1.location = "Tortuga_tavern_upstairs";
		pchar.quest.Terrapin_window.win_condition.l1.locator_group = "reload";
		pchar.quest.Terrapin_window.win_condition.l1.locator = "reload_window";
		pchar.quest.Terrapin_window.function = "Terrapin_GotoWindow";
		pchar.questTemp.Terrapin = "roofgo"; // 021012
	}
	else if (sQuestName == "Terrapin_FirstShot") // мушкетер стреляет
	{
		sld = CharacterFromID("TerrapinMush"+sTotalTemp);
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "shot", "Terrapin_FirstShot_1", 1.0);
	}
	else if (sQuestName == "Terrapin_FirstShot_1") // мушкетер попал в ГГ
	{
		sld = CharacterFromID("TerrapinMush1");
		LAi_SetWarriorType(sld);
		LAi_warrior_SetStay(sld, true);
		LAi_SetActorType(pchar);
		LAi_ActorAnimation(pchar, "hit_fire", "pchar_back_to_player", 0.8);
		CreateLocationParticles("blood_big", "quest", "shot"+sTotalTemp, 2.0, 0, 0, "");
		LAi_ApplyCharacterDamage(pchar, 150, "fire");
		LAi_CheckKillCharacter(pchar);
	}
	else if (sQuestName == "Terrapin_GirlShot") // застрелили девушку
	{
		CreateLocationParticles("blood_big", "quest", "roof", 2.0, 0, 0, "");
		CreateLocationParticles("blood_big", "quest", "roof", 1.8, 0, 0, "");
		sld = CharacterFromID("TerrapinRoofGirl");
		LAi_KillCharacter(sld);
		DoQuestCheckDelay("Terrapin_GirlShot_1", 1.5);
	}
	else if (sQuestName == "Terrapin_GirlShot_1") // 
	{
		LAi_SetActorType(pchar);
		LAi_ActorTurnToLocator(pchar, "quest", "mushketer2"); 
		sld = CharacterFromID("TerrapinMush2");
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "shot", "Terrapin_SecondShot", 1.0);
	}
	else if (sQuestName == "Terrapin_SecondShot") // мушкетер попал в ГГ
	{
		sld = CharacterFromID("TerrapinMush2");
		LAi_SetWarriorType(sld);
		LAi_warrior_SetStay(sld, true);
		LAi_SetActorType(pchar);
		LAi_ActorAnimation(pchar, "hit_fire", "pchar_back_to_player", 1.0);
		CreateLocationParticles("blood_big", "quest", "roof", 2.0, 0, 0, "");
		LAi_ApplyCharacterDamage(pchar, 150, "fire");
		LAi_CheckKillCharacter(pchar);
		// ставим горожанина
		sld = GetCharacter(NPC_GenerateCharacter("TerrapinRoofMan", "citiz_15", "man", "man", 25, FRANCE, -1, true, "quest"));
		FantomMakeCoolFighter(sld, 25, 65, 65, "blade_10", "pistol1", "bullet", 100);
		LAi_SetWarriorType(sld);
		LAi_warrior_SetStay(sld, true);
		LAi_warrior_DialogEnable(sld, true);
		ChangeCharacterAddressGroup(sld, "Tortuga_town", "quest", "roof2");
		LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
		LAi_LocationFightDisable(&Locations[FindLocation("Tortuga_town")], false);//разрешить драться
		sTotalTemp = "3";
	}
	else if (sQuestName == "Terrapin_TiboDied") // убили Тибо
	{
		LAi_group_Delete("EnemyFight");
		pchar.GenQuest.Notsearchbody = true; // не обыскивать до разговора с Кати
		sld = characterFromId("Kathy");
		LAi_CharacterEnableDialog(sld);
		LAi_SetActorType(sld);
		LAi_SetActorType(pchar);
		LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
		LAi_ActorTurnToCharacter(sld, pchar);
		SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
		AddComplexSelfExpToScill(100, 100, 100, 100);
	}
	else if (sQuestName == "LevasserDiedResidence") // убили Левассера в резиденции при штурме города
	{
		LAi_group_Delete("EnemyFight");
		chrDisableReloadToLocation = false;//открыть локацию
		sld = characterFromId("Tortuga_Mayor");
		LAi_NoRebirthEnable(sld); // респавнился, гад 
		pchar.questTemp.Sharlie.DelTerGuard = "true"; // убираем пиратскую эскадру
		ChangeCharacterComplexReputation(pchar, "authority", 5);
		ChangeOfficersLoyality("good_all", 1);
		AddCrewMorale(pchar, 5);
		AddComplexSelfExpToScill(100, 100, 100, 100);
		pchar.questTemp.Sharlie.LevasserDied = "true";
		AddQuestRecord("Sharlie", "32");
		Achievment_Set("ach_CL_121");
	}
	else if (sQuestName == "DefendSP_VideoSiege") // ролик
	{
		PChar.GenQuest.VideoAVI = "Siege";
		PChar.GenQuest.VideoAfterQuest = "DefendSP_continueSiege";
		DoQuestCheckDelay("PostVideo_Start", 0.2);
	}
	else if (sQuestName == "DefendSP_continueSiege") 
	{
		DoQuestReloadToLocation("Shore38", "reload", "sea", "DefendSP_SetInJungle");
		setCharacterShipLocation(pchar, "Shore38");
		setWDMPointXZ("Shore38"); // корабль в бухту Ламантен
	}
	else if (sQuestName == "DefendSP_SetInJungle") // ставим ГГ и его солдат в бухту
	{
		LocatorReloadEnterDisable("Shore38", "boat", true); // закрыть выход в море
		pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу
		pchar.GenQuest.CannotWait = true;//запрет ожидания
		// устанавливаем солдат ГГ, 12 рыл+офицер
		iRank = 25+MOD_SKILL_ENEMY_RATE*2;
		iScl = 60;
		for (i=0; i<=12; i++)
		{
			if (i == 0)
			{
				sld = GetCharacter(NPC_GenerateCharacter("DefendSP_soldier_"+i, "mercen_26", "man", "man", iRank+5, FRANCE, -1, true, "soldier"));
				FantomMakeCoolFighter(sld, iRank+5, iScl+5, iScl+5, "blade_13", "pistol4", "bullet", iScl*2+100);
				sld.name = StringFromKey("SharlieFinal_64");
				sld.lastname = StringFromKey("SharlieFinal_65");
				sld.dialog.FileName = "Quest\Sharlie\OtherNPC.c";
				sld.dialog.currentnode = "rosetti";
			}
			else
			{
				if (i == 9 || i == 12)
				{
					sld = GetCharacter(NPC_GenerateCharacter("DefendSP_soldier_"+i, "mush_ctz_"+(4+rand(2)), "man", "mushketer", iRank, FRANCE, -1, false, "soldier"));
					FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket2", "cartridge", iScl*2);
				}
				else
				{
					sld = GetCharacter(NPC_GenerateCharacter("DefendSP_soldier_"+i, "citiz_"+(31+rand(9)), "man", "man", iRank, FRANCE, -1, true, "soldier"));
					FantomMakeCoolFighter(sld, iRank, iScl, iScl, RandPhraseSimple("blade_10","blade_11"), "pistol1", "bullet", iScl*2);
				}
				LAi_CharacterDisableDialog(sld);
			}
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "Shore38", "rld", "loc"+i);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
	}
	else if (sQuestName == "DefendSP_GoJungle")
	{
		sld = CharacterFromID("Blaze");
		sld.dialog.currentnode = "first time";
		LAi_SetActorType(pchar);
		SetMainCharacterIndex(GetCharacterIndex("Blaze"));
		PChar = GetMainCharacter();			
		LAi_SetPlayerType(PChar);
		sld = characterFromId("DefendSP_soldier_0");
		sld.dialog.currentnode = "rosetti_2";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 0.5);
	}
	else if (sQuestName == "DefendSP_GateAlarm") // тревога поднята
	{
		pchar.questTemp.Sharlie.DefendSP.GateAlarm = true;
	}
	else if (sQuestName == "DefendSP_SpaPatrolDie")
	{
		chrDisableReloadToLocation = false;//открыть локацию
		LAi_group_Delete("EnemyFight");
		// прерывание на выход из города
		pchar.quest.DefendSP_jungle2.win_condition.l1 = "location";
		pchar.quest.DefendSP_jungle2.win_condition.l1.location = "FortFrance_ExitTown";
		pchar.quest.DefendSP_jungle2.function = "DefendSP_SpainAvanpost";
		DefendSP_CatchOurSoldiers();
		AddComplexSelfExpToScill(100, 100, 100, 100);
	}
	else if (sQuestName == "DefendSP_SpaAvanpostAttack")
	{
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "DefendSP_SpaAvanpostDie");
	}
	else if (sQuestName == "DefendSP_SpaAvanpostDie")
	{
		chrDisableReloadToLocation = false;//открыть локацию
		LocatorReloadEnterDisable("FortFrance_ExitTown", "reload2_back", true); // закрыть форт
		locations[FindLocation("FortFrance_Town")].QuestCapture = true;
		locations[FindLocation("FortFrance_Town")].hidden_fire = true;
		locations[FindLocation("FortFrance_Town")].hidden_sound = true;
		LAi_group_Delete("EnemyFight");
		// прерывание на город
		pchar.quest.DefendSP_jungle3.win_condition.l1 = "location";
		pchar.quest.DefendSP_jungle3.win_condition.l1.location = "FortFrance_Town";
		pchar.quest.DefendSP_jungle3.function = "DefendSP_TownBattle";
		AddQuestRecord("Sharlie", "33");
		DefendSP_CatchOurSoldiers();
		AddComplexSelfExpToScill(250, 250, 250, 250);
	}
	else if (sQuestName == "DefendSP_SpaTownDie")
	{
		LAi_group_Delete("EnemyFight");
		pchar.quest.DefendSP_town1.win_condition.l1 = "locator";
		pchar.quest.DefendSP_town1.win_condition.l1.location = "FortFrance_Town";
		pchar.quest.DefendSP_town1.win_condition.l1.locator_group = "reload";
		pchar.quest.DefendSP_town1.win_condition.l1.locator = "reloadPr1";
		pchar.quest.DefendSP_town1.function = "DefendSP_GotoMatieBase";
		pchar.quest.DefendSP_town2.win_condition.l1 = "location";
		pchar.quest.DefendSP_town2.win_condition.l1.location = "FortFrance_Dungeon";
		pchar.quest.DefendSP_town2.function = "DefendSP_BaseBattle";
		AddQuestRecord("Sharlie", "34");
		locations[FindLocation("FortFrance_Dungeon")].QuestCapture = true;
		sld = ItemsFromID("MaltieBase_keys");
		sld.shown = true;
		sld.startLocation = "FortFrance_Dungeon";
		sld.startLocator = "item"+(rand(4)+1); // ключ от камеры Мишеля
		DefendSP_CatchOurSoldiers();
		AddComplexSelfExpToScill(400, 400, 400, 400);
	}
	else if (sQuestName == "DefendSP_SpaBaseDie")
	{
		LAi_group_Delete("EnemyFight");
		sld = characterFromId("Mishelle");
		sld.dialog.currentnode = "Base_afterfight";
		AddQuestRecord("Sharlie", "35");
		DefendSP_CatchOurSoldiers();
		AddComplexSelfExpToScill(250, 250, 250, 250);
	}
	else if (sQuestName == "DefendSP_PrepareFortAttack")
	{
		// ставим мальтийцев
		iRank = 25+MOD_SKILL_ENEMY_RATE*2;
		iScl = 60;
		for (i=1; i<=7; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("DefendSP_frafort_"+i, "sold_fra_"+(rand(7)+9), "man", "man", iRank, FRANCE, 1, true, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, RandPhraseSimple("blade_12","blade_14"), "pistol1", "bullet", iScl*2);
			LAi_CharacterDisableDialog(sld);
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(sld, "FortFrance_Exittown", "rld", "aloc"+i);
		}
		// ставим Мишеля
		sld = characterFromId("Mishelle");
		sld.dialog.currentnode = "Fort_attack";
		ChangeCharacterAddressGroup(sld, "FortFrance_Exittown", "rld", "aloc10");
		GiveItem2Character(sld, "blade_13");
		sld.equip.blade = "blade_13";
		GiveItem2Character(sld, "pistol4");
		EquipCharacterbyItem(sld, "pistol4");
		LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
		TakeNItems(sld, "bullet", 50);
		AddItems(sld, "gunpowder", 50);
		TakeNItems(sld, "potion2", 10);
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	else if (sQuestName == "DefendSP_SpaFortDie")
	{
		LAi_group_Delete("EnemyFight");
		sld = characterFromId("Mishelle");
		sld.dialog.currentnode = "Fort_attack_2";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		DefendSP_CatchOurSoldiers();
		AddComplexSelfExpToScill(150, 150, 150, 150);
	}
	else if (sQuestName == "DefendSP_OpenExit")
	{
		LocatorReloadEnterDisable("FortFrance_town", "reload1_back", false);
		LocatorReloadEnterDisable("FortFrance_town", "reload2_back", false);
		LocatorReloadEnterDisable("FortFrance_town", "reload_gate", false);
		SetFunctionTimerCondition("DefendSP_AllClear", 0, 0, 1, false);
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	//Jason--------------------------------------- В поисках Стража Истины ------------------------------------
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	else if (sQuestName == "GuardOT_MCthink")
	{
		LAi_SetPlayerType(pchar);
		DoQuestCheckDelay("TalkSelf_Quest", 0.5);
	}
	else if (sQuestName == "GuardOT_ArriveBeach")
	{
		DoQuestCheckDelay("TalkSelf_Quest", 1.5);
		pchar.quest.GuardOT_gotobaster.win_condition.l1 = "location";
		pchar.quest.GuardOT_gotobaster.win_condition.l1.location = "Baster_town";
		pchar.quest.GuardOT_gotobaster.function = "GuardOT_EnterInTown";
	}
	else if (sQuestName == "GuardOT_ArriveGaleon")
	{
		// для умников :)
		if (sti(environment.time) < 21 && sti(environment.time) > 3)
		{
			int iTime = sti(environment.time);
			if (iTime >= 21) iAddTime = 24 - iTime + 21;
			if (iTime < 7) iAddTime = 21 - iTime;
			if (iTime >= 7 && iTime < 21) iAddTime = 24  + 21 - iTime;
			StoreDayUpdate();
			WaitDate("",0,0,0,iAddtime,5);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
		}
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		pchar.GenQuest.CantRun = true;
		CheckAndSetOverloadMode(GetMainCharacter()); // бег запрещаем
		InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться
		pchar.questTemp.Guardoftruth = "galeon";
		pchar.questTemp.Guardoftruth.Attack = "true";
		pchar.GenQuest.Notsearchbody = true;
		LAi_LockFightMode(pchar, true);
		DoQuestCheckDelay("GuardOT_ArriveGaleonSetMusic", 1.0);
		// ставим Марше
		sld = characterFromId("GOT_Marshe");
		sld.dialog.currentnode = "marshe_lay";
		LAi_CharacterDisableDialog(sld);//запрет диалога
		LAi_SetImmortal(sld, false);
		ChangeCharacterAddressGroup(sld, "Deck_Galeon_Ship", "quest", "lay");
		LAi_SetLayType(sld);
		LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, true, "GuardOT_MarsheEscape");
		RemoveAllCharacterItems(sld, true);
		// ставим вахтенных
		iRank = 25+MOD_SKILL_ENEMY_RATE*2;
		iScl = 65;
		for (i=1; i<=8; i++)
		{
			if (i == 5)
			{
				sld = GetCharacter(NPC_GenerateCharacter("GuardOT_galeonguard_"+i, "mercen_25", "man", "man", iRank+5, PIRATE, -1, true, "soldier"));
				FantomMakeCoolFighter(sld, iRank+5, iScl+5, iScl+5, "blade_16", "pistol5", "bullet", iScl*2+50);
			}
			else
			{
				sld = GetCharacter(NPC_GenerateCharacter("GuardOT_galeonguard_"+i, "citiz_"+(rand(9)+31), "man", "man", iRank, PIRATE, -1, true, "soldier"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_12", "pistol1", "bullet", iScl*2);
			}
			sld.dialog.FileName = "Quest\Sharlie\Guardoftruth.c";
			sld.dialog.currentnode = "galeonguard";
			sld.DontClearDead = true;
			ChangeCharacterAddressGroup(sld, "Deck_Galeon_Ship", "quest", "quest"+i);
			LAi_SetGuardianType(sld);
			LAi_group_MoveCharacter(sld, "GaleonFight");
			LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "GuardOT_GaleonGuardFight");
			LAi_SetCheckMinHP(pchar, LAi_GetCharacterHP(pchar)-1, false, "GuardOT_GaleonGuardFight");
		}
		LAi_group_SetRelation("GaleonFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_SetLookRadius("GaleonFight", 8.2);
		LAi_group_SetHearRadius("GaleonFight", 0.1);
		LAi_group_SetSayRadius("GaleonFight", 7.0);
		LAi_group_SetCheck("GaleonFight", "GuardOT_GaleonGuardDelete");
	}
	else if (sQuestName == "GuardOT_ArriveGaleonSetMusic")
	{
		SetMusic("music_q_battle");
		DoQuestCheckDelay("TalkSelf_Quest", 0.5);
	}
	else if (sQuestName == "GuardOT_GaleonGuardFight")
	{
		PlaySound("VOICE\Russian\EvilPirates01.wav");
		DeleteAttribute(pchar, "GenQuest.CantRun");
		CheckAndSetOverloadMode(GetMainCharacter());
		DeleteAttribute(pchar, "questTemp.Guardoftruth.Attack");
		GuardOT_GaleonGuardFightAdd();
		sld = characterFromId("GOT_Marshe");
		if (sld.location.locator == "lay") // если спит
		{
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, true);
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Deck_Galeon_Ship", "goto", "stand");
			LAi_ActorAfraid(sld, pchar, false);
		}
		LAi_RemoveCheckMinHP(pchar);
		for (i=1; i<=8; i++)
		{
			sld = characterFromId("GuardOT_galeonguard_"+i);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "GaleonFight");
		}
		LAi_group_FightGroups("GaleonFight", LAI_GROUP_PLAYER, true);
		LAi_SetFightMode(pchar, true);
	}
	else if (sQuestName == "GuardOT_MarsheEscape")
	{
		PlaySound("VOICE\Russian\EvilPirates02.wav");
		sld = characterFromId("GOT_Marshe");
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, "Deck_Galeon_Ship", "goto", "stand");
		LAi_ActorAfraid(sld, pchar, false);
		DoQuestCheckDelay("GuardOT_GaleonGuardFight", 1.8);
	}
	else if (sQuestName == "GuardOT_GaleonGuardDelete")
	{
		LAi_group_Delete("GaleonFight");
		DoQuestCheckDelay("hide_weapon", 1.0);
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
		if (CheckAttribute(pchar, "questTemp.Guardoftruth.Attack")) // все тихо
		{
			DeleteAttribute(pchar, "questTemp.Guardoftruth.Attack");
			DeleteAttribute(pchar, "GenQuest.CantRun");
			CheckAndSetOverloadMode(GetMainCharacter());
			LAi_RemoveCheckMinHP(pchar);
			sld = characterFromId("GOT_Marshe");
			LAi_CharacterEnableDialog(sld);
			LAi_RemoveCheckMinHP(sld);
			AddCharacterExpToSkill(pchar, "Sneak", 1000);
		}
		else
		{
			sld = characterFromId("GOT_Marshe");
			LAi_SetStayType(sld);
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "marshe_sitground";
		}
	}
	else if (sQuestName == "GuardOT_HuntersDie")
	{
		LAi_group_Delete("EnemyFight");
		chrDisableReloadToLocation = false;//открыть локацию
		AddQuestRecord("Guardoftruth", "26");
		AddComplexSelfExpToScill(180, 180, 180, 180);
	}
	else if (sQuestName == "GuardOT_CumanaCaveBandosDie")
	{
		LAi_group_Delete("EnemyFight");
		DoQuestCheckDelay("hide_weapon", 1.5);
		sld = characterFromId("GOT_Bart");
		sld.dialog.currentnode = "barty_5";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		AddComplexSelfExpToScill(100, 100, 100, 100);
	}
	else if (sQuestName == "GuardOT_BartyEscape")
	{
		n = 0;
		for(i=0; i<=4; i++)
		{
			sld = characterFromId("GOT_bandos_"+i);
			if (LAi_GetCharacterHP(sld) <= 0) n++;
		}
		sld = characterFromId("GOT_Bart");
		sld.dialog.currentnode = "barty_5";
		LAi_SetActorType(sld);
		RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
		RemoveCharacterEquip(sld, GUN_ITEM_TYPE);
		if (n < 5) // остались живые враги
		{
			LAi_ActorAnimation(sld, "afraid", "GuardOT_BartyEscape1", -1);
		}
		else
		{
			DoQuestCheckDelay("hide_weapon", 0.5);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		}
	}
	else if (sQuestName == "GuardOT_BartyEscape1")
	{
		sld = characterFromId("GOT_Bart");
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "afraid", "GuardOT_BartyEscape2", -1);
	}
	else if (sQuestName == "GuardOT_BartyEscape2")
	{
		sld = characterFromId("GOT_Bart");
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "afraid", "GuardOT_BartyEscape1", -1);
	}
	// belamour legendary edition -->
	else if (sQuestName == "RIP_Sosa") 
	{
		SendMessage(pchar, "lsl", MSG_CHARACTER_EX_MSG, "GunBelt", true);
		sld = characterFromId("GOT_Bart");
		LAi_SetImmortal(sld, false);
		LAi_KillCharacter(sld);
		ChangeCharacterComplexReputation(pchar, "nobility", -5);
		AddCharacterExpToSkill(pchar, "Sneak", 600);
		AddCharacterExpToSkill(pchar, "FencingL", 300);
		AddCharacterExpToSkill(pchar, "FencingS", 300);
		AddCharacterExpToSkill(pchar, "FencingH", 300);
		AddCharacterExpToSkill(pchar, "Pistol", 300);
		chrDisableReloadToLocation = false;//открыть локацию
		LAi_LocationDisableOfficersGen("Cumana_CaveEntrance", false);//офицеров пускать
		locations[FindLocation("Cumana_CaveEntrance")].DisableEncounters = false; //энкаутеры открыть
		locations[FindLocation("Cumana_Cave")].DisableEncounters = false; // patch
		LAi_LocationFightDisable(&Locations[FindLocation("Cumana_CaveEntrance")], false);//разрешить драться
		DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
		LocatorReloadEnterDisable("Cumana_CaveEntrance", "reload2_back", false);
		sld = characterFromId("GOT_Belinda");
		sld.dialog.currentnode = "Belinda_17";
		AddQuestRecord("Guardoftruth", "32");
		LAi_SetPlayerType(pchar);
		Achievment_SetStat(95, 1);
	}
	else if (sQuestName == "GuardOT_ClearMayakPatrol")
	{
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
		chrDisableReloadToLocation = false;//открыть локацию
		Map_NationQuestHunter(SPAIN); // немного развлечений
		SetTimerCondition("Map_SetNationCoolHanters", 0, 0, 4, false); // ещё немного развлечений
	}
	else if (sQuestName == "GuardOT_SpaOfficerInTavern")
	{
		/* if(CheckAttribute(pchar, "IsMushketer"))
		{
			SetMainCharacterToMushketer("", false);
		} */
		FreeSitLocator("Santiago_tavern", "sit_base4");
		DoQuestReloadToLocation("Santiago_tavern", "sit", "sit_base4", "");			
		sld = characterFromID("spa_baseprisoner");
		LAi_SetActorType(sld);
		LAi_ActorSetSitMode(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.5);
	}
	else if (sQuestName == "GuardOT_SpaOfficerOutTavern")
	{
		chrDisableReloadToLocation = false;
		LAi_LocationFightDisable(&Locations[FindLocation("Santiago_town")], false);//разрешить драться
		LAI_SetPlayerType(pchar);           
		DoQuestReloadToLocation("Santiago_tavern", "tables", "stay5", "");
		sld = CharacterFromID("spa_baseprisoner");
		ChangeCharacterAddressGroup(sld, "none", "", "");
		AddQuestRecord("Guardoftruth", "44");
		pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу
		// гопота, чтобы весело жилось
		pchar.quest.GuardOT_setbandos.win_condition.l1 = "ExitFromLocation";
		pchar.quest.GuardOT_setbandos.win_condition.l1.location = pchar.location;
		pchar.quest.GuardOT_setbandos.function = "GuardOT_SetBandosInTown"; 
		// на Гавану
		pchar.quest.GuardOT_Cuba2.win_condition.l1 = "location";
		pchar.quest.GuardOT_Cuba2.win_condition.l1.location = "Cuba2";
		pchar.quest.GuardOT_Cuba2.function = "GuardOT_Cuba2Arrive";
	}
	else if (sQuestName == "GuardOT_SantiagoBandDie")
	{
		LAi_group_Delete("EnemyFight");
		chrDisableReloadToLocation = false;
		AddQuestRecord("Guardoftruth", "45");
		AddComplexSelfExpToScill(180, 180, 180, 180);
		AddCharacterExpToSkill(pchar, GetEquipedBladeType(pchar), 50);
	}
	else if (sQuestName == "GuardOT_DiegoShoreGuardReady")
	{
		for(i=1; i<=13; i++)
		{
			sld = CharacterFromID("GOT_spashore_"+i);
			LAi_SetStayType(sld);
			LAi_CharacterDisableDialog(sld);
			if (i >= 2 && i < 6) sld.MusketerDistance = 0;
		}
		sld = CharacterFromID("spa_baseprisoner");
		LAi_SetImmortal(sld, false);
		ChangeCharacterAddressGroup(sld, "Shore15", "quest", "quest2");
		LAi_SetActorType(sld);
		LAi_ActorRunToLocator(sld, "rld", "aloc1", "", -1);
		sld = CharacterFromID("Diego");
		sld.name = StringFromKey("SharlieFinal_44");
		sld.lastname = StringFromKey("SharlieFinal_45");
		sld.greeting = "";
		ChangeCharacterAddressGroup(sld, "Shore15", "quest", "quest2");
		LAi_SetActorType(sld);
		LAi_ActorRunToLocator(sld, "rld", "aloc2", "", -1);
		DoQuestCheckDelay("GuardOT_DiegoShoreTalkReady", 3.0);
	}
	else if (sQuestName == "GuardOT_DiegoShoreTalkReady")
	{
		LAi_SetPlayerType(pchar);
		sld = CharacterFromID("spa_baseprisoner");
		sld.dialog.currentnode = "spa_prisoner_53";
		LAi_SetActorType(sld);
		LAi_ActorDialogNow(sld, pchar, "", -1);
	}
	else if (sQuestName == "GuardOT_DiegoShoreGuardDie")
	{
		LAi_group_Delete("EnemyFight");
		chrDisableReloadToLocation = false;
		AddQuestRecord("Guardoftruth", "49");
		LocatorReloadEnterDisable("shore15", "reload1_back", true);
		pchar.quest.GuardOT_exitsanantonio.win_condition.l1 = "location";
		pchar.quest.GuardOT_exitsanantonio.win_condition.l1.location = "Cuba2";
		pchar.quest.GuardOT_exitsanantonio.function = "GuardOT_CreateDiegoShips";
		AddComplexSelfExpToScill(180, 180, 180, 180);
		AddCharacterExpToSkill(pchar, GetEquipedBladeType(pchar), 50);
	}
	else if (sQuestName == "GuardOT_CoastalGuardDie")
	{
		LAi_group_Delete("EnemyFight");
		chrDisableReloadToLocation = false;
		GuardOT_CatchOurSoldiers();
		AddQuestRecord("Guardoftruth", "53");
		LocatorReloadEnterDisable("Beliz_jungle_04", "reload2_back", false);
		pchar.quest.GuardOT_junglefort.win_condition.l1 = "location";
		pchar.quest.GuardOT_junglefort.win_condition.l1.location = "Jungle_fort_exit";
		pchar.quest.GuardOT_junglefort.function = "GuardOT_CreateExitFortGuard";
		AddComplexSelfExpToScill(130, 130, 130, 130);
		AddCharacterExpToSkill(pchar, GetEquipedBladeType(pchar), 50);
	}
	else if (sQuestName == "GuardOT_ExitfortGuardDie")
	{
		LAi_group_Delete("EnemyFight");
		chrDisableReloadToLocation = false;
		GuardOT_CatchOurSoldiers();
		AddQuestRecord("Guardoftruth", "54");
		pchar.quest.GuardOT_junglefort1.win_condition.l1 = "location";
		pchar.quest.GuardOT_junglefort1.win_condition.l1.location = "Jungle_fort";
		pchar.quest.GuardOT_junglefort1.function = "GuardOT_CreateFortGuard";
		AddComplexSelfExpToScill(150, 150, 150, 150);
		AddCharacterExpToSkill(pchar, GetEquipedBladeType(pchar), 50);
	}
	else if (sQuestName == "GuardOT_FortGuardDie")
	{
		LAi_group_Delete("EnemyFight");
		chrDisableReloadToLocation = false;
		AddQuestRecord("Guardoftruth", "55");
		pchar.quest.GuardOT_junglefort2.win_condition.l1 = "location";
		pchar.quest.GuardOT_junglefort2.win_condition.l1.location = "Jungle_fort_ammo";
		pchar.quest.GuardOT_junglefort2.function = "GuardOT_SetDiegoFortInside";
		AddComplexSelfExpToScill(180, 180, 180, 180);
		AddCharacterExpToSkill(pchar, GetEquipedBladeType(pchar), 50);
	}
	else if (sQuestName == "GuardOT_ResidenceGuardDie")
	{
		LAi_group_Delete("EnemyFight");
		DoQuestCheckDelay("hide_weapon", 1.5);
		for (i=1; i<=15; i++)
		{
			if (GetCharacterIndex("GuardOT_soldier_"+i) != -1)
			{
				sld = CharacterFromID("GuardOT_soldier_"+i);
				sld.lifeday = 1;
			}
		}
		pchar.quest.GuardOT_DiegoDie.win_condition.l1 = "item";
		pchar.quest.GuardOT_DiegoDie.win_condition.l1.item = "skinmap";
		pchar.quest.GuardOT_DiegoDie.function = "GuardOT_FindSkinmap";
	}
	else if (sQuestName == "GuardOT_OpenCatocheDoor")
	{
		chrDisableReloadToLocation = false;
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		LocatorReloadEnterDisable("Jungle_fort_exit", "reload1_back", true); // закроем форт
	}
	else if (sQuestName == "GuardOT_CabinBandosDie")
	{
		LAi_group_Delete("EnemyFight");
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
		chrDisableReloadToLocation = false;//открыть локацию
		DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
		bQuestDisableMapEnter = false;
		Island_SetReloadEnableGlobal("Bermudes", true);
		AddQuestRecord("Guardoftruth", "61");
		for(i=1; i<=2; i++)
		{
			sld = CharacterFromID("GOT_cabinband_"+i);
			LAi_NoRebirthEnable(sld);
		}
		AddComplexSelfExpToScill(50, 50, 50, 50);
	}
	else if (sQuestName == "GuardOT_ArchyIntoStore")
	{
		DoQuestReloadToLocation("PortRoyal_store", "reload", "reload1", "GuardOT_ArchyIntoStore_1");
	}
	else if (sQuestName == "GuardOT_ArchyIntoStore_1")
	{
		sld = characterFromId("Archy");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocation(sld, "reload", "reload2", "PortRoyal_storeRoom", "sit", "sit1", "GuardOT_ArchyIntoStoreRoom", -1);
		LAi_SetActorType(pchar);
		LAi_ActorFollow(pchar, sld, "", -1);
		sld = ItemsFromID("lcheer");
		sld.shown = true;
		sld.startLocation = "PortRoyal_storeRoom";
		sld.startLocator = "sit1";
		sld = ItemsFromID("chest");
		sld.model = "lcheer";
		sld.shown = true;
		sld.startLocation = "PortRoyal_storeRoom";
		sld.startLocator = "sit2";
		//if (CheckAttribute(pchar, "IsMushketer")) SetMainCharacterToMushketer("", false);
	}
	else if (sQuestName == "GuardOT_ArchyIntoStoreRoom")
	{
		DoQuestReloadToLocation("PortRoyal_storeRoom", "sit", "sit2", "");
		LAi_SetPlayerType(pchar);
		sld = characterFromId("Archy");
		LAi_SetActorType(sld);
		LAi_ActorSetSitMode(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.2);
	}
	else if (sQuestName == "GuardOT_MCOutFromArchyRoom")
	{
		pchar.GenQuest.CamShuttle = 3;
		WaitDate("",0,0,0,9,5);
		chrDisableReloadToLocation = false;
		LAi_LocationFightDisable(&Locations[FindLocation("Portroyal_town")], false);//разрешить драться
		LAI_SetPlayerType(pchar);           
		DoQuestReloadToLocation("Portroyal_town", "reload", "reload6", "");
		sld = ItemsFromID("lcheer");
		sld.shown = false;
		sld = ItemsFromID("chest");
		sld.model = "";
		sld.shown = false;
		sld = characterFromId("Archy");
		ChangeCharacterAddressGroup(sld, "none", "", "");
		LocatorReloadEnterDisable("PortRoyal_store", "reload2", true);
		LocatorReloadEnterDisable("PortRoyal_town", "reload", true); // дом рядом закрываем
		AddQuestRecord("Guardoftruth", "64");
		pchar.quest.GuardOT_squadrongo.win_condition.l1 = "Timer";
		pchar.quest.GuardOT_squadrongo.win_condition.l1.date.hour  = sti(GetTime()+rand(12));
		pchar.quest.GuardOT_squadrongo.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1+rand(2));
		pchar.quest.GuardOT_squadrongo.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1+rand(2));
		pchar.quest.GuardOT_squadrongo.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1+rand(2));
		pchar.quest.GuardOT_squadrongo.function = "GuardOT_WillySquadronGo";
	}
	else if (sQuestName == "GuardOT_FindWayToRoom")
	{
		chrDisableReloadToLocation = false;
		pchar.quest.GuardOT_toroof.win_condition.l1 = "locator";
		pchar.quest.GuardOT_toroof.win_condition.l1.location = "PortRoyal_houseSp1Room";
		pchar.quest.GuardOT_toroof.win_condition.l1.locator_group = "reload";
		pchar.quest.GuardOT_toroof.win_condition.l1.locator = "reload1_quest";
		pchar.quest.GuardOT_toroof.win_condition.l2 = "Hour";
		pchar.quest.GuardOT_toroof.win_condition.l2.start.hour = 0.00;
		pchar.quest.GuardOT_toroof.win_condition.l2.finish.hour = 3.00;
		pchar.quest.GuardOT_toroof.again = true;
		pchar.quest.GuardOT_toroof.function = "GuardOT_ReloadToRoof";
		DeleteAttribute(pchar, "questTemp.Guardoftruth_room"); // 021012
	}
	else if (sQuestName == "GuardOT_SitInHouse")
	{
		LAi_SetActorType(Pchar);
		LAi_ActorAnimation(Pchar, "Ground_sitting", "", 2.5);
		DoQuestFunctionDelay("GuardOT_StandUpInHouse", 2.5);
		CreateLocationParticles("blood_big", "goto", "goto5", 1.0, 0, 0, "");
	}
	else if (sQuestName == "GuardOT_HouseMercenDie")
	{
		LAi_group_Delete("EnemyFight");
		chrDisableReloadToLocation = false;//открыть локацию
		DeleteAttribute(pchar, "GenQuest.CantRun");
		CheckAndSetOverloadMode(GetMainCharacter()); // бег разрешаем
		AddQuestRecord("Guardoftruth", "69");
		pchar.quest.GuardOT_setwillyjungle.win_condition.l1 = "ExitFromLocation";
		pchar.quest.GuardOT_setwillyjungle.win_condition.l1.location = pchar.location;
		pchar.quest.GuardOT_setwillyjungle.function = "GuardOT_SetWillyOutHouse";
		AddComplexSelfExpToScill(70, 70, 70, 70);
		AddCharacterExpToSkill(pchar, GetEquipedBladeType(pchar), 50);
	}
	else if (sQuestName == "GuardOT_CreateAddMercenInHouse")
	{
		PlaySound("Ambient\LAND\door_002.wav");
		iRank = 25+MOD_SKILL_ENEMY_RATE*2;
		iScl = 70;
		sld = GetCharacter(NPC_GenerateCharacter("GOT_housemercen_2", "mercen_14", "man", "man", iRank, ENGLAND, -1, true, "quest"));
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, "topor_04", "pistol5", "bullet", iScl*2+100);
		LAi_SetWarriorType(sld);
		ChangeCharacterAddressGroup(sld, "IslaDeVieques_House", "reload", "reload1");
		LAi_group_MoveCharacter(sld, "EnemyFight");
		LAi_group_SetCheck("EnemyFight", "GuardOT_HouseMercenDie");
	}
	else if (sQuestName == "GuardOT_WillyGetReady")
	{
		sld = characterFromId("Willy");
		LAi_SetWarriorType(sld);
		LAi_SetImmortal(sld, false);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		LAi_SetCheckMinHP(sld, 10, true, "GuardOT_WillyEscape"); // скрытое бессмертие
		DoQuestFunctionDelay("GuardOT_WillyMushketerFree", 3.0);
	}
	else if (sQuestName == "GuardOT_WillyEscape")
	{
		iTemp = 0;
		sld = characterFromId("Willy");
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, "IslaDeVieques_HouseEntrance", "quest", "teleport");
		LAi_LockFightMode(sld, true);
		LAi_ActorRunToLocation(sld, "reload", "reload1_back", "IslaDeVieques_Jungle_01", "rld", "loc1", "", -1);
		for(i=1; i<=5; i++)
		{
			sld = CharacterFromID("GuardOT_willymushketer_"+i);
			if (LAi_GetCharacterHP(sld) <= 0) iTemp++;
		}
		if (iTemp > 4) DoQuestCheckDelay("GuardOT_WillyMushketerDie", 5.0);
		else LAi_group_SetCheck("EnemyFight", "GuardOT_WillyMushketerDie");
	}
	else if (sQuestName == "GuardOT_WillyMushketerDie")
	{
		LAi_group_Delete("EnemyFight");
		chrDisableReloadToLocation = false;//открыть локацию
		AddQuestRecord("Guardoftruth", "70");
		pchar.quest.GuardOT_willyescape.win_condition.l1 = "location";
		pchar.quest.GuardOT_willyescape.win_condition.l1.location = "IslaDeVieques_Jungle_01";
		pchar.quest.GuardOT_willyescape.function = "GuardOT_WillyShootInJungle";
		AddComplexSelfExpToScill(100, 100, 100, 300);
	}
	else if (sQuestName == "GuardOT_WillyReadyInJungle")
	{
		sld = characterFromId("Willy");
		LAi_SetWarriorType(sld);
		LAi_SetImmortal(sld, false);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		LAi_SetCheckMinHP(sld, 10, true, "GuardOT_WillyEscapeNext"); // скрытое бессмертие
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	}
	else if (sQuestName == "GuardOT_WillyEscapeNext")
	{
		sld = characterFromId("Willy");
		LAi_SetActorType(sld);
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, "IslaDeVieques_Jungle_01", "quest", "teleport");
		LAi_LockFightMode(sld, true);
		LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "OpenTheDoors", -1);
		pchar.quest.GuardOT_crabShore.win_condition.l1 = "location";
		pchar.quest.GuardOT_crabShore.win_condition.l1.location = "shore74";
		pchar.quest.GuardOT_crabShore.function = "GuardOT_ArchyInCrabShore";
		// эскадру Патерсона - на Крабовый остров
		Group_SetAddress("Willy_group", "IslaDeVieques", "quest_ships", "quest_ship_1");
		AddCharacterExpToSkill(pchar, "Pistol", 200);
	}
	else if (sQuestName == "GuardOT_CrabShoreGuardDie")
	{
		LAi_group_Delete("EnemyFight");
		AddQuestRecord("Guardoftruth", "71");
		DeleteAttribute(pchar, "GenQuest.Notsearchbody");
		pchar.quest.GuardOT_seekarchykey.win_condition.l1 = "item";
		pchar.quest.GuardOT_seekarchykey.win_condition.l1.item = "key_archy";
		pchar.quest.GuardOT_seekarchykey.function = "GuardOT_FindArchyKey";
		AddComplexSelfExpToScill(170, 170, 170, 170);
		AddCharacterExpToSkill(pchar, GetEquipedBladeType(pchar), 100);
	}
	else if (sQuestName == "Ksochitam_SitTable")
	{
		if(CheckAttribute(pchar, "IsMushketer"))
		/* {
			SetMainCharacterToMushketer("", false);
		} */
		ChangeCharacterAddressGroup(pchar, "SentJons_HouseF3_room", "sit", "sit1");
		LAi_SetSitType(pchar);
		DoQuestCheckDelay("Ksochitam_SitTableWaitTime", 4.0);
	}
	else if (sQuestName == "Ksochitam_SitTableWaitTime")
	{
		SetLaunchFrameFormParam(StringFromKey("SharlieFinal_66", NewStr()), "Ksochitam_RoomStandUp", 0, 5);
		WaitDate("", 0, 0, 0, 0, 30); //крутим время
		LaunchFrameForm();
		RefreshLandTime();
		RecalculateJumpTable();
		Whr_UpdateWeather();
	}
	else if (sQuestName == "Ksochitam_RoomStandUp")
	{
		RemoveItems(pchar, "map_normal", 1);
		GiveItem2Character(pchar, "mark_map");
		ChangeCharacterAddressGroup(pchar, "SentJons_HouseF3_room", "goto", "goto1");
		LAi_SetActorType(pchar);
		sld = characterFromId("Jino");
		LAi_SetActorType(sld);
		LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
		LAi_ActorTurnToCharacter(sld, pchar);
		SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
	}
	else if (sQuestName == "Ksochitam_FindFirstWay")
	{
		sld = ItemsFromID("mark_map");
		sld.mark = 2;
		AddQuestRecord("Ksochitam", "3");
		sld = characterFromId("Jino");
		sld.dialog.currentnode = "ksochitam_25";
		pchar.quest.Ksochitam_jinotalk1.win_condition.l1 = "location";
		pchar.quest.Ksochitam_jinotalk1.win_condition.l1.location = pchar.location.from_sea;
		pchar.quest.Ksochitam_jinotalk1.function = "Ksochitam_JinoDollyTalk";
		locations[FindLocation(pchar.location.from_sea)].DisableEncounters = true; //энкаутеры закрыть
	}
	else if (sQuestName == "Ksochitam_FindSecondWay")
	{
		sld = ItemsFromID("mark_map");
		sld.mark = 3;
		AddQuestRecord("Ksochitam", "4");
		sld = characterFromId("Jino");
		sld.dialog.currentnode = "ksochitam_29";
		pchar.quest.Ksochitam_jinotalk2.win_condition.l1 = "location";
		pchar.quest.Ksochitam_jinotalk2.win_condition.l1.location = pchar.location.from_sea;
		pchar.quest.Ksochitam_jinotalk2.function = "Ksochitam_JinoDollyTalk";
		locations[FindLocation(pchar.location.from_sea)].DisableEncounters = true; //энкаутеры закрыть
	}
	else if (sQuestName == "Ksochitam_FindFullWay")
	{
		sld = ItemsFromID("mark_map");
		sld.mark = 4;
		AddQuestRecord("Ksochitam", "5");
		sld = characterFromId("Jino");
		sld.dialog.currentnode = "ksochitam_31";
		pchar.quest.Ksochitam_jinotalk3.win_condition.l1 = "location";
		pchar.quest.Ksochitam_jinotalk3.win_condition.l1.location = pchar.location.from_sea;
		pchar.quest.Ksochitam_jinotalk3.function = "Ksochitam_JinoDollyTalk";
		locations[FindLocation(pchar.location.from_sea)].DisableEncounters = true; //энкаутеры закрыть
		DeleteAttribute(pchar, "questTemp.Ksochitam_Dolly");
		pchar.questTemp.Ksochitam = "findway";
		// открываем Ксочитэм
		i = FindIsland("Ksochitam");
		Islands[i].visible = true;
		Islands[i].reload_enable = true;
		Islands[i].alwaysStorm = true; //живем в штормах
		Islands[i].storm = true;
		Islands[i].tornado = true; 
		SetTimerCondition("Map_SetNationCoolHanters", 0, 0, 2, false); // немного развлечений
		// прерывание на выход к Ксочитэму
		pchar.quest.Ksochitam_island.win_condition.l1 = "location";
		pchar.quest.Ksochitam_island.win_condition.l1.location = "Ksochitam";
		pchar.quest.Ksochitam_island.function = "Ksochitam_ArriveIsland";
		// прерывание на высадку на Ксочитэм
		pchar.quest.Ksochitam_rockshore.win_condition.l1 = "location";
		pchar.quest.Ksochitam_rockshore.win_condition.l1.location = "shore65";
		pchar.quest.Ksochitam_rockshore.function = "Ksochitam_ArriveRockshore";
	}
	else if (sQuestName == "Ksochitam_JinoStay")
	{
		sld = characterFromId("Jino");
		LAi_SetStayType(sld);
		// кладем Молот Тора в пещеру
		sld = ItemsFromID("talisman3");
		sld.model = "torus";
		pchar.GenQuestRandItem.Ksochitam_Cave = true;
		pchar.GenQuestRandItem.Ksochitam_Cave.randitem1 = "talisman3";
		// здесь ставим все прерывания на Ксочитэм, возможные на данный момент:
		// на первую локацию джунглей
		pchar.quest.Ksochitam_adversary1.win_condition.l1 = "location";
		pchar.quest.Ksochitam_adversary1.win_condition.l1.location = "Ksochitam_Jungle_01";
		pchar.quest.Ksochitam_adversary1.win_condition = "Ksochitam_adversary1";
		// на локацию пещеры к сокровищам
		pchar.quest.Ksochitam_adversary2.win_condition.l1 = "location";
		pchar.quest.Ksochitam_adversary2.win_condition.l1.location = "Ksochitam_Grot";
		pchar.quest.Ksochitam_adversary2.win_condition = "Ksochitam_adversary2";
		// на локацию затопленной пещеры к сокровищам
		pchar.quest.Ksochitam_adversary3.win_condition.l1 = "location";
		pchar.quest.Ksochitam_adversary3.win_condition.l1.location = "Ksochitam_WaterCave";
		pchar.quest.Ksochitam_adversary3.win_condition = "Ksochitam_adversary3";
		// на локацию пещеры к маске
		pchar.quest.Ksochitam_adversary4.win_condition.l1 = "location";
		pchar.quest.Ksochitam_adversary4.win_condition.l1.location = "Ksochitam_Cave";
		pchar.quest.Ksochitam_adversary4.win_condition = "Ksochitam_adversary4";
		// на локацию затопленной пещеры к маске
		pchar.quest.Ksochitam_adversary5.win_condition.l1 = "location";
		pchar.quest.Ksochitam_adversary5.win_condition.l1.location = "Ksochitam_FloodedCave";
		pchar.quest.Ksochitam_adversary5.win_condition = "Ksochitam_adversary5";
		// на локацию тупиковой затопленной пещеры к маске
		pchar.quest.Ksochitam_adversary5_1.win_condition.l1 = "location";
		pchar.quest.Ksochitam_adversary5_1.win_condition.l1.location = "Ksochitam_FloodedCaveLock";
		pchar.quest.Ksochitam_adversary5_1.win_condition = "Ksochitam_adversary5";
		// на локацию с разбитым кораблём
		pchar.quest.Ksochitam_shoreship.win_condition.l1 = "location";
		pchar.quest.Ksochitam_shoreship.win_condition.l1.location = "Shore_ship4";
		pchar.quest.Ksochitam_shoreship.function = "Ksochitam_shoreship";
		// на локацию с Санта-Квитерией
		pchar.quest.Ksochitam_SQ.win_condition.l1 = "location";
		pchar.quest.Ksochitam_SQ.win_condition.l1.location = "Shore66";
		pchar.quest.Ksochitam_SQ.function = "Ksochitam_SQOutside";
		// на локацию со Стражем маски
		pchar.quest.Ksochitam_MaskGuard.win_condition.l1 = "location";
		pchar.quest.Ksochitam_MaskGuard.win_condition.l1.location = "Shore_mask";
		pchar.quest.Ksochitam_MaskGuard.function = "Ksochitam_MaskGuard";
		// на фальшивую маску
		pchar.quest.Ksochitam_MaskFalse.win_condition.l1 = "item";
		pchar.quest.Ksochitam_MaskFalse.win_condition.l1.item = "mask_false";
		pchar.quest.Ksochitam_MaskFalse.win_condition = "Ksochitam_FindMaskFalse";
		// на настоящую маску
		pchar.quest.Ksochitam_MaskTrue.win_condition.l1 = "item";
		pchar.quest.Ksochitam_MaskTrue.win_condition.l1.item = "mask_true";
		pchar.quest.Ksochitam_MaskTrue.win_condition = "Ksochitam_FindMaskTrue";
	}
	else if (sQuestName == "Ksochitam_adversary1")
	{
		pchar.questTemp.Ksochitam.Adversary.L1 = "true";
	}
	else if (sQuestName == "Ksochitam_adversary2")
	{
		pchar.questTemp.Ksochitam.Adversary.L2 = "true";
	}
	else if (sQuestName == "Ksochitam_adversary3")
	{
		pchar.questTemp.Ksochitam.Adversary.L3 = "true";
	}
	else if (sQuestName == "Ksochitam_adversary4")
	{
		pchar.questTemp.Ksochitam.Adversary.L4 = "true";
	}
	else if (sQuestName == "Ksochitam_adversary5")
	{
		pchar.questTemp.Ksochitam.Adversary.L5 = "true";
	}
	else if (sQuestName == "Ksochitam_SQMonstersDie")
	{
		DeleteAttribute(pchar, "questTemp.Ksochitam.ShoreShip");
		chrDisableReloadToLocation = false;//открыть локацию
		AddQuestRecord("Ksochitam", "8");
		LocatorReloadEnterDisable("shore66", "reload2_back", true);
		pchar.quest.Ksochitam_SQInside.win_condition.l1 = "location";
		pchar.quest.Ksochitam_SQInside.win_condition.l1.location = "SantaQuiteriaInside";
		pchar.quest.Ksochitam_SQInside.function = "Ksochitam_SQInside";
	}
	else if (sQuestName == "Ksochitam_SQCskeletcaptalk")
	{
		for(i=2; i<=3; i++)
		{
			sld = characterFromId("SQI_skelet_"+i);
			LAi_SetActorType(sld);
		}
		DoQuestCheckDelay("hide_weapon", 1.0);
		sld = characterFromId("SQC_skeletcap");
		LAi_SetActorType(sld);
		LAi_ActorDialogNow(sld, pchar, "", -1);
	}
	else if (sQuestName == "Ksochitam_SQCskeletcapdie")
	{
		LAi_group_Delete("EnemyFight");
		pchar.questTemp.Ksochitam.SantaQuiteria = "true";
		AddQuestRecord("Ksochitam", "9");
		if (CheckCharacterItem(pchar, "mask_true"))
		{
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("shore66", "reload2_back", false);
		}
		else
		{
			pchar.GenQuest.NoDelBody = true;
		}
		// на ключ
		ChangeItemDescribe("key_archy", "itmdescr_key_mask");
		pchar.quest.Ksochitam_MaskKey.win_condition.l1 = "item";
		pchar.quest.Ksochitam_MaskKey.win_condition.l1.item = "key_archy";
		pchar.quest.Ksochitam_MaskKey.win_condition = "Ksochitam_FindMaskKey";
		// на журнал
		pchar.quest.Ksochitam_SQBook.win_condition.l1 = "item";
		pchar.quest.Ksochitam_SQBook.win_condition.l1.item = "SQCapBook";
		pchar.quest.Ksochitam_SQBook.win_condition = "Ksochitam_FindSQCapBook";
		// на скалистую бухту
		pchar.quest.Ksochitam_ReturnShip.win_condition.l1 = "location";
		pchar.quest.Ksochitam_ReturnShip.win_condition.l1.location = "Shore65";
		pchar.quest.Ksochitam_ReturnShip.function = "Ksochitam_CreateDeMaldonado";
		// делаем бухту 66 доступной для причаливания
		Island_SetReloadEnableLocal("Ksochitam", "reload_1", true);
		i = Findlocation("Shore66");
		locations[i].models.day.charactersPatch = "sandshore_patch3";
		locations[i].models.night.charactersPatch = "sandshore_patch3";	
		n = FindIsland("Ksochitam");
		Islands[n].reload.l2.label = "Shore66";
		Islands[n].reload.l2.name = "reload_1";
		Islands[n].reload.l2.go = "Shore66";
		Islands[n].reload.l2.emerge = "sea";
		Islands[n].reload.l2.radius = 600.0;
		Islands[n].reload.l2.pic = 0;
		Islands[n].reload.l2.tex = "t1";
		LAi_LocationDisableOfficersGen("Shore66", false);
		// запрещаем генерацию скелетов в Скалистой бухте
		i = Findlocation("Shore65");
		DeleteAttribute(&locations[i], "KsochitamSkeletons");
	}
	else if (sQuestName == "Ksochitam_FindMaskKey")
	{
		chrDisableReloadToLocation = false;//открыть локацию
		DeleteAttribute(pchar, "GenQuest.NoDelBody");
	}
	else if (sQuestName == "Ksochitam_FindSQCapBook")
	{
		AddQuestRecord("Ksochitam", "10");
	}
	else if (sQuestName == "Ksochitam_FindMaskFalse")
	{
		if (CheckCharacterItem(pchar, "mask_true"))
		{
			AddQuestRecord("Ksochitam", "11-1");
		}
		else
		{
			AddQuestRecord("Ksochitam", "11");
			LocatorReloadEnterDisable("shore66", "reload2_back", false);
		}
	}
	else if (sQuestName == "Ksochitam_MaldonadoDie")
	{
		chrDisableReloadToLocation = false;//открыть локацию
		LocatorReloadEnterDisable("Shore65", "reload2_back", true);
		AddQuestRecord("Ksochitam", "14");
		DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary");
		sld = characterFromId("Jino");
		sld.dialog.currentnode = "adversary_6";
		pchar.quest.Ksochitam_MaldonadoSquadron.win_condition.l1 = "location";
		pchar.quest.Ksochitam_MaldonadoSquadron.win_condition.l1.location = "Ksochitam";
		pchar.quest.Ksochitam_MaldonadoSquadron.function = "Ksochitam_CreateMaldonadoSquadron";
	}
	else if (sQuestName == "Ksochitam_GuardCryptRotate")
	{
		locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.01, 0.0, 2.0, 0.0, 1700);
		Pchar.FuncCameraFly = "";
		DoQuestCheckDelay("Ksochitam_GoGuardCryptMask", 9.5);
	}
	else if (sQuestName == "Ksochitam_GoGuardCryptMask")
	{
		locCameraResetState();
		LAi_ActorGoToLocator(pchar, "goto", "back", "Ksochitam_GuardCryptRotateNext", -1);
	}
	else if (sQuestName == "Ksochitam_GuardCryptRotateNext")
	{
		locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.005, 0.0, 2.0, 0.0, 1700);
		Pchar.FuncCameraFly = "";
		//DoQuestCheckDelay("Ksochitam_GuardCryptBack", 4.0);
		DoQuestCheckDelay("Video_GuardMask", 4.0);
	}
	else if (sQuestName == "Video_GuardMask")
	{
		PChar.GenQuest.VideoAVI = "Skeleton_grotto";
		PChar.GenQuest.VideoAfterQuest = "Ksochitam_GuardCryptBack";
		DoQuestCheckDelay("PostVideo_Start", 0.2);
	}
	else if (sQuestName == "Ksochitam_GuardCryptBack")
	{
		SetSchemeAfterFlagRise();
		iRank = MOD_SKILL_ENEMY_RATE*3+30;
		iTemp = MOD_SKILL_ENEMY_RATE*250+500;
		fMft = 1.0+MOD_SKILL_ENEMY_RATE/10;
		sld = GetCharacter(NPC_GenerateCharacter("GuardMask", "giant", "skeleton", "giant", iRank, PIRATE, -1, true, "quest"));
		SetSelfSkill(sld, 100, 100, 100, 100, 100);
		GiveItem2Character(sld, "blade_33");
		RemoveCharacterEquip(sld, GUN_ITEM_TYPE);
		sld.equip.blade = "blade_33";
		sld.name = StringFromKey("SharlieFinal_67");
		sld.lastname = StringFromKey("SharlieFinal_68");
		sld.dialog.FileName = "Quest\Sharlie\Ksochitam.c";
		sld.dialog.currentnode = "guardmask";
		SetSPECIAL(sld, 10, 10, 10, 10, 10, 10, 10);
		SetAllPerksToChar(sld, false);
		LAi_SetHP(sld, iTemp, iTemp);
		sld.MultiFighter = fMft; // мультифайтер
		sld.GuardMask = true;
		sld.PoisonResistent = true; // Addon 2016-1 Jason пиратская линейка патч 17/1
		TakeNItems(sld, "icollection", 5);
		LAi_SetCheckMinHP(sld, sti(LAi_GetCharacterHP(sld)/2), true, "Ksochitam_GuardMaskAddSkeletonsFirst");
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, "Shore_mask", "quest", "guardmask");
		DoQuestCheckDelay("Ksochitam_GuardMaskGo", 1.5);
	}
	else if (sQuestName == "Ksochitam_GuardMaskGo")
	{
		sld = characterFromId("GuardMask");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocator(sld, "quest", "detector", "Ksochitam_TurnToGuardMask", -1);
	}
	else if (sQuestName == "Ksochitam_TurnToGuardMask")
	{
		locCameraResetState();
		LAi_ActorTurnToLocator(pchar, "goto", "rotate"); 
		sld = characterFromId("GuardMask");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocator(sld, "goto", "rotate", "Ksochitam_GuardMaskTalk", -1);
	}
	else if (sQuestName == "Ksochitam_GuardMaskTalk")
	{
		LAi_SetPlayerType(pchar);
		EndQuestMovie();
		InterfaceStates.Buttons.Save.enable = true;
		bDisableCharacterMenu = false;
		sld = characterFromId("GuardMask");
		LAi_ActorDialogDelay(sld, pchar, "", 1.5);
	}
	else if (sQuestName == "Ksochitam_GuardMaskAddSkeletonsFirst")
	{
		log_testinfo("Первый фокус!");
		PlaySound("Ambient\Teno_inside\big_ring.wav");
		iTotalTemp = 2;
		iGlobalTemp = 0;
		DoQuestCheckDelay("Ksochitam_ShoreMaskAddSkeletons", 1.0);
		sld = characterFromId("GuardMask");
		LAi_SetImmortal(sld, false);
		LaunchIncasFire(sld, true);
		LAi_SetCurHPMax(sld);
		LAi_GetCharacterMaxEnergy(sld);
		log_info(StringFromKey("SharlieFinal_69"));
		LAi_SetCheckMinHP(sld, sti(LAi_GetCharacterHP(sld)/3), true, "Ksochitam_GuardMaskAddSkeletonsSecond");
	}
	else if (sQuestName == "Ksochitam_ShoreMaskAddSkeletons")
	{
		if (CheckAttribute(pchar, "questTemp.Ksochitam.GuardMaskBeat")) return true;
		log_testinfo("Скелеты создаются!!");
		PlaySound("Ambient\Teno_inside\teleporter.wav");
		if (MOD_SKILL_ENEMY_RATE < 6) iTotalTemp = iTotalTemp-1;
		iRank = 25+MOD_SKILL_ENEMY_RATE*2;
		iScl = 70;
		log_testinfo("Число скелетов: "+iTotalTemp+"");
		for (i=1; i<=iTotalTemp; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("guardmask_skelet_"+i+iGlobalTemp, "skel"+i, "skeleton", "skeleton", iRank, PIRATE, -1, true, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, RandPhraseSimple("blade_13","blade_10"), "pistol5", "bullet", iScl*2+100);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			string locator = LAi_FindNearestFreeLocator("monsters", locx, locy, locz);
			log_testinfo("Локатор: "+locator+"");
			ChangeCharacterAddressGroup(sld, "shore_mask", "monsters", locator);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "KSOCHITAM_MONSTERS");
			CreateLocationParticles("fire_incas_Simple", "monsters", locator, 0, 0, 0, "");
		}
		DoQuestCheckDelay("Ksochitam_ShoreMaskKillSkeletons", 30.0);
	}
	else if (sQuestName == "Ksochitam_ShoreMaskKillSkeletons")
	{
		for (i=1; i<=iTotalTemp; i++)
		{
			if (GetCharacterIndex("guardmask_skelet_"+i+iGlobalTemp) != -1)
			{
				sld = characterFromId("guardmask_skelet_"+i+iGlobalTemp);
				LaunchIncasFire(sld, true);
				LAi_KillCharacter(sld);
				ChangeCharacterAddressGroup(sld, "none", "", "");
			}
		}
		iGlobalTemp++;
		DoQuestCheckDelay("Ksochitam_ShoreMaskAddSkeletons", 3.0);
	}
	else if (sQuestName == "Ksochitam_GuardMaskAddSkeletonsSecond")
	{
		log_testinfo("Второй фокус!");
		PlaySound("Ambient\Teno_inside\big_ring.wav");
		if (MOD_SKILL_ENEMY_RATE > 2) iTotalTemp = 3;
		sld = characterFromId("GuardMask");
		LAi_SetImmortal(sld, false);
		LaunchIncasFire(sld, true);
		LAi_SetCurHPMax(sld);
		LAi_GetCharacterMaxEnergy(sld);
		log_info(StringFromKey("SharlieFinal_69"));
		LAi_SetCheckMinHP(sld, 300, true, "Ksochitam_GuardMaskAddSkeletonsThird");
		DoQuestFunctionDelay("Ksochitam_GuardMaskFlash", 0.5);
	}
	else if (sQuestName == "Ksochitam_GuardMaskAddSkeletonsThird")
	{
		log_testinfo("Третий фокус!");
		PlaySound("Ambient\Teno_inside\big_ring.wav");
		sld = characterFromId("GuardMask");
		LAi_SetImmortal(sld, false);
		RemoveItems(sld, "icollection", 5);
		CheckAndSetOverloadMode(sld);
		if (MOD_SKILL_ENEMY_RATE > 6) iTotalTemp = 4;
		LaunchIncasFire(sld, true);
		LAi_SetCurHPMax(sld);
		LAi_GetCharacterMaxEnergy(sld);
		log_info(StringFromKey("SharlieFinal_69"));
		LAi_SetCheckMinHP(sld, 100, true, "Ksochitam_GuardMaskFinalBattle");
	}
	else if (sQuestName == "Ksochitam_GuardMaskFinalBattle")
	{
		DoQuestCheckDelay("Ksochitam_ShoreMaskKillSkeletons", 0.1);
		pchar.questTemp.Ksochitam.GuardMaskBeat = "true";
		DeleteAttribute(pchar, "questTemp.Ksochitam.GuardMaskFight");
		sld = characterFromId("GuardMask");
		LAi_SetImmortal(sld, false);
		sld.dialog.currentnode = "guardmask_4";
		LaunchIncasFire(sld, true);
		LAi_SetCurHPMax(sld);
		LAi_GetCharacterMaxEnergy(sld);
		log_info(StringFromKey("SharlieFinal_69"));
		LAi_SetActorType(sld);
		DoQuestCheckDelay("hide_weapon", 1.0);
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
		LAi_ActorDialogDelay(sld, pchar, "", 2.0);
		DoQuestFunctionDelay("Ksochitam_SetMusic", 1.2);
	}
	else if (sQuestName == "Ksochitam_GuardMaskGift")
	{
		LaunchIncasFire(pchar, true);
		PlaySound("interface\notebook.wav");
		if (AddSPECIALValue(pchar, SPECIAL_S, 0) != SPECIAL_MAX)
		{
			notification(StringFromKey("SharlieFinal_70"), "None");
			AddSPECIALValue(pchar, SPECIAL_S, 1);
		}
		if (AddSPECIALValue(pchar, SPECIAL_E, 0) != SPECIAL_MAX)
		{
			notification(StringFromKey("SharlieFinal_71"), "None");
			AddSPECIALValue(pchar, SPECIAL_E, 1);
		}
		if (AddSPECIALValue(pchar, SPECIAL_A, 0) != SPECIAL_MAX)
		{
			notification(StringFromKey("SharlieFinal_72"), "None");
			AddSPECIALValue(pchar, SPECIAL_A, 1);
		}
		DoQuestCheckDelay("Ksochitam_GuardMaskGiftComplete", 3.0);
		DoQuestFunctionDelay("Ksochitam_SetMusic", 0.5);
		AddComplexSelfExpToScill(450, 450, 450, 450);
	}
	else if (sQuestName == "Ksochitam_GuardMaskGiftComplete")
	{
		LAi_SetPlayerType(pchar);
		sld = characterFromId("GuardMask");
		sld.dialog.currentnode = "guardmask_13";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	else if (sQuestName == "Ksochitam_GuardMaskGoAway")
	{
		LAi_SetActorType(pchar);
		sld = characterFromId("GuardMask");
		LAi_SetActorType(sld);
		GetCharacterPos(pchar, &locx, &locy, &locz);
		LAi_ActorGoToLocator(sld, "monsters", LAi_FindNearestFreeLocator("monsters", locx, locy, locz), "Ksochitam_GuardMaskGoAway1", -1);
	}
	else if (sQuestName == "Ksochitam_GuardMaskGoAway1")
	{
		sld = characterFromId("GuardMask");
		LaunchIncasFire(sld, true);
		LAi_ActorTurnToCharacter(pchar, sld);
		DoQuestCheckDelay("Ksochitam_GuardMaskDisappear", 1.5);
	}
	else if (sQuestName == "Ksochitam_GuardMaskDisappear")
	{
		sld = characterFromId("GuardMask");
		ChangeCharacterAddressGroup(sld, "none", "", "");
		PlaySound("Ambient\Teno_inside\teleporter.wav");
		// увеличиваем локатор с маской и вертаем тип локации
		n = Findlocation("Shore_mask");
		locations[n].type = "x_seashore";
		locations[n].locators_radius.item.item1 = 1.2;
		DoQuestCheckDelay("Ksochitam_ShoreMaskReload", 2.5);
		LAi_group_NotFightPlayerVSGroup("KSOCHITAM_MONSTERS");
	}
	else if (sQuestName == "Ksochitam_ShoreMaskReload")
	{
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		LAi_SetPlayerType(pchar);
		DoQuestReloadToLocation(pchar.location, pchar.location.group, pchar.location.locator, "");
		AddQuestRecord("Ksochitam", "12");
	}
	else if (sQuestName == "Ksochitam_FindMaskTrue")
	{
		if (CheckCharacterItem(pchar, "mask_false"))
		{
			AddQuestRecord("Ksochitam", "13-1");
		}
		else
		{
			AddQuestRecord("Ksochitam", "13");
		}
		chrDisableReloadToLocation = false;//открыть локацию
	}
	else if (sQuestName == "Ksochitam_JinoNormal")
	{
		sld = characterFromId("Jino");
		LAi_SetOwnerType(sld);
	}
	else if (sQuestName == "Tieyasal_VinsentoGo") // запускаем квест
	{
		sld = characterFromId("Vincento");
		LAi_SetHuberType(sld);
		ChangeCharacterAddressGroup(sld, "Santiago_Incquisitio", "sit", "armchair1");
		LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
		chrDisableReloadToLocation = false;//открыть локацию
		SetFunctionTimerCondition("Tieyasal_TotalOver", 0, 0, 120, false); // глобальный таймер квеста - 120 дней на выполнение - потом геймовер
		SetFunctionTimerCondition("Tieyasal_SetAdrianInChapel", 0, 0, 5, false);
		LAi_LocationDisableOfficersGen("Pearl_jungle_03", false); // пускать офицеров в локу телепорта
		pchar.questTemp.Tieyasal = "begin"; // далее - на Исла Тесоро
		AddQuestRecord("Tieyasal", "1");
	}
	else if (sQuestName == "Tieyasal_MCSoldiersReset") // 160912
	{
		chrDisableReloadToLocation = false;//открыть локацию
		for(i=1; i<=iTotalTemp; i++)
		{
			if (GetCharacterIndex("Tieyasal_Oursoldier_"+i) != -1)
			{
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
		}
		AddQuestRecord("Tieyasal", "9");
	}
	else if (sQuestName == "Tieyasal_PrepareDichosoTrap")
	{
		chrDisableReloadToLocation = false;
		if (CheckAttribute(pchar, "questTemp.Tieyasal.MigelKnow")) AddQuestRecord("Tieyasal", "8");
		else AddQuestRecord("Tieyasal", "7");
		pchar.quest.Tieyasal_Dichososhore.win_condition.l1 = "location";
		pchar.quest.Tieyasal_Dichososhore.win_condition.l1.location = "Shore42";
		pchar.quest.Tieyasal_Dichososhore.function = "Tieyasal_ArriveToNevis";
		locations[FindLocation("Shore42")].DisableEncounters = true; //энкаутеры закрыть
	}
	else if (sQuestName == "Tieyasal_CryptBattleComplete")
	{
		if (CheckAttribute(pchar, "questTemp.Tieyasal.MigelKnow")) AddQuestRecord("Tieyasal", "11");
		else AddQuestRecord("Tieyasal", "10");
		DeleteAttribute(pchar, "GenQuest.Notsearchbody");
		pchar.GenQuest.NoDelBody = true;
	}
	else if (sQuestName == "Tieyasal_GraveyardBattleComplete")
	{
		chrDisableReloadToLocation = false;//открыть локацию
		locations[FindLocation("Shore42")].DisableEncounters = false; 
		locations[FindLocation("Charles_exittown")].DisableEncounters = false; 
		locations[FindLocation("Charles_CaveEntrance")].DisableEncounters = false; 
		for(i=2; i<=4; i++)
		{
			locations[FindLocation("Charles_Jungle_0"+i)].DisableEncounters = false;
		}
		LocatorReloadEnterDisable("Shore42", "boat", false);
		for(i=1; i<=iTotalTemp; i++)
		{
			if (GetCharacterIndex("Tieyasal_Oursoldier_"+i) != -1)
			{
				sld = characterFromID("Tieyasal_Oursoldier_"+i);
				sld.lifeday = 0;
			}
		}
		pchar.quest.Tieyasal_Cabinthink.win_condition.l1 = "location";
		pchar.quest.Tieyasal_Cabinthink.win_condition.l1.location = "Nevis";
		pchar.quest.Tieyasal_Cabinthink.function = "Tieyasal_TalkSelfInCabin";
		AddQuestRecord("Tieyasal", "14");
	}
	else if (sQuestName == "Tieyasal_PrepareCabinTalk")
	{
		chrDisableReloadToLocation = true;
		DoQuestCheckDelay("TalkSelf_Quest", 2.0);
	}
	else if (sQuestName == "Tieyasal_AfterCabinTalk")
	{
		// снимаем все запреты
		chrDisableReloadToLocation = false;
		bQuestDisableMapEnter = false;
		Island_SetReloadEnableGlobal("Nevis", true);
		DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		bDisableCharacterMenu = false;
		DeleteAttribute(pchar, "GenQuest.CannotWait");
		if (pchar.questTemp.Tieyasal_CabinTalk == "calendar")
		{
			pchar.questTemp.Tieyasal = "calendar";
			AddQuestRecord("Tieyasal", "15");
		}
		else
		{
			pchar.questTemp.Tieyasal = "trip";
			AddQuestRecord("Tieyasal", "16");
		}
		pchar.quest.Tieyasal_TripStart.win_condition.l1 = "location";
		pchar.quest.Tieyasal_TripStart.win_condition.l1.location = "Shore_ship2";
		pchar.quest.Tieyasal_TripStart.function = "Tieyasal_TripStartInShore";
		pchar.quest.Tieyasal_Landway.win_condition.l1 = "location";
		pchar.quest.Tieyasal_Landway.win_condition.l1.location = "Tenochtitlan";
		pchar.quest.Tieyasal_Landway.function = "Tieyasal_SetUrakanItzaWarrior";
		LocatorReloadEnterDisable("Tayasal_jungle_09", "reload3_back", false); // открываем проход в Тайясаль
		LocatorReloadEnterDisable("Tayasal_jungle_07", "reload2_back", false); // patch-5
		DeleteAttribute(pchar, "questTemp.Tieyasal_CabinTalk");
	}
	else if (sQuestName == "Tieyasal_TeleportArrive")
	{
		Dolly_TeleportConsequences(); // последствия
		LAi_SetActorType(pchar);
		LAi_ActorAnimation(pchar, "Ground_sitting", "LSC_TeleportArrive_1", 3.0);
		pchar.questTemp.Tieyasal.Teleport = "true";
		// ставим офицеров, если такие были
		for(i=1; i<=3; i++)
		{
			idx = GetOfficersIndex(pchar, i);
			if(idx < 0) continue;
			sld = &Characters[idx];
			if (CheckAttribute(sld, "quest.teleportation"))
			{
				ChangeCharacterAddressGroup(sld, "Tenochtitlan", "officers", "reload1_"+i);
				if (CheckCharacterItem(sld, "Ultimate_potion"))
				{
					sTemp = StringFromKey("SharlieFinal_73");
					if (sld.sex == "woman") sTemp = StringFromKey("SharlieFinal_74");
					RemoveItems(sld, "Ultimate_potion", 1);
					Log_Info(StringFromKey("SharlieFinal_75", GetFullName(sld), sTemp));
				}
				else
				{
					sTemp = StringFromKey("SharlieFinal_76");
					if (sld.sex == "woman") sTemp = StringFromKey("SharlieFinal_77");
					LAi_KillCharacter(sld);
					Log_Info(StringFromKey("SharlieFinal_78", GetFullName(sld), sTemp));
				}
			}
		}
	}
	else if (sQuestName == "Tieyasal_ItzaWarriorPause")
	{
		if (pchar.questTemp.Tieyasal.ItzaWarrior == "1") DoQuestCheckDelay("Tieyasal_CreateItzaWarriorSecondGroup", 7.0);
		else DoQuestCheckDelay("Tieyasal_CreateItzaWarriorThirdGroup", 9.0);
	}
	else if (sQuestName == "Tieyasal_CreateItzaWarriorSecondGroup")
	{
		for(i=1; i<=iTotalTemp; i++)
		{
			sld = characterFromId("Itza_"+pchar.questTemp.Tieyasal.ItzaWarrior+"Group_"+i);
			ChangeCharacterAddressGroup(sld, "none", "", "");
		}
		LAi_group_Delete("ITZA");
		PlaySound("interface\abordage_wining.wav");
		PlaySound("interface\abordage_wining.wav");
		iRank = 25+MOD_SKILL_ENEMY_RATE*2;
		for(i=1; i<=iTotalTemp; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("Itza_2Group_"+i, "itza_"+(rand(7)+1), "man", "man", iRank, PIRATE, -1, false, "native"));
			FantomMakeCoolFighter(sld, iRank, 80, 80, RandPhraseSimple("topor_01","blade_02"), "pistol1", "bullet", 70);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, "Tenochtitlan", "rld", LAi_FindFarLocator("rld", locx, locy, locz));
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "ITZA");
		}
		LAi_group_SetRelation("ITZA", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("ITZA", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("ITZA", "Tieyasal_ItzaWarriorPause");
		pchar.questTemp.Tieyasal.ItzaWarrior = "2";
	}
	else if (sQuestName == "Tieyasal_CreateItzaWarriorThirdGroup")
	{
		for(i=1; i<=iTotalTemp; i++)
		{
			sld = characterFromId("Itza_"+pchar.questTemp.Tieyasal.ItzaWarrior+"Group_"+i);
			ChangeCharacterAddressGroup(sld, "none", "", "");
		}
		LAi_group_Delete("ITZA");
		PlaySound("interface\abordage_wining.wav");
		PlaySound("interface\abordage_wining.wav");
		iRank = 28+MOD_SKILL_ENEMY_RATE*2;
		for(i=1; i<=iTotalTemp; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("Itza_3Group_"+i, "itza_"+(rand(7)+1), "man", "man", iRank, PIRATE, -1, false, "native"));
			FantomMakeCoolFighter(sld, iRank, 85, 85, RandPhraseSimple("topor_01","blade_02"), "pistol5", "bullet", 100);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, "Tenochtitlan", "rld", LAi_FindFarLocator("rld", locx, locy, locz));
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "ITZA");
		}
		LAi_group_SetRelation("ITZA", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("ITZA", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("ITZA", "Tieyasal_ItzaWarriorDie");
	}
	else if (sQuestName == "Tieyasal_ItzaWarriorDie")
	{
		pchar.quest.Tieyasal_mushketfire.over = "yes"; //снять прерывание
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
		DoQuestCheckDelay("hide_weapon", 0.8);
		sld = characterFromId("Urakan");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocator(sld, "quest", "urakan", "Tieyasal_UrakanTalk", -1);
		AddComplexSelfExpToScill(50, 50, 50, 50);
	}
	else if (sQuestName == "Tieyasal_UrakanTalk")
	{
		for(i=1; i<=iTotalTemp; i++)
		{
			sld = characterFromId("Itza_3Group_"+i);
			ChangeCharacterAddressGroup(sld, "none", "", "");
		}
		// закрываем все храмовые локаторы кроме низа большого храма, чтобы не лез раньше времени
		for(i=1; i<=37; i++)
		{
			LocatorReloadEnterDisable("Tenochtitlan", "reloadTemple"+i, true);
		}
		LocatorReloadEnterDisable("Tenochtitlan", "reloadU1_back", true);
		LocatorReloadEnterDisable("Tenochtitlan", "reloadU2_back", true);
		sld = characterFromId("Urakan");
		LAi_SetActorType(sld);
		LAi_SetActorType(pchar);
		LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
		LAi_ActorTurnToCharacter(sld, pchar);
		SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
		for(i=1; i<=2; i++)
		{
			sld = characterFromId("Bridge_itza_"+i);
			LAi_SetActorType(sld);
		}
		LAi_group_Delete("TMP_FRIEND");
		// ставим ица-горожан
		for(i=1; i<=12; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("Itza_ctz_"+i, "itza_"+(rand(7)+1), "man", "man", 30, PIRATE, -1, false, "native"));
			FantomMakeCoolFighter(sld, 30, 100, 100, RandPhraseSimple("blade_01","blade_02"), "", "", 150);
			sld.name = GetIndianName(MAN);
			sld.lastname = "";
			sld.dialog.FileName = "Quest\Sharlie\Itza.c";
			sld.dialog.currentnode = "itza_ctz";
			sld.greeting = "indian_male";
			ChangeCharacterAddressGroup(sld, "Tenochtitlan", "goto", "goto"+i);
			LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, true);
			LAi_group_MoveCharacter(sld, "TMP_FRIEND");
			LAi_group_SetRelation("TMP_FRIEND", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
		}
	}
	else if (sQuestName == "Tieyasal_MishelleTalkActivation")
	{
		sld = characterFromId("Mishelle");
		LAi_SetActorType(pchar);
		LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
		LAi_ActorTurnToCharacter(sld, pchar);
		SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
	}
	else if (sQuestName == "Tieyasal_TempleGuardDie")
	{
		sld = characterFromId("Mishelle");
		LAi_SetImmortal(sld, false);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "ITZA");
		LAi_group_SetRelation("ITZA", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("ITZA", LAI_GROUP_PLAYER, true);
		LAi_SetCheckMinHP(sld, 200, true, "Tieyasal_RunSecondFloor");
	}
	else if (sQuestName == "Tieyasal_RunSecondFloor")
	{
		PlaySound("Ambient\Teno_inside\big_ring.wav");
		pchar.GenQuest.CantRun = true;
		CheckAndSetOverloadMode(GetMainCharacter()); // бег запрещаем
		sld = characterFromId("Mishelle");
		LAi_SetFightMode(sld, false);
		LAi_SetActorType(sld);
		LAi_ActorRunToLocation(sld, "quest", "detector1", "none", "", "", "", 20);
		DoQuestCheckDelay("Tieyasal_RunSecondFloor1", 2.0);
		// прерывание
		pchar.quest.Tieyasal_2floor.win_condition.l1 = "locator";
		pchar.quest.Tieyasal_2floor.win_condition.l1.location = "Temple_great";
		pchar.quest.Tieyasal_2floor.win_condition.l1.locator_group = "quest";
		pchar.quest.Tieyasal_2floor.win_condition.l1.locator = "detector1";
		pchar.quest.Tieyasal_2floor.function = "Tieyasal_SecondFloorActivate";// patch-4
	}
	else if (sQuestName == "Tieyasal_RunSecondFloor1")
	{
		sld = characterFromId("Mishelle");
		LAi_SetActorType(sld);
		LAi_ActorRunToLocation(sld, "quest", "detector1", "none", "", "", "Tieyasal_SecondFloorAttack", 20);
	}
	else if (sQuestName == "Tieyasal_SecondFloorAttack")
	{
		DeleteAttribute(pchar, "GenQuest.CantRun");
		CheckAndSetOverloadMode(GetMainCharacter()); // бег разрешаем
		DeleteAttribute(pchar, "questTemp.Tieyasal.LockLadder"); // открываем лестницу
		// ставим клона-мушкетера Мишеля
		sld = GetCharacter(NPC_GenerateCharacter("Mishelle_mushketer", "Migel_2_mush", "man", "mushketer", 60, PIRATE, -1, false, "quest"));
		FantomMakeCoolFighter(sld, 60, 100, 100, "", "mushket2x2", "cartridge", 150);
		LAi_SetHP(sld, 1000+MOD_SKILL_ENEMY_RATE*200, 1000+MOD_SKILL_ENEMY_RATE*200);
		SetSelfSkill(sld, 100, 100, 100, 100, 100);
		sld.name = StringFromKey("SharlieFinal_23");
		sld.lastname = StringFromKey("SharlieFinal_24"); // патч 17/1
		LAi_SetImmortal(sld, false);
		ChangeCharacterAddressGroup(sld, "Temple_great", "quest", "mushketer");
		sld.MusketerDistance = 0;
		sld.PoisonResistent = true; // Addon 2016-1 Jason пиратская линейка патч 17/1
		LAi_SetWarriorType(sld);
		LAi_warrior_SetStay(sld, true);
		LAi_warrior_DialogEnable(sld, false);
		iTemp = MOD_SKILL_ENEMY_RATE;
		TakeNItems(sld, "potion2", iTemp);
		TakeNItems(sld, "cartridge", 50);
		TakeNItems(sld, "bullet", 50);
		TakeNItems(sld, "gunpowder", 50);
		LAi_SetCheckMinHP(sld, 150, true, "Tieyasal_RunThirdFloor");
		pchar.questTemp.Tieyasal.Shooter = "true"; // устанавливаем защиту
		// ставим мушкетеров ица
		iRank = 30+MOD_SKILL_ENEMY_RATE*2;
		for(i=5; i<=6; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("Warrior_itza_mush_"+i, "mush_itza_"+(rand(2)+1), "man", "mushketer", iRank, PIRATE, -1, false, "quest"));
			FantomMakeCoolFighter(sld, iRank, 100, 100, "", "mushket1", "cartridge", 120);
			ChangeCharacterAddressGroup(sld, "Temple_great", "monsters", "mushketer"+i);
			sld.MusketerDistance = 0;
			LAi_SetWarriorType(sld);
			LAi_warrior_SetStay(sld, true);
			LAi_warrior_DialogEnable(sld, false);
		}
		// ставим воинов ица
		iTotalTemp = 5+makeint(MOD_SKILL_ENEMY_RATE/3);
		for(i=1; i<=iTotalTemp; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("Warrior_itza_"+i, "itza_"+i, "man", "man", iRank, PIRATE, -1, false, "native"));
			FantomMakeCoolFighter(sld, iRank, 100, 100, RandPhraseSimple("topor_01","blade_02"), "", "", 120);
			ChangeCharacterAddressGroup(sld, "Temple_great", "monsters", "warrior"+i);
			LAi_SetWarriorType(sld);
			LAi_warrior_SetStay(sld, true);
			LAi_warrior_DialogEnable(sld, false);
		}
		// добавочная группа ица
		for(i=11; i<=14; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("Warrior_itza_"+i, "itza_"+(i-7), "man", "man", iRank, PIRATE, -1, false, "native"));
			FantomMakeCoolFighter(sld, iRank, 90, 90, RandPhraseSimple("topor_01","blade_02"), "", "", 100);
			ChangeCharacterAddressGroup(sld, "Temple_great", "monsters", "warrior"+i);
			LAi_SetWarriorType(sld);
			LAi_warrior_SetStay(sld, true);
			LAi_warrior_DialogEnable(sld, false);
			LAi_group_MoveCharacter(sld, "TMP_FRIEND");
			LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "Tieyasal_AddingGroupActivate"); // patch-4
		}
	}
	else if (sQuestName == "Tieyasal_AddingGroupActivate") // 160912
	{
		pchar.quest.Tieyasal_2floor_add.over = "yes"; //снять прерывание
		for(i=11; i<=14; i++)
		{
			sld = characterFromId("Warrior_itza_"+i);
			LAi_RemoveCheckMinHP(sld);
			LAi_group_MoveCharacter(sld, "ITZA");
		}
		LAi_group_SetRelation("ITZA", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		//LAi_group_FightGroups("ITZA", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("ITZA", "Tieyasal_FloorWarriorDie");
	}
	else if (sQuestName == "Tieyasal_RunThirdFloor")
	{
		PlaySound("Ambient\Teno_inside\big_ring.wav");
		sld = characterFromId("Mishelle_mushketer");
		sld.lifeday = 0;
		LAi_LockFightMode(sld, true);
		LAi_group_MoveCharacter(sld, "TMP_FRIEND");
		ChangeCharacterAddressGroup(sld, "none", "", "");
		sld = characterFromId("Mishelle");
		ChangeCharacterAddressGroup(sld, "Temple_great", "quest", "mushketer");
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, "TMP_FRIEND");
		LAi_ActorRunToLocation(sld, "quest", "detector3", "none", "", "", "", -1);
		DeleteAttribute(pchar, "questTemp.Tieyasal.Shooter");
	}
	else if (sQuestName == "Tieyasal_FloorWarriorDie")
	{
		iRank = 30+MOD_SKILL_ENEMY_RATE*2;
		PlaySound("interface\abordage_wining.wav");
		PlaySound("interface\abordage_wining.wav");
		n = 3+makeint(MOD_SKILL_ENEMY_RATE/5);
		n = n+14;
		for(i=15; i<=n; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("Warrior_itza_"+i, "itza_"+(rand(7)+1), "man", "man", iRank, PIRATE, -1, false, "native"));
			FantomMakeCoolFighter(sld, iRank, 95, 95, "topor_01", "", "", 150);
			ChangeCharacterAddressGroup(sld, "Temple_great", "monsters", "warrior"+i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "ITZA");
		}
		LAi_group_SetRelation("ITZA", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("ITZA", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("ITZA", "Tieyasal_TempleWarriorDie");
	}
	else if (sQuestName == "Tieyasal_TempleWarriorDie")
	{
		DeleteAttribute(pchar, "questTemp.Tieyasal.LockGate");
		sld = characterFromId("Mishelle");
		LAi_SetImmortal(sld, false);
		LAi_SetCurHPMax(sld);
		LAi_GetCharacterMaxEnergy(sld);
		ChangeCharacterAddressGroup(sld, "Temple_great", "quest", "top");
		LAi_SetWarriorType(sld);
		LAi_warrior_SetStay(sld, true);
		iTemp = MOD_SKILL_ENEMY_RATE/2;
		TakeNItems(sld, "potion2", iTemp);
		LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)/2, true, "Tieyasal_TopAddWarrior"); // mitrokosta надо бессмертным делать
		iRank = 32+MOD_SKILL_ENEMY_RATE*2;
		for(i=1; i<=5; i++)
		{
			if (i == 4)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Top_itza_"+i, "mush_itza_"+(rand(2)+1), "man", "mushketer", iRank, PIRATE, -1, false, "quest"));
				FantomMakeCoolFighter(sld, iRank, 100, 100, "", "mushket2x2", "cartridge", 150);
				sld.MusketerDistance = 0;
			}
			else
			{
				sld = GetCharacter(NPC_GenerateCharacter("Top_itza_"+i, "itza_"+i, "man", "man", iRank, PIRATE, -1, false, "native"));
				FantomMakeCoolFighter(sld, iRank, 100, 100, "topor_01", "", "", 100);
			}
			ChangeCharacterAddressGroup(sld, "Temple_great", "monsters", "top"+i);
			LAi_SetWarriorType(sld);
			LAi_warrior_SetStay(sld, true);
			LAi_warrior_DialogEnable(sld, false);
		}
		// прерывание
		pchar.quest.Tieyasal_3floor.win_condition.l1 = "locator";
		pchar.quest.Tieyasal_3floor.win_condition.l1.location = "Temple_great";
		pchar.quest.Tieyasal_3floor.win_condition.l1.locator_group = "quest";
		pchar.quest.Tieyasal_3floor.win_condition.l1.locator = "detector3";
		pchar.quest.Tieyasal_3floor.function = "Tieyasal_ThirdFloorActivate";
	}
	else if (sQuestName == "Tieyasal_TopAddWarrior")
	{
		PlaySound("interface\abordage_wining.wav");
		// добавочная группа ица
		iRank = 32+MOD_SKILL_ENEMY_RATE*2;
		n = 2+makeint(MOD_SKILL_ENEMY_RATE/5);
		n = n+10;
		for(i=11; i<=n; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("Top_itza_add_"+i, "itza_"+(rand(7)+1), "man", "man", iRank, PIRATE, -1, false, "native"));
			FantomMakeCoolFighter(sld, iRank, 100, 100, "topor_01", "", "", 150);
			ChangeCharacterAddressGroup(sld, "Temple_great", "monsters", "warrior"+i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "ITZA");
		}
		sld = characterFromId("Mishelle");
		LAi_SetImmortal(sld, false);
		LAi_SetCheckMinHP(sld, 100, true, "Tieyasal_TempleFinalTalk");
	}
	else if (sQuestName == "Tieyasal_TempleFinalTalk")
	{
		// деактивируем оставшихся в живых индеев
		for(i=1; i<=5; i++)
		{
			sld = characterFromId("Top_itza_"+i);
			if (LAi_GetCharacterHP(sld) > 0)
			{
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "quest", "detector3", "none", "", "", "", 5.0);
			}
		}
		n = 2+makeint(MOD_SKILL_ENEMY_RATE/5);
		n = n+10;
		for(i=11; i<=n; i++)
		{
			sld = characterFromId("Top_itza_add_"+i);
			if (LAi_GetCharacterHP(sld) > 0)
			{
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "quest", "detector3", "none", "", "", "", 5.0);
			}
		}
		DoQuestCheckDelay("hide_weapon", 0.5);
		sld = characterFromId("Mishelle");
		sld.dialog.currentnode = "kukulkan_twice";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
	//		LAi_group_Delete("ITZA");  // даёт вылет в хардкор режиме
	}
	else if (sQuestName == "Tieyasal_KukulkanKick")
	{
		sld = characterFromId("Mishelle");
		LAi_SetActorType(sld);
		LAi_SetCurHPMax(sld);
		LAi_GetCharacterMaxEnergy(sld);
		LaunchBlast(sld);
		LaunchBlood(pchar, 1.8, true, "fire");
		Pchar.chr_ai.hp = stf(Pchar.chr_ai.hp)/5;
		LAi_SetActorType(pchar);
		LAi_ActorAnimation(pchar, "jump", "Tieyasal_SitInTemple", 0.5);
		PlaySound("People Fight\Death_NPC_08.wav");
	}
	else if (sQuestName == "Tieyasal_SitInTemple")
	{
		GetCharacterPos(pchar, &locx, &locy, &locz);
		locator = LAi_FindFarLocator("sit", locx, locy, locz);
		ChangeCharacterAddressGroup(pchar, "Temple_great", "sit", locator);
		LAi_SetActorType(pchar);
		LAi_ActorAnimation(pchar, "Ground_sitting", "", 2.5);
		DoQuestFunctionDelay("Tieyasal_StandUpInTemple", 2.5);
		LaunchBlood(pchar, 1.0, true, "fight");
		// запрещаем сохранение и интерфейсы, снимаем оружие
		bDisableCharacterMenu = true;
		InterfaceStates.Buttons.Save.enable = false;
		RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
		RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
		// ставим Мишеля, Канека и Уракана
		sld = characterFromId("Mishelle");
		LAi_ActorGoToLocator(sld, "goto", "stay1", "", -1);
		sld = characterFromId("Urakan");
		ChangeCharacterAddressGroup(sld, "Temple_great", "reload", "reload1");
		LAi_ActorGoToLocator(sld, "goto", "stay2", "", -1);
		sld = characterFromId("Kanek");
		ChangeCharacterAddressGroup(sld, "Temple_great", "quest", "detector3");
		LAi_ActorRunToLocator(sld, "goto", "stay3", "", -1);
		// убираем офицеров
		i = Findlocation("Tenochtitlan");
		DeleteAttribute(&locations[i], "setquestofficers");
	}
	else if (sQuestName == "Tieyasal_Fail_ReloadTown")
	{
		DoQuestReloadToLocation("Tenochtitlan", "reload", "reloadTemple33", "Tieyasal_Fail_GoToTown");
	}
	else if (sQuestName == "Tieyasal_Fail_GoToTown")
	{
		chr = characterFromId("Mishelle");
		LAi_SetActorType(chr);
		ChangeCharacterAddressGroup(chr, "Tenochtitlan", "reload", "reloadTemple32");
		LAi_ActorGoToLocation(chr, "reload", "reloadTemple31", "Temple_round", "quest", "kukulkan", "Tieyasal_Fail_GoToRoundTemple", -1);
		sld = characterFromId("Urakan");
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, "Tenochtitlan", "reload", "reloadTemple34");
		LAi_ActorFollow(sld, chr, "", -1);
		sld = characterFromId("Kanek");
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, "Tenochtitlan", "reload", "reloadTemple32");
		LAi_ActorFollow(sld, chr, "", -1);
		LAi_SetActorType(pchar);
		LAi_ActorFollow(pchar, chr, "", -1);
	}
	else if (sQuestName == "Tieyasal_Fail_GoToRoundTemple")
	{
		DoQuestReloadToLocation("Temple_round", "quest", "hero", "Tieyasal_Fail_IntoRoundTemple");
	}
	else if (sQuestName == "Tieyasal_Fail_IntoRoundTemple")
	{
		LAi_SetActorType(pchar);
		sld = characterFromId("Urakan");
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, "Temple_round", "quest", "urakan");
		sld = characterFromId("Kanek");
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, "Temple_round", "quest", "kanek");
		DoQuestCheckDelay("Tieyasal_Fail_RoundTempleRotate", 2.0);
	}
	else if (sQuestName == "Tieyasal_Fail_RoundTempleRotate")
	{
		locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.01, 0.0, 2.0, 0.0, 1700);
		Pchar.FuncCameraFly = "";
		DoQuestCheckDelay("Tieyasal_Fail_RoundTempleStop", 9.5);
	}
	else if (sQuestName == "Tieyasal_Fail_RoundTempleStop")
	{
		locCameraResetState();
		DoQuestCheckDelay("Tieyasal_Fail_KanekBead", 2.0);
	}
	else if (sQuestName == "Tieyasal_Fail_KanekBead")
	{
		sld = characterFromId("Kanek");
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "bead", "", 11.0);
		DoQuestCheckDelay("Tieyasal_Fail_DollyActivation", 11.0);
		PlaySound("Voice\Russian\sharlie\Kanek.wav");
		LAi_ActorTurnToCharacter(pchar, sld);
	}
	else if (sQuestName == "Tieyasal_Fail_DollyActivation")
	{
		CreateLocationParticles("fire_incas_Simple", "item", "dolly", 0.5, 0, 0, "");
		CreateLocationParticles("fire_incas_Simple", "item", "dolly", 1.0, 0, 0, "");
		CreateLocationParticles("fire_incas_Simple", "item", "dolly", 1.5, 0, 0, "");
		CreateLocationParticles("shadowstar", "shadowstar", "shadowstar1", 0, 0, 0, "");
		CreateLocationParticles("Firering", "item", "dolly", 1.0, 0, 0, "");
		DoQuestCheckDelay("Tieyasal_Fail_LastTalk", 4.0);
		LAi_ActorTurnToLocator(pchar, "item", "dolly");
	}
	else if (sQuestName == "Tieyasal_Fail_KanekPlace")
	{
		CreateLocationParticles("shadowstar", "shadowstar", "shadowstar1", 0, 0, 0, "");
		sld = characterFromId("Kanek");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocator(sld, "quest", "kanek", "Tieyasal_Fail_LastTalk", -1);
	}
	else if (sQuestName == "Tieyasal_Fail_LastTalk")
	{
		LAi_SetPlayerType(pchar);
		sld = characterFromId("Mishelle");
		sld.dialog.currentnode = "kukulkan_fail_8";
		LAi_SetActorType(sld);
		LAi_ActorDialogNow(sld, pchar, "", -1);
	}
	else if (sQuestName == "Tieyasal_Fail_TeleportStart")
	{
		SetMusic("music_teleport");
		PlaySound("interface\notebook.wav");
		for (i=1; i<=6; i++)
		{
			CreateLocationParticles("shadowstar", "goto", "goto"+i, 1.0, 0, 0, "");
		}
		DoQuestCheckDelay("Tieyasal_Fail_TeleportContinue_1", 7.0);
	}
	else if (sQuestName == "Tieyasal_Fail_TeleportContinue_1")
	{
		PlaySound("Weather\Thunder_Q.wav");
		CreateLocationParticles("shadowstar", "shadowstar", "shadowstar1", 0, 0, 0, "");
		for (i=1; i<=6; i++)
		{
			CreateLocationParticles("fire_incas", "goto", "goto"+i, 1.0, 0, 0, "");
		}
		DoQuestCheckDelay("Tieyasal_Fail_TeleportContinue_2", 7.0);
	}
	else if (sQuestName == "Tieyasal_Fail_TeleportContinue_2")
	{
		CreateLocationParticles("Firering", "item", "dolly", 1.0, 0, 0, "");
		for (i=1; i<=6; i++)
		{
			CreateLocationParticles("shadowstar", "goto", "goto"+i, 1.0, 0, 0, "");
		}
		PlaySound("Ambient\Teno_inside\big_ring.wav");
		DoQuestCheckDelay("Tieyasal_Fail_TeleportContinue_3", 6.0);
	}
	else if (sQuestName == "Tieyasal_Fail_TeleportContinue_3")
	{
		sld = characterFromId("Mishelle");
		ChangeCharacterAddressGroup(sld, "none", "", "");
		PlaySound("Ambient\Teno_inside\teleporter.wav");
		DoQuestCheckDelay("Tieyasal_Fail_TeleportContinue_4", 3.0);
	}
	else if (sQuestName == "Tieyasal_Fail_TeleportContinue_4")
	{
		PlaySound("Weather\Thunder_Q.wav");
		PlaySound("Ambient\Teno_inside\big_ring.wav");
		CreateLocationParticles("shipfire", "quest", "hero", 1.0, 0, 0, "");
		CreateLocationParticles("shipfire", "quest", "kukulkan", 1.0, 0, 0, "");
		CreateLocationParticles("shipfire", "quest", "urakan", 1.0, 0, 0, "");
		CreateLocationParticles("shipfire", "quest", "kanek", 1.0, 0, 0, "");
		PlaySound("Weather\koster_001.wav");
		for (i=1; i<=6; i++)
		{
			CreateLocationParticles("shipfire", "goto", "goto"+i, 1.0, 0, 0, "");
			for (n=1; n<=6; n++)
			{
				CreateLocationParticles("shadowstar", "goto", "goto"+i, 1.0, 0, 0, "");
			}
		}
		for (n=1; n<=10; n++)
		{
			CreateLocationParticles("shadowstar", "shadowstar", "shadowstar1", 0, 0, 0, "");
		}
		DoQuestCheckDelay("Tieyasal_Fail_TeleportContinue_5", 7.0);
	}
	else if (sQuestName == "Tieyasal_Fail_TeleportContinue_5")
	{
		sld = characterFromId("Kanek");
		ChangeCharacterAddressGroup(sld, "none", "", "");
		sld = characterFromId("Urakan");
		ChangeCharacterAddressGroup(sld, "none", "", "");
		RemoveAllCharacterItems(pchar, true);
		GiveItem2Character(pchar, "blade_13");
		EquipCharacterbyItem(pchar, "blade_13");
		GiveItem2Character(pchar, "pistol5");
		EquipCharacterbyItem(pchar, "pistol5");
		TakeNItems(pchar, "grapeshot", 50);
		AddItems(pchar, "bullet", 50);
		TakeNItems(pchar, "potion2", 3);
		LAi_SetCharacterUseBullet(pchar, GUN_ITEM_TYPE, "bullet");
		ChangeCharacterAddressGroup(pchar, "none", "", "");
		CreateLocationParticles("shadowstar_Big", "item", "dolly", 1.5, 0, 0, "");
		DoQuestCheckDelay("Tieyasal_Fail_TeleportContinue_6", 8.0);
	}
	else if (sQuestName == "Tieyasal_Fail_TeleportContinue_6")
	{
		SetLaunchFrameFormParam(StringFromKey("SharlieFinal_79", NewStr()), "", 0, 10);
		LaunchFrameForm();
		DoQuestCheckDelay("Tieyasal_Fail_TeleportContinue_7", 10.0);
		// меняем обличье Шарля
		ChangeShowIntarface();
		pchar.model = "Dragoon_1"; 
		pchar.model.animation = "man";
		Characters_RefreshModel(PChar);
		pchar.FaceId = 555; 
		pchar.name = StringFromKey("SharlieFinal_80");
		pchar.lastname = StringFromKey("SharlieFinal_81");
	}
	else if (sQuestName == "Tieyasal_Fail_TeleportContinue_7")
	{
		DoQuestReloadToLocation("Estate", "quest", "hero", "Europe_SharlieFinal");
	}
	else if (sQuestName == "Europe_SharlieFinal") // фэйловый финал
	{
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
		LAi_SetPlayerType(pchar);
		LAi_SetCurHPMax(pchar);
		LAi_GetCharacterMaxEnergy(pchar);
		sld = GetCharacter(NPC_GenerateCharacter("Piter", "blad_0", "man", "man", 10, ENGLAND, -1, false, "quest"));
		FantomMakeCoolFighter(sld, 10, 50, 50, "blade_12", "pistol1", "bullet", 100);
		ChangeCharacterAddressGroup(sld, "Estate", "quest", "piter");
		LAi_SetActorType(sld);
		for(i=1; i<=6; i++)
		{
			if (i == 1)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Europe_eng_"+i, "off_eng_4", "man", "man", 20, ENGLAND, -1, false, "quest"));
				FantomMakeCoolFighter(sld, 20, 50, 50, "blade_13", "pistol5", "bullet", 100);
				sld.name = StringFromKey("SharlieFinal_82");
				sld.lastname = StringFromKey("SharlieFinal_83");
				sld.dialog.FileName = "Quest\Sharlie\OtherNPC.c";
				sld.dialog.currentnode = "Europe";
				sld.greeting = "";
			}
			else
			{
				sld = GetCharacter(NPC_GenerateCharacter("Europe_eng_"+i, "sold_eng_"+(rand(7)+1), "man", "man", 20, ENGLAND, -1, false, "quest"));
				FantomMakeCoolFighter(sld, 20, 50, 50, "blade_12", "pistol1", "bullet", 100);
				LAi_CharacterDisableDialog(sld);
			}
			ChangeCharacterAddressGroup(sld, "Estate", "goto", "stay"+i);
			LAi_SetActorType(sld);
			if (i == 1) LAi_ActorDialog(sld, pchar, "", -1, 0);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
	}
	else if (sQuestName == "Europe_SharlieFinal_1")
	{
		SetMusic("music_MainMenu");
		pchar.questTemp.NoFast = true ; // запрет ускорения
		pchar.questTemp.Europe = true;
		pchar.questTemp.Tieyasal_FailEnd = true; // patch
		Achievment_Set("ach_47");
		if(MOD_SKILL_ENEMY_RATE > 9) Achievment_Set("ach_CL_103");
		if(CheckAttribute(pchar,"questTemp.HorseQty") && sti(pchar.questTemp.HorseQty) < 1)
		{
			if(!CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && !CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && !CheckAttribute(pchar, "quest.mtraxx_mirabella_life"))
			{
				Achievment_Set("ach_CL_104");
			}
		}
		LAi_SetPlayerType(pchar);
		DoQuestCheckDelay("TalkSelf_Quest", 0.1);
	}
	else if (sQuestName == "Europe_SharlieFinal_2")
	{
		ChangeShowIntarface();
		LAi_SetActorType(pchar);
		LAi_ActorGoToLocator(pchar, "goto", "goto8", "", -1);
		for(i=2; i<=6; i++)
		{
			sld = characterFromId("Europe_eng_"+i);
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
		}
		DoQuestCheckDelay("Europe_SharlieFinal_3", 0.5);
	}
	else if (sQuestName == "Europe_SharlieFinal_3")
	{
		SetMainCharacterIndex(GetCharacterIndex("Piter"));
		PChar = GetMainCharacter();
		locCameraFlyToPositionLookToHero(-22.5, 9.0, 3.25, 0, 14.0, 0.2, 0.01, -1);
		Pchar.FuncCameraFly = "";
		DoQuestCheckDelay("Europe_FinalFrame", 36.0);
	}
	else if (sQuestName == "Europe_FinalFrame")
	{
		SetLaunchFrameFormParam(StringFromKey("SharlieFinal_84", NewStr()), "", 0, 10);
		LaunchFrameForm();
		DoQuestCheckDelay("Final_Credits", 10.0);
	}
	else if (sQuestName == "Tieyasal_MishelleDie")
	{
		SetMusic("music_teleport");
		sld = characterFromId("Mishelle");
		LAi_SetImmortal(sld, false);
		LaunchIncasFire(sld, true);
		LaunchIncasFire(sld, true);
		LaunchIncasFire(sld, true);
		PlaySound("Ambient\Teno_inside\big_ring.wav");
		LAi_KillCharacter(sld);
		sld = characterFromId("Kanek");
		if (LAi_GetCharacterHP(sld) > 0) LAi_KillCharacter(sld);
		DoQuestFunctionDelay("Tieyasal_MishelleDie", 2.0);
		DoQuestCheckDelay("hide_weapon", 1.5);
	}
	else if (sQuestName == "Tieyasal_UrakanStay")
	{
		sld = characterFromId("Urakan");
		LAi_SetWarriorType(sld);
		LAi_warrior_SetStay(sld, true);
	}
	else if (sQuestName == "Tieyasal_MaskTerminationTurn")
	{
		LAi_ActorTurnToLocator(pchar, "item", "button04");
		DoQuestFunctionDelay("Tieyasal_MaskTerminationGo", 3.0);
	}
	else if (sQuestName == "Tieyasal_UrakanLastTalk")
	{
		LAi_SetPlayerType(pchar);
		sld = characterFromId("Urakan");
		sld.dialog.currentnode = "urakan_19";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	else if (sQuestName == "Tieyasal_FinalChoise")
	{
		if(MOD_SKILL_ENEMY_RATE > 9) Achievment_Set("ach_CL_103");
		if(CheckAttribute(pchar,"questTemp.HorseQty") && sti(pchar.questTemp.HorseQty) < 1)
		{
			if(!CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && !CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && !CheckAttribute(pchar, "quest.mtraxx_mirabella_life"))
			{
				Achievment_Set("ach_CL_104");
			}
		}
		LAi_SetPlayerType(pchar);
		DoQuestCheckDelay("TalkSelf_Quest", 0.1);
	}
	else if (sQuestName == "Final_ReturnToEurope") // финал - во Францию
	{
		EndQuestMovie();
		Achievment_Set("ach_48");
		pchar.GenQuest.VideoAVI = "Outro_home";
		pchar.GenQuest.VideoAfterQuest = "Final_Credits";
		DoQuestCheckDelay("PostVideo_Start", 0.2);
	}
	else if (sQuestName == "Final_StayInCarribean") // финал - остаемся
	{
		DeleteAttribute(pchar, "questTemp.Tieyasal_final");
		DeleteAttribute(pchar, "questTemp.Dolly_Tieyasal"); // прогон 4
		EndQuestMovie();
		InterfaceStates.Buttons.Save.enable = true;
		bDisableCharacterMenu = false;
		CloseQuestHeader("Tieyasal");
		AddQuestRecord("Sharlie", "43");
		CloseQuestHeader("Sharlie");
		Achievment_Set("ach_48");
		pchar.GenQuest.VideoAVI = "Outro_stay";
		PChar.GenQuest.VideoAfterQuest = "Final_ReloadShore";
		DoQuestCheckDelay("PostVideo_Start", 0.2);
		pchar.questTemp.Tieyasal_WinEnd = "true"; // patch-9
		Achievment_Set("ach_48");
		SetFunctionTimerCondition("LongHappy_Prepare", 0, 0, 1, false); // belamour legendary edition
	}
	else if (sQuestName == "Final_Credits")
	{
		GameOver("complete");
	}
	else if (sQuestName == "Final_ReloadShore")
	{
		DoQuestReloadToLocation("Shore_ship2", "goto", "goto1", "");
	}
	else
	{
		condition = false;
	}
	
	return condition;
}