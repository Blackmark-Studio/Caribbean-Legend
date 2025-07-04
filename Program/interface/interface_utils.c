//---------------------------------------------------------------------------------------------------
// scrollimage
//---------------------------------------------------------------------------------------------------
void FillScrollImageWithCompanionShips(string sNodeName, int iNotUsed)
{

	DeleteAttribute(&GameInterface, sNodeName);
	GameInterface.(sNodeName).current = -1;

	GameInterface.(sNodeName).ImagesGroup.t0 = "BLANK_SHIP";
	GameInterface.(sNodeName).BadTex1 = 0;
	GameInterface.(sNodeName).BadPic1 = "Not Used";

	//FillShipList(sNodeName + ".ImagesGroup", pchar);

	string attributeName, shipName;
	int iShipType, cn;
	int iListSize = 0;

	int isPossibleToFill = 1;
	for(int i= 0; i< COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(pchar, i);

		if(cn!= -1)
		{
			/*if(GetShipRemovable(&characters[cn]) == 0 && cn != nMainCharacterIndex)
			{
				isPossibleToFill = 0;
			}
			else
			{  */
				isPossibleToFill = 1;
			//}
			if(isPossibleToFill == 1)
			{
				AddShipPictureToList(sNodeName + ".ImagesGroup", GetCharacter(cn));
				iShipType = sti(characters[cn].ship.type);
				if(iShipType != SHIP_NOTUSED)
				{
					ref realShip = GetRealShip(iShipType);
					iShipType = sti(RealShips[iShipType].basetype);

					if (iShipType!= SHIP_NOTUSED)
					{
						shipName = ShipsTypes[iShipType].Name;
						attributeName = "pic" + (iListSize+1);

						GameInterface.(sNodeName).(attributeName).companionIndex = cn;
						GameInterface.(sNodeName).(attributeName).str1 = "#"+" "+ShipsTypes[iShipType].Class;
						GameInterface.(sNodeName).(attributeName).img1 = "ship";
						GameInterface.(sNodeName).(attributeName).tex1 = FindFaceGroupNum(sNodeName + ".ImagesGroup","SHIPS_"+shipName+"_"+realShip.ship.upgrades.hull);

						iListSize++;		
					}
				}
			}
			/*else 
			{
				attributeName = "pic" + (i+1);
				GameInterface.(sNodeName).(attributeName).tex1= 0;
			}  */
		} 
		/*else 
		{
			attributeName = "pic" + (i+1);
			GameInterface.(sNodeName).(attributeName).tex1= 0;
		} */
	}

	GameInterface.(sNodeName).ListSize = iListSize;
	//GameInterface.(sNodeName).NotUsed = iNotUsed;	
	GameInterface.SHIPS_SCROLL.NotUsed = iNotUsed - iListSize + 1;

	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_SCROLL_CHANGE, sNodeName, -1);
}
//---------------------------------------------------------------------------------------------------
void FillScrollImageWithFaces(string sNodeName, int iNotUsed, bool bCompanions, bool bPassengers)
{

	DeleteAttribute(&GameInterface, sNodeName);
	GameInterface.(sNodeName).current = -1;

	GameInterface.(sNodeName).ImagesGroup.t0 = "EMPTYFACE";
	GameInterface.(sNodeName).BadTex1 = 0;
	GameInterface.(sNodeName).BadPic1 = "emptyface";

	ref refCharacter = pchar;

	int iListSize = 0;
	int cn;
	string attributeName;
	aref pRef,pRef2;
	string PsgAttrName;


	if (bCompanions){

		FillFaceList(sNodeName + ".ImagesGroup", refCharacter, 1); // companions

		for(int n= 0; n< COMPANION_MAX; n++)
		{
			attributeName = "pic" + (iListSize+1);
			cn = GetCompanionIndex(refCharacter, n);

			if(cn!= -1)
			{
				GameInterface.(sNodeName).(attributeName).character = cn;
				GameInterface.(sNodeName).(attributeName).img1 = GetFacePicName(GetCharacter(cn));
				GameInterface.(sNodeName).(attributeName).tex1 = FindFaceGroupNum(sNodeName + ".ImagesGroup","FACE128_"+ characters[cn].FaceID);

				iListSize++;
			}
		}
	}

	if (bPassengers){


		makearef(pRef,refCharacter.Fellows.Passengers);
		FillFaceList(sNodeName + ".ImagesGroup", refCharacter, 2); // passengers

		for(int i= 0; i< GetPassengersQuantity(refCharacter); i++)
		{
			attributeName = "pic" + (iListSize+1);
			PsgAttrName = "id"+(i+1);
			cn = sti(pRef.(PsgAttrName));

			if(cn!=-1 && !CheckAttribute(&characters[cn], "isbusy"))
			{
				GameInterface.(sNodeName).(attributeName).character = cn;
				GameInterface.(sNodeName).(attributeName).img1 = GetFacePicName(GetCharacter(cn));
				GameInterface.(sNodeName).(attributeName).tex1 = FindFaceGroupNum(sNodeName + ".ImagesGroup","FACE128_"+ characters[cn].FaceID);

				iListSize++;
			}
		}
	}
	/*
	if (bOfficers)
	{
	makearef(pRef,refCharacter.Fellows.Passengers);

	FillFaceList(sNodeName + ".ImagesGroup", refCharacter, 0); // officers

	for(int o= 0; o< 4; o++)
	{
	attributeName = "pic" + (iListSize+1);
	cn = sti(pRef.(PsgAttrName));
	if(cn!=-1)
	{
	GameInterface.(sNodeName).(attributeName).character = cn;
	GameInterface.(sNodeName).(attributeName).img1 = GetFacePicName(GetCharacter(cn));
	GameInterface.(sNodeName).(attributeName).tex1 = FindFaceGroupNum(sNodeName+ ".ImagesGroup","FACE128_"+ characters[cn].FaceID);

	iListSize++;		
	}
	}
	}
	*/
	GameInterface.(sNodeName).ListSize = iListSize;
	GameInterface.(sNodeName).NotUsed = iNotUsed;	

	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_SCROLL_CHANGE, sNodeName, -1);
}
/// boal -->
void StartAboveForm(bool _pauseTime)
{
	if (IsEntity(&BattleInterface) || bLandInterfaceStart || bMainMenu)
	{
		ChangeShowIntarface();
	}

	EngineLayersOffOn(true);
    if (_pauseTime)
    {
		SetTimeScale(0.0);
	}
	else
	{
        SendMessage(pchar, "l", MSG_CHARACTER_STOPSTRAFE);
	}
	locCameraSleep(true);
	LAi_CharacterDisableDialog(pchar);
}

