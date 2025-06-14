
object TreasureTiers[16]; // Пуллы (тиры); 0-ой это SingleTreasures + QuestSlot + Флаги проверок

extern void InitTreasureTiers();
extern void InitTreasureTiers_Additions(bool SandBoxMode);

void TreasureTiersInit(bool SandBoxMode)
{
	if(LoadSegment("scripts\Treasure_Init.c"))
	{
		InitTreasureTiers();
        InitTreasureTiers_Additions(SandBoxMode)
		UnloadSegment("scripts\Treasure_Init.c");
	}
}

string GetIslandForTreasure()
{
	int iNum, m;
	ref Itm;
	aref arDest, arImt;
	string sAttr;
	
	m = 0;
	string sCurIsland = GetCharacterCurrentIslandId(pchar);
	makearef(arDest, NullCharacter.TravelMap.Islands);
	iNum = GetAttributesNum(arDest);
	
	string sArray[50]; // динамические массивы в Шторме не организуешь :(
	for (int i = 0; i<iNum; i++)
	{
		arImt = GetAttributeN(arDest, i);
		sAttr = GetAttributeName(arImt);
		if(CheckAttribute(&NullCharacter,"TravelMap.Islands." + sAttr + ".Treasure"))
		{
			if(sCurIsland == sAttr || CheckTreasureMaps(sAttr)) continue;
			else
			{
				sArray[m] = sAttr;
				m++;		
			}	
		}
	}
	m = rand(m-1);
	return sArray[m];
}

bool CheckTreasureMaps(string sIsland)
{
	ref Itm;
	
	if(GetCharacterItem(pchar,"mapQuest") > 0)
	{
		itm = ItemsFromID("mapQuest");
		if(CheckAttribute(itm, "MapIslId") && itm.MapIslId == sIsland) return true;
	}		
	if(GetCharacterItem(pchar,"map_full") > 0)
	{
		itm = ItemsFromID("map_full");
		if(CheckAttribute(itm, "MapIslId") && itm.MapIslId == sIsland) return true;
	}
	return false;
}

string GetLocationForTreasure(string island)
{
    int iNum;
	aref arDest, arImt;
	string sAttr;

	makearef(arDest, NullCharacter.TravelMap.Islands.(island).Treasure);
	iNum = GetAttributesNum(arDest);
    iNum = rand(iNum-1);
    
    arImt = GetAttributeN(arDest, iNum);
	return GetAttributeName(arImt);
}

string GetBoxForTreasure(string island, string location)
{
    int iNum;
	aref arDest, arImt;
	string sAttr;

	makearef(arDest, NullCharacter.TravelMap.Islands.(island).Treasure.(location));
	iNum = GetAttributesNum(arDest);
    iNum = rand(iNum-1);
    
    arImt = GetAttributeN(arDest, iNum);
	return GetAttributeValue(arImt);
}

// TO_DO: DEL
void GenerateAdmiralMapsTreasure(ref item, int abl)
{
	if (!CheckAttribute(pchar, "questTemp.AdmiralMap")) return;
	if (rand(abl) == 1)
	{
		string amap = SelectAdmiralMaps();
		if (amap != "") item.BoxTreasure.(amap)	= 1;
	}
}

void FillMapForTreasure(ref item)
{
    item.MapIslId   = GetIslandForTreasure();
    item.MapLocId   = GetLocationForTreasure(item.MapIslId);
    item.MapBoxId   = GetBoxForTreasure(item.MapIslId, item.MapLocId);
    DeleteAttribute(item, "BoxTreasure");

    if (!CheckAttribute(Pchar, "GenQuest.TreasureBuild") && rand(15) == 1)
    {
        item.MapTypeIdx = -1; // Подделка 6.25%
    }
    else
    {
        // Legendary edition - Новая система кладов
        FillBoxForTreasure(item); // Всё тут
        DeleteAttribute(Pchar, "GenQuest.TreasureBuild");
        Pchar.quest.SetTreasureFromMap.win_condition.l1          = "location";
        Pchar.quest.SetTreasureFromMap.win_condition.l1.location = item.MapLocId;
        Pchar.quest.SetTreasureFromMap.win_condition             = "SetTreasureFromMap";
		Pchar.GenQuest.Treasure.Vario = rand(5); // Определяем событие (33% скип)
		locations[FindLocation(item.MapLocId)].DisableEncounters = true;
    }
}

