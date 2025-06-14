/******************************************************************************************
			belamour Caribbean Legend работа с ачивками
*******************************************************************************************/
void Achievment_Set(string achID)
{
	if(achID == "") return;
	SetAchievement(achID);
}

void Achievment_SetStat(int achievNum, int _add)
{
	string statID = Stat_GetID(achievNum);
	if(statID == "")
	{
		trace("Achievments: No ID for Stat - " + achievNum);
		return;
	}
	int curState = GetStat(statID);
	int maxState = GetMaxState(achievNum);
	if(curState + _add > maxState) SetStat(statID, maxState);
	else SetStat(statID, curState + _add);
	StoreStats();
}

string Stat_GetID(int achievNum)
{
	string id = "";
	switch (achievNum)
	{
		case  1  :	id = "stat_03"; break;
		case  2  :	id = "stat_02"; break;
		case  3  :	id = "stat_03"; break;
		case  6  :	id = "stat_06"; break;
		case  7  :	id = "stat_07"; break;
		case  8  :	id = "stat_08"; break;
		case 21  :	id = "stat_21"; break;
		case 22  :	id = "stat_22"; break;
		case 23  :	id = "stat_23"; break;
		case 24  :	id = "stat_24"; break;
		case 25  :	id = "stat_25"; break;
		case 26  :	id = "stat_26"; break;
		case 27  :	id = "stat_27"; break;
		case 29  :	id = "stat_29"; break;
		case 31  :	id = "stat_31"; break;
		case 34  :	id = "stat_34"; break;
		case 35  :	id = "stat_35"; break;
		case 36  :	id = "stat_36"; break;
		case 37  :	id = "stat_37"; break;
		case 38  :	id = "stat_38"; break;
		case 39  :	id = "stat_39"; break;
		case 40  :	id = "stat_40"; break;
		case 41  :	id = "stat_41"; break;
		case 43  :	id = "stat_43"; break;
		case 50  :	id = "stat_50"; break;
		case 52  :	id = "stat_52"; break;
		case 53  :	id = "stat_53"; break;
		case 59  :	id = "stat_59"; break;
		case 60  :	id = "stat_60"; break;
		case 61  :	id = "stat_61"; break;
		case 62  :	id = "stat_62"; break;
		case 64  :	id = "stat_64"; break;
		case 68  :	id = "stat_68"; break;
		case 94  :	id = "stat_CL_94"; break;
		case 95  :	id = "stat_CL_95"; break;
		case 101  :	id = "stat_CL_101"; break;
		case 106  :	id = "stat_CL_106"; break;
		case 120  :	id = "stat_duelist"; break;
	}
	return id;
}

int GetMaxState(int StateNum)
{
	int curState = 0;
	switch (StateNum)
	{
		case 2  :	// Абордажник - абордаж кораблей (250)
			curState = 250;
		break;
		case 3  :	// Морской волк - уничтожение кораблей (500)
			curState = 500;
		break;		
		case 6 :	// Покрытый шрамами : потрачено здоровья >= 10000
			curState = 10000;			
		break;
		case 7 :	// Алхимик : кол-во актов алхимии >= 200
			curState = 200;
		break;	
		case 8	:	// Кладоискатель : (>= 100 вырытых кладов;
			curState = 100;	
		break;					
		
		case 21  :	// Душегуб : 9999 погибших матросов в экипаже ГГ
			curState = 9999;
		break;
		case 22  :	// Ветеран : разгромить >= 15 фортов
			curState = 15;	
		break;
		case 23  :	// Ветреный " посетить бордель 100 раз
			curState = 100;
		break;
		case 24  :	// Постоялец : заночевать в таверне >=50 раз
			curState = 50;
		break;
		case 25  :	// Азартный игрок : (выигрыш в карты/кости >= 500 ;	
			curState = 500;
		break;
		case 26  :	// Транжира : (проигрыш в карты/кости >= 500 ;		
			curState = 500;	
		break;
		case 27  :	// снайпер : убийство из пистолета >= 500
			curState = 500;	
		break;		
		
		case 29  :	// Доброе сердце : взять в команду кораблекрушенцев (>= 100)
			curState = 100;	
		break;		
			
		case 31  :	// Контрабандист : >=50 удачных сделок с контрабандистами
			curState = 50;	
		break;		
		case 34  :	// Гибель врагам : убийство военных (>=500)
			curState = 500;
		break;
		case 35  :	// Безжалостный : убийство гражданских (>= 500)
			curState = 50;	
		break;
		case 36  :	// Конкистадор :  убийство индейцев (>=250)
			curState = 250;			
		break;
		case 37  :	// Экзорцист :  убийство нечисти (>=100)
			curState = 100;		
		break;
		case 38  :	// Красная книга : убийство крабов (>=35)
			curState = 35;			
		break;
		case 39  :	// Торговец : Заработать торговлей/перепродажей 10000000
			curState = 10000000)					
		break;		
		case 40  :	// Исследователь : исследовать данжи (>=50)
			curState = 50;					
		break;
		case 41  :	// Щедрый : раздать милостыню 200 раз
			curState = 200;					
		break;			
		case 43  :	// Работорговец : продажа >= 5000 рабов
			curState = 5000;						
		break;		
		
		case 47  :	// Простодушный -  провальный финал
			curState = 1;			
		break;	
		case 50  :	// Морской разбойник -  утопить под пиратским флагом >=100 кораблей
			curState = 100;
		break;	
		
		case 52  :  // "Законник" - убийство бандитов >= 250
			curState = 250;				
		break;
		case 53  : // "Гроза Архипелага" - убийство пиратов >= 50
			curState = 50;					
		break;
		
		case 59  :  // за 50 поднятых бочёнков (энкаунтер на глобальной карте;
			curState = 50;			
		break;
		case 60  :  // за 20 спасённых капитанов (энкаунтер на глобальной карте)
			curState = 20;			
		break;
		case 61  :  // за 200 сброшенных/установленных в бою мин
			curState = 200;								
		break;
		
		case 64  :  // за самостоятельный ремонт в бухте
			curState = 5;						
		break;
		
		case 68  :  // за несколько купленных фальшивых карт кладов  (5;
			curState = 5;
		break;
		
		case 94  :  // забрать 5 партий багаута с Исла моны
			curState = 5;
		break;
		case 95  :  // застрелить троих в диалоге
			curState = 3;
		break;
		case 101  :  // собрать 20 кладов в режиме SandBox
			curState = 20;
		break;
		case 106  :  // торг в диалогах
			curState = 2;
		break;
		case 120  :  // Победить в генераторных дуэлях 10 раз
			curState = 10;
		break;
	}
	return curState;
}