void EndAboveForm(bool _pauseTime)
{
	if (_pauseTime)
    {
		SetTimeScale(1.0);
		TimeScaleCounter = 0;
	 	DelPerkFromActiveList("TimeSpeed");
	 	DeleteAttribute(pchar, "pause");
	}
	locCameraSleep(false);
	LAi_CharacterEnableDialog(pchar);
	if (!IsEntity(&BattleInterface) || !bLandInterfaceStart || !bMainMenu)
	{
		ChangeShowIntarface();
	}
}

void ChangeShowIntarface()
{
	if(DontRefreshBLI) return;
	if (bSeaActive && !bAbordageStarted)
    {
        if (!IsEntity(&BattleInterface))
        {
            InitBattleInterface();
            StartBattleInterface();
            RefreshBattleInterface();
        }
        else DeleteBattleInterface();
    }
    else
    {
		if (!IsEntity(&worldMap)) 
		{
			if (!bLandInterfaceStart && questMovieIsLockPlayerCtrl == false)// если батловый интерфейс не включен или главное меню
	        {
				StartBattleLandInterface(); // включаем 
	        }
	        else EndBattleLandInterface(); // выключаем 
        } 
		else // на глобалке
		{
			if (!IsEntity(&BattleInterface))
			{
				InitWmInterface(); // включаем
				if (!bGameMenuStart) wdmShowInterface(true);
			}
			else
			{
				DeleteWmInterface(); // выключаем
				wdmShowInterface(false);
			}
        }
    }
}
// вернуть тип по номеру скрола в ф2 персонаж
string GetOfficerTypeByNum(int nCurScrollNum)
{
    string ret = "";
    
	switch (nCurScrollNum)
	{
		case 1:
   			ret = "navigator";
		break;

		case 2:
   			ret = "boatswain";
		break;

		case 3:
   			ret = "cannoner";
		break;

		case 4:
   			ret = "doctor";
		break;

		case 5:
   			ret = "treasurer";
		break;

		case 6:
   			ret = "carpenter";
		break;

		case 7:
  			ret = "fighter";
		break;

		case 8:
   			ret = "fighter";
		break;

		case 9:
			ret = "fighter";
		break;
	}
	return ret;
}

