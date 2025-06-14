// --> Jason---------------------------------Бесчестный конкурент------------------------------------------
void ShadowTrader_Prepare(string qName)//Старт квеста
{
	if (SandBoxMode)
	{
		AddMapQuestMarkCity("BasTer", false);
		AddLandQuestMark(characterFromId("BasTer_trader"), "questmarkmain");
	}
}

void ShadowtraderTimeFort_Over(string qName)//просрочили отдать письмо коменданту
{
	DeleteAttribute(pchar, "questTemp.Shadowtrader.Fort");
	RemoveItems(PChar, "letter_1", 1);
	pchar.questTemp.Shadowtrader = "true";
	AddQuestRecord("Shadowtrader", "4");
	CloseQuestHeader("Shadowtrader");
	DeleteAttribute(pchar, "questTemp.Shadowtrader_Block");
	ChangeCharacterComplexReputation(pchar,"nobility", -1);
}

void ShadowtraderTimeSmugglers_Over(string qName)//просрочили прийти на стрелку
{
	pchar.quest.Shadowtrader_SMG.over = "yes"; //снять прерывание
	DeleteAttribute(pchar, "questTemp.Shadowtrader.SeekTrader");
	pchar.questTemp.Shadowtrader = "true";
	AddQuestRecord("Shadowtrader", "6");
	AddQuestUserData("Shadowtrader", "sSex1", GetSexPhrase(StringFromKey("MiniQuests_1"),StringFromKey("MiniQuests_2")));
	CloseQuestHeader("Shadowtrader");
	DeleteAttribute(pchar, "questTemp.Shadowtrader_Block");
	ChangeCharacterComplexReputation(pchar,"nobility", -1);
}

void ShadowAgent(string qName)//активация агента Паскаля
{
	pchar.quest.ShadowtraderTimeSmugglers_Over.over = "yes";//снять таймер
	sld = characterFromID("ShadowAgent_1");   
	LAi_SetActorType(sld);
	sld.dialog.Filename = "Quest\LineMiniQuests\ShadowTrader.c";
	sld.dialog.currentnode = "ShadowAgent";	
	sld.greeting = "marginal"; 
	LAi_ActorDialog(sld, pchar, "", -1, 0); 
	pchar.questTemp.Shadowtrader.ClearHouse = "true"; // 240912
}

void ShadowTrader_final(string qName)//выход из коммона на улицу
{
	chrDisableReloadToLocation = false;//открыть локацию
	DoQuestReloadToLocation(pchar.questTemp.Shadowtrader.City + "_town", "goto", "goto4", "");
	DeleteAttribute(pchar, "questTemp.Shadowtrader.ClearHouse"); // 240912
}

void ShadowTrader_questmark(string qName)//квестмарка на торговце
{
	AddMapQuestMarkCity("BasTer", false);
	AddLandQuestMark(characterFromId("BasTer_trader"), "questmarkmain");
	pchar.questTemp.Shadowtrader.EndFort = true;
}
// <-- Бесчестный конкурент конец

// --> Jason---------------------------------Дефицитный товар---------------------------------------------
void Wine_Exchange(string qName)
{
	sld = characterFromId(pchar.questTemp.Wine.id);
	sld.lifeday = 4;//на всякий случай
	LAi_SetStayType(sld);
	ChangeCharacterAddressGroup(sld, pchar.questTemp.Wine.City +"_fort", "goto", "goto53");
	sld.dialog.FileName = "Quest\LineMiniQuests\Wine.c";
	sld.dialog.currentnode = "Wine_fort";
	sld.greeting = "soldier";
	if(CheckAttribute(pchar,"questTemp.Wine.id") && GetCharacterIndex(pchar.questTemp.Wine.id) != -1)
	{
		AddLandQuestMark(characterFromId(pchar.questTemp.Wine.id), "questmarkmain");
	}
}

void WineTraderQM(string qName)
{
	for(i = 0; i < MAX_CHARACTERS; i++)
	{
		if(Characters[i].location != pchar.questTemp.Wine.City+"_town") continue;
        if(CheckAttribute(&Characters[i], "Merchant.type")) AddLandQuestMark(&Characters[i], "questmarkmain");
	}
}

void WineTraderQMDel()
{
	for(i = 0; i < MAX_CHARACTERS; i++)
	{
		if(Characters[i].location != pchar.questTemp.Wine.City+"_town") continue;
        if(CheckAttribute(&Characters[i], "Merchant.type")) DelLandQuestMark(&Characters[i]);
	}
}

void Soldier_wait(string qName)
{
	WineTraderQMDel();
	DelLandQuestMark(characterFromId(pchar.questTemp.Wine.TraderID));
	pchar.questTemp.Wine.fail = "true";
	AddQuestRecord("Wine", "2");
	CloseQuestHeader("Wine");
}

void Wine_wait(string qName)
{
	DeleteAttribute(pchar, "questTemp.Wine.wait");
	WineTraderQMDel();
	DelLandQuestMark(characterFromId(pchar.questTemp.Wine.TraderID));
}
// <--Дефицитный товар конец

// --> Jason -----------------------------Сомнительное предложение------------------------------------------------
void Contraoffer_Over(string qName)//просрочили доставить контрабанду
{
	AddQuestRecord("Contraoffer", "2");
	CloseQuestHeader("Contraoffer");
	DeleteAttribute(pchar, "GenQuest.Contraoffer");
}

void Contraoffer_Patrol() //нагрянул патруль
{	
	chrDisableReloadToLocation = true;
	LAi_group_Delete("EnemyFight"); 
	iTemp = sti(pchar.rank) + rand(MOD_SKILL_ENEMY_RATE); //это ранг от сложности
	int iNation = sti(pchar.GenQuest.Contraoffer.Trader.Nation);
	for (i=1; i<=3; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter("Contraoffer_patrol"+i, "sold_" + NationShortName(iNation) + "_" + (rand(1) + 1), "man", "man", iTemp, iNation, 0, true, "soldier"));
		SetFantomParamFromRank(sld, iTemp, true);         
		LAi_SetWarriorType(sld); 
		LAi_warrior_DialogEnable(sld, false);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
    }
    sld = GetCharacter(NPC_GenerateCharacter("Contraoffer_Officer", "off_" + NationShortName(iNation) + "_" + (rand(1) + 1), "man", "man", iTemp, iNation, 0, true, "soldier"));
	SetFantomParamFromRank(sld, iTemp, true); 
	sld.Dialog.Filename = "Quest\Other_Quests_NPC.c"; 
	sld.dialog.currentnode = "Contraoffer_patrol"; 
	sld.greeting = "soldier_arest";
    LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void Trader_free(string qName)//освобождаем диалог торговцу и затираем атрибуты
{
	DeleteAttribute(pchar, "GenQuest.Contraoffer.Trader");
}
// <-- Сомнительное предложение конец

// --> Jason -----------------------------------Охотник на корабли-----------------------------------------
void Findship_Over(string qName)//просрочили найти корабль на верфь
{
	AddQuestRecord("Findship", "2");
	CloseQuestHeader("Findship");
	DeleteAttribute(pchar, "GenQuest.Findship.Shipyarder");
}
// <-- Охотник на корабли конец

// --> Jason-------------------------------------Неудачливый вор-------------------------------------------
void Device_Over(string qName)//просрочили отыскать вора
{
	AddQuestRecord("Device", "2");
	CloseQuestHeader("Device");
	DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
}
// <-- Неудачливый вор конец

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Jason --> -------------------------------Заносчивый аристократ---------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Badboy_duelstart(string qName)
{
	pchar.quest.BadboyPlace.win_condition.l1 = "Location";
	pchar.quest.BadboyPlace.win_condition.l1.location = pchar.GenQuest.Badboy.Brothel.City + "_ExitTown";
	pchar.quest.BadboyPlace.function = "BadboyPlace";
}

void Badboy_duelOver(string qName)//не пришли на стрелку
{
	pchar.quest.BadboyPlace.over = "yes";
	LAi_LocationDisableOfficersGen(pchar.GenQuest.Badboy.Brothel.City + "_ExitTown", false);//офицеров пускать
	locations[FindLocation(pchar.GenQuest.Badboy.Brothel.City + "_ExitTown")].DisableEncounters = false; //энкаутеры откроем
	sld = characterFromId("Badboy");
	sld.lifeDay = 0;
}

void BadboyPlace(string qName)
{
	pchar.quest.Badboy_duelOver.over = "yes";
	LAi_group_Delete("EnemyFight"); 
    sld = characterFromID("Badboy");
	if (CheckAttribute(sld, "CityType"))
	{
		DeleteAttribute(sld, "City"); 
		DeleteAttribute(sld, "CityType");
	}
	ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_ExitTown", "goto", "goto1");
	LAi_SetActorType(pchar);
    LAi_SetActorType(sld);
    LAi_ActorTurnToCharacter(sld, pchar);
    SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
	LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
}

void Badboy_friends(string qName)
{
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
	chrDisableReloadToLocation = true;
	LAi_group_Delete("EnemyFight"); 
	iTemp = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE;
	for (i=1; i<=4; i++)
    {
		if (i == 1)
		{
			sld = characterFromID("Badboy");
			if (CheckAttribute(sld, "CityType"))
			{
				DeleteAttribute(sld, "City");
				DeleteAttribute(sld, "CityType");
			}
			TakeNItems(sld, "jewelry5", rand(10)); 
			TakeNItems(sld, "jewelry3", rand(10)); 
			TakeNItems(sld, "jewelry1", rand(10)); 
			sld.money = 24560;
			sld.SaveItemsForDead = true; // сохранять на трупе вещи
			sld.DontClearDead = true; // не убирать труп через 200с
		}
		else
		{
			sld = GetCharacter(NPC_GenerateCharacter("BadboyFriends_"+i, "citiz_"+(i + 40), "man", "man", iTemp, PIRATE, -1, true, "soldier"));
			FantomMakeCoolFighter(sld, iTemp, 40, 40, "blade_10", "pistol2", "bullet", 50);
			LAi_CharacterDisableDialog(sld);
		}
		LAi_SetActorType(sld);
		GetCharacterPos(pchar, &locx, &locy, &locz);
		ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_town", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
		LAi_group_MoveCharacter(sld, "EnemyFight");
		LAi_ActorDialog(sld, pchar, "", -1, 0); 
    }
}
// <-- Заносчивый аристократ конец

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// --> Jason -----------------------------------Место под солнцем---------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GetSunplaceShore()//выбор бухты
{
	pchar.GenQuest.Sunplace.Trader.Island = GetRandIslandId();
	while(pchar.GenQuest.Sunplace.Trader.Island == Islands[GetCharacterCurrentIsland(pchar)].id)
	{
		pchar.GenQuest.Sunplace.Trader.Island = GetRandIslandId();
	}
	pchar.GenQuest.Sunplace.Trader.Shore = GetIslandRandomShoreId(pchar.GenQuest.Sunplace.Trader.Island);
	while(pchar.GenQuest.Sunplace.Trader.Shore == "")
	{
		pchar.GenQuest.Sunplace.Trader.Island = GetRandIslandId();
		pchar.GenQuest.Sunplace.Trader.Shore = GetIslandRandomShoreId(pchar.GenQuest.Sunplace.Trader.Island);
		if (!isLocationFreeForQuests(pchar.GenQuest.Sunplace.Trader.Island)) pchar.GenQuest.Sunplace.Trader.Shore = "";
	}
}

void Sunplace_Over(string qName)//опоздали до места встречи
{
	pchar.quest.Sunplace_Trader.over = "yes";
	AddQuestRecord("Sunplace", "2");
	AddQuestUserData("Sunplace", "sType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Sunplace.Trader.ShipType), "Name"))));
	AddQuestUserData("Sunplace", "sSName", pchar.GenQuest.Sunplace.Trader.ShipName);
	AddQuestUserData("Sunplace", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.CityT+"Voc")); // belamour gen
	pchar.GenQuest.Sunplace.Trader = "continue";
	SetFunctionTimerCondition("SunplaceContinue_Over", 0, 0, 10, false);
}

void Sunplace_CreateTraderShip(string qName)//создание торгового корабля(-ей)
{
	pchar.quest.Sunplace_Over.over = "yes";
	int i, iNation, iShipType, iCannonType, iGoods, iSpace;
	iNation = sti(pchar.GenQuest.Sunplace.Trader.Nation);
	iShipType = sti(pchar.GenQuest.Sunplace.Trader.Shiptype);
	if (sti(pchar.rank) < 5) iCannonType = CANNON_TYPE_CULVERINE_LBS8;
	else iCannonType = CANNON_TYPE_CANNON_LBS16;
	iTemp = sti(pchar.rank)+2+rand(MOD_SKILL_ENEMY_RATE);
	sTemp = pchar.GenQuest.Sunplace.Trader.ShipName;
	Group_FindOrCreateGroup("SunplaceTrader");//создать группу
	Group_SetType("SunplaceTrader", "trade");//тип группы
	if (CheckAttribute(pchar, "GenQuest.Sunplace.Bonus"))
	{
		for (i=1; i<=4; i++)
		{
			if (i == 1) sTemp = pchar.GenQuest.Sunplace.Trader.ShipName;
			else sTemp = "";
			switch (i)
			{
				case 1: 
					iGoods = GOOD_MAHOGANY;
					iSpace = 500+rand(200);
					iShipType = SHIP_GALEON_H;
				break;
				case 2: 
					iGoods = GOOD_CHOCOLATE;
					iSpace = 1000+rand(200);
					iShipType = SHIP_GALEON_L;
				break;
				case 3: 
					iGoods = GOOD_EBONY;
					iSpace = 400+rand(100);
					iShipType = SHIP_PINNACE;
				break;
				case 4:
					iGoods = GOOD_COFFEE;
					iSpace = 500+rand(100);
					iShipType = SHIP_CORVETTE;
				break;
			}
			sld = GetCharacter(NPC_GenerateCharacter("SunplaceCaptain_"+i, "citiz_41", "man", "man", iTemp, iNation, 1, true, "quest"));
			FantomMakeSmallSailor(sld, iShipType, sTemp, CANNON_TYPE_CANNON_LBS20, 50+rand(10), 25+rand(10), 25+rand(10), 30+rand(10), 30+rand(10));
			SetFantomParamFromRank(sld, iTemp, true);
			SetCaptanModelByEncType(sld, "trade");
			Fantom_SetCharacterGoods(sld, iGoods, iSpace, 1);
			Group_AddCharacter("SunplaceTrader", "SunplaceCaptain_"+i);
			DeleteAttribute(sld, "SaveItemsForDead");
			DeleteAttribute(sld, "DontClearDead");
			sld.DontRansackCaptain = true; 
			sld.AlwaysEnemy = true;
			sld.AnalizeShips = true;
			sld.Ship.Mode = "trade";
			SetCharacterPerk(sld, "Tireless");
			SetCharacterPerk(sld, "HardHitter");
		}
		AddQuestRecord("Sunplace", "14");
		AddQuestUserData("Sunplace", "sType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Sunplace.Trader.ShipType), "Name"))));
		AddQuestUserData("Sunplace", "sGoods", GetGoodsNameAlt(sti(pchar.GenQuest.Sunplace.Trader.Goods)));
		AddQuestUserData("Sunplace", "sSName", pchar.GenQuest.Sunplace.Trader.ShipName);
	}
	else
	{
		sld = GetCharacter(NPC_GenerateCharacter("SunplaceCaptain_1", "citiz_41", "man", "man", iTemp, iNation, 1, true, "quest"));
		FantomMakeSmallSailor(sld, iShipType, sTemp, iCannonType, 30+rand(10), 15+rand(10), 15+rand(10), 20+rand(10), 20+rand(10));
		SetFantomParamFromRank(sld, iTemp, true); 
		SetCaptanModelByEncType(sld, "trade");
		iGoods = sti(pchar.GenQuest.Sunplace.Trader.Goods);
		iSpace = GetCharacterFreeSpace(sld, iGoods);
		iSpace = makeint(iSpace/2 + rand(iSpace/2));
		Fantom_SetCharacterGoods(sld, iGoods, iSpace, 1);
		Group_AddCharacter("SunplaceTrader", "SunplaceCaptain_1");
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		sld.DontRansackCaptain = true; 
		sld.AlwaysEnemy = true;
		sld.AnalizeShips = true;
		SetCharacterPerk(sld, "Tireless");
		SetCharacterPerk(sld, "HardHitter");
		AddQuestRecord("Sunplace", "3");
		AddQuestUserData("Sunplace", "sType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Sunplace.Trader.ShipType), "Name"))));
		AddQuestUserData("Sunplace", "sSName", pchar.GenQuest.Sunplace.Trader.ShipName);
	}

	Group_SetGroupCommander("SunplaceTrader", "SunplaceCaptain_1");
	Group_SetTaskAttack("SunplaceTrader", PLAYER_GROUP);
	Group_SetAddress("SunplaceTrader", pchar.GenQuest.Sunplace.Trader.Island, "quest_ships", "Quest_ship_6");
	Group_LockTask("SunplaceTrader");
	
	pchar.quest.Sunplace_AfterBattle.win_condition.l1 = "Character_Capture";
	pchar.quest.Sunplace_AfterBattle.win_condition.l1.character = "SunplaceCaptain_1";
	pchar.quest.Sunplace_AfterBattle.function = "Sunplace_AfterBattle";
	pchar.quest.Sunplace_AfterBattle_1.win_condition.l1 = "Character_sink";
	pchar.quest.Sunplace_AfterBattle_1.win_condition.l1.character = "SunplaceCaptain_1";
	pchar.quest.Sunplace_AfterBattle_1.function = "Sunplace_AfterBattle";
	pchar.quest.Sunplace_DieHard.win_condition.l1 = "MapEnter";
    pchar.quest.Sunplace_DieHard.function = "Sunplace_DieHard";
}

void Sunplace_AfterBattle(string qName)//реакция на победу
{
	DoQuestCheckDelay("sea_victory", 1.5);
	pchar.quest.Sunplace_AfterBattle.over = "yes";
	pchar.quest.Sunplace_AfterBattle_1.over = "yes";
	pchar.quest.Sunplace_DieHard.over = "yes";
	Group_DeleteGroup("SunplaceTrader");
    pchar.quest.Sunplace_DieHard.over = "yes";
	AddQuestRecord("Sunplace", "4");
	pchar.GenQuest.Sunplace.Trader = "complete";
	AddComplexSeaExpToScill(50, 50, 50, 50, 50, 50, 0);
}

void Sunplace_DieHard(string qName)//реакция на поражение
{
    pchar.quest.Sunplace_AfterBattle.over = "yes";
	pchar.quest.Sunplace_AfterBattle_1.over = "yes";
	if (CheckAttribute(pchar, "GenQuest.Sunplace.Bonus") && GetCharacterIndex("SunplaceCaptain_3") == -1)
	{
		AddQuestRecord("Sunplace", "4");
		AddQuestUserData("Sunplace", "sType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Sunplace.Trader.ShipType), "Name"))));
		pchar.GenQuest.Sunplace.Trader = "complete";
	}
	else
	{
		AddQuestRecord("Sunplace", "5");
		AddQuestUserData("Sunplace", "sType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Sunplace.Trader.ShipType), "Name"))));
		AddQuestUserData("Sunplace", "sSName", pchar.GenQuest.Sunplace.Trader.ShipName);
		AddQuestUserData("Sunplace", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.CityT+"Voc")); // belamour gen
		pchar.GenQuest.Sunplace.Trader = "continue";
		SetFunctionTimerCondition("SunplaceContinue_Over", 0, 0, 10, false);
	}
	Group_DeleteGroup("SunplaceTrader");
}

void SunplaceContinue_Over(string qName)//провалили все и окончательно по срокам
{
	pchar.quest.Sunplace_Store.over = "yes";
	AddQuestRecord("Sunplace", "11");
	CloseQuestHeader("Sunplace");
	DeleteAttribute(pchar, "GenQuest.Sunplace.Trader");
}

void Sunplace_CreateTrader(string qName)//создание конкурента в магазине
{
	ref chr = characterFromId(pchar.GenQuest.Sunplace.Trader.CityT + "_trader");
	sld = GetCharacter(NPC_GenerateCharacter("SunplaceTrader", "trader_7", "man", "man", 10, sti(chr.nation), -1, true, "quest"));
	FantomMakeCoolFighter(sld, 10, 10, 10, "", "", "bullet", 10);
	sld.name = pchar.GenQuest.Sunplace.Trader.Enemyname;
	sld.lastname = "";
	sld.dialog.FileName = "Quest\Other_quests_NPC.c";
	sld.dialog.currentnode = "Sunplace_Store";
	sld.money = 25650;
	sld.SaveItemsForDead = true; // сохранять на трупе вещи
	sld.DontClearDead = true; // не убирать труп через 200с
	LAi_SetCitizenType(sld);
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, pchar.GenQuest.Sunplace.Trader.CityT + "_store", "goto", "goto1");
}
	
void Kill_SunplaceTrader(string qName)//проверка убийства конкурента
{
	if (GetCharacterIndex("SunplaceTrader") == -1)
	{
		AddQuestRecord("Sunplace", "8");
		AddQuestUserData("Sunplace", "sName", pchar.GenQuest.Sunplace.Trader.Enemyname);
		pchar.GenQuest.Sunplace.Trader = "complete_murder";
	}
	else
	{
		sld = CharacterFromID("SunplaceTrader");
		sld.lifeday = 0;
		AddQuestRecord("Sunplace", "9");
		CloseQuestHeader("Sunplace");
		DeleteAttribute(pchar, "GenQuest.Sunplace.Trader");
	}
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.GenQuest.Sunplace.Trader.CityT + "_store")], true);
}

