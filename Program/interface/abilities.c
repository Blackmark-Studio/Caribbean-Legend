// Sith/mitrokosta меню навыки
#event_handler("Control Activation","ProcessInterfaceControls");// гуляем по меню кнопками Q и E
#include "interface\character_all.h"
int nCurScrollOfficerNum;
string selectedPerk;
int currentInfoMode = 0;
int currentScrollTab = 1;
bool bShowTabOfficers = true;

void InitInterface(string iniName)
{
	xi_refCharacter = pchar;
	InterfaceStack.SelectMenu_node = "LaunchAbilities"; // запоминаем, что звать по Ф2
	GameInterface.title = "titleCharacter";
	
	if (CheckAttribute(&InterfaceStates, "nCurScrollTab") && sti(InterfaceStates.nCurScrollTab) == 2)
	{
		bShowTabOfficers = false;
		currentScrollTab = 2;
	}
	FillCharactersScrollEx(bShowTabOfficers);
	FillPassengerScroll();
	if (CheckAttribute(&InterfaceStates, "CurCharacter")) 
	{
		GameInterface.CHARACTERS_SCROLL.current = InterfaceStates.CurCharacter;
		ProcessFrame();
	}
        
	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	SetEventHandler("InterfaceBreak","ProcessExitCancel",0);
	SetEventHandler("exitCancel","ProcessExitCancel",0);
    SetEventHandler("ievnt_command","ProcessCommandExecute",0);
    SetEventHandler("frame","ProcessFrame",1);
    SetEventHandler("ShowInfoWindow","ShowInfoWindow",0);
	SetEventHandler("MouseRClickUp","HideInfoWindow",0);
	SetEventHandler("TableSelectChange", "CS_TableSelectChange", 0);
	SetEventHandler("ExitOfficerMenu","ExitOfficerMenu",0);
	SetEventHandler("OfficerChange","OfficerChange",0);
	SetEventHandler("acceptaddofficer","AcceptAddOfficer",0);
	SetEventHandler("ExitRemoveOfficerMenu","ExitRemoveOfficerMenu",0);
	SetEventHandler("AcceptRemoveOfficer","AcceptRemoveOfficer",0);
	SetEventHandler("ExitPerkMenu","ExitPerkMenu",0);
	SetEventHandler("AcceptPerk","AcceptPerk",0);
	SetEventHandler("eScrollTabControlPress","procScrollTabChange",0);
    XI_RegistryExitKey("IExit_F2");
	
    SetVariable();
    SetCurrentNode("CHARACTERS_SCROLL");
    SetNodeUsing("CHARACTERS_SCROLL",true);
	if (MOD_SKILL_ENEMY_RATE > 9)// недоступно для ОК
	{
		SetNodeUsing("PERK_InstantRepair",false);
		SetNodeUsing("CONNECTIONS2",false);
	}
	if (CheckAttribute(&InterfaceStates, "nCurScrollTab") && CheckAttribute(&InterfaceStates, "CurCharacter")) 
		SetControlsScrollTabMode(currentScrollTab);
	else SetControlsScrollTabMode(1);
    HideSkillChanger();
	CreatePerksPictures();
	SetAlertMarks(xi_refCharacter);
}

// гуляем по меню кнопками Q и E
void ProcessInterfaceControls() 
{
	string controlName = GetEventData();
	if (controlName == "InterfaceGoLeft") {
        IDoExit(RC_INTERFACE_MAPVIEW);
    }
	if (controlName == "InterfaceGoRight") {
        IDoExit(RC_INTERFACE_NATIONRELATION);
    }
	if (controlName == "InterfaceInfoSwitch") {
		currentInfoMode = (currentInfoMode + 1) % 2;
		SetPerksNamesMode(currentInfoMode + 1);
    }
}

// показываем/скрываем названия перков
void SetPerksNamesMode(int nMode)
{
	switch (nMode)
	{
	    case 1: HidePerksNames(); break;// названия перков скрыты
	    case 2: CreatePerksNames(); break;// названия перков показаны
	}
}

void ProcessExitCancel()
{
	IDoExit(RC_INTERFACE_ANY_EXIT);
}

void IDoExit(int exitCode)
{
	int i, iOfficer;
	
	if(!GetAchievement("ach_CL_132"))
	{
		iOfficer = -1;
		int totalMush = 0;
		for(i = 1; i < 4; i++)
		{		
			iOfficer = GetOfficersIndex(pchar, i); 
			if(iOfficer != -1)
			{
				if(CheckAttribute(&characters[iOfficer], "isMushketer")) totalMush++;
			}
		}
		if(totalMush > 2) Achievment_Set("ach_CL_132");
	}
	/* if(bGlobalTutor)
	{
		for(i = 1; i < 4; i++)
		{		
			iOfficer = GetOfficersIndex(pchar, i); 
			if(iOfficer != -1)
			{
				DoQuestFunctionDelay("SharlieTutorial_AlonsoHired", 1.0);
			}
		}
	} */
	DelEventHandler("InterfaceBreak","ProcessExitCancel");
	DelEventHandler("exitCancel","ProcessExitCancel");
    DelEventHandler("ievnt_command","ProcessCommandExecute");
    DelEventHandler("frame","ProcessFrame");
    DelEventHandler("ShowInfoWindow","ShowInfoWindow");
	DelEventHandler("MouseRClickUp","HideInfoWindow");
	DelEventHandler("TableSelectChange", "CS_TableSelectChange");
	DelEventHandler("ExitOfficerMenu","ExitOfficerMenu");
	DelEventHandler("OfficerChange","OfficerChange");
	DelEventHandler("acceptaddofficer","AcceptAddOfficer");
	DelEventHandler("ExitRemoveOfficerMenu","ExitRemoveOfficerMenu");
	DelEventHandler("AcceptRemoveOfficer","AcceptRemoveOfficer");
	DelEventHandler("ExitPerkMenu","ExitPerkMenu");
	DelEventHandler("AcceptPerk","AcceptPerk");
	DelEventHandler("eScrollTabControlPress","procScrollTabChange");
	
	interfaceResultCommand = exitCode;
	if( CheckAttribute(&InterfaceStates,"ReloadMenuExit"))
	{
        DeleteAttribute(&InterfaceStates,"ReloadMenuExit");
		EndCancelInterface(false);
	}
	else
	{
		DeleteAttribute(&InterfaceStates, "CurCharacter");
		DeleteAttribute(&InterfaceStates, "nCurScrollTab");
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
		/////////////////////// menu ///////////////
		case "I_INVENTORY_2":
			if(comName=="click")
			{
			    // nodName = "I_INVENTORY";
				string attributeName = "pic" + (nCurScrollNum+1);
				if(GameInterface.CHARACTERS_SCROLL.(attributeName).character != "0")
				{
					InterfaceStates.CurCharacter = GameInterface.CHARACTERS_SCROLL.current;
				}
				else DeleteAttribute(&InterfaceStates, "CurCharacter");
				InterfaceStates.ReloadMenuExit = true;
				IDoExit(RC_INTERFACE_INVENTORY);
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
	}
	if (nodName == "I_INVENTORY" || nodName == "I_SHIP" || nodName == "I_QUESTBOOK" ||
		nodName == "I_ATLAS" || nodName == "I_ABILITIES" || nodName == "I_NATIONS")
	{
		if(comName=="click")
		{
            InterfaceStates.ReloadMenuExit = true;
			IDoExit(RC_INTERFACE_ANY_EXIT);
			PostEvent("LaunchIAfterFrame",1,"sl", nodName, 2);
			return;
		}
	}
	if (findsubstr(&nodName, "PERK_", 0) == 0 && comName == "click") 
	{
        SetCurrentNode("PERKWINDOW_TEXT");
		HidePerkSelect();
		ChoosePerk(strcut(&nodName, 5, strlen(&nodName) - 1));
    }
}

void SetVariable()
{
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

	// порог доступных навыков бары
	if (!CheckAttribute(xi_refCharacter,"perks.FreePoints_self_exp"))
	{
	   xi_refCharacter.perks.FreePoints_self_exp = 0;
	}
	if (!CheckAttribute(xi_refCharacter,"perks.FreePoints_ship_exp"))
	{
	   xi_refCharacter.perks.FreePoints_ship_exp = 0;
	}
	SetFormatedText("Personal_progress", sti(xi_refCharacter.perks.FreePoints_self_exp)+ "/" + GetFreePoints_SelfRate(xi_refCharacter));
	GameInterface.StatusLine.PERSONAL_PROGRESSBAR.Max   = GetFreePoints_SelfRate(xi_refCharacter);
	GameInterface.StatusLine.PERSONAL_PROGRESSBAR.Min   = 0;
	GameInterface.StatusLine.PERSONAL_PROGRESSBAR.Value = sti(xi_refCharacter.perks.FreePoints_self_exp);	
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"PERSONAL_PROGRESSBAR",0);
	SetFormatedText("Ship_progress", sti(xi_refCharacter.perks.FreePoints_ship_exp)+ "/" + GetFreePoints_ShipRate(xi_refCharacter));
	GameInterface.StatusLine.SHIP_PROGRESSBAR.Max   = GetFreePoints_ShipRate(xi_refCharacter);
	GameInterface.StatusLine.SHIP_PROGRESSBAR.Min   = 0;
	GameInterface.StatusLine.SHIP_PROGRESSBAR.Value = sti(xi_refCharacter.perks.FreePoints_ship_exp);	
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"SHIP_PROGRESSBAR",0);

	FillSkillTables();

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
	RefreshPerksPictures();
	RefreshPerksNames();
	ExitPerkMenu();
}

