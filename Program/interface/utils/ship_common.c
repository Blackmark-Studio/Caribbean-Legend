// Модуль общих интерфейсных штук для кораблей

// Заполнение корабельной таблицы характеристик
void SetShipOTHERTable2(string tabName, ref chr, string iconCell = "td1", string titleCell = "td2", string valueCell = "td3", string userdataPostfix = "")
{
	ref refBaseShip = GetRealShip(int(chr.ship.type));
	aref table = GetAref(&GameInterface, tabName);
	table.select = 0;
	table.hr.(iconCell).str = "";
	for (int i=1; i<=9; i++)
	{
		string row = "tr" + i;
		table.(row).(iconCell).icon.width = 35;
		table.(row).(iconCell).icon.height = 35;
		table.(row).(iconCell).icon.offset = "0, 2";
		table.(row).(titleCell).align = "left";
		table.(row).(titleCell).textoffset = "2,0";
		table.(row).(valueCell).align = "right";
		table.(row).(iconCell).icon.group = "EQUIP_ICONS";
	}

	int currentHp = int(chr.ship.hp);
	int maxHp = int(refBaseShip.hp);
	table.tr1.UserData.ID = "Hull";
	table.tr1.(iconCell).icon.image = "Hull";
	table.tr1.(titleCell).str = XI_ConvertString("Hull");
	table.tr1.(valueCell).str = XI_GetHumanCurrentMax(currentHp, maxHp);
	table.tr1.(valueCell).color = CheckAttribute(refBaseShip, "Tuning.HP") ? argb(255,128,255,255) : ARGB_Color("white");

	int currentCrew = GetCrewQuantity(chr);
	int maxCrew = GetMaxCrewQuantity(chr);
	table.("userdata" + userdataPostfix).minCrew = GetMinCrewQuantity(chr);
	table.tr2.UserData.ID = "Crew";
	table.tr2.(iconCell).icon.image = "Crew";
	table.tr2.(titleCell).str = XI_ConvertString("Crew");
	table.tr2.(valueCell).str = XI_GetHumanCurrentMax(currentCrew, maxCrew, "", " " + DLG_DeclensionKey(func_max(currentCrew, maxCrew), "people"));
	table.tr2.(valueCell).color = CheckAttribute(refBaseShip, "Tuning.MaxCrew") ? argb(255,128,255,255) : ARGB_Color("white");

	table.tr5.UserData.ID = "MaxSpeed";
	float maxSpeed = FindShipSpeedMax(chr);
	table.tr5.(iconCell).icon.image = "Speed";
	table.tr5.(titleCell).str = XI_ConvertString("MaxSpeed");
	table.tr5.(valueCell).str = ToHumanNumber(maxSpeed, 1) + " " + DLG_DeclensionKeyFloat(maxSpeed, "speed_units");
	table.tr5.(valueCell).color = CheckAttribute(refBaseShip, "Tuning.SpeedRate") ? argb(255,128,255,255) : ARGB_Color("white");
	
	table.tr6.UserData.ID = "Speed";
	float currentSpeed = FindShipSpeed(chr);
	table.tr6.(iconCell).icon.image = "Speed";
	table.tr6.(titleCell).str = XI_ConvertString("Speed");
	table.tr6.(valueCell).str = ToHumanNumber(currentSpeed, 1) + " " + DLG_DeclensionKeyFloat(currentSpeed, "speed_units");
	table.tr6.(valueCell).color = CheckAttribute(refBaseShip, "Tuning.SpeedRate") ? argb(255,128,255,255) : ARGB_Color("white");

	table.tr7.UserData.ID = "Maneuver";
	float turnRate = FindShipTurnRate(chr);
	float turnRateMax = FindShipTurnrateMax(chr);
	table.("userdata" + userdataPostfix).turnRate = FloatTostring(turnRateMax * turnRate, 1);
	table.("userdata" + userdataPostfix).turnRatePercent = int(turnRate*100)*0.01;
	table.("userdata" + userdataPostfix).turnRateMax = turnRateMax;
	table.tr7.(iconCell).icon.image = "Maneuver";
	table.tr7.(titleCell).str = XI_ConvertString("Maneuver");
	table.tr7.(valueCell).str = XI_HumanTurnRate(turnRateMax);
	table.tr7.(valueCell).color = CheckAttribute(refBaseShip, "Tuning.TurnRate") ? argb(255,128,255,255) : ARGB_Color("white");

	table.tr3.UserData.ID = "Rig";
	table.tr3.(iconCell).icon.image = "AgainstWind";
	table.tr3.(titleCell).str = XI_ConvertString("Sails");
	table.tr3.(valueCell).str = XI_ConvertString(GetRigType(chr));
	table.tr3.(valueCell).color = CheckAttribute(refBaseShip, "Tuning.rig") ? argb(255,128,255,255) : ARGB_Color("white");

	RecalculateCargoLoad(chr);
	int currentCapacity = GetCargoLoad(chr);
	int maxCapacity = GetCargoMaxSpace(chr);
	table.("userdata" + userdataPostfix).currentCapacity = currentCapacity;
	table.("userdata" + userdataPostfix).maxCapacity = maxCapacity;
	table.("userdata" + userdataPostfix).overload = currentCapacity > maxCapacity;
	table.tr4.UserData.ID = "Capacity";
	table.tr4.(iconCell).icon.image = "Capacity";
	table.tr4.(titleCell).str = XI_ConvertString("Capacity");
	table.tr4.(valueCell).str =  XI_GetHumanCurrentMax(currentCapacity, maxCapacity);
	table.tr4.(valueCell).color = CheckAttribute(refBaseShip, "Tuning.Capacity") ? argb(255,128,255,255) : ARGB_Color("white");

	table.tr8.UserData.ID = "sCannons";
	table.tr8.(iconCell).icon.image = "Caliber";
	table.tr8.(titleCell).str = XI_ConvertString("Caliber");
	int currentCaliber = GetCannonCaliber(int(chr.Ship.Cannons.Type));
	int maxCaliber = int(refBaseShip.MaxCaliber);
	string caliberText = DLG_DeclensionKey(func_max(currentCaliber, maxCaliber), "pounds");
	table.tr8.(valueCell).str = XI_GetHumanCurrentMax(currentCaliber, maxCaliber, " " + caliberText, " " + caliberText);

	int maxCannonsQty = int(refBaseShip.CannonsQuantity);
	int cannonsQty = GetCannonsNum(chr);
	bool maxCannons = cannonsQty == maxCannonsQty;
	table.tr9.UserData.ID = "CannonType";
	table.tr9.(iconCell).icon.group = "EQUIP_ICONS";
	table.tr9.(iconCell).icon.image = "Cannons";
	table.tr9.(titleCell).str = XI_ConvertString(GetCannonType(int(chr.Ship.Cannons.Type)) + "s2");
	if (sti(chr.Ship.Cannons.Type) == CANNON_TYPE_NONECANNON) table.tr9.(valueCell).str = "";
	else table.tr9.(valueCell).str = XI_GetHumanCurrentMax(cannonsQty, maxCannonsQty, "", " " + DLG_DeclensionKey(maxCannonsQty, "shipGun"));

	Table_UpdateWindow(tabName);

	XI_FillBar("BAR_HP", 0, maxHp, currentHp);
	XI_FillBar("BAR_CREW", 0, maxCrew, currentCrew);
	XI_FillBar("BAR_SP", 0, 100, int(GetSailPercent(chr)));
	XI_FillBar("BAR_CAPACITY", 0, maxCapacity, currentCapacity);
}