void Sunplace_CreateTraderLugger(string qName)//создание люггера конкурента
{
	pchar.quest.SunplaceContinue_Over.over = "yes";
	int iNation;
	iNation = sti(pchar.GenQuest.Sunplace.Trader.EnemyNation);
	iTemp = sti(pchar.rank)+2+rand(MOD_SKILL_ENEMY_RATE);
	Group_FindOrCreateGroup("SunplaceLugger");//создать группу
	Group_SetType("SunplaceLugger", "trade");//тип группы
	sld = GetCharacter(NPC_GenerateCharacter("Sunplace_Trader", "trader_7", "man", "man", iTemp, iNation, -1, true, "quest"));
	FantomMakeSmallSailor(sld, SHIP_LUGGER, "", CANNON_TYPE_CANNON_LBS6, 30+rand(10), 15+rand(10), 15+rand(10), 20+rand(10), 20+rand(10));
	SetFantomParamFromRank(sld, iTemp, true); 
	sld.name = pchar.GenQuest.Sunplace.Trader.Enemyname;
	sld.lastname = "";
	sld.SaveItemsForDead = true; // сохранять на трупе вещи
	sld.DontClearDead = true; // не убирать труп через 200с
	sld.DontRansackCaptain = true; 
	sld.AnalizeShips = true;
	sld.Ship.Mode = "trade";
	sld.money = 25650;
	Group_AddCharacter("SunplaceLugger", "Sunplace_Trader");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");

	Group_SetGroupCommander("SunplaceLugger", "Sunplace_Trader");
	Group_SetTaskRunaway("SunplaceLugger", PLAYER_GROUP);
	Group_SetAddress("SunplaceLugger", pchar.GenQuest.Sunplace.Trader.IslandID, "quest_ships", "Quest_ship_6");
	Group_LockTask("SunplaceLugger");
	
    pchar.quest.SunplaceLugger_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.SunplaceLugger_AfterBattle.win_condition.l1.group = "SunplaceLugger";
	pchar.quest.SunplaceLugger_AfterBattle.function = "SunplaceLugger_AfterBattle";
	pchar.quest.SunplaceLugger_DieHard.win_condition.l1 = "MapEnter";
    pchar.quest.SunplaceLugger_DieHard.function = "SunplaceLugger_DieHard";
}

void SunplaceLugger_AfterBattle(string qName)//реакция на победу
{
	DoQuestCheckDelay("sea_victory", 1.5);
	Group_DeleteGroup("SunplaceLugger");
    pchar.quest.SunplaceLugger_DieHard.over = "yes";
	AddQuestRecord("Sunplace", "8");
	AddQuestUserData("Sunplace", "sName", pchar.GenQuest.Sunplace.Trader.Enemyname);
	pchar.GenQuest.Sunplace.Trader = "complete_murder";
	AddComplexSeaExpToScill(50, 50, 50, 50, 50, 50, 0);
}

void SunplaceLugger_DieHard(string qName)//реакция на поражение
{
	Group_DeleteGroup("SunplaceLugger");
    pchar.quest.SunplaceLugger_AfterBattle.over = "yes";
	AddQuestRecord("Sunplace", "10");
	CloseQuestHeader("Sunplace");
	DeleteAttribute(pchar, "GenQuest.Sunplace.Trader");
}
// <-- Место под солнцем

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// --> Jason -----------------------------Сопровождение торговца из таверны----------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GetEscortTraderShore()//выбор бухты для эскорта торговца из таверны
{
	pchar.GenQuest.Escort.Trader.Island = GetRandIslandId();
	while(pchar.GenQuest.Escort.Trader.Island == Islands[GetCharacterCurrentIsland(pchar)].id)
	{
		pchar.GenQuest.Escort.Trader.Island = GetRandIslandId();
	} // patch-6
	pchar.GenQuest.Escort.Trader.Shore = GetIslandRandomShoreId(pchar.GenQuest.Escort.Trader.Island);
	while(pchar.GenQuest.Escort.Trader.Shore == "")
	{
		pchar.GenQuest.Escort.Trader.Island = GetRandIslandId();
		pchar.GenQuest.Escort.Trader.Shore = GetIslandRandomShoreId(pchar.GenQuest.Escort.Trader.Island);
		if (!isLocationFreeForQuests(pchar.GenQuest.Escort.Trader.Island)) pchar.GenQuest.Escort.Trader.Shore = "";
	}
	pchar.GenQuest.Escort.Trader.City = FindTownOnIsland(pchar.GenQuest.Escort.Trader.Island);
}

void CreateTraderShipAndAdd(ref sld)//создаем корабль сопровождаемого торговца 
{
	int iGoods, iSpace;
	int iShipType = sti(pchar.GenQuest.Escort.Trader.ShipType);
	// --> mitrokosta fix lifeday & name change
	int iRank = sti(pchar.rank) + 10;
	DeleteAttribute(sld, "CityType");
	DeleteAttribute(sld, "City");
	sld.rank = iRank;
	sld.lifeday = sti(pchar.GenQuest.Escort.Trader.DaysQty) + 1;
	sld.PhantomType = "citizen";
	SetFantomParamFromRank(sld, iRank, true);
	// <--
	FantomMakeSmallSailor(sld, iShipType, "", CANNON_TYPE_CANNON_LBS12, 40+rand(10), 30+rand(10), 30+rand(10), 30+rand(10), 30+rand(10));
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	SetCharacterGoods(sld, GOOD_FOOD, 300+rand(100));
	SetCharacterGoods(sld, GOOD_MEDICAMENT, 60+rand(30));
	iGoods = GOOD_COFFEE + hrand(sti(GOOD_PAPRIKA - GOOD_COFFEE)); // тэг из диалога
	iSpace = GetCharacterFreeSpace(sld, iGoods);
	iSpace = makeint(iSpace/2 + rand(iSpace/2));
	SetCharacterGoods(sld, iGoods, iSpace);
	SetCharacterRemovable(sld, false);
	SetCompanionIndex(pchar, -1, sti(sld.index));
	sld.loyality = MAX_LOYALITY;
	sld.Abordage.Enable = false;
	sld.AlwaysFriend = true;
	//sld.CompanionEnemyEnable = true;
}

void EscortTrader_Over(string qName)//опоздали сопроводить 170712
{
	pchar.quest.EscortTrader_fail.over = "yes";
	pchar.quest.EscortTrader_Complete.over = "yes";
	pchar.quest.EscortTrader_Attack.over = "yes";
	//RemoveCharacterCompanion(Pchar, characterFromID(pchar.GenQuest.Escort.Trader.id));
	sld = characterFromId(pchar.GenQuest.Escort.Trader.id);
	RemoveCharacterCompanion(Pchar, sld);//лесник удаление из эскадры ,так надежнее. если что - верну обратно .
	sld.lifeday = 0;//лесник . разлокировал 
	AddQuestRecord("TraderEscort", "2");
	CloseQuestHeader("TraderEscort");
	DeleteAttribute(pchar, "GenQuest.Escort.Trader");
	ChangeOfficersLoyality("bad_all", 1);
}

void EscortTrader_failed(string qName)//потеряли сопровождаемого 170712
{
	pchar.quest.EscortTrader_Complete.over = "yes";
	pchar.quest.EscortTrader_Over.over = "yes";
	pchar.quest.EscortTrader_Attack.over = "yes";
	ChangeCharacterComplexReputation(pchar,"nobility", -5);
	ChangeCharacterNationReputation(pchar, sti(pchar.GenQuest.Escort.Trader.Nation), -5);
	AddQuestRecord("TraderEscort", "3");
	CloseQuestHeader("TraderEscort");
	DeleteAttribute(pchar, "GenQuest.Escort.Trader");
	ChangeOfficersLoyality("bad_all", 1);
}

void EscortTraderAttackInShore(string qName)//в бухте напали пираты
{
	Island_SetReloadEnableGlobal(pchar.GenQuest.Escort.Trader.Island, false);//на остров нельзя
	Group_DeleteGroup("Pirate_Attack");
	Group_FindOrCreateGroup("Pirate_Attack");
	SelectLevelWarShipParameter();//автолевеллинг
    for (int i = 1; i <= 2; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter("TPirate_"+i, "mercen_"+(rand(27)+1), "man", "man", sti(PChar.rank) + 8, PIRATE, 10, true, "hunter"));
		FantomMakeSmallSailor(sld, iGlobalTemp, "", iTotalTemp, 30+rand(5), 30+rand(5), 30+rand(5), 30+rand(5), 35+rand(5));
		FantomMakeCoolFighter(sld, sti(PChar.rank)+5, 30, 30, sTotalTemp, "pistol2", "grapeshot", 30);
        Group_AddCharacter("Pirate_Attack", "TPirate_"+i);
    }
    Group_SetGroupCommander("Pirate_Attack", "TPirate_1");
	Group_SetTaskAttack("Pirate_Attack", PLAYER_GROUP);
	Group_SetPursuitGroup("Pirate_Attack", PLAYER_GROUP);
	Group_SetAddress("Pirate_Attack", pchar.GenQuest.Escort.Trader.Island, "", "");
	Group_LockTask("Pirate_Attack");
    
    pchar.quest.EscortTraderInShore_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.EscortTraderInShore_AfterBattle.win_condition.l1.group = "Pirate_Attack";
	pchar.quest.EscortTraderInShore_AfterBattle.function = "EscortTraderInShore_AfterBattle";
	pchar.quest.EscortTraderInShore_DieHard.win_condition.l1 = "MapEnter";
    pchar.quest.EscortTraderInShore_DieHard.function = "EscortTraderInShore_DieHard";
}

void EscortTraderInShore_AfterBattle(string qName)//победили
{
	DoQuestCheckDelay("sea_victory", 1.5);
	pchar.quest.EscortTraderInShore_DieHard.over = "yes";
	Group_DeleteGroup("Pirate_Attack");
	Island_SetReloadEnableGlobal(pchar.GenQuest.Escort.Trader.Island, true);
	AddQuestRecord("TraderEscort", "12");
	ChangeOfficersLoyality("good_all", 1);
	ChangeCharacterComplexReputation(pchar, "authority", 1);
	AddComplexSeaExpToScill(50, 50, 50, 100, 50, 50, 0);
}

void EscortTraderInShore_DieHard(string qName)//сбежали
{
	pchar.quest.EscortTraderInShore_AfterBattle.over = "yes";
	Group_DeleteGroup("Pirate_Attack");
	Island_SetReloadEnableGlobal(pchar.GenQuest.Escort.Trader.Island, true);
	pchar.quest.EscortTrader_fail.over = "yes";
	pchar.quest.EscortTrader_Complete.over = "yes";
	pchar.quest.EscortTrader_Over.over = "yes";//снять три прерывания
	sld = characterFromId(pchar.GenQuest.Escort.Trader.id);
	sld.lifeday = 0;
	RemoveCharacterCompanion(Pchar, sld);
	DeleteAttribute(pchar, "GenQuest.Escort.Trader");
	AddQuestRecord("TraderEscort", "13");
	AddQuestUserData("TraderEscort", "sSex1", GetSexPhrase(StringFromKey("MiniQuests_1"),StringFromKey("MiniQuests_2")));
	CloseQuestHeader("TraderEscort");
	ChangeOfficersLoyality("bad_all", 1);
}

void EscortTraderEnemy_Over(string qName)//опоздали по наводке
{
	pchar.quest.EscortTrader_EnTrader.over = "yes";
	DeleteAttribute(pchar, "GenQuest.Escort.Trader");
	AddQuestRecord("TraderEscort", "8");
	AddQuestUserData("TraderEscort", "sSex", GetSexPhrase(StringFromKey("MiniQuests_3"),StringFromKey("MiniQuests_4")));
	CloseQuestHeader("TraderEscort");
	ChangeOfficersLoyality("bad_all", 1);
}

void Create_EnemyTraderFleut(string qName)//флейт торговца
{
	pchar.quest.EscortTraderEnemy_Over.over = "yes";
	Island_SetReloadEnableGlobal(pchar.GenQuest.Escort.Trader.EnIsland, false);//на остров нельзя
	Group_DeleteGroup("Trade_Attack");
	Group_FindOrCreateGroup("Trade_Attack");
    sld = GetCharacter(NPC_GenerateCharacter("EnTrader", "trader_"+(rand(15)+1), "man", "man", sti(PChar.rank)+3, sti(pchar.GenQuest.Escort.Trader.Nation), 5, true, "quest"));
	sld.name = pchar.GenQuest.Escort.Trader.Enemyname;
	sld.lastname = "";
	FantomMakeSmallSailor(sld, SHIP_FLEUT, "", CANNON_TYPE_CANNON_LBS12, 20+rand(5), 15+rand(5), 20+rand(5), 15+rand(5), 15+rand(5));
	SetFantomParamFromRank(sld, sti(PChar.rank)+3, true); 
	sld.AlwaysEnemy = true;
	sld.Ship.Mode = "trade";
	int iGoods = sti(pchar.GenQuest.Escort.Trader.Goods);
	int iSpace = GetCharacterFreeSpace(sld, iGoods);
	iSpace = makeint(iSpace - iSpace/10);
	SetCharacterGoods(sld, iGoods, iSpace);
    Group_AddCharacter("Trade_Attack", "EnTrader");
		
    Group_SetGroupCommander("Trade_Attack", "EnTrader");
	Group_SetTaskRunaway("Trade_Attack", PLAYER_GROUP);
	Group_SetAddress("Trade_Attack", pchar.GenQuest.Escort.Trader.EnIsland, "quest_ships", "quest_ship_6");
	Group_LockTask("Trade_Attack");
    
	//на захват абордажем
	pchar.quest.EnemyTrader_Abordage.win_condition.l1 = "Character_Capture";
	pchar.quest.EnemyTrader_Abordage.win_condition.l1.character = "EnTrader";
	pchar.quest.EnemyTrader_Abordage.function = "EnemyTrader_Win";//взяли на абордаж
	//на потопление орудиями
	pchar.quest.EnemyTrader_Sink.win_condition.l1 = "Character_sink";
	pchar.quest.EnemyTrader_Sink.win_condition.l1.character = "EnTrader";
	pchar.quest.EnemyTrader_Sink.function = "EnemyTrader_Fail";//потопили
	//на карту
	pchar.quest.EnemyTrader_DieHard.win_condition.l1 = "MapEnter";
    pchar.quest.EnemyTrader_DieHard.function = "EnemyTrader_DieHard";
}

void EnemyTrader_Win(string qName)//победили
{
	DoQuestCheckDelay("sea_victory", 1.5);
	pchar.quest.EnemyTrader_DieHard.over = "yes";
	pchar.quest.EnemyTrader_Sink.over = "yes";
	Group_DeleteGroup("Trade_Attack");
	Island_SetReloadEnableGlobal(pchar.GenQuest.Escort.Trader.EnIsland, true);
	AddQuestRecord("TraderEscort", "9");
	AddQuestUserData("TraderEscort", "sSex1", GetSexPhrase(StringFromKey("MiniQuests_1"),StringFromKey("MiniQuests_2")));
	AddQuestUserData("TraderEscort", "sSex2", GetSexPhrase(StringFromKey("MiniQuests_5"),StringFromKey("MiniQuests_6")));
	AddQuestUserData("TraderEscort", "sAdd", pchar.GenQuest.Escort.Trader.add);
	CloseQuestHeader("TraderEscort");
	DeleteAttribute(pchar, "GenQuest.Escort.Trader");
	AddComplexSeaExpToScill(50, 50, 50, 100, 50, 50, 0);
	AddComplexSelfExpToScill(30, 30, 30, 30);
	AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
	AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
	ChangeOfficersLoyality("good_all", 1);
}

