
void QuestComplete(string sQuestName, string qname)
{
	// boal -->
	ref sld, chr, npchar, shTo;
	aref arOldMapPos, arAll, arPass;
	int     iTemp, i, n, ShipType, Rank, idx; // нужно для вычислений любых целых (нации)
    float locx, locy, locz, fTemp;
	string  attrName, Model, Blade, Gun, sTemp, sQuestTown, sQuestTitle; // любые строки для вычислений
	bool   bOk;
	int iChurchGenBanditsCount;
	
	int iShipType;
	ref rShip;
	
	if (bQuestLogShow)
    {
	    Log_Info("Quest completed : " + sQuestName + "  param = " + qname);
		trace("Quest completed : " + sQuestName + "  param = " + qname + " " + GetQuestBookDataDigit());
	}
	// boal <--
	if (CheckAttribute(pchar, "quest." + qname + ".function"))
	{
		string sFunction = pchar.quest.(qname).function;
		call sFunction(qname);
		return;
	}

	switch(sQuestName)
	{	
		// boal -->
		// смена отношений от времени
        // boal все теперь проверяется 15-25 день при расчете состояния мира = изменение в 5% - ранд(100) > 95
        case "Nation_Legend":
            SetTimerCondition("Nation_Legend", 0, 0, 15+rand(10), true);
			// тут чиним стророжевики -->
			if (!bSeaActive && !bAbordageStarted)
            {
              //  RepairAllDefenderFortShips();
            }
            // тут чиним стророжевики <--
            if (rand(100) > 93 && !bWorldAlivePause)
            {
                if(IsEntity(&worldMap))
                {
                    LaunchNationLegend();
                }else{
                    if (!bQuestCheckProcessFreeze) // можно показать
					{
					    DoQuestCheckDelay("Nation_Legend_Map", 1.5);
					}
					else
					{
	      				Pchar.quest.Nation_Legend_Map.win_condition.l1 = "MapEnter";
	                    Pchar.quest.Nation_Legend_Map.win_condition = "Nation_Legend_Map";
			        }
                }
        	}
        break;

        case "Nation_Legend_Map":
            if (!bQuestCheckProcessFreeze) // можно показать
			{
                LaunchNationLegend();
            }else{
                Pchar.quest.Nation_Legend_Map_TEST.win_condition.l1 = "MapEnter";
                Pchar.quest.Nation_Legend_Map_TEST.win_condition = "Nation_Legend_Map";
            }
        break;
		
		case "LocTeleport":
			TeleportCharacterToPos(pchar, stf(pchar.locx), stf(pchar.locy), stf(pchar.locz)); 
		break;
		
		case "update_sea_environment": //обновление моря
			trace("bSeaActive :" + bSeaActive);
			if(CheckAttribute(pchar, "debuger_weather"))
			{
				break; //если в дебагере, то ничего не делаем
			}		
			if(bSeaActive && !bAbordageStarted)
			{
				i = FindIsland(pchar.location);
				if(i != -1)
				{
					if(stf(Sea.MaxSeaHeight) != SetMaxSeaHeight(i))
					{
						WhrCreateSeaEnvironment();
					}
				}
			}
			else
			{
				i = FindLocation(pchar.location);
				if(i != -1)
				{
					WhrCreateSeaEnvironment();
				}
			}
		break;
		
		case "update_sea_after_cabin": //обновление моря при выходе из каюты в море
			if(bSeaActive)
			{
				WhrCreateSeaEnvironment();
			}		
		break;

		case "update_battle_interface":
			BattleInterface.textinfo.Location.text = GetBILocationName();
		break;

		// начало игры, туториал
		case "Tut_StartGame_CheckMinHP_1":
			if (!CheckAttribute(pchar, "HeroParam.Teach_beat"))
			{
				pchar.HeroParam.Teach_beat	= 0;
			}
			pchar.HeroParam.Teach_beat = sti(pchar.HeroParam.Teach_beat) + 1;
			sld = characterFromID("Sailor_1");
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorAfraid(sld, pchar, true);
			bOk = false;
			if (sti(pchar.HeroParam.Teach_beat) == 1 && sti(pchar.HeroParam.Teach_battle) == 1)
			{
				bOk = true;
			}
			else
			{
				if (sti(pchar.HeroParam.Teach_beat) == 2 && sti(pchar.HeroParam.Teach_battle) == 2)
				{
					bOk = true;
					pchar.HeroParam.Teach_beat = 3; // признак, что выиграл
				}
			}
			if (bOk)
			{
				DoQuestCheckDelay("Tut_StartGame_CheckMinHP_Hero", 0.3);
			}
        break;
        
        case "Tut_StartGame_CheckMinHP_2":
        	if (!CheckAttribute(pchar, "HeroParam.Teach_beat"))
			{
				pchar.HeroParam.Teach_beat	= 0;
			}
			pchar.HeroParam.Teach_beat = sti(pchar.HeroParam.Teach_beat) + 1;
			sld = characterFromID("Sailor_2");
   			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorAfraid(sld, pchar, true);
			if (sti(pchar.HeroParam.Teach_beat) == 2 && sti(pchar.HeroParam.Teach_battle) == 2)
			{
				sld = characterFromID("Sailor_1");
				LAi_SetActorTypeNoGroup(sld);
				pchar.HeroParam.Teach_beat = 3; // признак, что выиграл
				DoQuestCheckDelay("Tut_StartGame_CheckMinHP_Hero", 0.3);
			}
        break;
        
        case "Tut_StartGame_CheckMinHP_Hero":
        	// запуск диалога
        	LAi_SetActorTypeNoGroup(pchar);
        	sld = characterFromID("Sailor_2");
			LAi_SetActorTypeNoGroup(sld);
			sld = characterFromID("Sailor_1");
			LAi_SetActorTypeNoGroup(sld);
            PChar.GenQuest.CallFunctionParam = "Tut_StartDialog";
			DoQuestCheckDelay("CallFunctionParam", 2.0);
        break;

		//  Карты сокровищ  ГЕНЕРАТОР
        case "SetTreasureFromMap":
            SetTreasureBoxFromMap();
        break;

		case "ArestInResidenceEnd":
		    LAi_LockFightMode(Pchar, false); // ножками убежал
        break;

        // ОЗГи и Пожарная команда
        case "Battle_Hunters_Land":
            Lai_SetPlayerType(pchar);
            LAi_SetFightMode(Pchar, true);
			for (i=1; i<= sti(PChar.HunterCost.Qty); i++)
			{
	            sld = characterFromID(PChar.HunterCost.TempHunterType + "LandHunter0" + i);
				LAi_RemoveCheckMinHP(sld);
	            LAi_SetWarriorType(sld);
	            //LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
	            LAi_group_MoveCharacter(sld, "LAND_HUNTER");
			}
            LAi_group_SetRelation("LAND_HUNTER", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("LAND_HUNTER", LAI_GROUP_PLAYER, true);
        break;

        case "GoAway_Hunters_Land":
            DoQuestCheckDelay("OpenTheDoors", 4.0);
            sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
            for (i=1; i<= sti(PChar.HunterCost.Qty); i++)
			{
	            sld = characterFromID(PChar.HunterCost.TempHunterType + "LandHunter0" + i);
				LAi_type_actor_Reset(sld);
				LAi_ActorGoToLocation(sld, "reload", sTemp, "none", "", "", "", 4.0);
			}
        break;

        case "KnippelAppearance":
            TEV.boardingReloadFreeze = "";
            DoQuestCheckDelay("KnippelAppearance_2", 4.0);
        break;

        case "KnippelAppearance_2":
            PlaySound("Ambient\LAND\door_004.wav");
            // TO_DO:
            sld = GetCharacter(NPC_GenerateCharacter("Kneepel_FP", "Kneepel", "man", "man_B", 20, ENGLAND, -1, false, "quest"));
            sld.name = StringFromKey("QuestsUtilite_36");
            sld.lastname = StringFromKey("QuestsUtilite_37");
            sld.greeting = "knippel_1";
            LAi_SetHP(sld, 120, 120);
            SetSelfSkill(sld, 10, 12, 10, 10, 70);
            SetShipSkill(sld, 50, 20, 75, 75, 45, 20, 20, 10, 15);
            SetSPECIAL(sld, 9, 10, 6, 5, 5, 5, 9);
            SetCharacterPerk(sld, "HullDamageUp");
            SetCharacterPerk(sld, "SailsDamageUp");
            SetCharacterPerk(sld, "CrewDamageUp");
            SetCharacterPerk(sld, "CriticalShoot");
            SetCharacterPerk(sld, "LongRangeShoot");
            SetCharacterPerk(sld, "CannonProfessional");
            SetCharacterPerk(sld, "FastReload");
            sld.Dialog.Filename = "Quest\FireBrigade.c";
            sld.dialog.currentnode = "Kneepel";
            sTemp = GetGeneratedItem("blade_12");
            GiveItem2Character(sld, sTemp);
            EquipCharacterbyItem(sld, sTemp);
            GiveItem2Character(sld, "pistol1");
            EquipCharacterbyItem(sld, "pistol1");
            TakeNItems(sld, "bullet", 50);
            AddItems(sld, "gunpowder", 50);
            ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
            LAi_SetActorType(sld);
            LAi_ActorDialog(sld, pchar, "", -1.0, 0.0);
            LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
        break;

		// офицеры выживают!
        case "Survive_In_SeaOfficer":
			sld = GetCharacter(sti(Pchar.GenQuest.Survive_In_SeaOfficerIdx));
            iTemp = NPC_GeneratePhantomCharacter("citizen", sti(sld.Nation), MAN, -1);  // создать клон
			if (iTemp != -1)
			{
                npchar = &Characters[iTemp];
                if (CheckAttribute(sld, "PGGAi"))
	            {
	            	sTemp = npchar.id; // новый рандомный ИД
					DeleteAttribute(npchar, "");// все трем, а там и перки!
					CopyAttributes(npchar, sld);
	
					npchar.index = iTemp;
					// меняемся ИД, старый новому, новый трупу
					sld.id = sTemp; //navy (ПГГ fix) 26.12.06
					// тут трем накопивщиеся сабли и корабли 290704 BOAL -->
					DeleteAttribute(npchar, "Ship");
					npchar.ship.type = SHIP_NOTUSED;
                    npchar.location = "none";
                    npchar.location.from_sea = "";
					
					DeleteAttribute(npchar, "Fellows"); // его офицеры
					// пгг в рядового НПС
					sld.LifeDay = 0;
                    DeleteAttribute(sld, "PGGAi");
	            }
	            else
	            {
	                ChangeAttributesFromCharacter(npchar, sld, true);
	                
	    			sld.location = "none";
	    			sld.location.from_sea = "";
    			}
    			PlaySound("interface\" + LanguageGetLanguage() + "\_EvShip1.wav");
    			LAi_SetCurHPMax(npchar);
    			AddPassenger(Pchar, npchar, false);
    			Log_Info(StringFromKey("quests_reaction_1", GetFullName(npchar)));
            }
        break;
		
		case "Get_TreasureBarrel":
			Set_TreasureBarrel();
		break;
		
        // враги спасшиеся на шлюпках homo
        case "Survive_In_SeaPrisoner":  //homo 22/06/07
            sld = GetCharacter(sti(Pchar.GenQuest.Survive_In_SeaPrisonerIdx));
            iTemp = SetCharToPrisoner(sld);
			if (iTemp != -1)
			{
                npchar = &Characters[iTemp];
                PlaySound("interface\" + LanguageGetLanguage() + "\_EvShip1.wav");
                // лишнее, помер ПГГ и все тут if (findsubstr(sld.id, "PsHero_" , 0) != -1) npchar = sld.id; //homo for navy (ПГГ fix)
                LAi_SetCurHPMax(npchar);
    			sld.location = "none";
    			sld.location.from_sea = "";
                Log_Info(StringFromKey("quests_reaction_2", GetFullName(npchar)));
            }
        break;
        
		/////////////////////////Квест награда за голову//////////////////////////////////////
		case "CheckMaxHealthQuest":
            SetTimerCondition("CheckMaxHealthQuest", 0, 0, 5, true);
            SetNewDayHealthMax();
        break;
        
		case "My_Deck_Battle_End":  // запрет битв в трюме -после казни пленных
            LAi_LocationFightDisable(&Locations[FindLocation("My_Deck")], true);
            LAi_SetFightMode(Pchar, false);
        break;
		//  boal 290804 наказание битьем морды -->
        case "PunishmentAction":
            LAi_SetActorTypeNoGroup(PChar);
            sld = &Characters[makeint(Pchar.GenQuest.FreeRandomOfficerIdx)];
			LAi_SetActorTypeNoGroup(sld);
            LAi_ActorTurnToCharacter(pchar, sld);
            LAi_ActorAnimation(pchar, "attack_force_3", "", 0.9);
            DoQuestCheckDelay("PunishmentAction_1", 0.5);
         break;

         case "PunishmentAction_1":
            sld = &Characters[makeint(Pchar.GenQuest.FreeRandomOfficerIdx)];
            LAi_ActorAnimation(sld, "hit_attack_2", "PunishmentAction_2", 0.6);
         break;

         case "PunishmentAction_2":
            Lai_SetPlayerType(pchar);
            sld = &Characters[makeint(Pchar.GenQuest.FreeRandomOfficerIdx)];
            switch (pchar.GenQuest.PunishmentActionManType)
            {
                case "LAi_SetHuberStayType":
                    LAi_SetHuberStayTypeNoGroup(sld);
                    break;

                case "LAi_SetStayType":
                    LAi_SetCitizenTypeNoGroup(sld);
                    break;
            }
		break;
		//  boal 290804 наказание битьем морды <--
		// индульгенция -->
		case "donation":
			int iDonation = makeint(pchar.questTemp.donate);
			int iRep      = makeint(pchar.reputation.nobility);
			int iRepIncr;
			if (iRep <10)
			{
				if (iDonation >= 1000)
				{
					iRepIncr = iDonation / 1000;
					ChangeCharacterComplexReputation(pchar,"nobility", iRepIncr);
				}
			}
			if (iRep < 20 && iRep >= 10)
			{
				if (iDonation >= 2000)
				{
					iRepIncr = iDonation/2000;
					ChangeCharacterComplexReputation(pchar,"nobility", iRepIncr);
				}
			}
			if (iRep <30 && iRep >=20)
			{
				if (iDonation >= 3000)
				{
					iRepIncr = iDonation/3000;
					ChangeCharacterComplexReputation(pchar,"nobility", iRepIncr);
				}
			}
			if (iRep <40 && iRep >=30)
			{
				if (iDonation >= 4000)
				{
					iRepIncr = iDonation/4000;
					ChangeCharacterComplexReputation(pchar,"nobility", iRepIncr);
				}
			}
			if (iRep <50 && iRep >=40)
			{
				if (iDonation >= 5000)
				{
					iRepIncr = iDonation/5000;
					ChangeCharacterComplexReputation(pchar,"nobility", iRepIncr);
				}
			}
			if (iRep <60 && iRep >=50)
			{
				if (iDonation >= 6000)
				{
					iRepIncr = iDonation/6000;
					ChangeCharacterComplexReputation(pchar,"nobility", iRepIncr);
				}
			}
			if (iRep <70 && iRep >=60)
			{
				if (iDonation >= 7000)
				{
					iRepIncr = iDonation/7000;
					ChangeCharacterComplexReputation(pchar,"nobility", iRepIncr);
				}
			}
			if (iRep <80 && iRep >=70)
			{
				if (iDonation >= 8000)
				{
					iRepIncr = iDonation/8000;
					ChangeCharacterComplexReputation(pchar,"nobility", iRepIncr);
				}
			}
			if (iRep < REPUTATION_MAX && iRep >=80)
			{
				if (iDonation >= 10000)
				{
					iRepIncr = iDonation/10000;
					ChangeCharacterComplexReputation(pchar,"nobility", iRepIncr);
				}
				}
			pchar.questTemp.donate = 0; // mitrokosta фикс накопления пожертвований
		break;
	    // индульгенция <--
		case "SetNPCInShipDeck":  // народ внутри нашего корабля
            if (Pchar.location == Get_My_Cabin())//"My_Cabin" || Pchar.location == "My_Cabin_Small")
	        {
                SetOfficersInCabin();
            }
            else
            {
                if (Pchar.location == "My_Deck")// трюм
                {
                    SetPrisonerInHold();
                }
                else
                {
	                if (Pchar.location == "My_Campus")// кают-компания
	                {
	                    SetOfficersInCampus();
	                }
                }
            }
        break;
        
		case "SetQuestHoldBox":
			if (Pchar.location == "My_Deck")// трюм
            {
                FillQuestHoldBox(&Locations[FindLocation(Pchar.location)]);
            }
		break;
		
        case "Munity_on_Ship_Map":
            if (IsEntity(&worldMap) && GetCrewQuantity(pchar) > 0 && !IsCharacterEquippedArtefact(pchar, "totem_02"))
        	{
                MunityOnShip("ShipMunity");
            }
        break;

        case "Munity_on_Ship":
            pchar.quest.Munity = "";
            pchar.GenQuest.MunityStart = true;
            PlaySound("interface\" + LanguageGetLanguage() + "\_GTBoard2.wav");
            InterfaceStates.Buttons.Save.enable = 0;
            LAi_SetFightMode(Pchar, true);

            if (!CheckAttribute(pchar, "GenQuest.SlavesMunity"))
            {
                for (i=1; i<=9; i++)
                {
                    sld = SetFantomDefenceForts("goto", "", PIRATE, LAI_GROUP_TmpEnemy);
                    if (i >= (sti(PChar.Ship.Crew.Quantity)/((9-GetCharacterShipClass(PChar))*9))) break;
                    RemoveCharacterCrew(PChar, (9-GetCharacterShipClass(PChar))*9);
                }
                PChar.Ship.Crew.Morale = 25;
                ChangeCrewExp(PChar, "Soldiers", 2); // бонус на подавление
				// Addon-2016 Jason ФМК-Гваделупа
				if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "mutiny")
				{
					for (i=1; i<=3; i++)
					{
						sld = characterFromId("FMQG_pass_"+i);
						RemovePassenger(pchar, sld);
						GetCharacterPos(pchar, &locx, &locy, &locz);
						ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestLocator("goto", locx, locy, locz));
						LAi_SetWarriorType(sld);
						LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
						sld = SetFantomDefenceForts("goto", "", PIRATE, LAI_GROUP_TmpEnemy); // добавим ещё +3 тела
					}
				}
				if (CheckAttribute(pchar, "questTemp.FMQN") && pchar.questTemp.FMQN == "mutiny") // ФМК-Сент-Кристофер
				{
					for (i=1; i<=5; i++)
					{
						sld = characterFromId("FMQN_seafox_"+i);
						RemovePassenger(pchar, sld);
						GetCharacterPos(pchar, &locx, &locy, &locz);
						ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestLocator("goto", locx, locy, locz));
						LAi_SetWarriorType(sld);
						LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
					}
				}
            }
            else
            {
                for (i=1; i<=9; i++)
                {
                    sld = SetFantomSlaves("goto", "", LAI_GROUP_TmpEnemy);
                    if (i >= (GetCargoGoods(PChar, GOOD_SLAVES)/((9-GetCharacterShipClass(PChar))*9))) break;
                    RemoveCharacterGoodsSelf(PChar, GOOD_SLAVES, (9-GetCharacterShipClass(PChar))*9);
                }
                DeleteAttribute(pchar, "GenQuest.SlavesMunity");
                ChangeCrewExp(PChar, "Soldiers", 3); // бонус на подавление
            }
            LAi_group_SetHearRadius(LAI_GROUP_TmpEnemy, 100.0);
            LAi_group_FightGroups(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, true);
            LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);

            LAi_group_SetCheck(LAI_GROUP_TmpEnemy, "Dead_Munity");
			DoQuestFunctionDelay("Terrapin_SetMusic", 1.5); // Addon-2016 Jason
        break;

        case "Dead_Munity":
		if (CheckAttribute(pchar, "questTemp.MutinyOfficerIDX")) // mitrokosta переписал без атрибута begin - нафиг он нужен? только глаза мозолит
		{
			Log_SetStringToLog(StringFromKey("quests_reaction_3"));
			DeleteAttribute(pchar, "questTemp.MutinyOfficerIDX");
		}
		else Log_SetStringToLog(StringFromKey("quests_reaction_4"));

            InterfaceStates.Buttons.Save.enable = 1;
            pchar.quest.Munity = "Deads";
            LAi_SetFightMode(Pchar, false);
            DeleteAttribute(pchar, "GenQuest.MunityStart");
			// Addon-2016 Jason ФМК-Гваделупа
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "mutiny")
			{
				AddQuestRecord("FMQ_Guadeloupe", "5");
				CloseQuestHeader("FMQ_Guadeloupe");
				pchar.questTemp.FMQG = "fail";
			}
			// Addon-2016 Jason ФМК-Сент-Кристофер
			if (CheckAttribute(pchar, "questTemp.FMQN") && pchar.questTemp.FMQN == "mutiny")
			{
				AddQuestRecord("FMQ_Nevis", "2");
				CloseQuestHeader("FMQ_Nevis");
				pchar.questTemp.FMQN = "fail";
			}
        break;
        
		///  захват форта - город
        case "FreeCaptureForts": // уберем солдат, откроем входы (на всяк случай) при выходе на карту
            TWN_FreeCaptureForts();
        break;
        // захват с суши по диалогу мэра (телепорт)
        case "Town_Capture_Land":
            sld = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
            DeleteQuestAttribute("Union_with_Escadra");

            SetLocationCapturedState(sld.Default, true);

            DoQuestReloadToLocation(sld.Default.BoardLocation, sld.Default.BoardGroup, sld.Default.BoardLocator, "Capture_Forts");
        break;
        
        case "Capture_Town_Siege":
            PrepareTownBattle(); // тут только джунгли для этого случая

			if (!CheckAttribute(Pchar, "GenQuestFort.SoundOff"))
			{
            	PlaySound("interface\" + LanguageGetLanguage() + "\_GTTown2.wav");
            	AddCharacterExpToSkill(Pchar, "Leadership", 100);
			    AddCharacterExpToSkill(Pchar, "Sneak", 100);
            }
            else
            {
                DeleteAttribute(Pchar, "GenQuestFort.SoundOff");
            }
        break;
        // Возвращение губернаторам родные диалоги // boal переделал 251204
        case "Return_Gover_Dialog":
            Characters[sti(PChar.GenQuest.GoverIdx)].dialog.CurrentNode = "First time";
        break;

        case "Return_Gover_Dialog_Exit":
            DoQuestCheckDelay("Return_Gover_Dialog", 0.5);
        break;
        // после битвы в форте сюда
        case "Capture_Forts":
            TWN_Capture_Forts();
        break;

        case "FightInTown":
            TWN_FightInTown();
        break;

        case "FightInTown_OpenNext":
            TWN_FightInTown_OpenNext();
        break;

        case "FightInTown_Finish":
            LAi_grp_alarmactive = false; // конец тревоги
			LAi_LockFightMode(pchar, false);
            LAi_SetFightMode(Pchar, false);
        break;

        //Два пути захвата форта
        // 1 уходим с добычей - в диалоге мэра

        // 2 Если оставляем форт себе
        case "Residence_Captured_Any":
            TWN_Residence_Captured_Any();
        break;

        case "Residence_Captured_Any_02":
   			TWN_Residence_Captured_Any_02();
        break;

        case "Back_Mayor_Type":
            TWN_Back_Mayor_Type();
        break;

        case "CapturedToOurCity":
			PlayStereoOGG("music_ship_victory");
			sld = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
            Log_Info(StringFromKey("quests_reaction_5", GetCityName(sld.City)));
			// убрать контрабандиста
			sTemp = sld.City + "_Smuggler";
			if (GetCharacterIndex(sTemp) >= 0) // не везде есть
			{
				ChangeCharacterAddress(characterFromID(sTemp), "None", ""); // вся логика теперь в рассидки таверны
			}
            SetCaptureTownByHero(sld.City);
            LaunchColonyInfoScreen(); // табличка   to_do даёт вылет :(
			// отсчет для отбития
			sTemp = "Attack_Fort_" + sld.City;
            SetTimerCondition(sTemp, 0, 0, 25 + rand(70), false);
            PChar.Quest.(sTemp).CityId   = sld.City;
			PChar.Quest.(sTemp).function = "TWN_Siege_Any";
        break;
		///////////////////////////////// захват города <--
		//  системные фичи
		case "PostVideo_Start":
            bMainMenuLaunchAfterVideo = true;
			PostVideoAndQuest(PChar.GenQuest.VideoAVI, 100, "PostVideo_After");
        break;

        case "PostVideo_After":
            PostEvent("DoInfoShower",100,"s","");
			DoQuestCheckDelay(PChar.GenQuest.VideoAfterQuest, 0.1);
        break;
        
        case "SetTimerEvent":
        	attrName = PChar.Quest.(qname).Event;
        	sTemp = PChar.Quest.(qname).Event.Type;
        	Model = PChar.Quest.(qname).Event.Param;
        	SetEventHandler(attrName, attrName, 0);
        	Event(attrName, sTemp, Model);
        	break;

        case "CallFunctionParam":
            attrName = PChar.GenQuest.CallFunctionParam;
            call attrName();
        break;
        
		// Warship. CallFunctionParam не хочет работать с диалогами, поэтому испльзовать можно эту...
		case "NextFunction":
			DoQuestFunctionDelay(PChar.QuestTemp.NextFunction, 0.1);
		break;
        
        // вызов табличкм А в это время..
        case "LaunchFrameForm":
            PChar.GenQuest.CallFunctionParam = "LaunchFrameForm";
			DoQuestCheckDelay("CallFunctionParam", stf(pchar.AutoQuest.FrameDelay));
        break;
        
        case "Move_Govenour":  // переместим губернатора в другой город
            SetTimerCondition("Move_Govenour", 0, 0, 25+rand(10), true);
            Move_Govenour();
        break;
        
		// музыка виктори
		case "sea_victory":
			SetMusicOnce("music_ship_victory");
		break;
		
		case "sea_victory_2":
			SetMusicOnce("music_ship_victory2");
		break;
		
		// вижу парус
		case "see_sails":
			PlaySound("interface\" + LanguageGetLanguage() + "\_EvEnemy1.wav");
			PlaySound("interface\notebook.wav");
		break;
        
		case "pchar_back_to_player":
			Lai_SetPlayerType(pchar);
		break;

		case "WalkByFoot":
			bDisableFastReload = true;
		break;

        case "God_hit_us": // это такой прикол - задействовать в ловушки для сундуков(boal)
			iTemp = 10+rand(15);
			if ((MakeInt(pchar.chr_ai.hp)-iTemp) > 0)
            {
    			LAi_SetActorType(PChar);
                LAi_ActorAnimation(PChar, "hit_attack_2", "pchar_back_to_player", 1.0);
            }
			if (!LAi_IsImmortal(pchar))
            {
				LAi_ApplyCharacterDamage(pchar, iTemp, "other");
				if(bDrawBars) SendMessage(pchar, "lfff", MSG_CHARACTER_VIEWDAMAGE, iTemp, MakeFloat(MakeInt(pchar.chr_ai.hp)), MakeFloat(MakeInt(pchar.chr_ai.hp_max)));
				LAi_CheckKillCharacter(pchar);
				SendMessage(pchar, "l", MSG_CHARACTER_STOPSTRAFE);
			}
		break;
		// диалог с ГГ генератор
        case "TalkSelf_Start":
            StartActorSelfDialog("TalkSelf_Main");
        break;
        // диалог с ГГ квестовые реплики
        case "TalkSelf_Quest":
            StartActorSelfDialog("First time");
        break;
        /////  сидим за столом в таверне ->
        case "alc":
			LAi_Fade("alc_2_prepare", "alc2");
			/* if(CheckAttribute(pchar, "IsMushketer"))
			{
				SetMainCharacterToMushketer("", false);
			} */
		break;

		case "alc_2_prepare":
			LAi_SetSitType(pchar);
			LAi_SetActorType(characterFromID(pchar.questTemp.friend_in_tavern));
			LAi_ActorSetSitMode(characterFromID(pchar.questTemp.friend_in_tavern));

            sld = characterFromID(pchar.questTemp.friend_in_tavern);
            FreeSitLocator(sld.Default, sld.Default.ToLocator);  // очистим стул
			ChangeCharacterAddressGroup(pchar, sld.Default, sld.Default.group, sld.Default.ToLocator);
		break;

		case "alc2":
			LAi_ActorDialogNow(characterFromID(pchar.questTemp.friend_in_tavern), pchar, "", -1);
		break;

		case "exit_sit":
			if (CheckQuestAttribute("fight_in_tavern", "fight"))
			{
				pchar.quest.fight_in_tavern = "0";
				LAi_SetSitType(characterFromID(pchar.questTemp.friend_in_tavern));
			}
			else
			{
				if (pchar.location.group == "sit")
				{
					LAi_Fade("exit_sit_2", "");
				}
			}
		break;

		case "exit_sit_2":
   			sld = characterFromID(pchar.questTemp.friend_in_tavern);
			LAi_SetSitType(sld);
			LAi_SetPlayerType(pchar);
			//ChangeCharacterAddress(pchar, sld.Default, sld.Default.ToGo);
			PlaceCharacter(pchar, "tables", pchar.location); // ближний к столу
			// Captain Beltrop, 27.06.21, новый вариант
			if (CheckAttribute(pchar, "questTemp.BadHabitueSit"))
			{
				DeleteAttribute(pchar, "questTemp.BadHabitueSit");
			    rCharacter = characterFromID("Tavern_BadHabitue");
	            rCharacter.dialog.currentnode = "First time";
				rCharacter.quest.last_theme = 0;
	            ChangeCharacterAddressGroup(rCharacter, sld.Default, sld.Default.group, sld.Default.ToLocator);
	            LAi_SetSitType(rCharacter);
				LAi_group_MoveCharacter(rCharacter, sld.chr_ai.group);
			}
		break;
		// реплика таверншика о запрете драк -->
		case "tavern_keeper":
			attrName = GetCharIDByParam("TavernMan", "location", pchar.location);
            sld = characterFromID(attrName);
			sld.dialog.currentnode = "tavern_keeper";
			LAi_ActorWaitDialog(pchar, sld);
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "tavern_keeper_2", -1);
		break;

		case "tavern_keeper_2":
            attrName = GetCharIDByParam("TavernMan", "location", pchar.location);
            sld = characterFromID(attrName);
			sld.dialog.currentnode = "First time";
			LAi_SetBarmanType(sld);
		break;
		// реплика таверншика о запрете драк <--
 		case "without_memory":
			LAi_Fade("exit_sit_2", "saved_by_off");
			bQuestCheckProcessFreeze = true;
			WaitDate("",0,0,0, 5, 30);
			bQuestCheckProcessFreeze = false;
			RefreshLandTime();
		break;

		case "saved_by_off":
			LAi_SetStayType(pchar);
			Log_Info(StringFromKey("quests_reaction_6"));

			int oSum = 500 + rand(4500);
			if (makeint(Pchar.money) < oSum) oSum = makeint(Pchar.money);
			AddMoneyToCharacter(pchar, -oSum);
			if (sti(pchar.questTemp.stels.tavern) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, makeint(50+oSum/100));
				pchar.questTemp.stels.tavern = GetDataDay();
			}

   			sld = characterFromID(loadedLocation.fastreload + "_waitress");
   			pchar.questTemp.officiantLocator = sld.location.locator;
   			pchar.questTemp.officiantGroup   = sld.location.group;   // запомнить, где была
			PlaceCharacter(sld, "goto", pchar.location);
			if (CheckAttribute(pchar, "questTemp.Consumption") && pchar.location == "PortSpein_tavern") sld.dialog.currentnode = "without_moneysss";
			else sld.dialog.currentnode = "without_money"; // лесник ,выбор диалога если нажралдся в "цене чухотки"																																		 
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "officiant_back_to_citizen", 5.0, 1.0);
			DoQuestCheckDelay("pchar_back_to_player", 6.0);
		break;

		case "officiant_back_to_citizen":
			LAi_SetPlayerType(pchar);
            sld = characterFromID(loadedLocation.fastreload + "_waitress");
			LAi_SetWaitressType(sld);
			sld.location.locator = pchar.questTemp.officiantLocator;
			sld.location.group   = pchar.questTemp.officiantGroup;
		break;
		
		//  агенты стран в таверне -->
        case "NationUpdate":
            UpdateRelations();
            if(bSeaActive)
            {
                RefreshBattleInterface();
            }
		break;

        case "pir_flag_rise":
			Flag_PIRATE();
		break;
		// агенты в тавернах -->
        case "any_patent_take":
            AddMoneyToCharacter(pchar, -sti(pchar.PatentPrice));

            RemovePatent();

			GiveItem2Character(pchar, "patent_" + pchar.PatentNation);
            EquipCharacterbyItem(pchar, "patent_" + pchar.PatentNation);

            Items[sti(pchar.EquipedPatentId)].TitulCur = 1; // текущ звание сбросим
        	Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0; // счетчик звание сбросим
		break;

        case "fra_flag_rise":
            Flag_FRANCE();
        break;

        case "eng_flag_rise":
            Flag_ENGLAND();
        break;

        case "spa_flag_rise":
            Flag_SPAIN();
        break;

        case "hol_flag_rise": 
            Flag_HOLLAND();
        break;

        case "QuestAboardCabinDialog":  // диалог в абордаже, в каюте при достижении минНР
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)]; // фантом, тень отца капитана
			LAi_SetActorType(pchar);
            LAi_SetActorType(sld);
            SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
		    LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 0.5);
		break;
		
		case "LAi_ReloadBoarding": // задержка нужна
			LAi_EnableReload();
		    DelEventHandler("Control Activation", "LAi_ActivateReload");
			Log_SetActiveAction("Nothing");
			LAi_ReloadBoarding();
		break;
		
		case "LAi_EnableReload":
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
		break;
		// boal <---
		
		case "Map_SetNationHanters": // запустить перехватчиков на карте
			EnemyNationHunterOnMap(false);
        break;
		
		case "Map_SetNationCoolHanters": // запустить скоростных перехватчиков
			EnemyNationHunterOnMap(true);
        break;
		// --> belamour для быстрой команды по смене оружия
		case "pchar_fast_mushket":
			DeleteAttribute(pchar,"systeminfo.showmush");
		break;
		
		case "pchar_fast_mushket_fade":
			pchar.systeminfo.showmush = true;
		break;
		// <-- belamour

        ////////////////////////////////////////////////////////////////////////
		//  Служебный квест контрабандистов - ограничение по времени
		////////////////////////////////////////////////////////////////////////
		case "Rand_Smuggling":
			//слишком падает ChangeContrabandRelation(pchar, -10); // boal
			pchar.quest.KillSmugglers_after.over = "yes";  
			RemoveSmugglersFromShore();
		break;

		//Постановка стражников в локацию передачи контрабандистов
		case "Rand_ContrabandInterruption":
			chrDisableReloadToLocation = true;
			LAi_SetFightMode(pchar, false);
			LAi_LockFightMode(pchar, true);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться 130313
			// солдаты в начале
			iTemp = GetCityNation(GetCityNameByIsland(GiveArealByLocation(loadedLocation)));
			if(iTemp == -1) 
			{
				iTemp = sti(pchar.GenQuest.Contraband.GuardNation);// Нация патруля
			}	
			Pchar.quest.contraband.SoldierQty = makeint(2*GetOfficersQuantity(Pchar) + 3);
			for (i = 2; i <= sti(Pchar.quest.contraband.SoldierQty); i++)
			{
    			sld = SetFantomDefenceForts("", "", iTemp, "CoastalGuards");
    			attrName = "SoldierIDX"+i;
    			Pchar.quest.contraband.(attrName) = sld.index;
    			LAi_SetActorType(sld);
    			LAi_ActorFollow(sld, Pchar, "", 38);
    			sld.Dialog.Filename = "Smuggler_Guards_dialog.c";
				sld.Dialog.CurrentNode = "First time";
				sld.greeting = "patrol";
            }
			// вызовем независимо!!!! не тут :) SetCoastalGuardPursuit();

			// офицер в конце
            sld = SetFantomOfficer("", "", iTemp, "CoastalGuards");
			Pchar.quest.contraband.SoldierIDX1 = sld.index;
			LAi_SetActorType(sld);
			sld.Dialog.Filename = "Smuggler_Guards_dialog.c";
			sld.Dialog.CurrentNode = "First time";
			sld.greeting = "patrol";

			LAi_ActorDialog(&Characters[makeint(Pchar.quest.contraband.SoldierIDX1)], Pchar, "", 35, 1); // boal 120c - озвереть ждать!!!
			LAi_group_SetCheck("CoastalGuards", "CoastalGuardsAllDead");
		break;

		// belamour legendary edition опасный груз -->
		case "Contrabandzpq":
			chrDisableReloadToLocation = true;
			sld = characterFromID(pchar.GenQuest.Smugglerzpq);
			sld.Dialog.CurrentNode = "SmugglerZPQ";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		// <-- legendary edition
		
		case "Rand_ContrabandInterruptionAtSeaEnded":
			StopCoastalGuardPursuit();
			
			AddSimpleRumourCity(StringFromKey("quests_reaction_7")+ 
				StringFromKey("quests_reaction_8"), Pchar.quest.contraband.City, 3, 5, "");	
		break;

		case "Rand_ContrabandAtSeaEnded":
			StopCoastalGuardPursuit();
			
			AddSimpleRumourCity(StringFromKey("quests_reaction_7")+ 
				StringFromKey("quests_reaction_8"), Pchar.quest.contraband.City, 3, 5, "");				
		break;

		case "CoastalGuardsAllDead":
			for (i=1; i<4; i++)
			{
				sTemp = "Rand_Smug0" + i;
				LAi_SetGuardianTypeNoGroup(CharacterFromID(sTemp));
			}
			LAi_grp_alarmactive = false; // конец тревоги
		break;
		//  контрабанды <--
		
		/////////////////////////////////////////////////////////////////////////////////
		// НАЧАЛО КВЕСТА - УДАЛЕНИЕ ТЕКУЩЕГО НАПРАВЛЕНИЯ И СИЛЫ ВЕТРА
		/////////////////////////////////////////////////////////////////////////////////
		case "EraseWind":
			DeleteAttribute(pchar, "wind");
		break;
		/////////////////////////////////////////////////////////////////////////////////
		// КОНЕЦ КВЕСТА - УДАЛЕНИЕ ТЕКУЩЕГО НАПРАВЛЕНИЯ И СИЛЫ ВЕТРА
		/////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////
		// СБРОС СЧЕТЧИКА ДУЭЛЕЙ В ТАВЕРНЕ
		/////////////////////////////////////////////////////////////////////////////////		
		case "HabitueSpeakDisable_End":
			DeleteAttribute(pchar,"questTemp.HabitueSpeakDisable");
			DeleteAttribute(pchar,"questTemp.duelQty");
		break;
		/////////////////////////////////////////////////////////////////////////////////
		// СБРОС СЧЕТЧИКА ДУЭЛЕЙ В ТАВЕРНЕ
		/////////////////////////////////////////////////////////////////////////////////				
		
		/////////////////////////////////////////////////////////////////////////////////
		//	СЛУЖЕБНЫЕ ФИЧИ
		/////////////////////////////////////////////////////////////////////////////////
		case "hide_weapon":
			LAi_SetFightMode(pchar, false);
			break;

		case "AnyReloadToLocation":
			int iMonth, iDay, iHour, iMin;

			iMonth	= sti(PChar.AutoQuest.delayMonth);
			iDay	= sti(PChar.AutoQuest.delayDay);
			iHour	= sti(PChar.AutoQuest.delayHour);
			iMin	= sti(PChar.AutoQuest.delayMin);

			if(iMonth > 0 || iDay > 0 || iHour > 0 || iMin > 0)
			{
                bQuestCheckProcessFreeze = true;
				WaitDate("", 0, iMonth, iDay, iHour, iMin);
				bQuestCheckProcessFreeze = false;
			}
			DoQuestReloadToLocation(PChar.AutoQuest.idLocation, PChar.AutoQuest.idGroup, PChar.AutoQuest.idLocator, PChar.AutoQuest.questName);
			break;
		/////////////////////////////////////////////////////////////////////////////////
		//	СЛУЖЕБНЫЕ ФИЧИ
		/////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////
		//	START OF ПГГ
		/////////////////////////////////////////////////////////////////////////////////
		case "PGG_Companion_Leave":
			chrDisableReloadToLocation = true;
			sld = &Characters[sti(pchar.questTemp.PGG_Companion_Leave.index)];
			PlaceCharacter(sld, "goto", "random_must_be_near");

			sld.Dialog.CurrentNode = "companion_leave";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			break;

		case "RemoveCharacterFromLocation":
			sld = CharacterFromID(PChar.questTemp.Chr2Remove);
			ChangeCharacterAddressGroup(sld, "None", "", "");
			LAi_SetImmortal(sld, false);
			break;

		case "PGG_Q1AfterShoreFight":
			PGG_Q1AfterShoreFight();
			break;

		case "PGG_Q1AfterDeckFight":
			PGG_Q1AfterDeckFight();
			break;
		/////////////////////////////////////////////////////////////////////////////////
		//	END OF ПГГ
		/////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////
		//	Корсарское метро
		/////////////////////////////////////////////////////////////////////////////////
		case "RemoveTravelSmugglers":
			if (!CheckAttribute(PChar, "GenQuest.contraTravel.PatrolFight")) ChangeContrabandRelation(PChar, -10);
			RemoveSmugglersFromShore();

			if (!CheckAttribute(PChar, "GenQuest.contraTravel.ship")) 
			{
				AddQuestRecord("Gen_ContrabandTravel", "3");
				AddQuestUserData("Gen_ContrabandTravel", "sSex", GetSexPhrase(StringFromKey("quests_reaction_9"),StringFromKey("quests_reaction_10")));
				DeleteAttribute(PChar, "GenQuest.contraTravel");
				CloseQuestHeader("Gen_ContrabandTravel");
			}

			sld = CharacterFromID("Abracham_Gray");
			sld.location.from_sea = "";
			break;

		case "Travel_talkOnDeck":
			//убираем контрабандистов
			RemoveSmugglersFromShore();
			//кинозвезда Абрахам Грей :)
			sld = CharacterFromID("Abracham_Gray");
			//параметры..
			sld.nation = PIRATE;
			Ship_FlagRefresh(PChar); //флаг на лету
			sld.location.from_sea = "";

			LAi_group_MoveCharacter(sld, "TmpEnemy");
			LAi_SetActorType(sld);
			LAi_SetActorType(pchar);

			SetActorDialogAny2Pchar("Abracham_Gray", "", 2.0, 0.0);
			LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 2.0);
			LAi_ActorFollow(pchar, sld, "", 1.0);
			//компания....
			iTemp = 3 + rand(3);
			for(i = 0; i < iTemp; i++)
			{
				sTemp = "pirat" + (2 + rand(5));
				attrName = "goto" + (3 + i);
				sld = SetFantomDefenceForts("goto", attrName, PIRATE, "TmpEnemy");
			}
			LAi_group_SetRelation("TmpEnemy", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			LAi_group_ClearAllTargets();
			LAi_SetFightModeForOfficers(false);
			break;

		case "Travel_AfterDeckFight":
			AddQuestRecord("Gen_ContrabandTravel", "5");
			AddQuestUserData("Gen_ContrabandTravel", "sSex", GetSexPhrase(StringFromKey("quests_reaction_9"),StringFromKey("quests_reaction_10")));
			StartActorSelfDialog("GenTravel_Main");
			break;
		/////////////////////////////////////////////////////////////////////////////////
		//	END OF Корсарское метро
		/////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////
		// НАЧАЛО КВЕСТА - ДОСТАВКА ГРУЗА
		/////////////////////////////////////////////////////////////////////////////////
		case "trade_quest_open":
			int iTradeGoods    = sti(pchar.CargoQuest.iTradeGoods);
			int iQuantityGoods = sti(pchar.CargoQuest.iQuantityGoods);
			int iTradeNation   = sti(pchar.CargoQuest.iTradeNation);
			int iMoney         = sti(pchar.CargoQuest.iMoney);
            AddCharacterGoods(pchar, iTradeGoods, iQuantityGoods);
			//задаем квест
			SetTimerCondition("generate_trade_quest", 0, 0, sti(pchar.CargoQuest.iDaysExpired), false);

			pchar.quest.generate_trade_quest_progress = "begin";
			ReOpenQuestHeader("DELIVERY_TRADE_QUEST");
			AddQuestRecord("DELIVERY_TRADE_QUEST", "1");

			AddQuestUserDataForTitle("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			AddQuestUserDataForTitle("DELIVERY_TRADE_QUEST", "sTargetColony", XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));

			AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodQty", FindRussianQtyString(sti(pchar.CargoQuest.iQuantityGoods)));
			AddQuestUserData("DELIVERY_TRADE_QUEST", "sBaseColony", XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.CargoQuest.GiveTraderID)].city+"Gen"));
			AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
            attrName = "";
            if (pchar.CargoQuest.iTradeIsland != pchar.CargoQuest.iTradeColony)
            {
                attrName = StringFromKey("quests_reaction_11") + XI_ConvertString(pchar.CargoQuest.iTradeIsland+"Voc"); // belamour
            }
            AddQuestUserData("DELIVERY_TRADE_QUEST", "island", attrName);
    		AddQuestUserData("DELIVERY_TRADE_QUEST", "sTermsDelivery", FindRussianDaysString(makeint(pchar.CargoQuest.iDaysExpired)));
    		AddQuestUserData("DELIVERY_TRADE_QUEST", "sMoney", FindRussianMoneyString(iMoney));
            // немного веселой жизни
            TraderHunterOnMap(false);
		break;
		
		case "generate_trade_quest":
			if (pchar.quest.generate_trade_quest_progress == "begin")
			{
				pchar.quest.generate_trade_quest_progress = "failed";
				Log_SetStringToLog(StringFromKey("quests_reaction_12"));
				ChangeCharacterComplexReputation(pchar,"nobility", -10);
				OfficersReaction("bad");
				ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(characters[GetCharacterIndex(pchar.CargoQuest.TraderID)].nation)) + "hunter", 15);
                AddQuestRecord("DELIVERY_TRADE_QUEST", "3");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(sti(pchar.CargoQuest.iTradeGoods)));
			    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
			}
		break;
		/////////////////////////////////////////////////////////////////////////////////
		// КОНЕЦ КВЕСТА - ДОСТАВКА ГРУЗА
		/////////////////////////////////////////////////////////////////////////////////
		
		/////////////////////////////////////////////////////////////////////////////////
		// НАЧАЛО КВЕСТА - СПИМ В ТАВЕРНЕ
		/////////////////////////////////////////////////////////////////////////////////
		case "sleep_in_tavern":
			Statistic_AddValue(pchar, "TavernSleep", 1);
			Achievment_SetStat(24, 1);
			// Jason: сниманием штормление от пьянки
			if (CheckAttribute(pchar, "GenQuest.CamShuttle")) DeleteAttribute(pchar, "GenQuest.CamShuttle");
			// Jason: если Мэри или Элен в подругах и абордажниках - ночуем вместе
			if (GetCharacterIndex("Helena") != -1 && IsOfficer(characterFromId("Helena")) && CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				sld = characterFromId("Helena");
				ChangeCharacterAddressGroup(sld, pchar.location + "_upstairs", "goto", "goto3");
			}
			if (GetCharacterIndex("Mary") != -1 && IsOfficer(characterFromId("Mary")))
			{
				sld = characterFromId("Mary");
				ChangeCharacterAddressGroup(sld, pchar.location + "_upstairs", "goto", "goto3");
			}
			if (CheckAttribute(pchar, "GenQuest.LigaAttack.Go")) DoQuestReloadToLocation(pchar.location + "_upstairs", "goto", "goto1", "LigaAttack_LoginKillers"); //лига ночных убийц атакует
			else DoQuestReloadToLocation(pchar.location + "_upstairs", "goto", "goto1", "restore_hp");
		break;
		
		case "restore_hp":
			int iOfficer;
			LAi_SetCurHPMax(pchar);
			for (i=1; i<4; i++)
			{
				if (GetOfficersIndex(Pchar, i) != -1)
				{
					iOfficer = GetOfficersIndex(Pchar, i);
					LAi_SetCurHPMax(&characters[iOfficer]);
				}
			}			
		break;
		
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//											Киллеры Лиги в таверне
//////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "LigaAttack_LoginKillers":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
			chrDisableReloadToLocation = true;//закрыть локацию
			int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+10;
			if (iRank > 50) iRank = 50;
			int iScl = 30 + 3*sti(pchar.rank);
			if (iScl > 110) iScl = 110;
			for (i=1; i<=2; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("LigaHunter_"+i, "killer_"+(rand(4)+1), "man", "man", iRank, PIRATE, 0, true, "hunter")); // may-16
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_13", "pistol6", "bullet", iScl+50);
				LAi_SetActorType(sld);
				if (i == 1)
				{
					LAi_CharacterDisableDialog(sld);
					ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto2");
				}
				else
				{
					sld.dialog.Filename = "Quest\Other_quests_NPC.c";
					sld.dialog.currentnode = "LigaHunters";	
					sld.greeting = "hunter"; 
					ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto3");
					LAi_ActorDialog(sld, pchar, "", 2.0, 0); 
				}
				LAi_group_MoveCharacter(sld, "EnemyFight");
				DeleteAttribute(sld, "SaveItemsForDead");
				DeleteAttribute(sld, "DontClearDead");
			}
		break;
		
		case "LigaHunters_Dead":
			chrDisableReloadToLocation = false;
			LAi_group_Delete("EnemyFight");
			DeleteAttribute(pchar, "GenQuest.LigaAttack.Go");
		break;		
		
 		////////////////////////////////////////////////////////////////////////
		//  Начало    LOAN - ОГРАНИЧЕНИЕ ПО ВРЕМЕНИ
		////////////////////////////////////////////////////////////////////////
		case "LoansForAll":			// Addon 2016-1 Jason Пиратская линейка
			sTemp = pchar.quest.(qname).CityId;
			LoansMoneyAvenger(&Characters[GetCharacterIndex(sTemp + "_usurer")]);
			Characters[GetCharacterIndex(sTemp + "_usurer")].Dialog.CurrentNode = "DeadMotherfucker";
		break;
 		////////////////////////////////////////////////////////////////////////
		//  Конец    LOAN - ОГРАНИЧЕНИЕ ПО ВРЕМЕНИ
		////////////////////////////////////////////////////////////////////////				
		
   		////////////////////////////////////////////////////////////////////////
		//  Начало   Бордель
		//////////////////////////////////////////////////////////////////////// 
        case "Brothel_checkVisitTime":
			LocatorReloadEnterDisable(qname + "_Brothel", "reload2_back", true); //закрываем комнату
			sld = characterFromId(pchar.quest.(qname).HorseId);
			sld.location = qname+"_Brothel";
			sld.location.group = "goto";
			sld.location.locator = pchar.quest.(qname).locator;
			//ChangeCharacterAddressGroup(sld, qname+"_Brothel", "goto", pchar.quest.(qname).locator);
			DeleteAttribute(&characters[GetCharacterIndex(qname + "_Hostess")], "quest.selected"); //снимаем флаг у хозяйки
			//==> ноду девкам
			for(i=0; i<MAX_CHARACTERS; i++)
			{
				makeref(sld, Characters[i]);
				if (sld.location == qname+"_Brothel" && CheckAttribute(sld, "CityType") && sld.CityType == "horse")
				{
					sld.dialog.currentnode = "Horse_talk";
				}
			}
        break;
		
		// Sinistra катсцена с поцелуями
		case "Horse_Kiss":
			DialogExit();
			
			//if(CheckAttribute (pchar, "IsMushketer")) SetMainCharacterToMushketer("", false);
			TeleportCharacterToPosAy(pchar, 1.50, 0.00, -2.49, 0.00);
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "kiss", "1", 7.5);
			sld = characterFromId(pchar.horsekiss);
			TeleportCharacterToPosAy(sld, 1.50, 0.00, -1.89, 3.00);
			sld.model.animation = "woman";
			Characters_RefreshModel(sld);
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "kiss", "1", 7.5);
			locCameraFromToPos(2.37, 1.48, -1.02, true, -0.29, -0.14, -3.85);
			DoQuestCheckDelay("PlaySex_1", 7.5);
			DoQuestCheckDelay("Horse_Fuck", 7.5);
		break;
		
		case "Horse_Fuck":
			EndQuestMovie();
			bDisableCharacterMenu = false;
			locCameraTarget(PChar);
			locCameraFollow();
			LAi_SetPlayerType(pchar);
			ChangeCharacterAddressGroup(pchar, PChar.location, "goto", "goto2");
			
			sld = characterFromId(pchar.horsekiss);
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto1");
			LAi_SetStayType(sld);
			sld.dialog.currentnode = "Horse_AfterSex";
			
			// кач от борделя
			if (CheckNPCQuestDate(pchar, "BrothelSex"))
			{
				if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	
				{
					AddCharacterHealth(pchar, 10);
					AddCharacterMaxHealth(pchar, 1.0);
				}
				else AddCharacterHealth(pchar, 5);
				SetNPCQuestDate(pchar, "BrothelSex");
			}
			// изменение статусов
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "FencingS", -15);
			AddCharacterExpToSkill(pchar, "Pistol", -15);
		break;
		////////////////////////////////////////////////////////////////////////
		//  Конец    Бордель
		//////////////////////////////////////////////////////////////////////// 

		// универсальный диалогостартер (см метод  SetActorDialogAny2Pchar)
        case "ActorDialog_Any2Pchar":
            LAi_SetActorType(PChar);
            LAi_ActorWaitDialog(Pchar, characterFromID(Pchar.AutoQuest.NPCharId));
            LAi_ActorDialog(characterFromID(Pchar.AutoQuest.NPCharId), Pchar, Pchar.AutoQuest.Quest, stf(Pchar.AutoQuest.Time1), stf(Pchar.AutoQuest.Time2));
        break;

        case "OpenTheDoors":
            chrDisableReloadToLocation = false;
			bDisableFastReload = false; 
        break;

        case "CanEnterToMap":
            bQuestDisableMapEnter = false;
        break;

		case "CanNotEnterToMap": // patch-4
            bQuestDisableMapEnter = true;
			DoQuestCheckDelay("CanEnterToMap", 80.0);
        break;

		case "DeleteEnemyFight":
            LAi_group_Delete("EnemyFight");
        break;

        case "CloseBermudesDungeonDoor":
            LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", true);
			sld = characterFromId("Pirates_shipyarder");
			DeleteAttribute(sld, "Step_Door");
        break;

        case "CanFightCurLocation":
			LAi_LocationFightDisable(loadedLocation, false);
			chrDisableReloadToLocation = false;
        break;

        case "CannotFightCurLocation":
			LAi_LocationFightDisable(loadedLocation, true);
			chrDisableReloadToLocation = false;
        break;

        case "MainHeroFightModeOn":
			LAi_SetFightMode(pchar, true);
        break;

        case "MainHeroFightModeOff":
			LAi_SetFightMode(pchar, false);
			LAi_LockFightMode(pchar, true);
        break;

		case "ChurchNightGuard_timerInChurch_2":
			TavernWaitDate("wait_day");
		break;
		
		case "MayorSitBack": //посадить мэра обратно
			iTemp = GetCharacterIndex(Pchar.quest.MayorSitBack.mayorId)
			if (iTemp > 0)
			{
				sld = &characters[iTemp];
				sld.location = Pchar.quest.MayorSitBack.locationName;
				sld.location.group = "sit";
				sld.location.locator = Pchar.quest.MayorSitBack.locatorName;
				LAi_SetHuberTypeNoGroup(sld);
				RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
				RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
				RemoveCharacterEquip(pchar, MUSKET_ITEM_TYPE);
			}
        break;

		case "PlaySex_1":
			ResetSound();
			iTemp = rand(13)+1;
			switch (iTemp)
			{
				case 1: fTemp = 18.2; break;
				case 2: fTemp = 5.1;  break;
				case 3: fTemp = 19.3; break;
				case 4: fTemp = 8.2;  break;
				case 5: fTemp = 11.3; break;
				case 6: fTemp = 18.2; break;
				case 7: fTemp = 18.2; break;
				case 8: fTemp = 9.3;  break;
				case 9: fTemp = 19.4; break;
				case 10:fTemp = 12.2; break;
				case 11:fTemp = 19.4; break;
				case 12:fTemp = 12.3; break;
				case 13:fTemp = 10.2; break;
				case 14:fTemp = 11.2; break;
			}
			sGlobalTemp = iTemp;
			//LAi_FadeDelay(fTemp, "loading\inside\censored1.tga");
			//StartPictureAsVideo( "loading\inside\censored1.tga", fTemp );
			SetLaunchFrameFormParam("", "", 0, fTemp);
			SetLaunchFrameFormPic("loading\inside\censored1.tga");
            LaunchFrameForm();
			DoQuestCheckDelay("PlaySex_2", 1.0);			
		break;

		case "PlaySex_2":
			PlayStereoSound("sex\sex" + sGlobalTemp + ".wav");
            AddTimeToCurrent(2, rand(30));
			LAi_SetCurHPMax(pchar); // Rebbebion, полностью восстанавливаем здоровье и энергию
			if (pchar.location == "SanJuan_houseS1Bedroom")
			{
			    QuestSetCurrentNode("Isabella", "NewLife_afterSex");
			    LAi_SetStayType(CharacterFromID("Isabella"));
			}
			//квест официантки
			if (pchar.questTemp.different == "FackWaitress_facking")
			{
				sld = characterFromId("WairessQuest");
				ChangeCharacterAddress(sld, "none", "");
				AddCharacterExpToSkill(pchar, "Loyality", 20);
				if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	
				{
					AddCharacterHealth(pchar, 6);
					AddCharacterMaxHealth(pchar, 1.0);
				}
				else AddCharacterHealth(pchar, 3);
            	AddCharacterExpToSkill(pchar, "FencingS", -15);
            	AddCharacterExpToSkill(pchar, "Pistol", -15);
				ChangeCharacterComplexReputation(pchar,"nobility", -1);
				if (sti(pchar.questTemp.different.FackWaitress.Kick) != 1) 
				{
					pchar.questTemp.different = "FackWaitress_fackNoMoney";
					AddCharacterExpToSkill(pchar, "Fortune", 100);
				}
				pchar.money = sti(pchar.money) / sti(pchar.questTemp.different.FackWaitress.Kick);
				chrDisableReloadToLocation = false;
			}
			//квест развода хозяйки борделя
			if (pchar.questTemp.different == "HostessSex" && CheckAttribute(pchar, "questTemp.different.HostessSex.city"))
			{
				sld = characterFromId(pchar.questTemp.different.HostessSex.city + "_Hostess");
				ChangeCharacterAddressGroup(sld, pchar.questTemp.different.HostessSex.city + "_SecBrRoom", "goto", "goto8");
				LAi_SetOwnerTypeNoGroup(sld);
				DeleteAttribute(pchar, "questTemp.different.HostessSex");
				pchar.questTemp.different = "free";
			}
			//-->> Sinistra Ром на троих
			if (GetCharacterIndex(pchar.RomNaTroih_Shluha) != -1)
			{
				sld = CharacterFromID(pchar.RomNaTroih_Shluha);
				ChangeCharacterAddress(sld, "none", "");
				sld.lifeday = 0;
			}
			//<<-- Sinistra Ром на троих
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "EncGirl_facking")
			{
				sld = characterFromId("CangGirl");
				ChangeCharacterAddress(sld, "none", "");
				if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	
				{
					AddCharacterHealth(pchar, 10);
					AddCharacterMaxHealth(pchar, 1.0);
				}
				else AddCharacterHealth(pchar, 5);
				AddCharacterExpToSkill(pchar, "Loyality", 20);
				AddCharacterExpToSkill(pchar, "Fortune", 100);
            	AddCharacterExpToSkill(pchar, "FencingS", -20);
            	AddCharacterExpToSkill(pchar, "Pistol", -20);
				ChangeCharacterComplexReputation(pchar,"nobility", -1);
				pchar.money = sti(pchar.money) - makeint(sti(pchar.money)/15);
				chrDisableReloadToLocation = false;
				SetFunctionTimerCondition("EncGirl_SpeakTavernKeeper", 0, 0, 1, false);
			}
			if (CheckAttribute(pchar, "questTemp.Consumption.Sex"))//Jason, цена чахотки
			{
				LocatorReloadEnterDisable("PortSpein_tavern", "reload1_back", false); //открыть таверну
				LocatorReloadEnterDisable("PortSpein_tavern", "reload2_back", true); //закрыть комнату
				bDisableFastReload = false;//открыть переход
				if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	
				{
					AddCharacterHealth(pchar, 14);
					AddCharacterMaxHealth(pchar, 1.0);
				}
				else AddCharacterHealth(pchar, 7);
				ChangeCharacterComplexReputation(pchar, "nobility", -3);
				sld = characterFromId("PortSpein_waitress");
				ChangeCharacterAddressGroup(sld, "PortSpein_tavern", "goto", "goto1");
				LAi_SetWaitressType(sld);
				Consumption_Close();
			}
			if (pchar.location == "LosTeques_tavern_upstairs")//Jason
			{
				LocatorReloadEnterDisable("LosTeques_tavern", "reload1_back", false); //открыть таверну
				LocatorReloadEnterDisable("LosTeques_tavern", "reload2_back", true); //закрыть комнату
				bDisableFastReload = false;//открыть переход
				DeleteAttribute(pchar, "GenQuest.CannotWait");
				DeleteAttribute(pchar, "GenQuest.LosTequesSex");
				if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	
				{
					AddCharacterHealth(pchar, 10);
					AddCharacterMaxHealth(pchar, 1.0);
				}
				else AddCharacterHealth(pchar, 5);
				sld = characterFromId("MineFuckGirl");
				LAi_SetActorType(sld);
				ChangeCharacterAddress(sld, "none", "LosTeques_waittime");
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 4.0);
				DoQuestCheckDelay("LosTeques_waittime", 7.0);
			}
			if (CheckAttribute(pchar, "questTemp.FMQT") && pchar.location == "Tortuga_townhallBedroom")// Addon-2016 Jason, французские миниквесты (ФМК) Тортуга
			{
				FMQT_FinalWithSex();
			}
			if (pchar.location == "SantoDomingo_Brothel_room" && CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_2")// Addon 2016-1 Jason пиратская линейка
			{
				AddQuestRecord("Roger_1", "3");
				pchar.questTemp.Mtraxx = "jewelry_3";
				SetFunctionTimerCondition("Mtraxx_JewelryHavanaOver", 0, 0, 7, false); // таймер
				sld = characterFromId(sTotalTemp);
				ChangeCharacterAddressGroup(sld, "none", "", "");
				pchar.quest.mtr_jewelry_havana.win_condition.l1 = "location";
				pchar.quest.mtr_jewelry_havana.win_condition.l1.location = "Cuba2";
				pchar.quest.mtr_jewelry_havana.function = "Mtraxx_HavanaInfo";
				DeleteAttribute(pchar, "questTemp.Mtraxx.AffairOfHonor");
				DeleteAttribute(pchar, "questTemp.ZA.Block");
			}
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.WaitressSex")) {
				DeleteAttribute(pchar, "questTemp.HelenDrinking.WaitressSex");
				pchar.questTemp.HelenDrinking.DidWaitressSex = true;
				sld = CharacterFromID("SantaCatalina_waitress");
				ChangeCharacterAddressGroup(sld, "SantaCatalina_Tavern", "waitress", "barmen");
				LAi_SetWaitressTypeNoGroup(sld);
				sld.dialog.currentnode = "First time";
				if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	
				{
					AddCharacterHealth(pchar, 6);
					AddCharacterMaxHealth(pchar, 1.0);
				}
				else AddCharacterHealth(pchar, 3);
				chrDisableReloadToLocation = false;
				HelenDrinking_WaitressExit();
			}
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.AfterCaveSex1")) {
				DeleteAttribute(pchar, "questTemp.HelenDrinking.AfterCaveSex1");
				ChangeCharacterAddressGroup(pchar, PChar.location, "goto", "goto4");
				sld = CharacterFromID("Helena");
				sld.dialog.currentnode = "after_cave_sex";
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.AfterCaveSex2")) {
				DeleteAttribute(pchar, "questTemp.HelenDrinking.AfterCaveSex2");
				sld = CharacterFromID("Helena");
				sld.dialog.currentnode = "after_cave_sex_again";
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
		break;
		
		case "LosTeques_waittime":
			TavernWaitDate(sTotalTemp);
		break;

		case "SkritoeBessmertie":
			LAi_SetCurHP(pchar, 25.0);
			LAi_SetImmortal(pchar, false);
			LAi_SetCheckMinHP(pchar, 1, true, "SkritoeBessmertie");
		break;
		
		// belamour тут должен быть default: но наш компилятор решил читать между блоков )))
		if(HollandGambit_QuestComplete(sQuestName, qname)) return;
		if(Saga_QuestComplete(sQuestName, qname)) return;
		if(SharlieTrial_QuestComplete(sQuestName, qname)) return;
		if(Slavetrader_QuestComplete(sQuestName, qname)) return;
		if(SharlieFinal_QuestComplete(sQuestName, qname)) return;
		if(Roger_QuestComplete(sQuestName, qname)) return;
		if(RedChieftain_QuestComplete(sQuestName, qname)) return;
		if(FalseTrace_QuestComplete(sQuestName, qname)) return;
		if(Regatta_QuestComplete(sQuestName, qname)) return;
		if(Portugal_QuestComplete(sQuestName, qname)) return;
		if(Consumption_QuestComplete(sQuestName, qname)) return;
		if(Caleuche_QuestComplete(sQuestName, qname)) return;
		if(FMQ_QuestComplete(sQuestName, qname)) return;
		if(Patria_QuestComplete(sQuestName, qname)) return;
		if(GoldenGirl_QuestComplete(sQuestName, qname)) return;
		if(LongHappy_QuestComplete(sQuestName, qname)) return;
		if(IslaMona_QuestComplete(sQuestName, qname)) return;
		if(Longway_QuestComplete(sQuestName, qname)) return;
		if(HelenDrinking_QuestComplete(sQuestName, qname)) return;
		if(ChickenGod_QuestComplete(sQuestName, qname)) return;
		if(Tonzag_QuestComplete(sQuestName, qname)) return;
		if(Knippel_QuestComplete(sQuestName, qname)) return;
		if(Duran_QuestComplete(sQuestName, qname)) return;
		if(BlackMark_QuestComplete(sQuestName, qname)) return;
		if(Santa_Misericordia_QuestComplete(sQuestName, qname)) return;
		if(GenQuests_QuestComplete(sQuestName, qname)) return;
		if(MiniQuests_QuestComplete(sQuestName, qname)) return;
		if(LadyBeth_QuestComplete(sQuestName, qname)) return;
		if(Memento_QuestComplete(sQuestName, qname)) return;
		if(DiegoDeLanda_QuestComplete(sQuestName, qname)) return;
		if(SharlieTutorial_QuestComplete(sQuestName, qname)) return;
		if(DarkWatersOfHealing_QuestComplete(sQuestName, qname)) return;
		if(EdgesJustice_QuestComplete(sQuestName, qname)) return;
		if(VPVL_QuestComplete(sQuestName, qname)) return;
		if(MysteryOfBetsyPrice_QuestComplete(sQuestName, qname)) return;
	}	
}