void XI_FillBar(string barName, int min, int max, int value)
{
	GameInterface.StatusLine.(barName).Max   = max;
	GameInterface.StatusLine.(barName).Min   = min;
	GameInterface.StatusLine.(barName).Value = value;
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,barName,0);
}


void XI_ShipTableTooltip(ref chr, ref refBaseShip, string tabName, ref header, ref text, ref badText, ref goodText, ref sGroup, ref sGroupPicture, ref windRose, ref secondChr = nullptr, string userdataPostfix = "")
{
	aref table = GetAref(&GameInterface, tabName);
	int nChooseNum = SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "TABLE_OTHER", 1);
	string sRow = "tr"+nChooseNum;
	if (nChooseNum < 1) return;
	if (sRow + ".UserData" !in &table) return; 

	aref userdata = table.("userdata" + userdataPostfix)$aref;

	aref tuning = GetAref(refBaseShip, "tuning.modifiers", true);
	header = XI_ConvertString(table.(sRow).UserData.ID);
	text  = DLG_Convert(table.(sRow).UserData.ID, "ShipsDescribe.txt", &userdata);
	if (table.(sRow).UserData.ID == "CannonType")
	{
		ref cannon = GetCannonOnBort(chr, "cannonl");
		if (cannon == nullptr) return;
		int cannonType = GetCannonTypeByBort(chr, "cannonl");
		text += XI_HumanCannonAdditionalStats(cannon, cannonType);
		
		sGroup = "GOODS";
		sGroupPicture = GetCannonType(cannonType) + "_" + GetCannonCaliber(cannonType);
	}

	// трюм
	if (table.(sRow).UserData.ID == "Capacity" && sti(chr.ship.type) != SHIP_NOTUSED)
	{
		float overloadPercent = float(ceil(float(userdata.currentCapacity) / float(userdata.maxCapacity) * 100) * 0.01);
		goodText = XI_ConvertString("Used") + ": " + ToHumanPercent(overloadPercent);
		if (bool(userdata.overload)) badText += GetConvertStr("SourceOverload", "RPGDescribe.txt");
	}

	if (table.(sRow).UserData.ID == "Speed") SetModifiersStatText(chr, &tuning, M_SHIP_SPEED, &goodText, "ToHumanModifierPercent", 0.0);
	if (table.(sRow).UserData.ID == "Maneuver") 
	{
		if (CurrentInterface != INTERFACE_SHIPYARD)	goodText += DLG_Convert("ManeuverCurrent", "ShipsDescribe.txt", &userdata);
		SetModifiersStatText(chr, &tuning, M_SHIP_TURNRATE, &goodText, "ToHumanModifierPercent", 0.0);
	}
	if (table.(sRow).UserData.ID == "Crew") SetModifiersStatText(chr, &tuning, M_SHIP_MAXCREW, &goodText, "ToHumanModifierPercent", 0.0);
	if (table.(sRow).UserData.ID == "Capacity") SetModifiersStatText(chr, &tuning, M_SHIP_CAPACITY, &goodText, "ToHumanModifierPercent", 0.0);
	
	if (table.(sRow).UserData.ID == "Rig")
	{
		text = "";
		goodText = GetConvertStr(table.(sRow).UserData.ID, "ShipsDescribe.txt");
		windRose = true;
		if (secondChr == nullptr) return;
		
		header = XI_ConvertString(table.(sRow).UserData.ID);
		text = XI_ConvertString(GetRealShip(int(pchar.ship.type)).BaseName) + " '" + pchar.ship.name + "'";
		if (!IsMainCharacter(chr)) secondChr = chr; 
		refBaseShip = GetRealShip(int(secondChr.ship.type));
		badText = XI_ConvertString(refBaseShip.BaseName) + " '" + secondChr.ship.name + "'";
	}
}

