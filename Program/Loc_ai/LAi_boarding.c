#include "Loc_ai\boarding\boarding.h"
#include "Loc_ai\boarding\situations.c"
#include "Loc_ai\boarding\coordinated_boarding.c"
#include "Loc_ai\boarding\utility_helpers.c"
#include "Loc_ai\boarding\fight_helpers.c"
#include "Loc_ai\boarding\looting.c"
#include "Loc_ai\boarding\balance.c"

bool   IsFort = false; 
int    boarding_location = -1;
int    boarding_location_type = -1;
object boarding_fader;
int   boarding_player_crew = 0;
int   boarding_officers    = 0;
float boarding_player_base_crew    = 0.0; //boal
float boarding_player_crew_per_chr = 1.0;
int   boarding_player_crew_start   = 0; //sd

int   boarding_enemy_crew = 0;
float boarding_enemy_base_crew    = 0.0;
float boarding_enemy_crew_per_chr = 1.0;
int   boarding_enemy_crew_start   = 0; //sd

ref    boarding_enemy;
object boarding_adr[4];
float  boarding_exp = 0;
float  boarding_player_hp = 40;
float  boarding_enemy_hp = 40;
int    boarding_echr_index = -1;
int    boarding_erank = 10; // лишняя переменная, не удалена, чтобы не пердело ошибок
bool   LAi_boarding_process = false;
bool   Surrendered = false; // сдача в плен

int inside_ecrew_1, inside_ecrew_2;


