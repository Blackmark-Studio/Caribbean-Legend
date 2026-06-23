/*
Тип: стоячий, всегда стоит, отвечает на диалоги, никогда не боится

	Используемые шаблоны:
		stay
		dialog
		goto
*/



#define LAI_TYPE_PATROL		"patrol"

//Инициализация
void LAi_type_patrol_Init(ref chr)
{
	DeleteAttribute(chr, "location.follower");
	bool isNew = false;
	if(CheckAttribute(chr, "chr_ai.type") == false)
	{
		isNew = true;
	}
	else
	{
		if(chr.chr_ai.type != LAI_TYPE_PATROL) isNew = true;
	}
	if(isNew)
	{
		DeleteAttribute(chr, "chr_ai.type");
		chr.chr_ai.type = LAI_TYPE_PATROL;
		chr.chr_ai.type.locator = "";
		chr.chr_ai.type.state = "stay";
		chr.chr_ai.type.time = rand(5);
		chr.chr_ai.type.player = "0";
		chr.chr_ai.type.bottle = rand(10)+2;
		chr.chr_ai.type.checkTarget = 0;
		LAi_tmpl_stay_InitTemplate(chr);
	}
	else
	{
		if(!CheckAttribute(chr, "chr_ai.type.locator")) chr.chr_ai.type.locator = "";
		if(!CheckAttribute(chr, "chr_ai.type.state")) chr.chr_ai.type.state = "stay";
		if(!CheckAttribute(chr, "chr_ai.type.time")) chr.chr_ai.type.time = rand(5);
		if(!CheckAttribute(chr, "chr_ai.type.player")) chr.chr_ai.type.player = "0";
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
void LAi_type_patrol_CharacterUpdate(ref chr, float dltTime)
{
	int trg = -1;
	//Если болтаем, то ничего пока не меняем
	if(chr.chr_ai.tmpl == LAI_TMPL_DIALOG) return;
	
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
	float radius;
	if(chr.chr_ai.tmpl != LAI_TMPL_FIGHT && !LAi_grp_alarmactive)
	{
		//Ищем цель
		trg = LAi_group_GetTarget(chr);
		if(trg < 0)
		{
			//Патрулирование
			float time = float(chr.chr_ai.type.player) - dltTime;
			chr.chr_ai.type.player = time;
			if(time <= 0.0)
			{
				//Анализируем окружающих персонажей
				if (isDay() || GetRelation2BaseNation(int(chr.nation)) != RELATION_ENEMY) radius = 3.0; //eddy. дневной и начной патруль - разные, ночью смотрят дальше
				else radius = 6.0;
				int num = FindNearCharacters(chr, radius, -1.0, 180.0, 0.1, true, true);
				if(num > 0)
				{
					for(int i = 0; i < num; i++)
					{
						if(nMainCharacterIndex == int(chrFindNearCharacters[i].index))
						{							
							break;
						}
					}
					if(i < num)
					{
						//Нашли главного персонажа
						if(float(chr.chr_ai.type.player) <= 0.0 || LAi_CheckFightMode(pchar) != CHR_MODE_PEACE)
						{
							LAi_type_patrol_TestControl(chr);
							return;
						}
					}
					else
					{
						trg = int(chrFindNearCharacters[0].index);
					}
				}
			}			
			//Анализируем состояние ходьбы
			if(chr.chr_ai.tmpl == LAI_TMPL_GOTO)
			{
				if(LAi_tmpl_goto_IsWait(chr))
				{
					if(rand(100) < 20) LAi_type_patrol_Goto(chr);
				}
				return;
			}
			//Иногда звучим
			if(rand(1000) == 125)
			{
				LAi_CharacterPlaySound(chr, "sigh");
			}
			//Стоим
			time = float(chr.chr_ai.type.time) - dltTime;
			chr.chr_ai.type.time = time;
			if(time > 0.0)
			{
				if(trg >= 0) CharacterTurnByChr(chr, &Characters[trg]);
				return;
			}else{
				LAi_type_patrol_Goto(chr);
				return;
			}

		}else{
			//Начинаем атаку
			chr.chr_ai.type.state = "fight";
			if(!LAi_tmpl_SetFight(chr, &Characters[trg]))
			{
				//Несмогли инициировать шаблон
				LAi_type_patrol_Stay(chr);
			}
			else chr.chr_ai.type.checkTarget = rand(4) + 3; //таймер на проверялку расстояния до таргета
		}
	}else{
		//Проверим на правильность цель
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
					if (float(LAi_grp_relations.distance) > 2.0 && time < 0) //цель далеко, попробуем сменить на ближайшую
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
			if(trg >= 0)
			{
				chr.chr_ai.type.state = "fight";
				if(!LAi_tmpl_SetFight(chr, &Characters[trg]))
				{
					//Несмогли инициировать шаблон
					LAi_type_patrol_Stay(chr);
				}
				else chr.chr_ai.type.checkTarget = rand(4) + 3; //таймер на проверялку расстояния до таргета
			}else{
				LAi_type_patrol_Stay(chr);
			}
		}
	}
}

//Загрузка персонажа в локацию
bool LAi_type_patrol_CharacterLogin(ref chr)
{
	return true;
}

//Выгрузка персонажа из локацию
bool LAi_type_patrol_CharacterLogoff(ref chr)
{
	return true;
}

//Завершение работы темплейта
void LAi_type_patrol_TemplateComplite(ref chr, string tmpl)
{
	if(tmpl == "goto")
	{
		LAi_type_patrol_Stay(chr);
		CharacterTurnByLoc(chr, "goto", chr.chr_ai.type.locator);
		chr.chr_ai.type.locator = "";
	}
}

//Сообщить о желании завести диалог
void LAi_type_patrol_NeedDialog(ref chr, ref by)
{
}

//Запрос на диалог, если возвратить true то в этот момент можно начать диалог
bool LAi_type_patrol_CanDialog(ref chr, ref by)
{
	if(chr.chr_ai.type.state == "dialog")
	{
		if(int(by.index) == nMainCharacterIndex)
		{
			chr.chr_ai.type.state = "stay";
			return true;
		}
		return false;
	}
	if(LAi_CanNearEnemy(chr, 5.0)) return false;
	if(chr.chr_ai.tmpl == LAI_TMPL_STAY) return true;
	if(chr.chr_ai.tmpl == LAI_TMPL_GOTO) return true;
	if(int(by.index) == nMainCharacterIndex)
	{
		if(chr.chr_ai.tmpl == LAI_TMPL_DIALOG)
		{
			if(LAi_tmpl_dialog_StopNPC(chr)) return true;
		}
	}
	return false;
}

//Начать диалог
void LAi_type_patrol_StartDialog(ref chr, ref by)
{
	//Если мы пасивны, запускаем шаблон без времени завершения
	LAi_CharacterSaveAy(chr);
	CharacterTurnByChr(chr, by);
	LAi_tmpl_SetActivatedDialog(chr, by);
}

//Закончить диалог
void LAi_type_patrol_EndDialog(ref chr, ref by)
{
	LAi_tmpl_stay_InitTemplate(chr);
	LAi_CharacterRestoreAy(chr);
	bool isSet = false;
	if(chr.chr_ai.type.state == "goto")
	{
		if(chr.chr_ai.type.locator != "")
		{
			LAi_tmpl_goto_InitTemplate(chr);
			LAi_tmpl_goto_SetLocator(chr, "goto", chr.chr_ai.type.locator, -1.0);
			isSet = true;
		}
	}
	if(!isSet)
	{
		LAi_type_patrol_Stay(chr);
	}
}


//Персонаж выстрелил
void LAi_type_patrol_Fire(aref attack, aref enemy, float kDist, bool isFindedEnemy)
{
}


//Персонаж атакован
void LAi_type_patrol_Attacked(ref chr, ref by)
{
	if(chr.chr_ai.tmpl == LAI_TMPL_DIALOG)
	{
		LAi_tmpl_dialog_StopNPC(chr);
	}
	//если наносящий удар уже таргет, нефиг крутить код и переназначать цель
	if (LAi_tmpl_fight_GetTarget(chr) == int(by.index)) return;
	//Своих пропускаем
	if(!LAi_group_IsEnemy(chr, by)) return;
    //boal fix ai -->
    float dist = -1.0;
	
	if(!GetCharacterDistByChr3D(chr, by, &dist)) return;
	if(dist < 0.0) return;
	if(dist > 20.0) return;
	//Натравливаем
	LAi_tmpl_SetFight(chr, by);
    // boal <--
	if (rand(100) > 95 && !LAi_IsDead(chr) && !LAi_IsDead(pchar)) LAi_CharacterPlaySound(chr, "warrior");
}

//Проверить персонажа с заданной вероятностью
void LAi_type_patrol_Stay(ref chr)
{
	chr.chr_ai.type.time = 2 + rand(20);
	chr.chr_ai.type.state = "stay";
	LAi_tmpl_stay_InitTemplate(chr);
}

//Отправить персонажа в новую точку
void LAi_type_patrol_Goto(ref chr)
{
	//Идём в новую точку
	string newloc;
	if (!CheckAttribute(chr, "CityType")) Log_SetStringToLog("Ghf: " + chr.id);
	if (chr.CityType == "fortPatrol") 
	{
		string sTemp = chr.location.locator;
		newloc = "goto" + rand(6) + GetSymbol(sTemp, 7);
	}
	else newloc = LAi_FindRandomLocator("goto");
	if(newloc != "")
	{
		LAi_tmpl_goto_InitTemplate(chr);
		LAi_tmpl_goto_SetLocator(chr, "goto", newloc, -1.0);
		chr.chr_ai.type.state = "goto";
		chr.chr_ai.type.locator = newloc;
	}
}

//Проверить персонажа с заданной вероятностью
void LAi_type_patrol_TestControl(ref chr)
{
	chr.chr_ai.type.player = 5 + rand(10);
	int iRand;
	bool bFightMode = LAi_CheckFightMode(pchar) != CHR_MODE_PEACE;

	// belamour legendary edition адмиралу и губернатору можно ходить в боевом режиме
	bool bAdmiral = isMainCharacterPatented() && int(Items[int(pchar.EquipedPatentId)].TitulCur) > 4 && chr.nation == int(Items[int(pchar.EquipedPatentId)].Nation);
	bool bGenGov = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && chr.nation == GetBaseHeroNation();
	
	if (GetNationRelation2MainCharacter(int(chr.nation)) == RELATION_ENEMY || GetNationRelation(int(chr.nation), GetBaseHeroNation()) == RELATION_ENEMY) iRand = 3;
	else iRand = GetRelation2BaseNation(int(chr.nation)); // 0- друг 1- нейтрал 2- враг // новая нумерация 1 - друг, 2 - нейтрал, 3 - враг
	if (isDay()) 
	{
		// в друж. городе не цепляемся
		if (iRand < 3 || CharIsFromStockPirCity(chr))  //Экку Korsar - Что-бы пираты не прикапывались в стоковых поселках
		{
			//проверяем, нет ли обнажёнки оружия
			if (bFightMode && !bAdmiral && !bGenGov)
			{	//Пытаемся начать диалог
				LAi_SetFightMode(pchar, false);
				if(LAi_Character_CanDialog(chr, pchar))
				{
					chr.greeting = "";
					LAi_CharacterPlaySound(chr, "sold_weapon_off");
					chr.chr_ai.type.state = "dialog";
					chr.Dialog.CurrentNode = "SoldierNotBlade";
					LAi_tmpl_SetDialog(chr, pchar, -1.0);
				}
			}
			return;  
		}
		if (CheckNationLicence(HOLLAND)) iRand = 10;
		else
		{
			if (iRand == RELATION_NEUTRAL)
			{
				//проверяем, нет ли обнажёнки оружия
				if (bFightMode && !bAdmiral && !bGenGov)
				{	//Пытаемся начать диалог
					LAi_SetFightMode(pchar, false);
					if(LAi_Character_CanDialog(chr, pchar))
					{
						chr.chr_ai.type.state = "dialog";
						chr.Dialog.CurrentNode = "SoldierNotBlade";
						LAi_tmpl_SetDialog(chr, pchar, -1.0);
					}
					chr.chr_ai.type.player = 100;
					return;
				}					
				chr.chr_ai.type.player = 100;
				iRand = 60;
			}
			else 
			{	//враждебный
				if (bFightMode)	iRand = 500;
				else iRand = 120;
			}
		}
	}
	else 
	{
		if (iRand == RELATION_FRIEND || iRand == RELATION_NEUTRAL || CharIsFromStockPirCity(chr)) //Экку Korsar - Что-бы пираты не прикапывались в стоковых поселках
		{
			//проверяем, нет ли обнажёнки оружия
			if (bFightMode && !bAdmiral && !bGenGov)
			{	//Пытаемся начать диалог
				LAi_SetFightMode(pchar, false);
				if(LAi_Character_CanDialog(chr, pchar))
				{
					chr.chr_ai.type.state = "dialog";
					chr.Dialog.CurrentNode = "SoldierNotBlade";
					LAi_tmpl_SetDialog(chr, pchar, -1.0);
				}
			}			
			return; // в друж. городе не цепляемся
		}
		//eddy. ночной враг цепляется только так и шансов скрыться мало даже при супер прокачке скрытности.
		if (iRand == RELATION_ENEMY) 
		{
			if (bFightMode)
			{	
				iRand = 500;
			}
			else 
			{
				if(CheckNationLicence(HOLLAND)) iRand = 10;
				else iRand = 360;
			}
		}
		else 
		{
			//проверяем, нет ли обнажёнки оружия
			if (bFightMode && !bAdmiral && !bGenGov)
			{	//Пытаемся начать диалог
				LAi_SetFightMode(pchar, false);
				if(LAi_Character_CanDialog(chr, pchar))
				{
					chr.chr_ai.type.state = "dialog";
					chr.Dialog.CurrentNode = "SoldierNotBlade";
					LAi_tmpl_SetDialog(chr, pchar, -1.0);
				}
				chr.chr_ai.type.player = 80;
				return;
			}			
			chr.chr_ai.type.player = 60;
			iRand = 80; //ночью нейтрал
		}
	}
	
	// mitrokosta тупая стража по карибским нравам
	if (CheckAttribute(pchar, "questTemp.Trial") && CheckAttribute(chr, "City") && chr.City == "PortoBello") {
		iRand = 30;
	}
	
	//Проверим на начало диалога
	if (rand(iRand) <= StealthLuck)
	{
		if (!dialogRun && !bFightMode && StealthLuck < 60) // кач в диалоге - фигвам. кто с обнажёнкой бегает - тоже.
		{
			if (GetNationRelation2MainCharacter(int(chr.nation)) == RELATION_ENEMY && int(chr.nation) != PIRATE)
			{  // враг, которго не узнали - скрылся - молодец!
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 15);
			}
			if (GetBaseHeroNation() == int(chr.nation) && GetRelation2BaseNation(int(chr.nation)) == RELATION_ENEMY)
			{
			    AddCharacterExpToSkill(pchar, SKILL_SNEAK, 10);
			}
		}
		return;
	}
	if(CheckAttribute(pchar,"chr_ai.stealtDlgCooldown") && float(pchar.chr_ai.stealtDlgCooldown) > 0.0) return;
	//Пытаемся начать диалог
	LAi_SetFightMode(pchar, false);
	if(LAi_Character_CanDialog(chr, pchar))
	{
		chr.chr_ai.type.state = "dialog";
		LAi_tmpl_SetDialog(chr, pchar, -1.0);
		//Следующий раз будет нескоро
		chr.chr_ai.type.player = "50";
		pchar.chr_ai.stealtDlgCooldown = 20;
		if(!CheckAttribute(pchar,"StealtDeceptionPenalty")) pchar.StealtDeceptionPenalty = 0;
		else pchar.StealtDeceptionPenalty = int(pchar.StealtDeceptionPenalty)+5;
	}
	else
	{
		if(dialogSelf)
		{
			DialogExit();
			locCameraSleep(false);
			chr.chr_ai.type.player = "0";
			pchar.chr_ai.stealtDlgCooldown = 20;
			if(!CheckAttribute(pchar,"StealtDeceptionPenalty")) pchar.StealtDeceptionPenalty = 0;
			else pchar.StealtDeceptionPenalty = int(pchar.StealtDeceptionPenalty)+5;
		}
	}
}
