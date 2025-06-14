string LangFile = "SantaMisericordia.txt";

void SantaMisericordia_init()
{
	//if(!GetDLCenabled(DLC_APPID_4)) return;
	pchar.questTemp.SantaMisericordia = true;
	log_testinfo("Инициализация ГАЛЕОНА");
	pchar.questTemp.SantaMisericordia.stage = 1; // стадии меняем при выходе на карту
	pchar.questTemp.SantaMisericordia.colony = SantaMisericordia_findColony(sti(pchar.questTemp.SantaMisericordia.stage)); // колонии меняем при заходе в порт
    ref sld, chref;
	string sName = GetConvertStr("Ship_Name", LangFile);
	
	// характеристики запишем после ТЗ
	chref = GetCharacter(NPC_GenerateCharacter("SantaMisericordia_cap", "off_spa_2", "man", "man", 30, SPAIN, -1, false, "governor"));
	FantomMakeCoolSailor(chref, SHIP_GALEON_SM, sName, CANNON_TYPE_CANNON_LBS24, 105, 105, 105);
	FantomMakeCoolFighter(chref, 30, 100, 100, "lacrima_patris", "pistol8", "harpoon", 100);
	chref.ship.Crew.Morale = 100;
	ChangeCrewExp(chref, "Sailors",   100);
	ChangeCrewExp(chref, "Cannoners", 100);
	ChangeCrewExp(chref, "Soldiers",  100); 
	LAi_SetHP(chref, 200 + makeint(pchar.rank) * 2, 200 + makeint(pchar.rank) * 2);
	SetAllPerksToChar(chref, true);
	chref.name = GetConvertStr("Cap_Name", LangFile);
	chref.lastname = GetConvertStr("Cap_lastname", LangFile);
	UpgradeShipParameter(chref, "SpeedRate");	//апгрейдить скорость
	UpgradeShipParameter(chref, "TurnRate");	//манёвренность 
	chref.DontRansackCaptain = true; //квестовые не сдаются
	SetSPECIAL(chref, 10, 10, 10, 10, 10, 10, 10);
	SetSelfSkill(chref, 100, 100, 100, 100, 100);
	SetShipSkill(chref, 100, 100, 100, 100, 100, 100, 100, 100, 100);
	chref.SaveItemsForDead = true;
	chref.DontClearDead = true;
	chref.DontHitInStorm = true;
	//Предметы
	AddItems(chref, "harpoon", 20);
	AddItems(chref, "potion4", 5);
	GiveItem2Character(chref, "cirass1");
	EquipCharacterByItem(chref, "cirass1");
	GiveItem2Character(chref, "amulet_8");
	GiveItem2Character(chref, "amulet_10");
	GiveItem2Character(chref, "obereg_11");
	//Усиленный меч
	sld = ItemsFromID("lacrima_patris");
	sld.Attack = 90.0;
	SetBladeWeightAttack(sld);
	//Товары в трюме
	SetCharacterGoods(chref, GOOD_ROPES, 100+rand(50));
	SetCharacterGoods(chref, GOOD_CINNAMON, 100+rand(50));
	SetCharacterGoods(chref, GOOD_OIL, 100+rand(50));
	SetCharacterGoods(chref, GOOD_SHIPSILK, 100+rand(50));
	SetCharacterGoods(chref, GOOD_POWDER, 3000);
	SetCharacterGoods(chref, GOOD_BALLS, 900);
	SetCharacterGoods(chref, GOOD_GRAPES, 600);
	SetCharacterGoods(chref, GOOD_KNIPPELS, 500);
	SetCharacterGoods(chref, GOOD_BOMBS, 1000);
	
	string sGroup = "Sea_"+chref.id
	Group_FindOrCreateGroup(sGroup);
	Group_SetType(sGroup,"trade");
    Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
    Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, chref.id);
	Group_SetGroupCommander(sGroup, chref.id);
	SetRandGeraldSail(chref, sti(chref.Nation));
	
	chref.quest = "InMap";
	chref.city = SantaMisericordia_findColony(sti(pchar.questTemp.SantaMisericordia.stage));
	chref.quest.targetCity = SantaMisericordia_findColony(sti(pchar.questTemp.SantaMisericordia.stage)+1);
	chref.mapEnc.type = "trade";
	chref.mapEnc.worldMapShip = "galeon_sm";
	chref.mapEnc.Name = GetConvertStr("Ship_Name", LangFile);
	Map_CreateTrader(chref.city, chref.quest.targetCity, chref.id, 1000);
	
	// журнал капитана Фернандо де Аламиды
	sld = ItemsFromID("Reserve_item_02");
	sld.name = "itmname_FernandoDeAlavidaJournal";
	sld.describe = "itmdescr_FernandoDeAlavidaJournal";
	sld.picIndex = 14;
	sld.picTexture = "ITEMS_22";
	sld.price = 10;
	sld.Weight = 0.1;
	
	// скомканное письмо капитана Фернандо де Аламиды
	sld = ItemsFromID("Reserve_item_03");
	sld.name = "itmname_FernandoDeAlavidaPismo";
	sld.describe = "itmdescr_FernandoDeAlavidaPismo";
	sld.picIndex = 12;
	sld.picTexture = "ITEMS_22";
	sld.price = 10;
	sld.Weight = 0.1;
	
	PChar.quest.SantaMisericordia_ZapisiJurnala.win_condition.l1 = "item";
	PChar.quest.SantaMisericordia_ZapisiJurnala.win_condition.l1.item = "Reserve_item_02";
	PChar.quest.SantaMisericordia_ZapisiJurnala.function = "SantaMisericordia_ZapisiJurnala";
	
	// победа, чистим всё и возвращаем всё на место
	PChar.quest.SantaMisericordia_PobedaAchivka.win_condition.l1 = "NPC_Death";
	PChar.quest.SantaMisericordia_PobedaAchivka.win_condition.l1.character = "SantaMisericordia_cap";
	PChar.quest.SantaMisericordia_PobedaAchivka.function = "SantaMisericordia_Pobeda";
	
	// слухи о местонахождении галеона Милосердии
	SetTimerCondition("SantaMisericordia_Sluhi", 0, 4, 0, false);
}

