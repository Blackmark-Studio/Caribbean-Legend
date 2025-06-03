/// Sith, EvgAnat меню наций
#event_handler("Control Activation","ProcessInterfaceControls");// гуляем по меню кнопками Q и E
ref xi_refCharacter
int curNationIdx;

string CurTable, CurRow, CurCol;
int iSelected, iSelectedCol;

void InitInterface(string iniName)
{
	xi_refCharacter = pchar;
    InterfaceStack.SelectMenu_node = "LaunchNationRelation"; // запоминаем, что звать по Ф2
	GameInterface.title = "titleNationRelation";
	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);	
	ref chref = GetMainCharacter();
 
	SetEventHandler("InterfaceBreak","ProcessExitCancel",0);
	SetEventHandler("exitCancel","ProcessExitCancel",0);
    SetEventHandler("FlagsPress","FlagsProcess",0);
    SetEventHandler("ievnt_command","ProcessCommandExecute",0);
    SetEventHandler("MouseRClickUP","HideInfo",0);
	SetEventHandler("OnTableRClick", "OnTableRClick", 0);
	SetEventHandler("ShowInfoWindow","ShowInfoWindow",0);
    
	// доп инфа в шапку --->
	SetFormatedText("Weight", FloatToString(GetItemsWeight(xi_refCharacter), 1) + " / " + GetMaxItemsWeight(xi_refCharacter));
	SetFormatedText("Money", FindRussianMoneyString(sti(xi_refCharacter.money)));
	SetFormatedText("Dublon", FindRussianDublonString(sti(xi_refCharacter.dublon)));
	SetFormatedText("Rank", xi_refCharacter.rank);
	SetFormatedText("Rank_progress", GetCharacterRankRateCur(xi_refCharacter) + " / " + GetCharacterRankRate(xi_refCharacter));
	// порог уровня
	GameInterface.StatusLine.BAR_RANK.Max   = GetCharacterRankRate(xi_refCharacter);
	GameInterface.StatusLine.BAR_RANK.Min   = 0;
	GameInterface.StatusLine.BAR_RANK.Value = GetCharacterRankRateCur(xi_refCharacter);	
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"BAR_RANK",0);
	// <--- 	
    /////////////	
    CalculateHunter();

	string descr = XI_ConvertString("Mechanics_descr");
	SetFormatedText("INFO_MECH", descr);
	// SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"INFO_MECH",5);

	int nStrings = GetNumberOfStringsInFormatedText("INFO_MECH", descr); // считаем сколько строк в форме
	// Log_TestInfo("Всего строк " + nStrings);
	if(nStrings <8)// Запрет на скроллинг
	{
		SetNodeUsing("SCROLL_MECH",false);
		SendMessage( &GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"INFO_MECH", 13, 1 ); //1 - запрет, 0 - нет
	}

    curNationIdx = sti(chref.nation);
    SetNewNation(0);
    XI_RegistryExitKey("IExit_F2");
	SetAlertMarks(xi_refCharacter);
	
	SetNationWars();
	SetNationThreatLevel();
	SetPiratesThreatLevel();
	SetSquadronTable();
	SetThreatLevel();
}

// гуляем по меню кнопками Q и E
void ProcessInterfaceControls() 
{
    string controlName = GetEventData();
 
	if (controlName == "InterfaceGoLeft") {
        IDoExit(RC_INTERFACE_ABILITIES);
    }
	if (controlName == "InterfaceGoRight") {
        IDoExit(RC_INTERFACE_INVENTORY);
    }
}

void ProcessExitCancel()
{
	IDoExit(RC_INTERFACE_ANY_EXIT);
}