string XI_HumanTurnRate(float value)
{
	string name = xiStr("human_turn_rate_6");
	if (value < HUMAN_TURN_RATE_STEP_1) name = xiStr("human_turn_rate_1");
	else if (value < HUMAN_TURN_RATE_STEP_2) name = xiStr("human_turn_rate_2");
	else if (value < HUMAN_TURN_RATE_STEP_3) name = xiStr("human_turn_rate_3");
	else if (value < HUMAN_TURN_RATE_STEP_4) name = xiStr("human_turn_rate_4");
	else if (value < HUMAN_TURN_RATE_STEP_5) name = xiStr("human_turn_rate_5");
	return name;
}

void SetModifiersStatText(ref chr, ref equipTable, string modifier, ref result, string formatter, float base)
{
	string bonusText = "";
	for (string reason, aref source: equipTable.(modifier)$aref)
	{
		float value = float(source);
		if (value == 0.0) continue;
		bonusText += GetHumanReadableReason(reason, chr) + ": " + call formatter(base+value) + NewStr();
	}

	if (bonusText != "") bonusText = newStr() + " " + newStr() + " " + bonusText;
	result += bonusText;
}

void XI_UpdateCrewTable(string tableName, int morale, int exp)
{
	Table_Clear(tableName, false, true, false);
	aref table = GameInterface.(tableName)$aref;
	table.userdata.morale = morale;
	table.userdata.exp = exp;
	table.hr.td1.str = "";
	table.hr.td2.str = xiStr("Crew");
	table.hr.td2.textoffset = "-90,0";
	table.tr1.td1.str = xiStr("Exp");
	table.tr1.td2.str = XI_ConvertString(GetExpName(int(exp)));
	table.tr1.td1.textoffset = "68,-15";
	table.tr1.td2.textoffset = "0,-15";
	table.tr1.td1.align = "left";
	table.tr1.td2.align = "right";
	table.tr1.td1.icon.group = "HIRE_EFFECTS";
	table.tr1.td1.icon.image = "Louis";
	table.tr1.td1.icon.offset = "-2, 18";
	table.tr1.td1.icon.width = 47;
	table.tr1.td1.icon.height = 47;

	table.tr2.td1.str = xiStr("Morale");
	table.tr2.td2.str = XI_ConvertString(GetMoraleName(morale));
	table.tr2.td1.textoffset = "68,-15";
	table.tr2.td2.textoffset = "0,-15";
	table.tr2.td1.align = "left";
	table.tr2.td2.align = "right";
	table.tr2.td1.icon.group = "MORALE_SMALL";
	table.tr2.td1.icon.image = GetMoraleGroupPicture(float(morale));
	table.tr2.td1.icon.offset = "0, 20";
	table.tr2.td1.icon.width = 47;
	table.tr2.td1.icon.height = 47;
	Table_UpdateWindow(tableName);
}
void XI_SetCrewQualityStates(ref chr, string index = "", string prefix = "")
{
	int morale = GetCharacterCrewMorale(chr);
	float exp = GetCrewExp(chr);
	XI_UpdateCrewTable(prefix + "TABLE_CREW" + index, morale, exp);
	XI_FillBar(prefix + "BAR_CrewMorale" + index, 0, MORALE_MAX, morale);
	XI_FillBar(prefix + "BAR_CrewExp" + index, 0, EXP_MAX, int(exp));
}

