int  Part_HeroPart 				= 200;
int  Part_CompanionShipPerClass = 20;
int  Part_Gower					= 10; 
int  Part_Crew					= 1;
int  Part_Companion				= 30;
int  Part_Officer               = 10;	


// месячная базовая ставка одного матроса до модификаторов
#define CREW_SAILOR_MONTHLY_SALARY        165.0

// разовый аванс при найме матроса в таверне: полтора месячного жалования
#define CREW_HIRE_ADVANCE_MTP             1.7

// опыт экипажа влияет мягко: средний опыт 0..100 даёт множитель 0.75..1.25
#define CREW_EXP_SALARY_MTP_MIN           0.75
#define CREW_EXP_SALARY_MTP_RANGE         0.50

// сложность почти не трогает содержание: каждый шаг сложности от 6 даёт +/-5%
// MOD_SKILL_ENEMY_RATE идёт 2/4/6/8/10, поэтому делим разницу на 2
#define CREW_DIFFICULTY_SALARY_STEP       0.05

// Торговля и Харизма вместе могут снизить зарплату матросов максимум на 15%
// SKILL_LEADERSHIP в проекте соответствует русской Харизме
#define CREW_SKILL_SALARY_DISCOUNT_MAX    0.20

// базовая месячная ставка офицера за сам факт службы
#define OFFICER_BASE_MONTHLY_SALARY      2500.0

// стоимость одного очка умения офицера; сумма 14 навыков 1..100 даёт примерно 2к..50к
#define OFFICER_SKILL_POINT_COST         9.0

// сложность мягко влияет на зарплату офицеров: каждый шаг от 6 даёт +/-5%
// MOD_SKILL_ENEMY_RATE идёт 2/4/6/8/10, поэтому делим разницу на 2
#define OFFICER_DIFFICULTY_SALARY_STEP   0.05

// Торговля и Харизма вместе могут снизить зарплату офицеров максимум на 15%
#define OFFICER_SKILL_SALARY_DISCOUNT_MAX 0.15

void UpdateCrewExp()
{	
	int cn;
	ref chr;
	for (int i = 0; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(pchar, i);
		if(cn != -1)
		{
			chr = &characters[cn];
			if (bSeaActive || IsEntity(&worldMap))  // море или карта
			{
				ChangeCrewExp(chr, "Sailors", 1);
			}
			else
			{
				ChangeCrewExp(chr, "Sailors", -1);
				ChangeCrewExp(chr, "Cannoners", -1);
				ChangeCrewExp(chr, "Soldiers", -1);
			}
		}
	}
	
}
string GetExpName(int iExp)
{
	string sExp = "Exp 1";

	if(iExp >= 12)
	{
		sExp = "Exp 2";
	}
	if(iExp >= 24)
	{
		sExp = "Exp 3";
	}
	if(iExp >= 35)
	{
		sExp = "Exp 4";
	}
	if(iExp >= 46)
	{
		sExp = "Exp 5";
	}
	if(iExp >= 57)
	{
		sExp = "Exp 6";
	}
	if(iExp >= 68)
	{
		sExp = "Exp 7";
	}
	if(iExp >= 80)
	{
		sExp = "Exp 8";
	}
	if(iExp >= 90)
	{
		sExp = "Exp 9";
	}
	/*if(iExp >= 90)
	{
		sExp = "Exp 10";
	} */

	return sExp;
}

// boal новый учёт зп 16.01.04 -->
int GetMoneyForOfficer(ref Npchar)
{
	if (!CheckAttribute(Npchar, "Payment") || int(Npchar.Payment) != true) return 0;

	int sum = 0;
	for (int i=1; i <= SKILL_QTY; i++)
	{
		sum += GetSkillValue(Npchar, SKILL_TYPE, GetSkillNameByIdx(i));
	}

	// База: офицер получает ставку за службу + оплату за общий профессиональный опыт.
	// 14 навыков по 1 дают около 2к, 14 навыков по 100 дают около 50к до модификаторов.
	float payment = OFFICER_BASE_MONTHLY_SALARY + float(sum) * OFFICER_SKILL_POINT_COST;

	// Сложность слегка двигает содержание, но не перестраивает экономику.
	// MOD 2 = -10%, MOD 6 = база, MOD 10 = +10%.
	float mtp = 1.0 + ((float(MOD_SKILL_ENEMY_RATE) - 6.0) / 2.0) * OFFICER_DIFFICULTY_SALARY_STEP;

	// Сохраняем старый смысл Trustworthy: такой офицер обходится дешевле.
	if (HasPerk(Npchar, "Trustworthy")) mtp -= PERK_VALUE_TRUSTWORTHY;

	return int(payment * mtp);
}