////////////////////////////// общие методы для форм
void SetOTHERMiniTable(string _tabName, ref _chr)
{
    int     i;
	string  row, skillName, col;
    int     skillVal;

    GameInterface.(_tabName).select = 0;
	GameInterface.(_tabName).hr.td1.str = "";
	for (i=1; i<=5; i++)
	{
	    row = "tr" + i;

	    GameInterface.(_tabName).(row).td1.icon.width = 35;
    	GameInterface.(_tabName).(row).td1.icon.height = 35;
    	GameInterface.(_tabName).(row).td1.icon.offset = "0, 2";
		GameInterface.(_tabName).(row).td2.align = "left";
		// GameInterface.(_tabName).(row).td2.scale = 1.2;
		GameInterface.(_tabName).(row).td2.textoffset = "3,0";
		GameInterface.(_tabName).(row).td3.align = "right";
	}
	GameInterface.(_tabName).tr1.UserData.ID = "Rank";
	GameInterface.(_tabName).tr1.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr1.td1.icon.image = "Rank";
	GameInterface.(_tabName).tr1.td2.str = XI_ConvertString("Rank");
	GameInterface.(_tabName).tr1.td3.str = sti(_chr.rank);

	GameInterface.(_tabName).tr2.UserData.ID = "Life";
	GameInterface.(_tabName).tr2.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr2.td1.icon.image = "Life";
	GameInterface.(_tabName).tr2.td2.str = XI_ConvertString("Life");
	GameInterface.(_tabName).tr2.td3.str = MakeInt(LAi_GetCharacterHP(_chr)) + " / " + MakeInt(LAi_GetCharacterMaxHP(_chr));

    GameInterface.(_tabName).tr3.UserData.ID = "Reputation";
	GameInterface.(_tabName).tr3.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr3.td1.icon.image = "Reputation";
	GameInterface.(_tabName).tr3.td2.str = XI_ConvertString("Reputation");
	if (_chr.id == pchar.id)
	{
		GameInterface.(_tabName).tr3.td3.str = GetFullReputationComplexName(_chr);
	}	
	else
	{
		GameInterface.(_tabName).tr3.td3.str = XI_ConvertString(GetReputationName(sti(_chr.reputation)));
	}	
	// GameInterface.(_tabName).tr3.td3.scale = 1.2;
	
    GameInterface.(_tabName).tr4.UserData.ID = "Loyality";
	GameInterface.(_tabName).tr4.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr4.td1.icon.image = "Loyality";
	GameInterface.(_tabName).tr4.td2.str = XI_ConvertString("Loyality");
	if (_chr.id == pchar.id)
	{
		GameInterface.(_tabName).tr4.td3.str = "-";
	}
	else
	{
		GameInterface.(_tabName).tr4.td3.str = XI_ConvertString(GetLoyalityName(makeint(GetCharacterLoyality(_chr) * 100 / MAX_LOYALITY)));
	}
	// GameInterface.(_tabName).tr4.td3.scale = 1.2;
	
	GameInterface.(_tabName).tr5.UserData.ID = "weight";
	GameInterface.(_tabName).tr5.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr5.td1.icon.image = "weight";
	GameInterface.(_tabName).tr5.td2.str = XI_ConvertString("weight");
	GameInterface.(_tabName).tr5.td3.str = FloatToString(GetItemsWeight(_chr), 1) + " / "+GetMaxItemsWeight(_chr);
	
	// прорисовка
	Table_UpdateWindow(_tabName);
}
void SetSPECIALMiniTable(string _tabName, ref _chr)
{
    int     i;
	string  row, skillName, col;
    int     diff, skillVal;
    
    GameInterface.(_tabName).select = 0;
	GameInterface.(_tabName).hr.td1.str = "";
	row = "tr1";
	for (i=1; i<=7; i++)
	{
	    col = "td" + i;
	    skillName = GetSkillNameByTRIdx("SPECIALType", i);

		GameInterface.(_tabName).(row).(col).fontidx = 0;
		// GameInterface.(_tabName).(row).(col).scale = 0.85;
		GameInterface.(_tabName).(row).(col).textoffset = "-5,-6";
		GameInterface.(_tabName).(row).(col).str = XI_ConvertString(skillName + "T");
	}
	row = "tr2";
	for (i=1; i<=7; i++)
	{
	    col = "td" + i;
	    skillName = GetSkillNameByTRIdx("SPECIALType", i);
        skillVal = GetCharacterSPECIAL(_chr, skillName);
		GameInterface.(_tabName).(row).(col).fontidx = 1;
		// GameInterface.(_tabName).(row).(col).scale = 1.0;
		GameInterface.(_tabName).(row).(col).textoffset = "-5,-2";
		diff = skillVal - GetSkillValue(_chr, SPECIAL_TYPE, skillName);
		GameInterface.(_tabName).(row).(col).str = skillVal;
		if (diff == 0)
		{
     		GameInterface.(_tabName).(row).(col).color = argb(255,255,255,255);
		}
		else
		{
		   if (diff > 0)
		   {
	          GameInterface.(_tabName).(row).(col).color = argb(255,196,255,196);
	       }
	       else
	       {
	          GameInterface.(_tabName).(row).(col).color = argb(255,255,196,196);
	       }
		}
	}
	row = "tr3";
	for (i=1; i<=7; i++)
	{
	    col = "td" + i;
	    skillName = GetSkillNameByTRIdx("SelfType", i);

		GameInterface.(_tabName).(row).(col).icon.group = "ICONS_SPEC";
	    GameInterface.(_tabName).(row).(col).icon.image = skillName + " skill icon";
	    GameInterface.(_tabName).(row).(col).icon.width = 30;
    	GameInterface.(_tabName).(row).(col).icon.height = 30;
	}
	row = "tr4";
	for (i=1; i<=7; i++)
	{
	    col = "td" + i;
	    skillName = GetSkillNameByTRIdx("SelfType", i);
        skillVal = GetSummonSkillFromName(_chr, skillName); 
		GameInterface.(_tabName).(row).(col).fontidx = 1;
		GameInterface.(_tabName).(row).(col).scale = 0.85;
		GameInterface.(_tabName).(row).(col).textoffset = "-9,-4";

		diff = skillVal - GetSkillValue(_chr, SKILL_TYPE, skillName);
		GameInterface.(_tabName).(row).(col).str = skillVal;
		if (diff == 0)
		{
     		GameInterface.(_tabName).(row).(col).color = argb(255,255,255,255);
		}
		else
		{
		   if (diff > 0)
		   {
	          GameInterface.(_tabName).(row).(col).color = argb(255,196,255,196);
	       }
	       else
	       {
	          GameInterface.(_tabName).(row).(col).color = argb(255,255,196,196);
	       }
		}
	}
	
	row = "tr5";
	for (i=1; i<=7; i++)
	{
	    col = "td" + i;
	    skillName = GetSkillNameByTRIdx("ShipType", i);

		GameInterface.(_tabName).(row).(col).icon.group = "ICONS_SPEC";
	    GameInterface.(_tabName).(row).(col).icon.image = skillName + " skill icon";
	    GameInterface.(_tabName).(row).(col).icon.width = 30;
    	GameInterface.(_tabName).(row).(col).icon.height = 30;
	}
	row = "tr6";
	for (i=1; i<=7; i++)
	{
	    col = "td" + i;
	    skillName = GetSkillNameByTRIdx("ShipType", i);
        skillVal = GetSummonSkillFromName(_chr, skillName);
		GameInterface.(_tabName).(row).(col).fontidx = 1;
		GameInterface.(_tabName).(row).(col).scale = 0.85;
		GameInterface.(_tabName).(row).(col).textoffset = "-9,-4";
		diff = skillVal - GetSkillValue(_chr, SKILL_TYPE, skillName);
		GameInterface.(_tabName).(row).(col).str = skillVal;
		if (diff == 0)
		{
     		GameInterface.(_tabName).(row).(col).color = argb(255,255,255,255);
		}
		else
		{
		   if (diff > 0)
		   {
	          GameInterface.(_tabName).(row).(col).color = argb(255,196,255,196);
	       }
	       else
	       {
	          GameInterface.(_tabName).(row).(col).color = argb(255,255,196,196);
	       }
		}
	}
	// прорисовка
	Table_UpdateWindow(_tabName);
}

