/*
Тип: ситдят на лавочке

	Используемые шаблоны:
		stay
*/



#define LAI_TYPE_BENCHSIT		"benchsit"


//Инициализация
void LAi_type_benchsit_Init(ref chr)
{
	DeleteAttribute(chr, "location.follower");
	DeleteAttribute(chr, "chr_ai.type");
	chr.chr_ai.type = LAI_TYPE_BENCHSIT;
	LAi_SetBenchSitAnimation(chr);
	LAi_tmpl_stay_InitTemplate(chr);
}

//Процессирование типа персонажа
void LAi_type_benchsit_CharacterUpdate(ref chr, float dltTime)
{	
	if(chr.chr_ai.tmpl != LAI_TMPL_DIALOG)
	{
		if(rand(1000) == 313)
		{
            // звук не прописан в алиасах
			//LAi_CharacterPlaySound(chr, "woman_talk_town");
		}
	}
}

//Загрузка персонажа в локацию
bool LAi_type_benchsit_CharacterLogin(ref chr)
{
	return true;
}

//Выгрузка персонажа из локацию
bool LAi_type_benchsit_CharacterLogoff(ref chr)
{
	return true;
}

//Завершение работы темплейта
void LAi_type_benchsit_TemplateComplite(ref chr, string tmpl)
{
	//LAi_tmpl_player_InitTemplate(chr);
}

//Сообщить о желании завести диалог
void LAi_type_benchsit_NeedDialog(ref chr, ref by)
{
}

//Запрос на диалог, если возвратить true то в этот момент можно начать диалог
bool LAi_type_benchsit_CanDialog(ref chr, ref by)
{
	/* //Если уже говорим, то откажем
	if(chr.chr_ai.tmpl == LAI_TMPL_DIALOG) return false;
	//Согласимся на диалог
	return true; */
	return false;
}

//Начать диалог
void LAi_type_benchsit_StartDialog(ref chr, ref by)
{
	//Если мы пасивны, запускаем шаблон без времени завершения
	//LAi_tmpl_stay_InitTemplate(chr);
	//LAi_tmpl_SetActivatedDialog(chr, by);
	//LAi_tmpl_dialog_NoAni(chr);
	//chr.chr_ai.tmpl.firstAnim = 1;
}

//Закончить диалог
void LAi_type_benchsit_EndDialog(ref chr, ref by)
{
	/* LAi_tmpl_stay_InitTemplate(chr);
	LAi_SetbenchsitSitAnimation(chr); */
}

//Персонаж выстрелил
void LAi_type_benchsit_Fire(aref attack, aref enemy, float kDist, bool isFindedEnemy)
{
}


//Персонаж атакован
void LAi_type_benchsit_Attacked(ref chr, ref by)
{
	
}

//Найти врага
int LAi_type_benchsit_FindEnemy(ref chr, int num)
{
	return -1;
}

void LAi_SetbenchSitAnimation(ref chr)
{
	BeginChangeCharacterActions(chr);
	chr.actions.idle.i1 = "Sit_Bench_Idle01";
	chr.actions.idle.i2 = "Sit_Bench_Idle02";
	chr.actions.idle.i3 = "Sit_Bench_Idle03";
	chr.actions.idle.i4 = "Sit_Bench_Idle04";
	chr.actions.idle.i5 = "Sit_Bench_Idle05";
	chr.actions.idle.i6 = "Sit_Bench_Idle06";
	chr.actions.idle.i7 = "Sit_Bench_Idle06";
	chr.actions.idle.i8 = "Sit_Bench_Idle06";
	chr.actions.idle.i9 = "Sit_Bench_Idle06";
	chr.actions.idle.i10 = "Sit_Bench_Idle06";
	chr.actions.idle.i11 = "Sit_Bench_Idle06";
	chr.actions.dead.d1 = "Sit_Bench_Death";
	chr.actions.dead.d2 = "Sit_Bench_Death1";
	chr.actions.HitNoFight = "HitNoFightSit";
	EndChangeCharacterActions(chr);
}

