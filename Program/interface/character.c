/// BOAL меню персонажи
/// Sith переделка под LE
ref xi_refCharacter;
int nCurScrollNum, nCurScrollOfficerNum;
string CurTable, CurRow;
int iSelected; // курсор в таблице
bool bChangePIRATES;
bool bChangePIRATESNotFirstTime;
int HPDelta;
int oldRank;
bool bgr;
bool bfirst;

void InitInterface_R(string iniName, ref _char)
{
	StartAboveForm(true);
	if(!isEntity(&WorldMap) || !bSeaActive)
	{
		LAi_SetActorType(pchar);
	}
	// belamour персонаж из кораблей на приколе -->
	if(CheckAttribute(pchar,"SystemInfo.ShowShip"))
	{
		int chrIdx = sti(pchar.SystemInfo.ShowShip);
		xi_refCharacter = GetCharacter(chrIdx);
		bgr = true;
	}
	else
	{
		xi_refCharacter = _char;
		bgr = false;
	}

	GameInterface.title = "titleCharacter";
	bfirst = true;
    bChangePIRATES = false;
	bChangePIRATESNotFirstTime = false;
    if (CheckAttribute(xi_refCharacter, "SystemInfo.ChangePIRATES"))
    {
    	bChangePIRATES = true;
		
		if (CheckAttribute(xi_refCharacter, "SystemInfo.ChangePIRATES.NotFirstTime")) {
			bChangePIRATESNotFirstTime = true;
			HPDelta = GetHPIncrease(xi_refCharacter);
			oldRank = sti(xi_refCharacter.rank);
		}
		
    	DeleteAttribute(xi_refCharacter, "SystemInfo.ChangePIRATES");
	}
	GameInterface.StatusLine.LOYALITY.Max = 1;
    GameInterface.StatusLine.LOYALITY.Min = 0;
    GameInterface.StatusLine.LOYALITY.Value = 0;

	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	SetEventHandler("InterfaceBreak","ProcessExitCancel",0);
	SetEventHandler("exitCancel","ProcessExitCancel",0);
    SetEventHandler("ievnt_command","ProcessCommandExecute",0);
    SetEventHandler("ShowInfoWindow","ShowInfoWindow",0);
	SetEventHandler("MouseRClickUp","HideInfoWindow",0);
	SetEventHandler("TableSelectChange", "CS_TableSelectChange", 0);
	SetEventHandler("ChoosePerk","ChoosePerk",0);
	SetEventHandler("ExitPerkMenu","ExitPerkMenu",0);
	SetEventHandler("AcceptPerk","AcceptPerk",0);
	SetEventHandler("ExitMsgMenu", "ExitMsgMenu", 0);

    SetVariable();
    SetCurrentNode("TABLE_OTHER");
	
	if ( IsMainCharacter(xi_refCharacter) )
	{
		SetFormatedText("LOYALITY_STR", XI_ConvertString("Authority"));
	}
	else
	{
		SetFormatedText("LOYALITY_STR", XI_ConvertString("Loyality"));
	}	
    HideSkillChanger();
    if (bChangePIRATES)
    {
    	ShowMsgMenu(); // инфо чё делать в начале
    }
	
	FillPerksTable("Self", true);  // Личные навыки
	FillPerksTable2("Ship", true);  // Корабельные навыки
	if(bgr) // заходим из журнала
	{
		SetNodeUsing("MAIN_BACK", true);
		SetNodeUsing("FOG_TOP", true);
		SetNodeUsing("FOG_BOTTOM", true);
	} else {
		SetNodeUsing("MAIN_BACK", false);
		SetNodeUsing("FOG_TOP", false);
		SetNodeUsing("FOG_BOTTOM", false);
	}
	GameInterface.TABLE_PERKS.select = 1;
	GameInterface.TABLE_PERKS.top = 0;
	Table_UpdateWindow("TABLE_PERKS");
	ChoosePerk();
}

void ProcessExitCancel()
{
	IDoExit(RC_INTERFACE_ANY_EXIT);
}

void IDoExit(int exitCode)
{
	if (bChangePIRATES)
	{
		xi_refCharacter.skill.FreeSPECIAL = 0; // если не все распределил, сам дурак		
		
		if (!bChangePIRATESNotFirstTime) {
			ref sld = characterFromID("Sailor_1");
			LAi_SetActorTypeNoGroup(pchar);
			LAi_SetActorTypeNoGroup(sld);
			SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 0.5);        
		}
		
		if (CheckAttribute(pchar, "questTemp.ChickenGod.OnExitKick")) {
			DeleteAttribute(pchar, "questTemp.ChickenGod.OnExitKick");
			DoQuestFunctionDelay("ChickenGod_KickedFromTemple1", 1.0);
		}
    }

	EndAboveForm(true);
	if(!isEntity(&WorldMap) || !bSeaActive)
	{
		LAi_SetPlayerType(pchar);
	}
	DelEventHandler("InterfaceBreak","ProcessExitCancel");
	DelEventHandler("exitCancel","ProcessExitCancel");
    DelEventHandler("ievnt_command","ProcessCommandExecute");
    DelEventHandler("ShowInfoWindow","ShowInfoWindow");
	DelEventHandler("MouseRClickUp","HideInfoWindow");
	DelEventHandler("TableSelectChange", "CS_TableSelectChange");
	DelEventHandler("ChoosePerk","ChoosePerk");
	DelEventHandler("ExitPerkMenu","ExitPerkMenu");
	DelEventHandler("AcceptPerk","AcceptPerk");
	DelEventHandler("ExitMsgMenu", "ExitMsgMenu");
	// belamour вернуться во вкладку журнала, если пришли оттуда -->
	if(CheckAttribute(pchar,"SystemInfo.ShowShip"))
	{
		interfaceResultCommand = RC_INTERFACE_TO_QUESTBOOK;
	} 
	else
	{
		interfaceResultCommand = exitCode;
	}
	// <-- belamour
	if( CheckAttribute(&InterfaceStates,"ReloadMenuExit"))
	{
        DeleteAttribute(&InterfaceStates,"ReloadMenuExit");
		EndCancelInterface(false);
	}
	else
	{
		EndCancelInterface(true);
	}
}
void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();
    switch(nodName)
	{
        case "B_SKILLUP":
			if (comName=="click")
			{
                IncreaseSkill(1);
			}
			if (comName=="rclick")
			{
                IncreaseSkill(5);
			}
		break;

		case "B_SKILLDOWN":
	        if (comName=="click")
			{
			    DecreaseSkill(1);
			}
			if (comName=="rclick")
			{
			    DecreaseSkill(5);
			}
		break;
	}
}

