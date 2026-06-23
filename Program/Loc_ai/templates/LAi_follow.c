

#define LAI_TMPL_FOLLOW		"follow"

/*
	Возможные состояния:
		"wait"		ждёт цели
		"go"		идёт к цели
		"stay"		стоит у цели
		"pause"		ждёт возможности пройти к цели
		"falure"	дальше шаблон работать не может
*/


bool LAi_tmpl_SetFollow(ref chr, ref follow, float timeout)
{
	if(!LAi_tmpl_follow_InitTemplate(chr)) return false;
	LAi_tmpl_follow_SetFollow(chr, follow, timeout);
	return true;
}

bool LAi_tmpl_follow_IsGo(ref chr)
{
	if(!CheckAttribute(chr, "chr_ai.tmpl.state")) return false;
	if(chr.chr_ai.tmpl.state == "go") return true;
	return false;
}

bool LAi_tmpl_follow_InitTemplate(ref chr)
{
	SendMessage(&chr, "lsl", MSG_CHARACTER_EX_MSG, "LockFightMode", false);
	CharacterPlayAction(chr, "");
	bool isNew = false;
	if(CheckAttribute(chr, "chr_ai.tmpl"))
	{
		if(chr.chr_ai.tmpl != LAI_TMPL_FOLLOW) isNew = true;
	}else{
		isNew = true;
	}
	if(isNew)
	{
		DeleteAttribute(chr, "chr_ai.tmpl");
		chr.chr_ai.tmpl = LAI_TMPL_FOLLOW;
		chr.chr_ai.tmpl.follow = "";
		chr.chr_ai.tmpl.state = "wait";
		chr.chr_ai.tmpl.time = "0";
		chr.chr_ai.tmpl.wait = "0";
		chr.chr_ai.tmpl.timeout = "-1";
		if(LAi_IsInitedAI) SetCharacterTask_Stay(chr);
	}else{
		chr.chr_ai.tmpl.wait = "0";
		if(!CheckAttribute(chr, "chr_ai.tmpl.state")) chr.chr_ai.tmpl.state = "wait";
		if(chr.chr_ai.tmpl.state == "falure") chr.chr_ai.tmpl.state = "wait";
		if(!CheckAttribute(chr, "chr_ai.tmpl.time")) chr.chr_ai.tmpl.time = "0";
		if(!CheckAttribute(chr, "chr_ai.tmpl.timeout")) chr.chr_ai.tmpl.timeout = "-1";
		if(!CheckAttribute(chr, "chr_ai.tmpl.follow"))
		{
			chr.chr_ai.tmpl.follow = "";
			chr.chr_ai.tmpl.state = "wait";
		}else{
			if(chr.chr_ai.tmpl.follow == "") chr.chr_ai.tmpl.state = "wait";
		}
		LAi_tmpl_follow_updatetemplate(chr);
	}
	return true;
}

//Процессирование шаблона персонажа
void LAi_tmpl_follow_CharacterUpdate(ref chr, float dltTime)
{
	aref tmpl;
	makearef(tmpl, chr.chr_ai.tmpl);
	int idx;
	float time, timeout;
	timeout = float(tmpl.timeout);
	if(timeout >= 0.0)
	{
		time = float(tmpl.time);
		if(time < timeout)
		{
			tmpl.time = time + dltTime;
		}else{
			//Trace("Template <follow> -> timeout chr.id = " + chr.id);
			SetCharacterTask_Stay(chr);
			LAi_tmpl_follow_Teleport(chr);			
			tmpl.state = "stay";			
		}
	}
	if(tmpl.state == "stay")
	{
		if(timeout >= 0.0)
		{
			tmpl.timeout = "-1";
			LAi_tmpl_follow_Complite(chr);
		}
	}else{
		if(tmpl.state == "pause")
		{
			time = float(tmpl.wait) - dltTime;
			if(time < 0)
			{
				LAi_tmpl_follow_Go(chr);
			}else{
				tmpl.wait = time;
			}
		}else{
			if(tmpl.state == "wait")
			{
				SetCharacterTask_Stay(chr);
			}
		}
	}
}

//Персонаж выполнил команду  go to point
void LAi_tmpl_follow_EndGoToPoint(ref chr)
{
	LAi_tmpl_follow_updatetemplate(chr);
}

//Персонаж провалил команду  go to point
void LAi_tmpl_follow_FailureGoToPoint(ref chr)
{
	LAi_tmpl_follow_updatetemplate(chr);
}

//Персонаж выполнил команду  run to point
void LAi_tmpl_follow_EndRunToPoint(ref chr)
{	
	LAi_tmpl_follow_updatetemplate(chr);
}

//Персонаж провалил команду  run to point
void LAi_tmpl_follow_FailureRunToPoint(ref chr)
{	
	LAi_tmpl_follow_updatetemplate(chr);
}

//Персонаж не может добраться до точки назначения
void LAi_tmpl_follow_BusyPos(ref chr, float x, float y, float z)
{
	LAi_tmpl_follow_Stop(chr, 1.0 + rand(3));
}

