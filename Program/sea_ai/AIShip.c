object	Sail, Rope, Flag, Vant, VantL, VantZ;

#define MIN_ENEMY_DISTANCE_TO_DISABLE_MAP_ENTER				1000.0
#define MIN_ENEMY_DISTANCE_TO_DISABLE_MAP_ENTER_FORT		1400.0
#define MIN_ENEMY_DISTANCE_TO_DISABLE_ENTER_2_LOCATION		1150.0

bool	bAbordageShipCanBe = false;
int		iAbordageShipEnemyCharacter;

//bool	bNoDamage2Us = false;
bool	bCanEnterToLand = false;
aref	arIslandReload;
string	sIslandLocator;
string	sIslandID;
string	sSeaSoundPostfix;
int		iShipPriorityExecute = 2;
int		iShipPriorityRealize = 31;
bool	bUpdatePosMode = false;
int		iVicSoundTime = 0;
string	sSeaStartMusicName;
bool	isEnemyAround = false;

int		iNumShips = 0;
int		Ships[MAX_SHIPS_ON_SEA];

#define SHIP_DETONATE_SMALL		"ShipDetonateSmall"

#define TURN_RATE_MAGIC_NUMBER  244.444

#event_handler("Ship_StartLoad", "Ship_StartLoad");
#event_handler("Ship_EndLoad", "Ship_EndLoad");

void CreateRiggingEnvironment()
{
	CreateEntity(&Sail, "Sail");
	LayerAddObject(sCurrentSeaExecute, &Sail, iShipPriorityExecute + 1);
	LayerAddObject(sCurrentSeaRealize, &Sail, iShipPriorityRealize + 1);
	LayerAddObject(SAILS_TRACE, &Sail, 10);
	LayerAddObject(SEA_REFLECTION2, &Sail, 3);
	Sail.MinSpeed = 0.05;

	CreateEntity(&Rope, "Rope");
	LayerAddObject(sCurrentSeaExecute, &Rope, iShipPriorityExecute + 2);
	LayerAddObject(sCurrentSeaRealize, &Rope, iShipPriorityRealize + 2);
	
	CreateEntity(&Flag, "Flag");
	LayerAddObject(sCurrentSeaExecute, &Flag, iShipPriorityExecute + 3);
	LayerAddObject(sCurrentSeaRealize, &Flag, iShipPriorityRealize + 3);
	LayerAddObject(SEA_REFLECTION2, &Flag, 3);
	
	CreateEntity(&Vant, "Vant");
	LayerAddObject(sCurrentSeaExecute, &Vant, iShipPriorityExecute + 4);
	LayerAddObject(sCurrentSeaRealize, &Vant, iShipPriorityRealize + 4);
	
	CreateEntity(&VantL, "VantL");
	LayerAddObject(sCurrentSeaExecute, &VantL, iShipPriorityExecute + 4);
	LayerAddObject(sCurrentSeaRealize, &VantL, iShipPriorityRealize + 4);
	
	CreateEntity(&VantZ, "VantZ");
	LayerAddObject(sCurrentSeaExecute, &VantZ, iShipPriorityExecute + 4);
	LayerAddObject(sCurrentSeaRealize, &VantZ, iShipPriorityRealize + 4);
	
	iNumShips = 0;
}

void DeleteRiggingEnvironment()
{
	DeleteClass(&Sail);
	DeleteClass(&Rope);
	DeleteClass(&Flag);
	DeleteClass(&Vant);
	DeleteClass(&VantL);
	DeleteClass(&VantZ);
}

void DeleteShipEnvironment()
{
	DeleteRiggingEnvironment();

	DelEventHandler(SHIP_CHANGE_CHARGE, "Ship_ChangeChargeEvent");  // нигде не используется???
	DelEventHandler(SHIP_DROP_GOOD, "DropGoodsToSea");
	DelEventHandler(SHIP_HULL_HIT, "Ship_HullHitEvent");
	DelEventHandler(SHIP_CHECK_RELOAD_ENABLE, "Ship_CheckMainCharacter");
	DelEventHandler(SHIP_DETONATE_SMALL, "Ship_DetonateSmall");
	DelEventHandler(SHIP_BRANDER_DETONATE, "Ship_BranderDetonate");
	DelEventHandler(SHIP_FIRE_DAMAGE, "Ship_FireDamage");
	DelEventHandler(SHIP_TO_STRAND_NEXT, "Ship_OnStrandNext");
	DelEventHandler(SHIP_BORT_RELOADED, "Ship_OnBortReloaded");
	DelEventHandler(SHIP_ACTIVATE_FIRE_PLACE, "Ship_ActivateFirePlace");
	DelEventHandler(SHIP_UPDATE_PARAMETERS, "Ship_UpdateParameters");
	DelEventHandler(SHIP_CHECK_SITUATION, "Ship_CheckSituation");
	DelEventHandler(WHR_LIGHTNING, "Ship_Lightning");
	DelEventHandler("eSwitchPerks", "Ship_UpdatePerks");
	DelEventHandler("TornadoDamage", "Ship_TornadoDamage");
	DelEventHandler(SHIP_GET_RUNAWAY_POINT, "Ship_GetRunAwayPoint");
    DelEventHandler("event_WindChange", "Ship_WindAnalyse");
	DelEventHandler("frame", "Ship_VicSoundTime");
	DelEventHandler("Ship_SailsMoveSound", "Ship_SailsMoveSound");
	DelEventHandler("Ship_BortReloadEvent", "Ship_BortReloadEvent");
	DelEventHandler("event_sail_dot", "Ship_SailDot");
	DelEventHandler(SHIP_SET_BLOT, "Ship_SetBlot");
	DelEventHandler(SHIP_FAKE_FIRE, "Ship_EventFakeFire");

    // Sounds
    DelEventHandler("NextHour", "ShipBells");

	for (int i=0; i<iNumShips; i++) 
	{ 
		// delete particles from ship/etc
		SendMessage(&Characters[Ships[i]], "l", MSG_SHIP_SAFE_DELETE); 

		// delete sounds from ship
		if (CheckAttribute(&Characters[Ships[i]], "Ship.Sounds.WaterID")) 	ReleaseSound(sti(Characters[Ships[i]].Ship.Sounds.WaterID));
		if (CheckAttribute(&Characters[Ships[i]], "Ship.Sounds.SailsID"))   ReleaseSound(sti(Characters[Ships[i]].Ship.Sounds.SailsID));
		if (CheckAttribute(&Characters[Ships[i]], "Ship.Sounds.TurnID"))    ReleaseSound(sti(Characters[Ships[i]].Ship.Sounds.TurnID));
	}

	// scan characters for delete snd id's
	DeleteEntitiesByType("ship");
}

void ClearAllFire() // boal new
{
    for (int i=0; i<iNumShips; i++)
	{
		// delete particles from ship/etc
		if (Ships[i] != -1) SendMessage(&Characters[Ships[i]], "l", MSG_SHIP_SAFE_DELETE);
	}
}
// boal new сбросить всем в море проверку смотрения на флаг.
void Sea_ClearCheckFlag() 
{
    if (bSeaActive)
    {
		int i;
		
		for (i=0; i<iNumShips; i++)
		{
			if(sti(Ships[i]) >= 0 && sti(Ships[i]) < MAX_CHARACTERS) {
			if (!CheckAttribute(&Characters[Ships[i]], "DontCheckFlag"))
			{
			    DeleteAttribute(&Characters[Ships[i]], "CheckFlagYet"); // флаг распознования врага
			    DeleteAttribute(&Characters[Ships[i]], "CheckFlagDate");
			}
			}
		}
		// фортам трем
		for (i=0; i<MAX_COLONIES; i++)
		{
			if (CheckAttribute(&colonies[i], "commanderIdx"))
			{
				if (!CheckAttribute(&Characters[sti(colonies[i].commanderIdx)], "DontCheckFlag"))
				{
					DeleteAttribute(&Characters[sti(colonies[i].commanderIdx)], "CheckFlagYet"); // флаг распознования врага
				    DeleteAttribute(&Characters[sti(colonies[i].commanderIdx)], "CheckFlagDate");
			    }
			}
		}
	}
}

void CreateShipEnvironment()
{
	isEnemyAround = false;
	bUpdatePosMode = false;
	iVicSoundTime = 0;

	bAbordageFortCanBe = false;
	bAbordageShipCanBe = false;
	bCanEnterToLand = false;
	sIslandLocator = "";
	sIslandID = "";
	
	for (int i = 0; i < MAX_SHIPS_ON_SEA; i++) Ships[i] = -1;

	aref arCurWeather = GetCurrentWeather();
	sSeaSoundPostfix = arCurWeather.Sounds.Sea.Postfix; // TO_DO: в погоде обновлять

	CreateRiggingEnvironment();

	SetEventHandler(SEA_GET_LAYERS, "SeaAI_GetLayers", 0);

	SetEventHandler(SHIP_NOT_ENOUGH_BALLS, "Ship_NotEnoughBalls", 0);
	SetEventHandler(SHIP_GET_CURRENT_BALLS_NUM, "Ship_GetCurrentBallsNum", 0);
	SetEventHandler(SHIP_SHIP2ISLAND_COLLISION, "Ship_Ship2IslandCollision", 0);
	SetEventHandler(SHIP_SHIP2SHIP_COLLISION, "Ship_Ship2ShipCollision", 0);
	SetEventHandler(SHIP_SAIL_DAMAGE, "Ship_SailDamage", 0);
	SetEventHandler(SHIP_FIRE_DAMAGE, "Ship_FireDamage", 0);
	SetEventHandler(SHIP_CHECK_SITUATION, "Ship_CheckSituation", 0);
	SetEventHandler(SHIP_TO_STRAND, "Ship_OnStrand", 0);
	SetEventHandler(SHIP_TO_STRAND_NEXT, "Ship_OnStrandNext", 0);
	SetEventHandler(SHIP_DEAD, "Ship_OnDead", 0);
	SetEventHandler(SHIP_UPDATE_PARAMETERS, "Ship_UpdateParameters", 0);
	SetEventHandler(SHIP_DROP_GOOD, "DropGoodsToSea", 0);
	SetEventHandler(SHIP_CREATE, "Ship_OnCreate", 0);
	SetEventHandler(SHIP_BORT_RELOADED, "Ship_OnBortReloaded", 0);
	SetEventHandler(SHIP_CHANGE_CHARGE, "Ship_ChangeChargeEvent", 0);
	SetEventHandler(SHIP_HULL_HIT, "Ship_HullHitEvent", 0);
	SetEventHandler(SHIP_CHECK_RELOAD_ENABLE, "Ship_CheckMainCharacter", 0);
	SetEventHandler(SHIP_FIRE_ACTION, "Ship_FireAction", 0);
	SetEventHandler(SHIP_GET_BORT_FIRE_DELTA, "Ship_GetBortFireDelta", 0);
	SetEventHandler(SHIP_DETONATE_SMALL, "Ship_DetonateSmall", 0);
	SetEventHandler(SHIP_ACTIVATE_FIRE_PLACE, "Ship_ActivateFirePlace", 0);
	SetEventHandler(WHR_LIGHTNING, "Ship_Lightning", 0);
	SetEventHandler(SHIP_CREATELOADSHIP, "Ship_LoadShip", 0);
	SetEventHandler(SHIP_LOAD_SHIPACTIVATEFIREPLACE, "Ship_LoadShipActivateFirePlace", 0);
	SetEventHandler(SHIP_GET_RUNAWAY_POINT, "Ship_GetRunAwayPoint", 0);
    SetEventHandler("event_WindChange", "Ship_WindAnalyse", 0);
	SetEventHandler("TornadoDamage", "Ship_TornadoDamage", 0);

	SetEventHandler(SHIP_BRANDER_DETONATE, "Ship_BranderDetonate", 0);
	SetEventHandler(SHIP_MAST_DAMAGE, "Ship_MastDamage", 0);	
	SetEventHandler(SHIP_HULL_DAMAGE, "Ship_HullDamage", 0); // ugeen 15.11.10 - обработка событий повреждений отделяемых элементов корпуса
	SetEventHandler("eSwitchPerks", "Ship_UpdatePerks", 0);
	SetEventHandler("frame", "Ship_VicSoundTime", 0);
	SetEventHandler("Ship_SailsMoveSound", "Ship_SailsMoveSound", 0);
	SetEventHandler("Ship_BortReloadEvent", "Ship_BortReloadEvent", 0);
	SetEventHandler("event_sail_dot", "Ship_SailDot", 0);
	SetEventHandler(SHIP_SET_BLOT, "Ship_SetBlot", 0);
	SetEventHandler(SHIP_FAKE_FIRE, "Ship_EventFakeFire", 0);

    // Sounds
    if (bSeaActive)
    {
        SetEventHandler("NextHour", "ShipBells", 0);
    }
}

float Ship_GetBortFireDelta()
{
	aref aCharacter = GetEventData();
	float x = GetEventData();
	float y = GetEventData();
	float z = GetEventData();
	
	// коэффициент меткости
	float fAccuracy = stf(aCharacter.TmpSkill.Accuracy);
	float accRandMin = 0.21 - 0.16 * pow(fAccuracy, 0.35);
	float accRandMax = 3.5 - 3.45 * pow(fAccuracy, 0.75);
	float kAccuracy = (1.2 - pow(fAccuracy, 0.45)) * uniform(accRandMin, accRandMax);
	
	// коэффициент дистанции
	float fDistance = GetDistance2D(x, z, stf(aCharacter.Ship.Pos.x), stf(aCharacter.Ship.Pos.z));
	float kDistance = Bring2Range(0.0, 25.0, 0.0, 1000.0, fDistance);
	
	float fRadius = kAccuracy * kDistance;
	return fRadius;
}

string Ship_GetGroupID(ref rCharacter)
{
 	if (CheckAttribute(rCharacter, "SeaAI.Group"))// boal fix bug
    {
        return rCharacter.SeaAI.Group.Name;
    }
    else
    {
        return "";
    }
}
// boal 030804 -->
void Ship_NationAgressivePatent(ref rCharacter)
{
	if(LAi_IsDead(rCharacter))
		return;
	int HunterScore;
	
	// патент отнимаем всегда, когда палим по другу патента
    ref rMainCharacter = GetMainCharacter();

    if (isMainCharacterPatented())
    {
        if (sti(rCharacter.nation) != PIRATE && GetNationRelation(sti(Items[sti(rMainCharacter.EquipedPatentId)].Nation), sti(rCharacter.nation)) != RELATION_ENEMY)
        {
        	TakeItemFromCharacter(rMainCharacter, "patent_" + NationShortName(sti(Items[sti(rMainCharacter.EquipedPatentId)].Nation)));
			HunterScore = GetIntByCondition(HasShipTrait(rMainCharacter, "trait23"), 40, 20);
        	ChangeCharacterHunterScore(rMainCharacter, NationShortName(sti(Items[sti(rMainCharacter.EquipedPatentId)].Nation)) + "hunter", HunterScore);
        	Items[sti(rMainCharacter.EquipedPatentId)].TitulCur = 1; // текущ звание сбросим
        	Items[sti(rMainCharacter.EquipedPatentId)].TitulCurNext = 0; // счетчик звание сбросим
        	RemoveCharacterEquip(rMainCharacter, "patent");// Удаляем патент из экипировки
        	rCharacter.CheckNationBounty = true;
        }
    }
    else
    {// без патента
    	if (sti(rCharacter.nation) != PIRATE && !CheckAttribute(rCharacter, "CheckNationBounty"))   // ещё не наказывал
    	{
    		if (GetNationRelation(GetBaseHeroNation(), sti(rCharacter.nation)) != RELATION_ENEMY)
    		{
				HunterScore = GetIntByCondition(HasShipTrait(rMainCharacter, "trait23"), 1 + rand(2), 1);
				rCharacter.CheckNationBounty = true;
				// ChangeCharacterHunterScore(rMainCharacter, NationShortName(sti(rCharacter.nation)) + "hunter", HunterScore);
			}
    	}
    }
}

void Ship_NationAgressive(ref rMainGroupCharacter, ref rCharacter)// ком группы и в кого попали
{    
	if(LAi_IsDead(rCharacter))
		return;
	// используется на суше при атаке города
    ref rMainCharacter = GetMainCharacter();
    
    if (CheckAttribute(rCharacter, "Coastal_Captain")) return;  // есть флаг есть, то нет ругани, это таможенник и квестовый

	//--> eddy. квест мэра на пирата
	if (rCharacter.id == "MQPirate" && sti(rCharacter.nation) != PIRATE)
	{
		rCharacter.nation = PIRATE;
		Ship_FlagRefresh(characterFromId("MQPirate")); //флаг на лету
      	Pchar.quest.DestroyPirate_PirateIsOut.win_condition.l1 = "ExitFromSea";
		Pchar.quest.DestroyPirate_PirateIsOut.win_condition = "DestroyPirate_PirateIsOut";
	}
	//<-- eddy. квест мэра на пирата
	else
	{
		if (CheckAttribute(rCharacter, "ShipEnemyDisable") || CheckAttribute(rCharacter, "AlwaysFriend"))  return; // флаг не обижаться на выстрелы
	    if( sti(rMainCharacter.nation) == sti(rCharacter.nation) && sti(rMainCharacter.nation) != PIRATE)
	    {
            SetCharacterRelationBoth(sti(rCharacter.index), GetMainCharacterIndex(), RELATION_ENEMY);
            rMainCharacter.nation = PIRATE;
			DoQuestCheckDelay(NationShortName(PIRATE) + "_flag_rise", 0.1); // применение нац отношений флага
	        ChangeCharacterComplexReputation(rMainCharacter,"nobility", -10);
			ChangeCharacterComplexReputation(rMainCharacter,"authority", -2);
			ChangeCharacterComplexReputation(rMainCharacter,"fame", 0.5);
	    }
			// ещё не враждебный, нарушаем лицензию и ухудшаем отношения
			if (GetRelation(sti(rCharacter.index), nMainCharacterIndex) != RELATION_ENEMY)
			{
				LICENSE_CheckViolationAgainstGroup_Sea(rMainGroupCharacter);
				if (sti(rMainGroupCharacter.nation) != PIRATE) ChangeCharacterHunterScore(rMainCharacter, NationShortName(sti(rMainGroupCharacter.nation)) + "hunter", GetIntByCondition(HasShipTrait(rMainCharacter, "trait23"), 5, 3));
			}
	    Ship_NationAgressivePatent(rCharacter); // патент отнимаем всегда, когда палим по другу патента
	    SetNationRelation2MainCharacter(sti(rMainGroupCharacter.nation), RELATION_ENEMY);
	    SetCharacterRelationBoth(sti(rMainGroupCharacter.index), GetMainCharacterIndex(), RELATION_ENEMY);
    }
}
// boal 030804 <--
void Ship_FireAction()
{
	aref rCharacter = GetEventData();				// we attack this character
	aref rMainGroupCharacter = GetEventData();		// commander character for rCharacter
	int iRelation = GetEventData();
	
	if (LAi_IsDead(rCharacter)) return; // fix - нефиг палить в труп!
	
	// if companion - decrease reputation
	if (IsCompanion(rCharacter))
	{
		if (CheckAttribute(rCharacter, "CompanionEnemyEnable") && sti(rCharacter.CompanionEnemyEnable))
		{
			SeaAI_SetCompanionEnemy(rCharacter);
			// disconnect companion from our group and set it enemy to us
		}
		return;
	}
	else
	{
	    if (CheckAttribute(rCharacter, "ShipEnemyDisable") )  return; // флаг не обижаться на выстрелы
	    // убрал || CheckAttribute(rCharacter, "AlwaysFriend") тк если по отпущенному торговцу палить, то должен обижаться
	    DeleteAttribute(rCharacter, "AlwaysFriend");
	}
			
	if (iRelation != RELATION_ENEMY)
	{
		Ship_NationAgressive(rMainGroupCharacter, rCharacter);// boal 030804 в один метод
		// making whole group as enemy to us
		if (CheckAttribute(rMainGroupCharacter, "SeaAI.Group.Name"))
		{
			Group_SetEnemyToCharacter(rMainGroupCharacter.SeaAI.Group.Name, nMainCharacterIndex);
		}
		/* // наследие К3, в ВМЛ только мешает
		if (CheckAttribute(&rCharacter, "relation.UseOtherCharacter"))
		{
			if (sti(rCharacter.relation.UseOtherCharacter) >= 0)
			{
				SetCharacterRelationBoth(nMainCharacterIndex, sti(rCharacter.relation.UseOtherCharacter), RELATION_ENEMY);
			}
		}*/
	}
	else
	{
		if(!CheckAttribute(rCharacter, "Coastal_Captain"))
		{
			// патент нужно отнять даже если враг
			Ship_NationAgressivePatent(rCharacter);// патент отнимаем всегда, когда палим по другу патента
		}
	}
	DoQuestCheckDelay("NationUpdate", 0.3);
	//UpdateRelations();
	RefreshBattleInterface();

	//eddy. корабли с залоченным таском не менять
	if (CheckAttribute(rCharacter, "ShipTaskLock")) return;

	/*eddy
	int i;
	string sGroupID, sGroupType;
	ref rGroup;

	// clear group temporary task status
	// for (i=0; i<MAX_SHIP_GROUPS; i++) { AIGroups[i].TempTask = false; }

	// looking for enemy war/trade ships around
	for (i=0; i<iNumShips; i++)
	{
		ref rShipCharacter = GetCharacter(Ships[i]);

		if (SeaAI_GetRelation(GetMainCharacterIndex(), Ships[i]) != RELATION_ENEMY) continue;

		sGroupID = Ship_GetGroupID(rShipCharacter);
		sGroupType = Group_GetType(sGroupID);
		rGroup = Group_GetGroupByID(sGroupID);

		float fDistance = Ship_GetDistance2D(GetMainCharacter(), rShipCharacter);

		//вообще неясно, для чего это, если ниже все одно атака групп
		if (!sti(rGroup.TempTask) && fDistance < 2000.0)	// if distance < 2 km
		{
			switch (sGroupType)
			{
				case "trade":
					Group_SetTaskRunaway(sGroupID, PLAYER_GROUP);
				break;
				case "war":
					Group_SetTaskAttack(sGroupID, PLAYER_GROUP);
				break;
				case "pirate":
					Group_SetTaskAttack(sGroupID, PLAYER_GROUP);
				break;
			}
		}
	}*/

	// if fort - return
	int iShipType = sti(rCharacter.Ship.Type);
	iShipType = sti(RealShips[iShipType].basetype);
	if (ShipsTypes[iShipType].name == "Fort") 
	{ 
		return; 
	}

	string sGroupID = Ship_GetGroupID(rMainGroupCharacter);
	Group_SetTaskAttack(PLAYER_GROUP, sGroupID);
}

void Ship_SetBlot()
{
	aref rCharacter = GetEventData();
	
	// TODO
}

float Ship_MastDamage()
{
	int iDamageType 	= GetEventData();
	int iMastNum 		= GetEventData();
	float x 			= GetEventData();
	float y 			= GetEventData();
	float z 			= GetEventData();
	float fDamage 		= GetEventData();
	aref rCharacter 	= GetEventData();
	
	if (LAi_IsImmortal(rCharacter)) return 0.0;
	
	// belamour legendaty edition фикс неломающихся мачт у первоклассников 
	float fBonus        = 1.0;
	if(2-sti(RealShips[sti(rCharacter.ship.type)].Class) > 0) fBonus = 0.5;
	
	switch (iDamageType)
	{
		case SHIP_MAST_TOUCH_ISLAND:
            if(CheckAttribute(rCharacter, "AlwaysSandbankManeuver")) return 0.0; // Тупым запрет ломать мачты о берег
			fDamage = fDamage + 0.25*fBonus;
		break;
		case SHIP_MAST_TOUCH_SHIP:
			fDamage = fDamage + 0.2*fBonus;
		break;
		case SHIP_MAST_TOUCH_BALL:
			int iBallOwnerIndex 	= GetEventData();
			ref	rBallCharacter 		= GetCharacter(iBallOwnerIndex);	// кто пуляет
			int	iBallType = sti(AIBalls.CurrentBallType);   			// спорно, тк это не ядра, того кто стрелял, а скорее ядра ГГ
			switch (iBallType)
			{
				case GOOD_BALLS:
					fDamage = fDamage + 0.1*fBonus;
				break;
				case GOOD_GRAPES:
					fDamage = fDamage + 0.05*fBonus;
				break;
				case GOOD_KNIPPELS:
					fDamage = fDamage + 0.25*fBonus;
				break;
				case GOOD_BOMBS:
					fDamage = fDamage + 0.15*fBonus;
				break;
			}
			
		break;
	}

	fDamage = Clampf(fDamage);

	if (fDamage >= 1.0)
	{
		Play3DSoundEvent("ShipEMB/MastFall", x, y, z); // if mast fall - play sound
		rCharacter.Tmp.SpeedRecall = 0; 	// чтоб пересчитался маневр
		RefreshBattleInterface();
	}
	
	if(iDamageType == SHIP_MAST_TOUCH_BALL)
	{
		rCharacter.Ship.LastBallCharacter = iBallOwnerIndex;
//		Log_Info(" Ship_MastDamage : Character.id = " + rCharacter.id + " BallOwner.id = " + rBallCharacter.id);
		if (sti(rCharacter.Ship.LastBallCharacter) == GetMainCharacterIndex() 
			&& GetNationRelation2MainCharacter(sti(rCharacter.nation)) != RELATION_ENEMY)
		{
			if (!IsCompanion(rCharacter) && !CheckAttribute(rCharacter, "Coastal_Captain")) 
			{
				Ship_NationAgressive(rCharacter, rCharacter);// boal 030804 в один метод
				DoQuestCheckDelay("NationUpdate", 0.7);
			}
		}		
	}	
	return fDamage;	
}

float Ship_HullDamage()
{
	int iDamageType = GetEventData();
	int iHullNum = GetEventData(); // номер ноды в которую прилетело
	float x = GetEventData();
	float y = GetEventData();
	float z = GetEventData();
	float fDamage = GetEventData();
	aref rCharacter = GetEventData(); // в кого прилетело
	//aref aCharacter = GetEventData(); // владелец ядра (от кого прилетело)
	string HullName = GetEventData(); // имя ноды в которую прилетело
	
	switch (iDamageType)
	{
		case SHIP_HULL_TOUCH_BALL:
			int	iBallType = sti(AIBalls.CurrentBallType);   //спорно, тк это не ядра, того кто стрелял, а скорее ядра ГГ
			switch (iBallType)
			{
				case GOOD_BALLS:
					fDamage = fDamage + 0.40;
				break;
				case GOOD_GRAPES:
					fDamage = fDamage + 0.10;
				break;
				case GOOD_KNIPPELS:
					fDamage = fDamage + 0.20;
				break;
				case GOOD_BOMBS:
					fDamage = fDamage + 0.65;
				break;
			}
		break;
	}

	fDamage = Clampf(fDamage);
	if (fDamage >= 1.0)
	{
		CreateBlast(x,y,z);
		CreateParticleSystem("blast_inv", x, y, z, 0.0, 0.0, 0.0, 0);
		Play3DSound("cannon_explosion", x, y, z); // to_do
		RefreshBattleInterface();
		
		if(HasSubStr(HullName, "baller")) // потеряли перо руля
		{
			rCharacter.Ship.hulls.baller_destroyed = true; // признак поломки руля
			string sDamagedString = XI_ConvertString("ShipFight1") + rCharacter.Ship.Name + XI_ConvertString("ShipFight2");
			Log_SetStringToLog(sDamagedString);
		}
	}
	return fDamage;
}

// also see ShipSailState
float Ship_GetSailState(ref rCharacter)
{
	float fSailState = 1.0;
	SendMessage(rCharacter, "le", MSG_SHIP_GET_SAIL_STATE, &fSailState);
	return fSailState;
}
// boal 27.09.05 -->
void Ship_SetExplosion(ref rCharacter, ref rShipObject)
{
    // fire ship
    /*
	int iNumFirePlaces = rand(2);
	SendMessage(rShipObject, "le", MSG_SHIP_GET_NUM_FIRE_PLACES, &iNumFirePlaces);
	for (int i=0; i<=iNumFirePlaces; i++)
	{
		PostEvent(SHIP_ACTIVATE_FIRE_PLACE, rand(300), "ialsfl", rShipObject, rCharacter, i, "ShipEMB/ShipDamage_Fire", 3, -1);
	}
    */
	//PostEvent(SHIP_ACTIVATE_FIRE_PLACE, 100, "ialsfl", rShipObject, rCharacter, i, "ShipEMB/ShipDamage_Fire", 3, -1);  // даёт вылет
    float x, y, z;
    x = stf(rCharacter.ship.pos.x);
    y = stf(rCharacter.ship.pos.y);
    z = stf(rCharacter.ship.pos.z);
	PostEvent(SHIP_BRANDER_DETONATE, 800, "l", sti(rCharacter.index));
    Play3DSoundEvent("ShipEMB/Explosion_kruyt", x, y, z);
	Ship_SetTaskNone(SECONDARY_TASK, sti(rCharacter.index));
}
// boal <--
void Ship_SetSailState(int iCharacterIndex, float fSailState)
{
	SendMessage(&AISea, "laf", AI_MESSAGE_SHIP_SET_SAIL_STATE, &Characters[iCharacterIndex], fSailState);
}

