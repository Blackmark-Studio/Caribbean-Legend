// Общее для инвентаря и навыков поведение с переназначением офицеров/пассажиров

void FillPassengerScroll()
{
	string func;
	if (nCurScrollNum > 6 && nCurScrollNum < 10) func = "IsFellowAbleToGetBoarderJob";// слот абордажника
	else func = "IsFellowAbleToGetShipJob";// слот абордажника

	FillScrollWithCharacters(&NullCharacter, "PASSENGERSLIST", func, false, &nCurScrollOfficerNum, 1);
}

void OfficerChange()
{
	string attributeName = "pic" + (nCurScrollNum+1);

	if (nCurScrollNum > 6 && nCurScrollNum < 10 && !IsShipSafeReachableNow())
	{
		ShowError(xiStr("CantChangeOfficersNow"));
	}
	else if (GameInterface.CHARACTERS_SCROLL.(attributeName).character != "0")
	{
		int iCharacter = sti(GameInterface.CHARACTERS_SCROLL.(attributeName).character);
		xi_refCharacter = &characters[iCharacter];
		if (isOfficerInShip(xi_refCharacter, true) && xi_refCharacter.id != pchar.id)
		{
			CallWithConfirmation(xiStr("is remove officer"), "AcceptRemoveOfficer", true);
		}
	}
	else if (nCurScrollNum <= 9 && nCurScrollNum != 0)
	{
		FillPassengerScroll();
		SendMessage(&GameInterface,"lsl",MSG_INTERFACE_SCROLL_CHANGE,"PASSENGERSLIST",-1);
		SetCurrentNode("PASSENGERSLIST");
		ProcessFrame();
		SetOfficersSkills();

		XI_WindowShow("OFFICERS_WINDOW", true);
		XI_WindowDisable("OFFICERS_WINDOW", false);
		XI_WindowDisable("MAIN_WINDOW", true);
		SetCurrentNode("PASSENGERSLIST");

		Event("PopupIsShown");
	}
}

void ExitOfficerMenu()
{
	XI_WindowShow("OFFICERS_WINDOW", false);
	XI_WindowDisable("OFFICERS_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);
	GameInterface.strings.CharJob = "";
	SetCurrentNode("CHARACTERS_SCROLL");
	Event("PopupIsClosed");
}


void AcceptAddOfficer()
{
	int iCurrentNode = nCurScrollNum;
	bool bNeedFollow = false;
	bool bOk;
	ref rChar;
	
	string attributeName2 = "pic"+(nCurScrollOfficerNum+1);

    if (checkAttribute(&GameInterface, "PASSENGERSLIST."+attributeName2 + ".character"))
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
	Event(EVENT_CT_UPDATE_FELLOW, "a", &Characters[iChar]);
	ExitOfficerMenu();
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_SCROLL_CHANGE,"CHARACTERS_SCROLL",-1);
	ProcessFrame();
	SetVariable();
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
	Event(EVENT_CT_UPDATE_FELLOW, "a", &characters[iChar]);
	FillCharactersScrollEx(true);
	GameInterface.CHARACTERS_SCROLL.current = iCurrentNode;
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_SCROLL_CHANGE,"CHARACTERS_SCROLL",-1);
	SetVariable();
}

void SetOfficersSkills()
{
	string sCharacter = "pic" + (sti(GameInterface.PASSENGERSLIST.current) + 1);
	if (checkAttribute(&GameInterface, "PASSENGERSLIST." + sCharacter))
	{
		if (checkAttribute(&GameInterface, "PASSENGERSLIST." + sCharacter + ".character"))
		{
			sCharacter = GameInterface.PASSENGERSLIST.(sCharacter).character;
			ref otherchr = &characters[sti(sCharacter)];
			SetSPECIALMiniTable("TABLE_SMALLSKILL", otherchr);
			SetOTHERMiniTable("TABLE_SMALLOTHER", otherchr);
			SetFormatedText("OFFICER_NAME", GetFullName(otherchr));
			SetFormatedText("OFFICER_JOB", GetJobsList(otherchr, " / "));
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