//Персонаж начал перемещение за другим
void LAi_tmpl_follow_FollowGo(ref chr)
{
	chr.chr_ai.tmpl.state = "go";
}

//Персонаж начал дошёл до другого персонажа
void LAi_tmpl_follow_FollowStay(ref chr)
{	
	chr.chr_ai.tmpl.state = "stay";
	LAi_tmpl_follow_Complite(chr);
}

//Персонаж провалил команду  follow character
void LAi_tmpl_follow_FailureFollow(ref chr)
{	
	LAi_tmpl_follow_updatetemplate(chr);
}


//Персонаж начал перемещение за другим
void LAi_tmpl_follow_FightGo(ref chr)
{
	LAi_tmpl_follow_updatetemplate(chr);
}

//Персонаж начал дошёл до другого персонажа
void LAi_tmpl_follow_FightStay(ref chr)
{
	LAi_tmpl_follow_updatetemplate(chr);
}

//Персонаж провалил команду  Fight
void LAi_tmpl_follow_FailureFight(ref chr)
{
	LAi_tmpl_follow_updatetemplate(chr);
}

//Можно ли стрелять
bool LAi_tmpl_follow_IsFire(ref chr)
{	
	return false;
}

//Можно ли использовать оружие
bool LAi_tmpl_follow_IsFight(ref chr)
{
	return false;
}

//Персонаж выполнил команду  escape
void LAi_tmpl_follow_EndEscape(ref chr)
{
	LAi_tmpl_follow_updatetemplate(chr);
}

//Персонаж скользит вдоль патча
void LAi_tmpl_follow_EscapeSlide(ref chr)
{
	LAi_tmpl_follow_updatetemplate(chr);
}

//Персонаж провалил команду  escape
void LAi_tmpl_follow_FailureEscape(ref chr)
{
	LAi_tmpl_follow_updatetemplate(chr);
}


//Персонаж толкается с другими персонажами
void LAi_tmpl_follow_ColThreshold(ref chr)
{
	LAi_tmpl_follow_Stop(chr, 1.0 + rand(3));
}

//Персонаж закончил проигрывать анимацию
void LAi_tmpl_follow_EndAction(ref chr)
{
	LAi_tmpl_follow_updatetemplate(chr);
}


//Персонажа просят освободить место
void LAi_tmpl_follow_FreePos(ref chr, aref who)
{
	LAi_tmpl_follow_Go(chr);
}

//------------------------------------------------------------------------------------------
//Внутреннии функции
//------------------------------------------------------------------------------------------


//Установить за кем следовать
bool LAi_tmpl_follow_SetFollow(ref chr, ref follow, float timeout)
{
	chr.chr_ai.tmpl.follow = follow.index;
	chr.chr_ai.tmpl.state = "go";
	chr.chr_ai.tmpl.timeout = timeout;
	if(LAi_IsInitedAI)
	{
	   if(!SetCharacterTask_FollowCharacter(chr, follow))
	   {
			Trace("Template <follow> -> path not found chr.id = " + chr.id);
			if(LAi_tmpl_follow_Teleport(chr))
			{
				LAi_tmpl_follow_Complite(chr);
			}else{
				chr.chr_ai.tmpl.state = "falure";
				SetCharacterTask_Stay(chr);
				return false;
			}			
	   }
	}
	return true;
}

void LAi_tmpl_follow_Go(ref chr)
{
	if(chr.chr_ai.tmpl.state != "pause") return;
	chr.chr_ai.tmpl.wait = "0";
	chr.chr_ai.tmpl.state = "go";
	LAi_tmpl_follow_updatetemplate(chr);
}

void LAi_tmpl_follow_Stop(ref chr, float time)
{
	if(chr.chr_ai.tmpl.state != "go") return;
	chr.chr_ai.tmpl.wait = time;
	chr.chr_ai.tmpl.state = "pause";
	SetCharacterTask_Stay(chr);
}

bool LAi_tmpl_follow_Teleport(ref chr)
{
	if(float(chr.chr_ai.tmpl.timeout) >= 0)
	{
		if(chr.chr_ai.tmpl.follow == "") return false;
		int idx = int(chr.chr_ai.tmpl.follow);
		float x, y, z;
		if(!GetCharacterPos(chr, &x, &y, &z)) return false;
		//Trace("Template <follow> -> teleport chr.id = " + chr.id + " to pos(" + x + ", " + y + ", " + z + ")");
		TeleportCharacterToPos(chr, x, y, z);
		return true;
	}
	return false;
}

void LAi_tmpl_follow_Complite(ref chr)
{
	LAi_Character_TemplateComplite(chr, LAI_TMPL_FOLLOW);
}

void LAi_tmpl_follow_updatetemplate(ref chr)
{
	bool isGo = false;
	if(chr.chr_ai.tmpl.state == "go") isGo = true;
	if(chr.chr_ai.tmpl.state == "stay") isGo = true;
	if(isGo)
	{
		int idx = int(chr.chr_ai.tmpl.follow);
		LAi_tmpl_follow_SetFollow(chr, &Characters[idx], float(chr.chr_ai.tmpl.timeout));
	}else{
		SetCharacterTask_Stay(chr);
	}
}
