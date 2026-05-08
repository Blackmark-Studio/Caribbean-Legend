#define I_MIN_MORALE	10

#define FOOD_BY_CREW       10.0
#define FOOD_BY_SLAVES     20.0
#define FOOD_BY_PASSENGERS 10.0
#define RUM_BY_CREW        50.0
#define MEDICAMENT_BY_CREW 50.0
#define MEDICAMENT_BY_SLAVES 50.0

#define MAINTENANCE_MOD_ALL 0
#define MAINTENANCE_MOD_FOOD_LEFT 1
#define MAINTENANCE_MOD_FOOD_INFO 2
#define MAINTENANCE_MOD_MEDICAMENT_LEFT 3
#define MAINTENANCE_MOD_MEDICAMENT_INFO 4
#define MAINTENANCE_MOD_RUM_LEFT 5
#define MAINTENANCE_MOD_RUM_INFO 6

// На сколько дней еды в эскадре
int CalculateFood()
{
	int chrIndex;
	int foodStock = 0;
	float foodConsumption = 0;
	for (int i=0; i<COMPANION_MAX; i++)
	{
		chrIndex = GetCompanionIndex(pchar, i);
		if (chrIndex < 0) continue;

		ref chr = &characters[chrIndex];
		if (chr.ship.type == SHIP_NOTUSED) continue;

		object shipInfo;
		SetShipMaintenanceInfo(chr, &shipInfo, MAINTENANCE_MOD_FOOD_INFO);
		foodStock += GetAttributeInt(&shipInfo, "foodStock");
		foodConsumption += GetAttributeFloat(&shipInfo, "foodConsumption");
	}

	return makeint(foodStock/foodConsumption);
}

// На сколько дней рома в эскадре
int CalculateRum()
{
	int rumStock = 0;
	float rumConsumption = 0;
	for (int i=0; i<COMPANION_MAX; i++)
	{
		int chrIndex = GetCompanionIndex(pchar, i);
		if (chrIndex < 0) continue;

		ref chr = &characters[chrIndex];
		if (chr.ship.type == SHIP_NOTUSED) continue;

		object shipInfo;
		SetShipMaintenanceInfo(chr, &shipInfo, MAINTENANCE_MOD_RUM_INFO);
		rumStock += GetAttributeInt(&shipInfo, "rumStock");
		rumConsumption += GetAttributeFloat(&shipInfo, "rumConsumption");
	}

	return makeint(rumStock/rumConsumption);
}

// На сколько дней медикаментов в эскадре
int CalculateMedicament()
{
	int medicamentStock = 0;
	float medicamentConsumption = 0;
	for (int i=0; i<COMPANION_MAX; i++)
	{
		int chrIndex = GetCompanionIndex(pchar, i);
		if (chrIndex < 0) continue;

		ref chr = &characters[chrIndex];
		if (chr.ship.type == SHIP_NOTUSED) continue;

		object shipInfo;
		SetShipMaintenanceInfo(chr, &shipInfo, MAINTENANCE_MOD_MEDICAMENT_INFO);
		medicamentStock += GetAttributeInt(&shipInfo, "medicamentStock");
		medicamentConsumption += GetAttributeFloat(&shipInfo, "crewMedicamentConsumption");
		medicamentConsumption += GetAttributeFloat(&shipInfo, "slavesMedicamentConsumption");
	}

	return makeint(medicamentStock/medicamentConsumption);
}

void CalculateSupplies(ref food, ref rum, ref medicament)
{
	int foodStock = 0;
	float foodConsumption = 0;
	int rumStock = 0;
	float rumConsumption = 0;
	int medicamentStock = 0;
	float medicamentConsumption = 0;
	for (int i=0; i<COMPANION_MAX; i++)
	{
		int chrIndex = GetCompanionIndex(pchar, i);
		if (chrIndex < 0) continue;

		ref chr = &characters[chrIndex];
		if (chr.ship.type == SHIP_NOTUSED) continue;

		object shipInfo;
		SetShipMaintenanceInfo(chr, &shipInfo, MAINTENANCE_MOD_ALL);
		foodStock += GetAttributeInt(&shipInfo, "foodStock");
		foodConsumption += GetAttributeFloat(&shipInfo, "foodConsumption");
		rumStock += GetAttributeInt(&shipInfo, "rumStock");
		rumConsumption += GetAttributeFloat(&shipInfo, "rumConsumption");
		medicamentStock += GetAttributeInt(&shipInfo, "medicamentStock");
		medicamentConsumption += GetAttributeFloat(&shipInfo, "crewMedicamentConsumption");
		medicamentConsumption += GetAttributeFloat(&shipInfo, "slavesMedicamentConsumption");
	}
	food = int(foodStock / foodConsumption);
	rum = int(rumStock / rumConsumption);
	medicament = int(medicamentStock / medicamentConsumption);
}

