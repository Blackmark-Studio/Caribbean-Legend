
#define ISLAND_SHIPS_DAYS 1

void GenerateIslandShips(string sIslandID)
{
	//if (!TestRansackCaptain) return; // to_do

	int iColonyQuantity = int(Islands[FindIsland(sIslandID)].colonyquantity);
	int iNation;
	int iShipsQuantity;
	int iChar;
	int iType = 0;
    bool UpdateTasks = false;

	for (int i = 0; i< MAX_COLONIES; i++)
	{
        ref rColony = &Colonies[i];
		if (rColony.island == sIslandID)
		{
			if (IslandShipsValid(rColony))
			{
				// Belamour установить местных рыбаков
				if ("GenQuest.FishingBoat" in PChar)
					GenerateFishingBoat(sIslandID, int(rColony.nation));

				if (IslandShipsNeedGen(rColony))
				{
                    DeleteAttribute(rColony, "IslandCaps");
                    SaveCurrentNpcQuestDateParam(rColony, "GenShipDate"); // дата заполнения

					iNation = int(rColony.nation);
					int seed = rand(99);
					if (seed >= 95) return;                            // 5% что не будет
					else if (seed >= 85) iShipsQuantity = 1+rand(1);   // 10% что будет 1-2
					else if (seed >= 10) iShipsQuantity = 3+rand(2);   // 75% что будет 3-5
					else iShipsQuantity = 5 + rand(2);                 // 10% что будет 5-7

					// Костыль для лимитинга кол-ва кораблей, если у ГГ эскадра, пока беда с локаторами
					int playerShipsQty = GetCompanionQuantity(PChar);
					if (playerShipsQty > 3) iShipsQuantity = int(func_fmin(2, iShipsQuantity));
					else if (playerShipsQty > 2) iShipsQuantity = int(func_fmin(3, iShipsQuantity));
					else if (playerShipsQty > 1) iShipsQuantity = int(func_fmin(4, iShipsQuantity));

					while (iShipsQuantity > 0)
					{
                        // -1 это 1 день (TO_DO: DEL)
						iChar = GenerateCharacter(iNation, WITH_SHIP, "soldier", MAN, -ISLAND_SHIPS_DAYS, WARRIOR);
						PlaceCharacterShip(iChar, iNation, sIslandID, i);
                        ref chr = &Characters[iChar];
						chr.IslandShips = rColony.id; // Номер города, чтоб тереть по захвату города to_do
						if (iNation == PIRATE)
						{   // Наш город
							chr.AlwaysFriend = true;
							SetCharacterRelationBoth(iChar, GetMainCharacterIndex(), RELATION_FRIEND);
						}
                        string sType = (rand(1) == 0) ? "war" : "trade";
                        chr.Ship.Mode = sType;
						if (rand(4) == 1 || GetCharacterShipClass(chr) == 1)
                        {
                            SetRandGeraldSail(chr, iNation);
						}
                        chr.AlwaysSandbankManeuver = true;  // Тупым запрет тонуть об берег
						chr.AnalizeShips = true; // Анализить вражеские корабли
						chr.location.from_sea = rColony.from_sea;
						SetCaptanModelByEncType(chr, sType); // boal
						Fantom_SetCannons(chr, sType);
						Fantom_SetBalls(chr, sType);
						Fantom_SetGoods(chr, sType);
                        rColony.IslandCaps.(iShipsQuantity) = chr.id;
						iShipsQuantity--;
					}
                    FillIslandCapsInTown(rColony);
				}
                else UpdateTasks = true;
			}
		}
	}

    if (bSeaActive && UpdateTasks)
        UpdateIslandShipsTasks(sIslandID);
}

void PlaceCharacterShip(int iChar, int iNation, string sIslandID, int iColonyIdx)
{
	int iColonyNum = int(colonies[iColonyIdx].num);
	string sColonyID = colonies[iColonyIdx].id;

	string sGroup = "IslandGroup" + iChar;
    ref rGroup = Group_FindOrCreateGroup(sGroup);
    rGroup.IslandGroup = "";

	Group_AddCharacter(sGroup, characters[iChar].id);
	Group_SetGroupCommander(sGroup, characters[iChar].id);	
	string sLocatorGroup = "IslandShips" + iColonyNum;
	string sLocator = "Ship_"+(rand(5)+1);
	Group_SetAddress(sGroup, sIslandID, sLocatorGroup, sLocator);

	IslandShipSetTask(rGroup);
}
// очистить порт
void ClearIslandShips(string _city)
{
	if (!bSeaActive)
	{
		for (int i=GlobalCharacters; i<MAX_CHARACTERS; i++)
		{
			// отдельный код зачистки boal -->
			if (CheckAttribute(&characters[i], "IslandShips") && characters[i].IslandShips == _city)
			{
				InitCharacter(&characters[i], i);
				FreeCharacter(i); // mitrokosta освободить в пул, иначе будет утечка
			}
		}
		// потрем пустые группы
		Group_FreeAllDead();
	}
}

