
string totalInfo = "";
bool isSkipable = false;
bool bEncType   = false;
bool bShowVideo; // для показа квестовых роликов, если будут
bool bEscDisable = false; // belamour для выхода из меню на ESC BigPatch
string  sQuestSeaCharId = "";

void InitInterface(string iniName)
{
	StartAboveForm(true);	
	// лочим квест и карту
    bQuestCheckProcessFreeze = true;
    bEncType = false; // обычный тип
    bShowVideo = false;
    
    GameInterface.title = "title_map";

    SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

    SetFormatedText("MAP_CAPTION", XI_ConvertString("title_map"));

	SetFormatedText("INFO_TEXT_QUESTION", XI_ConvertString("MapWhatYouWantToDo"));

	SetCurrentNode("INFO_TEXT_QUESTION");
	
	CalculateInfoData();

	SetFormatedText("INFO_TEXT",totalInfo);

	SetEventHandler("InterfaceBreak","ProcessBreakExit",0); // Выход на море
	SetEventHandler("exitCancel","ProcessCancelExit",0); // Выход на море по крестику или Esc
	SetEventHandler("ievnt_command","ProcCommand",0); // выход на карту только тут (по НЕТ)
	SetEventHandler("evntDoPostExit","DoPostExit",0); // выход из интерфейса
	
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
	//IDoExit( RC_INTERFACE_MAP_EXIT );
	//wdmReloadToSea();
	
	//belamour выход через ESC -->
	if (!bEscDisable) 
	{ 
		pchar.SkipEshipIndex = pchar.eshipIndex; 
		IDoExit(RC_INTERFACE_MAP_EXIT);
	}
	//<-- belamour BigPatch
}

