
int iMapTarget = -1;
string sTargetId = "";
string sOkBtn = "";
string totalInfo = "";
string powerInfo = "";
bool bPowerCompare = true;
bool bPlayerInit = false;
bool isSkipable = true;
bool QuestSkipOff = false;
bool bShowVideo; // для показа квестовых роликов, если будут

int iSubs[4] = {1, 2, 3, 4};
string sRedText = "";
string sGreenText = "";
int EscapeChance = -1;
int EscapeSummary = -1;
bool EscapeBlock = false;
bool bRollEscape = false;

string sQuestSeaCharId[10] = {"", "", "", "", "", "", "", "", "", ""};
int iQuestSeaCharQty = 0;

void InitInterface_I(string iniName, int eshipIndex)
{
    iMapTarget = eshipIndex; // Наша цель, либо наш преследователь
    bPlayerInit = (pchar.space_press == "1");
    EscapeBlock = CheckAttribute(&TEV, "EscapeBlock");
    sOkBtn = XI_ConvertString("map_closer");
	StartAboveForm(true);
	// лочим квест и карту
    bQuestCheckProcessFreeze = true;
    bShowVideo = false;

    GameInterface.title = "title_map";

    SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);
    SendMessage(&GameInterface, "lslff", MSG_INTERFACE_MSG_TO_NODE, "CIRCLE_PROGRESSBAR", 9, 0.0, 0.0);
    SetNodeUsing("CIRCLE_PROGRESSBAR", false);

    SetFormatedText("MAP_CAPTION", XI_ConvertString("NavalSignal"));

	SetFormatedText("INFO_TEXT_QUESTION", XI_ConvertString("MapWhatYouWantToDo"));

	SetCurrentNode("INFO_TEXT_QUESTION");

	CalculateInfoData();

	SetFormatedText("INFO_TEXT", totalInfo);
	int nStrings = GetNumberOfStringsInFormatedText("INFO_TEXT", totalInfo); // считаем сколько строк в форме
	if (nStrings < 7) // Запрет на скроллинг
	{
		SetNodeUsing("SCROLL_TEXT", false);
		SendMessage(&GameInterface,"lsl", MSG_INTERFACE_MSG_TO_NODE, "INFO_TEXT", 5); // выравниванием текст по центру
		SendMessage(&GameInterface,"lsll", MSG_INTERFACE_MSG_TO_NODE, "INFO_TEXT", 13, 1); //1 - запрет, 0 - нет
	}
	
	SetEventHandler("InterfaceBreak","ProcessBreakExit",0); // Выход на море
	SetEventHandler("exitCancel","ProcessCancelExit",0); // Выход на море по крестику или Esc
	SetEventHandler("ievnt_command","ProcCommand",0); // выход на карту только тут (по НЕТ)
	SetEventHandler("evntDoPostExit","DoPostExit",0); // выход из интерфейса
	SetEventHandler("ShowInfoWindow", "ShowInfoWindow", 0);
	SetEventHandler("HideInfoWindow", "HideInfoWindow", 0);
	
	EI_CreateFrame("INFO_BORDERS", 250,152,550,342);
	PlaySound("interface\" + LanguageGetLanguage() + "\_EvShip"+rand(1)+".wav");
}

void ProcessBreakExit()
{
	IDoExit( RC_INTERFACE_MAP_EXIT );
	wdmReloadToSea();
}

void ProcessCancelExit()
{
	if (isSkipable) IDoExit(RC_INTERFACE_MAP_EXIT);
}

void IDoExit(int exitCode)
{
	EndAboveForm(true);
	DelEventHandler("InterfaceBreak","ProcessBreakExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcCommand");
	DelEventHandler("evntDoPostExit","DoPostExit");
	DelEventHandler("ShowInfoWindow", "ShowInfoWindow");
	DelEventHandler("HideInfoWindow", "HideInfoWindow");

	TimeScaleCounter = 0; //boal
	if(IsPerkIntoList("TimeSpeed"))
	{	
		DelPerkFromActiveList("TimeSpeed");
	}

	interfaceResultCommand = exitCode;
	EndCancelInterface(true);

	PostEvent("StopQuestCheckProcessFreeze", 100);//boal 230804 заморозка проверки квестов
}