void IDoExit(int exitCode)
{
	DelEventHandler("InterfaceBreak","ProcessExitCancel");
	DelEventHandler("exitCancel","ProcessExitCancel");
    DelEventHandler("FlagsPress","FlagsProcess");
    DelEventHandler("ievnt_command","ProcessCommandExecute");
    DelEventHandler("MouseRClickUP","HideInfo");
	DelEventHandler("OnTableRClick", "OnTableRClick");
	DelEventHandler("ShowInfoWindow","ShowInfoWindow");

	interfaceResultCommand = exitCode;
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

void OnTableRClick()
{
	string sControl = GetEventData();
	iSelected = GetEventData();
	iSelectedCol = GetEventData();
	CurTable = sControl;
	CurRow   =  "tr" + (iSelected);
	CurCol   =  "td" + (iSelectedCol);
	Table_UpdateWindow(sControl);
}

void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();
    switch(nodName)
	{
        case "LEFTCHANGE_NATION":
    		if(comName=="activate" || comName=="click")
    		{
				if (!CheckAttribute(pchar, "DisableChangeFlagMode"))
				{
					SetNewNation(-1);
				}
    		}
    	break;

    	case "RIGHTCHANGE_NATION":
    		if(comName=="activate" || comName=="click")
    		{
                if (!CheckAttribute(pchar, "DisableChangeFlagMode"))
                {
					SetNewNation(1);
				}
    		}
    	break;
		/////////////////////// menu ///////////////
		case "I_INVENTORY_2":
			if(comName=="click")
			{
			    nodName = "I_INVENTORY";
			}
		break;
		case "I_SHIP_2":
			if(comName=="click")
			{
			    nodName = "I_SHIP";
			}
		break;
		case "I_QUESTBOOK_2":
			if(comName=="click")
			{
			    nodName = "I_QUESTBOOK";
			}
		break;
		case "I_JOURNAL_2":
			if(comName=="click")
			{
			    nodName = "I_JOURNAL";
			}
		break;
		case "I_ATLAS_2":
			if(comName=="click")
			{
			    nodName = "I_ATLAS";
			}
		break;
		case "I_ABILITIES_2":
			if(comName=="click")
			{
			    nodName = "I_ABILITIES";
			}
		break;
		case "I_NATIONS_2":
			if(comName=="click")
			{
			    nodName = "I_NATIONS";
			}
		break;
		case "I_ITEMS_2":
			if(comName=="click")
			{
			    nodName = "I_ITEMS";
			}
		break;
	}
	// boal new menu 31.12.04 -->
	if (nodName == "I_INVENTORY" || nodName == "I_SHIP" ||
	    nodName == "I_QUESTBOOK" || nodName == "I_JOURNAL" || nodName == "I_ATLAS" || nodName == "I_ABILITIES" ||
		nodName == "I_NATIONS" || nodName == "I_ITEMS")
	{
		if(comName=="click")
		{
            InterfaceStates.ReloadMenuExit = true;
			IDoExit(RC_INTERFACE_ANY_EXIT);
			PostEvent("LaunchIAfterFrame",1,"sl", nodName, 2);
			return;
		}
	}
	// boal new menu 31.12.04 -->
}