int GetTresuareTier(int iTier)
{
    aref Lottery;
    makearef(Lottery, LTR.TresuareMap);
    DeleteAttribute(Lottery, "");

    string sTemp = "T" + iTier;
    Lottery.(sTemp).weight = LTR.TresuareMapTier.(sTemp).weight;
    if(iTier != 1)
    {
        sTemp = "T" + (iTier-1);
        Lottery.(sTemp).weight = LTR.TresuareMapTier.(sTemp).weight;
    }
    if(iTier != 15)
    {
        sTemp = "T" + (iTier+1);
        Lottery.(sTemp).weight = LTR.TresuareMapTier.(sTemp).weight;
    }

    sTemp = wrand("TresuareMap");
    CorrectWeightParameters("TresuareMapTier", sTemp, "Treasure");
    return sti(LTR.TresuareMapTier.(sTemp));
}

// Выбрать вещь и выбросить её из пулла
string GetRandEnabledItem(aref aTier, string sType)
{
    string sItem;
    aref aType, aItem;
    makearef(aType, aTier.(sType));
    int i, num = GetAttributesNum(aType);
    DeleteAttribute(&LTR, "RandItem"); //типа динамический массив
    for(i = 0; i < num; i++)
    {
        aItem = GetAttributeN(aType, i);
        if(GetAttributeValue(aItem) == "On")
        {
            sItem = i; //Safe moment
            LTR.RandItem.(sItem) = GetAttributeName(aItem);
        }
    }
    makearef(aItem, LTR.RandItem);
    int numItems = GetAttributesNum(aItem);

    // Ни одной вещи не нашлось, нужен ресет пулла
    if(numItems == 0)
    {
        for(i = 0; i < num; i++)
        {
            sItem = GetAttributeName(GetAttributeN(aType, i));
            for(int j = 1; j <= 15; j++)
            {
                if(CheckAttribute(&TreasureTiers[j], sType + "." + sItem))
                    TreasureTiers[j].(sType).(sItem) = "On";
            }
        }
        // Ещё раз рандомим
        return GetRandEnabledItem(aTier, sType);
    }

    // Рандомим и отключаем в тирах
    sItem = GetAttributeValue(GetAttributeN(aItem, rand(numItems-1)));
    if(!CheckAttribute(&TreasureTiers[0], sItem))
    {
        for(i = 1; i <= 15; i++)
        {
            if(CheckAttribute(&TreasureTiers[i], sType + "." + sItem))
                TreasureTiers[i].(sType).(sItem) = "Off";
        }
    }
    else
    {
        for(i = 1; i <= 15; i++)
        {
            DeleteAttribute(&TreasureTiers[i], sType + "." + sItem);
        }
        DeleteAttribute(&TreasureTiers[0], sItem);
    }

    return sItem;
}

void FillBoxForTreasure(ref item)
{
    int iTier = 0;
    aref aTier;

    if(!CheckAttribute(PChar, "Statistic.Treasure"))
        PChar.Statistic.Treasure = 0;

    // Определяем тир (15 отрезков в диапазоне от 3 до 692)
    iTier += GetCharacterSkill(PChar,SKILL_FORTUNE)*3;                //Везение (min 1)
    iTier += iClamp(0, 12, sti(PChar.Statistic.Treasure))*16;         //Количество найденных кладов
    if(CheckAttribute(PChar,"GenQuest.TreasureBuild")) iTier += 200;  //Сборная карта
    if(CheckCharacterPerk(PChar,"HT2")) iTier += MakeInt(iTier*0.15); //Счетовод
    iTier = iClamp(0, 14, iTier/47);    // Неполное частное от 0 до 14 (ниже +1 будет от 1 до 15)
    iTier = GetTresuareTier(iTier + 1); // Среди соседей взять рандомом по весу
    item.TreasureTier = iTier;          // Сохраним для ачивки и опыта
    SetMapDescribe(item, iTier);
    makearef(aTier, TreasureTiers[iTier]);

    // Заполняем
    int iBonus = 0;
    if(CheckCharacterPerk(PChar,"HT2")) iBonus = 25;
    FillBoxForNotes(item);                        //Записки
    FillBoxForQuest(item, iTier, iBonus);         //Квестовое
    FillBoxForEquip(item, aTier, iBonus, true);   //Экипировка
    FillBoxForJewelry(item, aTier, iBonus, true); //Ценности
    FillBoxForSpecial(item, aTier, iBonus, true); //Специальные предметы
}

