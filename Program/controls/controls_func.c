/************************************************************************************************
                              belamour функции упраления контролками (controls_func)
*************************************************************************************************/

void Process_Controls(string ControlName)
{
	// boal -->
 	aref  arItm;
    int   itmIdx;
	String itemID;
	bool bOk, bOk1;
	float kZoom;

	//if (bBettaTestMode) Log_QuestInfo(ControlName);
    // boal <--
	//trace("ProcessControls() : " + ControlName);
 	
	if (ControlName == "QuickSave") { MakeQuickSave(); }
	if (ControlName == "QuickLoad") { MakeQuickLoad(); }
	
    if (dialogRun) return;
	if (sti(InterfaceStates.Launched)==true) return;
	
	if (ControlName == "WhrPrevWeather")	{ Whr_LoadNextWeather(-1); }
	if (ControlName == "WhrNextWeather")	{ Whr_LoadNextWeather(1); }
	if (ControlName == "WhrUpdateWeather")	{ Whr_UpdateWeather(); }
	
	//if (ControlName == "Help") RunHelpChooser();

    // TO_DO: Перенести в движок
	if(XI_IsKeyPressed("alt") && !CheckAttribute(&objControlsState,"keygroups.AltPressedGroup"+"."+ControlName)) return;
	if(!XI_IsKeyPressed("alt") && CheckAttribute(&objControlsState,"keygroups.AltPressedGroup"+"."+ControlName)) return;
	
	if(bSeaActive && !bAbordageStarted)
	{
		switch(ControlName)
		{
			case "MainMenu": ProcessMainMenuKey();	break;
			case "Interface":
				ProcessInterfaceKey();
			break;

			case "Sea_CameraSwitch":  
				SeaCameras_Switch(); 
				ControlsDesc(); 
			break;
			
			case "FireCamera_Set":
				SeaCameras_SetFireCamera();
			break;
			
			case "Ship_Fire": Ship_DoFire(); break;

			case "Tele": Sea_ReloadStart(); break;
			
			case "FLT_LoadBalls" :
                Log_SetStringToLog(xiStr("msg_AIShip_1"));
                FLT_SendCommand(ControlName);
                return;
            break;
            case "FLT_LoadGrapes" :
                Log_SetStringToLog(xiStr("msg_AIShip_2"));
                FLT_SendCommand(ControlName);
                return;
            break;
            case "FLT_LoadChain" :
                Log_SetStringToLog(xiStr("msg_AIShip_3"));
                FLT_SendCommand(ControlName);
                return;
            break;
            case "FLT_LoadBombs" :
                Log_SetStringToLog(xiStr("msg_AIShip_4"));
                FLT_SendCommand(ControlName);
                return;
            break;			
            case "FLT_SailAway" :
                Log_SetStringToLog(xiStr("msg_AIShip_5"));
                FLT_SendCommand(ControlName);
                return;
            break;
            case "FLT_LowerSails" :
                Log_SetStringToLog(xiStr("msg_AIShip_6"));
                FLT_SendCommand(ControlName);
                return;
            break;
            case "FLT_ProtFlagship" :
                Log_SetStringToLog(xiStr("msg_AIShip_7"));
                FLT_SendCommand(ControlName);
                return;
            break;
		}
	}
	else
	{
		switch(ControlName)
		{
			case "MainMenu": ProcessMainMenuKey();	break;
			case "Interface":
				ProcessInterfaceKey();
			break;
			case "Tele": 
				StartQuickTeleport();
			break;
			case "TeleBack": Teleport(-1); break;
			case "Action":
				//DumpAttributes(loadedLocation/*loadedLocation.reload.reload1.x*/);
				//trace("Y: " + loadedLocation.reload.reload1.y);
				//trace("Z: " + loadedLocation.reload.reload1.z);
			break;
		}
	}

    // boal 27.11.03 time --> // belamour +/- на основную клавиатуру
  	if (ControlName=="TimeScaleFaster" || ControlName == "TimeScaleSlower" ||
		ControlName=="TimeScaleFasterBA" || ControlName=="TimeScaleSlowerBA" )
  	{
		//запрет ускорения под водой.
        if (CheckAttribute(loadedLocation, "type") && loadedLocation.type == "underwater") return; 
		if (CheckAttribute(pchar, "questTemp.NoFast")) return; //запрет ускорения
		DeleteAttribute(pchar, "pause");
		if (ControlName == "TimeScaleFaster" || ControlName=="TimeScaleFasterBA")
     	{
			if (TimeScaleCounter >= 12)
			{
			    TimeScaleCounter += 4;
			}
			else
			{
                if (TimeScaleCounter >= 4)
				{
				    TimeScaleCounter += 2;
				}
				else
				{
					TimeScaleCounter++;
				}
			}
		}
     	else
     	{
            if (TimeScaleCounter >= 16)
			{
			    TimeScaleCounter -= 4;
			}
			else
			{
                if (TimeScaleCounter >= 6)
				{
				    TimeScaleCounter -= 2;
				}
				else
				{
					TimeScaleCounter--;
				}
			}
		}
		if (true) // MOD_SKILL_ENEMY_RATE > 1) // запрет 0.25 скорости
        {
		   if (!bBettaTestMode && TimeScaleCounter < -2) TimeScaleCounter = -2;
		} 
        if (bDisableMapEnter)
        {
            if (TimeScaleCounter > 20) TimeScaleCounter = 20;
        }
        else
        {   // без боя
            if (bSeaActive && !bAbordageStarted )
            {
            	if (TimeScaleCounter > 28) TimeScaleCounter = 28; // море
            }
            else
            {
				/* if (IsEntity(&worldMap))
				{
					if (TimeScaleCounter > 28) TimeScaleCounter = 28;
				}
				else
				{
					if (TimeScaleCounter > 8) TimeScaleCounter = 8; // суша
				} */
            	if (TimeScaleCounter > 8) TimeScaleCounter = 8; // суша
            }
        }
		
     	float newTimeScale = 1 + (TimeScaleCounter)*0.25; // GetSeaTimeScale()
     	if (newTimeScale < 0) //don't wanna crash the game
     	{
        		TimeScaleCounter = -4;
        		newTimeScale = 0;
     	}
     	if (TimeScaleCounter == 0) //back to normal
     	{
        		SetTimeScale(1.0);
				TimeScale_Info("");
     	}
     	else
     	{
        	SetTimeScale(newTimeScale);
			TimeScale_Info("x" + newTimeScale);
     	}

        // TUTOR-ВСТАВКА
        if(TW_IsActive())
        {
            if(objTask.sea == "4_TimeScale" && TimeScaleCounter == 20)
            {
                objTask.sea = "5_TimeScale";
                TW_ColorWeak(TW_GetTextARef("TimeScale_plus"));
                itemID = StringFromKey("Tutorial_7", GKIC("TimeScaleSlowerBA", "Sailing3Pers"), GKIC("TimeScale", "Sailing3Pers"));
                TW_AddBottomText("TimeScale_minus", itemID, "Default");
				TW_RestartTimer();
                TW_RecalculateLayout();
            }
            else if(objTask.sea == "5_TimeScale" && TimeScaleCounter == 0)
            {
                TW_ColorWeak(TW_GetTextARef("TimeScale_minus"));
                TW_FinishSea_2_TimeScale();
            }
        }
	}
	// boal <--

	switch(ControlName)
	{
		case "SwitchCameraOffset":
			int iPreset = sti(locCamera.OffsetPreset.CurPreset);
			iPreset++;
			if(iPreset > 2)
				iPreset = 1;
			string sPreset = "preset"+iPreset;
			locCamera.offsetX = locCamera.OffsetPreset.(sPreset).x;
			locCamera.offsetY = locCamera.OffsetPreset.(sPreset).y;
			locCamera.offsetZ = locCamera.OffsetPreset.(sPreset).z;
			locCamera.OffsetPreset.CurPreset = iPreset;
		break;
		case "CharacterCamera_Forward":
			if(CheckAttribute(locCamera, "zoom.lock"))
				break;
			if(!CheckAttribute(locCamera, "zoom"))
				kZoom = 0.75;
			else
				kZoom = stf(locCamera.zoom);
			kZoom -= 0.05;
			if(kZoom < 0.5)
				kZoom = 0.5;
			locCamera.zoom = kZoom;
			locCameraSetRadius(stf(locCamera.maxRadius)*kZoom);
		break;

		case "CharacterCamera_Backward":
			if(CheckAttribute(locCamera, "zoom.lock"))
				break;
			if(!CheckAttribute(locCamera, "zoom"))
				kZoom = 0.75;
			else
				kZoom = stf(locCamera.zoom);
			kZoom += 0.05;
			if(!bBettaTestMode)
			{
				if(kZoom > 1.0) kZoom = 1.0;
			}
			locCamera.zoom = kZoom;
			locCameraSetRadius(stf(locCamera.maxRadius)*kZoom);
		break;

        case "TimeScale":
            DeleteAttribute(pchar, "pause");
			// if (loadedLocation.type == "Underwater") return; //запрет ускорения под водой.
			if(CheckAttribute(pchar, "questTemp.NoFast")) return; //запрет ускорения
			if(TimeScaleCounter != 0)
			{
				SetTimeScale(1.0);
				TimeScaleCounter = 0;
				TimeScale_Info("");
			}
			else
			{
				SetTimeScale(GetSeaTimeScale());
				TimeScaleCounter = 4;
				TimeScale_Info("x2");
			}

            // TUTOR-ВСТАВКА
            if(TW_IsActive())
            {
                if(objTask.sea == "2_TimeScale" && TimeScaleCounter != 0)
                {
                    objTask.sea = "3_TimeScale";
                    TW_ColorWeak(TW_GetTextARef("TimeScale_R_on"));
                    itemID = StringFromKey("Tutorial_5", GKIC("TimeScale", "Sailing3Pers"));
                    TW_AddBottomText("TimeScale_R_off", itemID, "Default");
                    TW_RecalculateLayout();
                }
                else if(objTask.sea == "3_TimeScale" && TimeScaleCounter == 0)
                {
                    objTask.sea = "4_TimeScale";
                    TW_ColorWeak(TW_GetTextARef("TimeScale_R_off"));
                    itemID = StringFromKey("Tutorial_6", GKIC("TimeScaleFasterBA", "Sailing3Pers"));
                    TW_AddBottomText("TimeScale_plus", itemID, "Default");
                    TW_RecalculateLayout();
                }
                else if(objTask.sea == "5_TimeScale" && TimeScaleCounter == 0)
                {
                    TW_ColorWeak(TW_GetTextARef("TimeScale_minus"));
                    TW_FinishSea_2_TimeScale();
                }
            }
		break;
	
		case "ChangeShowInterface":
				ChangeShowIntarface();
		break;
		
		case "TestShipCurrentSea":
			// пока не вытирать - нужно для всяческих тестов !!!!						
//			bOk = !bSeaActive;
//			bOk1 = bLandInterfaceStart && !LAi_IsFightMode(pchar);			
//			if(bOk || bOk1) 
//			{
//				pchar.chr_ai.energy = 0;
//				MakeSailDmg(1, 15.0);
//				GetAllSailsDamagePercent(pchar);
//				LaunchRepair(pchar);
//				TestShipInCurrentSea();
//			}
		break;
	
		case "VK_PAUSETimePause":
			if (!CheckAttribute(pchar, "pause"))
			{
				pchar.pause = true;
				SetTimeScale(0.0);
			    TimeScaleCounter = -3;
				// TimeScale_Info("Pause");
				TimeScale_Info(XI_ConvertString("Pause"));
			    // AddPerkToActiveList("TimeSpeed");
			}
			else
			{
                DeleteAttribute(pchar, "pause");
				SetTimeScale(1.0);	
				TimeScale_Info("");
				// DelPerkFromActiveList("TimeSpeed");
				TimeScaleCounter = 0;
			}
		break;

		case "BI_MapEnter":
			if(bMapEnter && IsEntity(&BattleInterface)) Sea_MapLoad();
		break;
		
		case "WMapCancel":
			if(IsEntity(&worldMap))
			{
				pchar.space_press = 1;
				DeleteAttribute(pchar, "SkipEshipIndex");// boal
			}
		break;
		
		case "Map_Best":
		//	if (bBettaTestMode) LaunchPaperMapScreen();
			if(CheckCharacterItem(PChar, "Map_Best") || bBettaTestMode) LaunchBestMapScreen();
		break;

		// --> ugeen
		case "Alchemy":
			CheckAlchemyRecipe();
			if(CheckAttribute(pchar,"alchemy.known") && bLandInterfaceStart && !LAi_IsFightMode(pchar))
			{
				LaunchAlchemyScreen();
			}
		break;
		// <-- ugeen
		// --> sith interface quick open
		case "Inventory":	
			if(bMenuEnter()) LaunchInventory();
		break;

		case "ShipState":				
			if(bMenuEnter()) LaunchShipState();
		break;

		case "QuestBook":				
			if(bMenuEnter()) LaunchQuestBook();
		break;

		case "MapView":
			if(bMenuEnter()) LaunchMapViewScreen();
		break;

		case "Abilities":				
			if(bMenuEnter()) LaunchAbilities();
		break;

		case "Nations":				
			if(bMenuEnter()) LaunchNationRelation();
		break;
		// <-- sith
		//--> belamour fasttravel
		
		case "Fast_port":
			HKT_Button(ControlName); 
		break;
		
		case "Fast_store":
			HKT_Button(ControlName);	
		break;
		
		case "Fast_Shipyard":
			HKT_Button(ControlName);
		break;
		
		case "Fast_tavern":
			HKT_Button(ControlName);
		break;
		
		case "Fast_townhall":
			HKT_Button(ControlName);
		break;
		
		case "Fast_bank":
			HKT_Button(ControlName);
		break;
		
		case "Fast_church":
			HKT_Button(ControlName);
		break;
		
		case "Fast_Brothel":
			HKT_Button(ControlName);
		break;
		
		case "Fast_PortOffice":
			HKT_Button(ControlName);
		break;
		
		case "Fast_prison":
			HKT_Button(ControlName);
		break;
		
		//экипировка
		case "HK_Musket":
			HKE_Button(ControlName); 
		break;
		
		case "HK_FencingL":
			HKE_Button(ControlName);
				
		break;
		
		case "HK_FencingS":
			HKE_Button(ControlName);
		break;
		
		case "HK_FencingH":
			HKE_Button(ControlName);	
		break;
		
		// боеприпас и лечебные зелья
		case "BulletChanger":
			BulletChanger();	
		break;
		
		case "PotionChanger":
			PotionChanger();	
		break;
		
		case "hk_Cabin":
			if(isShipInside(pchar.location) && bLandInterfaceStart) 
			{
				if(!chrDisableReloadToLocation || CheckShipSituation_GenQuest())
				{
					Return2SeaAfterCabin();
				}
			}
		break;
		//<-- belamour
		
		case "OfficersCharge":
			if(GetOfficersQuantity(pchar) > 0)
			{
				pchar.OfficerAttRange = 35.0;
				OfficersCharge();
				Log_Info(XI_ConvertString("OfficersCharge"));
			}	
		break;

		case "OfficersFollow":
			if(GetOfficersQuantity(pchar) > 0)
			{
				pchar.OfficerAttRange = 7.0;
				OfficersFollow();
				Log_Info(XI_ConvertString("OfficersFollow"));
			}	
		break;

		case "OfficersHold":
			if(GetOfficersQuantity(pchar) > 0)
			{
				pchar.OfficerAttRange = 7.0;
				OfficersHold();
				Log_Info(XI_ConvertString("OfficersHold"));
			}	
		break;
		
		case "ChrSwitchFightMode":
			if(SendMessage(pchar, "ls", MSG_CHARACTER_EX_MSG, "IsValidChangeMode"))
			{
				if(MusketPriority(pchar)) notification(XI_ConvertString("Swordsman_mode_Note"), "None");
				else notification(XI_ConvertString("Musketeer_mode_Note"), "None");
			}
		break;
		// boal -->
		/* case "ChrBackward": //ChrStrafeLeft ChrStrafeRight
            if (bLandInterfaceStart && LAi_IsFightMode(pchar))
            {
				pchar.chr_ai.energy = stf(pchar.chr_ai.energy) - 3;
 				if (stf(pchar.chr_ai.energy) < 0) pchar.chr_ai.energy = 0;
	        }
		break;
		
		case "ChrStrafeLeft":
            if (bLandInterfaceStart && LAi_IsFightMode(pchar))
            {
				pchar.chr_ai.energy = stf(pchar.chr_ai.energy) - 3;
 				if (stf(pchar.chr_ai.energy) < 0) pchar.chr_ai.energy = 0;
	        }
		break;
		
		case "ChrStrafeRight":
            if (bLandInterfaceStart && LAi_IsFightMode(pchar))
            {
				pchar.chr_ai.energy = stf(pchar.chr_ai.energy) - 3;
 				if (stf(pchar.chr_ai.energy) < 0) pchar.chr_ai.energy = 0;
	        }
		break; */
		
		case "BOAL_UsePotion": // boal KEY_C
            if (bLandInterfaceStart)
            {
				if(LAi_IsPoison(pchar)) 
				{
					if (UseBestPotion(pchar, true) == 0) 
					{
						if (UseBestPotion(pchar, false) == 0) 
						{
							Log_SetStringToLog(XI_ConvertString("No Potion Found"));
						}
					}
				}
				else 
				{
					if (UseBestPotion(pchar, false) == 0) 
					{
						if (UseBestPotion(pchar, true) == 0) 
						{
							Log_SetStringToLog(XI_ConvertString("No Potion Found"));
						}
					}
				}	
	        }
		break;
		
		// Warship 13.06.09 Выпить противоядие KEY_V
		case "UseAntidote":
			if(bLandInterfaceStart)
            {
				if(FindCharacterAntidote(PChar, &itemID)) // В itemID запишется ID предмета, который можно использовать
				{
					DoCharacterUsedItem(PChar, itemID);
					Log_info("Use antidote");
				}
			}
		break;
		
		case "Dolly":
			ref location = &Locations[FindLocation(pchar.location)];
			if (CheckAttribute(location, "dolly"))
			{
				bOk = (IsCharacterInLocator(pchar, "item", "dolly1")) || (IsCharacterInLocator(pchar, "item", "dolly2")) || (IsCharacterInLocator(pchar, "item", "dolly3"))
				if (CheckAttribute(location, "canteleport") && bOk && !CheckAttribute(pchar, "questTemp.LSC.MaryBye"))
				{
					if (CheckAttribute(pchar, "questTemp.NotTeleportation")) DoQuestCheckDelay("TalkSelf_Quest", 0.1);
					else
					{
					if (IsCharacterInLocator(pchar, "item", "dolly1")) sGlobalTemp = "dolly1";
					if (IsCharacterInLocator(pchar, "item", "dolly2")) sGlobalTemp = "dolly2";
					if (IsCharacterInLocator(pchar, "item", "dolly3")) sGlobalTemp = "dolly3";
					Dolly_TeleportStart();
				}
			}
			}
			if (CheckAttribute(location, "id") && location.id == "KhaelRoa_Treasure_Alcove") // калеуче
			{
				bOk = (IsCharacterInLocator(pchar, "teleport", "teleport0")) || (IsCharacterInLocator(pchar, "teleport", "teleport1")) || (IsCharacterInLocator(pchar, "teleport", "teleport2")) || (IsCharacterInLocator(pchar, "teleport", "teleport3")) || (IsCharacterInLocator(pchar, "teleport", "teleport4")) || (IsCharacterInLocator(pchar, "teleport", "teleport5")) || (IsCharacterInLocator(pchar, "teleport", "teleport6"))
				if (bOk)
				{
					if (IsCharacterInLocator(pchar, "teleport", "teleport0")) sGlobalTemp = "teleport0";
					if (IsCharacterInLocator(pchar, "teleport", "teleport1")) sGlobalTemp = "teleport1";
					if (IsCharacterInLocator(pchar, "teleport", "teleport2")) sGlobalTemp = "teleport2";
					if (IsCharacterInLocator(pchar, "teleport", "teleport3")) sGlobalTemp = "teleport3";
					if (IsCharacterInLocator(pchar, "teleport", "teleport4")) sGlobalTemp = "teleport4";
					if (IsCharacterInLocator(pchar, "teleport", "teleport5")) sGlobalTemp = "teleport5";
					if (IsCharacterInLocator(pchar, "teleport", "teleport6")) sGlobalTemp = "teleport6";
					Caleuche_TeleportStart();
				}
			}
		break;
		
		case "Ultimate_potion":
			if (CheckCharacterItem(pchar, "Ultimate_potion")) UltimatePotionEffect();
		break;
		
		case "WMapGetCoords":
			/*if(IsEntity(worldMap))
			{		
				Log_SetStringToLog("X = " + worldMap.playerShipX + " Z = " + worldMap.playerShipZ + " AY = " + worldMap.playerShipAY);
				Log_SetStringToLog("Текущие координаты : " + Map_GetRealCoordZ(makefloat(worldMap.playerShipZ)) + "  " + Map_GetRealCoordX(makefloat(worldMap.playerShipX)));
			}	*/
		break;

		case "Ship_GetPosition":
/*		
			if (bSeaActive && !bAbordageStarted)
			{
				if (CheckAttribute(pchar, "Ship.pos.x"))
				{
					//Log_SetStringToLog("X :" + pchar.ship.pos.x + " Y :" + pchar.ship.pos.y + " Z :" + pchar.ship.pos.z);
					Log_SetStringToLog("aX :" + pchar.ship.ang.x + " aY :" + pchar.ship.ang.y + " aZ :" + pchar.ship.ang.z);
					trace("aX :" + pchar.ship.ang.x + " aY :" + pchar.ship.ang.y + " aZ :" + pchar.ship.ang.z);
					//Log_SetStringToLog("Текущие координаты : " + Sea_GetRealCoordZ(makefloat(pchar.Ship.pos.z)) + "  " + Sea_GetRealCoordX(makefloat(pchar.Ship.pos.x)));	
				}	
			}	
*/			
		break;
				
        case "BOAL_ActivateRush":  // boal KEY_F
			if (bLandInterfaceStart && GetCharacterPerkUsing(pchar, "Rush") && CheckCharacterItem(pchar, "berserker_potion"))
            {
		        ActivateCharacterPerk(pchar, "Rush");
				PerkBerserkerReaction();
		    }
            else
            {
                if (bLandInterfaceStart && curKeyGroupName == "FightModeControls")
                {
                    PlaySound("interface\knock.wav");
                }
            }
	    break;

	    case "BOAL_DeadSearch":  // boal KEY_1
			if (bLandInterfaceStart)
            {
                itmIdx = Dead_FindCloseBody();
			    if (itmIdx != -1)
			    {
					Dead_OpenBoxProcedure();
				}
				else
				{
                    if(iControlsMode == 0)
					Log_info(XI_ConvertString("NoLoot")); // только в классической раскладке
				}
		    }
	    break;
	    
		case "BOAL_SetCamera":
		    // по F10
		    //CameraHoldPos();
		    if (MOD_BETTATESTMODE == "On")
		    {
                if(LoadSegment("Debuger.c"))
            	{
                    ActiveF10Control();
            		UnloadSegment("Debuger.c");
            	}
		    }
		break;

        case "BOAL_Control":
		    // по F11 вызывает окно отладчика
//			 ChangeShowIntarface();
			
		    if (MOD_BETTATESTMODE == "On" || MOD_BETTATESTMODE == "Test")
		    {
		       LaunchDebuderMenu();
		    }
			else
			{
				if(CheckAttribute(pchar,"goldenfleet.capname") && pchar.goldenfleet.capname == "") break;
				int CheatId = LanguageOpenFile("blackmark_cheat.txt");
				if(CheatId != -1)
				{
					if(LanguageConvertString(CheatId, "CheatStatus") == "on")
					{
						LaunchCheatsMenu();
					}
					LanguageCloseFile(CheatId);
				}
			}
			
		break;

		case "BOAL_Control3":
		    // по F9 вызывает окно отладчика			
		    if (MOD_BETTATESTMODE == "On")
		    {
		       //LaunchBoalDebugScreenSecond();
		    }
		break;

		case "LanternOnOff": // KEY_L фонарь
			if(CheckAttribute(pchar, "LanternOnChar") != 0)
			{
				if(CheckAttribute(pchar, "HandLight") == 0)
				{
					SendMessage(pchar, "lss", MSG_CHARACTER_EX_MSG, "HandLightOn", "lantern");  //установить переносной источник света
					SendMessage(pchar, "lsl", MSG_CHARACTER_EX_MSG, "UntieItem", 9);
					SendMessage(pchar, "lslssl", MSG_CHARACTER_EX_MSG, "TieItem", 9, "lantern_belton", "Lantern_belt",1);
					pchar.HandLight = true;
				} 
				else 
				{
					SendMessage(pchar, "ls", MSG_CHARACTER_EX_MSG, "HandLightOff");  //убрать переносной источник света
					SendMessage(pchar, "lsl", MSG_CHARACTER_EX_MSG, "UntieItem", 9);
					SendMessage(pchar, "lslssl", MSG_CHARACTER_EX_MSG, "TieItem", 9, "lantern_beltoff", "Lantern_belt",1);
					DeleteAttribute(pchar, "HandLight");
				}
			}
		break;
		
		case "Person_Say": // KEY_T
			// Интерфейс отдыха
			/*if(bLandInterfaceStart) // В "Мыслях вслух"
				LaunchTavernWaitScreen();*/
		break;
			
		case "Say": // KEY_Y
			// Интерфейс автозакупки товаров
			if(bLandInterfaceStart && CheckFunctionalTreasurer() && CheckAttribute(PChar, "TransferGoods.Enable")) // Если есть казначей, включена автозакупка и ГГ находится на суше
				LaunchTransferGoodsScreen();
		break;
        
        case "TeleportActive":
		    if (MOD_BETTATESTMODE == "On")
		    {
                if(LoadSegment("Debuger.c"))
            	{
                    ActiveF4Control();
            		UnloadSegment("Debuger.c");
            	}
		    }
		break;
		
		case "BOAL_ControF5":		
		    if (MOD_BETTATESTMODE == "On")
		    {
                if(LoadSegment("Debuger.c"))
            	{
                    ActiveF5Control();
            		UnloadSegment("Debuger.c");
            	}
		    }
			else
			{
				//Statistic_AddValue(PChar, "Cheats.F5", 1);
			}			
		break;

		case "BOAL_ControF7":
		    // по F7 вызывает окно отладчика
		    if (MOD_BETTATESTMODE == "On")
		    {
                if(LoadSegment("Debuger.c"))
            	{
                    ActiveF7Control();
            		UnloadSegment("Debuger.c");
            	}
		    }
			else
			{
				//Statistic_AddValue(PChar, "Cheats.F7", 1);
			}			
		break;

        case "BOAL_Control2": // F12		
            //Найти ближайшего видимого персонажа в заданном радиусе				
            if(LoadSegment("Debuger.c"))
        	{
                ActiveF12Control(); // можно меять пряв в рабочей игре
        		UnloadSegment("Debuger.c");
        	}					
        break;

        case "BOAL_ControlDebug": // VK_INSERT
		
            if (MOD_BETTATESTMODE == "On")
		    {
				// Whr_TestShipLights();
				// LaunchDebugWhr();
                //SetLaunchFrameFormParam("Прошли долгие дни...", "", 0, 6);
                //LaunchFrameForm();
        	}
        break;

		case "FreeCam":
			if(!bBettaTestMode) break;
            locCameraEnableFree = !locCameraEnableFree;
			if(locCameraEnableFree) Log_info("FreeCam On. Press TAB");
			else Log_info("FreeCam Off");
		break;
		// boal <--		
		// sith работа с ветром -->
		case "WindAngleIncrease": // смена угла ветра +
			if(bBettaTestMode && bSeaActive && !bAbordageStarted)
			{
				Weather.Wind.Angle = stf(Weather.Wind.Angle) + 0.1;
				pchar.wind.angle = Weather.Wind.Angle;
				fWeatherAngle = stf(Weather.Wind.Angle);
				WhrCreateSeaEnvironment();
			}
		break;

		case "WindAngleDecrease": // смена угла ветра -
			if(bBettaTestMode && bSeaActive && !bAbordageStarted)
			{
				Weather.Wind.Angle = stf(Weather.Wind.Angle) - 0.1;
				pchar.wind.angle = Weather.Wind.Angle;
				fWeatherAngle = stf(Weather.Wind.Angle);
				WhrCreateSeaEnvironment();
			}
		break;

		case "WindIncrease": // смена силы ветра +
			if(bBettaTestMode && bSeaActive && !bAbordageStarted)
			{
				Weather.Wind.Speed = stf(Weather.Wind.Speed) + 1.0;
				pchar.wind.speed = Weather.Wind.Speed;
				fWeatherSpeed = stf(Weather.Wind.Speed);
				WhrCreateSeaEnvironment();
			}
		break;

		case "WindDecrease": // смена силы ветра -
			if(bBettaTestMode && bSeaActive && !bAbordageStarted)
			{
				Weather.Wind.Speed = stf(Weather.Wind.Speed) - 1.0;
				pchar.wind.speed = Weather.Wind.Speed;
				fWeatherSpeed = stf(Weather.Wind.Speed);
				WhrCreateSeaEnvironment();
			}
		break;
		// <--
	}
}