// опыт команды нпс _chr
void SetCrewExpTable(ref _chr, string _tabName, string _bar1, string _bar2, string _bar3)
{
    int     i;
	string  row, skillName, col;
    int     skillVal;

    GameInterface.(_tabName).select = 0;
	GameInterface.(_tabName).hr.td1.str = "";
	for (i=1; i<=3; i++)
	{
	    row = "tr" + i;

	    GameInterface.(_tabName).(row).td1.icon.width = 40;
    	GameInterface.(_tabName).(row).td1.icon.height = 40;
    	// GameInterface.(_tabName).(row).td1.icon.offset = "0, 2";
		GameInterface.(_tabName).(row).td2.align = "left";
		// GameInterface.(_tabName).(row).td2.scale = 0.8;
		GameInterface.(_tabName).(row).td2.textoffset = "10,0";
		GameInterface.(_tabName).(row).td3.align = "right";
		// GameInterface.(_tabName).(row).td3.scale = 0.8;
	}
	GameInterface.(_tabName).tr1.UserData.ID = "Sailors";
	GameInterface.(_tabName).tr1.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr1.td1.icon.image = "Class";
	GameInterface.(_tabName).tr1.td2.str = XI_ConvertString("Sailors");
	if (GetCrewQuantity(_chr) > 0)
    {
		GameInterface.(_tabName).tr1.td3.str = XI_ConvertString(GetExpName(sti(_chr.Ship.Crew.Exp.Sailors)));
	}
	else
	{
		GameInterface.(_tabName).tr1.td3.str = "";
	}
	
	GameInterface.(_tabName).tr2.UserData.ID = "Cannoners";
	GameInterface.(_tabName).tr2.td1.icon.group = "ICONS_SPEC";
    GameInterface.(_tabName).tr2.td1.icon.image = "Cannons skill icon";
	GameInterface.(_tabName).tr2.td2.str = XI_ConvertString("Cannoners");
	if (GetCrewQuantity(_chr) > 0)
    {
		GameInterface.(_tabName).tr2.td3.str = XI_ConvertString(GetExpName(sti(_chr.Ship.Crew.Exp.Cannoners)));
	}
		else
	{
		GameInterface.(_tabName).tr2.td3.str = "";
	}
	
    GameInterface.(_tabName).tr3.UserData.ID = "Soldiers";
	GameInterface.(_tabName).tr3.td1.icon.group = "ICONS_SPEC";
    GameInterface.(_tabName).tr3.td1.icon.image = "grappling skill icon";
	GameInterface.(_tabName).tr3.td2.str = XI_ConvertString("Soldiers");
	if (GetCrewQuantity(_chr) > 0)
    {
		GameInterface.(_tabName).tr3.td3.str = XI_ConvertString(GetExpName(sti(_chr.Ship.Crew.Exp.Soldiers)));
	}
		else
	{
		GameInterface.(_tabName).tr3.td3.str = "";
	}
	// прорисовка
	Table_UpdateWindow(_tabName);
	
	///  прогресбары
	GameInterface.StatusLine.(_bar1).Max   = 100;
    GameInterface.StatusLine.(_bar1).Min   = 1;
    if (GetCrewQuantity(_chr) > 0)
    {
    	GameInterface.StatusLine.(_bar1).Value = sti(_chr.Ship.Crew.Exp.Sailors);
    }
    else
    {
    	GameInterface.StatusLine.(_bar1).Value = 1;
    }
    SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE, _bar1,0);
    
    GameInterface.StatusLine.(_bar2).Max   = 100;
    GameInterface.StatusLine.(_bar2).Min   = 1;
    if (GetCrewQuantity(_chr) > 0)
    {
    	GameInterface.StatusLine.(_bar2).Value = sti(_chr.Ship.Crew.Exp.Cannoners);
    }
    else
    {
    	GameInterface.StatusLine.(_bar2).Value = 1;
    }
    SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE, _bar2,0);
    
    GameInterface.StatusLine.(_bar3).Max   = 100;
    GameInterface.StatusLine.(_bar3).Min   = 1;
    if (GetCrewQuantity(_chr) > 0)
    {
    	GameInterface.StatusLine.(_bar3).Value = sti(_chr.Ship.Crew.Exp.Soldiers);
    }
    else
    {
    	GameInterface.StatusLine.(_bar3).Value = 1;
    }
    SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE, _bar3,0);
}