void IDoExit(int exitCode)
{
	EndAboveForm(true);
	DelEventHandler("InterfaceBreak","ProcessBreakExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcCommand");
	DelEventHandler("evntDoPostExit","DoPostExit");
	
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
	string comName = GetEventData();
	string nodName = GetEventData();
	
	switch(nodName)
	{
		case "B_OK":
			if(comName=="activate" || comName=="click")
			{
				if (sQuestSeaCharId != "")
				{
					if(sQuestSeaCharId == "LadyBeth_cap")
					{
						pchar.SkipEshipIndex = pchar.eshipIndex;
						IDoExit(RC_INTERFACE_MAP_EXIT);
						break;
					}
					wdmEnterSeaQuest(sQuestSeaCharId);
				}
				if(CharacterIsAlive("LadyBeth_cap"))
				{
					ref sld = characterFromId("LadyBeth_cap");
					if(sld.quest == "InCity" && sld.City == "Shore16" && worldMap.island == "Caiman")
					{
						pchar.SkipEshipIndex = pchar.eshipIndex;
						IDoExit(RC_INTERFACE_MAP_EXIT);
						break;
					}
				}
				// напасть
				IDoExit(RC_INTERFACE_MAP_EXIT);
				wdmReloadToSea();
			}
			if(comName=="rightstep")
			{
				if(GetSelectable("B_CANCEL"))	{SetCurrentNode("B_CANCEL");}
			}
		break;

		case "B_CANCEL":
			if(comName=="activate" || comName=="click")
			{
				//пропустить
				//PostEvent("evntDoPostExit",1,"l",RC_INTERFACE_MAP_EXIT);
				pchar.SkipEshipIndex = pchar.eshipIndex;
				IDoExit(RC_INTERFACE_MAP_EXIT);
			}	
			if(comName=="leftstep")
			{
				if(GetSelectable("B_OK"))	{SetCurrentNode("B_OK");}
			}
		break;
	}
}
void wdmRecalcReloadToSea()
{
	worldMap.encounter.type = "";
	totalInfo = "";
	string loadScr = "";
	int iRand;
	//Encounters
	int numEncounters = wdmGetNumberShipEncounters();
	int isShipEncounterType = 0;
    bool bPowerCompare = true;
	string sOkBtn = XI_ConvertString("map_attack");
    ref rChar;
	//Log_TestInfo("Начинаем перебирать энкаунтеров");
	for(int i = 0; i < numEncounters; i++)
	{
		if(wdmSetCurrentShipData(i))
		{
			if(MakeInt(worldMap.encounter.select) == 0) continue;
			isShipEncounterType++;

			string encID = worldMap.encounter.id;

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
                iNumWarShips = GetCharacterIndex(rEncounter.CharacterID);
                if (iNumWarShips != -1)
                {
                    rChar = &characters[iNumWarShips];
					sQuestSeaCharId = rChar.id; // квестовый 
					if (CheckAttribute(rChar, "mapEnc.Name"))
					{
						totalInfo = totalInfo + characters[iNumWarShips].mapEnc.Name;
						//sOkBtn = XI_ConvertString("map_defend");
					}
					else
					{
						totalInfo = totalInfo + "'" + characters[iNumWarShips].ship.name + "'.";
					}
				}
				bEncType = true;
			}
			else
			{
                // Торговый караван 
                if(iRealEncounterType <= ENCOUNTER_TYPE_MERCHANT_LARGE)
                {
                    if(iNumWarShips == 0)
                        totalInfo = totalInfo + GetTextOnShipsQuantity(iNumMerchantShips) + XI_ConvertString("of traders");
                    else
                        totalInfo = totalInfo + XI_ConvertString("Trade caravan") + GetTextOnShipsQuantity(iNumMerchantShips) + XI_ConvertString("merchants in accompaniment") + GetTextOnSecondShipsQuantity(iNumWarShips) + XI_ConvertString("guards");
                }

                // Торговая экспедиция - Средняя
                if(iRealEncounterType == ENCOUNTER_TYPE_MERCHANT_CROWN)
                {
                    totalInfo = totalInfo + XI_ConvertString("Crown caravan") + GetTextOnShipsQuantity(iNumMerchantShips) + XI_ConvertString("merchants in accompaniment") + GetTextOnSecondShipsQuantity(iNumWarShips) + XI_ConvertString("guards");
                }

                // Торговая экспедиция - Большая
                if(iRealEncounterType == ENCOUNTER_TYPE_MERCHANT_EXPEDITION)
                {
                    totalInfo = totalInfo + XI_ConvertString("Trade expedition") + GetTextOnShipsQuantity(iNumMerchantShips) + XI_ConvertString("merchants in accompaniment") + GetTextOnSecondShipsQuantity(iNumWarShips) + XI_ConvertString("guards");
                }

                // Работорговцы
                if(iRealEncounterType == ENCOUNTER_TYPE_MERCHANT_SLAVES)
                {
                    totalInfo = totalInfo + XI_ConvertString("Slave traders") + GetTextOnShipsQuantity(iNumMerchantShips) + XI_ConvertString("merchants in accompaniment") + GetTextOnSecondShipsQuantity(iNumWarShips) + XI_ConvertString("guards");
                }

                // Патруль
                if(iRealEncounterType >= ENCOUNTER_TYPE_PATROL_SMALL && iRealEncounterType <= ENCOUNTER_TYPE_PATROL_MEDIUM)
                {
                    totalInfo = totalInfo + XI_ConvertString("Patrol") + GetTextOnShipsQuantity(iNumWarShips + iNumMerchantShips);
                }

                // Военная эскадра
                if(iRealEncounterType >= ENCOUNTER_TYPE_NAVAL_MEDIUM && iRealEncounterType <= ENCOUNTER_TYPE_NAVAL_LARGE)
                {
                    totalInfo = totalInfo + XI_ConvertString("Naval squadron") + GetTextOnShipsQuantity(iNumWarShips + iNumMerchantShips);
                }

                // Контрабандисты
                if(iRealEncounterType == ENCOUNTER_TYPE_SMUGGLERS)
                {
                   // TO_DO
                }

                // Пираты
                if(iRealEncounterType == ENCOUNTER_TYPE_PIRATE)
                {
                    totalInfo = totalInfo + XI_ConvertString("Pirates") + GetTextOnShipsQuantity(iNumWarShips + iNumMerchantShips);
                }

                // Бочонок
                if(iRealEncounterType == ENCOUNTER_TYPE_BARREL)
                {
                    bPowerCompare = false;
                    totalInfo = totalInfo + XI_ConvertString("SailingItems");
                }

                // Кораблекрушенец
                if(iRealEncounterType == ENCOUNTER_TYPE_BOAT)
                {
                    bPowerCompare = false;
                    totalInfo = totalInfo + XI_ConvertString("ShipWreck");
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
					case ENGLAND:		
						totalInfo = totalInfo + XI_ConvertString("under english flag");
					break;
					case FRANCE:		
						totalInfo = totalInfo + XI_ConvertString("under french flag");
					break;
					case SPAIN:		
						totalInfo = totalInfo + XI_ConvertString("under spanish flag");
					break;
					case HOLLAND:		
						totalInfo = totalInfo + XI_ConvertString("under dutch flag");
					break;
					case PIRATE:		
						totalInfo = totalInfo + ".";
					break;
				}
			}

			if(GetNationRelation2MainCharacter(sti(rEncounter.Nation)) != RELATION_ENEMY)
			{
				isSkipable = true;
			}
		}
	}
	//Log_TestInfo("isShipEncounterType :" + isShipEncounterType);

	if (isShipEncounterType > 1)
	{
		switch (rand(1))
		{
			case 0 :
				if(IsDay()) loadScr = "interfaces\le\sea_1.tga";
				else		loadScr = "interfaces\le\sea_2.tga";
			break;
			case 1 :
				loadScr = "interfaces\le\sea_3.tga";
			break;
		}
        bPowerCompare = false;
		SetNewPicture("INFO_PICTURE", loadScr); 
		totalInfo = XI_ConvertString("NavalSignal") + XI_ConvertString("battle on course") + totalInfo;
		sOkBtn = XI_ConvertString("map_join");
	}
	else
	{
		if(iRealEncounterType == ENCOUNTER_TYPE_BARREL || iRealEncounterType == ENCOUNTER_TYPE_BOAT)
		{		
			if(iRealEncounterType == ENCOUNTER_TYPE_BARREL) 
			{
				SetNewPicture("INFO_PICTURE", "interfaces\le\polundra.tga"); 
			}	
			if(iRealEncounterType == ENCOUNTER_TYPE_BOAT) 
			{
				SetNewPicture("INFO_PICTURE", "interfaces\le\flplndra.tga"); 
			}			
			totalInfo = XI_ConvertString("NavalSignal") + XI_ConvertString("SpecialSituation") + totalInfo;
			sOkBtn = XI_ConvertString("map_tobort");
		}
		else
		{
			switch (rand(1))
			{
				case 0:
					if(IsDay()) loadScr = "interfaces\le\sea_1.tga";
					else		loadScr = "interfaces\le\sea_2.tga";
				break;
				case 1:
					loadScr = "interfaces\le\sea_3.tga";
				break;
			}
			if(sQuestSeaCharId != "")
			{
				switch (sQuestSeaCharId)
				{
					case "SantaMisericordia_cap":
						SetNewPicture("INFO_PICTURE", "interfaces\le\sea_sm.tga");
						totalInfo = GetConvertStr("SM_WorldMap", "SantaMisericordia.txt");
						sOkBtn = XI_ConvertString("map_attack");
					break;

					case "LadyBeth_cap":
                        bPowerCompare = false;
						SetNewPicture("INFO_PICTURE", "interfaces\le\sea_lb.tga");
						totalInfo = GetConvertStr("LadyBeth_WorldMap", "LadyBeth.txt");
						sOkBtn = XI_ConvertString("map_ok");
					break;
					
					case "Memento_cap":
						SetNewPicture("INFO_PICTURE", "interfaces\le\sea_mem.tga");
						totalInfo = StringFromKey("Memento_4");
						sOkBtn = XI_ConvertString("map_attack");
					break;

                    case "MaryCelesteCapitan":
                        bPowerCompare = false;
						SetNewPicture("INFO_PICTURE", "interfaces\le\sea_cel.tga");
                        totalInfo = XI_ConvertString("NavalSignal") + XI_ConvertString("someone sails") + totalInfo;
                    break;

                    //default:
                        SetNewPicture("INFO_PICTURE", loadScr); 
                        if(CheckAttribute(rChar, "Brigadier"))
                        {
                            totalInfo = XI_ConvertString("NavalSignal") + XI_ConvertString("someone follows") + totalInfo + 
                                        StringFromKey("QuestsUtilite_278") + GetStrSmallRegister(XI_ConvertString(GetShipTypeName(rChar))) + 
                                        " '" + rChar.Ship.Name + "'.";
                        }
                        else
                            totalInfo = XI_ConvertString("NavalSignal") + XI_ConvertString("someone sails") + totalInfo;
                    //break;
				}
				//sQuestSeaCharId = ""; ~!~ WTF
			}
			else
			{
				SetNewPicture("INFO_PICTURE", loadScr); 
				totalInfo = XI_ConvertString("NavalSignal") + XI_ConvertString("someone sails") + totalInfo;
			}
		}
	}
	if(!isSkipable) sOkBtn = XI_ConvertString("map_defend");
    if(bPowerCompare)
    {
        totalInfo += NewStr() + XI_ConvertString("Battle difficulty") + GetBattleDifficulty(rEncounter); // Механика мощи
        if(bBettaTestMode) MapEncInfo(rEncounter, iRealEncounterType);
    }
	SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"B_OK",0, "#" + sOkBtn);
}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}