void HKT_Button(string sHKB) // быстрый переход
{
	int curLocIdx, i; 
	String locID, sCityID;
	bool bOk;
	
	curLocIdx = FindLoadedLocation();
	sCityID = Locations[curLocIdx].fastreload;
	locID = strcut(sHKB, 4 , strlen(sHKB)-1);
	// --> проверка запретов перехода
	bOk = true;
	if(LAi_group_IsActivePlayerAlarm()) bOk = false;
	if(!LAi_IsCharacterControl(pchar)) bOk = false;
	if(bDisableFastReload)	bOk = false;
	if(!IsEnableFastTravel()) bOk = false;
	if (chrDisableReloadToLocation) bOk = false;
	if (sHKB != "Fast_port" && !CheckFastJump(Locations[curLocIdx].id, sCityID + locID)) bOk = false;
	if (sHKB == "Fast_port" && !CheckFastJump(Locations[curLocIdx].id, pchar.location.from_sea)) bOk = false;
	if (!bBettaTestMode && bOk && !CheckAttribute(pchar, "Cheats.LocTeleport")) // проверка города на враждебность
	{
		string sNation = Colonies[FindColony(loadedLocation.fastreload)].nation;
		if (sNation != "none")
		{
			i = sti(sNation);
			bOk = (GetNationRelation2MainCharacter(i) == RELATION_ENEMY) || GetRelation2BaseNation(i) == RELATION_ENEMY;
			if (bOk && (i != PIRATE))
			{
				bOk = false;
			}
			else
			{
				bOk = true;
			}
		}
		if(CheckNationLicence(HOLLAND)) bOk = true;
	}
	// <--
	if(bOk)
	{
		if (sHKB == "Fast_port")
			PlayerFastTravel(curLocIdx, pchar.location.from_sea, "reload1");
			else PlayerFastTravel(curLocIdx, sCityID + locID, "");
	}	
	if(pchar.location == sCityID + locID) {Log_info(XI_ConvertString("You are already there")); PlaySound("interface\knock.wav");}
	if (sHKB == "Fast_port" && pchar.location == pchar.location.from_sea) {Log_info(XI_ConvertString("You are already there")); PlaySound("interface\knock.wav");}
}	