float GetCrewSalaryExpMtp(ref chref)
{
	float crewExp = GetCrewExp(chref);
	if (crewExp < 0.0) crewExp = 0.0;
	if (crewExp > 100.0) crewExp = 100.0;

	return CREW_EXP_SALARY_MTP_MIN + CREW_EXP_SALARY_MTP_RANGE * crewExp / 100.0;
}

float GetCrewSalaryDifficultyMtp()
{
	return 1.0 + ((MOD_SKILL_ENEMY_RATE - 6.0) / 2.0) * CREW_DIFFICULTY_SALARY_STEP;
}

float GetCrewSalarySkillMtp(ref mchref)
{
	float nLeadership = GetSummonSkillFromNameToOld(mchref, SKILL_LEADERSHIP); // Харизма
	float nCommerce   = GetSummonSkillFromNameToOld(mchref, SKILL_COMMERCE);   // Торговля
	float skillAvg    = (nLeadership + nCommerce) / 2.0;

	// Навыки в старой шкале 1..10. Единица не даёт скидки, десять даёт полный бонус.
	float skillPower = (skillAvg - 1.0) / 9.0;
	if (skillPower < 0.0) skillPower = 0.0;
	if (skillPower > 1.0) skillPower = 1.0;

	return 1.0 - CREW_SKILL_SALARY_DISCOUNT_MAX * skillPower;
}

int GetMoneyForCrew(ref chref)
{
	int crewQty = GetCrewQuantity(chref);
	if (crewQty <= 0) return 0;

	float payment = float(crewQty) * CREW_SAILOR_MONTHLY_SALARY;
	payment *= GetCrewSalaryExpMtp(chref);
	payment *= GetCrewSalaryDifficultyMtp();
	payment *= GetCrewSalarySkillMtp(GetMainCharacter());
	payment *= SZN_GetModifierMtp(M_CREW_MAINTENANCE_COST, 1.0, 0.01);

	return int(payment);
}

int GetMoneyForOfficerFull(ref Npchar)
{
	float oLeaderShip = GetSummonSkillFromNameToOld(pchar, SKILL_LEADERSHIP); // Харизма
	float oCommerce   = GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE);   // Торговля
	float skillAvg    = (oLeaderShip + oCommerce) / 2.0;

	// Навыки в старой шкале 1..10. Единица не даёт скидки, десять даёт полный бонус.
	// Торговля и Харизма 50/50 дают до -15% к зарплате офицеров.
	float skillPower = (skillAvg - 1.0) / 9.0;
	if (skillPower < 0.0) skillPower = 0.0;
	if (skillPower > 1.0) skillPower = 1.0;

	float mSkillOficcer = 1.0 - OFFICER_SKILL_SALARY_DISCOUNT_MAX * skillPower;
	return int(GetMoneyForOfficer(Npchar) * mSkillOficcer);
}

int GetSalaryForShip(ref chref)
{
    int i, cn, iMax;
    ref mchref, offref;
    int nPaymentQ = 0;
    mchref = GetMainCharacter();

	float nLeaderShip = GetSummonSkillFromNameToOld(mchref,SKILL_LEADERSHIP);
	float nCommerce   = GetSummonSkillFromNameToOld(mchref,SKILL_COMMERCE);
	if (!GetRemovable(chref) && int(chref.index) != GetMainCharacterIndex()) return 0; // считаем только своих, а то всяких сопровождаемых кормить!!!
		
	// экипаж: фиксированная месячная ставка матроса + мягкие модификаторы опыта, сложности, навыков и сезона
	nPaymentQ += GetMoneyForCrew(chref);
    
    // теперь самого капитана и его офицеров (тут  главный герой не считается) так что пассажиров и оффицеров ниже
    if(int(chref.index) != GetMainCharacterIndex())
    {
        nPaymentQ += int(GetMoneyForOfficer(chref)*2/(nLeaderShip + nCommerce) );
        // офицеры
        for(i = 1; i < 4; i++)  // в к3 нет офов у компаньона :(
	    {
	        cn = GetOfficersIndex(chref, i);
		    if( cn > 0 )
		    {
			    offref = GetCharacter(cn);
			    if (GetRemovable(offref)) // считаем только своих, а то вских сопровождаемых кормить!!!
			    {
			        nPaymentQ += int(GetMoneyForOfficerFull(offref));
			    }
			}
		}
	}
	if(int(chref.index) == GetMainCharacterIndex()) // все пассажиры и офицеры для гл героя
	{
        iMax = GetPassengersQuantity(mchref);
		for(i=0; i < iMax; i++)
        {
            cn = GetPassenger(mchref,i);
            if(cn != -1)
            {
                if(!IsCompanion(GetCharacter(cn)))
                {
                    offref = GetCharacter(cn);
                    if (GetRemovable(offref)) // считаем только своих, а то вских сопровождаемых кормить!!!
			        {
                        if(CheckAttribute(offref,"prisoned"))
    		            {
    			            if(int(offref.prisoned)==true) continue;
    		            }
    			        nPaymentQ += int(GetMoneyForOfficerFull(offref));
			        }
                }
            }
        }
    }
	
	if(GetCharacterEquipByGroup(mchref, HAT_ITEM_TYPE) == "hat5")
	{
		iMax = GetPassengersQuantity(mchref);
		for(i=0; i < iMax; i++)
        {
            cn = GetPassenger(mchref,i);
            if(cn != -1)
            {
                if(IsCompanion(GetCharacter(cn)))
                {
                    if(chref.index == cn) nPaymentQ = int(nPaymentQ*0.85);
                }
            }
        }
	}

	if (IsEquipCharacterByItem(chref, "hat8"))
	{
		int iThreat = wdmGetSummaryThreat();
		nPaymentQ = int(nPaymentQ * (1 - 0.02 * iThreat));
	}

	if (ShipBonus2Artefact(chref, SHIP_AMSTERDAM))
	{
		nPaymentQ = int(float(nPaymentQ) * (1 - GetAmsterdamMtp("")));
	}

	return nPaymentQ;
}
// boal новый учёт зп <--