void EnemyTrader_Fail(string qName)//утонул флейт
{
	pchar.quest.EnemyTrader_DieHard.over = "yes";
	pchar.quest.EnemyTrader_Abordage.over = "yes";
	Group_DeleteGroup("Trade_Attack");
	Island_SetReloadEnableGlobal(pchar.GenQuest.Escort.Trader.EnIsland, true);
	AddQuestRecord("TraderEscort", "15");
	AddQuestUserData("TraderEscort", "sSex", GetSexPhrase(StringFromKey("MiniQuests_3"),StringFromKey("MiniQuests_4")));
	CloseQuestHeader("TraderEscort");
	DeleteAttribute(pchar, "GenQuest.Escort.Trader");
	AddCharacterExpToSkill(pchar, "Sailing", 10);//навигация
	AddCharacterExpToSkill(pchar, "Accuracy", 20);//меткость
	AddCharacterExpToSkill(pchar, "Cannons", 20);//орудия
	AddCharacterExpToSkill(pchar, "Defence", 10);//защита
	ChangeOfficersLoyality("bad_all", 1);
}

void EnemyTrader_DieHard(string qName)//сбежали
{
	pchar.quest.EnemyTrader_Abordage.over = "yes";
	pchar.quest.EnemyTrader_DieHard.over = "yes";
	Group_DeleteGroup("Trade_Attack");
	Island_SetReloadEnableGlobal(pchar.GenQuest.Escort.Trader.EnIsland, true);
	AddQuestRecord("TraderEscort", "10");
	AddQuestUserData("TraderEscort", "sSex1", GetSexPhrase(StringFromKey("MiniQuests_7"),StringFromKey("MiniQuests_8")));
	CloseQuestHeader("TraderEscort");
	DeleteAttribute(pchar, "GenQuest.Escort.Trader");
	ChangeOfficersLoyality("bad_all", 1);
}

void DesIslandAttack(string qName)//нападение торговца-пирата
{
	Log_Info(StringFromKey("MiniQuests_9"));
	Island_SetReloadEnableGlobal(pchar.GenQuest.Escort.Trader.Island, false);//на остров нельзя
	pchar.quest.EscortTrader_fail.over = "yes";
	pchar.quest.EscortTrader_Complete.over = "yes";
	pchar.quest.EscortTrader_Over.over = "yes";//снять три прерывания
	Group_FindOrCreateGroup("ETAttack"); 
	Group_SetType("ETAttack", "pirate");
	sld = characterFromId(pchar.GenQuest.Escort.Trader.id); 
	RemoveCharacterCompanion(Pchar, sld);
	Group_AddCharacter("ETAttack", pchar.GenQuest.Escort.Trader.id);
	sld.lifeday = 0;
	DeleteAttribute(sld, "AlwaysFriend");
	sld.Coastal_Captain = true;//не ругать нации
	sld.alwaysenemy = true;
	sld.nation = PIRATE;
	sld.Ship.Mode = "pirate";
	Ship_FlagRefresh(sld);
	Ship_NationAgressivePatent(sld);
	Ship_SetTaskAttack(SECONDARY_TASK, sti(sld.index), sti(pchar.index));
	SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);
	RefreshBattleInterface();
	UpdateRelations();
	if (sti(pchar.GenQuest.Escort.Trader.Chance) == 2)
	{
		SelectLevelWarShipParameter();//автолевеллинг
		for (int i = 1; i <= 2; i++)
		{
        sld = GetCharacter(NPC_GenerateCharacter("TPirate_"+i, "mercen_"+(rand(27)+1), "man", "man", sti(PChar.rank) + 5, PIRATE, 1, true, "hunter"));
		FantomMakeSmallSailor(sld, iGlobalTemp, "", iTotalTemp, 30+rand(5), 30+rand(5), 30+rand(5), 30+rand(5), 35+rand(5));
		FantomMakeCoolFighter(sld, sti(PChar.rank), 30, 30, sTotalTemp, "pistol2", "grapeshot", 30);
        Group_AddCharacter("ETAttack", "TPirate_"+i);
		}
	}
	Group_SetGroupCommander("ETAttack", pchar.GenQuest.Escort.Trader.id);
	Group_SetAddress("ETAttack", pchar.GenQuest.Escort.Trader.Island, "", "");
	Group_SetPursuitGroup("ETAttack", PLAYER_GROUP);
	Group_LockTask("ETAttack");
	pchar.quest.EscortTradeAttack_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.EscortTradeAttack_AfterBattle.win_condition.l1.group = "ETAttack";
	pchar.quest.EscortTradeAttack_AfterBattle.function = "EscortTraderAttack_AfterBattle";
	pchar.quest.EscortTradeAttack_DieHard.win_condition.l1 = "MapEnter";
    pchar.quest.EscortTradeAttack_DieHard.function = "EscortTraderAttack_DieHard";
}

void EscortTraderAttack_AfterBattle(string qName)//уничтожили врага
{
	DoQuestCheckDelay("sea_victory", 1.5);
	pchar.quest.EscortTradeAttack_DieHard.over = "yes";
	Group_DeleteGroup("Trade_Attack");
	Island_SetReloadEnableGlobal(pchar.GenQuest.Escort.Trader.Island, true); // patch-8
	DeleteAttribute(pchar, "GenQuest.Escort.Trader");
	if (sti(pchar.GenQuest.Escort.Trader.Chance) == 2) AddQuestRecord("TraderEscort", "11");
	else AddQuestRecord("TraderEscort", "14");
	AddQuestUserData("TraderEscort", "sSex1", GetSexPhrase(StringFromKey("MiniQuests_1"),StringFromKey("MiniQuests_2")));
	CloseQuestHeader("TraderEscort");
	AddComplexSeaExpToScill(100, 100, 100, 100, 100, 100, 0);
	AddCharacterExpToSkill(pchar, "Leadership", 100);//харизма
	AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
	ChangeOfficersLoyality("good_all", 1);
}

void EscortTraderAttack_DieHard(string qName)//ушли на карту
{
	pchar.quest.EscortTradeAttack_AfterBattle.over = "yes";
	Group_DeleteGroup("Trade_Attack");
	Island_SetReloadEnableGlobal(pchar.GenQuest.Escort.Trader.Island, true); // patch-8
	DeleteAttribute(pchar, "GenQuest.Escort.Trader");
	if (sti(pchar.GenQuest.Escort.Trader.Chance) == 2) AddQuestRecord("TraderEscort", "11");
	else AddQuestRecord("TraderEscort", "14");
	AddQuestUserData("TraderEscort", "sSex1", GetSexPhrase(StringFromKey("MiniQuests_1"),StringFromKey("MiniQuests_2")));
	CloseQuestHeader("TraderEscort");
	AddCharacterExpToSkill(pchar, "Sailing", 20);//навигация
	AddCharacterExpToSkill(pchar, "Defence", 20);//защита
	AddCharacterExpToSkill(pchar, "Repair", 20);//починка
	AddCharacterExpToSkill(pchar, "Sneak", 20);//скрытность
	ChangeOfficersLoyality("bad_all", 1);
}

void EscortTraderComplete(string qName)//сдача квеста по прибытию на место
{
	chrDisableReloadToLocation = true;
	bDisableFastReload = true;
	GetCharacterPos(pchar, &locx, &locy, &locz);
	sld = characterFromId(pchar.GenQuest.Escort.Trader.id);
	sld.lifeday = 0;
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, pchar.GenQuest.Escort.Trader.Location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_SetActorType(sld);
	sld.dialog.Filename = "Quest\QuestTrader_dialog.c";
	sld.dialog.currentnode = "EscortTrader_complete";
	sld.greeting = "captain_complete_1";
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}
// <-- Сопровождение торговца из таверны

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//--> Jason ------------------------------------гонки на гидропланах-----------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MCRaceInTargetCity(string qName)//прибыл ГГ
{
	pchar.quest.RacingTimeOver.over = "yes";
	if (!CheckAttribute(pchar, "GenQuest.Racing.Go.TraderWin"))
	{
	pchar.GenQuest.Racing.Go.MCWin = "true";
	AddQuestRecord("Racing", "2");
	AddQuestUserData("Racing", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.City+"Gen"));
	}
	else AddQuestRecord("Racing", "3");
}

void TraderRaceInTargetCity(string qName)//прибыл торговец
{
	int iNation = sti(pchar.GenQuest.Racing.Go.Nation);
	if (!CheckAttribute(pchar, "GenQuest.Racing.Go.MCWin")) pchar.GenQuest.Racing.Go.TraderWin = "true";
	sld = characterFromId("RaceTrader");
	ref chr = GetCharacter(NPC_GenerateCharacter("RaceTraderSkiper", "mercen_"+(rand(29)+1), "man", "man", sti(PChar.rank) + 20, iNation, -1, true, "quest"));
	FantomMakeSmallSailor(chr, SHIP_FLEUT, pchar.GenQuest.Racing.Go.ShipName, CANNON_TYPE_CANNON_LBS12, 100, 50, 50, 50, 50);
	chr.name = StringFromKey("MiniQuests_10");
	chr.lastname = GenerateRandomName_Generator(iNation, "man");
	Group_FindOrCreateGroup("RacingTrader"); 
	Group_SetType("RacingTrader", "Trade");//тип группы
	Group_AddCharacter("RacingTrader", "RaceTraderSkiper");
	Group_SetGroupCommander("RacingTrader", "RaceTraderSkiper");
	Group_SetAddress("RacingTrader", pchar.GenQuest.Racing.Go.Island, "quest_ships", "quest_ship_1");
	//для особо упоротых
	pchar.quest.Racing_fail.win_condition.l1 = "NPC_Death";
	pchar.quest.Racing_fail.win_condition.l1.character = "RaceTraderSkiper";
	pchar.quest.Racing_fail.function = "Racing_failed";
	//торговца усадим в таверну
	LAi_SetSitType(sld);
	FreeSitLocator(pchar.GenQuest.Racing.Go.City + "_tavern", "sit_front1");
	ChangeCharacterAddressGroup(sld, pchar.GenQuest.Racing.Go.City + "_tavern", "sit", "sit_front1");
	sld.dialog.currentnode = "Racing_Finished";
	sld.greeting = "captain_complete_2";
}

void Racing_failed(string qName)//если у кого-то хватит тупости
{
	pchar.quest.RacingTimeOver.over = "yes";
	Group_DeleteGroup("RacingTrader");
	sld = characterFromId("RaceTrader");
	sld.lifeday = 0;
	sld = characterFromId("RaceTraderSkiper");
	sld.lifeday = 0;
	ChangeCharacterHunterScore(PChar, NationShortName(sti(pchar.GenQuest.Racing.Go.Nation)) + "hunter", 90); //начислить НЗГ
	ChangeCharacterComplexReputation(pchar,"authority", -5);
	ChangeOfficersLoyality("bad_all", 5);
	DeleteAttribute(pchar, "GenQuest.Racing.Go");
	AddQuestRecord("Racing", "7");
	CloseQuestHeader("Racing");
}

void RacingTimeOver(string qName)//не пришли совсем
{
	pchar.quest.Racing_Finish.over = "yes";
	pchar.quest.Racing_fail.over = "yes";
	Group_DeleteGroup("RacingTrader");
	sld = characterFromId("RaceTrader");
	sld.lifeday = 0;
	sld = characterFromId("RaceTraderSkiper");
	sld.lifeday = 0;
	DeleteAttribute(pchar, "GenQuest.Racing.Go");
	ChangeCharacterComplexReputation(pchar,"authority", -2);
	ChangeOfficersLoyality("bad_all", 1);
	AddQuestRecord("Racing", "6");
	CloseQuestHeader("Racing");
}
//<-- гонки на гидропланах

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// --> Jason -----------------------------------мини-квесты монахов-------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Monkletter_Over(string qName)//опоздали с депешей
{
	pchar.GenQuest.Monkletter.Late = "true";
	AddQuestRecord("Monkletter", "4");
	AddQuestUserData("Monkletter", "sSex1", GetSexPhrase(StringFromKey("MiniQuests_1"),StringFromKey("MiniQuests_2")));
}

void Churchbooks_Over(string qName)//опоздали с доставкой молитвенников
{
	pchar.GenQuest.Churchbooks.Late = "true";
	AddQuestRecord("Churchbooks", "5");
}

void Monkpassenger_Over(string qName)//опоздали с пассажиром
{
	pchar.quest.Monkpassenger.over = "yes";
	sld = characterFromId(pchar.GenQuest.Monkpassenger.id);
	sTemp = sld.index+"Citizpassenger";
	if (IsEntity(&worldMap) || bSeaActive) 
	{
		pchar.quest.Monkpassenger_remove.win_condition.l1 = "Location_Type";
		pchar.quest.Monkpassenger_remove.win_condition.l1.location_type = "town";
		pchar.quest.Monkpassenger_remove.function = "Monkpassenger_remove";
	}
	else
	{
		RemovePassenger(Pchar, sld);
		log_info(StringFromKey("MiniQuests_11", GetFullName(sld)));
		AddQuestRecordEx(sTemp, "Citizpassenger", "2");
		CloseQuestHeader(sTemp);
		sld.lifeday = 0;
		DeleteAttribute(Pchar, "GenQuest.Monkpassenger");
	}
}

void Monkpassenger_remove(string qName)//удаление пассажира
{
	sld = characterFromId(pchar.GenQuest.Monkpassenger.id);
	sTemp = sld.index+"Citizpassenger";
	RemovePassenger(Pchar, sld);
	log_info(StringFromKey("MiniQuests_11", GetFullName(sld)));
	AddQuestRecordEx(sTemp, "Citizpassenger", "2");
	CloseQuestHeader(sTemp);
	sld.lifeday = 0;
	DeleteAttribute(Pchar, "GenQuest.Monkpassenger");
}

