#include "Loc_ai\boarding\cabin_fight.c"
// Здесь геймплейные функции абордажа

// Мушкетный залп
void BRD_FireMusketsShoot(ref pchar, ref echr, int mclass, int eclass, ref realmcrew, ref realecrew)
{
	if (BRD_IsCrewGiveUpCaptain(echr, 1)) return;

	float 	mShipClassCoeff, eShipClassCoeff;
	int   ecrewBak;
	int   	mCrewShot = 0;
	int	  	eCrewShot = 0;
	float	mDamage, eDamage;
	float   mCoeff 	= 0.0;
	bool	bOk = false;
	int tempMCrew = realmcrew;
	int tempECrew = realecrew;
	
	if (CheckOfficersPerk(pchar, "MusketsShoot")) // для ГГ
	{
		bOk = true;
		int OffQty = GetOfficersQuantity(pchar); 
		if (OffQty < 0) OffQty = 1;
		
		mShipClassCoeff = (eclass - mclass) * 0.15; // считаем коэффицент классности для ГГ
		mCrewShot = int(tempMCrew / 4);				// количество стрелков ГГ

		mCoeff = 0.5 + 0.1 * OffQty;
		// это базовая величина потенциального урона, который может нанести команда протагониста.
		mDamage = tempMCrew * mCoeff/4 + rand( int(tempMCrew * (1 - mCoeff)/4 ) );
		
		mDamage = mDamage * (1 + mShipClassCoeff);
		if(mDamage > tempECrew * 0.75) mDamage = tempECrew * 0.75;
		
		mDamage = mDamage * isEquippedArtefactUse(echr, "amulet_11", 1.0, 0.90);
		mDamage = mDamage * isEquippedArtefactUse(pchar, "indian_6", 1.0, 1.10);
		if (IsCharacterEquippedArtefact(pchar, "talisman18"))
		{
			mDamage *= 1.0 + ArticlesBonus(pchar);
		}

		ecrewBak = int(mDamage);
		tempECrew = tempECrew - ecrewBak;

		if(ecrewBak > 0)
			notification(XI_ConvertString("MusketVolleyKilled") + ecrewBak + XI_ConvertString("MusketVolleyEnemy"), "MusketsShoot");
	}
	if (CheckOfficersPerk(echr, "MusketsShoot")) // для противника
	{
		bOk = true;
		eShipClassCoeff = (mclass - eclass) * 0.15; 				// считаем коэффицент классности для противника
		eCrewShot = int(tempECrew / 4);								// количество стрелков противника
		eDamage = tempECrew * 0.2 + rand(int(tempECrew/20)); 			// базовая величина потенциального урона, который может нанести противник
		
		eDamage = eDamage * (1 + eShipClassCoeff);
		if(eDamage > tempMCrew * 0.75) eDamage = tempMCrew * 0.75;
		
		eDamage = eDamage * isEquippedArtefactUse(pchar, "amulet_11", 1.0, 0.90);
		eDamage = eDamage * isEquippedArtefactUse(echr, "indian_6", 1.0, 1.10);
		
		ecrewBak = int(eDamage);
		tempMCrew = tempMCrew - ecrewBak;
		
		if(ecrewBak > 0)
			notification(XI_ConvertString("MusketVolleyKilled") + ecrewBak + XI_ConvertString("MusketVolleyPlayer"), "X");

		Statistic_AddValue(pchar, "DeadCrewBoard", ecrewBak);
		Statistic_AddValue(pchar, "Sailors_dead", ecrewBak);
		AddMementoShipBonus(ecrewBak);
		Achievment_SetStat(21, ecrewBak);
	}
	if(bOk)
	{
		if(mclass <=2 || eclass <= 2) PlaySound("INTERFACE\MusketFire1.wav");
		else
		{
			if(rand(2) > 1) PlaySound("INTERFACE\MusketFire3.wav");
			else 			PlaySound("INTERFACE\MusketFire2.wav");
		}
	}

	realmcrew = func_max(0, tempMCrew);
	realecrew = func_max(0, tempECrew);
}

