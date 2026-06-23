/*
Тип:  сидящий на земле

	Используемые шаблоны:
		stay
		dialog
		ani
*/



#define LAI_TYPE_GROUNDSIT		"groundSit"


//Инициализация
void LAi_type_GroundSit_Init(ref chr)
{
	DeleteAttribute(chr, "location.follower");
	DeleteAttribute(chr, "chr_ai.type");
	chr.chr_ai.type = LAI_TYPE_GROUNDSIT;
	LAi_tmpl_stay_InitTemplate(chr);
	//Установим анимацию персонажу
	//LAi_SetDefaultStayAnimation(chr);
	LAi_SetSitPoorAnimation(chr);
	SendMessage(&chr, "lsl", MSG_CHARACTER_EX_MSG, "SetFightWOWeapon", false);
}

//Процессирование типа персонажа
void LAi_type_GroundSit_CharacterUpdate(ref chr, float dltTime)
{
	int num = FindNearCharacters(chr, 5.0, -1.0, -1.0, 0.001, false, true);
	int idx;
	if(num > 0)
	{
		for(int i = 0; i < num; i++)
		{
			idx = int(chrFindNearCharacters[i].index);
			if(LAi_group_IsEnemy(chr, &Characters[idx])) break;
		}
		if(i < num)
		{
			if(chr.chr_ai.tmpl != LAI_TMPL_ANI)
			{
				LAi_tmpl_ani_PlayAnimation(chr, "afraid", -1.0);
				LAi_SetAfraidDead(chr);
			}
		}else{
			if(chr.chr_ai.tmpl != LAI_TMPL_STAY)
			{
				LAi_tmpl_stay_InitTemplate(chr);
				LAi_SetDefaultDead(chr);
			}
		}
	}else{
		if(chr.chr_ai.tmpl != LAI_TMPL_DIALOG)
		{
			/* if(rand(500) == 123)
			{
				LAi_CharacterPlaySound(chr, "poorman_male");
			}  */
		}
		if(chr.chr_ai.tmpl != LAI_TMPL_STAY)
		{
			LAi_tmpl_stay_InitTemplate(chr);
			LAi_SetDefaultDead(chr);
		}
	}
}

//Загрузка персонажа в локацию
bool LAi_type_GroundSit_CharacterLogin(ref chr)
{
	return true;
}

//Выгрузка персонажа из локацию
bool LAi_type_GroundSit_CharacterLogoff(ref chr)
{
	return true;
}

//Завершение работы темплейта
void LAi_type_GroundSit_TemplateComplite(ref chr, string tmpl)
{
}

//Сообщить о желании завести диалог
void LAi_type_GroundSit_NeedDialog(ref chr, ref by)
{
}

//Запрос на диалог, если возвратить true то в этот момент можно начать диалог
bool LAi_type_GroundSit_CanDialog(ref chr, ref by)
{
	//Если уже говорим, то откажем
	if(chr.chr_ai.tmpl == LAI_TMPL_STAY) return true;
	//Согласимся на диалог
	return false;
}

//Начать диалог
void LAi_type_GroundSit_StartDialog(ref chr, ref by)
{
	//Если мы пасивны, запускаем шаблон без времени завершения
	LAi_tmpl_SetActivatedDialog(chr, by);
}

//Закончить диалог
void LAi_type_GroundSit_EndDialog(ref chr, ref by)
{
	LAi_tmpl_stay_InitTemplate(chr);
}

//Персонаж выстрелил
void LAi_type_GroundSit_Fire(aref attack, aref enemy, float kDist, bool isFindedEnemy)
{
}


//Персонаж атакован
void LAi_type_GroundSit_Attacked(ref chr, ref by)
{
	LAi_SetWarriorTypeNoGroup(chr);
}