void Monkpassenger_complete(string qName)//доставили пассажира
{
	sld = characterFromId(pchar.GenQuest.Monkpassenger.id);
	sld.Dialog.currentnode = "passenger_3";
	GetCharacterPos(pchar, &locx, &locy, &locz);
    ChangeCharacterAddressGroup(sld, pchar.GenQuest.Monkpassenger.City+"_town", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void Monkshipshine_Over(string qName)//действие освящения окончено
{
	DeleteAttribute(Pchar, "GenQuest.Shipshine");
	log_testinfo("Действие освящения истекло!");
}

void ShipCapellan_Remove()//удаление капеллана
{
	sld = characterFromId(pchar.questTemp.ShipCapellan.id);
	sld.dialog.currentnode = "capellan_7";
	DeleteAttribute(Pchar, "questTemp.ShipCapellan.Yes");
	if (IsEntity(&worldMap) || bSeaActive) 
	{
		pchar.quest.ShipCapellan_remove.win_condition.l1 = "Location_Type";
		pchar.quest.ShipCapellan_remove.win_condition.l1.location_type = "town";
		pchar.quest.ShipCapellan_remove.function = "ShipCapellan_remove_1";
	}
	else
	{
		RemovePassenger(Pchar, sld);
		log_info(StringFromKey("MiniQuests_12", GetFullName(sld)));
		PlaySound("interface\notebook.wav");
		sld.lifeday = 0;
		DeleteAttribute(Pchar, "questTemp.ShipCapellan.id");
	}
}

void ShipCapellan_remove_1(string qName)//удаление капеллана
{
	sld = characterFromId(pchar.questTemp.ShipCapellan.id);
	RemovePassenger(Pchar, sld);
	log_info(StringFromKey("MiniQuests_12", GetFullName(sld)));
	PlaySound("interface\notebook.wav");
	sld.lifeday = 0;
	DeleteAttribute(Pchar, "questTemp.ShipCapellan.id");
}
//<-- мини-квесты монахов

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// --> Jason -----------------------------------мини-квесты горожан-------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Townpassenger_Over(string qName)//опоздали с пассажиром
{
	pchar.quest.Townpassenger.over = "yes";
	sld = characterFromId(pchar.GenQuest.Townpassenger.id);
	sTemp = sld.index+"Citizpassenger";
	if (IsEntity(&worldMap) || bSeaActive) 
	{
		pchar.quest.Townpassenger_remove.win_condition.l1 = "Location_Type";
		pchar.quest.Townpassenger_remove.win_condition.l1.location_type = "town";
		pchar.quest.Townpassenger_remove.function = "Townpassenger_remove";
	}
	else
	{
		RemovePassenger(Pchar, sld);
		log_info(StringFromKey("MiniQuests_11", GetFullName(sld)));
		AddQuestRecordEx(sTemp, "Citizpassenger", "2");
		CloseQuestHeader(sTemp);
		sld.lifeday = 0;
		DeleteAttribute(Pchar, "GenQuest.Townpassenger");
	}
}

void Townpassenger_remove(string qName)//удаление пассажира
{
	sld = characterFromId(pchar.GenQuest.Townpassenger.id);
	sTemp = sld.index+"Citizpassenger";
	RemovePassenger(Pchar, sld);
	log_info(StringFromKey("MiniQuests_11", GetFullName(sld)));
	AddQuestRecordEx(sTemp, "Citizpassenger", "2");
	CloseQuestHeader(sTemp);
	sld.lifeday = 0;
	DeleteAttribute(Pchar, "GenQuest.Townpassenger");
}

void Townpassenger_complete(string qName)//доставили пассажира
{
	chrDisableReloadToLocation = true;//закрыть локацию
	sld = characterFromId(pchar.GenQuest.Townpassenger.id);
	sld.Dialog.currentnode = "passenger_3";
	GetCharacterPos(pchar, &locx, &locy, &locz);
    ChangeCharacterAddressGroup(sld, pchar.GenQuest.Townpassenger.City+"_town", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}
//<-- мини-кветсы горожан

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// --> Jason -----------------------------------мини-квесты дворян-------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Noblepassenger_Over(string qName)//опоздали с пассажиром
{
	pchar.quest.Noblepassenger.over = "yes";
	sld = characterFromId(pchar.GenQuest.Noblepassenger.id);
	sTemp = sld.index+"Citizpassenger";
	if (IsEntity(&worldMap) || bSeaActive) 
	{
		pchar.quest.Noblepassenger_remove.win_condition.l1 = "Location_Type";
		pchar.quest.Noblepassenger_remove.win_condition.l1.location_type = "town";
		pchar.quest.Noblepassenger_remove.function = "Noblepassenger_remove";
	}
	else
	{
		RemovePassenger(Pchar, sld);
		log_info(StringFromKey("MiniQuests_11", GetFullName(sld)));
		AddQuestRecordEx(sTemp, "Citizpassenger", "2");
		CloseQuestHeader(sTemp);
		sld.lifeday = 0;
		DeleteAttribute(Pchar, "GenQuest.Noblepassenger");
	}
}

void Noblepassenger_remove(string qName)//удаление пассажира
{
	sld = characterFromId(pchar.GenQuest.Noblepassenger.id);
	sTemp = sld.index+"Citizpassenger";
	RemovePassenger(Pchar, sld);
	log_info(StringFromKey("MiniQuests_11", GetFullName(sld)));
	AddQuestRecordEx(sTemp, "Citizpassenger", "2");
	CloseQuestHeader(sTemp);
	sld.lifeday = 0;
	DeleteAttribute(Pchar, "GenQuest.Noblepassenger");
}

void Noblepassenger_complete(string qName)//доставили пассажира
{
	chrDisableReloadToLocation = true;//закрыть локацию
	sld = characterFromId(pchar.GenQuest.Noblepassenger.id);
	sld.Dialog.currentnode = "passenger_3";
	GetCharacterPos(pchar, &locx, &locy, &locz);
    ChangeCharacterAddressGroup(sld, pchar.GenQuest.Noblepassenger.City+"_town", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void Noblelombard_Over(string qName)//время вышло
{
	sld = characterFromId(pchar.GenQuest.Noblelombard.id);
	sld.lifeday = 0;
	if (CheckAttribute(pchar, "GenQuest.Noblelombard.Regard")) AddQuestRecord("Noblelombard", "3");
	else AddQuestRecord("Noblelombard", "2");
	CloseQuestHeader("Noblelombard");
	//sld = characterFromId(pchar.GenQuest.Noblelombard.City+"_usurer");// лесник . из за этого вылет .
	DeleteAttribute(pchar, "quest.noblelombard");// лесник . с нпчара на пчара. теперь ок
	DeleteAttribute(Pchar, "GenQuest.Noblelombard");
}

void Noblelombard_Regard(string qName)//можно идти за наградой
{
	pchar.GenQuest.Noblelombard.Giveregard = "true";
}
//<-- мини-квесты дворян

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// --> Jason -----------------------------мини-квесты тёмных личностей----------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Marginpassenger_Over(string qName)
{
	DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
}

void Marginpassenger_InWorld(string qName)//запускаем кораблик с пассажиром на карте
{
    string sGroup = "Sea_MarginCap1";
	Group_DeleteGroup(sGroup);
	Group_FindOrCreateGroup(sGroup);
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE;
	int iScl = 3*sti(pchar.rank)+10;
	int iDays = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.GenQuest.Marginpassenger.Targetcity), GetArealByCityName(pchar.GenQuest.Marginpassenger.City))+5;
	int iShipType = pchar.GenQuest.Marginpassenger.ShipType;
	sTemp = pchar.GenQuest.Marginpassenger.ShipName;
	if (sti(pchar.rank) < 5) iTemp = CANNON_TYPE_CANNON_LBS3;
	if (sti(pchar.rank) >= 5 && sti(pchar.rank) < 8) iTemp = CANNON_TYPE_CANNON_LBS6;
	if (sti(pchar.rank) >= 8 && sti(pchar.rank) < 12) iTemp = CANNON_TYPE_CANNON_LBS12;
	if (sti(pchar.rank) >= 12 && sti(pchar.rank) < 15) iTemp = CANNON_TYPE_CANNON_LBS16;
	if (sti(pchar.rank) >= 15) iTemp = CANNON_TYPE_CANNON_LBS20;
	sld = GetCharacter(NPC_GenerateCharacter("MarginCap", "citiz_41", "man", "man", iRank, sti(pchar.GenQuest.Marginpassenger.Nation), iDays, true, "quest"));
	FantomMakeSmallSailor(sld, iShipType, sTemp, iTemp, iScl+10, iScl, iScl, iScl, iScl);
	SetFantomParamFromRank(sld, iRank, true); 
	SetCaptanModelByEncType(sld, "trade");
	sld.Ship.Mode = "trade";
	SetRandomNameToCharacter(sld);
	sld.Dialog.Filename = "Quest\Marginpassenger.c";
	sld.DeckDialogNode = "MarginCap";
	LAi_SetHP(sld, 170+iScl, 170+iScl);
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	TakeNItems(sld, "potion2", 3);
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "AdvancedBattleState");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "ShipSpeedUp");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	sld.mapEnc.type = "trade";
	sld.mapEnc.worldMapShip = "ranger";
	sld.mapEnc.Name = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name")))+" '"+pchar.GenQuest.Marginpassenger.ShipName + "'";
	Group_AddCharacter(sGroup, "MarginCap");
	Group_SetGroupCommander(sGroup, "MarginCap");
	Map_CreateTrader(pchar.GenQuest.Marginpassenger.City, pchar.GenQuest.Marginpassenger.Targetcity, "MarginCap", iDays);

	SetFunctionTimerCondition("Marginpassenger_InWorldOver", 0, 0, iDays, false);
	pchar.quest.Marginpassenger_Sink.win_condition.l1 = "Character_sink";
	pchar.quest.Marginpassenger_Sink.win_condition.l1.character = "MarginCap";
	pchar.quest.Marginpassenger_Sink.function = "Marginpassenger_InWorldFail";//потопили
}

void Marginpassenger_InWorldOver(string qName)//упустили кораблик
{
	pchar.quest.Marginpassenger_Sink.over = "yes"; //снять прерывание
	AddQuestRecord("Marginpassenger", "2");
	AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName);
	CloseQuestHeader("Marginpassenger");
	Group_DeleteGroup("Sea_MarginCap1");
	DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
	ChangeCharacterComplexReputation(pchar, "authority", -1);
	ChangeOfficersLoyality("bad_all", 1);
}

void Marginpassenger_InWorldFail(string qName)//потопили в бою
{
	pchar.quest.Marginpassenger_InWorldOver.over = "yes"; //снять прерывание
	Group_DeleteGroup("Sea_MarginCap1");
	AddQuestRecord("Marginpassenger", "3");
	AddQuestUserData("Marginpassenger", "sSex", GetSexPhrase(StringFromKey("MiniQuests_3"),StringFromKey("MiniQuests_4")));
	AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName);
	CloseQuestHeader("Marginpassenger");
	DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
	ChangeCharacterComplexReputation(pchar, "authority", -1);
	ChangeOfficersLoyality("bad_all", 1);
}

void Marginpassenger_CreateNeedman()//создаем выкупателя
{
	sld = GetCharacter(NPC_GenerateCharacter("MarginNeed", "citiz_"+(rand(9)+11), "man", "man", 10, sti(pchar.GenQuest.Marginpassenger.Nation), -1, true, "quest"));
	sld.Dialog.Filename = "Quest\Marginpassenger.c";
	sld.Dialog.currentnode = "MarginNeed";
	sld.name = pchar.GenQuest.Marginpassenger.q2Name;
	sld.lastname = "";
	LAi_SetImmortal(sld, true);
	RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
	RemoveCharacterEquip(sld, GUN_ITEM_TYPE);
	LAi_SetCitizenType(sld);
	ChangeCharacterAddressGroup(sld, pchar.GenQuest.Marginpassenger.Targetcity+"_town", "quest", "quest2");
	LAi_SetLoginTime(sld, 12.0, 21.0);
}

void Marginpassenger_SouthshoreOver(string qName)//опоздали в бухту
{
	AddQuestRecord("Marginpassenger", "14");
	AddQuestUserData("Marginpassenger", "sSex", GetSexPhrase(StringFromKey("MiniQuests_3"),StringFromKey("MiniQuests_4")));
	AddQuestUserData("Marginpassenger", "sShore", XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Dat"));
	CloseQuestHeader("Marginpassenger");
	DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
	ChangeCharacterComplexReputation(pchar, "authority", -1);
	ChangeOfficersLoyality("bad_all", 1);
	DeleteQuestCondition("Marginpassenger");
}

void Marginpassenger_Southshore(string qName)//бой в бухте
{
	pchar.quest.Marginpassenger_SouthshoreOver.over = "yes"; //снять таймер
	chrDisableReloadToLocation = true;
	GetCharacterPos(pchar, &locx, &locy, &locz);
	int iRank = sti(pchar.rank)+2;
	int iScl = 15 + 2*sti(pchar.rank);
	int n = 5+makeint(MOD_SKILL_ENEMY_RATE/2);
	//наши
    for (i=1; i<=9; i++)
    {
		sld = GetCharacter(NPC_GenerateCharacter("MPCrew_"+i, "citiz_"+(rand(9)+31), "man", "man", iRank, sti(pchar.nation), 0, true, "soldier"));
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_10", "pistol1", "bullet", iScl*2);
        LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		sTemp = LAi_FindNearestFreeLocator("goto", locx, locy, locz);
		if (sTemp == "") sTemp = LAi_FindNearestLocator("goto", locx, locy, locz);
        ChangeCharacterAddressGroup(sld, pchar.GenQuest.Marginpassenger.Shore, "goto", sTemp);
    }
	//враги
	for (int i=1; i <=n; i++)
	{
		if (i == 1)
		{
			sld = GetCharacter(NPC_GenerateCharacter("MPEnemy_"+i, "mush_spa_1", "man", "mushketer", iRank+3, SPAIN, 0, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank+3, iScl+2, iScl+2, "", "mushket1", "cartridge", iScl*2);
		}
		else
		{
			sld = GetCharacter(NPC_GenerateCharacter("MPEnemy_"+i, "sold_spa_"+(rand(7)+1), "man", "man", iRank+3, SPAIN, 0, true, "soldier"));
			FantomMakeCoolFighter(sld, iRank+3, iScl+2, iScl+2, "blade_10", "pistol1", "bullet", iScl*2);
		}
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		ChangeCharacterAddressGroup(sld, pchar.GenQuest.Marginpassenger.Shore, "reload", "reload1");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	sld = GetCharacter(NPC_GenerateCharacter("Spa_shore_off", "off_spa_"+(rand(1)+1), "man", "man", iRank+5, SPAIN, -1, true, "soldier"));
	FantomMakeCoolFighter(sld, iRank+5, iScl+5, iScl+5, "blade_10", "pistol5", "bullet", iScl*3);
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	ChangeCharacterAddressGroup(sld, pchar.GenQuest.Marginpassenger.Shore, "reload", "reload1");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "Marginpassenger_Afterbattle");
}

void Marginpassenger_SouthshipInWorld(string qName)//запускаем кораблик с деревом на карте
{
    string sGroup = "Sea_SouthshipCap1";
	Group_DeleteGroup(sGroup);
	Group_FindOrCreateGroup(sGroup);
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE;
	int iScl = 3*sti(pchar.rank)+10;
	int iDays = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.GenQuest.Marginpassenger.Southcity1), GetArealByCityName(pchar.GenQuest.Marginpassenger.Southcity))+5;
	sTemp = pchar.GenQuest.Marginpassenger.ShipName1;
	sld = GetCharacter(NPC_GenerateCharacter("SouthshipCap", "citiz_41"+(rand(9)), "man", "man", iRank, SPAIN, iDays, true, "quest"));
	FantomMakeSmallSailor(sld, SHIP_BARKENTINE, sTemp, CANNON_TYPE_CANNON_LBS12, iScl+10, iScl, iScl, iScl, iScl);
	FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_13", "pistol1", "bullet", 100);
	SetCaptanModelByEncType(sld, "trade");
	sld.Ship.Mode = "trade";
	SetRandomNameToCharacter(sld);
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.AlwaysEnemy = true;
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "AdvancedBattleState");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "ShipSpeedUp");
	AddCharacterGoods(sld, sti(pchar.GenQuest.Marginpassenger.Goods), sti(pchar.GenQuest.Marginpassenger.GoodsQty));//положить в трюм древесину
	sld.mapEnc.type = "trade";
	sld.mapEnc.worldMapShip = "ranger";
	sld.mapEnc.Name = StringFromKey("MiniQuests_13", pchar.GenQuest.Marginpassenger.ShipName1);
	Group_AddCharacter(sGroup, "SouthshipCap");
	Group_SetGroupCommander(sGroup, "SouthshipCap");
	Map_CreateTrader(pchar.GenQuest.Marginpassenger.Southcity, pchar.GenQuest.Marginpassenger.Southcity1, "SouthshipCap", iDays);
	SetFunctionTimerCondition("Marginpassenger_SouthshipInWorldOver", 0, 0, iDays, false);
	pchar.quest.Marginpassenger_Sink1.win_condition.l1 = "Character_sink";
	pchar.quest.Marginpassenger_Sink1.win_condition.l1.character = "SouthshipCap";
	pchar.quest.Marginpassenger_Sink1.function = "Marginpassenger_SouthshipFail";//потопили
	pchar.quest.Marginpassenger_Abordage1.win_condition.l1 = "Character_Capture";
	pchar.quest.Marginpassenger_Abordage1.win_condition.l1.character = "SouthshipCap";
	pchar.quest.Marginpassenger_Abordage1.function = "Marginpassenger_SouthshipWin";//взяли на абордаж
}

void Marginpassenger_SouthshipInWorldOver(string qName)//упустили кораблик
{
	pchar.quest.Marginpassenger_Sink1.over = "yes"; //снять прерывание
	pchar.quest.Marginpassenger_Abordage1.over = "yes"; //снять прерывание
	AddQuestRecord("Marginpassenger", "17");
	AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName1);
	CloseQuestHeader("Marginpassenger");
	Group_DeleteGroup("Sea_SouthshipCap1");
	DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
	ChangeCharacterComplexReputation(pchar, "authority", -1);
	ChangeOfficersLoyality("bad_all", 1);
}

void Marginpassenger_SouthshipFail(string qName)//потопили в бою
{
	pchar.quest.Marginpassenger_SouthshipInWorldOver.over = "yes"; //снять прерывание
	pchar.quest.Marginpassenger_Abordage1.over = "yes"; //снять прерывание
	Group_DeleteGroup("Sea_SouthshipCap1");
	AddQuestRecord("Marginpassenger", "18");
	AddQuestUserData("Marginpassenger", "sSex", GetSexPhrase(StringFromKey("MiniQuests_3"),StringFromKey("MiniQuests_4")));
	AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName1);
	CloseQuestHeader("Marginpassenger");
	DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
	AddComplexSeaExpToScill(50, 50, 50, 0, 50, 50, 0);
}

void Marginpassenger_SouthshipWin(string qName)//абордировали
{
	DoQuestCheckDelay("sea_victory", 1.5);
	pchar.quest.Marginpassenger_SouthshipInWorldOver.over = "yes"; //снять прерывание
	pchar.quest.Marginpassenger_Sink1.over = "yes"; //снять прерывание
	Group_DeleteGroup("Sea_SouthshipCap1");
	AddQuestRecord("Marginpassenger", "19");
	AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName1);
	CloseQuestHeader("Marginpassenger");
	DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
	AddComplexSeaExpToScill(100, 100, 100, 150, 100, 100, 0);
	AddComplexSelfExpToScill(50, 50, 50, 50);
	ChangeCharacterComplexReputation(pchar, "authority", 1);
	ChangeOfficersLoyality("good_all", 1);
	ChangeCharacterNationReputation(pchar, SPAIN, -1);
}
//<-- мини-квесты тёмных личностей

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Jason -------------------------------------мини-квесты бродячих капитанов----------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MarchCap_Create(string qName)//ставим кораблик
{
	log_Testinfo("Прерывание отработало");
	int iRank = sti(pchar.GenQuest.MarchCap.rank);
	int iNation = sti(pchar.GenQuest.MarchCap.basenation);
	int iShip = sti(pchar.GenQuest.MarchCap.shiptype);
	sTemp = pchar.GenQuest.MarchCap.model;
	pchar.GenQuest.MarchCap.begin = "true";
	Group_FindOrCreateGroup("MarchGroup");
	sld = GetCharacter(NPC_GenerateCharacter("MarchCap", sTemp, "man", "man", iRank, iNation, -1, false, "quest"));
	sld.Dialog.Filename = "Quest\MarchCap_dialog.c";
	sld.DeckDialogNode = "MarchCap";
	sld.name = pchar.GenQuest.MarchCap.name;
	sld.lastname = pchar.GenQuest.MarchCap.lastname;
	SetFantomParamFromRank(sld, iRank, true);
	sld.Ship.Type = GenerateShipExt(iShip, true, sld);
	sld.ship.name = pchar.GenQuest.MarchCap.shipname;
	sld.ship.mode = "trade";
	SetBaseShipData(sld);
	SetCrewQuantityFull(sld);
	Fantom_SetCannons(sld, "war");
	Fantom_SetBalls(sld, "pirate");
	Fantom_SetGoods(sld, "war");
	SetFantomParamHunter(sld); //крутые парни
	sld.AlwaysFriend = true;
	sld.DontRansackCaptain = true; //Desperado фикс спасения на шлюпке
	Character_SetAbordageEnable(sld, false);
	Group_AddCharacter("MarchGroup", "MarchCap");
	Group_SetGroupCommander("MarchGroup", "MarchCap");
	Group_SetAddress("MarchGroup", pchar.GenQuest.MarchCap.Startisland, "quest_ships", "quest_ship_1");
}

void MarchCap_Over(string qName)//снимаем кораблик 
{
	if (CheckAttribute(pchar, "GenQuest.MarchCap.begin"))
	{
		sld = characterFromId("MarchCap");
		sld.lifeday = 0;
		LAi_CharacterDisableDialog(sld);
		sld.DontDeskTalk = true;
	}
	else pchar.quest.MarchCap_Create.over = "yes"; //снять прерывание
	DeleteAttribute(pchar, "GenQuest.MarchCap"); // diffix
}

