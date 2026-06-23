/*
Тип: музыканты, играют на скрипке или флейте

	Используемые шаблоны:
		stay
*/



#define LAI_TYPE_MUSICIAN		"musician"


//Инициализация
void LAi_type_musician_Init(ref chr)
{
	DeleteAttribute(chr, "location.follower");
	DeleteAttribute(chr, "chr_ai.type");
	chr.chr_ai.type = LAI_TYPE_MUSICIAN;
	LAi_tmpl_stay_InitTemplate(chr);
	//SetViolinistStayAnimation(chr);
	//Установим анимацию персонажу
	if(CheckAttribute(chr, "musician"))
	{
		switch (chr.musician)
		{
			case "ViolinistStay": LAi_SetViolinistStayAnimation(chr); break;
			case "FlutistStay":   LAi_SetFlutistStayAnimation(chr); break;
			case "FlutistSit":    LAi_SetFlutistSitAnimation(chr); break;
		}
	}
	//SendMessage(&chr, "lsl", MSG_CHARACTER_EX_MSG, "SetFightWOWeapon", false);
}

//Процессирование типа персонажа
void LAi_type_musician_CharacterUpdate(ref chr, float dltTime)
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
bool LAi_type_musician_CharacterLogin(ref chr)
{
	return true;
}

//Выгрузка персонажа из локацию
bool LAi_type_musician_CharacterLogoff(ref chr)
{
	return true;
}

//Завершение работы темплейта
void LAi_type_musician_TemplateComplite(ref chr, string tmpl)
{
	//LAi_tmpl_player_InitTemplate(chr);
}

//Сообщить о желании завести диалог
void LAi_type_musician_NeedDialog(ref chr, ref by)
{
}

//Запрос на диалог, если возвратить true то в этот момент можно начать диалог
bool LAi_type_musician_CanDialog(ref chr, ref by)
{
	/* //Если уже говорим, то откажем
	if(chr.chr_ai.tmpl == LAI_TMPL_DIALOG) return false;
	//Согласимся на диалог
	return true; */
	return false;
}

//Начать диалог
void LAi_type_musician_StartDialog(ref chr, ref by)
{
	//Если мы пасивны, запускаем шаблон без времени завершения
	//LAi_tmpl_stay_InitTemplate(chr);
	//LAi_tmpl_SetActivatedDialog(chr, by);
	//LAi_tmpl_dialog_NoAni(chr);
	//chr.chr_ai.tmpl.firstAnim = 1;
}

//Закончить диалог
void LAi_type_musician_EndDialog(ref chr, ref by)
{
	/* LAi_tmpl_stay_InitTemplate(chr);
	LAi_SetmusicianSitAnimation(chr); */
}

//Персонаж выстрелил
void LAi_type_musician_Fire(aref attack, aref enemy, float kDist, bool isFindedEnemy)
{
}


//Персонаж атакован
void LAi_type_musician_Attacked(ref chr, ref by)
{
	
}

//Найти врага
int LAi_type_musician_FindEnemy(ref chr, int num)
{
	return -1;
}

void LAi_SetViolinistStayAnimation(ref chr)
{
	BeginChangeCharacterActions(chr);
	for(int i = 1; i < 12; i++)
	{
		string Attr = "i"+i;
		chr.actions.idle.(Attr) = "idle_1";
	}
	EndChangeCharacterActions(chr);
}

void LAi_SetFlutistStayAnimation(ref chr)
{
	BeginChangeCharacterActions(chr);
	for(int i = 1; i < 12; i++)
	{
		string Attr = "i"+i;
		chr.actions.idle.(Attr) = "flute_idle_1";
	}
	chr.actions.dead.d1 = "death_flute_1";
	chr.actions.dead.d2 = "death_flute_1";
	EndChangeCharacterActions(chr);
}

void LAi_SetFlutistSitAnimation(ref chr)
{
	BeginChangeCharacterActions(chr);
	for(int i = 1; i < 12; i++)
	{
		string Attr = "i"+i;
		chr.actions.idle.(Attr) = "flute_idle_sit_1";
	}
	chr.actions.dead.d1 = "death_flute_sit_1";
	chr.actions.dead.d2 = "death_flute_sit_1";
	EndChangeCharacterActions(chr);
}


