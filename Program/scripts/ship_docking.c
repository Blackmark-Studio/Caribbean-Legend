// Функции для стоянки кораблей в порту

// Старый метод для совместимости
int GetPortManPrice(int Price, ref NPChar)
{
    if (!CheckAttribute(NPChar, "PortManPrice"))
	{
		NPChar.PortManPrice = (0.06 + frnd()*0.1);
	}
	return makeint(Price * stf(NPChar.PortManPrice) /10 ) * 10;
}

// Расчёт цены стоянки
int GetPortManPriceExt(ref NPChar, ref chref)
{
	int price = makeint( sti(RealShips[sti(chref.Ship.Type)].Price) * (7 + MOD_SKILL_ENEMY_RATE/2) * (3 + GetNationRelation2MainCharacter(sti(NPChar.nation)))/360.0 );
	
	// для высокой сложности - x2 цена
	if (MOD_SKILL_ENEMY_RATE >= 6) price += price;
	return price;
}

// Сохраняем цены в портмана в ходе диалога
void PortmanCalculatePrices(ref NPChar, ref chref)
{
	NPChar.MoneyForShip = GetPortManPriceExt(&NPChar, &chref);
	NPChar.MoneyForCrew = GetSalaryForShip(&chref);

	// В Белизе скидка 50%
	if (CheckAttribute(pchar, "questTemp.GS_BelizSkidka") && NPChar.id == "Beliz_portman" && !CheckAttribute(NPChar, "DontNullShipBeliz") && sti(RealShips[sti(chref.Ship.Type)].Class) > 1)
	{
		NPChar.MoneyForShip = sti(NPChar.MoneyForShip)/2;
	}
}

// Оставляем корабль в порту с командой и офицером
void LeaveShipInPortWithCrew(ref NPChar, ref chref)
{
	int summ = makeint(NPChar.MoneyForShip) + makeint(NPChar.MoneyForCrew);
	AddMoneyToCharacter(pchar, -summ);
	chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
	chref.ShipInStockMan = NPChar.id;
	chref.ShipInStockMan.MoneyForShip = summ;
	// chref.ShipInStockMan.MoneyForCrew = NPChar.MoneyForCrew;
	chref.ShipInStockMan.AltDate = GetQuestBookDataDigit(); // для печати
	SaveCurrentNpcQuestDateParam(chref, "ShipInStockMan.Date"); // для расчёта
	RemoveCharacterCompanion(pchar, chref);

	chref.location = "";
	chref.location.group = "";
	chref.location.locator = "";
	NPChar.Portman	= sti(NPChar.Portman) + 1;
	pchar.ShipInStock = sti(pchar.ShipInStock) + 1;

	if(NPChar.id == "Beliz_portman" && CheckAttribute(pchar, "questTemp.GS_BelizSkidka") && !CheckAttribute(NPChar, "DontNullShipBeliz") && sti(RealShips[sti(chref.Ship.Type)].Class) > 1)
	{
		chref.DontNullShip = true;
		NPChar.DontNullShipBeliz = true;
	}

	string capAttr = "captain" + chref.index;
	TEV.DockedShips.(capAttr) = chref.index; // флаг для разбегания команды
}