void SetVariable()
{
	FillSkillTables();
	SetNewPicture("CHARACTER_BIG_PICTURE", "interfaces\le\portraits\512\face_" + xi_refCharacter.FaceId + ".tga");
	SetFormatedText("HERO_NAME", GetFullName(xi_refCharacter));
	
    // теперь это Лояльность
	if (xi_refCharacter.id == pchar.id)
	{
		GameInterface.StatusLine.LOYALITY.Max   = COMPLEX_REPUTATION_MAX;
		GameInterface.StatusLine.LOYALITY.Min   = COMPLEX_REPUTATION_MIN;
		GameInterface.StatusLine.LOYALITY.Value = sti(xi_refCharacter.reputation.authority);
		
		SetFormatedText("REPUTATION_STR", GetFullReputationComplexName(xi_refCharacter));
	}
	else
	{
		GameInterface.StatusLine.LOYALITY.Max   = MAX_LOYALITY;
		GameInterface.StatusLine.LOYALITY.Min   = 0;
		GameInterface.StatusLine.LOYALITY.Value = GetCharacterLoyality(xi_refCharacter);
		
		SetFormatedText("REPUTATION_STR", XI_ConvertString(GetReputationName(sti(xi_refCharacter.reputation))));
	}	
    if (xi_refCharacter.id == pchar.id)
    {
	    GameInterface.StatusLine.BAR_HEALTH.Max   = 60;
	    GameInterface.StatusLine.BAR_HEALTH.Min   = 1;
	    GameInterface.StatusLine.BAR_HEALTH.Value = makeint(pchar.Health.HP);
	    if (sti(pchar.Health.HP) > 60 )
	    {
	        GameInterface.StatusLine.BAR_HEALTH.Value = 60;
	    }
    }
    else
    {
        GameInterface.StatusLine.BAR_HEALTH.Max = 1;
        GameInterface.StatusLine.BAR_HEALTH.Min = 0;
        GameInterface.StatusLine.BAR_HEALTH.Value = 0;
    }

    SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"LOYALITY",0);
    SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"BAR_HEALTH",0);

    if (sti(xi_refCharacter.Skill.FreeSkill) > 0)
	{
        SetFormatedText("FREE_SKILL", xi_refCharacter.Skill.FreeSkill);
    }
    else
    {
        SetFormatedText("FREE_SKILL", "");
    }
    if (sti(xi_refCharacter.Skill.FreeSPECIAL) > 0)
	{
        SetFormatedText("FREE_SPECIAL", xi_refCharacter.Skill.FreeSPECIAL);
    }
    else
    {
        SetFormatedText("FREE_SPECIAL", "");
    }
	// ExitPerkMenu();
}

void ShowInfoWindow()
{
	string sCurrentNode = GetCurrentNode();
	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;
	int iItem;

	sPicture = "-1";
	string sAttributeName;
	int nChooseNum = -1;
	switch (sCurrentNode)
	{
		case "TABLE_SPECIAL":
		    sHeader = XI_ConvertString("Characteristics");
		    sText1  = GetRPGText(GameInterface.(CurTable).(CurRow).UserData.ID);
		break;
		case "TABLE_SKILL_1":
		    sHeader = XI_ConvertString("Personal skill");
		    sText1  = GetRPGText(GameInterface.(CurTable).(CurRow).UserData.ID);
		break;
		case "TABLE_SKILL_2":
		    sHeader = XI_ConvertString("Ship skill");
		    sText1  = GetRPGText(GameInterface.(CurTable).(CurRow).UserData.ID);
		break;
		case "LOYALITY_STR":
			if (xi_refCharacter.id == pchar.id)		
			{
				sHeader = XI_ConvertString("Authority");
				sText1  = GetRPGText("Authority");
			}
			else
			{
				sHeader = XI_ConvertString("Loyality");
				sText1  = GetRPGText("Loyality");
			}	
		break;
		case "REPUTATION_STR":
		    sHeader = XI_ConvertString("Reputation");
		    sText1  = GetRPGText("Reputation");
		break;
		case "TABLE_OTHER":
		    sHeader = XI_ConvertString(GameInterface.(CurTable).(CurRow).UserData.ID);
		    sText1  = GetRPGText(GameInterface.(CurTable).(CurRow).UserData.ID);
		break;
		case "PERSONAL_AVAILABLE":
		    sHeader = XI_ConvertString("Personal abilities");
		    sText1  = GetRPGText("Personal_abilities");
		    sText3  = GetRPGText("Abilities_active");
		break;
		case "SHIP_AVAILABLE":
		    sHeader = XI_ConvertString("Ship abilities");
		    sText1  = GetRPGText("Ship_abilities");
		    sText3  = GetRPGText("Abilities_active");
		break;
		case "TABLE_PERKS":
		    sHeader = XI_ConvertString("Personal abilities");
		    sText1  = GetRPGText("Personal_abilities");
		    sText3  = GetRPGText("Abilities_active");
		break;
		case "TABLE_PERKS2":
		    sHeader = XI_ConvertString("Ship abilities");
		    sText1  = GetRPGText("Ship_abilities");
		    sText3  = GetRPGText("Abilities_active");
		break;
		case "PERK_TABLE_NEED":
		    sHeader = GetRPGText("PERK_TABLE_NEED");
		    sText1  = GetRPGText("PERK_TABLE_NEED_desc");
		break;
	}
	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 64, 64);
}

void HideInfoWindow()
{
	CloseTooltip();
}

