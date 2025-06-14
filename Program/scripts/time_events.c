
void ActivateTimeEvents()
{

}

//////////////////////// boal SLiB ////////////////////////////////
void SalaryNextDayUpdate()
{
	if (sti(NullCharacter.SalayPayMonth) != GetDataMonth() && !bDisableMapEnter) // boal
	{
		// проверка на наличие кому платить -->
		int nPaymentQ = 0;
		int i, cn;
		ref chref;
		
		for (i=0; i<COMPANION_MAX; i++)
		{
			cn = GetCompanionIndex(pchar, i);
			if (cn >= 0)
			{
				chref = GetCharacter(cn);
				if (GetRemovable(chref)) // считаем только своих, а то вских сопровождаемых кормить!!!
				{
					nPaymentQ += GetSalaryForShip(chref);
				}
			}
		}
		
		// проверка на наличие кому платить <--
		NullCharacter.SalayPayMonth = GetDataMonth(); // boal
		if (nPaymentQ > 0)
		{
			if( CheckAttribute(pchar,"CrewPayment") )
			{
				nPaymentQ += makeint(pchar.CrewPayment); // а тут помним все до копейки!
			}
			if( CheckAttribute(pchar,"Partition.MonthPart") )
			{
				nPaymentQ += makeint(pchar.Partition.MonthPart); // доля за месяц
				DeleteAttribute(pchar,"Partition.MonthPart")
			}
			
			pchar.CrewPayment = nPaymentQ;
			LaunchMoneyGraphCollect();
			
			if (!dialogRun && !bQuestCheckProcessFreeze && !bAbordageStarted) // можно показать
			{
				LaunchSalaryScreen("");
			}
			else
			{
				Pchar.quest.LaunchSalaryScreen.win_condition.l1 = "MapEnter";
				PChar.quest.LaunchSalaryScreen.win_condition    = "LaunchSalaryScreen";
				PChar.quest.LaunchSalaryScreen.function         = "LaunchSalaryScreen";
			}
		}
	}
}