/* Метод расчёта содержания корабля. Работает в разных режимах от параметра `mode`
	0 – посчитать всё вместе, результат в объекте
	1 – еда, вернуть количество дней
	2 – еда, результат в объекте
	3 – мед, вернуть количество дней
	4 – мед, результат в объекте
	5 – ром, вернуть количество дней
	6 – ром, результат в объекте
*/
int SetShipMaintenanceInfo(ref chr, ref shipInfo = nullptr, int mode = 0)
{
	int crewQty = GetCrewQuantity(chr);
	int slavesQty = GetCargoGoods(chr, GOOD_SLAVES);
	float mtp;

	// Еда
	if (mode <= MAINTENANCE_MOD_FOOD_INFO)
	{
		int passengersQty = IsMainCharacter(chr) ? GetPassengersQuantity(pchar) : 0;
		int foodStock = GetCargoGoods(chr, GOOD_FOOD);
		float foodConsumption = makefloat(crewQty/FOOD_BY_CREW + passengersQty/FOOD_BY_PASSENGERS + slavesQty/FOOD_BY_SLAVES); // база
		mtp = SZN_GetModifierMtp(M_FOOD_CONSUMPTION, 1.0, 0.01);
		foodConsumption *= mtp;
		foodConsumption *= isEquippedArtefactUse(chr, "talisman6", 1.0, 0.75);
		foodConsumption *= GetCookMtp(chr);
		if (CheckAttribute(pchar, "questTemp.VPVL_Food")) foodConsumption *= 0.85; // Уменьшаем на 15% andre39966, для квеста "В плену великого улова"
		int iFoodConsumption = func_max(1, ceil(foodConsumption)); // не меньше 1, округляем в большую
		int foodDaysLeft = int(foodStock/iFoodConsumption);        // дни округляем в меньшую
		if (mode == MAINTENANCE_MOD_FOOD_LEFT) return foodDaysLeft;

		shipInfo.foodConsumption = iFoodConsumption;
		shipInfo.foodStock = foodStock;
		shipInfo.foodDaysLeft = foodDaysLeft;
	}

	// Медикаменты
	if (mode == MAINTENANCE_MOD_ALL || mode == MAINTENANCE_MOD_MEDICAMENT_LEFT || mode == MAINTENANCE_MOD_MEDICAMENT_INFO)
	{
		int medicamentStock = GetCargoGoods(chr, GOOD_MEDICAMENT);
		mtp = SZN_GetModifierMtp(M_MEDICAMENT_CONSUMPTION, 1.0, 0.01);
		int crewMedicamentConsumption = func_max(1, ceil(crewQty / MEDICAMENT_BY_CREW * mtp)); // не меньше 1, округляем в большую
		int slavesMedicamentConsumption = ceil(slavesQty / MEDICAMENT_BY_SLAVES * mtp);        // округляем в большую, но тут может быть 0, когда рабов нет вовсе

		int medicamentDaysLeft = int(medicamentStock / (crewMedicamentConsumption + slavesMedicamentConsumption)); // дни округляем в меньшую
		if (mode == MAINTENANCE_MOD_MEDICAMENT_LEFT) return medicamentDaysLeft;

		shipInfo.medicamentStock = medicamentStock;
		shipInfo.medicamentDaysLeft = medicamentDaysLeft;
		shipInfo.crewMedicamentConsumption = crewMedicamentConsumption;
		shipInfo.slavesMedicamentConsumption = slavesMedicamentConsumption;
	}

	// Ром
	if (mode == MAINTENANCE_MOD_ALL || mode == MAINTENANCE_MOD_RUM_LEFT || mode == MAINTENANCE_MOD_RUM_INFO)
	{
		int rumStock = GetCargoGoods(chr, GOOD_RUM);
		float rumConsumption = makefloat(crewQty) / RUM_BY_CREW;
		rumConsumption *= isEquippedArtefactUse(chr, "talisman4", 1.0, 0.2);
		rumConsumption *= GetBartenderMtp(chr);
		int iRumConsumption = func_max(1, ceil(rumConsumption));              // не меньше 1, округляем в большую
		int rumDaysLeft = crewQty != 0 ? int(rumStock / iRumConsumption) : 0; // дни округляем в меньшую
		if (mode == MAINTENANCE_MOD_RUM_LEFT) return rumDaysLeft;

		shipInfo.rumStock = rumStock;
		shipInfo.rumConsumption = iRumConsumption;
		shipInfo.rumDaysLeft = rumDaysLeft;
	}

	return 0;
}