void FillSuppliesTable(int mode, ref chr)
{
	if (int(chr.ship.type) == SHIP_NOTUSED) return;

	EI_DeleteTriggerFrame();
	CloseTooltipNew();
	bool isGoodsMode = mode == 1;
	SetNodeUsing("TABLE_SUPPLIES", !isGoodsMode);
	SetNodeUsing("TABLE_LIST", isGoodsMode);
	SetNodeUsing("SCROLL_LIST", isGoodsMode);
	if (mode == 0) XI_FillSupplies(chr);
	else XI_FillGoodsTable(chr);
}

void XI_FillGoodsTable(ref chr)
{
	SetNodeUsing("HELP", true);
	if (!CheckAttribute(&GameInterface, "TABLE_LIST.BackUp"))
	{
		GameInterface.TABLE_LIST.select = 0;
		GameInterface.TABLE_LIST.top    = 0;
		GameInterface.TABLE_LIST.BackUp = true;
		GameInterface.TABLE_LIST.hr.td1.textoffset = "90,0";
	}
	
	int n = 1;
	for (int i, ref good: &Goods)
	{
		int qty = GetCargoGoods(chr, i);
		if (qty <= 0) continue;

		string row = "tr" + n;
		string sGood = good.name;
		GameInterface.TABLE_LIST.(row).index = i;
		GameInterface.TABLE_LIST.(row).td2.str = qty;
		GameInterface.TABLE_LIST.(row).td3.str = GetGoodWeightByType(i, qty);
		GameInterface.TABLE_LIST.(row).td1.icon.group = "GOODS";
		GameInterface.TABLE_LIST.(row).td1.icon.image = sGood;
		GameInterface.TABLE_LIST.(row).td1.icon.offset = "-5, -5";
		GameInterface.TABLE_LIST.(row).td1.icon.width = 47;
		GameInterface.TABLE_LIST.(row).td1.icon.height = 47;
		GameInterface.TABLE_LIST.(row).td1.textoffset = "90,0";
		GameInterface.TABLE_LIST.(row).td1.line_space_modifier = 0.8;
		GameInterface.TABLE_LIST.(row).td1.str = XI_ConvertString(sGood);
		n++;
	}
	SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_LIST", 2, 0);
	Table_UpdateWindow("TABLE_LIST");
}

