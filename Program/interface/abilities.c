// Sith/mitrokosta меню навыки
#event_handler("Control Activation","ProcessInterfaceControls");// гуляем по меню кнопками Q и E
#include "interface\character_all.h"
#include "interface\utils\popup_error.c"
#include "interface\utils\popup_confirmation.c"
#include "interface\utils\perks.c"
#include "interface\utils\common_header.c"
#include "interface\utils\officer_change.c"
#include "interface\utils\special_skill_change.c"
#include "interface\utils\items\descriptors.c"
#include "interface\utils\modifiers.c"

int nCurScrollOfficerNum;
string selectedPerk;
int currentInfoMode = 0;
int currentScrollTab = 1;
int currentPerkTab = 1;
bool bShowTabOfficers = true;
aref cashTable;

void InitInterface(string iniName)
{
	xi_refCharacter = pchar;
	InterfaceStack.SelectMenu_node = "LaunchAbilities"; // запоминаем, что звать по Ф2
	GameInterface.title = "titleCharacter";
	currentScrollTab = GetCurrentCharactersTab();
	bShowTabOfficers = currentScrollTab == 1;
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
	SetEventHandler("HideInfoWindow","HideInfoWindow",0);
	SetEventHandler("TableSelectChange", "CS_TableSelectChange", 0);
	SetEventHandler("ExitOfficerMenu","ExitOfficerMenu",0);
	SetEventHandler("OfficerChange","OfficerChange",0);
	SetEventHandler("acceptaddofficer","AcceptAddOfficer",0);
	SetEventHandler("ExitPerkMenu","ExitPerkMenu",0);
	SetEventHandler("AcceptPerk","AcceptPerk",0);
	SetEventHandler("eScrollTabControlPress","procScrollTabChange",0);
	SetEventHandler("PopupIsShown","PopupIsShown",0);
	SetEventHandler("PopupIsClosed","PopupIsClosed",0);
	SetEventHandler("SwitchPerkTabs","SwitchPerkTabs",0);
	SetEventHandler("SelectorValueChanged","SelectorValueChanged",0);
	SetEventHandler("TestRerollGiveOfficer","TestRerollGiveOfficer",0);
	XI_RegistryExitKey("IExit_F2");

	SetVariable();
	SetCurrentNode("CHARACTERS_SCROLL");
	SetNodeUsing("CHARACTERS_SCROLL",true);
	if (MOD_SKILL_ENEMY_RATE > 9)// недоступно для ОК
	{
		SetNodeUsing("PERK_InstantRepair",false);
	}

	SetControlsScrollTabMode(currentScrollTab);
	SetPerksTabMode(1);
	HideSkillChanger();
	CreatePerksPictures();
	TEST_InitReroll();
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
	// if (controlName == "InterfaceInfoSwitch") {
	// 	currentInfoMode = (currentInfoMode + 1) % 2;
	// 	SetPerksNamesMode(currentInfoMode + 1);
	// }
	if (controlName == "InterfaceTabSwitch") {
		currentScrollTab = currentScrollTab % 2 + 1;
		SetControlsScrollTabMode(currentScrollTab);
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
	
	Perks_Achievments();
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
	DelEventHandler("HideInfoWindow","HideInfoWindow");
	DelEventHandler("TableSelectChange", "CS_TableSelectChange");
	DelEventHandler("ExitOfficerMenu","ExitOfficerMenu");
	DelEventHandler("OfficerChange","OfficerChange");
	DelEventHandler("acceptaddofficer","AcceptAddOfficer");
	DelEventHandler("ExitPerkMenu","ExitPerkMenu");
	DelEventHandler("AcceptPerk","AcceptPerk");
	DelEventHandler("eScrollTabControlPress","procScrollTabChange");
	DelEventHandler("PopupIsShown","PopupIsShown");
	DelEventHandler("PopupIsClosed","PopupIsClosed");
	DelEventHandler("SwitchPerkTabs","SwitchPerkTabs");
	DelEventHandler("SelectorValueChanged","SelectorValueChanged");
	DelEventHandler("TestRerollGiveOfficer","TestRerollGiveOfficer");
	
	interfaceResultCommand = exitCode;
	if( CheckAttribute(&InterfaceStates,"ReloadMenuExit"))
	{
        DeleteAttribute(&InterfaceStates,"ReloadMenuExit");
		EndCancelInterface(false);
	}
	else
	{
		DeleteAttribute(&InterfaceStates, "CurCharacter");
		if (interfaceResultCommand == RC_INTERFACE_ANY_EXIT) DeleteAttribute(&InterfaceStates, "nCurScrollTab");
		EndCancelInterface(true);
	}

	aref markers;
	makearef(markers, InterfaceStates.markers);
	for (int j = 0; j < GetAttributesNum(markers); j++)
	{
		string chrId = GetAttributeName(GetAttributeN(markers, j));
		if (pchar.id == chrId) continue;
		if (!CheckPassengerInCharacter(pchar, chrId)) DeleteAttribute(&markers, chrId);
	}
}

void SelectorValueChanged()
{
	int iComIndex = GetEventData();
	string sNodeName = GetEventData();
	int direction = 0;

	switch (iComIndex)
	{
		case ACTION_LEFTSTEP: direction = -1; break;
		case ACTION_RIGHTSTEP: direction = 1; break;
		case ACTION_MOUSECLICK:
		{
			if      (FindSubStr(sNodeName, "LEFTCHANGE_", 0) == 0) direction = -1; // клик левая стрелка
			else if (FindSubStr(sNodeName, "RIGHTCHANGE_", 0) == 0) direction = 1; // клик правая стрелка
		}
		break;
	}
	if (direction == 0) return;

	TEST_RerollChangeMode(&direction);
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
	if (findsubstr(&nodName, "PERK_", 0) == 0)
	{
		if (comName == "click")
		{
			SetCurrentNode("PERKWINDOW_TEXT");
			HidePerkSelect();
			ChoosePerk(strcut(&nodName, 5, strlen(&nodName) - 1));
		}
	  else if (comName == "dblclick" || comName == "activate")
		{
			ChoosePerk(strcut(&nodName, 5, strlen(&nodName) - 1));
			if (GetSelectable("PERKACCEPT")) CallWithConfirmation(xiStr("Accept Perk Confirmation"), "AcceptPerk", true);
		}
	}

	if (HasSubStr(nodName, "REROLL_BUTTON")) TEST_Reroll(nodName);
}

void SwitchPerkTabs()
{
	int iComIndex = GetEventData();
	string sNodName = GetEventData();
	if (sNodName == "TABBTN_SELF_PERKS") SetPerksTabMode(1);
	else if (sNodName == "TABBTN_SHIP_PERKS") SetPerksTabMode(2);
}

void SetVariable()
{

	SetCommonHeaderInfo();
	SetNodeUsing("PERKON", false);
	SetSelectable("PERKACCEPT", false);
	cashTable = CT_GetTableOrInit(xi_refCharacter, CT_COMMON);
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

		if (bBettaTestMode)
		{
		 CreateString(true,"lifepath",
										"LifePath=" + GEN_GetArchetype(xi_refCharacter, 0) +
										" Hobby=" + GEN_GetArchetype(xi_refCharacter, 1) +
										" var=" + GetAttributeOrDefault(xi_refCharacter, "personality.templateVar", "0") +
										,
										"INTERFACE_ULTRASMALL",COLOR_NORMAL,430,1000, SCRIPT_ALIGN_LEFT,1.0);
		}

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

	// Выпиливаем маркер о новых очках перков
	string chrId = xi_refCharacter.id;
	InterfaceStates.markers.(chrId) = true;
	GameInterface.CHARACTERS_SCROLL.(attributeName).img2 = "";
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_SCROLL_CHANGE,"CHARACTERS_SCROLL",-1);
	
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
	string sCurrentNode = GetEventData();
	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;
	int iItem;
	int	picW = 128;
	int	picH = 128;

	sPicture = "-1";
	string sAttributeName;
	int nChooseNum = -1;
	string sRow;
	switch (sCurrentNode)
	{
		case "CHARACTERS_SCROLL":
			CloseTooltipNew();
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
						sText2 = sText2 + NewStr() + GetConvertStr("perkByWorkerShort", "AbilityDescribe.txt"));
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
						sText2 = sText2 + NewStr() + GetConvertStr("perkByWorkerShort", "AbilityDescribe.txt"));
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
			CloseTooltipNew();
			nChooseNum = SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "TABLE_SPECIAL", 1);
			sRow = "tr"+nChooseNum;
			if (nChooseNum > 0) SetSkillsTooltip(sCurrentNode, &sHeader, &sText1, &sText2, &sText3, sRow);
			else return;
		break;
		
		case "TABLE_SKILL_1":
			CloseTooltipNew();
			nChooseNum = SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "TABLE_SKILL_1", 1);
			sRow = "tr"+nChooseNum;
			if (nChooseNum > 0) SetSkillsTooltip(sCurrentNode, &sHeader, &sText1, &sText2, &sText3, sRow);
			else return;
		break;
		case "TABLE_SKILL_2":
			CloseTooltipNew();
			nChooseNum = SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "TABLE_SKILL_2", 1);
			sRow = "tr"+nChooseNum;
			if (nChooseNum > 0) SetSkillsTooltip(sCurrentNode, &sHeader, &sText1, &sText2, &sText3, sRow);
			else return;
		break;
		case "TABSTR_SELF_PERKS":
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
		case "TABSTR_SHIP_PERKS":
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
	aref perk = PerkFromId(selectedPerk);
	SetDescriptorsTooltip(sCurrentNode, &sHeader, &sText1, &sText2, &sText3, &perk);
	CreateTooltipNew(sCurrentNode, sHeader, sText1, sText2, sText3, "", sPicture, sGroup, sGroupPicture, picW, picH, false);
	HidePerkSelect();
}