// На сколько дней еды на корабле
int CalculateShipFood(ref chr)
{
	return SetShipMaintenanceInfo(chr, nullptr, MAINTENANCE_MOD_FOOD_LEFT);
}

// На сколько дней еды на корабле
int CalculateShipMedicament(ref chr)
{
	return SetShipMaintenanceInfo(chr, nullptr, MAINTENANCE_MOD_MEDICAMENT_LEFT);
}

// На сколько дней рома на корабле
int CalculateShipRum(ref chr)
{
	return SetShipMaintenanceInfo(chr, nullptr, MAINTENANCE_MOD_RUM_LEFT);
}

// boal 21.04.04 крысы на корабле -->
void DailyRatsEatGoodsUpdate(ref chref)
{
	if(IsCharacterEquippedArtefact(chref, "talisman1")) return; // крысобог
	if(IsCharacterEquippedArtefact(chref, "rat_poison")) return; // мышьяк
	if(CheckAttribute(pchar, "GenQuest.Ole")) return; // Оле Кристиансен
	if(IsCharacterPerkOn(chref, "HT2")) return; // belamour legendary edition отсутствие крыс только на флагмане, если нужно у эскадры пишем pchar
	if (chref.index == GetMainCharacterIndex() && GetCharacterIndex("Longway") != -1)
	{
		ref rLongway = CharacterFromID("Longway");
		if(IsCharacterPerkOn(rLongway, "RatsWolf")) return;
	}
    int iGoods = GetRandomGood(FLAG_GOODS_TYPE_EXPORT + FLAG_GOODS_TYPE_IMPORT + FLAG_GOODS_TYPE_UNIQUE, FLAG_GOODS_NONE);
	if(iGoods == GOOD_BRICK) return;
    int iQuantity = GetCargoGoods(chref, iGoods);
    if (iQuantity > 60 && rand(4) != 2) // шанс не жрать, если весь спектр
    {
        float fSkill = GetSummonSkillFromNameToOld(chref, SKILL_REPAIR) + GetSummonSkillFromNameToOld(chref,SKILL_FORTUNE);
        
        iQuantity = 1+ rand(makeint(iQuantity / (10+fSkill)));
		//if (IsCharacterPerkOn(chref, "HT2")) iQuantity = makeint(iQuantity/2) + 1;
		if (CheckAttribute(chref, "quest.givemecat")) iQuantity = iQuantity * 0.75 + 1; // Митрокоста + Лесник - кошка на крбале ГГ снижение на 25%																			 
        RemoveCharacterGoodsSelf(chref, iGoods, iQuantity);
        //PlaySound("interface\notebook.wav");
        //if(LanguageGetLanguage() == "russian") Log_SetStringToLog(RandSwear());
        notification(StringFromKey("food_1") +
                           LinkRandPhrase(StringFromKey("food_2"), StringFromKey("food_3"), StringFromKey("food_4")) +
                           iQuantity + StringFromKey("food_5") + GetGoodsNameSeaSection(&Goods[iGoods]), "Rats");

        Statistic_AddValue(pchar, "RatsEatGoods", iQuantity);
                
		if (iQuantity > 400) iQuantity = 400;
		
		AddCharacterExpToSkill(chref, SKILL_REPAIR, iQuantity);
        AddCharacterExpToSkill(chref, SKILL_FORTUNE, iQuantity/10);
    }
}