void FillBoxForEquip(ref item, aref aTier, int iBonus, bool bOtherSlots)
{
    string itmName = GetRandEnabledItem(aTier, "Equip");
    if(IsGenerableItem(itmName)) itmName = GetGeneratedItem(itmName);
    item.BoxTreasure.(itmName) = 1; // Весь эквип выдаётся штучно
    if(bOtherSlots)
    {
        if(50 + iBonus > rand(99)) FillBoxForEquip(item, aTier, iBonus, false);
        if(25 + iBonus > rand(99)) FillBoxForEquip(item, aTier, iBonus, false);
    }
}

void FillBoxForJewelry(ref item, aref aTier, int iBonus, bool bOtherSlots)
{
    if(bOtherSlots)
    {
        // Золото в первый слот
        item.BoxTreasure.gold = sti(aTier.gold.min) + rand(sti(aTier.gold.dif));
        // Остальные четыре слота
        if(75 + iBonus > rand(99)) FillBoxForJewelry(item, aTier, iBonus, false);
        if(65 + iBonus > rand(99)) FillBoxForJewelry(item, aTier, iBonus, false);
        if(50 + iBonus > rand(99)) FillBoxForJewelry(item, aTier, iBonus, false);
        if(35 + iBonus > rand(99)) FillBoxForJewelry(item, aTier, iBonus, false);
    }
    else
    {
        string itmName = GetRandEnabledItem(aTier, "Jewelry");
        item.BoxTreasure.(itmName) = sti(aTier.Jewelry.(itmName).min) + rand(sti(aTier.Jewelry.(itmName).dif));
    }
}

void FillBoxForSpecial(ref item, aref aTier, int iBonus, bool bOtherSlots)
{
    string itmName = GetRandEnabledItem(aTier, "Special");
    if(itmName == "map" || itmName == "map_a") // Подбор карты
    {
        if(!SandBoxMode && !CheckAttribute(pchar, "questTemp.AdmiralMap"))
            itmName = "map"; // Пока нельзя

        bool bExcellent = (itmName == "map_a");
        int qMiss = MAPS_IN_ATLAS - sti(PChar.MapsAtlasCount); // Сколько на момент генерации не хватало обычных карт
        int qTy = sti(aTier.Special.(itmName).min) + rand(sti(aTier.Special.(itmName).dif));
        for(int i = 0; i < qTy; i++)
        {
            if(bExcellent)
            {
                itmName = SelectAdmiralMaps();
                if(itmName != "")
                {
                    TreasureTiers[0].map_a.(itmName) = ""; // Чтобы не генерило одинаковые адмиралки в клад
                    item.BoxTreasure.(itmName) = 1;
                }
                else
                {
                    bExcellent = false;
                    i = 0;
                    qTy = 1 + (qTy - i) * 2; // Адмиралки закончились, выдаём обычные в удвоенном количестве
                    if(qTy > 7) qTy = 7; // Но не более 6-ти (i начнёт с 1)
                }
            }
            else
            {
                itmName = SelectUsualMaps(item, &qMiss);
                if(CheckAttribute(item, "BoxTreasure." + itmName))
                    item.BoxTreasure.(itmName) = sti(item.BoxTreasure.(itmName)) + 1;
                else
                    item.BoxTreasure.(itmName) = 1;
            }
        }
        DeleteAttribute(&TreasureTiers[0], "map_a");
    }
    else
    {
        item.BoxTreasure.(itmName) = sti(aTier.Special.(itmName).min) + rand(sti(aTier.Special.(itmName).dif));
    }

    if(bOtherSlots)
    {
        // Половинку карты во второй слот
        if(25 + iBonus > rand(99))
        {
            if (GetCharacterItem(PChar, "map_part1") == 0)      item.BoxTreasure.map_part1 = 1;
            else if (GetCharacterItem(PChar, "map_part2") == 0) item.BoxTreasure.map_part2 = 1;
        }
        // Остальные три слота
        if(65 + iBonus > rand(99)) FillBoxForSpecial(item, aTier, iBonus, false);
        if(35 + iBonus > rand(99)) FillBoxForSpecial(item, aTier, iBonus, false);
        if(15 + iBonus > rand(99)) FillBoxForSpecial(item, aTier, iBonus, false);
    }
}

void FillBoxForNotes(ref item)
{
    aref aTreasureStories;
    makearef(aTreasureStories, pchar.questTemp.Treasure_Stories);
    string sNumb = GetRandomAttrName(aTreasureStories);
    if(sNumb != "error")
    {
        item.NoteNum = sNumb;
        item.BoxTreasure.treasure_note = 1;
    }
    else DeleteAttribute(item, "NoteNum");
}