void HideInfoWindow()
{
	CloseTooltipNew();
	if (XI_IsWindowEnable("MAIN_WINDOW")) SetCurrentNode("CHARACTERS_SCROLL");
}

void FillSkillTables()
{
	int     i;
	string  row, skillName;
	int     diff, skillVal, skillValWithEffects;
    
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
	SetFormatedText("TABSTR_SELF_PERKS", XI_ConvertString("Personal abilities") + "  -  " +xi_refCharacter.perks.FreePoints_self);
	SetFormatedText("TABSTR_SHIP_PERKS", XI_ConvertString("Ship abilities") + "  -  " + xi_refCharacter.perks.FreePoints_ship);
	
	GameInterface.TABLE_SPECIAL.select = 0;
	GameInterface.TABLE_SPECIAL.hr.td1.str = "";

	for (i=0; i<=7; i++)
	{
	    row = "tr" + i;
	    skillName = GetSkillNameByTRIdx("SPECIALType", i);
	    
        GameInterface.TABLE_SPECIAL.(row).UserData.ID = skillName;
		GameInterface.TABLE_SPECIAL.(row).td1.fontidx = 0;
		GameInterface.TABLE_SPECIAL.(row).td1.textoffset = "5,-5";
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
		skillVal = GetSpecialBase(xi_refCharacter, skillName);
		//GameInterface.TABLE_SPECIAL.(row).td4.str = skillVal; // старый метод
		int specialValue = GetSpecialAfterPenalty(xi_refCharacter, skillName);
		GameInterface.TABLE_SPECIAL.(row).td4.str = specialValue;
		// рассчет драйна
		diff = specialValue - skillVal;
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
		GameInterface.TABLE_SKILL_1.(row).td1.icon.group = "EQUIP_ICONS";
	    GameInterface.TABLE_SKILL_1.(row).td1.icon.image = skillName + " skill icon";
	    GameInterface.TABLE_SKILL_1.(row).td1.icon.width = 35;
    	GameInterface.TABLE_SKILL_1.(row).td1.icon.height = 35;
    	GameInterface.TABLE_SKILL_1.(row).td1.icon.offset = "-5, -2";
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
		skillVal = GetSkillBase(xi_refCharacter, &skillName);
		skillValWithEffects = GetSkillAfterPenalty(xi_refCharacter, &skillName);
		GameInterface.TABLE_SKILL_1.(row).td5.str = skillValWithEffects;
		// расчёт драйна
		diff = skillValWithEffects - skillVal;
		
		if (skillVal < SKILL_MAX)
		{
			GameInterface.TABLE_SKILL_1.(row).td3.str = makeint(GetSkillValueExp(xi_refCharacter, skillName) * 100.0 / makefloat(skillVal * GetCharacterExpRate(xi_refCharacter, skillName))) + " %";
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
		GameInterface.TABLE_SKILL_2.(row).td1.icon.group = "EQUIP_ICONS";
	    GameInterface.TABLE_SKILL_2.(row).td1.icon.image = skillName + " skill icon";
	    GameInterface.TABLE_SKILL_2.(row).td1.icon.width = 35;
    	GameInterface.TABLE_SKILL_2.(row).td1.icon.height = 35;
    	GameInterface.TABLE_SKILL_2.(row).td1.icon.offset = "-5, -2";
		GameInterface.TABLE_SKILL_2.(row).td2.align = "left";
		GameInterface.TABLE_SKILL_2.(row).td2.textoffset = "0,0";
		GameInterface.TABLE_SKILL_2.(row).td2.scale = 1.2;
		GameInterface.TABLE_SKILL_2.(row).td3.align = "left";
		GameInterface.TABLE_SKILL_2.(row).td3.scale = 1.2;
		GameInterface.TABLE_SKILL_2.(row).td5.fontidx = 0;
		GameInterface.TABLE_SKILL_2.(row).td5.scale = 0.8;
		GameInterface.TABLE_SKILL_2.(row).td5.align = "left";

		GameInterface.TABLE_SKILL_2.(row).td2.str = XI_ConvertString(skillName);
		skillVal = GetSkillBase(xi_refCharacter, &skillName);
		skillValWithEffects = GetSkillAfterPenalty(xi_refCharacter, &skillName);
		//GameInterface.TABLE_SKILL_2.(row).td5.str = skillVal; // старый метод
		GameInterface.TABLE_SKILL_2.(row).td5.str = skillValWithEffects;
		// рассчет драйна
		diff = skillValWithEffects - skillVal;

		if (skillVal < SKILL_MAX)
		{
			GameInterface.TABLE_SKILL_2.(row).td3.str = makeint(GetSkillValueExp(xi_refCharacter, skillName) * 100.0 / makefloat(skillVal * GetCharacterExpRate(xi_refCharacter, skillName))) + " %";
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
					int start;
	if (sti(xi_refCharacter.skill.freeskill) > 0 && ok)
	{
	    if (GetSkillValue(xi_refCharacter, SKILL_TYPE, GameInterface.(CurTable).(CurRow).UserData.ID) > 1)
        {
			if (CurTable == "TABLE_SKILL_1")
			{
				start = 630;
				SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE,"B_SKILLDown",0, start ,445 + 35*(iSelected-1), start + 20, 445 + 36 + 35*(iSelected-1), 0);
			}
			else
			{
				start = 630;
				SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE,"B_SKILLDown",0, start ,735 + 35*(iSelected-1), start + 20,735 + 36 + 35*(iSelected-1), 0);
			}
			SetNodeUsing("B_SKILLDown", true);
        }
        if (GetSkillValue(xi_refCharacter, SKILL_TYPE, GameInterface.(CurTable).(CurRow).UserData.ID) < SKILL_MAX)
        {

            if (CurTable == "TABLE_SKILL_1")
			{
				start = 692;
				SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE,"B_SKILLUP",0, start,445 + 35*(iSelected-1),start+20,445 + 36 + 35*(iSelected-1), 0);
			}
			else
			{
				start = 692;
				SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE,"B_SKILLUP",0, start,735 + 35*(iSelected-1),start+20,735 + 36 + 35*(iSelected-1), 0);
			}
            SetNodeUsing("B_SKILLUP",  true);
        }
	}
	
	ok = sti(xi_refCharacter.skill.freeskill) > 0 || sti(xi_refCharacter.skill.FreeSPECIAL) > 0;
	if (ok && CurTable == "TABLE_SPECIAL")
	{
	    if (GetSkillValue(xi_refCharacter, SPECIAL_TYPE, GameInterface.(CurTable).(CurRow).UserData.ID) > 1)
        {
			start = 636;
			SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE,"B_SKILLDown",0, start ,157 + 35*(iSelected-1), start+20, 157 + 36 + 35*(iSelected-1), 0);
			SetNodeUsing("B_SKILLDown", true);
        }
        if (GetSkillValue(xi_refCharacter, SPECIAL_TYPE, GameInterface.(CurTable).(CurRow).UserData.ID) < SPECIAL_MAX)
        {
					start = 696;
			SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE,"B_SKILLUP",0, start,157 + 35*(iSelected-1),start+20,157 + 36 + 35*(iSelected-1), 0);
            SetNodeUsing("B_SKILLUP",  true);
        }
	}
	if (CurTable != "PERKTABLE_NEED") ExitPerkMenu();
}

