// Общая информация в шапке интерфейсов
void SetCommonHeaderInfo()
{
	string sIni = "resource\ini\interfaces\components\header.ini";
	XI_MakeNode(sIni, "FORMATEDTEXT", "MONEY", 100);
	XI_MakeNode(sIni, "FORMATEDTEXT", "Dublon", 100);
	XI_MakeNode(sIni, "IMAGECOLLECTION", "MONEY_ICON", 100);
	XI_MakeNode(sIni, "IMAGECOLLECTION", "WEIGHT_ICON", 100);
	
	if (CurrentInterface != INTERFACE_QUESTBOOK)
	{
		XI_MakeNode(sIni, "FORMATEDTEXT", "WEIGHT", 100);
		SetFormatedText("Weight", FloatToString(GetItemsWeight(&xi_refCharacter), 1) + " / " + GetMaxItemsWeight(&xi_refCharacter));
	}
	else
	{
		XI_DeleteNode("WEIGHT_ICON");
	}
	SetFormatedText("Money", FindRussianMoneyString(sti(xi_refCharacter.money)));

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
		SetNodeUsing("A_ABILITIES",true);
	}
	if(CheckQuestInfo() || CheckNewDocs()) SetNodeUsing("A_QUESTBOOK",true);
	if(CheckQuestInfo()) SetNodeUsing("A_QUEST",true);
	if(CheckNewDocs()) SetNodeUsing("A_INFO",true);
}