// Вся логика выдачи у каждого квеста своя, это не общий пулл
// В нужном квесте в нужный момент пишется TreasureTiers[0].QuestSlot.attrName = sFuncName
// Эта функция должна быть в скриптах квеста с параметрами int iTier, int iBonus, ref item
// Не забыть по надобности (например, сразу же в той же функции или по завершению квеста) удалить QuestSlot.attrName атрибут
void FillBoxForQuest(ref item, int iTier, int iBonus)
{
    string func;
    aref aQuests;
    makearef(aQuests, TreasureTiers[0].QuestSlot);
    int num = GetAttributesNum(aQuests);
    // Обязательно идём сверху вниз! Если в каком-то вызове удалится один из атрибутов, то верхние перенумеруются
    for(int i = num - 1; i >= 0; i--)
    {
        func = GetAttributeValue(GetAttributeN(aQuests, i)); 
        call func(iTier, iBonus, item);
    }
}

void SetTreasureBoxFromMap()
{
    aref   item;
    ref    loc;
    string box;
    aref   arToBox;
    aref   arFromBox;

    if (GetCharacterItem(Pchar, "map_full") > 0)
    {
		notification(XI_ConvertString("TreasuresNear"), "Icollection");
        PlaySound("interface\notebook.wav");

        Items_FindItem("map_full", &item);
        int iTier = sti(item.TreasureTier);

        // Охотники за кладом - ОЗК (Пещера)
        switch (sti(pchar.GenQuest.Treasure.Vario))
        {
            case 0: Treasure_SetCaribWarrior();  break;
            case 1: Treasure_SetBandosWarrior(); break;  
        }
        // Джентельмены удачи - ДУ (Море) 50%
        if(rand(1)) TreasureHunterOnMap(rand(1), iTier);
        // ОЗК (Бухта)
        if( CheckAttribute(Pchar,"location.from_sea") )
        {
            if (rand(2) == 1) //33%
            {
                Pchar.quest.SetTreasureHunter.win_condition.l1          = "location";
                Pchar.quest.SetTreasureHunter.win_condition.l1.location = Pchar.location.from_sea;
                Pchar.quest.SetTreasureHunter.win_condition             = "";
                Pchar.quest.SetTreasureHunter.function = "SetTreasureHunter";
            }
        }

        box = item.MapBoxId;

        loc = &locations[FindLocation(item.MapLocId)];
        loc.(box).items = "";

        makearef(arToBox, loc.(box).items);
        makearef(arFromBox, item.BoxTreasure);
        CopyAttributes(arToBox, arFromBox);

        loc.(box) = Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear());
        loc.(box).Treasure = iTier; // признак сокровища в сундуке; запоминаем тир для ачивки и опыта
        if(CheckAttribute(item, "NoteNum"))
        {
            loc.(box).treasure_note = item.NoteNum; // Бокс запоминает номер
            DeleteAttribute(PChar, "questTemp.Treasure_Stories." + item.NoteNum); // История ушла из пула
            DeleteAttribute(item, "NoteNum");
        }

        DeleteAttribute(item, "MapIslId");
        TakeNItems(Pchar, "map_full", -1);
		if(IsEquipCharacterByArtefact(pchar, "talisman18"))
		{
			addArticlesBonus();
			notification(XI_ConvertString("TreasuresBlackwood"), "LogBook");
		}
    }
}