void MarchCap1_CreateConvoy(string qName)//конвой на боевой карте
{
	log_Testinfo("Прерывание отработало");
	pchar.quest.MarchCap_Attack_Over.over = "yes"; //снять прерывание
	pchar.quest.MarchCap1_fail.over = "yes"; //снять прерывание
	Island_SetReloadEnableGlobal(pchar.GenQuest.MarchCap.Island, false);//на остров нельзя
	pchar.GenQuest.MarchCap.StartGoodsQty = GetSquadronGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods));//это столько целевого товара было в трюмах до боя, если было
	Group_DeleteGroup("MarchCap_Attack");
	Group_FindOrCreateGroup("MarchCap_Attack");
	int iNation = sti(pchar.GenQuest.MarchCap.Nation);
	int iRank = sti(PChar.rank)+5;
	int iGoods = sti(pchar.GenQuest.MarchCap.Goods);
	int iSpace;
	//сопровождение
	SelectLevelWarShipParameter();
	sld = GetCharacter(NPC_GenerateCharacter("MrCGuard", "off_"+NationShortName(iNation)+"_"+(rand(5)+1), "man", "man", iRank+3, iNation, 2, true, "quest"));
	SetFantomParamFromRank(sld, iRank+3, true);
	sld.Ship.Type = GenerateShipExt(iGlobalTemp, 1, sld);
	SetRandomNameToShip(sld);
	SetBaseShipData(sld);
	SetCrewQuantityFull(sld);
	Fantom_SetCannons(sld, "war");
	Fantom_SetBalls(sld, "pirate");
	Fantom_SetGoods(sld, "war");
	SetFantomParamHunter(sld); //крутые парни
	sld.AlwaysEnemy = true;
	sld.ship.mode = "war";
	Group_AddCharacter("MarchCap_Attack", "MrCGuard");
    for (int i = 1; i <= 2; i++)//торговцы
    {
		SelectLevelTradeShipParameter();
        sld = GetCharacter(NPC_GenerateCharacter("MrCTrade_"+i, "trader_"+(rand(15)+1), "man", "man", iRank, iNation, 2, true, "quest"));
		sld.Ship.Type = GenerateShipExt(iGlobalTemp, 1, sld);
		SetFantomParamFromRank(sld, iRank, true);
		SetRandomNameToShip(sld);
		SetBaseShipData(sld);
		SetCrewQuantityFull(sld);
		Fantom_SetCannons(sld, "war");
		SetCaptanModelByEncType(sld, "trade");
		sld.AlwaysEnemy = true;
		sld.ship.mode = "trade";
		iSpace = GetCharacterFreeSpace(sld, iGoods);
		iSpace = makeint(iSpace/2 + (iSpace/2.5));
		Fantom_SetCharacterGoods(sld, iGoods, iSpace, 1);
        Group_AddCharacter("MarchCap_Attack", "MrCTrade_"+i);
    }
    Group_SetGroupCommander("MarchCap_Attack", "MrCGuard");
	Group_SetTaskRunAway("MarchCap_Attack", PLAYER_GROUP);
	Group_SetAddress("MarchCap_Attack", pchar.GenQuest.MarchCap.Island, "Quest_Ships", "Quest_Ship_" + (3+rand(4)));
	Group_LockTask("MarchCap_Attack");
	
	pchar.quest.MarchCap1_fail1.win_condition.l1 = "NPC_Death";
	pchar.quest.MarchCap1_fail1.win_condition.l1.character = "MarchCap";
	pchar.quest.MarchCap1_fail1.function = "MarchCap1_fail";
    pchar.quest.MarchCap1_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.MarchCap1_AfterBattle.win_condition.l1.group = "MarchCap_Attack";
	pchar.quest.MarchCap1_AfterBattle.function = "MarchCap1_AfterBattle";
}

void MarchCap_Attack_Over(string qName)//время вышло
{
	pchar.quest.MarchCap1_1.over = "yes"; //снять прерывание
	pchar.quest.MarchCap1_2.win_condition.l1 = "MapEnter";
	pchar.quest.MarchCap1_2.function = "MarchCap_DeckTalk";
	pchar.GenQuest.MarchCap.late = "true";
}

void MarchCap_fail(string qName)//компаньон погиб по пути
{
	if (!CheckAttribute(pchar, "GenQuest.MarchCap.WdmEnc")) pchar.quest.MarchCap_Attack_Over.over = "yes"; //снять прерывание
	pchar.quest.MarchCap1_1.over = "yes"; //снять прерывание
	sld = characterFromId("MarchCap");	
	AddQuestRecord("MarchCap", "3");
	AddQuestUserData("MarchCap", "sName", GetFullName(sld));
	CloseQuestHeader("MarchCap");
	DeleteAttribute(pchar, "GenQuest.MarchCap");
}

void MarchCap1_fail(string qName)//компаньон погиб в бою
{
	if (CheckAttribute(pchar, "GenQuest.MarchCap.Pirate")) pchar.quest.MarchCap1_DieHard.over = "yes"; //снять прерывание
	Island_SetReloadEnableGlobal(pchar.GenQuest.MarchCap.Island, true);//на остров можно
	pchar.quest.MarchCap1_AfterBattle.over = "yes"; //снять прерывание
	sld = characterFromId("MarchCap");	
	AddQuestRecord("MarchCap", "4");
	AddQuestUserData("MarchCap", "sName", GetFullName(sld));
	CloseQuestHeader("MarchCap");
	DeleteAttribute(pchar, "GenQuest.MarchCap");
}

void MarchCap_DeckTalk(string qName)//разговор на палубе
{
	if (CheckAttribute(pchar, "GenQuest.MarchCap.DieHard"))
	{
		pchar.quest.MarchCap1_AfterBattle.over = "yes"; //снять прерывание
		Island_SetReloadEnableGlobal(pchar.GenQuest.MarchCap.Island, true);//на остров можно
		Group_DeleteGroup("MarchCap_Attack");
	}
	pchar.quest.MarchCap1_3.over = "yes"; //снять прерывание
	pchar.quest.MarchCap1_4.over = "yes"; //снять прерывание
	aref arOldMapPos;
	makearef(arOldMapPos, worldMap.old);
	WdmPrepareMapForAbordage(arOldMapPos);
	MakeCloneShipDeck(pchar, true);//клон палубы
	LAi_LocationFightDisable(&Locations[FindLocation("Ship_deck")], true);
	DoReloadFromWorldMapToLocation("Ship_deck", "goto", "goto1");
	LAi_LockFightMode(pchar, true);
	sld = characterFromId("MarchCap");
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, "Ship_deck", "goto", "goto2");
	if (CheckAttribute(pchar, "GenQuest.MarchCap.late")) sld.dialog.currentnode = "MarchCap_TimeOver";
	else
	{
		if (CheckAttribute(pchar, "GenQuest.MarchCap.DieHard")) sld.dialog.currentnode = "MarchCap_DieHard";
		else
		{
			if (CheckAttribute(pchar, "GenQuest.MarchCap.Pirate")) sld.dialog.currentnode = "MarchCap_AfterBattleGold";
	else sld.dialog.currentnode = "MarchCap_AfterBattle";
		}
	}
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	pchar.quest.Munity = "";//чтобы не выскочил без разговора
	pchar.GenQuest.MarchCap.Deck = "true";
}

void MarchCap_LandTalk(string qName)//разговор на суше
{
	pchar.quest.MarchCap1_2.over = "yes"; //снять прерывание
	pchar.quest.MarchCap1_3.over = "yes"; //снять прерывание
	pchar.quest.MarchCap1_4.over = "yes"; //снять прерывание
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
	chrDisableReloadToLocation = true;//закрыть локацию
	sld = characterFromId("MarchCap");
	LAi_SetActorType(sld);
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	if (CheckAttribute(pchar, "GenQuest.MarchCap.Pirate")) sld.dialog.currentnode = "MarchCap_AfterBattleGold";
	else sld.dialog.currentnode = "MarchCap_AfterBattle";
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void MarchCap1_AfterBattle(string qName)//после боя или истечения времени существования конвоя
{
	pchar.quest.MarchCap1_fail1.over = "yes"; //снять прерывание
	if (CheckAttribute(pchar, "GenQuest.MarchCap.WdmEnc")) Group_DeleteGroup("Sea_WorldMarchCap1");
	else
	{
		if (CheckAttribute(pchar, "GenQuest.MarchCap.Pirate"))
		{
			DeleteAttribute(pchar, "GenQuest.MarchCap.DieHard");
			pchar.quest.MarchCap1_DieHard.over = "yes"; //снять прерывание
		}
		Island_SetReloadEnableGlobal(pchar.GenQuest.MarchCap.Island, true);//на остров можно
		Group_DeleteGroup("MarchCap_Attack");
	}
	pchar.quest.MarchCap1_2.win_condition.l1 = "MapEnter";
	pchar.quest.MarchCap1_2.function = "MarchCap_DeckTalk";//раздел добычи в море
	pchar.quest.MarchCap1_3.win_condition.l1 = "Location_Type";
	pchar.quest.MarchCap1_3.win_condition.l1.location_type = "seashore";
	pchar.quest.MarchCap1_3.function = "MarchCap_LandTalk";//раздел добычи на суше
	pchar.quest.MarchCap1_4.win_condition.l1 = "Location_Type";
	pchar.quest.MarchCap1_4.win_condition.l1.location_type = "town";
	pchar.quest.MarchCap1_4.function = "MarchCap_LandTalk";//раздел добычи на суше
	pchar.quest.MarchCap1_fail2.win_condition.l1 = "NPC_Death";
	pchar.quest.MarchCap1_fail2.win_condition.l1.character = "MarchCap";
	pchar.quest.MarchCap1_fail2.function = "MarchCap1_killed";
}

void MarchCap1_killed(string qName)//сам потопил компаньона
{
	pchar.quest.MarchCap1_2.over = "yes"; //снять прерывание
	pchar.quest.MarchCap1_3.over = "yes"; //снять прерывание
	pchar.quest.MarchCap1_4.over = "yes"; //снять прерывание
	AddQuestRecord("MarchCap", "9");
	AddQuestUserData("MarchCap", "sSex", GetSexPhrase(StringFromKey("MiniQuests_3"),StringFromKey("MiniQuests_4")));
	AddQuestUserData("MarchCap", "sSex1", GetSexPhrase(StringFromKey("MiniQuests_1"),StringFromKey("MiniQuests_2")));
	CloseQuestHeader("MarchCap");
	DeleteAttribute(pchar, "GenQuest.MarchCap");//почистим кучу лишних атрибутов
	pchar.GenQuest.MarchCap = "true"; //больше квеста не будет
}

void MarchCap2_CreateConvoy(string qName)//конвой на карте
{
	string sCapId = "WorldMarchCap";
    string sGroup = "Sea_" + sCapId + "1";
	Group_DeleteGroup(sGroup);
	Group_FindOrCreateGroup(sGroup);
	int iNation = sti(pchar.GenQuest.MarchCap.Nation);
	int iRank = sti(PChar.rank)+5;
	int iGoods = sti(pchar.GenQuest.MarchCap.Goods);
	int iDays = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.GenQuest.MarchCap.Finishcity), GetArealByCityName(pchar.GenQuest.MarchCap.Startcity))+5;
	int iSpace;
	for (int i = 1; i <= 3; i++)
    {
		sld = GetCharacter(NPC_GenerateCharacter(sCapId + i, "citiz_41", "man", "man", iRank, iNation, iDays, true, "quest"));
		SetRandomNameToCharacter(sld);
		SetRandomNameToShip(sld);
		SetFantomParamFromRank(sld, iRank, true);
		if (i == 1)
		{
			SelectLevelWarShipParameter();
			sld.Ship.Type = GenerateShipExt(iGlobalTemp, 1, sld);
			SetCaptanModelByEncType(sld, "war");
			sld.ship.mode = "war";
			SetFantomParamHunter(sld); //крутые парни
		}
		else
		{
			SelectLevelTradeShipParameter();
			sld.Ship.Type = GenerateShipExt(iGlobalTemp, 1, sld);
			SetCaptanModelByEncType(sld, "trade");
			sld.ship.mode = "trade";
		}
		SetBaseShipData(sld);
		SetCrewQuantityFull(sld);
		Fantom_SetCannons(sld, "war");
		sld.AlwaysEnemy = true;
		sld.AnalizeShips = true;
		if (i == 2 || i == 3)
		{
			iSpace = GetCharacterFreeSpace(sld, iGoods);
			iSpace = makeint(iSpace/2 + (iSpace/2.5));
			Fantom_SetCharacterGoods(sld, iGoods, iSpace, 1);
		}
		sld.mapEnc.type = "war";
		sld.mapEnc.worldMapShip = "quest_ship";
        sld.mapEnc.Name = StringFromKey("MiniQuests_14");
        Group_AddCharacter(sGroup, sCapId + i);
	}
	Group_SetGroupCommander(sGroup, sCapId+ "1");
    Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
    Group_LockTask(sGroup);
	Map_CreateTrader(pchar.GenQuest.MarchCap.Startcity, pchar.GenQuest.MarchCap.Finishcity, sCapId + "1", iDays);//запуск энкаунтера
	SetFunctionTimerCondition("MarchCap2_Attack_Over", 0, 0, iDays+1, false); //таймер на нахождение
	pchar.quest.MarchCap1_fail.over = "yes"; //снять прерывание
	pchar.quest.MarchCap2_fail.win_condition.l1 = "NPC_Death";
	pchar.quest.MarchCap2_fail.win_condition.l1.character = "MarchCap";
	pchar.quest.MarchCap2_fail.function = "MarchCap2_fail";
}

void MarchCap2_fail(string qName)//компаньон погиб по пути при движении энкаунтера
{
	sld = characterFromId("MarchCap");	
	AddQuestRecord("MarchCap", "3-1");
	AddQuestUserData("КВЕСТ", "sSex1", GetSexPhrase(StringFromKey("MiniQuests_15"),StringFromKey("MiniQuests_16")));
	AddQuestUserData("MarchCap", "sName", GetFullName(sld));
	CloseQuestHeader("MarchCap");
	DeleteAttribute(pchar, "GenQuest.MarchCap");
}

void MarchCap2_Attack_Over(string qName)//истекло время на нахождение
{
	pchar.quest.MarchCap2_fail.over = "yes"; //снять прерывание
	pchar.quest.MarchCap1_2.win_condition.l1 = "MapEnter";
	pchar.quest.MarchCap1_2.function = "MarchCap_DeckTalk";
	pchar.GenQuest.MarchCap.late = "true";
}

void MarchCap2_CheckBattle(string qName)//признак вступления в бой
{
	pchar.GenQuest.MarchCap.Battlestart = "true";//атрибут начатого боя
	pchar.GenQuest.MarchCap.StartGoodsQty = GetSquadronGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods));//это столько целевого товара было в трюмах до боя, если было
	pchar.quest.MarchCap2_fail.over = "yes"; //снять прерывание
	pchar.quest.MarchCap2_Attack_Over.over = "yes"; //снять таймер
	sld = characterFromId("WorldMarchCap1");
	sld.lifeday = 0;
	log_Testinfo("Релиз энкаунтера по выходу на карту!");
	pchar.quest.MarchCap1_fail1.win_condition.l1 = "NPC_Death";
	pchar.quest.MarchCap1_fail1.win_condition.l1.character = "MarchCap";
	pchar.quest.MarchCap1_fail1.function = "MarchCap1_fail";
    pchar.quest.MarchCap1_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.MarchCap1_AfterBattle.win_condition.l1.group = "Sea_WorldMarchCap1";
	pchar.quest.MarchCap1_AfterBattle.function = "MarchCap1_AfterBattle";
}

void MarchCap3_CreatePirate(string qName)//пират с золотишком
{
	pchar.GenQuest.MarchCap.StartGoodsQty = GetSquadronGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods));//это столько целевого товара было в трюмах до боя, если было
	pchar.quest.MarchCap_Attack_Over.over = "yes"; //снять таймер
	pchar.quest.MarchCap1_fail.over = "yes"; //снять прерывание
	Island_SetReloadEnableGlobal(pchar.GenQuest.MarchCap.Island, false);//закрыть остров
	pchar.GenQuest.MarchCap.DieHard = "true"; //атрибут бегства
	Group_DeleteGroup("MarchCap_Attack");
	Group_FindOrCreateGroup("MarchCap_Attack");
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE;
	int iScl = 3*sti(pchar.rank)+10;
	int iShipType = sti(pchar.GenQuest.MarchCap.ShipType);
	int iCannon = sti(pchar.GenQuest.MarchCap.Cannon);
	sld = GetCharacter(NPC_GenerateCharacter("MarchPirate", "mercen_"+(rand(27)+1), "man", "man", iRank, PIRATE, 1, true, "quest"));
	FantomMakeCoolSailor(sld, iShipType, "", iCannon, iScl+25, iScl, iScl);
	FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_10", "pistol1", "bullet", iScl*2);
	sld.name = GetName(NAMETYPE_ORIG, pchar.GenQuest.MarchCap.PirateName, NAME_NOM));
	sld.lastname = "";
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	switch (hrand(5))
	{
		case 0: UpgradeShipParameter(sld, "TurnRate"); break;
		case 1: UpgradeShipParameter(sld, "Capacity"); break;
		case 2: UpgradeShipParameter(sld, "MaxCrew"); break;
		case 3: UpgradeShipParameter(sld, "HP"); break;
		case 4: UpgradeShipParameter(sld, "SpeedRate"); break;
		case 5: UpgradeShipParameter(sld, "WindAgainstSpeed"); break;
	}
	Group_AddCharacter("MarchCap_Attack", "MarchPirate");
	sld.AlwaysEnemy = true;
	sld.AnalizeShips = true;
	AddCharacterGoods(sld, sti(pchar.GenQuest.MarchCap.Goods), sti(pchar.GenQuest.MarchCap.GoodsQty));//положить золото-серебро
	Group_SetGroupCommander("MarchCap_Attack", "MarchPirate");
	Group_SetTaskAttack("MarchCap_Attack", PLAYER_GROUP);
	Group_SetAddress("MarchCap_Attack", pchar.GenQuest.MarchCap.Island, "Quest_Ships", "Quest_Ship_"+(3+rand(4)));
	Group_LockTask("MarchCap_Attack");
	
	pchar.quest.MarchCap1_fail1.win_condition.l1 = "NPC_Death";
	pchar.quest.MarchCap1_fail1.win_condition.l1.character = "MarchCap";
	pchar.quest.MarchCap1_fail1.function = "MarchCap1_fail";
	pchar.quest.MarchCap1_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.MarchCap1_AfterBattle.win_condition.l1.group = "MarchCap_Attack";
	pchar.quest.MarchCap1_AfterBattle.function = "MarchCap1_AfterBattle";
	pchar.quest.MarchCap1_DieHard.win_condition.l1 = "MapEnter";
	pchar.quest.MarchCap1_DieHard.function = "MarchCap_DeckTalk";
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Jason ---------------------------------- новые генераторы губернаторов ----------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//--> Контркурьер
void TakePostcureer_CreateShip(string qName)
{
	Log_Info(StringFromKey("MiniQuests_17"));
	DoQuestCheckDelay("see_sails", 1.3);
	pchar.quest.AllMayorsQuests_Late.over = "yes"; //снимаем общий таймер
	Island_SetReloadEnableGlobal(pchar.GenQuest.TakePostcureer.Island, false);//на остров нельзя
	pchar.Cheats.SeaTeleport = true;
	int iNation = sti(pchar.GenQuest.TakePostcureer.Nation);
	int iRank = sti(pchar.rank)+makeint(MOD_SKILL_ENEMY_RATE/2)+2;
	int iScl = 2*sti(pchar.rank)+10;
	int iShipType = sti(pchar.GenQuest.TakePostcureer.ShipType);
	int iCannon = sti(pchar.GenQuest.TakePostcureer.Cannon);
	string sShipName = pchar.GenQuest.TakePostcureer.ShipName;
	Group_FindOrCreateGroup("ContraCureer");
	Group_SetType("ContraCureer", "war");//тип группы
	sld = GetCharacter(NPC_GenerateCharacter("ContraCureerCap", "off_"+NationShortName(iNation)+"_"+(rand(5)+1), "man", "man", iRank, iNation, -1, true, "quest"));
	FantomMakeSmallSailor(sld, iShipType, sShipName, iCannon, iScl, iScl, iScl, iScl, iScl);
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.AlwaysEnemy = true;
	sld.Ship.Mode = "war";
	Group_AddCharacter("ContraCureer", "ContraCureerCap");
	Group_SetGroupCommander("ContraCureer", "ContraCureerCap");
	Group_SetTaskAttack("ContraCureer", PLAYER_GROUP);
	Group_SetAddress("ContraCureer", pchar.GenQuest.TakePostcureer.Island, "Quest_Ships", "Quest_Ship_"+(3+rand(4)));
	Group_LockTask("ContraCureer");
	
	pchar.quest.ContraCureer_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.ContraCureer_AfterBattle.win_condition.l1.group = "ContraCureer";
	pchar.quest.ContraCureer_AfterBattle.function = "ContraCureer_AfterBattle";
	pchar.quest.ContraCureer_DieHard.win_condition.l1 = "MapEnter";
	pchar.quest.ContraCureer_DieHard.function = "ContraCureer_DieHard";
}

