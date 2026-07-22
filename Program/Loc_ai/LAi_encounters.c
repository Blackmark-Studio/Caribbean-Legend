
#include "Loc_ai\loc_encounters\jung_class.c"
#include "Loc_ai\loc_encounters\jung_list.c"
#include "Loc_ai\loc_encounters\city_list.c"

// Встречи в джунглях
bool LAi_CreateJungleEncounters(ref location)
{
    // Разовый запрет
	if (!bLandEncountersGen)
	{
		bLandEncountersGen = true;
		return false;
	}
    // Общий запрет
	if (location.DisableEncounters$bool(false) || bDisableLandEncounters)
        return false;
    // Проверка локаторов
	if ("locators.encdetector" !in location)
        return false;
    // Проверка даты (попытка генерации только раз в сутки)
    if (!CheckNPCQuestDate(location, "Enc_date"))
        return false;

    int iNation;
	string sAreal, sCity;

    // Проверка ареала
	sAreal = GiveArealByLocation(location);
	if (sAreal == "none")
        return false;
    // Проверка города на обитаемых островах
    bool bUninhabited = "onUninhabitedIsland" in location;
	if (!bUninhabited)
	{
		sCity = GetCityNameByIsland(sAreal);
		if (sCity == "none")
            return false;

		iNation = GetCityNation(sCity);
		if (iNation == -1 || iNation == PIRATE)
            return false;
	}

    // Если фильтры выше пройдены, то сохраняем дату попытки генерации
    SetNPCQuestDate(location, "Enc_date");

    // Начало игры
    if ("questTemp.Sharlie.Lock" in PChar)
        return false;
	// Земли Ица (дорога к Тайясалю) ~!~
	if ("ItzaLand" in location)
        return false;
    // Занято квестом
	if (!isLocationFreeForQuests(location.Id))
        return false;
	// Занято контрабандистами
	if (location.type == "seashore")
	{
		aref st = touchattr(location.models.always);
		for(int i = 0; i < @st; i++)
		{
			if (string(st[i]) == "smg")
				return false;
		}
	}

    // EncDetector содержит локаторы, имена которых сами являются группами
    // Так что encGroup это и локатор-детектор с большим радиусом,
    // и группа локаторов внутри него, где размещаются NPC
	string encGroup = LAi_FindRandomLocator("encdetector");
	aref grp = &location.locators.(encGroup);

    // Выбираем встречу
    bUninhabited |= "deadlocked" in location;
    aref arEnc = bUninhabited ? JungleEncList.GetUninhabited(location) : JungleEncList.GetRandomEnc(location);
    if (arEnc.isValid(location, grp))
    {
        arEnc.Generate(location, sAreal, sCity, iNation, grp, encGroup);
        if (!bUninhabited)
        {
            if (MOD_BETTATESTMODE == "On")
                Log_Info("Сгенерировано событие " + UpperFirst(nameattr(arEnc)) + " Шанс " + fts(JEL_CalcChancePercent(arEnc), 2) + "%");
            JungleEncList.UpdateWeights(nameattr(arEnc));
        }
        return true;
    }

    if (MOD_BETTATESTMODE == "On")
        Log_Info("Событие " + UpperFirst(nameattr(arEnc)) + " не подходит для локации " + location.id);

    return false;
}