void ProcessFrame()
{
	if (sti(GameInterface.CHARACTERS_SCROLL.current)!=nCurScrollNum && GetCurrentNode() == "CHARACTERS_SCROLL")
	{
		nCurScrollNum = sti(GameInterface.CHARACTERS_SCROLL.current);
		SetButtonsState();
		return;
	}
	if (sti(GameInterface.PASSENGERSLIST.current)!= nCurScrollOfficerNum && GetCurrentNode() == "PASSENGERSLIST")
	{
		nCurScrollOfficerNum = sti(GameInterface.PASSENGERSLIST.current);
		SetOfficersSkills();
		return;
	}
}

void SetButtonsState()
{
	string attributeName = "pic" + (nCurScrollNum+1);
	
	HideSkillChanger();
	if(GameInterface.CHARACTERS_SCROLL.(attributeName).character != "0")
	{
		int iCharacter = sti(GameInterface.CHARACTERS_SCROLL.(attributeName).character);
		//WriteNewData();
		xi_refCharacter = &characters[iCharacter];
		//ReMappingSkills();
		//SetSkills();
		SetVariable();
	}
	else
	{
        xi_refCharacter = pchar;
        SetVariable();
	}
}

void ShowInfoWindow()
{
	string sCurrentNode = GetCurrentNode();
	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;
	int iItem;
	int	picW = 128;
	int	picH = 128;

	sPicture = "-1";
	string sAttributeName;
	int nChooseNum = -1;
	switch (sCurrentNode)
	{
		case "CHARACTERS_SCROLL":
			picW = 256;
			picH = 256;
			nChooseNum = SendMessage( &GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"CHARACTERS_SCROLL", 2 );
			string attributeName = "pic" + (nChooseNum+1);
			int iCharacter = sti(GameInterface.CHARACTERS_SCROLL.(attributeName).character);
            sHeader = XI_ConvertString("passengership");
			sText1 = "";
			sText2 = "";

			if(currentScrollTab == 1)
			{
				switch(nChooseNum)
				{
					case 0:
						sHeader = GetCharacterFullName(pchar.id);
						sText1 = "";
						sText2 = XI_ConvertString("It's you");
						sText3 = "";
					break;

					case 1:
						sHeader = XI_ConvertString("navigator");
						sText1 = XI_ConvertString("Navigator_Descr");
						sText2 = XI_ConvertString("Navigator_Up");
					break;

					case 2:
						sHeader = XI_ConvertString("boatswain");
						sText1 = XI_ConvertString("Boatswain_Descr");
						sText2 = XI_ConvertString("Boatswain_Up");
					break;

					case 3:
						sHeader = XI_ConvertString("cannoner");
						sText1 = XI_ConvertString("Cannoner_Descr");
						sText2 = XI_ConvertString("Cannoner_Up");
					break;

					case 4:
						sHeader = XI_ConvertString("doctor");
						sText1 = XI_ConvertString("Doctor_Descr");
						sText2 = XI_ConvertString("Doctor_Up");
					break;

					case 5:
						sHeader = XI_ConvertString("treasurer");
						sText1 = XI_ConvertString("Treasurer_Descr");
						sText2 = XI_ConvertString("Treasurer_Up");
					break;

					case 6:
						sHeader = XI_ConvertString("carpenter");
						sText1 = XI_ConvertString("Carpenter_Descr");
						sText2 = XI_ConvertString("Carpenter_Up");
					break;

					case 7:
						sHeader = XI_ConvertString("fighter");
						sText1 = XI_ConvertString("Officer_Descr");
						sText2 = XI_ConvertString("Officer_Up");
					break;

					case 8:
						sHeader = XI_ConvertString("fighter");
						sText1 = XI_ConvertString("Officer_Descr");
						sText2 = XI_ConvertString("Officer_Up");
					break;

					case 9:
						sHeader = XI_ConvertString("fighter");
						sText1 = XI_ConvertString("Officer_Descr");
						sText2 = XI_ConvertString("Officer_Up");
					break;
				}

				if(iCharacter != 0)
				{
					ref rchr = &Characters[iCharacter];
					iItem = GetMoneyForOfficerFull(rchr);
					if (iItem > 0)
					{
						sText2 = XI_ConvertString("HirePrice") + " " + FindRussianMoneyString(iItem) + " " + XI_ConvertString("per month");
					}
					if(FindFellowtravellers(pchar,rchr) != FELLOWTRAVEL_COMPANION)
					{
						sText3 = XI_ConvertString("AddRemoveOfficerScroll");
					}
					else
					{
						if(CheckAttribute(rchr, "quest.convoyquest.money"))
						{
							sText3 = "";//SelectEscortQuestInfo(rchr);
						}
						sText1 = GetCharacterFullName(Characters[iCharacter].id);
						sHeader = XI_ConvertString("companionship");
					}
					sPicture = "interfaces\le\portraits\512\face_" + rchr.FaceId + ".tga"
					if(CheckCharacterPerk(rchr, "ByWorker")) 
					{
						if(CheckCharacterPerk(rchr, "ByWorker2")) sText2 = sText2 + NewStr() + GetConvertStr("perkByWorker2Short", "AbilityDescribe.txt"));
						else sText2 = sText2 + NewStr() + GetConvertStr("perkByWorkerShort", "AbilityDescribe.txt"));
					}
				}
			}
			else
			{
				if(nChooseNum == 0)
				{
					sHeader = XI_ConvertString("captain");
					sText1 = "";
					sText2 = XI_ConvertString("It's you");
					sText3 = "";
				}
				if(iCharacter != 0)
				{
					ref rchar = &Characters[iCharacter];
					if(FindFellowtravellers(pchar,rchar) != FELLOWTRAVEL_COMPANION)
					{
						sText1 = GetCharacterFullName(Characters[iCharacter].id);
						if (CheckAttribute(&Characters[iCharacter], "prisoned") && Characters[iCharacter].prisoned == true)
						{
							sHeader = GetRPGText("Prisoner");
							sText2 = GetRPGText("Prisoner_desc");
						}
					}
					sPicture = "interfaces\le\portraits\512\face_" + rchar.FaceId + ".tga"
					if(CheckCharacterPerk(rchar, "ByWorker")) 
					{
						if(CheckCharacterPerk(rchar, "ByWorker2")) sText2 = sText2 + NewStr() + GetConvertStr("perkByWorker2Short", "AbilityDescribe.txt"));
						else sText2 = sText2 + NewStr() + GetConvertStr("perkByWorkerShort", "AbilityDescribe.txt"));
					}
				}
				else return;
			}
			if(sPicture == "-1")
			{
				sPicture = "interfaces\le\portraits\512\" + sHeader + ".tga";
			}
			if (bBettaTestMode)
			{
				if(iCharacter != 0) sText3 += "   " +  Characters[iCharacter].id;
			}
		break;
		
		case "TABLE_SPECIAL":
		    sHeader = XI_ConvertString(GameInterface.(CurTable).(CurRow).UserData.ID);
		    sText1  = GetRPGText(GameInterface.(CurTable).(CurRow).UserData.ID);
		break;
		
		case "TABLE_SKILL_1":
		    sHeader = XI_ConvertString(GameInterface.(CurTable).(CurRow).UserData.ID);
		    sText1  = GetRPGText(GameInterface.(CurTable).(CurRow).UserData.ID);
		break;
		case "TABLE_SKILL_2":
		    sHeader = XI_ConvertString(GameInterface.(CurTable).(CurRow).UserData.ID);
		    sText1  = GetRPGText(GameInterface.(CurTable).(CurRow).UserData.ID);
		break;
		case "PERSONAL_AVAILABLE":
		    sHeader = XI_ConvertString("Personal abilities");
			// порог опыта
			if (!CheckAttribute(xi_refCharacter,"perks.FreePoints_self_exp"))
            {
               xi_refCharacter.perks.FreePoints_self_exp = 0;
            }
            sText1	= sti(xi_refCharacter.perks.FreePoints_self_exp)+ "/" + GetFreePoints_SelfRate(xi_refCharacter);		
		    sText1  = GetRPGText("Personal_abilities") + NewStr() + XI_ConvertString("Progress") + ": " + sText1;
			sText2 	= GetRPGText("Attention_abilities");
		    sText3  = GetRPGText("Abilities_available");
		break;
		case "SHIP_AVAILABLE":
		    sHeader = XI_ConvertString("Ship abilities");
			// порог опыта
			if (!CheckAttribute(xi_refCharacter,"perks.FreePoints_ship_exp"))
            {
               xi_refCharacter.perks.FreePoints_ship_exp = 0;
            }
            sText1 = sti(xi_refCharacter.perks.FreePoints_ship_exp)+ "/" + GetFreePoints_ShipRate(xi_refCharacter);
		    sText1  = GetRPGText("Ship_abilities") + NewStr() + XI_ConvertString("Progress") + ": " + sText1;
			sText2 	= GetRPGText("Attention_abilities");
			sText3 	= GetRPGText("Abilities_available");
		break;
		case "PERKTABLE_NEED":
		    sHeader = GetRPGText("PERK_TABLE_NEED");
		    sText1  = GetRPGText("PERK_TABLE_NEED_desc");
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
	}
	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, picW, picH);
	HidePerkSelect();
}