void XI_FillSupplies(ref chr)
{
	Table_Clear("TABLE_SUPPLIES", false, true, false);
	SetNodeUsing("HELP", false);

	int supplyGoods[] = {GOOD_BALLS, GOOD_BOMBS, GOOD_GRAPES, GOOD_KNIPPELS, GOOD_POWDER};
	supplyGoods += {GOOD_WEAPON};
	supplyGoods += {GOOD_FOOD, GOOD_RUM, GOOD_MEDICAMENT};
	supplyGoods += {GetCannonGoodsIdxByType(GetCaracterShipCannonsType(chr)),GOOD_PLANKS, GOOD_SAILCLOTH};
	int goodsSize = GetArraySize(&supplyGoods);
	aref table = GameInterface.TABLE_SUPPLIES$aref;
	touchattr(table.userdata);
	aref userdata = table.userdata$aref;
	SetShipMaintenanceInfo(chr, &userdata);
	
	int currentCrew = GetCrewQuantity(chr);
	aref approximation = touchattr(userdata.approximation);
	SetCrewQuantityFull(chr);
	SetShipMaintenanceInfo(chr, &approximation); // апроксимация для фулл-команды
	SetCrewQuantity(chr, currentCrew);

	SetShipMaintenanceInfo(chr, &userdata);

	userdata.crewQty = currentCrew;
	int bortFireSize = func_max(GetBortCannonsQty(chr, "cannonr"), GetBortCannonsQty(chr, "cannonl"));
	int row = 1;
	int col = 1;
	int maxCol = 3;
	for (int i = 0; i < goodsSize; i++)
	{
		string sRow = "tr" + row;
		string sCol = "td" + col;
		int goodIdx = supplyGoods[i];
		ref good = &Goods[goodIdx];
		int qty = goodIdx > -1 ? GetCargoGoods(chr, goodIdx) : 0;
		int color = qty > 0 ? COLOR_NORMAL : COLOR_DESELECT;
		table.(sRow).(sCol).userdata.goodIdx = goodIdx;
		table.(sRow).(sCol).userdata.goodName = good.name;
		table.(sRow).(sCol).userdata.qty = qty;
		table.(sRow).(sCol).userdata.supplyType = i;
		table.(sRow).(sCol).userdata.bortFireSize = bortFireSize;
		if (goodIdx == GOOD_POWDER) table.(sRow).(sCol).userdata.mineQty = qty / MINE_POWDER;
		table.(sRow).(sCol).icon.group = "GOODS";
		table.(sRow).(sCol).icon.image = good.name;
		table.(sRow).(sCol).icon.offset = "57, 0";
		table.(sRow).(sCol).icon.width = 58;
		table.(sRow).(sCol).icon.height = 58;
		table.(sRow).(sCol).textoffset = "0, 24";
		table.(sRow).(sCol).str = LowerFirst(XI_GetHumanSupplieStock(chr, goodIdx, i, qty, bortFireSize, &color, &userdata));
		table.(sRow).(sCol).color = color;
		table.(sRow).(sCol).align = "center";
	
		if (col == maxCol)
		{
			row++;
			col = 1;
		}
		else col++;
	}
	Table_UpdateWindow("TABLE_SUPPLIES");
}

int XI_SuppliesStockToColor(int days)
{
	if (days < 5) return COLOR_LIGHT_RED;
	if (days < 10) return COLOR_LIGHT_YELLOW;
	if (days > 20) return COLOR_LIGHT_GREEN;
	return COLOR_NORMAL;
}