//Начать абордаж с главным персонажем
void LAi_StartBoarding(int locType, ref echr, bool _isMCAttack)
{
	SendMessage(&Particles,"l", PS_CLEAR_CAPTURED); // повторное удаление партиклов, фикс огней в море.
	ResetSound();
	PauseAllSounds();
	bQuestCheckProcessFreeze = true;
	
	EmptyAbordageCharacters();
	IsFort = locType == BRDLT_FORT;

	//Установим обработчик на убийство группы
	SetEventHandler("LAi_event_GroupKill", "LAi_BoardingGroupKill", 1);
	//Настроим интерфейс
	DeleteBattleInterface();
	InitBattleLandInterface();
	//StartBattleLandInterface();
	//Сохраним индекс врага
	boarding_echr_index = sti(echr.index);
	//Параметры сражающихся сторон
	int mclass = GetCharacterShipClass(pchar); // класс корабля ГГ
	int mcrew = GetCrewQuantity(pchar); // число команды ГГ
	
	// Saving enemy captain rank for future use in CalculateAppropriateSkills (Gray 12.02.2005)
	pchar.EnemyRank = echr.rank
	
	DeleteAttribute(pchar, "abordage_active");
	Log_TestInfo("Наших до оружия " + mcrew);
	mcrew = GetWeaponCrew(pchar, mcrew);

	int eclass = GetCharacterShipClass(echr); // класс корабля НПС
	int ecrew = GetCrewQuantity(echr); // число команды НПС

	Log_TestInfo("Наших с оружием " + mcrew + " Врагов " + ecrew);
	boarding_location_type = locType;

	if (echr.id == "WorldMarchCap1" || echr.id == "WorldMarchCap2" || echr.id == "WorldMarchCap3")
	{
		if (!CheckAttribute(pchar, "GenQuest.MarchCap.Battlestart")) DoQuestFunctionDelay("MarchCap2_CheckBattle", 0.5); //Jason
	}
	//Jason, изъятие лицензии
	bool blic = (CheckAttribute(echr, "Ship.Mode")) && (echr.Ship.Mode == "trade");
	if (CheckCharacterItem(pchar, "HolTradeLicence"))
	{
		if (blic || sti(echr.nation) == HOLLAND)
		{
			TakeNationLicence(HOLLAND);
			log_info(XI_ConvertString("LicenseCancel"));
		}
	}

	if(!GetAchievement("ach_CL_123") && !IsFort)
 	{
 		if(GetHullPercent(pchar)<10.0) Achievment_Set("ach_CL_123");
 	}
	
	if (BRD_ProcessSurrender(pchar, echr, IsFort, mclass, eclass)) return; // Сдача в плен
	if (!IsFort) BRD_FireMusketsShoot(pchar, echr, mclass, eclass, &mcrew, &ecrew);    // мушкетный залп
	trace("псле мушкетных залпов: " + ecrew + " а mcrew " + mcrew);

	// база для расчета
	boarding_enemy_base_crew = ecrew;
	boarding_player_base_crew = mcrew;
	//Количество хитпойнтов для бонуса - учёт опыта солдат
	GetBoardingHP(pchar, echr, &boarding_player_hp, &boarding_enemy_hp);
	
	//Определяем цепь локаций для абордажа
	boarding_location = -1;

	string deckID = "";
	int locID = -1;
	BRD_SetLocationForFight(&deckID, &locID, echr, IsFort);
	if (locID < 0) return BRD_FallbackNoLocation(deckID, echr, IsFort);

	pchar.abordage = 0;
	boarding_enemy = echr;
	int maxcrew = GetBoardingMaxCrew(&Locations[locID], mclass, eclass); 	//Определяем размеры команд

	if (boarding_location_type == BRDLT_SHIP && eclass != 7)  // на тартане каюты нет
	{
		boarding_enemy.ShipCabinLocationId = GetShipCabinID(echr);
	}

	// согласованнный абордаж
	if (!IsFort && CheckOfficersPerk(pchar, "CoordinatedBoarding")) CoordinatedBoardingStart(pchar, boarding_enemy, &boarding_player_hp, &mcrew, &boarding_player_base_crew);
	//Количество хитпойнтов для бонуса - учёт опыта солдат
	// считаем как обычно, если компаньон оказался не при делах
	if (!CheckAttribute(boarding_enemy, "CoordinatedCharIdx")) GetBoardingHP(pchar, boarding_enemy, &boarding_player_hp, &boarding_enemy_hp);


	//Отношение сторон

	// fort -->
	// boal 21.01.2004 -->
	int cn, j, compCrew;
    ref officer;
    if(IsFort)
    {
        mcrew = mcrew + GetTroopersCrewQuantity(GetMainCharacter()); // если нет перка, то нолик
        boarding_player_base_crew = mcrew;// учёт всех кораблей
        //Максимальное количество человек
        Log_TestInfo("Итого: До расчета mcrew = "+mcrew+ " ecrew = "+ ecrew + " boarding_enemy_hp = "+ boarding_enemy_hp + " boarding_player_hp = "+boarding_player_hp);
    }
    // boal 21.01.2004 <--
    // fort <--
	
	float rel;
	if(mcrew > ecrew)
	{
        // нам бонуc boal
        boarding_player_hp = boarding_player_hp + GetBoarding_player_hp_Bonus(mcrew, ecrew);
		if (boarding_player_hp > 1000) boarding_player_hp = 1000;
		
        if(mcrew > maxcrew)
		{
			rel = makefloat(mcrew) / makefloat(maxcrew);
			mcrew = maxcrew;
			ecrew = MakeInt(ecrew / rel + 0.5);
		}
	}
	else
	{
		// boal 30.01.2004 -->
		boarding_enemy_hp = boarding_enemy_hp + GetBoarding_enemy_hp_Bonus(mcrew, ecrew);
		if (boarding_enemy_hp > 1500) boarding_enemy_hp = 1500;
		// boal 30.01.2004 <--
        if(ecrew > maxcrew)
		{       
			rel = makefloat(ecrew) / makefloat(maxcrew);
			ecrew = maxcrew;
			mcrew = MakeInt(mcrew/rel + 0.5);
		}
	}
	if(mcrew < 1) mcrew = 1;
	if(ecrew < 1) ecrew = 1;
	
    Log_TestInfo("После приведения mcrew = "+mcrew+ " ecrew = "+ ecrew + " boarding_enemy_hp = "+ boarding_enemy_hp + " boarding_player_hp = "+boarding_player_hp);

	//boarding_enemy_crew_start  = ecrew;
	
	//Jason: устанавливаем число тушек по разным палубам
	// верхнюю палубу оставляем без изменений по количеству, но срезаем 15% HP у воинов противника, на нижних палубах будут добавочные враги, но это компенсация за разделенность сил противника относительно сил героя
	inside_ecrew_1 = makeint(ecrew*0.3+0.5); // 30% - инсайд первого прохода
	inside_ecrew_2 = makeint(ecrew*0.2+0.5); // 20% - инсайд второго прохода
	if(IsFort) // на двор и бастион - поровну, по рез. тестов будем решать пропорции
	{
		inside_ecrew_1 = makeint(ecrew*0.3+0.5); // 30% - инсайд первого прохода
		inside_ecrew_2 = makeint(ecrew*0.3+0.5); // 30% - инсайд второго прохода
		ecrew = ecrew*0.6+0.5;
	}
	if (inside_ecrew_1 < 1) inside_ecrew_1 = 1;
	if (inside_ecrew_2 < 1) inside_ecrew_2 = 1;

	//ecrew = ecrew*0.7+1;
	
	boarding_enemy_crew        = ecrew;
	boarding_enemy_crew_start  = ecrew;
	boarding_player_crew       = mcrew;
	boarding_player_crew_start = mcrew;
	
	//Количество офицеров
	boarding_officers = 0;
	int passq;
	for(int i = 1; i < 4; i++)
	{
		passq = GetOfficersIndex(pchar, i);
		if (passq >= 0)
		{
			boarding_officers = boarding_officers + 1;   
			LAi_SetOfficerType(&characters[passq]);
		}
	}

	BRD_InjectBalanceWithGenerator(pchar, boarding_enemy, boarding_player_base_crew, boarding_enemy_base_crew);

	boarding_player_crew_per_chr = makefloat(boarding_player_base_crew / makefloat(mcrew)); //приведение типа
	boarding_enemy_crew_per_chr = makefloat(boarding_enemy_base_crew / makefloat(ecrew)); // Stone-D : For calculating final crew numbers

	//Выставим игроку и офицерам максимальную жизнь и запомним адреса
	LAi_SetCurHPMax(pchar);
	boarding_adr[0].location = pchar.location;
	boarding_adr[0].group    = pchar.location.group;
	boarding_adr[0].locator  = pchar.location.locator;
	for(i = 1; i < 4; i++)
	{
		int idx = GetOfficersIndex(pchar, i);
		if(idx < 0)
		{
			boarding_adr[i].location = "";
			boarding_adr[i].group    = "";
			boarding_adr[i].locator  = "";
			continue;
		}
		LAi_SetCurHPMax(&Characters[idx]);
		boarding_adr[i].location = Characters[idx].location;
		boarding_adr[i].group    = Characters[idx].location.group;
		boarding_adr[i].locator  = Characters[idx].location.locator;
	}
	//Стартуем
	LAi_boarding_process = true;
	BRD_LoadNextDeck(deckID, locType);

	if(CheckAttribute(pchar, "systeminfo.tutorial.firstboarding1"))
	{
		DoQuestFunctionDelay("Tutorial_firstboarding1", 5.0);
		DeleteAttribute(pchar, "systeminfo.tutorial.firstboarding1");
	}
	if(CheckAttribute(pchar, "systeminfo.tutorial.secondboarding1"))
	{
		DoQuestFunctionDelay("Tutorial_secondboarding1", 5.0);
		DeleteAttribute(pchar, "systeminfo.tutorial.secondboarding1");
	}
	pchar.OfficerAttRange = 35.0;
	OfficersCharge();
}