void ShowInfoWindow()
{
	// string sHeader = "TEST";
	string sCurrentNode = GetCurrentNode();
	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;
	string sText;
	int iShip, iChar;
	ref refBaseShip, refChar;

	switch(sCurrentNode)
	{
		case "FLAGPIC":
			sHeader = XI_ConvertString("Nation");
			sText1 = GetRPGText("Nation_hint");
		break;
		case "INFO_CLICK":
			sHeader = XI_ConvertString("Hunter_type");
			sText1 = GetRPGText("Hunter_hint");
		break;
		case "TABLE_SQUADRON":
			sHeader = XI_Convertstring("SquadPower");
			sText1 = XI_Convertstring("Mechanics_descr");
			if(CheckAttribute(GameInterface, CurTable + "." + CurRow + "." + CurCol + ".shipId"))
			{
				iShip = GameInterface.(CurTable).(CurRow).(CurCol).shipId;
			    refBaseShip = GetRealShip(iShip);
				iChar = GameInterface.(CurTable).(CurRow).(CurCol).charId;
				refChar = GetCharacter(iChar);
			    sPicture = "interfaces\le\portraits\512\face_" + refChar.FaceId + ".tga"
				sHeader = XI_ConvertString(refBaseShip.BaseName);
				sText = XI_Convertstring("Captain") + " - " + GetFullName(refChar);
				sText1 = sText + "\n\n" + GetConvertStr(refBaseShip.BaseName, "ShipsDescribe.txt");
				sText3 = XI_ConvertString("ShipPower") + ": " + makeint(GetRealShipPower(refChar)) + " / " + makeint(GetBaseShipPower(sti(refBaseShip.BaseType)));
			}
		break; 
		// sith --->
		case "WEIGHT":
		    sHeader = XI_ConvertString("Weight");
			sText1 = GetRPGText("Weight");
		break;
		case "MONEY":
		    sHeader = XI_ConvertString("Money");
			sText1 = GetRPGText("Money");
		break;		
		case "RANK":
		    sHeader = XI_ConvertString("Rank");
			sText1 = GetRPGText("Rank");
		break;
		//<--- sith
		case "BAR_POWER_INFO":
		    sHeader = XI_ConvertString("SquadPower");
			sText1 = "Описание формулы";
		break;
		case "BAR_THREAT_INFO":
		    sHeader = XI_ConvertString("Threat");
			sText1 = "Описание формулы";
		break;
	}
	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,255,255,255), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 160, 160);
}

void HideInfo()
{
	CloseTooltip();
	SetCurrentNode("OK_BUTTON");
}

void FlagsProcess()
{
	// boal 04.04.2004 -->
	bool bTmpBool = true;
	int i, cn;
	ref chref;
	
	if (CheckAttribute(pchar, "DisableChangeFlagMode")) return; // нефиг менять файл за 3 секунды сразу
	
	if (!bBettaTestMode)
	{
    	// if(LAi_group_IsActivePlayerAlarm()) bTmpBool = false;
    	// if(!LAi_IsCharacterControl(GetMainCharacter())) bTmpBool = false;
		// if(GetCharacterShipType(pchar) == SHIP_NOTUSED) bTmpBool = false;
    	if (bLandInterfaceStart)  bTmpBool = false; // на суше нельзя в принципе
    	if (bSeaActive && !CheckEnemyCompanionDistance2GoAway(false)) bTmpBool = false; // компаньон под ударом
        // проверка класса кораблей в эскадре -->
        /*for (i=0; i<4; i++)
    	{
    		cn = GetCompanionIndex(GetMainCharacter(), i);
    		if ( cn>=0 )
    		{
    			chref = GetCharacter(cn);
                if (GetCharacterShipClass(chref) <= 2) bTmpBool = false;
    		}
    	}  */
        // проверка класса кораблей в эскадре <--
	}
	if (bDisableMapEnter || !bTmpBool)
	{
        if (!bBettaTestMode)
        {
            PlaySound("interface\knock.wav");
            return;
        }
	}
	// смена флага
	Sea_ClearCheckFlag(); // сбросить всем в море проверку смотрения на флаг.
	pchar.DisableChangeFlagMode = true; //закрываем Флаг
	DoQuestFunctionDelay("FreeChangeFlagMode", 5.0); // ролик + запас
	
	switch (curNationIdx)
	{
    	case ENGLAND:	EnglandProcess();	break;
    	case FRANCE:	FranceProcess();	break;
    	case SPAIN:		SpainProcess();		break;
    	case PIRATE:	PirateProcess();	break;
    	case HOLLAND:	HollandProcess();	break;
	}
}