int AddCrewMorale(ref chr, int add, bool withNotification = false)
{
	string nameBefore, nameAfter;
	int moraleBefore;
	if (add > 0) add = SZN_IncreaseIntByModifier(add, M_CREW_MORALE_MTP);

    int morale = MORALE_NORMAL;
	if (CheckAttribute(chr, "Ship.Crew.Morale")) morale = int(chr.Ship.Crew.Morale);
	nameBefore = GetExpName(morale);
	moraleBefore = morale;
    morale += add;
	if(morale < MORALE_MIN)	morale = MORALE_MIN;
	if(morale > MORALE_MAX)	morale = MORALE_MAX;
	nameAfter = GetExpName(morale);
	chr.Ship.Crew.Morale = morale;
	if(chr.id == pchar.id)
	{
		if(nameBefore != nameAfter && moraleBefore < morale)
		{
			AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 6.0);
		}
	}
	
	if (withNotification) notification(StringFromKey(add > 0 ? "food_18" : "food_19"), "Sailor");
	return morale;
}

float ChangeCrewExp(ref chr, string sType, float fNewExp, bool withNotification = false)
{
	float exp = chr.Ship.Crew.Exp$float(10.0);
	if (sType != "sailors") return exp;

	fNewExp *= isEquippedArtefactUse(chr, "totem_09", 1.0, 2.0);
	if (IsCompanion(chr)) fNewExp *= SZN_GetModifierMtp(M_CREW_EXP_MTP, 1.0, 0.01);
	exp += fNewExp;
	
	if (withNotification && fNewExp > 0) notification(StringFromKey("food_20"), "Sailor");
	chr.Ship.Crew.Exp = func_fmin(float(EXP_MAX), exp);
	return float(chr.Ship.Crew.Exp);
}

// 3 опыта сшиты в 1, код пока оставлен, чтобы везде не менять
float GetCrewExp(ref chr, string sType = "")
{
	if ("Ship.Crew.Exp" !in chr) chr.Ship.Crew.Exp = 10.0;

	float exp = func_fmax(0.0, chr.Ship.Crew.Exp$float(10.0));
	if (ShipBonus2Artefact(chr, SHIP_MEMENTO))
	{
		ref realShip = &RealShips[int(chr.Ship.Type)];
		exp += realShip.DeadSailors.SailorsExpBonus$float(0.0);
	}

	return func_fmin(float(EXP_MAX), exp);
}

void SetCrewExp(ref chr, float value)
{
	chr.Ship.Crew.Exp = func_fmin(float(EXP_MAX), value);
}

float GetCrewExpRate()
{
	return float(50 + MOD_SKILL_ENEMY_RATE);
}

