////  файл для кораблей в порту, море и сторожевиков
void GenerateIslandShips(string sIslandID)
{
	//if (!TestRansackCaptain) return; // to_do
	
	int iColonyQuantity = sti(Islands[FindIsland(sIslandID)].colonyquantity);
	int iNation;
	int iShipsQuantity;
	int iChar;
	int iType = 0;

	for (int i = 0; i< MAX_COLONIES; i++)
	{
		if (Colonies[i].island == sIslandID)
		{
			if (colonies[i].nation != "none" && !CheckAttribute(&colonies[i], "HasNoFort") && !CheckAttribute(&colonies[i], "DontSetShipInPort"))
			{
				// belamour установить местных рыбаков -->
				if(CheckAttribute(pchar,"GenQuest.FishingBoat"))
				{
					GenerateFishingBoat(sIslandID, sti(Colonies[i].nation));
				}
				// <-- рыбацкое судно			  
				if (!CheckAttribute(&colonies[i], "GenShipDate") || GetNpcQuestPastDayParam(&colonies[i], "GenShipDate") > 0)
				{
                    SaveCurrentNpcQuestDateParam(&colonies[i], "GenShipDate"); // дата заполнения
                    
					iNation = sti(Colonies[i].nation);
					float fChecker = frand(1.0);
					if (fChecker < 0.8)
					{
						iShipsQuantity = makeint(fChecker * 4.0);
						while (iShipsQuantity > 0)
						{
							iChar = GenerateCharacter(iNation, WITH_SHIP, "soldier", MAN, -1, WARRIOR); //-1 - это 1 день
							PlaceCharacterShip(iChar, iNation, sIslandID, i);

                            characters[iChar].IslandShips = Colonies[i].id; // номер города, чтоб тереть по захвату города to_do
							if (iNation == PIRATE)
							{ // нащ город
								characters[iChar].AlwaysFriend        = true;
								SetCharacterRelationBoth(iChar, GetMainCharacterIndex(), RELATION_FRIEND);
							}
							iType = rand(1);
							if(iType == 0)
							{
								characters[iChar].Ship.Mode = "war";
							}
							else
							{
								characters[iChar].Ship.Mode = "trade";
							}
							if (rand(4) == 1 || GetCharacterShipClass(&characters[iChar]) == 1) SetRandGeraldSail(&characters[iChar], sti(characters[iChar].Nation));
							characters[iChar].AlwaysSandbankManeuver = true;  // тупым запрет тонуть об берег
							characters[iChar].AnalizeShips = true; //анализить вражеские корабли
							characters[iChar].location.from_sea = colonies[i].from_sea;
							SetCaptanModelByEncType(&characters[iChar], characters[iChar].Ship.Mode); // boal
							Fantom_SetCannons(&characters[iChar], characters[iChar].Ship.Mode);
							Fantom_SetBalls(&characters[iChar], characters[iChar].Ship.Mode);
							Fantom_SetGoods(&characters[iChar], characters[iChar].Ship.Mode);
							iShipsQuantity = iShipsQuantity - 1;
						}
					}
				}
			}
		}
	}
}

void PlaceCharacterShip(int iChar, int iNation, string sIslandID, int iColonyIdx)
{
	int iColonyNum = sti(colonies[iColonyIdx].num);
	
	string sColonyID = colonies[iColonyIdx].id;
	
	string sGroup = "IslandGroup" + iChar;
	
	Group_AddCharacter(sGroup, characters[iChar].id);
	Group_SetGroupCommander(sGroup, characters[iChar].id);	
	string sLocatorGroup = "IslandShips" + iColonyNum;
	string sLocator = "Ship_"+(rand(5)+1);
	Group_SetAddress(sGroup, sIslandID, sLocatorGroup, sLocator);

	//trace("sLocatorGroup is " + sLocatorGroup + " sLocator is " + sLocator);

	int iTask = rand(1);
	
	float x, z;
	if (iTask == 0)
	{
		x = rand(1000000);
		z = rand(1000000);
		Group_SetTaskMove(sGroup, x, z);
	}
	else
	{
		Ship_SetTaskDrift(SECONDARY_TASK, iChar);
		//Group_SetTaskNone(sGroup);
	}

	if (sti(characters[iChar].nation) != PIRATE && GetNationRelation2Character(iNation, nMainCharacterIndex) == RELATION_ENEMY)
	{
		Group_SetTaskAttack(sGroup, PLAYER_GROUP);
	}
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
	sld.Ship.Crew.Quantity = sti(GetOptCrewQuantity(sld)/2);
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