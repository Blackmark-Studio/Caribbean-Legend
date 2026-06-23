

#define LAI_TMPL_ANI	"ani"


void LAi_tmpl_ani_PlayAnimation(ref chr, string actionName, float timeout)
{
	LAi_tmpl_ani_InitTemplate(chr);
	chr.chr_ai.tmpl.animation = "";
	chr.chr_ai.tmpl.time = "0";
	if (timeout == -1) chr.chr_ai.tmpl.animation.playToEnd = true;
	chr.chr_ai.tmpl.timeout = timeout;
	chr.chr_ai.tmpl.animation = actionName;
	if(LAi_IsInitedAI)
	{
		SetCharacterTask_Stay(chr);
		CharacterPlayAction(chr, actionName);
	}
}

bool LAi_tmpl_ani_InitTemplate(ref chr)
{
	SendMessage(&chr, "lsl", MSG_CHARACTER_EX_MSG, "LockFightMode", false);
	CharacterPlayAction(chr, "");
	bool isNew = false;
	if(CheckAttribute(chr, "chr_ai.tmpl"))
	{
		if(chr.chr_ai.tmpl != LAI_TMPL_ANI) isNew = true;
	}else{
		isNew = true;
	}
	if(isNew)
	{
		DeleteAttribute(chr, "chr_ai.tmpl");
		chr.chr_ai.tmpl = LAI_TMPL_ANI;
		chr.chr_ai.tmpl.animation = "";
		chr.chr_ai.tmpl.time = "0";
		chr.chr_ai.tmpl.timeout = "-1";
		if(LAi_IsInitedAI) SetCharacterTask_Stay(chr);
	}else{
		chr.chr_ai.tmpl = LAI_TMPL_ANI;
		if(CheckAttribute(chr, "chr_ai.tmpl.animation") == false)
		{
			chr.chr_ai.tmpl.animation = "";
			chr.chr_ai.tmpl.time = "0";
			chr.chr_ai.tmpl.timeout = "-1";
		}
		if(CheckAttribute(chr, "chr_ai.tmpl.time") == false)
		{
			chr.chr_ai.tmpl.time = "0";
		}
		if(CheckAttribute(chr, "chr_ai.tmpl.timeout") == false)
		{
			chr.chr_ai.tmpl.timeout = "-1";
		}
		LAi_tmpl_ani_UpdateState(chr);
	}
	return true;
}

//Процессирование шаблона персонажа
void LAi_tmpl_ani_CharacterUpdate(ref chr, float dltTime)
{
	if(chr.chr_ai.tmpl.animation != "")
	{
		float timeout = float(chr.chr_ai.tmpl.timeout);
		if(timeout >= 0)
		{
			float time = float(chr.chr_ai.tmpl.time) + dltTime;
			chr.chr_ai.tmpl.time = time;
			if(time > timeout)
			{
				chr.chr_ai.tmpl.timeout = "-1";
				LAi_tmpl_ani_EndAnimation(chr);
			}
		}
	}
}

//Персонаж выполнил команду  go to point
void LAi_tmpl_ani_EndGoToPoint(ref chr)
{
	LAi_tmpl_ani_UpdateState(chr);
}

//Персонаж провалил команду  go to point
void LAi_tmpl_ani_FailureGoToPoint(ref chr)
{
	LAi_tmpl_ani_UpdateState(chr);
}


//Персонаж выполнил команду  run to point
void LAi_tmpl_ani_EndRunToPoint(ref chr)
{
	LAi_tmpl_ani_UpdateState(chr);
}

//Персонаж провалил команду  run to point
void LAi_tmpl_ani_FailureRunToPoint(ref chr)
{
	LAi_tmpl_ani_UpdateState(chr);
}

//Персонаж не может добраться до точки назначения
void LAi_tmpl_ani_BusyPos(ref chr, float x, float y, float z)
{
	LAi_tmpl_ani_UpdateState(chr);
}

//Персонаж начал перемещение за другим
void LAi_tmpl_ani_FollowGo(ref chr)
{
	LAi_tmpl_ani_UpdateState(chr);
}

//Персонаж начал дошёл до другого персонажа
void LAi_tmpl_ani_FollowStay(ref chr)
{
	LAi_tmpl_ani_UpdateState(chr);
}

//Персонаж провалил команду  follow character
void LAi_tmpl_ani_FailureFollow(ref chr)
{
	LAi_tmpl_ani_UpdateState(chr);
}


//Персонаж начал перемещение за другим
void LAi_tmpl_ani_FightGo(ref chr)
{
	LAi_tmpl_ani_UpdateState(chr);
}

//Персонаж начал дошёл до другого персонажа
void LAi_tmpl_ani_FightStay(ref chr)
{
	LAi_tmpl_ani_UpdateState(chr);
}

//Персонаж провалил команду  Fight
void LAi_tmpl_ani_FailureFight(ref chr)
{
	LAi_tmpl_ani_UpdateState(chr);
}

//Можно ли стрелять
bool LAi_tmpl_ani_IsFire(ref chr)
{	
	return false;
}

//Можно ли использовать оружие
bool LAi_tmpl_ani_IsFight(ref chr)
{
	return false;
}


//Персонаж выполнил команду  escape
void LAi_tmpl_ani_EndEscape(ref chr)
{
	LAi_tmpl_ani_UpdateState(chr);
}

//Персонаж скользит вдоль патча
void LAi_tmpl_ani_EscapeSlide(ref chr)
{
	LAi_tmpl_ani_UpdateState(chr);
}

//Персонаж провалил команду  escape
void LAi_tmpl_ani_FailureEscape(ref chr)
{
	LAi_tmpl_ani_UpdateState(chr);
}


//Персонаж толкается с другими персонажами
void LAi_tmpl_ani_ColThreshold(ref chr)
{
    if (!CheckAttribute(chr, "chr_ai.tmpl.ignorecol"))
        LAi_tmpl_ani_UpdateState(chr);
}


//Персонаж закончил проигрывать анимацию
void LAi_tmpl_ani_EndAction(ref chr)
{	
	if(chr.chr_ai.tmpl.animation == "") return;
	chr.chr_ai.tmpl.timeout = "-1"; //бага ещё та!
	LAi_tmpl_ani_EndAnimation(chr);
}


//Персонажа просят освободить место
void LAi_tmpl_ani_FreePos(ref chr, aref who)
{
	LAi_tmpl_ani_UpdateState(chr);
}

//Обновить состояние шаблона
void LAi_tmpl_ani_UpdateState(ref chr)
{
	if(LAi_IsInitedAI)
	{
		if(CharacterGetTask(chr) != "stay")
		{			
			SetCharacterTask_Stay(chr);
		}
		CharacterPlayAction(chr, chr.chr_ai.tmpl.animation);
	}
}

//Завершение проигрывания анимации
void LAi_tmpl_ani_EndAnimation(ref chr)
{
	chr.chr_ai.tmpl.animation = "";
	//--> нужно только для нищего при смене айдлов сидеть-стоять
	if (chr.chr_ai.type == LAI_TYPE_POOR) CharacterPlayAction(chr, "");
	//<-- нужно только для нищего при смене айдлов сидеть-стоять
	if(float(chr.chr_ai.tmpl.timeout) < 0.0 && !CheckAttribute(chr, "chr_ai.tmpl.animation.playToEnd"))
	{
		LAi_Character_TemplateComplite(chr, LAI_TMPL_ANI);
	}
}