///////////////////////////////////////  PERKS /////////////////////////
void CreatePerksPictures() {
	aref perks;
	makearef(perks, ChrPerksList.list);

	int perksNum = GetAttributesNum(perks);
	for (int i = 0; i < perksNum; i++) {
		aref perk = GetAttributeN(perks,i);
		string perkName = GetAttributeName(perk);
		string nodeName = "PERK_" + perkName;
		string bnodeName = "PERKBASE_" + perkName;
		if (CheckAttribute(&perk, "Hidden")) continue;
		if (!CheckAttribute(&perk, "cost")) continue;
		
		XI_MakeNode("resource\ini\interfaces\partials\perks.ini", "PICTURE", nodeName, 82);
		XI_MakeNode("resource\ini\interfaces\partials\perks.ini", "PICTURE", bnodeName, 81);
	}
	// RefreshPerksPictures();
	for (int x = 1; x < 9; x++)
	{
		SetFormatedText("TEXT_PERK_TREE_" + x, GetConvertStrB("perkTree" + GetTreeByIndex(x-1), "AbilityDescribe.txt"));
	}
}

void RefreshPerksPictures() {
	aref perks;
	makearef(perks, ChrPerksList.list);
	string currentPerks = "self";
	if (currentPerkTab == 2) currentPerks = "ship";

	for (int i = 0; i < GetAttributesNum(&perks); i++) {
		string pictureGroup = "PERKS_DISABLE";
		string pictureName  = "base";
		aref perk = GetAttributeN(&perks, i);
		string perkName = GetAttributeName(&perk);
		string nodeName = "PERK_" + perkName;
		string bnodeName = "PERKBASE_" + perkName;
		if (CheckAttribute(&perk, "Hidden")) continue;
		if (!CheckAttribute(&perk, "BaseType")) continue;
		bool perkShowing = perk.baseType == currentPerks;
		SetNodeUsing(bnodeName, perkShowing);
		SetNodeUsing(nodeName, perkShowing);
		if (!perkShowing) continue;

		SendMessage(&GameInterface,"lsll", MSG_INTERFACE_MSG_TO_NODE, bnodeName, 5, 0 );
		SendMessage(&GameInterface,"lsll", MSG_INTERFACE_MSG_TO_NODE, bnodeName, 4, argb(255,128,128,128));
		SendMessage(&GameInterface,"lsll", MSG_INTERFACE_MSG_TO_NODE, nodeName, 4, argb(255,128,128,128));

		switch(GetCharPerkInterfaceState(&xi_refCharacter, &perk))
		{
			case "active":
				pictureGroup = "PERKS_ENABLE";
				pictureName = "base_ship";
				if (perk.BaseType == "self") pictureName = "base_self";
				SendMessage(&GameInterface,"lsll", MSG_INTERFACE_MSG_TO_NODE, nodeName, 4, argb(255,128,128,128));
				SendMessage(&GameInterface,"lsll", MSG_INTERFACE_MSG_TO_NODE, bnodeName, 5, 1 );
			break;
			case "disabled":
				SendMessage(&GameInterface,"lsll", MSG_INTERFACE_MSG_TO_NODE, nodeName, 4,  argb(255,55,55,55));
				SendMessage(&GameInterface,"lsll", MSG_INTERFACE_MSG_TO_NODE, bnodeName, 4, argb(255,75,75,75));
			break;
			case "officer":
				pictureGroup = "PERKS_ENABLE";
				pictureName = "base_officer";
				SendMessage(&GameInterface,"lsll", MSG_INTERFACE_MSG_TO_NODE, bnodeName, 5, 1 );
			break;
			case "available":
				SendMessage(&GameInterface,"lsll", MSG_INTERFACE_MSG_TO_NODE, bnodeName, 4, argb(255,194, 183, 174));
			break;
		}

		SetNewGroupPicture(nodeName, pictureGroup, perkName);
		SetNewGroupPicture(bnodeName, pictureGroup, pictureName);
		HidePerkSelect();
	}
}