void HKE_Button(string sHKB) // мушкет и клинки
{
	return;
	string sGun, sItem, sBlade, BladeType, BladeInfo;
	ref rItem;
	aref aGun, arItems; 
	bool bOk;
	int i, p, iItemsNum; 

	int n = 0;
	
	BladeType = strcut(sHKB, 3 , strlen(sHKB)-1);
	sBlade = ""; 
	bOk = true;
	if(loadedLocation.type == "underwater") bOk = false;
	if(!LAi_IsCharacterControl(pchar)) bOk = false;
	
	if(bOk)
	{
		if (sHKB == "HK_Musket")
		{
			makearef(arItems, pchar.items);
			iItemsNum = GetAttributesNum(arItems);
			for(i=0; i<iItemsNum; i++)
			{
				sItem = GetAttributeName(GetAttributeN(arItems, i));
				rItem = ItemsFromID(sItem);
				if(!CheckAttribute(rItem, "groupID")) continue;
				if(rItem.groupID != MUSKET_ITEM_TYPE) continue;
				//if(!HasSubStr(rItem.id, "mushket")) continue;
				if(!CheckAttribute(rItem,"chargeQ")) continue;
				int chrgQ = sti(rItem.chargeQ);
				bool bGP = and(chrgQ >= 2, IsCharacterPerkOn(pchar,"GunProfessional")) || chrgQ < 2;
				if(!bGP) continue;
				if(sItem != "") 
				{
					p = GunNum();		 
					n++;
					if(n == p-1)
					{
						sGun = sItem; 
						Items_FindItem(sGun, &aGun);
						break;
					}
					sGun = sItem; 
					Items_FindItem(sGun, &aGun);
				}
			}
			
			
			if(sGun != "" && IsCharacterPerkOn(pchar,"Gunman") && CanEquipMushketOnLocation(PChar.Location))
			{
				SetMainCharacterToMushketer(sGun, true);
				GunCharging(pchar, MUSKET_ITEM_TYPE, sGun);
				log_info("Gun selected: "+GetConvertStr("itmname_"+sGun, "ItemsDescribe.txt")+"");
				/* DoQuestCheckDelay("pchar_fast_mushket_fade", 0.0);
				DoQuestCheckDelay("pchar_fast_mushket", 3.5); */
			}
			/* if(sGun != "" && HasSubStr(aGun.id, "mushket") && IsCharacterPerkOn(pchar,"Gunman") && CanEquipMushketOnLocation(PChar.Location))
			{
				if(!CheckAttribute(PChar, "IsMushketer")) 
				{
					if(CheckAttribute(pchar,"chr_ai.sGun"))
					{
						pchar.PrevGunId = pchar.chr_ai.sGun;
						pchar.GunChrgInfo = pchar.chr_ai.charge;
						pchar.GunBltChrgInfo = pchar.chr_ai.bullet;
					}
					DoQuestCheckDelay("pchar_fast_mushket_fade", 1.0);
					DoQuestCheckDelay("pchar_fast_mushket", 1.5);
					LAi_SetActorTypeNoGroup(pchar);
					if(CheckAttribute(pchar,"PrevMusId") && CheckAttribute(pchar,"items."+pchar.PrevMusId)) pchar.GenQuest.MusId = pchar.PrevMusId;
					else pchar.GenQuest.MusId = aGun.id;
					PlaySound("PEOPLE\clothes1.wav");
				}
				else
				{
					PChar.IsMushketer.MushketID = sGun;
					EquipCharacterByItem(PChar, sGun); 
					SendMessage(&ILogAndActions,"l",LI_CLEAR_STRINGS);
					Log_info(XI_ConvertString("GunSelect")+GetConvertStr(aGun.name, "ItemsDescribe.txt"));
					GunCharging(pchar, MUSKET_ITEM_TYPE, sGun);
				}
			}
			else
			{
				// предупреждалки
				if(!IsCharacterPerkOn(pchar,"Gunman")) Log_info(XI_ConvertString("MusketPerk"));
				if(!CanEquipMushketOnLocation(PChar.Location)) Log_info(XI_ConvertString("NoMusket")); // сейчас по факту это проверка модели героя
				if(pchar.model == "protocusto") Log_info(XI_ConvertString("DivingSuit"));
				if(!HasSubStr(aGun.id, "mushket")) Log_info(XI_ConvertString("MusketOut"));
				PlaySound("interface\knock.wav");
			} */
		}
		else
		{
			makearef(arItems, pchar.items);
			iItemsNum = GetAttributesNum(arItems);
			for(i=0; i<iItemsNum; i++)
			{
				sItem = GetAttributeName(GetAttributeN(arItems, i));
				rItem = ItemsFromID(sItem);
				// cle цзань
				if(sItem == "blade_41") SetBlade_FgtLvl(pchar, rItem);

				if(!CheckAttribute(rItem, "groupID")) continue;
				if(rItem.groupID != BLADE_ITEM_TYPE) continue;
				if(sItem != "" && rItem.groupID == BLADE_ITEM_TYPE && rItem.FencingType == BladeType) 
				{
					p = BladeNum(BladeType);		 
					n++;
					if(n == p-1)
					{
						sBlade = sItem; 
						BladeInfo = rItem.name; 
						break;
					}
					sBlade = sItem; 
					BladeInfo = rItem.name;
				}
			}
			if(sBlade != "")
			{
				EquipCharacterbyItem(pchar, sBlade); 
				PlaySound("PEOPLE FIGHT\Blade_Take_In_0"+(rand(2)+1) +".wav"); 
				SendMessage(&ILogAndActions,"l",LI_CLEAR_STRINGS);
				Log_info(XI_ConvertString("BladeSelect")+GetConvertStr(BladeInfo, "ItemsDescribe.txt"));
				GetWeaponQty();
			}
			else
			{
				Log_info(XI_ConvertString("BladeTypeOut"));
				PlaySound("interface\knock.wav");
			}
		}
	}		
}		