void FillSkillTables()
{
	int     i;
	string  row, skillName;
    int     diff, skillVal;

    // boal оптимизация скилов -->
    DelBakSkillAttr(xi_refCharacter);
    ClearCharacterExpRate(xi_refCharacter);
    RefreshCharacterSkillExpRate(xi_refCharacter);

    SetEnergyToCharacter(xi_refCharacter);
    // boal оптимизация скилов <--

    // if (!CheckAttribute(xi_refCharacter,"perks.FreePoints_self") )
		xi_refCharacter.perks.Points_self = СharacterPerksEnb(xi_refCharacter,"self");
    // if (!CheckAttribute(xi_refCharacter,"perks.FreePoints_ship") )
		xi_refCharacter.perks.Points_ship = СharacterPerksEnb(xi_refCharacter,"ship");

    SetFormatedText("PERSONAL_AVAILABLE", XI_ConvertString("Personal abilities") + "  -  " +xi_refCharacter.perks.Points_self);
    SetFormatedText("SHIP_AVAILABLE", XI_ConvertString("Ship abilities") + "  -  " + xi_refCharacter.perks.Points_ship);

	GameInterface.TABLE_SPECIAL.select = 0;
	GameInterface.TABLE_SPECIAL.hr.td1.str = "";

	for (i=1; i<=7; i++)
	{
	    row = "tr" + i;
	    skillName = GetSkillNameByTRIdx("SPECIALType", i);

        GameInterface.TABLE_SPECIAL.(row).UserData.ID = skillName;
		GameInterface.TABLE_SPECIAL.(row).td1.fontidx = 0;
		GameInterface.TABLE_SPECIAL.(row).td1.textoffset = "6,-5";
		//GameInterface.TABLE_SPECIAL.(row).td1.align = "center";
		GameInterface.TABLE_SPECIAL.(row).td2.textoffset = "5,0";
		GameInterface.TABLE_SPECIAL.(row).td3.align = "center";
		GameInterface.TABLE_SPECIAL.(row).td4.fontidx = 1;
		GameInterface.TABLE_SPECIAL.(row).td4.align = "left";
		GameInterface.TABLE_SPECIAL.(row).td4.scale = 0.8;

		GameInterface.TABLE_SPECIAL.(row).td1.str = XI_ConvertString(skillName + "T");
		GameInterface.TABLE_SPECIAL.(row).td2.str = XI_ConvertString(skillName);
		skillVal = GetSkillValue(xi_refCharacter, SPECIAL_TYPE, skillName);
		GameInterface.TABLE_SPECIAL.(row).td4.str = skillVal;
		// рассчет драйна
		diff = GetCharacterSPECIAL(xi_refCharacter, skillName) - skillVal;
		if (diff == 0)
		{
     		GameInterface.TABLE_SPECIAL.(row).td3.str = "";
     		DeleteAttribute(&GameInterface, "TABLE_SPECIAL." + row + ".td3.color");
		}
		else
		{
		   if (diff > 0)
		   {
	          GameInterface.TABLE_SPECIAL.(row).td3.str = "(+" + diff + ")";
	          GameInterface.TABLE_SPECIAL.(row).td3.color = argb(255,196,255,196);
	       }
	       else
	       {
	          GameInterface.TABLE_SPECIAL.(row).td3.str = "(" + diff + ")";
	          GameInterface.TABLE_SPECIAL.(row).td3.color = argb(255,255,196,196);
	       }
		}
	}
    GameInterface.TABLE_SKILL_1.select = 0;
    GameInterface.TABLE_SKILL_1.hr.td1.str = "";
	for (i=1; i<=7; i++)
	{
	    row = "tr" + i;
	    skillName = GetSkillNameByTRIdx("SelfType", i);

        GameInterface.TABLE_SKILL_1.(row).UserData.ID = skillName;
		GameInterface.TABLE_SKILL_1.(row).td1.icon.group = "ICONS_SPEC";
	    GameInterface.TABLE_SKILL_1.(row).td1.icon.image = skillName + " skill icon";
	    GameInterface.TABLE_SKILL_1.(row).td1.icon.width = 35;
    	GameInterface.TABLE_SKILL_1.(row).td1.icon.height = 35;
    	GameInterface.TABLE_SKILL_1.(row).td1.icon.offset = "-3, -2";
		GameInterface.TABLE_SKILL_1.(row).td2.align = "left";
		GameInterface.TABLE_SKILL_1.(row).td2.textoffset = "5,0";
		GameInterface.TABLE_SKILL_1.(row).td5.fontidx = 0;
		GameInterface.TABLE_SKILL_1.(row).td5.scale = 0.8;
		GameInterface.TABLE_SKILL_1.(row).td5.align = "left";

		GameInterface.TABLE_SKILL_1.(row).td2.str = XI_ConvertString(skillName);
		skillVal = GetSkillValue(xi_refCharacter, SKILL_TYPE, skillName);
		GameInterface.TABLE_SKILL_1.(row).td5.str = skillVal;
		// рассчет драйна
		diff = GetSummonSkillFromName(xi_refCharacter, skillName) - skillVal;

		if (skillVal < SKILL_MAX)
		{
			GameInterface.TABLE_SKILL_1.(row).td3.str = makeint(GetSkillValueExp(xi_refCharacter, skillName) * 100.0 / makefloat(skillVal * GetCharacterExpRate(xi_refCharacter, skillName))) + "%";
		}
		else
		{
		    GameInterface.TABLE_SKILL_1.(row).td3.str = "";
		}
		if (diff == 0)
		{
     		GameInterface.TABLE_SKILL_1.(row).td4.str = "";
     		DeleteAttribute(&GameInterface, "TABLE_SKILL_1." + row + ".td4.color");
		}
		else
		{
		   if (diff > 0)
		   {
	          GameInterface.TABLE_SKILL_1.(row).td4.str = "(+" + diff + ")";
	          GameInterface.TABLE_SKILL_1.(row).td4.color = argb(255,196,255,196);
	       }
	       else
	       {
	          GameInterface.TABLE_SKILL_1.(row).td4.str = "(" + diff + ")";
	          GameInterface.TABLE_SKILL_1.(row).td4.color = argb(255,255,196,196);
	       }
		}
	}
	GameInterface.TABLE_SKILL_2.select = 0;
	GameInterface.TABLE_SKILL_2.hr.td1.str = "";
	for (i=1; i<=7; i++)
	{
	    row = "tr" + i;
	    skillName = GetSkillNameByTRIdx("ShipType", i);

        GameInterface.TABLE_SKILL_2.(row).UserData.ID = skillName;
		GameInterface.TABLE_SKILL_2.(row).td1.icon.group = "ICONS_SPEC";
	    GameInterface.TABLE_SKILL_2.(row).td1.icon.image = skillName + " skill icon";
	    GameInterface.TABLE_SKILL_2.(row).td1.icon.width = 35;
    	GameInterface.TABLE_SKILL_2.(row).td1.icon.height = 35;
    	GameInterface.TABLE_SKILL_2.(row).td1.icon.offset = "-3, -2";
		GameInterface.TABLE_SKILL_2.(row).td2.align = "left";
		GameInterface.TABLE_SKILL_2.(row).td2.textoffset = "5,0";
		GameInterface.TABLE_SKILL_2.(row).td3.align = "left";
		GameInterface.TABLE_SKILL_2.(row).td5.fontidx = 0;
		GameInterface.TABLE_SKILL_2.(row).td5.scale = 0.8;
		GameInterface.TABLE_SKILL_2.(row).td5.align = "left";

		GameInterface.TABLE_SKILL_2.(row).td2.str = XI_ConvertString(skillName);
		skillVal = GetSkillValue(xi_refCharacter, SKILL_TYPE, skillName);
		GameInterface.TABLE_SKILL_2.(row).td5.str = skillVal;
		// рассчет драйна
		diff = GetSummonSkillFromName(xi_refCharacter, skillName) - skillVal;

		if (skillVal < SKILL_MAX)
		{
			GameInterface.TABLE_SKILL_2.(row).td3.str = makeint(GetSkillValueExp(xi_refCharacter, skillName) * 100.0 / makefloat(skillVal * GetCharacterExpRate(xi_refCharacter, skillName))) + "%";
		}
		else
		{
		    GameInterface.TABLE_SKILL_2.(row).td3.str = "";
		}
		if (diff == 0)
		{
     		GameInterface.TABLE_SKILL_2.(row).td4.str = "";
     		DeleteAttribute(&GameInterface, "TABLE_SKILL_2." + row + ".td4.color");
		}
		else
		{
		   if (diff > 0)
		   {
	          GameInterface.TABLE_SKILL_2.(row).td4.str = "(+" + diff + ")";
	          GameInterface.TABLE_SKILL_2.(row).td4.color = argb(255,196,255,196);
	       }
	       else
	       {
	          GameInterface.TABLE_SKILL_2.(row).td4.str = "(" + diff + ")";
	          GameInterface.TABLE_SKILL_2.(row).td4.color = argb(255,255,196,196);
	       }
		}
	}
	////  остальное
	GameInterface.TABLE_OTHER.select = 0;
	GameInterface.TABLE_OTHER.hr.td1.str = "";
	for (i=1; i<=8; i++)
	{
	    row = "tr" + i;

	    GameInterface.TABLE_OTHER.(row).td1.icon.width = 40;
    	GameInterface.TABLE_OTHER.(row).td1.icon.height = 40;
    	GameInterface.TABLE_OTHER.(row).td1.icon.offset = "0, 0";
		GameInterface.TABLE_OTHER.(row).td2.align = "left";
		// GameInterface.TABLE_OTHER.(row).td2.scale = 0.85;
		GameInterface.TABLE_OTHER.(row).td2.textoffset = "10,0";
		GameInterface.TABLE_OTHER.(row).td3.align = "right";
	}
	GameInterface.TABLE_OTHER.tr1.UserData.ID = "Rank";
	GameInterface.TABLE_OTHER.tr1.td1.icon.group = "ICONS_CHAR";
    GameInterface.TABLE_OTHER.tr1.td1.icon.image = "Rank";
	GameInterface.TABLE_OTHER.tr1.td2.str = XI_ConvertString("Rank");
	GameInterface.TABLE_OTHER.tr1.td3.str = sti(xi_refCharacter.rank);

	GameInterface.TABLE_OTHER.tr2.UserData.ID = "Life";
	GameInterface.TABLE_OTHER.tr2.td1.icon.group = "ICONS_CHAR";
    GameInterface.TABLE_OTHER.tr2.td1.icon.image = "Life";
	GameInterface.TABLE_OTHER.tr2.td2.str = XI_ConvertString("Life");
	GameInterface.TABLE_OTHER.tr2.td3.str = MakeInt(LAi_GetCharacterHP(xi_refCharacter)) + " / " + MakeInt(LAi_GetCharacterMaxHP(xi_refCharacter));

    GameInterface.TABLE_OTHER.tr3.UserData.ID = "Health";
	GameInterface.TABLE_OTHER.tr3.td1.icon.group = "ICONS_CHAR";
    GameInterface.TABLE_OTHER.tr3.td1.icon.image = "Health";
	GameInterface.TABLE_OTHER.tr3.td2.str = XI_ConvertString("Health");
	GameInterface.TABLE_OTHER.tr3.td3.str = GetHealthName(xi_refCharacter);
	GameInterface.TABLE_OTHER.tr3.td3.scale = 1.3;

	if (GetHealthNum(xi_refCharacter) >= GetHealthMaxNum(xi_refCharacter))
    {
        GameInterface.TABLE_OTHER.tr3.td3.color = SetAlphaIntoColor(COLOR_MONEY, GetAlphaFromSkill(10));
    }
    else
    {
        GameInterface.TABLE_OTHER.tr3.td3.color = SetAlphaIntoColor(COLOR_NORMAL, GetAlphaFromSkill(makeint(GetHealthNum(xi_refCharacter)* 1.9)));
    }

    GameInterface.TABLE_OTHER.tr4.UserData.ID = "Energy";
	GameInterface.TABLE_OTHER.tr4.td1.icon.group = "ICONS_CHAR";
    GameInterface.TABLE_OTHER.tr4.td1.icon.image = "Energy";
	GameInterface.TABLE_OTHER.tr4.td2.str = XI_ConvertString("Energy");
	GameInterface.TABLE_OTHER.tr4.td3.str = sti(Lai_CharacterGetEnergy(xi_refCharacter)) + " / " + sti(LAi_GetCharacterMaxEnergy(xi_refCharacter));
	diff = sti(LAi_GetCharacterMaxEnergy(xi_refCharacter) - GetCharacterMaxEnergyABSValue(xi_refCharacter));
	if (diff != 0)
	{
	   if (diff > 0)
	   {
          GameInterface.TABLE_OTHER.tr4.td3.color = argb(255,196,255,196);
       }
       else
       {
          GameInterface.TABLE_OTHER.tr4.td3.color = argb(255,255,196,196);
       }
	}
	else
	{
		DeleteAttribute(&GameInterface, "TABLE_OTHER.tr4.td3.color");
	}

	GameInterface.TABLE_OTHER.tr5.UserData.ID = "Money";
	GameInterface.TABLE_OTHER.tr5.td1.icon.group = "ICONS_CHAR";
    GameInterface.TABLE_OTHER.tr5.td1.icon.image = "Money";
	GameInterface.TABLE_OTHER.tr5.td2.str = XI_ConvertString("Money");
	GameInterface.TABLE_OTHER.tr5.td3.str = MakeMoneyShow(sti(xi_refCharacter.Money), MONEY_SIGN,MONEY_DELIVER);
	//GameInterface.TABLE_OTHER.tr5.td3.scale = 0.95;
	//GameInterface.TABLE_OTHER.tr5.td3.color = SetAlphaIntoColor(COLOR_MONEY, GetAlphaFromSkill(10));

/*	
    GameInterface.TABLE_OTHER.tr6.UserData.ID = "Reputation";
	GameInterface.TABLE_OTHER.tr6.td1.icon.group = "ICONS_CHAR";
    GameInterface.TABLE_OTHER.tr6.td1.icon.image = "Reputation";
	GameInterface.TABLE_OTHER.tr6.td2.str = XI_ConvertString("Reputation");
	GameInterface.TABLE_OTHER.tr6.td3.str = XI_ConvertString(GetReputationName(sti(xi_refCharacter.reputation)));
*/
	GameInterface.TABLE_OTHER.tr6.UserData.ID = "weight";
	GameInterface.TABLE_OTHER.tr6.td1.icon.group = "ICONS_CHAR";
    GameInterface.TABLE_OTHER.tr6.td1.icon.image = "weight";
	GameInterface.TABLE_OTHER.tr6.td2.str = XI_ConvertString("weight");
	GameInterface.TABLE_OTHER.tr6.td3.str = FloatToString(GetItemsWeight(xi_refCharacter), 1) + " / "+GetMaxItemsWeight(xi_refCharacter);

    GameInterface.TABLE_OTHER.tr7.UserData.ID = "Title";
	GameInterface.TABLE_OTHER.tr7.td1.icon.group = "ICONS_CHAR";
	GameInterface.TABLE_OTHER.tr7.td1.icon.image = "Title";

	DeleteAttribute(&GameInterface, "TABLE_OTHER.tr7.td2");
	GameInterface.TABLE_OTHER.tr7.td2.str = XI_ConvertString("Title");
	GameInterface.TABLE_OTHER.tr7.td2.align = "left";
	GameInterface.TABLE_OTHER.tr7.td2.textoffset = "10,0";

    DeleteAttribute(&GameInterface, "TABLE_OTHER.tr7.td3");
    GameInterface.TABLE_OTHER.tr7.td3.str = "";

	if (xi_refCharacter.id == pchar.id && isMainCharacterPatented())
    {
        GameInterface.TABLE_OTHER.tr7.td3.str = GetAddress_FormTitle(sti(Items[sti(pchar.EquipedPatentId)].Nation), sti(Items[sti(pchar.EquipedPatentId)].TitulCur));
        GameInterface.TABLE_OTHER.tr7.td2.icon.group = "NATIONS";
		GameInterface.TABLE_OTHER.tr7.td2.icon.image = GetNationNameByType(sti(Items[sti(pchar.EquipedPatentId)].Nation));
		GameInterface.TABLE_OTHER.tr7.td2.icon.offset = "80, 5";
		GameInterface.TABLE_OTHER.tr7.td2.icon.width = 30;
		GameInterface.TABLE_OTHER.tr7.td2.icon.height = 30;
    }
    else
    {
        GameInterface.TABLE_OTHER.tr7.td3.str = XI_ConvertString("NoTitle");
        GameInterface.TABLE_OTHER.tr7.td3.align = "right";
    }

	GameInterface.TABLE_OTHER.tr8.UserData.ID = "NextExp";
	GameInterface.TABLE_OTHER.tr8.td1.icon.group = "ICONS_CHAR";
    GameInterface.TABLE_OTHER.tr8.td1.icon.image = "NextExp";
	GameInterface.TABLE_OTHER.tr8.td2.str = XI_ConvertString("NextExp");
	GameInterface.TABLE_OTHER.tr8.td3.str = "";

	// прорисовка
	Table_UpdateWindow("TABLE_SPECIAL");
    Table_UpdateWindow("TABLE_SKILL_1");
    Table_UpdateWindow("TABLE_SKILL_2");
    Table_UpdateWindow("TABLE_PERKS");
    Table_UpdateWindow("TABLE_PERKS2");
    Table_UpdateWindow("TABLE_OTHER");
}