void SetNewNation(int add)
{
    ref   mchar = GetMainCharacter();
    bool  ok, ok2, ok3;
    
    curNationIdx = curNationIdx + add;
    if (curNationIdx < 0) curNationIdx = 4;
    if (curNationIdx > 4) curNationIdx = 0;
    SetNewGroupPicture("FLAGPIC", "NATIONS", GetNationNameByType(curNationIdx));
    
    if (IsCharacterPerkOn(mchar,"FlagPir")  ||
	    IsCharacterPerkOn(mchar,"FlagEng")  ||
		IsCharacterPerkOn(mchar,"FlagFra")  ||
		IsCharacterPerkOn(mchar,"FlagSpa")  ||
		IsCharacterPerkOn(mchar,"FlagHol"))
    {
		SetNodeUsing("CHANGEFLAG",true);
		if (!bBettaTestMode)
		{
			ok3 = bSeaActive && !CheckEnemyCompanionDistance2GoAway(false);
			if (bDisableMapEnter || bLandInterfaceStart || ok3) SetSelectable("CHANGEFLAG",false);
		}
        ok  = !IsCharacterPerkOn(mchar,"Flag" + NationShortName(curNationIdx)) && (sti(mchar.nation) != curNationIdx);
        ok2 =  true;
        if (isMainCharacterPatented())
        {
            ok2 = (sti(Items[sti(mchar.EquipedPatentId)].Nation) != curNationIdx);
        }
        if (ok && ok2)
        {
            SetNewNation(add);
        }
        if (sti(mchar.nation) == curNationIdx)
        {
			SetNodeUsing("CHANGEFLAG",false);
        }
    }
    else
    {
        SetNodeUsing("CHANGEFLAG",false);
	    SetNodeUsing("RIGHTCHANGE_NATION",false);
	    SetNodeUsing("LEFTCHANGE_NATION",false);
    }
}
void PirateProcess()
{
    //DoQuestCheckDelay("pir_flag_rise", 1.0);
    PChar.GenQuest.VideoAVI        = "Pirate";
    PChar.GenQuest.VideoAfterQuest = "pir_flag_rise";

    DoQuestCheckDelay("PostVideo_Start", 0.2);
	ProcessExitCancel();
}

void EnglandProcess()
{
    //DoQuestCheckDelay("eng_flag_rise", 1.0);
    PChar.GenQuest.VideoAVI        = "England";
    PChar.GenQuest.VideoAfterQuest = "eng_flag_rise";

    DoQuestCheckDelay("PostVideo_Start", 0.2);
    ProcessExitCancel();
}

void FranceProcess()
{
    PChar.GenQuest.VideoAVI        = "France";
    PChar.GenQuest.VideoAfterQuest = "fra_flag_rise";

    DoQuestCheckDelay("PostVideo_Start", 0.2);
	ProcessExitCancel();
}

void SpainProcess()
{
    PChar.GenQuest.VideoAVI        = "Spain";
    PChar.GenQuest.VideoAfterQuest = "spa_flag_rise";

    DoQuestCheckDelay("PostVideo_Start", 0.2);
    ProcessExitCancel();
}

void HollandProcess()
{
    PChar.GenQuest.VideoAVI        = "Holland";
    PChar.GenQuest.VideoAfterQuest = "hol_flag_rise";

    DoQuestCheckDelay("PostVideo_Start", 0.2);
	ProcessExitCancel();
}

void SetThreatLevel()
{
	string groupName = "message_icons";
	string pictureName = "threat0";
	pictureName = "threat" + wdmGetNationThreat(FRANCE);
	SendMessage(&GameInterface,"lslss",MSG_INTERFACE_MSG_TO_NODE,"FRA_THR", 6, groupName, pictureName );
	pictureName = "threat" + wdmGetNationThreat(ENGLAND);
	SendMessage(&GameInterface,"lslss",MSG_INTERFACE_MSG_TO_NODE,"ENG_THR", 6, groupName, pictureName );
	pictureName = "threat" + wdmGetNationThreat(SPAIN);
	SendMessage(&GameInterface,"lslss",MSG_INTERFACE_MSG_TO_NODE,"SPA_THR", 6, groupName, pictureName );
	pictureName = "threat" + wdmGetNationThreat(HOLLAND);
	SendMessage(&GameInterface,"lslss",MSG_INTERFACE_MSG_TO_NODE,"HOL_THR", 6, groupName, pictureName );
	pictureName = "threat" + wdmGetNationThreat(PIRATE);
	SendMessage(&GameInterface,"lslss",MSG_INTERFACE_MSG_TO_NODE,"PIR_THR", 6, groupName, pictureName );
}