void CheckAchievments()
{	
	// Легендарный :  уровень >= 40
	if(sti(pchar.rank) >= 40) Achievment_Set("ach_05");
	// Баловень судьбы : (удача = 100%)
	if(GetSkillValue(pchar, SKILL_TYPE, SKILL_FORTUNE) >= 100)	Achievment_Set("ach_11");
	// Фехтовальщик : (фехт в ЛО = 100%)
	if(GetSkillValue(pchar, SKILL_TYPE, SKILL_F_LIGHT) >= 100)	Achievment_Set("ach_12");
	// Гусар : (фехт в СО = 100%)
	if(GetSkillValue(pchar, SKILL_TYPE, SKILL_FENCING) >= 100)	Achievment_Set("ach_13");
	// Драгун : (фехт в ТО = 100%)
	if(GetSkillValue(pchar, SKILL_TYPE, SKILL_F_HEAVY) >= 100)	Achievment_Set("ach_14");
	// Шпион : (скрытность = 100%)
	if(GetSkillValue(pchar, SKILL_TYPE, SKILL_SNEAK) >= 100)	Achievment_Set("ach_15");
	// Крепкий орешек : (защита = 100%)
	if(GetSkillValue(pchar, SKILL_TYPE, SKILL_DEFENCE) >= 100)	Achievment_Set("ach_16");
	// Адмирал : (навигация = 100%)
	if(GetSkillValue(pchar, SKILL_TYPE, SKILL_SAILING) >= 100)	Achievment_Set("ach_17");
	// Негоциант : (торговля = 100%)
	if(GetSkillValue(pchar, SKILL_TYPE, SKILL_COMMERCE) >= 100) Achievment_Set("ach_18");				
	// Джедай :  достичь максимальной репутации
	if(sti(pchar.reputation.nobility) > 95) Achievment_Set("ach_19");
	// Ситх : достичь минимальной репутации
	if(sti(pchar.reputation.nobility) < 5) Achievment_Set("ach_20");
	// Скряга : сколотить капитал >= 10 000 000
	if(sti(pchar.money) >= 10000000) Achievment_Set("ach_28");
	// Флотоводец : собрать максимальную эскадру
	if(GetRemovableCompanionsNumber(pchar) == COMPANION_MAX) Achievment_Set("ach_30");
	// Болезненный : уронить здоровье до минимума
	if(GetHealthNum(pchar) < 2) Achievment_Set("ach_32");
	// Коллекционер : собрать коллекцию из 100 сокровищ
	if(CheckItemMyCabin("icollection") >= 100 || GetCharacterItem(pchar, "icollection") >= 100 ) Achievment_Set("ach_33");
	// Ростовщик :  вклады у ростовщиков на 5000000 песо
	if(CheckTotalDepositsSum(pchar, 5000000)) Achievment_Set("ach_42");
	// Ветер Перемен -  прохождение за Голландию
	if(CheckAttribute(pchar,"questTemp.HWIC.Detector") && (pchar.questTemp.HWIC.Detector == "holl_win")) Achievment_Set("ach_44");
	// На службе Империи -  прохождение за Англию
	if(CheckAttribute(pchar,"questTemp.HWIC.Detector") && (pchar.questTemp.HWIC.Detector == "eng_win")) Achievment_Set("ach_45");
	// Не зная страха - прохождение "Против всех"
	if(CheckAttribute(pchar,"questTemp.HWIC.Detector") && (pchar.questTemp.HWIC.Detector == "self_win")) Achievment_Set("ach_46");
	// "Путешественник" - посетить все колонии (таверны) 
	if(sti(pchar.questTemp.TavernVisit.counter) == 28) Achievment_Set("ach_54");
	// "Команда профессионалов" - нанять офицеров на все должности
	if(CheckForAllOfficers()) Achievment_Set("ach_55");
	// за три приготовленных зелья из Мангаросы
	if(CheckAttribute(pchar, "Mangarosa.Alchemy.MP") && CheckAttribute(pchar, "Mangarosa.Alchemy.MF") && CheckAttribute(pchar, "Mangarosa.Alchemy.MT")) Achievment_Set("ach_62");
	// за ремонт на всех верфях архипелага
	if(sti(pchar.questTemp.ShipyardVisit.counter) == 23) Achievment_Set("ach_63");
	// за полный апгрейд корабля
	if(CheckAttribute(pchar, "achievment.Tuning.stage1") && CheckAttribute(pchar, "achievment.Tuning.stage2") && CheckAttribute(pchar, "achievment.Tuning.stage3") && CheckAttribute(pchar, "achievment.Tuning.stage4")) Achievment_Set("ach_66");
	if(CheckAttribute(pchar,"Achievment.Barbie") && CheckAttribute(pchar,"Achievment.Genrih")) Achievment_Set("ach_CL_111");
	// дальше будет только хуже
	if(!GetAchievement("ach_CL_113"))
	{
		if(CheckAttribute(pchar,"reputation.enghunter") && CheckAttribute(pchar,"reputation.frahunter") && CheckAttribute(pchar,"reputation.spahunter") && CheckAttribute(pchar,"reputation.holhunter"))
		{
			if(sti(pchar.reputation.enghunter) > 99 && sti(pchar.reputation.frahunter) > 99  && sti(pchar.reputation.spahunter) > 99 && sti(pchar.reputation.holhunter) > 99)
			{
				Achievment_Set("ach_CL_113");
			}
		}
	}
	// неканонично
	if(startHeroType != 2 && !GetAchievement("ach_CL_124"))
	{
		if(CheckAttribute(pchar,"reputation.spahunter") && sti(pchar.reputation.spahunter) < -99)
			Achievment_Set("ach_CL_124");
	}
	
	if(!GetAchievement("ach_CL_143")) 
	{
		int hatsQ = 0;
		for(int n = 1; n < 9; n++)
		{
			if(GetCharacterItem(pchar, "hat"+n)) hatsQ++;
		}
		if(hatsQ > 7) Achievment_Set("ach_CL_143");
	}
	
	// ачивки и статы фриплея -->
	if(SandBoxMode)
	{
		if(sti(pchar.money) >= 1000000)
		{
			Achievment_Set("ach_CL_98");
		}
		if(CheckAttribute(pchar,"questTemp.Portugal.GG1") || CheckAttribute(pchar,"questTemp.Portugal.GG2")) pchar.questTemp.SanBoxTarget.Portugal = true;
		if(CheckAttribute(pchar,"questTemp.SanBoxTarget.RedChieftain") && CheckAttribute(pchar,"questTemp.SanBoxTarget.FalseTrace") && CheckAttribute(pchar,"questTemp.SanBoxTarget.Slavetrader")  && CheckAttribute(pchar,"questTemp.SanBoxTarget.Portugal"))
		{
			Achievment_Set("ach_CL_100");
			pchar.questTemp.SanBoxTarget.AllQuests = true;
			ChangeCharacterComplexReputation(pchar, "fame", COMPLEX_REPUTATION_MAX);
		}
		if(sti(pchar.money) >= 1000000 && CheckAttribute(pchar,"questTemp.SanBoxTarget.ColonyCaptured") && CheckAttribute(pchar,"questTemp.SanBoxTarget.AllQuests") && Statistic_AddValue(Pchar, "Treasure", 0) > 19)
		{
			Achievment_Set("ach_CL_102");
		}
	}
}

// belamour cle 1.5 пожарные бригады
void CheckFireBrigadeAchievements(int iNation, string sWinType)
{
	string shortName = NationShortName(iNation);
	if(!CheckAttribute(pchar,"Achievment.FireBrigade." + shortName))
	{
		if(iNation == SPAIN) Achievment_Set("ach_CL_158");
		pchar.Achievment.FireBrigade.(shortName) = true;
	}
	if(SandBoxMode && !GetAchievement("ach_CL_160"))
	{
		int fireBrigadeWinQty = 0;
		for(int i = 0; i <= NON_PIRATES; i++)
		{
			shortName = NationShortName(i);
			if(CheckAttribute(pchar,"Achievment.FireBrigade." + shortName))
				fireBrigadeWinQty ++;
		}
		if(fireBrigadeWinQty > NON_PIRATES) Achievment_Set("ach_CL_160");
	}
}