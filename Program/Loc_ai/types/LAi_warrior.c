/*
Тип: воин, бьёт врагов, когда свободен, возвращается к лидеру или стоит

	Используемые шаблоны:
		fight
		follow
		walk
		stay
		dialog
*/



#define LAI_TYPE_WARRIOR	"warrior"



//Установить войну командира
void LAi_warrior_SetCommander(ref chr, ref commander)
{
	chr.chr_ai.type.index = commander.index;
}

//Разрешить или запретить диалоги для война
void LAi_warrior_DialogEnable(ref chr, bool isEnable)
{
	chr.chr_ai.type.dialog = isEnable;
}

//Сказать войну стоять при отсутствие целей
void LAi_warrior_SetStay(ref chr, bool isStay)
{
	chr.chr_ai.type.stay = isStay;
}

//Инициализация
void LAi_type_warrior_Init(ref chr)
{
	DeleteAttribute(chr, "location.follower");
	bool isNew = false;
	if(CheckAttribute(chr, "chr_ai.type") == false)
	{
		isNew = true;
	}else{
		if(chr.chr_ai.type != LAI_TYPE_WARRIOR) isNew = true;
	}
	if(isNew == true)
	{
		//Новый тип
		DeleteAttribute(chr, "chr_ai.type");
		chr.chr_ai.type = LAI_TYPE_WARRIOR;
		chr.chr_ai.type.stay = "0";
		chr.chr_ai.type.index = "";
		chr.chr_ai.type.dialog = "1"; 
		chr.chr_ai.type.bottle = rand(10)+2;
		chr.chr_ai.type.checkTarget = 0;
		LAi_tmpl_stay_InitTemplate(chr);
	}else{
		if(!CheckAttribute(chr, "chr_ai.type.stay")) chr.chr_ai.type.stay = "0";
		if(!CheckAttribute(chr, "chr_ai.type.index")) chr.chr_ai.type.index = "";
		if(!CheckAttribute(chr, "chr_ai.type.dialog")) chr.chr_ai.type.dialog = "1"; 
	}
	//Установим анимацию персонажу
	if (chr.model.animation == "mushketer" && !CheckAttribute(chr, "isMusketer.weapon"))
	{
		LAi_NPC_MushketerEquip(chr);
	}
	else
	{
		LAi_SetDefaultStayAnimation(chr);
	}
	SendMessage(&chr, "lsl", MSG_CHARACTER_EX_MSG, "SetFightWOWeapon", false);
}

//Процессирование типа персонажа
void LAi_type_warrior_CharacterUpdate(ref chr, float dltTime)
{
	int trg = -1;
	//Ссылка на ветку с параметрами
	aref type;
	makearef(type, chr.chr_ai.type);

    // boal  лечимся -->
	float fCheck = float(chr.chr_ai.type.bottle) - dltTime;
	if(fCheck < 0)
	{
		chr.chr_ai.type.bottle = 5.0;
		if (!LAi_IsBottleWork(chr) && MOD_SKILL_ENEMY_RATE > 2)
		{
			string btl = "";		
			float dhlt;
			if(LAi_GetCharacterRelHP(chr) < 0.75)
			{
				dhlt = LAi_GetCharacterMaxHP(chr) - LAi_GetCharacterHP(chr);
				btl = FindHealthForCharacter(&Characters[int(chr.index)], dhlt);
				DoCharacterUsedItem(&Characters[int(chr.index)], btl);
				chr.chr_ai.type.bottle = 10.0;
			}
		}
	}
	else chr.chr_ai.type.bottle = fCheck;
	// boal  лечимся <--
	//Анализируем состояние
	if(chr.chr_ai.tmpl == LAI_TMPL_FIGHT)
	{
		//Воюем
		bool isValidate = false;
		trg = LAi_tmpl_fight_GetTarget(chr);
		fCheck = float(chr.chr_ai.type.checkTarget) - dltTime;
		chr.chr_ai.type.checkTarget = fCheck;
		if(trg >= 0)
		{			
			if(LAi_group_ValidateTarget(chr, &Characters[trg]))
			{
				if(!LAi_tmpl_fight_LostTarget(chr))
				{
					isValidate = true;
					if (float(LAi_grp_relations.distance) > 2.0 && fCheck < 0) //цель далеко, попробуем сменить на ближайшую
					{
						isValidate = false;
					}				
				}
			}
		}
		if(!isValidate)
		{
			//Ищем новую цель
			trg = LAi_group_GetTarget(chr);
			if(trg < 0)
			{
				//Переходим в режим ожидания
				LAi_tmpl_stay_InitTemplate(chr);
				LAi_type_warrior_SetWateState(chr);
			}else{
				//Натравливаем на новую цель
				LAi_tmpl_SetFight(chr, &Characters[trg]);
				chr.chr_ai.type.checkTarget = rand(3) + 2; //таймер на проверялку расстояния до таргета
				if(rand(100) > 95)
				{
					LAi_type_warrior_PlaySound(chr);
				}
			}
		}
	}else{
		//Ищем новую цель
		trg = LAi_group_GetTarget(chr);
		if(trg >= 0)
		{
			//Нападаем на новую цель
			LAi_tmpl_SetFight(chr, &Characters[trg]);
			chr.chr_ai.type.checkTarget = rand(3) + 2; //таймер на проверялку расстояния до таргета
			if(rand(100) > 95)
			{
				LAi_type_warrior_PlaySound(chr);
			}
		}else{
			if(chr.chr_ai.tmpl == LAI_TMPL_STAY)
			{
				//Стоим и ждём цели
				LAi_type_warrior_SetWateState(chr);
			}
			//слежение залезания ГГ в боксы
			if (CheckAttribute(chr, "watchBoxes")) 
			{
				int num = FindNearCharacters(chr, 10.0, -1.0, 180.0, 0.01, true, true);
				for(int i = 0; i < num; i++)
				{
					if(nMainCharacterIndex == int(chrFindNearCharacters[i].index))
					{					
						//нашли ГГ, проверяем, не в сундуке ли.						
						if (bMainCharacterInBox && !HasPerk(pchar, "Quiet"))
						{
							//Нападаем на новую цель
							LAi_group_Attack(chr, Pchar);
							if(chr.chr_ai.group == "LSC_NARVAL") DoQuestCheckDelay("LSC_NarvalConflict", 0.5);
							if(chr.chr_ai.group == "LSC_RIVADOS") DoQuestCheckDelay("LSC_RivadosConflict", 0.5);
							if(chr.chr_ai.group == "LSC_SHARK") DoQuestCheckDelay("LSC_SharkConflict", 0.5);
							if(rand(100) > 95)
							{
								LAi_type_warrior_PlaySound(chr);
							}	
						}
					}
				}
			}
		}
	}	
}

