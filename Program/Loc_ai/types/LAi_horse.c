

#define LAI_TYPE_HORSE	"horse"


//Инициализация
void LAi_type_horse_Init(ref chr)
{
	DeleteAttribute(chr, "location.follower");
	DeleteAttribute(chr, "chr_ai.type");
	chr.chr_ai.type = LAI_TYPE_HORSE;
	LAi_tmpl_stay_InitTemplate(chr);
	//Установим анимацию персонажу
	if(CheckAttribute(chr, "horse"))
	{
		switch (chr.horse)
		{
			case "HorseStay": LAi_SetHorseStayAnimation(chr); break;
			case "HorseSit":  LAi_SetHorseSitAnimation(chr);  break;
		}
	}
	//SendMessage(&chr, "lsl", MSG_CHARACTER_EX_MSG, "SetFightWOWeapon", false);
	/* bool isNew = false;
	if(CheckAttribute(chr, "chr_ai.type") == false)
	{
		isNew = true;
	}else{
		if(chr.chr_ai.type != LAI_TYPE_HORSE) isNew = true;
	}
	if(isNew == true)
	{
		DeleteAttribute(chr, "chr_ai.type");
		chr.chr_ai.type = LAI_TYPE_HORSE;
		//Установим шаблон гуляния
		LAi_tmpl_walk_InitTemplate(chr);
	}	
	chr.chr_ai.type.notalk = rand(10);
	chr.chr_ai.type.checkFight = rand(5)+2;
	//Установим анимацию персонажу
	LAi_SetDefaultStayAnimation(chr);
	SendMessage(&chr, "lsl", MSG_CHARACTER_EX_MSG, "SetFightWOWeapon", false); */
}

//Процессирование типа персонажа
void LAi_type_horse_CharacterUpdate(ref chr, float dltTime)
{	
	if(chr.chr_ai.tmpl != LAI_TMPL_DIALOG)
	{
		if(rand(1000) == 313)
		{
			LAi_CharacterPlaySound(chr, "woman_talk_town");
		}
	}
}

//Загрузка персонажа в локацию
bool LAi_type_horse_CharacterLogin(ref chr)
{
	return true;
}

//Выгрузка персонажа из локацию
bool LAi_type_horse_CharacterLogoff(ref chr)
{
	return true;
}

//Завершение работы темплейта
void LAi_type_horse_TemplateComplite(ref chr, string tmpl)
{

}

//Сообщить о желании завести диалог
void LAi_type_horse_NeedDialog(ref chr, ref by)
{
}

//Запрос на диалог, если возвратить true то в этот момент можно начать диалог
bool LAi_type_horse_CanDialog(ref chr, ref by)
{
	//Если уже говорим, то откажем
	if(chr.chr_ai.tmpl == LAI_TMPL_DIALOG) return false;
	if(CheckAttribute(chr, "horse") && chr.horse == "HorseSit") return false;
	//Согласимся на диалог
	return true; 
}

//Начать диалог
void LAi_type_horse_StartDialog(ref chr, ref by)
{
	//Если мы пасивны, запускаем шаблон без времени завершения
	LAi_CharacterSaveAy(chr);
	CharacterTurnByChr(chr, by);
	LAi_tmpl_SetActivatedDialog(chr, by);
}

//Закончить диалог
void LAi_type_horse_EndDialog(ref chr, ref by)
{
	LAi_CharacterRestoreAy(chr);
	LAi_tmpl_stay_InitTemplate(chr);
	chr.chr_ai.type.notalk = 10.0 + rand(20);
}

//Персонаж выстрелил
void LAi_type_horse_Fire(aref attack, aref enemy, float kDist, bool isFindedEnemy)
{

}

//Персонаж атакован
void LAi_type_horse_Attacked(ref chr, ref by)
{
	if(chr.chr_ai.tmpl == LAI_TMPL_DIALOG)
	{
		LAi_tmpl_dialog_StopNPC(chr);
		LAi_type_horse_CharacterUpdate(chr, 0.0);
	}
}

int LAi_type_horse_FindNearEnemy(ref chr)
{
	if(LAi_grp_alarmactive == true)
	{
		int num = FindNearCharacters(chr, 5.0, -1.0, -1.0, 0.001, false, true);
		if(num <= 0)
		{
			chrFindNearCharacters[0].index = "-1";
			return -1;
		}
		int cnt = 0;
		for(int i = 0; i < num; i++)
		{
			int idx = int(chrFindNearCharacters[i].index);
			if(LAi_group_IsEnemy(chr, &Characters[idx])) return idx;
		}
	}
	return -1;
}

void LAi_SetHorseStayAnimation(ref chr)
{
	int i;
	BeginChangeCharacterActions(chr);
	for(i = 1; i < 6; i++)
	{
		string Attr = "i"+i;
		chr.actions.idle.(Attr) = "Horse_Stay_idle_"+i;
	}
	for(i = 6; i < 11; i++)
	{
		Attr = "i"+i;
		chr.actions.idle.(Attr) = "Horse_Stay_idle_"+int(i-5);
	}
	chr.actions.idle.i11 = "Horse_Stay_idle_1";
	EndChangeCharacterActions(chr);
}

void LAi_SetHorseSitAnimation(ref chr)
{
	int i;
	BeginChangeCharacterActions(chr);
	for(i = 1; i < 5; i++)
	{
		string Attr = "i"+i;
		chr.actions.idle.(Attr) = "Horse_Sit_idle_"+i;
	}
	for(i = 5; i < 9; i++)
	{
		Attr = "i"+i;
		chr.actions.idle.(Attr) = "Horse_Sit_idle_"+int(i-4);
	}
	for(i = 9; i < 12; i++)
	{
		Attr = "i"+i;
		chr.actions.idle.(Attr) = "Horse_Sit_idle_"+int(i-8);
	}
	EndChangeCharacterActions(chr);
}