// Оставляем корабль в порту без команды и офицера
void LeaveShipInPort(ref NPChar, ref chref)
{
	aref arTo, arFrom;
	AddMoneyToCharacter(pchar, -makeint(NPChar.MoneyForShip));
	chref = GetCharacter(NPC_GenerateCharacter("ShipInStockMan_", "citiz_"+(rand(9)+31), "man", "man", 1, NPChar.nation, -1, false, "quest"));
	chref.id = "ShipInStockMan_" + chref.index; //меняем ID на оригинальный
	chref.loyality = MAX_LOYALITY; 
	chref.name = "";
	chref.lastname = "";
	chref.Ship.Crew.Quantity  = 0;
	DeleteAttribute(chref,"ship");
	chref.ship = "";
	
	chref.ShipInStockMan = NPChar.id;
	chref.ShipInStockMan.MoneyForShip = NPChar.MoneyForShip;
	chref.ShipInStockMan.AltDate = GetQuestBookDataDigit(); // для печати
	SaveCurrentNpcQuestDateParam(chref, "ShipInStockMan.Date"); // для расчёта

	ref compref = GetCharacter(sti(NPChar.ShipToStoreIdx));//компаньон, у которого надо забрать корабль
	compref.Ship.Crew.Quantity  = 0;
	RemoveCharacterCompanion(pchar, compref);
	makearef(arTo, chref.ship);
	makearef(arFrom, compref.Ship);
	CopyAttributes(arTo, arFrom);

	compref.ship.type = SHIP_NOTUSED;
	RemoveCharacterCompanion(pchar, compref);
	AddPassenger(pchar, compref, false);
	PortmanDelBakSkill(compref);

	chref.location = "";
	chref.location.group = "";
	chref.location.locator = "";
	NPChar.Portman	= sti(NPChar.Portman) + 1;
	pchar.ShipInStock = sti(pchar.ShipInStock) + 1;

	if(NPChar.id == "Beliz_portman" && CheckAttribute(pchar, "questTemp.GS_BelizSkidka") && !CheckAttribute(NPChar, "DontNullShipBeliz") && sti(RealShips[sti(chref.Ship.Type)].Class) > 1)
	{
		chref.DontNullShip = true;
		NPChar.DontNullShipBeliz = true;
	}
}

// Оставляем корабль на базе
void LeaveShipIslaMona(ref NPChar)
{
	ref chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
	chref.ShipInStockMan = NPChar.id;
	chref.ShipInStockMan.MoneyForShip = 0;
	chref.ShipInStockMan.AltDate = GetQuestBookDataDigit();
	SaveCurrentNpcQuestDateParam(chref, "ShipInStockMan.Date");
	RemoveCharacterCompanion(pchar, chref);
	chref.location = "";
	chref.location.group = "";
	chref.location.locator = "";
	if(sti(RealShips[sti(chref.Ship.Type)].Class) < 2)
	{
		npchar.FstClassInHarbour = 1;
	}
	npchar.portman = sti(npchar.portman)+1;
	pchar.ShipInStock = sti(pchar.ShipInStock)+1;
	ref colony = GetColonyByIndex(FindColony(loadedLocation.fastreload));
	colony.Ship.crew.quantity = sti(colony.Ship.crew.quantity) + sti(chref.Ship.Crew.Quantity);
	chref.Ship.Crew.Quantity = 0;
}


void PortmanDelBakSkill(ref _compref) // hasert
{
	DelBakSkillAttr(pchar);
	ClearCharacterExpRate(pchar);
	RefreshCharacterSkillExpRate(pchar);
	SetEnergyToCharacter(pchar);

	DelBakSkillAttr(_compref);
	ClearCharacterExpRate(_compref);
	RefreshCharacterSkillExpRate(_compref);
	SetEnergyToCharacter(_compref);
}

// Разбегание команды с кораблей в доках
void UpdateCrewInDockedShips()
{
	if (!CheckAttribute(&TEV, "DockedShips")) return;

	aref ships;
	ref captain;
	makearef(ships, TEV.DockedShips);

	for (int i=0; i < GetAttributesNum(&ships); i++)
	{
		aref capAttr = GetAttributeN(&ships, i);
		captain = GetCharacter(sti(GetAttributeValue(&capAttr)));
		if (GetNpcQuestPastDayParam(&captain, "DockedShips") < 29 && CheckAttribute(&captain, "DockedShips.control_year")) continue;
		SaveCurrentNpcQuestDateParam(&captain, "DockedShips");

		// Корабль забрали из порта, заканчиваем упражнение
		if (!CheckAttribute(&captain, "ShipInStockMan"))
		{
			DeleteAttribute(&ships, GetAttributeName(&capAttr));
			DeleteAttribute(&captain, "DockedShips");
			continue;
		}

		float mtp = 0.85 + makefloat(rand(10)) * 0.01; // от 5 до 15% уходит
		captain.Ship.Crew.Quantity = func_max(GetMinCrewQuantity(&captain), makeint(makefloat(sti(captain.Ship.Crew.Quantity)) * mtp + 0.5));
		captain.ShipInStockMan.MoneyForCrew = GetSalaryForShip(&captain);
	}
}