void ProcCommand()
{
    int i;
	string comName = GetEventData();
	string nodName = GetEventData();
	
	switch(nodName)
	{
		case "B_OK":
			if(comName=="activate" || comName=="click")
			{
				if (iQuestSeaCharQty != 0)
				{
                    bool bExit = false;
                    for(i = 0; i < iQuestSeaCharQty; i++)
                    {
                        if(sQuestSeaCharId[i] == "LadyBeth_cap") {
                            bExit = true;
                            break;
                        }
                    }
                    if(bExit)
					{
						IDoExit(RC_INTERFACE_MAP_EXIT);
						break;
					}
                    if(CharacterIsAlive("LadyBeth_cap"))
                    {
                        ref sld = characterFromId("LadyBeth_cap");
                        if(sld.quest == "InCity" && sld.City == "Shore16" && worldMap.island == "Caiman")
                        {
                            IDoExit(RC_INTERFACE_MAP_EXIT);
                            break;
                        }
                    }
                    for(i = 0; i < iQuestSeaCharQty; i++)
                    {
                        wdmEnterSeaQuest(sQuestSeaCharId[i]);
                    }
				}
				// напасть
                TEV.iTarget = iMapTarget;
				IDoExit(RC_INTERFACE_MAP_EXIT);
				wdmReloadToSea();
                DeleteAttribute(&TEV, "iTarget");
			}
			if(comName=="rightstep")
			{
				if(GetSelectable("B_CANCEL")) SetCurrentNode("B_CANCEL");
			}
		break;

		case "B_CANCEL":
			if(comName=="activate" || comName=="click")
			{
                if (bRollEscape)
                {
                    ShuffleSubs();
                    totalInfo = XI_ConvertString("map_maneuvers_" + iSubs[0]);
                    SetFormatedText("INFO_TEXT", totalInfo);
					SendMessage(&GameInterface,"lsl", MSG_INTERFACE_MSG_TO_NODE, "INFO_TEXT", 5); // выравниванием текст по центру
                    SetCurrentNode("INFO_TEXT_QUESTION");
                    SetNodeUsing("SCROLL_TEXT", false);
                    SendMessage(&GameInterface,"lsll", MSG_INTERFACE_MSG_TO_NODE, "INFO_TEXT", 13, 1);
                    SetNodeUsing("TRIGGER", false);
                    SetNodeUsing("INFO_PICTURE", false);
                    SetNodeUsing("CIRCLE_PROGRESSBAR", true);
                    SetSelectable("B_CANCEL", false);
                    SetSelectable("B_OK", false);
                    SetEventHandler("MapManeuvers", "ManeuversLoading", 0);
                    PostEvent("MapManeuvers", 0, "lllf", 0, 1, 0, 0.0);
                }
                else
                {
                    if (EscapeChance == 100) SuccessEscape();
                    IDoExit(RC_INTERFACE_MAP_EXIT);
                }
			}	
			if(comName=="leftstep")
			{
				if(GetSelectable("B_OK")) SetCurrentNode("B_OK");
			}
		break;
	}
}

