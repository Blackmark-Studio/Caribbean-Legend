

#define LAI_TMPL_WALK	"walk"


bool LAi_tmpl_walk_InitTemplate(ref chr)
{
	SendMessage(&chr, "lsl", MSG_CHARACTER_EX_MSG, "LockFightMode", false);
	CharacterPlayAction(chr, "");
	bool isNew = false;
	if(CheckAttribute(chr, "chr_ai.tmpl"))
	{
		if(chr.chr_ai.tmpl != LAI_TMPL_WALK) isNew = true;
	}else{
		isNew = true;
	}
	if(isNew)
	{
		//Новая установка
		DeleteAttribute(chr, "chr_ai.tmpl");
		chr.chr_ai.tmpl = LAI_TMPL_WALK;
		chr.chr_ai.tmpl.locator = "";
		chr.chr_ai.tmpl.time = 0;
		float maxtime = rand(5);
		chr.chr_ai.tmpl.maxtime = maxtime;	
		if(rand(3) != 0)
		{
			chr.chr_ai.tmpl.state = "goto";
			if(LAi_IsInitedAI) LAi_tmpl_walk_go_notime(chr);
		}else{
			chr.chr_ai.tmpl.state = "stay";
			if(LAi_IsInitedAI) SetCharacterTask_Stay(chr);
		}
	}else{
		//Востонавление
		if(!CheckAttribute(chr, "chr_ai.tmpl.state")) chr.chr_ai.tmpl.state = "stay";
		if(CheckAttribute(chr, "chr_ai.tmpl.locator"))
		{
			if(chr.chr_ai.tmpl.locator == "") chr.chr_ai.tmpl.state = "stay";
		}else{
			chr.chr_ai.tmpl.state = "stay";
		}
		if(!CheckAttribute(chr, "chr_ai.tmpl.time")) chr.chr_ai.tmpl.time = 0;
		if(!CheckAttribute(chr, "chr_ai.tmpl.maxtime")) chr.chr_ai.tmpl.maxtime = 1 + rand(5);
		if(chr.chr_ai.tmpl.state == "goto")
		{
			if(LAi_IsInitedAI)
			{
				if(SetCharacterTask_GotoPoint(chr, "goto", chr.chr_ai.tmpl.locator) == false)
				{
					SetCharacterTask_Stay(chr);
					chr.chr_ai.tmpl.state = "stay";
				}
			}
		}
		if(chr.chr_ai.tmpl.state == "stay")
		{
			if(LAi_IsInitedAI) SetCharacterTask_Stay(chr);
			if(chr.chr_ai.tmpl.locator != "")
			{
				CharacterTurnByLoc(chr, "goto", chr.chr_ai.tmpl.locator);
			}
		}
	}
	return true;
}


//Процессирование шаблона персонажа
void LAi_tmpl_walk_CharacterUpdate(ref chr, float dltTime)
{
	float time, maxtime;
	int idx;
	aref tmpl;
	float dist;
	makearef(tmpl, chr.chr_ai.tmpl);
	//Смотрим текущее состояние шаблона
	tmpl.time = float(tmpl.time) + dltTime;
	if(tmpl.state == "stay")
	{
		//Повышаем желание пойти
		time = float(tmpl.time);
		maxtime = float(tmpl.maxtime);
		if(time > maxtime)
		{
			//Пора идти
			LAi_tmpl_walk_go(chr);
		}else{
			//Смотрим на проходящих
			if(rand(5) == 3)
			{
				idx = LAi_FindNearestVisCharacter(chr, 2.0);
				if(idx >= 0)
				{
					//Нашли на кого попялиться
					tmpl.state = "look";
					tmpl.state.time = 0;
					tmpl.state.maxtime = 3 + rand(3);
					tmpl.state.index = idx;
					CharacterTurnByChr(chr, &Characters[idx]);
				}
			}
		}
	}else{
		if(tmpl.state == "look")
		{
			tmpl.time = float(tmpl.time) + dltTime;
			time = float(tmpl.state.time);
			maxtime = float(tmpl.state.maxtime);
			idx = int(tmpl.state.index);
			if(GetCharacterDistByChr(chr, &Characters[idx], &dist) == false)
			{
				time = maxtime;
			}
			if(dist > 4.0 || dist < 0.0)
			{
				time = maxtime;
			}
			if(time < maxtime)
			{
				time = time + dltTime;
				tmpl.state.time = time;
				CharacterTurnByChr(chr, &Characters[idx]);
			}else{
				DeleteAttribute(chr, "chr_ai.tmpl.state");
				tmpl.state = "stay";
				CharacterTurnByLoc(chr, "goto", chr.chr_ai.tmpl.locator);
			}
		}
	}
}