void CalculateInfoData()
{
	if (pchar.space_press == "1")
	{
		isSkipable = true;
	}
    wdmRecalcReloadToSea();
    
	/* if (pchar.space_press == "1")
	{
		isSkipable = true;
	} */
	SetCurrentNode("B_OK");
		
    SetSelectable("B_CANCEL",true);

	if (!isSkipable && !bBettaTestMode)
	{
		if (CheckOfficersPerk(pchar, "SailingProfessional"))
		{
			if (rand(100) > 75) {SetSelectable("B_CANCEL",false); bEscDisable = true;} // belamour BigPatch
        }
		else
		{
			if (rand(100) > 25) {SetSelectable("B_CANCEL",false); bEscDisable = true;} // belamour BigPatch
        }
	}
	if (pchar.space_press == "1") bEncType = false;
	
	if (bEncType && !bBettaTestMode) // спец тип не пропустить
	{
        SetSelectable("B_CANCEL",false);
		bEscDisable = true; // belamour BigPatch
	}
	pchar.space_press = 0;
}

void MapEncInfo(ref rEncounter, int iRealEncounterType)
{
    int i, qty;
    string sInfo;
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
    ref rTmpl = &EncountersTypes[iRealEncounterType];
    aref arShips, aShip;
    if(iRealEncounterType != ENCOUNTER_TYPE_ALONE)
    {
        sInfo += NewStr() + NewStr() + "TEMPLATE LOG" + NewStr();
        sInfo += "WorldMap model: " + rTmpl.worldMapShip + NewStr();
        sInfo += "Type: ";
        switch(sti(rTmpl.Type))
        {
            case ENCOUNTER_TRADE: sInfo += "Trade"; break;
            case ENCOUNTER_WAR:   sInfo += "War"; break;
            case ENCOUNTER_SPECIAL: sInfo += "Special"; break;
            //default:
                sInfo += "UNKNOWN";
        }
        sInfo += NewStr() + "Chance: " + rTmpl.Chance + NewStr();
        sInfo += "Слоты кораблей в шаблоне:";
        makearef(arShips, rTmpl.Ships);
        qty = GetAttributesNum(arShips);
        for(i = 0; i<qty; i++)
        {
            sInfo += NewStr() + "    " + (i) + ") ";
            aShip = GetAttributeN(arShips, i);
            sInfo += "Spec ";
            switch(sti(aShip.ShipSpec))
            {
                case SHIP_SPEC_UNIVERSAL: sInfo += "UNIVERSAL; "; break;
                case SHIP_SPEC_MERCHANT: sInfo += "MERCHANT; "; break;
                case SHIP_SPEC_RAIDER: sInfo += "RAIDER; "; break;
                case SHIP_SPEC_WAR: sInfo += "WAR; "; break;
                //default:
                    sInfo += "UNKNOWN; ";
            }
            sInfo += "Qty " + aShip.qMin + " - " + (sti(aShip.qMin) + sti(aShip.qMax) - sti(aShip.qMin)) + "; ";
            sInfo += "Cls " + aShip.cMin + " - " + (sti(aShip.cMin) + sti(aShip.cMax) - sti(aShip.cMin)) + "; ";
            sInfo += "Type " + aShip.Type + "; ";
        }
    }

    // ИНФА О КОРАБЛЯХ ТЕКУЩЕЙ ЭНКИ
    int iShipType, idx, num;
    sInfo += NewStr() + NewStr() + "Корабли текущей эночки:";
    if(CheckAttribute(rEncounter, "CharacterID"))
    {
        string sTemp;
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
                        if(!CheckAttribute(rChar, "index") || rChar.index == "none" || LAi_IsDead(rChar)) continue;
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
    else if(CheckAttribute(rEncounter, "ShipTypes"))
    {
        num = 0;
        makearef(arShips, rEncounter.ShipTypes);
        qty = GetAttributesNum(arShips);
        for(i = 0; i < qty; i++)
        {
            iShipType = GetAttributeValue(GetAttributeN(arShips, i));
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