void wdmRecalcReloadToSea()
{
	worldMap.encounter.type = "";
	totalInfo = "";
	powerInfo = "";
	string loadScr = "";
	int i, idx;
	int isShipEncounterType = 0;
    ref rChar;

    int numShips = 0;
    for(i = 0; i < COMPANION_MAX; i++)
    {
        idx = GetCompanionIndex(PChar, i);
        if (idx != -1) numShips++;
    }
	int numEncounters = wdmGetNumberShipEncounters();

    int  iPlayer = SendMessage(&worldMap, "l", MSG_GET_PLAYERSHIP_IDX);
    int  iSort[2];
    bool bSort[2];
    if (iMapTarget >= 0)
    {
        idx = 1;
        // Нумерация энок для wdmSetCurrentShipData, пропускает корабль игрока
        // wdmGetNumberShipEncounters возвращает кол-во энок без учёта игрока
        if (iMapTarget >= iPlayer) iMapTarget--;
        iSort[0] = iMapTarget;
    }
    else idx = 0;

    if (numEncounters > 0)
    {
        SetArraySize(&iSort, numEncounters);
        SetArraySize(&bSort, numEncounters);
        int j = 0;
        int numEncountersReal = numEncounters + (iPlayer != -1);
        // В этом цикле скипаем игрока
        for (i = 0; i < numEncountersReal; i++)
        {
            if (i == iPlayer) continue;

            bSort[j] = SendMessage(&worldMap, "ll", MSG_WORLDMAP_IS_ENEMY, i);
            if (j != iMapTarget && bSort[j])
            {
                iSort[idx] = j;
                idx++;
            }
            j++;
        }
        // В предыдущем уже скипали, поэтому здесь сразу проверяем
        for (i = 0; i < numEncounters; i++)
        {
            if (i != iMapTarget && !bSort[i])
            {
                iSort[idx] = i;
                idx++;
            }
        }
    }

    int BattleSecond = -1;
    bool bTargetInBattle = false;
	for(i = 0; i < numEncounters; i++)
	{
        if(numShips >= MAX_SHIPS_LOAD_FROM_WDM && BattleSecond == -1) break;
		if(wdmSetCurrentShipData(iSort[i]))
		{
			if(worldMap.encounter.select == "0") continue;
			isShipEncounterType++;

            // Если битва, то запрещаем break по MAX_SHIPS_LOAD_FROM_WDM для следующей итерации
            // Текущая логика создания энок гарантирует, что второй участник битвы будет в iSort[i+1]
            if (BattleSecond != -1) BattleSecond = -1; // Тут запрет снимется
            else BattleSecond = worldMap.encounter.attack;

			string encID = worldMap.encounter.id;
            if (i == 0 && iMapTarget >= 0)
            {
                sTargetId = encID;
                if(BattleSecond != -1) bTargetInBattle = true;
            }

			aref rEncounter;
			makearef(rEncounter, worldMap.encounters.(encID).encdata);

			int iRealEncounterType = sti(rEncounter.RealEncounterType);

			if (isShipEncounterType > 1 && iRealEncounterType < ENCOUNTER_TYPE_BARREL)
			{
			    totalInfo = totalInfo + XI_ConvertString("But in the same way");
			}

			int iNumMerchantShips = 0;
			int iNumWarShips = 0;
			if(CheckAttribute(rEncounter, "NumMerchantShips"))
			{
				iNumMerchantShips = sti(rEncounter.NumMerchantShips);
			}
			if(CheckAttribute(rEncounter, "NumWarShips"))
			{
				iNumWarShips = sti(rEncounter.NumWarShips);
			}

			if (CheckAttribute(rEncounter, "CharacterID"))
			{
                idx = GetCharacterIndex(rEncounter.CharacterID);
                if (idx != -1)
                {
                    rChar = &characters[idx];
                    iQuestSeaCharQty++;
					sQuestSeaCharId[iQuestSeaCharQty - 1] = rChar.id; // квестовый 
					if (CheckAttribute(rChar, "mapEnc.Name"))
                        totalInfo = totalInfo + rChar.mapEnc.Name;
					else
                        totalInfo = totalInfo + "'" + rChar.ship.name + "'.";
                    if (CheckAttribute(rChar, "SeaAI.Group.Name"))
                        numShips += Group_GetLiveCharactersNum(rChar.SeaAI.Group.Name);
                    if (CheckAttribute(rChar, "mapEnc.NoSkip"))
                    {
                        isSkipable = false;
                        QuestSkipOff = true;
                    }
                    if (CheckAttribute(rChar, "AlwaysEnemy"))
                    {
                        isSkipable = false;
                    }
				}
			}
			else
			{
                numShips += iNumWarShips + iNumMerchantShips;
                // Торговый караван 
                if(iRealEncounterType <= ENCOUNTER_TYPE_MERCHANT_LARGE)
                {
                    if(iNumWarShips == 0)
                        totalInfo = totalInfo + GetTextOnShipsQuantity(iNumMerchantShips) + XI_ConvertString("of traders");
                    else
                        totalInfo = totalInfo + XI_ConvertString("Trade caravan") + GetTextOnShipsQuantity(iNumMerchantShips) + XI_ConvertString("merchants in accompaniment") + GetTextOnSecondShipsQuantity(iNumWarShips) + XI_ConvertString("guards");
					if(iRealEncounterType < ENCOUNTER_TYPE_MERCHANT_LARGE)
						loadScr = "interfaces\le\worldmapenc\caravan.tga";
					else
						loadScr = "interfaces\le\worldmapenc\galeon.tga";
                }

                // Торговая экспедиция - Средняя
                else if(iRealEncounterType == ENCOUNTER_TYPE_MERCHANT_CROWN)
                {
                    totalInfo = totalInfo + XI_ConvertString("Crown caravan") + GetTextOnShipsQuantity(iNumMerchantShips) + XI_ConvertString("merchants in accompaniment") + GetTextOnSecondShipsQuantity(iNumWarShips) + XI_ConvertString("guards");
					loadScr = "interfaces\le\worldmapenc\galeon.tga";
                }

                // Торговая экспедиция - Большая
                else if(iRealEncounterType == ENCOUNTER_TYPE_MERCHANT_EXPEDITION)
                {
                    totalInfo = totalInfo + XI_ConvertString("Trade expedition") + GetTextOnShipsQuantity(iNumMerchantShips) + XI_ConvertString("merchants in accompaniment") + GetTextOnSecondShipsQuantity(iNumWarShips) + XI_ConvertString("guards");
					loadScr = "interfaces\le\worldmapenc\galeon.tga";
                }

                // Работорговцы
                else if(iRealEncounterType == ENCOUNTER_TYPE_MERCHANT_SLAVES)
                {
                    totalInfo = totalInfo + XI_ConvertString("Slave traders") + GetTextOnShipsQuantity(iNumMerchantShips) + XI_ConvertString("merchants in accompaniment") + GetTextOnSecondShipsQuantity(iNumWarShips) + XI_ConvertString("guards");
					loadScr = "interfaces\le\worldmapenc\slvtraders.tga";
                }

                // Патруль
                else if(iRealEncounterType >= ENCOUNTER_TYPE_PATROL_SMALL && iRealEncounterType <= ENCOUNTER_TYPE_PATROL_MEDIUM)
                {
                    totalInfo = totalInfo + XI_ConvertString("Patrol") + GetTextOnShipsQuantity(iNumWarShips + iNumMerchantShips);
					loadScr = "interfaces\le\worldmapenc\patrol.tga";
                }

                // Военная эскадра
                else if(iRealEncounterType >= ENCOUNTER_TYPE_NAVAL_MEDIUM && iRealEncounterType <= ENCOUNTER_TYPE_NAVAL_LARGE)
                {
                    totalInfo = totalInfo + XI_ConvertString("Naval squadron") + GetTextOnShipsQuantity(iNumWarShips + iNumMerchantShips);
					loadScr = "interfaces\le\worldmapenc\warfleet.tga";
                }

                // Контрабандисты
                else if(iRealEncounterType == ENCOUNTER_TYPE_SMUGGLERS)
                {
                   // TO_DO
                }

                // Пираты
                else if(iRealEncounterType == ENCOUNTER_TYPE_PIRATE)
                {
                    totalInfo = totalInfo + XI_ConvertString("Pirates") + GetTextOnShipsQuantity(iNumWarShips + iNumMerchantShips);
					loadScr = "interfaces\le\worldmapenc\pirates.tga";
                }

                // Бочонок
                else if(iRealEncounterType == ENCOUNTER_TYPE_BARREL)
                {
                    bPowerCompare = false;
                    totalInfo = totalInfo + XI_ConvertString("SailingItems");
					loadScr = "interfaces\le\worldmapenc\barrel.tga";
                }

                // Кораблекрушенец
                else if(iRealEncounterType == ENCOUNTER_TYPE_BOAT)
                {
                    bPowerCompare = false;
                    totalInfo = totalInfo + XI_ConvertString("ShipWreck");
					loadScr = "interfaces\le\worldmapenc\flplndra.tga";
                }
			}
			
			if(sti(rEncounter.Nation) < 0)
			{
        		totalInfo = totalInfo + "БАГА -1.";
      		}

			if(iRealEncounterType != ENCOUNTER_TYPE_BARREL && iRealEncounterType != ENCOUNTER_TYPE_BOAT)
			{
				switch(sti(rEncounter.Nation))
				{		        
					case ENGLAND: totalInfo = totalInfo + XI_ConvertString("under english flag"); break;
					case FRANCE:  totalInfo = totalInfo + XI_ConvertString("under french flag");  break;
					case SPAIN:   totalInfo = totalInfo + XI_ConvertString("under spanish flag"); break;
					case HOLLAND: totalInfo = totalInfo + XI_ConvertString("under dutch flag");   break;
					case PIRATE:  totalInfo = totalInfo + "."; break;
				}
			}

			if(bSort[iSort[i]] && GetNationRelation2MainCharacter(sti(rEncounter.Nation)) == RELATION_ENEMY)
			{   // Враждебный преследователь
				isSkipable = false;
			}
		}
	}

	if (isShipEncounterType > 1)
	{
        if (bTargetInBattle)
            loadScr = "interfaces\le\worldmapenc\battle.tga";
        else
        {
            switch (rand(1))
            {
                case 0 :
                    if(IsDay()) loadScr = "interfaces\le\worldmapenc\1.tga";
                    else		loadScr = "interfaces\le\worldmapenc\2.tga";
                break;
                case 1 :
                    loadScr = "interfaces\le\worldmapenc\3.tga";
                break;
            }
        }
        bPowerCompare = false; // TO_DO: Умный расчёт 
		SetNewPicture("INFO_PICTURE", loadScr); 
		totalInfo = XI_ConvertString("battle on course") + totalInfo;
		sOkBtn = XI_ConvertString("map_join");
	}
	else
	{
		if(iRealEncounterType == ENCOUNTER_TYPE_BARREL || iRealEncounterType == ENCOUNTER_TYPE_BOAT)
		{
			totalInfo = XI_ConvertString("SpecialSituation") + totalInfo;
			sOkBtn = XI_ConvertString("map_tobort");
		}
		else
		{
			if(sQuestSeaCharId[0] != "")
			{
				switch (sQuestSeaCharId[0])
				{
					case "SantaMisericordia_cap":
						loadScr = "interfaces\le\worldmapenc\sm.tga";
						totalInfo = GetConvertStr("SM_WorldMap", "SantaMisericordia.txt");
					break;

					case "LadyBeth_cap":
                        bPowerCompare = false;
						loadScr = "interfaces\le\worldmapenc\lb.tga";
						totalInfo = GetConvertStr("LadyBeth_WorldMap", "LadyBeth.txt");
						sOkBtn = XI_ConvertString("map_ok");
					break;
					
					case "Memento_cap":
						loadScr = "interfaces\le\worldmapenc\mem.tga";
						totalInfo = StringFromKey("Memento_4");
					break;

                    case "MaryCelesteCapitan":
                        bPowerCompare = false;
						loadScr = "interfaces\le\worldmapenc\cel.tga";
                        totalInfo = XI_ConvertString("someone sails") + totalInfo;
                    break;

                    case "Head_of_Gold_Squadron":
						loadScr = "interfaces\le\worldmapenc\goldfleet.tga";
                        totalInfo = XI_ConvertString("someone sails") + totalInfo;
                    break;

                    //default:
                        if(CheckAttribute(rChar, "mapEnc.Marker"))
                        {
                            switch(rChar.mapEnc.Marker)
                            {
                                case "Brigadier":
                                    switch(sti(rEncounter.Nation))
                                    {
                                        case ENGLAND:	loadScr = "interfaces\le\worldmapenc\chm.tga";	break;
                                        case FRANCE:	loadScr = "interfaces\le\worldmapenc\gr.tga";	break;
                                        case SPAIN:		loadScr = "interfaces\le\worldmapenc\elc.tga";	break;
                                        case HOLLAND:	loadScr = "interfaces\le\worldmapenc\mf.tga";	break;
                                    }
									totalInfo = XI_ConvertString("someone follows") + totalInfo + StringFromKey("QuestsUtilite_278") + GetStrSmallRegister(XI_ConvertString(GetShipTypeName(rChar))) + " '" + rChar.Ship.Name + "'.";
                                    break;

                                case "BigBrigadier":
                                    loadScr = "interfaces\le\worldmapenc\ams.tga";
									totalInfo = StringFromKey("QuestsUtilite_331");
                                    break;

                                case "BountyHunter":
									loadScr = "interfaces\le\worldmapenc\hunters.tga";
									totalInfo = XI_ConvertString("someone sails") + totalInfo;
                                    break;
                            }
                        }
                        else
                            totalInfo = XI_ConvertString("someone sails") + totalInfo;
                    //break;
				}
			}
			else
			{
				totalInfo = XI_ConvertString("someone sails") + totalInfo;
			}

			if(loadScr == "")
			{
				switch (rand(1))
					{
						case 0:
							if(IsDay()) loadScr = "interfaces\le\worldmapenc\1.tga";
							else		loadScr = "interfaces\le\worldmapenc\2.tga";
						break;
						case 1:
							loadScr = "interfaces\le\worldmapenc\3.tga";
						break;
					}
			}
		}

        SetNewPicture("INFO_PICTURE", loadScr);
	}
	if(!isSkipable) 
    {
        if (bPlayerInit) sOkBtn = XI_ConvertString("map_yes");
        else sOkBtn = XI_ConvertString("map_defend");
    }
    if(bPowerCompare)
    {
		int iBattleDifficulty = GetBattleDifficulty(rEncounter); // инт сложности
		string sBattleDifficulty = XI_ConvertString("Unknown dif");
		switch(iBattleDifficulty)
		{
			case 1: // Elementary dif
				sBattleDifficulty = "<color=255,255,255,255>" + XI_ConvertString("Elementary dif") + "</color>"; //обычный
			break;
			case 2: // Low dif
				sBattleDifficulty = "<color=255,128,255,128>" + XI_ConvertString("Low dif") + "</color>"; //зелёный
			break;
			case 3:// Medium dif
				sBattleDifficulty = "<color=255,255,245,155>" + XI_ConvertString("Medium dif") + "</color>"; //желтый
			break;
			case 4:// High dif
				sBattleDifficulty = "<color=255,240,175,95>" + XI_ConvertString("High dif") + "</color>"; //оранжевый
			break;
			case 5:// Fatal dif
				sBattleDifficulty = "<color=255,255,128,128>" + XI_ConvertString("Fatal dif") + "</color>"; //красный
			break;
		}
		powerInfo = XI_ConvertString("Battle difficulty") + sBattleDifficulty; // Механика мощи
		SetFormatedText("POWER_TEXT",powerInfo);
        if(bBettaTestMode) MapEncInfo(rEncounter, iRealEncounterType);
    }
    else 
    {
        SetNodeUsing("POWER_LINES", false);
    }
    SendMessage(&GameInterface, "lsls", MSG_INTERFACE_MSG_TO_NODE, "B_OK", 0, "#" + sOkBtn);
}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}

