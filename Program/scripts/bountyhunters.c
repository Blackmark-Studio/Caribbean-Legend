
void SeaHunterCheck_eng(string qName) {SeaHunterCheck(ENGLAND);}
void SeaHunterCheck_fra(string qName) {SeaHunterCheck(FRANCE);}
void SeaHunterCheck_spa(string qName) {SeaHunterCheck(SPAIN);}
void SeaHunterCheck_hol(string qName) {SeaHunterCheck(HOLLAND);}

void SeaHunterCheck(int iNation)
{
	int    i, iTemp;
	string sGroup, sCapId;
	ref    sld;

    sCapId = NationShortName(iNation);
	SetFunctionTimerCondition("SeaHunterCheck_" + sCapId, 0, 0, 6 + rand(20), true);
	if (CheckAttribute(PChar, "GenQuest.SeaHunter2Pause")) return; // Captain Beltrop, 12.09.21, морские ОЗГи
    UpdatePlayerSquadronPower();

    // открыть, если не нужны мирные охотники if(NationsRelations2MainCharacter[iNation] != RELATION_ENEMY) return;

    iTemp = wdmGetNationThreat(iNation);
    if (iTemp != 0)
    {
        string sMapShip = Nations[iNation].worldMapShip + "_";
        int iShips[4];
        iShips[0] = 0;
        iShips[1] = 0;
        iShips[2] = 0;
        iShips[3] = 0;

        if(iTemp == 1) {
            sMapShip += "sloop";
            iShips[0] = 5;
            iShips[1] = 5;
        }
        else if(iTemp == 2) {
            sMapShip += "sloop";
            iShips[0] = 4;
            iShips[1] = 4;
        }
        else if(iTemp == 3) {
            sMapShip += "bark";
            iShips[0] = 3 + rand(1);
            iShips[1] = 3 + rand(1);
            iShips[2] = 3 + rand(1);
        }
        else if(iTemp == 4) {
            sMapShip += "bark";
            iShips[0] = 2 + rand(1);
            iShips[1] = 2 + rand(1);
            iShips[2] = 2 + rand(1);
        }
        else {
            sMapShip += "frigate";
            iShips[0] = 2 + rand(1);
            iShips[1] = 2 + rand(1);
            iShips[2] = 2 + rand(1);
            iShips[3] = 2 + rand(1);
        }

        sCapId += "Hunter0";
        sGroup = "Sea_" + sCapId + "1";
        Group_DeleteGroup(sGroup);
        Group_FindOrCreateGroup(sGroup);

        for (i = 1; i <= 4; i++)
        {
            if(iShips[i-1] == 0) break;
            sld = GetCharacter(NPC_GenerateCharacter(sCapId + i, "off_hol_2", "man", "man", 5, iNation, 20, true, "hunter"));
            if(i == 1 || i == 3) sld.GenShip.Spec = SHIP_SPEC_RAIDER;
            else sld.GenShip.Spec = SHIP_SPEC_WAR;
            sld.GenShip.Class = iShips[i-1];
            SetShipHunter(sld);
            sld.WatchFort = true; //видеть форты
            SetFantomParamHunter(sld); //крутые парни
            SetCaptanModelByEncType(sld, "war");
            sld.AlwaysEnemy = true;
            sld.DontRansackCaptain = true;
            sld.mapEnc.type = "war";
            sld.mapEnc.Name = XI_ConvertString("BountyHunters");
            sld.mapEnc.worldMapShip = sMapShip;
            sld.hunter = "hunter";
            Group_AddCharacter(sGroup, sCapId + i);
            if (i == 1 || GetCharacterShipClass(sld) < 3) SetRandGeraldSail(sld, sti(sld.Nation));
        }

        Group_SetGroupCommander(sGroup, sCapId + "1");
        Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
        Group_LockTask(sGroup);

        // Механика мощи
        if(wdmCompareEncPower(iNation)) Map_CreateTrader("", "", sCapId + "1", 8);
        else Map_CreateWarrior("", sCapId + "1", 8);
    }
}