void SetNationWars()
{
	int nation1, nation2;
	string sTable, sCol;
	int iCol;
	int x1, y1, x2, y2;
	
	for(nation1 = ENGLAND; nation1 <= HOLLAND; nation1++)
	{
		sTable = Nations[nation1].name + "_WAR";
		iCol = 0;
		for(nation2 = ENGLAND; nation2 <= HOLLAND; nation2++)
		{
			if(nation1 == nation2)
				continue;
			if(GetNationRelation(nation1, nation2) == RELATION_ENEMY)
			{
				iCol++;
				sCol = "td" + iCol;
				GameInterface.(sTable).tr1.(sCol).icon.group = "message_icons";
				GameInterface.(sTable).tr1.(sCol).icon.image = Nations[nation2].name;
				GameInterface.(sTable).tr1.(sCol).icon.width = 40;
				GameInterface.(sTable).tr1.(sCol).icon.height = 40;
				GameInterface.(sTable).tr1.(sCol).icon.offset = "0, 0";
			}
		}
		GetNodePosition(sTable, &x1, &y1, &x2, &y2);
		x1 += (3 - iCol) * 20;
		x2 = x1 + 40 * iCol;
		SetNodePosition(sTable, x1, y1, x2, y2);
		Table_UpdateWindow(sTable);
	}
}

void SetNationThreatLevel()
{
	GameInterface.StatusLine.BAR_THREAT.Max   = 100.0;
	GameInterface.StatusLine.BAR_THREAT.Min   = 0.0;
	float fBarLevel[6];
	fBarLevel[0] = 0.0;
	fBarLevel[1] = 8.0;
	fBarLevel[2] = 20.0;
	fBarLevel[3] = 38.0;
	fBarLevel[4] = 64.0;
	fBarLevel[5] = 100.0;
	float fRealLevel[6];
	fRealLevel[0] = 0.0;
	fRealLevel[1] = 10.0;
	fRealLevel[2] = 15.0;
	fRealLevel[3] = 20.0;
	fRealLevel[4] = 30.0;
	fRealLevel[5] = 50.0;
	float fHunterScore[4];
	fHunterScore[ENGLAND] = stf(pchar.reputation.enghunter);
	fHunterScore[FRANCE]  = stf(pchar.reputation.frahunter);
	fHunterScore[SPAIN]   = stf(pchar.reputation.spahunter);
	fHunterScore[HOLLAND] = stf(pchar.reputation.holhunter);
	
	float fNationThreat[4];
	float fMaxThreat = 0;
	int i, j;
	for(i = ENGLAND; i <= HOLLAND; i++)
	{
		for(int iLevel = 1; iLevel <= 5; iLevel++)
		{
			if(fHunterScore[i] > fRealLevel[iLevel - 1] && fHunterScore[i] <= fRealLevel[iLevel])
			{
				fNationThreat[i] = Bring2Range(fBarLevel[iLevel - 1], fBarLevel[iLevel], fRealLevel[iLevel - 1], fRealLevel[iLevel], fHunterScore[i]);
				break;
			}
		}
		if(fHunterScore[i] > fRealLevel[5])
			fNationThreat[i] = 100.0;

		if(fNationThreat[i] > fMaxThreat)
			fMaxThreat = fNationThreat[i];
	}
    // PIRATE
	int iPiratesThreatLevel = wdmGetNationThreat(PIRATE);
	float fPiratesThreat = fBarLevel[iPiratesThreatLevel];
    if(fPiratesThreat > fMaxThreat)
		fMaxThreat = fPiratesThreat;

	GameInterface.StatusLine.BAR_THREAT.Value = fMaxThreat;
	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "BAR_THREAT", 0);
	
	int x1, y1, x2, y2;
	GetNodePosition("BAR_THREAT", &x1, &y1, &x2, &y2);
	int x = x1 + makeint((x2 - x1) * stf(GameInterface.StatusLine.BAR_THREAT.Value) / stf(GameInterface.StatusLine.BAR_THREAT.Max));
	int y = y1;
	GetNodePosition("POINTER_THREAT", &x1, &y1, &x2, &y2);
	int width = x2 - x1;
	int height = y2 - y1;
	x1 = x - width/2;
	x2 = x1 + width;
	y1 = y - height;
	y2 = y;
	SetNodePosition("POINTER_THREAT", x1, y1, x2, y2);
	
	int iCurLevel;
	int iNationLevel[4];
	string sNode;
	for(i = ENGLAND; i <= HOLLAND; i++)
	{
		iCurLevel = 5;
		for(j = 0; j <= 4; j++)
		{
			if(fNationThreat[i] < fBarLevel[j + 1])
			{
				iCurLevel = j;
				break;
			}
		}
		iNationLevel[i] = iCurLevel;
		sNode = Nations[i].name + "_THREAT_FLAG";
		if(iCurLevel == 0)
			SetNodeUsing(sNode, false);
		else
			SetNodeUsing(sNode, true);
	}
	
	int n;
	int minX, maxX, left, right;
	int xt1, yt1, xt2, yt2;
	GetNodePosition("BAR_THREAT", &minX, &y1, &maxX, &y2);
	y1 += 75;
	for(iCurLevel = 0; iCurLevel <= 5; iCurLevel++)
	{
		n = 0;
		for(i = ENGLAND; i <= HOLLAND; i++)
		{
			if(iNationLevel[i] == iCurLevel)
				n++;	// n - количество наций на текущем уровне
		}
		if(iCurLevel != 0)
		{
			if(iCurLevel == 1)
				left = minX;
			else
				left = minX + makeint((maxX - minX) * fBarLevel[iCurLevel - 1] * 0.01);
			right = minX + makeint((maxX - minX) * fBarLevel[iCurLevel] * 0.01);
		}
		if(n > 0)
		{
			j = 0;
			for(i = ENGLAND; i <= HOLLAND; i++)
			{
				if(iNationLevel[i] != iCurLevel)
					continue;
				j++;
				sNode = Nations[i].name + "_THREAT_FLAG";
				x = left + makeint((right - left) * j / (n+1));
				GetNodePosition(sNode, &xt1, &yt1, &xt2, &yt2);
				x1 = x - makeint((xt2 - xt1)/2.0);
				x2 = x1 + (xt2 - xt1);
				y2 = y1 + (yt2 - yt1);
				SetNodePosition(sNode, x1, y1, x2, y2);
			}
		}
	}
}