void CalculateInfoData()
{
    SetCurrentNode("B_OK");

    wdmRecalcReloadToSea();
	if (bPlayerInit || bBettaTestMode)
    {
        isSkipable = true;
        SetNodeUsing("TRIGGER", false);
    }
    if (!isSkipable)
    {
        sOkBtn = XI_ConvertString("map_escape");
        if (QuestSkipOff)
        {
            SetNodeUsing("TRIGGER", false);
            SetSelectable("B_CANCEL", false);
        }
        else
        {
            EscapeChance = CalculateEscapeChance();
            if(EscapeChance > 0)
            {
                if (EscapeChance != 100) bRollEscape = true;
            }
            else SetSelectable("B_CANCEL", false);
            if (!EscapeBlock) sOkBtn += " (" + EscapeChance + "%)";
        }
        SendMessage(&GameInterface, "lsls", MSG_INTERFACE_MSG_TO_NODE, "B_CANCEL", 0, "#" + sOkBtn);
    }
	int x1, y1, x2, y2;
	GetNodePosition("INFO_TEXT", &x1, &y1, &x2, &y2);
	if(!bPowerCompare) SetNodePosition("INFO_TEXT", x1, y1, x2, y2+45);
	pchar.space_press = 0;
}

void MapEncInfo(ref rEncounter, int iRealEncounterType)
{
    int i, qty;
    string sInfo, sTemp;
    ref rChar, rShip, rBaseShip;

    // БАЗОВАЯ ИНФА ПО ЭНКАУНТЕРУ
    switch(iRealEncounterType)
    {
        case ENCOUNTER_TYPE_ALONE: sInfo = "Alone / Quest / Custom"; break;
        case ENCOUNTER_TYPE_MERCHANT_SMALL: sInfo = "MERCHANT_SMALL"; break;
        case ENCOUNTER_TYPE_MERCHANT_MEDIUM: sInfo = "MERCHANT_MEDIUM"; break;
        case ENCOUNTER_TYPE_MERCHANT_LARGE: sInfo = "MERCHANT_LARGE"; break;
        case ENCOUNTER_TYPE_MERCHANT_CROWN: sInfo = "MERCHANT_CROWN"; break;
        case ENCOUNTER_TYPE_MERCHANT_EXPEDITION: sInfo = "MERCHANT_EXPEDITION"; break;
        case ENCOUNTER_TYPE_MERCHANT_SLAVES: sInfo = "MERCHANT_SLAVES"; break;
        case ENCOUNTER_TYPE_NAVAL_MEDIUM: sInfo = "NAVAL_MEDIUM"; break;
        case ENCOUNTER_TYPE_NAVAL_LARGE: sInfo = "NAVAL_LARGE"; break;
        case ENCOUNTER_TYPE_PATROL_SMALL: sInfo = "PATROL_SMALL"; break;
        case ENCOUNTER_TYPE_PATROL_MEDIUM: sInfo = "PATROL_MEDIUM"; break;
        case ENCOUNTER_TYPE_SMUGGLERS: sInfo = "SMUGGLERS"; break;
        case ENCOUNTER_TYPE_PIRATE: sInfo = "PIRATE"; break;
        case ENCOUNTER_TYPE_BARREL: sInfo = "BARREL"; break;
        case ENCOUNTER_TYPE_BOAT: sInfo = "BOAT"; break;
        //default:
            sInfo = "UNKNOWN";
    }
    float pcharPower = stf(PChar.Squadron.RawPower);
    sInfo = NewStr() + NewStr() + "ENC LOG" + NewStr() + "Encounter: " + sInfo + NewStr();
    sInfo += "Raw player power: " + fts(pcharPower, 2) + NewStr() + "Modified player power: " + fts(stf(PChar.Squadron.ModPower), 2) + NewStr();
    if(pcharPower == 0.0) pcharPower = 1.0;
    if(CheckAttribute(rEncounter, "CurPower"))
        sInfo += "Enc power: " + fts(stf(rEncounter.CurPower), 2) + NewStr() + "Ratio (Enc * 0.9 / Raw): " + fts(stf(rEncounter.CurPower) / pcharPower * 0.9, 2);
    else if(CheckAttribute(rEncounter, "Power"))
        sInfo += "Enc power: " + fts(stf(rEncounter.Power), 2) + NewStr() + "Ratio (Enc * 0.9 / Raw): " + fts(stf(rEncounter.Power) / pcharPower * 0.9, 2);
    else
        sInfo += "Enc power: UNKNOWN" + NewStr() + "Ratio: UNKNOWN";
    sInfo += NewStr() + XI_ConvertString("Battle difficulty") + GetBattleDifficulty(rEncounter);

    // ИНФА О ТЕКУЩЕМ СОСТОЯНИИ ШАБЛОНА ГЕНЕРАЦИИ
    int iShipType, idx, num;
    ref rTmpl = &EncountersTypes[iRealEncounterType];
    if(iRealEncounterType != ENCOUNTER_TYPE_ALONE)
    {
        sInfo += NewStr() + NewStr() + "TEMPLATE LOG" + NewStr();
        sInfo += "WorldMap model: " + rTmpl.worldMapShip + NewStr();
        sInfo += "Type: ";
        switch(sti(rTmpl.Type))
        {
            case ENCOUNTER_TRADE:   sInfo += "Trade";   break;
            case ENCOUNTER_WAR:     sInfo += "War";     break;
            case ENCOUNTER_SPECIAL: sInfo += "Special"; break;
            //default:
                sInfo += "UNKNOWN";
        }
        // sInfo += NewStr() + "Chance: " + rTmpl.Chance + NewStr();
        if (iRealEncounterType < WorldMapRandomEncQty)
        {
            int BitParams;
            sInfo += NewStr() + "Слоты кораблей в шаблоне:";
            for(i = 0; i < 4; i++)
            {
                switch (i)
                {
                    case 0:
                        BitParams = ENC_MERCHANT_SLOT[iRealEncounterType];
                        if (!BitParams) continue;
                        break;
                    case 1:
                        BitParams = ENC_WAR_SLOT[iRealEncounterType];
                        if (!BitParams) continue;
                        break;
                    case 2:
                        BitParams = ENC_RAIDER_SLOT[iRealEncounterType];
                        if (!BitParams) continue;
                        break;
                    case 3:
                        BitParams = ENC_UNIVERSAL_SLOT[iRealEncounterType];
                        if (!BitParams) continue;
                        break;
                }
                sInfo += NewStr() + "    " + (i) + ") ";
                sInfo += "Spec ";
                switch(i)
                {
                    case SHIP_SPEC_UNIVERSAL: sInfo += "UNIVERSAL; "; break;
                    case SHIP_SPEC_MERCHANT:  sInfo += "MERCHANT; ";  break;
                    case SHIP_SPEC_RAIDER:    sInfo += "RAIDER; ";    break;
                    case SHIP_SPEC_WAR:       sInfo += "WAR; ";       break;
                    //default:
                        sInfo += "UNKNOWN; ";
                }
                sInfo += "Qty " + and(BitParams, 15) + " - " + and(shr(BitParams, 4), 15) + "; ";
                sInfo += "Cls " + and(shr(BitParams, 8), 15) + " - " + and(shr(BitParams, 12), 15) + "; ";
            }
            BitParams = ENC_RANDOM_PARAMS[iRealEncounterType];
            if (BitParams)
            {
                sInfo += NewStr() + "    Есть рандом между слотами: ";
                if (and(BitParams, 1)) sInfo += " торговый ";
                if (and(shr(BitParams, 1), 1)) sInfo += " военный ";
                if (and(shr(BitParams, 2), 1)) sInfo += " рейдер ";
                if (and(shr(BitParams, 3), 1)) sInfo += " универсал ";
            }
        }
    }

    // ИНФА О КОРАБЛЯХ ТЕКУЩЕЙ ЭНКИ
    sInfo += NewStr() + NewStr() + "Корабли текущей эночки:";
    if(CheckAttribute(rEncounter, "CharacterID"))
    {
        ref chr = CharacterFromID(rEncounter.CharacterID);
        if(CheckAttribute(chr, "SeaAI.Group.Name"))
        {
            sTemp = chr.SeaAI.Group.Name;
            int	iGroupIndex = Group_FindGroup(sTemp);
            if (iGroupIndex > 0)
            {
                ref rGroup = Group_GetGroupByIndex(iGroupIndex);
                if (CheckAttribute(rGroup, "Quest"))
                {
                    aref aCompanions, aCharInfo;
                    makearef(aCompanions, rGroup.Quest);
                    qty = GetAttributesNum(aCompanions);
                    num = 0;
                    for(i = 0; i < qty; i++)
                    {
                        aCharInfo = GetAttributeN(aCompanions, i);
                        idx = sti(aCharInfo.index);
                        if(idx == -1) continue;
                        rChar = GetCharacter(idx);
                        if(LAi_IsDead(rChar)) continue;
                        iShipType = sti(rChar.Ship.Type);
                        if(iShipType == SHIP_NOTUSED) continue;
                        rShip = GetRealShip(iShipType);
                        rBaseShip = &ShipsTypes[sti(rShip.BaseType)];

                        num++;
                        sInfo += NewStr() + "    " + (num) + ") ";
                        sInfo += XI_ConvertString(rBaseShip.Name) + "; ";
                        sInfo += wdmGetSpec(sti(rBaseShip.Spec)) + "; ";
                        sInfo += rBaseShip.Class + " класс; ";
                        sInfo += fts(GetRealShipPower(rChar), 2) + " мощь";
                    }
                }
            }
        }
    }
    else if(CheckAttribute(rEncounter, "FixedShips"))
    {
        num = 0;
        aref arShip, arShips;
        makearef(arShips, rEncounter.FixedShips);
        qty = GetAttributesNum(arShips);
        for(i = 0; i < qty; i++)
        {
            arShip = GetAttributeN(arShips, i);
            iShipType = arShip.type;
            rBaseShip = &ShipsTypes[iShipType];

            num++;
            sInfo += NewStr() + "    " + (num) + ") ";
            sInfo += XI_ConvertString(rBaseShip.Name) + "; ";
            sInfo += wdmGetSpec(sti(rBaseShip.Spec)) + "; ";
            sInfo += rBaseShip.Class + " класс; ";
            sInfo += fts(GetBaseShipPower(iShipType), 2) + " мощь";
        }
    }

    trace(sInfo);
}