//Расставить персонажей для боя
void LAi_SetBoardingActors(string locID, ref boarding_enemy)
{
	int    limit, i, j, iQty;
	ref    chr;
	string model, ani, sTemp;
	int    xhp;
	int    locIndex = FindLocation(locID);
	ref    location = &Locations[locIndex];
	int    mclass = GetCharacterShipClass(pchar);
	int    eclass = GetCharacterShipClass(boarding_enemy);
	int    locMChar;
    
	limit = MAX_GROUP_SIZE;
	// локаторов разное число на моделях :( Переделал все на инфу из кода boal 01.01.05  +1 всегда для ГГ
	chr = &Locations[locIndex];
	aref boardingObject;
	makearef(boardingObject, TEV.boarding);

	object temp;
	aref perkChars, enemyPerkChars, realPerkChars, realEnemyPerkChars;
	makearef(perkChars, temp.perkChars);
	makearef(enemyPerkChars, temp.enemyPerkChars);
	makearef(realPerkChars, boardingObject.perkChars.player);
	makearef(realEnemyPerkChars, boardingObject.perkChars.brdenemy);
	CopyAttributes(&perkChars, realPerkChars);
	CopyAttributes(&enemyPerkChars, realEnemyPerkChars);
	int attackerRankOffset = int(boardingObject.attacker.rank);
	int defenderRankOffset = int(boardingObject.defender.rank);
	bool attackerElixir = boardingObject.attacker.elixir$bool(false);
	bool defenderElixir = boardingObject.defender.elixir$bool(false);

	if(CheckAttribute(location, "boarding.locatorNum")) limit = int(location.boarding.locatorNum);

	Log_TestInfo("Location: " + locID + " Limit: " + limit);
	Log_TestInfo("Player: " + boarding_player_crew + " х " + boarding_player_crew_per_chr + " Enemy: " + boarding_enemy_crew + " х " + boarding_enemy_crew_per_chr);

	string sLocType = "loc";
	// определение стороны на палубе
	sLocType = ChooseShipUpDeck(pchar, boarding_enemy);

	object aSoldier[1];
	object aMushketers[1];
	GenerateItemsForCharacter(pchar, ITEM_PACK_GENERIC, &aSoldier, &aMushketers);

	object aSoldierEnemy[1];
	object aMushketersEnemy[1];
	GenerateItemsForCharacter(boarding_enemy, ITEM_PACK_GENERIC, &aSoldierEnemy, &aMushketersEnemy);
	if (!CheckAttribute(location, "CabinType"))
	{ // не грузим матросов в каюту
		object aBoardingModels[1];
		SetArraySize(&aBoardingModels, limit);
		GenerateCrew(pchar, "soldier", &aBoardingModels);
		j = 0;

		for(i = LAi_numloginedcharacters; i < limit; i++)
		{
			if(boarding_player_crew <= 0) break;
			model = aBoardingModels[j].model;
			ani = aBoardingModels[j].ani;
			j++;
			// boal star with new loc always  -->
			if (pchar.location.locator == (sLocType + i))
			{ // искодим из того, что наша локация всегда < 4 офицеры пусть накладываются а матросик идёт к противнику.
	           locMChar = rand(3);
	           while (pchar.location.locator == (sLocType + locMChar))
	           {
	               locMChar = rand(3);
	           }
		       chr = LAi_CreateFantomCharacterEx(model, ani, "rld", sLocType+locMChar);// 0-всегда свободен, если офицеров нет, а i != 0, тк мы точно есть
			}
			else
			{
			   chr = LAi_CreateFantomCharacterEx(model, ani, "rld", sLocType + i);
			}
			// boal star with new loc always  <--

			LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER);
			boarding_player_crew = boarding_player_crew - 1;

			SetNPCEquip(chr, &aSoldier, false);

			if (IsFort) SetFantomParamFortOur(chr);
			else SetFantomParamAbordOur(chr);

			AddCharHP(chr, int(boarding_player_hp)); // влияение опыта и морали в НР
			BRD_InjectPerks(chr, i, &perkChars, location, attackerElixir);
			BRD_InjectBalance(chr, attackerRankOffset, boardingObject, location);
			SetNewModelToChar(chr); //иначе сабли не те, что реально
			chr.AboardFantom = true;
		}
		//ставим своих мушкетеров -->
		if (CheckOfficersPerk(pchar, "MusketsShoot") && CheckAttribute(&Locations[locIndex], "UpDeckType") && !CheckAttribute(boarding_enemy, "GenQuest.CrewSkelMode"))
		{
			int MusChr;
			int mush_officers = 0;
			for(int cm = 1; cm < 4; cm++)
			{
				MusChr = GetOfficersIndex(pchar, cm);
				if (MusChr >= 0)
				{
					if(!MusketPriority(&characters[MusChr])) continue;
					mush_officers = mush_officers + 1;
					string sNum = "n"+mush_officers;
					pchar.GenQuest.boarding.(sNum) = characters[MusChr].id;
					if(CheckAttribute(&characters[MusChr],"MusketerDistance"))
					{
						characters[MusChr].boarding.mDistance = float(characters[MusChr].MusketerDistance);
						characters[MusChr].MusketerDistance = 0.0;
					}
					if(mush_officers > 1) break;
				}
			}
			if (!IsFort) iQty = 2-mush_officers;
			else iQty = 3;

			object aBoardingMushModels[1];
			SetArraySize(&aBoardingMushModels, iQty);
			GenerateCrew(pchar, "mushketer", &aBoardingMushModels);
			j = 0;

			for(i=1; i<=iQty; i++)
			{
				if (LAi_CheckLocatorFree("rld", sLocType+"mush"+i))
				{
					model = aBoardingMushModels[j].model;
					ani = aBoardingMushModels[j].ani;
					j++;
					chr = GetCharacter(NPC_GenerateCharacter("GenChar_", model, "man", ani, 5, int(pchar.nation), 0, false, "soldier"));
					chr.id = "GenChar_" + chr.index;
					
					chr.AboardFantom = true;
					if (!IsFort) chr.MusketerDistance = 0;
					LAi_SetWarriorType(chr);
					LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER);
					ChangeCharacterAddressGroup(chr, locID, "rld", sLocType+"mush"+i);

					SetNPCEquip(chr, &aMushketers, true);
					if (IsFort) SetMushketerParamFortOur(chr);
					else SetMushketerParamAbordOur(chr);

					AddCharHP(chr, int(boarding_player_hp)); // влияение опыта и морали в НР
					BRD_InjectBalance(chr, attackerRankOffset, boardingObject, location);
				}
			}

			if(!IsFort && mush_officers > 0)
			{
				if(CheckAttribute(pchar, "GenQuest.boarding.n2"))
				{
					chr = characterFromId(pchar.GenQuest.boarding.n2);
					ChangeCharacterAddressGroup(chr, locID, "rld", sLocType+"mush"+1);
				}
				if(CheckAttribute(pchar, "GenQuest.boarding.n1"))
				{
					chr = characterFromId(pchar.GenQuest.boarding.n1);
					ChangeCharacterAddressGroup(chr, locID, "rld", sLocType+"mush"+2);
				}
			}
		}
		if(!IsFort && !CheckAttribute(&Locations[locIndex], "UpDeckType"))
		{
			if(CheckAttribute(pchar, "GenQuest.boarding.n2"))
			{
				chr = characterFromId(pchar.GenQuest.boarding.n2);
				if(CheckAttribute(chr,"boarding.mDistance"))
				{
					chr.MusketerDistance = float(chr.boarding.mDistance);
					DeleteAttribute(chr,"boarding.mDistance");
				}
				DeleteAttribute(pchar, "GenQuest.boarding.n2");
			}
			if(CheckAttribute(pchar, "GenQuest.boarding.n1"))
			{
				chr = characterFromId(pchar.GenQuest.boarding.n1);
				if(CheckAttribute(chr,"boarding.mDistance"))
				{
					chr.MusketerDistance = float(chr.boarding.mDistance);
					DeleteAttribute(chr,"boarding.mDistance");
				}
				DeleteAttribute(pchar, "GenQuest.boarding.n1");
			}
		}
		//<-- ставим своих мушкетеров
	}
	//Установим врагов
	if (sLocType == "loc") sLocType = "aloc";
	else sLocType = "loc";

	bool isCabin = CheckAttribute(&Locations[locIndex], "boarding.Loc.Capt");
	if (BRD_IsUpperDeskFight(boarding_enemy) && isCabin)
	{
		PostEvent("LAi_event_boarding_EnableReload", 200);
		limit = 0;
	}
	int capIdx = 0;
	if (!isCabin && boarding_enemy_crew > limit) capIdx = rand(limit-1);
	else if (!isCabin) capIdx = rand(boarding_enemy_crew - 1);

	object aBoardingModelsEnemy[1];
	SetArraySize(&aBoardingModelsEnemy, limit);
	GenerateCrew(boarding_enemy, "soldier", &aBoardingModelsEnemy);
	j = 0;

	for(i = 0; i < limit; i++) // <= тк loc0 .. loc4 = 5
	{
		if(boarding_enemy_crew <= 0) break;
		model = aBoardingModelsEnemy[j].model;
		ani = aBoardingModelsEnemy[j].ani;
		j++;

		string fantomLock = sLocType + i;
		if (i == 0 && isCabin) fantomLock = Locations[locIndex].boarding.Loc.Capt;
		chr = LAi_CreateFantomCharacterEx(model, ani, "rld", fantomLock);
		LAi_group_MoveCharacter(&chr, LAI_GROUP_BRDENEMY);

		if (IsFort)
		{
			SetNPCEquip(chr, &aSoldierEnemy, false);
			SetFantomParamFortEnemy(&chr);
		}
		else if (i == capIdx)
		{
			BRD_PlaceCaptain(chr, boarding_enemy, locIndex, sLocType);
			ChangeCharacterAddressGroup(chr, location.id, "rld", "cabin_boarding_enemy1");
		}
		else 
		{
			SetNPCEquip(chr, &aSoldierEnemy, false);
			SetFantomParamAbordEnemy(&chr);
			BRD_InjectPerks(chr, i, &enemyPerkChars, location, defenderElixir);
		}

		chr.nation = int(boarding_enemy.nation);
		boarding_enemy_crew = boarding_enemy_crew - 1;

		SetNewModelToChar(&chr); //иначе сабли не те, что реально
		chr.AboardFantom = true;
		AddCharHP(&chr, int(boarding_enemy_hp)); // влияение опыта и морали в НР
		BRD_InjectBalance(chr, defenderRankOffset, boardingObject, location);
		
		if(boarding_enemy.id == "Memento_Cap" && !CheckAttribute(&Locations[locIndex], "CabinType"))
		{
			chr.QuestCorpseLoot = "Memento_Cap";
		}
	}
	//ставим вражеских мушкетеров -->
	if (CheckCharacterPerk(boarding_enemy, "MusketsShoot") || IsFort)
	{
		if (CheckAttribute(&Locations[locIndex], "UpDeckType") && !CheckAttribute(boarding_enemy, "GenQuest.CrewSkelMode"))
		{
			if (!IsFort) iQty = 2;
			else iQty = 3;

			object aBoardingMushModelsEnemy[1];
			SetArraySize(&aBoardingMushModelsEnemy, iQty);
			GenerateCrew(boarding_enemy, "mushketer", &aBoardingMushModelsEnemy);
			j = 0;

			for(i=1; i<=iQty; i++)
			{
				if (LAi_CheckLocatorFree("rld", sLocType+"mush"+i))
				{
					model = aBoardingMushModelsEnemy[j].model;
					ani = aBoardingMushModelsEnemy[j].ani;
					j++;
					chr = GetCharacter(NPC_GenerateCharacter("GenChar_", model, "man", ani, 5, int(boarding_enemy.nation), 0, false, "soldier"));
					chr.id = "GenChar_" + chr.index;

					chr.AboardFantom = true;
					chr.MusketerDistance = 0;
					LAi_SetWarriorType(chr);
					LAi_group_MoveCharacter(chr, LAI_GROUP_BRDENEMY);
					ChangeCharacterAddressGroup(chr, locID, "rld", sLocType+"mush"+i);
					boarding_enemy_crew = boarding_enemy_crew - 1; // to_do: если сухопутных нет, уйдёт в минус

					SetNPCEquip(chr, &aMushketersEnemy, true);

					if (IsFort) SetMushketerParamFortEnemy(chr);
					else SetMushketerParamAbordEnemy(chr);

					AddCharHP(chr, int(boarding_enemy_hp)); // влияение опыта и морали в НР
					BRD_InjectBalance(chr, defenderRankOffset, boardingObject, location);
				}
			}	
		}
	}
	//<-- ставим вражеских мушкетеров
	if(boarding_enemy.id == "Memento_Cap") chr.QuestCorpseLoot = "Memento_Cap";
	if (bBettaTestMode)
	{
		trace("============Абордажный положняк=================");
		DumpAttributes(boardingObject);
		trace("============Абордажный положняк=================");
	}
	BRD_StartFight(locIndex, boarding_enemy, isCabin, boardingObject);
}