void HideInfoWindow()
{
	CloseTooltip();
	SetCurrentNode("CHARACTERS_SCROLL");
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

    // Оптимизон для проверок пенальти в десятках вызовов ниже и внутри функций
    xi_refCharacter.TempSailing = GetSummonSkillFromNameSimple(xi_refCharacter, SKILL_SAILING);

    if (!CheckAttribute(xi_refCharacter,"perks.FreePoints_self") )
		xi_refCharacter.perks.FreePoints_self = 0;
    if (!CheckAttribute(xi_refCharacter,"perks.FreePoints_ship") )
		xi_refCharacter.perks.FreePoints_ship = 0;
	if(HaveAllPerks(xi_refCharacter, "self")) SetFormatedText("PERSONAL_AVAILABLE", XI_ConvertString("Personal abilities"));
	else SetFormatedText("PERSONAL_AVAILABLE", XI_ConvertString("Personal abilities") + "  -  " +xi_refCharacter.perks.FreePoints_self);
    if(HaveAllPerks(xi_refCharacter, "ship")) SetFormatedText("SHIP_AVAILABLE", XI_ConvertString("Ship abilities"));
	else SetFormatedText("SHIP_AVAILABLE", XI_ConvertString("Ship abilities") + "  -  " + xi_refCharacter.perks.FreePoints_ship);
	
	GameInterface.TABLE_SPECIAL.select = 0;
	GameInterface.TABLE_SPECIAL.hr.td1.str = "";

	for (i=0; i<=7; i++)
	{
	    row = "tr" + i;
	    skillName = GetSkillNameByTRIdx("SPECIALType", i);
	    
        GameInterface.TABLE_SPECIAL.(row).UserData.ID = skillName;
		GameInterface.TABLE_SPECIAL.(row).td1.fontidx = 0;
		GameInterface.TABLE_SPECIAL.(row).td1.textoffset = "3,-5";
		//GameInterface.TABLE_SPECIAL.(row).td1.align = "center";
		// GameInterface.TABLE_SPECIAL.(row).td1.scale = 0.88;
		GameInterface.TABLE_SPECIAL.(row).td2.textoffset = "0,0";
		GameInterface.TABLE_SPECIAL.(row).td2.scale = 1.25;
		GameInterface.TABLE_SPECIAL.(row).td3.align = "center";
		GameInterface.TABLE_SPECIAL.(row).td4.fontidx = 1;
		GameInterface.TABLE_SPECIAL.(row).td4.textoffset = "5,0";
		GameInterface.TABLE_SPECIAL.(row).td4.align = "left";
		GameInterface.TABLE_SPECIAL.(row).td4.scale = 0.8;

		GameInterface.TABLE_SPECIAL.(row).td1.str = XI_ConvertString(skillName + "T");
		GameInterface.TABLE_SPECIAL.(row).td2.str = XI_ConvertString(skillName);
		skillVal = GetSkillValue(xi_refCharacter, SPECIAL_TYPE, skillName);
		//GameInterface.TABLE_SPECIAL.(row).td4.str = skillVal; // старый метод
		GameInterface.TABLE_SPECIAL.(row).td4.str = GetCharacterSPECIAL(xi_refCharacter, skillName);
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
    	GameInterface.TABLE_SKILL_1.(row).td1.icon.offset = "-10, -2";
		GameInterface.TABLE_SKILL_1.(row).td2.align = "left";
		GameInterface.TABLE_SKILL_1.(row).td2.scale = 1.2;
		GameInterface.TABLE_SKILL_1.(row).td2.textoffset = "-2,0";
		GameInterface.TABLE_SKILL_1.(row).td5.fontidx = 0;
		// GameInterface.TABLE_SKILL_1.(row).td5.textoffset = "0,0";
		GameInterface.TABLE_SKILL_1.(row).td5.scale = 0.8;
		GameInterface.TABLE_SKILL_1.(row).td5.align = "left";
		// GameInterface.TABLE_SKILL_1.(row).td5.align = "center";
		GameInterface.TABLE_SKILL_1.(row).td3.scale = 1.2;
		// GameInterface.TABLE_SKILL_1.(row).td4.scale = 0.85;

		GameInterface.TABLE_SKILL_1.(row).td2.str = XI_ConvertString(skillName);
		skillVal = GetSkillValue(xi_refCharacter, SKILL_TYPE, skillName);
		//GameInterface.TABLE_SKILL_1.(row).td5.str = skillVal; // старый метод
		GameInterface.TABLE_SKILL_1.(row).td5.str = GetSummonSkillFromName(xi_refCharacter, skillName);
		// расчёт драйна
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
    	GameInterface.TABLE_SKILL_2.(row).td1.icon.offset = "-10, -2";
		GameInterface.TABLE_SKILL_2.(row).td2.align = "left";
		GameInterface.TABLE_SKILL_2.(row).td2.textoffset = "0,0";
		GameInterface.TABLE_SKILL_2.(row).td2.scale = 1.2;
		GameInterface.TABLE_SKILL_2.(row).td3.align = "left";
		GameInterface.TABLE_SKILL_2.(row).td3.scale = 1.2;
		GameInterface.TABLE_SKILL_2.(row).td5.fontidx = 0;
		GameInterface.TABLE_SKILL_2.(row).td5.scale = 0.8;
		GameInterface.TABLE_SKILL_2.(row).td5.align = "left";

		GameInterface.TABLE_SKILL_2.(row).td2.str = XI_ConvertString(skillName);
		skillVal = GetSkillValue(xi_refCharacter, SKILL_TYPE, skillName);
		//GameInterface.TABLE_SKILL_2.(row).td5.str = skillVal; // старый метод
		GameInterface.TABLE_SKILL_2.(row).td5.str = GetSummonSkillFromName(xi_refCharacter, skillName);
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

	// Прорисовка
	Table_UpdateWindow("TABLE_SPECIAL");
    Table_UpdateWindow("TABLE_SKILL_1");
    Table_UpdateWindow("TABLE_SKILL_2");

    // Убираем бэкап
    DeleteAttribute(xi_refCharacter, "TempSailing");
}

void CS_TableSelectChange()
{
	string sControl = GetEventData();
	iSelected = GetEventData();
    CurTable = sControl;
    CurRow   =  "tr" + (iSelected);
 	NullSelectTable("TABLE_SPECIAL");
    NullSelectTable("TABLE_SKILL_1");
    NullSelectTable("TABLE_SKILL_2");

    sti(xi_refCharacter.rank_exp)
	if (CurTable == "TABLE_SKILL_1" || CurTable == "TABLE_SKILL_2")
	{
        string skillName;
        int skillVal;
        skillName = GameInterface.(CurTable).(CurRow).UserData.ID;
        skillVal = GetSkillValue(xi_refCharacter, SKILL_TYPE, skillName);
	}
	// установим скилчанжер, если нужно
	HideSkillChanger();
    SetSkillArrows();
}

void SetSkillArrows()
{
   	bool ok;
	ok = CurTable == "TABLE_SKILL_1" || CurTable == "TABLE_SKILL_2";
	if (sti(xi_refCharacter.skill.freeskill) > 0 && ok)
	{
	    if (GetSkillValue(xi_refCharacter, SKILL_TYPE, GameInterface.(CurTable).(CurRow).UserData.ID) > 1)
        {
			if (CurTable == "TABLE_SKILL_1")
			{
				SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE,"B_SKILLDown",0, 594 ,445 + 35*(iSelected-1), 619, 445 + 36 + 35*(iSelected-1), 0);
			}
			else
			{
				SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE,"B_SKILLDown",0, 594 ,735 + 35*(iSelected-1), 619,735 + 36 + 35*(iSelected-1), 0);
			}
			SetNodeUsing("B_SKILLDown", true);
        }
        if (GetSkillValue(xi_refCharacter, SKILL_TYPE, GameInterface.(CurTable).(CurRow).UserData.ID) < SKILL_MAX)
        {
            if (CurTable == "TABLE_SKILL_1")
			{
				SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE,"B_SKILLUP",0, 643,445 + 35*(iSelected-1),668,445 + 36 + 35*(iSelected-1), 0);
			}
			else
			{
				SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE,"B_SKILLUP",0, 643,735 + 35*(iSelected-1),668,735 + 36 + 35*(iSelected-1), 0);
			}
            SetNodeUsing("B_SKILLUP",  true);
        }
	}
	
	ok = sti(xi_refCharacter.skill.freeskill) > 0 || sti(xi_refCharacter.skill.FreeSPECIAL) > 0;
	if (ok && CurTable == "TABLE_SPECIAL")
	{
	    if (GetSkillValue(xi_refCharacter, SPECIAL_TYPE, GameInterface.(CurTable).(CurRow).UserData.ID) > 1)
        {
			SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE,"B_SKILLDown",0, 594 ,155 + 35*(iSelected-1), 619, 155 + 36 + 35*(iSelected-1), 0);
			SetNodeUsing("B_SKILLDown", true);
        }
        if (GetSkillValue(xi_refCharacter, SPECIAL_TYPE, GameInterface.(CurTable).(CurRow).UserData.ID) < SPECIAL_MAX)
        {
			SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE,"B_SKILLUP",0, 643,155 + 35*(iSelected-1),668,155 + 36 + 35*(iSelected-1), 0);
            SetNodeUsing("B_SKILLUP",  true);
        }
	}
	if (CurTable != "PERKTABLE_NEED") ExitPerkMenu();
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
	        SetFormatedText("OFFICER_JOB", GetOfficerPosition(sCharacter));
	        SetSelectable("ACCEPT_ADD_OFFICER", true);
        }
        else
        {
            Table_Clear("TABLE_SMALLSKILL", false, true, true);
            Table_Clear("TABLE_SMALLOTHER", false, true, true);
            SetFormatedText("OFFICER_NAME", "");
	        SetFormatedText("OFFICER_JOB", "");
			SetSelectable("ACCEPT_ADD_OFFICER", false);
        }
	}
	else
    {
        Table_Clear("TABLE_SMALLSKILL", false, true, true);
        Table_Clear("TABLE_SMALLOTHER", false, true, true);
        SetFormatedText("OFFICER_NAME", "");
        SetFormatedText("OFFICER_JOB", "");
        SetSelectable("ACCEPT_ADD_OFFICER", false);
    }
}

