//////////////////////////////////////////////////////////////////////////////////////////////////////////
// Jason ----------------------------------------Цена чахотки--------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Consumption_CommandantHouse(string qName)//создаем слугу и заполняем сундуки
{
	pchar.questTemp.Consumption.House = "true";//атрибут, что пришёл
	chrDisableReloadToLocation = true;
	int iRank = sti(pchar.rank)+10;
	int iScl = 20 + 2*sti(pchar.rank);
	sld = GetCharacter(NPC_GenerateCharacter("Conservant_1", "citiz_5", "man", "man", iRank, SPAIN, -1, true, "quest"));
	FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_10", "pistol1", "bullet", iScl*2);
	sld.dialog.FileName = "Quest\LineMiniQuests\Consumption.c";
	sld.dialog.currentnode = "Servant";
	sld.greeting = "citizen_male";
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, "PortSpein_houseF2", "goto", "goto4");
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	//заполним сундуки
	pchar.GenQuestBox.PortSpein_houseF2 = true;
	pchar.GenQuestBox.PortSpein_houseF2.box1.items.cannabis6 = 1;
	pchar.GenQuestBox.PortSpein_houseF2.box1.items.jewelry42 = 1;
	pchar.GenQuestBox.PortSpein_houseF2.box1.items.astrolab = 1;
	pchar.GenQuestBox.PortSpein_houseF2.box1.items.cirass2 = 1;
	pchar.GenQuestBox.PortSpein_houseF2.box1.items.gold_dublon = 44;
	pchar.GenQuestBox.PortSpein_houseF2.box2.items.potion2 = 15;
	pchar.GenQuestBox.PortSpein_houseF2.box2.items.jewelry6 = 72;
	pchar.GenQuestBox.PortSpein_houseF2.box2.items.jewelry3 = 12;
	pchar.GenQuestBox.PortSpein_houseF2.box2.items.indian_4 = 1;
	pchar.GenQuestBox.PortSpein_houseF2.box2.items.pistol6 = 1;
	pchar.GenQuestBox.PortSpein_houseF2.box3.items.letter_consumption = 1;
	pchar.GenQuestBox.PortSpein_houseF2.box3.items.map_trinidad = 1;
	pchar.GenQuestBox.PortSpein_houseF2.box3.items.recipe_berserker_potion = 1; // patch-9
	pchar.GenQuestBox.PortSpein_houseF2.box3.items.berserker_potion = 1; // patch-9
	pchar.GenQuestBox.PortSpein_houseF2.box3.items.jewelry15 = 1;
	pchar.GenQuestBox.PortSpein_houseF2.box3.items.gold_dublon = 500;
	//прерывание на письмо
	pchar.quest.Consumption1.win_condition.l1 = "item";
	pchar.quest.Consumption1.win_condition.l1.item = "letter_consumption";
	pchar.quest.Consumption1.function = "ConsumptionFindLetter";
}

void ConsumptionFindLetter(string qName)//нашли письмо
{
	AddQuestRecord("Consumption", "7");
	AddQuestUserData("Consumption", "sSex1", GetSexPhrase(StringFromKey("Consumption_1"),StringFromKey("Consumption_2")));
}