void BulletChanger() // боеприпас 
{
	string sGunType = GUN_ITEM_TYPE;
	if(MusketPriority(pchar)) sGunType = MUSKET_ITEM_TYPE;
	//if(GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE) == "" && GetCharacterEquipByGroup(pchar, MUSKET_ITEM_TYPE) != "") sGunType = MUSKET_ITEM_TYPE;
	
	if(CheckAttribute(pchar, "chr_ai."+sGunType+".bulletNum") && sti(pchar.chr_ai.(sGunType).bulletNum) > 1)
	{
		int i, p;
		int n = 0;
		string BulletType;
	
		aref arType; 
		string sGun = GetCharacterEquipByGroup(pchar, sGunType);
		if(sGun == "") return;
		ref rItm = ItemsFromID(sGun);
		makearef(arType, rItm.type);	
		for (i = 0; i < sti(pchar.chr_ai.(sGunType).bulletNum); i++)
		{
			string sTir = GetAttributeName(GetAttributeN(arType, i));
			string sBullet = rItm.type.(sTir).bullet;
			p = BulNum(sGunType);		 
			n++;
			if(n == p-1)
			{
				BulletType = sBullet; 
				break;
			}
			BulletType = sBullet; 
		}
		LAi_SetCharacterUseBullet(pchar, sGunType, BulletType);
		LAi_GunSetUnload(pchar, sGunType);
		SendMessage(&ILogAndActions,"l",LI_CLEAR_STRINGS);
		PlaySound("People Fight\reload1.wav")
		
		// предупреждающие логи
		string GunPowder = LAi_GetCharacterGunpowderType(pchar, sGunType);
		int iGunPowder = GetCharacterItem(pchar, GunPowder);
		
		if(GunPowder != ""  && iGunPowder < LAi_GetCharacterChargeQuant(pchar, sGunType)) 
		{
			Log_info(XI_ConvertString("Not enough of gunpowder"));
			PlaySound("PEOPLE FIGHT\MushketEmpty.wav");
		}
	}
}

