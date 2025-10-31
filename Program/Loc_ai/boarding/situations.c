bool BRD_ProcessSurrender(ref mchr, ref echr, bool isFort, int mclass, int eclass)
{
	if (isFort) return false;
	if (CheckAttribute(echr, "DontRansackCaptain")) return false;
	if (!CheckForSurrender(mchr, echr, 1)) return false;

	echr.ship.crew.morale = 5;// после захвата у них мораль такая
 
	if (mclass < eclass) AddCrewMorale(mchr, ( 3 + 2*rand(eclass-mclass)));
	else AddCrewMorale(mchr, 3);

	SendMessage(&Particles,"l", PS_CLEAR_CAPTURED); // повторное удаление партиклов, фикс огней в море.
	//Следующей локации нет
	DelEventHandler("LAi_event_GroupKill", "LAi_BoardingGroupKill");
	boarding_location = -1;

	// Saved value is not needed anymore... (Gray 14.02.2005)
	DeleteAttribute(pchar, "EnemyRank");
	bQuestCheckProcessFreeze = false;//fix
	//Настроим интерфейс
	Log_SetActiveAction("Nothing");
	EndBattleLandInterface();
	//Выгружаемся в интерфейс
	ChangeCrewExp(pchar, "Soldiers", 1);
	AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 7.0);
	LaunchRansackMain(pchar, echr, "crew");
	DelOurMusketerDist();
	LAi_boarding_process = false;  
	Event(SHIP_CAPTURED, "l", sti(echr.index));
	return true;
}

// изменен принцип сдачи, больше не учитываем ранг, перк морского волка, навык абордажа, количество других кораблей и мораль
bool CheckForSurrender(ref player, ref enemy, int _deck)
{
	if (boarding_location_type == BRDLT_FORT) return false;          // любая крепость как брестская
	if (GetPrisonerQty() > PRISONER_MAX) return false;               // проверка на кол-во пленых

	int playerCrew = GetWeaponCrew(player, GetCrewQuantity(player)); // базовые экипажи
	int enemyCrew = GetCrewQuantity(enemy);                          // базовые экипажи
	int playerPoints = playerCrew * 400;                             // очки берем за n экипажей, чтобы не плавать в точках
	int enemyPoints = enemyCrew * 1200;                              // очки противника с базовым преимуществом

	if(ShipBonus2Artefact(player, SHIP_MEMENTO) && CheckAttribute(&RealShips[sti(player.Ship.Type)], "DeadSailors.SurrenderChanceBonus"))
	{
		playerPoints = makeint(makefloat(playerPoints) * 1.0 + stf(RealShips[sti(player.Ship.Type)].DeadSailors.SurrenderChanceBonus) / 100.0);
	}

	int leadersDiff = GetCharacterSkill(player, SKILL_LEADERSHIP) - GetCharacterSkill(enemy, SKILL_LEADERSHIP); // разница в харизме от -100 до 100
	int soldiersDiff = makeint(GetCrewExp(player, "Soldiers") - GetCrewExp(enemy, "Soldiers"));                 // разница в опыте солдат от -100 до 100
	int skillBasedPoints = playerCrew * 2 * (soldiersDiff + leadersDiff);                                       // докидываем хардскиллуху
	int modSkillDebuff = playerCrew * 10 * MOD_SKILL_ENEMY_RATE;                                                // штрафуем от сложности
	int famePoints = (sti(player.reputation.fame) - 50) * playerCrew * 2;                                       // докидываем известность, репутация неважна
	int faithScore = hrand(9, enemy.id);                                                                        // щепотка суточно-привязанного рандома
	int fortuneLevel = GetCharacterSkill(player, SKILL_FORTUNE);                                                // удача любит храбрых
	int fortunePoints = playerCrew * fortuneLevel * iClamp(0, 3, faithScore - 4);                               // удача любит храбрых
	playerPoints = playerPoints - modSkillDebuff + skillBasedPoints + fortunePoints;                            // складываем очки игрока

	if (CheckAttribute(enemy, "Ship.Mode") && enemy.Ship.Mode == "Trade") enemyPoints -= enemyCrew * 300; // торговцы склонны сдаваться
	if (sti(enemy.Nation) == PIRATE) enemyPoints += 4000 + enemyCrew * 400;                               // а вот пираты не склонны
	if (CheckAttribute(enemy, "CaptainBrownTrousers")) enemyPoints += 12000 + enemyCrew * 400;            // а уж особо отважные пираты...
	if (GetCharacterShipClass(enemy) > 4) enemyPoints += 20000;                                           // капитаны малых кораблей рассчитывают вырезать всех сами

	bool result = playerPoints > enemyPoints;
	result = BRD_CheckFaith(playerPoints, enemyPoints, enemy, faithScore, result);                   // докидываем ещё веселых штук от рандомной вражеской морали

	if (bBettaTestMode) 
	{
		Log_Info("Харизмы: " + leadersDiff);
		Log_Info("Опыт солдат: " + soldiersDiff);
		Log_Info("Удача добавила: " + fortunePoints);
		Log_Info("Известность добавила: " + famePoints);
		Log_Info("Сложность отняла: " + modSkillDebuff);
		Log_Info("Скиллуха добавила: " + skillBasedPoints);
		Log_Info("Очков у игрока: " + playerPoints);
		Log_Info("Очков у компа: " + enemyPoints);
		Log_Info("Очко судьбы: " + faithScore);  
		if (CheckAttribute(enemy, "BoardingFaith.CaptainPreferSuicide")) Log_Info("Будет суицид");
		if (CheckAttribute(enemy, "BoardingFaith.CrewGiveUpCaptain")) Log_Info("Будет подстава");
		if (CheckAttribute(enemy, "BoardingFaith.SurrenderBeforeCabin")) Log_Info("Будет сдача перед каютой");
	}

	return result;
}