void Consumption_CreateSergio(string qName)//создаем Сержио
{
	chrDisableReloadToLocation = true;
	int iRank = sti(pchar.rank)+8;
	int iScl = 15 + 2*sti(pchar.rank); // patch-9
	sld = GetCharacter(NPC_GenerateCharacter("Sergio", "SerhioSaldo", "man", "man", iRank, SPAIN, -1, true, "quest"));
	FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_13", "pistol1", "bullet", iScl*2);
	sld.name = StringFromKey("Consumption_3");
    sld.lastname = StringFromKey("Consumption_4");
	sld.dialog.FileName = "Quest\LineMiniQuests\Consumption.c";
	sld.dialog.currentnode = "Sergio";
	sld.greeting = "soldier";
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	LAi_SetActorType(sld);
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, "PortSpein_town", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void Consumption_MeetSergio(string qName)//пришли на встречу
{
	chrDisableReloadToLocation = true;
	pchar.quest.Consumption4.over = "yes"; //снять прерывание
	if (CheckAttribute(pchar, "questTemp.Consumption.House"))
	{//подчистим дом коменданта
		pchar.GenQuestBox.PortSpein_houseF2 = true;
		pchar.GenQuestBox.PortSpein_houseF2.box1.items.mineral1 = 1;
		pchar.GenQuestBox.PortSpein_houseF2.box2.items.mineral5 = 1;
		pchar.GenQuestBox.PortSpein_houseF2.box3.items.mineral6 = 1;
		if (!CheckAttribute(pchar, "questTemp.Consumption.Fight")) 
		{
			sld = characterFromId("Conservant_1");
			sld.lifeday = 0;
		}
	}
	else pchar.quest.Consumption.over = "yes"; //снять прерывание
	sld = characterFromId("Sergio");
	sld.dialog.currentnode = "Sergio_5";
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, "PortSpein_Exittown", "rld", "aloc9");
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void Consumption_FailSergio(string qName)//опоздали
{
	locations[FindLocation("PortSpein_Exittown")].DisableEncounters = false; //энкаутеры открыть
	LAi_LocationDisableOfficersGen("PortSpein_Exittown", false);//офицеров пускать
	pchar.quest.Consumption3.over = "yes"; //снять прерывание
	if (CheckAttribute(pchar, "questTemp.Consumption.House"))
	{//подчистим дом коменданта
		pchar.GenQuestBox.PortSpein_houseF2 = true;
		pchar.GenQuestBox.PortSpein_houseF2.box1.items.mineral1 = 1;
		pchar.GenQuestBox.PortSpein_houseF2.box2.items.mineral5 = 1;
		pchar.GenQuestBox.PortSpein_houseF2.box3.items.mineral6 = 1;
		if (!CheckAttribute(pchar, "questTemp.Consumption.Fight")) 
		{
			sld = characterFromId("Conservant_1");
			sld.lifeday = 0;
		}
	}
	else pchar.quest.Consumption.over = "yes"; //снять прерывание
	AddQuestRecord("Consumption", "9");
	Consumption_Close();
}

void Consumption_CreateBandits()//бандиты Хуана
{
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE;
	int iScl = 10 + 2*sti(pchar.rank); // patch-9
	for (i=1; i<=3; i++)
	{
		if (i == 1)
		{
			sld = GetCharacter(NPC_GenerateCharacter("Conbandit_"+i, "mush_ctz_2", "man", "mushketer", iRank, PIRATE, 0, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "bullet", iScl*2); // patch-9
			sld.MusketerDistance = 0;
			ChangeCharacterAddressGroup(sld, "PortSpein_Exittown", "goto", "goto2");
		}
		else
		{
			sld = GetCharacter(NPC_GenerateCharacter("Conbandit_"+i, "citiz_"+(i+47), "man", "man", iRank, PIRATE, 0, true, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_17", "pistol3", "bullet", iScl*2); // patch-9
			DeleteAttribute(sld, "SaveItemsForDead");
			DeleteAttribute(sld, "DontClearDead");
			ChangeCharacterAddressGroup(sld, "PortSpein_Exittown", "rld", "aloc"+(i+4));
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			if (i == 2)
			{
				sld.dialog.filename = "Quest\LineMiniQuests\Consumption.c";
				sld.dialog.currentnode = "Bandit";
				LAi_SetActorType(sld);
				LAi_ActorDialogNow(sld, pchar, "", -1);
			}
		}
	}
}

void Consumption_CreateJuan(string qName)//галеон Хуана
{
	pchar.quest.Consumption6.over = "yes"; //снять прерывание
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE; // patch-9
	int iScl = 15 + 2*sti(pchar.rank);
	int iCannon, iShip;
	if (sti(pchar.rank) < 11)
	{
		iShip = SHIP_GALEON_L;
		iCannon = CANNON_TYPE_CANNON_LBS20;
	}
	else
	{
		iShip = SHIP_GALEON_H;
		if (sti(pchar.rank) < 18) iCannon = CANNON_TYPE_CANNON_LBS24;
		else iCannon = CANNON_TYPE_CANNON_LBS32;
	}
	Island_SetReloadEnableGlobal("Trinidad", false);
	Group_FindOrCreateGroup("ConJuanShip");
	sld = GetCharacter(NPC_GenerateCharacter("ConJuan", "HuanTubercul", "man", "man", iRank, PIRATE, -1, true, "quest"));
	sld.name = StringFromKey("Consumption_5");
    sld.lastname = StringFromKey("Consumption_6");
	FantomMakeSmallSailor(sld, iShip, "", iCannon, iScl, iScl, iScl, iScl, iScl);
	if(sti(pchar.rank) < 15 && MOD_SKILL_ENEMY_RATE < 9)
	{
		SetCrewQuantity(sld, GetOptCrewQuantity(sld));
	}
	FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_19", "pistol5", "bullet", iScl*3); // 280313
	sld.AlwaysEnemy = true;
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.Coastal_Captain = true;
	sld.WatchFort = true;
	sld.Ship.Mode = "pirate";
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	if (sti(pchar.rank) > 14) SetCharacterPerk(sld, "CannonProfessional");
	if (MOD_SKILL_ENEMY_RATE > 4) SetCharacterPerk(sld, "MusketsShoot");
	Group_AddCharacter("ConJuanShip", "ConJuan");
	Group_SetGroupCommander("ConJuanShip", "ConJuan");
	Group_SetTaskAttack("ConJuanShip", PLAYER_GROUP);
	Group_SetAddress("ConJuanShip", "Trinidad", "quest_ships", "quest_ship_8");
	Group_LockTask("ConJuanShip");
	pchar.quest.Consumption_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.Consumption_AfterBattle.win_condition.l1.group = "ConJuanShip";
	pchar.quest.Consumption_AfterBattle.function = "Consumption_AfterBattle";
	pchar.quest.Consumption_DieHard.win_condition.l1 = "MapEnter";
	pchar.quest.Consumption_DieHard.function = "Consumption_DieHard";
	pchar.Cheats.SeaTeleport = true;
}

void Consumption_AfterBattle(string qName)//победили
{
	DoQuestCheckDelay("sea_victory", 1.5);
	pchar.quest.Consumption_DieHard.over = "yes";
	Group_DeleteGroup("ConJuanShip");
	pchar.questTemp.Consumption = "final";
	if (CheckAttribute(pchar, "questTemp.Consumption.Abordage"))
	{
		AddComplexSeaExpToScill(250, 200, 200, 200, 200, 200, 0);
		ChangeOfficersLoyality("good_all", 1);
		AddQuestRecord("Consumption", "12");
		pchar.quest.Consumption_boom.win_condition.l1 = "NPC_Death";
		pchar.quest.Consumption_boom.win_condition.l1.character = "ConJuan_free";
		pchar.quest.Consumption_boom.function = "Consumption_OpenLocation";//для извращенцев
		bDisableSailTo = true;
	}
	else
	{
		Island_SetReloadEnableGlobal("Trinidad", true);
		ChangeOfficersLoyality("bad_all", 1);
		AddQuestRecord("Consumption", "13");
		AddQuestUserData("Consumption", "sSex", GetSexPhrase(StringFromKey("Consumption_7"),StringFromKey("Consumption_8")));
		Consumption_Close();
	}
}

void Consumption_OpenLocation(string qName)//открыть локацию
{
	log_Testinfo("ОСТРОВ ОТКРЫТ!!!");
	bDisableSailTo = false;
	Island_SetReloadEnableGlobal("Trinidad", true);
}

void Consumption_DieHard(string qName)//сбежали
{
	pchar.quest.Consumption_AfterBattle.over = "yes";
	Group_DeleteGroup("ConJuanShip");
	Island_SetReloadEnableGlobal("Trinidad", true);
	ChangeOfficersLoyality("bad_all", 1);
	AddQuestRecord("Consumption", "14");
	Consumption_Close();
}

void Consumption_FailJuan(string qName)//опоздали
{
	pchar.quest.Consumption5.over = "yes";
	AddQuestRecord("Consumption", "15");
	Consumption_Close();
}

void Consumption_Close()//подчистка квеста и возврат официантки в норму
{
	sld = characterFromId("PortSpein_waitress");
	DelLandQuestMark(sld);
	sld.dialog.filename = "Waitress_dialog.c";
	sld.dialog.currentnode = "First time";//вертаем ноду официантке
	CloseQuestHeader("Consumption");
	DeleteAttribute(pchar, "questTemp.Consumption");
	if(CheckAttribute(pchar, "Cheats.SeaTeleport")) DeleteAttribute(pchar, "Cheats.SeaTeleport");
}
//<-- Цена чахотки конец

//=================================================================
//======================кейсы из quests_reaction===================
//=================================================================
bool Consumption_QuestComplete(string sQuestName, string qname)
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////
// Jason ----------------------------------------Цена чахотки--------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////

	ref sld;
	
	bool condition = true;
	
	if (sQuestName == "Consumption_AfterHouseFight")
	{
		LAi_group_Delete("EnemyFight");
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
		chrDisableReloadToLocation = false;
		pchar.questTemp.Consumption.Fight = "true";
	}
	else if (sQuestName == "Conbandit_AfterFight")
	{
		DoQuestCheckDelay("hide_weapon", 1.3);
		LAi_group_Delete("EnemyFight");
		locations[FindLocation("PortSpein_Exittown")].DisableEncounters = false; //энкаутеры открыть
		LAi_LocationDisableOfficersGen("PortSpein_Exittown", false);//офицеров пускать
		sld = characterFromId("Sergio");
		if (LAi_GetCharacterHP(sld) > 0)
		{
			sld = characterFromId("Sergio");
			sld.dialog.currentnode = "Sergio_8";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		}
		else
		{
			chrDisableReloadToLocation = false;
			sld = characterFromId("PortSpein_waitress");
			sld.dialog.filename = "Waitress_dialog.c";
			sld.dialog.currentnode = "First time";//вертаем ноду официантке
			AddQuestRecord("Consumption", "10");
			CloseQuestHeader("Consumption");
			DeleteAttribute(pchar, "questTemp.Consumption");
		}
	}
	else if (sQuestName == "ConJuan_AfterFight_1")
	{
		Log_Info(StringFromKey("Consumption_9"));
		chrDisableReloadToLocation = false;
		pchar.GenQuest.ShipSituation.Explosion = ShipSituation_4;//ба-бах!
		pchar.GenQuest.ShipSituation.Explosion.CapId = "ConJuan";
		AddComplexSelfExpToScill(100, 100, 100, 100);
		pchar.questTemp.Consumption.Abordage = "true";
		DoQuestCheckDelay("LAi_ReloadBoarding", 1.0);
	}
	else if (sQuestName == "ConJuan_AfterFight_2")
	{
		pchar.GenQuest.ShipSituation.Explosion = ShipSituation_0;//ба-бах!
		pchar.GenQuest.ShipSituation.Explosion.CapId = "ConJuan";
		AddComplexSelfExpToScill(150, 150, 150, 150);
		pchar.questTemp.Consumption.Abordage = "true";
		ChangeCharacterComplexReputation(pchar, "nobility", 5);
		ChangeCharacterComplexReputation(pchar, "authority", 3);
		OfficersReaction("good");//ещё раз повысим репутацию
		Log_Info(StringFromKey("Consumption_10"));
	}
	else if (sQuestName == "ConsumptionSexWaitress")
	{
		sld = characterFromId("PortSpein_waitress");
		sld.dialog.currentnode = "Waitress_sex";
		LAi_SetStayType(sld);
	}
	else
	{
		condition = false;
	}
	
	return condition;
}