// boal -->
////////////////////////   общие методы //////////////////////////
void SetActorDialogAny2Pchar(string _charId, string _doQuest, float time1, float time2)
{
    Pchar.AutoQuest.NPCharId = _charId;
    Pchar.AutoQuest.Quest    = _doQuest;
    Pchar.AutoQuest.Time1    = time1;
    Pchar.AutoQuest.Time2    = time2;
}

//для универсализации (navy 17.10.05)
//уcтановки для телепорта ГГ в любую локацию с задержкой или без. 
//Для отложенного вызова напр. AddDialogExitQuest()
void SetAnyReloadToLocation(string idLocation, string idGroup, string idLocator, string questName, int delayMonth, int delayDay, int delayHour, int delayMin)
{
    ref PChar = GetMainCharacter();

	PChar.AutoQuest.delayMonth	= delayMonth;
	PChar.AutoQuest.delayDay	= delayDay;
	PChar.AutoQuest.delayHour	= delayHour;
	PChar.AutoQuest.delayMin	= delayMin;

	PChar.AutoQuest.idLocation	= idLocation;
	PChar.AutoQuest.idGroup		= idGroup;
	PChar.AutoQuest.idLocator	= idLocator;
	PChar.AutoQuest.questName	= questName;
}

// Инициация таблички В это время на Беде  -->
// _FrameText - текст  Перенос строки делать "текст"+ NewStr() +"текст"
// _FrameQuest - квест после завершения таблички, если == "Reload_To_Location" см. SetLaunchFrameReloadLocationParam
// если же будет == "Run_Function" см. SetLaunchFrameRunFunctionParam
// _delay - время в с. отложения вызова таблички (нужно для неконфликта с заставкой загрузки локаций, где-то 0.1-1.5с)
// _autoEnd - время в с. автозавершения показа таблички, 4-6с на фразу
void SetLaunchFrameFormParam(string _FrameText, string _FrameQuest, float _delay, float _autoEnd)
{
    pchar.AutoQuest.FrameText    = _FrameText;
    pchar.AutoQuest.FrameQuest   = _FrameQuest;
    pchar.AutoQuest.FrameDelay   = _delay;
    pchar.AutoQuest.FrameAutoEnd = _autoEnd;
}