void SetShipOTHERTable(string _tabName, ref _chr)
{
    int     i;
	string  row;
	float   fTmp;

    int iShip = sti(_chr.ship.type);
	ref refBaseShip = GetRealShip(iShip);
		
    GameInterface.(_tabName).select = 0;
	GameInterface.(_tabName).hr.td1.str = "";
	for (i=1; i<=9; i++)
	{
	    row = "tr" + i;

	    GameInterface.(_tabName).(row).td1.icon.width = 35;
    	GameInterface.(_tabName).(row).td1.icon.height = 35;
    	GameInterface.(_tabName).(row).td1.icon.offset = "0, 2";
		GameInterface.(_tabName).(row).td2.align = "left";
		// GameInterface.(_tabName).(row).td2.scale = 0.85;
		GameInterface.(_tabName).(row).td2.textoffset = "10,0";
		GameInterface.(_tabName).(row).td3.align = "right";
		// GameInterface.(_tabName).(row).td3.scale = 0.85;
	}
	GameInterface.(_tabName).tr1.UserData.ID = "Hull";
	GameInterface.(_tabName).tr1.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr1.td1.icon.image = "Hull";
	GameInterface.(_tabName).tr1.td2.str = XI_ConvertString("Hull");
	GameInterface.(_tabName).tr1.td3.str = sti(_chr.ship.hp) + " / " + sti(refBaseShip.hp);
    if (!CheckAttribute(&RealShips[iShip], "Tuning.HP")) 
	{
		GameInterface.(_tabName).tr1.td3.color = argb(255,255,255,255);
	}
	else 
	{
		GameInterface.(_tabName).tr1.td3.color = argb(255,128,255,255);
	}

	GameInterface.(_tabName).tr2.UserData.ID = "Sails";
	GameInterface.(_tabName).tr2.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr2.td1.icon.image = "Sails";
	GameInterface.(_tabName).tr2.td2.str = XI_ConvertString("Sails");
	GameInterface.(_tabName).tr2.td3.str = sti(_chr.ship.sp) + " / " + sti(refBaseShip.sp);

    GameInterface.(_tabName).tr3.UserData.ID = "Speed";
	GameInterface.(_tabName).tr3.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr3.td1.icon.image = "Speed";
	GameInterface.(_tabName).tr3.td2.str = XI_ConvertString("Speed");
	if (IsCompanion(_chr))
	{
		GameInterface.(_tabName).tr3.td3.str = FloatToString(FindShipSpeed(_chr),2) + " / " + FloatToString(stf(refBaseShip.SpeedRate),2);
	}
	else
	{
	    GameInterface.(_tabName).tr3.td3.str = FloatToString(stf(refBaseShip.SpeedRate),2);
	}
	if (!CheckAttribute(&RealShips[iShip], "Tuning.SpeedRate")) 
	{
		GameInterface.(_tabName).tr3.td3.color = argb(255,255,255,255);
	}
	else
	{
		GameInterface.(_tabName).tr3.td3.color = argb(255,128,255,255);
	}	
	

    GameInterface.(_tabName).tr4.UserData.ID = "Maneuver";
	GameInterface.(_tabName).tr4.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr4.td1.icon.image = "Maneuver";
	GameInterface.(_tabName).tr4.td2.str = XI_ConvertString("Maneuver");
	if (IsCompanion(_chr))
	{
  		GameInterface.(_tabName).tr4.td3.str = FloatToString((stf(refBaseShip.turnrate) * FindShipTurnRate(_chr)), 2) + " / " + FloatToString(stf(refBaseShip.TurnRate),2);
	}
	else
	{
	    GameInterface.(_tabName).tr4.td3.str = FloatToString(stf(refBaseShip.TurnRate),2);
	}
	if (!CheckAttribute(&RealShips[iShip], "Tuning.TurnRate")) 
	{
		GameInterface.(_tabName).tr4.td3.color = argb(255,255,255,255);
	}
	else
	{
		GameInterface.(_tabName).tr4.td3.color = argb(255,128,255,255);
	}

	GameInterface.(_tabName).tr5.UserData.ID = "AgainstWind";
	GameInterface.(_tabName).tr5.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr5.td1.icon.image = "AgainstWind";
	GameInterface.(_tabName).tr5.td2.str = XI_ConvertString("AgainstWind");
	
	fTmp = acos(1.0 - FindShipWindAgainstSpeed(_chr)) * 180.0/PI;
	GameInterface.(_tabName).tr5.td3.str = makeint(180.0 - fTmp) + " / " + (makeint(fTmp));
	
	if (!CheckAttribute(&RealShips[iShip], "Tuning.WindAgainst")) 
	{
		GameInterface.(_tabName).tr5.td3.color = argb(255,255,255,255);
	}
	else
	{
		GameInterface.(_tabName).tr5.td3.color = argb(255,128,255,255);
	}
	
	
	RecalculateCargoLoad(_chr);
	GameInterface.(_tabName).tr6.UserData.ID = "Capacity";
	GameInterface.(_tabName).tr6.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr6.td1.icon.image = "Capacity";
	GameInterface.(_tabName).tr6.td2.str = XI_ConvertString("Capacity");
	GameInterface.(_tabName).tr6.td3.str = GetCargoLoad(_chr) + " / " + GetCargoMaxSpace(_chr);
	if (!CheckAttribute(&RealShips[iShip], "Tuning.Capacity")) 
	{
		GameInterface.(_tabName).tr6.td3.color = argb(255,255,255,255);
	}
	else
	{
		GameInterface.(_tabName).tr6.td3.color = argb(255,128,255,255);
	}
	
	GameInterface.(_tabName).tr7.UserData.ID = "Crew";
	GameInterface.(_tabName).tr7.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr7.td1.icon.image = "Crew";
	GameInterface.(_tabName).tr7.td2.str = XI_ConvertString("Crew");
	GameInterface.(_tabName).tr7.td3.str = GetCrewQuantity(_chr) + " : "+ sti(refBaseShip.MinCrew) +" / " + sti(refBaseShip.OptCrew);	
	if (!CheckAttribute(&RealShips[iShip], "Tuning.MaxCrew")) 
	{
		GameInterface.(_tabName).tr7.td3.color = argb(255,255,255,255);
	}
	else
	{
		GameInterface.(_tabName).tr7.td3.color = argb(255,128,255,255);
	}
	
	GameInterface.(_tabName).tr8.UserData.ID = "sCannons";
	GameInterface.(_tabName).tr8.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr8.td1.icon.image = "Caliber";
	GameInterface.(_tabName).tr8.td2.str = XI_ConvertString("sCannons"); //XI_ConvertString("Caliber");
	GameInterface.(_tabName).tr8.td3.str = XI_ConvertString("caliber" + refBaseShip.MaxCaliber) + " / " + sti(refBaseShip.CannonsQuantity);
	
	if (!CheckAttribute(&RealShips[iShip], "Tuning.Cannon")) 
	{
		GameInterface.(_tabName).tr8.td3.color = argb(255,255,255,255);
	}
	else
	{
		GameInterface.(_tabName).tr8.td3.color = argb(255,128,255,255);
	}
		
	GameInterface.(_tabName).tr9.UserData.ID = "CannonType";
	GameInterface.(_tabName).tr9.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr9.td1.icon.image = "Cannons";
	GameInterface.(_tabName).tr9.td2.str = XI_ConvertString(GetCannonType(sti(_chr.Ship.Cannons.Type)) + "s2");
	
	if (sti(_chr.Ship.Cannons.Type) != CANNON_TYPE_NONECANNON)
	{
		if(GetCannonsNum(_chr) > 0)
		{
		GameInterface.(_tabName).tr9.td3.str = XI_ConvertString("caliber" + GetCannonCaliber(sti(_chr.Ship.Cannons.Type))) + " / " + GetCannonsNum(_chr);
	}
	else
	{
			GameInterface.(_tabName).tr9.td3.str = GetCannonsNum(_chr);
		}	
	}
	else
	{
	    GameInterface.(_tabName).tr9.td3.str = "";
	}
	// прорисовка
	Table_UpdateWindow(_tabName);
}