//Персонаж выполнил команду  go to point
void LAi_tmpl_walk_EndGoToPoint(ref chr)
{
	LAi_tmpl_walk_endgo(chr);
}

//Персонаж провалил команду  go to point
void LAi_tmpl_walk_FailureGoToPoint(ref chr)
{
	LAi_tmpl_walk_endgo(chr);
}


//Персонаж выполнил команду  run to point
void LAi_tmpl_walk_EndRunToPoint(ref chr)
{
	LAi_tmpl_walk_endgo(chr);
}

//Персонаж провалил команду  run to point
void LAi_tmpl_walk_FailureRunToPoint(ref chr)
{
	LAi_tmpl_walk_endgo(chr);
}

//Персонаж не может добраться до точки назначения
void LAi_tmpl_walk_BusyPos(ref chr, float x, float y, float z)
{
	LAi_tmpl_walk_endgo(chr);
	if(chr.chr_ai.tmpl.state == "stay")
	{
		CharacterTurnByPoint(chr, x, y, z);
	}
}

//Персонаж начал перемещение за другим
void LAi_tmpl_walk_FollowGo(ref chr)
{
	LAi_tmpl_walk_endgo(chr);
}

//Персонаж начал дошёл до другого персонажа
void LAi_tmpl_walk_FollowStay(ref chr)
{
	LAi_tmpl_walk_endgo(chr);
}

//Персонаж провалил команду  follow character
void LAi_tmpl_walk_FailureFollow(ref chr)
{
	LAi_tmpl_walk_endgo(chr);
}


//Персонаж начал перемещение за другим
void LAi_tmpl_walk_FightGo(ref chr)
{
	LAi_tmpl_walk_endgo(chr);
}

//Персонаж начал дошёл до другого персонажа
void LAi_tmpl_walk_FightStay(ref chr)
{
	LAi_tmpl_walk_endgo(chr);
}

//Персонаж провалил команду  Fight
void LAi_tmpl_walk_FailureFight(ref chr)
{
	LAi_tmpl_walk_endgo(chr);
}

//Можно ли стрелять
bool LAi_tmpl_walk_IsFire(ref chr)
{
	return false;
}

//Можно ли использовать оружие
bool LAi_tmpl_walk_IsFight(ref chr)
{
	return false;
}


//Персонаж выполнил команду  escape
void LAi_tmpl_walk_EndEscape(ref chr)
{
	LAi_tmpl_walk_endgo(chr);
}

//Персонаж скользит вдоль патча
void LAi_tmpl_walk_EscapeSlide(ref chr)
{
	LAi_tmpl_walk_endgo(chr);
}

//Персонаж провалил команду  escape
void LAi_tmpl_walk_FailureEscape(ref chr)
{
	LAi_tmpl_walk_endgo(chr);
}