void SetLaunchFrameFormPic(string _FramePic)
{
    pchar.AutoQuest.FramePic    = _FramePic;
}
// метод для инициации перехода после таблички
void SetLaunchFrameReloadLocationParam(string idLocation, string idGroup, string idLocator, string questName)
{
    pchar.AutoQuest.FrameLocation      = idLocation;
    pchar.AutoQuest.FrameGroup         = idGroup;
    pchar.AutoQuest.FrameLocator       = idLocator;
    pchar.AutoQuest.FrameLocationQuest = questName;
}
// метод для вызова метода из кода после таблички _func - метод, _delay - задержка вызова метода после таблички в с.
void SetLaunchFrameRunFunctionParam(string _func, float _delay)
{
    pchar.AutoQuest.FrameFunction      = _func;
    pchar.AutoQuest.FrameFunctionDelay = _delay;
}
// Инициация таблички В это время на Беде  <--

void WaitNextHours(string qName)
{
	// belamour прерывание ночной приключенец -->
	if(CheckAttribute(pchar,"GenQuest.NightAdventureId"))
	{
		if(GetCharacterIndex(pchar.GenQuest.NightAdventureId) != -1)
		{
			ref sld = characterFromId(pchar.GenQuest.NightAdventureId);
			ChangeCharacterAddressGroup(sld, "none", "", "");
		}
		SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
	}
	// <-- прерывание ночного приключенца 
	string sHour;
	float locx, locy, locz;
	GetCharacterPos(pchar, &locx, &locy, &locz);
	pchar.locx = locx;
	pchar.locy = locy;
	pchar.locz = locz;
	sHour = StringFromKey("quests_reaction_13");
	if(sti(pchar.quest.waithours) == 1)		sHour = StringFromKey("quests_reaction_14");
	if(sti(pchar.quest.waithours) == 24)	sHour = StringFromKey("quests_reaction_15");
	if(isShipInside(pchar.location))
	{
		SetLaunchFrameFormParam(sHour, "", 0.1, 2.0);
	}
	else
	{
		SetLaunchFrameFormParam(sHour, "Reload_To_Location", 0.1, 2.0);
		SetLaunchFrameReloadLocationParam(pchar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"), "LocTeleport");
	}
	
	WaitDate("", 0, 0, 0, sti(pchar.quest.waithours), 0);
	LaunchFrameForm();
	DeleteAttribute(pchar,"quest.waithours");
	RefreshLandTime();
	RecalculateJumpTable();
	Whr_UpdateWeather();
}

//Sith проматывание дней
void WaitNextDays(string qName)
{
	string sDay;
	float locx, locy, locz;
	GetCharacterPos(pchar, &locx, &locy, &locz);
	pchar.locx = locx;
	pchar.locy = locy;
	pchar.locz = locz;
	sDay = StringFromKey("quests_reaction_16");
	if(sti(pchar.quest.waithours) == 1)	sDay = StringFromKey("quests_reaction_15");
	if(isShipInside(pchar.location))
	{
		SetLaunchFrameFormParam(sDay, "", 0.1, 2.0);
	}
	else
	{
		SetLaunchFrameFormParam(sDay, "Reload_To_Location", 0.1, 2.0);
		SetLaunchFrameReloadLocationParam(pchar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"), "LocTeleport");
	}
	for (int i = 0; i < sti(pchar.quest.waithours); i++) WaitDate("", 0, 0, 1, 0, 0);	
	// WaitDate("", 0, 0, sti(pchar.quest.waithours), 0, 0);
	LaunchFrameForm();
	DeleteAttribute(pchar,"quest.waithours");
	RefreshLandTime();
	RecalculateJumpTable();
	Whr_UpdateWeather();
}

void RemovePatent()
{
	RemoveCharacterEquip(pchar, "patent");
    if (CheckCharacterItem(Pchar, "patent_eng"))
    {
        TakeItemFromCharacter(pchar, "patent_eng");
        ChangeCharacterComplexReputation(pchar,"nobility", -10);
    }
    if (CheckCharacterItem(Pchar, "patent_fra"))
    {
        TakeItemFromCharacter(pchar, "patent_fra");
        ChangeCharacterComplexReputation(pchar,"nobility", -10);
    }
    if (CheckCharacterItem(Pchar, "patent_spa"))
    {
        TakeItemFromCharacter(pchar, "patent_spa");
        ChangeCharacterComplexReputation(pchar,"nobility", -10);
    }
    if (CheckCharacterItem(Pchar, "patent_hol"))
    {
        TakeItemFromCharacter(pchar, "patent_hol");
        ChangeCharacterComplexReputation(pchar,"nobility", -10);
    }
}

void StartActorSelfDialog(string _CurrentNode)
{
    LAi_SetActorType(pchar);
    LAi_CharacterSaveAy(pchar);
    locCameraSleep(true);
    float fAng;
	SendMessage(&locCamera, "le", MSG_CAMERA_GET_AY, &fAng);
    CharacterTurnAy(pchar, fAng-PI);
    pchar.Dialog.CurrentNode = _CurrentNode;
    LAi_ActorSelfDialog(pchar, "pchar_back_to_player");
}

// подъем флагов
void Flag_PIRATE()
{
	PChar.nation	= PIRATE;
	Ship_FlagRefresh(PChar); //флаг на лету
	SetNationToOfficers(PIRATE);
	
	SetNationRelation2MainCharacter(ENGLAND, RELATION_ENEMY);
	SetNationRelation2MainCharacter(FRANCE, RELATION_ENEMY);
	SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
	
	SetNationRelation2MainCharacter(PIRATE, RELATION_FRIEND);
	SetNationRelation2MainCharacter(HOLLAND, RELATION_ENEMY);
	
	LAi_group_SetRelation("PIRATE_CITIZENS", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
	//Relation_PIRATE_SOLDIERS();
	// сторожевики Тортуги
	if (pchar.location == "Tortuga" && !CheckAttribute(pchar, "questTemp.Sharlie.DelTerGuard")) Tortuga_ShipGuardAttack();
	// капеллан
	if (CheckAttribute(pchar, "questTemp.ShipCapellan.Yes")) ShipCapellan_Remove();
	// Addon 2016-1 Jason Пиратская линейка
	if (CheckAttribute(pchar, "questTemp.Mtraxx.Ignasio.Flag"))
	{
		DeleteAttribute(pchar, "questTemp.Mtraxx.Ignasio.Signal");
		DeleteAttribute(pchar, "questTemp.Mtraxx.Ignasio.Flag");
		Mtraxx_CorridaIgnasioFailFlag();
	}
	LAi_group_ClearAllTargets();
	DoQuestCheckDelay("NationUpdate", 3.0);
	UpdateRelations();
	RefreshBattleInterface();
	wdmSetNationFlag(sti(pchar.nation));
	SetSchemeAfterFlagRise();
}            

void Flag_FRANCE()
{
	PChar.nation	= FRANCE;
    Ship_FlagRefresh(PChar); //флаг на лету
    SetNationToOfficers(FRANCE);

    SetNationRelation2MainCharacter(ENGLAND, GetNationRelation(ENGLAND, FRANCE));
    SetNationRelation2MainCharacter(FRANCE, RELATION_FRIEND);
    SetNationRelation2MainCharacter(SPAIN, GetNationRelation(FRANCE, SPAIN));
    SetNationRelation2MainCharacter(PIRATE, RELATION_ENEMY);

    SetNationRelation2MainCharacter(HOLLAND, GetNationRelation(FRANCE, HOLLAND));

    LAi_group_SetRelation("FRANCE_CITIZENS", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL); //LAI_GROUP_FRIEND);
    //Relation_FRANCE_SOLDIERS();
	// Addon 2016-1 Jason Пиратская линейка
	if (CheckAttribute(pchar, "questTemp.Mtraxx.Ignasio.Flag"))
	{
		DeleteAttribute(pchar, "questTemp.Mtraxx.Ignasio.Signal");
		DeleteAttribute(pchar, "questTemp.Mtraxx.Ignasio.Flag");
		Mtraxx_CorridaIgnasioFailFlag();
	}
    LAi_group_ClearAllTargets();
    DoQuestCheckDelay("NationUpdate", 3.0);
    UpdateRelations();
	RefreshBattleInterface();
	wdmSetNationFlag(sti(pchar.nation));
	SetSchemeAfterFlagRise();
}

void Flag_ENGLAND()
{
	PChar.nation	= ENGLAND;
    Ship_FlagRefresh(PChar); //флаг на лету
    SetNationToOfficers(ENGLAND);

	SetNationRelation2MainCharacter(ENGLAND, RELATION_FRIEND);
	SetNationRelation2MainCharacter(FRANCE, GetNationRelation(ENGLAND, FRANCE));
	SetNationRelation2MainCharacter(SPAIN, GetNationRelation(ENGLAND, SPAIN));
	SetNationRelation2MainCharacter(PIRATE, RELATION_ENEMY);
    SetNationRelation2MainCharacter(HOLLAND, GetNationRelation(ENGLAND, HOLLAND));

    LAi_group_SetRelation("ENGLAND_CITIZENS", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
    //Relation_ENGLAND_SOLDIERS();
    LAi_group_ClearAllTargets();
    DoQuestCheckDelay("NationUpdate", 3.0);
    UpdateRelations();
	RefreshBattleInterface();
	wdmSetNationFlag(sti(pchar.nation));
	SetSchemeAfterFlagRise();
}

void Flag_SPAIN()
{
	PChar.nation = SPAIN;
    Ship_FlagRefresh(PChar); //флаг на лету
    SetNationToOfficers(SPAIN);

	SetNationRelation2MainCharacter(ENGLAND, GetNationRelation(ENGLAND, SPAIN));
	SetNationRelation2MainCharacter(FRANCE, GetNationRelation(FRANCE, SPAIN));
	SetNationRelation2MainCharacter(SPAIN, RELATION_FRIEND);
	SetNationRelation2MainCharacter(PIRATE, RELATION_ENEMY);
    SetNationRelation2MainCharacter(HOLLAND, GetNationRelation(SPAIN, HOLLAND));

    LAi_group_SetRelation("SPAIN_CITIZENS", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
    //Relation_SPAIN_SOLDIERS();
	if (pchar.location == "Tortuga" && !CheckAttribute(pchar, "questTemp.Sharlie.DelTerGuard")) Tortuga_ShipGuardAttack();
	// Addon 2016-1 Jason Пиратская линейка
	if (CheckAttribute(pchar, "questTemp.Mtraxx.Ignasio.Flag"))
	{
		DeleteAttribute(pchar, "questTemp.Mtraxx.Ignasio.Signal");
		DeleteAttribute(pchar, "questTemp.Mtraxx.Ignasio.Flag");
		Mtraxx_CorridaIgnasioRightFlag();
	}
    LAi_group_ClearAllTargets();
    DoQuestCheckDelay("NationUpdate", 3.0);
    UpdateRelations();
	RefreshBattleInterface();
	wdmSetNationFlag(sti(pchar.nation));
	SetSchemeAfterFlagRise();
}

void Flag_HOLLAND()
{
	PChar.nation	= HOLLAND;
    Ship_FlagRefresh(PChar); //флаг на лету
    SetNationToOfficers(HOLLAND);

    SetNationRelation2MainCharacter(ENGLAND, GetNationRelation(ENGLAND, HOLLAND));
    SetNationRelation2MainCharacter(FRANCE, GetNationRelation(FRANCE, HOLLAND));
    SetNationRelation2MainCharacter(SPAIN, GetNationRelation(SPAIN, HOLLAND));
    SetNationRelation2MainCharacter(PIRATE, RELATION_ENEMY);
    SetNationRelation2MainCharacter(HOLLAND, RELATION_FRIEND);

    LAi_group_SetRelation("HOLLAND_CITIZENS", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
    //Relation_HOLLAND_SOLDIERS();
    LAi_group_ClearAllTargets();
    DoQuestCheckDelay("NationUpdate", 3.0);
    UpdateRelations();
	RefreshBattleInterface();
	wdmSetNationFlag(sti(pchar.nation));
	SetSchemeAfterFlagRise();
}

void Flag_Rerise()
{
	switch (sti(PChar.nation))
	{
    	case ENGLAND:	Flag_ENGLAND();	break;
    	case FRANCE:	Flag_FRANCE();	break;
    	case SPAIN:		Flag_SPAIN();	break;
    	case PIRATE:	Flag_PIRATE();	break;
    	case HOLLAND:	Flag_HOLLAND();	break;
	}
}