string SantaMisericordia_findColony(int stage);
{
	string OurColonies[22];
    OurColonies[0] = "Havana";
    OurColonies[1] = "Santiago";
    OurColonies[2] = "PortRoyal";
    OurColonies[3] = "Tortuga";
    OurColonies[4] = "PortPax";
    OurColonies[5] = "SantoDomingo";
    OurColonies[6] = "SanJuan";
    OurColonies[7] = "Marigo";
    OurColonies[8] = "Charles";
    OurColonies[9] = "SentJons";
    OurColonies[10] = "BasTer";
    OurColonies[11] = "FortFrance";
    OurColonies[12] = "Bridgetown";
    OurColonies[13] = "Villemstad";
    OurColonies[14] = "PortSpein";
    OurColonies[15] = "Cumana";
    OurColonies[16] = "Caracas";
    OurColonies[17] = "Maracaibo";
    OurColonies[18] = "Cartahena";
    OurColonies[19] = "PortoBello";
    OurColonies[20] = "SantaCatalina";
    OurColonies[21] = "Beliz";

    string SpanishColonies[22];
    int spanishCount = 0;

    for (int j = 0; j < 22; j++) 
	{
        ref rCity = GetColonyRefByID(OurColonies[j]);
        if (sti(rCity.nation) == SPAIN)
		{
            SpanishColonies[spanishCount] = OurColonies[j];
            spanishCount++;
        }
    }
	
    // Проверка на корректность стадии
    if (stage < 1 || stage > spanishCount)
	{
		trace("Некорректная стадия " + stage + " Испанских колоний: " + spanishCount);
		Log_testinfo("Некорректная стадия " + stage + " Испанских колоний: " + spanishCount);
        return "";
    }
	
    return SpanishColonies[stage - 1]; // Индексы начинаются с 0, а стадии - с 1. Нулевая стадия только в последнем городе
}

int TotalSpainColonies()
{
	int spanishCount = 0;
	for(int i=0; i<MAX_COLONIES; i++)
	{
		if(Colonies[i].nation == SPAIN && !CheckAttribute(&Colonies[i], "HasNoFort"))
		{
			if(Colonies[i].id == "Panama") continue;
			if(Colonies[i].id == "SanAndres") continue;
			spanishCount++;
		}
	}
	return spanishCount;
}