void ChoosePerk(string perkName)
{
	XI_WindowShow("PERKWINDOW", true);
	XI_WindowDisable("PERKWINDOW", false);

	aref perk;
	makearef(perk, ChrPerksList.list.(perkName));
	string reason = "";
	string descr = GetPerkDescribe(perk, xi_refCharacter);
	bool canTake = CanTakePerk(&xi_refCharacter, &perk, &reason);
	bool isAlreadyHave = reason == "alreadyHave";
	selectedPerk = perkName;

	SetFormatedText("PERKWINDOW_CAPTION", GetConvertStrB(perkName, "AbilityDescribe.txt"));

	string showingPrice = its(GetPerkPrice(perk));
	if (IsAlreadyHave || reason == "disabled") showingPrice = "";
	SetFormatedText("PERKPRICE", showingPrice);
	SetNodeUsing("PERKON", isAlreadyHave); // галочка уже есть
	SetSelectable("PERKACCEPT", canTake);  // кнопка взятия перка
	SetNewGroupPicture("PERKPICTURE", PERKPICTURE(isAlreadyHave), perkName); // иконка перка
	SetNewGroupPicture("PERKPICTURE_BASE", PERKPICTURE(isAlreadyHave), PERKPICTURE_BASE(isAlreadyHave, &perk)); // подложка перка
	int color = argb(255,128,128,128);
	if (canTake) color = argb(255,194, 183, 174);
	SendMessage(&GameInterface,"lsll", MSG_INTERFACE_MSG_TO_NODE, "PERKPICTURE_BASE", 4, color);
	SetPerkSelect();
	HideSkillChanger();

	int descriptorsQty = FillUpDescriptors(&perk);
	int x,y,x2,y2;
	XI_DeleteNode("PERKWINDOW_TEXT");
	XI_MakeNode("resource\ini\interfaces\abilities.ini", "FORMATEDTEXT", "PERKWINDOW_TEXT", 83);
	SetFormatedText("PERKWINDOW_TEXT", descr);
	GetNodePosition("PERKWINDOW_TEXT",&x,&y,&x2,&y2)
	if (descriptorsQty > 0) SetNodePosition("PERKWINDOW_TEXT", x, y, x2, y2);
	else SetNodePosition("PERKWINDOW_TEXT", x, y-30, x2, y2);

	AutoLayoutCenter("DESCRIPTOR_1|DESCRIPTOR_2|DESCRIPTOR_3|DESCRIPTOR_4", descriptorsQty);
	AutoLayoutCenter("DESCRIPTOR_1_VALUE|DESCRIPTOR_2_VALUE|DESCRIPTOR_3_VALUE|DESCRIPTOR_4_VALUE", descriptorsQty);
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
		xi_refCharacter.perks.FreePoints_self = sti(xi_refCharacter.perks.FreePoints_self) - GetPerkPrice(perkName);
	}
	else
	{
		xi_refCharacter.perks.FreePoints_ship = sti(xi_refCharacter.perks.FreePoints_ship) - GetPerkPrice(perkName);
    }
    if (SetCharacterPerk(xi_refCharacter, perkName))
    {   // перерисуем персонажа
    	FillSkillTables();
			SetVariable();
    }
    // перерисуем все -->
	SetFormatedText("TABSTR_SELF_PERKS", XI_ConvertString("Personal abilities") + "  -  " +xi_refCharacter.perks.FreePoints_self);
	SetFormatedText("TABSTR_SHIP_PERKS", XI_ConvertString("Ship abilities") + "  -  " + xi_refCharacter.perks.FreePoints_ship);
	RefreshPerksPictures();
	// if(currentScrollTab == 1) FillCharactersScrollEx(true);
	// else FillCharactersScrollEx(false);
	// FillPassengerScroll();
	// GameInterface.CHARACTERS_SCROLL.current = iCurrentNode;
	// SendMessage(&GameInterface,"lsl",MSG_INTERFACE_SCROLL_CHANGE,"CHARACTERS_SCROLL",-1);
	// // SetVariable();
	// перерисуем все <--
	// ExitPerkMenu();
	ChoosePerk(perkName);
}