void CS_TableSelectChange()
{
	bfirst = false;
	string sControl = GetEventData();
	iSelected = GetEventData();
    CurTable = sControl;
	bool ok = CurTable == "TABLE_PERKS" || CurTable == "TABLE_PERKS2";
    CurRow   =  "tr" + (iSelected);
    //sti(GameInterface.(sControl).(sRow).index);
 	NullSelectTable("TABLE_SPECIAL");
    NullSelectTable("TABLE_SKILL_1");
    NullSelectTable("TABLE_SKILL_2");
    NullSelectTable("TABLE_PERKS");
    NullSelectTable("TABLE_PERKS2");
    NullSelectTable("TABLE_OTHER");
    // перерисует порог опыта
    GameInterface.TABLE_OTHER.tr9.td3.str = "";
    if (CurTable == "TABLE_OTHER" && CurRow == "tr1")
    {
    	GameInterface.TABLE_OTHER.tr9.td3.str = GetCharacterRankRateCur(xi_refCharacter) + "/" + GetCharacterRankRate(xi_refCharacter);
    }
    sti(xi_refCharacter.rank_exp)
	if (CurTable == "TABLE_SKILL_1" || CurTable == "TABLE_SKILL_2")
	{
        string skillName;
        int skillVal;
        skillName = GameInterface.(CurTable).(CurRow).UserData.ID;
        skillVal = GetSkillValue(xi_refCharacter, SKILL_TYPE, skillName);
		if (skillVal != SKILL_MAX && skillVal != 0)
		{
	       GameInterface.TABLE_OTHER.tr9.td3.str = sti(GetSkillValueExp(xi_refCharacter, skillName))+ "/" + makeint(skillVal * GetCharacterExpRate(xi_refCharacter, skillName));
		}
	}
	Table_UpdateWindow("TABLE_OTHER");
	// установим скилчанжер, если нужно
	HideSkillChanger();
    SetSkillArrows();
	if (ok)
	{
		ChoosePerk();
		SetNodeUsing("PERKPICTURE_BASE", true);
	} else {
		ChoosePerk();
		SetNodeUsing("PERKPICTURE_BASE", false);
	}
}