void SantaMisericordia_ToCity(string sChar)
{
	if(!CharacterIsAlive(sChar)) {Log_testinfo("Капитан ГАЛЕОНА умер"); return;}
	pchar.questTemp.SantaMisericordia.colony = SantaMisericordia_findColony(sti(pchar.questTemp.SantaMisericordia.stage)+1);
	Log_testinfo("капитан галеона сошёл в порту "+ pchar.questTemp.SantaMisericordia.colony);
	
	//DeleteQuestCondition("SantaMisericordia_ToMap");
	
	//таймер через сколько опять выйти на карту
	int Qty = 14; //через сколько дней выйдем на карту
	PChar.quest.SantaMisericordia_toMap.win_condition.l1            = "Timer";
    PChar.quest.SantaMisericordia_toMap.win_condition.l1.date.day   = GetAddingDataDay(0, 0, Qty);
    PChar.quest.SantaMisericordia_toMap.win_condition.l1.date.month = GetAddingDataMonth(0, 0, Qty);
    PChar.quest.SantaMisericordia_toMap.win_condition.l1.date.year  = GetAddingDataYear(0, 0, Qty);
    PChar.quest.SantaMisericordia_toMap.function					= "SantaMisericordia_toMap";
	
	DeleteQuestCheck("SantaMisericordia_MapRelease");
	
	ref sld = &characters[GetCharacterIndex(sChar)];
	sld.quest = "InCity"; //флаг кэпа ходит по городу
	sld.City = sld.quest.targetCity; //аттрибут текущего города пропишем
	sld.DontDeskTalk = true; //нельзя выслать шлюпку
	if(CheckAttribute(sld, "SinkTenPercent")) DeleteAttribute(sld, "SinkTenPercent");
	int iColony = FindColony(sld.City);
	//стоит на рейде в порту
	string sGroup = "Sea_" + sld.id;
	Group_FindOrCreateGroup(sGroup);
	Group_AddCharacter(sGroup, sld.id);			
	Group_SetGroupCommander(sGroup, sld.id);
	Group_SetType(sGroup, "war");
	Group_SetAddress(sGroup, colonies[iColony].island, "quest_ships", "Quest_ship_"+(rand(2)+1));
	Group_SetTaskNone(sGroup);
	//ставим ограничения в колонии, где находится ревизор
	pchar.questTemp.SantaMisericordia.ColonyZapret = pchar.questTemp.SantaMisericordia.colony;
	//губернатор уступает место
	sld = CharacterFromID(pchar.questTemp.SantaMisericordia.colony + "_Mayor");
	sld.quest.SantaMisericordia;
	LAi_SetStayType(sld);
	ChangeCharacterAddressGroup(sld, pchar.questTemp.SantaMisericordia.colony + "_townhall", "goto", "governor1");
	//контрабандист
	sld = CharacterFromID(pchar.questTemp.SantaMisericordia.colony + "_Smuggler");
	sld.quest.SantaMisericordia;
	//бордель
	if (CharacterIsAlive(pchar.questTemp.SantaMisericordia.colony + "_Hostess"))
	{
		sld = CharacterFromID(pchar.questTemp.SantaMisericordia.colony + "_Hostess");
		sld.quest.SantaMisericordia;
	}
	//молится в церкви c 6-9
	sld = GetCharacter(NPC_GenerateCharacter("SantaMisericordia_clone_church", "off_spa_2", "man", "man", 30, SPAIN, -1, false, "governor"));
	sld.name = GetConvertStr("Cap_Name", LangFile);
	sld.lastname = GetConvertStr("Cap_lastname", LangFile);
	FantomMakeCoolFighter(sld, 30, 100, 100, "lacrima_patris", "pistol8", "harpoon", 100);
	sld.dialog.filename = "Quest\ShipsPack\SantaMisericordia_dialog.c";
	sld.dialog.currentnode = "Alamida_church";
	LAi_SetLoginTime(sld, 6.0, 8.99);
	sld.City = pchar.questTemp.SantaMisericordia.colony;
	ChangeCharacterAddressGroup(sld, pchar.questTemp.SantaMisericordia.colony + "_church", "sit", "sit"+(rand(3)+3));
	LAi_SetSitType(sld);
	sld.nonTable = true;
	sld.inChurch = true;
	LAi_SetImmortal(sld, true);
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	//ходит по улицам в городе c 9-17
	sld = GetCharacter(NPC_GenerateCharacter("SantaMisericordia_clone_city", "off_spa_2", "man", "man", 30, SPAIN, -1, false, "governor"));
	sld.name = GetConvertStr("Cap_Name", LangFile);
	sld.lastname = GetConvertStr("Cap_lastname", LangFile);
	FantomMakeCoolFighter(sld, 30, 100, 100, "lacrima_patris", "pistol8", "harpoon", 100);
	sld.dialog.filename = "Quest\ShipsPack\SantaMisericordia_dialog.c";
	sld.dialog.currentnode = "Alamida_city";
	LAi_SetLoginTime(sld, 9.0, 16.99);
	sld.City = pchar.questTemp.SantaMisericordia.colony;
	ChangeCharacterAddressGroup(sld, pchar.questTemp.SantaMisericordia.colony + "_town", "goto", "goto"+(rand(5)+1));
	LAi_SetCitizenType(sld);
	LAi_SetImmortal(sld, true);
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	//сидит в резиденции c 17-21
	sld = GetCharacter(NPC_GenerateCharacter("SantaMisericordia_clone_guber", "off_spa_2", "man", "man", 30, SPAIN, -1, false, "governor"));
	sld.name = GetConvertStr("Cap_Name", LangFile);
	sld.lastname = GetConvertStr("Cap_lastname", LangFile);
	FantomMakeCoolFighter(sld, 30, 100, 100, "lacrima_patris", "pistol8", "harpoon", 100);
	sld.dialog.filename = "Quest\ShipsPack\SantaMisericordia_dialog.c";
	sld.dialog.currentnode = "Alamida_guber";
	LAi_SetLoginTime(sld, 17.0, 20.99);
	sld.City = pchar.questTemp.SantaMisericordia.colony;
	ChangeCharacterAddressGroup(sld, pchar.questTemp.SantaMisericordia.colony + "_townhall", "sit", "sit1");
	LAi_SetHuberType(sld);
	LAi_SetImmortal(sld, true);
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	// Слухи жителей города
	string rumour1 = GetConvertStr("City_Rum1", LangFile);
	string rumour2 = GetConvertStr("City_Rum2", LangFile);
	string rumour3 = GetConvertStr("City_Rum3", LangFile);
	string rumour4 = GetConvertStr("City_Rum4", LangFile);
	string rumour5 = GetConvertStr("City_Rum5", LangFile);
	string rumour6 = GetConvertStr("City_Rum6", LangFile);
	string rumour7 = GetConvertStr("City_Rum7", LangFile);
	string rumour8 = GetConvertStr("City_Rum8", LangFile);
	string rumour9 = GetConvertStr("City_Rum9", LangFile);
	string rumour10 = GetConvertStr("City_Rum10", LangFile);
	
  
	/* switch (LanguageGetLanguage())
	{
	case "russian": break;
	case "english": break;
    
	} */
	
	AddSimpleRumourCity(rumour1, pchar.questTemp.SantaMisericordia.colony, 7, 1, "");
	AddSimpleRumourCity(rumour2, pchar.questTemp.SantaMisericordia.colony, 7, 1, "");
	AddSimpleRumourCity(rumour3, pchar.questTemp.SantaMisericordia.colony, 7, 1, "");
	AddSimpleRumourCity(rumour4, pchar.questTemp.SantaMisericordia.colony, 7, 1, "");
	AddSimpleRumourCity(rumour5, pchar.questTemp.SantaMisericordia.colony, 7, 1, "");
	AddSimpleRumourCity(rumour6, pchar.questTemp.SantaMisericordia.colony, 7, 1, "");
	AddSimpleRumourCity(rumour7, pchar.questTemp.SantaMisericordia.colony, 7, 1, "");
	AddSimpleRumourCity(rumour8, pchar.questTemp.SantaMisericordia.colony, 7, 1, "");
	AddSimpleRumourCity(rumour9, pchar.questTemp.SantaMisericordia.colony, 7, 1, "");
	AddSimpleRumourCity(rumour10, pchar.questTemp.SantaMisericordia.colony, 7, 1, "");
}

