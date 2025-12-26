void SetShipPerks(ref chr, string sIndex)
{
	SetNodeUsing("SHIP_PERK1" + sIndex, false);
	SetNodeUsing("SHIP_PERK2" + sIndex, false);
	SetNodeUsing("SHIP_PERK_BORDER1" + sIndex, false);
	SetNodeUsing("SHIP_PERK_BORDER2" + sIndex, false);
	SetNodeUsing("SHIP_PERK_BACKGROUND1" + sIndex, false);
	SetNodeUsing("SHIP_PERK_BACKGROUND2" + sIndex, false);
	SetNodeUsing("SHIP_AUDIT_STAMP" + sIndex, false);

	int iShipType = GetCharacterShipType(chr);
	if (iShipType == SHIP_NOTUSED) return;

	string borderTexture = "border";
	string specialityName = GetShipSpecDesc(chr);
	string traitName = GetShipTraitDesc(chr);
	ref realShip = GetRealShip(iShipType);
	if (CheckAttribute(realShip, "tuning.SpecialityUpgrade")) borderTexture = "border_upgraded";

	SetNewGroupPicture("SHIP_PERK1" + sIndex, "PERKS_SHIPS", specialityName);
	SetNewGroupPicture("SHIP_PERK2" + sIndex, "PERKS_SHIPS", traitName);
	SetNewGroupPicture("SHIP_PERK_BORDER1" + sIndex, "PERKS_SHIPS", borderTexture);
	SetNewGroupPicture("SHIP_PERK_BORDER2" + sIndex, "PERKS_SHIPS", "border");
	SetNewGroupPicture("SHIP_PERK_BACKGROUND1" + sIndex, "PERKS_SHIPS", "background");
	SetNewGroupPicture("SHIP_PERK_BACKGROUND2" + sIndex, "PERKS_SHIPS", "background");
	if (CheckAttribute(realShip, "tuning.Audit"))
	{
		SetNewGroupPicture("SHIP_AUDIT_STAMP" + sIndex, "PERKS_SHIPS", "audit_stamp");
		SetNodeUsing("SHIP_AUDIT_STAMP" + sIndex, true);
	}
	if (specialityName != "") SetNodeUsing("SHIP_PERK1" + sIndex, true);
	if (traitName != "")      SetNodeUsing("SHIP_PERK2" + sIndex, true);
	if (specialityName != "") SetNodeUsing("SHIP_PERK_BORDER1" + sIndex, true);
	if (traitName != "")      SetNodeUsing("SHIP_PERK_BORDER2" + sIndex, true);
	if (specialityName != "") SetNodeUsing("SHIP_PERK_BACKGROUND1" + sIndex, true);
	if (traitName != "")      SetNodeUsing("SHIP_PERK_BACKGROUND2" + sIndex, true);
}

void SetShipPerksTooltip(ref chr, ref sCurrentNode, ref sHeader, ref sText1, ref sText2, ref sText3, ref sPicture, ref sGroup, ref sGroupPicture)
{
	ref realShip;
	if (HasSubStr(sCurrentNode, "SHIP_PERK1"))
	{
		string sPerkName1 = GetShipSpecDesc(chr);
		sGroup = "";
		sGroupPicture = "";
		sHeader = DLG_Convert(sPerkName1, "ShipsPerksDescribe.txt", &NullObject);
		sText1 = DLG_Convert(sPerkName1 + "_desc", "ShipsPerksDescribe.txt", &NullObject);
		sText3 = DLG_Convert(sPerkName1 + "_desc2", "ShipsPerksDescribe.txt", &NullObject);
		realShip = GetRealShip(GetCharacterShipType(chr));
		if (CheckAttribute(realShip, "tuning.SpecialityUpgrade")) sText3 += newStr()  + " " + newStr() + DLG_Convert("SpecialityUpgrade", "ShipsPerksDescribe.txt", &NullObject);
	}
	else if (HasSubStr(sCurrentNode, "SHIP_PERK2"))
	{
		string sPerkName2 = GetShipTraitDesc(chr);
		realShip = GetRealShip(GetCharacterShipType(chr));
		sGroup = "";
		sGroupPicture = "";
		sHeader = DLG_Convert(sPerkName2, "ShipsPerksDescribe.txt", &NullObject);
		sText1 = DLG_Convert(sPerkName2 + "_desc", "ShipsPerksDescribe.txt", &NullObject);
		if (sPerkName2 == "sp4") sText3 = DLG_Convert(sPerkName2 + "_desc2", "ShipsPerksDescribe.txt", realShip);
		else sText3 = DLG_Convert(sPerkName2 + "_desc2", "ShipsPerksDescribe.txt", &NullObject);
		if (CheckAttribute(realShip, "DeadSailors"))
		{
			aref arShipBonus;
			makearef(arShipBonus, realShip.DeadSailors);
			sText3 += newStr() + GetAssembledString(GetConvertStr("sp3_SailorsBoardingBonus_desc","ShipsPerksDescribe.txt"), arShipBonus)
									+ GetAssembledString(GetConvertStr("sp3_SailorsBoardingBonus1_desc","ShipsPerksDescribe.txt"), realShip);
			sText3 += newStr() + GetAssembledString(GetConvertStr("sp3_SurrenderChanceBonus_desc","ShipsPerksDescribe.txt"), arShipBonus)
									+ GetAssembledString(GetConvertStr("sp3_SurrenderChanceBonus1_desc","ShipsPerksDescribe.txt"), realShip);
		}
	}
}