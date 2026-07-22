
void ProcessDialogEvent()
{
    int iTemp;
    object dlgContext;
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    int NPCNation = NPChar.Nation;
    string type = NPChar.CapType;
    bool bWar = (type == "War") || (type == "WarForeigner");
    string file = "Dialogs\Encounters\Visitor_Cap.txt";

	switch(Dialog.CurrentNode)
	{
		case "First time":
            // Alarm
            if (LAi_grp_playeralarm > 0.0)
            {
                NextDiag.TempNode = "First time";
                Dialog.text = DLG_Convert("VisitorCap_Alarm", file);
                link.l1 = DLG_Convert("VisitorCap_Alarm_Ok", file);
                link.l1.go = "Exit";
                break;
            }
            // Second node
            NextDiag.TempNode = "Quests";
            NPChar.Quest.meeting = "1";
            // Choose greeting
            bool bKnow = false;
            dlgContext.CityName = GetCityName(NPChar.City);
            dlgContext.CityNameAcc = XI_ConvertString("Colony" + NPChar.City + "Acc");
            iTemp = FindColony(NPChar.City);
            if (iTemp != -1 && bool(Colonies[iTemp].HeroOwn))
            {   // Свой город
                Dialog.text = DLG_Convert("VisitorCap_Hello_HeroOwn_" + type, file, &dlgContext);
                bKnow = true;
            }
            else if ("questTemp.Patria.GenGovernor" in PChar && NPCNation == FRANCE)
            {   // Генерал-губернатор
                Dialog.text = DLG_Convert("VisitorCap_Hello_GenGovernor" + type, file, &dlgContext);
                bKnow = true;
            }
            else if (bWar && IsMainCharacterPatented() && int(Items[int(PChar.EquipedPatentId)].TitulCur) > 4 && int(Items[int(PChar.EquipedPatentId)].Nation) == NPCNation)
            {   // Вице-адмирал
                Dialog.text = DLG_Convert("VisitorCap_Hello_War_ViceAdmiral" + type, file, &dlgContext);
                bKnow = true;
            }
            if (bWar && IsOfficerFullEquip() && int(Items[int(PChar.EquipedPatentId)].Nation) == NPCNation)
            {   // Офицер с патентом
                Dialog.text = DLG_Convert("VisitorCap_Hello_War_Officer" + type, file, &dlgContext);
            }
            else
            {
                Dialog.text = DLG_Convert("VisitorCap_Hello_" + type, file, &dlgContext);
            }
            link.l1 = DLG_Convert("VisitorCap_Hello_Answer_" + bKnow, file);
            link.l1.go = "Quests";
            link.l2 = DLG_Convert("VisitorCap_Bye_0", file);
            link.l2.go = "Exit";
		break;

        case "Quests":
            NextDiag.TempNode = "Quests";
            // Alarm
            if (LAi_grp_playeralarm > 0.0)
            {
                Dialog.text = DLG_Convert("VisitorCap_Alarm", file);
                link.l1 = DLG_Convert("VisitorCap_Alarm_Ok", file);
                link.l1.go = "Exit";
                break;
            }
            // Default talk
            Dialog.text = DLG_Convert("VisitorCap_Default_" + type, file);
            link.l1 = DLG_Convert("VisitorCap_link_Rumours", file);
            link.l1.go = "Rumours";
            if (type == "Trade")
            {
                link.l2 = DLG_Convert("VisitorCap_link_Price", file);
                link.l2.go = "Price_1";
            }
			link.l3 = DLG_Convert("VisitorCap_link_Advice", file);
			link.l3.go = "Advice";
			link.l4 = DLG_Convert("VisitorCap_link_Craft", file);
			link.l4.go = "Craft";
			link.l5 = DLG_Convert("VisitorCap_Bye_1", file);
			link.l5.go = "Exit";
        break;

        case "Rumours":
			NextDiag.TempNode = "Quests";
            string srum, answHero, blockText;
			srum = SelectRumourEx("landcaptain", NPChar);
            while(srum == NPChar.LastRumour$string(""))
                srum = GetRumourStub("landcaptain");
            NPChar.LastRumour = srum;
            blockText = DLG_Convert("VisitorCap_Rumours_Block", file);
            answHero = DLG_Convert("VisitorCap_Rumours_Answ", file);
			Dialog.Text = NPCStringReactionRepeat(srum, srum, srum, blockText, "block", 1, NPChar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(answHero, answHero, answHero, "", NPChar, Dialog.CurrentNode);
			link.l1.go = "Quests";
            bool bOk = int(NPChar.Quest.Repeat.Rumours.ans) != 3;
			link.l2 = bOk ? DLG_Convert("VisitorCap_Bye_2", file) : DLG_Convert("VisitorCap_Bye_3", file);
			link.l2.go = "Exit";
		break;

        case "Price_1":
			if (CheckNPCQuestDate(NPChar, "trade_date"))
			{
                SetNPCQuestDate(NPChar, "trade_date");
				iTemp = FindPriceStoreMan(NPChar);
	            if (iTemp == -1)
	            {
	                Dialog.Text = DLG_Convert("VisitorCap_NoPrice", file);
					link.l1 = DLG_Convert("VisitorCap_NoPrice_Ok", file);
					link.l1.go = "Exit";
	            }
	            else
	            {
                    sld = &Characters[iTemp];
                    PChar.PriceList.ShipStoreIdx = iTemp;
                    dlgContext.CityName = GetCityName(sld.City);
					Dialog.Text = DLG_Convert("VisitorCap_Price_1", file, &dlgContext);
					link.l1 = DLG_Convert("VisitorCap_Price_1_link_1", file);
					link.l1.go = "Price_2";
					link.l2 = DLG_Convert("VisitorCap_Price_1_link_2", file);
					link.l2.go = "Exit";
				}
			}
			else
			{
                Dialog.Text = DLG_Convert("VisitorCap_Price_1_Block", file);
				link.l1 = DLG_Convert("VisitorCap_Price_1_Block_Return", file);
				link.l1.go = "Quests";
				link.l2 = DLG_Convert("VisitorCap_Price_1_Block_Ok", file);
				link.l2.go = "Exit";
            }
		break;

		case "Price_2":
			PlaySound("interface\important_item.wav");
            sld = &Characters[int(PChar.PriceList.ShipStoreIdx)];
			SetPriceListByStoreMan(&Colonies[FindColony(sld.City)]);
			Dialog.Text = DLG_Convert("VisitorCap_Price_2", file);
			link.l1 = DLG_Convert("VisitorCap_Price_2_Return", file);
			link.l1.go = "Quests";
			link.l2 = DLG_Convert("VisitorCap_Price_2_Bye", file);
			link.l2.go = "Exit";
		break;

        case "Advice":
            if ("CapAdvice" !in NPChar)
            {
                Dialog.Text = DLG_Convert("VisitorCap_Advice_None_" + NPChar.NoAdv$string("0"), file);
                link.l1 = DLG_Convert("VisitorCap_Advice_Block_Return", file);
                link.l1.go = "Quests";
                link.l2 = DLG_Convert("VisitorCap_Advice_Block_Exit", file);
                link.l2.go = "Exit";
                NPChar.NoAdv = "1";
                break;
            }

            string sAdviceType = bWar ? "War" : type;
            if (NPChar.CapAdvice != "Block")
            {
                CapVisitors_AdviceBonus(NPChar);
                NPChar.CapAdvice = "Block";
                Dialog.Text = DLG_Convert("VisitorCap_Advice_" + sAdviceType, file);
                link.l1 = DLG_Convert("VisitorCap_Advice_Return", file);
                link.l1.go = "Quests";
                link.l2 = DLG_Convert("VisitorCap_Advice_Exit", file);
                link.l2.go = "Exit";
                break;
            }
            Dialog.Text = DLG_Convert("VisitorCap_Advice_Block_" + sAdviceType, file);
            link.l1 = DLG_Convert("VisitorCap_Advice_Block_Return", file);
            link.l1.go = "Quests";
            link.l2 = DLG_Convert("VisitorCap_Advice_Block_Exit", file);
            link.l2.go = "Exit";
        break;

        case "Craft":
            if (!CapVisitors_ItemCheck(NPChar))
            {
                Dialog.Text = DLG_Convert("VisitorCap_Craft_Nothing_" + NPChar.NoAnsw$string("0"), file);
                link.l1 = DLG_Convert("VisitorCap_Craft_Block_Return", file);
                link.l1.go = "Quests";
                link.l2 = DLG_Convert("VisitorCap_Craft_Block_Exit", file);
                link.l2.go = "Exit";
                NPChar.NoAnsw = "1";
                break;
            }
            if ("VisitorCapSold" in NPChar)
            {
                Dialog.Text = DLG_Convert("VisitorCap_Craft_Block", file);
                link.l1 = DLG_Convert("VisitorCap_Craft_Block_Return", file);
                link.l1.go = "Quests";
                link.l2 = DLG_Convert("VisitorCap_Craft_Block_Exit", file);
                link.l2.go = "Exit";
                break;
            }
            iTemp = NPChar.CapItem.Price;
            string ItemType = NPChar.CapItem.Type;
            bool bDublons = "CapItem.Price.Dublons" in NPChar;
            dlgContext.Item = LowerFirst(GetItemName(NPChar.CapItem));
            dlgContext.Price = bDublons ? FindRussianDublonString(iTemp) : FindRussianMoneyString(iTemp);
            Dialog.Text = DLG_Convert("VisitorCap_Craft_" + ItemType, file, &dlgContext);
            string mapAdd = "";
            if (ItemType == "Map")
                mapAdd = "_Map_" + (GetCharacterItem(PChar, NPChar.CapItem) > 0);
            if (bDublons ? PCharDublonsTotal() > iTemp : int(PChar.Money) > iTemp)
            {
                link.l1 = DLG_Convert("VisitorCap_Craft_Buy" + mapAdd, file);
                link.l1.go = "CraftBuy";
            }
			link.l2 = DLG_Convert("VisitorCap_Craft_Return", file);
			link.l2.go = "Quests";
            link.l3 = DLG_Convert("VisitorCap_Craft_Exit" + mapAdd, file);
            link.l3.go = "Exit";
        break;

        case "CraftBuy":
            NPChar.VisitorCapSold = "";
            iTemp = NPChar.CapItem.Price;
            if ("CapItem.Price.Dublons" in NPChar)
                RemoveDublonsFromPCharTotal(iTemp);
            else
                AddMoneyToCharacter(PChar, -iTemp);
            if (NPChar.CapItem == "MapPart")
                AddMapPart();
            else
                TakeNItems(PChar, NPChar.CapItem, int(NPChar.CapItem.Qty));
            Dialog.Text = DLG_Convert("VisitorCap_CraftBuy_" + NPChar.CapItem.Type, file);
			link.l1 = DLG_Convert("VisitorCap_CraftBuy_Return", file);
			link.l1.go = "Quests";
            link.l2 = DLG_Convert("VisitorCap_CraftBuy_Exit", file);
            link.l2.go = "Exit";
        break;

		case "CitizenNotBlade":
			dialog.text = DLG_Convert("VisitorCap_NoBlade", file);
			link.l1 = DLG_Convert("VisitorCap_NoBlade_Ok", file);
			link.l1.go = "Exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

// Метод из Capitans_dialog.c
int FindPriceStoreMan()
{
	int i, storeArray[40], howStore = 0;
	for(i = 0; i < MAX_CHARACTERS; i++)
	{
		if (Characters[i].Dialog.Filename$string("") == "Common_Store.c")
		{
            if (Characters[i].location == "none") continue;
            storeArray[howStore] = i;
            howStore++;
		}
    }
    return (howStore != 0) ? storeArray[hrand(howStore-1)] : -1;
}