void SetPerkSelect() {
	int sColor = argb(155,75,75,75);//серый
	string snodeName = "PERKSELECT_" + selectedPerk;
	if (selectedPerk != "") {
        XI_MakeNode("resource\ini\interfaces\partials\perks.ini", "PICTURE", snodeName, 83);
		SetNewGroupPicture("PERKSELECT_" + selectedPerk, "perks_enable", "select");
		if (CheckPerkFilter(xi_refCharacter, &selectedPerk)) {
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
	int nColor1 = ARGB_Color("offGrey");
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
			nColor1 = ARGB_Color("white");
		break;
		case 2:
			sPic2 = "TabSelected";
			sPic4 = "TabSelectedMark";
			nColor2 = ARGB_Color("white");
		break;
	}
    
	SetNewGroupPicture("TABBTN_SCROLL_1", "TABS", sPic1);
	SetNewGroupPicture("TABBTN_SCROLL_2", "TABS", sPic2);
	SetNewGroupPicture("TABBTN_SCROLL_1_MARK", "TABS", sPic3);
	SetNewGroupPicture("TABBTN_SCROLL_2_MARK", "TABS", sPic4);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_SCROLL_1", 8,0,nColor1);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_SCROLL_2", 8,0,nColor2);

	FillScrollControlsList(nMode);
	InterfaceStates.nCurScrollTab = nMode;
}