void SetSkillArrows()
{
   	bool ok;
	int  minP;
	ok = CurTable == "TABLE_SKILL_1" || CurTable == "TABLE_SKILL_2";
	if (sti(xi_refCharacter.skill.freeskill) > 0 && ok && !bChangePIRATES)  //для начала игры фиг
	{
	    if (GetSkillValue(xi_refCharacter, SKILL_TYPE, GameInterface.(CurTable).(CurRow).UserData.ID) > 1)
        {
			if (CurTable == "TABLE_SKILL_1")
			{
				SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE,"B_SKILLDown",0, 890 ,450 + 35*(iSelected-1), 915, 450 + 36 + 35*(iSelected-1), 0);
			}
			else
			{
				SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE,"B_SKILLDown",0, 890 ,730 + 35*(iSelected-1), 915,730 + 36 + 35*(iSelected-1), 0);
			}
			SetNodeUsing("B_SKILLDown", true);
        }
        if (GetSkillValue(xi_refCharacter, SKILL_TYPE, GameInterface.(CurTable).(CurRow).UserData.ID) < SKILL_MAX)
        {
            if (CurTable == "TABLE_SKILL_1")
			{
				SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE,"B_SKILLUP",0, 950,450 + 35*(iSelected-1),975,450 + 36 + 35*(iSelected-1), 0);
			}
			else
			{
				SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE,"B_SKILLUP",0, 950,730 + 35*(iSelected-1),975,730 + 36 + 35*(iSelected-1), 0);
			}
            SetNodeUsing("B_SKILLUP",  true);
        }
	}
	ok = sti(xi_refCharacter.skill.freeskill) > 0 || sti(xi_refCharacter.skill.FreeSPECIAL) > 0 || bChangePIRATES;  //для начала игры
	if (ok && CurTable == "TABLE_SPECIAL")
	{
        minP = 1;
        if (bChangePIRATES)
        {
            minP = 3;
        }
	    if (GetSkillValue(xi_refCharacter, SPECIAL_TYPE, GameInterface.(CurTable).(CurRow).UserData.ID) > minP)
        {
			SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE,"B_SKILLDown",0, 890 ,170 + 35*(iSelected-1), 915, 170 + 36 + 35*(iSelected-1), 0);
			SetNodeUsing("B_SKILLDown", true);
        }
        if (GetSkillValue(xi_refCharacter, SPECIAL_TYPE, GameInterface.(CurTable).(CurRow).UserData.ID) < SPECIAL_MAX)
        {
			SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE,"B_SKILLUP",0, 950,170 + 35*(iSelected-1),975,170 + 36 + 35*(iSelected-1), 0);
            SetNodeUsing("B_SKILLUP",  true);
        }
	}
}
void NullSelectTable(string sControl)
{
	if (sControl != CurTable)
	{
	    GameInterface.(sControl).select = 0;
	    Table_UpdateWindow(sControl);
	}
}