void SetFoodShipInfo(ref chr, string _textName)
{
	int iColor, iFood;
	string sText;
	
	SetFormatedText(_textName, "");
	if (sti(chr.ship.type) != SHIP_NOTUSED)
	{
		sText = XI_ConvertString("FoodShipInfo");
		iFood = CalculateShipFood(chr);
		sText = sText + FindRussianDaysString(iFood);
		SetFormatedText(_textName, sText);
		if(iFood >= 5)
		{
			iColor = argb(255,255,255,192);
		}
		if(iFood > 10)
		{
			iColor = argb(255,192,255,192);
		}
		if(iFood < 5)
		{
			iColor = argb(255,255,192,192);
		}
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE, _textName, 8,-1,iColor);	
	}
}

void SetFoodShipInfoShort(ref chr, string _textName)
{
	int iColor, iFood;
	string sText;
	
	SetFormatedText(_textName, "");
	if (sti(chr.ship.type) != SHIP_NOTUSED)
	{
		iFood = CalculateShipFood(chr);
		sText = FindRussianDaysString(iFood);
		SetFormatedText(_textName, sText);
		if(iFood >= 5)
		{
			iColor = argb(255,255,255,192);
		}
		if(iFood > 10)
		{
			iColor = argb(255,192,255,192);
		}
		if(iFood < 5)
		{
			iColor = argb(255,255,192,192);
		}
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE, _textName, 8,-1,iColor);	
	}
}