// играем с судьбой капитана
bool BRD_CheckFaith(int mpoints, int epoints, ref enemy, int faithScore, bool result)
{
	if (GetCharacterShipClass(enemy) == 7) return result; // не лезем в баркасы/тартаны
	DeleteAttribute(enemy, "BoardingFaith");              // на всякий случай обнуляем с прошлого раза, если уже брали на абордаж

	// события почти-сдачи, когда преимущество игрока велико, но недостаточно
	if (mpoints * 1.1 > epoints)
	{
		switch (faithScore)
		{
			case 0: // меняем сдачу на суицид
				if (mpoints * 1.2 < epoints) return result;
				enemy.BoardingFaith.CaptainPreferSuicide = 1;
				result = false;
			break;

			case 1: // меняем сдачу на подставу кэпа от команды
				if (mpoints * 1.2 < epoints) return result;
				enemy.BoardingFaith.CrewGiveUpCaptain = 1;
				result = false;
			break;

			case 2: // если сдача не случилась, будет подстава кэпа
				if (!result && mpoints * 1.3 > epoints) enemy.BoardingFaith.CrewGiveUpCaptain = 1;
			break;

			case 3: // если сдача не случилась, будет суицид
				if (!result && mpoints * 1.3 > epoints) enemy.BoardingFaith.CaptainPreferSuicide = 1;
			break;

			case 4: // сдается на второй палубе
				if (mpoints * 1.1 < epoints) return result;
				enemy.BoardingFaith.SurrenderBeforeCabin = 1;
				result = false;
			break;
		}
	}
	else // остальные события
	{
		if (CheckAttribute(enemy,"chr_ai.hpchecker.quest")) return result; // квестовые ситуации имеются, лучше поговорим в каюте
		if (faithScore < 3) enemy.BoardingFaith.UpperDeskFight = 1;
		if (faithScore < 1) enemy.BoardingFaith.GiveUpCapOnKill = 1;
	}

	return result;
}

// применяем дополнительные исходы абордажа в каюте кэпа
void BRD_CheckSitutationInCabin(ref clone, ref enemyCaptain)
{
	// суицид
	if (!CheckAttribute(enemyCaptain, "BoardingFaith.CaptainPreferSuicide")) return;
	if (CheckAttribute(enemyCaptain,"chr_ai.hpchecker.quest")) return;
	SetNewModelToChar(clone);

	PlaySound("People Fight\PistolFire.wav");
	notification(StringFromKey("boarding_1"), "X");
	DeleteAttribute(&clone, "items");
	clone.items.pistol1 = 1;
	clone.items.bullet = rand(5);
	clone.items.gunpowder = rand(5);
	clone.SaveItemsForDead = true;
	LAi_KillCharacter(&clone);
	PostEvent("LAi_event_boarding_EnableReload", 2000);
}