void SantaMisericordia_ToMap(string sQuest)
{
	if(!CharacterIsAlive("SantaMisericordia_cap")) {Log_testinfo("Капитан ГАЛЕОНА умер"); return;}
	ref chref = characterFromId("SantaMisericordia_cap");
	chref.quest = "InMap";
	
	string sGroup = "Sea_"+chref.id
	Group_FindOrCreateGroup(sGroup);
	Group_SetAddressNone(sGroup);
	
	pchar.questTemp.SantaMisericordia.stage = sti(pchar.questTemp.SantaMisericordia.stage) + 1;
	if(sti(pchar.questTemp.SantaMisericordia.stage) >= TotalSpainColonies())
	{		
		pchar.questTemp.SantaMisericordia.stage = 0;
		chref.city = SantaMisericordia_findColony(TotalSpainColonies());
	}
	else
	{
		chref.city = SantaMisericordia_findColony(sti(pchar.questTemp.SantaMisericordia.stage));
	}
	// При ПЧФ не заходим в Картахену
	if (CheckAttribute(pchar, "questTemp.Mtraxx"))
	{
		if (pchar.questTemp.Mtraxx != "fail" && pchar.questTemp.Mtraxx != "fail_end" && pchar.questTemp.Mtraxx != "full_complete" && pchar.questTemp.Mtraxx != "full_complete_end")
		{
			if(SantaMisericordia_findColony(sti(pchar.questTemp.SantaMisericordia.stage)+1) == "Cartahena")
			{
				pchar.questTemp.SantaMisericordia.stage = sti(pchar.questTemp.SantaMisericordia.stage) + 1;
				Log_testInfo("Капитан ГАЛЕОНА ПРОПУСТИЛ КАРТАХЕНУ направился в колонию: "+SantaMisericordia_findColony(sti(pchar.questTemp.SantaMisericordia.stage)+1));
			}
		}
	}
	// при НСО не заходим на Тринидад
	if (CheckAttribute(pchar, "questTemp.Patria"))
	{
		if (pchar.questTemp.Patria != "end" && pchar.questTemp.Patria != "fail")
		{
			if(SantaMisericordia_findColony(sti(pchar.questTemp.SantaMisericordia.stage)+1) == "PortSpein")
			{
				pchar.questTemp.SantaMisericordia.stage = sti(pchar.questTemp.SantaMisericordia.stage) + 1;
				Log_testInfo("Капитан ГАЛЕОНА ПРОПУСТИЛ ТРИНИДАД направился в колонию: "+SantaMisericordia_findColony(sti(pchar.questTemp.SantaMisericordia.stage)+1));
			}
		}
	}
	
	chref.quest.targetCity = SantaMisericordia_findColony(sti(pchar.questTemp.SantaMisericordia.stage)+1);
	Log_testInfo("Капитан ГАЛЕОНА направился в колонию: "+chref.quest.targetCity + " из колонии : "+chref.city);
	chref.mapEnc.type = "trade";
	chref.mapEnc.worldMapShip = "galeon_sm";
	chref.mapEnc.Name = GetConvertStr("Ship_Name", LangFile);
	Map_CreateTrader(chref.city, chref.quest.targetCity, chref.id, 1000);
	
	//убираем ограничения в колонии, где находился ревизор
	pchar.questTemp.SantaMisericordia.ColonyZapret = "";
	//капитан клон исчезает
	if (CharacterIsAlive("SantaMisericordia_clone_church"))
	{
		sld = CharacterFromID("SantaMisericordia_clone_church");
		sld.lifeday = 0;
	}
	if (CharacterIsAlive("SantaMisericordia_clone_city"))
	{
		sld = CharacterFromID("SantaMisericordia_clone_city");
		sld.lifeday = 0;
	}
	if (CharacterIsAlive("SantaMisericordia_clone_guber"))
	{
		sld = CharacterFromID("SantaMisericordia_clone_guber");
		sld.lifeday = 0;
	}
	//губернатор возвращается на место
	sld = CharacterFromID(pchar.questTemp.SantaMisericordia.colony + "_Mayor");
	DeleteAttribute(sld, "quest.SantaMisericordia");
	LAi_SetHuberType(sld);
	ChangeCharacterAddressGroup(sld, pchar.questTemp.SantaMisericordia.colony + "_townhall", "sit", "sit1");
	//контрабандист
	sld = CharacterFromID(pchar.questTemp.SantaMisericordia.colony + "_Smuggler");
	DeleteAttribute(sld, "quest.SantaMisericordia");
	//бордель
	if (CharacterIsAlive(pchar.questTemp.SantaMisericordia.colony + "_Hostess"))
	{
		sld = CharacterFromID(pchar.questTemp.SantaMisericordia.colony + "_Hostess");
		DeleteAttribute(sld, "quest.SantaMisericordia");
		LAi_CharacterEnableDialog(sld);
	}
}

void CheckSantaMisericordia()
{
	if(CharacterIsAlive("SantaMisericordia_cap"))
	{
		ref sld = CharacterFromID("SantaMisericordia_cap")
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
				if(CheckAttribute(enc, "quest.chrID") && enc.quest.chrID == "SantaMisericordia_cap")
				{
					bAtMap = true;
				}
			}
			// на карте нет, но и атрибут "в порту" отсутствует
			if(!bAtMap)
			{
				SantaMisericordia_ToCity("SantaMisericordia_cap");
			}
			else
			{
				if(CheckQuestCondition("SantaMisericordia_MapRelease"))
				{
					Map_ReleaseQuestEncounter("SantaMisericordia_cap");
				}
				else
				{
					SetFunctionTimerCondition("SantaMisericordia_MapRelease", 0, 0, 31, false);
				}
			}
		}
	}
}

void SantaMisericordia_MapRelease(string qName)
{
	
}