void ContraCureer_AfterBattle(string qName)//победили
{
	DoQuestCheckDelay("sea_victory", 1.5);
	pchar.quest.ContraCureer_DieHard.over = "yes";
	Group_DeleteGroup("ContraCureer");
	Island_SetReloadEnableGlobal(pchar.GenQuest.TakePostcureer.Island, true);
	DeleteAttribute(pchar, "Cheats.SeaTeleport");
	if (CheckCharacterItem(pchar, "ContraPostLetters"))
	{
		AddComplexSeaExpToScill(150, 100, 100, 100, 100, 100, 0);
		ChangeOfficersLoyality("good_all", 1);
		AddQuestRecord("MayorsQuestsList", "4");
		pchar.GenQuest.TakePostcureer = "Execute"; //флаг выполнил успешно
	}
	else
	{
		ChangeOfficersLoyality("bad_all", 1);
		AddQuestRecord("MayorsQuestsList", "4-1");
		pchar.GenQuest.TakePostcureer = "Found"; //флаг провалил
	}
}

void ContraCureer_DieHard(string qName)//сбежали
{
	pchar.quest.ContraCureer_AfterBattle.over = "yes";
	Group_DeleteGroup("ContraCureer");
	Island_SetReloadEnableGlobal(pchar.GenQuest.TakePostcureer.Island, true);
	AddQuestRecord("MayorsQuestsList", "5");
	pchar.GenQuest.TakePostcureer = "Found"; //флаг провалил
	DeleteAttribute(pchar, "Cheats.SeaTeleport");
}
//<-- Контркурьер

//--> Контрфрахт - арсенал
void TakeArsenalship_CreateShip(string qName)
{
	Log_Info(StringFromKey("MiniQuests_18"));
	DoQuestCheckDelay("see_sails", 1.3);
	pchar.quest.AllMayorsQuests_Late.over = "yes"; //снимаем общий таймер
	Island_SetReloadEnableGlobal(pchar.GenQuest.TakeArsenalship.Island, false);//на остров нельзя
	pchar.Cheats.SeaTeleport = true;
	int iNation = sti(pchar.GenQuest.TakeArsenalship.Nation);
	int iRank = sti(pchar.rank)+makeint(MOD_SKILL_ENEMY_RATE/2)+2;
	int iScl = 2*sti(pchar.rank)+10;
	int iShipType = sti(pchar.GenQuest.TakeArsenalship.ShipType);
	int iShipTypeA = sti(pchar.GenQuest.TakeArsenalship.ShipTypeA);
	int iCannon = sti(pchar.GenQuest.TakeArsenalship.Cannon);
	int iCannonA = sti(pchar.GenQuest.TakeArsenalship.CannonA);
	string sShipName = pchar.GenQuest.TakeArsenalship.ShipName;
	Group_FindOrCreateGroup("ContraCureer");
	Group_SetType("ContraCureer", "war");//тип группы
	sld = GetCharacter(NPC_GenerateCharacter("ContraCureerCap", "off_"+NationShortName(iNation)+"_"+(rand(5)+1), "man", "man", iRank, iNation, -1, true, "quest"));
	FantomMakeSmallSailor(sld, iShipTypeA, "", iCannonA, iScl, iScl, iScl, iScl, iScl); // Addon 2016-1 Jason пиратская линейка
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.Ship.Mode = "war";
	Group_AddCharacter("ContraCureer", "ContraCureerCap");
	sld = GetCharacter(NPC_GenerateCharacter("ContraArsCap", "off_"+NationShortName(iNation)+"_"+(rand(5)+1), "man", "man", iRank, iNation, -1, true, "quest"));
	FantomMakeSmallSailor(sld, iShipType, sShipName, iCannon, iScl, iScl, iScl, iScl, iScl);
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.AlwaysEnemy = true;
	sld.Ship.Mode = "war";
	if (MOD_SKILL_ENEMY_RATE > 4) SetCharacterPerk(sld, "MusketsShoot");
	int iGoods = GOOD_BALLS + hrand(makeint(GOOD_BOMBS - GOOD_BALLS));
	int iSpace = GetCharacterFreeSpace(sld, iGoods);
	iSpace = makeint(iSpace/4);
	AddCharacterGoods(sld, iGoods, iSpace);
	AddCharacterGoods(sld, GOOD_POWDER, iSpace);
	AddCharacterGoods(sld, GOOD_WEAPON, 1000+rand(1000));
	AddCharacterGoods(sld, GOOD_BALLS, 500);
	AddCharacterGoods(sld, GOOD_GRAPES, 1000);
	AddCharacterGoods(sld, GOOD_KNIPPELS, 500);
	AddCharacterGoods(sld, GOOD_BOMBS, 500);
	Group_AddCharacter("ContraCureer", "ContraArsCap");
	Group_SetGroupCommander("ContraCureer", "ContraCureerCap");
	Group_SetTaskAttack("ContraCureer", PLAYER_GROUP);
	Group_SetAddress("ContraCureer", pchar.GenQuest.TakeArsenalship.Island, "Quest_Ships", "Quest_Ship_"+(3+rand(4)));
	Group_LockTask("ContraCureer");
	
	pchar.quest.ContraArs_AfterBattle.win_condition.l1 = "NPC_Death";
	pchar.quest.ContraArs_AfterBattle.win_condition.l1.character = "ContraArsCap";
	pchar.quest.ContraArs_AfterBattle.function = "ContraArs_AfterBattle";
	pchar.quest.ContraArs_DieHard.win_condition.l1 = "MapEnter";
	pchar.quest.ContraArs_DieHard.function = "ContraArs_DieHard";
}

void ContraArs_AfterBattle(string qName)//победили
{
	DoQuestCheckDelay("sea_victory", 1.5);
	pchar.quest.ContraArs_DieHard.over = "yes";
	//Group_DeleteGroup("ContraCureer");
	Island_SetReloadEnableGlobal(pchar.GenQuest.TakeArsenalship.Island, true);
	AddComplexSeaExpToScill(150, 100, 100, 100, 100, 100, 0);
	ChangeOfficersLoyality("good_all", 1);
	AddQuestRecord("MayorsQuestsList", "8-1");
	pchar.GenQuest.TakeArsenalship = "Execute"; //флаг выполнил успешно
	DeleteAttribute(pchar, "Cheats.SeaTeleport");
}

void ContraArs_DieHard(string qName)//сбежали
{
	pchar.quest.ContraArs_AfterBattle.over = "yes";
	Group_DeleteGroup("ContraCureer");
	Island_SetReloadEnableGlobal(pchar.GenQuest.TakeArsenalship.Island, true);
	ChangeOfficersLoyality("bad_all", 1);
	AddQuestRecord("MayorsQuestsList", "5");
	pchar.GenQuest.TakeArsenalship = "Found"; //флаг провалил
	DeleteAttribute(pchar, "Cheats.SeaTeleport");
}
//<-- Контрфрахт - арсенал

//--> ОЗГ - пират
void TakePirateship_CreateShip(string qName)
{
	Log_Info(StringFromKey("MiniQuests_19"));
	DoQuestCheckDelay("see_sails", 1.3);
	pchar.quest.AllMayorsQuests_Late.over = "yes"; //снимаем общий таймер
	Island_SetReloadEnableGlobal(pchar.GenQuest.TakePirateship.Island, false);//на остров нельзя
	pchar.Cheats.SeaTeleport = true;
	int iRank = sti(pchar.rank)+makeint(MOD_SKILL_ENEMY_RATE/2)+5;
	int iScl = 2*sti(pchar.rank)+15;
	int iShipType = sti(pchar.GenQuest.TakePirateship.ShipType);
	int iCannon = sti(pchar.GenQuest.TakePirateship.Cannon);
	string sShipName = pchar.GenQuest.TakePirateship.ShipName;
	Group_FindOrCreateGroup("ContraCureer");
	Group_SetType("ContraCureer", "pirate");//тип группы
	sld = GetCharacter(NPC_GenerateCharacter("ContraCureerCap", "citiz_"+(rand(9)+51), "man", "man", iRank, PIRATE, -1, true, "quest"));
	sld.name = pchar.GenQuest.TakePirateship.Name;
	sld.lastname = "";
	FantomMakeSmallSailor(sld, iShipType, sShipName, iCannon, iScl, iScl, iScl, iScl, iScl);
	FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_05", "pistol1", "bullet", 50);
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.WatchFort = true;
	sld.AlwaysEnemy = true;
	sld.Ship.Mode = "pirate";
	SetCharacterPerk(sld, "MusketsShoot");
	int iGoods = GOOD_CHOCOLATE + hrand(makeint(GOOD_COTTON - GOOD_CHOCOLATE));
	int iSpace = GetCharacterFreeSpace(sld, iGoods);
	iSpace = makeint(iSpace/2);
	AddCharacterGoods(sld, iGoods, iSpace);
	Group_AddCharacter("ContraCureer", "ContraCureerCap");
	Group_SetGroupCommander("ContraCureer", "ContraCureerCap");
	Group_SetTaskAttack("ContraCureer", PLAYER_GROUP);
	Group_SetAddress("ContraCureer", pchar.GenQuest.TakePirateship.Island, "Quest_Ships", "Quest_Ship_"+(3+rand(4)));
	Group_LockTask("ContraCureer");
	
	pchar.quest.ContraCureer_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.ContraCureer_AfterBattle.win_condition.l1.group = "ContraCureer";
	pchar.quest.ContraCureer_AfterBattle.function = "ContraPirate_AfterBattle";
	pchar.quest.ContraCureer_DieHard.win_condition.l1 = "MapEnter";
	pchar.quest.ContraCureer_DieHard.function = "ContraPirate_DieHard";
}

void ContraPirate_AfterBattle(string qName)//победили
{
	DoQuestCheckDelay("sea_victory", 1.5);
	pchar.quest.ContraCureer_DieHard.over = "yes";
	Group_DeleteGroup("ContraCureer");
	Island_SetReloadEnableGlobal(pchar.GenQuest.TakePirateship.Island, true);
	AddComplexSeaExpToScill(200, 150, 150, 150, 150, 150, 0);
	ChangeOfficersLoyality("good_all", 1);
	AddQuestRecord("MayorsQuestsList", "9-1");
	pchar.GenQuest.TakePirateship = "Execute"; //флаг выполнил успешно
	DeleteAttribute(pchar, "Cheats.SeaTeleport");
}

void ContraPirate_DieHard(string qName)//сбежали
{
	pchar.quest.ContraCureer_AfterBattle.over = "yes";
	Group_DeleteGroup("ContraCureer");
	Island_SetReloadEnableGlobal(pchar.GenQuest.TakePirateship.Island, true);
	ChangeOfficersLoyality("bad_all", 1);
	AddQuestRecord("MayorsQuestsList", "5");
	pchar.GenQuest.TakePirateship = "Found"; //флаг провалил
	DeleteAttribute(pchar, "Cheats.SeaTeleport");
}
//<-- ОЗГ - пират

//--> ОЗГ - пассажир
void TakePassenger_CreateShip(string qName)
{
	int iNation = sti(pchar.GenQuest.TakePassenger.Nation);
	int iRank = sti(pchar.rank)+makeint(MOD_SKILL_ENEMY_RATE/2)+4;
	int iScl = 2*sti(pchar.rank)+10;
	int iShipType = sti(pchar.GenQuest.TakePassenger.ShipType);
	int iCannon = sti(pchar.GenQuest.TakePassenger.Cannon);
	int iDays = sti(pchar.GenQuest.TakePassenger.Terms2);
	string sShipName = pchar.GenQuest.TakePassenger.ShipName;
	string sCapId = "ContraPassCap";
    string sGroup = "Sea_" + sCapId + "1";
	Group_DeleteGroup(sGroup);
	Group_FindOrCreateGroup(sGroup);
	sld = GetCharacter(NPC_GenerateCharacter(sCapId, "off_"+NationShortName(iNation)+"_"+(rand(5)+1), "man", "man", iRank, iNation, iDays, true, "quest"));
	FantomMakeSmallSailor(sld, iShipType, sShipName, iCannon, iScl, iScl, iScl, iScl, iScl);
	FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_06", "pistol1", "bullet", 50);
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	sld.Ship.Mode = "war";	
	sld.AlwaysEnemy = true;
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	int iGoods = GOOD_COFFEE + hrand(sti(GOOD_PAPRIKA - GOOD_COFFEE));
	int iSpace = GetCharacterFreeSpace(sld, iGoods);
	iSpace = makeint(iSpace/4);
	AddCharacterGoods(sld, iGoods, iSpace);
	sld.mapEnc.type = "trade";
	sld.mapEnc.worldMapShip = "quest_ship";
    sld.mapEnc.Name = "'" + sShipName + " '";
    Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
    Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
    Group_LockTask(sGroup);
	Map_CreateTrader(pchar.GenQuest.TakePassenger.City, pchar.GenQuest.TakePassenger.CityA, sld.id, iDays);//запуск энкаунтера
	pchar.quest.ContraCureer_Abordage.win_condition.l1 = "Character_Capture";
	pchar.quest.ContraCureer_Abordage.win_condition.l1.character = "ContraPassCap";
	pchar.quest.ContraCureer_Abordage.function = "ContraPass_Abordage";//взяли на абордаж
	pchar.quest.ContraCureer_Sink.win_condition.l1 = "Character_sink";
	pchar.quest.ContraCureer_Sink.win_condition.l1.character = "ContraPassCap";
	pchar.quest.ContraCureer_Sink.function = "ContraPass_Sink";//потопили
}

void ContraPass_Abordage(string qName)//победили
{
	pchar.quest.AllMayorsQuests_Late.over = "yes"; //снимаем общий таймер
	pchar.quest.ContraCureer_Sink.over = "yes";
	Group_DeleteGroup("Sea_ContraPassCap1");
	AddComplexSeaExpToScill(150, 100, 100, 100, 100, 100, 0);
	ChangeOfficersLoyality("good_all", 1);
	AddQuestRecord("MayorsQuestsList", "10-1");
	pchar.GenQuest.TakePassenger = "Execute"; //флаг выполнил успешно
}

void ContraPass_Sink(string qName)//провалили
{
	pchar.quest.AllMayorsQuests_Late.over = "yes"; //снимаем общий таймер
	pchar.quest.ContraCureer_Abordage.over = "yes";
	Group_DeleteGroup("Sea_ContraPassCap1");
	ChangeOfficersLoyality("bad_all", 1);
	AddQuestRecord("MayorsQuestsList", "10-2");
	pchar.GenQuest.TakePassenger = "Found"; //флаг провалил
}
//<-- ОЗГ - пассажир