//Загрузка персонажа в локацию
bool LAi_type_warrior_CharacterLogin(ref chr)
{
	return true;
}

//Выгрузка персонажа из локацию
bool LAi_type_warrior_CharacterLogoff(ref chr)
{
	return true;
}

//Завершение работы темплейта
void LAi_type_warrior_TemplateComplite(ref chr, string tmpl)
{
}

//Сообщить о желании завести диалог
void LAi_type_warrior_NeedDialog(ref chr, ref by)
{
}

//Запрос на диалог, если возвратить true то в этот момент можно начать диалог
bool LAi_type_warrior_CanDialog(ref chr, ref by)
{	
	if(int(chr.chr_ai.type.dialog) == 0) return false;
	//Если просто стоим, то согласимся
	if(chr.chr_ai.tmpl == LAI_TMPL_STAY) return true;
	if(chr.chr_ai.tmpl == LAI_TMPL_FOLLOW) return true;
	if(chr.chr_ai.tmpl == LAI_TMPL_WALK) return true;
	return false;
}

//Начать диалог
void LAi_type_warrior_StartDialog(ref chr, ref by)
{
	//Если мы пасивны, запускаем шаблон без времени завершения	
	LAi_CharacterSaveAy(chr);
	CharacterTurnByChr(chr, by);
	LAi_tmpl_SetActivatedDialog(chr, by);
}

//Закончить диалог
void LAi_type_warrior_EndDialog(ref chr, ref by)
{
	LAi_tmpl_stay_InitTemplate(chr);
	LAi_CharacterRestoreAy(chr);
}


//Персонаж выстрелил
void LAi_type_warrior_Fire(aref attack, aref enemy, float kDist, bool isFindedEnemy)
{
}


//Персонаж атакован
void LAi_type_warrior_Attacked(ref chr, ref by)
{
	//если наносящий удар уже таргет, нефиг крутить код и переназначать цель
	if (LAi_tmpl_fight_GetTarget(chr) == int(by.index)) return;
	//Своих пропускаем
	if(!LAi_group_IsEnemy(chr, by)) return;
	LAi_group_UpdateTargets(chr);
    float dist = -1.0;	
	if(!GetCharacterDistByChr3D(chr, by, &dist)) return;
	if(dist < 0.0) return;
	if(dist > 20.0) return;
	//Натравливаем
	LAi_tmpl_SetFight(chr, by);
	chr.chr_ai.type.checkTarget = rand(3)+2;
	if(rand(100) > 90)
	{
		LAi_type_warrior_PlaySound(chr);
	}
}

//Переходим в режим ожидания
void LAi_type_warrior_SetWateState(ref chr)
{
	if(int(chr.chr_ai.type.stay) == 0)
	{
		if(chr.chr_ai.type.index != "")
		{
			int cmd = int(chr.chr_ai.type.index);
			if(cmd >= 0)
			{
				//Возвращаемся к командиру
				LAi_tmpl_SetFollow(chr, &Characters[cmd], -1.0);
			}else{
				//Гуляем в поисках цели
				LAi_tmpl_walk_InitTemplate(chr);
			}
		}else{
			//Гуляем в поисках цели
			LAi_tmpl_walk_InitTemplate(chr);
		}
	}else{
		//Ожидаем цель стоя на месте
		if(chr.chr_ai.tmpl != LAI_TMPL_STAY)
		{
			LAi_tmpl_stay_InitTemplate(chr);
		}
	}
}

void LAi_type_warrior_PlaySound(ref chr)
{
	if(LAi_IsDead(chr) && !LAi_IsDead(pchar)) return;
	string sname = "";
	if(CheckAttribute(chr, "sex"))
	{
		switch(chr.sex)
		{
		case "man":
			sname = "warrior";
			break;
		case "woman":
			break;
		case "skeleton":
			sname = "skeleton";
			break;
		}
	}
	if(sname == "") return;
	LAi_CharacterPlaySound(chr, sname);
}