void SetPerksTabMode(int nMode)
{
	int nColor1 = ARGB_Color("offGrey");
	int nColor2 = ARGB_Color("offGrey");

	string sPic1 = "TabDeSelected";
	string sPic2 = sPic1;

	string sPic3 = sPic1;
	string sPic4 = sPic1;

	switch (nMode)
	{
		case 1:
			sPic1 = "TabSelected";
			sPic3 = "TabSelectedMark";
			nColor1 = ARGB_Color("white");
		break;
		case 2:
			sPic2 = "TabSelected";
			sPic4 = "TabSelectedMark";
			nColor2 = ARGB_Color("white");
		break;
	}

	SetNewGroupPicture("TABBTN_SELF_PERKS", "TABS", sPic1);
	SetNewGroupPicture("TABBTN_SHIP_PERKS", "TABS", sPic2);
	SetNewGroupPicture("TABBTN_SELF_PERKS_MARK", "TABS", sPic3);
	SetNewGroupPicture("TABBTN_SHIP_PERKS_MARK", "TABS", sPic4);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_SELF_PERKS", 8,0,nColor1);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_SHIP_PERKS", 8,0,nColor2);

	int start = 0;
	if (nMode == 2) start = 8; 
	for (int i = 0; i < 8; i++)
	{
		string treeName = DLGO(GetConvertStrB("perkTree" + GetTreeByIndex(i+start), "AbilityDescribe.txt"), &NullCharacter);
		SetFormatedText("TEXT_PERK_TREE_" + (i+1), treeName);
	}

	SetNodeUsing("PERK_TREES_SELF", nMode == 1);
	SetNodeUsing("PERK_TREES_SHIP", nMode == 2);

	currentPerkTab = nMode;
	RefreshPerksPictures();
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