// Обычные ДУ
void TraderHunterOnMap(bool bCool)
{
    int Rank = sti(PChar.Rank);
    int iShips[4];
    int i, num, max, add = 5;
    iShips[0] = 0; // Рейдер
    iShips[1] = 0; // Универсал
    iShips[2] = 0; // Рейдер
    iShips[3] = 0; // Военник
    if(bCool) add = 8;

    if(Rank < 8)      {iShips[0] = 6; num = 1;}
    else if(Rank < 15){iShips[0] = 5+rand(1); iShips[1] = 5+rand(1); num = 2;}
    else if(Rank < 20){iShips[0] = 4+rand(1); iShips[1] = 4+rand(1); num = 2;}
    else if(Rank < 25){iShips[0] = 3+rand(1); iShips[1] = 3+rand(1); iShips[2] = 3+rand(1); num = 3;}
    else              {iShips[0] = 3+rand(1); iShips[1] = 3+rand(1); iShips[2] = 3+rand(1); iShips[3] = 2; num = 4;}

    max = num;
    i = GetCompanionQuantity(PChar);
    if(i > num) max += rand(i-num);

    ref  sld;
    string sCapId = "TraderHunter0";
    string sGroup = "Sea_" + sCapId + "1";
	Group_DeleteGroup(sGroup);
	Group_FindOrCreateGroup(sGroup);

    for (i = 1; i <= max; i++)
    {
        if(i > num) Rank = iShips[rand(num-1)];
        else Rank = iShips[i-1];
        sld = GetCharacter(NPC_GenerateCharacter(sCapId + i, "off_hol_2", "man", "man", sti(PChar.Rank) + add, PIRATE, 10, true, "hunter"));
        sld.GenShip.Class = Rank;
        if(i > num)
        {   // Вероятности на спеки специально равные (рейдеру не больше остальных), если у игрока большая эскадра
            if(num == 1) sld.GenShip.Spec = SHIP_SPEC_RAIDER;
            else if(num < 4) sld.GenShip.Spec = RandFromTwo(SHIP_SPEC_RAIDER, SHIP_SPEC_UNIVERSAL);
            else sld.GenShip.Spec = RandFromThree(SHIP_SPEC_RAIDER, SHIP_SPEC_UNIVERSAL, SHIP_SPEC_WAR);
        }
        else
        {
            if(i == 1 || i == 3) sld.GenShip.Spec = SHIP_SPEC_RAIDER;
            else if(i == 2) sld.GenShip.Spec = SHIP_SPEC_UNIVERSAL;
            else sld.GenShip.Spec = SHIP_SPEC_WAR;
        }
        SetShipHunter(sld);
        SetFantomParamHunter(sld); //крутые парни
        SetCaptanModelByEncType(sld, "war");
        sld.AlwaysEnemy = true;
        sld.DontRansackCaptain = true;
        sld.mapEnc.type = "war";
        sld.mapEnc.Name = XI_ConvertString("GentlemenOfFortune");
		sld.hunter = "pirate";
        Group_AddCharacter(sGroup, sCapId + i);
        if(Rank < 3 && rand(1)) SetRandGeraldSail(sld, PIRATE);
    }

    Group_SetGroupCommander(sGroup, sCapId+ "1");
    Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
    Group_LockTask(sGroup);
    if(bCool) Map_CreateCoolWarrior("", sCapId + "1", 8); // Быстрые
    else Map_CreateWarrior("", sCapId + "1", 8);
}

// ДУ - ОЗК
void TreasureHunterOnMap(bool bCool, int iTier)
{
    if (iTier < 2) return;
    int iShips[4];
    int i, num, max, add = 5;
    iShips[0] = 0; // Рейдер
    iShips[1] = 0; // Рейдер
    iShips[2] = 0; // Универсал
    iShips[3] = 0; // Военник
    if(bCool) add = 8;

    if(iTier < 4)      {iShips[0] = 6; num = 1;}
    else if(iTier < 6) {iShips[0] = 5+rand(1); num = 1;}
    else if(iTier < 8) {iShips[0] = 5+rand(1); iShips[1] = 5; num = 2;}
    else if(iTier < 10){iShips[0] = 4+rand(1); iShips[1] = 4+rand(1); num = 2;}
    else if(iTier < 12){iShips[0] = 3+rand(1); iShips[1] = 3+rand(1); iShips[2] = 3; num = 3;}
    else if(iTier < 14){iShips[0] = 2+rand(1); iShips[1] = 2+rand(1); iShips[2] = 2+rand(1); num = 3;}
    else               {iShips[0] = 2+rand(1); iShips[1] = 2+rand(1); iShips[2] = 2+rand(1); iShips[3] = 2+rand(1); num = 4;}

    max = num;
    i = GetCompanionQuantity(PChar);
    if(i > num) max += rand(i-num);

    ref  sld;
    string sCapId = "TreasureHunter0";
    string sGroup = "Sea_" + sCapId + "1";
	Group_DeleteGroup(sGroup);
	Group_FindOrCreateGroup(sGroup);

    for (i = 1; i <= max; i++)
    {
        if(i > num) iTier = iShips[rand(num-1)];
        else iTier = iShips[i-1];
        sld = GetCharacter(NPC_GenerateCharacter(sCapId + i, "off_hol_2", "man", "man", sti(PChar.rank) + add, PIRATE, 10, true, "hunter"));
        sld.GenShip.Class = iTier;
        if(i > num)
        {   // Вероятности на спеки специально равные (рейдеру не больше остальных), если у игрока большая эскадра
            if(num < 3) sld.GenShip.Spec = SHIP_SPEC_RAIDER;
            else if(num == 3) sld.GenShip.Spec = RandFromTwo(SHIP_SPEC_RAIDER, SHIP_SPEC_UNIVERSAL);
            else sld.GenShip.Spec = RandFromThree(SHIP_SPEC_RAIDER, SHIP_SPEC_UNIVERSAL, SHIP_SPEC_WAR);
        }
        else
        {
            if(i < 3) sld.GenShip.Spec = SHIP_SPEC_RAIDER;
            else if(i == 3) sld.GenShip.Spec = SHIP_SPEC_UNIVERSAL;
            else sld.GenShip.Spec = SHIP_SPEC_WAR;
        }
        SetShipHunter(sld);
        SetFantomParamHunter(sld); //крутые парни
        SetCaptanModelByEncType(sld, "war");
        sld.AlwaysEnemy = true;
        sld.DontRansackCaptain = true;
        sld.mapEnc.type = "war";
        sld.mapEnc.Name = XI_ConvertString("GentlemenOfFortune");
		sld.hunter = "pirate";
        Group_AddCharacter(sGroup, sCapId + i);
        if(iTier < 3 && rand(1)) SetRandGeraldSail(sld, PIRATE);
    }

    Group_SetGroupCommander(sGroup, sCapId+ "1");
    Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
    Group_LockTask(sGroup);
    if(bCool) Map_CreateCoolWarrior("", sCapId + "1", 8); // Быстрые
    else Map_CreateWarrior("", sCapId + "1", 8);
}