int GetCharacterCrewMorale(ref chr, bool withoutBonus = false)
{
	if(!CheckAttribute(chr, "ship.crew.morale"))
	{
		chr.ship.crew.morale = MORALE_NORMAL;
	}

	if (withoutBonus) return int(chr.ship.crew.morale);
	
	if(GetCharacterIndex(chr.id) == GetMainCharacterIndex())
	{
		int iShipBonus = 0;
		int iCurCrewMorale = int(chr.ship.crew.morale);
		
		if(ShipBonus2Artefact(chr, SHIP_MEMENTO))
		{
			if(CheckAttribute(&RealShips[int(chr.Ship.Type)], "DeadSailors.SailorsMoraleBonus"))
			{
				iShipBonus = int(RealShips[int(chr.Ship.Type)].DeadSailors.SailorsMoraleBonus);
			}
		}
		if(iShipBonus > 0)
		{
			chr.ship.crew.morale.mementoBonus = iShipBonus;
		}
		else 
		{
			if(CheckAttribute(chr, "ship.crew.morale.mementoBonus"))
			{
				iCurCrewMorale -= int(chr.ship.crew.morale.mementoBonus);
				if(iCurCrewMorale < 0) iCurCrewMorale = 0;
				DeleteAttribute(chr, "ship.crew.morale.mementoBonus");
				chr.ship.crew.morale = iCurCrewMorale;
			}
		}
		iCurCrewMorale += iShipBonus;
		if(iCurCrewMorale > 100) iCurCrewMorale = 100;
		chr.ship.crew.morale = iCurCrewMorale;
	}
	
	return int(chr.ship.crew.morale);
}

// Получить базовый множитель рекрутов для таверны без учёта нации
float GetBaseCrewMtpForTavern()
{
	float fKrank = 1.0 + (2.5 - 1.0) * (pow(float(pchar.rank), 0.25) - 1.0) / (pow(40.0, 0.25) - 1.0);
	float fKcharisma = 1.0 + (2.5 - 1.0) * (pow(float(GetSummonSkillFromNameSimple(pchar, SKILL_LEADERSHIP)), 1.35) - 1.0) / (pow(100.0, 1.35) - 1.0);
	float fKrep = GetReputationCoef(abs(COMPLEX_REPUTATION_NEUTRAL - int(pchar.reputation.nobility)));
	float fSpecial = 1.0;
	if (CheckAttribute(pchar, "GenQuest.Shipshine")) fSpecial += 1.25;
	if (IsEquipCharacterByItem(pchar, "greenIdol")) fSpecial += 0.30;
	if (IsEquipCharacterByItem(pchar, "hat3")) fSpecial += 0.05;
	fSpecial += SZN_GetModifierMtp(M_RECRUITS_MTP, 0.0);
	return fKrank * fKcharisma * fKrep * fSpecial;
}

// Получить множитель рекрутов для нации
float GetNationCrewMtpForTavern(int iNation)
{
	float fKrelation = GetNationRelationCoef(ChangeCharacterNationReputation(pchar, iNation, 0));
	if (iNation != PIRATE) return fKrelation;

	ref ship = &RealShips[int(pchar.Ship.Type)];
	if (CheckAttribute(pchar, "questTemp.CharleePrince")) fKrelation += 0.5;
	if (ShipBonus2Artefact(pchar, SHIP_MEMENTO));
	{
		if (CheckAttribute(ship, "DeadSailors.RecruitPiratesBonus")) fKrelation += float(ship.DeadSailors.RecruitPiratesBonus);
	}

	return fKrelation;
}