void SantaMisericordia_fromMapBattle(string sChar)
{
	if(!GetDLCenabled(DLC_APPID_4)) return;
	if(!CharacterIsAlive("SantaMisericordia_cap")) return;
	pchar.questTemp.SantaMisericordia.AttackFromMap = true;
	ref sld = characterFromId("SantaMisericordia_cap");
	sld.AlwaysEnemy = true;
	//Islands[FindIsland(worldMap.island)].storm = true;
	//pchar.questTemp.SantaMisericordia_stormLocation = worldMap.island;
	pchar.quest.SantaMisericordia_SeaExitDS.win_condition.l1			= "EnterToSea";           	
    pchar.quest.SantaMisericordia_SeaExitDS.function    				= "SantaMisericordia_SeaExitDS";
}

void SantaMisericordia_SeaExitDS(string sQuest)
{
	pchar.quest.SantaMisericordia_DelStorm.win_condition.l1 = "MapEnter";
	pchar.quest.SantaMisericordia_DelStorm.function = "SantaMisericordia_DelStorm";
}

void SantaMisericordia_DelStorm(string sQuest)
{
	
	/* if(CheckAttribute(pchar,"questTemp.SantaMisericordia_stormLocation"))
	{
		if(CheckAttribute(&Islands[FindIsland(pchar.questTemp.SantaMisericordia_stormLocation)],"storm"))
		{
			log_testinfo("Удаляем шторм");
			DeleteAttribute(&Islands[FindIsland(pchar.questTemp.SantaMisericordia_stormLocation)],"storm");
			DeleteAttribute(pchar,"questTemp.SantaMisericordia_stormLocation");
		}
	} */
	if(CheckAttribute(pchar, "questTemp.SantaMisericordia.AttackFromMap"))
		DeleteAttribute(pchar, "questTemp.SantaMisericordia.AttackFromMap");
	if(CheckAttribute(pchar, "questTemp.SantaMisericordia.Branders"))
		DeleteAttribute(pchar, "questTemp.SantaMisericordia.Branders");
	if(CheckAttribute(pchar, "questTemp.SantaMisericordia.ChangeWhr"))
		DeleteAttribute(pchar, "questTemp.SantaMisericordia.ChangeWhr");
	if(CheckAttribute(pchar, "questTemp.SantaMisericordia.mines"))
		DeleteAttribute(pchar, "questTemp.SantaMisericordia.mines");
	if(CheckAttribute(pchar, "questTemp.SantaMisericordia.Detonate"))
		DeleteAttribute(pchar, "questTemp.SantaMisericordia.Detonate");
	/* ref sld = characterFromId("SantaMisericordia_cap");
	if(CheckAttribute(sld, "AlwaysEnemy"))
		DeleteAttribute(sld, "AlwaysEnemy"); */
}

void SantaMisericordia_SpawnBranders()
{
	pchar.questTemp.SantaMisericordia.Branders = true;
	ref sld = GetCharacter(NPC_GenerateCharacter("SantaMisericordia_Brander", "mercen_23", "man", "man", 30, SPAIN, -1, true, "quest"));
	//LAi_SetImmortal(sld, true);
	FantomMakeCoolSailor(sld, SHIP_TARTANE, "", CANNON_TYPE_CANNON_LBS3, 100, 10, 10);
	SetShipSkill(sld, 30, 10, 10, 10, 100, 10, 10, 10, 10);
	UpgradeShipParameter(sld, "SpeedRate");
	UpgradeShipParameter(sld, "Capacity");
	UpgradeShipParameter(sld, "WindAgainstSpeed");
	UpgradeShipParameter(sld, "TurnRate");
	
	ref ship = GetRealShip(sld.ship.type);
	
	sld.ShipTaskLock = true;
	sld.Abordage.Enable = false;
	sld.FixedShipSpeed = 20.0;
	DeleteAttribute(sld, "SinkTenPercent");
	NullCharacterGoods(sld);
	SetCharacterGoods(sld, GOOD_POWDER, 200);
	Group_AddCharacter("SantaMisericordia_Brander", "SantaMisericordia_Brander");
	Group_SetGroupCommander("SantaMisericordia_Brander", "SantaMisericordia_Brander");
	Sea_LoginGroupCurrentSea("SantaMisericordia_Brander");
	SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);
	Ship_SetTaskBrander(PRIMARY_TASK, sti(sld.index), GetMainCharacterIndex());
	log_testinfo("Запущен брандер 1");
	DoQuestFunctionDelay("SantaMisericordia_SpawnBrander2", 10.0);
}
void SantaMisericordia_SpawnBrander2(string sQuest)
{
	ref sld = GetCharacter(NPC_GenerateCharacter("SantaMisericordia_Brander2", "mercen_23", "man", "man", 30, SPAIN, -1, true, "quest"));
	//LAi_SetImmortal(sld, true);
	FantomMakeCoolSailor(sld, SHIP_TARTANE, "", CANNON_TYPE_CANNON_LBS3, 100, 10, 10);
	SetShipSkill(sld, 30, 10, 10, 10, 100, 10, 10, 10, 10);
	UpgradeShipParameter(sld, "SpeedRate");
	UpgradeShipParameter(sld, "Capacity");
	UpgradeShipParameter(sld, "WindAgainstSpeed");
	UpgradeShipParameter(sld, "TurnRate");
	
	ref ship = GetRealShip(sld.ship.type);
	
	sld.ShipTaskLock = true;
	sld.Abordage.Enable = false;
	sld.FixedShipSpeed = 20.0;
	DeleteAttribute(sld, "SinkTenPercent");
	NullCharacterGoods(sld);
	SetCharacterGoods(sld, GOOD_POWDER, 200);
	Group_AddCharacter("SantaMisericordia_Brander2", "SantaMisericordia_Brander2");
	Group_SetGroupCommander("SantaMisericordia_Brander2", "SantaMisericordia_Brander2");
	Sea_LoginGroupCurrentSea("SantaMisericordia_Brander2");
	SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);
	Ship_SetTaskBrander(PRIMARY_TASK, sti(sld.index), GetMainCharacterIndex());
	log_testinfo("Запущен брандер 2");
}