void SetTreasureHunter(string temp)
{
    int    j, i, k;
	string sTemp, sCapId;
	ref    sld;
	bool   ok;

	if (chrDisableReloadToLocation) return; // идёт некий другой квест с запретом выхода
	
    Pchar.GenQuest.Hunter2Pause = true;
    
    j = GetOfficersQuantity(Pchar) + 2;
    
	sCapId = "LandHunter0";
    sTemp = "LAND_HUNTER";
	ok = true;
	arrayNPCModelHow = 0;
    for (i = 1; i <= j; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter(sCapId + i, "off_hol_2", "man", "man", sti(PChar.rank) + 5, PIRATE, 0, true, "hunter"));
        SetFantomParamHunter(sld); //крутые парни
        sld.Dialog.CurrentNode = "TreasureHunter";
        sld.dialog.filename = "Hunter_dialog.c";
        sld.greeting = "hunter";
        sld.location = "none"; // вот где порылась собака!!!!!!!!!!!

        SetModelPirate(sld);
        k = 0;
		while (!CheckNPCModelUniq(sld) && k < 10)
		{
		    k++;
			SetModelPirate(sld);
		}
		arrayNPCModel[arrayNPCModelHow] = sld.model;
		arrayNPCModelHow++;
		
        LAi_SetActorTypeNoGroup(sld);
        LAi_SetCheckMinHP(sld, (LAi_GetCharacterHP(sld) - 1), false, "Battle_Hunters_Land");
        if (PlaceCharacter(sld, "goto", "random_must_be_near") == "" && i == 1) // fix если вдруг нет в локации
        {
            ok = false;
            break;
        }
        LAi_ActorFollow(sld, pchar, "", 8.0);
        //LAi_Actor2WaitDialog(sld, pchar); // ждать диалог, но бежать
        LAi_group_MoveCharacter(sld, sTemp);
    }

	LAi_group_SetRelation(sTemp, LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
	LAi_group_SetRelation(sTemp, LAI_GROUP_PLAYER_OWN, LAI_GROUP_NEITRAL);

	LAi_group_ClearAllTargets();
	LAi_SetFightModeForOfficers(false);
	if (ok)
    {
        PChar.HunterCost = makeint(sti(Pchar.money) / 5) + rand(20)*1000; //сразу генерим
        PChar.HunterCost.Qty = i;
        PChar.HunterCost.TempHunterType = "";
        sld = characterFromID(sCapId + "1");
        LAi_type_actor_Reset(sld);
        LAi_ActorDialog(sld, pchar, "", 4.0, 0);
		chrDisableReloadToLocation = true;
		DoQuestCheckDelay("OpenTheDoors", 5.0);
    }
}

