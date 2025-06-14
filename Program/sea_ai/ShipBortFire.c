// залп в авторежиме
void Ship_BortFire()
{
	float	dx, dy, dz, d2x, d2y, d2z;
	float	ax = 0.0;
	float 	az = 0.0;
	float   vz = 0.0;
	aref	firedShip;
	string	bortName;
	ref rCharacter = GetCharacter(GetEventData());
	firedShip = GetEventData();
	bortName = GetEventData();
	
	string sMode = GetEventData();
	
	// TUTOR-ВСТАВКА
	if(TW_IsActive() && IsMainCharacter(rCharacter))
	{
		if(sMode == "auto" && objTask.sea_battle == "1_AutoFire")
		{
			if(TW_IncreaseCounter("sea_battle", "AutoFire_do", 1))
				TW_FinishSea_Battle_1_AutoFire();
		}
		if(sMode == "aiming" && objTask.sea_battle == "3_AimingFire")
		{
			objTask.sea_battle = "4_AimingFire";
            TW_ColorWeak(TW_GetTextARef("AimingFire_do"));
            string sText = StringFromKey("Tutorial_16", GKIC("FireCamera_Set", "SailingFire"));
            TW_AddBottomText("AimingFire_exit", sText, "Default");
            TW_RecalculateLayout();
		}
	}
	
    // boal fix charge 29.11.03 -->
    if (bortName == "cannonr" || bortName == "cannonl")
    { // только для бортов проверяем.
        rCharacter.BOAL_ReadyCharge = "0";
    }
    //Log_SetStringToLog("Ship_BortFire " + rCharacter.id + " "+ bortName);
	// boal fix charge 29.11.03 <--
	
	// boal  05.12.03 check skill -->
	bool  bTempNotEnoughBalls = false;
	if (sti(rCharacter.index) == GetMainCharacterIndex())
	{
		ballNumber = 0;
        bTempNotEnoughBalls = bNotEnoughBalls;
	}
	bool bOfficer;
	bOfficer = (sti(rCharacter.index) == GetMainCharacterIndex()) || CheckAttribute(rCharacter, "Payment"); // аналог IsCompanion(rCharacter) только без цикла и кучи иф
	if (bDisableMapEnter && bOfficer && !bTempNotEnoughBalls) // use only in battle
	{
        if (bortName == "cannonr" || bortName == "cannonl")
        {
            AddCharacterExpToSkill(rCharacter, "Cannons", 3);
            ChangeCrewExp(rCharacter, "Cannoners", 0.28);
        }
        else
        {
            AddCharacterExpToSkill(rCharacter, "Cannons", 1);
            ChangeCrewExp(rCharacter, "Cannoners", 0.1);
        }
        //AddCharacterExpToSkill(rCharacter, "Accuracy", 1);
    }
    else
    {
    	if (bortName == "cannonr" || bortName == "cannonl")
        {
            ChangeCrewExp(rCharacter, "Cannoners", 0.08);
        }
        else
        {
            ChangeCrewExp(rCharacter, "Cannoners", 0.03);
        }
    }
    // boal <--
	
	//belamour расчет бонуса от противооткатной системы 
	if(sti(rCharacter.index) == GetMainCharacterIndex())
	{
		if(HasShipTrait(rCharacter, "trait12"))
		{
			if(CheckAttribute(rCharacter,"Tmp.LastBortFire") && rCharacter.Tmp.LastBortFire == bortName)
			{
				if(!CheckAttribute(rCharacter,"Tmp.LastBortFire.Bonus"))
				{
					rCharacter.Tmp.LastBortFire.Bonus = 6;
				}
				else
				{
					rCharacter.Tmp.LastBortFire.Bonus = sti(rCharacter.Tmp.LastBortFire.Bonus) + 6;
					if(sti(rCharacter.Tmp.LastBortFire.Bonus) > 35)
						rCharacter.Tmp.LastBortFire.Bonus = 35;
				}
				//Log_testinfo("Выстрел с борта: " + bortName + " повысил бонус до: " + stf(rCharacter.Tmp.LastBortFire.Bonus));
			}
			else
			{
				DeleteAttribute(rCharacter,"Tmp.LastBortFire.Bonus");
			}
			
			rCharacter.Tmp.LastBortFire = bortName;
		}
		else
		{
			DeleteAttribute(rCharacter,"Tmp.LastBortFire");
		}
	}
	
	if(sMode == "aiming")
		return;
	
	dx = GetEventData();
	dy = GetEventData();
	dz = GetEventData();
	d2x = GetEventData();
	d2y = GetEventData();
	d2z = GetEventData();

	SendMessage(&SeaOperator, "lisffffff", MSG_SEA_OPERATOR_FIRE, firedShip, bortName, dx, dy, dz, d2x, d2y, d2z);
}