void ShowInfoWindow()
{
	string sCurrentNode = GetEventData();
	string sHeader, sText1, sText2, sText3, sText4, sPicture, sGroup, sGroupPicture;
	int iColor1, iColor2, iColor3, iColor4;
	int	picW = 128;
	int	picH = 128;

	switch (sCurrentNode)
	{
		case "B_CANCEL":
		    sHeader = XI_ConvertString("Factors");
            sText1 = "";
			iColor1 = argb(255,255,255,255);
			sText2 = sRedText;
			iColor2 = argb(255,255,255,255);
			sText3 = sGreenText;
			iColor3 = argb(255,255,255,255);
            if (!EscapeBlock) sText4 = XI_ConvertString("TotalSmall") + EscapeSummary;
            else sText4 = "";
			iColor4 = argb(255,255,255,255);
			sPicture = "";
		break;
	}

	CreateTooltipNew(sCurrentNode, sHeader, sText1, sText2, sText3, sText4, sPicture, sGroup, sGroupPicture, picW, picH, true);
}

void HideInfoWindow()
{
	CloseTooltipNew();
}

int CalculateEscapeChance()
{
    if (EscapeBlock)
    {
        sRedText = XI_ConvertString("EscapeBlock");
        return 0;
    }

    ref rChar, rShip;
    float fTemp;
    int i, idx, iShipType;
    int iCompQty = 0;
    int iWar = 0;   int iUniv = 0;      int iRaider = 0;  int iTrade = 0;
    int iSails = 0; int iLoadLight = 0; int iLoadHard = 0;

    int tradeShipModifier = -6;
    if (GetCharacterEquipByGroup(pchar, HAT_ITEM_TYPE) == "hat6") tradeShipModifier = -3;

    for(i = 0; i < COMPANION_MAX; i++)
    {
        idx = GetCompanionIndex(PChar, i);
        if (idx != -1)
        {
            iCompQty++;
            rChar = &Characters[idx];
            iShipType = sti(rChar.Ship.Type);
            if(iShipType == SHIP_NOTUSED) continue;
            rShip = GetRealShip(iShipType);
            // Тип
            switch (sti(rShip.Spec))
            {
                case SHIP_SPEC_MERCHANT:  iTrade  += tradeShipModifier; break;
                case SHIP_SPEC_UNIVERSAL: iUniv   += 8;   break;
                case SHIP_SPEC_RAIDER:    iRaider += 12;  break;
                case SHIP_SPEC_WAR:       iWar    += -10; break;
            }
            // Паруса
            fTemp = stf(rChar.ship.SP) / stf(rShip.SP);
            iSails += (MakeInt(100.0 - (fTemp * 100.0)) / 10) * -4;
            // Загруженность
            fTemp = MakeFloat(GetCargoLoad(rChar)) / MakeFloat(GetCargoMaxSpace(rChar));
            int indendantBonus = GetIntByCondition(CheckOfficersPerk(pchar, "Intendant"), 0, PERK_VALUE_INTENDANT);
            if (fTemp <= 0.4) iLoadLight += 10 + indendantBonus;
            else if (fTemp >= 0.7) iLoadHard += -12 + indendantBonus; 
        }
    }

    int iNegative = -100;
    sRedText = XI_ConvertString("EscapeNeg_0") + iNegative;
    if (iTrade != 0)
    {
        iNegative += iTrade;
        sRedText += NewStr() + XI_ConvertString("EscapeNeg_1") + iTrade;
        
    }
    if (iWar != 0)
    {
        iNegative += iWar;
        sRedText += NewStr() + XI_ConvertString("EscapeNeg_2") + iWar;
        
    }
    if (iSails != 0)
    {
        iNegative += iSails;
        sRedText += NewStr() + XI_ConvertString("EscapeNeg_3") + iSails;
    }
    if (iLoadHard != 0)
    {
        iNegative += iLoadHard;
        sRedText += NewStr() + XI_ConvertString("EscapeNeg_4") + iLoadHard;
    }
    if (sTargetId != "" && CheckAttribute(&worldMap, "encounters." + sTargetId + ".SpeedMod"))
    {
        iNegative += -1000;
        sRedText += NewStr() + XI_ConvertString("EscapeNeg_5") + -1000;
    }

    int iPositive = 0;
    // Удача
    i = GetCharacterSPECIAL(PChar, SPECIAL_L) * 4;
    iPositive += i;
    sGreenText = XI_ConvertString(SPECIAL_L) + ": " + i;
    // Скрытность
    i = MakeInt(90.0 * pow((MakeFloat(GetSkillAfterPenalty(PChar, SKILL_SNEAK))/100.0), 0.40));
    iPositive += i;
    sGreenText += NewStr() + XI_ConvertString(SKILL_SNEAK) + ": " + i;
    // Навигация
    int iSailing = GetSkillAfterPenalty(PChar, SKILL_SAILING);
    i = MakeInt(65.0 * pow((MakeFloat(iSailing)/100.0), 0.40));
    iPositive += i;
    sGreenText += NewStr() + XI_ConvertString(SKILL_SAILING) + ": " + i;
    // Навигация выше порога
    i = 1 * (iSailing - GetShipClassNavySkill(GetCharacterShipClass(PChar)));
    if (i > 0)
    {
        iPositive += i;
        sGreenText += NewStr() + XI_ConvertString("EscapePos_0") + i;
    }
    if (iRaider != 0)
    {
        iPositive += iRaider;
        sGreenText += NewStr() + XI_ConvertString("EscapePos_1") + iRaider;
        
    }
    if (iUniv != 0)
    {
        iPositive += iUniv;
        sGreenText += NewStr() + XI_ConvertString("EscapePos_2") + iUniv;
        
    }
    if (iLoadLight != 0)
    {
        iPositive += iLoadLight;
        sGreenText += NewStr() + XI_ConvertString("EscapePos_3") + iLoadLight;
    }
    if (CheckOfficersPerk(PChar, "SailingProfessional"))
    {
        iPositive += PERK_VALUE2_SAILING_PROFESSIONAL;
        sGreenText += NewStr() + GetConvertStr("SailingProfessional", "AbilityDescribe.txt") + ": " + PERK_VALUE2_SAILING_PROFESSIONAL;
    }
    if (CheckOfficersPerk(PChar, "LoneWolf") && GetCompanionQuantity(pchar) < 1)
    {
        iPositive += PERK_VALUE2_LONE_WOLF;
        sGreenText += NewStr() + GetConvertStr("LoneWolf", "AbilityDescribe.txt") + ": " + PERK_VALUE2_LONE_WOLF;
    }
    if (CheckCharacterItem(PChar, GetMapByArea(worldMap.island)))
    {
        iPositive += 14;
        sGreenText += NewStr() + XI_ConvertString("EscapePos_4") + 14;
    }
    if (iCompQty == 1 && GetCharacterShipClass(PChar) > 5)
    {
        iPositive += 15;
        sGreenText += NewStr() + XI_ConvertString("EscapePos_5") + 15;
    }

    EscapeSummary = iPositive + iNegative;
    return iClamp(0, 100, EscapeSummary);
}