// Warship 11.07.09 Вывести в текстовое поле инфу о количестве дней, на сколько хватит рому на судне
void SetRumShipInfo(ref _character, String _node)
{
	int color, rum;
	String text;
	
	SetFormatedText(_node, "");
	
	if(sti(_character.ship.type) != SHIP_NOTUSED)
	{
		text = XI_ConvertString("RumShipInfo");
		rum = CalculateShipRum(_character);
		text = text + FindRussianDaysString(rum);
		SetFormatedText(_node, text);
		
		if(rum < 3)
		{
			color = argb(255, 255, 192, 192);
		}
		
		if(rum >= 3)
		{
			color = argb(255, 255, 255, 192);
		}
		
		if(rum >= 10)
		{
			color = argb(255, 192, 255, 192);
		}
		
		SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, _node, 8, -1, color);	
	}
}

void SetRumShipInfoShort(ref _character, String _node)
{
	int color, rum;
	String text;
	
	SetFormatedText(_node, "");
	
	if(sti(_character.ship.type) != SHIP_NOTUSED)
	{
		rum = CalculateShipRum(_character);
		text = FindRussianDaysString(rum);
		SetFormatedText(_node, text);
		
		if(rum < 3)
		{
			color = argb(255, 255, 192, 192);
		}
		
		if(rum >= 3)
		{
			color = argb(255, 255, 255, 192);
		}
		
		if(rum >= 10)
		{
			color = argb(255, 192, 255, 192);
		}
		
		SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, _node, 8, -1, color);	
	}
}