//Загрузить локацию абордажа
bool BRD_LoadNextDeck(string locationID, int locType)
{
	ReloadProgressStart();
	int locIndex = FindLocation(locationID);
	Log_SetActiveAction("Nothing");
	Dead_Char_num = 0; // boal dead body
	if(locIndex >= 0)
	{
		//Устанавливаем главного персонажа
		pchar.location = locationID;
		pchar.location.group = "rld";
		int locNum[20];
		int locI;
		int maxLocators = 2;
		
		if (CheckAttribute(&Locations[locIndex], "boarding.locatorNum"))
		{
			maxLocators = sti(Locations[locIndex].boarding.locatorNum);
		}
		locI = 0;
		locNum[locI] = rand(maxLocators-1);
		string sLocType = "loc";
		int    mclass = GetCharacterShipClass(GetMainCharacter());
		int    eclass = GetCharacterShipClass(boarding_enemy);
		// определение стороны на палубе
		sLocType = ChooseShipUpDeck(pchar, boarding_enemy);

		pchar.location.locator = sLocType + locNum[locI];
		// для каюты перекрыть
		if (CheckAttribute(&Locations[locIndex], "CabinType") && CheckAttribute(&Locations[locIndex], "boarding.Loc.Hero"))
		{
			pchar.location.locator = Locations[locIndex].boarding.Loc.Hero;
		}
		bool   okLoc;
		int iLoc, j;
		if (!CheckAttribute(&Locations[locIndex], "CabinType"))
		{ // не грузим офов, если каюту
			int logined = 1;
			for(int i = 1; i < 4; i++)
			{
				int idx = GetOfficersIndex(pchar, i);
				if(idx < 0) continue;
				//Log_TestInfo("Load Off " + Characters[idx].id);
				if (logined > maxLocators) break;

				DeleteAttribute(&Characters[idx], "location");

				Characters[idx].location.loadcapture = true; // boal чтоб грузились в фортах -->

				iLoc = rand(3);

				okLoc = false;
				while (!okLoc)
				{
				    for(j = 0; j <=locI; j++)
				    {
				        if (locNum[j] == iLoc)
				        {
				            iLoc = rand(3);
				            okLoc = false;
				            break;
				        }
				        okLoc = true;
				    }
				}
				locI++;
				locNum[locI] = iLoc;
				ChangeCharacterAddressGroup(&Characters[idx], locationID, "rld", sLocType + locNum[locI]);
				logined = logined + 1;
			}
		}
		//Перегружаемся в локацию
		boarding_location = locIndex;
				
		if(LoadLocation(&Locations[boarding_location]))
		{
			//работа с сундуком в каюте boal -->
			if (CheckAttribute(&Locations[boarding_location], "CabinType"))
			{
				FillAboardCabinBox(&Locations[boarding_location], boarding_enemy);
			}  
			//Расставляем персонажей
			LAi_SetBoardingActors(locationID, boarding_enemy);
			LAi_InstantFightMode(pchar); //Вытащим саблю
			dialogDisable = true; //Запретим диалог
		}else{
			Trace("Boarding: Boarding location not loaded, current loc <" + locationID + ">");
		}
	}else{
		Trace("Boarding: Boarding location not found, current loc <" + locationID + ">");
	}
	ReloadProgressEnd();
	PostEvent("LoadSceneSound", 500);
	DoQuestCheckDelay("update_sea_environment", 0.1);
	return true;
}