void SetPiratesThreatLevel()
{
	int iThreat = wdmGetNationThreat(PIRATE);
	int x;
	switch(iThreat)
	{
		case 1:		x = 4;		break;
		case 2:		x = 14;		break;
		case 3:		x = 29;		break;
		case 4:		x = 51;		break;
		case 5:		x = 82;		break;
	}
	
	int x1, y1, x2, y2;
	GetNodePosition("BAR_THREAT", &x1, &y1, &x2, &y2);
	int width = x2 - x1;
	y1 += 140;
	int xt1, yt1, xt2, yt2;
	GetNodePosition("PIRATESRISKSPIC", &xt1, &yt1, &xt2, &yt2);
	y2 = y1 + (yt2 - yt1);
	x1 += makeint(x * width / 100.0) - makeint((xt2 - xt1)/2.0);
	x2 = x1 + (xt2 - xt1);
	SetNodePosition("PIRATESRISKSPIC", x1, y1, x2, y2);
}

void SetSquadronTable()
{
	ref rShip, rChar;
	int iChar, iShipType, n, iMight;
	string sShipPic, sClass, sCol, sIcon;
	float fMight, fSquadronMight;
	fSquadronMight = 0.0;
	n = 0;
	for(int i = 0; i < COMPANION_MAX; i++)
	{
		iChar = GetCompanionIndex(pchar, i);
		if(iChar != -1)
		{
			rChar = GetCharacter(iChar);
			iShipType = sti(rChar.ship.type);
			if(iShipType != SHIP_NOTUSED)
			{
				n++;	// количество кораблей
				rShip  = GetRealShip(iShipType);
				fMight = GetRealShipPower(rChar);
				fSquadronMight += fMight;
				sShipPic = rShip.BaseName + rShip.ship.upgrades.hull;
				sClass = rShip.class;
				sCol = "td" + n;
				GameInterface.TABLE_SQUADRON.tr1.(sCol).charId = iChar;
				GameInterface.TABLE_SQUADRON.tr1.(sCol).shipId = iShipType;
				GameInterface.TABLE_SQUADRON.tr1.(sCol).icon1.texture = "interfaces\le\ships\" + sShipPic + ".tga";
				GameInterface.TABLE_SQUADRON.tr1.(sCol).icon1.uv = "0,0,1,1";
				GameInterface.TABLE_SQUADRON.tr1.(sCol).icon1.width = 80;
				GameInterface.TABLE_SQUADRON.tr1.(sCol).icon1.height = 80;
				GameInterface.TABLE_SQUADRON.tr1.(sCol).icon1.offset = "15, 0";
				GameInterface.TABLE_SQUADRON.tr1.(sCol).might = fMight;	// записываем мощь

				if(fMight < 200/5)
					iMight = 1;
				else if(fMight < 325/5)
					iMight = 2;
				else if(fMight < 475/5)
					iMight = 3;
				else if(fMight < 675/5)
					iMight = 4;
				else if(fMight < 925/5)
					iMight = 5;
				else
					iMight = 6;

				for(int j = 2; j <= iMight + 1; j++)
				{
					sIcon = "icon" + j;
					GameInterface.TABLE_SQUADRON.tr1.(sCol).(sIcon).group = "EFFECTS_ARROWS";
					GameInterface.TABLE_SQUADRON.tr1.(sCol).(sIcon).image = "up";
					GameInterface.TABLE_SQUADRON.tr1.(sCol).(sIcon).width = 15;
					GameInterface.TABLE_SQUADRON.tr1.(sCol).(sIcon).height = 12;
					GameInterface.TABLE_SQUADRON.tr1.(sCol).(sIcon).offset = "0, " + (64 - (j-2) * 12);
				}

				GameInterface.TABLE_SQUADRON.tr1.(sCol).str = sClass;
				GameInterface.TABLE_SQUADRON.tr1.(sCol).scale = 0.9;
				GameInterface.TABLE_SQUADRON.tr1.(sCol).textoffset = "48, 22";
			}
		}
	}

	int x1, x2, y1, y2;
	GetNodePosition("TABLE_SQUADRON", &x1, &y1, &x2, &y2);
	x1 += (5 - n) * 60;
	x2 = x1 + 120 * n;
	SetNodePosition("TABLE_SQUADRON", x1, y1, x2, y2);

	Table_UpdateWindow("TABLE_SQUADRON");

	GameInterface.StatusLine.BAR_POWER.Max   = 925;
	GameInterface.StatusLine.BAR_POWER.Min   = 0;

    // Механика мощи
    PChar.Squadron.RawPower = fSquadronMight; // Кэш
    if(CheckCharacterPerk(PChar, "SeaDogProfessional")) fSquadronMight *= 1.3;
    if(IsEquipCharacterByArtefact(PChar, "talisman15")) fSquadronMight *= 1.15;
    PChar.Squadron.ModPower = fSquadronMight; // Кэш
	
	float fBarLevel[6];
	fBarLevel[0] = 0.0;
	fBarLevel[1] = 0.08;
	fBarLevel[2] = 0.2;
	fBarLevel[3] = 0.38;
	fBarLevel[4] = 0.64;
	fBarLevel[5] = 1.0;
	float fRealLevel[6];
	fRealLevel[0] = 0.0;
	fRealLevel[1] = 200.0;
	fRealLevel[2] = 325.0;
	fRealLevel[3] = 475.0;
	fRealLevel[4] = 675.0;
	fRealLevel[5] = 925.0;
	
	float fBarPower = fSquadronMight;
	for(int iLevel = 1; iLevel <= 5; iLevel++)
	{
		if(fSquadronMight > fRealLevel[iLevel - 1] && fSquadronMight <= fRealLevel[iLevel])
		{
			fBarPower = Bring2Range(fBarLevel[iLevel - 1] * 925, fBarLevel[iLevel] * 925, fRealLevel[iLevel - 1], fRealLevel[iLevel], fSquadronMight);
			break;
		}
	}
	
    GameInterface.StatusLine.BAR_POWER.Value = fBarPower;

	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "BAR_POWER", 0);

	GetNodePosition("BAR_POWER", &x1, &y1, &x2, &y2);
	int x = x1 + makeint((x2 - x1) * fBarPower / stf(GameInterface.StatusLine.BAR_POWER.Max));
	int y = y1;
	
	GetNodePosition("POINTER_POWER", &x1, &y1, &x2, &y2);
	int width = x2 - x1;
	int height = y2 - y1;
	x1 = x - width/2;
	x2 = x1 + width;
	y1 = y - height;
	y2 = y;
	SetNodePosition("POINTER_POWER", x1, y1, x2, y2);
}