// boal food for crew 20.01.2004 -->
void DailyEatCrewUpdate()   // сюда пихаю все что в 1 день
{
    ref mainCh = GetMainCharacter();
    int i, cn, crew, morale;
    ref chref;
    
    // to_do
    // boal 030804 Начисление денег верфям -->
    //DailyShipyardMoneyUpdate();
    // boal 030804 Начисление денег верфям <--
	
	// ugeen Начисление денег торговцам -->
	DailyTradersMoneyUpdate();
	// ugeen Начисление денег  торговцам<--
	
    mainCh.questTemp.abordage = 0; // fix квест потопить пирата второй абордаж

    //таможня
    //if(IsCharacterPerkOn(mainCh, "CustomsHouse"))
    //{
    //    AddGoverGoods();
    //}

    SetNewDayHealth(); // здоровье за день
  
	// ОЗГи -->
	//SetPortShoreEnter(mainCh);
    DeleteAttribute(mainCh, "GenQuest.Hunter2Pause");  // boal бойня в форте кончилась - ОЗГи вернулись
    // ОЗГи <--

    //  уже не нужно SetAllHabitueToNew(); // сменить всех пьяниц в тавернах
	if (CheckAttribute(mainCh, "questTemp.ShipCapellan.Yes")) AddCrewMorale(mainCh, 2); //Jason, влияние корабельного капеллана на мораль

	////////////////      ЕДА     /////////////////
	if (bNoEatNoRats) return; // betatest
    if (sti(mainCh.Ship.Type) == SHIP_NOTUSED ) return;

	// снижение лояльности от долга 02.02.08 -->
	if (CheckAttribute(pchar, "CrewPayment")) // Долг
	{
		ChangeCharacterComplexReputation(pchar,"authority", -0.1);
        cn = makeint(pchar.CrewPayment);
        if (cn > 32000) cn = 32000;
		if (rand(cn) > 1000)
		{
			// belamour legendary edition перк получил время работы, старый метод не подходит
            morale = 5;
			for (i = 0; i<GetPassengersQuantity(pchar); i++)
			{   // любой пассажир у кого есть пристрастие может свалить
				cn = GetPassenger(pchar, i);
				if (cn != -1)
				{
		            chref = &Characters[cn];
					if (CheckAttribute(chref, "loyality") && !CheckAttribute(chref, "OfficerWantToGo.DontGo") && rand(morale) == 2 && !IsEquipCharacterByArtefact(chref, "totem_04"))
					{
		    			chref.loyality = makeint(chref.loyality) - 1;
					}
				}
			}
		}
	}
	// снижение лояльности от долга 02.02.08 <--
	
	for(i=0; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(mainCh,i);
		if( cn>=0 )
		{
			chref = GetCharacter(cn);

			if (!GetRemovable(chref)) continue;

			// RATS -->
			DailyRatsEatGoodsUpdate(chref);
			// RATS <--
			DailyEatCrewUpdateForShip(chref, false);
			DailyCheckIfQuartermaster(chref);
		}
	}
}