string XI_GetHumanSupplieStock(ref chr, int goodIdx, int supplyType, int qty, int bortFireSize, ref color, ref userdata)
{
	object ctx;
	ctx.qty = qty;
	int daysValue;
	if (supplyType <= 4)
	{
		int num = bortFireSize > 0 ? qty / bortFireSize : 0;
		if (num < 1) return xiStr("No");
		return num + " " + DLG_DeclensionKey(num, "bortFire");
	} 
	if (goodIdx == GOOD_WEAPON)
	{
		if (qty == 0) return GetConvertStr("weapon_0", "supplies.txt");
		float comparsion = float(qty) / float(func_max(1,GetCrewQuantity(chr)));
		if (comparsion < 1.0)
		{
			color = COLOR_LIGHT_RED;
			return GetConvertStr("weapon_1", "supplies.txt");
		}
		else if (comparsion < 1.2) return GetConvertStr("weapon_2", "supplies.txt");

		color = COLOR_LIGHT_GREEN;
		return GetConvertStr("weapon_3", "supplies.txt");
	}
	if (goodIdx == GOOD_FOOD) 
	{
		daysValue = CalculateShipFood(chr);
		color = XI_SuppliesStockToColor(daysValue);
		return daysValue > 0 ? FindRussianDaysString(daysValue) : xiStr("No");
	}
	if (goodIdx == GOOD_RUM)
	{
		daysValue = CalculateShipRum(chr);
		color = XI_SuppliesStockToColor(daysValue);
		return daysValue > 0 ? FindRussianDaysString(daysValue) : xiStr("No");
	}
	if (goodIdx == GOOD_MEDICAMENT)
	{
		daysValue = CalculateShipMedicament(chr);
		color = XI_SuppliesStockToColor(daysValue);
		return daysValue > 0 ? FindRussianDaysString(daysValue) : xiStr("No");
	}
	if (goodIdx == GOOD_PLANKS)
	{
		float planksPerDay = GetHullRepairDay(chr, true, 75.0);
		float hullPerDay = GetHullRepairDay(chr, false, 75.0);
		userdata.planksPerDay = planksPerDay;
		userdata.hullPerDay = hullPerDay * 0.01;
		userdata.planks = qty;
		daysValue = planksPerDay > 0.0 ? int(qty / planksPerDay) : 0;
		userdata.hullFullValue = func_fmin(100.0, float(int(hullPerDay * daysValue)) * 0.01);
		if (qty < 1) return xiStr("No");
		return FindRussianDaysString(func_max(1, daysValue));
	}
	if (goodIdx == GOOD_SAILCLOTH)
	{
		float sailClothesPerDay = GetSailRepairDay(chr, true, 75.0);
		float sailsPerDay = GetSailRepairDay(chr, false, 75.0);
		userdata.sailClothesPerDay = sailClothesPerDay;
		userdata.sailsPerDay = sailsPerDay  * 0.01;
		userdata.sailClothes = qty;
		daysValue = sailClothesPerDay > 0.0 ? int(qty / sailClothesPerDay) : 0;
		userdata.sailsFullValue = func_fmin(100.0, float(int(sailsPerDay * daysValue)) * 0.01);
		if (qty < 1) return xiStr("No");
		return FindRussianDaysString(func_max(1, daysValue));
	}

	return DLG_Convert("spareCannons", "supplies.txt", &ctx);
}