// belamour рыбацкое сундно генерация лодки
void GenerateFishingBoat(string IslandID, int Nation)
{
	log_testinfo("Сгенерировалось рыбацкое судно");
	Group_FindOrCreateGroup("FishingBoat");
	Group_SetType("FishingBoat", "trade"); //тип группы
	ref sld = GetCharacter(NPC_GenerateCharacter("FishingBoatCap", "citiz_25", "man", "man", 10, Nation, -1, true, "citizen"));
	sld.Merchant.type = "FishingBoat";
	GiveItemToTrader(sld);
	sld.dialog.filename = "Capitans_dialog.c";
	sld.DeckDialogNode = "First time";
	sld.greeting = "fisher";
	if(rand(1)==0)FantomMakeCoolSailor(sld, SHIP_TARTANE,"" ,-1 , 10, 10, 10);
	else FantomMakeCoolSailor(sld, SHIP_LUGGER, "", CANNON_TYPE_CANNON_LBS3, 10, 10, 10);
	sld.Ship.Crew.Quantity = int(GetOptCrewQuantity(sld)/2);
	NullCharacterGoods(sld); // удалить товары
	SetCharacterGoods(sld, GOOD_BALLS, 50);
	SetCharacterGoods(sld, GOOD_POWDER, 50);
	SetCharacterGoods(sld, GOOD_SAILCLOTH, 5);
	SetCharacterGoods(sld, GOOD_PLANKS, 5);
	SetCharacterGoods(sld, GOOD_WEAPON, 30);
	SetCharacterGoods(sld, GOOD_RUM, 2);
	SetCharacterGoods(sld, GOOD_MEDICAMENT, 30);
	SetCharacterGoods(sld, GOOD_FOOD, GetCharacterFreeSpace(sld, GOOD_FOOD));
	sld.Ship.Mode = "trade";
	Group_AddCharacter("FishingBoat", "FishingBoatCap");
	Group_SetGroupCommander("FishingBoat", "FishingBoatCap");
	Group_SetTaskNone("FishingBoat");//нет задачи
	Group_SetAddress("FishingBoat", IslandID, "quest_ships", "quest_ship_"+(3+rand(3)));
	Group_LockTask("FishingBoat");

	DeleteAttribute(pchar,"GenQuest.FishingBoat");
	SetFunctionTimerCondition("FishingBoat_End", 0, 0, 1, false);
}

void UpdateIslandShipsTasks(string sIslandID)
{
    for(int i = 0; i < MAX_SHIP_GROUPS; i++)
    {
        ref rGroup = &AIGroups[i];
        if ("IslandGroup" !in rGroup)
            continue;
        if (rGroup.Location$string("") != sIslandID) 
            continue;
        if (int(rGroup.Task) == AITASK_NONE)
            IslandShipRestoreTask(rGroup);
    }
}

void IslandShipSetTask(ref rGroup)
{
    string sGroup = rGroup.id;
    int iChar = Group_GetCharacterIndexR(rGroup, 0);
    if (iChar < 0)
        return;

    if (rand(1) == 0)
    {   // Задать перемещение
        float fAng = frnd() * PIm2;
        Group_SetTaskMove(sGroup, 10000.0 * sin(fAng), 10000.0 * cos(fAng));
    }
    else
    {   // Дрифт
        Group_SetTaskDrift(sGroup);
    }

    // Атака именно после потенциальной выдачи задачи на перемещение,
    // так как после боя может к ней вернуться
    int iNation = int(Characters[iChar].nation);
    if (iNation != PIRATE && GetNationRelation2Character(iNation, nMainCharacterIndex) == RELATION_ENEMY)
    {
        Group_SetTaskAttack(sGroup, PLAYER_GROUP);
    }
}

// PLAYER_GROUP регулярно пересоздаётся, и если у кого-то стояла задача атаковать PLAYER_GROUP,
// то после удаления PLAYER_GROUP задача заменится на AITASK_NONE, а нужно восстановить первичную:
void IslandShipRestoreTask(ref rGroup)
{
    string sGroup = rGroup.id;
    int iChar = Group_GetCharacterIndexR(rGroup, 0);
    if (iChar < 0)
        return;

    int iNation = int(Characters[iChar].nation);
    if (iNation != PIRATE && GetNationRelation2Character(iNation, nMainCharacterIndex) == RELATION_ENEMY)
    {   // После атаки сам вернётся к нужной задаче
        Group_SetTaskAttack(sGroup, PLAYER_GROUP);
        return;
    }

    if ("Task.Target.Pos.x" in rGroup)
    {   // Восстановить перемещение
        Group_SetTaskMove(sGroup, float(rGroup.Task.Target.Pos.x), float(rGroup.Task.Target.Pos.z));
    }
    else
    {   // Восстановить дрифт
        Group_SetTaskDrift(sGroup);
    }
}

bool IslandShipsValid(ref rColony)
{
    return rColony.Nation != "none" && "HasNoFort" !in rColony && "DontSetShipInPort" !in rColony;
}

bool IslandShipsNeedGen(ref rColony)
{
    return "GenShipDate" !in rColony || GetNpcQuestPastDayParam(rColony, "GenShipDate") > ISLAND_SHIPS_DAYS;
}

#event_handler(EVENT_PREPARE_SHIPS, "CheckIslandShipsGen");
void CheckIslandShipsGen(ref loc)
{
    if ("fastreload" !in loc) return;
    int iColony = FindColony(loc.fastreload);
    if (iColony < 0) return;
    ref rColony = &Colonies[iColony];
    if (IslandShipsValid(rColony) && IslandShipsNeedGen(rColony))
        GenerateIslandShips(rColony.island);
}