void PopupIsShown()
{
	SetAllPerksSelectable(false);
	XI_WindowDisable("PERKWINDOW", true);
}

void PopupIsClosed()
{
	SetAllPerksSelectable(true);
	XI_WindowDisable("PERKWINDOW", false);
}

void TEST_InitReroll()
{
	SetNodeUsing("REROLL_BUTTON_COMMONER", bBettaTestMode);
	SetNodeUsing("REROLL_BUTTON_ELITE", bBettaTestMode);
	SetNodeUsing("REROLL_BUTTON_MINIBOSS", bBettaTestMode);
	SetNodeUsing("REROLL_BUTTON_BOSS", bBettaTestMode);
	SetNodeUsing("DESCRIP_TEXT_REROLL", bBettaTestMode);
	SetNodeUsing("FRAME_REROLL", bBettaTestMode);
	SetNodeUsing("RIGHTCHANGE_REROLL", bBettaTestMode);
	SetNodeUsing("LEFTCHANGE_REROLL", bBettaTestMode);
	SetFormatedTextButton("REROLL_BUTTON_COMMONER", "#Коммонер");
	SetFormatedTextButton("REROLL_BUTTON_ELITE", "#Элита");
	SetFormatedTextButton("REROLL_BUTTON_MINIBOSS", "#Минибосс");
	SetFormatedTextButton("REROLL_BUTTON_BOSS", "#Босс");
	SetFormatedText("DESCRIP_TEXT_REROLL", "Офицер");
}