//Перегрузиться в следующую локации
void LAi_ReloadBoarding()
{
//	Log_TestInfo("ReloadBoarding()");
	//Разрешим диалоги
	dialogDisable = false;
	//Проверим предыдущую локацию
	if(boarding_location < 0)
	{
		Trace("Boarding: No loaded current boarding location");
		LAi_boarding_process = false;
		return;
	}
	//Установить хендлеры для обработки
	SetEventHandler("FaderEvent_StartFade", "LAi_ReloadStartFade", 0);
	SetEventHandler("FaderEvent_EndFade", "LAi_ReloadEndFade", 0);
	//Создаём фейдер и запускаем
	CreateEntity(&boarding_fader, "fader");
	string nextDeck = Locations[boarding_location].boarding.nextdeck;
	if (nextDeck != "")
	{
		SendMessage(&boarding_fader, "ls", FADER_PICTURE0, "loading\ImgBack.tga");
		if(CheckAttribute(&Locations[FindLocation(nextDeck)], "image"))
		{
			SendMessage(&boarding_fader, "ls", FADER_PICTURE, Locations[FindLocation(nextDeck)].image);
		}
	}
	float fadeOutTime = RELOAD_TIME_FADE_OUT;
	SendMessage(&boarding_fader, "lfl", FADER_OUT, fadeOutTime, false);
	SendMessage(&boarding_fader, "l", FADER_STARTFRAME);
}

void LAi_ReloadStartFade()
{
	ResetSound();
	PauseAllSounds();
	SendMessage(&Particles,"l", PS_CLEAR_CAPTURED);
	DelEventHandler("FaderEvent_StartFade", "LAi_ReloadStartFade");
	if(boarding_location >= 0) UnloadLocation(&Locations[boarding_location]);
}