void FillPassengerScroll()
{
	int i, howWork;
	string faceName;
	string attributeName;
	string PsgAttrName;
	int _curCharIdx;
	ref _refCurChar;
	aref pRef, pRef2;
	bool  ok;
	
	DeleteAttribute(&GameInterface, "PASSENGERSLIST");

	nCurScrollOfficerNum = -1;
	GameInterface.PASSENGERSLIST.current = 0;
	makearef(pRef,pchar.Fellows.Passengers);

	int nListSize = GetPassengersQuantity(pchar);
	int nListSizeFree = GetFreePassengersQuantity(pchar);

	GameInterface.PASSENGERSLIST.NotUsed = 6;
	GameInterface.PASSENGERSLIST.ListSize = nListSizeFree + 2;

	GameInterface.PASSENGERSLIST.ImagesGroup.t0 = "EMPTYFACE";

	FillFaceList("PASSENGERSLIST.ImagesGroup", pchar, 2); // passengers

	GameInterface.PASSENGERSLIST.BadTex1 = 0;
	GameInterface.PASSENGERSLIST.BadPic1 = "emptyface";

	int m = 0;
	for(i=0; i<nListSize; i++)
	{
		attributeName = "pic" + (m+1);
		PsgAttrName = "id"+(i+1);
		makearef(pRef2,GameInterface.PASSENGERSLIST.(attributeName));

		_curCharIdx = sti(pRef.(PsgAttrName));

		if (_curCharIdx!=-1)
		{
			ok = CheckAttribute(&characters[_curCharIdx], "prisoned") && sti(characters[_curCharIdx].prisoned) == true;
			if (!ok && GetRemovable(&characters[_curCharIdx]))
			{
                // совместители должностей -->
                howWork = 1;
                if (CheckCharacterPerk(&characters[_curCharIdx], "ByWorker"))
                {
                    howWork = 2;
                }
                if (CheckCharacterPerk(&characters[_curCharIdx], "ByWorker2"))
                {
                    howWork = 3;
                }
                ok = !CheckAttribute(&characters[_curCharIdx], "isbusy") || sti(characters[_curCharIdx].isbusy) < howWork;
                PsgAttrName = GetOfficerTypeByNum(nCurScrollNum);
				// совместители должностей <--
				if (ok && !CheckAttribute(&characters[_curCharIdx], PsgAttrName))
				{
					GameInterface.PASSENGERSLIST.(attributeName).character = _curCharIdx;
					GameInterface.PASSENGERSLIST.(attributeName).img1 = GetFacePicName(GetCharacter(_curCharIdx));
					GameInterface.PASSENGERSLIST.(attributeName).tex1 = FindFaceGroupNum("PASSENGERSLIST.ImagesGroup","FACE128_"+Characters[_curCharIdx].FaceID);
					m++;
				}
			}
		}
	}
	GameInterface.PASSENGERSLIST.ListSize = m + 2; // не знаю зачем, но для совместимости с "было"
}