void SetOfficersSkills()
{
	string sCharacter = "pic"+(sti(GameInterface.PASSENGERSLIST.current)+1);
	if (checkAttribute(GameInterface, "PASSENGERSLIST."+sCharacter))
	{
		if (checkAttribute(GameInterface, "PASSENGERSLIST."+sCharacter + ".character"))
		{
			sCharacter = GameInterface.PASSENGERSLIST.(sCharacter).character;
			ref otherchr = &characters[sti(sCharacter)];
	        SetSPECIALMiniTable("TABLE_SMALLSKILL", otherchr);
	        SetOTHERMiniTable("TABLE_SMALLOTHER", otherchr);
	        SetFormatedText("OFFICER_NAME", GetFullName(otherchr));
	        SetSelectable("ACCEPT_ADD_OFFICER", true);
        }
        else
        {
            Table_Clear("TABLE_SMALLSKILL", false, true, true);
            Table_Clear("TABLE_SMALLOTHER", false, true, true);
            SetFormatedText("OFFICER_NAME", "");
            SetSelectable("ACCEPT_ADD_OFFICER", false);
        }
	}
	else
    {
        Table_Clear("TABLE_SMALLSKILL", false, true, true);
        Table_Clear("TABLE_SMALLOTHER", false, true, true);
        SetFormatedText("OFFICER_NAME", "");
        SetSelectable("ACCEPT_ADD_OFFICER", false);
    }
}

void HideSkillChanger()
{
    SetNodeUsing("B_SKILLUP",  false);
	SetNodeUsing("B_SKILLDown",  false);
}

void IncreaseSkill(int _add)
{
	int     iValue;
	string  sSkillName;

    sSkillName = GameInterface.(CurTable).(CurRow).UserData.ID;
    if (CurTable != "TABLE_SPECIAL")
    {
		if (sti(xi_refCharacter.skill.freeskill) < _add) _add = sti(xi_refCharacter.skill.freeskill);
		if ((GetSkillValue(xi_refCharacter, SKILL_TYPE, sSkillName) + _add) > SKILL_MAX)
		{
		    _add = SKILL_MAX - GetSkillValue(xi_refCharacter, SKILL_TYPE, sSkillName);
		}
	    if (_add > 0)
	    {
	        iValue = AddCharacterSkill(xi_refCharacter, sSkillName, _add);
			xi_refCharacter.skill.freeskill = sti(xi_refCharacter.skill.freeskill) - _add;
	    }
	    else return;
    }
    else
    {
        if (sti(xi_refCharacter.skill.FreeSPECIAL) < _add) _add = sti(xi_refCharacter.skill.FreeSPECIAL);
		if ((GetSkillValue(xi_refCharacter, SPECIAL_TYPE, sSkillName) + _add) > SPECIAL_MAX)
		{
		    _add = SPECIAL_MAX - GetSkillValue(xi_refCharacter, SPECIAL_TYPE, sSkillName);
		}
	    if (_add > 0)
	    {
	        iValue = AddSPECIALValue(xi_refCharacter, sSkillName, _add);
			xi_refCharacter.skill.FreeSPECIAL = sti(xi_refCharacter.skill.FreeSPECIAL) - _add;
	    }
	    else return;
	    
	    if (bChangePIRATES)
	    { //для начала игры пересчет скилов
	    	// начальные скилы задать
			if (!bChangePIRATESNotFirstTime) {
				InitStartParam(xi_refCharacter);
			} else {
				if(oldRank == sti(xi_refCharacter.rank)) {
					if(CheckAttribute(xi_refCharacter, "chr_ai.hp_max_back")) {
						xi_refCharacter.chr_ai.hp_max_back = stf(xi_refCharacter.chr_ai.hp_max_back) - HPDelta + GetHPIncrease(xi_refCharacter);
					} else {
						xi_refCharacter.chr_ai.hp_max = stf(xi_refCharacter.chr_ai.hp_max) - HPDelta + GetHPIncrease(xi_refCharacter);
					}
				}
				
				HPDelta = GetHPIncrease(xi_refCharacter);
				oldRank = sti(xi_refCharacter.rank);
			}
		    SetEnergyToCharacter(xi_refCharacter);
	    }
    }
	SetVariable();
	SetSkillArrows();
}

void DecreaseSkill(int _add)
{
	int     iValue;
	string  sSkillName;

    sSkillName = GameInterface.(CurTable).(CurRow).UserData.ID;
    if (CurTable != "TABLE_SPECIAL")
    {
	    if (GetSkillValue(xi_refCharacter, SKILL_TYPE, sSkillName) <= _add)
	    {
	        _add = GetSkillValue(xi_refCharacter, SKILL_TYPE, sSkillName) - 1;
	    }
	    if (_add > 0)
	    {
	        iValue = AddCharacterSkill(xi_refCharacter, sSkillName, -_add);
			xi_refCharacter.skill.freeskill = sti(xi_refCharacter.skill.freeskill) + _add;
	    }
	    else return;
    }
    else
    {
		if (GetSkillValue(xi_refCharacter, SPECIAL_TYPE, sSkillName) <= _add)
	    {
	        _add = GetSkillValue(xi_refCharacter, SPECIAL_TYPE, sSkillName) - 1;
	    }
	    if (bChangePIRATES && (GetSkillValue(xi_refCharacter, SPECIAL_TYPE, sSkillName) - _add) < 3)
        {
            _add = GetSkillValue(xi_refCharacter, SPECIAL_TYPE, sSkillName) - 3;
		}
	    if (_add > 0)
	    {
	        iValue = AddSPECIALValue(xi_refCharacter, sSkillName, -_add);
			xi_refCharacter.skill.FreeSPECIAL = sti(xi_refCharacter.skill.FreeSPECIAL) + _add;
	    }
	    else return;
	    
	    if (bChangePIRATES)
	    { //для начала игры пересчет скилов
	    	// начальные скилы задать
		    if (!bChangePIRATESNotFirstTime) {
				InitStartParam(xi_refCharacter);
			} else {
				if(CheckAttribute(xi_refCharacter, "chr_ai.hp_max_back")) {
					xi_refCharacter.chr_ai.hp_max_back = stf(xi_refCharacter.chr_ai.hp_max_back) - HPDelta + GetHPIncrease(xi_refCharacter);
				} else {
					xi_refCharacter.chr_ai.hp_max = stf(xi_refCharacter.chr_ai.hp_max) - HPDelta + GetHPIncrease(xi_refCharacter);
				}
				
				HPDelta = GetHPIncrease(xi_refCharacter);
			}
		    SetEnergyToCharacter(xi_refCharacter);
	    }
    }
    SetVariable();
    SetSkillArrows();
}
///////////////////////////////////////  PERKS /////////////////////////
void FillPerksTable(string _type, bool _refresh)
{
	int perksQ, i, n;
	string perkName, row, icoGroup;
	aref arPerksRoot;
	
    Table_Clear("TABLE_PERKS", false, true, false);
	GameInterface.TABLE_PERKS.hr.td1.str = "";
	if (_refresh)
	{
	    GameInterface.TABLE_PERKS.select = 0;
	    GameInterface.TABLE_PERKS.top = 0;
	}
	
	makearef(arPerksRoot,ChrPerksList.list); // общий список
	perksQ = GetAttributesNum(arPerksRoot);
	n = 1;
	for(i=0; i<perksQ; i++)
	{
	    row = "tr" + n;

        perkName = GetAttributeName(GetAttributeN(arPerksRoot,i));
        if (xi_refCharacter.id == pchar.id && CheckAttribute(arPerksRoot, perkName + ".NPCOnly")) continue;
        if (xi_refCharacter.id != pchar.id && CheckAttribute(arPerksRoot, perkName + ".PlayerOnly")) continue;
        if (CheckAttribute(arPerksRoot, perkName + ".Hiden")) continue;

		if (!CheckAttribute(arPerksRoot, perkName + ".BaseType")) // to_DO
        {
            arPerksRoot.(perkName).BaseType = "self";
        }
		if (CheckAttribute(arPerksRoot, perkName + ".BaseType") && arPerksRoot.(perkName).BaseType == _type)
		{
			GameInterface.TABLE_PERKS.(row).UserData.ID   = perkName;
			GameInterface.TABLE_PERKS.(row).UserData.Type = _type;
            if (CheckCharacterPerk(xi_refCharacter, perkName))
            {
				icoGroup = "PERKS_ENABLE";
                GameInterface.TABLE_PERKS.(row).td2.color = argb(255,255,255,255);
            }
            else
            {
                icoGroup = "PERKS_DISABLE";
                GameInterface.TABLE_PERKS.(row).td2.color = argb(255,196,196,196);
            }
			GameInterface.TABLE_PERKS.(row).td1.icon.group  = icoGroup;
			GameInterface.TABLE_PERKS.(row).td1.icon.image  = perkName;
			GameInterface.TABLE_PERKS.(row).td1.icon.width  = 50;
		    GameInterface.TABLE_PERKS.(row).td1.icon.height = 50;
		    GameInterface.TABLE_PERKS.(row).td1.icon.offset = "-3, -2";
			GameInterface.TABLE_PERKS.(row).td2.line_space_modifier = 0.9;
			GameInterface.TABLE_PERKS.(row).td2.str = GetConvertStr(perkName, "AbilityDescribe.txt");
			GameInterface.TABLE_PERKS.(row).td2.textoffset = "0,0";
			// GameInterface.TABLE_PERKS.(row).td2.scale = 0.80;
			n++;
		}
	}
	// прорисовка
	Table_UpdateWindow("TABLE_PERKS");
}