bool LAi_ReloadEndFade()
{
	ref loc = &Locations[boarding_location];
	DelEventHandler("FaderEvent_EndFade", "LAi_ReloadEndFade");
	SendMessage(&boarding_fader, "lfl", FADER_IN, RELOAD_TIME_FADE_IN, true);
	bool canReload = true;
	// Jason: во всех инсайдах и добавочных локациях форта число расчетных тушек х2, по рез.тестов возможно, будет дифференциация по типам инсайдов.
	if (IsUpperDeck(boarding_location)) boarding_enemy_crew = inside_ecrew_1*2; // увеличиваем внутри число тушек вдвое
	else boarding_enemy_crew = inside_ecrew_2*2; // увеличиваем внутри число тушек вдвое

	if(IsFort)
	{
		if (CheckAttribute(loc, "insidenext")) boarding_enemy_crew = inside_ecrew_2*2;
		else boarding_enemy_crew = inside_ecrew_1*2;
	}
	if (!CheckAttribute(loc, "boarding.nextdeck") || loc.boarding.nextdeck == "") canReload = false;
	if (canReload) return BRD_LoadNextDeck(loc.boarding.nextdeck, -1);
	if (!Surrendered && CheckAttribute(boarding_enemy, "ShipCabinLocationId")) return BRD_LoadCabin(boarding_enemy);

	SendMessage(&Particles,"l", PS_CLEAR_CAPTURED); // повторное удаление партиклов, фикс огней в море.
	//Следующей локации нет
	DelEventHandler("LAi_event_GroupKill", "LAi_BoardingGroupKill");
	boarding_location = -1;

	//Пересчитываем команду игрока
	float crew = boarding_player_crew * boarding_player_crew_per_chr; // ВЫЖИВШИЕ офицеры - это не мартросы не должны влиять
	ref mchar       = GetMainCharacter();
	float fDefenceSkill = 0.9 + MakeFloat(GetSummonSkillFromName(mchar, SKILL_DEFENCE)) / SKILL_MAX;
	int deadCrew    = makeint((boarding_player_base_crew - crew) / fDefenceSkill + 0.3); // бонус выжившим
	if (CheckAttribute(pchar, "questTemp.ShipCapellan.Yes")) deadCrew = makeint(deadCrew/2); //Jason, капеллан на борту - потери в 2 раза меньше
	int deadCrewWOMedic = makeint(boarding_player_base_crew - crew); // без бонуса
	float leaderSkill = GetSummonSkillFromNameToOld(mchar, SKILL_LEADERSHIP);

	BRD_ApplyMedicine(deadCrewWOMedic, &deadCrew); // расчёт медицины

	// Saved value is not needed anymore... (Gray 14.02.2005)
	DeleteAttribute(mchar, "EnemyRank");
	bQuestCheckProcessFreeze = false;
	RemoveCharacterGoodsSelf(mchar, GOOD_WEAPON, deadCrew);
	crew = boarding_player_base_crew - deadCrew; // выжившие с бонусом
	Statistic_AddValue(mchar, "Sailors_dead", deadCrew);
	Statistic_AddValue(mchar, "DeadCrewBoard", deadCrew);
	AddMementoShipBonus(deadCrew);
	Achievment_SetStat(21, deadCrew);
	AddCharacterExpToSkill(mchar, "Defence", makeint(deadCrew / 3 + 0.5)); //качаем защиту
	AddCharacterExpToSkill(mchar, "Grappling", makeint(deadCrew / 3 + 0.5));

	// после боя падает мораль
	if (deadCrew > makeint(crew+0.3)) // погибло больше, чем выжило
	{
		AddCrewMorale(mchar, sti(-20 / leaderSkill));
		ChangeCharacterComplexReputation(pchar,"authority", -0.5);
	}
	else
	{  //растет, если потерь мало
		AddCrewMorale(mchar, sti(leaderSkill));
		ChangeCharacterComplexReputation(pchar,"authority", 0.5);
	}

	int crewSurvived = MakeInt(crew + 0.3);
	// распределяем потери по кораблю ГГ и присоединившегося компаньона
	if (CheckAttribute(&boarding_enemy, "CoordinatedCharIdx")) CoordinatedBoardingEnd(pchar, boarding_enemy.CoordinatedCharIdx, crewSurvived);
	else SetCrewQuantityOverMax(pchar, crewSurvived); // десант весь ГГ как перегруз команды

	Log_TestInfo("----- в конце стало " + crew +" матросов ---");
	SetCrewQuantity(boarding_enemy, 0); //Пересчитываем команду соперника
	//Настроим интерфейс
	Log_SetActiveAction("Nothing");
	EndBattleLandInterface();
	//Востановим адреса
	pchar.location         = boarding_adr[0].location;
	pchar.location.group   = boarding_adr[0].group;
	pchar.location.locator = boarding_adr[0].locator;
	
	for(int i = 1; i < 4; i++)
	{
		int idx = GetOfficersIndex(pchar, i);
		if(idx < 0) continue;
		Characters[idx].location         = boarding_adr[i].location;
		Characters[idx].location.group   = boarding_adr[i].group;
		Characters[idx].location.locator = boarding_adr[i].locator;
	}
	//Выгружаемся в интерфейс
	return BRD_ExitToInterface(boarding_enemy, boarding_enemy_base_crew, IsFort, Surrendered);
}