bool BRD_ExitToInterface(ref chr, int leftCrew, bool IsFort, ref surrender)
{
	trace("BRD_ExitToInterface sur: " + surrender + " leftCrew: " + leftCrew);
	LAi_boarding_process = false;
	if (CheckAttribute(pchar, "GenQuest.QuestAboardCaptanSurrender")) // квестовая сдача в плен кэпа
	{
		DeleteAttribute(pchar, "GenQuest.QuestAboardCaptanSurrender"); // разово
		surrender = true;
	}

	// Завершаем с другим интерфейсом, если команда предала капитана
	if (BRD_IsCrewGiveUpCaptain(chr, leftCrew)) return BRD_CrewGiveUpCaptain(chr, leftCrew);

	if (surrender)
	{
		ChangeCrewExp(pchar, "Soldiers", 4);
		LAi_SetCurHPMax(chr);  // нужно, чтоб был живой!!!
		SetCrewQuantity(chr, int(leftCrew*(rand(20)*0.01))); // раз кэп живой, то можно раненых воскресить
		LaunchRansackMain(pchar, chr, "captain"); //капитан в плен
		DelOurMusketerDist();
		Event(SHIP_CAPTURED, "l", int(chr.index));
		return true;
	}

	if (!IsFort)
	{
		ChangeCrewExp(pchar, "Soldiers", 5);
		LaunchRansackMain(pchar, chr, ""); //не сдался
		DelOurMusketerDist();
		Event(SHIP_CAPTURED, "l", int(chr.index));
		return true;
	}
	if(IsFort)
	{
		ChangeCrewExp(pchar, "Soldiers", 7);
		Event(FORT_CAPTURED, "l", int(chr.index));
		chr.Ship.Crew.Quantity = 10 + rand(350); // рабы (остатки выживших)
		LaunchFortCapture(chr);
		return true;
	}
	Trace("Boarding: unknow boarding location type");
}