// должность офицера
string GetOfficerPosition(string sCharacter)
{	
	if (CheckAttribute(pchar,"Fellows.Passengers.navigator") && sCharacter == sti(pchar.Fellows.Passengers.navigator))
		return XI_ConvertString("navigator");
	if (CheckAttribute(pchar,"Fellows.Passengers.boatswain") && sCharacter == sti(pchar.Fellows.Passengers.boatswain))
		return XI_ConvertString("boatswain");
	if (CheckAttribute(pchar,"Fellows.Passengers.cannoner") && sCharacter == sti(pchar.Fellows.Passengers.cannoner))
		return XI_ConvertString("cannoner");
	if (CheckAttribute(pchar,"Fellows.Passengers.doctor") && sCharacter == sti(pchar.Fellows.Passengers.doctor))
		return XI_ConvertString("doctor");
	if (CheckAttribute(pchar,"Fellows.Passengers.treasurer") && sCharacter == sti(pchar.Fellows.Passengers.treasurer))
		return XI_ConvertString("treasurer");
	if (CheckAttribute(pchar,"Fellows.Passengers.carpenter") && sCharacter == sti(pchar.Fellows.Passengers.carpenter))
		return XI_ConvertString("carpenter");
	
	for(int i=1; i<4; i++)
	{	
		if (sti(GetOfficersIndex(pchar, i)) == sti(sCharacter))
			return XI_ConvertString("fighter");
	}

	return XI_ConvertString("passengership");
}

// значки уведомлений в шапке
void SetAlertMarks(ref chr)
{
	SetNodeUsing("A_INVENTORY",false);
	SetNodeUsing("A_SHIP",false);
	SetNodeUsing("A_QUESTBOOK",false);
	SetNodeUsing("A_ATLAS",false);
	SetNodeUsing("A_ABILITIES",false);
	SetNodeUsing("A_NATIONS",false);
	SetNodeUsing("A_QUEST",false);
	SetNodeUsing("A_INFO",false);
	
	if(CheckAttribute(chr,"perks.FreePoints_self") || CheckAttribute(chr,"perks.FreePoints_ship"))
	{
        if(!HaveAllPerks(chr, "any")) SetNodeUsing("A_ABILITIES",true);
	}
	if(CheckQuestInfo() || CheckNewDocs()) SetNodeUsing("A_QUESTBOOK",true);
	if(CheckQuestInfo()) SetNodeUsing("A_QUEST",true);
	if(CheckNewDocs()) SetNodeUsing("A_INFO",true);
}