void DailyMedicamentUpdate(ref chr, bool IsCompanionTraveler, ref shipInfo, int crewQty, int slavesQty)
{
	int crewMedicamentConsumption = GetAttributeInt(shipInfo, "crewMedicamentConsumption");
	int slavesMedicamentConsumption = GetAttributeInt(shipInfo, "slavesMedicamentConsumption");
	int medicamentStock = GetAttributeInt(shipInfo, "medicamentStock");

	if (crewMedicamentConsumption > 0)
	{
		if (medicamentStock < 1)
		{
			int deadCrewQty = crewMedicamentConsumption;
			if(!IsCompanionTraveler) Log_Info(StringFromKey("food_6", chr.Ship.Name, FindRussianSailorString(deadCrewQty, "No")));

			Statistic_AddValue(pchar, "Sailors_dead", deadCrewQty);
			AddMementoShipBonus(deadCrewQty);
			Achievment_SetStat(21, deadCrewQty);
			chr.Ship.Crew.Quantity = crewQty - deadCrewQty;
			float nMoraleDecreaseQ = deadCrewQty / 2;
			nMoraleDecreaseQ *= (1-SZN_GetModifierMtp(M_CREW_MORALE_DEBUFF_MTP, 0.0, 0.0, 0.99));
			AddCrewMorale(chr, -makeint(nMoraleDecreaseQ));
			ChangeCharacterComplexReputation(pchar,"authority", -1);
		}
		else
		{
			if(CheckShipSituationDaily_GenQuest(chr) == 2) crewMedicamentConsumption = crewMedicamentConsumption * 2;
			if(CheckShipSituationDaily_GenQuest(chr) == 3) crewMedicamentConsumption = crewMedicamentConsumption * 3;
			
			RemoveCharacterGoodsSelf(chr, GOOD_MEDICAMENT, crewMedicamentConsumption);
			if (medicamentStock < 16)
			{
				if(!IsCompanionTraveler) Log_Info(StringFromKey("food_7", chr.Ship.Name));
			}
		}
	}

	// рабы
	if (slavesMedicamentConsumption > 0)
	{
		if (medicamentStock < 1)
		{
			if(!IsCompanionTraveler) Log_Info(StringFromKey("food_8", chr.Ship.Name, FindRussianSlavesString(slavesMedicamentConsumption, "No")));

			RemoveCharacterGoodsSelf(chr, GOOD_SLAVES, slavesMedicamentConsumption);
		}
		else
		{
			slavesMedicamentConsumption /= 3;
			RemoveCharacterGoodsSelf(chr, GOOD_MEDICAMENT, slavesMedicamentConsumption);
		}
	}
}

void DailyRumUpdate(ref chr, bool IsCompanionTraveler, ref shipInfo, int crewQty)
{
	int rumConsumption = GetAttributeInt(shipInfo, "rumConsumption");
	if (rumConsumption < 1) return;

	int rumStock = GetAttributeInt(shipInfo, "rumStock");
	if (rumStock >= rumConsumption)
	{
		RemoveCharacterGoodsSelf(chr, GOOD_RUM, rumConsumption);
		if (CheckShipSituationDaily_GenQuest(chr) == 1) AddCrewMorale(chr, 2); // поднимем мораль
		if (rumStock - rumConsumption > rumConsumption) return;
		if (IsCompanionTraveler) return;
		Log_Info(StringFromKey("food_9", chr.Ship.Name)); // проверка на остатки
		return;
	}

	RemoveCharacterGoodsSelf(chr, GOOD_RUM, rumStock);
}