bool XI_ShipSuppliesTooltip(ref chr, string currentNode, ref header, ref text, ref goodText, ref badText, ref sGroup, ref sGroupPicture)
{
	if (currentNode != "TABLE_SUPPLIES") return false;

	CloseTooltipNew();
	string sRow = "tr" + (GetSelectedRow(currentNode) + 1);
	string sCol = "td" + (GetSelectedColumn(currentNode) + 1);
	aref userdata = GameInterface.(currentNode).(sRow).(sCol).userdata$aref;
	aref commonUserData = GameInterface.(currentNode).userdata$aref;
	CopyAttributesSafe(&userdata, &commonUserData);
	ref good = &Goods[int(userdata.goodIdx)];
	header = GetGoodName(good);
	text = GetAssembledString(GetGoodDescr(good), good);
	goodText = "";
	if ("cannonIdx" in good) goodText += DLG_Convert("spareCannons_tooltip", "supplies.txt");

	if (int(userdata.supplyType) <= 4 && int(userdata.bortFireSize) > 0) goodText += DLG_Convert("bortFire_tooltip", "supplies.txt", &userdata) + "\n";
	if (int(userdata.supplyType) > 5 && int(userdata.supplyType) < 9) goodText += XI_GetHumanSuppliesEstimationFor(int(userdata.goodIdx), good, &userdata);
	else if (int(userdata.supplyType) < 9 || userdata.mineQty$int(0) > 0) goodText += DLG_ConvertE(good.name + "_tooltip", "supplies.txt", &userdata);
	else if (int(userdata.goodIdx) == GOOD_SAILCLOTH && int(userdata.sailClothes) > 0) goodText += DLG_ConvertE(good.name + "_tooltip", "supplies.txt", &userdata);
	else if (int(userdata.goodIdx) == GOOD_PLANKS && int(userdata.planks) > 0) goodText += DLG_ConvertE(good.name + "_tooltip", "supplies.txt", &userdata);
	CreateTooltipNew(currentNode, header, text, badText, goodText, "", "", "", "", 0, 0, false, false);
	return true;		
}

string XI_GetHumanSuppliesEstimationFor(int goodIdx, ref good, ref userdata)
{
	if (goodIdx == GOOD_MEDICAMENT) userdata.medicamentconsumption = int(userdata.crewmedicamentconsumption) + int(userdata.slavesmedicamentconsumption);
	string result = DLG_Convert(good.name + "_tooltip", "supplies.txt", &userdata);
	if (int(userdata.foodconsumption) == int(userdata.approximation.foodconsumption)) return result;
	
	if (goodIdx == GOOD_MEDICAMENT) userdata.approximation.medicamentconsumption = int(userdata.approximation.crewmedicamentconsumption) + int(userdata.approximation.slavesmedicamentconsumption);
	return result + "\n" + DLG_Convert(good.name + "_approximation_tooltip", "supplies.txt", &userdata)
}

bool XI_CrewQualityTooltip(string currentNode, ref header, ref text, ref goodText, ref badText)
{
	if (currentNode != "TABLE_CREW" && currentNode != "TABLE_CREW2" && currentNode != "HIRE_TABLE_CREW" && currentNode != "HIRE_TABLE_CREW2") return false;

	CloseTooltipNew();
	int row = GetSelectedRow(currentNode);

	aref userdata = GameInterface.(currentNode).userdata$aref;
	if (row == 1)
	{
		header = DLG_Convert("Crew_Exp", "ShipsDescribe.txt");
		text  = DLG_Convert("Crew_Exp_hint", "ShipsDescribe.txt");
	}
	else if (row == 2)
	{
		header = XiStr("Crew Morale");
		text  = XiStr("morale_descr");
	}
	else return false;

	CreateTooltipNew(currentNode, header, text, badText, goodText, "", "", "", "", 0, 0, false, false);
	return true;
}

string XI_HumanCannonAdditionalStats(ref Cannon, int cannonType)
{
	string text = ""; 
	text += NewStr() + "***" + NewStr() + XI_ConvertString("Type") +": " + XI_ConvertString(GetCannonType(cannonType));
	text += NewStr() + XI_ConvertString("Caliber") + ": " + XI_ConvertString("caliber" + GetCannonCaliber(cannonType));
	text += NewStr() + XI_ConvertString("Fire range2") + ": "  + sti(Cannon.FireRange);
	text += NewStr() + XI_ConvertString("CannonsDamage") + ": x" + FloatToString(stf(Cannon.DamageMultiply), 1);
	text += NewStr() + XI_ConvertString("CannonsTime") + ": " + sti(GetCannonReloadTime(Cannon)) + " " + XI_ConvertString("sec.");
	text += NewStr() + XI_ConvertString("Weight") + ": " + sti(Cannon.Weight) + " " + XI_ConvertString("cwt") + NewStr() + "***";
	return text;
}