void ManeuversLoading()
{
    int iRealDelta = GetEventData();
    int iDots = GetEventData();
    int iCurSub = GetEventData();
    float fRatio = GetEventData();
    int dltTime = GetRDeltaTime();

    fRatio += dltTime / 2000.0;
    if (fRatio > 1.0) 
    {
		SendMessage(&GameInterface, "lslff", MSG_INTERFACE_MSG_TO_NODE, "CIRCLE_PROGRESSBAR", 9, 0.0, PIm2);
        DelEventHandler("MapManeuvers", "ManeuversLoading");
        SetEventHandler("MapManeuvers", "ManeuversResult", 0);
        PostEvent("MapManeuvers", 0); // Следующий кадр
        return;
    }
    SendMessage(&GameInterface, "lslff", MSG_INTERFACE_MSG_TO_NODE, "CIRCLE_PROGRESSBAR", 9, 0.0, PIm2 * fRatio);

    if (iRealDelta > 250)
    {
        iRealDelta = 0;
        string dots = "";
        if (iDots == 3)      dots = "...";
        else if (iDots == 2) dots = "..";
        else if (iDots == 1) dots = ".";
        else
        {
            iCurSub = (iCurSub+1) % 4;
            totalInfo = XI_ConvertString("map_maneuvers_" + iSubs[iCurSub]);
        }
        SetFormatedText("INFO_TEXT", totalInfo + dots);
		SendMessage(&GameInterface,"lsl", MSG_INTERFACE_MSG_TO_NODE, "INFO_TEXT", 5); // выравниванием текст по центру
        iDots = (iDots+1) % 4;
    }

    iRealDelta += dltTime;
    PostEvent("MapManeuvers", 0, "lllf", iRealDelta, iDots, iCurSub, fRatio);
}