void FillPerksTable2(string _type, bool _refresh)
{
	int perksQ, i, n;
	string perkName, row, icoGroup;
	aref arPerksRoot;

    Table_Clear("TABLE_PERKS2", false, true, false);
	GameInterface.TABLE_PERKS2.hr.td1.str = "";
	if (_refresh)
	{
	    GameInterface.TABLE_PERKS2.select = 0;
	    GameInterface.TABLE_PERKS2.top = 0;
	}

	makearef(arPerksRoot,ChrPerksList.list); // общий список
	perksQ = GetAttributesNum(arPerksRoot);
	n = 1;
	for(i=0; i<perksQ; i++)
	{
	    row = "tr" + n;

        perkName = GetAttributeName(GetAttributeN(arPerksRoot,i));
        if (xi_refCharacter.id == pchar.id && CheckAttribute(arPerksRoot, perkName + ".NPCOnly")) continue;
        if (xi_refCharacter.id != pchar.id && CheckAttribute(arPerksRoot, perkName + ".PlayerOnly")) continue;
        if (CheckAttribute(arPerksRoot, perkName + ".Hiden")) continue;

        if (!CheckAttribute(arPerksRoot, perkName + ".BaseType")) // to_DO
        {
            arPerksRoot.(perkName).BaseType = "self";
        }
		if (CheckAttribute(arPerksRoot, perkName + ".BaseType") && arPerksRoot.(perkName).BaseType == _type)
		{
			GameInterface.TABLE_PERKS2.(row).UserData.ID   = perkName;
			GameInterface.TABLE_PERKS2.(row).UserData.Type = _type;
            if (CheckCharacterPerk(xi_refCharacter, perkName))
            {
                icoGroup = "PERKS_ENABLE";
                GameInterface.TABLE_PERKS2.(row).td2.color = argb(255,255,255,255);
            }
            else
            {
                icoGroup = "PERKS_DISABLE";
                GameInterface.TABLE_PERKS2.(row).td2.color = argb(255,196,196,196);
            }
			GameInterface.TABLE_PERKS2.(row).td1.icon.group  = icoGroup;
			GameInterface.TABLE_PERKS2.(row).td1.icon.image  = perkName;
			GameInterface.TABLE_PERKS2.(row).td1.icon.width  = 50;
		    GameInterface.TABLE_PERKS2.(row).td1.icon.height = 50;
		    GameInterface.TABLE_PERKS2.(row).td1.icon.offset = "-3, -2";
			GameInterface.TABLE_PERKS2.(row).td2.line_space_modifier = 0.9;
			GameInterface.TABLE_PERKS2.(row).td2.str = GetConvertStr(perkName, "AbilityDescribe.txt");
			GameInterface.TABLE_PERKS2.(row).td2.textoffset = "0,0";
			n++;
		}
	}
	// прорисовка
	Table_UpdateWindow("TABLE_PERKS2");
}