// пересчет наёмников в городах
void UpdateCrewInColonies()
{
	int nNeedCrew = 0;
	ref rTown;
	int nPastQ, nPastM, iNation;
	int eSailors, eCannoners, eSoldiers;
	int processed = 0;
	aref bonuses;
	makearef(bonuses, TEV.CrewDate.bonuses);

	// Раз в неделю обновляем множитель рекрутов в тавернах по нациям
	if (GetNpcQuestPastDayParam(&TEV, "CrewDate") > 6 || !CheckAttribute(&TEV, "CrewDate.control_year"))
	{
		SaveCurrentNpcQuestDateParam(&TEV, "CrewDate");
		float baseCrewMtp = GetBaseCrewMtpForTavern();
		Log_TestInfo("Обновили модификатор рекрутов, теперь он " + baseCrewMtp + " до учёта нации");
		for (int j=0; j < MAX_NATIONS; j++)
		{
			string nationAttr = "n"+j;
			bonuses.(nationAttr) = baseCrewMtp * GetNationCrewMtpForTavern(j);
		}
	}

	for(int i=0; i < MAX_COLONIES; i++)
	{
		rTown = &colonies[i];
		if (rTown.nation == "none") continue;
		if (rTown.id == "IslaMona") continue;
		if (rTown.id == "SanAndres") continue;

		// belamour legendary edition 
		DeleteAttribute(rTown, "AdditionalCrew");
		DeleteAttribute(rTown, "AddCrewTalisman9");
		int daysPast = GetNpcQuestPastDayParam(rTown, "CrewDate");

		if (daysPast < (3 + rand(2)) && CheckAttribute(rTown, "CrewDate.control_year")) continue;
		SaveCurrentNpcQuestDateParam(rTown, "CrewDate");

		nPastQ = 0;
		if (CheckAttribute(rTown,"ship.crew.quantity"))	nPastQ = int(rTown.ship.crew.quantity);
		iNation = int(rTown.nation);

		float cityMaxCrew = float(GetAttributeValue(GetAttributeN(bonuses, iNation))) * 16.2; // Сколько было бы людей в таверне при идеальном броске кубика
		nNeedCrew = int(cityMaxCrew * (0.6 + rand(40) * 0.01)); // hrand(40, rTown.id)  // фактическое от 60 до 100%

		int excessCrew = nPastQ - int(cityMaxCrew);
		if (excessCrew > 10)
		{
			nNeedCrew += int(float(excessCrew) * 0.9);
			rTown.Ship.Crew.HasExcess = true; // отметка, чтобы показать эффект присутствия лишних матросов
		}
		else DeleteAttribute(&rTown, "Ship.Crew.HasExcess");

		rTown.Ship.crew.quantity = nNeedCrew;
		processed++;
		if (processed > 9) break;
		if (daysPast < 5) continue;

		if (nPastQ > nNeedCrew)
			nPastM = MORALE_NORMAL/3 + rand(MORALE_MAX-MORALE_NORMAL/3);
		else
			nPastM = MORALE_NORMAL/5 + rand(int(MORALE_NORMAL*1.5));
		nPastM = int(float(nPastM) * SZN_GetModifierMtp(M_CREW_HIRE_MORALE_MTP, 1.0, 0.01, 2.0));
		rTown.Ship.crew.morale = nPastM;
		rTown.Ship.Crew.Exp = (45 + rand(100)) * SZN_GetModifierMtp(M_CREW_HIRING_EXP_MTP, 1.0, 0.01);

		ChangeCrewExp(rTown, "Sailors", 0);
	}
}

int GetCrewPriceForTavern(string sColony)
{
	int iColony = FindColony(sColony);
	ref rTown = &colonies[iColony];
	if(rTown.id == "IslaMona") return 0;

	// Найм матроса = недельный аванс от новой месячной ставки.
	// Используем те же мягкие множители, что и для месячной зарплаты экипажа:
	// опыт городских рекрутов, сложность, Торговля+Харизма игрока и сезон найма.
	float crewCost = CREW_SAILOR_MONTHLY_SALARY * CREW_HIRE_ADVANCE_MTP;
	crewCost *= GetCrewSalaryExpMtp(rTown);
	crewCost *= GetCrewSalaryDifficultyMtp();
	crewCost *= GetCrewSalarySkillMtp(GetMainCharacter());
	crewCost *= SZN_GetModifierMtp(M_CREW_HIRE_COST, 1.0, 0.01);

	if (IsEquipCharacterByItem(pchar, "hat3")) crewCost *= 0.95;

	int nCrewCost = int(crewCost);
	if (nCrewCost < 10) nCrewCost = 10; // не ниже!
	return nCrewCost;
}

float GetNationRelationCoef(int rel)
{
	if (rel < 0 )    return 0.85;
    if (rel <= 20 )  return 1.0;
    if (rel <= 50 )  return 1.2;
    if (rel <= 80 )  return 1.5;
    if (rel <= 100 ) return 1.85;
	
	return 0.85;
}

float GetReputationCoef(int rep)
{
	return Bring2Range(1.0, 1.35, 0.0, 50.0, float(rep));
}

int GetMaxCrewAble()
{
	float nLeaderShip = 0.5 + GetSummonSkillFromNameToOld(pchar, SKILL_LEADERSHIP);
	return int(nLeaderShip*(55.0 + 10*(5-MOD_SKILL_ENEMY_RATE) + nLeaderShip * 15.0) + 2*nLeaderShip*abs(REPUTATION_NEUTRAL - int(pchar.reputation.nobility)));
}

int GetCurCrewEscadr()
{
	int i, cn;
	int nNeedCrew = 0;
	
	for(i=0; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(GetMainCharacter(),i);
		if(cn>=0 && GetRemovable(&Characters[cn]))
		{
			nNeedCrew += GetCrewQuantity(GetCharacter(cn));
		}
	}
	return nNeedCrew;
}

