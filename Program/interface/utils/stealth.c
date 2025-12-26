void SetNewNation(int add, ref curNationIdx)
{
	bool ok, ok2, ok3;
	int iCurNation = curNationIdx;

	iCurNation = iCurNation + add;
	if (iCurNation < 0) iCurNation = 4;
	if (iCurNation > 4) iCurNation = 0;

	SetNewGroupPicture("FLAGPIC", "NATIONS", GetNationNameByType(iCurNation));
	SetNodeUsing("FLAG_BTN", true);
	if (!bBettaTestMode)
	{
		ok3 = bSeaActive && !CheckEnemyCompanionDistance2GoAway(false);
		if (bDisableMapEnter || bLandInterfaceStart || ok3)
			SetSelectable("FLAG_BTN", false);
	}

	ok = !STH_CanUseFlag(iCurNation) && sti(pchar.nation) != iCurNation;
	ok2 = true;
	if (isMainCharacterPatented())
	{
		ok2 = (sti(Items[sti(pchar.EquipedPatentId)].Nation) != iCurNation);
	}
	if (ok && ok2) SetNewNation(add, &iCurNation);
	if (sti(pchar.nation) == iCurNation) SetNodeUsing("FLAG_BTN", false);

	curNationIdx = iCurNation;
}