void BRD_PlaceCaptain(ref chr, ref boarding_enemy, int locIndex, string sLocType)
{
	ref location = &Locations[locIndex];
	string model, ani, sTemp;
	bool isCabin = CheckAttribute(location, "boarding.Loc.Capt");
	if (BRD_IsUpperDeskFight(boarding_enemy) && isCabin) return;

	if (!CheckAttribute(location, "UpDeckType") && !isCabin)
	{
		SetFantomParamAbordEnemy(chr);
		return; // обычного матросика пилим
	}
	else if (!BRD_IsUpperDeskFight(boarding_enemy) && !isCabin)
	{
		SetFantomParamAbordEnemy(chr);
		return; // обычного матросика пилим
	};

	if (!isCabin) notification(StringFromKey("boarding_3"), "leadership");

	model = LAi_GetBoardingModel(boarding_enemy, &ani);
	LAi_CreateFantomCharacterEx(model, ani, "rld", sLocType);
	ChangeAttributesFromCharacter(chr, boarding_enemy, true);
	GEN_OverrideAppearance(chr, 6);
	chr.MainCaptanIdx = boarding_enemy.index;
	chr.CaptanId = boarding_enemy.id; // на всякий случай нативное
	boarding_enemy.CaptanId = boarding_enemy.id; // на всякий случай нативное
	if (MOD_SKILL_ENEMY_RATE > 8 && rand(3) == 2) chr.SuperShooter = true; 
	if (boarding_enemy.sex == "man") chr.greeting = "CapSinkShip";
	if (CheckAttribute(chr,"Situation")) // на палубе не случится, т. к. ситуативные не сдаются
	{
		if (bSeaCanGenerateShipSituation) SetQuestAboardCabinDialogSituation(chr);
		else DeleteAttribute(chr,"Situation");
	}
	else
	{
        // to_do: временно убираем эти генеры
		//if (!BRD_IsUpperDeskFight(boarding_enemy)) CaptainComission_GenerateSituation(chr);
		SetQuestAboardCabinDialog(chr);
		BRD_CheckSitutationInCabin(chr, boarding_enemy); // Применяем доп. ситуации, если нет квестовых диалогов
	}

	int xhp = makeint((MOD_SKILL_ENEMY_RATE*2+sti(chr.rank))/10.0);
	if (!bImCasual && xhp > 3) SetCharacterPerk(chr, "Energaiser"); 

	if (xhp > 0)
	{
		if (xhp > 6) xhp = 6; 
		switch (xhp)
		{
			case 6:
				if(!bImCasual) xhp = 1;
				else xhp = 2;
			break;
			
			case 5:
				if(!bImCasual) xhp = 2;
				else xhp = 3;
			break;
			
			case 4:
				if(!bImCasual) xhp = 3;
				else xhp = 7;
			break;
			
			case 3:
				if(!bImCasual) xhp = 7;
				else xhp = 6;
			break;
			
			case 2:
				if(!bImCasual) xhp = 6;
				else xhp = 5;
			break;
			
			case 1:
				xhp = 5;
			break;
		}

		model = "cirass" + xhp;
		chr.cirassId  = Items_FindItemIdx(model);
	}
}

void BRD_SetCrewSurrendered()
{
	for(int i=0; i < LAi_numloginedcharacters; i++)
	{
		int idx = LAi_loginedcharacters[i];
		if(idx < 0) continue;
		ref chr = &Characters[idx];
		if (!CheckAttribute(chr, "chr_ai.group") || chr.chr_ai.group != LAI_GROUP_BRDENEMY) continue;

		LAi_group_MoveCharacter(chr, LAI_GROUP_DEFAULT);
		SetSurrenderedType(chr);
	}
}

bool BRD_IsCrewGiveUpCaptain(ref enemy, int leftCrew)
{
	if (!CheckAttribute(enemy, "BoardingFaith.CrewGiveUpCaptain")) return false;
	return leftCrew > 0; // кто-то же должен что-то решать
}