void MunityOnShip(string _stat)
{
	int i;
	Statistic_AddValue(pchar, _stat, 1);
	MakeCloneShipDeck(pchar, true); // подмена палубы
	i = FindLocation("Ship_deck");
	Locations[i].image = "loading\Mutiny_512.tga"; // это клоновая локация, вернётся само при перетирании другим
	DoQuestReloadToLocation("Ship_deck", "reload", "reload1", "Munity_on_Ship");
}
/* 20.01.08 Дележ добычи =======================================================================
Концепт:
Делим только награбленное, торговые, квестовые барыши не делим (выпадают сухупутные грабежи)
Для этого считаем сколько было денег до выхода в море, после моря и баталии, на карте и суше подсчет денег после
Сравниваем, если убытки, ничего не делаем, если доходы, то к дележу.
Сумма может быть не выплачена сразу, наличие суммы влияет на мораль как и ЗП.
Повышение морали погашает задолженность, если долгов нет, то плата просто так
Наличие долгов делает -1 морали каждый день, ром может спасти, а может и нет, если ещё и перегруз
Долги наследуются, даже, если все умерли. Это условность, но необходимо же как-то с ГГ стрести деньги.
Товар и корабли считаются по условно-минимальным ценам, то есть ГГ покупает их у команды и платит долю по бросовой цене.
Общая ЗП при этом сохраняется, так как доходы от торговли и контрабанды не делятся.
Грабеж города считаем условно поделенным, то есть матросы нахапали свои доли сами и не делим дополнительно (сложно делать и барышей там мало).
*/
void Partition_SetValue(string state) // state = "before" || "after" - для сравнения было-стало
{
	if (CheckAttribute(pchar, "GenQuest.DontPartition"))
	{
		DeleteAttribute(pchar, "GenQuest.DontPartition");
		Log_TestInfo("Дележ добычи не производится!");
		return;
	} // Jason
	
	int      ret, part;
	int      i, cn, iMax;
	ref      chref;
	int      HowOff, HowComp, HowCrew, HowGower;
	string   sTemp;
	
	// пройтись по всей недвижимости, налику у пассажиров и компаньонов, оценить состав матросов в начале - если 0,
	// то остальные пришли потом, не положена доля
	ret = 0;
	// допуск - не считаем ростовщиков, тк в море их нет и предметы личные, тк это мародёрство без дележа
	// деньги в офах - это деньги ГГ на хранении их считаем, тк потеря их - убыток ГГ
	HowComp = 0;
	HowCrew = 0;
	Partition_GetCargoCostCoeff(state);
	part = Part_HeroPart + (9 - MOD_SKILL_ENEMY_RATE/2)*Part_HeroPart; // доля ГГ
	for (i=0; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(Pchar, i);
		if (cn >= 0)
		{
			chref = GetCharacter(cn);
			if (GetRemovable(chref)) // считаем только своих
			{
				ret += int(chref.Money);
				ret = ret + Partition_GetCargoValue(chref); // деньги на кармане и корабль
				HowComp += 1; // ГГ тут же
				HowCrew += GetCrewQuantity(chref);
				part += Part_CompanionShipPerClass * (7 - GetCharacterShipClass(chref));
			}
		}
	}
	
	HowOff = 0;
	iMax = GetPassengersQuantity(Pchar);
	for(i=0; i < iMax; i++)
	{
		cn = GetPassenger(Pchar, i);
		if(cn != -1)
		{
			chref = GetCharacter(cn);
			if (GetRemovable(chref)) // считаем только своих
			{
				if(CheckAttribute(chref, "prisoned"))
				{
					if(int(chref.prisoned)) continue;
				}
				
				ret += int(chref.Money);
				HowOff += 1;
			}
		}
	}
	// предметы в каюте
	ref loc;
	if (Pchar.SystemInfo.CabinType != "")
	{
		loc = &locations[FindLocation(Pchar.SystemInfo.CabinType)];
		
		for (i = 1; i <= 4; i++)
		{
			sTemp = "box" + i;
			if (CheckAttribute(loc, sTemp + ".money"))
			{
				ret += int(loc.(sTemp).money);
			}
		}
	}
	
	if (isMainCharacterPatented())	HowGower = Part_Gower + (MOD_SKILL_ENEMY_RATE);
	else 							HowGower = 0;
	
	Pchar.Partition.(state).Money    = ret;
	Pchar.Partition.(state).HowOff   = HowOff;
	Pchar.Partition.(state).HowComp  = HowComp - 1;
	Pchar.Partition.(state).HowCrew  = HowCrew;
	Pchar.Partition.(state).HeroPart = part;
	
	Log_TestInfo("Partition_SetValue." + state + " Money " + ret + " Off " + HowOff + " Comp " + (HowComp -1) + " Crew " + HowCrew + " Gower " + HowGower);
	if (state == "after" && CheckAttribute(Pchar, "Partition.before.Money"))
	{
		if (int(Pchar.Partition.before.Money) < int(Pchar.Partition.after.Money))
		{  // Делим бабки	
			if(bPartitionSet)
			{
				int    TotalAmount, iGowerPart;
				float  fOffPart, fCrewPart, fHeroPart;
				TotalAmount = int(Pchar.Partition.after.Money) - int(Pchar.Partition.before.Money);
				Log_TestInfo("Общий доход составил " + TotalAmount);
				
				iGowerPart = int(HowGower * TotalAmount/100.0);
												
				TotalAmount -= iGowerPart;  
				
				HowOff  = Pchar.Partition.before.HowOff$int(0);
				HowComp = Pchar.Partition.before.HowComp$int(0);
				HowCrew = Pchar.Partition.before.HowCrew$int(0);
								
				HowCrew = HowCrew * Part_Crew;
				HowOff  = HowOff * Part_Officer + HowComp * Part_Companion;
				fHeroPart = float(Pchar.Partition.before.HeroPart);
				
				fCrewPart = HowCrew / (HowCrew + HowOff + fHeroPart);
				fOffPart  = HowOff / (HowCrew + HowOff + fHeroPart);
				
				if (!CheckAttribute(Pchar, "Partition.MonthPart"))           Pchar.Partition.MonthPart = 0;
				if (!CheckAttribute(Pchar, "Partition.MonthPart.Crew"))      Pchar.Partition.MonthPart.Crew = 0;
				if (!CheckAttribute(Pchar, "Partition.MonthPart.Officers"))  Pchar.Partition.MonthPart.Officers = 0;
				if (!CheckAttribute(Pchar, "Partition.MonthPart.Hero"))      Pchar.Partition.MonthPart.Hero = 0;
				if (!CheckAttribute(Pchar, "Partition.MonthPart.Gower"))     Pchar.Partition.MonthPart.Gower = 0;
				
				Pchar.Partition.MonthPart.Gower = int(Pchar.Partition.MonthPart.Gower) + iGowerPart;
				
				if (isMainCharacterPatented())
				{
					Log_TestInfo("Доля губернатора составила " + iGowerPart + " Долг перед губернатором " + Pchar.Partition.MonthPart.Gower);
				}	
				
				ret = int(fCrewPart * TotalAmount);
				Pchar.Partition.MonthPart.Crew     = int(Pchar.Partition.MonthPart.Crew) + ret;
				Pchar.Partition.MonthPart.Officers = int(Pchar.Partition.MonthPart.Officers) + int(fOffPart * TotalAmount);
				ret += int(fOffPart * TotalAmount);
				
				Pchar.Partition.MonthPart.Hero = int(Pchar.Partition.MonthPart.Hero) + (TotalAmount - ret);
				Pchar.Partition.MonthPart = int(Pchar.Partition.MonthPart) + ret;
				Log_TestInfo("Доля команды " + ret + ". Долг перед командой " + Pchar.Partition.MonthPart);			
			}
		}
	}
}