void DailyFoodUpdate(ref chr, bool IsCompanionTraveler, ref shipInfo, int crewQty, int slavesQty)
{
	int foodConsumption = GetAttributeInt(shipInfo, "foodConsumption");
	int foodStock = GetAttributeInt(shipInfo, "foodStock");

	// Если еды хватает
	if (foodStock >= foodConsumption)
	{
		RemoveCharacterGoodsSelf(chr, GOOD_FOOD, foodConsumption);
		// проверка на остатки
		int daysLeft = GetAttributeInt(shipInfo, "foodDaysLeft");
		if (daysLeft < 5 && !IsCompanionTraveler)
		{
			Log_Info(StringFromKey("food_10", chr.Ship.Name, FindRussianDaysString(daysLeft-1)));
			Log_Info(StringFromKey("food_11"));
			PlaySound("interface\notebook.wav");
		}

		// возможный бунт рабов
		if (IsMainCharacter(chr) && slavesQty > (crewQty * 1.5 + sti(chr.Ship.Crew.Morale)))
		{
			if(rand(2) == 1 && 12 - GetSummonSkillFromNameToOld(chr, SKILL_LEADERSHIP) > rand(10))
			{
				if(IsEntity(&worldMap) && !IsCharacterEquippedArtefact(chr, "totem_02")) // belamour legendary edition
				{
					chr.GenQuest.SlavesMunity = true;
					Log_Info(StringFromKey("food_12"));
					MunityOnShip("SlavesMunity");
				}
			}
		}
		return;
	}

	// Далее код на случай, если еды не хватило
	RemoveCharacterGoodsSelf(chr, GOOD_FOOD, foodStock);
	PlaySound("interface\notebook.wav");
	
	if(!IsCompanionTraveler) Log_Info(StringFromKey("food_13", chr.Ship.Name));
	if (IsMainCharacter(chr))
	{
		AddCharacterHealth(pchar, -1);
		ChangeCharacterComplexReputation(pchar,"authority", -1);
	}
	
	if (crewQty > 1)
	{
		int iDeadCrew = makeint(crewQty/10 +0.5);
		chr.Ship.Crew.Quantity = crewQty - iDeadCrew;
		Statistic_AddValue(pchar, "Sailors_dead", iDeadCrew);
		AddMementoShipBonus(iDeadCrew);
		Achievment_SetStat(21, iDeadCrew);
		if(!IsCompanionTraveler) Log_Info(StringFromKey("food_14"));
	}

	if (slavesQty > 0)
	{
		RemoveCharacterGoodsSelf(chr, GOOD_SLAVES, makeint(slavesQty/5 + 0.5));
		if(!IsCompanionTraveler) Log_Info(StringFromKey("food_15"));
	}

	int nMoraleDecreaseQ = 12 - GetSummonSkillFromNameToOld(chr, SKILL_LEADERSHIP);
	nMoraleDecreaseQ = makeint(makefloat(nMoraleDecreaseQ) * (1-SZN_GetModifierMtp(M_CREW_MORALE_DEBUFF_MTP, 0.0, 0.0, 0.99)));
	chr.Ship.Crew.Morale = func_max(MORALE_MIN, sti(chr.Ship.Crew.Morale) - nMoraleDecreaseQ);
}