//Персонаж толкается с другими персонажами
void LAi_tmpl_walk_ColThreshold(ref chr)
{
	if(chr.chr_ai.tmpl.state == "stay")
	{
		chr.chr_ai.tmpl.time = 0;
		chr.chr_ai.tmpl.maxtime = 5;
		LAi_tmpl_walk_go_notime(chr);
	}else{
		if(chr.chr_ai.tmpl.state == "look")
		{
			chr.chr_ai.tmpl.time = 0;
			chr.chr_ai.tmpl.maxtime = 5;
			LAi_tmpl_walk_go_notime(chr);
		}else{
			if(LAi_tmpl_walk_neareststaycheck(chr))
			{
				LAi_tmpl_walk_nowstay(chr);
			}else{
				chr.chr_ai.tmpl.time = 0;
				chr.chr_ai.tmpl.maxtime = 8;
				LAi_tmpl_walk_go_notime(chr);
			}
		}
	}
}


//Персонаж закончил проигрывать анимацию
void LAi_tmpl_walk_EndAction(ref chr)
{
	LAi_tmpl_walk_endgo(chr);
}

//Персонажа просят освободить место
void LAi_tmpl_walk_FreePos(ref chr, aref who)
{
	LAi_tmpl_walk_go(chr);
}

//------------------------------------------------------------------------------------------
//Внутреннии функции
//------------------------------------------------------------------------------------------

void LAi_tmpl_walk_go(ref chr)
{
	chr.chr_ai.tmpl.maxtime = 8 + rand(50);
	chr.chr_ai.tmpl.time = 0;
	LAi_tmpl_walk_go_notime(chr);
}

void LAi_tmpl_walk_go_notime(ref chr)
{
	string loc;
	if(rand(3) == 2)
	{
		loc = LAi_FindRandomLocator("goto");
	}else{
		loc = FindCharacterOptLocator(chr, "goto");
		if(loc == "")
		{
			loc = LAi_FindRandomLocator("goto");
		}
	}
	if(loc == "")
	{
		//Локатора нет, стоим
		chr.chr_ai.tmpl.maxtime = 60;
		chr.chr_ai.tmpl.time = 0;
		chr.chr_ai.tmpl.state = "stay";
		return;
	}
	if(SetCharacterTask_GotoPoint(chr, "goto", loc) == false)	
	{
		//Локатора нет, стоим
		chr.chr_ai.tmpl.maxtime = 1;
		chr.chr_ai.tmpl.time = 0;
		chr.chr_ai.tmpl.state = "stay";
		return;
	}
	chr.chr_ai.tmpl.state = "goto";
	chr.chr_ai.tmpl.locator = loc;
}


void LAi_tmpl_walk_endgo(ref chr)
{
	if(float(chr.chr_ai.tmpl.time) > float(chr.chr_ai.tmpl.maxtime))
	{
		//Проверяем ближних стоячих
		if(LAi_tmpl_walk_neareststaycheck(chr))
		{
			//Останавливаем
			LAi_tmpl_walk_nowstay(chr);
		}else{
			//Ищем новую цель
			LAi_tmpl_walk_go_notime(chr);
		}
	}else{
		//Ищем новую цель
		LAi_tmpl_walk_go_notime(chr);
	}
}

void LAi_tmpl_walk_nowstay(ref chr)
{
	//Переходим в режим ожидания
	chr.chr_ai.tmpl.time = 0;
	chr.chr_ai.tmpl.maxtime = 5 + rand(30);
	SetCharacterTask_Stay(chr);
	chr.chr_ai.tmpl.state = "stay";
	if(chr.chr_ai.tmpl.locator != "")
	{
		CharacterTurnByLoc(chr, "goto", chr.chr_ai.tmpl.locator);
	}
}

bool LAi_tmpl_walk_neareststaycheck(ref chr)
{
	int num = FindNearCharacters(chr, 4.0, -1.0, -1.0, 0.01, false, false);
	if(num <= 0) return true;
	int cnt = 0;
	for(int i = 0; i < num; i++)
	{
		int idx = int(chrFindNearCharacters[i].index);
		if(CharacterGetTask(&Characters[idx]) == "Stay")
		{
			cnt++;
		}
	}	
	if(cnt > 1) return false;
	return true;
}