void SantaMisericordia_ChangeWhr()
{
	return;
	pchar.questTemp.SantaMisericordia.ChangeWhr = true;
	DeleteAttribute(&Islands[FindIsland(pchar.questTemp.SantaMisericordia_stormLocation)],"storm");
	Seafoam.storm = "false";
	WeatherParams.Rain.Duration  = 1000000; 				// затяжной дождь
	WeatherParams.Rain.ThisDay 		= true;
    WeatherParams.Rain.StartTime 	= MakeInt(GetHour());
	DeleteAttribute(&WeatherParams,"Storm");
	Whr_UpdateWeather();
	//PauseAllSounds();
	//ResetSound();
	//SetSchemeAfterFlagRise();
	log_testinfo("Убираем шторм");
}

void SantaMisericordia_Mines(ref chRef)
{
	log_testinfo("Спамим мины");
	pchar.questTemp.SantaMisericordia.mines = 1;
	AISeaGoods_AddGood(chRef, "powder" + 1, "barrel", 600.0, 1);
    PlaySound("Ships\jakor_002.wav");
    chRef.Tmp.SpeedRecall = 0;  // чтоб пересчитались скорость и маневр
	DoQuestFunctionDelay("SantaMisericordia_NextMine", 5.0);
}

void SantaMisericordia_NextMine(string sQuest)
{
	if(!CharacterIsAlive("SantaMisericordia_cap")) return;
	if(sti(pchar.questTemp.SantaMisericordia.mines) > 30) return;
	pchar.questTemp.SantaMisericordia.mines = sti(pchar.questTemp.SantaMisericordia.mines)+1;
	Log_TestInfo("Мина номер: "+sti(pchar.questTemp.SantaMisericordia.mines));
	ref chRef = characterFromId("SantaMisericordia_cap");
	AISeaGoods_AddGood(chRef, "powder" + 1, "barrel", 600.0, 1);
    PlaySound("Ships\jakor_002.wav");
    chRef.Tmp.SpeedRecall = 0;  // чтоб пересчитались скорость и маневр
	DoQuestFunctionDelay("SantaMisericordia_NextMineNext", 5.0);
}

void SantaMisericordia_NextMineNext(string sQuest)
{
	if(!CharacterIsAlive("SantaMisericordia_cap")) return;
	if(sti(pchar.questTemp.SantaMisericordia.mines) > 30) return;
	pchar.questTemp.SantaMisericordia.mines = sti(pchar.questTemp.SantaMisericordia.mines)+1;
	Log_TestInfo("Мина номер: "+sti(pchar.questTemp.SantaMisericordia.mines));
	ref chRef = characterFromId("SantaMisericordia_cap");
	AISeaGoods_AddGood(chRef, "powder" + 1, "barrel", 600.0, 1);
    PlaySound("Ships\jakor_002.wav");
    chRef.Tmp.SpeedRecall = 0;  // чтоб пересчитались скорость и маневр
	DoQuestFunctionDelay("SantaMisericordia_NextMine", 5.0);
}

void SantaMisericordia_SpainReputation()
{
	bQuestDisableMapEnter = true;
	pchar.questTemp.SantaMisericordia.SpainReputation = true;
	ChangeCharacterNationReputation(pchar, SPAIN, -100);
}

void Alamida_abordage_OfficerPodhodit(string sQuest)
{
	if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && CharacterIsAlive("Helena") && CheckPassengerInCharacter(pchar, "Helena"))
	{
		sld = GetCharacter(CreateCharacterClone(CharacterFromID("Helena"), 0));
		sld.id = "Helena_Clone";
		ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
		sld.Dialog.FileName = "Quest\ShipsPack\SantaMisericordia_dialog.c";
		sld.dialog.currentnode = "Alamida_Helena";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		return;
	}
	if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && CharacterIsAlive("Mary") && CheckPassengerInCharacter(pchar, "Mary"))
	{
		sld = GetCharacter(CreateCharacterClone(CharacterFromID("Mary"), 0));
		sld.id = "Mary_Clone";
		ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
		sld.Dialog.FileName = "Quest\ShipsPack\SantaMisericordia_dialog.c";
		sld.dialog.currentnode = "Alamida_Mary";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		return;
	}
	if (CharacterIsAlive("Irons") && CheckPassengerInCharacter(pchar, "Irons"))
	{
		sld = GetCharacter(CreateCharacterClone(CharacterFromID("Irons"), 0));
		sld.id = "Irons_Clone";
		//sld.MusketerDistance = 10;
		ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
		sld.Dialog.FileName = "Quest\ShipsPack\SantaMisericordia_dialog.c";
		sld.dialog.currentnode = "Alamida_Tommi";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		return;
	}
	if (CharacterIsAlive("Tichingitu") && CheckPassengerInCharacter(pchar, "Tichingitu"))
	{
		sld = GetCharacter(CreateCharacterClone(CharacterFromID("Tichingitu"), 0));
		sld.id = "Tichingitu_Clone";
		//sld.MusketerDistance = 10;
		ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
		sld.Dialog.FileName = "Quest\ShipsPack\SantaMisericordia_dialog.c";
		sld.dialog.currentnode = "Alamida_Tichingitu";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		return;
	}
	LAi_EnableReload();
	Log_SetActiveAction("Reload");
}

void SantaMisericordia_ZapisiJurnala(string sQuest)
{
	TakeItemFromCharacter(pchar, "Reserve_item_02");
	AddQuestRecordInfo("ChroniclesMadness", "1");
	
	PChar.quest.SantaMisericordia_HavanaCrypt.win_condition.l1 = "location";
	PChar.quest.SantaMisericordia_HavanaCrypt.win_condition.l1.location = "Havana_CryptBig2";
	PChar.quest.SantaMisericordia_HavanaCrypt.function = "SantaMisericordia_HavanaCrypt";
}