void ExitOfficerMenu()
{
	XI_WindowShow("OFFICERS_WINDOW", false);
	XI_WindowDisable("OFFICERS_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);
	SetAllPerksSelectable(true);
	SetCurrentNode("CHARACTERS_SCROLL");
}

void OfficerChange()
{
	string attributeName = "pic" + (nCurScrollNum+1);
	
	//if(bGlobalTutor && nCurScrollNum < 7) return;
	
	if(GameInterface.CHARACTERS_SCROLL.(attributeName).character != "0")
	{
		int iCharacter = sti(GameInterface.CHARACTERS_SCROLL.(attributeName).character);
		xi_refCharacter = &characters[iCharacter];
		if (isOfficerInShip(xi_refCharacter, true) && xi_refCharacter.id != pchar.id)
		{
			XI_WindowShow("REMOVE_OFFICER_WINDOW", true);
			XI_WindowDisable("REMOVE_OFFICER_WINDOW", false);
			XI_WindowDisable("MAIN_WINDOW", true);
			SetCurrentNode("REMOVE_CANCEL_OFFICER");
			SetAllPerksSelectable(false);
		}
	}
	else
	{
		if (nCurScrollNum <= 9 && nCurScrollNum != 0)
		{
			FillPassengerScroll();
			SendMessage(&GameInterface,"lsl",MSG_INTERFACE_SCROLL_CHANGE,"PASSENGERSLIST",-1);
			SetCurrentNode("PASSENGERSLIST");
			ProcessFrame();
			SetOfficersSkills();

			XI_WindowShow("OFFICERS_WINDOW", true);
			XI_WindowDisable("OFFICERS_WINDOW", false);
			XI_WindowDisable("MAIN_WINDOW", true);
			SetAllPerksSelectable(false);
		}
	}
}

void AcceptAddOfficer()
{
	int iCurrentNode = nCurScrollNum;
	bool bNeedFollow = false;
	bool bOk;
	ref rChar;
	
	string attributeName2 = "pic"+(nCurScrollOfficerNum+1);

    if (checkAttribute(GameInterface, "PASSENGERSLIST."+attributeName2 + ".character"))
    {
		int iChar = sti(GameInterface.PASSENGERSLIST.(attributeName2).character);

		if (!CheckAttribute(&characters[iChar], "isbusy"))
		{
			characters[iChar].isbusy = 1;
		}
		else
		{
		    characters[iChar].isbusy = sti(characters[iChar].isbusy) + 1; // совместители
		}
		bOk = (Characters[iChar].location != pchar.location);  // ниже локация перебивается на ГГ
		switch (nCurScrollNum)
		{
			case 1:
				pchar.Fellows.Passengers.navigator = iChar;
			break;

			case 2:
				pchar.Fellows.Passengers.boatswain = iChar;
			break;

			case 3:
				pchar.Fellows.Passengers.cannoner = iChar;
			break;

			case 4:
				pchar.Fellows.Passengers.doctor = iChar;
			break;

			case 5:
				pchar.Fellows.Passengers.treasurer = iChar;
			break;

			case 6:
				pchar.Fellows.Passengers.carpenter = iChar;
			break;

			case 7:
				SetOfficersIndex(pchar, 1, iChar);
				bNeedFollow = true;
			break;

			case 8:
				SetOfficersIndex(pchar, 2, iChar);
				bNeedFollow = true;
			break;

			case 9:
				SetOfficersIndex(pchar, 3, iChar);
				bNeedFollow = true;
			break;
		}
        attributeName2 = GetOfficerTypeByNum(nCurScrollNum);
    	characters[iChar].(attributeName2) = true; // совместитель дожности
    	//SetCharacterTask_FollowCharacter(&Characters[iChar], PChar);
    	if (!IsEntity(&worldMap) && !bSeaActive && bNeedFollow) // только для офов
    	{
	    	if (IsEntity(&loadedLocation) && loadedLocation.type == "tavern")
	    	{   //  пусть всегда будут появляться
	    	    PlaceCharacter(&Characters[iChar], "goto", "random_must_be_near");
	    	}
			else // запрет обмена с офами, где их нет
			{
				ref loc = &Locations[FindLocation(pchar.location)];
				aref grp;
				makearef(grp, loc.locators.officers);
				int num = GetAttributesNum(grp);
				if (num < 1 || CheckAttribute(loc, "DisableOfficers")) ChangeCharacterAddressGroup(&Characters[iChar], "none", "", "");
			}
	    	LAi_tmpl_SetFollow(&Characters[iChar], GetMainCharacter(), -1.0);
    	}
		FillCharactersScrollEx(true);
		GameInterface.CHARACTERS_SCROLL.current = iCurrentNode;
		
		rChar = &characters[iChar];
		Event("eSwitchPerks", "l", sti(rChar.index));
	}
	ExitOfficerMenu();
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_SCROLL_CHANGE,"CHARACTERS_SCROLL",-1);
	ProcessFrame();
	SetVariable();
}