void ManeuversResult()
{
    bRollEscape = false;
    DelEventHandler("MapManeuvers", "ManeuversResult");
    if (EscapeChance <= rand(99))
    {
        AddCharacterExpToSkill(PChar, SKILL_SNEAK, 7);
        AddCharacterExpToSkill(PChar, SKILL_FORTUNE, 3);
        SetSelectable("B_OK", true);
        SetNodeUsing("CIRCLE_PROGRESSBAR", false);
        SetNodeUsing("INFO_PICTURE", true);
        // TO_DO: Особая пикча неудачного побега
        PlaySound("interface\sobitie_na_karte_001.wav");
        totalInfo = XI_ConvertString("map_escape_no");
        SetFormatedText("INFO_TEXT", totalInfo);
		SendMessage(&GameInterface,"lsl", MSG_INTERFACE_MSG_TO_NODE, "INFO_TEXT", 5); // выравниванием текст по центру
    }
    else
    {
        SuccessEscape();
        IDoExit(RC_INTERFACE_MAP_EXIT);
    }
}

void SuccessEscape()
{
    TEV.EscapeBlock = "";
    SetFunctionTimerCondition("wdmEscapeRefresh", 0, 0, 1, false);

    Notification(XI_ConvertString("map_escape_yes"), "Sneak");
    PlaySound("interface\s_korablami_001.wav");
	Achievment_SetStat(188, 1);

    // Замедление
    if (sTargetId != "")
    {
        if (CheckAttribute(&TEV, "EncSpeed." + sTargetId)) return; // Дважды не снижаем
        AddCharacterExpToSkill(PChar, SKILL_SNEAK, 10);
        AddCharacterExpToSkill(PChar, SKILL_FORTUNE, 5);
        // Обновить скорость
        float curSpeed = stf(worldMap.encounters.(sTargetId).kMaxSpeed);
        SendMessage(&worldMap, "lsf", MSG_WORLDMAP_SET_SPEED, sTargetId, curSpeed * 0.7);
        worldMap.encounters.(sTargetId).kMaxSpeed = curSpeed * 0.7;
        // Процессирование
        worldMap.encounters.(sTargetId).SpeedMod = "";
        TEV.EncSpeed.(sTargetId) = curSpeed;
        TEV.EncSpeed.(sTargetId).dLeft = 3;
        if (!CheckAttribute(PChar, "quest.wdmEncSpeedUpdate"))
            SetFunctionTimerCondition("wdmEncSpeedUpdate", 0, 0, 1, true);
    }
}

void ShuffleSubs()
{
    int i, j, tmp;
    for (i = 3; i > 0; i--)
    {
        j = rand(i);
        tmp = iSubs[i];
        iSubs[i] = iSubs[j];
        iSubs[j] = tmp;
    }
}