void SantaMisericordia_HavanaCrypt(string sQuest)
{
	chrDisableReloadToLocation = true;
	DoQuestFunctionDelay("SantaMisericordia_HavanaCrypt_2", 3.0);
}

void SantaMisericordia_HavanaCrypt_2(string sQuest)
{
	LAi_FadeLong("", "");
	DoQuestFunctionDelay("SantaMisericordia_HavanaCrypt_3", 1.0);
	LAi_SetActorType(pchar);
}

void SantaMisericordia_HavanaCrypt_3(string sQuest)
{
	StartQuestMovie(true, false, true);
	TeleportCharacterToPosAy(pchar, -4.15, 2.90, -4.91, 1.50);
	//locCameraFromToPos(-1.08, 4.72, -4.57, true, -4.93, 2.20, -5.38);
	locCameraFromToPos(-0.82, 4.64, -4.19, true, -4.13, 2.36, -5.24);
	DoQuestFunctionDelay("SantaMisericordia_HavanaCrypt_4", 0.5);
	LAi_SetActorType(pchar);
	//LAi_ActorAnimation(pchar, "church_stay_5", "1", 5.0);
	//LAi_ActorAnimation(pchar, "barmen_look_around", "1", 5.0);
}

void SantaMisericordia_HavanaCrypt_4(string sQuest)
{
	DoQuestFunctionDelay("SantaMisericordia_HavanaCrypt_5", 5.0);
	LAi_ActorAnimation(pchar, "idle_5", "1", 5.0);
}

void SantaMisericordia_HavanaCrypt_5(string sQuest)
{
	DoQuestFunctionDelay("SantaMisericordia_HavanaCrypt_6", 4.0);
	DoQuestFunctionDelay("SantaMisericordia_HavanaCrypt_5_1", 1.0);
	LAi_ActorAnimation(pchar, "barman_look_around", "1", 7.0);
}

void SantaMisericordia_HavanaCrypt_5_1(string sQuest)
{
	PlaySound("Ships\snasti_skrp_008.wav");
	PlaySound("Ships\snasti_skrp_008.wav");
	DoQuestFunctionDelay("SantaMisericordia_HavanaCrypt_5_2", 1.5);
}

void SantaMisericordia_HavanaCrypt_5_2(string sQuest)
{
	PlaySound("interface\important_item.wav");
	GiveItem2Character(PChar, "Talisman17");
	notification(GetConvertStr("Took_LiberMisericordiae", LangFile), "BoxPlus");
}

void SantaMisericordia_HavanaCrypt_6(string sQuest)
{
	if (CharacterIsAlive("DiegoDeLanda"))
	{
		sld = CharacterFromID("DiegoDeLanda");
		ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload2");
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, pchar, "", -1);
		LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
		pchar.questTemp.ISawDiegoDeLanda = sti(pchar.questTemp.ISawDiegoDeLanda) + 1; // встретил Диего де Ланда
		pchar.questTemp.DiegoDeLanda_SantaMisericordia = true;
		
		PlaySound("ambient\jail\jail_door2.wav");
		DoQuestFunctionDelay("SantaMisericordia_HavanaCrypt_7", 5.0);
	}
	else DiegoDeLanda_Leaving_End();
}

void SantaMisericordia_HavanaCrypt_7(string sQuest)
{
	LAi_FadeLong("", "");
	DoQuestFunctionDelay("SantaMisericordia_HavanaCrypt_8", 1.0);
	
}

void SantaMisericordia_HavanaCrypt_8(string sQuest)
{
	LAi_SetStayType(pchar);
	TeleportCharacterToPosAy(pchar, -4.15, 2.90, -4.91, -1.50);
	sld = CharacterFromID("DiegoDeLanda");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 0, 0);
	locCameraFromToPos(-3.06, 4.79, -4.29, true, -5.44, 2.70, -4.88);
}

void SantaMisericordia_Pobeda(string sQuest)
{
	//ачивки
	Achievment_Set("ach_CL_136");
	if (sti(pchar.rank) < 15) Achievment_Set("ach_CL_137");
	bQuestDisableMapEnter = false;
	
	//чистим всё
	if (CharacterIsAlive("SantaMisericordia_clone_church"))
	{
		sld = CharacterFromID("SantaMisericordia_clone_church");
		sld.lifeday = 0;
	}
	if (CharacterIsAlive("SantaMisericordia_clone_city"))
	{
		sld = CharacterFromID("SantaMisericordia_clone_city");
		sld.lifeday = 0;
	}
	if (CharacterIsAlive("SantaMisericordia_clone_guber"))
	{
		sld = CharacterFromID("SantaMisericordia_clone_guber");
		sld.lifeday = 0;
	}
	DeleteQuestCondition("SantaMisericordia_Sluhi");
	DeleteQuestCondition("SantaMisericordia_ToMap");
	//губернатор возвращается на место
	sld = CharacterFromID(pchar.questTemp.SantaMisericordia.colony + "_Mayor");
	DeleteAttribute(sld, "quest.SantaMisericordia");
	LAi_SetHuberType(sld);
	ChangeCharacterAddressGroup(sld, pchar.questTemp.SantaMisericordia.colony + "_townhall", "sit", "sit1");
	//контрабандист
	sld = CharacterFromID(pchar.questTemp.SantaMisericordia.colony + "_Smuggler");
	DeleteAttribute(sld, "quest.SantaMisericordia");
	//бордель
	if (CharacterIsAlive(pchar.questTemp.SantaMisericordia.colony + "_Hostess"))
	{
		sld = CharacterFromID(pchar.questTemp.SantaMisericordia.colony + "_Hostess");
		DeleteAttribute(sld, "quest.SantaMisericordia");
		LAi_CharacterEnableDialog(sld);
	}
}

