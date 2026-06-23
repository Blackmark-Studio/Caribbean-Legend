/*
Тип: губернатор, отвечает на диалоги, никогда не боится

	Используемые шаблоны:
		stay
		dialog
*/



#define LAI_TYPE_HUBER		"huber"


//Инициализация
void LAi_type_huber_Init(ref chr)
{
	DeleteAttribute(chr, "location.follower");
	DeleteAttribute(chr, "chr_ai.type");
	chr.chr_ai.type = LAI_TYPE_HUBER;
	LAi_tmpl_stay_InitTemplate(chr);
	//Установим анимацию персонажу
	LAi_SetHuberSitAnimation(chr);
	SendMessage(&chr, "lsl", MSG_CHARACTER_EX_MSG, "SetFightWOWeapon", false);
}

//Процессирование типа персонажа
void LAi_type_huber_CharacterUpdate(ref chr, float dltTime)
{	
	int num;
	float locx, locy, locz;
	if (CheckAttribute(chr, "standUp") && !LAi_IsCapturedLocation) //не при захвате колонии
	{
		num = FindNearCharacters(chr, 15.0, -1.0, -1.0, 0.01, false, false);
		int iNumEnemy = LAi_type_huber_FindEnemy(chr, num);
		if (iNumEnemy > 0) //есть враги
		{
			GetCharacterPos(chr, &locx, &locy, &locz);			
            Pchar.quest.MayorSitBack.win_condition.l1 = "ExitFromLocation";
            Pchar.quest.MayorSitBack.win_condition.l1.location = pchar.location;
            Pchar.quest.MayorSitBack.function = "MayorSitBack";
			Pchar.quest.MayorSitBack.mayorId = chr.id;
			Pchar.quest.MayorSitBack.locationName = chr.location;
			Pchar.quest.MayorSitBack.locatorName = chr.location.locator;
			EquipCharacterByItem(chr, FindCharacterItemByGroup(chr, BLADE_ITEM_TYPE));
			EquipCharacterByItem(chr, FindCharacterItemByGroup(chr, GUN_ITEM_TYPE));
			LAi_SetWarriorTypeNoGroup(chr); //ребрендинг и вперед на врага
			ChangeCharacterAddressGroup(chr, chr.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_group_Attack(chr, &characters[iNumEnemy]);
			if (CheckAttribute(chr, "standUp.exitDisable")) chrDisableReloadToLocation = true;
		}
	}
	//слежение залезания ГГ в боксы
	if (CheckAttribute(chr, "watchBoxes")&& chr.chr_ai.tmpl != LAI_TMPL_DIALOG) 
	{
		num = FindNearCharacters(chr, 10.0, -1.0, 180.0, 0.01, true, true);
		for(int i = 0; i < num; i++)
		{
			if(nMainCharacterIndex == int(chrFindNearCharacters[i].index))
			{					
				//нашли ГГ, проверяем, не в сундуке ли.						
				if (bMainCharacterInBox && !HasPerk(pchar, "Quiet"))
				{
					//Нападаем на новую цель
					GetCharacterPos(chr, &locx, &locy, &locz);	
					LAi_SetWarriorTypeNoGroup(chr); //ребрендинг и вперед на врага
					ChangeCharacterAddressGroup(chr, chr.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
					LAi_group_Attack(chr, pchar);
					if (CheckAttribute(chr, "watchBoxes.exitDisable")) chrDisableReloadToLocation = true;
				}
			}
		}
	}
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
bool LAi_type_huber_CharacterLogin(ref chr)
{
	return true;
}

//Выгрузка персонажа из локацию
bool LAi_type_huber_CharacterLogoff(ref chr)
{
	return true;
}

//Завершение работы темплейта
void LAi_type_huber_TemplateComplite(ref chr, string tmpl)
{
	LAi_tmpl_player_InitTemplate(chr);
}

//Сообщить о желании завести диалог
void LAi_type_huber_NeedDialog(ref chr, ref by)
{
}

//Запрос на диалог, если возвратить true то в этот момент можно начать диалог
bool LAi_type_huber_CanDialog(ref chr, ref by)
{
	//Если уже говорим, то откажем
	if(chr.chr_ai.tmpl == LAI_TMPL_DIALOG) return false;
	//Согласимся на диалог
	return true;
}

//Начать диалог
void LAi_type_huber_StartDialog(ref chr, ref by)
{
	//Если мы пасивны, запускаем шаблон без времени завершения
	//LAi_tmpl_stay_InitTemplate(chr);
	LAi_tmpl_SetActivatedDialog(chr, by);
	//LAi_tmpl_dialog_NoAni(chr);
	chr.chr_ai.tmpl.firstAnim = 1;
}

//Закончить диалог
void LAi_type_huber_EndDialog(ref chr, ref by)
{
	LAi_tmpl_stay_InitTemplate(chr);
	LAi_SetHuberSitAnimation(chr);
}

//Персонаж выстрелил
void LAi_type_huber_Fire(aref attack, aref enemy, float kDist, bool isFindedEnemy)
{
}


//Персонаж атакован
void LAi_type_huber_Attacked(ref chr, ref by)
{
	
}

//Найти врага
int LAi_type_huber_FindEnemy(ref chr, int num)
{
	if(num <= 0) return -1;
	int i, idx;
	if(LAi_grp_playeralarm > 0)
	{
		for(i = 0; i < num; i++)
		{
			idx = int(chrFindNearCharacters[i].index);
			if(LAi_group_IsEnemy(chr, &Characters[idx])) return idx;
		}
	}
	else
	{		
		for(i = 0; i < num; i++)
		{
			idx = int(chrFindNearCharacters[i].index);
			if(LAi_CheckFightMode(&Characters[idx]) != CHR_MODE_PEACE) return idx;
		}
	}
	return -1;
}

