/*
Тип: кузнец

	Используемые шаблоны:
		stay
		dialog
*/



#define LAI_TYPE_BLACKSMITH		"blacksmith"


//Инициализация
void LAi_type_blacksmith_Init(ref chr)
{
	DeleteAttribute(chr, "location.follower");
	DeleteAttribute(chr, "chr_ai.type");
	chr.chr_ai.type = LAI_TYPE_BLACKSMITH;
	LAi_tmpl_stay_InitTemplate(chr);
	//Установим анимацию персонажу
	SetBlacksmithAnimation(chr);
	//SendMessage(&chr, "lsl", MSG_CHARACTER_EX_MSG, "SetFightWOWeapon", false);
}

//Процессирование типа персонажа
void LAi_type_blacksmith_CharacterUpdate(ref chr, float dltTime)
{	
	if(chr.chr_ai.tmpl != LAI_TMPL_DIALOG)
	{
		if(rand(1000) == 313)
		{
            // звук не прописан в алиасах
			//LAi_CharacterPlaySound(chr, "governor");
		}
	}
}

//Загрузка персонажа в локацию
bool LAi_type_blacksmith_CharacterLogin(ref chr)
{
	return true;
}

//Выгрузка персонажа из локацию
bool LAi_type_blacksmith_CharacterLogoff(ref chr)
{
	return true;
}

//Завершение работы темплейта
void LAi_type_blacksmith_TemplateComplite(ref chr, string tmpl)
{
	//LAi_tmpl_player_InitTemplate(chr);
}

//Сообщить о желании завести диалог
void LAi_type_blacksmith_NeedDialog(ref chr, ref by)
{
}

//Запрос на диалог, если возвратить true то в этот момент можно начать диалог
bool LAi_type_blacksmith_CanDialog(ref chr, ref by)
{
	//Если уже говорим, то откажем
	if(chr.chr_ai.tmpl == LAI_TMPL_DIALOG) return false;
	//Согласимся на диалог
	return true; 
}

//Начать диалог
void LAi_type_blacksmith_StartDialog(ref chr, ref by)
{
	SetBlacksmithDialogAnimation(chr);
	LAi_tmpl_SetActivatedDialog(chr, by);
	LAi_CharacterSaveAy(chr);
	CharacterTurnByChr(chr, by);
}

//Закончить диалог
void LAi_type_blacksmith_EndDialog(ref chr, ref by)
{
	SetBlacksmithAnimation(chr);
	LAi_CharacterRestoreAy(chr);
	LAi_tmpl_stay_InitTemplate(chr);
}

//Персонаж выстрелил
void LAi_type_blacksmith_Fire(aref attack, aref enemy, float kDist, bool isFindedEnemy)
{
}


//Персонаж атакован
void LAi_type_blacksmith_Attacked(ref chr, ref by)
{
	
}

//Найти врага
int LAi_type_blacksmith_FindEnemy(ref chr, int num)
{
	return -1;
}

void SetBlacksmithAnimation(ref chr)
{
	BeginChangeCharacterActions(chr);
	chr.actions.idle.i1 = "idle_1";
	for(int i = 1; i < 12; i++)
	{
		string Attr = "i"+i;
		chr.actions.idle.(Attr) = "idle_1";
	}
/* 	chr.actions.dead.d1 = "Sit_Bench_Death";
	chr.actions.dead.d2 = "Sit_Bench_Death1";
	chr.actions.HitNoFight = "HitNoFightSit"; */
	EndChangeCharacterActions(chr);
}

void SetBlacksmithDialogAnimation(ref chr)
{
	BeginChangeCharacterActions(chr);
	for(int i = 1; i < 12; i++)
	{
		string Attr = "i"+i;
		chr.actions.idle.(Attr) = "dialog_stay"+i;
	}
	EndChangeCharacterActions(chr);
}