void ExitRemoveOfficerMenu()
{
	XI_WindowShow("REMOVE_OFFICER_WINDOW", false);
	XI_WindowDisable("REMOVE_OFFICER_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);
	SetAllPerksSelectable(true);
	SetCurrentNode("CHARACTERS_SCROLL");
}

void AcceptRemoveOfficer()
{
    int iCurrentNode = nCurScrollNum;
	string attributeName2 = "pic"+(nCurScrollNum+1);

	int iChar = sti(GameInterface.CHARACTERS_SCROLL.(attributeName2).character);

    characters[iChar].isbusy = sti(characters[iChar].isbusy) - 1; // совместители
	if (sti(characters[iChar].isbusy) <= 0)
	{
		DeleteAttribute(&characters[iChar], "isbusy");
	}

	switch (nCurScrollNum)
	{
		case 1:
			pchar.Fellows.Passengers.navigator = -1;
		break;

		case 2:
			pchar.Fellows.Passengers.boatswain = -1;
		break;

		case 3:
			pchar.Fellows.Passengers.cannoner = -1;
		break;

		case 4:
			pchar.Fellows.Passengers.doctor = -1;
		break;

		case 5:
			pchar.Fellows.Passengers.treasurer = -1;
		break;

		case 6:
			pchar.Fellows.Passengers.carpenter = -1;
		break;

		case 7:
			RemoveOfficersIndex(pchar, GetOfficersIndex(pchar, 1));
		break;

		case 8:
			RemoveOfficersIndex(pchar, GetOfficersIndex(pchar, 2));
		break;

		case 9:
			RemoveOfficersIndex(pchar, GetOfficersIndex(pchar, 3));
		break;
	}
    attributeName2 = GetOfficerTypeByNum(nCurScrollNum);
    DeleteAttribute(&characters[iChar], attributeName2); // совместитель дожности
    
	FillCharactersScrollEx(true);
	GameInterface.CHARACTERS_SCROLL.current = iCurrentNode;
	ExitRemoveOfficerMenu();
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_SCROLL_CHANGE,"CHARACTERS_SCROLL",-1);
	SetVariable();
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
	    if (_add > 0)
	    {
	        iValue = AddSPECIALValue(xi_refCharacter, sSkillName, -_add);
			xi_refCharacter.skill.FreeSPECIAL = sti(xi_refCharacter.skill.FreeSPECIAL) + _add;
	    }
	    else return;
    }
    SetVariable();
    SetSkillArrows();
}

///////////////////////////////////////  PERKS /////////////////////////
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

void CreatePerksPictures() {
	aref perks;
	makearef(perks, ChrPerksList.list);

	int perksNum = GetAttributesNum(perks);
	for (int i = 0; i < perksNum; i++) {
		string perkName = GetAttributeName(GetAttributeN(perks,i));
		string nodeName = "PERK_" + perkName;
		string bnodeName = "PERKBASE_" + perkName;
		
		// XI_MakeNode("resource\ini\interfaces\abilities.ini", "PICTURE", nodeName, 82);
		// XI_MakeNode("resource\ini\interfaces\abilities.ini", "PICTURE", bnodeName, 81);
	}
	RefreshPerksPictures();
}

void RefreshPerksPictures() {
	aref perks;
	makearef(perks, ChrPerksList.list);
	string pictureGroup;
	string pictureName;
	int pColor1 = argb(255,128,128,128);
	int pColor2 = argb(255,88,118,88); //зелёный
	int pColor3 = argb(255,55,55,55);//серый
	int pColor4 = argb(255,75,75,75);//серый

	int perksNum = GetAttributesNum(perks);

	for (int i = 0; i < perksNum; i++) {
		string perkName = GetAttributeName(GetAttributeN(perks,i));
		string nodeName = "PERK_" + perkName;
		string bnodeName = "PERKBASE_" + perkName;
		SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, bnodeName, 5, 0 );		
		if (CheckAttribute(perks, perkName + ".Hiden")) continue;
		// активные перки
		if (CheckCharacterPerk(xi_refCharacter, perkName)) {
			pictureGroup = "PERKS_ENABLE";
			if (ChrPerksList.list.(perkName).BaseType == "self") {
				pictureName = "base_self";
			} else {
				pictureName = "base_ship";
			}
			SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,nodeName, 4, pColor1);
			SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, bnodeName, 5, 1 );
		}
		else {
			pictureGroup = "PERKS_DISABLE";
			pictureName = "base";
			SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,nodeName, 4, pColor1);
			// недоступные перки
			if (CheckPerkFilter(perkName)) {
				SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,nodeName, 4, pColor3);
				SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,bnodeName, 4, pColor4);
			}
			// есть у офа, но нет у ГГ
			if (xi_refCharacter.id == pchar.id && GetOfficersPerkUsing(pchar, perkName)) {
				pictureGroup = "PERKS_ENABLE";
				pictureName = "base_officer";
				SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, bnodeName, 5, 1 );
			}
			/* if(GetCharacterEquipByGroup(pchar, HAT_ITEM_TYPE) == "hat5" && IsCompanion(xi_refCharacter) && GetOfficersPerkUsing(xi_refCharacter, perkName))
			{
				pictureGroup = "PERKS_ENABLE";
				pictureName = "base_officer";
				SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, bnodeName, 5, 1 );
			} */
		}
		SetNewGroupPicture(nodeName, pictureGroup, perkName);
		SetNewGroupPicture(bnodeName, pictureGroup, pictureName);
		HidePerkSelect();
	}
}