ref SetFantomSkeletForts(string group, string locator, string enemygroup, string _type)
// _type = "GhostShipCrew"   _type = "ParamHunter"  _type = "none"
{
    string emodel;
    ref    Cr;

    emodel = GetRandSkelModel();

    Cr = LAi_CreateFantomCharacterEx(emodel, "man", group, locator);

    if (Cr.location.locator != "")
    {
		if (_type == "GhostShipCrew" || _type == "ParamHunter")
		{
			SetFantomParamHunter(Cr);
		}
		else
		{
		    SetFantomParam(Cr);
		}
		LAi_SetWarriorType(Cr);
	    LAi_group_MoveCharacter(Cr, enemygroup);
	    LAi_NoRebirthEnable(Cr); //не показывать убитых при входе в локацию
	    LAi_LoginInCaptureTown(Cr, true); // для записи игры
	    if (_type == "GhostShipCrew")
	    {
		    // возможно даёт вылеты от многих трупов Cr.DontClearDead = true;
		    Cr.GhostShipCrew = true;
	    }
    }
    return Cr;
}

string SelectUsualMaps(ref item, ref qMiss) // Выбор обычной неповторяющейся карты
{	
    string sMap = "";
    string map[MAPS_IN_ATLAS];
    map[0] = "map_jam";
    map[1] = "map_cayman";
    map[2] = "map_barbados";
    map[3] = "map_trinidad";
    map[4] = "map_Curacao";
    map[5] = "map_martiniqua";
    map[6] = "map_dominica";
    map[7] = "map_puerto";
    map[8] = "map_cuba";
    map[9] = "map_hisp";
    map[10] = "map_nevis";
    map[11] = "map_guad";
    map[12] = "map_antigua";
    map[13] = "map_TORTUGA";
    map[14] = "map_terks";
    map[15] = "map_sm";
    map[16] = "map_bermudas";
    map[17] = "map_beliz";
    map[18] = "map_santa";
    map[19] = "map_maine_1";
    map[20] = "map_maine_2";
    map[21] = "map_panama";
    map[22] = "map_cumana";

    string storeArray[MAPS_IN_ATLAS];
    int howStore = 0;
    string sTemp;

    if(qMiss > 0)
    {
        for (int i = 0; i < MAPS_IN_ATLAS; i++)
        {
            sTemp = map[i];
            if (!CheckMainHeroMap(sTemp) && !CheckAttribute(item, "BoxTreasure." + sTemp))
            {
                storeArray[howStore] = sTemp;
                howStore++;
            }
        }
        qMiss--;
    }
    else
        howStore = MAPS_IN_ATLAS; // У игрока на пару с текущим кладом имеются все карты, теперь можно рандомить любую

    if (howStore > 0)
        sMap = storeArray[rand(howStore - 1)];

    return sMap;
}

void SetMapDescribe(ref item, int iTier)
{
    iTier = 1 + ((iTier - 1) / 5); // 1 [1;5], 2 [6;10], 3 [11;15]

    // Описания для составных
    if(CheckAttribute(PChar, "GenQuest.TreasureBuild"))
    {
        item.MapTypeIdx = 9 + iTier; // 10, 11, 12
        return;
    }
    // Описания по тирам (shuffle bag)
    aref aDesc;
    string sTemp = "T" + iTier;
    makearef(aDesc, LTR.TresuareMapDescribe.(sTemp));
    if(GetAttributesNum(aDesc) == 0) // reload
    {
        aDesc.v1 = 1;
        aDesc.v2 = 2;
        aDesc.v3 = 3;
    }
    sTemp = GetRandomAttrName(aDesc);
    item.MapTypeIdx = (iTier - 1) * 3 + sti(aDesc.(sTemp)); // 123, 456, 789
    DeleteAttribute(aDesc, sTemp);
}

// Открыли записку из клада
void Treasure_Stories(string attr)
{
    DeleteAttribute(PChar, "Treasure_Stories_Read." + attr);
	PChar.questTemp.Treasure_Stories = sti(PChar.questTemp.Treasure_Stories) + 1;
	if(!GetAchievement("ach_CL_141") && sti(PChar.questTemp.Treasure_Stories) == 1)  Achievment_Set("ach_CL_141");
	if(!GetAchievement("ach_CL_142") && sti(PChar.questTemp.Treasure_Stories) == 32) Achievment_Set("ach_CL_142");
}

// Записка попала в инвентарь из клада
// Добавим её в последовательность прочтения, уберём атрибут с сундука
bool TreasureNotesHandler(aref arItm)
{
    if(!CheckAttribute(arItm, "curNumb")) return false;

    string attr = arItm.curNumb;
    PChar.Treasure_Stories_Read.(attr) = attr;
    ref loc = &Locations[FindLocation(arItm.curLoc)];
    attr = arItm.curBox;
    DeleteAttribute(loc, attr + ".treasure_note");
    return true;
}