int Partition_GetCargoValue(ref chref)
{
	float    ret;
	int      i, st, idx;
	ref      rGood;
	string   sGood;
	ref      shref;
	ref      Cannon;
	float	 costCoeff;
	
	ret = 0;
	//return 0;
	st = GetCharacterShipType(chref);
	
	if (st != SHIP_NOTUSED)
	{
		shref = GetRealShip(st);
		
		ret += int(shref.Price) * 0.3; // 0.3 - понижение стоимости корабля для грабежа
		// пушки считаем по бортам
		if (int(chref.Ship.Cannons.Type) != CANNON_TYPE_NONECANNON)
		{
		    Cannon = GetCannonByType(int(chref.Ship.Cannons.Type));
			idx = GetCannonGoodsIdxByType(int(chref.Ship.Cannons.Type)); // индекс орудия как товара
			sGood = Goods[idx].name;
			if(CheckAttribute(pchar,"Goods." + (sGood)+ ".costCoeff")) 
			{
				costCoeff = float(pchar.Goods.(sGood).costCoeff);
			}
			else costCoeff = 1.0;	
		    ret += int(Cannon.Cost) * 0.4 * costCoeff * GetCannonsNum(chref);
		}
		for (i=0; i<GetArraySize(&Goods); i++)
		{
			sGood = Goods[i].name;
			costCoeff = 1.0;
			if(CheckAttribute(pchar,"Goods." + (sGood) + ".costCoeff")) costCoeff = float(pchar.Goods.(sGood).costCoeff);
			if(i > GOOD_CANNON_3 - 1)
			{
				ret += float(GetCargoGoods(chref, i) * int(Goods[i].Cost) * 0.33 * costCoeff / float(Goods[i].Units));
			}
			else
			{
				ret += float(GetCargoGoods(chref, i) * int(Goods[i].Cost) * 0.7 * costCoeff / float(Goods[i].Units));
			}	
		}
	}
	return int(ret);
}