// Warship. Вынес в отдельный метод
void DailyEatCrewUpdateForShip(ref rChar, bool IsCompanionTraveler) // IsCompanionTraveler - спец флаг для компаньонов-путешественников
{
	object shipInfo;
	SetShipMaintenanceInfo(rChar, &shipInfo);
	int iCrewQty = GetCrewQuantity(rChar);
	int slavesQty = GetCargoGoods(rChar, GOOD_SLAVES);
	int cn, morale, nMoraleDecreaseQ, iDeadCrew;
	if (iCrewQty + slavesQty < 1) return;
	if (!CheckAttribute(rChar, "Ship.Crew.Morale")) rChar.Ship.Crew.Morale = 50;

	// Расчёт медицины
	DailyMedicamentUpdate(rChar, IsCompanionTraveler, &shipInfo, iCrewQty, slavesQty);
	if (iCrewQty + slavesQty < 1)
	{
		UpdatePlayerSquadronPower();
		return;
	}

	DailyRumUpdate(rChar, IsCompanionTraveler, &shipInfo, iCrewQty);

	iCrewQty = GetCrewQuantity(rChar);
	// рассчет перегруза команды на мораль  и авторитет -->
	if(iCrewQty > GetOptCrewQuantity(rChar) && !IsCharacterEquippedArtefact(rChar, "talisman4"))
	{
		float debuff = makefloat(1+rand(3));
		debuff *= (1-SZN_GetModifierMtp(M_CREW_MORALE_DEBUFF_MTP, 0.0, 0.0, 0.99));
		AddCrewMorale(rChar, -makeint(debuff));
		ChangeCharacterComplexReputation(pchar,"authority", -0.1);
	} 
	// рассчет перегруза команды на мораль <--

	if (IsEquipCharacterByItem(pchar, "greenIdol")) AddCrewMorale(rChar, -1);
	
	// расчёт долга на мораль
	if(iCrewQty > 0 && CheckAttribute(PChar, "CrewPayment"))
	{
		cn = makeint(PChar.CrewPayment);
		if(cn > 32000) cn = 32000;
		if(rand(cn) > 1000)
		{
			ChangeCharacterComplexReputation(pchar,"authority", -0.2);
			AddCrewMorale(rChar, -1);
			if(i > 0 && rand(5) == 2 && !CheckAttribute(rChar, "OfficerWantToGo.DontGo") && !IsEquipCharacterByArtefact(rChar, "totem_04"))
			{
				rChar.loyality = sti(rChar.loyality) - 1;
			}
		}
	}

	DailyFoodUpdate(rChar, IsCompanionTraveler, &shipInfo, iCrewQty, slavesQty);
	
	if(sti(rChar.index) == GetMainCharacterIndex())
	{
		if(sti(rChar.Ship.Crew.Morale) <= MORALE_MIN)
		{
			//int locidx = FindLocation(rChar.location); // не используется
			if(IsEntity(&worldMap) && GetCrewQuantity(rChar) > 0 && !IsCharacterEquippedArtefact(rChar, "totem_02"))
			{
				Log_Info(StringFromKey("food_16", rChar.Ship.Name));
				MunityOnShip("ShipMunity");
			}
		}
	}
	else
	{
		if(GetShipRemovable(rChar) && !CheckAttribute(rChar, "OfficerWantToGo.DontGo") && !IsCompanionTraveler && !IsEquipCharacterByArtefact(rChar, "totem_04")) // ПГГ, квестовые оффы и компаньоны-путешественники не бунтуют
		{
			if(sti(rChar.Ship.Crew.Morale) <= MORALE_MIN || sti(rChar.loyality) <= 0) // допуск, что лояльность есть у всех офов
			{
				if(GetCrewQuantity(rChar) > 0 && !IsCharacterEquippedArtefact(rChar, "totem_02"))
				{
					Log_Info(StringFromKey("food_16", rChar.Ship.Name));
					Log_Info(StringFromKey("food_17"));
					Statistic_AddValue(PChar, "ShipMunity", 1);
					RemoveCharacterCompanion(PChar, rChar);
					//fix  ПГГ
					if(!CheckAttribute(rChar, "PGGAi"))
					{
						rChar.LifeDay = 0; // стереть при выходе
					}
					else
					{
						rChar.PGGAi.IsPGG = true;
						rChar.RebirthPhantom = true;
						rChar.PGGAi.location.town = PGG_FindRandomTownByNation(sti(rChar.nation));
						rChar.Dialog.FileName = "PGG_Dialog.c";
						rChar.Dialog.CurrentNode = "Second Time";
						PGG_ChangeRelation2MainCharacter(rChar, -20);
					}
					rChar.location = ""; // нафиг, нафиг..а то в таверне появлялся...
					rChar.location.group = "";
					rChar.location.locator = "";
				}
			}
		}
	}
    // Механика мощи
    UpdatePlayerSquadronPower();
}

void DailyTradersMoneyUpdate()
{
	ref rCharacter;
	
	for(int n = 0; n < MAX_CHARACTERS; n++)
	{
		makeref(rCharacter,Characters[n]);
		if (CheckAttribute(rCharacter, "Merchant.type")) // торговцы 
		{
			if(rCharacter.Merchant.type != "jeweller")
			{
				if(sti(rCharacter.money) > TRADER_MAX_MONEY || sti(rCharacter.money) < TRADER_MIN_MONEY) 	
				{
					rCharacter.money = TRADER_MIN_MONEY + rand(TRADER_NORM);
					if(ShipBonus2Artefact(pchar, SHIP_LADYBETH))
					{
						rCharacter.money = sti(rCharacter.money) * 2;
					}
				}
				if(CheckAttribute(rCharacter, "City") && rCharacter.City == GetLadyBethCity())
				{
					rCharacter.money = sti(rCharacter.money) * 2;
				}
				if(rCharacter.Merchant.type == "GasparGold") 
				{
					if(CheckAttribute(rCharacter, "items"))
						DeleteAttribute(rCharacter, "items");
					rCharacter.money = 5000000;
					GiveItemToTrader(rCharacter);
				}
			}
			else
			{
				if(sti(rCharacter.money) > USURER_MAX_MONEY || sti(rCharacter.money) < USURER_MIN_MONEY) 	
				{
					rCharacter.money = USURER_MIN_MONEY + rand(USURER_NORM);
				}
			}	
		}
	}
}