void ChoosePerk(string perkName)
{
	bool ok = true;
	bool showCondition = true;
	selectedPerk = perkName;
	string  descr    = GetConvertStr("perk" + perkName, "AbilityDescribe.txt");
	aref rootItems;
	int    i;
	string row, perkCond, icoGroup;
	SetNewGroupPicture("PERKPICTURE", "PERKS_ENABLE", perkName);
    SetFormatedText("PERKWINDOW_CAPTION", GetConvertStr(perkName, "AbilityDescribe.txt"));
    
    if (CheckAttribute(&ChrPerksList, "list." + perkName + ".OfficerType") && perkName != "IronWill")
    {
		descr += "\n\n" + XI_ConvertString("Perk_Descr11") + " " + XI_ConvertString(ChrPerksList.list.(perkName).OfficerType)+ XI_ConvertString("Perk_Descr12");
    }
    SetFormatedText("PERKWINDOW_TEXT", descr);

    if (ChrPerksList.list.(perkName).BaseType == "self")
    {
		if (sti(xi_refCharacter.perks.FreePoints_self) <= 0) ok = false;
	}
	else
	{
		if (sti(xi_refCharacter.perks.FreePoints_ship) <= 0) ok = false;
    }
	if (CheckPerkFilter(perkName)) ok = false;
	
	// проверка на необходимые перки -->
	if (CheckAttribute(&ChrPerksList, "list." + perkName + ".condition"))
	{
        makearef(rootItems, ChrPerksList.list.(perkName).condition);
		Table_Clear("PERKTABLE_NEED", false, true, false);
		GameInterface.PERKTABLE_NEED.select = 0;
		GameInterface.PERKTABLE_NEED.hr.td1.str = "";
		GameInterface.PERKTABLE_NEED.top = 0;
		for (i=0; i<GetAttributesNum(rootItems); i++)
    	{
    	    row = "tr" + (i+1);
    	    perkCond = GetAttributeName(GetAttributeN(rootItems, i));
    	    if (CheckCharacterPerk(xi_refCharacter, perkCond))
            {
                icoGroup = "PERKS_ENABLE";
                GameInterface.PERKTABLE_NEED.(row).td2.color = argb(255,255,255,255);
            }
            else
            {
                icoGroup = "PERKS_DISABLE";
                GameInterface.PERKTABLE_NEED.(row).td2.color = argb(255,196,196,196);
                ok = false;
            }
			GameInterface.PERKTABLE_NEED.(row).td1.icon.group  = icoGroup;
			GameInterface.PERKTABLE_NEED.(row).td1.icon.image  = perkCond;
			GameInterface.PERKTABLE_NEED.(row).td1.icon.width  = 40;
		    GameInterface.PERKTABLE_NEED.(row).td1.icon.height = 40;
		    GameInterface.PERKTABLE_NEED.(row).td1.icon.offset = "0, 2";

			GameInterface.PERKTABLE_NEED.(row).td2.str = GetConvertStr(perkCond, "AbilityDescribe.txt");
			GameInterface.PERKTABLE_NEED.(row).td2.line_space_modifier = 0.8;
			GameInterface.PERKTABLE_NEED.(row).td2.textoffset = "0,2";
    	}
		Table_UpdateWindow("PERKTABLE_NEED");
	}
	else
	{
	    showCondition = false;
	}
	// проверка на необходимые перки <--

    // проверка ранга
    if (CheckAttribute(&ChrPerksList, "list." + perkName + ".rank") && sti(xi_refCharacter.rank) < sti(ChrPerksList.list.(perkName).rank))
	{
        ok = false;
    }

	XI_WindowShow("PERKWINDOW", true);
	XI_WindowDisable("PERKWINDOW", false);

	// XI_WindowDisable("MAIN_WINDOW", true);
	
	if (CheckCharacterPerk(xi_refCharacter, perkName))
 	{
 	    SetNodeUsing("PERKON", true);
 	    ok = false; // уже есть
  	    SetNewGroupPicture("PERKPICTURE", "PERKS_ENABLE", perkName);
		if (ChrPerksList.list.(perkName).BaseType == "self"){
			SetNewGroupPicture("PERKPICTURE_BASE", "PERKS_ENABLE", "base_self");
		}
        else {
			SetNewGroupPicture("PERKPICTURE_BASE", "PERKS_ENABLE", "base_ship");
		}
	}
 	else
 	{
 	    SetNodeUsing("PERKON", false);
 	    SetNewGroupPicture("PERKPICTURE", "PERKS_DISABLE", perkName);
		SetNewGroupPicture("PERKPICTURE_BASE", "PERKS_DISABLE", "base");
 	}
    SetSelectable("PERKACCEPT", ok);
    SetNodeUsing("PERKTABLE_NEED", showCondition);
	SetPerkSelect();
	HideSkillChanger();
}

void ExitPerkMenu()
{
	XI_WindowShow("PERKWINDOW", false);
	XI_WindowDisable("PERKWINDOW", true);
	// XI_WindowDisable("MAIN_WINDOW", false);
	
	SetCurrentNode("CHARACTERS_SCROLL");
	HidePerkSelect();
}

void AcceptPerk()
{
	int iCurrentNode = nCurScrollNum;
	string perkName = selectedPerk;
    if (ChrPerksList.list.(perkName).BaseType == "self")
    {
		xi_refCharacter.perks.FreePoints_self = sti(xi_refCharacter.perks.FreePoints_self) - 1;
	}
	else
	{
		xi_refCharacter.perks.FreePoints_ship = sti(xi_refCharacter.perks.FreePoints_ship) - 1;
    }
    if (SetCharacterPerk(xi_refCharacter, perkName))
    {   // перерисуем персонажа
    	FillSkillTables();	
    }
    // перерисуем все -->
	SetFormatedText("PERSONAL_AVAILABLE", XI_ConvertString("Personal abilities") + "  -  " +xi_refCharacter.perks.FreePoints_self);
    SetFormatedText("SHIP_AVAILABLE", XI_ConvertString("Ship abilities") + "  -  " + xi_refCharacter.perks.FreePoints_ship);
    RefreshPerksPictures();
	RefreshPerksNames();
	FillCharactersScrollEx(true);
	FillPassengerScroll();
	GameInterface.CHARACTERS_SCROLL.current = iCurrentNode;
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_SCROLL_CHANGE,"CHARACTERS_SCROLL",-1);
	SetVariable();
	// перерисуем все <--
	ExitPerkMenu();
}