void Ship_SetTaskNone(int iTaskPriority, int iCharacterIndex)
{
	ref rCharacter = GetCharacter(iCharacterIndex);
	rCharacter.SeaAI.Task = AITASK_NONE;
}

void Ship_SetTaskAbordage(int iTaskPriority, int iCharacterIndex, int iCharacterIndexAbordageTo)
{
	ref rCharacter = GetCharacter(iCharacterIndex);
	rCharacter.SeaAI.Task = AITASK_ABORDAGE;
	rCharacter.SeaAI.Task.Target = iCharacterIndexAbordageTo;
	SendMessage(&AISea, "lllaa", AI_MESSAGE_SHIP_SET_TASK, AITASK_ABORDAGE, iTaskPriority, &Characters[iCharacterIndex], &Characters[iCharacterIndexAbordageTo]);
}

void Ship_SetTaskBrander(int iTaskPriority, int iCharacterIndex, int iCharacterIndexBranderTo)
{
	ref rCharacter = GetCharacter(iCharacterIndex);
	rCharacter.SeaAI.Task = AITASK_BRANDER;
	rCharacter.SeaAI.Task.Target = iCharacterIndexBranderTo;
	SendMessage(&AISea, "lllaa", AI_MESSAGE_SHIP_SET_TASK, AITASK_BRANDER, iTaskPriority, &Characters[iCharacterIndex], &Characters[iCharacterIndexBranderTo]);
}

void Ship_SetTaskMove(int iTaskPriority, int iCharacterIndex, float x, float z)
{
	ref rCharacter = GetCharacter(iCharacterIndex);
	rCharacter.SeaAI.Task = AITASK_MOVE;
	//rCharacter.SeaAI.Task.Target = "";
	rCharacter.SeaAI.Task.Pos.x = x;
	rCharacter.SeaAI.Task.Pos.z = z;
	SendMessage(&AISea, "lllaff", AI_MESSAGE_SHIP_SET_TASK, AITASK_MOVE, iTaskPriority, &Characters[iCharacterIndex], x, z);
}

void Ship_SetTaskRunaway(int iTaskPriority, int iCharacterIndex, int iFromIndex)
{
	ref rCharacter = GetCharacter(iCharacterIndex);
	rCharacter.SeaAI.Task = AITASK_RUNAWAY;
	rCharacter.SeaAI.Task.Target = iFromIndex;
	SendMessage(&AISea, "llla", AI_MESSAGE_SHIP_SET_TASK, AITASK_RUNAWAY, iTaskPriority, &Characters[iCharacterIndex]);	
	Ship_SetSailState(iCharacterIndex, 1);
}

void Ship_SetTaskAttack(int iTaskPriority, int iCharacterIndex, int iCharacterIndexVictim)
{
	ref rCharacter = GetCharacter(iCharacterIndex);
	rCharacter.SeaAI.Task = AITASK_ATTACK;
	rCharacter.SeaAI.Task.Target = iCharacterIndexVictim;
	SendMessage(&AISea, "lllaa", AI_MESSAGE_SHIP_SET_TASK, AITASK_ATTACK, iTaskPriority, &Characters[iCharacterIndex], &Characters[iCharacterIndexVictim]);
}

void Ship_SetTaskSailTo(int iTaskPriority, int iCharacterIndex, int iCharacterIndexSailTo)
{
	ref rCharacter = GetCharacter(iCharacterIndex);
	rCharacter.SeaAI.Task = AITASK_MOVE;
	rCharacter.SeaAI.Task.Target = iCharacterIndexSailTo;
	SendMessage(&AISea, "lllaa", AI_MESSAGE_SHIP_SET_TASK, AITASK_MOVE, iTaskPriority, &Characters[iCharacterIndex], &Characters[iCharacterIndexSailTo]);
}

void Ship_SetTaskDrift(int iTaskPriority, int iCharacterIndex)
{
	ref rCharacter = GetCharacter(iCharacterIndex);
	rCharacter.SeaAI.Task = AITASK_DRIFT;
	//rCharacter.SeaAI.Task.Target = "";
	SendMessage(&AISea, "llla", AI_MESSAGE_SHIP_SET_TASK, AITASK_DRIFT, iTaskPriority, &Characters[iCharacterIndex]);
}

void Ship_SetTaskDefendGroup(int iTaskPriority, int iCharacterIndex, string sDefendGroup)
{
	SendMessage(&AISea, "lllas", AI_MESSAGE_SHIP_SET_TASK, AITASK_DEFEND_GROUP, iTaskPriority, &Characters[iCharacterIndex], sDefendGroup);
}

void Ship_SetTaskDefend(int iTaskPriority, int iCharacterIndex, int iCharacterIndex2Defend)
{
	ref rCharacter = GetCharacter(iCharacterIndex);
	rCharacter.SeaAI.Task = AITASK_DEFEND;
	rCharacter.SeaAI.Task.Target = iCharacterIndex2Defend;
	SendMessage(&AISea, "lllaa", AI_MESSAGE_SHIP_SET_TASK, AITASK_DEFEND, iTaskPriority, &Characters[iCharacterIndex], &Characters[iCharacterIndex2Defend]);
}

void Ship_DoFire()
{
	int bCameraOutside = SeaCameras_isCameraOutside();// || CrosshairHidden();     // LDH 17Jan17 aimed fire when crosshair visible
	// LDH 09Feb17 - tell player how to get aiming crogghair
/*	bool bTemp = bMapEnter || bCanEnterToLand;	// LDH 11Feb17
	if (CrosshairHidden() && GetCurControlGroup() == "Sailing1Pers" && bTemp)
		Log_Info("Нажмите клавишу 'C' для активации прицельного огня");*/
	SendMessage(&AISea, "lal", AI_MESSAGE_CANNON_FIRE, &Characters[nMainCharacterIndex], bCameraOutside);
}

void Ship_StartLoad()
{
	aref rCharacter = GetEventData();
	if(rCharacter.id != "0" && sti(rCharacter.ship.type) != SHIP_NOTUSED)
	{
		ref refBaseShip;
		int nShipType = GetCharacterShipType(rCharacter);
		refBaseShip = GetRealShip(nShipType);
		SetTextureForShip(refBaseShip, rCharacter);
	}
}

void Ship_EndLoad()
{
	SetTexturePath(0, "");
}

void Ship_SetTrackSettings(ref rCharacter)
{
	ref rShip = GetRealShip(GetCharacterShipType(rCharacter));

	rCharacter.Ship.Track.Enable = rShip.Track.Enable;
	if (!sti(rShip.Track.Enable)) return;

	rCharacter.Ship.Track.TrackDistance = 1.0;
	rCharacter.Ship.Track.WaveHeight2 = 0.9;
	rCharacter.Ship.Track.WaveHeight1 = 0.2;

	if (GetTime() >= 6.0 && GetTime() <= 20.0)
	{
	rCharacter.Ship.Track1.Texture = "ships\trailShip.tga";
	rCharacter.Ship.Track2.Texture = "ships\trailKeel.tga";
	}
	else
	{
	rCharacter.Ship.Track1.Texture = "ships\trailShip_n.tga";
	rCharacter.Ship.Track2.Texture = "ships\trailKeel_n.tga";	
	}

	rCharacter.Ship.Track1.TrackWidthSteps = 12.0;
	rCharacter.Ship.Track2.TrackWidthSteps = 4.0;

	rCharacter.Ship.Track1.ZStart = rShip.Track1.ZStart;
	rCharacter.Ship.Track1.LifeTime = rShip.Track1.LifeTime;
	rCharacter.Ship.Track1.Width = rShip.Track1.Width;
	rCharacter.Ship.Track1.Speed = rShip.Track1.Speed;

	rCharacter.Ship.Track2.ZStart = rShip.Track2.ZStart;
	rCharacter.Ship.Track2.LifeTime = rShip.Track2.LifeTime;
	rCharacter.Ship.Track2.Width = rShip.Track2.Width;
	rCharacter.Ship.Track2.Speed = rShip.Track2.Speed;
}

void Ship_SetLightsOff(ref rCharacter, float fTime, bool bLights, bool bFlares, bool bNow)
{
	SendMessage(rCharacter, "lflll", MSG_SHIP_SETLIGHTSOFF, fTime, bLights, bFlares, bNow);
	rCharacter.Ship.Lights = 0; //fix
}

void Ship_SetLightsAndFlares(ref rCharacter)
{
	if(CheckAttribute(sea,"lights") && sti(sea.lights) == 1)
	{
		rCharacter.Ship.Flares = 1;
		rCharacter.Ship.Lights = 1;
	}
	else
	{
		rCharacter.Ship.Flares = 0;
		rCharacter.Ship.Lights = 0;
	}
    trace("Ship.Lights = " + sti(rCharacter.Ship.Lights));
}

void Ship_Add2Sea(int iCharacterIndex, bool bFromCoast, string sFantomType, bool isOffline)
{
	ref rCharacter = GetCharacter(iCharacterIndex);

	DeleteAttribute(rCharacter, "ship.cannons.chance_for_explode"); //to_do у нас не юзается

	aref arCharacter; makearef(arCharacter, Characters[sti(rCharacter.index)]);
	
	int iShipType = sti(rCharacter.Ship.Type);

	if(iShipType == SHIP_NOTUSED)
	{
		return;
	}

	int iRealShip = sti(RealShips[iShipType].basetype);

	if(!CheckAttribute(&RealShips[iShipType], "name"))
	{
		Trace("Ship_Add2Sea() : SHIP " + iShipType + ", have no name!   NPCid = "+ rCharacter.id);
		if (MOD_BETTATESTMODE == "On") Log_Info("Ship_Add2Sea ERROR : SHIP " + iShipType + ", have no name!   NPCid = "+ rCharacter.id);
		return;
	}
	if (iRealShip >= GetArraySize(&ShipsTypes))
	{
		Trace("Character.id = " + rCharacter.id + ", have invalid ship type = " + iShipType + ", and try load to sea");
		return;
	}
	// boal -->
	// 22.04.05 сброс всех отношений
    if (!CheckAttribute(rCharacter, "AlwaysEnemy") && !CheckAttribute(rCharacter, "AlwaysFriend")) // у врагов не трем
    {
    	DelCharacterRelation(iCharacterIndex);
    }
    else
    {
		if (CheckAttribute(rCharacter, "AlwaysFriend"))
		{
			SetCharacterRelationBoth(iCharacterIndex, GetMainCharacterIndex(), RELATION_FRIEND);
		}
		if (CheckAttribute(rCharacter, "AlwaysEnemy"))
		{
			SetCharacterRelationBoth(iCharacterIndex, GetMainCharacterIndex(), RELATION_ENEMY);
		}
    }
    DeleteAttribute(rCharacter, "Ship_SetTaskAbordage"); // boal
    DeleteAttribute(rCharacter, "Killer.status"); // boal 09.06.05 SUPER FIX
    DeleteAttribute(rCharacter, "CheckFlagYet"); // флаг распознования врага
    DeleteAttribute(rCharacter, "CheckNationBounty"); // Проверка НЗГ за нацию друга базе
    DeleteAttribute(rCharacter, "ShipCannonChargeType"); // флаг офов, чем пулять постоянно, ставится игроком командами, до след приказа Атака или конца снарядов
    DeleteAttribute(rCharacter, "SeaAI.RunAwayPnt");

	if (CheckAttribute(rCharacter, "DontCheckFlag"))
	{
	    rCharacter.CheckFlagYet = true;
	}
    rCharacter.TmpSkillRecall = "0"; //boal 25.05.04 оптимизация расчета, когда == 0 считаем скилы
    rCharacter.Tmp.SpeedRecall = 0; // оптимизация скорости и маневра
    rCharacter.Tmp.fShipSpeed  = 1; // начальная инициация
	rCharacter.Tmp.fWatchFort  = rand(15); // оптимизация оглядок на форт
	rCharacter.Tmp.fWatchFort.Qty = 15;
    // boal <--
	if (CheckAttribute(GetCharacter(iCharacterIndex), "SeaFantom"))
	{
		SetBaseShipData(rCharacter);
		Ship_SetFantomData(rCharacter);
		Fantom_SetUpgrade(rCharacter, sFantomType);		
        Fantom_SetCannons(rCharacter, sFantomType);
		Fantom_SetBalls(rCharacter, sFantomType);
		Fantom_SetGoods(rCharacter, sFantomType);
		SaveCurrentNpcQuestDateParam(rCharacter, "Add2SeaTime"); //фантомы помнят время входа в море
	}
	ApplyShipDynamicSpeedEffects(rCharacter);
	//rCharacter.TmpPerks.Turn = false;

	CharacterUpdateShipFromBaseShip(iCharacterIndex);

	rCharacter.Ship.Ang.y = 0.0;

	Ship_ClearImpulseStrength(rCharacter);
	Ship_SetLightsAndFlares(rCharacter);
	Ship_SetTrackSettings(rCharacter);

	aref baseship;
	ref refBaseShip;

	makearef(baseship,rCharacter.ship);
	int nShipType = GetCharacterShipType(rCharacter);
	refBaseShip = GetRealShip(nShipType);

	rCharacter.Tmp.BortsReloaded.Event = false;
	rCharacter.Tmp.BortsReloaded.cannonl = false;
	rCharacter.Tmp.BortsReloaded.cannonr = false;
    rCharacter.BOAL_ReadyCharge = "1"; // в начале всегда заряжен ядрами, пусть и палит ими

	rCharacter.Features.GeraldSails = true;
	rCharacter.Ship.LastBallCharacter = -1;
	rCharacter.Ship.WindDotShip = 1.0;
	rCharacter.Ship.Speed.z = 0.0;
	rCharacter.Ship.Speed.y = 0.0;
	rCharacter.Ship.Speed.x = 0.0;
	
	//  убрать это, когда будет в ядре работать
	rCharacter.Ship.BoxSize.x = 1.0;  // должно считаться в ядре :( не работает
	rCharacter.Ship.BoxSize.y = 1.0;
	rCharacter.Ship.BoxSize.z = 2.0;

    rCharacter.Ship.Sounds = "";
	rCharacter.Ship.Strand = false;
	rCharacter.Ship.Strand.SndID = SOUND_INVALID_ID;
	rCharacter.Ship.Stopped = false;
	rCharacter.Ship.POS.Mode = SHIP_SAIL;
	rCharacter.Ship.SeaAI.Init.AbordageDistance = 30.0;

	ref	rCannon = GetCannonByType(sti(rCharacter.Ship.Cannons.Type));
	float fRange = "FireRange" in rCannon ? float(rCannon.FireRange) : 550.0;
	rCharacter.Ship.SeaAI.Init.AttackDistance = fRange / (1.4 + frandSmall(2.0)); // Это очень важный параметр, он определяет дистанцию АИ, на которой будет стараться держаться корабль
	rCharacter.Ship.SeaAI.Init.FollowDistance = makefloat(180.0 + rand(120)); // Было 300, делаю рандом для разнообразия поведения компаньонов и следования в группе
    rCharacter.SeaAI.ChargeTicks = 0;

	if(sti(rCharacter.Ship.Cannons.Type) == CANNON_TYPE_NONECANNON)
	{
		rCharacter.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS12;
	}

	if (bFromCoast == false) { rCharacter.Ship.Speed.z = 1.0; }

	// create ship
	Event("eSwitchPerks", "l", iCharacterIndex);											// Perks
	//Event(SHIP_UPDATE_PARAMETERS, "lf", iCharacterIndex, stf(rCharacter.Ship.Speed.z));   // Parameters
	
	//ugeen --> жесть !! у энкаунтеров не снят атрибут Ship.Sink <-- 3 часа трахался из-за этой ошибки :(  <-- из-за неё некорректно работал мод флагов
	if(CheckAttribute(rCharacter,"Ship.Sink")) {trace("ShipSink rCharacter.id = " + rCharacter.id); DeleteAttribute(rCharacter,"Ship.Sink");}
	
	CreateEntity(&Characters[iCharacterIndex], "Ship");
	
    Event(SHIP_UPDATE_PARAMETERS, "lf", iCharacterIndex, stf(rCharacter.Ship.Speed.z));		// Parameters      после создания корабля

	aref arChar, arShip;
	makearef(arChar, characters[iCharacterIndex]);
	makearef(arShip, RealShips[iShipType]);

	Ship_CreateStaticSounds(rCharacter);

	//SendMessage(&AISea, "liaa", AI_MESSAGE_ADD_SHIP, &Characters[iCharacterIndex], &Characters[iCharacterIndex], &RealShips[iShipType]);
	SendMessage(&AISea, "liaa", AI_MESSAGE_ADD_SHIP, &Characters[iCharacterIndex], arChar, arShip);

	float ax = 0.0;
	float az = 0.0;	
/*	
	if(SetHeel_XZ(rCharacter,  &ax, &az)) // крен
	{
		SendMessage(rCharacter, "lff", MSG_SHIP_SET_HEEL_XZ, ax, az); 
	}	
*/	
	// Только для примера - освободить все паруса одного корабля от эффекта надувания
	//SendMessage(&Sail,"li", MSG_SAIL_FREE_GROUP, &Characters[iCharacterIndex]);
	
    /* if (!CheckAttribute(rCharacter, "Ship.BoxSize.x"))
	{
		trace("No Ship.BoxSize id=" + rCharacter.id);
		rCharacter.Ship.BoxSize.x = 1.0;  // должно считаться в ядре
		rCharacter.Ship.BoxSize.y = 1.0;
		rCharacter.Ship.BoxSize.z = 2.0;
	} */
	if(isOffline) ReloadProgressUpdate();
	
	Ships[iNumShips] = iCharacterIndex;
	iNumShips++;
}

void Ship_OnBortReloaded()
{
	aref aCharacter = GetEventData();
	string sBort = GetEventData();

	if (!bSeaLoaded || bAbordageStarted) { return; }  // fix
	// далее по коду была глупость, тк прерывание шло по всем НПС, звуков таких не было вовсе в ресурсах, те мина была в игре. "Сапер boal"
	if (sti(aCharacter.index) != nMainCharacterIndex) { return; } // fix
	/*{
		if (sBort == "cannonl" || sBort == "cannonr") { Ship_PlaySound3D(aCharacter, "bortreloaded_" + sBort, 1.0);	}
		//"bortreloaded_all"
	}*/

	if (!sti(aCharacter.Tmp.BortsReloaded.Event))
	{
		aCharacter.Tmp.BortsReloaded.Event = true;
		PostEvent("Ship_BortReloadEvent", 300, "a", aCharacter);
	}
	if (sBort == "cannonl") { aCharacter.Tmp.BortsReloaded.cannonl = true; }
	if (sBort == "cannonr") { aCharacter.Tmp.BortsReloaded.cannonr = true; }
}