bool BRD_IsSurrenderBeforeCabin(ref enemy)
{
	return CheckAttribute(enemy, "BoardingFaith.SurrenderBeforeCabin");
}

bool BRD_IsUpperDeskFight(ref enemy)
{
	return CheckAttribute(enemy, "BoardingFaith.UpperDeskFight");
}

bool BRD_CrewGiveUpCaptain(ref enemy, int leftCrew)
{
	BRD_TurnCaptainIntoSailor(enemy);
	int resCrew = leftCrew-1;
	SetCrewQuantity(enemy, func_max(0, resCrew));
	AddCharacterExpToSkill(pchar, "Leadership", 30);
	LaunchRansackMain(pchar, enemy, "captain");
	Event(SHIP_CAPTURED, "l", sti(enemy.index));
	return true;
}

// Превращаем капитана в якобы нового избранного матросика
void BRD_TurnCaptainIntoSailor(ref chr)
{
	SetRandomNameToCharacter(chr);
	SetFantomParamFromRank(chr, 1, true);
	chr.model = "citiz_" + (31 + (rand(9)));
	FaceMaker(chr);
}

// Убили капитана на абордаже
void BRD_BoardingCaptainKilled(ref clone)
{
	if (!CheckAttribute(clone, "MainCaptanIdx")) return;
	if (HasSubStr(clone.location, "cabin")) return;

	ref captain = GetCharacter(sti(clone.MainCaptanIdx));
	if (!CheckAttribute(captain, "BoardingFaith.GiveUpCapOnKill") && GetCrewQuantity(captain) > 0)
	{
		notification(StringFromKey("boarding_6"), "Berserker");
		return;
	}

	captain.BoardingFaith.CrewGiveUpCaptain = true;
	BRD_TurnCaptainIntoSailor(captain);

	notification(StringFromKey("boarding_5"), "IronWill");
	LAi_SetFightMode(pchar, 0);

	if(HasPerk(pchar, "Looting"))
	{
		SetEventHandler("BRD_InitLooting", "BRD_InitLooting", 1);
		PostEvent("BRD_InitLooting", 500, "i", &Locations[boarding_location]);
	}

	PostEvent("LAi_event_boarding_EnableReload", 3000);
	BRD_SetCrewSurrendered();
}

// Убили какого-то подменыша на абордаже
void BRD_BoardingCloneKilled(ref clone)
{
	if (!CheckAttribute(clone, "PersonalityCloneType")) return;
	string attr = clone.chr_ai.group;
	string type = clone.PersonalityCloneType;
	DeleteAttribute(&TEV, "boarding.perkChars." +attr + "." + type);
	if (attr != LAI_GROUP_PLAYER) return;
	if (type != "boatswain" && type != "companion") return;

	ref chr = GetCharacter(sti(clone.PersonalityCloneIdx));
	Notification(XI_ConvertString("OfficerWounded1") + XI_ConvertString("OfficerWounded2"), GetMessagePortrait(chr));
	if (!CheckAttribute(chr, "OfficerImmortal")) return;

	if(!bSeaActive)
	{
		SetFunctionExitFromLocationCondition("RestoreInjOfficerInLoc", pchar.location, false);
	}
	else
	{
		PChar.quest.RestoreInjOfficerInLoc.win_condition.l1 = "ExitFromSea";
		PChar.quest.RestoreInjOfficerInLoc.function = "RestoreInjOfficerInLoc";
	}

	chr.chr_ai.hp = LAi_GetCharacterMaxHP(chr);
	chr.OfficerImmortal = "Injury";
	chr.Health.HP = makefloat(chr.Health.HP) - 10.0;
	if(makefloat(chr.Health.HP) < 20.0) chr.Health.HP = 20.0;
	string qName = "RestoreHealth_" + chr.index;
	PChar.quest.(qName).win_condition.l1            = "Timer";
	PChar.quest.(qName).win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
	PChar.quest.(qName).win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
	PChar.quest.(qName).win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
	PChar.quest.(qName).function					= "AddOfficerHealth";
	PChar.quest.(qName).again = true;
}