void SetPerkSelect() {
	int sColor = argb(155,75,75,75);//серый
	string snodeName = "PERKSELECT_" + selectedPerk;
	if (selectedPerk != "") {
        XI_MakeNode("resource\ini\interfaces\abilities.ini", "PICTURE", snodeName, 83);
		SetNewGroupPicture("PERKSELECT_" + selectedPerk, "perks_enable", "select");
		if (CheckPerkFilter(selectedPerk)) {
			SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,snodeName, 4, sColor);
		} else {
		SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, snodeName, 5, 1 );
		}
    }
}

void HidePerkSelect() {
    if (selectedPerk != "") {
        XI_DeleteNode("PERKSELECT_" + selectedPerk);
    }
}

void CreatePerksNames() {
	aref perks;
	makearef(perks, ChrPerksList.list);

	int perksNum = GetAttributesNum(perks);
	for (int i = 0; i < perksNum; i++) {
		string perkName = GetAttributeName(GetAttributeN(perks,i));
		string nodeName = "PERKNAME_" + perkName;
		
		XI_MakeNode("resource\ini\interfaces\abilities.ini", "FORMATEDTEXT", nodeName, 83);
	}
	RefreshPerksNames();
}

void RefreshPerksNames() {
	aref perks;
	makearef(perks, ChrPerksList.list);
	int tColor1 = argb(255,255,255,255);
	int tColor2 = argb(255,255,245,155);//желтый
	int tColor3 = argb(255,255,225,155);//оранжевый
	int tColor4 = argb(255,196,255,196);//зелёный
	int tColor5 = argb(255,155,155,155);//серый

	int perksNum = GetAttributesNum(perks);
	for (int i = 0; i < perksNum; i++) {
		string perkName = GetAttributeName(GetAttributeN(perks,i));
		string nodeName = "PERKNAME_" + perkName;

		if (CheckAttribute(perks, perkName + ".Hiden")) continue;

		SetFormatedText(nodeName, GetConvertStr(perkName, "AbilityDescribe.txt"));
		// активные перки
		if (CheckCharacterPerk(xi_refCharacter, perkName)) {
			if (ChrPerksList.list.(perkName).BaseType == "self") {
				SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,nodeName, 8, 0, tColor2);
			} else {
				SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,nodeName, 8, 0, tColor3);
			}
		}
		else {
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,nodeName, 8, 0, tColor1);
			// недоступные перки
			if (CheckPerkFilter(perkName)) {
				SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,nodeName, 8, 0, tColor5);
			}
			// есть у офа, но нет у ГГ
			if (xi_refCharacter.id == pchar.id && GetOfficersPerkUsing(pchar, perkName)) {
				SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,nodeName, 8, 0, tColor4);
			}
		}
	}
}

void HidePerksNames() {
	aref perks;
	makearef(perks, ChrPerksList.list);

	int perksNum = GetAttributesNum(perks);
	for (int i = 0; i < perksNum; i++) {
		string perkName = GetAttributeName(GetAttributeN(perks,i));
		string nodeName = "PERKNAME_" + perkName;
		XI_DeleteNode(nodeName);
	}
}

void SetAllPerksSelectable(bool selectable) {
    aref perks;
    makearef(perks, ChrPerksList.list);

    int perksNum = GetAttributesNum(perks);
    for (int i = 0; i < perksNum; i++) {
        string perkName = GetAttributeName(GetAttributeN(perks,i));
        string nodeName = "PERK_" + perkName;
        string bnodeName = "PERKNAME_" + perkName;
        
        SetSelectable(nodeName, selectable);
        SetSelectable(bnodeName, selectable);
    }
}

void procScrollTabChange()
{
	int iComIndex = GetEventData();
	string sNodName = GetEventData();
	if(sNodName == "TABBTN_SCROLL_1")
	{
		SetControlsScrollTabMode(1);
		return;
	}
	if(sNodName == "TABBTN_SCROLL_2")
	{
		if(GetFreePassengersQuantity(pchar) == 0) return;
		SetControlsScrollTabMode(2);
		return;
	}
}

void SetControlsScrollTabMode(int nMode)
{
	int nColor1 = argb(255,196,196,196);
	int nColor2 = nColor1;
	if(GetFreePassengersQuantity(pchar) == 0) nColor2 = argb(255,128,128,128);

	string sPic1 = "TabDeSelected";
	string sPic2 = sPic1;

	string sPic3 = sPic1;
	string sPic4 = sPic1;

	switch (nMode)
	{
		case 1:
			sPic1 = "TabSelected";
			sPic3 = "TabSelectedMark";
			nColor1 = argb(255,255,255,255);
		break;
		case 2:
			sPic2 = "TabSelected";
			sPic4 = "TabSelectedMark";
			nColor2 = argb(255,255,255,255);
		break;
	}
    
	SetNewGroupPicture("TABBTN_SCROLL_1", "TABS", sPic1);
	SetNewGroupPicture("TABBTN_SCROLL_2", "TABS", sPic2);
	SetNewGroupPicture("TABBTN_SCROLL_1_MARK", "TABS", sPic3);
	SetNewGroupPicture("TABBTN_SCROLL_2_MARK", "TABS", sPic4);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_SCROLL_1", 8,0,nColor1);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_SCROLL_2", 8,0,nColor2);

	FillScrollControlsList(nMode);
}

void FillScrollControlsList(int nMode)
{
	switch (nMode)
	{
	    case 1: 
			FillCharactersScrollEx(true);
			currentScrollTab = 1;
		break;  // офицеры
	    case 2: 
			FillCharactersScrollEx(false); 
			currentScrollTab = 2;
		break;  // пассажиры
	}
	if (CheckAttribute(&InterfaceStates, "CurCharacter")) 
	{
		GameInterface.CHARACTERS_SCROLL.current = InterfaceStates.CurCharacter;
		SendMessage(&GameInterface,"lsl",MSG_INTERFACE_SCROLL_CHANGE,"CHARACTERS_SCROLL",-1);
		DeleteAttribute(&InterfaceStates, "CurCharacter");
	}
	else
	{
		GameInterface.CHARACTERS_SCROLL.current = 0;
		SendMessage(&GameInterface,"lsl",MSG_INTERFACE_SCROLL_CHANGE,"CHARACTERS_SCROLL",-1);
	}
}