void Ship_BortReloadEvent()
{
	aref aCharacter = GetEventData();
	
	if (sti(aCharacter.Tmp.BortsReloaded.Event))
	{
		bool bLeft = sti(aCharacter.Tmp.BortsReloaded.cannonl) == true;
		bool bRight = sti(aCharacter.Tmp.BortsReloaded.cannonr) == true;

		if (bLeft && bRight)
		{
			//Ship_PlaySound3D(aCharacter, "bortreloaded_all", 1.0);
			// типа перезарядка двух бортов PlaySound("interface\_GunReady.wav");
		}
		else
		{
			if (bLeft)  { PlaySound("interface\" + LanguageGetLanguage() + "\_GunReadyL.wav"); }
			if (bRight) { PlaySound("interface\" + LanguageGetLanguage() + "\_GunReadyR.wav"); }
		}
	}

	Ship_ClearBortsReloadedEvent(aCharacter);
}

void Ship_ClearBortsReloadedEvent(aref aCharacter)
{
	aCharacter.Tmp.BortsReloaded.Event = false;
	aCharacter.Tmp.BortsReloaded.cannonl = false; 
	aCharacter.Tmp.BortsReloaded.cannonr = false; 
}

void Ship_ChangeChargeEvent() // нигде не используется???
{
	string	sBallName;
	
	ref rCharacter = GetCharacter(GetEventData());

	SendMessage(&AISea, "la", AI_MESSAGE_CANNON_RELOAD, rCharacter);
	sBallName = GetEventData();
	rCharacter.Ship.Cannons.Charge = sBallName;
	Cannon_RecalculateParameters(sti(rCharacter.index));

	//fix if (bSeaLoaded) { Ship_PlaySound3D(rCharacter, "reloadstart_" + sBallName, 1.0); }

	Ship_ClearBortsReloadedEvent(rCharacter);
}

void Ship_ChangeCharge(ref rCharacter, int iNewChargeType)
{
	int iCurrentChargeType = rCharacter.Ship.Cannons.Charge.Type;
	if(iNewChargeType == iCurrentChargeType)
		return;
	
	float rCharge, lCharge, fCharge, bCharge;
	rCharge = ("Ship.Cannons.borts.cannonr.ChargeRatio" in rCharacter) ? rCharacter.Ship.Cannons.borts.cannonr.ChargeRatio : 1.0;
	lCharge = ("Ship.Cannons.borts.cannonl.ChargeRatio" in rCharacter) ? rCharacter.Ship.Cannons.borts.cannonl.ChargeRatio : 1.0;
	fCharge = ("Ship.Cannons.borts.cannonf.ChargeRatio" in rCharacter) ? rCharacter.Ship.Cannons.borts.cannonf.ChargeRatio : 1.0;
	bCharge = ("Ship.Cannons.borts.cannonb.ChargeRatio" in rCharacter) ? rCharacter.Ship.Cannons.borts.cannonb.ChargeRatio : 1.0;
	
	SendMessage(&AISea, "la", AI_MESSAGE_CANNON_RELOAD, rCharacter); // must be first line in this function
	
	if (CheckOfficersPerk(rCharacter, "CriticalShoot"))
	{
		if (rCharge == 1.0)
			SendMessage(&AISea, "lasf", AI_MESSAGE_SET_CANNON_RECHARGE, rCharacter, "cannonr", PERK_VALUE2_CRITICAL_SHOOT);
		if (lCharge == 1.0)
			SendMessage(&AISea, "lasf", AI_MESSAGE_SET_CANNON_RECHARGE, rCharacter, "cannonl", PERK_VALUE2_CRITICAL_SHOOT);
		if (fCharge == 1.0)
			SendMessage(&AISea, "lasf", AI_MESSAGE_SET_CANNON_RECHARGE, rCharacter, "cannonf", PERK_VALUE2_CRITICAL_SHOOT);
		if (bCharge == 1.0)
			SendMessage(&AISea, "lasf", AI_MESSAGE_SET_CANNON_RECHARGE, rCharacter, "cannonb", PERK_VALUE2_CRITICAL_SHOOT);
	}

	ref rGood = GetGoodByType(iNewChargeType);
	rCharacter.Ship.Cannons.Charge = rGood.name;
	rCharacter.Ship.Cannons.Charge.Type = iNewChargeType;
	
	AI_SetFireMode(rCharacter, iNewChargeType);

	Cannon_RecalculateParameters(sti(rCharacter.index));

	rCharacter.BOAL_ReadyCharge = "1";
    rCharacter.SeaAI.ChargeTicks = 0;

	//fix Ship_PlaySound3D(rCharacter, "reloadstart_" + rGood.name, 1.0);

	Ship_ClearBortsReloadedEvent(rCharacter);
}

void Ship_OnCreate()
{
	ref rCharacter = GetCharacter(GetEventData());
	
	rCharacter.Ship.Speed.z = 0.0;
	rCharacter.Ship.Speed.y = 0.0;
	rCharacter.Ship.Speed.x = 0.0;
}

void Ship_SetSurrendered(ref rCharacter)
{
	if (LAi_IsDead(rCharacter) || sti(rCharacter.ship.type) == SHIP_NOTUSED) return; 
	if (CheckAttribute(rCharacter,"surrendered")) return;
	
	ref rBaseShip = GetRealShip(sti(rCharacter.Ship.Type));
	rCharacter.surrendered = true;	
	Ship_FlagRefresh(rCharacter); //флаг на лету
	
	string sSurrenderString;
	string sSurrenderShipType = XI_ConvertString(rBaseShip.BaseName);
	sSurrenderString = sSurrenderShipType + " '" + rCharacter.Ship.Name + "' " +GetShipSexWord(rBaseShip.BaseName, XI_ConvertString("ShipFight3M"), XI_ConvertString("ShipFight3W")) + XI_ConvertString("ShipFight4");
	Log_SetStringToLog(sSurrenderString);
	
	Ship_SetTaskRunaway(SECONDARY_TASK, sti(rCharacter.index), GetMainCharacterIndex());
	
	SetCharacterRelationBoth(sti(rCharacter.index), GetMainCharacterIndex(), RELATION_FRIEND);
	rCharacter.AlwaysFriend = true; // флаг - не обижаться на выстрелы, абордировать нельзя, можно только выслать шлюпку
	UpdateRelations();
	RefreshBattleInterface();
	DoQuestCheckDelay("NationUpdate", 1.5);
}

bool Ship_CheckSurrendered(ref echr)
{
	bool bOk = true;

	if (LAi_IsDead(echr) || sti(echr.ship.type) == SHIP_NOTUSED) return false;
	if (sti(echr.index) == nMainCharacterIndex) return false;
	if (IsCompanion(echr)) return false;	
	if (GetNationRelation2MainCharacter(sti(echr.nation)) != RELATION_ENEMY) return false;
	if (CheckAttribute(echr,"situation")) return false;
	
	if(CheckAttribute(echr,"DontSurrender")) return false;
	
	if (sti(echr.Nation) == PIRATE || CheckAttribute(echr, "DontRansackCaptain")) return false; // квестовые и пираты не выбрасывают белый флаг
	
	ref mchr = GetMainCharacter();
	
	if (sti(echr.rank) > (40 - MOD_SKILL_ENEMY_RATE)) bOk = false; 	
	if (sti(mchr.rank) < (sti(echr.rank) - MOD_SKILL_ENEMY_RATE / 2))  bOk = false;
	
	int eclass = GetCharacterShipClass(echr);
	int mclass = GetCharacterShipClass(mchr);
	if (eclass == 1) bOk = false;
	
	if(!bOk) 
	{
		echr.DontSurrender = true;
		return false;
	}	
	
	float fCrewRate = 0.5;  
	if (CheckAttribute(echr, "Ship.Mode"))
	{
		switch(echr.Ship.Mode)
		{
			case "Trade":
				fCrewRate = 0.6;
			break;
			case "War" 	:
				fCrewRate = 0.2;
			break;
		}
	}
	float mcrew = stf(GetWeaponCrew(mchr, GetCrewQuantity(mchr))); // честный учёт с оружием
	float ecrew = stf(GetCrewQuantity(echr));
	
	float fRep    = abs(REPUTATION_NEUTRAL - sti(mchr.reputation.nobility)) / 50.0; // приведение к 0..1
	float emorale = stf(echr.ship.crew.morale) / MORALE_MAX; // 0..1  это рандом
	float mmorale = stf(mchr.ship.crew.morale) / MORALE_MAX; // 0..1
	float mskill  = (GetSummonSkillFromNameToOld(mchr, "Leadership") + GetSummonSkillFromNameToOld(mchr, "Grappling")) / 20.0;  // 0..10
	float eskill  = (GetCharacterSkillToOld(echr, "Leadership") + GetCharacterSkillToOld(echr, "Defence")) / 20.0;    // 0..10
	
	mcrew = mcrew * (mcrew * GetCrewExp(mchr, "Soldiers")) / (GetOptCrewQuantity(mchr) * GetCrewExpRate()); 
    ecrew = ecrew * (ecrew * GetCrewExp(echr, "Soldiers")) / (GetOptCrewQuantity(echr) * GetCrewExpRate());  // это рандом, а значит случайность
	
    mcrew = mcrew *(0.5 + mmorale);
    ecrew = ecrew *(0.5 + emorale); // рандом в  emorale - она ранд
    
    mcrew = mcrew * (0.2 + mskill)*(0.05 + fRep)*fCrewRate;
    ecrew = ecrew * (0.2 + eskill);

	int mShip = GetCompanionQuantity(mchr);
    int eShip;
    string sGroupID = Ship_GetGroupID(echr);
    if (sGroupID != "") eShip = Group_GetLiveCharactersNum(sGroupID);
    else				eShip = 1;

	mcrew = mcrew * (1.0 + mclass / 20.0); // влияние класса минимально, тк есть в экипаже
    ecrew = ecrew * (1.0 + eclass / 20.0);  // класс также влияет наоборот, даёт бонус мелким
    
    mcrew = mcrew * (1.0 + (mShip-1) / 5.0);
    ecrew = ecrew * (1.0 + (eShip-1) / 5.0);
	
	if(ShipBonus2Artefact(mchr, SHIP_MEMENTO) && CheckAttribute(&RealShips[sti(mchr.Ship.Type)], "DeadSailors.SurrenderChanceBonus"))
	{
		mcrew *= 1.0 + stf(RealShips[sti(mchr.Ship.Type)].DeadSailors.SurrenderChanceBonus) / 100.0;
	}

    if (mcrew > ecrew)
	{
		// проверка на мин HP && SP		
		if (GetSailPercent(echr) < 25.0 || GetHullPercent(echr) < 25.0) return true; // выбросил белый флаг			
	}
	return false; // не сдался
}

void Ship_CheckSituation()
{
	aref rCharacter = GetEventData();
	aref rShipObject = GetEventData();
	
    int iChar = rCharacter.index;
	if (iChar == nMainCharacterIndex)
        return;

    int iShipType = rCharacter.Ship.Type;
	if (LAi_IsDead(rCharacter) || iShipType == SHIP_NOTUSED)
        return;

	string chrId = rCharacter.id;
	if ("SeaAI.Task" !in rCharacter)
	{
		trace("Character " + chrId  + " without task");
		rCharacter.SeaAI.Task = AITASK_NONE;
	}
    int iTask = rCharacter.SeaAI.Task;

    ref rTarget; // nullptr as default
	int iTarget = -1;
	if ("SeaAI.Task.Target" in rCharacter)
	{
		if (rCharacter.SeaAI.Task.Target != "")
	    {
            rTarget = GetCharacter(int(rCharacter.SeaAI.Task.Target));
            if (LAi_IsDead(rTarget))
            {
                rTarget = nullptr;
                DeleteAttribute(rCharacter, "SeaAI.Task.Target");
            }
            else iTarget = rTarget.index;
	    }
        else DeleteAttribute(rCharacter, "SeaAI.Task.Target");
    }

    ref rLastBallCharacter; // nullptr as default
	int iLastBallChar = -1;
	if (int(rCharacter.Ship.LastBallCharacter) != -1)
	{
        rLastBallCharacter = GetCharacter(int(rCharacter.Ship.LastBallCharacter));
        if (LAi_IsDead(rLastBallCharacter))
        {
            rLastBallCharacter = nullptr;
            rCharacter.Ship.LastBallCharacter = -1;
        }
        else iLastBallChar = rLastBallCharacter.index;
	}

	ref rShip = GetRealShip(iShipType);
	aref rSituation;
	makearef(rSituation, rCharacter.SeaAI.Update.Situation);

    float fDistance;
	float fMinEnemyDistance = rSituation.MinEnemyDistance;

	// boal проверка на абордаж не главного героя 27.01.2004 -->
    // check ships for abordage
    if (Ship_AutoAbordage(rCharacter, fMinEnemyDistance)) return;

	// Warship 08.07.09 Запрет спуска парусов
	if ("CanDropSails" in rCharacter && !int(rCharacter.CanDropSails))
		Ship_SetSailState(iChar, 1.0);

	// check for enought quantity of balls 
	int iShipCannonsNum  = GetCannonsNum(rCharacter);
	if ("ShipCannonChargeType" in rCharacter) // офам приказ, чем палить все время
	{
	    if (GetCargoGoods(rCharacter, int(rCharacter.ShipCannonChargeType)) < iShipCannonsNum)
	        DeleteAttribute(rCharacter, "ShipCannonChargeType"); // следующий проход решит на что менять заряд
	}
	else
	{
        int iCurrentBallType = rCharacter.Ship.Cannons.Charge.Type;
        bool bBalls    = GetCargoGoods(rCharacter, GOOD_BALLS)    >= iShipCannonsNum;
        bool bKnippels = GetCargoGoods(rCharacter, GOOD_KNIPPELS) >= iShipCannonsNum;
        bool bBombs    = GetCargoGoods(rCharacter, GOOD_BOMBS)    >= iShipCannonsNum;
        bool bGrapes   = GetCargoGoods(rCharacter, GOOD_GRAPES)   >= iShipCannonsNum;

		int iNewBallType = iCurrentBallType;
        if ("BOAL_ReadyCharge"  !in rCharacter) rCharacter.BOAL_ReadyCharge  = "1"; // на $-оператор
        if ("SeaAI.ChargeTicks" !in rCharacter) rCharacter.SeaAI.ChargeTicks = "0"; // на $-оператор
	    rCharacter.SeaAI.ChargeTicks = int(rCharacter.SeaAI.ChargeTicks) + 1;

        bool bForcedChange = true;
        ref rCannon = GetCannonByType(int(rCharacter.Ship.Cannons.Type));
        float fRange = rCannon.FireRange;
        // Накапало 20 тиков с текущим зарядом
	    if (int(rCharacter.SeaAI.ChargeTicks) >= 20)
	    {
            bool bOk1 = false, bOk2 = false;
            if (rCharacter.BOAL_ReadyCharge == "0")
            {   // Условие 1: был выстрел текущим снарядом и борты сейчас не заряжены оба сразу
                float rbcr = "Ship.Cannons.borts.cannonr.ChargeRatio" in rCharacter ? rCharacter.Ship.Cannons.borts.cannonr.ChargeRatio : 1.0; // to_do на $-оператор
                float lbcr = "Ship.Cannons.borts.cannonl.ChargeRatio" in rCharacter ? rCharacter.Ship.Cannons.borts.cannonl.ChargeRatio : 1.0; // to_do на $-оператор
                bOk1 = rbcr < 0.85 || lbcr < 0.85;
            }
            if (!bOk1)
            {   // Условие 2: провалена проверка дистанции до ближайшего врага, при этом прошло целых 20 тиков
                switch(iCurrentBallType)
                {
                    case GOOD_KNIPPELS: bOk2 = fMinEnemyDistance > fRange * 0.8; break;
                    case GOOD_BOMBS:    bOk2 = fMinEnemyDistance > fRange * 0.6; break;
                    case GOOD_GRAPES:   bOk2 = fMinEnemyDistance > fRange * 0.3; break;
                }
            }
            if (bOk1 || bOk2)
            {
                bForcedChange = false;
                iNewBallType = Ship_FindOtherBallType(rCharacter, fMinEnemyDistance, fRange, iTask, rTarget,
                                                      bBalls, bBombs, bGrapes, bKnippels);
            }
        }
        // Если не выбирали заряд от оценки ситуации, то проверим особые случаи
	    if (bForcedChange)
	    {
		    if (bBalls && fMinEnemyDistance > fRange * 0.9) iNewBallType = GOOD_BALLS;
            else if (bKnippels && iTask == AITASK_RUNAWAY) iNewBallType = GOOD_KNIPPELS;
	    }

        if (iNewBallType >= 0 && iNewBallType != iCurrentBallType)
        {
            Ship_ChangeCharge(rCharacter, iNewBallType); // Здесь BOAL_ReadyCharge = 1, ChargeTicks = 0
            // rCharacter.Ship.SeaAI.Init.AttackDistance
        }
    }

	bool bIsCompanion = IsCompanion(rCharacter);

	// check some tasks
	if (iTarget != -1)
	{
		switch (iTask)
		{
			case AITASK_BRANDER:
				float fBranderDistance = 45.0 + (7.0 - float(rShip.Class)) * 15.0;
				fDistance = Ship_GetDistance2D(rCharacter, rTarget);
				if (fBranderDistance > fDistance)
				{
					// Fire ship
					Ship_SetExplosion(rCharacter, rShipObject);
					Log_Info("" + XI_ConvertString(rShip.BaseName) + " '" + rCharacter.Ship.Name + "' " + GetShipSexWord(rShip.BaseName, XI_ConvertString("ShipFight5M"), XI_ConvertString("ShipFight5W")) + XI_ConvertString("ShipFight6"));
					return;
				}
                break;
			case AITASK_ATTACK:
				// ~!~ belamour фикс поведения Маркуса при штурме Картахены
				if (chrId == "Terrax" && "questTemp.Mtraxx.Cartahena.Fort" in pchar)
				{
					if (Ship_GetDistance2D(rCharacter, rTarget) > 1100.0)
						Ship_SetTaskAbordage(SECONDARY_TASK, iChar, iTarget);
				}
                break;
            case AITASK_ABORDAGE:
                // ~!~ belamour фикс поведения Маркуса при штурме Картахены
                if (chrId == "Terrax" && "questTemp.Mtraxx.Cartahena.Fort" in pchar)
                {
                    if (Ship_GetDistance2D(rCharacter, rTarget) < 950.0)
                        Ship_SetTaskAttack(SECONDARY_TASK, iChar, iTarget);
                }
                break;
		}
	}

	// boal AI компа -->
    float HPPercent, SailsPercent, CrewPercent;
	if (chrId == "Tonzag_Hunter_1")
    {
        if ("questTemp.TonzagQuest.Hunter" in pchar)
        {
            HPPercent    = GetHullPercent(rCharacter);
            SailsPercent = GetSailPercent(rCharacter);
            CrewPercent  = GetCrewPercent(rCharacter);
            if (HPPercent < 50.0 || SailsPercent < 50.0 || CrewPercent < 50.0)
            {
                DeleteAttribute(pchar, "questTemp.TonzagQuest.Hunter");
                Tonzag_SpawnBrander();
            }
        }
	}
	else if (chrId == "SantaMisericordia_cap")
	{
        if ("questTemp.SantaMisericordia.AttackFromMap" in pchar)
        {
            HPPercent    = GetHullPercent(rCharacter);
            SailsPercent = GetSailPercent(rCharacter);
            CrewPercent  = GetCrewPercent(rCharacter);
            if ((HPPercent < 90.0 || SailsPercent < 90.0 || CrewPercent < 90.0) && "questTemp.SantaMisericordia.Branders" !in pchar)
                SantaMisericordia_SpawnBranders();

            /* if ((HPPercent < 65.0 || SailsPercent < 65.0 || CrewPercent < 65.0) &&
                   !CheckAttribute(pchar, "questTemp.SantaMisericordia.ChangeWhr"))
            {
                SantaMisericordia_ChangeWhr();
            } */

            if ((HPPercent < 50.0 || SailsPercent < 50.0 || CrewPercent < 50.0) && "questTemp.SantaMisericordia.mines" !in pchar)
                SantaMisericordia_Mines(rCharacter);

            if (CrewPercent < 40.0 && "questTemp.SantaMisericordia.Detonate" !in pchar)
            {
                PostEvent(SHIP_BRANDER_DETONATE, 800, "l", iChar);
                PlaySound("Sea Battles\Vzriv_fort_001.wav");
                Ship_SetTaskNone(SECONDARY_TASK, iChar);
                pchar.questTemp.SantaMisericordia.Detonate = true;
            }

            //Ship_SetTaskBrander(SECONDARY_TASK, iChar, iLastBallChar);
        }
        /* else
        {
            HPPercent    = GetHullPercent(rCharacter);
            SailsPercent = GetSailPercent(rCharacter);
            if ((HPPercent < 99.0 || SailsPercent < 99.0 || CrewPercent < 99.0) &&
                !CheckAttribute(pchar, "questTemp.SantaMisericordia.SpainReputation"))
            {
                SantaMisericordia_SpainReputation();
            }
        }*/
	}
	
	fDistance = Ship_GetDistance2D(pchar, rCharacter);

	if (seaAlarmed && "SystemInfo.Tutorial.FirstSeaBattle_SandBox" in pchar)
	{
		DoQuestFunctionDelay("Rum_NewGameTip0", 5.0);
		DeleteAttribute(pchar, "systeminfo.tutorial.firstSeaBattle_SandBox");
	}
	
	//fix 171204 boal Не нужно наших с толку сбивать
	if (bIsCompanion)
		return;
    
	string sGroupID = Ship_GetGroupID(rCharacter);
	if (iTarget != -1)
	{
		if (iNewBallType < 0 || iShipCannonsNum < float(rShip.CannonsQuantity) * 0.1)
		{
			// ~!~ Maybe we can abordage???
			Ship_SetTaskRunaway(SECONDARY_TASK, iChar, iTarget);
			return;
		}
	}
	if (GetNationRelation2MainCharacter(sti(rCharacter.nation)) == RELATION_ENEMY) // Враг ГГ
	{
		if ("AlwaysFriend" in rCharacter)
			SetCharacterRelationBoth(iChar, nMainCharacterIndex, RELATION_FRIEND);
		else
		{
			//--> eddy. анализим форт. проверяем наличие форта, враждебность и залоченный таск
			if ("WatchFort" in rCharacter && bIsFortAtIsland &&
				GetRelation(iChar, iFortCommander) == RELATION_ENEMY && "ShipTaskLock" !in rCharacter)
			{
				if (int(rCharacter.Tmp.fWatchFort) >= int(rCharacter.Tmp.fWatchFort.Qty))
				{
					rCharacter.Tmp.fWatchFort = 0; //сброс счетчика оптимизации
					//проверяем расстояние до форта и наличие флага 'следить за фортом'
					if (GetDistance2D(float(rCharacter.Ship.Pos.x), float(rCharacter.Ship.Pos.z), fFort_x, fFort_z) < 1000.0)
					{
						Ship_SetTaskRunaway(SECONDARY_TASK, iChar, iFortCommander);
						rCharacter.Tmp.fWatchFort.Qty = 200; //не лочим таск, но увеличиваем паузу срабатывания
						//Log_SetStringToLog("Я ("+rCharacter.id+") ухожу от форта."); 
					}
				}
				else
					rCharacter.Tmp.fWatchFort = int(rCharacter.Tmp.fWatchFort) + 1;
			}
			//<-- анализим форт
			if ("SinkTenPercent" !in rCharacter) // это не ЧЖ и не идущие на абордаж пираты
			{
				HPPercent    = GetHullPercent(rCharacter);
				SailsPercent = GetSailPercent(rCharacter);
				int   CrewQuantity    = rCharacter.Ship.Crew.Quantity;
				int   MinCrewQuantity = GetMinCrewQuantity(rCharacter);
				int   iCharactersNum1, iCharactersNum2;
				float fCharactersRatio;
				bool bAnalyze = "AnalizeShips" in rCharacter;
				bool bAdvantage;
				if (GetRelation(iChar, nMainCharacterIndex) != RELATION_ENEMY)
				{
					SetCharacterRelationBoth(iChar, nMainCharacterIndex, RELATION_ENEMY);
					Group_SetTaskAttack(sGroupID, PLAYER_GROUP);
					UpdateRelations();
					DoQuestCheckDelay("NationUpdate", 0.9);
				}
				if (iLastBallChar != -1 && "Ship_SetTaskAbordage" !in rCharacter && "ShipTaskLock" !in rCharacter) // нет приказа на абордаж
				{
					bAdvantage = float(rCharacter.ship.hp) > float(rLastBallCharacter.ship.hp) * 0.35;
					if (iTask == AITASK_NONE)
					{
						//кэп без таска, такое маловероятно. но тем не менее...
						if (bAnalyze)
						{
							//проверим, стоит ли атаковать
							if (bAdvantage)
								Ship_SetTaskAttack(SECONDARY_TASK, iChar, iLastBallChar);
							else
								Ship_SetTaskRunaway(SECONDARY_TASK, iChar, iLastBallChar);							
						}
						else	//кэп без атрибута проверки кораблей - всегда в атаке
							Ship_SetTaskAttack(SECONDARY_TASK, iChar, iLastBallChar);
					}
					else if (SailsPercent > 50.0 && HPPercent > 30.0 && iTask != AITASK_RUNAWAY) // не убегает уже
					{
						//корабль в хорошем состоянии, таск не ранэвей. здесь тоже проверим при наличии атрибута анализа кораблей
						if (bAnalyze)
						{
							// Warship fix Должно быть здесь
							iCharactersNum1 =  Group_GetLiveCharactersNum(rCharacter.SeaAI.Group.Name);
							iCharactersNum2 =  Group_GetLiveCharactersNum(rLastBallCharacter.SeaAI.Group.Name);
							fCharactersRatio =  iCharactersNum2 > 0 ? float(iCharactersNum1) / iCharactersNum2 : 0.0;
							if (bAdvantage)
							{
								// Если есть шанс победить, то проверяем ещё и количественное соотношение групп. не лезть на крупные эскадры
								if (fCharactersRatio >= 0.5 || int(rShip.Class) <= int(RealShips[int(rLastBallCharacter.ship.type)].Class))
									Ship_SetTaskAttack(SECONDARY_TASK, iChar, iLastBallChar);
								else
									Ship_SetTaskRunaway(SECONDARY_TASK, iChar, iLastBallChar);
							}
							else
							{
								if (fCharactersRatio >= 2.0)
									Ship_SetTaskAttack(SECONDARY_TASK, iChar, iLastBallChar);
								else
									Ship_SetTaskRunaway(SECONDARY_TASK, iChar, iLastBallChar);
							}
						}
						else	// Кэп без атрибута проверки кораблей - всегда в атаке
							Ship_SetTaskAttack(SECONDARY_TASK, iChar, iLastBallChar);
					}
					else if (HPPercent < 15.0)	// смертники!!!
					{
						if (iTask != AITASK_BRANDER && rand(20) == 1) // Очень часто плохо - убивает все вокруг
							Ship_SetTaskBrander(SECONDARY_TASK, iChar, iLastBallChar);
						else if (iTask == AITASK_ATTACK)
							Ship_SetTaskRunaway(SECONDARY_TASK, iChar, iLastBallChar);
					}
					else if (HPPercent < 25.0 || CrewQuantity <= int(1.5 * MinCrewQuantity))
						Ship_SetTaskRunaway(SECONDARY_TASK, iChar, iLastBallChar);
					else if (bAnalyze && bAdvantage)	//eddy. здесь смотрим Runaway. проверяем атрибут анализа шипов и анализим, стоит ли атаковать
					{
						//может только что ушел от форта? 
						if (int(rCharacter.Tmp.fWatchFort.Qty) == 200)
						{
							//тогда Runaway меняем за один такт до проверки форта
							if (int(rCharacter.Tmp.fWatchFort) >= 199)
							{
								if (iLastBallChar == iFortCommander)	//только не на форткоммандера, камикадзе не делаем
									Ship_SetTaskAttack(SECONDARY_TASK, iChar, nMainCharacterIndex);
								else
									Ship_SetTaskAttack(SECONDARY_TASK, iChar, iLastBallChar);
							}
						}	//форт тут ни при чем
						else if (iLastBallChar == iFortCommander)	//только не на форткоммандера, камикадзе не делаем
							Ship_SetTaskAttack(SECONDARY_TASK, iChar, nMainCharacterIndex);
						else
						{
							iCharactersNum1 = Group_GetLiveCharactersNum(rCharacter.SeaAI.Group.Name);
							iCharactersNum2 = Group_GetLiveCharactersNum(rLastBallCharacter.SeaAI.Group.Name);
							fCharactersRatio =  iCharactersNum2 > 0 ? float(iCharactersNum1) / iCharactersNum2 : 0.0;
							if (fCharactersRatio >= 0.5 || int(rShip.Class) <= int(RealShips[int(rLastBallCharacter.Ship.Type)].Class))
								Ship_SetTaskAttack(SECONDARY_TASK, iChar, iLastBallChar);
							else
								Ship_SetTaskRunaway(SECONDARY_TASK, iChar, iLastBallChar);
						}
					}
				}
				else if ("ShipTaskLock" !in rCharacter && iTarget == -1)	// если плывет мимо и нет rCharacter.Ship.LastBallCharacter (никто по нему не стрелял)
				{
					bAdvantage = float(rCharacter.ship.hp) > float(pchar.ship.hp) * 0.35;
					if (iTask == AITASK_RUNAWAY)
					{	//eddy. а то ранэвей у нас как залоченный таск
						if (bAnalyze && HPPercent > 30.0 && SailsPercent > 70.0 && bAdvantage)
							Ship_SetTaskAttack(SECONDARY_TASK, iChar, nMainCharacterIndex);
					}
					else
					{
						//праздношатающийся кэп, проверяем атрибут анализа шипов. если атрибут есть и противник крут - валим.
						if (bAnalyze && !bAdvantage)
						{
							iCharactersNum1 =  Group_GetLiveCharactersNum(rCharacter.SeaAI.Group.Name);
							iCharactersNum2 =  Group_GetLiveCharactersNum(pchar.SeaAI.Group.Name);	
							fCharactersRatio = iCharactersNum2 > 0 ? float(iCharactersNum1) / iCharactersNum2 : 0.0;
							if (fCharactersRatio >= 2.0)
								Ship_SetTaskAttack(SECONDARY_TASK, iChar, nMainCharacterIndex);
							else
								Ship_SetTaskRunaway(SECONDARY_TASK, iChar, nMainCharacterIndex);
						}
						else	// если есть шанс победить - атакуем
							Ship_SetTaskAttack(SECONDARY_TASK, iChar, nMainCharacterIndex);
					}
				}
			}
			else
			{
				// --> Калеуче
				if (FindSubStr(chrId, "Caleuche", 0) != -1)
				{
					if (chrId == "Caleuche_seacap") // у Доминики
					{
						if (fDistance < 500.0)
							Ship_SetTaskAbordage(SECONDARY_TASK, iChar, nMainCharacterIndex);
						if (fDistance < 150.0)
							Caleuche_GhostshipBoarding(); // активизация квестового абордажа
					}
					else if (chrId == "Map_Caleuche") // на карте
					{
						if (fDistance < 900.0)
						{
							Ship_SetTaskAbordage(SECONDARY_TASK, iChar, nMainCharacterIndex);
							pchar.quest.Caleuche_map_clear.win_condition.l1 = "MapEnter";
							pchar.quest.Caleuche_map_clear.function = "Caleuche_ClearFromMap";
							rCharacter.lifeday = 0;
							Map_ReleaseQuestEncounter("Map_Caleuche");
						}
						if (fDistance < 150.0)
							Caleuche_MapGhostshipBoarding(); // активизация квестового абордажа
					}
				}
				else if ("PearlTartane" in rCharacter && int(rCharacter.PearlTartane))
				{
					if (fDistance < 16.0 * Get_AISeaGoods_AbordageSkillMultiplier(pchar))
					{
						PlaySound("interface\important_item.wav");
						int SmallPearlQty, BigPearlQty;
						if ("JewelryGulf" in rCharacter) // Addon 2016-1 Jason пиратская линейка
						{
							SmallPearlQty = rand(25) + 20;
							BigPearlQty = rand(20) + 15;
							TakeNItems(pchar, "jewelry8", SmallPearlQty);
							TakeNItems(pchar, "jewelry7", BigPearlQty);
							Log_SetStringToLog(XI_ConvertString("PearlTartane11") + rCharacter.ship.name + XI_ConvertString("PearlTartane12") + SmallPearlQty + XI_ConvertString("PearlTartane13") + BigPearlQty + XI_ConvertString("PearlTartane14"));
							pchar.questTemp.Mtraxx.JewQty = int(pchar.questTemp.Mtraxx.JewQty) + BigPearlQty;
							pchar.questTemp.Mtraxx_SobralVsyo = int(pchar.questTemp.Mtraxx_SobralVsyo) + 1;
							DoQuestFunctionDelay("Mtraxx_PearlQuantityHint", 0.1);
							if (int(pchar.questTemp.Mtraxx_SobralVsyo) == 5)
							{
								int i = pchar.questTemp.Mtraxx.JewQty;
								AddQuestRecord("Roger_1", "16");
								AddQuestUserData("Roger_1", "sQty", FindRussianQtyString(i));
								QuestSetCurrentNode("Terrax", "mtraxx_7");
								pchar.questTemp.Mtraxx = "jewelry_11";
								AddLandQuestMark(characterFromId("Terrax"), "questmarkmain");
								AddMapQuestMarkCity("LaVega", false);
								DeleteAttribute(pchar, "Cheats.SeaTeleport");
							}
						}
						else
						{
							SmallPearlQty = rand(250) + 100;
							BigPearlQty = rand(150) + 50;
							TakeNItems(pchar, "jewelry53", SmallPearlQty);
							TakeNItems(pchar, "jewelry52", BigPearlQty);
							Log_SetStringToLog(XI_ConvertString("PearlTartane21") + rCharacter.ship.name + XI_ConvertString("PearlTartane22") + SmallPearlQty + XI_ConvertString("PearlTartane23") + BigPearlQty + XI_ConvertString("PearlTartane24"));
						}
						rCharacter.PearlTartane = false; //уже ограбили
						pchar.questTemp.GrabbingTartane = "success"; //флаг успешное нападение
					}
					if (fDistance < 60.0 && "JewelryGulf" in rCharacter && "questTemp.Mtraxx_PearlHelpHint" !in pchar)
					{
						pchar.questTemp.Mtraxx_PearlHelpHint = true;
						DoQuestFunctionDelay("Mtraxx_PearlHelpHint", 0.5);
					}
				}
				else
				{
					if ("PearlTartane" !in rCharacter)
						Ship_SetTaskAttack(SECONDARY_TASK, iChar, nMainCharacterIndex);
					// Addon-2016-1 Jason, пиратская линейка
					if (chrId == "Losada_Seacap_1")
					{
						if (fDistance > 3000.0 && "questTemp.Mtraxx.LosadaEscape" in pchar)
							Mtraxx_IgnasioOpenMap();		
					}
				}
			}
		}
	}
	else	// не враги
	{
		// далее насильственное установление враждебности для определённых НПС
		// boal 030804 узнал на днях, что можно это все делать оин раз и оно ПОМНИТ!!!  но тогда нужно ИД проверять, тк перекрываем выше
		if ("AlwaysEnemy" in rCharacter)
		{
			SetCharacterRelationBoth(iChar, nMainCharacterIndex, RELATION_ENEMY);
			Ship_SetTaskAttack(SECONDARY_TASK, iChar, nMainCharacterIndex);
		}
		else if ("AlwaysFriend" in rCharacter)
			SetCharacterRelationBoth(iChar, nMainCharacterIndex, RELATION_FRIEND);
		else if (int(rCharacter.nation) != PIRATE || bBettaTestMode)	//boal 030804 нужно чтоб при тесте флаг с пиратами мирил
		{
			// фикс отношений
			SetCharacterRelationBoth(iChar, nMainCharacterIndex, GetNationRelation2MainCharacter(int(rCharacter.nation)));
			// проверка на ложный флаг -->
			if ("CheckFlagYet" !in rCharacter)
			{
				if ("CheckFlagDate" !in rCharacter || GetNpcQuestPastDayParam(rCharacter, "CheckFlagDate") > 1)
				{
					if (fDistance < MIN_ENEMY_DISTANCE_TO_DISABLE_MAP_ENTER)
					{
						rCharacter.CheckFlagYet = true; // все, проверил
						Ship_CheckFlagEnemy(rCharacter);
						SaveCurrentNpcQuestDateParam(rCharacter, "CheckFlagDate");
					}
				}
			}
			// проверка на ложный флаг <--
			// Jason: корабли проверяют расстояние
			// --> Таможенный патруль
			if (chrId == "ContraCureerCap")
			{
				if (fDistance < 150.0)
				{
					SetCharacterRelationBoth(iChar, nMainCharacterIndex, RELATION_ENEMY);
					SetCharacterRelationBoth(GetCharacterIndex("ContraContraCap"), nMainCharacterIndex, RELATION_ENEMY);
					Group_SetTaskAttack(sGroupID, PLAYER_GROUP);
					Group_LockTask(sGroupID);
					rCharacter.nation = PIRATE;
					ref rContraCap = CharacterFromId("ContraContraCap");	
					rContraCap.nation = PIRATE;
					Ship_FlagRefresh(rCharacter);
					Ship_FlagRefresh(rContraCap);
					UpdateRelations();
					RefreshBattleInterface();
				}
			}
			// --> Полакр Марлин
			else if (chrId == "Cap_Marlin")
			{
				if (fDistance < 200.0)
				{
					SetCharacterRelationBoth(iChar, nMainCharacterIndex, RELATION_ENEMY);
					Group_SetTaskAttack(sGroupID, PLAYER_GROUP);
					Group_LockTask(sGroupID);
					UpdateRelations();
					RefreshBattleInterface();
				}
			}
			// --> фрегат Беспощадный
			else if (chrId == "Saga_vampire")
			{
				if (fDistance < 200.0)
					Saga_CheckVensanEnemyes(); // пытается распознать
				if (fDistance < 25.0 && "questTemp.Saga.BarbTemptation.Bomb" in pchar)
					Saga_HitSeaBomb();
			}
			// --> Джекман, Центурион
			else if (chrId == "Jackman")
			{
				if (fDistance < 200.0)
					Saga_CheckJackmanFrigate(); // пытается распознать
				if (fDistance < 25.0 && "questTemp.Saga.BarbTemptation.Fugas" in pchar)
					Saga_HitSeaFugas();
			}
			// --> Моллиган, Устрица
			else if (chrId == "Molligan")
			{
				if (fDistance < 500.0 && "questTemp.Saga.Molligan.enemy" in pchar)
					Saga_MolliganAttack(); // атакует                             
			}
			// --> Бейкер, лодка
			else if (chrId == "Baker_Cap")
			{
				if (fDistance < 20.0 && "questTemp.Saga.Shadows.Baker" in pchar)
					Saga_BakerToCabin(); // принимаем на борт		
			}
			// --> люггер Диего 030712
			else if (chrId == "GOT_camicadze")
			{
				if (fDistance < 200.0)
					GuardOT_CamicadzeBoom(); // атакует		
			}
			// --> // Addon-2016 Jason, французские миниквесты (ФМК) Мартиника
			else if (chrId == "FMQM_Tartane_Cap")
			{
				if (fDistance < 500.0 && "quest.seaattack" !in rCharacter)
					FMQM_TartanaAlarm();                             
			}
			else if (chrId == "Rum_Cap")
			{
				if (fDistance < 3900.0 && "questTemp.Sharlie.Rum.TipT" in pchar)
				{
					DeleteAttribute(pchar, "questTemp.Sharlie.Rum.TipT");
					//NewGameTip(XI_ConvertString("RumCap"));
					LaunchTutorial("SeaTimeScaleUp", 1);
				}
				if (fDistance < 4000.0 - MOD_SKILL_ENEMY_RATE * 100 && "questTemp.Sharlie.Rum.Tip0" in pchar)
				{
					DeleteAttribute(pchar, "questTemp.Sharlie.Rum.Tip0");
					//NewGameTip(XI_ConvertString("RumCap"));
					// ~!~ TO_DO
					if (LanguageGetLanguage() == "Russian") LaunchMessage("Вы на верном пути! Почти у цели!");
					else LaunchMessage("You are on the right course! Almost there!");
				}
				if (fDistance < 3500.0 - MOD_SKILL_ENEMY_RATE * 100 && "questTemp.Sharlie.Rum.Tip1" in pchar)
				{
					DeleteAttribute(pchar, "questTemp.Sharlie.Rum.Tip1");
					//NewGameTip(XI_ConvertString("RumCap"));
					LaunchTutorial("SeaFastTravel", 1);
				}
			}
			else if (chrId == "TK_Genrih") 
			{
				if (fDistance < 150.0 && "questTemp.TK_Otpustil" in pchar) 
				{
					DeleteAttribute(pchar, "questTemp.TK_Otpustil");
					NewGameTip(XI_ConvertString("TKGenrihCap"));
					rCharacter.nation = PIRATE;
				}
			}
			if ("SystemInfo.Tutorial.FirstSea_SandBox" in pchar)
			{
				DoQuestFunctionDelay("Rum_NewGameTip2", 0.5);
				DeleteAttribute(pchar, "SystemInfo.Tutorial.FirstSea_SandBox");
			}
		}
		else
			SetCharacterRelationBoth(iChar, nMainCharacterIndex, RELATION_ENEMY); // На море пираты нападают всегда
		// fix на нападение при условии, что нация дружеская, а с НПС мы всё равно враждуем <--

		if (GetRelation(nMainCharacterIndex, iChar) == RELATION_ENEMY)
		{
			Group_SetTaskAttack(sGroupID, PLAYER_GROUP);
			UpdateRelations(); // перенес от ниже, тк исходим из того, что изначально все друзья всё равно
		}
		//UpdateRelations();  // to_do это тонкое место, это тормоз, но рефрешить нужно
	}

	if (chrId == "PueblaCap")
	{
		if ("questTemp.Trial.Tip" in pchar)
		{
			DeleteAttribute(pchar, "questTemp.Trial.Tip");
			NewGameTip(XI_ConvertString("PueblaCap"));
			if ("systeminfo.tutorial.BoardingTactics" in pchar)
			{
				DoQuestFunctionDelay("Tutorial_BoardingTactics", 2.5);
				DeleteAttribute(pchar, "systeminfo.tutorial.BoardingTactics");
			}
		}
	}
	else if (chrId == "TK_Heiter")
	{
		if (fDistance < 1000.0 && "systeminfo.tutorial.BoardingTactics" in pchar)
		{
			DoQuestFunctionDelay("Tutorial_BoardingTactics", 2.5);
			DeleteAttribute(pchar, "systeminfo.tutorial.BoardingTactics");
		}
	}
}

// проверка флага НПС у ГГ, мож он пират?
void Ship_CheckFlagEnemy(ref rCharacter)
{
	ref     mChar = GetMainCharacter();
	int     iCompan, iClass;
	float   fSneak;
	float   fPerkInfl = 1.0;
	int     i, cn;
	ref     chref;
	bool    bViewFlag = false;
	int     iNationToChange = sti(mChar.nation);  // было
	if (sti(rCharacter.nation) == PIRATE) return;
    iCompan = GetCompanionQuantity(mChar);
    iClass  = 7;
	// поиск мин.  те старшего класса
	for (i=0; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(GetMainCharacter(), i);
		if (cn>=0)
		{
			chref = GetCharacter(cn);
            if (GetCharacterShipClass(chref) < iClass) iClass = GetCharacterShipClass(chref);
		}
	}
    if (GetNationRelation(GetBaseHeroNation(), sti(rCharacter.nation)) == RELATION_ENEMY && GetDaysContinueNationLicence(HOLLAND) == -1) // проверка грамот
    {
        // to_do ch.CheckLicence    = true; // Проверять наличие торговой лицензии при распознании,нужно фортам и сторожевикам
		iNationToChange = GetBaseHeroNation();
        bViewFlag       = true;
    }
    if (!bViewFlag)
    {
        if (ChangeCharacterHunterScore(mChar, NationShortName(sti(rCharacter.nation)) + "hunter", 0) > (8 + rand( (iClass-1)*(6-iCompan) ) ))
        {
            bViewFlag       = true;
            iNationToChange = PIRATE;
        }
    }

		STH_CheckShip(rCharacter);
  //   if (bViewFlag)
  //   {  // смотрим флаг у ГГ и узнаем в нём...
	// 	if(CheckAttribute(pchar, "questTemp.Guardoftruth") && CheckCharacterItem(pchar, "VerifyPaper") && pchar.location == "cuba1") return; // грамота отца Винсенто
	// 	if(CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && CheckCharacterItem(pchar, "VerifyPaper") && pchar.location == "Trinidad") return; // грамота отца Винсенто

	// 	fSneak  = stf(mChar.TmpSkill.Sneak); // 0.01..1.0
	// 	int rep = sti(abs(REPUTATION_NEUTRAL - sti(mChar.reputation.nobility)) * 0.75);
	// 	if(CheckCharacterPerk(mChar, "HT2")) fPerkInfl = 2.0;
	// 	if ((rand(100) + rand(20) + rand(rep)) > (fPerkInfl*fSneak * 12 * (iClass + iClass/4) * (6-iCompan) * GetBonusDeceptionChance(mChar)) * GetFloatByCondition(HasShipTrait(mChar, "trait05"), 1.0, 1.15))
	// 	{
			/*mChar.nation = iNationToChange;  // to_do ролик флага сделать
			Ship_FlagRefresh(PChar); //флаг на лету
	        SetNationToOfficers(iNationToChange);
	        SetNationRelation2MainCharacter(sti(rCharacter.nation), RELATION_ENEMY);
	        */
			// pchar.MoorName = " ";	// LDH 12Feb17 - don't display MoorName in battle
      //       //Log_Info(XI_ConvertString("FriendFail1")+ NationNamePeople(sti(rCharacter.nation)) + XI_ConvertString("FriendFail2"));
      //       notification(XI_ConvertString("FriendFailNotif"), "SneakFail");
			// SetCharacterRelationBoth(sti(rCharacter.index), nMainCharacterIndex, RELATION_ENEMY);
			// DoQuestCheckDelay(NationShortName(iNationToChange) + "_flag_rise", 0.1); // применение нац отношений флага
			// if (sti(pchar.questTemp.stels.sea) != GetDataDay())
			// {
			// 	AddCharacterExpToSkill(mChar, SKILL_SNEAK, 50);
			// 	pchar.questTemp.stels.sea = GetDataDay();
			// }
	// 	}
	// 	else
	// 	{ // не узнал
	// 		notification(XI_ConvertString("FriendsuccessNotif"), "Sneak");
	// 		if (sti(pchar.questTemp.stels.sea) != GetDataDay())
	// 		{
	// 			AddCharacterExpToSkill(mChar, SKILL_SNEAK, (iCompan * 200 / iClass));
	// 			ChangeCrewExp(mChar, "Sailors", 0.5);
	// 			pchar.questTemp.stels.sea = GetDataDay();
	// 		}
	// 	}
	// }
	if (!bBettaTestMode || !SandBoxMode)
	{
		if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_MIRAGE && sti(rCharacter.nation) == ENGLAND && CheckAttribute(pchar, "questTemp.HWIC.Holl"))//Мираж для англичан враг
		{
			Log_Info(XI_ConvertString("FriendFailMirage"));
			SetNationRelation2MainCharacter(ENGLAND, RELATION_ENEMY);
			LAi_group_ClearAllTargets();
			DoQuestCheckDelay("NationUpdate", 3.0);
			UpdateRelations();
			RefreshBattleInterface();
		}
		if (LineShips_CheckAndIdentify(sti(rCharacter.nation))) // если пришёл на линейнике этой нации
		{
			Log_Info(XI_ConvertString("FriendFailBattleShip1")+ NationNamePeople(sti(rCharacter.nation)) + XI_ConvertString("FriendFailBattleShip2"));
			SetNationRelation2MainCharacter(sti(rCharacter.nation), RELATION_ENEMY);
			LAi_group_ClearAllTargets();
			DoQuestCheckDelay("NationUpdate", 3.0);
			UpdateRelations();
			RefreshBattleInterface();
			ChangeCharacterNationReputation(pchar, sti(rCharacter.nation), -3);
		}
		if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_AMSTERDAM && sti(rCharacter.nation) == HOLLAND && CheckAttribute(pchar, "questTemp.ClockTower_AmsterdamCheck"))
		{
			SetNationRelation2MainCharacter(HOLLAND, RELATION_ENEMY);
			LAi_group_ClearAllTargets();
			DoQuestCheckDelay("NationUpdate", 3.0);
			UpdateRelations();
			RefreshBattleInterface();
		}
	}
}

void Ship_ActivateFirePlace()
{
	aref	arShipObject = GetEventData();
	aref	arCharacter = GetEventData();
	int		iFirePlaceIndex = GetEventData();
	string	sSoundName = GetEventData();
	float	fFireTime = GetEventData();
	int		iBallCharacterIndex = GetEventData();

	if (!bAbordageStarted) // fix
	{
		if(rand(5) < 4)
            SendMessage(arShipObject, "llsssfl", MSG_SHIP_ACTIVATE_FIRE_PLACE, iFirePlaceIndex, "ship_smoke", "ship_fire", sSoundName, fFireTime, iBallCharacterIndex);
		else
            SendMessage(arShipObject, "llsssfl", MSG_SHIP_ACTIVATE_FIRE_PLACE, iFirePlaceIndex, "sea_smoke", "ship_fire", sSoundName, fFireTime, iBallCharacterIndex);
	}
}

void Ship_BranderDetonate()
{
	ref		rCharacter = GetCharacter(GetEventData());

	ref		rBranderBaseShip = GetRealShip(sti(rCharacter.Ship.Type));
 	float	fBranderDistance = 1.9 * (45.0 + (6.0 - stf(rBranderBaseShip.Class)) * 15.0); //fix
	float   fMaxDamage = 1000.0 + MakeFloat(GetCargoGoods(rCharacter, GOOD_POWDER)) * 4;

	aref	arShipObjects[64];
	int		iBranderNumShips = 1;
	
	if(CheckAttribute(rCharacter,"Situation") && rCharacter.situation == "Explosion" ) // ситуация со взрывом
	{
		fMaxDamage = 1000.0 + MakeFloat(GetCargoGoods(rCharacter, GOOD_POWDER)) * 3;
		if(GetCargoGoods(rCharacter, GOOD_POWDER) < 300) { fMaxDamage += 400.0; }	
		ref mc = GetMainCharacter();
		int iDiffClass = sti(RealShips[sti(mc.Ship.Type)].Class) - sti(RealShips[sti(rCharacter.Ship.Type)].Class);
		if(iDiffClass > 0) fMaxDamage += iDiffClass * 500.0;
		fMaxDamage = fMaxDamage / 20.0 * MOD_SKILL_ENEMY_RATE;		
	}	
	if (!FindEntity(&arShipObjects[0], "ship")) { return; }// can't be
	while (FindEntityNext(&arShipObjects[iBranderNumShips])) { iBranderNumShips++; }
	
	// enumerate ship and do damage
	for (int i=0; i<iBranderNumShips; i++)
	{
		int iCharacterIndex = -1;
		SendMessage(arShipObjects[i], "le", MSG_SHIP_GET_CHARACTER_INDEX, &iCharacterIndex);
		if (iCharacterIndex == sti(rCharacter.index)) { continue; }
		ref rOtherCharacter = GetCharacter(iCharacterIndex);
		ref	rOtherBaseShip = GetRealShip(sti(rOtherCharacter.Ship.Type));
		float fDistance = Ship_GetDistance2D(rCharacter, rOtherCharacter);
		if (fDistance > fBranderDistance) { continue; }
		float fDamageMultiply = Bring2Range(1.0, 0.0, 10.0, fBranderDistance, fDistance);
		Ship_ApplyHullHitpoints(rOtherCharacter, fMaxDamage * fDamageMultiply, KILL_BY_SPY, sti(rCharacter.index));
		// fire random fire places
		//int iNumFirePlaces = 0;
		//SendMessage(&arShipObjects[i], "le", MSG_SHIP_GET_NUM_FIRE_PLACES, &iNumFirePlaces);

		// add move impulse to ship
		float x = stf(rOtherCharacter.Ship.Pos.x) - stf(rCharacter.Ship.Pos.x);
		float z = stf(rOtherCharacter.Ship.Pos.z) - stf(rCharacter.Ship.Pos.z);
		float fLen = stf(rOtherBaseShip.Class) * fDamageMultiply * (1.0 / sqrt(x * x + z * z));
		SendMessage(&arShipObjects[i], "llffffff", MSG_SHIP_ADD_MOVE_IMPULSE, false, x * fLen, 0.0, z * fLen, 0.0, 0.0, 0.0);
	}
	Ship_Detonate(rCharacter, true, true);
}

float Ship_GetDistance2D(ref rCharacter1, ref rCharacter2)
{
	if (CheckAttribute(rCharacter1, "Ship.Pos.x") && CheckAttribute(rCharacter2, "Ship.Pos.x")) // fix boal
	{
		return GetDistance2D(stf(rCharacter1.Ship.Pos.x), stf(rCharacter1.Ship.Pos.z), stf(rCharacter2.Ship.Pos.x), stf(rCharacter2.Ship.Pos.z));
	}   
	else
	{
		return 1000.0;
	}
}

int Ship_FindOtherBallType(ref rCharacter, float fMinEnemyDistance, float fRange, int iTask, ref rTarget,
                           bool bBalls, bool bBombs, bool bGrapes, bool bKnippels)
{
    // ~!~ TO_DO: fMinEnemyDistance это дистанция до ближайшего врага, который не обязательно таргет
	if (rTarget != nullptr)
	{
		ref rBaseShip = GetRealShip(GetCharacterShipType(rCharacter));
        float fRangeModifier = 1.0;
		int iType = -1;

		if (bBalls)
		{
			iType = GOOD_BALLS;
		}

		if (fMinEnemyDistance <= fRange * 0.8 && bKnippels) 
		{
            fRangeModifier = 0.8;
            if (iTask == AITASK_RUNAWAY)
            {
                rCharacter.Ship.SeaAI.Init.AttackDistance = fRange * fRangeModifier / (1.4 + frandSmall(3.0));
                return GOOD_KNIPPELS;
			}
            if (int(rTarget.ship.sp) > 30 && Ship_GetSailState(rTarget) >= 0.5)
			{
				iType = GOOD_KNIPPELS;
			}
		}

		if (fMinEnemyDistance <= fRange * 0.5 && bBombs)
		{
            fRangeModifier = 0.6;
			iType = GOOD_BOMBS;
		}

		if (fMinEnemyDistance <= fRange * 0.2 && bGrapes)
		{
            fRangeModifier = 0.3;
			if (int(rTarget.ship.crew.quantity) > int(rBaseShip.MinCrew))
			{
				iType = GOOD_GRAPES;  
			}
		}

		rCharacter.Ship.SeaAI.Init.AttackDistance = fRange * fRangeModifier / (1.4 + frandSmall(3.0));
		return iType;
	}

	if (bBalls) return GOOD_BALLS;
	if (bBombs) return GOOD_BOMBS;
	if (bKnippels) return GOOD_KNIPPELS;
	if (bGrapes) return GOOD_GRAPES;

	return -1;
}

// event: indicate that ball is not enough for fire for main character
void Ship_NotEnoughBalls()
{
	bNotEnoughBalls = GetEventData();
	// boal -->
	if (!bNotEnoughBalls)
	{
	    if (GetCargoGoods(pchar, GOOD_POWDER) < 1)
	    {
	        bNotEnoughBalls = true;
	    }
	}
	// boal <--

}

int Ship_GetCurrentBallsNum()
{
	aref aCharacter = GetEventData();
	return GetCargoGoods(aCharacter,sti(aCharacter.Ship.Cannons.Charge.Type));
}

void Ship_SailDamage()
{
	float x, y, z;
	int iCharacterIndex 	= GetEventData();
	x = GetEventData();
	y = GetEventData();
	z = GetEventData();
	int	iBallCharacterIndex = GetEventData();

	ref	rBallCharacter 	= GetCharacter(iBallCharacterIndex);	// кто пуляет
	ref	rOurCharacter 	= GetCharacter(iCharacterIndex);   		// по кому
	
	if (LAi_IsImmortal(rOurCharacter)) return;
	
//	Log_Info(" Ship_SailDamage : rOurCharacter.id = " + rOurCharacter.id + " rBallCharacter.id = " + rBallCharacter.id);
	
	rOurCharacter.Ship.LastBallCharacter = iBallCharacterIndex;
	
	string sSound;
	int	iBallType = sti(AIBalls.CurrentBallType);
	switch (iBallType)
	{
		case GOOD_BALLS:	sSound = "ShipEMB/SailDamage_ball";    break;
		case GOOD_GRAPES:	sSound = "ShipEMB/SailDamage_grapes";  break;
		case GOOD_KNIPPELS:	sSound = "ShipEMB/SailDamage_knippel"; break;
		case GOOD_BOMBS:	sSound = "ShipEMB/SailDamage_bomb";    break;
	}
	//log_testinfo("From bort " + AIBalls.FromBort);
	Play3DSoundEvent(sSound, x, y, z);
	if (rand(100) < 15) Play3DSound("fly_ball_misc", x, y, z);

	bool isOurCompanion = IsCompanion(rOurCharacter);

	if (sti(rOurCharacter.Ship.LastBallCharacter) == nMainCharacterIndex &&
        GetNationRelation2MainCharacter(sti(rOurCharacter.nation)) != RELATION_ENEMY)
    {	
        if (!IsCompanion(rOurCharacter) && !CheckAttribute(rOurCharacter, "Coastal_Captain")) // по своим можно палить таможня пофиг
        {
            Ship_NationAgressive(rOurCharacter, rOurCharacter);
            DoQuestCheckDelay("NationUpdate", 0.7);
        }	
    }
	if(HasShipTrait(rBallCharacter, "trait24") && rand(2) == 1)
	{
		if(AIBalls.FromBort == "cannonb" || AIBalls.FromBort == "cannonf") // с порно, тк это не ядра, того кто стрелял, а скорее ядра ГГ
		{
			int iRandStartTime = rand(1000);
			float fTotalDotTime = 15.0;
			PostEvent("event_sail_dot", iRandStartTime, "llf", iCharacterIndex, iBallCharacterIndex, fTotalDotTime);
		}
	}
}

void Ship_Ship2IslandCollision()
{
	float	fPower, fSlide, x, y, z;
	int		iOurCharacterIndex, iEnemyCharacterIndex, iTouchPoint;

	iOurCharacterIndex = GetEventData();
	iEnemyCharacterIndex = GetEventData();
	fPower = abs(GetEventData());
	fSlide = abs(GetEventData());
	iTouchPoint = GetEventData();
	x = GetEventData();
	y = GetEventData();
	z = GetEventData();

	ref rOurCharacter = GetCharacter(iOurCharacterIndex);

    if (!CheckAttribute(rOurCharacter, "AlwaysSandbankManeuver"))  //boal
    {
		float fHP = (1.0 - fSlide) * fPower * 3.0;
		Ship_ApplyHullHitpoints(rOurCharacter, fHP, KILL_BY_ISLAND, -1);

		if (fPower > 1.0) { Play3DSound("coll_ship2rock", x, y, z); }
	}
}

float Ship_GetAttackHP(int iCharacterIndex, float fDistance)
{
	float fAttackHP = 0.0;
	if (bSeaActive)
	{
		SendMessage(&AISea, "lafe", AI_MESSAGE_SHIP_GET_ATTACK_HP, &Characters[iCharacterIndex], fDistance, &fAttackHP);
	}
	return fAttackHP;
}

float Ship_GetHP(ref rCharacter) 
{ 
	return stf(rCharacter.Ship.HP); 
}

void Ship_Ship2ShipCollision()
{
	int		iOurCharacterIndex, iEnemyCharacterIndex, iTouchPoint;
	float	fPower, fSlide, x, y, z;
	
	iOurCharacterIndex = GetEventData();   // кого
	iEnemyCharacterIndex = GetEventData();  // кто
	fPower = abs(GetEventData());
	fSlide = abs(GetEventData());
	iTouchPoint = GetEventData();
	x = GetEventData();
	y = GetEventData();
	z = GetEventData();
	
	ref rOurCharacter = GetCharacter(iOurCharacterIndex);
	ref rEnemyCharacter = GetCharacter(iEnemyCharacterIndex);
	bool bDead = LAi_IsDead(rOurCharacter) || LAi_IsDead(rEnemyCharacter);
	if (fPower > 1.0 || (bDead && fPower > 0.1))
	{
		string sAttr = "a" + func_min(iOurCharacterIndex, iEnemyCharacterIndex) + "b" + func_max(iOurCharacterIndex, iEnemyCharacterIndex);
		if(("CollisionSound." + sAttr) !in &TEV)
		{
			Play3DSound("coll_ship2ship", x, y, z);
			int randTime = rand(1000) + 300;
			TEV.CollisionSound.(sAttr) = true;
			PostEvent("Event_CollisionSoundCooldown", randTime, "s", sAttr);
		}
	}
	
	if(bDead)
		return;
	
	float fHP = (1.0 - fSlide) * fPower * 10.0;
	//Trace("Ship->Ship touch: idx = " + iOurCharacterIndex + ", fpower = " + fPower + ", fHP = " + fHP + ", fSlide = " + fSlide);
	Ship_ApplyHullHitpoints(rOurCharacter, fHP, KILL_BY_TOUCH, iEnemyCharacterIndex);
	// зашита от потопления тараном -->
	if (iEnemyCharacterIndex == GetMainCharacterIndex() && GetHullPercent(rOurCharacter) <= 14)
	{
		if (!IsCompanion(rOurCharacter) && GetRelation(sti(rOurCharacter.index), GetMainCharacterIndex()) != RELATION_ENEMY)
		{
			Ship_NationAgressive(rOurCharacter, rOurCharacter);
	    	DoQuestCheckDelay("NationUpdate", 0.9);
    	}
	}
	// зашита от потопления тараном <--
}

void Ship_ApplyCrewHitpoints(ref rOurCharacter, float fCrewHP)
{         // че-то распук метод "неподецки" - переделал 29.07.06 boal
	if (LAi_IsImmortal(rOurCharacter)) 
	{ 
		return; 
	}

	ref rBaseShip = GetRealShip(GetCharacterShipType(rOurCharacter));
	float fMultiply = 1.0 - (0.75 * stf(rOurCharacter.TmpSkill.Defence)); // было 0.05 - что полная хрень, тк скил 0..1

	if (CheckOfficersPerk(rOurCharacter, "Doctor1")) fMultiply = fMultiply * (1-PERK_VALUE_DOCTOR1);
	if (CheckOfficersPerk(rOurCharacter, "Doctor2")) fMultiply = fMultiply * (1-PERK_VALUE_DOCTOR2);

	if(ShipBonus2Artefact(rOurCharacter, SHIP_GALEON_SM))
	{
		fMultiply = fMultiply * isEquippedArtefactUse(rOurCharacter, "amulet_10", 1.0, 0.85 );
	}
	else
	{
		fMultiply = fMultiply * isEquippedArtefactUse(rOurCharacter, "amulet_10", 1.0, 0.90 ); //belamour isEquippedAmuletUse не работает на офицерах, только на ГГ
	}
	fMultiply *= fLiberMisBonus(rOurCharacter);
	float fDamage = fCrewHP * fMultiply; 

	float fNewCrewQuantity = stf(rOurCharacter.Ship.Crew.Quantity) - fDamage;
	float f5Percent = stf(rBaseShip.MinCrew) * 0.25; // boal fix неубиваемые 25% команды- было 0.05;
	// boal  check skill -->
	if (fNewCrewQuantity >= f5Percent && IsCompanion(rOurCharacter))
	{
       AddCharacterExpToSkill(rOurCharacter, "Defence", makefloat(fCrewHP / 2 + 0.5));
       ChangeCrewExp(rOurCharacter, "Soldiers",  (fCrewHP / stf(rBaseShip.OptCrew))); // to_do может быть много
    }
    // boal <--
	
	if (fNewCrewQuantity < f5Percent) { fNewCrewQuantity = f5Percent; }
	if (fNewCrewQuantity < 0.0) { fNewCrewQuantity = 0.0; }
	
	if (sti(rOurCharacter.index) == GetMainCharacterIndex() && stf(rBaseShip.MinCrew) > fNewCrewQuantity && stf(rBaseShip.MinCrew) <= stf(rOurCharacter.Ship.Crew.Quantity))
    {  // переход на мин команду
        PlaySound("OBJECTS\SHIPCHARGE\_Damage1.wav");
    }
	// boal fix утопленников   -->
	if (stf(rOurCharacter.Ship.Crew.Quantity) > fNewCrewQuantity)
	{   // на случай косяков со знаком fCrewHP
		if (sti(rOurCharacter.index) == GetMainCharacterIndex() || IsCompanion(rOurCharacter))
		{
			Statistic_AddValue(GetMainCharacter(), "Sailors_dead", stf(rOurCharacter.Ship.Crew.Quantity) - fNewCrewQuantity);
			Achievment_SetStat(21, makeint(sti(rOurCharacter.Ship.Crew.Quantity) - fNewCrewQuantity));
			AddMementoShipBonus(stf(rOurCharacter.Ship.Crew.Quantity) - fNewCrewQuantity);
		}
		rOurCharacter.Ship.Crew.Quantity = fNewCrewQuantity;
	}
	if (stf(rOurCharacter.Ship.Crew.Quantity) < 0.0) { rOurCharacter.Ship.Crew.Quantity = 0.0; }
	// boal fix утопленников   <--
}

void Ship_ApplyHullHitpoints(ref rOurCharacter, float fHP, int iKillStatus, int iKillerCharacterIndex)
{
	bool bHullTututorial = bGlobalTutor && GetHullPercent(rOurCharacter) > 20;
   	if (LAi_IsImmortal(rOurCharacter) && !bHullTututorial) { return; }

	float fCurHP;
	float fMinus 	= 0.0;
	float fPlus 	= 0.0;
	float fPercent	= 0.0;
	
    if (bSeaReloadStarted) { return; }
	if (fHP <= 0.0) { return; }
	if (LAi_IsDead(rOurCharacter) || !CheckAttribute(rOurCharacter, "Ship.HP")) { return; }   // fix
	
    if (iKillerCharacterIndex >= 0)
	{
		bool isKillerMainChr = IsMainCharacter(&Characters[iKillerCharacterIndex]);
		if (sti(Characters[iKillerCharacterIndex].TmpPerks.HullDamageUp)) 		fPlus += PERK_VALUE_HULL_DAMAGE_UP;
		if (sti(Characters[iKillerCharacterIndex].TmpPerks.CannonProfessional)) fPlus += PERK_VALUE_CANNON_PROFESSIONAL;
		
		if(IsCharacterEquippedArtefact(&Characters[iKillerCharacterIndex], "indian_8")) fPlus += 0.10; // belamour произведение даёт 0 без перков
		if (isKillerMainChr && CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p3.Completed")) fPlus += 0.1;
		if(CheckAttribute(&Characters[iKillerCharacterIndex],"Tmp.LastBortFire.Bonus"))
		{
			fPlus += stf(Characters[iKillerCharacterIndex].Tmp.LastBortFire.Bonus) / 100.0;
		}

		if (isKillerMainChr) fPlus += SZN_GetModifierMtp(M_ENEMY_HULL_DAMAGE_MTP, 0.0);
	}

	if (sti(rOurCharacter.TmpPerks.BasicBattleState))			fMinus += PERK_VALUE_BASIC_BATTLE_STATE;
	if (sti(rOurCharacter.TmpPerks.AdvancedBattleState))		fMinus += PERK_VALUE_ADVANCED_BATTLE_STATE;
	if (sti(rOurCharacter.TmpPerks.ShipDefenseProfessional))	fMinus += PERK_VALUE_SHIP_DEFENSE_PROFESSIONAL;
	
	if(IsCharacterEquippedArtefact(rOurCharacter, "amulet_8"))
	{
		if(ShipBonus2Artefact(rOurCharacter, SHIP_GALEON_SM))
			fMinus += 0.10;
		else
			fMinus += 0.05; // belamour произведение даёт 0 без перков
	}
	if(IsCharacterEquippedArtefact(rOurCharacter, "talisman7")) fMinus += 0.05; // belamour legendary edition скарабей
	if (IsMainCharacter(rOurCharacter) && CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p3.Completed")) fMinus += 0.1;
	
	if (CheckAttribute(rOurCharacter, "SeaBoss")) fMinus = fPlus + stf(rOurCharacter.SeaBoss); // Addon 2016-1 Jason Пиратская линейка

	fCurHP = stf(rOurCharacter.Ship.HP) - fHP * (1.0 + fPlus - fMinus);
	
	if (CheckAttribute(rOurCharacter, "ShipHideImmortal")) // Addon 2016-1 Jason Пиратская линейка
	{
		if (fCurHP <= sti(rOurCharacter.ShipHideImmortal)) LAi_SetImmortal(rOurCharacter, true);
	}
	if (fCurHP <= 0.0)
	{
	if (CheckAttribute(rOurCharacter, "ShipHideImmortal"))
	{
			fCurHP = 200.0;
			LAi_SetImmortal(rOurCharacter, true);
		}
		else
	{
		fCurHP = 0.0;
		ShipDead(sti(rOurCharacter.index), iKillStatus, iKillerCharacterIndex);
	}
	}
	
    if(fCurHP > sti(RealShips[sti(rOurCharacter.ship.type)].HP))
	{
		fCurHP = RealShips[sti(rOurCharacter.ship.type)].HP;
	}
	rOurCharacter.Ship.HP = fCurHP;
	
	// расчет пенальти в корпус для последующего учёта при ремонте
	if(CheckAttribute(RealShips[sti(rOurCharacter.ship.type)],"QuestShip")) fPercent = 1.0;
	else fPercent = 1.0 + (makefloat(MOD_SKILL_ENEMY_RATE)/4.0);
}

void ShipDead(int iDeadCharacterIndex, int iKillStatus, int iKillerCharacterIndex)
{
	ref rDead, rKillerCharacter, rBaseShip, rKillerBaseShip, sld;

	rDead = GetCharacter(iDeadCharacterIndex);
	if (!CheckAttribute(rDead, "Ship.Type")) // fix
    {
        if (MOD_BETTATESTMODE == "On") Log_Info("Error: ShipDead Нет корабля у iDeadCharacterIndex = "+iDeadCharacterIndex);
        return;
    }
    int  iDeadNation = sti(rDead.nation);
    bool bDeadCompanion = IsCompanion(rDead);
	rBaseShip = GetRealShip(sti(rDead.Ship.Type));

	if (iKillerCharacterIndex != -1)
	{
		rKillerCharacter = GetCharacter(iKillerCharacterIndex);
		rKillerBaseShip = GetRealShip(sti(rKillerCharacter.Ship.Type));
		// boal  check skill -->
		if (!bDeadCompanion && iKillStatus != KILL_BY_SPY)
        {
			switch (iKillStatus)
		    {
			    case KILL_BY_TOUCH:
	                AddCharacterExpToSkill(rKillerCharacter, "Sailing", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 90);
	                ChangeCrewExp(rKillerCharacter, "Sailors", 1);
	                // boal statistic info 17.12.2003 -->
	                Statistic_AddValue(rKillerCharacter, "KillShip_" + rBaseShip.Class, 1);
					Achievment_SetStat(3, 1);
					Achievment_Set("ach_01");
					if(sti(rKillerCharacter.nation) == PIRATE) Achievment_SetStat(50, 1);
	                // boal statistic info 17.12.2003 <--
			    break;
			    case KILL_BY_BALL:
			        AddCharacterExpToSkill(rKillerCharacter, "Accuracy", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 35);
			        AddCharacterExpToSkill(rKillerCharacter, "Sailing", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 65);
			        AddCharacterExpToSkill(rKillerCharacter, "Cannons", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 40);
			        ChangeCrewExp(rKillerCharacter, "Sailors", 1);
			        ChangeCrewExp(rKillerCharacter, "Cannoners", 2);
			        // boal statistic info 17.12.2003 -->
	                Statistic_AddValue(rKillerCharacter, "KillShip_" + rBaseShip.Class, 1);
					Achievment_SetStat(3, 1);
					Achievment_Set("ach_01");
					if(sti(rKillerCharacter.nation) == PIRATE) Achievment_SetStat(50, 1);
	                // boal statistic info 17.12.2003 <--
	                //homo 25/06/07 только враг и 1/4
        			if (rand(4) == 2 && GetRelation(sti(rDead.Index), sti(Pchar.Index))== RELATION_ENEMY)
                    {
                        //обычный
                        if(!CheckAttribute(rDead, "DontRansackCaptain") || rDead.DontRansackCaptain == false) AISeaGoods_AddGood(rDead, "enemy_boat", "lo_boat", 1000.0, 1); //homo 25/06/07 спасается на шлюпке
                    }
                    //homo
					if(!GetAchievement("ach_CL_161") && !SeaCameras_isCameraOutside())
					{
						Achievment_Set("ach_CL_161");
					}
			    break;
			    case KILL_BY_ABORDAGE:
			        AddCharacterExpToSkill(rKillerCharacter, "Grappling", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 110);
			        AddCharacterExpToSkill(rKillerCharacter, "Sailing", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 70);
			        AddCharacterExpToSkill(rKillerCharacter, SKILL_FORTUNE, stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 10);
			        AddCharacterExpToSkill(rKillerCharacter, "Defence", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 60);
			        ChangeCrewExp(rKillerCharacter, "Sailors", 0.5);
					// в лаи_бординг ChangeCrewExp(rKillerCharacter, "Soldiers", 4);
			        // boal statistic info 17.12.2003 -->
	                Statistic_AddValue(rKillerCharacter, "KillAbordShip_" + rBaseShip.Class, 1);
					Achievment_SetStat(2, 1);
					Achievment_Set("ach_01");
	                // boal statistic info 17.12.2003 <--
					if(HasShipTrait(rKillerCharacter, "trait22"))
					{
						float fTraitRepair = (stf(rKillerBaseShip.Class) / stf(rBaseShip.Class)) * ((100.0 - GetHullPercent(rKillerCharacter)) / 5.0);
						ProcessHullRepair(rKillerCharacter, fTraitRepair);
						ProcessSailRepair(rKillerCharacter, 12.0);
					}
			    break;
		    }
			if (iKillStatus != KILL_BY_SELF)
			{
				if (iDeadNation == PIRATE && IsMainCharacter(rKillerCharacter) && sti(rKillerBaseShip.BaseType) == SHIP_AMSTERDAM) UpgradeAmsterdam(rKillerBaseShip);
		        AddCharacterExpToSkill(rKillerCharacter, SKILL_FORTUNE, stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 20);
		        AddCharacterExpToSkill(rKillerCharacter, "Leadership", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 25);

	            // статистка по нации
		    	Statistic_AddValue(rKillerCharacter, NationShortName(iDeadNation)+"_KillShip", 1);
		    	if (rand(8) < 3 && iDeadNation != PIRATE)  // 30% повышаем награду
		    	{
					ChangeCharacterHunterScore(rKillerCharacter, NationShortName(iDeadNation) + "hunter", GetIntByCondition(HasShipTrait(rKillerCharacter, "trait23"), 1 + rand(1), 1));
				}
			}
        }
        // boal 04.04.04 <--
	}

	//int iQuantity = GetCompanionQuantity(pchar);
	
	float fX = stf(rDead.Ship.Pos.x);
	float fY = stf(rDead.Ship.Pos.y);
	float fZ = stf(rDead.Ship.Pos.z);

	rDead.Ship.HP = 0;
	rDead.Killer.Status = iKillStatus;
	rDead.Killer.Index = iKillerCharacterIndex;
		
	LAi_SetCurHP(rDead, 0.0);
		
	int iExp = 0;
	if (iKillerCharacterIndex != -1) 
	{ 
		iExp = 2 * MakeInt(stf(rBaseShip.HP) * stf(rKillerBaseShip.Class) / stf(rBaseShip.Class)); 
	}

	bool bCompanion = false;
	if (iKillerCharacterIndex != -1) 
	{ 
		bCompanion = IsCompanion(rKillerCharacter); 
	}

 	if (bCompanion)
	{
        if (bDeadCompanion)
        {
            iExp = 0;
            if (iKillerCharacterIndex == GetMainCharacterIndex())
            {
                ChangeCharacterComplexReputation(pchar,"nobility", -15);
            }
        }
        else if (iDeadNation == PIRATE && !CheckAttribute(rDead, "AlwaysFriend"))
        {   // Мы или наш компаньон потопили вражеского пирата
            ChangePirateThreat(sti(rBaseShip.Class) - 7);
        }
	}      
    
	bool bRealKill = false;
	switch (iKillStatus)
	{
		case KILL_BY_TOUCH:
			if (iKillerCharacterIndex != -1) { bRealKill = true; }
		break;
		case KILL_BY_BALL:
			bRealKill = true;
		break;
		case KILL_BY_ABORDAGE:
			bRealKill = true;
		break;
	}

	// Ship sunk log
	if (iDeadCharacterIndex != nMainCharacterIndex)
	{
		string sSunkString;
		string sSunkShipType = XI_ConvertString(rBaseShip.BaseName);
		string sKillShipType = "";
		string sKillShipName = "";
		if (iKillerCharacterIndex != -1)
		{
		    sKillShipType = XI_ConvertString(rKillerBaseShip.BaseName);
		    sKillShipName = "" + rKillerCharacter.Ship.Name;
		}
		if (bCompanion && !bDeadCompanion && bRealKill)
		{
			sSunkString = "'" + rDead.Ship.Name + "' " + XI_ConvertString("ShipSunkM");
            /* sSunkString = sSunkShipType + " '" + rDead.Ship.Name + "' " + GetShipSexWord(rBaseShip.BaseName, XI_ConvertString("ShipSunkM"), XI_ConvertString("ShipSunkW")) + GetFullName(rKillerCharacter); */
        }
        else
        {
            if (sKillShipName == "")
            {
				sSunkString = "'" + rDead.Ship.Name + "' " + XI_ConvertString("ShipSunkM");
            	//sSunkString = sSunkShipType + " '" + rDead.Ship.Name + "' " + GetShipSexWord(rBaseShip.BaseName, XI_ConvertString("ShipSunkM"), XI_ConvertString("ShipSunkW"));
            }
            else
            {
				sSunkString = "'" + rDead.Ship.Name + "' " + XI_ConvertString("ShipSunkM");
				//sSunkString = sSunkShipType + " '" + rDead.Ship.Name + "' " +GetShipSexWord(rBaseShip.BaseName, XI_ConvertString("ShipSunkM"), XI_ConvertString("ShipSunkW")) + sKillShipType + " '" + sKillShipName + "'";
			}
        }
		//Log_SetStringToLog(sSunkString);
		notification(sSunkString, "DeadShip");
	}

 	if (rand(10) >= 6)
	{ 
		bool bDetonate = false;
		switch (iKillStatus)
		{
			case KILL_BY_BALL:	
				bDetonate = true; 
			break;
			/*case KILL_BY_SPY:	
				bDetonate = true; 
			break;  */ // идёт вылет, если второй раз рекурсию Ship_Detonate делать
		}
		if (bDetonate) 
		{ 
			Ship_Detonate(rDead, true, false); 
		}
	}

	// set attributes for sinking effect
	rDead.Ship.Sink = "";
	aref aSink; makearef(aSink, rDead.Ship.Sink);
	
/*	
	aSink.Speed.y = 0.35;	// speed of sink y
	aSink.Speed.x = 0.017 * (frnd() * 2.0 - 1.0);	// speed sink angle rotate around x
	aSink.Speed.z = 0.017 * (frnd() * 2.0 - 1.0);	// speed sink angle rotate around z
*/
	// корабль тонет  - немного добавим драматизьму :-)
	aSink.Speed.y = 0.25 + (frnd() * 0.05);	// speed of sink y
	aSink.Speed.x = 0.021 * (frnd() * 2.0 - 1.0);	// speed sink angle rotate around x
	aSink.Speed.z = 0.04 * (frnd() * 2.0 - 1.0);	// speed sink angle rotate around z
	
	if (iDeadCharacterIndex == nMainCharacterIndex)
	{ 
		SeaCameras_SetDieCamera();
		FadeOutMusic(2);
		//PlayStereoOGG("music_ship_dead");
		// убил ЛГ
		if (iKillerCharacterIndex != -1 && rKillerCharacter.id == "GhostCapt")
		{
		    DoQuestCheckDelay("Survive_In_Sea", 9.0);
		}
		else
		{
			InterfaceStates.Buttons.Save.enable = false;
			PostEvent(GAME_OVER_EVENT, 15000);
		}
	}
	else
	{
        if (bDeadCompanion && CheckOfficersPerk(rDead, "ShipEscape") && GetRemovable(rDead)) // выживаем
        {
			// belamour 09/09/24
			if(CheckAttribute(rDead, "OfficerImmortal")) AISeaGoods_AddGood_ImmortalOfficer(rDead, "boat", "lo_boat", 5000.0, 1);
            //homo 22/06/07
            else AISeaGoods_AddGood(rDead, "boat", "lo_boat", 1000.0, 1);
            RemoveCharacterCompanion(pchar, rDead);
            Log_Info(GetFullName(rDead) + XI_ConvertString("SurvivedBoat"));
        }
	}

    Play3DSoundEvent("ShipEMB/Ship_sinking", fX, fY, fZ);
	
	// TUTOR-ВСТАВКА
	if(TW_IsActive() && objTask.sea_battle == "3_WinBattle" && Ship_GetGroupID(rDead) == "SharlieTutorial_SeaAttack")
	{
		if(TW_IncreaseCounter("sea_battle", "WinBattle_do", 1))
		{
			objTask.sea_battle = "";
			PostEvent("TW_Release", 2000);
		}
	}

	// Message to AI
	SendMessage(&AISea, "la", AI_MESSAGE_CHARACTER_DEAD, rDead);

	// Event
	Event(SHIP_DEAD, "l", iDeadCharacterIndex);
}

// boal -->
void ShipTaken(int iDeadCharacterIndex, int iKillStatus, int iKillerCharacterIndex)
{
	ref rDead, rKillerCharacter, rMainCharacter, rBaseShip, rKillerBaseShip;

	rDead = GetCharacter(iDeadCharacterIndex);
	rDead.Killer.Index = iKillerCharacterIndex;
	rBaseShip = GetRealShip(sti(rDead.Ship.Type));
	rMainCharacter = GetMainCharacter();

	bool bCompanion = false;
	bool bDeadCompanion = IsCompanion(rDead);

    LAi_SetCurHP(rDead, 0.0); // умер
	rDead.Killer.Status = iKillStatus;
	rDead.Killer.Index = iKillerCharacterIndex;
    if (iKillerCharacterIndex != -1 && !bDeadCompanion)
	{
		rKillerCharacter = GetCharacter(iKillerCharacterIndex);
		rKillerBaseShip = GetRealShip(sti(rKillerCharacter.Ship.Type));
		bCompanion = IsCompanion(rKillerCharacter);
		// boal  check skill -->
        AddCharacterExpToSkill(rKillerCharacter, SKILL_FORTUNE, stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 20);
        AddCharacterExpToSkill(rKillerCharacter, "Leadership", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 25);
        AddCharacterExpToSkill(rKillerCharacter, "Grappling", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 120);
		AddCharacterExpToSkill(rKillerCharacter, "Sailing", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 70);
		AddCharacterExpToSkill(rKillerCharacter, "Commerce", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 30);
		AddCharacterExpToSkill(rKillerCharacter, "Repair", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 60);
		AddCharacterExpToSkill(rKillerCharacter, "Defence", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 60);
        // boal <--
        // boal statistic info 17.12.2003 -->
        Statistic_AddValue(rKillerCharacter, "AbordShip_" + rBaseShip.Class, 1);
        Statistic_AddValue(rKillerCharacter, NationShortName(sti(rDead.nation))+"_AbordShip", 1);
		Achievment_SetStat(2, 1);
		Achievment_Set("ach_01");
        // boal statistic info 17.12.2003 <--
        
        ChangeCrewExp(rKillerCharacter, "Sailors", 0.5);
		// в лаи_бординг ChangeCrewExp(rKillerCharacter, "Soldiers", 5); // to_do перенести на форму захвата
	}
	if (iDeadCharacterIndex != GetMainCharacterIndex())
	{
		string sSunkShipType = XI_ConvertString(rBaseShip.BaseName);
		string sKillShipType = XI_ConvertString(rKillerBaseShip.BaseName);

		if(bCompanion && !bDeadCompanion)
		{
            Log_SetStringToLog(sSunkShipType + " '" + rDead.Ship.Name + "' " + XI_ConvertString("WasCaptured1"));
        }
	}
    if (rand(8) < 3 && !bDeadCompanion && sti(rDead.nation) != PIRATE)  // 30% повышаем награду
    {
        ChangeCharacterHunterScore(rKillerCharacter, NationShortName(sti(rDead.nation)) + "hunter", 1+rand(1));
    }
}
// захваченный корабль, отпущен
void ShipTakenFree(int iDeadCharacterIndex, int iKillStatus, int iKillerCharacterIndex)
{
	ref rDead, rKillerCharacter, rMainCharacter, rBaseShip, rKillerBaseShip;

	rDead = GetCharacter(iDeadCharacterIndex);
	rDead.Killer.Index = iKillerCharacterIndex;
	rBaseShip = GetRealShip(sti(rDead.Ship.Type));
	rMainCharacter = GetMainCharacter();

    LAi_SetCurHP(rDead, 0.0); // умер
	rDead.Killer.Status = iKillStatus;
	rDead.Killer.Index = iKillerCharacterIndex;
    if (iKillerCharacterIndex != -1)
	{
		rKillerCharacter = GetCharacter(iKillerCharacterIndex);
		rKillerBaseShip = GetRealShip(sti(rKillerCharacter.Ship.Type));
		
        AddCharacterExpToSkill(rKillerCharacter, "Leadership", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 50);
        AddCharacterExpToSkill(rKillerCharacter, "Grappling", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 120);
		AddCharacterExpToSkill(rKillerCharacter, "Sailing", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 80);
		AddCharacterExpToSkill(rKillerCharacter, SKILL_FORTUNE, stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 70);
		AddCharacterExpToSkill(rKillerCharacter, "Repair", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 10);
		AddCharacterExpToSkill(rKillerCharacter, "Defence", stf(rKillerBaseShip.Class) / stf(rBaseShip.Class) * 10);
        
		Statistic_AddValue(rKillerCharacter, "AbordShipFree_" + rBaseShip.Class, 1);  // эту статистику пока нигде не видно to_do
        Statistic_AddValue(rKillerCharacter, NationShortName(sti(rDead.nation))+"_AbordShipFree", 1);
        Statistic_AddValue(rKillerCharacter, "AbordShipFree", 1); // отпущено
        
        ChangeCrewExp(rKillerCharacter, "Sailors", 0.5);
		// в лаи_бординг ChangeCrewExp(rKillerCharacter, "Soldiers", 5); // to_do перенести на форму захвата
		if(!CheckAttribute(rDead,"Situation"))
		{
			ChangeCharacterComplexReputation(rKillerCharacter,"nobility", 2); 
			ChangeCharacterComplexReputation(rKillerCharacter,"authority", -2); 
			ChangeCharacterComplexReputation(rKillerCharacter,"fame", 1); 
			OfficersReaction("good");
		}	
	}
	if (iDeadCharacterIndex != GetMainCharacterIndex() && !CheckAttribute(rDead,"Situation"))
	{
		string sSunkShipType = XI_ConvertString(rBaseShip.BaseName);
		string sKillShipType = XI_ConvertString(rKillerBaseShip.BaseName);

        Log_SetStringToLog(sSunkShipType + " '" + rDead.Ship.Name + "' " + XI_ConvertString("WasCaptured2"));
		if (CheckAttribute(pchar, "GenQuest.Detonation"))
		{
			DoQuestCheckDelay("CanNotEnterToMap", 0.2); // patch-4
			DeleteAttribute(pchar, "GenQuest.Detonation");
		}
	}
    if (rand(20) < 3 && sti(rDead.nation) != PIRATE)  // 14% повышаем награду
    {
        ChangeCharacterHunterScore(rKillerCharacter, NationShortName(sti(rDead.nation)) + "hunter", 1+rand(1));
    }
}
// boal <--

void Ship_SailHitEvent()
{
}

void Ship_HullHitEvent()
{
	float	fHP;

	int		iBallType = sti(AIBalls.CurrentBallType);

	aref	rShipObject = GetEventData();

	int		iBallCharacterIndex = GetEventData();
	int		iOurCharacterIndex = GetEventData();

	ref		rBallCharacter = GetCharacter(iBallCharacterIndex);	// кто пуляет
	ref		rOurCharacter = GetCharacter(iOurCharacterIndex);   // по кому

	rOurCharacter.Ship.LastBallCharacter = iBallCharacterIndex;

	float	x = GetEventData();
	float	y = GetEventData();
	float	z = GetEventData();

	int		iFirePlaceIndex = GetEventData();   
	float	fFirePlaceDistance = GetEventData();
	
	//Log_Info(" Ship_HullHitEvent : rOurCharacter.id = " + rOurCharacter.id + " rBallCharacter.id = " + rBallCharacter.id);

	bool	bDead = LAi_IsDead(rOurCharacter) && CheckAttribute(rBallCharacter, "Ship.Cannons.Type");  // boal fix

	bool	bSeriousBoom = false;
	bool	bInflame = false;
    bool    isOurCompanion   = IsCompanion(rOurCharacter);
    float   fTmpCannonDamage = 0;
    
    if (bDead) return; // фикс, не нужно обсчитывать труп
	// Cannon damage multiply
	ref rCannon = GetCannonByType(sti(rBallCharacter.Ship.Cannons.Type));
	float fCannonDamageMultiply = stf(rCannon.DamageMultiply);
	if (GetMainCharacterIndex() == iBallCharacterIndex && !SeaCameras_isCameraOutside())
	{
		fCannonDamageMultiply += isEquippedArtefactUse(rBallCharacter, "totem_08", 0.0, 0.1); // Повелитель огня для прицельной у ГГ
	}

	float fDistanceDamageMultiply = Bring2Range(1.2, 0.25, 0.0, stf(AIBalls.CurrentMaxBallDistance), stf(AIBalls.CurrentBallDistance));

	float fCritical = 0.0;
	if (int(rBallCharacter.TmpPerks.CriticalShoot))
		fCritical += PERK_VALUE_CRITICAL_SHOOT;
	if (int(rBallCharacter.TmpPerks.CannonProfessional))
		fCritical += PERK_VALUE_CANNON_PROFESSIONAL;
	if (fPercentChance(fCritical))
		bSeriousBoom = true;

	ref rBall = GetGoodByType(iBallType);
	switch (iBallType)
	{
		case GOOD_BALLS:
			breachTheHull(rOurCharacter, rBallCharacter, stf(AIBalls.CurrentBallDistance), fCannonDamageMultiply);
			if (rand(85) == 17) bSeriousBoom = true; // boal 35
			if (rand(30) == 15) bInflame = true;
            Play3DSoundEvent("ShipEMB/ShipDamage_ball", x, y, z);
		break;
		case GOOD_GRAPES:
			bSeriousBoom = false;
			Play3DSoundEvent("ShipEMB/ShipDamage_grapes", x, y, z);
            if (rand(100) < 30) Play3DSoundEvent("sounds of sailors/SailorGroan", x, y, z); // Play3DSound("episode_boom", x, y, z);
		break;
		case GOOD_KNIPPELS:
			bSeriousBoom = false;
            Play3DSoundEvent("ShipEMB/ShipDamage_knippel", x, y, z);
		break;
		case GOOD_BOMBS:
			if (rand(50) == 10) bSeriousBoom = true; // boal 20
			if (rand(5) == 1)   bInflame = true;
			Play3DSoundEvent("ShipEMB/ShipDamage_bomb", x, y, z);
		break;
	}
	fTmpCannonDamage = fCannonDamageMultiply * stf(rBall.DamageHull);
	if (rand(2) == 1) CreateParticleSystem("blast", x, y, z, 0.0, 0.0, 0.0, 0);// boal fix

    if (sti(rOurCharacter.TmpPerks.ShipDefenseProfessional) && rand(1000) < 700) bSeriousBoom = false; // no seriouse boom

    float fCrewDamage = stf(rBall.DamageCrew) * fCannonDamageMultiply * AIShip_isPerksUse(rBallCharacter.TmpPerks.CrewDamageUp, 1.0, PERK_VALUE_CREW_DAMAGE_UP);
	
	if(rOurCharacter.id == "Memento_cap" && GetHullPercent(rOurCharacter) > 30.0)
	{
		fCrewDamage /= 10.0;
	}
	
	if (bSeriousBoom)
	{
		fCrewDamage = fCrewDamage * 7.0;
		fHP = fDistanceDamageMultiply * fCannonDamageMultiply * stf(rBall.DamageHull) * (8.0 + frnd() * 4.0); // 4.0
		Ship_ApplyHullHitpoints(rOurCharacter, fHP, KILL_BY_BALL, iBallCharacterIndex);

        if (iBallCharacterIndex == nMainCharacterIndex) PlayShipSoundEvent(PChar, "sounds of sailors/SailorJubilation_Battle", true);
		notification("'"+rOurCharacter.Ship.Name+GetSimpleSeaSectionKey("Ship_critical_notif"), "Brander");
		/* if (iBallCharacterIndex == nMainCharacterIndex)
		{
			Log_SetStringToLog(GetSimpleSeaSectionKey("Ship_critical"));
		} */
		/*int iFlow = rand(100);  // to_do
		if(iFlow < 10)
		{
			if(sti(rOurCharacter.index) == nMainCharacterIndex)
			{
				Log_SetStringToLog(GetSimpleSeaSectionKey("Ship_flow"));
			}
			rOurCharacter.ship.flow = iFlow;
		}
		*/
		// boal  check skill -->
		if (!isOurCompanion && IsCompanion(rBallCharacter) && !CheckAttribute(rOurCharacter, "ShipEnemyDisable"))
		{
            AddCharacterExpToSkill(rBallCharacter, "Accuracy", 15);
            AddCharacterExpToSkill(rBallCharacter, SKILL_FORTUNE, 15);
            AddCharacterExpToSkill(rBallCharacter, "Leadership", 2);
            AddCharacterExpToSkill(rBallCharacter, "Sailing", 15);
            AddCharacterExpToSkill(rBallCharacter, "Cannons", 15);
            ChangeCrewExp(rBallCharacter, "Sailors", 0.05);
			ChangeCrewExp(rBallCharacter, "Cannoners", 0.5);
        }
        // boal <--
	}
	else
	{ 
		fHP = fDistanceDamageMultiply * fCannonDamageMultiply * stf(rBall.DamageHull);
		Ship_ApplyHullHitpoints(rOurCharacter, fHP, KILL_BY_BALL, iBallCharacterIndex); 
		// boal  check skill -->
		if (!isOurCompanion && IsCompanion(rBallCharacter) && !CheckAttribute(rOurCharacter, "ShipEnemyDisable"))
		{
            AddCharacterExpToSkill(rBallCharacter, "Accuracy", 2.5);
            AddCharacterExpToSkill(rBallCharacter, "Sailing", 1);
            AddCharacterExpToSkill(rBallCharacter, "Cannons", 1);
            ChangeCrewExp(rBallCharacter, "Cannoners", 0.01);
        }
        // boal <--
	}
	Ship_ApplyCrewHitpoints(rOurCharacter, fCrewDamage);

	if(HasShipTrait(rBallCharacter, "trait24") && !bInflame)
	{
		if(AIBalls.FromBort == "cannonb" || AIBalls.FromBort == "cannonf") // с порно, тк это не ядра, того кто стрелял, а скорее ядра ГГ
		{
			if(rand(2) == 1) bInflame = true;
		}
	}

	if (bInflame == true && fFirePlaceDistance < 4.0 && iFirePlaceIndex >= 0)
	{
		int iRandStartTime = rand(1000);
		float fTotalFireTime = Ship_GetTotalFireTime(rOurCharacter);
		if(HasShipTrait(rBallCharacter, "trait24"))
		{
			fTotalFireTime = 15.0;
			rBallCharacter.AIShipFireDamage = fHP * 2.0 / 15.0;
		}

		PostEvent(SHIP_ACTIVATE_FIRE_PLACE, iRandStartTime, "ialsfl", rShipObject, rOurCharacter, iFirePlaceIndex, "ShipEMB/ShipDamage_Fire", fTotalFireTime, iBallCharacterIndex);
		PostEvent(SHIP_FIRE_DAMAGE, iRandStartTime, "lllf", iOurCharacterIndex, iBallCharacterIndex, iFirePlaceIndex, fTotalFireTime);
	}

	if (bSeriousBoom == true) 
	{ 
		if (rOurCharacter.id == pchar.id || rand(2) == 1)
		{
			Ship_Serious_Boom(x, y, z); 
		}
		fTmpCannonDamage = fTmpCannonDamage * 6.0;
		//boal 27.09.05 -->
		if ((GetCargoGoods(rOurCharacter, GOOD_POWDER) / 20.0) > (GetCargoMaxSpace(rOurCharacter) * 0.25) && rand(1) == 1)
		{
			Ship_SetExplosion(rOurCharacter, rShipObject);
			Log_Info(XI_ConvertString("ShipOn") + rOurCharacter.Ship.Name + XI_ConvertString("PowderDetonate"));
		}
		//boal 27.09.05 <--
	}
    SendMessage(&AISea, "laffff", AI_MESSAGE_CANNONS_BOOM_CHECK, rOurCharacter, fTmpCannonDamage, x, y, z);  // fix перенес с проверкой на труп
	// boal 290704 раз в минуту проверяем обиду на гл героя, если жухлит через желтый прицел -->
	//Log_Info(rOurCharacter.id);
	
/*	
	Log_Info(" Ship_HullHitEvent : LastBallCharacter : " + rOurCharacter.Ship.LastBallCharacter + " mCharIndex : " + GetMainCharacterIndex());
	Log_Info(" GetNationRelation2MainCharacter(sti(rOurCharacter.nation)) : " + GetNationRelation2MainCharacter(sti(rOurCharacter.nation)));
	if(CheckAttribute(rOurCharacter, "Coastal_Captain")) Log_Info("Coastal_Captain");
*/	
	
	if (sti(rOurCharacter.Ship.LastBallCharacter) == GetMainCharacterIndex() && GetNationRelation2MainCharacter(sti(rOurCharacter.nation)) != RELATION_ENEMY)
    {
        if (!isOurCompanion && !CheckAttribute(rOurCharacter, "Coastal_Captain")) // по своим можно палить таможня пофиг
        {
            Ship_NationAgressive(rOurCharacter, rOurCharacter);// boal 030804 в один метод
            DoQuestCheckDelay("NationUpdate", 0.7);
        }
    }
	/* if (rOurCharacter.id == "TortugaBranderCap_2" || rOurCharacter.id == "TortugaBranderCap_3") //Jason: атака брандеров у Тортуги 2015
	{
		if (sti(rOurCharacter.Ship.LastBallCharacter) == GetMainCharacterIndex() && CheckAttribute(rOurCharacter, "checkattack")) Tortuga_ShipGuardAttack();
	} */
	if (rOurCharacter.id == "WorldMarchCap1" || rOurCharacter.id == "WorldMarchCap2" || rOurCharacter.id == "WorldMarchCap3") //Jason: горячий рейд
	{
		if (!CheckAttribute(pchar, "GenQuest.MarchCap.Battlestart")) DoQuestFunctionDelay("MarchCap2_CheckBattle", 0.5);
	}
	if (rOurCharacter.id == "Cap_Vensan") //Jason: сага, бригантина венсана
	{
		if (!CheckAttribute(pchar, "questTemp.Saga.BarbTemptation.Vensan_free")) DoQuestFunctionDelay("Saga_BrigantineDetonate", 0.5);
	}
	if (rOurCharacter.id == "Saga_Vagrant" || rOurCharacter.id == "Saga_vampire") //Jason: сага - Бродяга и Упырь
	{
		Saga_VagrantVampireAttack();
	}
	if (rOurCharacter.id == "Jackman") //Jason: сага - Джекман
	{
		Saga_CenturionAttack();
	}
	if (rOurCharacter.id == "Molligan" && CheckAttribute(pchar, "questTemp.Saga.Molligan.friend") && sti(AIBalls.CurrentBallType) == GOOD_GRAPES) //Jason: сага - Моллиган 
	{
		Saga_MolliganCriticalAttack();
	}
	if (rOurCharacter.id == "Rozencraft" && CheckAttribute(pchar, "GenQuest.Bakaut")) //Jason: генератор бакаута 
	{
		DeleteAttribute(pchar, "GenQuest.Bakaut"); // конец генератора
	}
	if(!CheckAttribute(pchar, "questTemp.SantaMisericordia.AttackFromMap") && !CheckAttribute(pchar, "questTemp.SantaMisericordia.SpainReputation") && rOurCharacter.id == "SantaMisericordia_cap")
	{
		SantaMisericordia_SpainReputation();
	}
	if(rOurCharacter.id == "Memento_cap" && !CheckAttribute(rOurCharacter, "PlayerAttack"))
	{
		Memento_PlayerAttack();
	}
    // boal 290704 раз в минуту проверяем обиду на гл героя, если жухлит через желтый прицел <--sti(AIBalls.CurrentBallType)
}

float Ship_GetTotalFireTime(ref rCharacter)
{
	int iRepairSkill = MakeInt(stf(rCharacter.TmpSkill.Repair) * 10.0); 
	return MakeFloat(5 + 3 * (10 - iRepairSkill));
}

void Ship_FireDamage()
{
	int iOurCharacterIndex = GetEventData();
	int iBallCharacterIndex = GetEventData();

	int iFirePlaceIndex = GetEventData();
	float fTotalFireTime = GetEventData();

	ref rOurCharacter = GetCharacter(iOurCharacterIndex);
	ref rBallCharacter = GetCharacter(iBallCharacterIndex);
	
	int iSClass = GetCharacterShipClass(rOurCharacter);

	float fHP = (9 - iSClass) * (0.5 + frnd() * 0.5);

	int iTime = 1000 + rand(500);

	// if abordage or interface launched
	if (!bAbordageStarted && !sti(InterfaceStates.Launched)) 
	{ 
		if(HasShipTrait(rBallCharacter, "trait24"))
		{
			if(CheckAttribute(rBallCharacter, "AIShipFireDamage"))
				fHP = stf(rBallCharacter.AIShipFireDamage);
			Ship_ApplyHullHitpoints(rOurCharacter, fHP, KILL_BY_BALL, iBallCharacterIndex); 
			fTotalFireTime = fTotalFireTime - 1.0;
			iTime = 1000;
			//Log_testinfo("trait24 : урон по корпусу " + rand(10));
		}
		else
		{
			Ship_ApplyHullHitpoints(rOurCharacter, fHP, KILL_BY_BALL, iBallCharacterIndex); 
			fTotalFireTime = fTotalFireTime - MakeFloat(iTime) / 250.0;
		}
	}

	if (fTotalFireTime > 0.0)
	{
		PostEvent(SHIP_FIRE_DAMAGE, iTime, "lllf", iOurCharacterIndex, iBallCharacterIndex, iFirePlaceIndex, fTotalFireTime);
	}
    else
	{
		DeleteAttribute(rBallCharacter, "AIShipFireDamage");
	}
}

void Ship_SailDot()
{
	int iOurCharacterIndex = GetEventData();
	int iBallCharacterIndex = GetEventData();
	float fTotalSailDotTime = GetEventData();

	ref rOurCharacter = GetCharacter(iOurCharacterIndex);
	ref rBallCharacter = GetCharacter(iBallCharacterIndex);
	
	int iSClass = GetCharacterShipClass(rOurCharacter);

	float fSP = 0.0;

	int iTime = 1000;

	// if abordage or interface launched
	if (!bAbordageStarted && !sti(InterfaceStates.Launched)) 
	{ 
		if(HasShipTrait(rBallCharacter, "trait24"))
		{
			int iBallType = sti(rBallCharacter.Ship.Cannons.Charge.Type);
			fSP = GetRigDamage(iBallCharacterIndex, iBallType, rOurCharacter);
			
			MakeSailDmg(iOurCharacterIndex, fSP * 2.0 / 15.0); 
			fTotalSailDotTime = fTotalSailDotTime - 1.0;
			//Log_testinfo("trait24 : урон по парусам" + rand(10));
		}
	}

	if (fTotalSailDotTime > 0.0)
	{
		PostEvent("event_sail_dot", iTime, "llf", iOurCharacterIndex, iBallCharacterIndex, fTotalSailDotTime);
	}
}

void Ship_Serious_Boom(float x, float y, float z)
{
	CreateBlast(x,y,z);
	CreateParticleSystem("ShipExplode", x, y, z, 0.0, 0.0, 0.0, 0);
	Play3DSoundEvent("ShipEMB/Explosion_Ship", x, y, z);
}

void Ship_SetFantomData(ref rFantom)
{
	ref		rBaseShip;

	rBaseShip = GetRealShip(sti(rFantom.Ship.Type));

	int iOptCrew = sti(rBaseShip.OptCrew);

	int iBaseHP = sti(rBaseShip.HP);
	int iCapacity = sti(rBaseShip.Capacity);

	float crewMtp = SZN_GetModifierMtp(M_WORLD_SHIPS_CREW_MTP, 1.0, 0.10, 1.0);
	int resultCrew = iOptCrew - rand(makeint(iOptCrew / 3)) + makeint(iOptCrew / 5); //отп команды +-20%
	if (crewMtp != 1.0) resultCrew *= crewMtp + 0.10 - frand(0.20);
	rFantom.ship.Crew.Quantity = resultCrew;

	float hullMtp = SZN_GetModifierMtp(M_WORLD_SHIPS_HULL_MTP, 1.0, 0.10, 1.0);
	if (iBaseHP == GetAttributeInt(rFantom, "Ship.HP") && hullMtp != 1.0)
	{
		rFantom.Ship.HP = iBaseHP * fClamp(0.10, 1.0, hullMtp + 0.15 - frand(0.30));
	}
	else if (rand(3) == 2)
	{ 
		rFantom.Ship.HP = iBaseHP - rand(makeint(iBaseHP / 8));
	}
	else rFantom.Ship.HP = iBaseHP;

	if (CheckAttribute(rFantom, "Ship.Masts")) { DeleteAttribute(rFantom, "Ship.Masts"); }
	if (CheckAttribute(rFantom, "Ship.Blots")) { DeleteAttribute(rFantom, "Ship.Blots"); }
	if (CheckAttribute(rFantom, "Ship.Sails")) { DeleteAttribute(rFantom, "Ship.Sails"); }
	if (CheckAttribute(rFantom, "Ship.Hulls")) { DeleteAttribute(rFantom, "Ship.Hulls"); }
}

void CharacterUpdateShipFromBaseShip(int iCharacterIndex)
{
	ref rCharacter, rBaseShip;
	
	rCharacter = GetCharacter(iCharacterIndex);
	rBaseShip = GetRealShip(sti(rCharacter.Ship.Type));

	if (!CheckAttribute(rCharacter,"Ship.Crew.Quantity")) 
	{ 
		rCharacter.ship.Crew.Quantity = rBaseShip.MaxCrew; 
	}

	if (!CheckAttribute(rCharacter,"Ship.HP")) 
	{ 
		rCharacter.Ship.HP = rBaseShip.HP; 
	}
	if (!CheckAttribute(rCharacter,"Ship.SP")) 
	{ 
		rCharacter.Ship.SP = rBaseShip.SP; 
	}

	if (!CheckAttribute(rCharacter,"Ship.Cannons.Charge.Type")) 
	{ 
		rCharacter.Ship.Cannons.Charge.Type = GOOD_BOMBS; 
	}
	
	//Trace("Init cindex = " + iCharacterIndex + ", ship HP = " + rCharacter.Ship.HP + ", id = " + rCharacter.id + ", idx = " + rCharacter.index);
	if (!CheckAttribute(rCharacter,"Ship.Cannons.Type")) 
	{ 
		rCharacter.Ship.Cannons.Type = CANNON_TYPE_CULVERINE_LBS8; 
	}

	rCharacter.Ship.Cannons.Borts = "";
}

float Ship_CalcGrapplingPerk(ref rCharacter)
{
	aref	arTmpPerks; 
	makearef(arTmpPerks, rCharacter.TmpPerks);

	float fGrapplingPerk = AIShip_isPerksUse(rCharacter.TmpPerks.LongRangeGrappling, 1.0, 1.15); 
	return AIShip_isPerksUse(rCharacter.TmpPerks.GrapplingProfessional, fGrapplingPerk, 1.25);

	return fGrapplingPerk;
}

float Ship_CalcMaxAbordageDistance(float fGrappling, float fGrapplingPerk)
{
	return fGrapplingPerk * Bring2Range(15.0, 40.0, 0.0, 1.0, fGrappling);
}

float Ship_CalcMaxAbordageAngle(float fGrappling)
{
	return Bring2Range(0.70, 0.45, 0.0, 1.0, fGrappling);
}

float Ship_CalcMaxAbordageSpeed(float fGrappling)
{
	return Bring2Range(3.0, 5.0, 0.0, 1.0, fGrappling);
}

void Ship_CheckEnemiesAroundMainCharacter()
{
}

void Ship_CheckMainCharacter()
{
	aref	arUpdate, arMoorLoc;
	ref		rIsland;
	int		i, iRelation;
	float	x, z, fBestDistance, fDistance;
	float	fMinEnemyDistance = 1000000.0;
	float	fMinFortAbordDistance = 1000000.0; // для работы доплыть до при разбитом форте
	float	fortDistance = 1000000.0; //для разделения дистанций выхода на карту кораблей и фортов
	bool	bAbordageStartNow = false;
	int		iAbordageStartNowCharacter = -1;

    ClearPostEventsForEvent(SHIP_CHECK_RELOAD_ENABLE);
	PostEvent(SHIP_CHECK_RELOAD_ENABLE, 1000);

	ref rCharacter = pchar;

	// if abordage launched, return
	if (bAbordageStarted) { return; }

	// if interface launched, return
	if (sti(InterfaceStates.Launched)) { return; }

	// if main character is dead - skip
	if (LAi_IsDead(rCharacter)) { return; }

	iStormLockSeconds = iStormLockSeconds - 1;
	if (iStormLockSeconds < 0) { iStormLockSeconds = 0; }

	bAbordageFortCanBe = false;
	bAbordageShipCanBe = false;
	bCanEnterToLand = false;
	bDisableSailTo = false;
	sIslandLocator = "";
	sIslandID = "";

	makearef(arUpdate, rCharacter.SeaAI.Update);

	if (!CheckAttribute(arUpdate, "Ships")) { return; }
	if (!CheckAttribute(arUpdate, "Forts")) { return; }
    // boal время в море идёт!!! -->
    locTmpTime = locTmpTime + 0.5;  // можно засунуть проверку locDisableUpdateTime, если нужно выключить
    if (locTmpTime > 9)
	{
		/*if (bDisableMapEnter)
		{
			if (locTmpTime > 29)
			{
				CalcLocalTime(6);
    			BattleInterface.textinfo.Date.text = XI_convertString("Date:")+GetQuestBookData();
			}
		}
		else
		{ */
		    CalcLocalTime(2);
      		BattleInterface.textinfo.Date.text = GetQuestBookData();
		//}
	}
	// boal время в море идёт!!! <--
	
	x = stf(rCharacter.Ship.Pos.x);
	z = stf(rCharacter.Ship.Pos.z);

	float fOurHP = Ship_GetHP(rCharacter);
	float fOurGrappling = stf(rCharacter.TmpSkill.Grappling);
	float fOurCrewFencing = (0.1 + fOurGrappling * stf(rCharacter.Ship.Crew.Quantity));

	float fOurBoxSizeX = stf(rCharacter.Ship.BoxSize.x) / 2.0;

	bool bGrapplingProfessional = sti(rCharacter.TmpPerks.GrapplingProfessional);

	// max abordage parameters for our player
	float fOurGrapplingPerk = Ship_CalcGrapplingPerk(rCharacter);

	float fOurMaxAbordageDistance = Ship_CalcMaxAbordageDistance(fOurGrappling, fOurGrapplingPerk);
	float fOurMaxAbordageAngle = Ship_CalcMaxAbordageAngle(fOurGrappling); 
	float fOurMaxAbordageSpeed = Ship_CalcMaxAbordageSpeed(fOurGrappling);

	string sPlayerLocation = rCharacter.location;
	string sPlayerLocator = rCharacter.location.locator;

	// find island
	int iIslandIndex = FindIsland(sPlayerLocation);
	if (iIslandIndex >= 0)
	{
		rIsland = GetIslandByIndex(iIslandIndex);
	}

	aref aShips, aForts;
	makearef(aShips, arUpdate.Ships);
	makearef(aForts, arUpdate.Forts);

	// check forts for abordage
	int iFortsNum = GetAttributesNum(aForts);
	fBestDistance = 10000000.0;
	for (i=0; i<iFortsNum && iIslandIndex >= 0; i++)
	{
		aref aFort = GetAttributeN(aForts, i);
		iRelation = sti(aFort.relation);

		ref rFortCharacter = GetCharacter(sti(aFort.idx)); 
		if (LAi_IsDead(rFortCharacter)) { continue; }
		int iFortMode = sti(rFortCharacter.Fort.Mode);
		aref aRLoc = FindIslandReloadLocator(sPlayerLocation, rFortCharacter.location.locator);
		if (!CheckAttribute(aRLoc, "Radius")) { continue; }  // fix
		float fRadius = stf(aRLoc.Radius);
		fDistance = stf(aFort.Distance);
		if (iFortMode == FORT_HOLD_FIRE) iFortMode = FORT_NORMAL; // в контексте данной проверки одно и то же

		// Коррида -->
		if (fDistance < 5000 && pchar.location == "SentMartin" && CheckAttribute(pchar, "questTemp.Mtraxx.Ignasio.Check"))
		{
			DeleteAttribute(pchar, "questTemp.Mtraxx.Ignasio.Check");
			pchar.questTemp.Mtraxx.Ignasio.Fail = "true";
		}
		if (fDistance < 5000 && pchar.location == "SentMartin" && CheckAttribute(pchar, "questTemp.Mtraxx.Ignasio.Ship"))
		{
			Mtraxx_CorridaCheckPolacre();
		}
		if (fDistance < 1600 && fDistance > 800 && pchar.location == "SentMartin" && CheckAttribute(pchar, "questTemp.Mtraxx.Ignasio.Signal"))
		{
			pchar.questTemp.Mtraxx.Ignasio.Flag = "true";
		}
		if (fDistance > 1600 && pchar.location == "SentMartin" && CheckAttribute(pchar, "questTemp.Mtraxx.Ignasio.Signal") && CheckAttribute(pchar, "questTemp.Mtraxx.Ignasio.Flag"))
		{
			DeleteAttribute(pchar, "questTemp.Mtraxx.Ignasio.Flag");
		}
		if (fDistance < 800 && pchar.location == "SentMartin" && CheckAttribute(pchar, "questTemp.Mtraxx.Ignasio.Signal"))
		{
			DeleteAttribute(pchar, "questTemp.Mtraxx.Ignasio.Signal");
			DeleteAttribute(pchar, "questTemp.Mtraxx.Ignasio.Flag");
			RemoveItems(pchar, "wolfreeks_book", 1);
			AddQuestRecord("Roger_8", "13");
			Mtraxx_CorridaIgnasioFail();
		}
		// <-- Коррида

		switch (iFortMode)
		{
			case FORT_NORMAL:
				if (iRelation == RELATION_ENEMY)
				{
					if (fMinEnemyDistance > fDistance) { fortDistance = fDistance; }
				}
				else
				{
					// единоразовое узнавание врага
					// проверка на ложный флаг -->
					if (!CheckAttribute(rFortCharacter, "CheckFlagYet"))
					{
                        if (!CheckAttribute(rFortCharacter, "CheckFlagDate") || GetNpcQuestPastDayParam(rFortCharacter, "CheckFlagDate") > 1)
                        { // второй раз подряд уже не смотрим, на выход их порта
							if (fDistance < (MIN_ENEMY_DISTANCE_TO_DISABLE_MAP_ENTER_FORT * 1.5))
						    {
						        rFortCharacter.CheckFlagYet = true; // все, проверил
						        Ship_CheckFlagEnemy(rFortCharacter);
						        SaveCurrentNpcQuestDateParam(rFortCharacter, "CheckFlagDate");
						    }
					    }
					}
					// проверка на ложный флаг <--
				}
				// Jason НСО
				if (fDistance < 1000 && pchar.location == "SentMartin" && CheckAttribute(pchar, "questTemp.Patria.SanMartinFort") && ChangeCharacterHunterScore(pchar, "holhunter", 0) > 10)
				{
					bQuestDisableMapEnter = true;
					DoQuestFunctionDelay("Mtraxx_MarkusGameOver", 3.0);
				}
				if (fDistance < 400 && pchar.location == "SentMartin" && CheckAttribute(pchar, "questTemp.Patria.SanMartinFort"))
				{
					Patria_SanMartinFortAttack();
				}
				if (fDistance > 1500 && pchar.location == "Nevis" && CheckAttribute(pchar, "questTemp.Patria.Escape"))
				{
					DeleteAttribute(pchar, "questTemp.Patria.Escape");
					bQuestDisableMapEnter = false;
				}
			break;
			case FORT_DEAD:
                if (iRelation == RELATION_FRIEND) { continue; }
				if (fDistance > fRadius) { continue; }
				if (fBestDistance > fDistance)
				{
					fBestDistance = fDistance;

					bCanEnterToLand = true;

					sIslandID = rIsland.id;
					makearef(arIslandReload, rIsland.reload);
					sIslandLocator = aRLoc.GoAfterBoard.location;
				}
			break;
			case FORT_ABORDAGE:
                if (iRelation == RELATION_FRIEND) { continue; }
				if (iRelation == RELATION_ENEMY)
				{
					//if (fMinEnemyDistance > fDistance) { fMinEnemyDistance = fDistance; }
					if (fMinFortAbordDistance > fDistance) { fMinFortAbordDistance = fDistance; } //fix входа в порт
				}
				if (fDistance > fRadius) { continue; }
				if (!Character_IsAbordageEnable(rFortCharacter) || bDisableMapEnter)  { continue; } // bDisableMapEnter - значит враги рядом, нефиг брать форт под пушками кораблей boal
				if(CheckAttribute(pchar, "questTemp.SantaMisericordia") && CharacterIsAlive("SantaMisericordia_cap"))
				{
					ref sld = characterFromId("SantaMisericordia_cap");
					if(CheckAttribute(sld,"quest") && sld.quest == "InCity")
					{
						ref rSeaGroup = Group_GetGroupByID(GetGroupIDFromCharacter(sld));
						if(CheckAttribute(rSeaGroup,"location") && rSeaGroup.location == pchar.location)
							continue;
					}
				}
				if (fBestDistance > fDistance)
				{
					fBestDistance = fDistance;

					bAbordageFortCanBe = true;
					sAbordageLocator = rFortCharacter.location.locator;
					iAbordageFortEnemyCharacter = sti(rFortCharacter.index);
				}
			break;
		}
	}

	// check ships for abordage
	int iShipsNum = GetAttributesNum(aShips);
	fBestDistance = 10000000.0;
	for (i=0; i<iShipsNum; i++)
	{
		aref aShip = GetAttributeN(aShips, i);

		ref rShipCharacter = GetCharacter(sti(aShip.idx)); 
		fDistance = stf(aShip.Distance);		// distance between player ship and this ship
		iRelation = sti(aShip.relation);
		
		if (LAi_IsDead(rShipCharacter)) 
		{ 
			continue; 
		}
		if (iRelation != RELATION_ENEMY) 
		{ 
			continue; 
		}
		if (fMinEnemyDistance > fDistance) 
		{ 
			fMinEnemyDistance = fDistance; 
		}

		if (!Character_IsAbordageEnable(rShipCharacter)) 
		{ 
			continue; 
		}

		float fAng = stf(aShip.d_ay);						// it's dot.ay between ships
		float fRelativeSpeed = stf(aShip.RelativeSpeed);	// it's relative speed about player ship
		float fEnemyBoxSizeX = stf(rShipCharacter.Ship.BoxSize.x) / 2.0;

		bool bOurAngleTest = abs(fAng) > fOurMaxAbordageAngle && fRelativeSpeed < fOurMaxAbordageSpeed;
		float fAbordageDistance = fDistance - fEnemyBoxSizeX - fOurBoxSizeX;

		// test our ship with enemy
		if (bGrapplingProfessional || bOurAngleTest)
		{
			if (fAbordageDistance < fOurMaxAbordageDistance && fBestDistance > fDistance)
			{
				// abordage enable
				fBestDistance = fDistance;
				bAbordageShipCanBe = true;
				iAbordageShipEnemyCharacter = sti(rShipCharacter.index);
			}
		}
		
		//bool MementoDisableBoarding = rShipCharacter.id == "Memento_cap" && GetHullPercent(rShipCharacter) > 30.0;
		//if(MementoDisableBoarding) bAbordageShipCanBe = false;
		
		// test enemy ship with our
		float fEnemyGrappling = stf(rShipCharacter.TmpSkill.Grappling);

		// max abordage parameters for our player
		float fEnemyGrapplingPerk = Ship_CalcGrapplingPerk(rShipCharacter);

		float fEnemyMaxAbordageDistance = Ship_CalcMaxAbordageDistance(fEnemyGrappling, fEnemyGrapplingPerk);
		float fEnemyMaxAbordageAngle = Ship_CalcMaxAbordageAngle(fEnemyGrappling); 
		float fEnemyMaxAbordageSpeed = Ship_CalcMaxAbordageSpeed(fEnemyGrappling);

		bool bEnemyAngleTest = abs(fAng) > fEnemyMaxAbordageAngle && fRelativeSpeed < fEnemyMaxAbordageSpeed;
		if (bEnemyAngleTest)
		{
			if (fAbordageDistance < fEnemyMaxAbordageDistance)
			{
				// maybe other character want abordage us?
				fEnemyGrappling = stf(rCharacter.TmpSkill.Grappling); 
				float fEnemyCrewFencing = (0.1 + fEnemyGrappling * stf(rShipCharacter.Ship.Crew.Quantity));
				float fRatio = fEnemyCrewFencing / fOurCrewFencing;
				if (sti(rShipCharacter.nation) == PIRATE) 
				{ 
					fRatio = fRatio * 1.6; 
				}
				
				//if(MementoDisableBoarding) continue;
				
				if (fRatio > 1.2 && !CheckAttribute(rShipCharacter, "Abordage.MakeDisable")) // Jason НСО
				{
					iAbordageStartNowCharacter = sti(rShipCharacter.index);
					bAbordageStartNow = true;
					break;
				}
			}
		}
	}

	float r, x1, z1;
	string sLocatorName;

	// check reload to locations possibility
	if (iIslandIndex >= 0 && fMinEnemyDistance > MIN_ENEMY_DISTANCE_TO_DISABLE_ENTER_2_LOCATION)
	{
		if (Island_isReloadEnableGlobal(sPlayerLocation))
		{
			aref arReload;
			makearef(arReload, rIsland.Reload);

			int iNumLocators = GetAttributesNum(arReload);
			for (int j=0; j<iNumLocators; j++)
			{
				aref arLocator;
				arLocator = GetAttributeN(arReload, j);
				sLocatorName = GetAttributeName(arLocator);
				if (Island_isReloadFort(sPlayerLocation, arLocator.name)) { continue; }
				if (!Island_isReloadEnableLocal(sPlayerLocation, arLocator.name)) { continue; }
				if(!CheckAttribute(rIsland, "reload." + sLocatorName + ".x") || !CheckAttribute(rIsland, "reload." + sLocatorName + ".z"))
				{
					continue;
				}

				x1 = stf(rIsland.reload.(sLocatorName).x);
				z1 = stf(rIsland.reload.(sLocatorName).z);
				/*if (checkAttribute(rIsland, "reload."+sLocatorName+".wdmisland"))
				{
					wdmCurrentIsland = rIsland.reload.(sLocatorName).wdmisland;
				}*/
				r = stf(rIsland.reload.(sLocatorName).radius);
				if (sqrt(sqr(x1 - x) + sqr(z1 - z)) < r)
				{
					bCanEnterToLand = true;
					sIslandID = rIsland.id;
					makearef(arIslandReload, rIsland.reload);
					sIslandLocator = rIsland.reload.(sLocatorName).name;

					// LDH 24Jan17 - display mooring location name -->
					makearef(arMoorLoc, rIsland.reload.(sLocatorName));
					string MoorName = GetLocatorName(arMoorLoc);
					if (!CheckAttribute(pchar, "MoorName")) pchar.MoorName = " ";
					if (MoorName != pchar.MoorName)
                    {
						// LDH 14Feb17 rewrite
						// LDH 26Jan17 - play anchor sound if moor location changes due to overlapping locations
						if (pchar.MoorName != " " && MoorName != " ")
						{
							boal_soundOn = false;		// make sure it's only played once
							PlaySound("interface\_Yakordrop.wav");
						}
						pchar.MoorName = MoorName;
                    }
					// LDH 24Jan17 <--

					break;
				}
			}

			// LDH 12Feb17 display moor name in battle interface -->
			// If we don't do this, location does not update
			BattleInterface.textinfo.Location.text = GetBILocationName();
			// LDH 12Feb17 <--
		}
	}
	else
	{
		// LDH 13Feb17 display region name in battle interface -->
		pchar.Moorname = " ";
		// If we don't do this, location does not update
		BattleInterface.textinfo.Location.text = GetBILocationName();
		// LDH 13Feb17 <--
	}

	// disable any abordage if storm
	if (Whr_IsStorm() && !CheckAttribute(pchar, "GenQuest.AbordageInStorm"))
	{
		bAbordageStartNow = false;
		bAbordageFortCanBe = false;
		bAbordageShipCanBe = false;
	}

	// Enter 2 map enable/disable
	// Peoples on ship mode update
	int iPrevShipPOSMode = sti(rCharacter.Ship.POS.Mode);
	rCharacter.Ship.POS.Mode = SHIP_SAIL;

	bDisableMapEnter = false;
	if (fMinEnemyDistance < MIN_ENEMY_DISTANCE_TO_DISABLE_MAP_ENTER)
	{
		bCanEnterToLand = false;
		bDisableMapEnter = true;

		rCharacter.Ship.POS.Mode = SHIP_WAR;
	}
	if (fortDistance < MIN_ENEMY_DISTANCE_TO_DISABLE_MAP_ENTER_FORT)
	{
		bCanEnterToLand = false;
		bDisableMapEnter = true;
		rCharacter.Ship.POS.Mode = SHIP_WAR;
	}
    // boal fix входа в порт -->
    if (fMinFortAbordDistance < MIN_ENEMY_DISTANCE_TO_DISABLE_ENTER_2_LOCATION)
    {
        bCanEnterToLand = false;
    }
    // boal <--
	if (iStormLockSeconds)
	{
		bDisableMapEnter = true;
		bCanEnterToLand = false;
		bDisableSailTo = true;

		rCharacter.Ship.POS.Mode = SHIP_STORM;
	}

	// new music
    oldSeaAlarmed = seaAlarmed;
	bool bMakeCurrentUpdate = bUpdatePosMode;
	if (iVicSoundTime<=0 && sti(rCharacter.Ship.POS.Mode) != iPrevShipPOSMode) {
		bMakeCurrentUpdate = true;
	}
	if (bMakeCurrentUpdate)
	{
		switch (sti(rCharacter.Ship.POS.Mode))
		{
			case SHIP_SAIL:
				if (!Whr_IsStorm()) 
				{ 
					seaAlarmed = false;
                    if (oldSeaAlarmed != seaAlarmed)
                        UpdateSailorsChatter();
					if (iPrevShipPOSMode == SHIP_WAR)
					{
                   		Ship_PlayVictory("music_ship_victory", 8500);
						//PlayStereoOGG("music_ship_victory");
					} // fix boal
					FadeOutMusic(3);
					//PlayStereoOGG(sSeaStartMusicName); 
					if (Whr_IsDay()) SetMusic("music_sea_day");
					else SetMusic("music_sea_night");
				}
				else
				{ 
					FadeOutMusic(3); //fix
					PlayStereoOGG("music_End_storm"); 
				}
			break;
			case SHIP_WAR:
				FadeOutMusic(3); // fix
				//PlayStereoOGG("music_sea_battle"); 
				seaAlarmed = true;
                if (oldSeaAlarmed != seaAlarmed)
                    UpdateSailorsChatter();
				string ClassicSoundScene = "";
				if(CheckAttribute(&InterfaceStates,"ClassicSoundScene") && sti(InterfaceStates.ClassicSoundScene) > 0) ClassicSoundScene = "classic_";
				if(bGlobalTutor)
				{
					SetMusic("music_q_Seabattle");
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Memento.AttackFromMap"))
				{
					SetMusic("music_Memento");
					break;
				}
				if(CheckAttribute(pchar, "questTemp.SantaMisericordia.AttackFromMap"))
					SetMusic(ClassicSoundScene+"SantaMisericordia");
				else
					SetMusic(ClassicSoundScene+"music_sea_battle");
			break;
		}
		ControlsDesc();
		BI_ShowExtInfo();
		bUpdatePosMode = false;
	}

	// if quest disable enter 2 map
	if (bQuestDisableMapEnter) { bDisableMapEnter = true; }

	// Start abordage automatically
	if (bAbordageStartNow) 
	{ 
		ref rTargetCharacter = GetCharacter(iAbordageStartNowCharacter);
		if(GetRelation(sti(rCharacter.index), iAbordageStartNowCharacter) == RELATION_ENEMY)
		{
			if(LAi_IsDead(rCharacter) == false && LAi_IsDead(rTargetCharacter) == false)
			{
				iAbordageShipEnemyCharacter = iAbordageStartNowCharacter;
				Sea_AbordageLoad(SHIP_ABORDAGE, false); 
			}
		}
	}
	
	// mitrokosta проверка на близость ле франсуа
	if (iIslandIndex >= 0 && CheckAttribute(pchar, "questTemp.Rum.Tip2")) {
		r = stf(rIsland.EffectRadius);
		sLocatorName = pchar.questTemp.Rum.Tip2.Reload;

		x1 = stf(rIsland.reload.(sLocatorName).x);
		z1 = stf(rIsland.reload.(sLocatorName).z);
		
		if (sqr(x1 - x) + sqr(z1 - z) < sqr(r)) {
			DeleteAttribute(pchar, "questTemp.Rum.Tip2");
			NewGameTip(XI_ConvertString("RumTip21"));
			NewGameTip(XI_ConvertString("RumTip22"));
		}
	}
}

void Ship_OnStrandNext()
{
	ref	rCharacter = GetCharacter(GetEventData());
	if (LAi_IsDead(rCharacter)) { return; }

	bool bOnStrand = sti(rCharacter.Ship.Strand);
	if (!bOnStrand) 
	{ 
		int iSoundID = sti(rCharacter.Ship.Strand.SndID);
		if (iSoundID != 0) { StopSound(sti(rCharacter.Ship.Strand.SndID), 3000); }
		rCharacter.Ship.Strand.SndID = SOUND_INVALID_ID;
		return; 
	}
	if (!CheckAttribute(rCharacter, "AlwaysSandbankManeuver"))  //boal
	{
		float fCurrentSpeedZ = stf(rCharacter.Ship.Speed.z);
		float fHP = 4.0 * fCurrentSpeedZ / 7.0;
		Ship_ApplyHullHitpoints(rCharacter, fHP, KILL_BY_ISLAND, -1);
	}
	PostEvent(SHIP_TO_STRAND_NEXT, 100 + rand(100), "l", sti(rCharacter.index));
}

void Ship_OnStrand()
{
	ref rCharacter = GetCharacter(GetEventData());
	bool bNewStrand = GetEventData();
	
	bool bPrevStrand = sti(rCharacter.Ship.Strand);

	rCharacter.Ship.Strand = bNewStrand;

	float x = stf(rCharacter.Ship.Pos.x);
	float y = stf(rCharacter.Ship.Pos.y);
	float z = stf(rCharacter.Ship.Pos.z);

	if (bPrevStrand == 0 && bNewStrand == 1)
	{
		PostEvent(SHIP_TO_STRAND_NEXT, 100, "l", sti(rCharacter.index));
		rCharacter.Ship.Strand.SndID = Play3DSoundComplex("ship_aground", x, y, z, true, false);
	}
}

// Small boom
void Ship_DetonateSmall()
{
	ref  rCharacter = GetCharacter(GetEventData());
	aref arCharShip; makearef(arCharShip, rCharacter.Ship);

    if (bAbordageStarted) return;
	if (sti(InterfaceStates.Launched)) return;
	
	float x = stf(arCharShip.Pos.x);
	float y = stf(arCharShip.Pos.y);
	float z = stf(arCharShip.Pos.z);
	
	if (y > -3.0)
	{
		int iSClass = GetCharacterShipClass(rCharacter);
		PostEvent(SHIP_DETONATE_SMALL, 200 + iSClass * 300 + rand(900), "l", sti(rCharacter.index));
	}

	float bx = arCharShip.BoxSize.x;
	float by = arCharShip.BoxSize.y;
	float bz = arCharShip.BoxSize.z;

	float fCos = cos(stf(arCharShip.Ang.y));
	float fSin = sin(stf(arCharShip.Ang.y));

	//for (int i=0; i < 1 + rand(1); i++)
	//{
		float x1, y1, z1;
		x1 = (frnd() - 0.5) * bx;
		z1 = (frnd() - 0.5) * bz;

		RotateAroundY(&x1, &z1, fCos, fSin);

		y1 = 1.0 + y + frnd() * 3.0;
		Ship_Serious_Boom(x1 + x, y1, z1 + z);
		CreateParticleSystem("blast", x1 + x, y1, z1 + z, 0.0, 0.0, 0.0, 0);
	//}
}

void Ship_Turn180(ref rCharacter)
{
	//rCharacter.TmpPerks.Turn = true;
	//rCharacter.TmpPerks.Turn.Angle = PI;
	rCharacter.Tmp.SpeedRecall = 0; // чтоб пересчитался маневр
}

// Big Boom on ship
void Ship_Detonate(ref rCharacter, bool bMakeSmallBoom, bool bMakeDead)
{
	if (!CheckAttribute(rCharacter, "Ship.Pos.x")) 
	{
		Trace("Ship_Detonate: Can't find Ship.Pos in character with id: " + rCharacter.id);
		return;
	}
	aref	arCharShip; makearef(arCharShip, rCharacter.Ship);
	
	float x = stf(arCharShip.Pos.x);
	float y = stf(arCharShip.Pos.y);
	float z = stf(arCharShip.Pos.z);

	int iMinBoom = MakeInt(Bring2Range(6.0, 2.0, 1.0, 7.0, stf(GetCharacterShipClass(rCharacter))));

	float bx = arCharShip.BoxSize.x;
	float by = arCharShip.BoxSize.y;
	float bz = arCharShip.BoxSize.z;

	float fCos = cos(stf(arCharShip.Ang.y));
	float fSin = sin(stf(arCharShip.Ang.y));

	bool isBoomAlready = false;
	int iMax = iMinBoom + rand(2); //fix
	for (int i=0; i<iMax; i++)
	{
		float x1, y1, z1;
		x1 = (frnd() - 0.5) * bx;
		z1 = (frnd() - 0.5) * bz;

		RotateAroundY(&x1, &z1, fCos, fSin);
		
		y1 = 1.0 + y + frnd() * 3.0;
		if(isBoomAlready == false)
		{
			Ship_Serious_Boom(x1 + x, y1, z1 + z);
		}
		isBoomAlready = true;
		CreateParticleSystem("blast_inv", x1 + x, y1, z1 + z, 0.0, 0.0, 0.0, 0);
	}
	if (bMakeDead) ShipDead(sti(rCharacter.Index), KILL_BY_SPY, -1);

	if (bMakeSmallBoom) PostEvent(SHIP_DETONATE_SMALL, 600 + rand(1000), "l", sti(rCharacter.index));
}

float AIShip_isPerksUse(string sPerk, float fOff, float fOn)
{
	if (sti(sPerk)) { return fOn; }
	return fOff;
}

// EVENT, calculate dynamic parameters for ship, one per second
void Ship_UpdateParameters()
{
	int		iCharacterIndex = GetEventData();
	ref		rCharacter = GetCharacter(iCharacterIndex);
	float	fSailState = GetEventData();
	bool	bDead = LAi_IsDead(rCharacter);
	
	if(int(rCharacter.ship.type) == SHIP_NOTUSED || bDead)
		return;

	aref	arTmpPerks;
	makearef(arTmpPerks, rCharacter.TmpPerks);
	Ship_UpdateTmpSkills(rCharacter);	// update temporary skill storage
	Cannon_RecalculateParameters(int(rCharacter.index));

	aref arCharShip;
	makearef(arCharShip, rCharacter.Ship);
	ref rShip = GetRealShip(int(arCharShip.Type));
	float fShipAngle = float(arCharShip.Ang.y);

	//if(bEnableIslandSailTo)
	/*if(pchar.Ship.POS.Mode == SHIP_WAR)
	{
		//log_info("Боевой");
		if(stf(rCharacter.ship.sp) >= 50.0)
		{
			if (iArcadeSails == 1) arCharShip.ArcadeSpeed = 2.0*2.5;
			else arCharShip.ArcadeSpeed = 2.0;
		}
		else
		{
			if(CheckAttribute(arCharShip,"ArcadeSpeed")) DeleteAttribute(arCharShip,"ArcadeSpeed");
		}
	}
	else
	{
		//log_info("Мирный");
		if (iArcadeSails == 1) arCharShip.ArcadeSpeed = 5.0*2.5;
		else arCharShip.ArcadeSpeed = 5.0;
	}*/

    // TUTOR-ВСТАВКА
    if(TW_IsActive() && objTask.sea == "1_Turn") // && IsMainCharacter(rCharacter) 
    {
        if(!CheckAttribute(&TEV, "Tutor.BackAY"))
            TEV.Tutor.BackAY = fShipAngle;
        else
        {
            float fTutorTurn = abs(float(TEV.Tutor.BackAY) - fShipAngle) * 2.0;
            if(TW_IncreasePercents("sea", "turn_text", fTutorTurn))
                TW_FinishSea_1_Turn();
            else TEV.Tutor.BackAY = fShipAngle;
        }
    }
	
	float fShipSpeed, fShipTurnRate;
	bool bGDMode = ("GameDesignerMode" in &TEV);

	// кэш оптимизация
	if (!CheckAttribute(rCharacter, "Tmp.SpeedRecall") || int(rCharacter.Tmp.SpeedRecall) <= 0)
	{
		fShipSpeed = !bGDMode ? FindShipSpeed(rCharacter) : float(rShip.SpeedRate);			
		fShipTurnRate = FindShipTurnRate(rCharacter);
		rCharacter.Tmp.SpeedRecall   = 8 + rand(5);
		rCharacter.Tmp.fShipSpeed    = fShipSpeed;
		rCharacter.Tmp.fShipTurnRate = fShipTurnRate;
	}
	else
	{
		fShipSpeed    = float(rCharacter.Tmp.fShipSpeed);
		fShipTurnRate = float(rCharacter.Tmp.fShipTurnRate);
		rCharacter.Tmp.SpeedRecall   = int(rCharacter.Tmp.SpeedRecall) - 1;
	}
    
	float fWindSpeed = !bGDMode ? Whr_GetWindSpeed() : WIND_MAX_POWER;
	float fWindPower = fWindSpeed / WIND_MAX_POWER; // ~!~
	fShipSpeed *= fWindPower;
	float fWindAngle = Whr_GetWindAngle();
	float fWindShipAngle = fWindAngle - fShipAngle;
	while(fWindShipAngle < -PI)
		fWindShipAngle += 2*PI;
	while(fWindShipAngle > PI)
		fWindShipAngle -= 2*PI;
	if(fWindShipAngle < 0.0)
		fWindShipAngle = -fWindShipAngle;
	Sea_ApplyMaxSpeedZ(rCharacter, fWindShipAngle, &fShipSpeed);
	
	if(CheckAttribute(rCharacter, "cheats.ArcadeSailing"))
		arCharShip.MaxSpeedZ = FindShipSpeed(rCharacter) * fWindPower;
	
	if (iArcadeSails == 1)	// Apply arcade mode
	{
		arCharShip.MaxSpeedZ = (2.5 * float(arCharShip.MaxSpeedZ));
		arCharShip.MaxSpeedY = (2.0 * float(arCharShip.MaxSpeedY));
	}
	
	float fMaxSpeedY = float(rShip.TurnRate) / TURN_RATE_MAGIC_NUMBER; //boal
	float fTRFromSailState = 1.0;
	switch (MakeInt(fSailState * 2.0))
	{
		case 0: fTRFromSailState = 0.05; break;
		case 1: fTRFromSailState = 1.0; break;
		case 2: fTRFromSailState = 0.68; break;
	}
	// зависимость от скорости на маневр
    float fTRFromSpeed = 1.0;
    float fCurrentSpeedZ = float(rCharacter.Ship.Speed.z);
	if (iCharacterIndex == GetMainCharacterIndex())
	{
        if (MOD_SKILL_ENEMY_RATE > 2) // халява и юнга - послабление)
			fTRFromSpeed = 1.0 - 0.68 * (1.0 - Clampf(fCurrentSpeedZ / fShipSpeed));
	}
	else
		fTRFromSpeed = 1.0 - (0.69 - MOD_SKILL_ENEMY_RATE*0.01) * (1.0 - Clampf(fCurrentSpeedZ / fShipSpeed));
	float fTRFromSailDamage = Bring2Range(0.01, 1.0, 0.1, 100.0, float(arCharShip.sp));
	float fTRResult = fMaxSpeedY * fShipTurnRate * fTRFromSailState * fTRFromSpeed * fTRFromSailDamage;

	fTRResult = Bring2Range(0.004, 0.95, 0.00001, 1.0, fTRResult);
	arCharShip.MaxSpeedY =	fTRResult;
	
	// calculate immersion
	float fLoad = Clampf(GetCargoLoad(rCharacter) / float(rShip.Capacity));
	float baseImmersion = float(rShip.SubSeaDependWeight) * fLoad; // это уровень погружения от веса
	float fBaseShipHP = float(rShip.HP);
	float fCurHP = float(arCharShip.HP);
	float resultImmersion = GetShipBreachedImmersion(rCharacter, &arCharShip, baseImmersion, fCurHP, fBaseShipHP);
	arCharShip.Immersion = resultImmersion;
	
	if(fBaseShipHP < fCurHP)
		fBaseShipHP = fCurHP;
	if (bSeaActive && (fCurHP / fBaseShipHP < 0.09999))	// do damage if ship hull < 10%, sinking
	{
        float fLightRepair = AIShip_isPerksUse(arTmpPerks.LightRepair, 1.0, 0.0);
        // это спец атрибут по убиванию этой функции
        if (CheckAttribute(rCharacter, "SinkTenPercent") && !sti(rCharacter.SinkTenPercent))
			fLightRepair = 0.0;
		float fSinkDamage = fLightRepair * (fBaseShipHP / 100.0) * 0.08;
		if (CheckAttribute(rCharacter, "Ship.LastBallCharacter"))
			Ship_ApplyHullHitpoints(rCharacter, fSinkDamage, KILL_BY_BALL, sti(rCharacter.Ship.LastBallCharacter));
		else
			Ship_ApplyHullHitpoints(rCharacter, fSinkDamage, KILL_BY_TOUCH, -1);
		/*if(!CheckAttribute(rCharacter, "ship.flow")) // to_do
		{
			rCharacter.ship.flow = 0;
		}
		rCharacter.ship.flow = sti(rCharacter.ship.flow) + 1;	*/
		if (iCharacterIndex == nMainCharacterIndex) 
		{ 
			if(!IsPerkIntoList("sink"))
        	{
				if (rand(1) == 0)
					PlaySound("interface\" + LanguageGetLanguage() + "\_Abandon1.wav");
				else
					PlaySound("interface\" + LanguageGetLanguage() + "\_Abandon2.wav");
			}
			AddPerkToActiveList("sink"); 
		}
	}
	else if (iCharacterIndex == nMainCharacterIndex)
		DelPerkFromActiveList("sink");
	
	float fBaseSailHP = float(rShip.SP);
	float fWindDotShip = GetDotProduct(fWindAngle, fShipAngle);		// Wind.ay | Ship.ay

	if (bStorm && bSeaActive)	// do damage if storm or tornado
	{
		int shipClass = GetCharacterShipClass(rCharacter);
		float tickValue = pow(1 - (iStormLockSeconds / 90.0), 0.65); // зависимость от времени в шторме, от 0 к 1
		float hullPercent = 0.0120 - 0.0117 * tickValue;
		float sailsPercentPoints = 1.0 - 0.97 * tickValue;
		float classDamageMtp = shipClass > 5 ? 0.15 : 0.0; // бонус малым классам

		// Общие модификаторы урона от шторма
		float damageMtp = isEquippedArtefactUse(rCharacter, "talisman2", 1.0, 0.2);
		damageMtp += SZN_GetModifierMtp(M_STORM_DAMAGE_MTP, 0.0);

		float sailsStateMtp = 0.0;
		switch (fSailState)
		{
			case 0.0: sailsStateMtp = 0.85; break; // спущены
			case 0.5: sailsStateMtp = 0.45; break; // боевое положение
		}
		Ship_ApplyHullHitpoints(rCharacter, fBaseShipHP * hullPercent * func_fmax(0.01, damageMtp - classDamageMtp), KILL_BY_TOUCH, -1);
		MakeSailDmg(iCharacterIndex, sailsPercentPoints * func_fmax(0.01, damageMtp - sailsStateMtp));

		float fExp = 88 * hullPercent * (1.0+sailsStateMtp); // опыт начисляем по проценту урона корпусу с бонусом, если опустил паруса
		if (!bDead && IsCompanion(rCharacter) && tickValue < 1.0)
		{
			AddCharacterExpToSkill(rCharacter, "Sailing", fExp);
			ChangeCrewExp(rCharacter, "Sailors", 0.5);
		}
		// rotate impulse
		float fRotate = fClamp(-0.01, 0.01, float(rCharacter.Ship.Tornado.Rotate.y) + (frnd() * 0.08 - 0.04));  //fix boal
		rCharacter.Ship.Tornado.Rotate.y = fRotate;  //fix boal
		arCharShip.Impulse.Rotate.y = fRotate;
	}

	if (bTornado && bSeaActive)
	{
		float fTornadoDistance = GetDistance2D(float(Tornado.x), float(Tornado.z), float(arCharShip.Pos.x), float(arCharShip.Pos.z));
		float fTornadoDamageMultiply = Bring2Range(1.0, 0.0, 0.0, 100.0, fTornadoDistance) * isEquippedArtefactUse(rCharacter, "talisman2", 1.0, 0.2);
		Ship_ApplyHullHitpoints(rCharacter, fTornadoDamageMultiply * (fBaseShipHP / 100.0) * 8.5, KILL_BY_TOUCH, -1);	// hull damage
		switch (MakeInt(fSailState * 2.0))	// sails damage
		{
			case 0: 
				MakeSailDmg(iCharacterIndex, fTornadoDamageMultiply * (fBaseSailHP / 100.0) * 1.5);
			break;
			case 1: 
				MakeSailDmg(iCharacterIndex, fTornadoDamageMultiply * (fBaseSailHP / 100.0) * 4.5); 
			break;
			case 2: 
				MakeSailDmg(iCharacterIndex, fTornadoDamageMultiply * (fBaseSailHP / 100.0) * 8.5); 
			break;
		}
	}

	if (CheckAttribute(rCharacter, "Ship.Cargo.RecalculateCargoLoad") && int(rCharacter.Ship.Cargo.RecalculateCargoLoad))	// Recalculate Cargo Load if need
	{
		if (rand(5) == 1)  // оптимизация, сильные тормоза
		{
			RecalculateCargoLoad(rCharacter);
			rCharacter.Ship.Cargo.RecalculateCargoLoad = 0;
		}
	}
	
	// start random sounds :: SHIPS
    if (rand(2) == 1)
    {
        Ship_PlaySoundEvent(rCharacter, "ShipEMB/Creak_Rigging", frnd() * 1.2 - 0.6, 0.0, frnd() * 1.6 - 0.8);
        //Ship_PlaySound3DComplex(rCharacter, "squeak_sea" + sSeaSoundPostfix, 0.9, frnd() * 1.2 - 0.6, 0.0, frnd() * 1.6 - 0.8);
    }
	// start random sounds :: SAILS TO_DO ~!~
    /*if (rand(40) <= fSailState * 5.0)
    {
        Ship_PlaySound3DComplex(rCharacter, "sails_ambient", fSailState * 0.5, 0.0, 0.0, 0.5 + frnd() * 0.0);
    }*/
	
	if (!bSeaLoaded || !CheckAttribute(rCharacter, "SeaAI.Task.Target"))
		return;
	if(int(rCharacter.SeaAI.Task.Target) <= 0)
		return;
	ref rTargetCharacter = GetCharacter(int(rCharacter.SeaAI.Task.Target));
	bool bSkipTarget = false;
	if(!CheckAttribute(rTargetCharacter, "location") || rTargetCharacter.location == "none" || rTargetCharacter.location != rCharacter.location)
		bSkipTarget = true;
	if (bSkipTarget)
		return;
	float fDistance = Ship_GetDistance2D(rCharacter, rTargetCharacter);
	float fEnemyLeadership = stf(rTargetCharacter.TmpSkill.Leadership); 
	float fEnemyGrappling = stf(rTargetCharacter.TmpSkill.Grappling); // ~!~
	float fEnemyCrewFencing = (0.1 + fEnemyLeadership + fEnemyGrappling * stf(rCharacter.Ship.Crew.Quantity));
	float fOurLeadership = stf(rCharacter.TmpSkill.Leadership); 
	float fOurGrappling = stf(rCharacter.TmpSkill.Grappling);
	float fOurCrewFencing = (0.1 + fOurLeadership + fOurGrappling * stf(rTargetCharacter.Ship.Crew.Quantity));
	float fRatio = fEnemyCrewFencing / fOurCrewFencing;
	if (int(rCharacter.nation) == PIRATE)
		fRatio = fRatio * 1.6; 
	if (int(rCharacter.rank) > int(rTargetCharacter.rank))
		fRatio = fRatio * 1.2; 
	
	if (fRatio > 1.2 && CheckAttribute(rCharacter, "Tmp.fShipSpeed") && CheckAttribute(rTargetCharacter, "Tmp.fShipSpeed") && stf(rCharacter.Tmp.fShipSpeed) > (stf(rTargetCharacter.Tmp.fShipSpeed) / 1.5))
	{
		if(GetRelation(int(rCharacter.index), int(rTargetCharacter.index)) == RELATION_ENEMY)
		{
			Ship_SetTaskAbordage(SECONDARY_TASK, int(rCharacter.index), int(rTargetCharacter.index)); // fix PRIMARY_TASK
			rCharacter.Ship_SetTaskAbordage = true; // запомним, чтоб не сбивать
		}
	}
	else
		DeleteAttribute(rCharacter, "Ship_SetTaskAbordage");

	if (int(rCharacter.SeaAI.Task) == AITASK_RUNAWAY)
	{
		/*Ship_SetSailState(sti(rCharacter.index), 1);

		//проверяем дистанцию и дальность стрельбы орудий противника
		//проверяем нашу скорость и скорость противника
		//делаем чек на лидершип
		//проверяем мораль команды
		//если набираем 2 или больше очков - выкидываем груз за борт.
		//выключаем фонари.
		Ship_SetLightsOff(rCharacter, 15.0, true, true, false);

		ref rCannon = GetCannonByType(sti(rTargetCharacter.Ship.Cannons.Type));
		float TargetRange = stf(rCannon.FireRange);
		int isDropGoods = 0;

		if(fDistance <= TargetRange)
		{
			isDropGoods = isDropGoods + 1;
		}
		
		float fOurSpeed = FindShipSpeed(rCharacter);
		float fEnemySpeed = FindShipSpeed(rTargetCharacter);

		if(fOurSpeed <= fEnemySpeed)
		{
			isDropGoods = isDropGoods + 1;
		}

		if(fOurLeadership < rand(12))
		{
			isDropGoods = isDropGoods + 1;
		}

		float fOurMorale = GetCharacterCrewMorale(rCharacter);
		if(fOurMorale < rand(99))
		{
			isDropGoods = isDropGoods + 1;
		}

		if(isDropGoods > 2)
		*/
		// бешенная оптимизация, если кто-то убегает -->
		Ship_SetSailState(int(rCharacter.index), 1);  // to_do нужно проверять, может довольно одного раза или в ядре будет дурить
		if (int(rCharacter.Ship.Lights) == 1)
			Ship_SetLightsOff(rCharacter, 15.0, true, true, false);
		if (int(rCharacter.Ship.SP) > 50 && rand(100) > 80)  // не выкидывать, если не убежать, а то нет смысла брать приз
			PostEvent(SHIP_DROP_GOOD, 1000, "a", rCharacter);
		if (int(rCharacter.Ship.SP) < 60 && GetCargoGoods(rCharacter, GOOD_POWDER) >= MINE_POWDER*2 && rand(39) == 5)	// сброс мины
			SetMineFree(rCharacter, 1); 
		// бешенная оптимизация, если кто-то убегает <--
		return;
	}

	if (int(rCharacter.SeaAI.Task) != AITASK_ABORDAGE)
		return;
	if (GetRelation(int(rCharacter.index), int(rTargetCharacter.index)) != RELATION_ENEMY)
		return;
	if(LAi_IsDead(rCharacter) || LAi_IsDead(rTargetCharacter))
		return;
	if (int(rTargetCharacter.index) != nMainCharacterIndex)
		return;
	float fCharacterGrappling = stf(rCharacter.TmpSkill.Grappling);
	float fCharacterGrapplingPerk  = Ship_CalcGrapplingPerk(rCharacter);
	float fCharacterDistance = Ship_CalcMaxAbordageDistance(fCharacterGrappling, fCharacterGrapplingPerk);
	float fCharacterAngle = Ship_CalcMaxAbordageAngle(fCharacterGrappling);
	float fCharacterSpeed = Ship_CalcMaxAbordageSpeed(fCharacterGrappling);

	float fAng = 0.0;
	float fRelativeSpeed = stf(arCharShip.Speed.z);

	aref	arUpdate;
	makearef(arUpdate, rCharacter.SeaAI.Update);
	aref aShips;
	makearef(aShips, arUpdate.Ships);
	int iShipsNum = GetAttributesNum(aShips);
	for (int i=0; i<iShipsNum; i++)
	{
		aref aShip = GetAttributeN(aShips, i);
		ref rShipCharacter = GetCharacter(int(aShip.idx)); 
		if(rShipCharacter.id == rTargetCharacter.id)
		{
			fRelativeSpeed = stf(aShip.RelativeSpeed);
			fAng = stf(aShip.d_ay);
		}
	}
	float fEnemyBoxSizeX = stf(rTargetCharacter.Ship.BoxSize.x) / 2.0;
	float fCharacterBoxSizeX = stf(rCharacter.Ship.BoxSize.x) / 2.0;
	float fAbordageDistance = fDistance - fEnemyBoxSizeX - fCharacterBoxSizeX;

	if (fAbordageDistance >= fCharacterDistance || fAng >= fCharacterAngle || fRelativeSpeed >= fCharacterSpeed)
		return;
	if (fRatio > 1.1)
	{
		iAbordageShipEnemyCharacter = int(rCharacter.index);
		Sea_AbordageLoad(SHIP_ABORDAGE, false);
	}
	else
	{
		if (stf(rCharacter.ship.hp) > float(rTargetCharacter.ship.hp) * 0.5 ||
            GetCrewQuantity(rCharacter) > GetCrewQuantity(rTargetCharacter))
        {
			Ship_SetTaskAttack(SECONDARY_TASK, int(rCharacter.index), int(rTargetCharacter.index));
		}
        else
        {
			Ship_SetTaskRunaway(SECONDARY_TASK, int(rCharacter.index), int(rCharacter.SeaAI.Task.Target));
        }
    }
}

void Ship_PrintExp(int iExp)
{
	if (iExp <= 0) { return; }

	object oRes;
	string sExpQuantity = iExp;
	string sExpString = GetSimpleSeaSectionKey("sea_exp_add");

	Event(PARSE_STRING, "asls", &oRes, sExpString, 1, sExpQuantity);

	Log_SetStringToLog(oRes.Str);
}

void Ship_TornadoDamage()
{
	float fTime = GetEventData();
	
	Tornado.x = GetEventData();
	Tornado.z = GetEventData();
}

void Ship_UpdateTmpSkills(ref rCharacter)
{
	///// с оптимизацией
	if (!CheckAttribute(rCharacter, "TmpSkillRecall") || sti(rCharacter.TmpSkillRecall) <= 0)
    {
        rCharacter.TmpSkill = "";

    	aref aTmpSkill; makearef(aTmpSkill, rCharacter.TmpSkill);

    	// calc skills for speed optimization
    	//aTmpSkill.Commerce = MakeFloat(GetSummonSkillFromName(rCharacter, SKILL_COMMERCE)) / SKILL_MAX;
    	aTmpSkill.Leadership = MakeFloat(GetSummonSkillFromName(rCharacter, SKILL_LEADERSHIP)) / SKILL_MAX;
    	aTmpSkill.Sneak     = MakeFloat(GetSummonSkillFromName(rCharacter, SKILL_SNEAK)) / SKILL_MAX;
    	aTmpSkill.Defence   = MakeFloat(GetSummonSkillFromName(rCharacter, SKILL_DEFENCE)) / SKILL_MAX;
    	aTmpSkill.Grappling = MakeFloat(GetSummonSkillFromName(rCharacter, SKILL_GRAPPLING)) / SKILL_MAX;
    	aTmpSkill.Sailing   = MakeFloat(GetSummonSkillFromName(rCharacter, SKILL_SAILING)) / SKILL_MAX;
    	aTmpSkill.Repair    = MakeFloat(GetSummonSkillFromName(rCharacter, SKILL_REPAIR)) / SKILL_MAX;
    	aTmpSkill.Fencing   = MakeFloat(GetSummonSkillFromName(rCharacter, SKILL_FENCING)) / SKILL_MAX;
    	aTmpSkill.Accuracy  = MakeFloat(GetSummonSkillFromName(rCharacter, SKILL_ACCURACY)) / SKILL_MAX;
    	aTmpSkill.Cannons   = MakeFloat(GetSummonSkillFromName(rCharacter, SKILL_CANNONS)) / SKILL_MAX;

        if (sti(rCharacter.index) == GetMainCharacterIndex())
        {
            if (SeaCameras.Camera == "SeaDeckCamera")
        	{
                // TO_DO DEL
        		aTmpSkill.Accuracy = Clampf(stf(aTmpSkill.Accuracy) + 0.15); // было 0.4
        	}
        	//rCharacter.SystemInfo.GlobalMinEnemyDistance = stf(rCharacter.SystemInfo.LastMainMinEnemyDistance); // fix выхода на карту
        	if (rand(10) == 3)//boal fix отношений, редко обновляется дял профилактики
        	{
        	    DoQuestCheckDelay("NationUpdate", 1.0);
        	}
    	}
    	rCharacter.TmpSkillRecall = 25 + rand(49); // разное время - размазанный пересчет, а то все скопом всё равно //"60"; // считаем раз в минуту
    	// анализ погони
		if (GetNpcQuestPastTimeParam(rCharacter, "Add2SeaTime") > 55) // 2 дня Только у фантомов есть признак, остальные 0
		{
		    if (CheckAttribute(rCharacter, "SeaAI.Task") && rCharacter.SeaAI.Task != AITASK_RUNAWAY) // че б не было, всё равно может гнать за ГГ
	        {
	        	Ship_SetTaskRunaway(SECONDARY_TASK, sti(rCharacter.index), sti(pchar.index));
	        }
		}
	}
	else
	{
        rCharacter.TmpSkillRecall = sti(rCharacter.TmpSkillRecall) - 1;

        if (sti(rCharacter.index) == GetMainCharacterIndex())
    	{
            rCharacter.TmpSkill.Accuracy  = MakeFloat(GetSummonSkillFromName(rCharacter, SKILL_ACCURACY)) / SKILL_MAX;
            if (SeaCameras.Camera == "SeaDeckCamera")
            {
                // TO_DO DEL
                rCharacter.TmpSkill.Accuracy = Clampf(stf(rCharacter.TmpSkill.Accuracy) + 0.15);
            }
    	}
	}
}

void Ship_UpdatePerks()
{
	int iCharacterIndex = GetEventData();
	ref rCharacter = GetCharacter(iCharacterIndex);

	//Trace("Ship_UpdatePerks: rCharacter.id = " + rCharacter.id);
	if (sti(rCharacter.ship.type) == SHIP_NOTUSED) return; // fix для смены корабля
	rCharacter.TmpPerks = "";
	aref aTmpPerks; makearef(aTmpPerks, rCharacter.TmpPerks);

	// calc perks for speed optimization
	//if (!CheckAttribute(rCharacter, "TmpPerks.Turn")) {	rCharacter.TmpPerks.Turn = 0; }
      // to_do
	aTmpPerks.Thrift	  	    = CheckOfficersPerk(rCharacter, "Thrift");
	aTmpPerks.BeneathWaterline = CheckOfficersPerk(rCharacter, "BeneathWaterline");
    aTmpPerks.FastReload				= CheckOfficersPerk(rCharacter, "FastReload");
	aTmpPerks.ImmediateReload			= CheckOfficersPerk(rCharacter, "ImmediateReload");
	aTmpPerks.HullDamageUp			 	= CheckOfficersPerk(rCharacter, "HullDamageUp");
	aTmpPerks.CrewDamageUp				= CheckOfficersPerk(rCharacter, "CrewDamageUp");
	aTmpPerks.CriticalShoot				= CheckOfficersPerk(rCharacter, "CriticalShoot");
	aTmpPerks.LongRangeShoot			= CheckOfficersPerk(rCharacter, "LongRangeShoot");
	aTmpPerks.CannonProfessional		= CheckOfficersPerk(rCharacter, "CannonProfessional");
	aTmpPerks.LongRangeGrappling		= CheckOfficersPerk(rCharacter, "LongRangeGrappling");
	aTmpPerks.GrapplingProfessional		= CheckOfficersPerk(rCharacter, "GrapplingProfessional");
	aTmpPerks.BasicBattleState			= CheckOfficersPerk(rCharacter, "BasicBattleState");
	aTmpPerks.AdvancedBattleState		= CheckOfficersPerk(rCharacter, "AdvancedBattleState");
	aTmpPerks.ShipDefenseProfessional	= CheckOfficersPerk(rCharacter, "ShipDefenseProfessional");
	aTmpPerks.ShipSpeedUp				= CheckOfficersPerk(rCharacter, "ShipSpeedUp");
	aTmpPerks.ShipTurnRateUp			= CheckOfficersPerk(rCharacter, "ShipTurnRateUp");
	aTmpPerks.SailingProfessional		= CheckOfficersPerk(rCharacter, "SailingProfessional");
	aTmpPerks.LightRepair				= CheckOfficersPerk(rCharacter, "LightRepair");
	// update main character if rCharacter is companion   - это было, но зачем?? (boal)
	if (iCharacterIndex != nMainCharacterIndex && IsCompanion(rCharacter))
	{
		Event("eSwitchPerks", "l", nMainCharacterIndex);
	}
}

void Ship_Lightning()
{
	if (!bSeaActive) { return; }

	float x = GetEventData();
	float y = GetEventData();
	float z = GetEventData();

	for (int i=0; i<iNumShips; i++)
	{
		ref rCharacter = GetCharacter(Ships[i]);
		aref arShipChar; makearef(arShipChar, rCharacter.Ship);

		float sx = stf(arShipChar.Pos.x);
		float sy = stf(arShipChar.Pos.y);
		float sz = stf(arShipChar.Pos.z);
		float bx = stf(arShipChar.BoxSize.x);
		float by = stf(arShipChar.BoxSize.y);
		float bz = stf(arShipChar.BoxSize.z);
		float fDist = GetDistance2D(x, z, sx, sz);
		float fMinLightningDist = 20.0 + bz / 1.5;
		if (fDist < fMinLightningDist)
		{
			int iMinBoom = MakeInt(Bring2Range(5.0, 2.0, 1.0, 7.0, stf(GetCharacterShipClass(rCharacter))));
			float fCos = cos(stf(arShipChar.Ang.y));
			float fSin = sin(stf(arShipChar.Ang.y));
			int iMax = iMinBoom + rand(2);
			for (int k=0; k<iMax; k++)
			{
				float dx = 0.6 * bx * (frnd() - 0.5);
				float dz = 0.7 * bz * (frnd() - 0.5);
				RotateAroundY(&dx, &dz, fCos, fSin);
				Ship_Serious_Boom(sx + dx, sy + 0.1 * by * frnd(), sz + dz);
			}

			Ship_ApplyHullHitpoints(rCharacter, iMinBoom * 40.0, KILL_BY_TOUCH, -1);
			Ship_ApplyCrewHitpoints(rCharacter, MakeFloat(rand(3)));

			int iNumFirePlaces = 0;
			SendMessage(rCharacter, "le", MSG_SHIP_GET_NUM_FIRE_PLACES, &iNumFirePlaces);
			
			float fFirePlaces = Bring2Range(1.0, 0.1, 0.0, fMinLightningDist, fDist);

			float fCurr = 0.0;
			float fTest = (1.0 - fFirePlaces) * iNumFirePlaces;
			for (int j=0; j<iNumFirePlaces; j++)
			{
				fCurr = fCurr + 1.0;
				if (fCurr < fTest) continue;
	
				fCurr = 0.0;
				int iRandStartTime = rand(10000);
				float fTotalFireTime = Ship_GetTotalFireTime(rCharacter);

				PostEvent(SHIP_ACTIVATE_FIRE_PLACE, iRandStartTime, "ialsfl", rCharacter, rCharacter, j, "ShipEMB/ShipDamage_Fire", fTotalFireTime, -1);
				PostEvent(SHIP_FIRE_DAMAGE, iRandStartTime, "lllf", Ships[i], -1, j, fTotalFireTime);
			}
		}
	}
}

// Create a new ship for character  to_do del нигде не юзается
void Ship_CreateForCharacter(ref rCharacter, int iShipType, string sShipName)
{
	DeleteAttribute(rCharacter, "Ship");

	rCharacter.Ship.Type = iShipType;
	rCharacter.Ship.Name = sShipName;

	rCharacter.Ship.Cannons.Borts = "";
	rCharacter.Ship.Cannons.Charge.Type = GOOD_BOMBS;
	rCharacter.Ship.Ang.y = 0.0;
	rCharacter.Ship.Pos.x = 0.0;
	rCharacter.Ship.Pos.y = 0.0;
	rCharacter.Ship.Pos.z = 0.0;
	rCharacter.Ship.Speed.z = 0.0;

	SetBaseShipData(rCharacter);
}

void Ship_ClearImpulseStrength(ref rCharacter)
{
	aref arImpulse; makearef(arImpulse, rCharacter.Ship.Impulse);
	arImpulse.Rotate.x = 0.0;
	arImpulse.Rotate.y = 0.0;
	arImpulse.Rotate.z = 0.0;
	arImpulse.Speed.x = 0.0;
	arImpulse.Speed.y = 0.0;
	arImpulse.Speed.z = 0.0;

	rCharacter.Ship.Tornado.Rotate.y = 0.0;  // fix boal
}

void Ship_PrepareShipForLocation(ref rCharacter)
{
	Ship_ClearImpulseStrength(rCharacter);
}
//  далее новые методы, не было в ПКМ
void Ship_LoadShip()
{
	int iCharacterIndex = GetEventData();
	ref rCharacter = GetCharacter(iCharacterIndex);
	
	//Dev_Trace("Ship_LoadShip = " + iCharacterIndex + " id = " + rCharacter.id + " ship.type = " + rCharacter.ship.type + " IsDead = " + LAi_IsDead(rCharacter));

	//if (sti(rCharacter.ship.type) != SHIP_NOTUSED && !LAi_IsDead(rCharacter))
	if (sti(rCharacter.ship.type) != SHIP_NOTUSED)
	{
		Event("eSwitchPerks", "l", iCharacterIndex);
		Ships[iNumShips] = iCharacterIndex;
		Event(SHIP_UPDATE_PARAMETERS, "lf", iCharacterIndex, stf(rCharacter.Ship.Speed.z));		// Parameters      после создания корабля
		iNumShips++;

	}
}

void Ship_LoadShipActivateFirePlace()
{
	int iOurCharacterIndex = GetEventData();
	int iBallCharacterIndex = GetEventData();
	int iFirePlaceIndex = GetEventData();
	float fTotalFireTime = GetEventData();

	Dev_Trace("iBallCharacterIndex = " + iBallCharacterIndex);
	int iStartTime = 500;

	PostEvent(SHIP_FIRE_DAMAGE, iStartTime, "lllf", iOurCharacterIndex, iBallCharacterIndex, iFirePlaceIndex, fTotalFireTime);
}

void SetTextureForShip(aref refBaseShip, aref rCharacter)
{
	if(!CheckAttribute(refBaseShip, "name"))
	{
		trace("SetTextureForShip(): ship " + refBaseShip.basetype + " have no name! NPCid = "+ rCharacter.id);
		if (MOD_BETTATESTMODE == "On") Log_Info("SetTextureForShip(): ship " + refBaseShip.basetype + " have no name! NPCid = "+ rCharacter.id);
		return;
	}

	string sPath = "ships\" + refBaseShip.name + "\";
	
	if(CheckAttribute(refBaseShip, "ship.Upgrades.hull"))  // boal 16/07/06 просто разные корпуса, без НПС
	{
		sPath = sPath + "hull" + refBaseShip.ship.upgrades.hull + "\";
	}
	
	SetTexturePath(0, sPath);
}

void DropGoodsToSea()
{
	aref rCharacter = GetEventData();

	ref rGood;
	string sGood;

	for (int i=0; i<GetArraySize(&Goods); i++)
	{
		sGood = Goods[i].name;
		if (CheckAttribute(&Goods[i], "DontDrop")) continue;

		if(CheckAttribute(rCharacter, "Ship.Cargo.Goods."+sGood))
		{
			int	iQuantity = sti(rCharacter.Ship.Cargo.Goods.(sGood));
			
			if(CheckAttribute(rCharacter, "Ship.Cargo.Goods."+sGood+".Lock")) continue; // залоченные товары не выкидывать !!!!! <-- ugeen fix
			
			if (iQuantity < 1 && rand(1) == 1) continue; 
			iQuantity = makeint(iQuantity/2 + rand(makeint(iQuantity/3)));   // выкидываем не все и не всегда, а то под ноль
			
			if (iQuantity < 1) continue; 
			
			RemoveCharacterGoods(rCharacter, i, iQuantity);

			iQuantity = iQuantity / sti(Goods[i].Units);

			if (iQuantity <= 1) 
			{ 
				continue; 
			}

			rCharacter.Ship.Cargo.Goods.(sGood) = 0;
            rCharacter.Ship.Cargo.RecalculateCargoLoad = true; // boal fix оптимизация
			//RecalculateCargoLoad(rCharacter);
            rCharacter.Tmp.SpeedRecall = 0; // чтоб пересчитались скорость и маневр
            
			if (CheckAttribute(&Goods[i], "Swim")) 
			{ 
				int iSwimQuantity = makeint(iQuantity/3 + rand(makeint(iQuantity/3)) + rand(makeint(iQuantity/3)));

				if(iSwimQuantity < 1)
				{
					iSwimQuantity = 1;
				}
				float fTime = stf(Goods[i].Swim.Time);
				string sModel = Goods[i].Swim.Model;

				//trace ("sModel is " + sModel);

				fTime = fTime + (frnd() - 0.5) * fTime / 2.0;

				AISeaGoods_AddGood(rCharacter, sGood, sModel, fTime * 60.0, iSwimQuantity);
			}
			return;
		}
	}
}

float Ship_GetRunAwayPoint()
{
	aref arChar = GetEventData();
    if(!CheckAttribute(arChar, "SeaAI.RunAwayPnt"))
        Ship_SetRunAwayPoint(arChar);
    return stf(arChar.SeaAI.RunAwayPnt);
}

void Ship_SetRunAwayPoint(aref arChar)
{
    float fWindAngle = Whr_GetWindAngle();
	float fShipAngle = stf(arChar.Ship.Ang.y);
	float fShipWindAngle = fShipAngle - fWindAngle;
	arChar.SeaAI.RunAwayPnt = fWindAngle + FindBestCourse(arChar, fShipWindAngle);
/*    float fCourse1 = fWindAngle - fCourse;
    float fCourse2 = fWindAngle + fCourse;
    if(cos(fShipAy - fCourse1) > cos(fShipAy - fCourse2))
         arChar.SeaAI.RunAwayPnt = fCourse1;
    else arChar.SeaAI.RunAwayPnt = fCourse2;	*/
}

void Ship_WindAnalyse()
{
    int iCharIdx;
    for(int i = 0; i < iNumShips; i++)
    {
        iCharIdx = Ships[i];
        if (iCharIdx < 0 || iCharIdx >= TOTAL_CHARACTERS) continue;
        DeleteAttribute(GetCharacter(iCharIdx), "SeaAI.RunAwayPnt");
    }
}

// boal -->
string GetShipSexWord(string _type, string _man, string _woman)
{
    if (_type == "WarTartane" || 
	    _type == "Schooner"   || 
		_type == "Schooner_W" ||
		_type == "Caravel"    || 
		_type == "Shnyava"    || 
		_type == "Caracca"    || 
		_type == "Brigantine" ||
		_type == "XebekVML")
    {
        return _woman;
    }
    else
    {
        return _man;
    }
}
// boal 08.08.06 метод пересчета орудий на корабле  - доработал ядро
void Ship_ResearchCannons(ref aCharacter)
{
	if (bSeaLoaded)
	{
		SendMessage(&AISea, "la", AI_MESSAGE_RESEARCH_CANNONS, aCharacter);
		RefreshBattleInterface();
		Ship_ChangeCharge(aCharacter, sti(aCharacter.Ship.Cannons.Charge.Type));
	}
}
// boal 20.08.06 перерисовка флага -->
void Ship_FlagRefresh(ref rCharacter)
{
    if (bSeaLoaded)
	{
		SendMessage(rCharacter, "l", MSG_SHIP_FLAG_REFRESH);
	}
}

void EmptyFantom_DropGoodsToSea(ref rChar, int iFantomType)
{
	float fTime;
	string sGood, sModel;
	int iQty;
	if(iFantomType == ENCOUNTER_TYPE_BARREL)
	{	
		int irand = hrand(100, rChar.location);
		if(irand > 92) // делаем бум
		{
			AISeaGoods_AddGood_Special(rChar, "powder1", "barrel_treasure", 1500.0, 1); // нарвались на беспризорную мину
		}
		else
		{
			if(irand < 40) 
			{
				for (int i=GOOD_FOOD; i<=GOOD_OIL; i++)
				{
					sGood = Goods[i].name;
					if (rand(3) > 1) continue; 
					if (CheckAttribute(&Goods[i], "Swim")) 
					{
						iQty = rand(15) + rand(10) + 5; 
						fTime = stf(Goods[i].Swim.Time);
						sModel = Goods[i].Swim.Model;
						fTime = fTime + (frnd() - 0.5) * fTime / 2.0;

						AISeaGoods_AddGood_Special(rChar, sGood, sModel, fTime * 60.0, iQty);
					}	
				}
			}
            TEV.Last_Treasure_Barrel_ID = rChar.id + rChar.name + rChar.location; // Запоминаем инфу о текущей бочке
			AISeaGoods_AddGood_Special(rChar, "barrel_treasure", "barrel_treasure", 1500.0, 1);			
		}	
	}
	if(iFantomType == ENCOUNTER_TYPE_BOAT)
	{
		AISeaGoods_AddGood_Special(rChar, "unknown_boat", "lo_boat", 1500.0, 1);
	}
	SendMessage(&AISea, "la", AI_MESSAGE_CHARACTER_DEAD, rChar);
}

void Ship_DoFakeFire(ref rChar, string sBort, float fRandTime)
{
	SendMessage(rChar, "lsf", MSG_SHIP_DO_FAKE_FIRE, sBort, fRandTime);
}

void Ship_EventFakeFire()
{
	float fX 	= GetEventData();
	float fY 	= GetEventData();
	float fZ 	= GetEventData();
	float fAY 	= GetEventData();
	
	CreateParticleSystem("cancloud_fire", fX, fY, fZ, 0.0, fAY, 0.0, 5);
	Play3DSound("cannon_fire", fX, fY, fZ);
}

void Ship_SetTechnique(ref rCharacter, string sTech)
{
	SendMessage(rCharacter, "ls", MSG_MODEL_SET_TECHNIQUE, sTech);
}

void Ship_SetGhostShip(ref rCharacter, string sTech)
{
	Ship_SetTechnique(rCharacter, sTech);
	
	LayerDelObject(sCurrentSeaRealize, rCharacter);
	LayerAddObject(sCurrentSeaRealize, rCharacter, 100000);
}

void Sea_ApplyMaxSpeedZ(ref rCharacter, float fWindShipAngle, ref fShipSpeed)
{
	rCharacter.Ship.BestCourseAngle = FindBestAngleBase(rCharacter);
	
	if(CheckAttribute(rCharacter, "FixedShipSpeed"))
		fShipSpeed = float(rCharacter.FixedShipSpeed);
	else
		fShipSpeed *= GetCurSpeedFromPoint(rCharacter, fWindShipAngle);
	
	rCharacter.ship.MaxSpeedZ = fShipSpeed;
}

float FindBestCourse(ref chr, float fShipWindAngle)
{
	int iRealShip = int(chr.ship.type);
	int iShipType = int(RealShips[iRealShip].basetype);
	ref rShip = &ShipsTypes[iShipType];
	if("sails_data" !in rShip)
		return fShipWindAngle;
	aref arData = &rShip.sails_data;
	float fRad;
	int angStep = 360 / SHIP_SPEEDPOINT_QUANTITY;
	float fSpeed, fMaxSpeed, fBestAngle, fDelta, fMinDelta;
	fMaxSpeed = 0.0;
	fMinDelta = PI;
	bool bAdvanced = false;
	if("tuning.rig" in &RealShips[iRealShip])
		bAdvanced = true;
	for(int i = 0; i < SHIP_SPEEDPOINT_QUANTITY; i++)
	{
		fRad = Degree2Radian(float(i * angStep));
		fSpeed = Ship_SimulateSailsSpeed(arData, fRad, chr, false) * Ship_GetSpeedPoint(rShip, i * angStep, bAdvanced);
		if(fSpeed > fMaxSpeed + 0.01)
		{
			fMaxSpeed = fSpeed;
			fBestAngle = fRad;
			fMinDelta = GetAngleDelta(fShipWindAngle, fRad);
		}
		else if(abs(fSpeed - fMaxSpeed) <= 0.01)
		{
			fDelta = GetAngleDelta(fShipWindAngle, fRad);
			if(fDelta < fMinDelta)
			{
				fMinDelta = fDelta;
				fBestAngle = fRad;
			}
		}
	}
	return fBestAngle;
}

float FindBestAngleBase(ref chr)
{
	int iRealShip = int(chr.ship.type);
	ref rShip = &RealShips[iRealShip];
	if("best_angle" in &rShip)
		return float(rShip.best_angle);
	int iShipType = int(RealShips[iRealShip].basetype);
	ref baseShip = &ShipsTypes[iShipType];
	if("sails_data" !in baseShip)
		return 0.0;
	aref arData = &baseShip.sails_data;
	float fAngle;
	int angStep = 360 / SHIP_SPEEDPOINT_QUANTITY;
	float fSpeed, fMaxSpeed, fBestAngle;
	fMaxSpeed = 0.0;
	bool bAdvanced = false;
	if("tuning.rig" in &rShip)
		bAdvanced = true;
	for(int i = 0; i < SHIP_SPEEDPOINT_QUANTITY; i++)
	{
		fAngle = float(i * angStep);
		fSpeed = Ship_SimulateSailsSpeed(arData, fAngle, chr, false) * Ship_GetSpeedPoint(baseShip, i * angStep, bAdvanced);
		if(fSpeed > fMaxSpeed)
		{
			fMaxSpeed = fSpeed;
			fBestAngle = fAngle;
		}
	}
	rShip.best_angle = fBestAngle;
	return fBestAngle;
}

float GetAngleDelta(float ang1, float ang2)
{
    return abs(atan2(sin(ang1 - ang2), cos(ang1 - ang2)));
}

void SetFireMode(ref chr, string newMode)
{
	if(newMode != FIRE_MODE_RANDOM && GetAttributeInt(chr, "TmpPerks.BeneathWaterline") != 1)
		return;
	chr.firemode = newMode;
}

string GetFireMode(ref chr)
{
	if ("firemode" !in chr || GetAttributeInt(chr, "TmpPerks.BeneathWaterline") != 1)
		return FIRE_MODE_RANDOM;
	return chr.firemode;
}

void AI_SetFireMode(ref chr, int iChargeType)
{
	if (IsMainCharacter(chr))
		return;
	if (GetAttributeInt(chr, "TmpPerks.BeneathWaterline") != 1)
		return;
	int iDirect = 1;
	int iRandom = 1;
	int iReverse = 1;
	
	switch(iChargeType)
	{
		case GOOD_BALLS:		iDirect = 40;		iRandom = 20;		iReverse = 40;		break;
		case GOOD_GRAPES:		iDirect = 30;		iRandom = 50;		iReverse = 20;		break;
		case GOOD_KNIPPELS:		iDirect = 20;		iRandom = 30;		iReverse = 50;		break;
		case GOOD_BOMBS:		iDirect = 50;		iRandom = 30;		iReverse = 20;		break;
	}
	
	int r = rand(iDirect + iRandom + iReverse - 1);
	string sNewMode;
	if (r < iDirect)
		sNewMode = FIRE_MODE_DIRECT;
	else if (r < iDirect + iRandom)
		sNewMode = FIRE_MODE_RANDOM;
	else
		sNewMode = FIRE_MODE_REVERSE;
	
	SetFireMode(chr, sNewMode);
}

#event_handler("Event_CollisionSoundCooldown", "CollisionSoundCooldown");
void CollisionSoundCooldown()
{
	string sAttr = GetEventData();
	DeleteAttribute(&TEV, "CollisionSound." + sAttr);
}