//--> Таможенный патруль
void CustomPatrol_CreateShip(string qName)
{
	int iNation = sti(pchar.GenQuest.CustomPatrol.Nation);
	int iRank = sti(pchar.rank)+makeint(MOD_SKILL_ENEMY_RATE/2)+2;
	int iScl = 2*sti(pchar.rank)+10;
	int iShipType = sti(pchar.GenQuest.CustomPatrol.ShipType);
	int iShipTypeA = sti(pchar.GenQuest.CustomPatrol.ShipTypeA);
	int iCannon = sti(pchar.GenQuest.CustomPatrol.Cannon);
	int lcr = sti(pchar.GenQuest.CustomPatrol.Loginlocator);
	int iDay = 1;
	if (makeint(environment.time) > 20.0) iDay = 2;
	Group_FindOrCreateGroup("ContraCureer");
	Group_SetType("ContraCureer", "pirate");//тип группы
	sld = GetCharacter(NPC_GenerateCharacter("ContraCureerCap", "citiz_"+(rand(9)+51), "man", "man", iRank, iNation, iDay, true, "quest"));//кэп-сдатчик
	FantomMakeSmallSailor(sld, iShipType, "", iCannon, iScl, iScl, iScl, iScl, iScl);
	FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_05", "pistol1", "bullet", 50);
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.Ship.Mode = "pirate";
	sld.WatchFort = true;
	sld.Coastal_Captain = true;
	if (hrand(1) == 0) AddCharacterGoods(sld, GOOD_SLAVES, 250+(hrand(100, "1")));
	Group_AddCharacter("ContraCureer", "ContraCureerCap");
	sld = GetCharacter(NPC_GenerateCharacter("ContraContraCap", "citiz_"+(rand(9)+41), "man", "man", iRank, iNation, iDay, true, "quest"));//конрик-приемщик
	FantomMakeSmallSailor(sld, iShipType, "", iCannon, iScl, iScl, iScl, iScl, iScl);
	FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_06", "pistol1", "bullet", 50);
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.Ship.Mode = "pirate";
	sld.WatchFort = true;
	sld.Coastal_Captain = true;
	if (hrand(1) == 1) AddCharacterGoods(sld, GOOD_SLAVES, 250+(hrand(100, "1")));
	Group_AddCharacter("ContraCureer", "ContraContraCap");
	Group_SetGroupCommander("ContraCureer", "ContraCureerCap");
	Group_SetAddress("ContraCureer", pchar.GenQuest.CustomPatrol.Island, "Quest_Ships", "Quest_Ship_"+lcr);
	
	//взяли на абордаж
	pchar.quest.ContraCureer_Capture.win_condition.l1 = "Character_Capture";
	pchar.quest.ContraCureer_Capture.win_condition.l1.character = "ContraCureerCap";
	pchar.quest.ContraCureer_Capture.function = "CustomPatrol_AfterBattle";
	//потопили
	pchar.quest.ContraCureer_Sink.win_condition.l1 = "Character_sink";
	pchar.quest.ContraCureer_Sink.win_condition.l1.character = "ContraCureerCap";
	pchar.quest.ContraCureer_Sink.function = "CustomPatrol_AfterBattle";
	// сбежали
	pchar.quest.ContraCureer_DieHard.win_condition.l1 = "MapEnter";
	pchar.quest.ContraCureer_DieHard.function = "CustomPatrol_DieHard";
}

void CustomPatrol_AfterBattle(string qName)//победили
{
	pchar.quest.AllMayorsQuests_Late.over = "yes"; //снимаем общий таймер
	pchar.quest.ContraCureer_DieHard.over = "yes";
	pchar.quest.ContraCureer_Capture.over = "yes";
	pchar.quest.ContraCureer_Sink.over = "yes";
	//Group_DeleteGroup("ContraCureer");
	AddComplexSeaExpToScill(150, 100, 100, 100, 100, 100, 0);
	AddCharacterExpToSkill(pchar, "Sneak", 200);//скрытность
	ChangeOfficersLoyality("good_all", 1);
	AddQuestRecord("MayorsQuestsList", "11-1");
	pchar.GenQuest.CustomPatrol = "Execute"; //флаг выполнил успешно
	ChangeContrabandRelation(pchar, -20);
}

void CustomPatrol_DieHard(string qName)//сбежали
{
	pchar.quest.AllMayorsQuests_Late.over = "yes"; //снимаем общий таймер
	pchar.quest.ContraCureer_AfterBattle.over = "yes";
	Group_DeleteGroup("ContraCureer");
	ChangeOfficersLoyality("bad_all", 1);
	AddQuestRecord("MayorsQuestsList", "5");
	pchar.GenQuest.CustomPatrol = "Found"; //флаг провалил
}
//<-- Таможенный патруль

//--> Дезертир
void FindFugitive_Over(string qName)//не пошёл сдавать пленника
{
	pchar.quest.FindFugitive1.over = "yes"; //снять прерывание
	sld = &Characters[sti(Pchar.GenQuest.FindFugitive.PrisonerIDX)];
	ReleasePrisoner(sld); //освободили пленника
	sld.lifeday = 0;
	log_info(StringFromKey("MiniQuests_20", pchar.GenQuest.FindFugitive.Name));
	PlaySound("interface\notebook.wav");
	pchar.GenQuest.FindFugitive = "Late"; //флаг опоздал
}

void FindFugitive_inResidence(string qName)//в резиденции
{
	chrDisableReloadToLocation = true;//закрыть локацию
	sld = &Characters[sti(Pchar.GenQuest.FindFugitive.PrisonerIDX)];
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_SetActorType(sld);
	LAi_ActorFollow(sld, pchar, "", -1);
}
//<-- Дезертир

//=================================================================
//======================кейсы из quests_reaction===================
//=================================================================
bool MiniQuests_QuestComplete(string sQuestName, string qname)
{
	ref sld;
	aref arOldMapPos, arAll, arPass;
	int     iTemp, i, n, iRank, Rank;
    float locx, locy, locz;
	string  attrName, sTemp; // любые строки для вычислений
	bool   bOk;
	
	bool condition = true;
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Jason----------------------------------------------Бесчестный конкурент-----------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (sQuestName == "Shadow_inRoom") {
		chrDisableReloadToLocation = true;//закрыть локацию
		sld = characterFromID("ShadowAgent_1");   
		sld.LSC_clan = true; // 110912 fix
		LAi_SetImmortal(sld, false);
		iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+5; // 240912
		sld = GetCharacter(NPC_GenerateCharacter("ShadowAgent_2", "citiz_"+(rand(9)+41), "man", "man", iRank, PIRATE, 2, true, "citizen"));
		SetFantomParamFromRank(sld, iRank, true);
		sld.LSC_clan = true; // 110912 fix
		GiveItem2Character(sld, "blade_05");
		EquipCharacterbyItem(sld, "blade_05");
		LAi_SetStayType(sld);
		ChangeCharacterAddressGroup(sld, "CommonFlamHouse", "goto", "goto3");
		sld = GetCharacter(NPC_GenerateCharacter("ShadowTrader", "trader_11", "man", "man", 10, PIRATE, 2, true, "quest"));
		SetFantomParamFromRank(sld, 10, true);
		RemoveAllCharacterItems(sld, true);
		GiveItem2Character(sld, "blade_03");
		EquipCharacterbyItem(sld, "blade_03"); // 240912
		sld.LSC_clan = true; // 110912 fix
		LAi_SetActorType(sld);
		sld.dialog.Filename = "Quest\LineMiniQuests\ShadowTrader.c";
		sld.dialog.currentnode = "ShadowTrader";	
		sld.greeting = "store_1";
		LAi_SetImmortal(sld, true);
		sld.SaveItemsForDead = true;
		sld.money = 20550;
		TakeNItems(sld, "jewelry1", rand(5));
		TakeNItems(sld, "jewelry2", rand(10));
		TakeNItems(sld, "jewelry5", rand(20));
		ChangeCharacterAddressGroup(sld, "CommonFlamHouse", "goto", "goto1");
		DoQuestReloadToLocation("CommonFlamHouse", "goto", "goto4", "");
		LAi_SetActorType(pchar);
		LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
		LAi_ActorTurnToCharacter(sld, pchar);
		SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
	}
	
	else if (sQuestName == "ShadowTrader_afterfight") {
		LAi_group_Delete("EnemyFight");
		sld = characterFromID("ShadowTrader");        
		LAi_SetStayType(sld);
		DoQuestCheckDelay("hide_weapon", 1.3);
		sld = characterFromID("ShadowTrader"); 
		sld.greeting = "ransack"; // 240912
	}
	
	else if (sQuestName == "ShadowTrader_killed_end") {//убили Паскаля
	sld = characterFromID("ShadowTrader"); 
	LAi_SetActorType(sld);
	LAi_KillCharacter(sld);
	LAi_SetPlayerType(pchar);
		DoQuestFunctionDelay("ShadowTrader_final", 15.0);
	pchar.questTemp.Shadowtrader.End.Kill = "true";
	AddQuestRecord("Shadowtrader", "10");
	AddQuestUserData("Shadowtrader", "sSex", GetSexPhrase(StringFromKey("MiniQuests_3"),StringFromKey("MiniQuests_4")));
	AddQuestUserData("Shadowtrader", "sSex1", GetSexPhrase(StringFromKey("MiniQuests_1"),StringFromKey("MiniQuests_2")));
	ChangeCharacterComplexReputation(pchar,"nobility", -3); 
	AddComplexSelfExpToScill(70, 70, 70, 70);
	AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
	AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
	Achievment_SetStat(95, 1);
	}
//<-- Бесчестный конкурент конец

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Jason---------------------------------------Заносчивый аристократ------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	else if (sQuestName == "Badboy_capture") {
		sld = characterFromId("Badboy");
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "Afraid", "Badboy_afraid", 3.0);
	}
	
	else if (sQuestName == "Badboy_afraid") {
		LAi_SetActorType(pchar);
		sld = characterFromID("Badboy");        
		LAi_SetActorType(sld);
		LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
		LAi_ActorTurnToCharacter(sld, pchar);
		SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
	}
	
	else if (sQuestName == "Badboy_killed_end") {
	sld = characterFromID("Badboy"); 
	LAi_SetActorType(sld);
	LAi_KillCharacter(sld);
	LAi_SetPlayerType(pchar);
	ChangeCharacterComplexReputation(pchar,"nobility", -15); 
	chrDisableReloadToLocation = false;
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
	Achievment_SetStat(95, 1);
	}
	
	else if (sQuestName == "Badboy_die") {
		if (CheckAttribute(PChar, "quest.BadboyPlace")) Pchar.quest.BadboyPlace.over = "yes";
		if (CheckAttribute(PChar, "quest.BadboyDuelTimer")) Pchar.quest.BadboyDuelTimer.over = "yes";
		DoQuestCheckDelay("hide_weapon", 1.0);
		chrDisableReloadToLocation = false;
		LAi_LocationDisableOfficersGen(pchar.GenQuest.Badboy.Brothel.City + "_ExitTown", false); //офицеров пускать
		locations[FindLocation(pchar.GenQuest.Badboy.Brothel.City + "_ExitTown")].DisableEncounters = false; //энкаутеры откроем
		pchar.GenQuest.Badboy.Complete = "true";
	}
// <-- Заносчивый аристократ конец

	//поисковый генератор
	else if (sQuestName == "CitizSeekCap_afterCabinFight") {
		sld = GetCharacter(NPC_GenerateCharacter(pchar.GenQuest.CitizSeekCap.label + "_" + pchar.GenQuest.CitizSeekCap.WifeCity, pchar.GenQuest.CitizSeekCap.model, pchar.GenQuest.CitizSeekCap.sex, pchar.GenQuest.CitizSeekCap.ani, 5, pchar.GenQuest.CitizSeekCap.nation, -1, false, "citizen"));
		sld.name = pchar.GenQuest.CitizSeekCap.WifeName;
		sld.lastname = pchar.GenQuest.CitizSeekCap.WifeLastname;
		sld.dialog.filename   = "Quest\ForAll_dialog.c";
		sld.dialog.currentnode = pchar.GenQuest.CitizSeekCap.label + "_Board";
		sld.quest.SeekCap = pchar.GenQuest.CitizSeekCap.label;
		sld.quest.cribCity = pchar.GenQuest.CitizSeekCap.WifeCity;
		DeleteAttribute(pchar, "GenQuest.CitizSeekCap");
		LAi_SetStayType(sld);
		GetCharacterPos(pchar, &locx, &locy, &locz);
		ChangeCharacterAddressGroup(sld, pchar.location, "rld", LAi_FindFarLocator("rld", locx, locy, locz));
		LAi_SetActorType(pchar);
		LAi_SetActorType(sld);
		SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
		LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
	}

	else if (sQuestName == "CitizSeekCap_GivePrisoner") {
		sld = GetCharacter(NPC_GenerateCharacter(pchar.GenQuest.CitizSeekCap.label + "_" + pchar.GenQuest.CitizSeekCap.PrisonerCity, pchar.GenQuest.CitizSeekCap.model, pchar.GenQuest.CitizSeekCap.sex, pchar.GenQuest.CitizSeekCap.ani, 5, sti(pchar.GenQuest.CitizSeekCap.nation), -1, false, "citizen"));
		sld.name = pchar.GenQuest.CitizSeekCap.PrisonerName;
		sld.lastname = pchar.GenQuest.CitizSeekCap.PrisonerLastname;
		//pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(sld);
		//SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
		AddPassenger(pchar, sld, false);//добавить пассажира
		SetCharacterRemovable(sld, false);
		log_info(StringFromKey("MiniQuests_21", sld.name)); // 170712
		PlaySound("interface\notebook.wav");
		DeleteAttribute(pchar, "GenQuest.CitizSeekCap");
	}
	