// Jason. Встречи в пещерах
bool LAi_CreateCaveEncounters(ref location)
{
	if (CheckAttribute(location, "type") && location.type == "cave")
	{
        // На if'ах оставил старую логику (TO_DO: переверить)
        // За счёт "&" для каждой конкретной location в конкретный день используется одна и та же дробь
        string tag2 = location.id;
        string tag = "&" + tag2;

		if (!bLandEncountersGen) //если прерывание на локацию, энкаунтеров не генерим
		{		
			bLandEncountersGen = true;
			return false;
		}
		if(CheckAttribute(location, "DisableEncounters") && location.DisableEncounters == true) return false; // mitrokosta фикс неправильного включения энкаунтеров
		if (CheckAttribute(location, "enc") && GetNpcQuestPastDayParam(location, "enc") < 1) return false;
		if (findsubstr(location.id, "Ksochitam_" , 0) != -1 || findsubstr(location.id, "mine_" , 0) != -1) return false;
		if (CheckAttribute(pchar, "questTemp.Sharlie.Lock")) return false;
		if (location.id == "Bermudes_Cavern" || location.id == "FortFrance_Dungeon") return false; // patch
		if (hrand(12, tag2) > 5) return false;
		
		//log_Testinfo("Работают пещерные энкаунтеры");
		ref chr, rItm;
		int i, num, iMassive;
		string str, locator, sItm, sJew, sGem, sMin;
		string model[10];
		float locx, locy, locz;
		int iRank = 8+int(pchar.rank)+int(MOD_SKILL_ENEMY_RATE)/2;
		switch(rand(4))
		{
			case 0: // бандюки
				str = "CaveBandos"+ location.index + "_";
				num = 4;
				i = 0;
				model[0] = "citiz_41";
				model[1] = "citiz_42";
				model[2] = "citiz_43";
				model[3] = "citiz_44";
				model[4] = "citiz_45";
				model[5] = "citiz_46";
				model[6] = "citiz_47";
				model[7] = "citiz_48";
				model[8] = "citiz_49";
				model[9] = "citiz_50";
				while(i < num)
				{
					iMassive = rand(9);
					
					if(model[iMassive] != "")
					{
						chr = GetCharacter(NPC_GenerateCharacter(str+i, model[iMassive], "man", "man", iRank, PIRATE, 1, true, "marginal"));
						SetFantomParamFromRank(chr, iRank, true);
						chr.dialog.filename = "CaveEnc_dialog.c";
						chr.greeting = "banditos";
						chr.role = "banditos";
						LAi_SetCheckMinHP(chr, LAi_GetCharacterHP(chr)-1, false, "CaveEnc_RaidersBeforeDialog"); 
						if(!CheckAttribute(location, "nofire")) // вокруг костра
						{
							chr.dialog.currentnode = "CaveBanditosSit";
							rItm = ItemsFromID("fire");
							rItm.shown = true;
							rItm.startLocation = location.id;
							rItm.startLocator = "fire";
							location.fire = true;
                            CreateFireParticles("goto", "fire");
							locator = "ass"+(i+1);
							ChangeCharacterAddressGroup(chr, location.id, "goto", locator);
							LAi_SetGroundSitTypeNoGroup(chr);
						}
						else // стоймя
						{
							chr.dialog.currentnode = "CaveBanditosStay";
							GetCharacterPos(pchar, &locx, &locy, &locz);
							ChangeCharacterAddressGroup(chr, location.id, "monsters", LAi_FindFarFreeLocator("monsters", locx, locy, locz));
							LAi_SetGuardianType(chr);
							chr.protector = true;
						}
						if (hrand(14, tag2) == 1) // кладокопатели
						{
							chr.dialog.currentnode = "CaveBanditosTreasure";
							chr.SaveItemsForDead = true;
							AddMoneyToCharacter(chr, 2000 + hrand(2000, chr.id + chr.name));
							TakeNItems(chr, "gold_dublon",  hrand(25,   chr.id + chr.name));
							if (hrand(5, tag)  == 1) TakeNItems(chr, "chest", 1);
							if (hrand(10, tag) == 2) TakeNItems(chr, "icollection", 1);
							switch (hrand(7, tag))
                            {                            
                                case 0: TakeNItems(chr, "jewelry1",  hrand(50, tag2)); break;
                                case 1: TakeNItems(chr, "jewelry2",  hrand(30, tag2)); break;
							    case 2: TakeNItems(chr, "jewelry3",  hrand(40, tag2)); break;
							    case 3: TakeNItems(chr, "jewelry4",  hrand(30, tag2)); break;
							    case 4: TakeNItems(chr, "jewelry5",  hrand(100, tag2)); break;
							    case 5: TakeNItems(chr, "jewelry6",  hrand(200, tag2)); break;
							    case 6: TakeNItems(chr, "jewelry52", hrand(200, tag2)); break;
							    case 7: TakeNItems(chr, "jewelry53", hrand(500, tag2)); break;
                            }
						}
						i++;
						model[iMassive] = "";
					}
				}
				pchar.GenQuest.LandEnc.LocId = location.id;
				str = "TimeCaveRaiders_" + location.index;
				pchar.quest.(str).LocIdx = location.index;
				pchar.quest.(str).win_condition.l1 = "Timer";
				pchar.quest.(str).win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
				pchar.quest.(str).win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
				pchar.quest.(str).win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
				pchar.quest.(str).win_condition = "CaveEnc_RaidersOver";
				SaveCurrentNpcQuestDateParam(location, "enc");
			break;
			
			case 1: // карибы
				str = "CaveBandos"+ location.index + "_";
				num = 4;
				i = 0;
				model[0] = "canib_1";
				model[1] = "canib_2";
				model[2] = "canib_3";
				model[3] = "canib_4";
				model[4] = "canib_5";
				model[5] = "canib_6";
				model[6] = "canib_1";
				model[7] = "canib_2";
				model[8] = "canib_3";
				model[9] = "canib_4";
				while(i < num)
				{
					iMassive = rand(9);
					
					if(model[iMassive] != "")
					{
						chr = GetCharacter(NPC_GenerateCharacter(str+i, model[iMassive], "man", "man", iRank+5, PIRATE, 1, true, "native"));
						SetFantomParamFromRank(chr, iRank+5, true);
						chr.dialog.filename = "CaveEnc_dialog.c";
						chr.greeting = "indiano";
						chr.name = GetIndianName(MAN);
						chr.lastname = "";
						LAi_SetCheckMinHP(chr, LAi_GetCharacterHP(chr)-1, false, "CaveEnc_RaidersBeforeDialog"); 
						if(!CheckAttribute(location, "nofire")) // вокруг костра
						{
							chr.dialog.currentnode = "CaveCaribSit";
							rItm = ItemsFromID("fire");
							rItm.shown = true;
							rItm.startLocation = location.id;
							rItm.startLocator = "fire";
							location.fire = true;
							CreateFireParticles("goto", "fire");
							locator = "ass"+(i+1);
							ChangeCharacterAddressGroup(chr, location.id, "goto", locator);
							LAi_SetGroundSitTypeNoGroup(chr);
						}
						else // стоя
						{
							chr.dialog.currentnode = "CaveCaribStay";
							GetCharacterPos(pchar, &locx, &locy, &locz);
							ChangeCharacterAddressGroup(chr, location.id, "monsters", LAi_FindFarFreeLocator("monsters", locx, locy, locz));
							LAi_SetGuardianType(chr);
							chr.protector = true;
						}
						if (hrand(10, tag2) == 0) // богатенькие
						{
							chr.SaveItemsForDead = true;
							switch (hrand(3, tag))
                            {                            
                                case 0: TakeNItems(chr, "jewelry5",  hrand(100, tag2)); break;
                                case 1: TakeNItems(chr, "jewelry6",  hrand(150, tag2)); break;
                                case 2: TakeNItems(chr, "jewelry52", hrand(300, tag2)); break;
                                case 3: TakeNItems(chr, "jewelry53", hrand(700, tag2)); break;
                            }
						}
						i++;
						model[iMassive] = "";
					}
				}
				pchar.GenQuest.LandEnc.LocId = location.id;
				str = "TimeCaveRaiders_" + location.index;
				pchar.quest.(str).LocIdx = location.index;
				pchar.quest.(str).win_condition.l1 = "Timer";
				pchar.quest.(str).win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
				pchar.quest.(str).win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
				pchar.quest.(str).win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
				pchar.quest.(str).win_condition = "CaveEnc_RaidersOver";
				SaveCurrentNpcQuestDateParam(location, "enc");
			break;
			
			case 2: // мирный индеец
				str = "CaveWalker"+location.index;
				chr = GetCharacter(NPC_GenerateCharacter(str, "miskito_"+(rand(5)+1), "man", "man", iRank, PIRATE, 1, true, "native"));
				SetFantomParamFromRank(chr, iRank, true);
				chr.name = GetIndianName(MAN);
				chr.lastname = "";
				chr.greeting = "item_indian";
				chr.dialog.filename = "Enc_Indian.c";
				chr.dialog.currentnode = "First time";
				LAi_SetWarriorType(chr);
				GetCharacterPos(pchar, &locx, &locy, &locz);
				ChangeCharacterAddressGroup(chr, location.id, "monsters", LAi_FindFarFreeLocator("monsters", locx, locy, locz));
				chr.Merchant.type = "indian";
				chr.money = TRADER_MIN_MONEY;
				SaveCurrentNpcQuestDateParam(location, "enc");
			break;
			
			case 3: // скелеты с лутом
				if(CheckAttribute(location, "id.label") && location.id.label == "Grot") return false;
				str = "CaveSkelet"+ location.index + "_";
				sTotalTemp = str;
				for(i=0; i<4; i++)
				{
					chr = GetCharacter(NPC_GenerateCharacter(str+i, "skel"+(rand(3)+1), "man", "man", iRank, PIRATE, 1, true, "marginal"));
					RemoveAllCharacterItems(chr, true);
					chr.SaveItemsForDead = true;
					chr.DontClearDead = true; 
					CaveEnc_FillSkeleton(chr, i);
					LAi_SetWarriorType(chr);
					GetCharacterPos(pchar, &locx, &locy, &locz);
					ChangeCharacterAddressGroup(chr, location.id, "monsters", LAi_FindFarFreeLocator("monsters", locx, locy, locz));
				}
				DoQuestCheckDelay("CaveEnc_SkeletDie", 1.3);
				SaveCurrentNpcQuestDateParam(location, "enc");
			break;
			
			case 4: // заполним сундук
				str = location.id;
				sJew = "jewelry"+(hrand(11, tag2)+12);
				sGem = "jewelry"+(hrand(5,  tag2)+1);
				sMin = "mineral"+(hrand(13, tag2)+13);
				switch (hrand(2, tag2))
				{
					case 0: sItm = "indian_"+(hrand(10, tag2)+1); break;
					case 1: sItm = "amulet_"+(hrand(10, tag2)+1); break;
					case 2: sItm = "obereg_"+(hrand(10, tag2)+1); break;
				}
				pchar.GenQuestBox.(str) = true;
				switch (hrand(10, tag)) 
                {
                    case 0: pchar.GenQuestBox.(str).box1.items.gold_dublon = hrand(100, tag2); break;
                    case 1: pchar.GenQuestBox.(str).box1.items.chest    = hrand(1, tag2);   break;
                    case 2: pchar.GenQuestBox.(str).box1.items.jewelry7 = hrand(3, tag2);   break;
                    case 3: pchar.GenQuestBox.(str).box1.items.jewelry5 = hrand(100, tag2); break;
                    case 4: pchar.GenQuestBox.(str).box1.items.jewelry6 = hrand(200, tag2); break;
                    case 5: pchar.GenQuestBox.(str).box1.items.jewelry6 = hrand(200, tag2); break;
                }
				if (hrand(10, tag) > 5) pchar.GenQuestBox.(str).box1.items.(sMin) = 1;
				if (hrand(7, tag) == 0) pchar.GenQuestBox.(str).box1.items.(sItm) = 1;
				if (hrand(7, tag) == 1) pchar.GenQuestBox.(str).box1.items.(sJew) = hrand(20, tag2);
				if (hrand(7, tag) == 2) pchar.GenQuestBox.(str).box1.items.(sGem) = hrand(30, tag2);
				SaveCurrentNpcQuestDateParam(location, "enc");
			break;
		}
		return true;
	}
	return false;
}
