
void FillUpCannonStats(ref cannonItem, ref chr)
{
	Table_Clear("TABLE_CANNON_STATS", false, true, false);
	aref statTable = GameInterface.TABLE_CANNON_STATS$aref;

	touchattr(GameInterface.TABLE_CANNON_STATS.userdata);
	aref stats = GameInterface.TABLE_CANNON_STATS.userdata$aref;
	stats.DamageMultiply.iconGroup = "EQUIP_ICONS";
	stats.DamageMultiply.iconName = "gundamage";
	stats.DamageMultiply.humanValue = "x" + FloatToString(cannonItem.DamageMultiply, 1);
	stats.DamageMultiply = cannonItem.DamageMultiply;
	stats.firerange.iconGroup = "EQUIP_ICONS";
	stats.firerange.iconName = "radius";
	stats.firerange.humanValue = int(cannonItem.firerange) + " " + xiStr("yard.");
	stats.firerange = cannonItem.firerange;
	stats.reloadtime.iconGroup = "EQUIP_ICONS";
	stats.reloadtime.iconName = "time";
	stats.reloadtime = GetCannonReloadTime(cannonItem);
	stats.reloadtime.humanValue = int(stats.reloadtime) + " " + xiStr("sec.");
	stats.hp.iconGroup = "EQUIP_ICONS";
	stats.hp.iconName = "life";
	stats.hp = IsCharacterEquippedArtefact(chr, "talisman3") ? float(cannonItem.hp) * 1.3 : cannonItem.hp;
	stats.hp.humanValue = int(stats.hp);
	SetFormatedText("CANNON_WEIGHT_VALUE", FloatToString(cannonItem.weight, 1));

	int colIndex = 1;
	int rowIndex = 1;
	for (string statName, aref itemStat: &stats)
	{
		string sRow = "tr" + (rowIndex);
		string sCol = "td" + (colIndex);
		statTable.(sRow).(sCol).icon.group  = itemStat.iconGroup;
		statTable.(sRow).(sCol).icon.width = 32;
		statTable.(sRow).(sCol).icon.height = 32;
		statTable.(sRow).(sCol).icon.image  = itemStat.iconName;
		statTable.(sRow).(sCol).icon.offset = "32, 0";
		statTable.(sRow).(sCol).str = itemStat.humanValue;
		statTable.(sRow).(sCol).align = "center";
		statTable.(sRow).(sCol).textoffset = "0, 18";
		statTable.(sRow).(sCol).statName = statName;
		if (colIndex < 2) colIndex++;
		else
		{
			colIndex = 1;
			rowIndex++;
		}
	}

	Table_UpdateWindow("TABLE_CANNON_STATS");
}

bool XI_CannonStatsTooltip (ref chr, string currentNode, ref header, ref text, ref badText, ref goodText)
{
	CloseTooltipNew();
	if (currentNode == "CANNON_WEIGHT_VALUE")
	{
		header = DLG_Convert("Cannon_weight_header", "ShipsDescribe.txt", &userdata);
		text = DLG_Convert("Cannon_weight_text", "ShipsDescribe.txt", &userdata);
		CreateTooltipNew(currentNode, header, text, badText, goodText, "", "", "", "", 0, 0, false, false);
		return true;
	}

	if (currentNode != "TABLE_CANNON_STATS") return false;

	aref userdata = GameInterface.(currentNode).userdata$aref;
	int row = GetSelectedRow(currentNode) + 1;
	int col = GetSelectedColumn(currentNode) + 1;
	string statName = GameInterface.(currentNode).("tr" + row).("td" + col).statName;
	header = DLG_Convert("Cannon_" + statName + "_header", "ShipsDescribe.txt", &userdata);
	text = DLG_Convert("Cannon_" + statName + "_text", "ShipsDescribe.txt", &userdata);
	if (statName == "hp" && IsCharacterEquippedArtefact(chr, "talisman3")) goodText = GetItemName("talisman3") +": +" + ToHumanPercent(0.30);
	CreateTooltipNew(currentNode, header, text, badText, goodText, "", "", "", "", 0, 0, false, false);
	return true;
}