void PotionChanger() // лечебные зелья
{
	int i, p;
	int n = 0;
	string PotionCur = "";
	ref rItem;
	aref Items, arItems;
	string sItem
	
	makearef(arItems, pchar.items);
	int iItemsNum = GetAttributesNum(arItems);
	for(i=0; i<iItemsNum; i++)
	{
		sItem = GetAttributeName(GetAttributeN(arItems, i));
		rItem = ItemsFromID(sItem);
		if(!CheckAttribute(rItem, "potion")) continue;
		if(!CheckAttribute(rItem, "potion.health")) continue;
		p = PtnNum();		 
		n++;
		if(n == p-1)
		{
			PotionCur = sItem;
			break;
		}
		PotionCur = sItem;
	}
	if(PotionCur != "") 
	{
		pchar.GenQuest.Potion_choice = PotionCur;
		SendMessage(&ILogAndActions,"l",LI_CLEAR_STRINGS);
	}
}

int BladeNum(string Type)
{
	int qty = 0;
	string sItem;
	ref rItem;
	aref arItems; 
		  
	int i, iItemsNum; 
	
	makearef(arItems, pchar.items);
	iItemsNum = GetAttributesNum(arItems);
	for(i=0; i<iItemsNum; i++)
	{
		sItem = GetAttributeName(GetAttributeN(arItems, i));
		rItem = ItemsFromID(sItem);
		if(!CheckAttribute(rItem, "groupID")) continue;
		if(rItem.groupID != BLADE_ITEM_TYPE) continue;
		if(sItem != "" && rItem.groupID == BLADE_ITEM_TYPE && rItem.FencingType == Type) 
		{
			qty++;
			if(IsEquipCharacterByItem(pchar, rItem.id)) return qty;
		}
	}
	return qty;
}