#event_handler("EvSituationsUpdate","WorldSituationsUpdate");
void WorldSituationsUpdate()
{
	int 	iStep = GetEventData();

	switch(iStep)
	{
		case 0:		
			DailyEatCrewUpdate();
		
            DeleteAttribute(pchar, "SkipEshipIndex");// boal
			Log_QuestInfo("WorldSituationsUpdate DailyEatCrewUpdate");

			UpdateSeeds();

			CheckCharactersUpdateItems();

			if (CheckAttribute(pchar, "questTemp.LSC")) 
			{ //Jason: еженедельное обновление паролей кланов LSC и ежедневное вытирание
				if (GetDataDay() == 7 || GetDataDay() == 14 || GetDataDay() == 21 || GetDataDay() == 28)
				{
					sNrvParol = UpdateLSCClanParol();
					sRvdParol = UpdateLSCClanParol();
					if (CheckAttribute(pchar, "questTemp.LSC.NParol_bye")) DeleteAttribute(pchar, "questTemp.LSC.NParol_bye");
					if (CheckAttribute(pchar, "questTemp.LSC.RParol_bye")) DeleteAttribute(pchar, "questTemp.LSC.RParol_bye");
				}
				if (CheckAttribute(pchar, "questTemp.LSC.parol_nrv")) DeleteAttribute(pchar, "questTemp.LSC.parol_nrv");
				if (CheckAttribute(pchar, "questTemp.LSC.parol_rvd")) DeleteAttribute(pchar, "questTemp.LSC.parol_rvd");
			} 
			if (CheckAttribute(pchar, "questTemp.Saga.JessOnShip")) 
			{ //Jason: отрицательные явления при наличии на корабле Джессики
				AddCrewMorale(pchar, -5);
				ChangeOfficersLoyality("bad_all", 1);
				AddCharacterHealth(pchar, -2);
			}
			// трем эскадру у Тортуги
			Tortuga_DeleteShipGuard();
		break;
		
		case 1:			
			if(bRains) Whr_RainFogGenerator(); // генератор дождей и туманов в локациях

			SalaryNextDayUpdate();  // зряплата
			Log_QuestInfo("WorldSituationsUpdate SalaryNextDayUpdate");

			if (rand(2) == 0) Norman_ChangeFesivalFace(); // выходки Нормана
			if (GetDataDay() == 5 && CheckAttribute(pchar, "questTemp.OilTrade")) DoQuestFunctionDelay("Oil_SetSergioToMayak", 1.0); // генератор смол
			if (GetDataDay() == 1 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && !CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.IslandLock")) // Addon 2016-1 Jason пиратская линейка
			{
				for (int i=0; i<MAX_ISLANDS; i++)
				{				
					if (!CheckAttribute(&Islands[i], "hidden")) Island_SetReloadEnableGlobal(Islands[i].id, true);
				}
			}

			// Мерзкий Божок - без НИ
			if (GetDLCenabled(DLC_APPID_2) && !CheckAttribute(pchar, "questTemp.CG_SpawnAguebana") && pchar.rank >= 9) DoQuestFunctionDelay("ChickenGod_BrothelCheck", 1.0);
			// Чёрная Метка - без НИ
			if (GetDLCenabled(DLC_APPID_3) && !CheckAttribute(pchar, "questTemp.BM_StartQuest") && pchar.rank >= 5) DoQuestCheckDelay("BM_StartQuest", 1.0);
			if (GetDLCenabled(DLC_APPID_4))
			{
				if(!CheckAttribute(pchar, "questTemp.SantaMisericordia")) SantaMisericordia_init();
				else if (GetDataDay() == 4) CheckSantaMisericordia();
			}
			if (GetDLCenabled(DLC_APPID_5))
			{	
				if(!CheckAttribute(pchar, "questTemp.LadyBeth"))
				{
					if(SandBoxMode) LadyBeth_init();
					else if (CheckAttribute(pchar, "questTemp.TrialEnd")) LadyBeth_init();
				}
				else if(GetDataDay() == 13)
				{
					CheckLadyBeth();
				}
			}
			if (GetDLCenabled(DLC_APPID_6))
			{
				if(!CheckAttribute(pchar, "questTemp.Memento"))
				{
					if(SandBoxMode) Memento_init();
					else if (CheckAttribute(pchar, "questTemp.TrialEnd")) Memento_init();
				}
				else if(GetDataDay() == 6)
				{
					CheckMemento();
				}
			}
			CheckAchievments();
		break;
		
		case 2:				
			// Jason: ежедневная переустановка сторожевиков Тортуги
			Tortuga_SetShipGuard();
			ProcessHullDecrease();	// учёт безвозвратной убыли корпуса
			ProcessDayRepair();
			
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.CharleePrince"))
			{
				if (GetDataDay() % 5 == 0)
				{
					ChangeCharacterComplexReputation(pchar, "nobility", -1);
				}
				if (GetDataDay() % 10 == 0)
				{
					OfficersReaction("bad");
				}
			}
		break;
		
		case 3:				
			Group_FreeAllDead();

			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria.Governor") && GetDataDay() == 15)
			{
				AddMoneyToCharacter(pchar, 100000);
				log_info(StringFromKey("time_events_1"));
			}
			if (!CheckAttribute(pchar, "questTemp.Patria_BugsFixer")) Patria_BugsFixer(); // 17-add	
			
			if (CheckAttribute(pchar, "questTemp.LongHappy.BaronPart") && GetDataDay() == 5)
			{
				LongHappy_GiveBaronPart();
				log_info(StringFromKey("time_events_2"));
			}	
			
			// belamour legendary edition генерация призов за штурм колоний
			if(GetDataDay() == 13)
			{
				pchar.colonyprise.good = 28+rand(6);
				pchar.colonyprise.item = rand(4);
			}			
			
		break;
		
		case 4:		
			QuestActions(); //eddy	
			// Jason Исла Мона
			if (CheckAttribute(pchar, "questTemp.IslaMona.Factory") && GetDataDay() == 15)		 
			{
				IslaMona_FactoryPart();
			}	
		break;
		
		case 5:
			wdmEmptyAllOldEncounter();// homo чистка энкоутеров				
		break;
		
		case 6:
			UpdateCrewExp();  // изменение опыта команды	
		break;
		
		case 7:
			UpdateCrewInColonies(); // пересчет наёмников в городах	
		break;
		
		case 8:
			if(IsEntity(&worldMap))
			{
				EmptyAllFantomCharacter(); // трем НПС
				wdmEmptyAllDeadQuestEncounter();
				WM_SetNationsThreat();	// обновляем индикаторы угрозы
			}
		break;
		
		case 9:		
			if(GetDataDay() == 28) UpdateReputation();
		break;
		
		case 10:
			GenerateRumour(); //homo 05/07/06
			pchar.goldenfleet.capname = GetPersonaName();
		break;		
		
	}

	iStep++;
	InterfaceStates.WorldSituationUpdateStep = iStep;

	if(iStep <= 10)
	{
		PostEvent("EvSituationsUpdate", 1000, "l", iStep);
	}
}


//////////////////////////////// начало игры - туториал ////////////////////////////////
void Tut_StartGame(string sQuest)
{
	StartQuestMovie(true, false, true);
    SetCharacterTask_None(GetMainCharacter());
    LAi_LockFightMode(Pchar, true);
	PChar.GenQuest.CallFunctionParam = "Tut_Continue";
	DoQuestCheckDelay("CallFunctionParam", 5.0);
	LAi_LocationFightDisable(loadedLocation, true);
	DoQuestFunctionDelay("Tut_locCamera_1", 0.1);
	LAi_SetStayType(pchar);
	TeleportCharacterToPosAy(pchar, -1.00, 3.20, 11.60, -0.90);
}

void Tut_locCamera_1(string _tmp)
{
    locCameraFromToPos(-4.33, 3.66, 13.51, true, -0.81, 3.10, 10.99);
}

void Tut_Continue()
{
    ref sld;
    LAi_LocationFightDisable(loadedLocation, false);
    LAi_SetFightMode(Pchar, false);
    LAi_LockFightMode(pchar, true);
    
	sld = GetCharacter(NPC_GenerateCharacter("Sailor_1", "Alonso", "man", "man", 1, PIRATE, 0, false, "soldier"));
    sld.name 	= StringFromKey("time_events_7");
    sld.lastname 	= "";
    sld.Dialog.CurrentNode = "First time";
    sld.dialog.filename = "Quest\StartGame_dialog.c";
    sld.greeting = "Teacher_pirat";

    SetSPECIAL(sld, 9,8,10,3,6,10,4);
    InitStartParam(sld);
	LAi_SetHP(sld, GetCharacterBaseHPValue(pchar)/2, GetCharacterBaseHPValue(pchar)/2);
    SetEnergyToCharacter(sld);

    LAi_SetCheckMinHP(sld, 1, true, "Tut_StartGame_CheckMinHP_1");
    GiveItem2Character(sld, "blade_11");
	EquipCharacterByItem(sld, "blade_11");
	// пустоля нет, лечилок нет
    ChangeCharacterAddressGroup(sld, "Ship_deck_Low", "reload", "reload1");
    LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 5.0, 0);

	// генерим второго матроса, но пока не ставим
	sld = GetCharacter(NPC_GenerateCharacter("Sailor_2", "citiz_31", "man", "man", 1, PIRATE, 0, false, "soldier"));
    sld.name 	= StringFromKey("time_events_5");
    sld.lastname 	= StringFromKey("time_events_6");

    SetSPECIAL(sld, 8,10,9,3,6,10,4);
    InitStartParam(sld);
	LAi_SetHP(sld, GetCharacterBaseHPValue(pchar)/2, GetCharacterBaseHPValue(pchar)/2);
    SetEnergyToCharacter(sld);

    LAi_SetCheckMinHP(sld, 1, true, "Tut_StartGame_CheckMinHP_2");
    GiveItem2Character(sld, "blade_12");
	EquipCharacterByItem(sld, "blade_12");
	GiveItem2Character(sld, "pistol1");
	EquipCharacterByItem(sld, "pistol1");
		
	AddItems(sld, "bullet", 30);
	AddItems(sld, "gunpowder", 30);
	LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");	
	// лечилок нет
    sld.location = "Ship_deck_Low";  // чтоб не терся, пока его нет
	//раскидаем квестовых нпс по локациям
	//SetQuestsCharacters();	
}