void Treasure_SetCaribWarrior()
{
	chrDisableReloadToLocation = true;//закрыть локацию
	int iRank = 10+sti(pchar.rank)+makeint(MOD_SKILL_ENEMY_RATE)/2;
	for(int i=1; i<=4; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Treasure_carib_"+i, "canib_"+(rand(5)+1), "man", "man", iRank, PIRATE, 1, true, "native"));
		SetFantomParamFromRank(sld, iRank, true);
		sld.name = GetIndianName(MAN);
		sld.lastname = "";
		LAi_CharacterDisableDialog(sld);
		GetCharacterPos(pchar, &locx, &locy, &locz);
		ChangeCharacterAddressGroup(sld, pchar.location, "monsters", LAi_FindNearestFreeLocator("monsters", locx, locy, locz));
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
	}
}

void Treasure_SetBandosWarrior()
{
	chrDisableReloadToLocation = true;//закрыть локацию
	int iRank = 8+sti(pchar.rank)+makeint(MOD_SKILL_ENEMY_RATE)/2;
	for(int i=1; i<=4; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Treasure_bandos_"+i, "citiz_"+(rand(9)+41), "man", "man", iRank, PIRATE, 1, true, "marginal"));
		SetFantomParamFromRank(sld, iRank, true);
		LAi_CharacterDisableDialog(sld);
		GetCharacterPos(pchar, &locx, &locy, &locz);
		ChangeCharacterAddressGroup(sld, pchar.location, "monsters", LAi_FindNearestFreeLocator("monsters", locx, locy, locz));
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
	}
}

void Treasure_SetCaptainWarrior(string qName)
{
    ref loc = &Locations[FindLocation(pchar.location)];
    if(CheckAttribute(loc, "townsack")) return; //fix: Вдруг вышли не в джунгли, а, например, в мастерскую Алексуса?

	string model;
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE;
	chrDisableReloadToLocation = true;//закрыть локацию
	LAi_LocationFightDisable(loc, true);//запретить драться // patch-6
	for(int i=1; i<=4; i++)
	{
		model = "citiz_"+(rand(9)+51);
		if (i > 1) model = "mercen_"+(rand(29)+1);
		sld = GetCharacter(NPC_GenerateCharacter("Treasure_sailor_"+i, model, "man", "man", iRank, PIRATE, 1, true, "soldier"));
		SetFantomParamFromRank(sld, iRank, true);
		sld.Dialog.Filename = "Hunter_dialog.c";
		sld.Dialog.currentnode = "TreasureCaptain";
		sld.greeting = "hunter";
		if (i > 1) LAi_CharacterDisableDialog(sld);
		GetCharacterPos(pchar, &locx, &locy, &locz);
		ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindFarLocator("goto", locx, locy, locz));
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
}

void Treasure_SetOfficerWarrior(string qName)
{
    ref loc = &Locations[FindLocation(pchar.location)];
    if(CheckAttribute(loc, "townsack")) return; //fix: Вдруг вышли не в джунгли, а, например, в мастерскую Алексуса?

    int iNation = PIRATE;
	string sTemp = GetCityNameByIsland(Pchar.curIslandId);
    if(sTemp != "none")   iNation = sti(colonies[FindColony(sTemp)].nation);
	if(iNation == PIRATE) iNation = hrand(NON_PIRATES, Pchar.curIslandId);

	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE;
	chrDisableReloadToLocation = true;//закрыть локацию
	LAi_LocationFightDisable(loc, true);//запретить драться // patch-6
	for(int i=1; i<=4; i++)
	{
		sTemp = "off_"+NationShortName(iNation)+"_"+(rand(4)+1);
		if (i > 1) sTemp = "sold_"+NationShortName(iNation)+"_"+(rand(7)+1);
		sld = GetCharacter(NPC_GenerateCharacter("Treasure_soldier_"+i, sTemp, "man", "man", iRank, PIRATE, 1, true, "soldier"));
		SetFantomParamFromRank(sld, iRank, true);
		sld.Dialog.Filename = "Hunter_dialog.c";
		sld.Dialog.currentnode = "TreasureOfficer";
		sld.greeting = "patrol";
		if (i > 1) LAi_CharacterDisableDialog(sld);
		GetCharacterPos(pchar, &locx, &locy, &locz);
		ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindFarLocator("goto", locx, locy, locz));
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
}
