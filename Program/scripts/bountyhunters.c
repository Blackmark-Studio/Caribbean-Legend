// BOAL 27/06/06 переделка под нужны ВМЛ, все стерли и написали заново.
void SeaHunterCheck()
{
	int    i, j, iTemp;
	string sGroup, sCapId;
	ref    sld;

	SetTimerCondition("SeaHunterCheck", 0, 0, 6 + rand(20), true);
	if (CheckAttribute(PChar, "GenQuest.SeaHunter2Pause")) return; // Captain Beltrop, 12.09.21, морские ОЗГи
    UpdatePlayerSquadronPower();

    for (j = 0; j < MAX_NATIONS; j++)
    {
        if (j == PIRATE) continue;
        // открыть, если не нужны мирные охотники if(NationsRelations2MainCharacter[j] != RELATION_ENEMY) continue;

        iTemp = wdmGetNationThreat(j);
        if (iTemp != 0)
        {
            string sMapShip = Nations[j].worldMapShip + "_";
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

            sCapId = NationShortName(j) + "Hunter0";
            sGroup = "Sea_" + sCapId + "1";
			Group_DeleteGroup(sGroup);
			Group_FindOrCreateGroup(sGroup);

            for (i = 1; i <= 4; i++)
            {
                if(iShips[i-1] == 0) continue;
                sld = GetCharacter(NPC_GenerateCharacter(sCapId + i, "off_hol_2", "man", "man", 5, j, 20, true, "hunter"));
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
                if (i == 1 || GetCharacterShipClass(sld) == 1) SetRandGeraldSail(sld, sti(sld.Nation));
            }

            Group_SetGroupCommander(sGroup, sCapId+ "1");

            // Механика мощи
            if(wdmCompareEncPower(j))
            {
                Map_CreateTrader("", "", sCapId + "1", 8);
            }
            else 
            {
                Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
                Group_LockTask(sGroup);
                Map_CreateWarrior("", sCapId + "1", 8);
            }
        }
    }
}

void SetShipHunter(ref Hunter)
{
    int ShipsHunter, hcrew, iTemp;

    if(!CheckAttribute(Hunter, "GenShip"))
    {
        ReGen:
        iTemp = sti(PChar.rank);
        if (iTemp >= 20)                    ShipsHunter = SHIP_GALEON_H     + rand(2);
        else if (iTemp >= 12 && iTemp < 20) ShipsHunter = SHIP_GALEON_L     + rand(3);
        else if (iTemp >= 8  && iTemp < 12) ShipsHunter = SHIP_BRIGANTINE   + rand(2);
        else if (iTemp >= 5  && iTemp < 8)  ShipsHunter = SHIP_SCHOONER_W;
        else                                ShipsHunter = SHIP_CAREERLUGGER + rand(2);
    }
    else
    {
        iTemp = sti(Hunter.GenShip.Class);
        ShipsHunter = WME_GetShipTypeExt(iTemp, iTemp, "War", Hunter.GenShip.Spec, -1);
        if(ShipsHunter == INVALID_SHIP_TYPE)
        {
            Log_TestInfo("WARNING! CANT FIND SHIP IN WME_GetShipTypeExt!");
            goto ReGen;
        }
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