void TEST_Reroll(string nodeName)
{
	int level;
	switch (nodeName)
	{
		case "REROLL_BUTTON_COMMONER": level = GEN_COMMONER; break;
		case "REROLL_BUTTON_ELITE":    level = GEN_ELITE;    break;
		case "REROLL_BUTTON_MINIBOSS": level = GEN_MINIBOSS; break;
		case "REROLL_BUTTON_BOSS":     level = GEN_BOSS;     break;
	}

	int rank = sti(pchar.rank);
	string mainArchetype = GEN_ARCHETYPE_RANDOM;
	string secondaryArchetype = GEN_ARCHETYPE_RANDOM;

	if (SetHeroAutolevel(xi_refCharacter)) ForceHeroAutolevel(xi_refCharacter);
	else ForceAdaptivelevel(xi_refCharacter, rank, GetAttributeInt(&GameInterface, "RerollMode"), level, mainArchetype, secondaryArchetype, GEN_FIXED_PIRATES, 0.5);
	SetVariable();
	string idx = GameInterface.CHARACTERS_SCROLL.current;
	SetControlsScrollTabMode(currentScrollTab);
	GameInterface.CHARACTERS_SCROLL.current = idx;
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_SCROLL_CHANGE, "CHARACTERS_SCROLL",-1);
}

void TEST_RerollChangeMode(int direction)
{
	int currentMode = GetAttributeInt(&GameInterface, "RerollMode");
	string text;
	currentMode = iClamp(0, 1, currentMode + direction);
	switch (currentMode)
	{
		case GEN_TYPE_OFFICER: text = "Офицер"; break;
		case GEN_TYPE_ENEMY: text = "Противник"; break;
	}
	GameInterface.RerollMode = currentMode;
	SetFormatedText("DESCRIP_TEXT_REROLL", text);
}

void TestRerollGiveOfficer()
{
	if (!bBettaTestMode) return;

	int _iComIndex = GetEventData();
	string sNodName = GetEventData();
	int index = sti(strright(sNodName, 1)) + 7;
	string job = GetTreeByIndex(index);

	if (job == "Background") RemoveCaptainOfficers(xi_refCharacter);
	else if (job == "Flags") GiveCaptainOfficers(xi_refCharacter, true);
	else
	{
		int score = makeint(GetSkillSum(xi_refCharacter) / 11 + 0.5);
		int perkPoints = makeint(score / 7);
		perkPoints = 3+rand(10);
		GiveCaptainVirtualOfficer(xi_refCharacter, perkPoints, score, job);
	}

	RefreshPerksPictures();
	SetVariable();
}