int GunNum()
{
	int qty = 0;
	string sItem;
	ref rItem;
	aref arItems; 	  
	int i, iItemsNum; 
	
	makearef(arItems, pchar.items);
	iItemsNum = GetAttributesNum(arItems);
	for(i=0; i<iItemsNum; i++)
	{
		sItem = GetAttributeName(GetAttributeN(arItems, i));
		rItem = ItemsFromID(sItem);
		if(!CheckAttribute(rItem, "groupID")) continue;
		if(rItem.groupID != MUSKET_ITEM_TYPE) continue;
		if(!HasSubStr(rItem.id, "mushket")) continue;
		if(sItem != "") 
		{
			qty++;
			if(IsEquipCharacterByItem(pchar, rItem.id)) return qty;
		}
	}
	return qty;
}

int BulNum(string GunType)
{
	int qty = 0;
	aref arType;
	string sGun = GetCharacterEquipByGroup(pchar, GunType);
	ref rGun = ItemsFromID(sGun);
	makearef(arType, rGun.type);	
	for (int i = 0; i < sti(pchar.chr_ai.(GunType).bulletNum); i++)
	{
		string sTir = GetAttributeName(GetAttributeN(arType, i));
		string sBullet = rGun.type.(sTir).bullet;
		qty++;
		if(LAi_GetCharacterBulletType(pchar, GunType) == sBullet) return qty;
	}
	return qty;
}

int PtnNum()
{
	int qty = 0;
	ref rItem;
	string sItem;
	aref arItems;
	
	makearef(arItems, pchar.items);
	int iItemsNum = GetAttributesNum(arItems);
	for(int i=0; i<iItemsNum; i++)
	{
		sItem = GetAttributeName(GetAttributeN(arItems, i));
		rItem = ItemsFromID(sItem);
		if(!CheckAttribute(rItem, "potion")) continue;
		if(sItem == "potion3") continue;
		qty++;
		if(CheckAttribute(pchar, "GenQuest.Potion_choice") && pchar.GenQuest.Potion_choice == sItem) return qty;
	}
	return qty;
}