void ChoosePerk()
{
	bool ok = false;
	bool showCondition = true;
	string perkName;
	if(bfirst) perkName = GameInterface.TABLE_PERKS.tr1.UserData.ID;
	else perkName = GameInterface.(CurTable).(CurRow).UserData.ID;
	string  descr    = GetConvertStr("perk" + perkName, "AbilityDescribe.txt");
	aref rootItems;
	int    i;
	string row, perkCond, icoGroup;
	SetNewGroupPicture("PERKPICTURE", "PERKS_ENABLE", perkName);
    SetFormatedText("PERK_WINDOW_CAPTION", GetConvertStr(perkName, "AbilityDescribe.txt"));

    SetFormatedText("PERK_WINDOW_TEXT", descr);
    SetVAligmentFormatedText("PERK_WINDOW_TEXT");

    if (CurTable == "TABLE_PERKS" || CurTable == "TABLE_PERKS2")
	{
		ok = true;
		//if (bChangePIRATES && bChangePIRATESNotFirstTime) ok = false;
		if (GameInterface.(CurTable).(CurRow).UserData.Type == "self")
		{
			if (sti(xi_refCharacter.perks.FreePoints_self) <= 0) ok = false;
		}
		else
		{
			if (sti(xi_refCharacter.perks.FreePoints_ship) <= 0) ok = false;
		}
		if (CheckPerkFilter(perkName)) ok = false;
	}
	// проверка на необходимые перки -->
	if (CheckAttribute(&ChrPerksList, "list." + perkName + ".condition"))
	{
        makearef(rootItems, ChrPerksList.list.(perkName).condition);
		Table_Clear("PERK_TABLE_NEED", false, true, false);
		GameInterface.PERK_TABLE_NEED.select = 0;
		GameInterface.PERK_TABLE_NEED.hr.td1.str = "";
		GameInterface.PERK_TABLE_NEED.top = 0;
		for (i=0; i<GetAttributesNum(rootItems); i++)
    	{
    	    row = "tr" + (i+1);
    	    perkCond = GetAttributeName(GetAttributeN(rootItems, i));
    	    if (CheckCharacterPerk(xi_refCharacter, perkCond))
            {
                icoGroup = "PERKS_ENABLE";
                GameInterface.PERK_TABLE_NEED.(row).td2.color = argb(255,255,255,255);
            }
            else
            {
                icoGroup = "PERKS_DISABLE";
                GameInterface.PERK_TABLE_NEED.(row).td2.color = argb(255,196,196,196);
                ok = false;
            }
			GameInterface.PERK_TABLE_NEED.(row).td1.icon.group  = icoGroup;
			GameInterface.PERK_TABLE_NEED.(row).td1.icon.image  = perkCond;
			GameInterface.PERK_TABLE_NEED.(row).td1.icon.width  = 40;
		    GameInterface.PERK_TABLE_NEED.(row).td1.icon.height = 40;
		    GameInterface.PERK_TABLE_NEED.(row).td1.icon.offset = "0, 2";
			GameInterface.PERK_TABLE_NEED.(row).td2.str = GetConvertStr(perkCond, "AbilityDescribe.txt");
			GameInterface.PERK_TABLE_NEED.(row).td2.line_space_modifier = 0.8;
			GameInterface.PERK_TABLE_NEED.(row).td2.textoffset = "0,2";
    	}
		Table_UpdateWindow("PERK_TABLE_NEED");
	}
	else
	{
	    showCondition = false;
	}
	// проверка на необходимык перки <--

    // проверка ранга
    if (CheckAttribute(&ChrPerksList, "list." + perkName + ".rank") && sti(xi_refCharacter.rank) < sti(ChrPerksList.list.(perkName).rank))
	{
        ok = false;
    }

	XI_WindowShow("PERK_WINDOW", true);
	XI_WindowDisable("PERK_WINDOW", false);
	// XI_WindowDisable("MAIN_WINDOW", true);

	if (CheckCharacterPerk(xi_refCharacter, perkName))
 	{
 	    SetNodeUsing("PERK_ON", true);
 	    ok = false; // уже есть
   	    SetNewGroupPicture("PERKPICTURE", "PERKS_ENABLE", perkName);
		if (ChrPerksList.list.(perkName).BaseType == "self"){
			SetNewGroupPicture("PERKPICTURE_BASE", "PERKS_ENABLE", "base_self");
		} else {
			SetNewGroupPicture("PERKPICTURE_BASE", "PERKS_ENABLE", "base_ship");
		}
	}
 	else
 	{
 	    SetNodeUsing("PERK_ON", false);
 	    SetNewGroupPicture("PERKPICTURE", "PERKS_DISABLE", perkName);
 		SetNewGroupPicture("PERKPICTURE_BASE", "PERKS_DISABLE", "base");
	}
    SetNodeUsing("PERK_ACCEPT", ok);
    SetNodeUsing("PERK_TABLE_NEED", showCondition);
}

void ExitPerkMenu()
{
	XI_WindowShow("PERK_WINDOW", false);
	XI_WindowDisable("PERK_WINDOW", true);
	// XI_WindowDisable("MAIN_WINDOW", false);

	SetCurrentNode("TABLE_PERKS");
}

void AcceptPerk()
{
    string  perkName = GameInterface.(CurTable).(CurRow).UserData.ID;
    if (GameInterface.(CurTable).(CurRow).UserData.Type == "self")
    {
		xi_refCharacter.perks.Points_self = sti(xi_refCharacter.perks.Points_self) + 1;
		xi_refCharacter.perks.FreePoints_self = sti(xi_refCharacter.perks.FreePoints_self) - 1;
	}
	else
	{
		xi_refCharacter.perks.Points_ship = sti(xi_refCharacter.perks.Points_ship) + 1;
		xi_refCharacter.perks.FreePoints_ship = sti(xi_refCharacter.perks.FreePoints_ship) - 1;
    }
    SetCharacterPerk(xi_refCharacter, perkName);
    // перерисуем все -->
    SetFormatedText("PERSONAL_AVAILABLE", XI_ConvertString("Personal_abilities") + " " + xi_refCharacter.perks.Points_self);
    SetFormatedText("SHIP_AVAILABLE", XI_ConvertString("Ship_abilities") + " " + xi_refCharacter.perks.Points_ship);
	FillPerksTable("Self", true);  // Личные навыки
	FillPerksTable2("Ship", true);  // Корабельные навыки
    // FillPerksTable(GameInterface.(CurTable).(CurRow).UserData.Type, false);
    // FillPerksTable2(GameInterface.(CurTable).(CurRow).UserData.Type, false);
    // перерисуем все <--
	ExitPerkMenu();
}

void ExitMsgMenu()
{
	XI_WindowShow("MSG_WINDOW", false);
	XI_WindowDisable("MSG_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);

	SetCurrentNode("TABLE_OTHER");
}

void ShowMsgMenu()
{
	XI_WindowShow("MSG_WINDOW", true);
	XI_WindowDisable("MSG_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);

	SetCurrentNode("MSG_OK");
}

//проверка на лишние перки
bool CheckPerkFilter(string perkName) {
	if(xi_refCharacter.id == pchar.id && CheckAttribute(&ChrPerksList, "list." + perkName + ".NPCOnly")) return true;
	if(xi_refCharacter.id != pchar.id && CheckAttribute(&ChrPerksList, "list." + perkName + ".PlayerOnly")) return true;
	if(!CheckCharacterPerk(xi_refCharacter, "HT1") && perkName == "FencingMaster") return true; 
	if(!CheckCharacterPerk(xi_refCharacter, "HT1") && perkName == "TannedLeather") return true;
	if(!CheckCharacterPerk(xi_refCharacter, "HT2") && perkName == "RatsWolf") return true;
	if(!CheckCharacterPerk(xi_refCharacter, "HT2") && perkName == "Mimicry") return true;
	if(!CheckCharacterPerk(xi_refCharacter, "HT2") && perkName == "TreasureHunter") return true;
	if(!CheckCharacterPerk(xi_refCharacter, "HT3") && perkName == "Dragoon") return true;
	if(!CheckCharacterPerk(xi_refCharacter, "HT3") && perkName == "SecondWind") return true;
	if(!CheckCharacterPerk(xi_refCharacter, "HT4") && perkName == "Jager") return true;
	if(!CheckCharacterPerk(xi_refCharacter, "HT4") && perkName == "Bombardier") return true;
	if(!CheckCharacterPerk(xi_refCharacter, "HT4") && perkName == "Sniper") return true;        
	return false;
}