void CalculateHunter()
{
    ref mc = GetMainCharacter();
    SetFormatedText("Fra_rep", GetNationReputation(pchar, FRANCE));
    SetFormatedText("Eng_rep", GetNationReputation(pchar, ENGLAND));
    SetFormatedText("Spa_rep", GetNationReputation(pchar, SPAIN));
    SetFormatedText("Hol_rep", GetNationReputation(pchar, HOLLAND));
    SetFormatedText("Ind_rep", GetFactionReputationName(sti(pchar.questTemp.Indian.relation))); // индейцы
    SetFormatedText("Smg_rep", GetFactionReputationName(sti(pchar.questTemp.Contraband.relation))); // контрабандисты
	SendMessage( &GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"Fra_rep", 5 );
	SendMessage( &GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"Eng_rep", 5 );
	SendMessage( &GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"Spa_rep", 5 );
	SendMessage( &GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"Hol_rep", 5 );
	SendMessage( &GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"Ind_rep", 5 );
	SendMessage( &GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"Smg_rep", 5 );

	GameInterface.StatusLine.BAR_FRA.Max   = 100;
	GameInterface.StatusLine.BAR_FRA.Min   = -100;
	GameInterface.StatusLine.BAR_FRA.Value = -sti(pchar.reputation.frahunter);
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE, "BAR_FRA", 0);
	
	GameInterface.StatusLine.BAR_ENG.Max   = 100;
	GameInterface.StatusLine.BAR_ENG.Min   = -100;
	GameInterface.StatusLine.BAR_ENG.Value = -sti(pchar.reputation.enghunter);
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE, "BAR_ENG", 0);

	GameInterface.StatusLine.BAR_SPA.Max   = 100;
	GameInterface.StatusLine.BAR_SPA.Min   = -100;
	GameInterface.StatusLine.BAR_SPA.Value = -sti(pchar.reputation.spahunter);
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE, "BAR_SPA", 0);

	GameInterface.StatusLine.BAR_HOL.Max   = 100;
	GameInterface.StatusLine.BAR_HOL.Min   = -100;
	GameInterface.StatusLine.BAR_HOL.Value = -sti(pchar.reputation.holhunter);
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE, "BAR_HOL", 0);
	
	GameInterface.StatusLine.BAR_IND.Max   = 100;
	GameInterface.StatusLine.BAR_IND.Min   = 0;
	GameInterface.StatusLine.BAR_IND.Value = sti(pchar.questTemp.Indian.relation);
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE, "BAR_IND", 0);

	GameInterface.StatusLine.BAR_SMG.Max   = 100;
	GameInterface.StatusLine.BAR_SMG.Min   = 0;
	GameInterface.StatusLine.BAR_SMG.Value = sti(pchar.questTemp.Contraband.relation);
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE, "BAR_SMG", 0);
}
