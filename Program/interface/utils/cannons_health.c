bool XI_CannonsHealthTooltip(ref chr, string currentNode, ref header, ref text, ref badText, ref goodText, float health = -1.0)
{
	string bortName = "";
	switch (currentNode)
	{
		case "CANNONS_HEALTH_F": bortName = "cannonF"; break;
		case "CANNONS_HEALTH_B": bortName = "cannonB"; break;
		case "CANNONS_HEALTH_L": bortName = "cannonL"; break;
		case "CANNONS_HEALTH_R": bortName = "cannonR"; break;
		case "CANNONS_HEALTH_ZONE": bortName = "stock"; break;
	}
	if (bortName == "") return false;

	float damageMtp, reloadMtp;
	if (bortName == "stock")
	{
		damageMtp = CAN_GetDamageMtpForHealth(health, 0.0);
		reloadMtp = CAN_GetReloadMtpForHealth(health, 0.0);	
	}
	else
	{
		CAN_CashCannonsHealth(chr, true);
		damageMtp = CAN_GetHealthDamageMtp(chr, bortName);
		reloadMtp = CAN_GetHealthReloadMtp(chr, bortName);
	}

	header = xiStr("CannonsHealthTooltipHeader");
	text = DLGO(xiStr("CannonsHealthTooltipText"));
	string bonusText = xiStr("CannonsDamage") + " " + ToHumanModifierPercent(damageMtp) + "\n";
	bonusText += xiStr("CannonsTime") + " " + ToHumanModifierPercent(-reloadMtp);

	if (damageMtp > 0) goodText += bonusText;
	else if (damageMtp < 0) badText += bonusText;

	CreateTooltipNew(currentNode, header, text, badText, goodText, "", "", "", "", 0, 0, false, false);
	return true;
}

string XI_HumanCannonsHealth(float health)
{
	return DLG_Convert("Cannon_health_" + CAN_HumanCannonsHealthLevel(health), "ShipsDescribe.txt");
}

string XI_CannonsHealthIcon(float health)
{
	return "health_" + CAN_HumanCannonsHealthLevel(health);
}

string XI_GetCannonsHealthIconForStock(ref chr, ref good)
{
	float health = CAN_GetCannonsStockHealth(chr, good.name);
	return XI_CannonsHealthIcon(health);
}