//Разрешить перегрузку на следующую палубу
#event_handler("LAi_event_boarding_EnableReload", "LAi_EnableReload");
void LAi_EnableReload()
{
	if(CheckAttribute(&TEV, "boardingReloadFreeze")) return; //TO_DO: на глобальный бул
	//Log_Testinfo("LAi_BoardingGroupKill boardM = " + boardM);
	if (boardM == 1)
	{
		ResetSoundScheme(); //надо гасить только Scheme, иначе партиклы звука на кострах, факелах, и прочем - не пашут
		SetSoundScheme("deck"); // обычная схема
		SetMusic("music_abordage");
		boardM = -1;
	}
	Surrendered = BRD_IsSurrenderBeforeCabin(boarding_enemy); // не надумла ли сдаваться

	SetEventHandler("Control Activation","LAi_ActivateReload",1);
	if(CheckAttribute(loadedlocation, "CabinType")) Log_SetActiveAction("BoardingEnd");
	else Log_SetActiveAction("BoardingReload"); // belamour legendary edition бутафория 
	//Уберём саблю
	LAi_SetFightMode(pchar, 0);
	
	// sd -->
	Log_TestInfo("Start boarding_enemy_crew_start: " + boarding_enemy_crew_start + " boarding_enemy_crew: " + boarding_enemy_crew);
	Log_TestInfo("Start boarding_player_crew_start: " + boarding_player_crew_start + " boarding_player_crew: " + boarding_player_crew);
	// sd <--
	
	//Вернём выживших обратно в кучу
	for(int i = 0; i < LAi_numloginedcharacters; i++)
	{
		int index = LAi_loginedcharacters[i];
		if(index >= 0)
		{
			if(index != GetMainCharacterIndex())
			{
				ref chr = &Characters[index];
				if(!LAi_IsDead(chr) && !IsOfficer(chr) && chr.model.animation != "mushketer") // boal && sd не нужны офицеры для матросов
				{
					if(chr.chr_ai.group == LAI_GROUP_PLAYER)
					{
						boarding_player_crew = boarding_player_crew + 1;
						LAi_SetHuberStayTypeNoGroup(chr); //нефиг им стоять, все-равно мешаются ! пущай расходятся по палубе Jason: а вот тут и дыра с прокачкой вылезла. Зачем из группы игрока надо было выводить? Фикс.
					}
				}
			}
		}
	}
	SetNextDeck(boarding_enemy, boarding_location, IsFort);
}

//Активация перегрузки на следующую палубу
void LAi_ActivateReload()
{
	string controlName = GetEventData();
	if(controlName != "ChrAction") return;
	if (CheckAttribute(pchar, "GenQuest.CannotReloadBoarding")) return; // Jason
	DelEventHandler("Control Activation", "LAi_ActivateReload");
	Log_SetActiveAction("Nothing");
	LAi_ReloadBoarding();
}

//Убийство группы
void LAi_BoardingGroupKill()
{
	string group = GetEventData();
	if (group != LAI_GROUP_BRDENEMY) return;

	if(!IsFort && HasPerk(pchar, "Looting"))
	{
		SetEventHandler("BRD_InitLooting", "BRD_InitLooting", 1);
		PostEvent("BRD_InitLooting", 500, "i", &Locations[boarding_location]);
	}

	PostEvent("LAi_event_boarding_EnableReload", 5000);
}

bool BRD_LoadCabin(ref boarding_enemy)
{
	if(CheckAttribute(&Locations[FindLocation(boarding_enemy.ShipCabinLocationId)], "image"))
	{
		SendMessage(&boarding_fader, "ls", FADER_PICTURE0, "loading\ImgBack.tga");
		SendMessage(&boarding_fader, "ls", FADER_PICTURE, Locations[FindLocation(boarding_enemy.ShipCabinLocationId)].image);
	}
	BRD_LoadNextDeck(boarding_enemy.ShipCabinLocationId, -1);
	DeleteAttribute(boarding_enemy, "ShipCabinLocationId"); // чтоб не зациклилось
	return true;
}
