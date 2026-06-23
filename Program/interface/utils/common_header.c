// Общая информация в шапке интерфейсов
void SetCommonHeaderInfo()
{
	string sIni = "resource\ini\interfaces\components\header.ini";
	XI_MakeNode(sIni, "FORMATEDTEXT", "MONEY", 100);
	XI_MakeNode(sIni, "FORMATEDTEXT", "Dublon", 100);
	XI_MakeNode(sIni, "IMAGECOLLECTION", "MONEY_ICON", 100);
	XI_MakeNode(sIni, "IMAGECOLLECTION", "WEIGHT_ICON", 100);
	XI_MakeNode(sIni, "PICTURE", "SEASON_ICON_BG", 100);
	XI_MakeNode(sIni, "PICTURE", "SEASON_ICON", 100);
	SetNewGroupPicture("SEASON_ICON", "SEASONS_ICONS", SZN_GetCurrentSeasonName());
	
	if (CurrentInterface != INTERFACE_QUESTBOOK)
	{
		XI_MakeNode(sIni, "FORMATEDTEXT", "WEIGHT", 100);
		SetFormatedText("Weight", FloatToString(GetItemsWeight(&xi_refCharacter), 1) + " / " + GetMaxItemsWeight(&xi_refCharacter));
	}
	else
	{
		XI_DeleteNode("WEIGHT_ICON");
	}
	SetFormatedText("Money", FindRussianMoneyString(int(xi_refCharacter.money)));

	int dublonQty = GetCharacterItem(&xi_refCharacter, "gold_dublon");
	if (IsMainCharacter(&xi_refCharacter))
	{
		int cabinDublon = CheckItemMyCabin("gold_dublon");
		dublonQty +=  cabinDublon;
	}

	string dublonStr = FindRussianDublonString(dublonQty);

	SetFormatedText("Dublon", dublonStr);

	SetAlertMarks(&xi_refCharacter);
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
		// if(!HaveAllPerks(chr, "any")) SetNodeUsing("A_ABILITIES",true);
		if (!CheckAttribute(&InterfaceStates, "markers." + chr.id)) SetNodeUsing("A_ABILITIES",true);
		if (HaveAllPerks(chr, "any")) SetNodeUsing("A_ABILITIES", false);
	}
	if(CheckQuestInfo() || CheckNewDocs()) SetNodeUsing("A_QUESTBOOK",true);
	if(CheckQuestInfo()) SetNodeUsing("A_QUEST",true);
	if(CheckNewDocs()) SetNodeUsing("A_INFO",true);
}

bool CommonHeaderTooltip(string currentNode, ref header, ref text, ref badText, ref goodText)
{
	switch (currentNode)
	{
		case "WEIGHT":
			header = XI_ConvertString("Weight");
			text = GetRPGText("Weight");
		break;
		case "MONEY":
			header = XI_ConvertString("Money");
			text = GetRPGText("Money");
		break;
		case "SEASON_ICON_BG":
			header = DLG_Convert("Node0_title", "StoryFrames\Seasons\Next" +SZN_GetCurrentSeasonName() + ".txt");
			text = DLG_Convert("Description", "StoryFrames\Seasons\Common.txt");

			aref currentSeason = GetAref(&SeasonSystem, "current", true);
			SZN_ShowModifiers(&currentSeason, &header, &text, &badText, &goodText, DLG_Convert("effects_current_title", "StoryFrames\Seasons\Common.txt"));
			CreateTooltipWithConfig(currentNode, header, text, badText, goodText, "", "", "", "", 0, 0, "SZN_TooltipConfigWhite");
			return true;
		break;
	}

	return false;
}