void SetShipHunter(ref Hunter)
{
    int ShipsHunter, hcrew, iTemp;

    if(!CheckAttribute(Hunter, "GenShip"))
    {
        ReGen:
        iTemp = sti(PChar.rank);
        if (iTemp >= 25)      ShipsHunter = GetRandomShipType(FLAG_SHIP_CLASS_3 + FLAG_SHIP_CLASS_2, FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
        else if (iTemp >= 20) ShipsHunter = GetRandomShipType(FLAG_SHIP_CLASS_3, FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
        else if (iTemp >= 12) ShipsHunter = GetRandomShipType(FLAG_SHIP_CLASS_4 + FLAG_SHIP_CLASS_3, FLAG_SHIP_TYPE_RAIDER + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY);
        else if (iTemp >= 8)  ShipsHunter = GetRandomShipType(FLAG_SHIP_CLASS_4, FLAG_SHIP_TYPE_RAIDER + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY);
        else if (iTemp >= 5)  ShipsHunter = GetRandomShipType(FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_RAIDER + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY);
        else                  ShipsHunter = GetRandomShipType(FLAG_SHIP_CLASS_6 + FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_RAIDER, FLAG_SHIP_NATION_ANY);
    }
    else
    {
        iTemp = sti(Hunter.GenShip.Class);
        ShipsHunter = WME_GetShipTypeExt(iTemp, iTemp, "War", Hunter.GenShip.Spec, sti(Hunter.nation), false);
        if(ShipsHunter == INVALID_SHIP_TYPE) goto ReGen;
    }

    SetRandomNameToCharacter(Hunter);
    SetRandomNameToShip(Hunter);
    Hunter.Ship.Type = GenerateShipExt(ShipsHunter, 1, Hunter);
    SetBaseShipData(Hunter);
    hcrew = GetMaxCrewQuantity(Hunter);
    SetCrewQuantity(Hunter, hcrew);
    SetCrewQuantityFull(Hunter); // to_do

    DeleteAttribute(Hunter,"ship.sails");
    DeleteAttribute(Hunter,"ship.masts");
    DeleteAttribute(Hunter,"ship.blots");
	DeleteAttribute(Hunter,"ship.hulls");

    if (Hunter.nation == PIRATE)
    {
        Fantom_SetCannons(Hunter, "pirate");
        Fantom_SetBalls(Hunter, "pirate");
		Fantom_SetUpgrade(Hunter, "pirate");
    }
    else
    {
        Fantom_SetCannons(Hunter, "war");
        Fantom_SetBalls(Hunter, "war");
		Fantom_SetUpgrade(Hunter, "war");
    }
}

// ОЗГИ на суше (порт и бухта)
void LandHunterReactionResult(ref loc)  // отработает после входа в локацию, но после квест_реакшна на вход
{
	int    j, i, k;
	string typeHunter, sTemp, sCapId;
	ref    sld;
	bool   ok;
	
	//if (actLoadFlag) return; // идёт лоад
	if (LAi_IsCapturedLocation) return;
	if (chrDisableReloadToLocation) return; // идёт некий другой квест с запретом выхода
	if (loc.type != "seashore" && loc.type != "port") return;   
	if (CheckAttribute(Pchar, "GenQuest.Hunter2Pause")) 
	{
		DeleteAttribute(Pchar, "GenQuest.Hunter2Pause");
		return; 
	}
	if (CheckAttribute(Pchar, "GenQuest.HunterLongPause")) return; // Addon 2016-1 Jason пиратская линейка
	if (LAi_grp_alarmactive == true)  return;  // уже ГГ кто-то бьет
	
	//if (GetQuestPastDayParam("Land_HunterTimerHasBeen") == 0) return; // сегодня уже были
	for (j=0; j< MAX_NATIONS; j++)
    {
        if (j == PIRATE) continue;
        // открыть, если не нужны мирные охотники if(NationsRelations2MainCharacter[j] != RELATION_ENEMY) continue;

        typeHunter = NationShortName(j);
        if (GetQuestPastDayParam("Land_HunterTimer" + typeHunter) > (7 + rand(7)))
        {
			SaveCurrentQuestDateParam("Land_HunterTimer" + typeHunter); // запомним, даже если нет озгов, выход их ФОР отложит озгов до след раза у др нации
			if (ChangeCharacterNationReputation(pchar, j, 0) <= -10)// Минус это НЗГ
	        {
	            Log_QuestInfo("LandHunterReactionResult " + typeHunter);
				sCapId = typeHunter + "LandHunter0";
	            sTemp = "LAND_HUNTER"; 
				ok = true;
				arrayNPCModelHow = 0;
	            for (i = 1; i <= 8; i++)
	            {
	                sld = GetCharacter(NPC_GenerateCharacter(sCapId + i, "off_hol_2", "man", "man", 5, j, 0, true, "hunter"));
	                SetFantomParamHunter(sld); //крутые парни
	                sld.name 		= XI_ConvertString("BountyHunter");
	                sld.lastname 	= "";
	                sld.Dialog.CurrentNode = "First time";
	                sld.dialog.filename = "Hunter_dialog.c";
	                sld.greeting = "hunter";
	                sld.location = "none"; // вот где порылась собака!!!!!!!!!!!
	
	                SetModelPirate(sld);
	                k = 0;
					while (!CheckNPCModelUniq(sld) && k < 10)
					{
					    k++;
         				SetModelPirate(sld);
					}
					arrayNPCModel[arrayNPCModelHow] = sld.model;
					arrayNPCModelHow++;
	                LAi_SetActorTypeNoGroup(sld);
	                LAi_SetCheckMinHP(sld, (LAi_GetCharacterHP(sld) - 1), false, "Battle_Hunters_Land");
	                if (PlaceCharacter(sld, "goto", "random_must_be_near") == "" && i == 1) // fix если вдруг нет в локации
	                {
	                    ok = false;
	                    break;
	                }
	                LAi_ActorFollow(sld, pchar, "", 8.0);
	                //LAi_Actor2WaitDialog(sld, pchar); // ждать диалог, но бежать
	                LAi_group_MoveCharacter(sld, sTemp);
	                if (abs(ChangeCharacterNationReputation(pchar, j, 0)) < (i * 9)) break; // число от НЗГ
	            }
	            
				LAi_group_SetRelation(sTemp, LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
				LAi_group_SetRelation(sTemp, LAI_GROUP_PLAYER_OWN, LAI_GROUP_NEITRAL);
				
				LAi_group_ClearAllTargets();
				LAi_SetFightModeForOfficers(false); 
				if (ok)
	            {
	                pchar.HunterCost = abs(ChangeCharacterNationReputation(pchar, j, 0));
	                PChar.HunterCost = makeint(PChar.HunterCost)*2000 + rand(5000); //сразу генерим
	                PChar.HunterCost.TempHunterType = typeHunter;
	                PChar.HunterCost.Qty = i;
	                //LAi_SetActorType(Pchar);
	                sld = characterFromID(sCapId + "1");
	                LAi_type_actor_Reset(sld);
	                LAi_ActorDialog(sld, pchar, "", 4.0, 0);
					//SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
		    		//LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 4.1);
		    		chrDisableReloadToLocation = true;
		    		DoQuestCheckDelay("OpenTheDoors", 5.0);
	            }
	            // запомним и сегодня больше не парим ГГ
	            //SaveCurrentQuestDateParam("Land_HunterTimerHasBeen");
	            break;
	        }
        }
    }
}

// Captain Beltrop, 12.09.21, удаление морских ОЗГов
void SeaHunter_Delete()
{
	for (int j=0; j < MAX_NATIONS; j++)
	{
		if (j == PIRATE) continue;
		string typeHunter = NationShortName(j);
		string sCapId = typeHunter + "Hunter01";
		Map_ReleaseQuestEncounter(sCapId);
	}
}

void FireBrigade_eng(string qName) {FireBrigadeCheck(ENGLAND);}
void FireBrigade_fra(string qName) {FireBrigadeCheck(FRANCE);}
void FireBrigade_spa(string qName) {FireBrigadeCheck(SPAIN);}
void FireBrigade_hol(string qName) {FireBrigadeCheck(HOLLAND);}

void FireBrigadeCheck(int iNation)
{
	int    i, iTemp, num;
	string sGroup, sCapId, sTemp;
    string sNation = NationShortName(iNation);
	ref    sld;
    bool   bSkip = false;

    UpdatePlayerSquadronPower();

    iTemp = wdmGetNationThreat(iNation);
    if(iNation == ENGLAND && iTemp < 3) bSkip = true;
    else if(iNation == FRANCE  && iTemp < 4) bSkip = true;
    else if(iNation == SPAIN   && iTemp < 5) bSkip = true;
    else if(iNation == HOLLAND && iTemp < 3) bSkip = true;
    if(CharacterIsAlive(sNation + "Brigadier01")) bSkip = true;

    if(!bSkip)
    {
        bSkip = wdmCompareEncPower(iNation);
        string sMapShip = Nations[iNation].worldMapShip + "_manowar"; // to_do

        sCapId = sNation + "Brigadier0";
        sGroup = "Sea_" + sCapId + "1";
        Group_DeleteGroup(sGroup);
        Group_FindOrCreateGroup(sGroup);

        int iShips[6];
        iShips[0] = 0;
        iShips[1] = 0;
        iShips[2] = 0;
        iShips[3] = 0;
        iShips[4] = 0;
        iShips[5] = 0;

        if(iNation == ENGLAND) {
            iShips[0] = SHIP_HIMERA;
            iShips[1] = 4;
            iShips[2] = 4;
            iShips[3] = 3;
        }
        else if(iNation == FRANCE) {
            iShips[0] = SHIP_CORVETTE_QUEST;
            iShips[1] = 3;
            iShips[2] = 3;
            iShips[3] = 2;
        }
        else if(iNation == SPAIN) {
            iShips[0] = SHIP_ELCASADOR;
            iShips[1] = 3;
            iShips[2] = 3;
            iShips[3] = 2;
            iShips[4] = 2;
            iShips[5] = 3;
        }
        else if(iNation == HOLLAND) {
            iShips[0] = SHIP_MAYFANG;
            iShips[1] = 5;
            iShips[2] = 3;
            iShips[3] = 4;
            iShips[4] = 4;
        }

        int iDays;
        if(bSkip) iDays = 8;
        else iDays = 29;

        for (i = 1; i <= 6; i++)
        {
            if(iShips[i - 1] == 0) break;
            sld = GetCharacter(NPC_GenerateCharacter(sCapId + i, "off_hol_2", "man", "man", 5, iNation, iDays, true, "hunter"));
            if(i == 1)
            {
                //"quest"?
                if(iNation == ENGLAND) {
                    sld.name = StringFromKey("GoldenGirl_8");
                    sld.lastname = StringFromKey("GoldenGirl_9");
                    sld.model = "Baronet_1";
                    sld.Ship.Type = GenerateShipExt(SHIP_HIMERA, true, sld);
                    sld.Ship.Name = StringFromKey("QuestsUtilite_277");
                    sld.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS20;
                }
                else if(iNation == FRANCE) {
                    sld.model = "off_fra_2";
                    //sld.greeting = "";
                    sld.Ship.Type = GenerateShipExt(SHIP_CORVETTE_QUEST, true, sld);
                    sld.Ship.Name = StringFromKey("SharlieFinal_7");
                    sld.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS32;
                }
                else if(iNation == SPAIN) {
                    if(SandBoxMode)
                    {
                        sld.name = StringFromKey("QuestsUtilite_56");
                        sld.lastname = StringFromKey("QuestsUtilite_57");
                        sld.model = "Alonso";
                        sld.greeting = "Alonso";
                    }
                    else sld.model = "SpaOfficer2";
                    sld.Ship.Type = GenerateShipExt(SHIP_ELCASADOR, true, sld);
                    sld.Ship.Name = StringFromKey("Roger_72");
                    sld.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS32;
                }
                else if(iNation == HOLLAND) {
                    sld.name = StringFromKey("QuestsUtilite_42");
                    sld.lastname = StringFromKey("QuestsUtilite_43");
                    sld.model = "Longway";
                    sld.model.animation = "Longway";
                    sld.greeting = "Longway";
                    sld.Ship.Type = GenerateShipExt(SHIP_MAYFANG, true, sld);
                    sld.Ship.Name = StringFromKey("HollandGambit_12");
                    sld.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS16;
                }
                sld.Brigadier = "";
                sld.QuestHandler = "FireBrigadeInterruption";
                sld.DontClearDead      = true;
                sld.SaveItemsForDead = true;
                FaceMaker(sld);
                CirassMaker(sld);
                SetBaseShipData(sld);
                DeleteAttribute(sld,"ship.sails");
                DeleteAttribute(sld,"ship.masts");
                DeleteAttribute(sld,"ship.blots");
                DeleteAttribute(sld,"ship.hulls");
                Fantom_SetBalls(sld, "war");
                SetCrewQuantityFull(sld);
                AddCrewMorale(sld, 100);
                ChangeCrewExp(sld, "Sailors", 100);
                ChangeCrewExp(sld, "Cannoners", 100);
                ChangeCrewExp(sld, "Soldiers", 100);
            }
            else
            {
                if(iNation == ENGLAND) {
                    if(i < 3) sld.GenShip.Spec = SHIP_SPEC_RAIDER;
                    else sld.GenShip.Spec = SHIP_SPEC_WAR;
                }
                else if(iNation == FRANCE) {
                    if(i == 2) sld.GenShip.Spec = SHIP_SPEC_RAIDER;
                    else sld.GenShip.Spec = SHIP_SPEC_WAR;
                }
                else if(iNation == SPAIN) {
                    if(i < 5) sld.GenShip.Spec = SHIP_SPEC_RAIDER;
                    else sld.GenShip.Spec = SHIP_SPEC_WAR;
                }
                else if(iNation == HOLLAND) {
                    if(i == 2) sld.GenShip.Spec = SHIP_SPEC_RAIDER;
                    else if(i == 3) sld.GenShip.Spec = SHIP_SPEC_WAR;
                    else sld.GenShip.Spec = SHIP_SPEC_UNIVERSAL;
                }
                sld.GenShip.Class = iShips[i-1];
                SetShipHunter(sld);
                SetCaptanModelByEncType(sld, "war");
            }
            SetFantomParamHunter(sld);
            if(i == 1) SetBrigadierLoot(sld, iNation);
            sld.WatchFort = true;
            sld.AlwaysEnemy = true;
            sld.DontRansackCaptain = true;
            sld.AlwaysSandbankManeuver = true;
            sld.mapEnc.type = "war";
            sld.mapEnc.Name = XI_ConvertString("Punitive expedition");
            sld.mapEnc.worldMapShip = sMapShip;
            sld.hunter = "hunter";
            Group_AddCharacter(sGroup, sCapId + i);
            if(i != 1 && rand(1)) SetRandGeraldSail(sld, iNation);
        }

        Group_SetGroupCommander(sGroup, sCapId + "1");
        Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
        Group_LockTask(sGroup);

        // Механика мощи
        if(bSkip) Map_CreateTrader("", "", sCapId + "1", 7);
        else Map_CreateWarrior("", sCapId + "1", 28);
    }

    SetFunctionTimerCondition("FireBrigade_" + sNation, 0, 0, 5 + rand(4), true);
}

void FireBrigadeRefresh(ref rChar, int iNation, int Delay)
{
    if(CheckAttribute(&TEV, "FreezeRefresh" + iNation))
    {
        DeleteAttribute(&TEV, "FreezeRefresh" + iNation);
        return;
    }
    rChar.lifeday = 0;
    SetFunctionTimerCondition("FireBrigade_" + NationShortName(iNation), 0, 0, Delay, true);
}

void FireBrigadeInterruption(ref rCaptain)
{
    int iNation = sti(rCaptain.nation);
    string sTemp;
    string sNation = NationShortName(iNation);

    // Убежать
    sTemp = "FireBrigadeEscape" + sNation;
    PChar.quest.(sTemp).win_condition.l1 = "ExitFromSea";
	PChar.quest.(sTemp).function = "FireBrigadeEscape";
    PChar.quest.(sTemp).Nation = iNation;
    // Потопить
    sTemp = "FireBrigadeSink" + sNation;
    PChar.quest.(sTemp).win_condition.l1 = "Character_sink";
	PChar.quest.(sTemp).win_condition.l1.character = rCaptain.id;
	PChar.quest.(sTemp).function = "FireBrigadeSink";
    PChar.quest.(sTemp).Nation = iNation;
    // Захватить
    sTemp = "FireBrigadeCapture" + sNation;
    PChar.quest.(sTemp).win_condition.l1 = "Character_Capture";
	PChar.quest.(sTemp).win_condition.l1.character = rCaptain.id;
	PChar.quest.(sTemp).function = "FireBrigadeCapture";
    PChar.quest.(sTemp).Nation = iNation;
}

void FireBrigadeEscape(string qName)
{
    int iNation = sti(PChar.quest.(qName).Nation);
    string sTemp;
    string sNation = NationShortName(iNation);

    sTemp = "FireBrigadeCapture" + sNation;
    PChar.quest.(sTemp).over = "yes";
    sTemp = "FireBrigadeSink" + sNation;
    PChar.quest.(sTemp).over = "yes";
    sTemp = "FreezeRefresh" + iNation;
    TEV.(sTemp) = ""; // Блокнуть рефреш от удаления энкаунтера
    sTemp = sNation + "Brigadier01";
    Map_ReleaseQuestEncounter(sTemp);
    iNation = GetCharacterIndex(sTemp);
    if(iNation != -1) characters[iNation].lifeday = 0;
    sTemp = "Sea_" + sTemp;
	Group_DeleteGroup(sTemp);
    SetFunctionTimerCondition("FireBrigade_" + sNation, 0, 0, 5 + rand(4), true);
}

void FireBrigadeSink(string qName)
{
    int iNation = sti(PChar.quest.(qName).Nation);
    string sTemp;
    string sNation = NationShortName(iNation);

    sTemp = "FireBrigadeCapture" + sNation;
    PChar.quest.(sTemp).over = "yes";
    sTemp = "FireBrigadeEscape" + sNation;
    PChar.quest.(sTemp).over = "yes";
    sTemp = "FreezeRefresh" + iNation;
    TEV.(sTemp) = "";
    //sTemp = sNation + "Brigadier01";
    //Map_ReleaseQuestEncounter(sTemp);
    sTemp = "FireBrigade_" + sNation;
    PChar.quest.(sTemp).over = "yes"; // Ваша песенка спета, сэр
	CheckFireBrigadeAchievements(iNation, "Sink");
}

void FireBrigadeCapture(string qName)
{
    int iNation = sti(PChar.quest.(qName).Nation);
    string sTemp;
    string sNation = NationShortName(iNation);

    sTemp = "FireBrigadeSink" + sNation;
    PChar.quest.(sTemp).over = "yes";
    sTemp = "FireBrigadeEscape" + sNation;
    PChar.quest.(sTemp).over = "yes";
    sTemp = "FreezeRefresh" + iNation;
    TEV.(sTemp) = "";
    //sTemp = sNation + "Brigadier01";
    //Map_ReleaseQuestEncounter(sTemp);
    sTemp = "FireBrigade_" + sNation;
    PChar.quest.(sTemp).over = "yes";
	CheckFireBrigadeAchievements(iNation, "Capture");
}

void SetBrigadierLoot(ref sld, int iNation)
{
    string sTemp;
    if(iNation == ENGLAND) {
        // Бландербуз
        sTemp = GetCharacterEquipByGroup(sld, GUN_ITEM_TYPE);
        if(sTemp != "")
        {
            RemoveCharacterEquip(sld, GUN_ITEM_TYPE);
            TakeNItems(sld, sTemp, -1);
            // to_do: убрать порох и пули
        }
        GiveItem2Character(sld, "pistol8");
        EquipCharacterbyItem(sld, "pistol8");
        LAi_SetCharacterBulletType(sld, "harpoon");
        LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "harpoon");
        AddItems(sld, "gunpowder", 30 + rand(20));
    }
    else if(iNation == FRANCE) {
        // Мальтийский меч
        sTemp = sld.equip.blade;
        RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
        TakeNItems(sld, sTemp, -1);
        sTemp = GetGeneratedItem("blade_36");
        GiveItem2Character(sld, sTemp);
        EquipCharacterbyItem(sld, sTemp);
    }
    else if(iNation == SPAIN) {
        sTemp = GetCharacterEquipByGroup(sld, CIRASS_ITEM_TYPE);
        if(sTemp != "")
        {
            RemoveCharacterEquip(sld, CIRASS_ITEM_TYPE);
            TakeNItems(sld, sTemp, -1);
        }
        GiveItem2Character(sld, "cirass4");
        EquipCharacterbyItem(sld, "cirass4");
    }
    else if(iNation == HOLLAND) {
        // Цзянь
        sTemp = sld.equip.blade;
        RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
        TakeNItems(sld, sTemp, -1);
        sTemp = GetGeneratedItem("blade_41");
        GiveItem2Character(sld, sTemp);
        EquipCharacterbyItem(sld, sTemp);
    }
}