void Tut_RestoreState()
{
	ref sld;
	
	pchar.Health.Damg = 0.0; // здоровье бережем
	pchar.Health.weekDamg = 0.0;

	LAi_SetCurHPMax(pchar);
	LAi_SetCheckMinHP(pchar, 1, true, "Tut_StartGame_CheckMinHP_Hero");
	LAi_SetImmortal(pchar, false);
	
	sld = characterFromID("Sailor_1");
	LAi_SetCurHPMax(sld);
	LAi_SetCheckMinHP(sld, 1, true, "Tut_StartGame_CheckMinHP_1");
	LAi_SetImmortal(sld, false);
	
	sld = characterFromID("Sailor_2");
	LAi_SetCurHPMax(sld);
	LAi_SetCheckMinHP(sld, 1, true, "Tut_StartGame_CheckMinHP_2");
	LAi_SetImmortal(sld, false);
	
	DeleteAttribute(pchar, "HeroParam.Teach_beat");
}

void Tut_TeachBattle()
{
	ref sld;
	
	LAi_SetPlayerType(pchar);
	LAi_SetFightMode(Pchar, true);
	sld = characterFromID("Sailor_1");
	LAi_SetWarriorType(sld);
    LAi_group_MoveCharacter(sld, "TmpEnemy");
	
	if (sti(pchar.HeroParam.Teach_battle) == 2)
	{
        sld = characterFromID("Sailor_2");
		if (!IsEntity(sld))
        {
        	ChangeCharacterAddressGroup(sld, "Ship_deck_Low", "reload", "reload1");
        }
		LAi_SetWarriorType(sld);
	    LAi_group_MoveCharacter(sld, "TmpEnemy");
	}
	LAi_group_SetHearRadius("TmpEnemy", 100.0);
    LAi_group_FightGroupsEx("TmpEnemy", LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
    LAi_group_SetRelation("TmpEnemy", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	if(CheckAttribute(pchar, "systeminfo.tutorial.firstfight1_SandBox"))
	{
		DoQuestFunctionDelay("Tutorial_firstfight1_SandBox", 0.2);
		DeleteAttribute(pchar, "systeminfo.tutorial.firstfight1_SandBox");
	}
}

void Tut_StartDialog()
{
	ref sld = characterFromID("Sailor_1");
	
	if (CheckAttribute(pchar, "HeroParam.Teach_beat"))
	{ // признак, что выиграл
		if (sti(pchar.HeroParam.Teach_beat) == 3)
		{
		    sld.Dialog.CurrentNode = "Teach_battle_win_2";
		}
		else
		{
			if (sti(pchar.HeroParam.Teach_battle) == 1)
			{
				sld.Dialog.CurrentNode = "Teach_battle_win";
			}
			else
			{
			    sld.Dialog.CurrentNode = "Teach_battle_win_3";
			}
		}
	}
	else
	{
		sld.Dialog.CurrentNode = "Teach_battle_lose";
	}
	LAi_ActorWaitDialog(pchar, sld);
	LAi_ActorDialog(sld, pchar, "", 4.0, 0);
}