// Все участники на местах, начинаем драку или?..
void BRD_StartFight(int locIndex, ref boarding_enemy, bool isCabin, ref boardingObject)
{
	if (CheckAttribute(boarding_enemy, "replaceFightWithFunc"))
	{
		RunCallbacks(boarding_enemy, "replaceFightWithFunc");
		DeleteAttribute(boarding_enemy, "replaceFightWithFunc");
		return;
	}

	ref location = &Locations[locIndex];
	if (!isCabin && BRD_IsCrewGiveUpCaptain(boarding_enemy, 1))
	{
		if (CheckAttribute(location, "UpDeckType")) notification(StringFromKey("boarding_2"), "IronWill");// первая палуба
		PostEvent("LAi_event_boarding_EnableReload", 200);
		LAi_SetFightMode(pchar, 0);
		BRD_SetCrewSurrendered();
	}

	if (isCabin) InitCabinFight(location, boarding_enemy, boardingObject);
  LAi_group_FightGroupsEx(LAI_GROUP_PLAYER, LAI_GROUP_BRDENEMY, true, GetMainCharacterIndex(), -1, false, false);
  LAi_group_SetCheckEvent(LAI_GROUP_BRDENEMY);
}

// Максимум команды от меньшего из двух класса корабля
int GetBoardingMaxCrew(ref location, int mclass, int eclass)
{
	int maxcrew;
	int shipClass = func_min(mclass, eclass);
	switch (shipClass)
	{
		case 7: maxcrew = 8;  break;
		case 6: maxcrew = 10;	break;
		case 5: maxcrew = 12;	break;
		case 4: maxcrew = 14;	break;
		case 3: maxcrew = 16;	break;
		case 2: maxcrew = 22;	break;
		case 1: maxcrew = 24;	break;
	}

	if (CheckAttribute(location, "boarding.locatorNum"))
	{
		maxcrew = func_min(int(location.boarding.locatorNum), maxcrew);
	}

	return iClamp(1, BRDLT_MAXCREW, maxcrew);
}