bool ach139condition()
{
	if(sti(Pchar.Ship.Type) == SHIP_NOTUSED) return false;

	if (sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_GALEON_SM && IsEquipCharacterByItem(pchar, "lacrima_patris") && IsCharacterEquippedArtefact(pchar, "Talisman17"))
	{
		if(CheckAttribute(pchar,"equip_item.slot1") && pchar.equip_item.slot1 != SLOT_NOT_USED && isMonkArtefact(pchar.equip_item.slot1)
		&& CheckAttribute(pchar,"equip_item.slot2") && pchar.equip_item.slot2 != SLOT_NOT_USED && isMonkArtefact(pchar.equip_item.slot2)
		&& CheckAttribute(pchar,"equip_item.slot3") && pchar.equip_item.slot3 != SLOT_NOT_USED && isMonkArtefact(pchar.equip_item.slot3))
		return true;
	}
	return false;
}

//=================================================================
//======================кейсы из quests_reaction===================
//=================================================================
bool Santa_Misericordia_QuestComplete(string sQuestName, string qname)
{
	ref sld, chr, npchar, rloc, shTo;
	aref arOldMapPos, arAll, arPass;
	int     iTemp, i, n, ShipType, Rank, idx; // нужно для вычислений любых целых (нации)
    float locx, locy, locz, fTemp;
	string  attrName, Model, Blade, Gun, sTemp, sQuestTown, sQuestTitle; // любые строки для вычислений
	bool   bOk;
	
	bool condition = true;
	
	// ==> Квест "Святое Милосердие"
	if (sQuestName == "SantaMisericordia_TrirdRound") {
		DoQuestCheckDelay("hide_weapon", 1.2);
		sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
		sld.Dialog.FileName = "Quest\ShipsPack\SantaMisericordia_dialog.c";
		sld.Dialog.CurrentNode = "Alamida_abordage_TrirdRound";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	
	else if (sQuestName == "SantaMisericordia_Molitva") {
		DoQuestCheckDelay("hide_weapon", 1.2);
		sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
		sld.Dialog.FileName = "Quest\ShipsPack\SantaMisericordia_dialog.c";
		sld.Dialog.CurrentNode = "Alamida_abordage_Molitva";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	
	else if (sQuestName == "SantaMisericordia_CanLeaveCauta") {
		LAi_EnableReload();
		Log_SetActiveAction("Reload");
	}
	
	else if (sQuestName == "SantaMisericordia_Final") {
		PlaySound("ambient\jail\jail_door2.wav");
		LAi_FadeLong("SantaMisericordia_Final2", "");
	}
	
	else if (sQuestName == "SantaMisericordia_Final2") {
		Achievment_Set("ach_CL_138");
		chrDisableReloadToLocation = false;
		EndQuestMovie();
		locCameraSleep(false);
		locCameraToPos(-2.09, 5.61, -4.92, true);
		locCameraTarget(PChar);
		locCameraFollow();
		LAi_SetPlayerType(pchar);
		if (sti(pchar.questTemp.ISawDiegoDeLanda) == 2)
		{
			SetQuestHeader("SixCaptains");
			AddQuestRecord("SixCaptains", "1");
			AddQuestUserData("SixCaptains", "sSex", GetSexPhrase("","а")); 
			CloseQuestHeader("SixCaptains");
		}
	}
	
	else if (sQuestName == "SantaMisericordia_Sluhi") {
		SetTimerCondition("SantaMisericordia_Sluhi", 0, 4, 0, false);
		sld = CharacterFromID(""+pchar.questTemp.SantaMisericordia.colony+"_Mayor");
		
		string rumour1 = GetConvertStr("City_Rum11", LangFile);
		string rumour2 = GetConvertStr("City_Rum12", LangFile);
		string rumour3 = GetConvertStr("City_Rum13", LangFile);
		string rumour4 = GetConvertStr("City_Rum14", LangFile);
		string rumour5 = GetConvertStr("City_Rum15", LangFile);
		string rumour6 = GetConvertStr("City_Rum16", LangFile);
		string rumour7 = GetConvertStr("City_Rum17", LangFile);
		string rumour8 = GetConvertStr("City_Rum18", LangFile);
		string rumour9 = GetConvertStr("City_Rum19", LangFile);
		string rumour10 = GetConvertStr("City_Rum20", LangFile);
		string rumour11 = GetConvertStr("City_Rum21", LangFile);
		string rumour12 = GetConvertStr("City_Rum22", LangFile);
		string rumour13 = GetConvertStr("City_Rum23", LangFile);
		
		AddSimpleRumour(LinkRandPhrase(rumour1+XI_ConvertString("Colony"+pchar.questTemp.SantaMisericordia.colony)+rumour2, rumour3+XI_ConvertString("Colony"+pchar.questTemp.SantaMisericordia.colony+"Acc")+rumour4, rumour5+XI_ConvertString("Colony"+pchar.questTemp.SantaMisericordia.colony+"Gen")+rumour6+GetFullName(sld)+rumour7), SPAIN, 30, 1);
		
		AddSimpleRumourAllNationsWithException(LinkRandPhrase(rumour8+XI_ConvertString("Colony"+pchar.questTemp.SantaMisericordia.colony+"Voc")+rumour9, rumour10+XI_ConvertString("Colony"+pchar.questTemp.SantaMisericordia.colony+"Voc")+rumour11, rumour12+XI_ConvertString("Colony"+pchar.questTemp.SantaMisericordia.colony+"Gen")+rumour13), SPAIN, 30, 1);
	}
	// <== Квест "Святое Милосердие"
	else
	{
		condition = false;
	}
	
	return condition;
}