//--> Jason ТТГ, почта 2 уровень, агент в таверне
	else if (sQuestName == "PostAgent_inTavern_Room") {
		DoQuestReloadToLocation(pchar.questTemp.WPU.Postcureer.StartCity +"_tavern_upstairs", "goto", "goto4", "");			
		sld = characterFromID("PostAgent");        
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.5);
	}
	
	else if (sQuestName == "PostAgent_inTavern_Room_end") {
		SetLaunchFrameFormParam(StringFromKey("MiniQuests_22"), "", 0, 4);
		LaunchFrameForm();
		WaitDate("", 0, 0, 0, 1, 10); //крутим время
		RecalculateJumpTable();
		sld = characterFromID("PostAgent");        
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 4.5);
	}
	// <-- почтовый генер 2 уровня, агент в таверне
	else if (sQuestName == "DisasterShipIndian_Win") {
		chrDisableReloadToLocation = false;
		sld = characterFromId("WMCaptain");
		LAi_SetActorType(sld);
		sld.dialog.Filename = "Quest\Other_quests_NPC.c";
		sld.dialog.currentnode = "DisasterCap_8";
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
//<-- ТТГ, почта 2 уровень, конец
	
//--> Jason, действия горожан по мини-квестам
	//отпускание рабов через монаха
	else if (sQuestName == "Monk_RemoveSlaves") {
		RemoveCharacterGoods(pchar, GOOD_SLAVES, GetSquadronGoods(pchar, GOOD_SLAVES));
		OfficersReaction("good");
		ChangeCharacterComplexReputation(pchar, "nobility", 1);
	}
	
	//освящение кораблей через монаха
	else if (sQuestName == "Monk_Shipshine") {
		OfficersReaction("good");
		ChangeCharacterComplexReputation(pchar, "nobility", 1);
		ChangeCharacterComplexReputation(pchar, "authority", 2);
		AddCrewMorale(pchar, 10);
		pchar.quest.Shipshine.win_condition.l1 = "Timer";
		pchar.quest.Shipshine.win_condition.l1.date.hour  = sti(GetTime());
		pchar.quest.Shipshine.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 15);
		pchar.quest.Shipshine.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 15);
		pchar.quest.Shipshine.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 15);
		pchar.quest.Shipshine.function = "Monkshipshine_Over";
	}
	
	//установка капеллана в кают-компанию
	else if (sQuestName == "Monk_Capellan") {
		chrDisableReloadToLocation = false;//открыть локацию
		sld = characterFromId(pchar.questTemp.ShipCapellan.id);
		sld.dialog.currentnode = "capellan_4";
		LAi_SetStayType(sld);
	}

	//установка дворянина с реликвией в таверну
	else if (sQuestName == "Nobleman_lombardTavern") {
		chrDisableReloadToLocation = false;//открыть локацию
		sld = characterFromId(pchar.GenQuest.Noblelombard.id);
		sld.dialog.currentnode = "lombard_4";
		LAi_SetSitType(sld);
	}
	
	//установка дворянина в церковь
	else if (sQuestName == "Nobleslaves_Place") {
		chrDisableReloadToLocation = false;//открыть локацию
		sld = characterFromId(sGlobalTemp);
		sld.dialog.currentnode = "slaves_3";
		LAi_SetSitType(sld);
		LAi_SetLoginTime(sld, 11.0, 13.0);
	}
	
	//выдача пассажира после абордажа
	else if (sQuestName == "Marginpassenger_GivePrisoner") {
		sld = GetCharacter(NPC_GenerateCharacter("MarginPass", pchar.GenQuest.Marginpassenger.model, pchar.GenQuest.Marginpassenger.sex, pchar.GenQuest.Marginpassenger.ani, 2, sti(pchar.GenQuest.Marginpassenger.Nation), -1, true, "quest"));
		sld.Dialog.Filename = "Quest\Marginpassenger.c";
		sld.dialog.currentnode = "MarginPass";
		sld.name = pchar.GenQuest.Marginpassenger.q1Name;
		sld.lastname = "";
		ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
		LAi_SetActorType(sld);
		LAi_ActorDialogNow(sld, pchar, "", -1);
		pchar.GenQuest.Marginpassenger.Boarding = "true";
		AddComplexSeaExpToScill(50, 50, 50, 50, 50, 50, 0);
		AddComplexSelfExpToScill(60, 60, 60, 60);
	}
	
	//после боя в бухте
	else if (sQuestName == "Marginpassenger_Afterbattle") {
		LAi_group_Delete("EnemyFight");
		chrDisableReloadToLocation = false;
		AddCharacterGoods(pchar, sti(pchar.GenQuest.Marginpassenger.Goods), sti(pchar.GenQuest.Marginpassenger.GoodsQty));
		AddQuestRecord("Marginpassenger", "15");
		AddQuestUserData("Marginpassenger", "sSex1", GetSexPhrase(StringFromKey("MiniQuests_7"),StringFromKey("MiniQuests_8")));
		AddQuestUserData("Marginpassenger", "sShore", XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Dat"));
		CloseQuestHeader("Marginpassenger");
		DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
		AddComplexSelfExpToScill(80, 80, 80, 80);
		ChangeCharacterComplexReputation(pchar, "authority", 1);
		ChangeOfficersLoyality("good_all", 1);
		ChangeCharacterNationReputation(pchar, SPAIN, -1);
	}
	
	////////////////////////////////////////////////////////////////////////
	//  Начало    Сопровождение торговца
	////////////////////////////////////////////////////////////////////////
	else if (sQuestName == "prepare_for_convoy_quest") {
		iTemp = sti(colonies[FindColony(pchar.quest.destination)].nation);
		sld = GetCharacter(NPC_GenerateCharacter("QuestTrader", "", "man", "man", makeint((sti(pchar.rank)+60)/4), iTemp, -1, true, "citizen"));
		SetCaptanModelByEncType(sld, "trade");
		sld.reputation.nobility = (1 + rand(44) + rand(44));
		sld.Dialog.Filename = "convoy_traider.c";
		sld.dialog.currentnode = "prepare_convoy_quest";
		sld.greeting = "Gr_ConvoyTrader";
		sld.BakNation = sld.nation;		
		sld.Abordage.Enable = true;
		sld.CompanionEnemyEnable = true;
		LAi_LoginInCaptureTown(sld, true);
		ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");			
		pchar.quest.generate_convoy_quest_progress = "begin";
		Pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу.
		chrDisableReloadToLocation = true;
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	
	else if (sQuestName == "convoy_refused") {
		pchar.quest.generate_convoy_quest_failed.over = "yes";
		pchar.quest.generate_convoy_quest_completed.over = "yes";
		pchar.quest.generate_convoy_quest_timer.over = "yes";
		if (checkquestattribute("generate_convoy_quest_progress", "completed"))
		{
			OfficersReaction("good");
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			AddCharacterExpToSkill(pchar, "COMMERCE", 5);
			AddQuestRecord("convoy_quest", "4");
			CloseQuestHeader("convoy_quest");
			AddMoneyToCharacter(pchar, sti(pchar.ConvoyQuest.convoymoney));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			RemoveCharacterCompanion(Pchar, characterFromID("QuestTrader"));
			CloseQuestHeader("convoy_quest");
		}
		pchar.quest.generate_convoy_quest_progress = "";
		GetCharacterPos(pchar, &locx, &locy, &locz);
		LAi_SetActorType(characterFromID("QuestTrader"));
		LAi_ActorGoToLocation(characterFromID("QuestTrader"), "reload", LAi_FindFarLocator("reload", locx, locy, locz), "none", "", "", "", 20.0);
	}
	
	else if (sQuestName == "generate_convoy_quest_timer") {
		AddQuestRecord("convoy_quest", "2");
		CloseQuestHeader("convoy_quest");            
		sld = characterFromID("QuestTrader");
		ChangeCharacterHunterScore(pchar, NationShortName(sti(sld.BakNation)) + "hunter", 5+rand(10));// награда
		RemoveCharacterCompanion(Pchar, sld);
		OfficersReaction("bad");
		ChangeCharacterComplexReputation(pchar,"nobility", -10);
		pchar.quest.generate_convoy_quest_progress = "";
		pchar.quest.generate_convoy_quest_failed.over = "yes";
		pchar.quest.generate_convoy_quest_completed.over = "yes";
	}
	
	else if (sQuestName == "generate_convoy_quest_failed") { // торговец умер
		ChangeCharacterComplexReputation(pchar,"nobility", -5);
		OfficersReaction("bad");
		RemoveCharacterCompanion(Pchar, characterFromID("QuestTrader"));
		pchar.quest.generate_convoy_quest_progress = "";
		pchar.quest.generate_convoy_quest_failed.over = "yes";
		pchar.quest.generate_convoy_quest_completed.over = "yes";
		pchar.quest.generate_convoy_quest_timer.over  = "yes";            
		AddQuestRecord("convoy_quest", "3");
		CloseQuestHeader("convoy_quest");
	}
	
	else if (sQuestName == "generate_convoy_quest_completed") {
		sld = characterFromID("QuestTrader");
		if (IsCompanion(sld))
		{
			sld.dialog.currentnode = "complete_convoy_quest";
			PlaceCharacter(sld, "goto", pchar.location);			
			Pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу.			
			chrDisableReloadToLocation = true;
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		}
		else
		{
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			ChangeCharacterHunterScore(pchar, NationShortName(sti(sld.BakNation)) + "hunter", 10+rand(10));// награда
			OfficersReaction("bad");
			pchar.quest.generate_convoy_quest_progress = "";				
			pchar.quest.generate_convoy_quest_failed.over = "yes";
			pchar.quest.generate_convoy_quest_completed.over = "yes";
			pchar.quest.generate_convoy_quest_timer.over  = "yes";  
			AddQuestRecord("convoy_quest", "5");
			CloseQuestHeader("convoy_quest");
		}
	}		

	else if (sQuestName == "convoy_agreeded") {
		sld = characterFromID("QuestTrader");
		CharacterIntoCompanionAndGoOut(pchar, sld, "reload", "reload1_back", 3.0, false);
		ReOpenQuestHeader("convoy_quest");
		AddQuestRecord("convoy_quest", "1");
		AddQuestUserData("convoy_quest", "sSex", GetSexPhrase(StringFromKey("MiniQuests_1"),StringFromKey("MiniQuests_2")));
		sTemp = XI_ConvertString("Colony" + pchar.quest.destination + "Gen") + StringFromKey("MiniQuests_23") + XI_ConvertString(GetIslandByCityName(pchar.quest.destination) + "Voc") + ","; // belamour gen
		AddQuestUserData("convoy_quest", "sCity", sTemp);
		AddQuestUserData("convoy_quest", "sDay", FindRussianDaysString(sti(pchar.ConvoyQuest.iDay)));
		AddQuestUserData("convoy_quest", "sMoney", FindRussianMoneyString(sti(pchar.ConvoyQuest.convoymoney)));
		// по городу вернём его порт
		attrName = GetPortByCityName(pchar.quest.destination);            
		pchar.quest.generate_convoy_quest_completed.win_condition.l1 = "Location";
		pchar.quest.generate_convoy_quest_completed.win_condition.l1.location = attrName;
		pchar.quest.generate_convoy_quest_completed.win_condition = "generate_convoy_quest_completed";			
		if (rand(2) == 1) TraderHunterOnMap(false);
	}
	////////////////////////////////////////////////////////////////////////
	//  Конец    Сопровождение торговца
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//  Начало    Доставка пассажира
	////////////////////////////////////////////////////////////////////////
	else if (sQuestName == "prepare_for_passenger_quest") {
		iTemp = sti(colonies[FindColony(sGlobalTemp)].nation);
		Rank = NPC_GenerateCharacter("QuestPassanger", "", "man", "man", makeint((sti(pchar.rank)+60)/4), iTemp, -1, true, "citizen");
		sld = &characters[Rank];
		sld.id = sld.id + "_" + sld.index; //меняем ID на оригинальный
		sld.reputation = (1 + rand(44) + rand(44));
		SetCaptanModelByEncType(sld, "trade");
		SetRandomNameToCharacter(sld);
		sld.Dialog.Filename = "convoy_passenger.c";
		sld.dialog.currentnode = "prepare_convoy_quest";
		LAi_LoginInCaptureTown(sld, true);
		ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");			
		Pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу.
		chrDisableReloadToLocation = true;
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);            
	}

	else if (sQuestName == "AllPassangersDead") { // торговец умер
		sld = &characters[sti(pchar.quest.(qname).Idx)];
		ChangeCharacterComplexReputation(pchar,"nobility", -5);
		RemovePassenger(PChar, sld);
		sTemp = sld.id + "_complited";
		pchar.quest.(sTemp).over = "yes";
		sTemp = sld.id + "_TimeOver";
		pchar.quest.(sTemp).over = "yes";
		DeleteAttribute(pchar, "GenQuest.ConvoyPassenger." + sld.id); //извлекаем из структуры недовольных
		//--> смотрим Deck
		makearef(arAll, pchar.GenQuest.ConvoyPassenger);
		if (GetAttributesNum(arAll) == 0) pchar.quest.ConvoyMapPassenger.over = "yes";
		//<-- смотрим Deck
		attrName = sld.index + "convoy_passenger";
		AddQuestRecordEx(attrName, "Gen_convoy_passenger", "3");
		CloseQuestHeader(attrName);
	}
	
	else if (sQuestName == "AllPassangersTimeOver") {
		sld = &characters[sti(pchar.quest.(qname).Idx)];
		sTemp = sld.id;
		Pchar.GenQuest.ConvoyPassenger.(sTemp) = sld.index; //в структуру недовольных
		if (!CheckAttribute(Pchar, "quest.ConvoyMapPassenger"))
		{
			Pchar.quest.ConvoyMapPassenger.win_condition.l1 = "MapEnter";
			Pchar.quest.ConvoyMapPassenger.win_condition = "AllPassengerDeck";
		}
	}
	
	else if (sQuestName == "AllPassengerDeck") { // разговор на палубе			
		MakeCloneShipDeck(pchar, true); // подмена палубы
		makearef(arAll, pchar.GenQuest.ConvoyPassenger);
		iTemp = GetAttributesNum(arAll);
		for (i=0; i<iTemp; i++)
		{
			arPass = GetAttributeN(arAll, i);
			sld = &characters[sti(arPass)];				
			ChangeCharacterAddress(sld, "Ship_deck", "goto4");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0); 
		}
		makearef(arOldMapPos, worldMap.old);
		WdmPrepareMapForAbordage(arOldMapPos);
		DoReloadFromWorldMapToLocation("Ship_deck", "goto", "goto5");
		ReloadFromWMtoL_complete();
		pchar.quest.Munity = "";  // признак выхода с палубы
		LAi_LockFightMode(Pchar, true);
	}
	
	else if (sQuestName == "AllPassangersComplited") {
		sld = &characters[sti(pchar.quest.(qname).Idx)];
		sTemp = sld.id + "_TimeOver";
		pchar.quest.(sTemp).over = "yes";
		sTemp = sld.id + "_dead";
		pchar.quest.(sTemp).over = "yes";
		Pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу.
		chrDisableReloadToLocation = true;
		sld.dialog.currentnode = "complete_convoy_quest";
		PlaceCharacter(sld, "goto", "random_must_be");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);     
	}
	////////////////////////////////////////////////////////////////////////
	//  Конец    Доставка пассажира
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//  ОЗГ - пассажир
	//////////////////////////////////////////////////////////////////////// 
	else if (sQuestName == "ContraPass_GivePrisoner") {
		chrDisableReloadToLocation = true;//закрыть локацию
		sld = GetCharacter(NPC_GenerateCharacter("ContraPassTempsailor", "Alonso", "man", "man", 10, sti(pchar.Mation), 0, true, "quest"));
		sld.name 	= StringFromKey("MiniQuests_24");
		sld.lastname = "";
		sld.Dialog.Filename = "MayorQuests_dialog.c";
		sld.dialog.currentnode = "Tempsailor";
		GetCharacterPos(pchar, &locx, &locy, &locz);
		ChangeCharacterAddressGroup(sld, pchar.location, "rld", LAi_FindNearestFreeLocator("rld", locx, locy, locz));
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		AddComplexSelfExpToScill(50, 50, 50, 50);
	}
	
	////////////////////////////////////////////////////////////////////////
	//  дезертир
	//////////////////////////////////////////////////////////////////////// 
	else if (sQuestName == "Fugitive_afterfight") {
		chrDisableReloadToLocation = false;//открыть локацию
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.GenQuest.FindFugitive.City+"_tavern")], true);//запретить драться - для таверны, для остальных пройдёт без последствий
		LAi_group_Delete("EnemyFight");
		sld = characterFromId("Fugitive");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		AddComplexSelfExpToScill(30, 30, 30, 30);
	}

	////////////////////////////////////////////////////////////////////////
	//  Начало   Генератор - Поручение капитана "Операция 'Галеон'"
	//////////////////////////////////////////////////////////////////////// 

	else if (sQuestName == "CaptainComission_FightInDeck") {
		GetCharacterPos(pchar, &locx, &locy, &locz);
		LAi_LocationFightDisable(loadedLocation, false);
		LAi_SetFightMode(pchar, true);
		Rank = sti(pchar.rank) + 5 + rand(MOD_SKILL_ENEMY_RATE);
		LAi_group_Delete("EnemyFight");
		for (i=1; i < 5; i++) 
		{	
			sld = characterFromID("saylor_0" + i);
			sld.rank = Rank;
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "CaptainComission_TeamIsDead");
	}
	
	else if (sQuestName == "CaptainComission_TeamIsDead") {
		pchar.quest.CaptainComission_CapIsOut.win_condition.l1 = "ExitFromSea";
		pchar.quest.CaptainComission_CapIsOut.function = "CaptainComission_CapIsOut";
		pchar.quest.CaptainComission_CapIsDead.win_condition.l1 = "NPC_Death";
		pchar.quest.CaptainComission_CapIsDead.win_condition.l1.character = "CapComission_1";
		pchar.quest.CaptainComission_CapIsDead.function = "CaptainComission_CapIsDead";
		LAi_SetFightMode(pchar, false);
		LAi_LocationFightDisable(loadedLocation, true);
		//DoQuestCheckDelay("TalkSelf_Quest", 0.4); //диалог сам-на-сам лесник  лишнее
	}

	else if (sQuestName == "CaptainComission_TalkCanoneer") {
		LAi_Fade("CaptainComission_TalkCanoneer_prepare", "CaptainComission_TalkCanoneer2");
	}
	
	else if (sQuestName == "CaptainComission_TalkCanoneer_prepare") {
		LAi_SetSitType(pchar);
		sld = characterFromID("CapComission_Canoneer");
		LAi_SetActorType(sld);
		LAi_ActorSetSitMode(sld);			
		ChangeCharacterAddressGroup(pchar, pchar.GenQuest.CaptainComission.City + "_tavern", "sit", "sit_front2");
	}
	
	else if (sQuestName == "CaptainComission_TalkCanoneer2") {
		LAi_ActorDialogNow(characterFromID("CapComission_Canoneer"), pchar, "", -1);
	}
	
	else if (sQuestName == "CaptainComission_exit_sit") {
		if (pchar.location.group == "sit")
		{
			LAi_Fade("CaptainComission_exit_sit_2", "");
		}
	}

	else if (sQuestName == "CaptainComission_exit_sit_2") {
		sld = characterFromID("CapComission_Canoneer");
		LAi_SetSitType(sld);
		LAi_SetPlayerType(pchar);
		PlaceCharacter(pchar, "tables", pchar.location); // ближний к столу
	}

	else if (sQuestName == "CaptainComission_GangDialog_1") {
		sld = characterFromID("Gang_0");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);	
	}
			
	else if (sQuestName == "CaptainComission_MapEnterAfterShoreBattle") {
		for (i = 1; i <=3; i++)
		{
			iTemp = GetCharacterIndex("Pirate_Captain0" + i);
			if (iTemp != -1)
			{
				characters[iTemp].lifeDay = 0;
			}
		}
		Group_DeleteGroup("Pirate_Guards"); 
		DeleteAttribute(pchar, "GenQuest.CaptainComission");
	}
	
	else if (sQuestName == "CaptainComission_GenerateCapJail") {
		sld = characterFromID("CapComission_1");
		ChangeCharacterAddressGroup(sld, pchar.GenQuest.CaptainComission.City + "_prison", "goto", "goto9");
		LAi_group_MoveCharacter(sld, "Prisoner_Group"); 
		LAi_SetCitizenType(sld);// с этого места не было кода лесник
		LAi_SetStayType(sld);						
		sld.name = pchar.GenQuest.CaptainComission.Name;
		sld.lastname = "";
		sld.greeting = "Gr_prison";
		sld.dialog.FileName = "GenQuests_Dialog.c";
		sld.dialog.currentnode = "CaptainComission_370"; 											 
	}
	
	else if (sQuestName == "CaptainComission_Capitan_Cdox") {
		 // добавлена проверка на смерть капитана по "поручению капитана" от руки игрока уже после тюрьмы. лесник
		AddQuestRecord("CaptainComission2", "33");
		AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
		pchar.quest.CaptainComission_Capitan_Cdox.over = "yes"; // на сякий случай
		CloseQuestHeader("CaptainComission2");
		DeleteAttribute(pchar, "GenQuest.CaptainComission");
	}
	
	
	else if (sQuestName == "CaptainComission_PrisonFree_Death") {			
		pchar.quest.CapComission_DeletePrisonGroup.win_condition.l1 = "ExitFromLocation";
		pchar.quest.CapComission_DeletePrisonGroup.win_condition.l1.location = pchar.location;
		pchar.quest.CapComission_DeletePrisonGroup.win_condition = "CaptainComission_DeletePrisonGroup";
		pchar.quest.CaptainComission_GetSecretTimeIsOut.over = "yes";
		AddQuestRecord("CaptainComission2", "55");
		AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
		CloseQuestHeader("CaptainComission2");
		DeleteAttribute(pchar, "GenQuest.CaptainComission");
	}
	
	else if (sQuestName == "CaptainComission_DeletePrisonGroup") {
		LAi_group_Delete("CapComission_Prison");
	}

	else if (sQuestName == "CaptainComission_ExitFromPrison") {
		iTemp = GetCharacterIndex("CapComission_1");
		if (iTemp != -1)
		{
			pchar.quest.CaptainComission_ExitFromTown.win_condition.l1 	= "EnterToSea";           	
			pchar.quest.CaptainComission_ExitFromTown.function    		= "CaptainComission_ExitFromTown";						
			pchar.GenQuest.CaptainComission.canSpeakCaptain = true;
			pchar.TownEscape = true;
		}
	}
	
	else if (sQuestName == "CaptainComission_MeetWithCaptain") {
		Sea_DeckBoatStartNow(pchar);
	}

	else if (sQuestName == "CaptainComission_MapEnterCapDied") {
		DeleteAttribute(pchar, "GenQuest.CaptainComission");
	}
	
	else if (sQuestName == "CaptainComission_ShoreGangDialog") {
		SetMainCharacterIndex(1);
		pchar = GetMainCharacter();
		LAi_SetPlayerType(pchar);
		locCameraTarget(pchar)
		locCameraFollow();
		EndQuestMovie(); 	
		ChangeShowIntarface();
		InterfaceStates.Buttons.Save.enable = true;
		bDisableCharacterMenu = false;			
		DoQuestFunctionDelay("CaptainComission_BattleInShore", 5.0); 
	}
	////////////////////////////////////////////////////////////////////////
	//  Конец   Генератор - Поручение капитана "Операция 'Галеон'"
	//////////////////////////////////////////////////////////////////////// 

	////////////////////////////////////////////////////////////////////////
	//  Начало   Генератор - "Кораблекрушенцы"
	//////////////////////////////////////////////////////////////////////// 		
	
	else if (sQuestName == "ShipWreck_RemoveSailorsFromShore") {
		for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
		{
			iTemp = GetCharacterIndex("ShipWreck_" + i);		
			if(iTemp != -1)
			{
				Characters[iTemp].LifeDay = 0;
			}
		}	
		DeleteAttribute(pchar, "GenQuest.ShipWreck");		
	}
	////////////////////////////////////////////////////////////////////////
	//  Конец   Генератор - "Кораблекрушенцы"
	////////////////////////////////////////////////////////////////////////
	else
	{
		condition = false;
	}
	
	return condition;
}