void Partition_GetCargoCostCoeff(string state) // state = "before" || "after" - для сравнения было-стало
{
	int 		i, j, cn, st, ret, idx;
	string   	sGood;
	ref         chref, cannon;
	
	//trace("Partition_GetCargoCostCoeff    state :"+state);
	for (i=0; i<GetArraySize(&Goods); i++)
	{
		sGood = Goods[i].name;
		if(i > GOOD_CANNON_3 - 1) // учёт пушек - как установленных, так и в виде товара
		{
			ret = 0;			
			for (j=0; j<COMPANION_MAX; j++)
			{
				cn = GetCompanionIndex(Pchar, j);
				if (cn >= 0)
				{
					chref = GetCharacter(cn);
					if (GetRemovable(chref)) // считаем только своих
					{
						st = GetCharacterShipType(chref);
						if (int(chref.Ship.Cannons.Type) != CANNON_TYPE_NONECANNON)
						{
							idx = GetCannonGoodsIdxByType(int(chref.Ship.Cannons.Type));
							if(idx == i) ret += GetCannonsNum(chref);
						}
					}
				}
			}			
			pchar.partition.(state).(sGood) = GetSquadronGoods(pchar, i) + ret;
			RecalculateCargoCostCoeff(pchar, state, sGood, int(pchar.partition.(state).(sGood)));
		}
		else
		{
			pchar.partition.(state).(sGood) = GetSquadronGoods(pchar, i);
			RecalculateCargoCostCoeff(pchar, state, sGood, int(pchar.partition.(state).(sGood)));
		}
	}
	
}

void RecalculateCargoCostCoeff(ref _refCharacter, string state, string _goodsName, int _Qty)
{
/*
state = "before" - перед выходом в море или до начала грабежа города - коэффициент цены на все новые товары = 1.0
state = "after"  - перед выходом на сушу или после грабежа города    - коэффициент цены на все новые товары = 0.80 - MOD_SKILL_ENEMY_RATE * 0.05
*/
	int 	oldQty					= 0;
	float 	oldPriceCoeff 			= 1.0;
	float 	newPriceCoeff 			= 1.0;	
	float 	validateNewGoodQuality 	= 1.0;
	
	if(state == "after")
	{
		validateNewGoodQuality = 0.80 - MOD_SKILL_ENEMY_RATE * 0.05;
	}	
	
	if(_Qty > 0)
	{
		if(CheckAttribute(_refCharacter,"Goods." + (_goodsName) + ".costCoeff"))
		{
			oldPriceCoeff = float(_refCharacter.Goods.(_goodsName).costCoeff);
		}
		else
		{
			_refCharacter.Goods.(_goodsName).costCoeff = oldPriceCoeff;
		}	
		if(CheckAttribute(_refCharacter, "partition." + (state) + "." + (_goodsName)))
		{
			switch (state)
			{
				case "before" 	:
					if(CheckAttribute(pchar,"partition.after." + (_goodsName)))
					{
						oldQty = int(pchar.partition.after.(_goodsName));
					}
					else oldQty = 0;
				break;
				case "after"	:
					if(CheckAttribute(pchar,"partition.before." + (_goodsName)))
					{
						oldQty = int(pchar.partition.before.(_goodsName));
					}	
					else oldQty = 0;
				break;
			}
		}
		else oldQty = 0;
		
		if(_Qty > oldQty)
		{
			_Qty = _Qty - oldQty;
			newPriceCoeff = (oldQty * oldPriceCoeff + validateNewGoodQuality * _Qty)/ (oldQty + _Qty);
		}
		else newPriceCoeff = oldPriceCoeff;
	}
	else
	{
		newPriceCoeff = 1.0;
	}
//	trace("goodsName " + _goodsName + " oldQty " + oldQty + " Qty " + _Qty + " oldCostCoeff " + oldPriceCoeff +" newCostCoeff " + newPriceCoeff);

	_refCharacter.Goods.(_goodsName).costCoeff = newPriceCoeff;
}