// Заканчиваем абордаж сдачей, т. к. не нашли локацию
bool BRD_FallbackNoLocation(string deckID, ref echr, bool isFort)
{
	Trace("Boarding: ship location not found <" + deckID + ">, no start boarding");
	DeleteAttribute(pchar, "EnemyRank");
	bQuestCheckProcessFreeze = false;

	if(!isFort)
	{
		LaunchRansackMain(pchar, echr, "captain");  // на деле параметры LaunchRansackMain не важны совсем - все определеятеся от реалий
		Event(SHIP_CAPTURED, "l", int(echr.index)); // to_do can be harmfull
	}
	else if (isFort)
	{
		Event(FORT_CAPTURED, "l", int(echr.index));
		echr.Ship.Crew.Quantity = 10 + rand(350); // рабы (остатки выживших)
		LaunchFortCapture(echr);
	}

	SendMessage(&Particles,"l", PS_CLEAR_CAPTURED);
	ChangeCrewExp(pchar, "Soldiers", 1);
	LAi_boarding_process = false;
	return true;
}

void BRD_ApplyMedicine(int deadCrewWOMedic, ref deadCrew)
{
	int iTemp = deadCrewWOMedic - deadCrew;
	if (iTemp <= 0) return;

	if (CheckShipSituationDaily_GenQuest(pchar) > 1) 
	{
		deadCrew += deadCrewWOMedic; // если эпидемия - матросы не лечатся, лекарство не потребляется
		return;
	}

	if (GetCargoGoods(pchar, GOOD_MEDICAMENT) < iTemp)
	{
		deadCrewWOMedic = iTemp - GetCargoGoods(pchar, GOOD_MEDICAMENT); // умерли от ран
		RemoveCharacterGoodsSelf(pchar, GOOD_MEDICAMENT, GetCargoGoods(pchar, GOOD_MEDICAMENT)); // все нулим
		deadCrew += deadCrewWOMedic; // трупов больше
		Log_Info(XI_ConvertString("Meds1") + deadCrewWOMedic + XI_ConvertString("Meds2"));
		return;
	}

	RemoveCharacterGoodsSelf(pchar, GOOD_MEDICAMENT, iTemp);
	if (GetCargoGoods(pchar, GOOD_MEDICAMENT) < 16)
	{
		Log_Info(XI_ConvertString("Meds3") + pchar.Ship.Name + XI_ConvertString("Meds4"));
	}

}

